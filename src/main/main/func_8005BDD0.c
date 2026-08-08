#include "ultra64.h"
void audioDecodeLZSS(s32);                                 /* extern */

void audioDrainDecode(void) {
    audioDecodeLZSS(0x7FFFFFFF);
}
