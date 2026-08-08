#include "ultra64.h"
void overlayMarkNodes(char*, u16*, s32, s32);              /* extern */
void overlayMarkLeaf(char*, u16*, s32);                   /* extern */
extern s32 gRenderInitDone;

void overlayNodeMark(Unk *arg0) {
    s16 sp10;
    s32 temp_a2;
    s32 temp_s1;

    sp10 = 0;
    temp_s1 = arg0->unk50;
    gRenderInitDone = 0;
    overlayMarkNodes(temp_s1, &sp10, arg0->unk160, arg0->unk164);
    temp_a2 = arg0->unk168;
    if (temp_a2 != 0) {
        overlayMarkLeaf(temp_s1, &sp10, temp_a2);
    }
}
