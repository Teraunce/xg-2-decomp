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
extern VIState * volatile D_80095644;
extern s32 D_80000300;
extern ModeEntry D_800963E0;
extern ModeEntry D_80096430;
extern ModeEntry D_80096390;
extern vu32 D_A4400010;
extern vu32 D_A4400000;

void func_8008EAB8(VIBuf *, s32);
void func_80087728(void);

void func_80087158(void) {
    func_8008EAB8(&D_800955E0, 0x60);
    D_80095640 = &D_800955E0;
    D_80095644 = &D_800955E0.sub30;
    D_800955E0.sub30.unk02 = 1;
    D_80095640->unk02 = 1;
    D_80095644->unk04 = 0x80000000;
    D_80095640->unk04 = 0x80000000;
    if (D_80000300 == 0) {
        D_80095644->unk08 = &D_800963E0;
    } else if (D_80000300 == 2) {
        D_80095644->unk08 = &D_80096430;
    } else {
        D_80095644->unk08 = &D_80096390;
    }
    D_80095644->unk00 = 0x20;
    D_80095644->unk0C = ((Unk *)D_80095644->unk08)->unk04;
    if ((u32) D_A4400010 >= 0xBU) {
        do {
        } while ((u32) D_A4400010 >= 0xBU);
    }
    D_A4400000 = 0;
    func_80087728();
}

VIBuf *func_80087298(void) {
    return D_80095640;
}
