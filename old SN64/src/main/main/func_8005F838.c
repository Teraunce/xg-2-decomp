#include "ultra64.h"
s32 func_8004E6C8(s32);                               /* extern */
s32 func_8004E6F4(s32);                               /* extern */
void func_8005B224(s32, u8*, u32);                     /* extern */
void func_800622C0();                                  /* extern */
void func_8007BA98(u32, s32);                          /* extern */
void func_8007BB48(u32, s32);                          /* extern */
void func_8007BCA8();                                  /* extern */
s32 func_8009F528(s32);                                 /* extern */
s32 func_800AE1C8();                                  /* extern */
s32 func_800AE368(s32);                                 /* extern */
extern s32 D_31880;
extern s32 D_8004BA18;
extern s32 D_800B55C0;
extern s8 D_80181F00;
extern Unk D_80181FD0;
extern s8 D_80182280;
extern Unk D_801822E0;

void func_8005F838(void) {
    s32 *var_a1;
    s32 *var_v1;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 var_a0;
    s32 var_a0_2;
    s8 *temp_v0;
    s8 *temp_v1;

    func_8007BCA8();
    func_8007BA98(&D_800B55C0, &D_31880);
    func_8007BB48(&D_800B55C0, &D_31880);
    func_8005B224(D_8004BA18 + 0x18, &D_800B55C0, &D_31880);
    func_8007BCA8();
    func_8007BA98(&D_800B55C0, &D_31880);
    func_8007BB48(&D_800B55C0, &D_31880);
    func_8009F528(0x13);
    func_800AE1C8();
    var_a0 = 0;
    var_a1 = &D_801822E0;
    var_v1 = &D_80181FD0;
    do {
        *var_v1 = 0;
        *var_a1 = 0;
        var_a1 += 4;
        var_a0 += 1;
        var_v1 += 4;
    } while (var_a0 < 0x1A);
    var_a0_2 = 0;
    do {
        temp_v1 = &(&D_80182280)[var_a0_2];
        temp_v0 = &(&D_80181F00)[var_a0_2];
        var_a0_2 += 1;
        *temp_v0 = 0;
        *temp_v1 = 0;
    } while (var_a0_2 < 0xD);
    temp_v0_2 = func_8004E6C8(0);
    D_801822E0.unk0 = temp_v0_2;
    D_80181FD0.unk0 = temp_v0_2;
    temp_v0_3 = func_8004E6F4(0);
    D_80181FD0.unk34 = temp_v0_3;
    D_801822E0.unk34 = temp_v0_3;
    func_800AE368(0);
    D_80181F00 = 1;
    D_80182280 = 1;
    func_800622C0();
}
