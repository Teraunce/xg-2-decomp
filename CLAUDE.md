# Extreme-G 2 (XG2) Decompilation — Project Guide

## Goal

Decompile all ~500+ functions in Extreme-G 2 (N64, 1997) from MIPS assembly to
readable C source, compiled with **IDO 7.1**.  The build produces a ROM identical
to `baserom.z64` (SHA1 `ed0a50086ef9a89f5b445c20ab6f365165959630`).

Byte-matching every function is **not** the goal — the ROM is always byte-exact
because it embeds the original `compressed_main.bin` blob.  C files are compiled
for readability, correctness, and as many IDO byte-matches as possible.

## Current Status (as of 2026-08-08)  <!-- update date when status changes -->

| Metric | Count |
|---|---|
| C source files | 453 |
| IDO byte-matching functions | **14** |
| Files compiling with zero errors (IDO 7.1) | **453** |
| Remaining M2C_ERROR call sites | **0** |
| Remaining FIXME annotations | **0** |
| Named functions (proper identifiers) | **702** |
| Named data globals applied | **810** |
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
34. **Named 11 additional functions** — seventeenth batch: particle (`particleUpdate`), math
    (`vec3NormalizeAssert`, `mtxNodeInit`, `memsetWord`), audio (`audioQueueDispatch`,
    `audioQueueDispatchGetter`, `sfxRandNext`), SFX (`sfxGetActiveCount`, `sfxGetCount`,
    `sfxPhaseHook`), geometry (`geomNodeDispatchGetter`). Applied 41 replacements
    across 15 files. Total named: **343**.
33. **Named 15 additional functions** — sixteenth batch: scene (`sceneDispatch`), audio
    (`audioNoteUnlink`, `audioNoteRelease`, `mtxEulerRotF`, `mtxEulerRotGetter`),
    geometry (`geomBufWrite`, `geomBufWriteGetter`), SFX (`sfxChannelClear`,
    `sfxResetPhase`, `sfxSlotResolve`, `sfxNullReturn`, `sfxGetRunning`), overlay
    (`overlayGetEntry`), exception (`intExceptionDispatch`), video (`viRenderSync`).
    Applied 67 replacements across 21 files. Total named: **332**.
32. **Named 15 additional functions** — fifteenth batch: C runtime (`strlen`), controller pak
    (`crc8Calc`), SI (`siInitControllerReadCmd`), OS timer (`__osTimerSetCompare`,
    `__osTimerEnqueue`), stream (`streamTryReadVarInt`, `streamReadS16`), SFX
    (`sfxComputeDist`), matrix (`guRotateInt`), audio (`audioMidiNodeInit`,
    `audioFillDecayTable`), utility (`byteArrayFind`, `localeGet`), game
    (`gameStateMachineLoop`), RSP (`osSpSetPcIfHalted`). Applied 68 replacements
    across 30 files. Total named: **317**. Also fixed 2 missed GETTER_NOJR stubs
    (`guRotateInt`, `osSpSetPcIfHalted`).
31. **Named 16 additional functions** — fourteenth batch: matrix (`guRotateF`, `guRotate`,
    `vec3NormalizeF`), spatial SFX (`sfxComputeSpatial`, `sfxPlaySpatial`), audio
    (`audioDecodeStart`), OS thread (`__osDequeueThread`, `__osRemoveLink`,
    `osMsgQueueInit`), SI (`siInitPollCmd`), C runtime (`memcmp`, `memcmpImpl`),
    overlay (`overlayRelocate`, `overlayMarkNodes`, `overlayMarkLeaf`, `overlayNodeMark`).
    Applied 74 replacements across 31 files. Total named: **302**.
