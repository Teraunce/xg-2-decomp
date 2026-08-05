#include "ultra64.h"
#define M2C_ERROR(x) ((Unk *)0)
void func_80086078();                                  /* extern */
extern s32 D_800952D0;

void func_8007DA74(void) {
    if ((s32)M2C_ERROR(/* Read from unset register $t6 */) != 0) {
        func_80086078();
        D_800952D0 = 0;
    }
}

void func_8007DAA4(void) {

}
