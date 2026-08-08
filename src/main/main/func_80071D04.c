#include "ultra64.h"
void entityClearSlots(s32, s32);                       /* extern */
void osWritebackInvalDCache(u32, s32);                            /* extern */
void osWritebackDCache(u32, s32);                            /* extern */
s32 osRecvMesg(Unk*, s32*, s32);                         /* extern */
s32 siReadBlocking(s32);                               /* extern */
void contGetInputPort(s32);                               /* extern */
s32 siQueryControllers(s32, u8*);                       /* extern */
s32 contPakBuildMap(s32, Unk*, s32);                /* extern */
extern s32 gHandlerMsgQueue;
extern Unk gHandlerCtx;
extern s32 gSiCmdBuf;
extern s32 gContInput;

void contPakHandlerDetect(s32 *arg0) {
    u8 sp10;
    Unk *var_s0;
    Unk *var_s3;
    s32 *var_s2;
    s32 temp_v1;
    s32 var_s1;
    char *var_s4;

    osWritebackDCache(&gContInput, 0x10);
    siReadBlocking(&gHandlerMsgQueue);
    osRecvMesg(&gHandlerMsgQueue, 0, 1);
    osWritebackInvalDCache(&gSiCmdBuf, 0x40);
    contGetInputPort(&gContInput);
    if (siQueryControllers(&gHandlerMsgQueue, &sp10) == 0) {
        var_s1 = 0;
        var_s0 = &gHandlerCtx;
        var_s4 = &gHandlerCtx + 0x17C;
        var_s3 = &gContInput;
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
                        if (contPakBuildMap(&gHandlerMsgQueue, var_s4, var_s1) != 0) {
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
    gHandlerCtx.unk160 = (s32) (gHandlerCtx.unk160 - 1);
}
