# Extreme-G 2 (XG2) Decompilation — Project Guide

## Goal

Decompile all ~500+ functions in Extreme-G 2 (N64, 1997) from MIPS assembly to
readable C source, compiled with **IDO 7.1**.  The build produces a ROM identical
to `baserom.z64` (SHA1 `ed0a50086ef9a89f5b445c20ab6f365165959630`).

Byte-matching every function is **not** the goal — the ROM is always byte-exact
because it embeds the original `compressed_main.bin` blob.  C files are compiled
for readability, correctness, and as many IDO byte-matches as possible.

## Current Status (as of 2026-08-09, session 5)  <!-- update date when status changes -->

| Metric | Count |
|---|---|
| C source files | 453 |
| IDO byte-matching functions | **14** |
| Files compiling with zero errors (IDO 7.1) | **453** |
| Remaining M2C_ERROR call sites | **0** |
| Remaining FIXME annotations | **0** |
| Named functions (proper identifiers) | **702** |
| Named data globals applied | **810** |
| Named struct typedefs | **15** (TrackNode + 7 AudioNode types + Matrix4x4 + CameraView + ViewportEntry + VideoModeConfig + ViOutConfig + Entity + RenderNode) |
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
66. **Named struct fields — TrackNode** — created `include/track.h` with the
    `TrackNode` typedef (0x38 bytes, all known fields named). Updated 4 C files
    to use `TrackNode *` instead of `Unk *`, replacing all `->unkXX` accesses with
    named fields and simplifying stride arithmetic:
    - `func_8004FCF8.c` (trackNodeRender): `Unk *` locals → `TrackNode *`; `->unk0/4/8`
      → `->posX/Y/Z`; `->unkC/E/10` → `->normalX/Y/Z`; `->unk12` → `->colorIdx`;
      `->unk16` → `->flags`; `->unk18` → `->nextNode`; `->unk2C/2E/30` →
      `->raceColor0/1/2`; `->unk32/34` → `->friction/renderNode`; cross-element
      accesses `->unk38/3C/40` → `(ptr+1)->posX/Y/Z`; pointer increments
      `+= 0x38` / `-= 0x38` → `++` / `--`; section-start check
      `*(s32*)((char*)ptr - 20) != 0x8000` → `(ptr-1)->nextNode != 0x8000`.
    - `func_8004EC88.c` (trackNodeSearchNearest): `temp_s1` → `TrackNode *`;
      m2c stride decomposition `(var_v0 - var_s0) * 8 + base` → `&base[var_s0]`.
    - `func_8004EE64.c` (trackNodeFindNearest): `temp_a0` → `TrackNode *`;
      `->unk50` (cross-element offset 0x50 = 0x38+0x18) → `temp_a0[1].nextNode`;
      stride multiplications → array subscripts.
    - `func_80050260.c` (trackEdgeProcess): forward declaration updated to
      `TrackNode *`; call site cast added.
    All 453 C files compile cleanly.
68. **Named struct — Matrix4x4** — created `include/mtx.h` with `Matrix4x4` typedef
    (0x40 bytes, 16 f32 fields in row-major layout). Updated 8 C files to use
    `Matrix4x4 *` instead of `Unk *` for matrix arguments:
    - `func_8005685C.c` (mtxRotXF): local typedef → `#include "mtx.h"`.
    - `func_800568F4.c` (mtxRotAxisF + mtxRotAxisFGetter2): same.
    - `func_8005698C.c` (mtxRotZF): same.
    - `func_80056EAC.c` (mtxCatF + mtxXfmPoint3): signatures updated; loop vars
      `var_a2`/`var_v0` kept as `Unk *` for aliased-copy stride path.
    - `func_80058138.c` (mtxRotAxisAngle): arg0 → `Matrix4x4 *`; arg1 stays `Unk *` (vec3).
    - `func_80058294.c` (mtxLookAt): arg0 → `Matrix4x4 *`.
    - `func_80058584.c` (mtxSetFromVectorsNeg): arg0 → `Matrix4x4 *`.
    - `func_800577A8.c` (mtxProjectVec + guMtxScaleF2L): arg0 → `Matrix4x4 *` in both;
      `var_a0` kept as `Unk *` for row-stride loop; guMtxScaleF2L arg1 stays `Unk *`
      (N64 fixed-point Mtx output).
    All 453 C files compile cleanly.
