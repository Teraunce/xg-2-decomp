#include "ultra64.h"
#define M2C_ERROR(x) ((Unk *)0)
/* Warning: missing "jr $ra" in last block of func_8007B368 (initial). */

void func_8007A758(char*, char*);                          /* extern */
void func_8007B178(void *, f32, f32, s32, f32);             /* extern */
extern f32 D_8004C888;

void func_8007B318(f32 arg1, s32 arg0, f32 arg4) {
    s32 sp20;

    func_8007B178(&sp20, arg0, arg1, (s32)M2C_ERROR(/* Read from unset register $f16 */), arg4);
    func_8007A758(&sp20, arg0);
}

void func_8007B368(f32 arg1, s32 arg2, s32 arg3) {

}
