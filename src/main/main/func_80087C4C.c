#include "ultra64.h"
void contParseReadRespGetter(s32, s32);                          /* extern */

void contGetInputPort(s32 arg0) {
    s32 sp1F;

    contParseReadRespGetter(&sp1F, arg0);
}