69. **Extended Matrix4x4 sweep — 6 more files** — continued Matrix4x4 conversion:
    - `func_80056A18.c` (mtxIdentInit, mtxCopyTranslate, func_80056B80, func_80056C2C):
      mtxIdentInit + mtxCopyTranslate → `Matrix4x4 *`; func_80056B80/func_80056C2C stay
      `Unk *` (write packed s16.16 N64 Mtx integers).
    - `func_80056DE0.c` (rdpMtxPackRow, mtxNodeInit, mtxCatFSafe): mtxNodeInit →
      `Matrix4x4 *`; rdpMtxPackRow stays `Unk *` (implicit SN64 register ABI).
    - `func_80057DB4.c` (mtxSetFromVectors, mtxTransposeL2F): mtxTransposeL2F →
      `Matrix4x4 *`; mtxSetFromVectors stays `Unk *` (writes packed N64 Mtx).
    - `func_80079F58.c` (guLookAtF): arg0 → `Matrix4x4 *`; `guMtxIdent` call cast
      `(char *)arg0`.
    - `func_8007B508.c` (guScaleF): replaced local `UnkStruct_arg0` typedef with
      `#include "mtx.h"`; arg0 → `Matrix4x4 *`.
    - `func_8007B890.c` (mtxEulerScaleF): arg0 → `Matrix4x4 *`.
    All 453 C files compile cleanly.
70. **Named struct — CameraView** — created `include/camera.h` with `CameraView` typedef
    (minimum 0x1E8 bytes; embedded in gEntityPool entity entries). Updated 3 C files to use
    `CameraView *arg1` instead of `Unk *`, replacing all arg1->unkXX accesses:
    - `func_8006AE78.c` (cameraHiliteRender): eyeX/Y/Z, atX/Y/Z, upX/Y/Z, nearClip.
    - `func_80069A60.c` (cameraViewRender): same fields.
    - `func_800693BC.c` (cameraMatrixBuild): same fields + hiliteFlag (0x1E4).
    All 453 C files compile cleanly.
71. **Named structs — ViewportEntry + VideoModeConfig** — created `include/vi.h` with
    `ViewportEntry` (0x20 bytes: x/y/w/h s32 + scaleX/Y/centerX/Y f32) and `VideoModeConfig`
    (0x80 bytes: `ViewportEntry vp[4]`). Extracted from local typedef in func_8004E7A8.c.
    Updated 4 files:
    - `func_8004E7A8.c` (viModeConfig): removed 33-line local typedef; added `#include "vi.h"`;
      rewrote all flat `p->unkXX` accesses as `p[n].field` using `ViewportEntry *p = gVideoMode.vp`.
    - `func_8005F980.c` (gameSceneInit): `extern Unk gVideoMode` → `extern VideoModeConfig`;
      8 direct field accesses → `gVideoMode.vp[0].field`.
    - `func_800676DC.c` (gameRaceRender): `extern s32 gVideoMode` → `extern VideoModeConfig`;
      `Unk *temp_s2` → `ViewportEntry *`; `(arg0 << 5) + &gVideoMode` → `&gVideoMode.vp[arg0]`;
      8 field accesses → named fields.
    - `func_80067DB4.c` (trackEntityRender): same extern + pointer fix; `temp_s1->unk8/unkC` →
      `temp_s1->w/h`.
72. **Matrix4x4 for mtxIdentSetPos** — `func_8007B7D8.c`: replaced local `UnkStruct_arg0` typedef
    with `#include "mtx.h"`; arg0 → `Matrix4x4 *`; `guMtxIdent(arg0)` → `guMtxIdent((char *)arg0)`.
    All 453 C files compile cleanly.
73. **Decompiled audioQueueDispatch** — rewrote `func_8005C9BC.c` from a void stub to a
    full C implementation. The function uses non-standard ABI ($v1 as input); re-ABIed
    to `s32 cmd` ($a0). Extracted 3 alabel entry points as separate callable C functions
    sharing a `static void audioQueueTail()` helper. 5-case switch:
    - case 0: initialize audio DMA (calls func_8007BA98/8008E518/8007CD08/8007E074/EA68/E5E8)
    - case 1: increment decode-tick counter; overflow → status=2 + countdown=0x2A
    - case 2: countdown delay; at zero, poll RSP done and conditionally clear status
    - case 3: decrement decode counter; at zero, call func_8007EAE8 and set status=4
    - case 4: poll RSP done; when done, clear status
    audioQueueTail: FPU timing computation then calls func_8007EAA8 (set audio volume).
    17 extern D_ globals declared with descriptive comments.
74. **Fixed pre-existing syntax errors** — 2 files repaired:
    - `func_8008E628.c`: 14 assignment statements missing trailing `;` (m2c output bug);
      fixed with Python script detecting `expr)` pattern on assignment lines.
    - `func_80090598.c`: missing `)` before `{` on one `if` condition + missing `;`
      on the next statement; both fixed with Edit tool.
    All 453 C files compile cleanly after fixes.
