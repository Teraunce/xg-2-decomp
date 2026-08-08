#include "ultra64.h"
s32 *overlayDecompress(void *);                         /* extern */
extern s32 gOverlayTable;

s32 audioLoadBank(s32 arg0) {
    return *overlayDecompress((arg0 * 0x10) + &gOverlayTable);
}
