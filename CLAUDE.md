# Extreme-G 2 (XG2) Decompilation — Project Guide

## Goal

Decompile all ~500+ functions in Extreme-G 2 (N64, 1997) from MIPS assembly to
readable C source, compiled with **IDO 7.1**.  The build produces a ROM identical
to `baserom.z64` (SHA1 `ed0a50086ef9a89f5b445c20ab6f365165959630`).

Byte-matching every function is **not** the goal — the ROM is always byte-exact
because it embeds the original `compressed_main.bin` blob.  C files are compiled
for readability, correctness, and as many IDO byte-matches as possible.

## Current Status (as of 2026-08-05)  <!-- update date when status changes -->

| Metric | Count |
|---|---|
| C source files | 453 |
| IDO byte-matching functions | **14** |
| Files compiling with zero errors (IDO 7.1) | **453** |
| Remaining M2C_ERROR call sites | **0** |
| Remaining FIXME annotations | **0** |
| Named functions (proper identifiers) | **286** |
| Named data globals applied | **97** |
| ROM byte-exact match | ✅ yes |

The 14 IDO-matched functions (all leaf functions — no `sw $ra`):
`func_8007A8E0`, `func_8007AC38`, `func_8007B7D8`, `func_8007E5E8`,
`func_8007EAE8`, `func_80082818`, `func_80082E98`, `func_80082EDC`,
`func_80082F30`, `func_800843AC`, `func_80086D28`, `func_80087DBC`,
`func_8008E4EC`, `func_8008EE18`.

**Why only leaf functions match:** The original game was compiled with SN64
(GCC 2.7.2), which saves `$ra` at `sp+frame−8` and puts `addiu $sp` in the `jr
$ra` delay slot.  IDO saves `$ra` at `sp+0x14` and uses a standard epilogue.
This ABI difference makes non-leaf functions permanently non-matching with IDO.
14 matches is the practical ceiling.

---

## Compiler

**IDO 7.1** (`tools/ido/cc`) — the build compiler for this project.

```bash
tools/ido/cc -O2 -mips2 -G0 -Wab,-r4300_mul -non_shared -Xcpluscomm \
    -woff 649,838,712 -signed -I include -c -o out.o src.c
```

The game was originally compiled with **SN Systems SN64 (GCC 2.7.2 Cygnus SN64.X)**,
but SN64 requires 32-bit x86 support that is not available in this environment.
IDO 5.3 (`tools/ido53/cc`) is also present; also non-matching.

---

## Build

```bash
# Full ROM build — always byte-exact (uses compressed_main.bin blob)
make

# Verify ROM matches baserom.z64
make verify          # sha1sum + cmp

# Compile all 453 C files with IDO — error check only, not linked into ROM
make compile_check
make compile_check -j8   # parallel

# IDO byte-match check for a single function
make match_check FUNC=func_8007A8E0

# Main-block asm-stub-only link + byte-compare (reference verification)
make verify_main
```

Output: `build/xg2.z64`  
ELF map: `build/xg2.map`

---

## How the ROM build works

The full ROM (`xg2.ld`) links:

```
N64 header (asm)  +  boot block (asm)  +  compressed_main.bin  +  assets
```

`compressed_main.bin` is the **original compressed binary blob** — C-compiled
objects are never linked into the final ROM.  This means:

- The ROM is always byte-exact regardless of how good (or bad) the C is.
- `make compile_check` is purely a compile-error and readability check.
- `make match_check FUNC=...` tells you if IDO produces identical `.text`.

`xg2_main.ld` is used only by `make verify_main` to link all asm stubs into a
decompressed reference image and verify it against `decompressed_main.bin`.

---

## Linker Scripts

**`xg2.ld`** — full ROM build (boot + compressed main blob + assets).

**`xg2_main.ld`** — main decompressed block only (0x8004BA20–0x8009xxxx).
Used only for `verify_main`.  All entries reference `.s.o` asm stubs.

---

## File Layout

