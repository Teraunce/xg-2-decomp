#include "ultra64.h"
void sfxSetPitch(s32);                                 /* extern */
void sfxSetFreq(s32);                                 /* extern */
void sfxSetFilter(s32);                                 /* extern */
void sfxSetState(s32);                                 /* extern */
extern s32 D_801823F8;
extern s32 D_801823FC;
extern s32 D_80182400;
extern s16 D_8018240C;
extern s16 D_80182414;
extern s16 D_80182458;
extern s16 D_80182E74;
extern s16 D_80182E76;
extern s32 D_80182E78;
extern s32 D_80182E7C;
extern s32 D_80182E80;
extern s16 D_80182E90;
extern s16 D_80182E92;
extern s16 D_80182E94;
extern s16 D_80182E96;
extern s8 D_80182E9C;

void rdpStateInit(void) {
    sfxSetPitch(0);
    sfxSetFreq(8);
    sfxSetFilter(0);
    sfxSetState(1);
    D_80182E7C = 0;
    D_80182E76 = 0;
    D_80182E74 = 0;
    D_80182E94 = 0;
    D_80182E96 = 0;
    D_80182E92 = 0x140;
    D_80182E90 = 0xF0;
    D_80182E9C = 2;
    D_80182E80 = 0;
    D_80182E78 = 0;
    D_801823F8 = 0xFF00FF;
    D_801823FC = 0xFF00FF;
    D_80182400 = -1;
    D_8018240C = 1;
    D_80182458 = 0;
    D_80182414 = 0;
}
