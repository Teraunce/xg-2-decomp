#include "ultra64.h"
void osCreateMesgQueue(Unk*, s32, s32);                       /* extern */
void osSetEventMesg(s32, s32, s32);                         /* extern */
s32 siReadControllers(char*, s32, s32);                    /* extern */
extern s32 D_80192820;
extern s32 D_80192840;

s32 contInit(void) {
    u8 sp2C;
    s32 sp28;
    s32 sp10;
    Unk *var_s0;
    Unk *var_v1;
    s32 var_a0;

    osCreateMesgQueue(&sp10, &sp28, 1);
    osSetEventMesg(5, &sp10, 1);
    var_s0 = &D_80192820;
    siReadControllers(&sp10, &sp2C, &D_80192820);
    var_a0 = 0;
    var_v1 = &D_80192840;
loop_1:
    if (!(((s32) sp2C >> var_a0) & 1)) {
        var_v1->unk0 = 0;
        goto block_8;
    }
    if (var_s0->unk3 & 8) {
        var_v1->unk0 = 0;
block_8:
        var_v1->unk2 = 0;
        var_v1->unk3 = 0;
        var_v1->unk4 = 0;
        var_v1 += 6;
        var_a0 += 1;
        var_s0 += 4;
        if (var_a0 >= 4) {
            return -1;
        }
        goto loop_1;
    }
    return var_a0;
}