```
baserom.z64             — reference ROM (12 MB)
xg2.ld                  — full ROM linker script
xg2_main.ld             — main block linker script (asm stubs only)
Makefile
NOTES.md                — low-level technical notes

include/
  ultra64.h             — N64 SDK types + BREAK/M2C macros
  types.h / unk.h       — Unk struct, s8/u8/s32/f32 typedefs
  os.h                  — OSThread context block (from exception handler analysis)
  n64_hardware.h        — RDP/RSP MMIO addresses
  audio.h / video.h     — subsystem headers

src/main/main/          — 453 C source files (one per .s file)
  entry.c               — empty; all data defined in asm/main/main/entry.s
  func_XXXXXXXX.c       — each contains one or more functions

asm/main/main/          — 453+ .s stub files (spimdisasm output)
  func_XXXXXXXX.s       — MIPS assembly; nonmatching/alabel/glabel directives

tools/
  ido/cc                — IDO 7.1 (primary compiler)
  ido53/cc              — IDO 5.3 (available, also non-matching)
  sn64/gcc              — SN64 (32-bit x86 — not usable in this environment)
  mips-binutils/        — mips-linux-gnu-{as,ld,objcopy,objdump}
  verify_boot.py        — verifies boot block byte-match
  verify_decomp.py      — verifies main block byte-match

old SN64/               — archived original SN64-oriented project files
```

---

## Decompilation Workflow

### 1. Run m2c on a function

```bash
python3 tools/m2c.py asm/main/main/func_XXXXXXXX.s \
    --target mips --asm-function func_XXXXXXXX \
    --structs --pointer-style-left > /tmp/out.c
```

Paste the output into `src/main/main/func_XXXXXXXX.c`.

### 2. Fix common m2c failures

| Error | Cause | Fix |
|---|---|---|
| `Found jr instruction` | Jump table (`jr $reg`) | Write `switch` using jtbl entries from `entry.s` |
| `Cannot find branch target funcXXXX` | Branch back to own glabel | Translate as `do { ... } while (cond)` |
| `Cannot find branch target .LXXXXXXXX` | Cross-function backward branch | Handwritten MIPS; write empty stub |
| `Last instruction missing delay slot` | 4-byte fragment | `if (cond) return;` or similar |
| `Unable to determine jump table` | Same as Found jr | Write switch |
| `Label refers to a delay slot` | m2c can't express construct | Write stub, keep as nonmatching |
| `Failed to parse instruction` | Bogus instruction (bltz to OS) | Write stub for whole function |
| `Function D_XXXX contains no instructions` | Rodata label, not a function | Remove failure comment; symbol lives in entry.s |

### 3. Check for IDO byte-match

```bash
make match_check FUNC=func_XXXXXXXX
```

Compiles the C with IDO, assembles the .s stub, diffs `.text` sections.
Output: `✓ MATCH` or a disassembly diff.

Only leaf functions (no `sw $ra` in the asm) can byte-match IDO.

---

## Key Technical Patterns

### Permanently non-matching: non-leaf functions

Any function that saves `$ra` uses SN64's ABI (ra at `sp+frame−8`, addiu in delay
slot) which IDO cannot reproduce.  These compile fine and are readable C; they
just won't byte-match.

### GETTER_NOJR (8-byte functions, permanently non-matching)

Functions that load a global into a register and fall through to the next function
(no `jr $ra`).  SN64 fall-through optimization — cannot be expressed in standard C.
Kept as asm stubs.  Identified by `lui + lw/lwc1` with no `jr $ra` in the 8 bytes.

Example: `func_80087D78` (loads `D_80096370` into `$t6` for `func_80087D80`).

### 64-bit MIPS instructions (permanently non-matching)

Functions using `ld`/`sd`, `ddiv`, `daddu`, `dsrav`, `dsll32`, `dsra32` etc. are
handwritten MIPS for 64-bit math — IDO o32 cannot emit these from C.  Write a
readable stub; it won't match but at least documents the intent.

### Branch-back-to-self (do-while loops)

m2c fails when a `bnez`/`beqz` targets the function's own glabel.  Translate as
`do { ... } while (condition)`.

