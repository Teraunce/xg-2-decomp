#include "ultra64.h"
void func_8007AA68(char *arg0, f32 *arg1, char *arg2) {
    s32 sp5C;
    f32 sp1C;
    f32 *temp_a1;
    f32 *var_a0_2;
    f32 *var_a1;
    f32 *var_t1;
    f32 *var_v1;
    f32 temp_ft1;
    f32 var_ft4;
    f32 var_ft5;
    s32 var_a0;
    Unk *temp_t1;
    Unk *var_a3;
    Unk *var_v1_2;

    var_v1 = &sp1C;
    var_a3 = arg0;
    do {
        var_a1 = var_v1;
        var_t1 = arg1;
        *var_a1 = 0.0f;
        var_a0 = 4;
        var_ft4 = *var_a1;
        var_ft5 = var_a3->unk0 * *var_t1;
        if (4 != 0x10) {
            do {
                var_a0 += 4;
                var_a1 += 4;
                var_t1 += 4;
                ((Unk*)var_a1)->unk0 /* FIXME: was ->unk-4 */ = (f32) (var_ft4 + var_ft5);
                ((Unk*)var_a1)->unk0 /* FIXME: was ->unk-4 */ = (f32) (((Unk*)var_a1)->unk0 /* FIXME: was ->unk-4 */ + (var_a3->unk4 * ((Unk*)var_t1)->unkC));
                ((Unk*)var_a1)->unk0 /* FIXME: was ->unk-4 */ = (f32) (((Unk*)var_a1)->unk0 /* FIXME: was ->unk-4 */ + (var_a3->unk8 * ((Unk*)var_t1)->unk1C));
                ((Unk*)var_a1)->unk0 = 0.0f;
                var_ft4 = ((Unk*)var_a1)->unk0;
                ((Unk*)var_a1)->unk0 /* FIXME: was ->unk-4 */ = (f32) (((Unk*)var_a1)->unk0 /* FIXME: was ->unk-4 */ + (var_a3->unkC * ((Unk*)var_t1)->unk2C));
                var_ft5 = var_a3->unk0 * ((Unk*)var_t1)->unk0;
            } while (var_a0 != 0x10);
        }
        temp_a1 = var_a1 + 4;
        temp_t1 = var_t1 + 4;
        ((Unk*)temp_a1)->unk0 /* FIXME: was ->unk-4 */ = (f32) (var_ft4 + var_ft5);
        ((Unk*)temp_a1)->unk0 /* FIXME: was ->unk-4 */ = (f32) (((Unk*)temp_a1)->unk0 /* FIXME: was ->unk-4 */ + (var_a3->unk4 * ((Unk*)temp_t1)->unkC));
        ((Unk*)temp_a1)->unk0 /* FIXME: was ->unk-4 */ = (f32) (((Unk*)temp_a1)->unk0 /* FIXME: was ->unk-4 */ + (var_a3->unk8 * ((Unk*)temp_t1)->unk1C));
        ((Unk*)temp_a1)->unk0 /* FIXME: was ->unk-4 */ = (f32) (((Unk*)temp_a1)->unk0 /* FIXME: was ->unk-4 */ + (var_a3->unkC * ((Unk*)temp_t1)->unk2C));
        var_v1 += 0x10;
        var_a3 += 0x10;
    } while ((u32) var_v1 < (u32) &sp5C);
    var_v1_2 = arg2;
    var_a0_2 = &sp1C;
    do {
        temp_ft1 = *var_a0_2;
        var_a0_2 += 0x10;
        var_v1_2 += 0x10;
        var_v1_2->unk0 /* FIXME: was ->unk-10 */ = temp_ft1;
        var_v1_2->unk0 /* FIXME: was ->unk-C */ = (f32) ((Unk*)var_a0_2)->unk0 /* FIXME: was ->unk-C */;
        var_v1_2->unk0 /* FIXME: was ->unk-8 */ = (f32) ((Unk*)var_a0_2)->unk0 /* FIXME: was ->unk-8 */;
        var_v1_2->unk0 /* FIXME: was ->unk-4 */ = (f32) ((Unk*)var_a0_2)->unk0 /* FIXME: was ->unk-4 */;
    } while ((void*)var_a0_2 != (void*)&sp5C);
}
