#include "ultra64.h"
void **func_8004D7A0(void *);                       /* extern */
extern s32 D_8004B8B0;

char *func_8004E6F4(s32 arg0) {
    Unk *temp_v0;

    temp_v0 = *func_8004D7A0((arg0 * 0x10) + &D_8004B8B0);
    ((Unk *)temp_v0->unk30)->unk34 = (f32) temp_v0->unk40;
    ((Unk *)temp_v0->unk30)->unk38 = (f32) temp_v0->unk44;
    ((Unk *)temp_v0->unk30)->unk3C = (f32) temp_v0->unk48;
    ((Unk *)temp_v0->unk30)->unk40 = (f32) temp_v0->unk4C;
    ((Unk *)temp_v0->unk30)->unk44 = (f32) temp_v0->unk50;
    ((Unk *)temp_v0->unk30)->unk48 = (f32) temp_v0->unk54;
    return temp_v0->unk30;
}