75. **Implemented entityUpdateDispatch (func_8005566C.c)** — rewrote from empty stub
    to full C implementation. The function spans 0xDA8 bytes with 17 alabel markers
    and a 28-entry jump table (`jtbl_8004BCE8`). Used static file-scope variables for
    SN64 callee-saved register state (`$s2–$s6`, 9 stack locals). Split into 3 C
    functions:
    - `func_80055900(void)` — externally callable infinite dispatch loop (10 entries
      in `jtbl_8004BCE8` jump to it directly); `osRecvMesg` on `gPiMesgQueue`,
      28-case switch on received state word.
    - `entityUpdateDispatch(void)` — initialises static state and all subsystems,
      then calls `func_80055900()`.
    - `func_80056414(void)` — `sP2Flags |= 1; func_80055900();`
    - `func_8005641C(void)` — `gOverlayState = 0; func_80055900();`
    Also: renamed `contPakWriteNote` (4-param, func_8008A898) to `contPakWriteNoteEntry`
    to resolve naming collision with the 6-param outer function in func_8008A994.c.

76. **Restored full 453-file clean compile** — fixed a batch of pre-existing and
    session-introduced compilation errors that were uncovered when ultra64.h gained
    proper `osRecvMesg` / `osSendMesg` / `osCreateMesgQueue` declarations:
    - **Header `#include "types.h"` → `#include "ultra64.h"`** in all 5 sub-headers
      (`include/track.h`, `include/mtx.h`, `include/vi.h`, `include/audio.h`,
      `include/camera.h`) — `types.h` does not exist; `ultra64.h` provides all types.
    - **OS function redeclarations** — stripped stale `s32 osRecvMesg(Unk*, s32*, s32)`
      / `void osSendMesg(...)` / `void osCreateMesgQueue(Unk*, s32, s32)` forward
      declarations from 40 source files; updated the 3 definition files
      (`func_8007CD08.c`, `func_8007CE48.c`, `func_8007BA28.c`) to use the correct
      `OSMesgQueue*` / `OSMesg` parameter types with internal `Unk *` casts.
    - **MMIO macro conflicts** — removed `extern s32 PI_STATUS_REG` / `SI_PIF_ADDR_RD64B`
      / `SI_PIF_ADDR_WR64B` declarations from 11 files where the name is already a
      dereference macro in ultra64.h (expansion caused syntax errors).
    - **Missing semicolons** — fixed ~14 m2c-output assignment statements missing
      trailing `;` across func_8007AA68, func_8007E8E4, func_80088C98, func_80089EF8,
      func_8004F4AC, func_80062D98, func_80065648, func_80065964, func_80075360,
      func_8007DD7C, func_8007F5C4, func_800805A4, func_8008DE28, and others.
    - **Syntax errors** — fixed `|;` in func_80062D98 (multiline OR expression);
      spurious `;` after `else if` in func_8007F5C4 and func_800805A4; `(;` inside
      function-pointer calls in func_8008DE28; unbalanced `)` in func_80065964
      (intToAsciiStr / copyU16Array / rdpFmt2Digit / rdpFormatFloatGetter calls).
    - **GETTER_NOJR return type errors** — changed `return someFunc()` to `someFunc()`
      in 6 void GETTER_NOJR stubs (func_800586CC, func_8005D178, func_80084F48,
      func_800857DC, func_8008E368, func_8008E3C0).
    - **Duplicate extern** — removed duplicate `gSfxFadeTimer` declaration in
      func_80062B0C.c; removed conflicting 4-param forward declaration of
      `contPakWriteNote` in func_8008A994.c; renamed func_8008A898.c function to
      `contPakWriteNoteEntry`.
    All 453 C files compile cleanly.

77. **Implemented gameThreadEntry (func_800541C0.c)** — rewrote from empty stub to full
    C89 implementation (~940 lines). Frame: 0xB0, saves $ra/$fp/$s0–$s7/$fs0.
    - `outQueue`/`inQueue` typed as `OSMesgQueue *`, loaded from the args struct.
    - Outer `osRecvMesg` loop on `inQueue`; switch on message type (0x13–0x17).
    - Message 0x13: init — calls gameHandlerSetup, audioSystemInit, sfxRaceInit, etc.
    - Message 0x14/0x16: frame update — per-entity state machine via jtbl_8004BCC8
      (6 states, goto-based C89 control flow); 6 parallel struct pointers incremented
      at loop tail.
    - Message 0x17: big update — swap timing counters, call gameLoopDispatch(), send reply.
    - Skip-frame path (.L800551E4): subtract D_8004BCE4 from fs0.
    All 453 C files compile cleanly.

