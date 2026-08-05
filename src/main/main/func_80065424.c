#include "ultra64.h"
#define M2C_ERROR(x) ((Unk *)0)
void func_8006114C(void**);                               /* extern */
u16 func_8006421C(void**, Unk*, u32, s16, s32, u32);      /* extern */
extern Unk *D_80182408;
extern s16 D_8018240C;
extern Unk *D_80182410;
extern u16 D_80182414;
extern s32 D_80182418;
extern s16 D_80182458;

void func_80065424(s32 arg0) {
    s32 temp_s0;
    s32 var_s0;
    s32 var_s1;
    u32 var_s2;
    u32 var_v0;
    Unk *temp_v0;
    Unk *temp_v1;

    if ((s32)M2C_ERROR(/* Read from unset register $v0 */) != 0) {
        var_s2 = 0;
        if (D_80182414 != 0) {
            var_s1 = 0;
            do {
                var_v0 = *(s32 *)((char *)D_80182410 + var_s1);
                if (var_v0 != 0) {
                    var_s0 = var_v0 * 2;
                    do {
                        temp_s0 = (var_s0 + var_v0) * 2;
                        temp_v0 = (Unk *)((char *)D_80182408 + temp_s0);
                        temp_v1 = (Unk *)((char *)D_80182410 + var_s1);
                        func_8006421C(arg0, temp_v1->unk8, temp_v1->unk4, temp_v0->unk2, (s32) temp_v0->unk4, *(((temp_v0->unk0 & 0xF) * 4) + &D_80182418));
                        var_v0 = (u16) *(s32 *)((char *)D_80182408 + temp_s0) >> 4;
                        var_s0 = var_v0 * 2;
                    } while (var_v0 != 0);
                }
                var_s2 += 1;
                var_s1 += 0xC;
            } while (var_s2 < (u16) D_80182414);
        }
        func_8006114C(arg0);
        D_8018240C = 1;
        D_80182458 = 0;
        D_80182414 = 0;
    }
}
