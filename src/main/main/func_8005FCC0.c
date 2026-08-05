#include "ultra64.h"
void func_8005FC3C(void);                              /* extern */
void func_80063878(u16);                               /* extern */
char *func_800639B0(s32);                           /* extern */
s32 func_80063B0C(s32);                             /* extern */
s32 func_80066FD0(s32, s32, void *, s32);              /* extern */
s32 func_80070C88(void *, s32 (*)(void *, s32));                /* extern */
extern s32 D_80092B80;
extern s32 D_80092B88;
extern s32 D_80092B8C;
extern s32 D_80092B90;
extern s32 D_8009334C;
extern s32 *D_80093350;
extern s32 D_80173D08;
extern s32 D_801820D8;
extern Unk D_80182EA8;

void func_8005FCC0(s32 arg3) {
    s32 sp60;
    s32 sp10;
    s32 temp_s0;
    s32 temp_s1;
    s32 temp_v1_2;
    s32 var_a1;
    s32 var_a2;
    s32 var_a3;
    s32 sp;
    s32 var_t0;
    s8 *temp_v0;
    s8 *temp_v1;
    s8 var_a0;
    s8 var_a3_2;
    Unk *temp_v0_2;

    var_a3 = arg3;
    if ((s32)0 /* implicit $v0 from caller */ != 0) {
        D_80092B88 = 0;
    } else {
        D_80092B88 = D_80092B8C;
    }
    if (D_80092B88 & 0x200) {
        var_a2 = 0;
        if (D_80182EA8.unk16DC >= 0xD) {
            D_80182EA8.unk16E0 = 0;
            D_80182EA8.unk16DC = (s32) ((D_80173D08 % 6) + 0xD);
        } else {
            var_a3_2 = 0;
            var_t0 = 0;
            do {
                var_a0 = 0;
                var_a1 = var_t0;
loop_8:
                if ((void *)((var_a1 + &D_80182EA8))->unk4 != 0) {
                    temp_v0 = &sp10 + var_a2;
                    temp_v1 = &sp60 + var_a2;
                    var_a2 += 1;
                    *temp_v0 = var_a3_2;
                    *temp_v1 = var_a0;
                }
                var_a0 += 1;
                var_a1 += 4;
                if (var_a0 < 6) {
                    goto loop_8;
                }
                var_a3_2 += 1;
                var_t0 += 0xD8;
            } while (var_a3_2 < 0xC);
            var_a3 = (s32) D_80173D08 % var_a2;
            sp = 0; D_80182EA8.unk16DC = (s32) ((Unk*)(s32)(sp + var_a3))->unk10;
            D_80182EA8.unk16E0 = (s32) ((Unk*)(s32)(sp + var_a3))->unk60;
        }
    }
    temp_s1 = D_80182EA8.unk16D8;
    D_8009334C = 0;
    D_80093350 = (D_80182EA8.unk16DC * 0xD8) + (&D_80182EA8 + 0x1C) + (D_80182EA8.unk16E0 * 0x10);
    if (temp_s1 == 1) {
        temp_v1_2 = ((Unk*)D_80182EA8.unk16F8)->unk8;
        if ((temp_v1_2 >= 0xA) && (temp_v1_2 < 0xD)) {
            temp_s0 = func_80063B0C(func_80066FD0(D_80182EA8.unk16DC, D_80182EA8.unk16E0, &D_80182EA8, var_a3)) & 0xFFFF;
            temp_v0_2 = func_800639B0(temp_s0);
            if (temp_v0_2->unkC < *D_80093350) {
                D_8009334C = temp_s1;
                D_80093350 = &D_80092B90;
                D_80092B90 = temp_v0_2->unkC;
            }
            func_80063878(temp_s0);
        }
    }
    if (D_80092B80 != 0) {
        func_8005FC3C();
        return;
    }
    func_80070C88(&D_801820D8, func_8005FC3C);
}

void func_8005FF2C(void) {

}