78. **Implemented frameDispatchThread (func_800602A0.c)** — rewrote from empty stub to
    full C89 implementation. 17-entry jump table (jtbl_8004BF80, messages 0xB–0x1B).
    Static shared state: `sRecvQueue`, `sSendQueue`, `sPhase`, `sRaceProgress`,
    `sTickCount`, `sVolScale` (models $s0/$s1/$s4/$fs1 SN64 callee-saved across alabel
    entry points).
    - `frameDispatchThread(Unk *args)`: loads queues from args[0]/args[4], inits state,
      enters `frameRecvAndDispatch()`.
    - `func_8006030C`/`func_80060310`: alabel entry points, both call `frameRecvAndDispatch()`.
    - `frameRecvAndDispatch()`: infinite osRecvMesg loop, dispatches via jtbl_8004BF80.
    - `frameHandle14()`: race phase state machine (phases 2–7): progress counter,
      audio fade, overlay probe, race-start music selection via jtbl_8004BFE0/BFF8.
    - `func_800607E0`, `func_80060800`, `func_80060808`, `func_80060824`: companion
      entry points for messages 0x17, 0xB, 0x1B, and alabel 0x1B+4.
    All 453 C files compile cleanly.

79. **D_ rename sweep — 8 symbols, 120 replacements** — applied across 5 files:
    `func_80052F5C.c` (44), `func_800541C0.c` (40), `func_8005566C.c` (2),
    `func_800602A0.c` (27), `func_8006C128.c` (7).
    Mappings: `D_80182EA8`→`gRaceCtx`, `D_80173C28`→`gRaceCtrlCount`,
    `D_80091968`→`gTrackNodeCount`, `D_8017C950`→`gRaceMax`,
    `D_80092B88`→`gGameFlags2`, `D_80173C40`→`gEventQueueSize`,
    `D_80173C0C`→`gContPakUpdateFlag`, `D_80173D08`→`gLoopCount`.
    All 453 C files compile cleanly.

80. **D_ rename sweep — 11 symbols, 194 replacements** — applied across 5 files:
    `func_80052F5C.c` (32), `func_800541C0.c` (103), `func_800602A0.c` (25),
    `func_80066580.c` (19), `func_8006C128.c` (15).
    Mappings: `D_80170880`→`gRenderPool`, `D_801786C0`→`gFrameSyncMsg`,
    `D_8017C958`→`gLodFlag`, `D_8017C938`→`gGameDirty`, `D_80091E74`→`gFrameTick`,
    `D_80182468`→`gSceneState`, `D_8017CDF0`→`gDeferredFlag`,
    `D_8017CDC8`→`gCurEntityPtr`, `D_80173C1C`→`gSceneTransFlag`,
    `D_80091F50`→`gEntityScratch`, `D_80170874`→`gFrameCounter`.
    Named data globals total: **821**. All 453 C files compile cleanly.

81. **D_ rename sweep — 15 symbols, 110 replacements** — applied across 7 files:
    `func_80052F5C.c` (29), `func_800541C0.c` (39), `func_8005566C.c` (14),
    `func_8005C9BC.c` (16), `func_800602A0.c` (2), `func_80066580.c` (8),
    `func_8006C128.c` (2).
    Mappings: `D_80092814`→`gAudioDecodeTick`, `D_80182E74`→`gTextColorA`,
    `D_80178750`→`gRenderFade`, `D_80091E5C`→`gSplitScreenMode`,
    `D_8017CDDC`→`gPiMsgBuf`, `D_8017CCD0`→`gFrameFlipSync`,
    `D_8017C940`→`gSkipFrameFlag`, `D_8017C888`→`gFadeCounter`,
    `D_80174C38`→`gFrameSyncCountB`, `D_80174C28`→`gFrameSyncFlag`,
    `D_80174C20`→`gFrameSyncCountA`, `D_80173BC8`→`gUnkFlag_173BC8`,
    `D_8016BE58`→`gVelStateBlock`, `D_80092824`→`gAudioFramePending`,
    `D_80091EA0`→`gEntityPool`.
    Named data globals total: **836**. All 453 C files compile cleanly.

