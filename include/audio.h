#ifndef AUDIO_H
#define AUDIO_H

#include "ultra64.h"

/* =========================================================================
 * AudioNodeBase — common 0x14-byte header for every audio processing node.
 *
 * audioNodeInit(base, cmdFn, propFn, nodeType) populates this header.
 * All specific node types embed this as their first member.
 *
 * Node type constants (nodeType field):
 * ========================================================================= */
#define AUDIO_NODE_ADPCM     0   /* ADPCM decoder node */
#define AUDIO_NODE_VOICE     1   /* PCM voice node */
#define AUDIO_NODE_TIMER     3   /* timer / sync node */
#define AUDIO_NODE_MIDI      4   /* MIDI event node */
#define AUDIO_NODE_GEOM      5   /* geometry / wavetable node */
#define AUDIO_NODE_MIX       6   /* audio mix node */
#define AUDIO_NODE_NOTEWRITE 7   /* note-write output node */

typedef struct AudioNodeBase {
    /* 0x00 */ s32 state;    /* 0 = inactive */
    /* 0x04 */ s32 cmdFn;    /* command dispatch function pointer (as s32) */
    /* 0x08 */ s32 propFn;   /* property accessor function pointer (as s32) */
    /* 0x0C */ u16 unk0C;
    /* 0x0E */ u16 unk0E;
    /* 0x10 */ s32 nodeType; /* AUDIO_NODE_* constant */
    /* 0x14 */
} AudioNodeBase;

/* -------------------------------------------------------------------------
 * AudioTimerNode — timer / sync node (0x1C bytes, type = AUDIO_NODE_TIMER)
 * Allocated size: 0x1C bytes
 * ------------------------------------------------------------------------- */
typedef struct AudioTimerNode {
    /* 0x00 */ AudioNodeBase base;
    /* 0x14 */ s32 unk14;   /* timer counter / delay state (initial: 0) */
    /* 0x18 */ s32 unk18;   /* initial active state (initial: 1) */
    /* 0x1C */
} AudioTimerNode;

/* -------------------------------------------------------------------------
 * AudioNoteWriteNode — note output node (0x20 bytes, type = AUDIO_NODE_NOTEWRITE)
 * Allocated size: 0x20 bytes
 * Writes note events into a per-voice s32 array (4 bytes per voice).
 * ------------------------------------------------------------------------- */
typedef struct AudioNoteWriteNode {
    /* 0x00 */ AudioNodeBase base;
    /* 0x14 */ s32 writeIdx;    /* current write index (incremented per note) */
    /* 0x18 */ s32 voiceCount;  /* number of voices */
    /* 0x1C */ s32 bufPtr;      /* output buffer pointer (voiceCount × 4 bytes) */
    /* 0x20 */
} AudioNoteWriteNode;

/* -------------------------------------------------------------------------
 * AudioMixNode — audio mixing node (0x4C bytes, type = AUDIO_NODE_MIX)
 * Allocated size: 0x4C bytes
 * ------------------------------------------------------------------------- */
typedef struct AudioMixNode {
    /* 0x00 */ AudioNodeBase base;
    /* 0x14 */ s32 unk14;        /* mix state */
    /* 0x18 */ s32 voiceCount;   /* number of voices */
    /* 0x1C */ s32 voiceBufPtr;  /* voice data buffer pointer (voiceCount × 4 bytes) */
    /* 0x20 */ u8  pad20[0x2C];  /* unused gap */
    /* 0x4C */
} AudioMixNode;

/* -------------------------------------------------------------------------
 * AudioVoiceNode — PCM voice node (0x34 bytes, type = AUDIO_NODE_VOICE)
 * Allocated size: 0x34 bytes
 * ------------------------------------------------------------------------- */
typedef struct AudioVoiceNode {
    /* 0x00 */ AudioNodeBase base;
    /* 0x14 */ s32 pcmBufPtr;   /* PCM output buffer pointer (0x20 bytes) */
    /* 0x18 */ f32 gain;        /* volume gain (initial: 1.0f) */
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ f32 unk20;       /* pan/pitch parameter (initial: 0.0f) */
    /* 0x24 */ s32 unk24;       /* (initial: 1) */
    /* 0x28 */ s32 unk28;
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ s32 unk30;
    /* 0x34 */
} AudioVoiceNode;

/* -------------------------------------------------------------------------
 * AudioAdpcmNode — ADPCM decoder node (0x48 bytes, type = AUDIO_NODE_ADPCM)
 * Allocated size: 0x48 bytes
 * decodeCtx[8] is passed to the init callback (arg1(arg0 + 0x34))
 * ------------------------------------------------------------------------- */
typedef struct AudioAdpcmNode {
    /* 0x00 */ AudioNodeBase base;
    /* 0x14 */ s32 inBufPtr;        /* input  PCM buffer (0x20 bytes) */
    /* 0x18 */ s32 outBufPtr;       /* output PCM buffer (0x20 bytes) */
    /* 0x1C */ u8  pad1C[0x14];     /* unknown gap */
    /* 0x30 */ s32 initResult;      /* return value from init callback */
    /* 0x34 */ u8  decodeCtx[0x8];  /* ADPCM state passed to init callback */
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ s32 unk40;           /* (initial: 1) */
    /* 0x44 */ s32 unk44;
    /* 0x48 */
} AudioAdpcmNode;

/* -------------------------------------------------------------------------
 * AudioMidiNode — MIDI event node (0x50 bytes, type = AUDIO_NODE_MIDI)
 * Allocated size: 0x50 bytes
 * eventBufPtr → 0x50-byte MIDI event ring buffer
 * ------------------------------------------------------------------------- */
typedef struct AudioMidiNode {
    /* 0x00 */ AudioNodeBase base;
    /* 0x14 */ s32 eventBufPtr;  /* MIDI event buffer pointer (0x50 bytes) */
    /* 0x18 */ u16 unk18;
    /* 0x1A */ u16 unk1A;        /* (initial: 1) */
    /* 0x1C */ u16 unk1C;        /* (initial: 1) */
    /* 0x1E */ u16 unk1E;        /* (initial: 1) */
    /* 0x20 */ u16 unk20;
    /* 0x22 */ u16 unk22;
    /* 0x24 */ u16 unk24;
    /* 0x26 */ u16 unk26;        /* (initial: 1) */
    /* 0x28 */ u16 unk28;        /* (initial: 1) */
    /* 0x2A */ u8  pad2A[4];
    /* 0x2E */ u16 unk2E;        /* (initial: 1) */
    /* 0x30 */ s32 unk30;
    /* 0x34 */ s32 unk34;
    /* 0x38 */ s32 unk38;        /* (initial: 1) */
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ s32 unk40;
    /* 0x44 */ s32 unk44;
    /* 0x48 */ s32 unk48;
    /* 0x4C */ u8  pad4C[4];
    /* 0x50 */
} AudioMidiNode;

#endif /* AUDIO_H */
