/****************************************************************************
 * path/to/correct/directory/dummy_component1.c
 *
 * After finished discussion, LICENSE description should be added.
 *
 ****************************************************************************/

#ifndef __DUMMY_CONPONENT1_H
#define __DUMMY_CONPONENT1_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <mossfw/mossfw_component.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define DUMMY1_ACCELTYPE  (MOSSFW_DATA_TYPE_SHORT + \
                           MOSSFW_DATA_TYPEGRP_V3 + \
                           MOSSFW_DATA_TYPENAME_ACCEL + \
                           MOSSFW_DATA_TYPEARRAY_SINGLE)

#define DUMMY1_GYROTYPE   (MOSSFW_DATA_TYPE_SHORT + \
                           MOSSFW_DATA_TYPEGRP_V3 + \
                           MOSSFW_DATA_TYPENAME_GYRO + \
                           MOSSFW_DATA_TYPEARRAY_SINGLE)

#define DUMMY1_OUTPUTTYPE  (MOSSFW_DATA_TYPE_FLOAT + \
                            MOSSFW_DATA_TYPEGRP_V3 + \
                            MOSSFW_DATA_TYPENAME_GYRO + \
                            MOSSFW_DATA_TYPEARRAY_SINGLE)

/****************************************************************************
 * Public Function Prorotypes
 ****************************************************************************/

void init_dummy1(void);
void final_dummy1(void);
mossfw_input_t *dummy1_get_accelinput(void);
mossfw_input_t *dummy1_get_gyroinput(void);
mossfw_output_t *dummy1_get_output(void);

#endif  /* __DUMMY_CONPONENT1_H */
