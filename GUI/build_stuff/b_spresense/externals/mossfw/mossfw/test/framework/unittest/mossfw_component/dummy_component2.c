/****************************************************************************
 * path/to/correct/directory/dummy_component1.c
 *
 * After finished discussion, LICENSE description should be added.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <mossfw/mossfw_debug.h>
#include <mossfw/mossfw_lock.h>
#include <mossfw/mossfw_memoryallocator.h>
#include <mossfw/mossfw_component.h>
#include <dummy_component2.h>
#include <unity.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define DUMMY2_BLKNUM      (2)
#define CALLBACK_ASYNC (true)

/****************************************************************************
 * Private Data Types
 ****************************************************************************/

static struct dummy2_s
{
  mossfw_input_t *accel;
  mossfw_input_t *gyro;
  mossfw_callback_op_t *op;
  mossfw_output_t *out;
  mossfw_allocator_t *alloc;
  mossfw_data_t *curbuf;
  int curnum;
  int allocbuf_size;
  int dbgcnt;
  mossfw_onedata_t accel_dat;
  mossfw_onedata_t gyro_dat;
  int acceldat_exist;
  int gyrodat_exist;
} dummy2;

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * name: maincode_of_algorighm
 ****************************************************************************/

static void maincode_of_algorithm(short *accel,
                                  short *gyro,
                                  float *result)
{
  /*
   * This is an example for inprementation of the algorithm.
   * No meaning for below calcuation.
   */

  result[0] = (float)(accel[0] + gyro[0] * 2);
  result[1] = (float)(accel[1] + gyro[1] * 2);
  result[2] = (float)(accel[2] + gyro[2] * 2);
}

/****************************************************************************
 * name: dummy2_operate_cb
 ****************************************************************************/

static int dummy2_operate_cb(mossfw_callback_op_t *op, unsigned long arg)
{
  int ret;
  mossfw_onedata_t accel;
  mossfw_onedata_t gyro;

  (void)op;
  (void)arg;

  dummy2.dbgcnt++;

  /*
   * Confirm if all needed data is collected.
   * Othewise, nothing to do.
   */

  if (mossfw_get_delivereddata_num(dummy2.accel) >= (int)sizeof(accel.xyzs) &&
      mossfw_get_delivereddata_num(dummy2.gyro)  >= (int)sizeof(gyro.xyzs) )
    {
      if (dummy2.curbuf == NULL)
        {
          dummy2.curbuf = mossfw_data_alloc(dummy2.alloc,
                                               dummy2.allocbuf_size, false);

          TEST_ASSERT_NOT_EQUAL(NULL, dummy2.curbuf);
        }

      mossfw_get_delivereddata_single(dummy2.accel, &accel);
      mossfw_get_delivereddata_single(dummy2.gyro,  &gyro);

      /* Call actual algorithm code to calculate something */

      maincode_of_algorithm((short *)&accel.xyzs,
                            (short *)&gyro.xyzs,
                            (float *)&dummy2.curbuf->data.xyzf[dummy2.curnum]);

      dummy2.curnum++;
      dummy2.curbuf->data_bytes += sizeof(mossfw_data_v3f_t);
      if (dummy2.curbuf->data_bytes >= dummy2.allocbuf_size)
        {
          /*
           * If the allocated memory is full,
           * deliver the memory block to output.
           */

          ret = mossfw_deliver_dataarray(dummy2.out, dummy2.curbuf);
          TEST_ASSERT_EQUAL(OK, ret);
          mossfw_data_free(dummy2.curbuf);
          dummy2.curbuf = NULL;
          dummy2.curnum = 0;
        }
    }

  return OK;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * name: init_dummy2
 ****************************************************************************/

void init_dummy2(mossfw_allocator_t *alc)
{
  /* Create in / out connector */

  dummy2.accel = mossfw_input_create(DUMMY2_ACCELTYPE, DUMMY2_BLKNUM);
  dummy2.gyro = mossfw_input_create(DUMMY2_GYROTYPE, DUMMY2_BLKNUM);
  dummy2.op = mossfw_callback_op_create(dummy2_operate_cb, 0, CALLBACK_ASYNC);
  dummy2.out = mossfw_output_create(DUMMY2_OUTPUTTYPE);
  dummy2.alloc = alc;
  dummy2.curbuf = NULL;
  dummy2.curnum = 0;
  dummy2.allocbuf_size = mossfw_fixedsize_allocator(alc);
  dummy2.dbgcnt = 0;
  dummy2.acceldat_exist = 0;
  dummy2.gyrodat_exist = 0;

  /* Set callback function as sync. */

  mossfw_set_waitcondition(dummy2.accel, sizeof(mossfw_data_v3s_t),
                        dummy2.op);
  mossfw_set_waitcondition(dummy2.gyro, sizeof(mossfw_data_v3s_t),
                        dummy2.op);

  /*
   * If any other initialization for this component,
   * it should be described here.
   */
}

/****************************************************************************
 * name: final_dummy2
 ****************************************************************************/

void final_dummy2(void)
{
   mossfw_callback_op_delete(dummy2.op);
  mossfw_input_delete(dummy2.accel);
  mossfw_input_delete(dummy2.gyro);
  mossfw_output_delete(dummy2.out);

  if (dummy2.curbuf)
    {
      mossfw_data_free(dummy2.curbuf);
    }
}

/****************************************************************************
 * name: dummy2_get_accelinput
 ****************************************************************************/

mossfw_input_t *dummy2_get_accelinput(void)
{
  return dummy2.accel;
}

/****************************************************************************
 * name: dummy2_get_gyroinput
 ****************************************************************************/

mossfw_input_t *dummy2_get_gyroinput(void)
{
  return dummy2.gyro;
}

/****************************************************************************
 * name: dummy2_get_output
 ****************************************************************************/

mossfw_output_t *dummy2_get_output(void)
{
  return dummy2.out;
}
