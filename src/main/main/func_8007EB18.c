#include "ultra64.h"
typedef struct {
    /* 0x00 */ u8 pad00[0x18];
    /* 0x18 */ char *unk18;
    /* 0x1C */ u8 pad1C[0x8];
    /* 0x24 */ s32 unk24;
    /* 0x28 */ u8 pad28[0x4];
    /* 0x2C */ s32 unk2C;
} UnkStruct_arg0;
typedef struct {
    /* 0x00 */ u8 pad00[0x8];
    /* 0x08 */ s32 unk8;
} UnkStruct_temp_v0;

s32 audioNoteMinTime(Unk*, Unk*);                      /* extern */
void osSetTimer(void **, s32, s32);           /* extern */

void audioStartTimer(UnkStruct_arg0 *arg0) {
    s16 sp20;
    s32 sp1C;
    s32 temp_a0;

    if (arg0->unk2C == 1) {
        temp_a0 = arg0->unk18;
        if ((temp_a0 != 0) && (audioNoteMinTime(temp_a0, &sp1C) != 0)) {
            sp20 = 0;
            osSetTimer((void **)(arg0 + 0x48), &sp20, arg0->unk24 * sp1C);
        }
    }
}

void audioCalcPeriod(UnkStruct_arg0 *arg0) {
    UnkStruct_temp_v0 *temp_v0;

    temp_v0 = arg0->unk18;
    if (temp_v0 != NULL) {
        arg0->unk24 = (s32) ((s32)arg0 * temp_v0->unk8);
        return;
    }
    arg0->unk24 = 0x1E8;
}
