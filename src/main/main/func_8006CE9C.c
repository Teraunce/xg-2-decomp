#include "ultra64.h"
typedef struct {
    /* 0x00 */ u8 pad00[0x10];
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ s32 unk24;
    /* 0x28 */ s32 unk28;
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ s32 unk30;
    /* 0x34 */ s32 unk34;
    /* 0x38 */ s32 unk38;
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ s32 unk40;
    /* 0x44 */ s32 unk44;
    /* 0x48 */ s32 unk48;
    /* 0x4C */ s32 unk4C;
} UnkStruct_arg0;

void sfxLoadUcode(UnkStruct_arg0*);                   /* extern */
void osSpTaskStart(s32);                            /* extern */
extern s32 D_800777C8;
extern s32 D_80077898;
extern s32 D_80078A28;
extern s32 gGameFlags;
extern s32 D_80094250;
extern s32 D_80094640;
extern s32 D_8016C5D0;
extern s32 D_80190810;
extern s32 D_801928A0;
extern s32 D_801A28A0;

char *sfxRspTaskRunLen(UnkStruct_arg0 *arg0, s32 arg1) {
    char *var_v0;
    char *temp_s0;

    arg0->unk10 = 1;
    arg0->unk1C = (s32) (&D_80077898 - &D_800777C8);
    arg0->unk18 = &D_800777C8;
    arg0->unk14 = 0;
    if (gGameFlags & 4) {
        arg0->unk20 = &D_80077898;
        var_v0 = &D_80094250;
    } else {
        arg0->unk20 = &D_80078A28;
        var_v0 = &D_80094640;
    }
    arg0->unk28 = var_v0;
    temp_s0 = arg0 + 0x10;
    arg0->unk24 = 0x1000;
    arg0->unk2C = 0x800;
    arg0->unk30 = &D_80190810;
    arg0->unk34 = 0x400;
    arg0->unk38 = &D_801928A0;
    arg0->unk3C = &D_801A28A0;
    arg0->unk48 = &D_8016C5D0;
    arg0->unk40 = (void *) (arg0 + 0x58);
    arg0->unk44 = arg1;
    arg0->unk4C = 0xC00;
    sfxLoadUcode(temp_s0);
    osSpTaskStart(temp_s0);
    return temp_s0;
}
