#include "ultra64.h"
f32 sqrtfWrap(f32);                             /* extern */

void func_8007AC98(f32 *arg0, f32 *arg1, f32 *arg2) {
    f32 temp_fa1;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 temp_fv1_2;

    temp_fv1 = *arg0;
    temp_fa1 = *arg1;
    temp_fv0 = *arg2;
    temp_fv1_2 = 1.0f / sqrtfWrap((temp_fv0 * temp_fv0) + (temp_fv1 * temp_fv1) + (temp_fa1 * temp_fa1));
    *arg0 *= temp_fv1_2;
    *arg1 *= temp_fv1_2;
    *arg2 *= temp_fv1_2;
}
