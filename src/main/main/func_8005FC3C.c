#include "ultra64.h"
void func_800620CC(void*);                               /* extern */
s32 func_800621B0();                                /* extern */
s32 func_800621C0(s32, s32);                          /* extern */
void func_80063E24();                                  /* extern */
extern s32 D_80091E54;
extern s32 D_80092B80;
extern s32 D_80173D08;
extern s32 D_80181E48;
extern s32 D_80181E4C;

void func_8005FC3C(void) {
    s32 var_s0;

    func_80063E24();
    if (D_80181E48 == 0) {
        D_80181E48 = 1;
        D_80181E4C = D_80173D08;
        var_s0 = func_800621B0() - 1;
        if (var_s0 >= 0) {
            do {
                func_800620CC(func_800621C0(var_s0, 0));
                var_s0 -= 1;
            } while (var_s0 >= 0);
        }
        D_80091E54 = 0;
    }
}

s32 func_8005FCB8(void) {
    return D_80092B80;
}
