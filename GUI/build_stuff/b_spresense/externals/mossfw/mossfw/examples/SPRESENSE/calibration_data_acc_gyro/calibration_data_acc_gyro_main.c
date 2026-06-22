/****************************************************************************
 * Copyright 2023 Sony Semiconductor Solutions Corporation
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <stdio.h>

#include <sys/ioctl.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <time.h>
#include <errno.h>
#include <assert.h>

#include <nuttx/sensors/bmi160.h>
#include <arch/chip/scu.h>
#include <arch/board/cxd56_sdcard.h>
#include <arch/board/board.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define SAMPLING_LOOP_COUNT 5

#define ACC_DEVPATH      "/dev/accel0"
#define CONFIG_EXAMPLES_ACC_SIGNO 12
#define SCU_BUFFER_SIZE 2000
#define WATERMARK_COUNT 100
#define TIMEOUT_SEC     10
#define TIMEOUT_NSEC    0
#define CONFIG_EXAMPLES_MAG_SIGNO 14
#define SD_ACC_DEVPATH  "/mnt/sd0/acc.mat"
#define SD_GYR_DEVPATH  "/mnt/sd0/gyr.mat"
#define SD_MAG_DEVPATH  "/mnt/sd0/mag.mat"

#define SCU_RATE_1600HZ 1
#define SCU_RATE_800HZ  2
#define SCU_RATE_400HZ  3
#define SCU_RATE_200HZ  4
#define SCU_RATE_100HZ  5
#define SCU_RATE_50HZ   6

#define SCU_SAMPLE_RATE SCU_RATE_100HZ

#define TIME_OFFSET     (1.0 / (32768.0 / 10.0 / SCU_SAMPLE_RATE))

struct three_axis_s
{
  uint16_t x;
  uint16_t y;
  uint16_t z;
};

#define ACC_EN  1
#define GYRO_EN 1
#define MAG_EN  0

/****************************************************************************
 * Private Data
 ****************************************************************************/

static FILE *fp;

#if ACC_EN
static int fd_acc;
static void *buffer_acc;
static FILE *fp_acc;
#endif
#if GYRO_EN
static int fd_gyr;
static void *buffer_gyr;
static FILE *fp_gyr;
#endif
#if MAG_EN
static int fd_mag;
static void *buffer_mag;
static FILE *fp_mag;
#endif

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * name: tick_to_msec
 ****************************************************************************/

static float tick_to_msec(uint32_t sec, uint16_t tick, int num)
{
  float time;
  time = ((float)tick / 32768);
  time += (float)num * (TIME_OFFSET);
  time += sec;

  return time;
}

/****************************************************************************
 * name: scu_setup
 ****************************************************************************/

static int scu_setup(int fd, int size, int rate)
{
  int ret;

  /* Set FIFO size to 6 (bytes) * 128 (Hz).
   * This size is enough to store 0.5 second data without overwrite
   * if task has been delayed.
   */

  ret = ioctl(fd, SCUIOC_SETFIFO, size);
  if (ret < 0)
    {
      fprintf(stderr, "SETFIFO failed. %d\n", ret);
      return ret;
    }

  /* Set sequencer sampling rate 128 Hz
   * (if config CXD56_SCU_PREDIV = 64)
   * 32768 / 64 / (2 ^ 2) = 128
   */

  ret = ioctl(fd, SCUIOC_SETSAMPLE, rate);
  if (ret < 0)
    {
      fprintf(stderr, "SETSAMPLE failed. %d\n", ret);
      return ret;
    }

  return OK;
}

/****************************************************************************
 * name: sensing_init
 ****************************************************************************/

static void sensing_init(void)
{
  int ret;

  /* Allocate memory for picking up sensing data */
#if ACC_EN
  buffer_acc = malloc(SCU_BUFFER_SIZE);
  if (!buffer_acc)
    {
      fprintf(stderr, "Memory allocation failure.\n");
      return;
    }

  memset(buffer_acc, 0, SCU_BUFFER_SIZE);

  ret = scu_setup(fd_acc, SCU_BUFFER_SIZE, SCU_SAMPLE_RATE);
  if (ret < 0)
    {
      free(buffer_acc);
      return;
    }

#endif
#if GYRO_EN
  buffer_gyr = malloc(SCU_BUFFER_SIZE);
  if (!buffer_gyr)
    {
      fprintf(stderr, "Memory allocation failure.\n");
      return;
    }

  memset(buffer_gyr, 0, SCU_BUFFER_SIZE);

  ret = scu_setup(fd_gyr, SCU_BUFFER_SIZE, SCU_SAMPLE_RATE);
  if (ret < 0)
    {
      free(buffer_gyr);
      return;
    }

#endif
#if MAG_EN
  buffer_mag = malloc(SCU_BUFFER_SIZE);
  if (!buffer_mag)
    {
      fprintf(stderr, "Memory allocation failure.\n");
      return;
    }

  memset(buffer_mag, 0, SCU_BUFFER_SIZE);

  ret = scu_setup(fd_mag, SCU_BUFFER_SIZE, SCU_SAMPLE_RATE);
  if (ret < 0)
    {
      free(buffer_mag);
      return;
    }

#endif
}

