#include "ultra64.h"
s32 sfxQueueCmd(s16, f32, s32, s8, s32);           /* extern */
void audioQueuePlay(s32, f32, s32, s8, s32);           /* extern */
void audioQueueStop(s32);                               /* extern */
s32 audioQueueFind(s32, f32*, s32*, s32*);                    /* extern */
s32 sfxEntitySpatial(f32 *, s32 *, s32 *, s32 *);      /* extern */
extern s32 D_80092844;

void sfxEntitySpatialUpdate(s32 arg1, f32 arg2, s32 arg3, s32 *arg4) {
    s32 sp1C;
    s32 sp18;
    s32 temp_a0;
    s32 temp_a0_2;

    sp18 = 0x40;
    sp1C = 0;
    if (sfxEntitySpatial(&arg2, &arg3, &sp18, &sp1C) != 0) {
        temp_a0 = *arg4;
        if (temp_a0 != 0) {
            if (audioQueueFind(temp_a0, 0, 0, 0) != 0) {
                audioQueuePlay(*arg4, arg2, arg3, sp18, sp1C);
                return;
            }
            if (D_80092844 >= 0x1A) {
                *arg4 = 0;
                return;
            }
            goto block_7;
        }
        if (D_80092844 < 0x1A) {
block_7:
            *arg4 = sfxQueueCmd(arg1, arg2, arg3, sp18, sp1C);
        }
    } else {
        temp_a0_2 = *arg4;
        if (temp_a0_2 != 0) {
            audioQueueStop(temp_a0_2);
            *arg4 = 0;
        }
    }
}
