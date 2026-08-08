#include "ultra64.h"
typedef struct {
    /* 0x00 */ u8 pad00[0xC];
    /* 0x0C */ s32 unkC;
} UnkStruct_arg1;

s32 *overlayDecompress(void *);                         /* extern */
extern s32 D_8004B7B0;

void overlayGetEntryAlt(s32 arg0, UnkStruct_arg1 *arg1) {
    arg1->unkC = (s32) *overlayDecompress((arg0 * 0x10) + &D_8004B7B0);
}
