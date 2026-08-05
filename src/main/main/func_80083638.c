#include "ultra64.h"
typedef struct {
    /* 0x00 */ u8 pad00[0x4];
    /* 0x04 */ s32 unk4;
    /* 0x08 */ u8 pad08[0x10];
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ s32 unk24;
    /* 0x28 */ char *unk28;
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ u8 pad30[0x8];
    /* 0x38 */ s32 unk38;
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ s32 unk40;
    /* 0x44 */ s32 unk44;
} UnkStruct_arg0;
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ u8 pad04[0x4];
    /* 0x08 */ s32 unk8;
} UnkStruct_arg2;
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
} UnkStruct_temp_a0;
typedef struct {
    /* 0x00 */ u8 pad00[0x4];
    /* 0x04 */ s32 unk4;
} UnkStruct_temp_v0_2;
typedef struct {
    /* 0x00 */ u8 pad00[0xC];
    /* 0x0C */ char *unkC;
    /* 0x10 */ char *unk10;
} UnkStruct_temp_v0_3;
typedef struct {
    /* 0x00 */ u8 pad00[0xC];
    /* 0x0C */ char *unkC;
} UnkStruct_temp_v0_4;
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ u8 pad04[0x4];
    /* 0x08 */ s32 unk8;
    /* 0x0C */ char *unkC;
} UnkStruct_temp_v0_5;
typedef struct {
    /* 0x00 */ s32 unk0;
} UnkStruct_temp_v1;
typedef struct {
    /* 0x00 */ s32 unk0;
} UnkStruct_temp_v1_2;
typedef struct {
    /* 0x00 */ u8 pad00[0x8];
    /* 0x08 */ s32 unk8;
} UnkStruct_temp_v1_4;
typedef struct {
    /* 0x00 */ u8 pad00[0x8];
    /* 0x08 */ s32 unk8;
} UnkStruct_temp_v1_5;

void memcpyBytes(Unk*, char*, s32);                   /* extern */
extern s32 func_8008380C;
extern s32 audioAdpcmCmd;

void func_80083638(UnkStruct_arg0 *arg0, s32 arg1, UnkStruct_arg2 *arg2) {
    u8 temp_v0;
    u8 temp_v1_3;
    UnkStruct_temp_a0 *temp_a0;
    UnkStruct_temp_v0_2 *temp_v0_2;
    UnkStruct_temp_v0_3 *temp_v0_3;
    UnkStruct_temp_v0_4 *temp_v0_4;
    UnkStruct_temp_v0_5 *temp_v0_5;
    UnkStruct_temp_v1 *temp_v1;
    UnkStruct_temp_v1_2 *temp_v1_2;
    UnkStruct_temp_v1_4 *temp_v1_4;
    UnkStruct_temp_v1_5 *temp_v1_5;

    if (arg1 != 4) {
        if (arg1 == 5) {
            arg0->unk28 = arg2;
            arg0->unk38 = 0;
            arg0->unk44 = (s32) arg2->unk0;
            temp_v0 = arg2->unk8;
            switch (temp_v0) {                      /* irregular */
            case 0:
                temp_v0_2 = arg0->unk28;
                arg0->unk4 = &audioAdpcmCmd;
                temp_v0_2->unk4 = (s32) (((s32) temp_v0_2->unk4 / 9) * 9);
                temp_v0_3 = arg0->unk28;
                temp_a0 = temp_v0_3->unk10;
                arg0->unk2C = (s32) (temp_a0->unk0 * 0x10 * temp_a0->unk4);
                temp_v1 = temp_v0_3->unkC;
                if (temp_v1 != NULL) {
                    arg0->unk1C = (s32) temp_v1->unk0;
                    arg0->unk20 = (s32) ((Unk *)temp_v0_3->unkC)->unk4;
                    arg0->unk24 = (s32) ((Unk *)temp_v0_3->unkC)->unk8;
                    memcpyBytes(temp_v0_3->unkC + 0xC, arg0->unk18, 0x20);
                    return;
                }
                arg0->unk24 = 0;
                arg0->unk20 = 0;
                arg0->unk1C = 0;
                return;
            case 1:
                temp_v0_4 = arg0->unk28;
                arg0->unk4 = &func_8008380C;
                temp_v1_2 = temp_v0_4->unkC;
                if (temp_v1_2 != NULL) {
                    arg0->unk1C = (s32) temp_v1_2->unk0;
                    arg0->unk20 = (s32) ((Unk *)temp_v0_4->unkC)->unk4;
                    arg0->unk24 = (s32) ((Unk *)temp_v0_4->unkC)->unk8;
                    return;
                }
                arg0->unk24 = 0;
                arg0->unk20 = 0;
                arg0->unk1C = 0;
                return;
            }
        }
    } else {
        temp_v0_5 = arg0->unk28;
        arg0->unk3C = 0;
        arg0->unk40 = 1;
        arg0->unk38 = 0;
        if (temp_v0_5 != NULL) {
            arg0->unk44 = (s32) temp_v0_5->unk0;
            temp_v1_3 = temp_v0_5->unk8;
            if (temp_v1_3 == 0) {
                temp_v1_4 = temp_v0_5->unkC;
                if (temp_v1_4 != NULL) {
                    arg0->unk24 = (s32) temp_v1_4->unk8;
                }
            } else if (temp_v1_3 == 1) {
                temp_v1_5 = temp_v0_5->unkC;
                if (temp_v1_5 != NULL) {
                    arg0->unk24 = (s32) temp_v1_5->unk8;
                }
            }
        }
    }
}
