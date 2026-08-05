#include "ultra64.h"

void osSetTimer(char *arg0, s16 *arg1, s32 arg2);

void func_80082598(char *arg0) {
    s32 sp24;
    s16 sp20;

    sp20 = 1;
    sp24 = (*(s32 *)((char *)arg0 + 0x3C) * 0x30) + *(s32 *)((char *)arg0 + 0x40);
    osSetTimer((char *)arg0 + 0x14, &sp20, 0);
}

s32 func_800825E8(char *arg0) {
    s32 base;

    base = (*(s32 *)((char *)arg0 + 0x3C) * 0x30) + *(s32 *)((char *)arg0 + 0x40);
    return *(s32 *)(base + 0x28);
}