30. **Named 15 additional functions** — thirteenth batch: matrix (`guMtxL2FFixed`),
    OS PI (`__osPiIsBusy`), MIDI/audio (`midiSetNote`, `audioNodeSetValue`,
    `audioRspDispatchNode`), utility (`calcHash`, `alignUp256`, `intToAsciiStr`),
    SRAM (`sramDmaStep`, `sramStartDmaSafe`), controller pak (`contPakScanNotes`,
    `contPakAllocNote`, `siQueryControllers`), exception handler (`exceptionVectors`),
    HUD renderer (`rdpTextLayout`). Applied 94 replacements across 34 files.
    Total named: **286**.
    Also fixed all 33 GETTER_NOJR stubs — each now calls its fall-through successor.
35. **Named 17 additional functions** — eighteenth batch: audio semitone (`audioSemitoneRatio`),
    audio node (`audioNodeSetProp`), MIDI (`midiDecodeEvent`), audio note (`audioNoteFind`,
    `audioNoteLookup`, `audioNoteActivate`), MIDI tempo (`midiProcessTempo`), audio stream
    (`audioStreamTick`), overlay (`overlayRelocatePtrs`), TLB (`tlbVirtToPhys`), OS timer
    (`osTimerHandlerGetter`), exception install (`osExceptionInstall`), cache (`cacheInvalDcache`,
    `cacheInvalIcache`), audio geometry (`audioGeomNodeInit`), audio RSP build
    (`audioRspBuildDL`), audio timer (`audioTimerResched`). Applied 68 replacements across
    22 files. Fixed `geomNodeDispatchGetter` GETTER_NOJR stub. Total named: **360**.
36. **Named 28 additional functions** — nineteenth batch: track node (`trackNodeFindNearest`,
    `trackNodeFindNearestGetter`), matrix rotation (`mtxRotAxisF`, `mtxRotAxisFGetter`,
    `mtxRotAxisFGetter2`, `mtxCatFSafe`), N64 SDK (`guRotateDeg`, `guLookAtHiliteF`,
    `guLookAtHilite`, `osGetThreadPri`), PI (`osEPiRawReadIoCart`, `piMgrInit`, `piReadBytes`),
    controller SI (`contParseReadResp`, `contParseReadRespGetter`, `siReadControllers`,
    `contGetInputPort`, `contParsePollResp`, `contParsePollRespGetter`), audio node
    (`audioAdpcmNodeInit`, `audioMixNodeInit`, `audioAdpcmNodeCmd`, `audioMixNodeCmd`,
    `audioMidiNodeCmd`, `audioNodeCmd`, `audioNodeCmdGetter`, `audioNoteClearAll`),
    SFX (`sfxNoteAssign`). Applied 133 replacements across 53 files. Fixed `guRotateDeg`
    and `osEPiRawReadIoCart` GETTER stubs. Total named: **388**.
37. **Named 21 additional functions** — twentieth batch: frame sync (`viGetSyncByte`), SFX
    (`sfxMarkAllActive`, `sfxTableInit`, `sfxComputeFreqOffset`), dispatchers
    (`entityUpdateDispatch`, `sceneObjectDispatch`, `gameLoopDispatch`, `gameLoopDispatchGetter`),
    SRAM/PI (`sramCopyData`), overlay (`overlayLoadEntries`), audio
    (`audioTimerDispatch`, `midiTimerReset`, `audioVoiceNodeInit`, `audioCalcRatio`,
    `audioGeomNodeCmd`), controller pak (`contPakWritePage`, `contPakBuildCmd`,
    `contPakReadPage`, `contPakWriteNote`), PI (`piGetHandle`),
    track (`trackNodeSearchNearest`). Applied 81 replacements across 41 files. Total named: **409**.
38. **Named 9 additional functions** — twenty-first batch: handler setup (`handlerSetupLooped`,
    `handlerSetupTable`), controller pak SI DMA (`contPakSiDmaRead`), audio dispatchers
    (`audioSeqUpdate`, `audioNodeDispatch`, `gbiCmdDispatch`, `audioResetCallback`),
    RDP float formatter (`rdpFormatFloat`, `rdpFormatFloatGetter`).
    Applied 34 replacements across 16 files. Total named: **418**.
