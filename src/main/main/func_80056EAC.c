#include "ultra64.h"
void func_80056EAC(Unk *arg0, Unk *arg1, Unk *arg2) {
    Unk sp_buf[8];
    Unk *sp = sp_buf; /* $sp base — local stack byte-pointer */
    f32 sp3C;
    f32 sp38;
    f32 sp34;
    f32 sp30;
    f32 sp2C;
    f32 sp28;
    f32 sp24;
    f32 sp20;
    f32 sp1C;
    f32 sp18;
    f32 sp14;
    f32 sp10;
    f32 spC;
    f32 sp8;
    f32 sp4;
    f32 sp0;
    Unk *var_a2;
    Unk *var_v0;

    var_a2 = arg2;
    if (arg1 == var_a2) {
        sp0 = (arg0->unk0 * arg1->unk0) + (arg0->unk4 * arg1->unk10) + (arg0->unk8 * arg1->unk20) + (arg0->unkC * arg1->unk30);
        sp4 = (arg0->unk0 * arg1->unk4) + (arg0->unk4 * arg1->unk14) + (arg0->unk8 * arg1->unk24) + (arg0->unkC * arg1->unk34);
        sp8 = (arg0->unk0 * arg1->unk8) + (arg0->unk4 * arg1->unk18) + (arg0->unk8 * arg1->unk28) + (arg0->unkC * arg1->unk38);
        spC = (arg0->unk0 * arg1->unkC) + (arg0->unk4 * arg1->unk1C) + (arg0->unk8 * arg1->unk2C) + (arg0->unkC * arg1->unk3C);
        sp10 = (arg0->unk10 * arg1->unk0) + (arg0->unk14 * arg1->unk10) + (arg0->unk18 * arg1->unk20) + (arg0->unk1C * arg1->unk30);
        sp14 = (arg0->unk10 * arg1->unk4) + (arg0->unk14 * arg1->unk14) + (arg0->unk18 * arg1->unk24) + (arg0->unk1C * arg1->unk34);
        sp18 = (arg0->unk10 * arg1->unk8) + (arg0->unk14 * arg1->unk18) + (arg0->unk18 * arg1->unk28) + (arg0->unk1C * arg1->unk38);
        sp1C = (arg0->unk10 * arg1->unkC) + (arg0->unk14 * arg1->unk1C) + (arg0->unk18 * arg1->unk2C) + (arg0->unk1C * arg1->unk3C);
        sp20 = (arg0->unk20 * arg1->unk0) + (arg0->unk24 * arg1->unk10) + (arg0->unk28 * arg1->unk20) + (arg0->unk2C * arg1->unk30);
        sp24 = (arg0->unk20 * arg1->unk4) + (arg0->unk24 * arg1->unk14) + (arg0->unk28 * arg1->unk24) + (arg0->unk2C * arg1->unk34);
        sp28 = (arg0->unk20 * arg1->unk8) + (arg0->unk24 * arg1->unk18) + (arg0->unk28 * arg1->unk28) + (arg0->unk2C * arg1->unk38);
        sp2C = (arg0->unk20 * arg1->unkC) + (arg0->unk24 * arg1->unk1C) + (arg0->unk28 * arg1->unk2C) + (arg0->unk2C * arg1->unk3C);
        sp30 = (arg0->unk30 * arg1->unk0) + (arg0->unk34 * arg1->unk10) + (arg0->unk38 * arg1->unk20) + (arg0->unk3C * arg1->unk30);
        sp34 = (arg0->unk30 * arg1->unk4) + (arg0->unk34 * arg1->unk14) + (arg0->unk38 * arg1->unk24) + (arg0->unk3C * arg1->unk34);
        sp38 = (arg0->unk30 * arg1->unk8) + (arg0->unk34 * arg1->unk18) + (arg0->unk38 * arg1->unk28) + (arg0->unk3C * arg1->unk38);
        var_v0 = sp;
        sp3C = (arg0->unk30 * arg1->unkC) + (arg0->unk34 * arg1->unk1C) + (arg0->unk38 * arg1->unk2C) + (arg0->unk3C * arg1->unk3C);
        do {
            var_a2->unk0 = (s32) var_v0->unk0;
            var_a2->unk4 = (s32) var_v0->unk4;
            var_a2->unk8 = (s32) var_v0->unk8;
            var_a2->unkC = (s32) var_v0->unkC;
            var_v0 += 0x10;
            var_a2 += 0x10;
        } while ((void*)var_v0 != (void*)&arg0);
        return;
    }
    var_a2->unk0 = (f32) ((arg0->unk0 * arg1->unk0) + (arg0->unk4 * arg1->unk10) + (arg0->unk8 * arg1->unk20) + (arg0->unkC * arg1->unk30));
    var_a2->unk4 = (f32) ((arg0->unk0 * arg1->unk4) + (arg0->unk4 * arg1->unk14) + (arg0->unk8 * arg1->unk24) + (arg0->unkC * arg1->unk34));
    var_a2->unk8 = (f32) ((arg0->unk0 * arg1->unk8) + (arg0->unk4 * arg1->unk18) + (arg0->unk8 * arg1->unk28) + (arg0->unkC * arg1->unk38));
    var_a2->unkC = (f32) ((arg0->unk0 * arg1->unkC) + (arg0->unk4 * arg1->unk1C) + (arg0->unk8 * arg1->unk2C) + (arg0->unkC * arg1->unk3C));
    var_a2->unk10 = (f32) ((arg0->unk10 * arg1->unk0) + (arg0->unk14 * arg1->unk10) + (arg0->unk18 * arg1->unk20) + (arg0->unk1C * arg1->unk30));
    var_a2->unk14 = (f32) ((arg0->unk10 * arg1->unk4) + (arg0->unk14 * arg1->unk14) + (arg0->unk18 * arg1->unk24) + (arg0->unk1C * arg1->unk34));
    var_a2->unk18 = (f32) ((arg0->unk10 * arg1->unk8) + (arg0->unk14 * arg1->unk18) + (arg0->unk18 * arg1->unk28) + (arg0->unk1C * arg1->unk38));
    var_a2->unk1C = (f32) ((arg0->unk10 * arg1->unkC) + (arg0->unk14 * arg1->unk1C) + (arg0->unk18 * arg1->unk2C) + (arg0->unk1C * arg1->unk3C));
    var_a2->unk20 = (f32) ((arg0->unk20 * arg1->unk0) + (arg0->unk24 * arg1->unk10) + (arg0->unk28 * arg1->unk20) + (arg0->unk2C * arg1->unk30));
    var_a2->unk24 = (f32) ((arg0->unk20 * arg1->unk4) + (arg0->unk24 * arg1->unk14) + (arg0->unk28 * arg1->unk24) + (arg0->unk2C * arg1->unk34));
    var_a2->unk28 = (f32) ((arg0->unk20 * arg1->unk8) + (arg0->unk24 * arg1->unk18) + (arg0->unk28 * arg1->unk28) + (arg0->unk2C * arg1->unk38));
    var_a2->unk2C = (f32) ((arg0->unk20 * arg1->unkC) + (arg0->unk24 * arg1->unk1C) + (arg0->unk28 * arg1->unk2C) + (arg0->unk2C * arg1->unk3C));
    var_a2->unk30 = (f32) ((arg0->unk30 * arg1->unk0) + (arg0->unk34 * arg1->unk10) + (arg0->unk38 * arg1->unk20) + (arg0->unk3C * arg1->unk30));
    var_a2->unk34 = (f32) ((arg0->unk30 * arg1->unk4) + (arg0->unk34 * arg1->unk14) + (arg0->unk38 * arg1->unk24) + (arg0->unk3C * arg1->unk34));
    var_a2->unk38 = (f32) ((arg0->unk30 * arg1->unk8) + (arg0->unk34 * arg1->unk18) + (arg0->unk38 * arg1->unk28) + (arg0->unk3C * arg1->unk38));
    var_a2->unk3C = (f32) ((arg0->unk30 * arg1->unkC) + (arg0->unk34 * arg1->unk1C) + (arg0->unk38 * arg1->unk2C) + (arg0->unk3C * arg1->unk3C));
}

void func_800576FC(Unk *arg0, Unk *arg1, Unk *arg2) {
    arg2->unk0 = (f32) ((arg0->unk0 * arg1->unk0) + (arg0->unk10 * arg1->unk4) + (arg0->unk20 * arg1->unk8) + arg0->unk30);
    arg2->unk4 = (f32) ((arg0->unk4 * arg1->unk0) + (arg0->unk14 * arg1->unk4) + (arg0->unk24 * arg1->unk8) + arg0->unk34);
    arg2->unk8 = (f32) ((arg0->unk8 * arg1->unk0) + (arg0->unk18 * arg1->unk4) + (arg0->unk28 * arg1->unk8) + arg0->unk38);
}
