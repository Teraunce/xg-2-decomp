#include "ultra64.h"
char *heap_alloc_default(s32);                             /* extern */
void audioPlayCopySample(s32, s32, s32);                     /* extern */
u32 *sfxFreeBlock(s32 arg0);                       /* static */
extern s32 D_8004B658;
extern u32 *gSfxDefTable;
extern Unk D_800E6E40;
extern Unk *D_801823D0;
extern u16 D_801823D4;
extern Unk D_801823D8;
extern char *D_801823DC;
extern u32 D_801823E0;
extern s32 D_85388;

void sfxTableInit(void) {
    s32 temp_s0;
    s32 var_v0;
    u16 var_v1;
    u32 *temp_v0_3;
    Unk *temp_v0;
    Unk *temp_v0_2;

    temp_v0 = heap_alloc_default(0x200);
    D_801823D0 = temp_v0;
    var_v1 = 0;
    var_v0 = 0 * 8;
    do {
        var_v1 += 1;
        temp_v0_2 = var_v0 + temp_v0;
        temp_v0_2->unk0 = 0;
        temp_v0_2->unk4 = var_v1;
        var_v0 = var_v1 * 8;
    } while (var_v1 < 0x40U);
    D_801823D4 = 1;
    D_801823D0->unk1FC = 0;
    D_801823D8.unk0 = 0;
    D_801823D8.unk4 = &D_800E6E40;
    D_800E6E40.unk0 = &D_85388;
    D_800E6E40.unk4 = 0;
    audioPlayCopySample(D_8004B658, 4, &D_801823E0);
    temp_s0 = D_801823E0 * 0x10;
    temp_v0_3 = sfxFreeBlock(temp_s0);
    gSfxDefTable = temp_v0_3;
    audioPlayCopySample(D_8004B658 + 8, temp_s0, temp_v0_3);
}

u16 sfxAllocBlock(s32 arg0) {
    u16 temp_a2;
    u32 *temp_v1_2;
    Unk *var_a1;
    Unk *var_a3;
    u32 temp_v1;
    u32 var_a0;
    Unk *temp_t0;

    var_a3 = &D_801823D8;
    temp_a2 = D_801823D4;
    var_a1 = D_801823D8.unk4;
    if (temp_a2 == 0) {
        return 0U;
    }
    temp_t0 = (temp_a2 * 8) + D_801823D0;
    var_a0 = (arg0 + 0xF) & ~0xF;
    D_801823D4 = temp_t0->unk4;
    if (var_a0 < 8U) {
        var_a0 = 8;
    }
    if (var_a1 != NULL) {
loop_6:
        temp_v1 = var_a1->unk0;
        if (temp_v1 < var_a0) {
            var_a3 = var_a1;
            var_a1 = var_a1->unk4;
            if (var_a1 == NULL) {
                /* Duplicate return node #14. Try simplifying control flow for better match */
                return 0U;
            }
            goto loop_6;
        }
        temp_t0->unk0 = var_a1;
        if ((u32) (temp_v1 - 8) >= var_a0) {
            temp_v1_2 = var_a1 + var_a0;
            temp_t0->unk4 = var_a0;
            var_a3->unk4 = temp_v1_2;
            *temp_v1_2 = var_a1->unk0 - var_a0;
            ((Unk *)var_a3->unk4)->unk4 = (u32 *) var_a1->unk4;
        } else {
            temp_t0->unk4 = (u32) var_a1->unk0;
            var_a3->unk4 = (u32 *) var_a1->unk4;
        }
        return temp_a2;
    }
    return 0U;
}