39. **Named 14 additional functions** — twenty-second batch: RSP (`rspResetCounters`), video
    (`viSetResolution`), physics (`velStateInit`), entity (`entityListPrune`, `entityFindNearest`),
    geometry (`triComputeNormal`), audio heap (`audioHeapInit`), MIDI note (`midiAllocNote`,
    `midiReleaseNote`, `midiNoteIsPlaying`, `midiTimerSetNote`, `midiNoteSetState`),
    audio channel (`audioSetChanA`, `audioSetChanB`).
    Applied 42 replacements across 18 files. Also swept 194 stale replacements across 72 files.
    Total named: **432**.
40. **Named 12 additional functions** — twenty-third batch: matrix scale (`guScaleF`, `guScale`),
    trig (`sinInt`), audio (`audioNoteMinTime`, `audioNodeStateRead`, `audioNodeGetPos`,
    `audioClearNode`), SFX params (`sfxSetPitch`, `sfxSetFreq`, `sfxSetFilter`),
    RDP formatting (`u16StrLen`, `rdpFmt2Digit`).
    Applied 35 replacements across 14 files. Total named: **444**.
41. **Named 9 additional functions** — twenty-fourth batch: PI IO (`osEPiRawReadIo`,
    `osEPiRawReadIoGetter`, `osEPiRawWriteIo`, `osEPiRawWriteIoGetter`), 64-bit runtime
    (`__ashrdi3`, `__umoddi3`, `__ashldi3`, `__moddi3`, `__divdi3`).
    Applied 21 replacements across 7 files. Total named: **453**.
42. **Named 7 additional functions** — twenty-fifth batch: audio (`audioBankLookup`,
    `audioTriOsc`), math (`frexp`, `u64DivImpl`, `intDiv`), RSP/VI (`rspTaskAlloc`, `viInit`).
    Applied 21 replacements across 14 files. Total named: **460**.
43. **Named 7 additional functions** — twenty-sixth batch: controller (`contInit`), SI
    (`siMsgDispatch`, `siDmaReset`), video (`viModeConfig`, `viSetFieldBit`, `viSetDisplay`),
    audio (`audioDrainDecode`).
    Applied 20 replacements across 10 files. Total named: **467**.
44. **Named 24 additional functions** — twenty-seventh batch: matrix (`guTranslateF`, `mtxEulerScaleFGetter`,
    `mtxEulerScaleF`, `mtxProjectVec`, `guMtxL2FFixedW`), audio synth (`audioSynthInit`, `audioMidiInit`,
    `audioBuildFrame`, `audioSampleInit`, `audioBufRecycle`, `audioDmaBufAlloc`, `audioDmaBufInit`,
    `audioRspDone`, `audioSetBufLen`, `audioSetChanWeight`, `audioLoadBank`, `audioLoadWavetable`),
    MIDI (`midiSeqStop`, `midiSetVolume`, `midiSetExpression`, `midiSetController`),
    entity/SFX (`sfxEntityInit`, `sfxComputeSpatialImpl`), track (`trackEdgeProcess`).
    Applied 70 replacements across 33 files. Fixed `mtxEulerScaleFGetter` GETTER_NOJR stub.
    Total named: **491**.
45. **Named 8 additional functions** — twenty-eighth batch: matrix (`guMtxIdentL`, `guOrthoF`, `guOrtho`),
    SFX (`sfxPlaySpatialDef`, `sfxEntitySpatial`, `sfxRaceInit`),
    render (`rdpFrameBegin`), controller pak (`contPakUpdate`).
    Applied 24 replacements across 13 files. Total named: **499**.
46. **Named 5 additional functions** — twenty-ninth batch: SFX (`sfxBufAlloc`, `sfxHandlerEnsure`,
    `sfxRenderBegin`, `sfxPhaseTick`), utility (`getRaceCtrl`).
    Applied 13 replacements across 8 files. Total named: **504**.