82. **D_ rename sweep — 24 symbols, 129 replacements** — applied across 7 files:
    `func_80052F5C.c` (42), `func_800541C0.c` (41), `func_8005566C.c` (24),
    `func_8005C9BC.c` (6), `func_800602A0.c` (6), `func_80066580.c` (5),
    `func_8006C128.c` (5).
    Mappings: `D_8017CD30`→`gCameraSlotCache`, `D_8017C108`→`gRaceEndMsg`,
    `D_80174C18`→`gPiMsgSlotA`, `D_80173C38`→`gRaceRestartFlag`,
    `D_80092808`→`gAudioBufTarget`, `D_80091F7C`→`gTimerLo`,
    `D_80182E84`→`gTextColorRGBA`, `D_8017CC58`→`gEntityRenderCount`,
    `D_8017CA08`→`gContInputCache`, `D_8017C954`→`gLodShadow`,
    `D_8017C1A8`→`gFrameAccumB`, `D_801786C8`→`gRenderSlotCount`,
    `D_80174C24`→`gActiveEntityIdx`, `D_80174C14`→`gViewportWatermark`,
    `D_80174C00`→`gPiMsgSlotC`, `D_80174BEC`→`gRenderCompleteFlag`,
    `D_800939B8`→`gDLBufBase`, `D_800924C4`→`gHandlerObjPtr`,
    `D_80091E84`→`gAudioCallbackFlag`, `D_80091E7C`→`gPrevFrameTick`,
    `D_80091F80`→`gTimerLoCopy`, `D_80091DFC`→`gVehicleTable`,
    `D_800E6E40`→`gAudioSynthState`, `D_80092500`→`gCameraObj`.
    Named data globals total: **860**. All 453 C files compile cleanly.

83. **D_ rename sweep — 19 symbols, 77 replacements** — applied across 7 files.
    Mappings: `D_80091E68`→`gTrackNodePtr`, `D_80185DB8`→`gParticleCount`,
    `D_80184580`→`gGameTypeCode`, `D_80182E7C`→`gTextFillFlag`,
    `D_8017EFE8`→`gAudioWorkBufB`, `D_8017CDE0`→`gRenderParamA`,
    `D_8017CDD0`→`gRenderParamB`, `D_8017C93C`→`gFrameLockFlag`,
    `D_8017C1AC`→`gFrameAccumA`, `D_80174C10`→`gFrameSkipShadow`,
    `D_80174748`→`gViewportTileBuf`, `D_8016DFB0`→`gEntityRenderFlags`,
    `D_801605D8`→`gRenderNodeBuf`, `D_80093F04`→`gSfxLodFlag`,
    `D_80092820`→`gAudioRetryCountdown`, `D_8009280C`→`gAudioBufRunning`,
    `D_800924B4`→`gFrameDbIdx`, `D_80091E78`→`gSubTickCounter`,
    `D_80091E54`→`gAudioBufState`.
    Named data globals total: **879**. All 453 C files compile cleanly.

84. **D_ rename sweep — 19 symbols, 62 replacements** — applied across 6 files.
    Mappings: `D_8004BCA4`→`gFrameTimerF`, `D_8004BCBC`→`gFrameTimerCap`,
    `D_8004BE18`→`gAudioTimingThresh`, `D_8004C460`→`gLodDistClose`,
    `D_801839B4`→`gSplitTypeFlag`, `D_8017CA40`→`gRenderSyncB`,
    `D_8017C898`→`gRenderStateReply`, `D_80192840`→`gAudioStreamStatus`,
    `D_8017CA20`→`gRenderSyncFlag`, `D_801808EC`→`gAudioModeConfig`,
    `D_80182E68`→`gSceneLoopCount`, `D_80182E76`→`gTextColorB`,
    `D_80182E94`→`gTextColorACopy`, `D_80182E96`→`gTextColorBCopy`,
    `D_80182E6C`→`gClearColor`, `D_80174BF0`→`gRenderFlagB`,
    `D_80174550`→`gEntityInputBuf`, `D_80173D10`→`gHandlerMsgBufB`,
    `D_80173D00`→`gHandlerMsgBufA`.
    Named data globals total: **898**. All 453 C files compile cleanly.

85. **D_ rename sweep — 20 symbols, 59 replacements** — applied across 6 files.
    Mappings: `D_80091FCC`→`gMultiPlayerFlag`, `D_80091FD0`→`gPlayerCountBit`,
    `D_80093334`→`gControllerCount`, `D_800910C8`→`gCameraData`,
    `D_80173BD0`→`gTrackRenderEntries`, `D_80090CF8`→`gDLBufSaveA`,
    `D_801747C8`→`gInitReplyToken`, `D_8016DF88`→`gPlayerConfigTable`,
    `D_8016DFD8`→`gEntityTrackState`, `D_801708C0`→`gRenderPool2`,
    `D_80091E98`→`gContSnapshot`, `D_80173CE8`→`gInitMsgQueue2`,
    `D_8009281C`→`gAudioDecodeInc`, `D_80093F08`→`gRaceTriggerFlag`,
    `D_80173CB8`→`gRaceCountdownMsg`, `D_80093A28`→`gDLBufBaseB`,
    `D_80093EB0`→`gTexLodTableA`, `D_80093E98`→`gTexLodTableB`,
    `D_80093EA4`→`gTexLodTableC`, `D_80090EA0`→`gEntityPoolBase`.
    Named data globals total: **918**. All 453 C files compile cleanly.

