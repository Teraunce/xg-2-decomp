#include "ultra64.h"
s32 osVirtualToPhysical(u32);                             /* extern */
void func_8007DA18(Unk*);                               /* extern */
void func_8007DA48(Unk*, void**);                       /* extern */
s32 func_8008E518(Unk*, s32, s32, s32, s32, s32, s32);  /* extern */
extern s32 D_800927D8;
extern s32 D_8017EFC8;
extern s32 D_8017F448;
extern s32 D_801816A8;
extern Unk D_80181E30;
extern char *D_80181E34;

s32 func_8005BDF0(s32 arg0, s32 arg1) {
    char *temp_a0;
    Unk *temp_s0;
    Unk *temp_s1;
    s32 temp_s2;
    s32 temp_s3;
    s32 temp_v0;
    s32 var_s0;
    char *temp_a0_2;
    char *var_s0_2;
    Unk *var_s1;

    var_s0_2 = NULL;
    var_s1 = D_80181E34;
    if (var_s1 != NULL) {
loop_1:
        temp_v0 = var_s1->unk8;
        if (arg0 >= temp_v0) {
            var_s0_2 = var_s1;
            if ((temp_v0 + 0x300) < (arg0 + arg1)) {
                var_s1 = var_s1->unk0;
                if (var_s1 == NULL) {
                    goto block_4;
                }
                goto loop_1;
            }
            var_s1->unkC = (s32) D_801816A8;
            return osVirtualToPhysical((var_s1->unk10 + arg0) - var_s1->unk8);
        }
        goto block_4;
    }
block_4:
    temp_s1 = D_80181E30.unk8;
    temp_a0 = temp_s1;
    D_80181E30.unk8 = (void *) temp_s1->unk0;
    func_8007DA18(temp_a0);
    if (var_s0_2 != NULL) {
        func_8007DA48(temp_s1, var_s0_2);
        var_s0 = arg0 & 1;
    } else {
        temp_s0 = D_80181E30.unk4;
        if (D_80181E30.unk4 != 0) {
            D_80181E30.unk4 = temp_s1;
            temp_s1->unk0 = temp_s0;
            temp_s1->unk4 = 0;
            temp_s0->unk4 = temp_s1;
        } else {
            D_80181E30.unk4 = temp_s1;
            temp_s1->unk0 = 0;
            temp_s1->unk4 = 0;
        }
        var_s0 = arg0 & 1;
    }
    temp_s3 = arg0 - var_s0;
    temp_s2 = temp_s1->unk10;
    temp_s1->unk8 = temp_s3;
    temp_a0_2 = (D_800927D8 * 0x18) + &D_8017F448;
    temp_s1->unkC = (s32) D_801816A8;
    D_800927D8 += 1;
    func_8008E518(temp_a0_2, 0, 0, temp_s3, temp_s2, 0x300, &D_8017EFC8);
    return osVirtualToPhysical(temp_s2) + var_s0;
}