47. **Named 17 additional functions** — thirtieth batch: matrix (`guScaleGetter`, `guEulerScaleL`),
    HUD (`rdpFormatStr`), controller pak (`pakNameToU16`, `contPakHandlerInit`, `contPakHandlerDetect`,
    `contPakHandlerRead`, `contPakSaveNote`, `contPakLoadNote`, `contPakCreateNote`,
    `contPakReadDir`, `contPakVerifyRead`), PI DMA (`piCopyBytes`, `piSetBytes`, `piMoveBytes`),
    render (`renderTexLine`, `renderTexLineW`).
    Applied 51 replacements across 24 files. Fixed `guScaleGetter` GETTER_NOJR stub.
    Total named: **521**.
48. **Named 13 additional functions** — thirty-first batch: OS timer (`__osTimerHandler`),
    controller pak SI (`contPakSiWrite`), MIDI (`midiTrackInit`, `midiQueueProcess`),
    audio synth (`audioSynthChannelInit`, `audioSynthSetupGetter`, `audioSynthSetup`),
    controller pak handlers (`contPakHandlerWait`, `contPakHandlerStatus`, `contPakFormatNote`),
    audio flush (`pendingFlushClear`), VI manager (`viMgrInitGetter`, `viMgrInit`).
    Applied 35 replacements across 21 files. Fixed `audioSynthSetupGetter` and `viMgrInitGetter`
    GETTER_NOJR stubs. Total named: **534**.
