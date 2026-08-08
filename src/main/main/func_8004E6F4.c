#include "ultra64.h"
void **overlayDecompress(void *);                       /* extern */
extern s32 gOverlayTable2;

char *audioLoadWavetable(s32 arg0) {
    Unk *temp_v0;

    temp_v0 = *overlayDecompress((arg0 * 0x10) + &gOverlayTable2);
    ((Unk *)temp_v0->unk30)->unk34 = (f32) temp_v0->unk40;
    ((Unk *)temp_v0->unk30)->unk38 = (f32) temp_v0->unk44;
    ((Unk *)temp_v0->unk30)->unk3C = (f32) temp_v0->unk48;
    ((Unk *)temp_v0->unk30)->unk40 = (f32) temp_v0->unk4C;
    ((Unk *)temp_v0->unk30)->unk44 = (f32) temp_v0->unk50;
    ((Unk *)temp_v0->unk30)->unk48 = (f32) temp_v0->unk54;
    return temp_v0->unk30;
}
