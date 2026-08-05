#include "ultra64.h"
/* Warning: missing "jr $ra" in last block of func_8007DA6C (initial). */

void func_8007D7D8(void *, s32, s32);              /* extern */
extern s32 gPendingFlushFlag;

void func_8007D8CC(Unk *arg0, s32 arg1) {
    s32 var_s3;
    char *temp_a0;
    char *temp_a0_2;
    Unk *temp_t9;
    Unk *temp_v0;
    Unk *var_s2;
    Unk *var_t3;

    if (arg0->unk0 == 0x4231) {
        var_s3 = 0;
        var_s2 = arg0;
        if (arg0->unk2 > 0) {
            do {
                temp_t9 = var_s2->unk4 + arg0;
                var_s2->unk4 = temp_t9;
                if ((temp_t9 != NULL) && (temp_t9->unk2 == 0)) {
                    temp_v0 = temp_t9->unk8;
                    temp_t9->unk2 = 1U;
                    temp_a0 = (char*)((s32)temp_v0 + (s32)arg0);
                    if (temp_v0 != NULL) {
                        temp_t9->unk8 = temp_a0;
                        func_8007D7D8(temp_a0, arg0, arg1);
                    }
                    var_t3 = (s32)0 /* implicit $t5 count from caller */;
                    if ((s32)0 /* implicit $t5 count from caller */ > 0) {
                        do {
                            temp_a0_2 = var_t3->unkC + arg0;
                            var_t3->unkC = temp_a0_2;
                            if (temp_a0_2 != NULL) {
                                func_8007D7D8(temp_a0_2, arg0, arg1);
                            }
                            var_t3 = (Unk*)((s32)var_t3 + 4); /* $t3 loop feedback: var_t3 + 4 */
                        } while (((s32)0 /* $t4 loop counter */ + 1) < (s32)0 /* implicit $t5 count from caller */);
                    }
                }
                var_s3 += 1;
                var_s2 += 4;
            } while (var_s3 < arg0->unk2);
        }
    }
}

void func_8007D9D0(Unk *arg0, s32 arg1) {
    s32 temp_t7;
    s32 var_v0;
    Unk *var_v1;

    var_v0 = 0;
    var_v1 = arg0;
    if (arg0->unk2 > 0) {
        do {
            temp_t7 = var_v1->unk4;
            var_v0 += 1;
            var_v1 += 8;
            *(s32*)((char*)var_v1 - 4)= (s32) (temp_t7 + arg1);
        } while (var_v0 < arg0->unk2);
    }
}

void __osTimerUnlink(Unk *arg0) {
    void **temp_v0_2;
    Unk *temp_v0;

    temp_v0 = arg0->unk0;
    if (temp_v0 != NULL) {
        temp_v0->unk4 = (void **) arg0->unk4;
    }
    temp_v0_2 = arg0->unk4;
    if (temp_v0_2 != NULL) {
        *temp_v0_2 = arg0->unk0;
    }
}

void __osTimerInsert(Unk *arg0, void **arg1) {
    Unk *temp_v0;

    arg0->unk4 = arg1;
    arg0->unk0 = (void *) *arg1;
    temp_v0 = *arg1;
    if (temp_v0 != NULL) {
        temp_v0->unk4 = arg0;
    }
    *arg1 = arg0;
}

void func_8007DA74(void);  /* forward: GETTER_NOJR fallthrough */
void func_8007DA6C(void) {
    func_8007DA74();
}