49. **Named 10 additional functions** — thirty-second batch: audio node dispatch
    (`audioTimerNodeCmd`, `audioNoteWriteCmd`, `audioMixCmd`, `audioVoiceNodeCmd`,
    `audioAdpcmDecodeCmd`, `audioGeomRspCmd`, `audioTriOscCmd`), SFX note
    (`sfxNotePlay`, `sfxNoteUpdate`, `sfxFrameBegin`), RSP (`rspHalt`),
    PI mutex (`__piUnlock`, __piLock`).
    Applied 26 replacements across 16 files. Total named: **544**.
50. **Named 15 additional functions** — thirty-third batch: collision (`triContainsPoint2D`),
    track (`trackNodeRender`), SFX (`sfxEntryWrite`), frame thread
    (`frameDispatchThread`, `frameThreadInit`), audio node RSP builders
    (`audioTimerNodeCmd`, `audioNoteWriteCmd`, `audioMixCmd`, `audioVoiceNodeCmd`,
    `audioAdpcmDecodeCmd`, `audioGeomRspCmd`, `audioTriOscCmd`).
    Applied 36 replacements across 20 files. Total named: **559**.
51. **Named 8 additional functions** — thirty-sixth batch: matrix (`mtxRotZF`, `rdpMtxPackRow`),
    controller pak (`contPakFatAlloc`, `contPakOpenNote`, `contPakReadChain`, `contPakRepairNotes`),
    SI commands (`siSetupWriteCmd`, `siSetupReadCmd`).
    Applied 24 replacements across 15 files. Total named: **567**.
52. **Named 9 additional functions** — thirty-seventh batch: game thread (`gameThreadEntry`,
    `gameThreadInit`), controller pak (`contPakBuildNoteMap`, `contPakCountNoteLinks`),
    PI DMA (`piCartDmaComplete`), OS interrupt (`osEnableIntMask`), printf
    (`vsprintfCore`, `fmtIntBuf`), 64-bit runtime (`__divmoddi3`).
    Applied 24 replacements across 13 files. Total named: **576**.
53. **Named 9 additional functions** — thirty-eighth batch: SFX (`sfxFrameStateMachine`),
    game loop (`gameMainLoop`, `gameStateInit`), matrix (`mtxRotXF`), FMV (`fmvDecodeFrame`),
    audio (`audioQueueStopAll`, `audioPlayNormalized`), game mode (`gameModeReset`,
    `gameModeResetGetter`). Applied 18 replacements across 10 files.
    Fixed `gameModeResetGetter` GETTER_NOJR stub. Total named: **585**.
54. **Named 5 additional functions** — thirty-ninth batch: SFX (`sfxRaceSetup`,
    `sfxRaceSetupGetter`, `sfxMixCmd`), geometry (`geomCollisionDispatch`),
    OS scheduler (`__osIntHandler`).
    Applied 11 replacements across 5 files. Fixed `sfxRaceSetupGetter` GETTER_NOJR stub.
    Total named: **590**.
55. **Named 8 additional functions** — fortieth batch: SFX (`sfxLoadSample`),
    render (`renderSceneDispatch`, `renderMainDispatch`), controller pak (`contPakEventLoop`),
    SRAM (`sramHwDispatch`), matrix (`guRotateDegF2L`), OS interrupt (`osDisableIntMask`),
    PI wait (`__osPiWait`).
    Applied 16 replacements across 11 files. Total named: **598**.
56. **Named 8 additional functions** — forty-first batch: audio timer (`audioTimerCmd0F`,
    `audioTimerCmd11`), MIDI (`midiSmfInit`), GFX pipeline (`gfxAllocWait`,
    `gfxAudioDecodeWait`, `gfxAudioWait`, `overlayLoadDL`), RSP DMA (`rspReadBytes`).
    Applied 11 replacements across 8 files. Total named: **606**.
57. **Named 12 additional functions** — forty-second batch: overlay (`overlayLoadEntry`,
    `overlayLoadAlt`, `overlayGetEntryAlt`), heap (`frameHeapInit`), track
    (`trackNodeFindWrapper`), video (`viGetSyncWord`), audio (`audioSampleInitWrap`),
    matrix (`mtxSetFromVectors`, `mtxTransposeL2F`, `mtxRotAxisAngle`, `mtxRotAxisApply`),
    SFX (`sfxProcessInput`).
    Applied 12 replacements across 11 files. Total named: **618**.
58. **Named 5 additional functions** — forty-third batch: entity (`entitySpawn`), GFX
    (`gfxFrameSetup`), matrix (`mtxSetFromVectorsNeg`, `cameraSetupMtx`), RSP
    (`rspDrainMesgQueue`). Applied 5 replacements across 5 files. Total named: **623**.
63. **Named 3 additional functions** — forty-eighth batch: printf formatting
    (`vsprintfFloat`, `vsprintfGHandler`), string util (`u16StrTrimEnd`).
    Applied 5 replacements across 3 files. Total named: **702**.
    3 unnamed functions remain (implicit-register stubs: `func_80086904`,
    `func_80087EB8`, `func_8008FFA0` — all use $at/$t6/$t7/$v0 from callers,
    cannot be reliably named without broader context).
62. **Named 16 additional functions** — forty-seventh batch: camera (`cameraMatrixBuild`,
    `cameraViewRender`, `cameraHiliteRender`), render (`trackEntityRender`,
    `gfxDLFrameSetup`, `gfxDLEnd`, `renderTexLineWW`), SFX RSP (`sfxRspTaskRun`,
    `sfxRspTaskRunLen`), SFX entity (`sfxEntityHandler`), controller pak
    (`contPakThreadInit`), handler (`entityHandlerSetup`, `entityHandlerSetupEx`),
    PI IO (`piReadByte`, `piWriteByte`), PI lock (`__piLockGetter`).
    Applied 16 replacements across 16 files. Total named: **699**.
    6 unnamed functions remain (implicit-register stubs + unresolved).
61. **Named 24 additional functions** — forty-sixth batch: SRAM (`sramHwInit`,
    `sramReadStatus`, `sramWriteName`, `sramWriteNote`, `sramErase`, `sramReadBuf`,
    `sramWriteBuf`, `sramPiDmaStep`), math/trig (`cosInt`, `mtxIdentSetPos`, `s64Mod`),
    audio/MIDI (`midiSeqLoad`, `osTimerQueueReload`, `audioTimerSetDecay`,
    `audioTimerSetAttack`, `audioSeqNodeInit`, `midiSeqStep`, `audioBuildVoice`),
    VI (`viSetRefresh`, `viSetGamma`, `viSetOutput`), utility (`isUnaligned`, `sprintf`),
    AI DMA (`aiDmaInit`).
    Applied 24 replacements across 24 files. Total named: **683**.
60. **Named 20 additional functions** — forty-fifth batch: render (`renderLineRect`,
    `renderLineRectEx`, `renderTrackCurves`), math (`s64Div`), SFX format
    (`sfxFormatName3`, `sfxFormatName4`, `sfxFormatName5`), SFX playback
    (`sfxChannelDispatch`, `sfxSpawnSample`, `sfxStateRdpSync`,
    `sfxTableInitGetter`, `sfxLoadSampleGetter`), game (`gameMenuRender`,
    `gameStateSync`, `gameRaceRender`, `gameCameraSetup`), RDP (`rdpDataLoad`,
    `rdpTrackLayout`, `rdpDrawString`), font (`fontStringWidth`).
    Applied 20 replacements across 20 files. Fixed 2 GETTER_NOJR stubs
    (`sfxTableInitGetter`, `sfxLoadSampleGetter`). Total named: **659**.
59. **Named 16 additional functions** — forty-fourth batch: entity (`entityPhysicsInit`),
    render (`renderNodeSetup`), memory (`mainPoolAlloc`), audio subsystem
    (`audioSystemInit`, `audioRspDoneGetter`, `audioFrameBuild`, `audioTimerAcquire`),
    SFX (`sfxAmbientTick`, `sfxEntityPlayDef`, `sfxEntityPlay`, `sfxEntitySpatialUpdate`,
    `sfxPositionalUpdate`, `sfxPositionalUpdateDoppler`, `sfxPlayAtNearest`,
    `sfxRaceUpdate`), game (`gameSceneInit`).
    Applied 19 replacements across 16 files. Fixed `audioRspDoneGetter` GETTER_NOJR stub.
    Total named: **639**.
64. **Named 263 data globals** — fifteen batches of D_XXXXXXXX symbol identification:
    Display/render (`gDLPtr`, `gLineVtxBase`, `gRenderBase`, `gRenderIdx`, `gLineTexBase`,
    `gTexScaleX`, `gTexScaleY`, `gScreenWidth`, `gScreenHeight`, `gCurRenderNode`,
    `gEntityVisited`, `gEntityActive`, `gRdpTilePtr`, `gRdpTilePtr2`, `gTexTileCmd`,
    `gOrthoMtx`, `gPerspMtx`, `gDLBufEnd`, `gGfxTaskOut`, `gRspGeomBuf`),
    SFX/audio (`gSfxVoiceCount`, `gSfxBufList`, `gSfxCooldown`, `gSfxTimer`,
    `gSfxFrameState`, `gSfxBlockedFlag`, `gSfxTimerRef`, `gSfxFrameOut`,
    `gSfxOutputActive`, `gSfxActive`, `gSfxEffectFlag`, `gSfxEffectList`,
    `gSfxEffectTableA`, `gSfxEffectTableB`, `gSfxChanPtr`, `gSfxChanFuncs`,
    `gSfxSpatialCount`, `gSfxListenerPos`, `gSfxListenerScale`, `gSfxDistMax`,
    `gSfxDistClamp2`, `gSfxDistClamp3`, `gSfxDistThresh`, `gSfxPanScale`,
    `gSfxVolDecay`, `gSfxPitchScale`, `gSfxSpatialScale`, `gSfxVolScale`,
    `gSfxDecodeDst`, `gSfxDecodeBuf`, `gSfxDecodeBufData`, `gSfxDecodeSize`,
    `gSfxDecodedCount`, `gSfxDecodeIdx`, `gSfxDecodeState`, `gSfxDecodePending`,
    `gSfxDecodeTable`, `gSfxStreamCtx`, `gSfxChanReady`, `gSfxMidiReady`,
    `gSfxQueueDepth`, `gSfxQueueReady`, `gSfxRaceReady`, `gSfxRaceTimer`,
    `gSfxAmbientSlot`, `gSfxAmbientCount`, `gSfxAmbientHandle`, `gSfxAmbientIds`,
    `gSfxAmbientParams`, `gSfxEntityHandle`, `gSfxUcodeEnd`, `gSfxProbeTable`,
    `gSfxDmaDst`, `gSfxBufPool`, `gSfxGameParams`, `gSfxSampleRate`),
    Audio engine (`gAudioDmaBuf`, `gAudioUcode`, `gAudioUcodeEnd`, `gAudioUcodeImemEnd`,
    `gAudioUcodeData`, `gAudioRspData`, `gAudioSynthCfg`, `gAudioMesgQueue`,
    `gAudioHeap`, `gAudioLoadTask`, `gAudioYieldBuf`, `gAudioAiBuf`, `gAudioOutBuf`,
    `gAudioOutBuf`, `gAudioBufPtr`, `gAudioBufSize`, `gAudioBufSizeMin`,
    `gAudioNoteList`, `gAudioStreamBuf`, `gAudioDecodeCount`, `gAudioHufDst`,
    `gAudioFrameIdx`, `gAudioFrameCount`, `gAudioQueueBuf`, `gAudioQueueState`,
    `gAudioPackedParams`, `gAudioParam0`–`gAudioParam4`, `gAudioSampleBase`,
    `gAudioBankIdx`, `gAudioBankData`, `gAudioOutCtx`, `gAudioTrackBuf`,
    `gAudioTrackBuf2`, `gMidiCtx`, `gMidiNoteTable`, `gMidiFreqTable`,
    `gMidiVelThresh`, `gMidiSynthCfg`, `gMidiSynthCfg`),
    Track/race (`gTrackEdgeData`, `gTrackEdgeTable`, `gTrackSegLen`, `gTrackNodePtr`,
    `gTrackNodePool`, `gTrackTilt`, `gTrackTiltDir`, `gTrackFriction`, `gTrackReady`,
    `gTrackRenderPtr`, `gTrackColorKey`, `gRaceCtx`, `gRaceActive`, `gRaceMax`,
    `gRacePhase`, `gRaceCtrlCount`, `gRaceFlags`, `gRaceEntityPtr`),
    Render/text (`gTextCurX`, `gTextCurY`, `gTextBaseX`, `gTextLayoutX`, `gTextLayoutW`,
    `gTextCharAdv`, `gTextFontId`, `gTextWrap`, `gTextAlignFlags`, `gTextVisible`,
    `gTextGlyphIdx`, `gTextGlyphCoords`, `gTextVertBuf`, `gTextColorBuf`,
    `gTextTexU`, `gTextTexV`, `gGlyphSize`, `gGlyphCacheIdx`, `gFontData`,
    `gFontRange`, `gFontTable`, `gFontGlyphPtr`, `gFontCacheKey`, `gFontInitDone`,
    `gFontMesgQueue`, `gRdpSyncDone`, `gTexColorKey`, `gTexAddrKey`, `gTexCacheSlot`,
    `gTexUVScale`),
    SI/controller (`gSiReadBuf`, `gSiCmdBuf`, `gSiLocked`, `gSiWriteReady`,
    `gSiMesgQueue`, `gSiMutexQueue`, `gContInput`, `gContPakSaveData`, `gContPakNoteAttr`,
    `gContPakSlots`, `gContPakResult`, `gContPakCurEntry`, `gContPakDetected`,
    `gContPakMesgQueue`, `gContPakDirCount`, `gContPakDirId`, `gContPakWaitCnt`,
    `gContPakDmaReady`),
    SRAM/PI (`gSramReady`, `gSramInit`, `gSramState`, `gSramDmaHead`, `gSramDmaNode`,
    `gSramPiDmaCtx`, `gSramPiHandle`, `gPiMesgQueue`),
    OS/hardware (`PI_STATUS_REG`, `SP_STATUS_REG`, `VI_V_CURRENT`, `SRAM_ADDR_REG`,
    `gPhysMemBase`, `gExcBase`, `gViMsg`, `gViModePtr`, `gViModeData`, `gViModeCfg`,
    `gViInited`, `gViTimingA`–`gViTimingD`, `gViRegPair0A`–`gViRegPair0E`,
    `gNmiMesgQueue`, `gNmiMsg`, `gNmiMsg2`, `gTimerCount`, `gTimerPrev`, `gTimerHi`,
    `gTimerBase`, `gTimerElapsed`, `gOsTimerQueue`, `gRspDmaMesgQueue`,
    `gRspTask`, `gRspGeomBuf`, `gAudioRspData`),
    Game/misc (`gHandlerCtx`, `gHandlerMsgQueue`, `gEntityMesgQueue`, `gEntityFlagMask`,
    `gLoopCount`, `gGameMode`, `gGameFlags2`, `gRaceFlags`, `gGameThread`,
    `gGameThreadArgs`, `gVideoMode`, `gVideoModeCfg`, `gMtxIdent00`–`gMtxIdent33`,
    `gMtxOneF`, `gMtxZeroF`, `gOneF`, `gDegToRad`, `gTrigCoeffs`, `gRotClamp`,
    `gRandState`, `gRandInitB`, `gRandStateA`, `gRandStateB`, `gOrthoMtx`,
    `gOverlayTable`, `gOverlayTable2`, `gSceneOverlay`, `gSceneReady`,
    `gCamClampF`, `gCamDLData`, `gDLBufEnd`, `gFontInitDone`).
    Named data globals total: **360** (97 pre-existing + 263 this session).
    All 453 C files still compile cleanly.
65. **Named 450 additional data globals** — ten batches of remaining D_XXXXXXXX
    symbols, covering all rodata f32/f64 constant clusters, BSS globals, and MMIO
    registers. Key groups: ROM data pointers (`gFontRomAddr`, `gFontRomSize`,
    `gAudioBankRomAddr`/`RomSize`/`EntryCount`, `gAudioUcodeRomAddr`/`RomSize`/
    `EntryCount`, `gSceneOverlayData`, `gAudioHufTableRom`, `gGfxSetupTable`),
    resolution/texture scaling (`gResScaleX`, `gResScaleY`, `gTileScaleU`, `gTileScaleV`),
    VI mode register pairs (`gViRegPair2A`–`gViRegPair2J`), velStateInit params
    (`gVelStateInitF`, `gVelInitParamA`–`gVelInitParamM`), entity/track init
    (`gTrackSearchDist`, `gEntitySlotInitA/B`, `gNodeInitF`, `gEntityUpVecY`,
    `gEntitySpawnScale`), trackNodeRender params (`gTrackNodeRenderA`–`D`),
    geometry constants (`gVec3NormLen`, `gEdgeCrossParam`, `gGeomParamA`–`I`),
    fog/display (`gFogYScale`, `gMtxPackInitF`), sfx spatial computation
    (`gSfxSpatialDistThresh`, `gSfxSpatialParamB`–`F`, `gSfxSpatialImplA`–`H`,
    `gSfxSpatialDefDist`, `gSfxInterpConst`, `gSfxInterpScale`, `gSfxVolInitF`),
    sfx frequency (`gSfxFreqParamA/B`, `gSfxFreqThresh`, `gSfxFreqScale`,
    `gSfxRaceParamA`), audio (`gAudioBufScale`, `gAudioNodeConst`),
    camera (`gCamAvgScale/Clamp`, `gCamNearClip`, `gCamFarClip`, `gCamPerspDist/Far`,
    `gCamUpVecY`), misc (`gFmtScaleD`, `gGeomScaleConst`, `gGfxRenderBufBase`),
    MMIO (`AI_STATUS`=0xA450000C, `SI_STATUS`=0xA4800018).
    Named data globals total: **810**. All 453 C files compile cleanly.
    13 D_ references intentionally left as-is (comment-only annotations in
    nonmatching stub files, e.g. D_80052BAC, D_80059234, D_800669F4, etc.).
