#include "ultra64.h"
void timerQueueInit(Unk*, s32, s32);                  /* extern */
void audioNoteClearAll(Unk*);                            /* extern */
void pendingFlushEnqueue(void *, void *);                       /* extern */
char *audioHeapAlloc(s32 arg0, s32 arg1, Unk *arg2, u8 arg3, s32 arg4); /* static */
extern s32 gPendingFlushFlag;
extern s32 audioNodeUpdate;

void audioSynthInit(Unk *arg0, Unk *arg1) {
    char *sp2C;
    char *temp_v0;
    char *var_v1;
    s32 var_a0;
    char *temp_a2;

    temp_a2 = arg1->unkC;
    arg0->unk20 = 0;
    arg0->unk18 = 0;
    arg0->unk30 = 0xFF;
    arg0->unk24 = 0x1E8;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    arg0->unk32 = 0x7FFF;
    arg0->unk5C = 0x3E80;
    arg0->unk1C = 0;
    arg0->unk14 = (s32) gPendingFlushFlag;
    arg0->unk70 = (s32) arg1->unk10;
    arg0->unk74 = (s32) arg1->unk14;
    arg0->unk38 = 9;
    arg0->unk78 = (s32) arg1->unk18;
    arg0->unk34 = (u8) arg1->unk8;
    sp2C = temp_a2;
    arg0->unk60 = audioHeapAlloc(0, 0, temp_a2, arg1->unk8, 0x10);
    audioNoteClearAll(arg0);
    temp_v0 = audioHeapAlloc(0, 0, temp_a2, (u8) arg1->unk0, 0x38);
    arg0->unk6C = 0;
    var_a0 = 0;
    if (arg1->unk0 > 0) {
        var_v1 = temp_v0;
        do {
            var_a0 += 1;
            *var_v1 = arg0->unk6C;
            arg0->unk6C = var_v1;
            var_v1 += 0x38;
        } while (var_a0 < arg1->unk0);
    }
    arg0->unk64 = 0;
    arg0->unk68 = 0;
    timerQueueInit(arg0 + 0x48, audioHeapAlloc(0, 0, sp2C, (u8) arg1->unk4, 0x1C), arg1->unk4);
    arg0->unk0 = 0;
    arg0->unk8 = &audioNodeUpdate;
    arg0->unk4 = arg0;
    pendingFlushEnqueue(gPendingFlushFlag, arg0);
}

char *audioHeapAlloc(s32 arg0, s32 arg1, Unk *arg2, u8 arg3, s32 arg4) {
    char *temp_a0;
    char *var_v1;
    s32 temp_t7;

    temp_a0 = arg2->unk4;
    var_v1 = NULL;
    temp_t7 = ((arg3 * arg4) + 0xF) & ~0xF;
    if ((u32) (arg2->unk0 + arg2->unk8) >= (u32) (temp_a0 + temp_t7)) {
        var_v1 = temp_a0;
        arg2->unk4 = (void *) (temp_a0 + temp_t7);
    }
    return var_v1;
}

void audioSetNoteSlot(Unk *arg0, Unk *arg1, s32 arg2) {
    s32 temp_v0;

    temp_v0 = arg2 * 0x10;
    *(Unk**)(s32)(arg0->unk60 + temp_v0) = arg1;
    ((Unk *)(arg0->unk60 + temp_v0))->unk7 = (u8) arg1->unk1;
    ((Unk *)(arg0->unk60 + temp_v0))->unk9 = (u8) arg1->unk0;
    ((Unk *)(arg0->unk60 + temp_v0))->unk8 = (u8) arg1->unk2;
    ((Unk *)(arg0->unk60 + temp_v0))->unk4 = (s16) arg1->unkC;
}

void audioDefaultNoteSlot(Unk *arg0, s32 arg1) {
    s32 temp_v0;

    temp_v0 = arg1 * 0x10;
    ((Unk *)(arg0->unk60 + temp_v0))->unk6 = 0;
    ((Unk *)(arg0->unk60 + temp_v0))->unkA = 0;
    ((Unk *)(arg0->unk60 + temp_v0))->unk7 = 0x40;
    ((Unk *)(arg0->unk60 + temp_v0))->unk9 = 0x7F;
    ((Unk *)(arg0->unk60 + temp_v0))->unk8 = 5;
    ((Unk *)(arg0->unk60 + temp_v0))->unkB = 0;
    ((Unk *)(arg0->unk60 + temp_v0))->unk4 = 0xC8;
    ((Unk *)(arg0->unk60 + temp_v0))->unkC = 1.0f;
}
