#include "ultra64.h"

typedef struct {
    /* 0x00 */ char *unk0;
    /* 0x04 */ u8 pad04[0x16];
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ u8 pad1C[0x1C];
    /* 0x38 */ s32 unk38;
    /* 0x3C */ char *unk3C;
    /* 0x40 */ char *unk40;
    /* 0x44 */ u8 pad44[4];
    /* 0x48 */ s32 unk48;
} UnkStruct_arg0;

typedef struct {
    /* 0x00 */ u8 pad00[8];
    /* 0x08 */ void (*unk8)(void *, s32, void *);
} UnkStruct_unk0;

s32 audioMidiNodeCmd(UnkStruct_arg0 *arg0, s32 arg1, char *arg2) {
    UnkStruct_unk0 *temp_a0;

    switch (arg1) {
    case 3:
        if (arg0->unk40 != 0) {
            *(void **)arg0->unk40 = arg2;
        } else {
            arg0->unk3C = arg2;
        }
        arg0->unk40 = arg2;
        break;
    case 4:
        temp_a0 = arg0->unk0;
        arg0->unk38 = 1;
        arg0->unk48 = 0;
        arg0->unk1A = 1;
        if (temp_a0 != NULL) {
            ((s32(*)())(s32)temp_a0->unk8)(temp_a0, 4, arg2);
        }
        break;
    case 9:
        temp_a0 = arg0->unk0;
        arg0->unk48 = 1;
        if (temp_a0 != NULL) {
            ((s32(*)())(s32)temp_a0->unk8)(temp_a0, 9, arg2);
        }
        break;
    case 1:
        arg0->unk0 = arg2;
        break;
    default:
        temp_a0 = arg0->unk0;
        if (temp_a0 != NULL) {
            ((s32(*)())(s32)temp_a0->unk8)(temp_a0, arg1, arg2);
        }
        break;
    }
    return 0;
}
