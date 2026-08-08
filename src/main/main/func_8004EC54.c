#include "ultra64.h"
s32 heap_alloc_default(s32);                               /* extern */
extern s32 gRenderBase;
extern s32 gGameInitParam;

void frameHeapInit(void) {
    s32 temp_v0;

    temp_v0 = heap_alloc_default(0xFA00);
    gGameInitParam = temp_v0;
    gRenderBase = temp_v0;
}