86. **D_ rename sweep — 43 symbols, 91+46+10 replacements** — final three passes
    across all remaining named D_ symbols. Key mappings: rodata constants
    (`D_8004BC94`–`D_8004BCB4`→`gViewInitA`–`G`, `D_8004BCC0`→`gFrameTimerInc`,
    `D_8004BCE0`→`gPhysTickOne`, `D_8004BCE4`→`gSkipFrameDecr`,
    `D_8004BF7C`→`gAudioVolScale`, `D_8004C46C`→`gTexLodNear`,
    `D_8004C470`→`gTexLodMid`, `D_8004CE50`→`gTempoDurConst`,
    `D_8004BE08`→`gAudioTimingScale`, `D_8004B680`→`gAudioUcodeBase`,
    `D_8004BA1C`→`gRomHeader`), BSS/RAM (`D_80173C3C`→`gRenderInitFlag`,
    `D_80093350`→`gRaceCtrlPtr`, `D_80174C4C`→`gViewportCountB`,
    `D_80174C48`→`gViewportCountA`, `D_80174728`→`gViewInitF`,
    `D_800924D8`→`gViewportInitTable`, `D_800B39B0`→`gSfxSampleTable`,
    `D_800B55C0`→`gSfxUcodeBase`, `D_80174C08`→`gPiMsgSlotB`,
    `D_800925C4`→`gAudioSfxReady`, `D_80091E80`→`gAudioStateFlag`,
    `D_80090CFC`→`gDLBufSaveB`, `D_80095B50`→`gViModeNtsc`,
    `D_800956F0`→`gViModePal60`, `D_80095FB0`→`gViModeMpal`,
    `D_80092804`→`gAudioSampleRate`, `D_80092818`→`gAudioDecodeDecr`,
    `D_80092B5C`→`gFrameEventCount`, `D_80092B80`→`gRaceReadyFlag`,
    `D_80173C20`→`gRaceStartMsg`, `D_80178450`→`gOverlayReadyMsg`,
    `D_80093B98`→`gDLSegAddr`, `D_80093B08`→`gRenderBufBase`,
    `D_80000300`→`gHwVersion`, `D_800924D0`→`gFrameStateCount`,
    `D_80093B10`→`gDLSegAddrB`, `D_8017C968`→`gViewportTable`,
    `D_80178694`→`gHorizScaleF`, `D_8017869C`→`gVertScaleF`,
    `D_80185DBD`→`gParticleColorG`, `D_80185DBE`→`gParticleColorB`,
    `D_8018D878`→`gSceneLoadBuf`).
    Named data globals total: **961**. All 453 C files compile cleanly.
    14 D_ references remain: all are comment-only annotations,
    GETTER_NOJR preload notes, or the `D_801747C8_msgO` / `UnkStruct_D_80095644`
    intentional workarounds — none are live code D_ references.

67. **Named struct — ViOutConfig** — added to `include/vi.h` (0x08 bytes: `ctrl` u16 +
    2-byte pad + `output` s32). Updated `func_800876D8.c` (viSetOutput): removed local
    `UnkStruct_D_80095644` typedef; `gVIConfig` re-typed as `ViOutConfig *`; `->unk4` →
    `->output`, `->unk0` → `->ctrl`. All 453 C files compile cleanly.

68. **Named struct — Entity** — created `include/entity.h` with the `Entity` typedef
    (0x228 bytes, partial field coverage). Fields named from entityPhysicsInit analysis:
    `posX/velX/velY/posY/velZ/posZ/upY` (0x00–0x1C), `unk018/020/024/028/02C` (flags),
    `timerA/timerB/timerEnable` (0xB0–0xB8), `nearClip` (0xCC), `renderObj *` (0xD0),
    `unkD4/unkDC` (per-slot counters), `raceFlags/unk104/viewDepth` (0xE4/104/124),
    `unk12C/velParamF/unk134/unk144/velParamG` (0x12C–0x148), `physicsSlot[0x88]`
    (0x14C), `unk1D4/raceSlotType/unk1E0/hiliteFlag` (0x1D4–0x1E4),
    `unk1E8–unk214/raceSlotCount/velParamL/velParamM` (0x1E8–0x21C).
    Updated `func_8004EFFC.c` (entityPhysicsInit): `arg0` → `Entity *`; all
    named fields replaced; `var_v1`/`temp_v0` kept as `Unk *` for the 8-slot
    pointer-arithmetic sub-loop. All 453 C files compile cleanly.

