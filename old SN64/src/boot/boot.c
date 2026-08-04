/**
 * boot.c — Handwritten boot stub
 *
 * ROM:0x1000 → VRAM:0x8004B400
 * IPL3 (CIC-6102) copies ROM[0x1000..0x101000] to VRAM:0x8004B400
 * and jumps here. This stub clears BSS (empty in shipped ROM),
 * calls the LZSS decompressor (func_8004B498), then hits a BREAK.
 * func_8004B464 (cache flush) and func_8004B498 (decompressor) are
 * called from here and do not return to this stub.
 */

#include "ultra64.h"

/* BSS start/end symbols from linker script (both resolve to same address
   in this build — BSS section is empty). */
extern u32 _bssStart;
extern u32 _bssEnd;

/* Second BSS range (also empty). */
extern u32 _bss2Start;
extern u32 _bss2End;

void func_8004B498(void);
void func_8004B464(void);

void func_8004B400(void) {
    u32 *ptr;
    u32 *end;

    /* Clear first BSS range */
    ptr = &_bssStart;
    end = &_bssEnd;
    while (ptr < end) {
        *ptr++ = 0;
    }

    /* Clear second BSS range */
    ptr = &_bss2Start;
    end = &_bss2End;
    while (ptr < end) {
        *ptr++ = 0;
    }

    /* Run LZSS decompressor + OS init (does not return — jumps to
       decompressed code at 0x8004BA20 after decompression). */
    func_8004B498();

    /* Dead code: func_8004B498 never returns. */
    BREAK(1);
}
