
/****************************************************************************
 * path/to/correct/directory/dummy_func1.c
 *
 * After finished discussion, LICENSE description should be added.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#undef malloc
#undef pthread_cond_wait

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "mossfw/mossfw_ringbuffary.h"

/****************************************************************************
 * Private Deta
 ****************************************************************************/

static int count = 0;
static int malloc_pettern_before = 0;
static int wait_pettern_before = 0;

/****************************************************************************
 * Public Deta
 ****************************************************************************/

int err_ringbuffarray_malloc_pettern = 0;
int err_ringbuffarray_wait_pettern = 0;
mossfw_ringbuffarray_t *err_ringbuffarray_buff;

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * name: dummy_malloc
 ****************************************************************************/

void *dummy_malloc(size_t size)
{
    void *ret;

    if(malloc_pettern_before != err_ringbuffarray_malloc_pettern)
      {
        count = 0;
      }
    malloc_pettern_before = err_ringbuffarray_malloc_pettern;

    switch (err_ringbuffarray_malloc_pettern)
    {
    case 1 :
      if(0 == count) {
        ret = NULL;
      }
      else {
        ret = NULL;
      }
      count++;
      break;
    case 2 :
      if(0 == count) {
        ret = malloc(size);
      }
      else {
        ret = NULL;
      }
      count++;
      break;

    default:
      ret = malloc(size);
      break;
    }

    return ret;
}

/****************************************************************************
 * name: dummy_condition_wait
 ****************************************************************************/

int dummy_condition_wait(pthread_cond_t * cond,
			      pthread_mutex_t * mutex)
{
    if(wait_pettern_before != err_ringbuffarray_wait_pettern)
      {
        count = 0;
      }
    wait_pettern_before = err_ringbuffarray_wait_pettern;

    switch (err_ringbuffarray_wait_pettern)
    {
    case 1 :
      if(0 == count)
        {
          cond->__data.__g1_orig_size = 0;
          mutex->__data.__count = 0;
          err_ringbuffarray_buff->stored_num = 64;
        }
      else
       {
          cond->__data.__g1_orig_size = 0;
          mutex->__data.__count = 0;
          err_ringbuffarray_buff->stored_num = 1;
        }
      count++;
      break;
    case 2 :
      if(0 == count)
        {
          cond->__data.__g1_orig_size = 0;
          mutex->__data.__count = 0;
          err_ringbuffarray_buff->stored = NULL;
        }
      else
       {
          cond->__data.__g1_orig_size = 0;
          mutex->__data.__count = 0;
          err_ringbuffarray_buff->stored = (mossfw_data_container_t *)err_ringbuffarray_buff;
        }
      count++;
      break;
    default :
      break;
    }

  return 0;
}
