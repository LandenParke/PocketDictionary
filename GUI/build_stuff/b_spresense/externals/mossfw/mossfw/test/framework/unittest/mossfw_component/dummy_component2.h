/****************************************************************************
 * path/to/correct/directory/dummy_component1.c
 *
 * After finished discussion, LICENSE description should be added.
 *
 ****************************************************************************/

#ifndef __DUMMY_CONPONENT2_H
#define __DUMMY_CONPONENT2_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <mossfw/mossfw_component.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define DUMMY2_ACCELTYPE  (MOSSFW_DATA_TYPE_SHORT + \
                           MOSSFW_DATA_TYPEGRP_V3 + \
                           MOSSFW_DATA_TYPENAME_ACCEL + \
                           MOSSFW_DATA_TYPEARRAY_SINGLE)

#define DUMMY2_GYROTYPE   (MOSSFW_DATA_TYPE_SHORT + \
                           MOSSFW_DATA_TYPEGRP_V3 + \
                           MOSSFW_DATA_TYPENAME_GYRO + \
                           MOSSFW_DATA_TYPEARRAY_SINGLE)

#define DUMMY2_OUTPUTTYPE  (MOSSFW_DATA_TYPE_FLOAT + \
                            MOSSFW_DATA_TYPEGRP_V3 + \
                            MOSSFW_DATA_TYPENAME_GYRO + \
                            MOSSFW_DATA_TYPEARRAY_ARRAY)

/****************************************************************************
 * Public Function Prorotypes
 ****************************************************************************/

void init_dummy2(mossfw_allocator_t *alc);
void final_dummy2(void);
mossfw_input_t *dummy2_get_accelinput(void);
mossfw_input_t *dummy2_get_gyroinput(void);
mossfw_output_t *dummy2_get_output(void);

#endif  /* __DUMMY_CONPONENT2_H */
