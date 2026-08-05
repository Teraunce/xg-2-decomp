#include "ultra64.h"
void func_8004D358();                                  /* extern */
s32 func_8004E4E4();                                /* extern */
void func_8005566C(void);                              /* extern */
void osCreateMesgQueue(Unk*, s32, s32);                       /* extern */
void osCreateThread(OSThread*, OSId, u32, s32, u32, OSPri);          /* extern */
void osSetEventMesg(s32, s32, s32);                     /* extern */
void osStartThread(Unk*);                               /* extern */
void func_800872A8(s32, s32, s32);                     /* extern */
extern s32 D_8014D6E8;
extern s32 D_80163720;
extern s32 D_8016DF70;
extern s32 D_8016E290;
extern s32 D_80173C20;
extern s32 D_80173C40;
extern s32 D_80173C48;
extern Unk D_80173C88;
extern s32 D_80173CB8;
extern s32 D_80174550;
extern s32 D_80174558;
extern s32 D_80174708;
extern s32 D_80174724;
extern s32 D_801747C8;
extern s32 D_80174BF0;
extern s32 D_80174C30;
extern s32 D_80174C40;
extern s32 D_80178450;
extern s32 D_80178610;
extern s32 D_801786A0;
extern s32 D_801786B0;
extern s32 D_801786C0;
extern s32 D_8017C120;
extern s32 D_8017C128;
extern s32 D_8017C800;
extern s32 D_8017C890;
extern s32 D_8017C898;
extern s32 D_8017C960;
extern s32 D_8017CA28;
extern s32 D_8017CA30;
extern s32 D_8017CA38;
extern s32 D_8017CA48;
extern s32 D_8017CC50;
extern s32 func_8004E1B8;

void gameMainLoop_setup(s32 arg0) {
    s32 temp_v0;

    osCreateMesgQueue(&D_8016DF70, &D_8016E290, 0x20);
    func_8004D358();
    temp_v0 = func_8004E4E4();
    D_8017C890 = 1;
    D_80174724 = temp_v0;
    D_8017CA28 = 4;
    D_80174C40 = 5;
    D_8017CA38 = 6;
    D_801786B0 = 8;
    D_80173C40 = 9;
    D_8017C960 = 7;
    D_8017C898 = 0xA;
    D_801747C8 = 0xB;
    D_8017C120 = 0x19;
    D_801786C0 = 0xC;
    D_80173CB8 = 0xD;
    D_80178450 = 0xE;
    D_8017C800 = 0xF;
    D_80173C20 = 0x10;
    D_8017CA48 = 0x1A;
    D_80174BF0 = 0x11;
    D_801786A0 = 0x12;
    D_8017CC50 = 3;
    D_8017CA30 = 2;
    D_80174C30 = 0x18;
    osCreateMesgQueue(&D_80174708, &D_8017C128, 0x20);
    osSetEventMesg(4, &D_80174708, &D_8017CC50);
    osSetEventMesg(9, &D_80174708, &D_8017CA28);
    osSetEventMesg(6, &D_80174708, &D_8017CA38);
    osSetEventMesg(0xE, &D_80174708, &D_801786B0);
    func_800872A8(&D_80174708, &D_8017CA30, 1);
    osCreateMesgQueue(&D_80173C48, &D_80178610, 0x20);
    osSetEventMesg(5, &D_80173C48, &D_8017C890);
    osCreateThread(&D_80174558, 9, &func_8004E1B8, 0, &D_80174550, 0xE);
    osStartThread(&D_80174558);
    D_80173C88.unk0 = 0;
    D_80173C88.unk4 = 1;
    D_80173C88.unkC = 3;
    D_80173C88.unk14 = 1;
    D_80173C88.unk1C = 3;
    D_80173C88.unk8 = 2;
    D_80173C88.unk10 = 0;
    D_80173C88.unk18 = 2;
    D_80173C88.unk20 = 0;
    D_80173C88.unk24 = 1;
loop_1:
    func_8005566C();
    goto loop_1;
}

void func_8004E4B0(void) {
    s32 *var_v0;
    s32 var_v1;

    var_v1 = 0xFE;
    var_v0 = &D_80163720 + 0x3F8;
    do {
        *var_v0 = 0;
        var_v1 -= 1;
        var_v0 -= 4;
    } while (var_v1 >= 0);
    D_8014D6E8 = 0;
}

void func_8004E4DC(void) {

}
