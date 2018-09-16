
// Change this if you're not compiling for an MK3
#include "./variants/1_75mm_MK3-EINSy10a-E3Dv6full.h"

#define STEPS_TO_MM(steps) ((float)steps / axis_steps_per_unit[Z_AXIS])
#define MM_TO_STEPS(z) (int(z * axis_steps_per_unit[Z_AXIS]))

