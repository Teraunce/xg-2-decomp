#include "ultra64.h"
void __osTimerInsert(Unk*, void**);                       /* extern */
char *audioHeapAlloc(s32, s32, s32, s32, s32);              /* extern */
void func_80082E98(void *);                               /* extern */
void func_80082EDC(void *, s32, s32);                     /* extern */
void func_80082F30(void *, s32, s32);                     /* extern */
void func_80082F84(Unk*, s32);                          /* extern */
s32 func_8008300C(void *, s32, s32);                     /* extern */
void audioMidiNodeInit(Unk*, s32);                          /* extern */
void func_80083638(void *, s32, void *);                         /* extern */
s32 func_80084188(Unk*, s32, s32);                       /* extern */
s32 func_800843AC(void *, s32, char*);                       /* extern */
s32 audioNoteWrite(Unk*, s32, s32);                       /* extern */
void func_80085068(s32);                       /* extern */
s32 audioNodeSetProp(Unk*, s32, s32);                       /* extern */
s32 func_800865F8(Unk*, s16, s32, s32);            /* extern */

void func_80082B98(Unk *arg0, Unk *arg1) {
    char *sp5C;
    char *sp48;
    char *temp_v0;
    char *temp_v0_2;
    char *temp_v0_3;
    Unk *var_s0;
    char *var_s1;
    char *var_s2;
    char *var_s3;
    char *var_v1;
    s32 temp_s7;
    s32 var_s4;

    temp_s7 = arg1->unk14;
    arg0->unk0 = 0;
    arg0->unk20 = 0;
    arg0->unk1C = 0;
    arg0->unk3C = (s32) arg1->unk4;
    arg0->unk48 = 0xA0;
    arg0->unk44 = (s32) arg1->unk18;
    arg0->unk24 = (s32) arg1->unk10;
    temp_v0 = audioHeapAlloc(0, 0, temp_s7, 1, 0x1C);
    sp5C = temp_v0;
    func_80082E98(temp_v0);
    arg0->unk38 = sp5C;
    arg0->unk34 = audioHeapAlloc(0, 0, temp_s7, 1, 0x4C);
    arg0->unk40 = 1;
    func_80082F30(arg0->unk34, audioHeapAlloc(0, 0, temp_s7, arg1->unk4, 4), arg1->unk4);
    arg0->unk30 = audioHeapAlloc(0, 0, temp_s7, 1, 0x20);
    func_80082EDC(arg0->unk30, audioHeapAlloc(0, 0, temp_s7, arg1->unk4, 4), arg1->unk4);
    if (arg1->unk1C != 0) {
        func_800865F8(arg0, 0, arg1, temp_s7);
    } else {
        audioNoteWrite(arg0->unk30, 2, arg0->unk34);
    }
    arg0->unk4 = 0;
    arg0->unk8 = 0;
    arg0->unk14 = 0;
    arg0->unk18 = 0;
    arg0->unkC = 0;
    arg0->unk10 = 0;
    temp_v0_2 = audioHeapAlloc(0, 0, temp_s7, arg1->unk4, 0xDC);
    var_s4 = 0;
    var_s0 = temp_v0_2;
    if (arg1->unk4 > 0) {
        var_s1 = temp_v0_2 + 0x8C;
        var_s2 = temp_v0_2 + 0x58;
        var_s3 = temp_v0_2 + 0x10;
        sp48 = arg0 + 4;
        do {
            __osTimerInsert(var_s0, sp48);
            var_s0->unk8 = 0;
            func_8008300C(var_s3, arg0->unk24, temp_s7);
            func_80083638(var_s3, 1, 0);
            func_80082F84(var_s2, temp_s7);
            func_80085068(1);
            audioMidiNodeInit(var_s1, temp_s7);
            func_800843AC(var_s1, 1, var_s2);
            func_80084188(arg0->unk34, 2, var_s1);
            var_s0->unkC = (void *) (var_s0 + 0x8C);
            var_s4 += 1;
            var_s0 += 0xDC;
            var_s1 += 0xDC;
            var_s2 += 0xDC;
            var_s3 += 0xDC;
        } while (var_s4 < arg1->unk4);
        var_s4 = 0;
    }
    audioNodeSetProp(sp5C, 1, arg0->unk30);
    temp_v0_3 = audioHeapAlloc(0, 0, temp_s7, arg1->unk8, 0x1C);
    arg0->unk2C = 0;
    var_v1 = temp_v0_3;
    if (arg1->unk8 > 0) {
        do {
            var_s4 += 1;
            *var_v1 = arg0->unk2C;
            arg0->unk2C = var_v1;
            var_v1 += 0x1C;
        } while (var_s4 < arg1->unk8);
    }
    arg0->unk28 = temp_s7;
}
