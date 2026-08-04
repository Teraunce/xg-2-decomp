#!/usr/bin/env python3
"""
Verify the decompressed main segment looks like valid MIPS code.
Run after tools/lzss_decomp.py.
"""
import sys
import struct

def count_valid_mips(data):
    try:
        import rabbitizer
        valid = sum(
            1 for i in range(0, len(data) - 3, 4)
            if rabbitizer.Instruction(
                struct.unpack('>I', data[i:i+4])[0],
                category=rabbitizer.InstrCategory.CPU
            ).isValid()
        )
        return valid, len(data) // 4
    except ImportError:
        return None, None

def find_prologues(data):
    """Count addiu $sp, $sp, -N (function prologue pattern)."""
    count = 0
    for i in range(0, len(data) - 3, 4):
        w = struct.unpack('>I', data[i:i+4])[0]
        if (w >> 16) == 0x27BD and (w & 0x8000):
            count += 1
    return count

def main():
    path = sys.argv[1] if len(sys.argv) > 1 else 'assets/boot/decompressed_main.bin'
    with open(path, 'rb') as f:
        data = f.read()

    print(f'File: {path}')
    print(f'Size: {len(data):,} bytes ({len(data)//1024} KB)')

    valid, total = count_valid_mips(data)
    if valid is not None:
        print(f'Valid MIPS instructions: {valid}/{total} ({100*valid//total}%)')
    
    prologues = find_prologues(data)
    print(f'Function prologues (addiu $sp,-N): {prologues}')

    if prologues > 50:
        print('✓ Looks like valid game code')
    elif prologues > 10:
        print('? Possibly valid – low prologue count')
    else:
        print('✗ Very few prologues – decompressor parameters may be wrong')

if __name__ == '__main__':
    main()