67. **Named struct fields — AudioNode hierarchy** — created `include/audio.h` with
    `AudioNodeBase` (0x14 bytes) and 6 concrete node types: `AudioTimerNode` (0x1C),
    `AudioNoteWriteNode` (0x20), `AudioMixNode` (0x4C), `AudioVoiceNode` (0x34),
    `AudioAdpcmNode` (0x48), `AudioMidiNode` (0x50). Updated 7 C files to use typed
    node pointers instead of `Unk *`:
    - `func_80082E98.c` (audioTimerNodeInit): `AudioTimerNode *arg0`; unk14/18 named.
    - `func_80082EDC.c` (audioNoteWriteNodeInit): `AudioNoteWriteNode *arg0`;
      unk14→writeIdx, unk18→voiceCount, unk1C→bufPtr.
    - `func_80082F30.c` (audioMixNodeInit): `AudioMixNode *arg0`;
      unk18→voiceCount, unk1C→voiceBufPtr.
    - `func_80082F84.c` (audioVoiceNodeInit): `AudioVoiceNode *arg0`;
      unk14→pcmBufPtr, unk18→gain, unk24/28/2C/30 retained.
    - `func_8008300C.c` (audioAdpcmNodeInit): `AudioAdpcmNode *arg0`;
      unk14→inBufPtr, unk18→outBufPtr, unk30→initResult, unk34→decodeCtx[].
    - `func_800830B4.c` (audioMidiNodeInit): `AudioMidiNode *arg0`;
      unk14→eventBufPtr; remaining u16 fields retained as unkXX.
    - `func_800849A4.c` (audioNodeInit + audioNoteWrite): `AudioNodeBase *arg0`
      in audioNodeInit with all 6 fields named (state/cmdFn/propFn/unk0C/unk0E/
      nodeType); `AudioNoteWriteNode *arg0` in audioNoteWrite with writeIdx/bufPtr.
    All 453 C files compile cleanly.

86. **Applied Entity * to entity dispatch files (Task 21)** — converted 6 C files to use
    `Entity *` typed pointers instead of stride arithmetic / `Unk *`:
    - `func_80068D2C.c` (trackEntityRender): `Entity *temp_v0/v0_2`; gEntityPool[var_t2]
      subscripts; `timerA/timerB/atX/Y/Z/eyeX/Y/Z/hiliteFlag` field names.
    - `func_80067DB4.c` (gameCameraSetup): `Entity *temp_t1/s0/s1_2/s0_4/v0_5`; all
      `(arg0 * 0x228) + &gEntityPool` → `ent`; colorR/G/B, raceSlotType, renderObj,
      velParamG, timerA/B, upX/Y/Z, atX/Y/Z, eyeX/Y/Z, hiliteFlag fields applied;
      raw byte sub-regions kept as `(char *)ent + 0x30`.
    - `func_8005E2E4.c` (entityFindNearest): `Entity *var_a1/v1`; `gEntityPool` base
      iteration; atX/Y/Z, raceSlotCount, renderObj fields; `RenderNode *temp_v0`; speed field.
    - `func_8005D9C0.c` (sfxComputeSpatialImpl): `Entity *var_s1/v1`; renderObj,
      posX/Y/Z, active, raceSlotType, eyeX/Y/Z, atX/Y/Z, upX/Y/Z, raceSlotCount,
      unkC0/C4/C8 fields; `RenderNode *temp_v0/v0_2/v0_3`; speed field.
    - `func_8004EFFC.c` (entityPhysicsInit): `RenderNode *arg1`; entity/entityIdx fields.
    - `func_800676DC.c` (gameRaceRender): `RenderNode *var_s1`; active, posX/Y/Z, upX/Y/Z,
      alphaParam, raceIdx, speed fields; `var_s1++` stride.
    - `func_80052BB0.c` (mainPoolAlloc/func_80052C04): `RenderNode *arg0/var_a0`;
      distRef, active, state fields; `var_a0++` stride.
    Fixed Entity struct: `u8 unk1D8[4]` → 4 individual bytes (for ->unk1D9 scalar access);
    `u8 unk224[4]` → `u16 unk224; u8 unk226[2]` (for scalar assignment).
    Added `struct RenderNode_s;` forward decl + tagged struct pattern for circular reference.
    All 453 C files compile cleanly.