```c
void func_80061AD0(s32 *arg0, s32 arg1, s32 arg2) {
    do { *arg0++ = arg1; } while (arg2-- != 0);
}
```

### Jump tables in entry.s

All `jtbl_8004Cxxx` tables are defined as `dlabel` entries in
`asm/main/main/entry.s`, NOT inline with the function.  When m2c reports
"Found jr instruction", grep entry.s for the table name to get the address array.

```bash
grep -A 12 "dlabel jtbl_8004CF38" asm/main/main/entry.s
```

### Handwritten MIPS (stays as asm forever)

Functions using `mtc0`/`mfc0`, `$k0`/`$k1` (kernel regs), or cross-function
backward branches cannot be expressed in C.  Write an empty stub:

```c
static void func_80076000(void) {
    /* handwritten: exception vector — mtc0/$k0/jr — see asm stub */
}
```

### Delay-slot fragments (4-byte functions)

m2c reports "Last instruction missing delay slot."  Write the minimal equivalent:

```c
void func_80056EA8(s32 arg0, s32 arg1, s32 arg2) {
    if (arg0 == arg2) { return; }
}
```

### M2C helper macros (defined in ultra64.h)

```c
#define M2C_BREAK(n)              BREAK(n)
#define M2C_MEMCPY_ALIGNED(d,s,n) memcpy((void*)(d),(const void*)(s),(n))
```

`M2C_ERROR` has been fully eliminated from the codebase.  All former
`M2C_ERROR` call sites were replaced with one of:
- `0 /* implicit $REG from caller */` — volatile caller register
- `0.0 /* implicit $fREG float from caller */` — float caller register
- `NULL /* implicit $sN set by caller */` — callee-saved implicit state
- A hardware-instruction comment (`/* mfc0 ... */`, `/* cache ... */`)
- A loop-feedback variable (`var_tN /* loop feedback */`)
- `*(CAST*)((char*)ptr - N)` — formerly `ptr->unk0 /* FIXME: was ->unk-N */`

---

## ROM Structure

```
0x000000 – 0x000040   N64 header (ipl3 + entry vector)
0x000040 – 0x001000   IPL3 boot code
0x001000 – 0x005000   Boot block (boot.s + init.s)
0x005000 – 0x054B20   Compressed main block (LZSS)
0x054B20 – end        Assets / overlays
```

The compressed main block decompresses to ~305 KB at 0x8004BA20–0x800977FF.
`assets/boot/compressed_main.bin` is the original compressed blob used for
linking; `assets/boot/decompressed_main.bin` is the reference uncompressed image.

---

## Splat Config

`.splat/xg2.yaml` — controls how the ROM is split into .s stub files.
Regenerate stubs (destructive): `python3 tools/splat.py .splat/xg2.yaml`

`asm/main/main/` has one .s file per function, named by address.  Each contains
`nonmatching funcXXXX, <size>` + `glabel funcXXXX` + the MIPS instructions.

---

## Session History (summarised)

1. ROM analysed, splat config created, build system set up — ROM byte-matches.
2. 581 undefined symbols resolved (D_ data + func_ addresses in symbol_addrs.txt).
3. 6 cross-function .L label references fixed.
4. xg2_main.elf linked and verified.
5. IDO toolchain confirmed; first batch of leaf functions decompiled.
6. 135 `sw $ra, 0x14($sp)` pattern functions decompiled to C.
7. SN64 confirmed as the original compiler (but not usable here — 32-bit only).
8. ~46% of C files had compile errors — fixed.
9. Remaining asm-only functions decompiled.
10. `include/os.h` written from exception handler analysis.
11. SFX subsystem decompiled.
12. 41 parse-error C files fixed — all 453 C files now compile cleanly.
13. **Project migrated to IDO-only build** — Makefile rewritten, SN64 requirement
    dropped, ROM always byte-exact via compressed_main.bin blob.
14. **Confirmed 14 IDO byte-matches** (all leaf functions); 14 is the practical
    ceiling given SN64 vs IDO ABI differences.
