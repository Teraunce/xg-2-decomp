#include "ultra64.h"
s32 *func_8004D7A0(void *);                         /* extern */
extern s32 D_8004B7B0;

s32 func_8004E7A8(s32 arg0) {
    return *func_8004D7A0((arg0 * 0x10) + &D_8004B7B0);
}

void func_8004E7D4(char *arg0) {
    s32 var_v1;
    Unk *var_a0;

    var_a0 = arg0;
    var_v1 = 0;
    var_a0->unk0 = 0;
    var_a0->unk1 = 0;
    var_a0->unk2 = 0;
    var_a0->unk4 = 0;
    var_a0->unk5 = 0;
    var_a0->unk6 = 0;
    do {
        var_a0->unk8 = 0;
        var_a0->unk9 = 0;
        var_a0->unkA = 0;
        var_a0->unkC = 0;
        var_a0->unkD = 0;
        var_a0->unkE = 0;
        var_a0->unk10 = 0x49;
        var_a0->unk11 = 0x49;
        var_a0->unk12 = 0x49;
        var_v1 += 1;
        var_a0 += 0x10;
    } while (var_v1 < 7);
}

/* -------------------------------------------------------------------------
 * func_8004E830 — video mode configuration dispatch.
 *
 * Reads gGameState (0-6), jumps via jtbl_8004BB20, and fills the
 * D_8017C968 VideoModeConfig struct with resolution/FP-scale values.
 * Each of the 7 cases writes different dimensions and float coefficients.
 *
 *   mode 0: 320×240 (NTSC standard)
 *   mode 1: 320×120 (half-height)
 *   mode 2: 160×240 (half-width)
 *   mode 3: 160×120 with 4 viewports (unk40-unk7C used)
 *   mode 4: 160×120 with 2 viewports (unk40-unk5C used)
 *   mode 5: 320×120 alternate coefficients (unk40-unk5C used)
 *   mode 6: 160×240 alternate (unk40-unk5C used)
 * ------------------------------------------------------------------------- */

typedef struct {
    /* +00 */ s32 unk00;
    /* +04 */ s32 unk04;
    /* +08 */ s32 unk08;
    /* +0C */ s32 unk0C;
    /* +10 */ f32 unk10;
    /* +14 */ f32 unk14;
    /* +18 */ f32 unk18;
    /* +1C */ f32 unk1C;
    /* +20 */ s32 unk20;
    /* +24 */ s32 unk24;
    /* +28 */ s32 unk28;
    /* +2C */ s32 unk2C;
    /* +30 */ f32 unk30;
    /* +34 */ f32 unk34;
    /* +38 */ f32 unk38;
    /* +3C */ f32 unk3C;
    /* +40 */ s32 unk40;
    /* +44 */ s32 unk44;
    /* +48 */ s32 unk48;
    /* +4C */ s32 unk4C;
    /* +50 */ f32 unk50;
    /* +54 */ f32 unk54;
    /* +58 */ f32 unk58;
    /* +5C */ f32 unk5C;
    /* +60 */ s32 unk60;
    /* +64 */ s32 unk64;
    /* +68 */ s32 unk68;
    /* +6C */ s32 unk6C;
    /* +70 */ f32 unk70;
    /* +74 */ f32 unk74;
    /* +78 */ f32 unk78;
    /* +7C */ f32 unk7C;
} VideoModeConfig;

extern s32 gGameState;          /* current video mode index (0-6) */
extern VideoModeConfig D_8017C968; /* video mode config struct */

/* fp scale constants per mode, stored in rodata (entry.s dlabel section) */
extern f32 D_8004BB3C, D_8004BB40, D_8004BB44, D_8004BB48, D_8004BB4C, D_8004BB50;
extern f32 D_8004BB54, D_8004BB58, D_8004BB5C;
extern f32 D_8004BB60, D_8004BB64, D_8004BB68;
extern f32 D_8004BB6C, D_8004BB70, D_8004BB74, D_8004BB78;
extern f32 D_8004BB7C, D_8004BB80, D_8004BB84, D_8004BB88;
extern f32 D_8004BB8C, D_8004BB90, D_8004BB94, D_8004BB98, D_8004BB9C;
extern f32 D_8004BBA0, D_8004BBA4, D_8004BBA8, D_8004BBAC, D_8004BBB0;

