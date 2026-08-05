#include "ultra64.h"
void entityClearSlots(s32, s32);                       /* extern */
void osWritebackInvalDCache(u32, s32);                            /* extern */
void osWritebackDCache(u32, s32);                            /* extern */
s32 osRecvMesg(Unk*, s32*, s32);                         /* extern */
s32 func_80087BC8(s32);                               /* extern */
void func_80087C4C(s32);                               /* extern */
s32 func_8008B248(s32, u8*);                       /* extern */
s32 contPakBuildMap(s32, Unk*, s32);                /* extern */
extern s32 D_801887A0;
extern Unk D_801887D0;
extern s32 D_8018AD28;
extern s32 D_80192860;

void func_80071D04(s32 *arg0) {
    u8 sp10;
    Unk *var_s0;
    Unk *var_s3;
    s32 *var_s2;
    s32 temp_v1;
    s32 var_s1;
    char *var_s4;

    osWritebackDCache(&D_80192860, 0x10);
    func_80087BC8(&D_801887A0);
    osRecvMesg(&D_801887A0, 0, 1);
    osWritebackInvalDCache(&D_8018AD28, 0x40);
    func_80087C4C(&D_80192860);
    if (func_8008B248(&D_801887A0, &sp10) == 0) {
        var_s1 = 0;
        var_s0 = &D_801887D0;
        var_s4 = &D_801887D0 + 0x17C;
        var_s3 = &D_80192860;
        var_s2 = arg0;
        do {
            if ((((s32) sp10 >> var_s1) & 1) && (*var_s2 != 0)) {
                if (!(var_s3->unk2 & 2) && (temp_v1 = var_s0->unk31C, (temp_v1 != 0)) && (temp_v1 != 1) && (temp_v1 != 7)) {
                    if (temp_v1 == 5) {
                        goto block_10;
                    }
                } else {
block_10:
                    entityClearSlots(var_s1, 1);
                    if (var_s0->unk31C == 5) {
                        if (contPakBuildMap(&D_801887A0, var_s4, var_s1) != 0) {
                            var_s0->unk33C = 1;
                        } else {
                            var_s0->unk33C = 0;
                        }
                        var_s0->unk32C = 1;
                    }
                }
            }
            var_s0 += 4;
            var_s4 += 0x68;
            var_s3 += 4;
            var_s1 += 1;
            var_s2 += 0x24;
        } while (var_s1 < 4);
    }
    D_801887D0.unk160 = (s32) (D_801887D0.unk160 - 1);
}
