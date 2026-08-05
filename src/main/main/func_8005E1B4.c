#include "ultra64.h"
s32 sfxQueueCmd(s16, f32, s32, s8, s32);           /* extern */
void audioQueuePlay(s32, f32, s32, s8, s32);           /* extern */
void audioQueueStop(s32);                               /* extern */
s32 audioQueueFind(s32, f32*, s32*, s32*);                    /* extern */
s32 func_8005D9BC(f32, f32, s32, s32, f32, f32, f32 *, s32 *, s32 *, s32 *, s32); /* extern */
extern s32 D_80092844;

void func_8005E1B4(Unk *arg0, Unk *arg1, s32 arg2, f32 arg3, s32 arg4, s32 *arg5) {
    s32 sp34;
    s32 sp30;
    s32 temp_a0;
    s32 temp_a0_2;

    sp30 = 0x40;
    sp34 = 0;
    if (func_8005D9BC(arg0->unk0, arg0->unk4, arg0->unk8, arg1->unk0, arg1->unk4, arg1->unk8, &arg3, &arg4, &sp30, &sp34, 0) != 0) {
        temp_a0 = *arg5;
        if (temp_a0 != 0) {
            if (audioQueueFind(temp_a0, 0, 0, 0) != 0) {
                audioQueuePlay(*arg5, arg3, arg4, sp30, sp34);
                return;
            }
            if (D_80092844 < 0x1A) {
                goto block_5;
            }
            goto block_8;
        }
block_5:
        *arg5 = sfxQueueCmd(arg2, arg3, arg4, sp30, sp34);
        return;
    }
    temp_a0_2 = *arg5;
    if (temp_a0_2 != 0) {
        audioQueueStop(temp_a0_2);
block_8:
        *arg5 = 0;
    }
}
