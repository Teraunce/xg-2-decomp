#include "ultra64.h"
u8 func_8007DC58(s32, s32);                         /* extern */
s32 func_8007DD1C();                                /* extern */

void func_8007DD7C(Unk *arg0, Unk *arg1) {
    s32 sp28;
    s32 sp24;
    s32 temp_a2;
    s32 temp_t6;
    s32 temp_t9;
    s32 var_t3;
    s32 var_v0;
    s8 temp_a2_2;
    s8 temp_v0;
    s8 temp_v0_2;
    u32 temp_a0;
    u32 var_t1;
    u8 temp_a0_2;
    Unk *temp_t5;
    Unk *temp_v0_3;
    Unk *temp_v0_4;
    Unk *temp_v1;
    char *var_t9;

    var_t1 = -1U;
    temp_a2 = arg0->unk10;
    var_t3 = sp24;
    var_v0 = 0;
    do {
        if (((u32) arg0->unk4 >> var_v0) & 1) {
            temp_v1 = arg0 + (var_v0 * 4);
            if (arg0->unk14 != 0) {
                temp_v1->unkB8 = (u32) (temp_v1->unkB8 - temp_a2);
            }
            temp_a0 = temp_v1->unkB8;
            if (temp_a0 < var_t1) {
                var_t1 = temp_a0;
                var_t3 = var_v0;
            }
        }
        var_v0 += 1;
    } while (var_v0 != 0x10);
    temp_v0 = func_8007DC58(arg0, var_t3);
    if (temp_v0 == 0xFF) {
        temp_v0_2 = func_8007DC58((s32)0 /* implicit $t4 from caller */, (s32)0 /* implicit $t3 from caller */);
        temp_a2_2 = temp_v0_2 & 0xFF;
        if (temp_v0_2 == 0x51) {
            arg1->unk0 = 3;
            arg1->unk8 = (u8)(s32)0 /* implicit $t2 from caller */;
            arg1->unk9 = temp_a2_2;
            arg1->unkB = func_8007DC58((s32)0 /* implicit $t4 from caller */, (s32)0 /* implicit $t3 from caller */);
            arg1->unkC = func_8007DC58((s32)0 /* implicit $t4 from caller */, (s32)0 /* implicit $t3 from caller */);
            arg1->unkD = func_8007DC58((s32)0 /* implicit $t4 from caller */, (s32)0 /* implicit $t3 from caller */);
            ((Unk*)((s32)0 /* implicit $t4 from caller */ + (s32)0 /* implicit $t3 from caller */))->unkA8 = 0;
        } else if (temp_v0_2 == 0x2F) {
            temp_t6 = ((Unk*)0 /* implicit $t4 */)->unk4 ^ (1 << (s32)0 /* implicit $t3 from caller */);
            ((Unk*)0 /* implicit $t4 */)->unk4 = temp_t6;
            if (temp_t6 != 0) {
                arg1->unk0 = 0x12;
            } else {
                arg1->unk0 = 4;
            }
        } else if (temp_v0_2 == 0x2E) {
            func_8007DC58((s32)0 /* implicit $t4 from caller */, (s32)0 /* implicit $t3 from caller */);
            func_8007DC58((s32)0 /* implicit $t4 from caller */, (s32)0 /* implicit $t3 from caller */);
            ((Unk*)((s32)0 /* implicit $t4 from caller */ + (s32)0 /* implicit $t3 from caller */))->unkA8 = 0;
            arg1->unk0 = 0x13;
        } else if (temp_v0_2 == 0x2D) {
            temp_t5 = (s32)0 /* implicit $t4 from caller */ + ((s32)0 /* implicit $t3 from caller */ * 4);
            temp_v0_3 = temp_t5->unk18;
            temp_a0_2 = temp_v0_3->unk1;
            temp_v0_4 = temp_v0_3 + 1;
            var_t9 = temp_v0_4 + 5;
            if (temp_a0_2 == 0) {
                temp_v0_3->unk1 = (u8) temp_v0_4->unk0 /* FIXME: was ->unk-1 */;
            } else {
                if (temp_a0_2 != 0xFF) {
                    temp_v0_3->unk1 = (u8) (temp_a0_2 - 1);
                }
                var_t9 = (temp_v0_4 + 5) - ((temp_v0_4->unk1 << 0x18) + (temp_v0_4->unk2 << 0x10) + (temp_v0_4->unk3 << 8) + temp_v0_4->unk4);
            }
            temp_t5->unk18 = var_t9;
            ((Unk*)((s32)0 /* implicit $t4 from caller */ + (s32)0 /* implicit $t3 from caller */))->unkA8 = 0;
            arg1->unk0 = 0x14;
        }
    } else {
        arg1->unk0 = 1;
        if (temp_v0 & 0x80) {
            arg1->unk8 = (u8) (temp_v0 & 0xFF);
            arg1->unk9 = func_8007DC58((s32)0 /* implicit $t4 from caller */, (s32)0 /* implicit $t3 from caller */);
            ((Unk*)((s32)0 /* implicit $t4 from caller */ + (s32)0 /* implicit $t3 from caller */))->unkA8 = (s8) (s32)0 /* implicit $t2 from caller */;
        } else {
            arg1->unk9 = temp_v0;
            arg1->unk8 = (u8) ((Unk*)((s32)0 /* implicit $t4 from caller */ + (s32)0 /* implicit $t3 from caller */))->unkA8;
        }
        temp_t9 = arg1->unk8 & 0xF0;
        if ((temp_t9 != 0xC0) && (temp_t9 != 0xD0)) {
            arg1->unkA = func_8007DC58((s32)0 /* implicit $t4 from caller */, (s32)0 /* implicit $t3 from caller */);
            if ((arg1->unk8 & 0xF0) == 0x90) {
                sp28 = (s32)0 /* implicit $t1 from caller */;
                sp24 = (s32)0 /* implicit $t3 from caller */;
                arg1->unkC = func_8007DD1C();
            }
        } else {
            arg1->unkA = 0;
        }
    }
    arg1->unk4 = (s32)0 /* implicit $t1 from caller */;
    ((Unk*)0 /* implicit $t4 */)->unk10 = (s32)0 /* implicit $t1 from caller */;
    ((Unk*)0 /* implicit $t4 */)->unkC = (s32) (((Unk*)0 /* implicit $t4 */)->unkC + (s32)0 /* implicit $t1 from caller */);
    if (arg1->unk0 != 0x12) {
        ((Unk*)0 /* implicit $t5 */)->unkB8 = (s32) (((Unk*)0 /* implicit $t5 */)->unkB8 + func_8007DD1C());
    }
    ((Unk*)0 /* implicit $t4 */)->unk14 = 1;
}
