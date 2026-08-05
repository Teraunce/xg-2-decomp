#include "ultra64.h"
void func_80085FEC(Unk *arg0, s32 arg2, s32 arg4) {
    Unk *temp_a0;
    Unk *temp_v0;

    temp_a0 = arg0->unk0;
    temp_v0 = ((s32(*)())(s32)temp_a0->unk4)(temp_a0, arg4);
    temp_v0->unk4 = (s32) ((arg2 * 2) & 0xFFFF);
    temp_v0->unk0 = 0x08000000;
    temp_v0->unk8 = 0x0D000000;
    temp_v0->unkC = 0x04400580;
    temp_v0->unk14 = (s32) ((arg2 * 4) & 0xFFFF);
    temp_v0->unk10 = 0x08000000;
    temp_v0->unk18 = 0x06000000;
    ((Unk *)(temp_v0 + 0x20))->unk0 /* FIXME: type unknown */ /* FIXME: was ->unk-4 */ = (s32) arg0->unk14;
}

void func_80086078(Unk *arg0) {
    arg0->unk0 = 0;
}
