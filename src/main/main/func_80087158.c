#include "ultra64.h"

typedef struct {
    /* 0x04 */ s32 unk04;
} ModeEntry;

typedef struct {
    /* 0x00 */ u16 unk00;
    /* 0x02 */ u16 unk02;
    /* 0x04 */ u32 unk04;
    /* 0x08 */ ModeEntry *unk08;
    /* 0x0C */ s32 unk0C;
} VIState;

typedef struct {
    /* 0x00 */ u8 pad00[2];
    /* 0x02 */ u16 unk02;
    /* 0x04 */ u32 unk04;
    /* 0x08 */ u8 pad08[0x26];
    /* 0x30 */ VIState sub30;
} VIBuf;

extern VIBuf D_800955E0;
extern VIBuf * volatile D_80095640;
extern VIState * volatile gVIConfig;
extern s32 osMemSize;
extern ModeEntry D_800963E0;
extern ModeEntry D_80096430;
extern ModeEntry D_80096390;
extern vu32 D_A4400010;
extern vu32 D_A4400000;

void bzero(VIBuf *, s32);
void osViSwapBuffer(void);

void osViInit(void) {
    bzero(&D_800955E0, 0x60);
    D_80095640 = &D_800955E0;
    gVIConfig = &D_800955E0.sub30;
    D_800955E0.sub30.unk02 = 1;
    D_80095640->unk02 = 1;
    gVIConfig->unk04 = 0x80000000;
    D_80095640->unk04 = 0x80000000;
    if (osMemSize == 0) {
        gVIConfig->unk08 = &D_800963E0;
    } else if (osMemSize == 2) {
        gVIConfig->unk08 = &D_80096430;
    } else {
        gVIConfig->unk08 = &D_80096390;
    }
    gVIConfig->unk00 = 0x20;
    gVIConfig->unk0C = ((Unk *)gVIConfig->unk08)->unk04;
    if ((u32) D_A4400010 >= 0xBU) {
        do {
        } while ((u32) D_A4400010 >= 0xBU);
    }
    D_A4400000 = 0;
    osViSwapBuffer();
}

VIBuf *osViGetCurrentFramebuffer(void) {
    return D_80095640;
}
