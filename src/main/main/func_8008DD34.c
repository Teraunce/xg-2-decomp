#include "ultra64.h"
s32 __osEnqueueThread(void *, s32);                          /* extern */
s32 __osPopQueue(void *);                          /* extern */
extern s32 __osRunQueue;
extern Unk gOsTimerQueue;

void piDmaNotify(void) {
    Unk *sp2C;
    Unk *sp28;
    s32 sp24;
    s32 temp_hi;

    sp2C = (Unk*)((char*)&gOsTimerQueue + 0x40);
    sp28 = (Unk*)gOsTimerQueue.unk40;
    if ((gOsTimerQueue.unk40 != 0) && (((Unk*)gOsTimerQueue.unk40)->unk8 < ((Unk*)gOsTimerQueue.unk40)->unk10)) {
        temp_hi = (s32) (sp28->unkC + sp28->unk8) % (s32) sp28->unk10;
        sp24 = temp_hi;
        *(s32*)(s32)(sp28->unk14 + (temp_hi * 4)) = (s32)sp2C->unk4;
        sp28->unk8 = (s32) (sp28->unk8 + 1);
        if (((Unk*)(s32)sp28->unk0)->unk0 != 0) {
            __osEnqueueThread(&__osRunQueue, __osPopQueue(sp28));
        }
    }
}
