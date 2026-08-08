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

extern VIBuf gViModeData;
extern VIBuf * volatile gViModePtr;
extern VIState * volatile gVIConfig;
extern s32 osMemSize;
extern ModeEntry gViMode0;
extern ModeEntry gViMode1;
extern ModeEntry gViMode2;
extern vu32 VI_V_CURRENT;
extern vu32 VI_CTRL;

void bzero(VIBuf *, s32);
void osViSwapBuffer(void);

void osViInit(void) {
    bzero(&gViModeData, 0x60);
    gViModePtr = &gViModeData;
    gVIConfig = &gViModeData.sub30;
    gViModeData.sub30.unk02 = 1;
    gViModePtr->unk02 = 1;
    gVIConfig->unk04 = 0x80000000;
    gViModePtr->unk04 = 0x80000000;
    if (osMemSize == 0) {
        gVIConfig->unk08 = &gViMode0;
    } else if (osMemSize == 2) {
        gVIConfig->unk08 = &gViMode1;
    } else {
        gVIConfig->unk08 = &gViMode2;
    }
    gVIConfig->unk00 = 0x20;
    gVIConfig->unk0C = ((Unk *)gVIConfig->unk08)->unk04;
    if ((u32) VI_V_CURRENT >= 0xBU) {
        do {
        } while ((u32) VI_V_CURRENT >= 0xBU);
    }
    VI_CTRL = 0;
    osViSwapBuffer();
}

VIBuf *osViGetCurrentFramebuffer(void) {
    return gViModePtr;
}