/****************************************************************************
 * name: sensing_main
 ****************************************************************************/

static void sensing_main(void)
{
  sigset_t set;
  int ret;
  int i;
  int j;
  struct siginfo value;
  struct scufifo_wm_s wm;
  struct scutimestamp_s ts;
  struct timespec timeout;
  struct scutimestamp_s *ts_p;
  struct three_axis_s *ta;
  float timestamp;
#if ACC_EN
  int count_acc = 0;
#endif
#if GYRO_EN
  int count_gyr = 0;
#endif
#if MAG_EN
  int count_mag = 0;
#endif

#if ACC_EN
  wm.signo = CONFIG_EXAMPLES_ACC_SIGNO;
  wm.ts = &ts;
  wm.watermark = WATERMARK_COUNT;
  ret = ioctl(fd_acc, SCUIOC_SETWATERMARK, (unsigned long)(uintptr_t)&wm);
#elif GYRO_EN
  wm.signo = CONFIG_EXAMPLES_GYRO_SIGNO;
  wm.ts = &ts;
  wm.watermark = WATERMARK_COUNT;
  ret = ioctl(fd_gyr, SCUIOC_SETWATERMARK, (unsigned long)(uintptr_t)&wm);
#elif MAG_EN
  wm.signo = CONFIG_EXAMPLES_MAG_SIGNO;
  wm.ts = &ts;
  wm.watermark = WATERMARK_COUNT;
  ret = ioctl(fd_mag, SCUIOC_SETWATERMARK, (unsigned long)(uintptr_t)&wm);
#endif
  if (ret < 0)
    {
      printf("SETWATERMARK failed. %d\n", ret);
      return;
    }

  /* Set timeout 10 seconds, SCU may send signal every 1 second. */

  timeout.tv_sec  = TIMEOUT_SEC;
  timeout.tv_nsec = TIMEOUT_NSEC;

  /* Start sequencer */
#if ACC_EN
  ret = ioctl(fd_acc, SCUIOC_START, 0);
  if (ret != 0)
    {
      fprintf(stderr, "Sequencer start failed. %d\n", errno);
      free(buffer_acc);
      return;
    }

#endif
#if GYRO_EN
  ret = ioctl(fd_gyr, SCUIOC_START, 0);
  if (ret != 0)
    {
      fprintf(stderr, "Sequencer start failed. %d\n", errno);
      free(buffer_gyr);
      return;
    }

#endif
#if MAG_EN
  ret = ioctl(fd_mag, SCUIOC_START, 0);
  if (ret != 0)
    {
      fprintf(stderr, "Sequencer start failed. %d\n", errno);
      free(buffer_mag);
      return;
    }

#endif

#if SAMPLING_LOOP_COUNT
  for (i = 0; i < SAMPLING_LOOP_COUNT; i++)
#else
  for (; ; )
#endif
    {
      sigemptyset(&set);
#if ACC_EN
      sigaddset(&set, CONFIG_EXAMPLES_ACC_SIGNO);
#elif GYRO_EN
      sigaddset(&set, CONFIG_EXAMPLES_GYRO_SIGNO);
#elif MAG_EN
      sigaddset(&set, CONFIG_EXAMPLES_MAG_SIGNO);
#endif
      ret = sigtimedwait(&set, &value, &timeout);
      if (ret < 0)
        {
          int errcode = errno;

          if (errcode != EAGAIN)
            {
              fprintf(stderr, "ERROR: sigtimedwait() failed: %d\n", errcode);
              return;
            }

          printf("Timeout!\n");
          return;
        }

      ts_p = value.si_value.sival_ptr;

#if ACC_EN
      count_acc = read(fd_acc, buffer_acc, SCU_BUFFER_SIZE);
#endif
#if GYRO_EN
      count_gyr = read(fd_gyr, buffer_gyr, SCU_BUFFER_SIZE);
#endif
#if MAG_EN
      count_mag = read(fd_mag, buffer_mag, SCU_BUFFER_SIZE);
#endif
#if ACC_EN
      if (count_acc < 0)
        {
          fprintf(stderr, "Read error %d.\n", errno);
        }
      else
        {
          fprintf(fp, "acc %03d samples read.\n",
            count_acc / sizeof(struct three_axis_s));
          ta = buffer_acc;
          for (j = 0; j < count_acc / sizeof(struct three_axis_s); j++)
            {
              timestamp = tick_to_msec(ts_p->sec, ts_p->tick, j);
              fprintf(fp_acc, "   %e   %e   %e   %e\n",
                        timestamp, (float)ta->x, (float)ta->y, (float)ta->z);
              ta++;
            }
        }

#endif
#if GYRO_EN
      if (count_gyr < 0)
        {
          fprintf(stderr, "Read error %d.\n", errno);
        }
      else
        {
          fprintf(fp, "gyr %03d samples read.\n",
            count_gyr / sizeof(struct three_axis_s));
          ta = buffer_gyr;
          for (j = 0; j < count_gyr / sizeof(struct three_axis_s); j++)
            {
              timestamp = tick_to_msec(ts_p->sec, ts_p->tick, j);
              fprintf(fp_gyr, "   %e   %e   %e   %e\n",
                        timestamp, (float)ta->x, (float)ta->y, (float)ta->z);
              ta++;
            }
        }

#endif
#if MAG_EN
      if (count_mag < 0)
        {
          fprintf(stderr, "Read error %d.\n", errno);
        }
      else
        {
          fprintf(fp, "mag %03d samples read.\n",
            count_mag / sizeof(struct three_axis_s));
          ta = buffer_mag;
          for (j = 0; j < count_mag / sizeof(struct three_axis_s); j++)
            {
              timestamp = tick_to_msec(ts_p->sec, ts_p->tick, j);
              fprintf(fp_mag, "   %e   %e   %e   %e\n",
                        timestamp, (float)ta->x, (float)ta->y, (float)ta->z);
              ta++;
            }
        }
#endif
    }

  /* Stop sequencer */

#if ACC_EN
  (void) ioctl(fd_acc, SCUIOC_STOP, 0);
#endif
#if GYRO_EN
  (void) ioctl(fd_gyr, SCUIOC_STOP, 0);
#endif
#if MAG_EN
  (void) ioctl(fd_mag, SCUIOC_STOP, 0);
#endif

  return;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * name: main
 ****************************************************************************/

int main(int argc, char *argv[])
{
  fp = fopen("/dev/ttyS0", "w");

#if ACC_EN
  fp_acc = fopen(SD_ACC_DEVPATH, "w");
  fd_acc = open(ACC_DEVPATH, O_RDONLY);
  if (fd_acc < 0)
    {
      fprintf(stderr, "Device %s open failure. %d\n", ACC_DEVPATH, fd_acc);
      return -1;
    }

#endif
#if GYRO_EN
  fp_gyr = fopen(SD_GYR_DEVPATH, "w");
  fd_gyr = open(CONFIG_EXAMPLES_GYRO_DEVNAME, O_RDONLY);
  if (fd_gyr < 0)
    {
      printf("Device %s open failure. %d\n",
  CONFIG_EXAMPLES_GYRO_DEVNAME, fd_gyr);
      return -1;
    }

#endif
#if MAG_EN
  fp_mag = fopen(SD_MAG_DEVPATH, "w");
  fd_mag = open(CONFIG_EXAMPLES_MAG_DEVNAME, O_RDONLY);
  if (fd_mag < 0)
    {
      printf("Device %s open failure. %d\n",
  CONFIG_EXAMPLES_MAG_DEVNAME, fd_mag);
      return -1;
    }

#endif

  printf("Sensing start...\n");

  sensing_init();

  sensing_main();

#if ACC_EN
  free(buffer_acc);
  close(fd_acc);
  fclose(fp_acc);
#endif
#if GYRO_EN
  free(buffer_gyr);
  close(fd_gyr);
  fclose(fp_gyr);
#endif
#if MAG_EN
  free(buffer_mag);
  close(fd_mag);
  fclose(fp_mag);
#endif

  printf("Sensing end...\n");

  return 0;
}
