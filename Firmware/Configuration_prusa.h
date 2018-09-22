

#define CUSTOM_REV_NUM 2


#define FW_MK3
// #define FW_MK25_13A
//#define FW_MK25_10A

#if defined(FW_MK3)
#include "./variants/1_75mm_MK3-EINSy10a-E3Dv6full.h"
#define M951
#elif defined(FW_MK25_13A)
#include "./variants/1_75mm_MK25-RAMBo13a-E3Dv6full.h"
#elif defined(FW_MK25_10A)
#include "./variants/1_75mm_MK25-RAMBo10a-E3Dv6full.h"
#endif

#define STEPS_TO_MM(steps) ((float)steps / axis_steps_per_unit[Z_AXIS])
#define MM_TO_STEPS(z) (int(z * axis_steps_per_unit[Z_AXIS]))


// #define DEBUG_BABYSTEP
// #define DEBUG_SetLiveZ