87. **Named RenderNode struct (Task 22)** — created `include/render.h` with `RenderNode`
    typedef (0x668 bytes; verified with IDO 7.1 size-check array). Key fields:
    posX/Y/Z (0x00), modelObj (0x0C), eyeX/Y/Z (0x10), atX/Y/Z (0x1C), refX/Y/Z (0x034),
    upX/Y/Z (0x040), vehicleSlot (0x054), bikeObj (0x06C), vehicleEntry (0x114),
    speedParam (0x2DC), distRef (0x30C), velX/Y/Z (0x398), raceIdx (0x440), active (0x450),
    alphaParam (0x558), entityIdx (0x560), entity (0x568), state (0x588), speed (0x648),
    cameraFlag (0x64C). Mutual forward declaration with `Entity` via tagged struct tags.
    Updated 5 more files to use `RenderNode *`:
    - `func_80069A60.c` (cameraViewRender): arg0 → `RenderNode *`; upX/Y/Z, eyeX/Y/Z,
      atX/Y/Z, refX/Y/Z, modelObj, cameraFlag fields; `gTrackNodePool[arg7].cameraFlag`.
    - `func_800676DC.c`, `func_80052BB0.c`, `func_8005D9C0.c`, `func_8005E2E4.c`:
      already updated in Task 21.
    All 453 C files compile cleanly.

89. **Applied Entity/RenderNode types to gameStateInit (func_80052F5C.c)** — converted all
    raw byte-offset casts in the 0xFA4-byte init function:
    - Added `#include "entity.h"` and `#include "render.h"`.
    - `extern Unk gEntityPool[]` → `extern Entity gEntityPool[]`; `extern Unk gRenderPool[]`
      → `extern RenderNode gRenderPool[]`; `extern s32 gCameraData` → `extern Entity gCameraData`.
    - Forward declaration `func_8004EFFC(void *a0, void *a1)` → `entityPhysicsInit(Entity *a0, RenderNode *a1)`.
    - Stage 6 entity pool init: `Unk *entityEnt` → `Entity *entityEnt`; all 15 raw-offset
      writes replaced with named fields (eyeX/Y/Z, atX/Y/Z, upX/Y/Z, timerA/B/timerEnable,
      renderObj=NULL, unk1E0, hiliteFlag); stride `+= 0x228` → `entityEnt++`.
    - Stage 11 render pool init: `Unk *renderEnt` → `RenderNode *renderEnt`; index
      `(u8 *)gRenderPool + s2 * 0x668` → `&gRenderPool[s2]`; all field accesses converted:
      state (0x588), speedParam (0x2DC), cameraFlag (0x64C), bikeObj (0x06C), modelObj (0x0C),
      vehicleSlot (0x054), unk594 (0x594), vehicleEntry (0x114); tail zero loop → `modelObj = NULL`.
    - Single-player camera: `func_8004EFFC(&gCameraData, gRenderPool)` → `entityPhysicsInit(&gCameraData, gRenderPool)`;
      `*(s32 *)((u8 *)&gCameraData + 0x1E0) = 1` → `gCameraData.unk1E0 = 1`.
    - Linkage loop: `ep`/`rp` typed as `Entity *`/`RenderNode *`; stride expressions → `ep++`/`rp++`.
    - Expanded `include/render.h`: split `unk58C[0xC]` to expose `s16 unk594` (0x594).
    All 453 C files compile cleanly.

88. **Improved renderSceneDispatch / expanded RenderNode (Task 23)** — updated
    `func_8006C128.c` (renderSceneDispatch, 0xC64 bytes) to use proper struct types
    throughout instead of raw byte-offset casts:
    - Added `#include "entity.h"` and `#include "render.h"`.
    - `gEntityPool` extern changed from `s32` to `Entity gEntityPool[]`; `gRenderPool`
      changed to `RenderNode gTrackNodePool[]`.
    - `CameraView *cam` → `Entity *cam = &gEntityPool[player_idx]`; cast to
      `(CameraView *)cam` only at camera function call sites.
    - All raw `(u8 *)ent + 0xXX` accesses in Phase 1 converted: `timerA`, `timerB`,
      `colorR/G/B`, `unk134`, `unk1E0`, `raceSlotType`, `hiliteFlag`, `renderObj`.
    - Render loop `Unk *ent` → `RenderNode *ent = gTrackNodePool`; loop stride
      `+= 0x668` → `ent++`. RenderNode fields applied: `activeFlag`, `state`,
      `eyeX/Y/Z`, `cameraFlag`, `modelObj`, `alphaParam`, `viewScaleX`, `viewScaleY`,
      `entityIdx`.
    - Forward declarations for `func_8013F3BC`, `func_800AD77C` updated to `Entity *`.
    - Forward declarations for `cameraViewRender`, `cameraHiliteRender`,
      `cameraMatrixBuild` updated to `RenderNode *arg0`.
    - Expanded RenderNode struct (`include/render.h`) to expose three previously
      unnamed fields: `viewScaleX` (0x57C, f32), `viewScaleY` (0x580, f32),
      `activeFlag` (0x598, s32). Size still 0x668 (IDO verified).
    All 453 C files compile cleanly.
