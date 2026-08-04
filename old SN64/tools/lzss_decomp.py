#!/usr/bin/env python3
"""
XG2 LZSS decompressor
Okumura variant: 4096-byte ring buffer, fill=0x20, initial pos=0xFEE
bit=1 -> literal, bit=0 -> back-reference (12-bit offset, 4-bit length, min 2)

Usage:
  python3 tools/lzss_decomp.py <input.bin> <output.bin>
  python3 tools/lzss_decomp.py --rom baserom.z64 --out assets/boot/decompressed_main.bin
"""
import sys
import struct
import argparse

ROM_SRC_OFFSET  = 0x4C620   # ROM offset of compressed data
ROM_SRC_SIZE    = 0x2B588   # size of compressed blob (44386 words)
DEST_VRAM       = 0x8024BA20


def decompress(src: bytes) -> bytes:
    N        = 4096
    ring     = bytearray(b'\x20' * N)
    r        = 0xFEE
    out      = bytearray()
    si       = 0
    flags    = 0

    while si < len(src):
        flags >>= 1
        if (flags & 0x100) == 0:
            flags = src[si] | 0xFF00
            si += 1
        if flags & 1:
            # Literal byte
            if si >= len(src):
                break
            c = src[si]; si += 1
            out.append(c)
            ring[r] = c
            r = (r + 1) & (N - 1)
        else:
            # Back-reference
            if si + 1 >= len(src):
                break
            j = src[si]; si += 1
            k = src[si]; si += 1
            i      = j | ((k & 0xF0) << 4)
            length = (k & 0x0F) + 2
            for m in range(length):
                c = ring[(i + m) & (N - 1)]
                out.append(c)
                ring[r] = c
                r = (r + 1) & (N - 1)

    return bytes(out)


def main():
    ap = argparse.ArgumentParser(description='XG2 LZSS decompressor')
    ap.add_argument('--rom', help='Source ROM file (extracts blob automatically)')
    ap.add_argument('--out', default='decompressed_main.bin', help='Output file')
    ap.add_argument('input', nargs='?', help='Raw compressed input file')
    ap.add_argument('output', nargs='?', help='Output file (positional)')
    args = ap.parse_args()

    if args.rom:
        with open(args.rom, 'rb') as f:
            f.seek(ROM_SRC_OFFSET)
            src = f.read(ROM_SRC_SIZE)
        out_path = args.out
    elif args.input:
        with open(args.input, 'rb') as f:
            src = f.read()
        out_path = args.output or 'decompressed.bin'
    else:
        ap.print_help()
        sys.exit(1)

    print(f'Decompressing {len(src)} bytes...', file=sys.stderr)
    result = decompress(src)
    print(f'Decompressed to {len(result)} bytes (VRAM: 0x{DEST_VRAM:08X}–0x{DEST_VRAM+len(result):08X})', file=sys.stderr)

    with open(out_path, 'wb') as f:
        f.write(result)
    print(f'Written to {out_path}', file=sys.stderr)


if __name__ == '__main__':
    main()
