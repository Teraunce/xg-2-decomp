#include "ultra64.h"
#define M2C_ERROR(x) ((Unk *)0)
typedef struct {
    /* 0x00 */ u8 pad00[0x10];
    /* 0x10 */ s32 unk10;
} UnkStruct_sp1C;

void func_8008DD34();                                  /* extern */
extern s32 D_80095290;
extern s32 D_A4600010;
extern s32 D_A5000510;

void func_8008DC54(void) {
    UnkStruct_sp1C *sp1C;
    s32 sp18;

    sp1C = (s32)M2C_ERROR(/* Read from unset register $t6 */) + 0x14;
    sp18 = D_A4600010;
    if (sp18 & 3) {
        do {
            sp18 = D_A4600010;
        } while (sp18 & 3);
    }
    D_A5000510 = sp1C->unk10 | 0x10000000;
    sp18 = D_A4600010;
    if (sp18 & 3) {
        do {
            sp18 = D_A4600010;
        } while (sp18 & 3);
    }
    D_A5000510 = sp1C->unk10;
    func_8008DD34();
    D_A4600010 = 2;
    D_80095290 |= 0x100401;
}