void func_8004E830(void) {
    VideoModeConfig *p;
    u32 mode;

    mode = (u32) gGameState;
    if (mode >= 7U) {
        return;
    }

    p = &D_8017C968;

    switch (mode) {
    case 0: /* 320x240 NTSC */
        p->unk00 = 0;
        p->unk04 = 0;
        p->unk08 = 0x140;
        p->unk0C = 0xF0;
        p->unk10 = D_8004BB3C; p->unk14 = D_8004BB40;
        p->unk18 = D_8004BB3C; p->unk1C = D_8004BB40;
        p->unk20 = 0x79; p->unk24 = 0xC0;
        p->unk28 = 0x4C; p->unk2C = 0x24;
        p->unk30 = D_8004BB44; p->unk34 = D_8004BB48;
        p->unk38 = D_8004BB4C; p->unk3C = D_8004BB50;
        break;
    case 1: /* 320x120 half-height */
        p->unk00 = 0; p->unk04 = 0;
        p->unk08 = 0x140; p->unk0C = 0x78;
        p->unk10 = D_8004BB54; p->unk14 = D_8004BB58;
        p->unk18 = D_8004BB54; p->unk1C = D_8004BB58;
        p->unk20 = 0;
        p->unk24 = 0x78; p->unk28 = 0x140; p->unk2C = 0x78;
        p->unk30 = D_8004BB54; p->unk34 = D_8004BB58;
        p->unk38 = D_8004BB54; p->unk3C = D_8004BB5C;
        break;
    case 2: /* 160x240 half-width */
        p->unk00 = 0; p->unk04 = 0;
        p->unk08 = 0xA0; p->unk0C = 0xF0;
        p->unk10 = D_8004BB60; p->unk14 = D_8004BB64;
        p->unk18 = D_8004BB60; p->unk1C = D_8004BB64;
        p->unk20 = 0xA0; p->unk24 = 0;
        p->unk28 = 0xA0; p->unk2C = 0xF0;
        p->unk30 = D_8004BB60; p->unk34 = D_8004BB64;
        p->unk38 = D_8004BB68; p->unk3C = D_8004BB64;
        break;
    case 3: /* 160x120 quad-viewport */
        p->unk00 = 0; p->unk04 = 0;
        p->unk08 = 0xA0; p->unk0C = 0x78;
        p->unk10 = D_8004BB6C; p->unk14 = D_8004BB70;
        p->unk18 = D_8004BB6C; p->unk1C = D_8004BB70;
        p->unk20 = 0xA0; p->unk24 = 0;
        p->unk28 = 0xA0; p->unk2C = 0x78;
        p->unk30 = D_8004BB6C; p->unk34 = D_8004BB70;
        p->unk38 = D_8004BB74; p->unk3C = D_8004BB70;
        p->unk40 = 0;
        p->unk44 = 0x78; p->unk48 = 0xA0; p->unk4C = 0x78;
        p->unk50 = D_8004BB6C; p->unk54 = D_8004BB70;
        p->unk58 = D_8004BB6C; p->unk5C = D_8004BB78;
        p->unk60 = 0xA0; p->unk64 = 0x78;
        p->unk68 = 0xA0; p->unk6C = 0x78;
        p->unk70 = D_8004BB6C; p->unk74 = D_8004BB70;
        p->unk78 = D_8004BB74; p->unk7C = D_8004BB78;
        break;
    case 4: /* 160x120 dual-viewport */
        p->unk00 = 0; p->unk04 = 0;
        p->unk08 = 0xA0; p->unk0C = 0x78;
        p->unk10 = D_8004BB7C; p->unk14 = D_8004BB80;
        p->unk18 = D_8004BB7C; p->unk1C = D_8004BB80;
        p->unk20 = 0xA0; p->unk24 = 0;
        p->unk28 = 0xA0; p->unk2C = 0x78;
        p->unk30 = D_8004BB7C; p->unk34 = D_8004BB80;
        p->unk38 = D_8004BB84; p->unk3C = D_8004BB80;
        p->unk40 = 0;
        p->unk44 = 0x78; p->unk48 = 0xA0; p->unk4C = 0x78;
        p->unk50 = D_8004BB7C; p->unk54 = D_8004BB80;
        p->unk58 = D_8004BB7C; p->unk5C = D_8004BB88;
        break;
    case 5: /* 320x120 alt */
        p->unk00 = 0; p->unk04 = 0;
        p->unk08 = 0x140; p->unk0C = 0x78;
        p->unk10 = D_8004BB8C; p->unk14 = D_8004BB90;
        p->unk18 = D_8004BB8C; p->unk1C = D_8004BB90;
        p->unk20 = 0; p->unk24 = 0x78;
        p->unk28 = 0xA0; p->unk2C = 0x78;
        p->unk30 = D_8004BB94; p->unk34 = D_8004BB90;
        p->unk38 = D_8004BB94; p->unk3C = D_8004BB98;
        p->unk40 = 0xA0; p->unk44 = 0x78;
        p->unk48 = 0xA0; p->unk4C = 0x78;
        p->unk50 = D_8004BB94; p->unk54 = D_8004BB90;
        p->unk58 = D_8004BB9C; p->unk5C = D_8004BB98;
        break;
    case 6: /* 160x240 alt */
        p->unk00 = 0; p->unk04 = 0;
        p->unk08 = 0xA0; p->unk0C = 0xF0;
        p->unk10 = D_8004BBA0; p->unk14 = D_8004BBA4;
        p->unk18 = D_8004BBA0; p->unk1C = D_8004BBA4;
        p->unk20 = 0xA0; p->unk24 = 0;
        p->unk28 = 0xA0; p->unk2C = 0x78;
        p->unk30 = D_8004BBA0; p->unk34 = D_8004BBA8;
        p->unk38 = D_8004BBAC; p->unk3C = D_8004BBA8;
        p->unk40 = 0xA0; p->unk44 = 0x78;
        p->unk48 = 0xA0; p->unk4C = 0x78;
        p->unk50 = D_8004BBA0; p->unk54 = D_8004BBA8;
        p->unk58 = D_8004BBAC; p->unk5C = D_8004BBB0;
        break;
    }
}
