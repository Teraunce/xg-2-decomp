#include "ultra64.h"
void func_8004D138(s32, s32, s32);                  /* extern */
char *func_8004D4A8(s32);                           /* extern */
void func_80063C08(void);                             /* extern */
extern s32 D_8004B650;
extern s32 D_8004B654;
extern char *D_801823E8;

void func_80063CD8(void) {
    s32 temp_s0;
    s32 temp_s1;
    s32 var_t0;
    u32 var_a1;
    u32 var_s0;
    u32 var_s1;
    Unk *temp_a2;
    Unk *temp_a3;
    char *temp_v0;
    Unk *temp_v1;
    Unk *var_a0;

    temp_s1 = D_8004B654;
    temp_s0 = D_8004B650;
    temp_v0 = func_8004D4A8(temp_s1);
    D_801823E8 = temp_v0;
    func_8004D138(temp_s0, temp_v0, temp_s1);
    var_a0 = D_801823E8;
    var_s1 = 0;
    var_a0->unk4 = (void *) (var_a0 + var_a0->unk4);
    if (var_a0->unk0 != 0) {
        temp_a3 = var_a0;
        var_t0 = 0;
        do {
            var_s0 = 0;
            temp_a2 = temp_a3->unk4 + var_t0;
            temp_a2->unk8 = (void *) (temp_a3 + temp_a2->unk8);
            if (temp_a2->unk4 != 0) {
                do {
                    var_a1 = 0;
                    var_a0 = temp_a2->unk8 + (var_s0 * 8);
                    var_a0->unk4 = (void *) (temp_a3 + var_a0->unk4);
                    if (var_a0->unk2 != 0) {
                        do {
                            temp_v1 = var_a0->unk4 + (var_a1 * 8);
                            temp_v1->unk4 = (void *) (temp_a3 + temp_v1->unk4);
                            var_a1 += 1;
                        } while (var_a1 < (u16) var_a0->unk2);
                    }
                    var_s0 += 1;
                } while (var_s0 < (u16) temp_a2->unk4);
            }
            var_s1 += 1;
            var_t0 += 0xC;
        } while (var_s1 < (u16) temp_a3->unk0);
    }
    func_80063C08();
}
