#include "ultra64.h"
void func_8007BCD8(Unk*, s32, s32);                       /* extern */
void func_8007BD08(OSThread*, OSId, u32, s32, u32, OSPri);        /* extern */
void func_8007D0E8(Unk*);                               /* extern */
extern s32 D_80174BD0;
extern s32 D_8017BF58;
extern s32 D_8017C8B0;
extern Unk D_8017CCC0;
extern s32 func_800541C0;

void func_800555D8(s32 arg0) {
    func_8007BCD8(&D_80174BD0, &D_8017C8B0, 0x20);
    D_8017CCC0.unk0 = arg0;
    D_8017CCC0.unk4 = &D_80174BD0;
    func_8007BD08(&D_8017BF58, 4, &func_800541C0, &D_8017CCC0, &D_8017BF58, 7);
    func_8007D0E8(&D_8017BF58);
}
