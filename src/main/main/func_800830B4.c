#include "ultra64.h"
s32 audioHeapAlloc(s32, s32, s32, s32, s32);               /* extern */
void audioNodeInit(Unk*, s32, s32, s32);              /* extern */
extern s32 audioMidiNodeCmd;
extern s32 audioNodeDispatch;

void audioMidiNodeInit(Unk *arg0, s32 arg1) {
    audioNodeInit(arg0, &audioNodeDispatch, &audioMidiNodeCmd, 4);
    arg0->unk14 = audioHeapAlloc(0, 0, arg1, 1, 0x50);
    arg0->unk38 = 1;
    arg0->unk48 = 0;
    arg0->unk1A = 1;
    arg0->unk28 = 1;
    arg0->unk2E = 1;
    arg0->unk1C = 1;
    arg0->unk1E = 1;
    arg0->unk20 = 0;
    arg0->unk22 = 0;
    arg0->unk26 = 1;
    arg0->unk24 = 0;
    arg0->unk30 = 0;
    arg0->unk34 = 0;
    arg0->unk18 = 0;
    arg0->unk3C = 0;
    arg0->unk40 = 0;
    arg0->unk44 = 0;
}

void audioFillDecayTable(Unk *arg0) {
    f64 temp_fv1;
    f64 var_fv0;
    s32 temp_v1;
    s32 var_a1;
    s32 var_a1_2;
    Unk *var_a2;
    Unk *var_a2_2;

    temp_v1 = (s32) (arg0->unk0 << 0xE) >> 0xF;
    arg0->unk2 = (s16) (0x4000 - (s16) temp_v1);
    arg0->unk2C = 1;
    var_a1 = 0;
    var_a2 = arg0;
    do {
        var_a1 += 1;
        var_a2 += 2;
        var_a2->unk6 = 0;
    } while (var_a1 < 8);
    var_a1_2 = var_a1 + 1;
    var_a2->unk8 = (s16) temp_v1;
    temp_fv1 = (f64) (s16) temp_v1 / 16384.0;
    var_a2_2 = var_a2 + 2;
    var_fv0 = temp_fv1;
    if (var_a1_2 < 0x10) {
        do {
            var_fv0 *= temp_fv1;
            var_a1_2 += 1;
            var_a2_2 += 2;
            var_a2_2->unk6 = (s16) (s32) (var_fv0 * 16384.0);
        } while (var_a1_2 < 0x10);
    }
}