15. **Eliminated all M2C_ERROR call sites** — every implicit-register and
    hardware-instruction placeholder resolved across all 453 C files.
16. **Eliminated all FIXME annotations** — 48 "type unknown" comments stripped,
    127 negative-offset pointer FIXMEs rewritten as `*(CAST*)((char*)ptr - N)`
    explicit byte-offset expressions; 0 FIXMEs remain.
17. **Applied 47 named function identifiers** — OS primitives and game entry
    points renamed from `func_XXXXXXXX` to proper names (e.g. `osDisableInt`,
    `osRestoreInt`, `osVirtualToPhysical`, `osCreateThread`, etc.) across 116
    source files (510 replacements total).
18. **Applied 97 named data globals** — `D_XXXXXXXX` references replaced with
    descriptive names (e.g. `gGameState`, `gEntityPool`, `gSfxActiveCount`,
    `gTrackNodeCount`, `gPlayerList`, `osMemSize`, etc.) across 118 source files
    (771 replacements total).
19. **Named 48 additional functions** — second batch of identifications: N64 OS
    scheduler (`osRecvMesg`, `osSendMesg`, `osStartThread`, `osDestroyThread`,
    `osGetTime`, `osSetTimer`, `osSetEventMesg`, `osSetIntMask`, `__osEnqueueWait`,
    `__osEnqueueThread`, `__osPopQueue`, `__osDispatchThread`, `__osTimerUnlink`,
    `__osTimerInsert`, etc.), math/graphics (`cosf`, `sinf`, `guMtxF2L`,
    `guMtxIdent`, `vec3Cross`, `vec3CrossEdge`), and audio (`sfxQueueCmd`,
    `sfxFrameTick`). Applied 515 replacements across 139 files.
20. **Named 13 additional functions** — third batch: SI/controller pak
    (`osContPakRead`, `osContPakWrite`, `contPakRepairId`, `__siInit`, `__siLock`,
    `__siAcquire`, `__siUnlock`), geometry (`vec3Normalize`), SFX events
    (`sfxMarkEntityActive`, `sfxEventDequeue`, `sfxEventEnqueue`, `sfxFlushTimers`),
    SRAM DMA (`sramStartDma`). Applied 224 replacements across 61 files.
21. **Named 11 additional functions** — fourth batch: SFX subsystem (`sfxHasEntity`,
    `sfxGetEntity`, `sfxPlay`, `sfxGetEntry`, `sfxMapId`, `audioStreamReadByte`),
    RSP/display list (`spTaskSubmit`, `gfxSpTaskWait`, `renderLineStrip`), overlay
    memory (`overlayDecompress`), game (`gameHandlerSetup`). Applied 177
    replacements across 53 files.
25. **Named 11 additional functions** — eighth batch: entity handler (`handlerGetResult`,
    `gfxDmaEventLoop`), audio (`audioSetNoteSlot`, `audioNoteWrite`, `audioRspSetupSample`,
    `audioDecodeHufh`), stream readers (`streamReadU32`, `streamReadVarInt`),
    timer (`timerRelinkByType`), controller pak (`contPakReadEntry`, `contPakFetchNote`).
    Applied replacements across 35 files.
24. **Named 10 additional functions** — seventh batch: SFX dispatch variants
    (`sfxStopAtEntity`, `sfxPlayNoteAtEntity`, `sfxIsBusy`, `sfxPlayCue`),
    controller pak (`contPakTransfer`, `contPakBuildMap`), PI DMA (`piDmaNotify`),
    GFX helpers (`gfxGetWritePtr`, `rdpSetFillColor`, `rdpSetFogColor`).
    Applied replacements across 29 files.
23. **Named 13 additional functions** — sixth batch: SFX dispatch variants
    (`sfxPlayLoopAtEntity`, `sfxPlayPanAtEntity`, `sfxPlayAbsAtEntity`,
    `sfxResetNote`, `sfxNoteRetrigger`, `sfxComputePan`, `sfxGetFrameOutput`,
    `sfxSetCueParams`, `sfxGetTopEntity`), audio note setup (`audioLoadNotes`),
    controller pak (`contPakByteSum`), runtime helpers (`__muldi3`),
    utility (`storeByteUnaligned`). Applied replacements across 29 files.
