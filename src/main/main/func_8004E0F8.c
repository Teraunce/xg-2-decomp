#include "ultra64.h"
void viInit(Unk*, s32, s32, s32, s32, s32, s32);       /* extern */
void osCreateThread(OSThread*, OSId, u32, s32, u32, OSPri);          /* extern */
void osSetThreadPri(Unk*, s32);                              /* extern */
void osStartThread(Unk*);                               /* extern */
void viMgrInitGetter(s32);                                 /* extern */
void osViSetMode(char*);                               /* extern */
void osViSetYScale(s32);                                 /* extern */
void viSetFieldBit(u8);                                 /* extern */
void osEPiLoad(s32, char*, char*, s32);                    /* extern */
extern s32 D_8016D9D0;
extern s32 D_80170310;
extern s32 D_80170378;
extern s32 D_80170398;
extern s32 D_801706B8;
extern s32 gameMainLoop_setup;

void gameMainThread(void) {
    viMgrInitGetter(0xFE);
    viInit(&D_80170310, 0x140, 0xF0, 0, 0, 0, 0);
    osViSetMode(&D_80170310);
    osViSetYScale(0x42);
    viSetFieldBit(1);
    osEPiLoad(0x96, &D_80170378, &D_80170398, 0xC8);
    osCreateThread(&D_801706B8, 3, &gameMainLoop_setup, 0, &D_8016D9D0, 0xA);
    osStartThread(&D_801706B8);
    osSetThreadPri(0, 0);
loop_1:
    goto loop_1;
}
