/****************************************************************************
 * path/to/correct/directory/dummy_component1.c
 *
 * After finished discussion, LICENSE description should be added.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <mossfw/mossfw_component.h>
#include <dummy_component1.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define DUMMY1_BLKNUM      (2)

/****************************************************************************
 * Private Data Types
 ****************************************************************************/

static struct dummy1_s
{
  mossfw_input_t *accel;
  mossfw_input_t *gyro;
  mossfw_output_t *out;
  mossfw_callback_op_t *op;
} dummy1;

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

  result[0] = (float)(accel[0] + gyro[0]);
  result[1] = (float)(accel[1] + gyro[1]);
  result[2] = (float)(accel[2] + gyro[2]);
}

/****************************************************************************
 * name: dummy1_operate_cb
 ****************************************************************************/

static int dummy1_operate_cb(mossfw_callback_op_t *op, unsigned long arg)
{
  mossfw_onedata_t accel;
  mossfw_onedata_t gyro;
  mossfw_onedata_t result;

  (void)op;
  (void)arg;

  /*
   * Confirm if all needed data is collected.
   * Othewise, nothing to do.
   */

  if (mossfw_get_delivereddata_num(dummy1.accel) >= (int)sizeof(accel.xyzs) &&
      mossfw_get_delivereddata_num(dummy1.gyro)  >= (int)sizeof(gyro.xyzs) )
    {
      /* Call actual algorithm code to calculate something */

      mossfw_get_delivereddata_single(dummy1.accel, &accel);
      mossfw_get_delivereddata_single(dummy1.gyro,  &gyro);

      maincode_of_algorithm((short *)&accel.xyzs,
                            (short *)&gyro.xyzs,
                            (float *)&result.xyzf);
      mossfw_deliver_data(dummy1.out, &result);
    }

  return OK;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * name: init_dummy1
 ****************************************************************************/

void init_dummy1(void)
{
  /* Create in / out connector */

  dummy1.accel = mossfw_input_create(DUMMY1_ACCELTYPE, DUMMY1_BLKNUM);
  dummy1.gyro = mossfw_input_create(DUMMY1_GYROTYPE, DUMMY1_BLKNUM);
  dummy1.out = mossfw_output_create(DUMMY1_OUTPUTTYPE);
  dummy1.op = mossfw_callback_op_create(dummy1_operate_cb, 0, false);

  /* Set callback function as sync. */

  mossfw_set_waitcondition(dummy1.accel, sizeof(mossfw_data_v3s_t),
                        dummy1.op);
  mossfw_set_waitcondition(dummy1.gyro, sizeof(mossfw_data_v3s_t),
                        dummy1.op);

  /*
   * If any other initialization for this component,
   * it should be described here.
   */
}

/****************************************************************************
 * name: final_dummy1
 ****************************************************************************/

void final_dummy1(void)
{
  mossfw_callback_op_delete(dummy1.op);
  mossfw_input_delete(dummy1.accel);
  mossfw_input_delete(dummy1.gyro);
  mossfw_output_delete(dummy1.out);
}

/****************************************************************************
 * name: dummy1_get_accelinput
 ****************************************************************************/

mossfw_input_t *dummy1_get_accelinput(void)
{
  return dummy1.accel;
}

/****************************************************************************
 * name: dummy1_get_gyroinput
 ****************************************************************************/

mossfw_input_t *dummy1_get_gyroinput(void)
{
  return dummy1.gyro;
}

/****************************************************************************
 * name: dummy1_get_output
 ****************************************************************************/

mossfw_output_t *dummy1_get_output(void)
{
  return dummy1.out;
}
