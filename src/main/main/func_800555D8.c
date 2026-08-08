#include "ultra64.h"
void osCreateMesgQueue(Unk*, s32, s32);                       /* extern */
void osCreateThread(OSThread*, OSId, u32, s32, u32, OSPri);        /* extern */
void osStartThread(Unk*);                               /* extern */
extern s32 D_80174BD0;
extern s32 D_8017BF58;
extern s32 D_8017C8B0;
extern Unk D_8017CCC0;
extern s32 gameThreadEntry;

void gameThreadInit(s32 arg0) {
    osCreateMesgQueue(&D_80174BD0, &D_8017C8B0, 0x20);
    D_8017CCC0.unk0 = arg0;
    D_8017CCC0.unk4 = &D_80174BD0;
    osCreateThread(&D_8017BF58, 4, &gameThreadEntry, &D_8017CCC0, &D_8017BF58, 7);
    osStartThread(&D_8017BF58);
}
