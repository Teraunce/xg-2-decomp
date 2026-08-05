#include "ultra64.h"
/* Warning: missing "jr $ra" in last block of func_8006D1EC (initial). */

s32 osVirtualToPhysical(u32);                       /* extern */
extern s32 gTrackNodeCount;
extern s32 gPendingEventFlag;
extern s32 D_80091E60;
extern s32 D_800934E0;
extern s32 D_80093980;
extern s32 D_80170870;
extern s32 D_80173BC0;
extern s32 D_80173C10;
extern s32 D_80173C18;
extern Unk *D_80173CC0;
extern s32 D_80178690;
extern s32 D_8017C114;
extern s32 D_8017C8A4;
extern s32 *D_8017C8A8;
extern s32 D_8017C930;
extern s32 D_8017CA44;

void func_8006CF98(Unk *arg0) {
    s32 *temp_a1;
    Unk *temp_a1_3;
    Unk *temp_s0;
    Unk *temp_s0_2;
    Unk *temp_s0_3;
    Unk *temp_v1_2;
    Unk *temp_v1_3;
    Unk *temp_v1_4;
    s32 temp_a1_2;
    s32 temp_v1;

    temp_a1 = arg0 + 0x58;
    D_8017C8A8 = temp_a1;
    temp_v1 = arg0 + 0x10DE0;
    D_80173C10 = temp_v1;
    D_80173CC0 = temp_a1;
    temp_a1_2 = arg0->unk1F540;
    D_80178690 = temp_v1;
    D_8017C114 = 0;
    D_80173CC0 = arg0 + 0x60;
    arg0->unk58 = 0xDB060000;
    D_80173CC0 = arg0 + 0x68;
    arg0->unk5C = 0;
    arg0->unk60 = 0xDB060004;
    D_8017C930 = D_80173BC0;
    D_80170870 = temp_a1_2;
    arg0->unk64 = osVirtualToPhysical(D_80091E60);
    temp_v1_2 = D_80173CC0;
    temp_s0 = D_80173CC0 + 8;
    temp_v1_2->unk4 = &D_80093980;
    D_80173CC0 = temp_s0;
    D_80173CC0 = temp_s0 + 8;
    temp_v1_2->unk0 = 0xDE000000;
    temp_s0->unk4 = &D_800934E0;
    D_80173CC0 = temp_s0 + 0x10;
    D_80173CC0->unk8 = 0xDE000000;
    temp_s0->unk8 = 0xFE000000;
    temp_s0->unkC = osVirtualToPhysical(D_80173BC0);
    if (gPendingEventFlag != 0) {
        temp_v1_3 = D_80173CC0;
        temp_s0_2 = D_80173CC0 + 8;
        temp_v1_3->unk0 = 0xE7000000;
        D_80173CC0 = temp_s0_2;
        D_80173CC0 = temp_s0_2 + 8;
        temp_v1_3->unk4 = 0;
        temp_s0_2->unk4 = 0x300000;
        D_80173CC0 = temp_s0_2 + 0x10;
        D_80173CC0->unk8 = 0xE3000A01;
        temp_s0_2->unk8 = (s32) (((D_8017CA44 - 1) & 0xFFF) | 0xFF100000);
        temp_s0_2->unkC = osVirtualToPhysical(D_80173BC0);
        temp_v1_4 = D_80173CC0;
        temp_a1_3 = D_80173CC0 + 8;
        temp_v1_4->unk0 = 0xF7000000;
        D_80173CC0 = temp_a1_3;
        D_80173CC0 = temp_a1_3 + 8;
        temp_v1_4->unk4 = 0xFFFCFFFC;
        temp_a1_3->unk4 = 0;
        D_80173CC0->unk8 = (s32) ((((D_8017CA44 - 1) & 0x3FF) << 0xE) | ((((D_80173C18 - 1) & 0x3FF) * 4) | 0xF6000000));
    }
    temp_s0_3 = D_80173CC0 + 8;
    D_80173CC0->unk0 = 0xE7000000;
    D_80173CC0->unk4 = 0;
    D_80173CC0->unk8 = (s32) (((D_8017CA44 - 1) & 0xFFF) | 0xFF100000);
    D_80173CC0 = temp_s0_3;
    D_80173CC0 = temp_s0_3 + 8;
    temp_s0_3->unk4 = osVirtualToPhysical(arg0->unk1F540);
}

void func_8006D1FC(void);  /* forward: GETTER_NOJR fallthrough */
void func_8006D1EC(void) {
    func_8006D1FC();
}