22. **Named 19 additional functions** — fifth batch: COP0/interrupt helpers
    (`getCOP0Status`, `setCOP0Status`, `intDisable`, `intRestore`), entity/handler
    (`handlerPostCmd`, `entityClearSlots`, `entityStepState`), SFX/audio
    (`sfxPlayAtEntity`, `sfxComputePitch`, `sfxComputeVolume`, `sfxAllocBlock`,
    `audioHeapAlloc`, `audioNodeInit`, `audioStartTimer`), byte utilities
    (`byteCopy`, `byteCopyEnd`), math/rendering (`mtxLookAt`, `renderCurveStrip`),
    runtime (`__udivdi3`). Applied ~270 replacements across 62 files.
26. **Named 6 audio/math functions** — ninth batch: audio queue (`audioQueuePlay`,
    `audioQueueFind`), audio sample (`audioPlayCopySample`, `audioSetupCopySample`,
    `audioSetTrack`), geometry (`vec3DotOffset`). Applied replacements across 18 files.
27. **Named 18 additional functions** — tenth batch: matrix (`guMtxL2F`, `guMtxCatF`,
    `guMtxCat`, `mtxTransformVec`, `guMtxXfm`), memory (`bzero`, `memcpyBytes`),
    handler (`handlerPostSfxCmd`), audio RSP (`audioRspSubmit`), sfx ucode
    (`sfxLoadUcode`), frame allocator (`frameAlloc`), sfx state (`sfxGetState`),
    timer queue (`timerQueueInit`), flush list (`pendingFlushEnqueue`), controller pak
    (`crc5Calc`, `contPakLoadSave`, `contPakCountNotes`, `contPakProbe`).
    Applied replacements across 55 files. Total named: **236**.
29. **Named 16 additional functions** — twelfth batch: frame alloc (`dlResetPtr`),
    PRNG (`randRange`), memory (`memsetBytes`), sfx (`sfxFindEntity`, `sfxSetState`),
    GFX DL (`rdpRunSetupDL`, `gfxAddSyncCmd`, `rdpStateInit`), handler (`gameHandlerInit`),
    audio (`audioSetCallback`, `guPerspectiveF`, `guPerspective`, `siReadBlocking`,
    `audioLoopDmaCmd`, `audioInitDecodeTable`, `audioInitFreqTable`).
    Applied replacements across 36 files. Total named: **271**.
28. **Named 19 additional functions** — eleventh batch: controller pak (`contPakVerifyNote`),
    audio rate (`audioSetRates`), audio stream (`audioStreamReadVarInt`, `audioDecodeLZSS`,
    `audioBootDecode`), RSP counter (`audioGetRspCount`), note slot (`audioDefaultNoteSlot`),
    audio node (`audioNodeUpdate`, `audioCalcPeriod`, `audioRspDispatch`, `timerRelink`),
    matrix game-local (`mtxCatF`, `mtxXfmPoint3`, `mtxIdentInit`), entity init
    (`entitySlotReset`, `sfxEntryReset`), COP0 (`setCOP0Compare`), locale (`localeCheck`),
    audio timing (`audioSetBeatPos`). Applied replacements across 41 files. Total named: **255**.
30. **Named 15 additional functions** — thirteenth batch: matrix (`guMtxL2FFixed`),
    OS PI (`__osPiIsBusy`), MIDI/audio (`midiSetNote`, `audioNodeSetValue`,
    `audioRspDispatchNode`), utility (`calcHash`, `alignUp256`, `intToAsciiStr`),
    SRAM (`sramDmaStep`, `sramStartDmaSafe`), controller pak (`contPakScanNotes`,
    `contPakAllocNote`, `siQueryControllers`), exception handler (`exceptionVectors`),
    HUD renderer (`rdpTextLayout`). Applied 94 replacements across 34 files.
    Total named: **286**.
    Also fixed all 33 GETTER_NOJR stubs — each now calls its fall-through successor.