u32 *sfxFreeBlock(s32 arg0) {
    Unk *temp_v0_2;
    Unk *var_a2;
    Unk *var_v1;
    u32 temp_a0;
    u32 temp_a1;
    u32 temp_v0;

    var_a2 = &D_801823D8;
    var_v1 = D_801823D8.unk4;
    temp_a0 = (arg0 + 0xF) & ~0xF;
    if (var_v1 != NULL) {
loop_1:
        temp_v0_2 = var_v1->unk4;
        if (temp_v0_2 != NULL) {
            var_a2 = var_v1;
            var_v1 = temp_v0_2;
            goto loop_1;
        }
        if ((var_v1 == NULL) || (temp_a1 = var_v1->unk0, ((temp_a1 < temp_a0) != 0))) {
            /* Duplicate return node #5. Try simplifying control flow for better match */
            return NULL;
        }
        if ((u32) (temp_a1 - 8) < temp_a0) {
            var_a2->unk4 = 0;
            return var_v1;
        }
        temp_v0 = temp_a1 - temp_a0;
        var_v1->unk0 = temp_v0;
        return var_v1 + temp_v0;
    }
    return NULL;
}

void sfxPlay(u16 arg0) {
    s32 temp_a2;
    s32 var_v0;
    u16 temp_a0;
    Unk *var_a1;
    u32 temp_a2_2;
    u32 var_a0;
    Unk *temp_v0;
    Unk *temp_v0_2;
    Unk *temp_v1;

    var_a1 = &D_801823D8;
    var_a0 = D_801823D8.unk4;
    temp_v0 = ((arg0 & 0xFFFF) * 8) + D_801823D0;
    temp_v1 = temp_v0->unk0;
    temp_v1->unk0 = (s32) temp_v0->unk4;
    if (var_a0 != 0) {
        var_v0 = var_a0 < (u32) temp_v1;
loop_2:
        if (var_v0 != 0) {
            var_a1 = (u32 *) var_a0;
            var_a0 = ((Unk*)(s32)var_a0)->unk4;
            var_v0 = var_a0 < (u32) temp_v1;
            if (var_a0 != 0) {
                goto loop_2;
            }
        }
    }
    temp_a2 = temp_v1->unk0;
    if ((u32)(temp_v1 + temp_a2) == var_a0) {
        temp_v1->unk0 = (s32) (temp_a2 + ((Unk*)(s32)var_a0)->unk0);
        var_a0 = ((Unk*)(s32)var_a0)->unk4;
    }
    if (var_a1 == &D_801823D8) {
        var_a1->unk4 = temp_v1;
        goto block_13;
    }
    temp_a2_2 = var_a1->unk0;
    if ((var_a1 + temp_a2_2) != temp_v1) {
        var_a1->unk4 = temp_v1;
block_13:
        temp_v1->unk4 = var_a0;
    } else {
        var_a1->unk4 = (void *) var_a0;
        var_a1->unk0 = temp_a2_2 + temp_v1->unk0;
    }
    temp_a0 = D_801823D4;
    D_801823D4 = arg0;
    temp_v0_2 = ((arg0 & 0xFFFF) * 8) + D_801823D0;
    temp_v0_2->unk0 = 0;
    temp_v0_2->unk4 = temp_a0;
}

void sfxPhaseHook(void) {

}

void func_80063954(s32 *arg0, u32 *arg1, s32 *arg2) {
    u32 temp_v1;
    Unk *var_a3;

    var_a3 = D_801823DC;
    *arg0 = 0;
    *arg1 = 0;
    *arg2 = 0;
    if (var_a3 != NULL) {
        do {
            *arg0 += var_a3->unk0;
            temp_v1 = var_a3->unk0;
            if ((u32) *arg1 < temp_v1) {
                *arg1 = temp_v1;
            }
            *arg2 += 1;
            var_a3 = var_a3->unk4;
        } while (var_a3 != NULL);
    }
}

s32 sfxGetEntry(s32 arg0) {
    return *(s32*)((char*)D_801823D0 + (arg0 & 0xFFFF) * 8);
}

s32 func_800639D0(s32 arg0) {
    s32 var_v0;
    Unk *temp_a0;

    temp_a0 = ((arg0 & 0xFFFF) * 8) + D_801823D0;
    var_v0 = 0;
    if (temp_a0->unk0 != 0) {
        var_v0 = temp_a0->unk4;
    }
    return var_v0;
}

s32 func_800639FC(s32 arg0) {
    return D_8004B658 + *((arg0 * 0x10) + gSfxDefTable);
}

s32 func_80063A20(s32 arg0) {
    return ((Unk*)((char*)gSfxDefTable + arg0 * 0x10))->unk8;
}
