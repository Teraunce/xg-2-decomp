#include "ultra64.h"
s32 sfxQueueCmd(s32, s32, s32, s32, s32);             /* extern */
s32 audioQueueFind(s32, f32*, s32*, s32*);                    /* extern */
extern s32 D_80181538;
extern s32 D_80181558;
extern s32 D_80181578;
extern s32 D_8018157C;
extern s32 D_80181580;

void func_8005D0C8(void) {
    s32 temp_v1;
    s32 temp_v1_2;

    if ((D_80181578 != D_8018157C) && ((D_80181580 == 0) || (audioQueueFind(D_80181580, 0, 0, 0) == 0))) {
        temp_v1 = D_80181578 * 4;
        D_80181580 = sfxQueueCmd(*(temp_v1 + &D_80181538), 0x3F800000, 0x10000, *(temp_v1 + &D_80181558), 0);
        temp_v1_2 = D_80181578 + 1;
        D_80181578 = temp_v1_2;
        if (temp_v1_2 >= 8) {
            D_80181578 = 0;
        }
    }
}
