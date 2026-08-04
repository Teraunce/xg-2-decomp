#include "ultra64.h"
#define M2C_ERROR(x) ((Unk *)0)
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ u8 pad08[0x8];
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
} UnkStruct_arg0;
typedef struct {
    /* 0x00 */ char *unk0;
    /* 0x04 */ char *unk4;
    /* 0x08 */ u8 pad08[0x8];
    /* 0x10 */ s32 unk10;
    /* 0x14 */ u32 unk14;
} UnkStruct_sp34;
typedef struct {
    /* 0x00 */ u8 pad00[0x10];
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
} UnkStruct_temp_t3;
typedef struct {
    /* 0x00 */ u8 pad00[0x10];
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
} UnkStruct_temp_t7;

s32 func_8007C768();                                /* extern */
s32 func_8007C788(s32);                               /* extern */
extern void **D_800952C0;

u32 func_8007D4F0(UnkStruct_arg0 *arg0) {
    UnkStruct_sp34 *sp34;
    u32 sp2C;
    s8 sp28;
    s32 sp24;
    u32 *sp20;
    char *sp1C;
    UnkStruct_temp_t3 *temp_t3;
    UnkStruct_temp_t7 *temp_t7;
    u32 temp_t0;
    u32 temp_t1;
    u32 temp_t2;
    u32 temp_t5;
    u32 temp_t5_2;
    u32 temp_t6;
    u32 temp_t7_2;

    sp24 = func_8007C768();
    temp_t7 = *D_800952C0;
    sp34 = temp_t7;
    temp_t1 = arg0->unk14;
    temp_t0 = arg0->unk10;
    sp2C = temp_t1;
    sp28 = temp_t0;
    if ((void*)temp_t7 != (void*)D_800952C0) {
        temp_t2 = temp_t7->unk10;
        if ((temp_t0 >= temp_t2) && ((temp_t2 < temp_t0) || ((u32) temp_t7->unk14 < temp_t1))) {
loop_4:
            sp20 = &sp28;
            temp_t5 = ((Unk*)&sp28)->unk4;
            temp_t7_2 = sp34->unk14;
            ((Unk*)&sp28)->unk4 = (u32) (temp_t5 - temp_t7_2);
            ((Unk*)&sp28)->unk0 = (((Unk*)&sp28)->unk0 - sp34->unk10) - (temp_t5 < temp_t7_2);
            temp_t3 = sp34->unk0;
            sp34 = temp_t3;
            if ((void*)temp_t3 != (void*)D_800952C0) {
                temp_t6 = temp_t3->unk10;
                if ((temp_t6 < sp28) || ((sp28 >= temp_t6) && ((u32) temp_t3->unk14 < sp2C))) {
                    goto loop_4;
                }
            }
        }
    }
    arg0->unk10 = sp28;
    arg0->unk14 = sp2C;
    if ((void*)sp34 != (void*)D_800952C0) {
        sp1C = sp34 + 0x10;
        temp_t5_2 = sp34->unk14;
        sp34->unk14 = (u32) (temp_t5_2 - sp2C);
        sp34->unk10 = (s32) ((sp34->unk10 - sp28) - (temp_t5_2 < sp2C));
    }
    arg0->unk0 = sp34;
    arg0->unk4 = (void *) sp34->unk4;
    *sp34->unk4 = arg0;
    sp34->unk4 = arg0;
    func_8007C788(sp24);
    return sp28;
}

void func_8007D678(void) {
    (s32)M2C_ERROR(/* mtc0 $a0, $11 */);
}
