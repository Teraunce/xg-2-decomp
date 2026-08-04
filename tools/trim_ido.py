#!/usr/bin/env python3
"""
trim_ido.py  --  Fix IDO 7.1 .text section padding in ELF32 object files.

IDO 7.1 pads the .text section of every compiled object to a 16-byte boundary.
The reference N64 binary was linked with functions packed at 4-byte alignment
(no padding).  After IDO compiles a .c file we need to trim the trailing nops
from the .text section so the object can link byte-exactly.

The expected size is read from the matching .s stub:
    nonmatching func_XXXXXXXX, 0xSIZE

For stubs with multiple functions, only secondary function sizes are included
if the corresponding symbol is actually present in the compiled .o.

Usage:
    python3 tools/trim_ido.py  <input.o>  <output.o>  <stub.s>
"""
import sys
import struct
import re
import subprocess
import os


def get_defined_symbols(obj_path: str) -> set:
    """Return set of symbols defined in the .text section of an ELF object."""
    syms = set()
    try:
        with open(obj_path, 'rb') as f:
            data = f.read()
        # Simple ELF32 symbol table scan
        if data[:4] != b'\x7fELF':
            return syms
        def u16(off): return struct.unpack_from('>H', data, off)[0]
        def u32(off): return struct.unpack_from('>I', data, off)[0]
        e_shoff = u32(32)
        e_shentsize = u16(46)
        e_shnum = u16(48)
        e_shstrndx = u16(50)
        strtab_off = u32(e_shoff + e_shstrndx * e_shentsize + 16)
        def shname(i):
            sh_name = u32(e_shoff + i * e_shentsize)
            return data[strtab_off + sh_name:].split(b'\x00')[0].decode('ascii', errors='replace')
        # Find .symtab and .strtab
        symtab_off = symtab_size = symtab_entsize = 0
        symstr_off = 0
        for i in range(e_shnum):
            sh_off = e_shoff + i * e_shentsize
            sh_type = u32(sh_off + 4)
            name = shname(i)
            if name == '.symtab' and sh_type == 2:
                symtab_off = u32(sh_off + 16)
                symtab_size = u32(sh_off + 20)
                symtab_entsize = u32(sh_off + 36)
                symstr_idx = u32(sh_off + 24)
                symstr_off = u32(e_shoff + symstr_idx * e_shentsize + 16)
        if symtab_off and symtab_entsize:
            n = symtab_size // symtab_entsize
            for i in range(n):
                ent = symtab_off + i * symtab_entsize
                st_name = u32(ent)
                st_info = data[ent + 12]
                st_shndx = u16(ent + 14)
                bind = (st_info >> 4) & 0xF
                typ = st_info & 0xF
                if typ == 2 and st_shndx != 0:  # STT_FUNC, defined
                    sym = data[symstr_off + st_name:].split(b'\x00')[0].decode('ascii', errors='replace')
                    if sym:
                        syms.add(sym)
    except Exception:
        pass
    return syms


def parse_expected_size(stub_path: str, input_obj: str = None) -> int:
    """Read expected .text size from .s stub.

    Sums the primary function size plus:
    - Secondary nonmatching function sizes (only if the symbol is in the compiled .o)
    - Trailing nop words after the last endlabel

    Handles the mixed case where the primary function is matched (no nonmatching
    directive for it) but secondary functions in the same .s file are still
    nonmatching.  In that case the primary size is derived by counting instruction
    comment lines up to the first secondary glabel.
    """
    lines = open(stub_path).readlines()

    # Collect glabel names in order (these are the functions in the file)
    glabels = []
    for line in lines:
        m = re.match(r'\s*glabel\s+(\S+)', line)
        if m:
            glabels.append(m.group(1))

    # Collect nonmatching entries: {name: size}
    nm_map = {}
    for line in lines:
        m = re.match(r'\s*nonmatching\s+(\S+),\s*(0x[0-9A-Fa-f]+|\d+)', line)
        if m:
            nm_map[m.group(1)] = int(m.group(2), 0)

    defined = get_defined_symbols(input_obj) if input_obj else set()

    primary = glabels[0] if glabels else None
    secondaries = glabels[1:] if len(glabels) > 1 else []

    # Determine primary size
    if primary and primary in nm_map:
        # Normal nonmatching: use the declared size
        total = nm_map[primary]
    else:
        # Primary is matched: count its instruction comment lines.
        # Instructions before the first secondary glabel (or end of file).
        inst_pat = re.compile(
            r'/\*\s*[0-9A-Fa-f]{5,6}\s+[0-9A-Fa-f]{8}\s+[0-9A-Fa-f]{8}\s*\*/'
        )
        in_primary = False
        primary_insts = 0
        primary_endlabel = re.compile(r'\s*endlabel\s+' + re.escape(primary)) if primary else None
        for line in lines:
            if primary and re.match(r'\s*glabel\s+' + re.escape(primary), line):
                in_primary = True
                continue
            if in_primary:
                # Stop at the primary function's endlabel (or first secondary glabel)
                if primary_endlabel and primary_endlabel.match(line):
                    break
                if secondaries and any(
                    re.match(r'\s*glabel\s+' + re.escape(s), line) for s in secondaries
                ):
                    break
                if inst_pat.search(line):
                    primary_insts += 1
        total = primary_insts * 4

    # Add secondary nonmatching sizes if the symbol is in the compiled .o
    for sec in secondaries:
        if sec in nm_map and sec in defined:
            total += nm_map[sec]

    # Count trailing nop lines after the last endlabel
    last_end = -1
    for i, line in enumerate(lines):
        if re.match(r'\s*endlabel\s+', line):
            last_end = i
    if last_end >= 0:
        for line in lines[last_end + 1:]:
            if re.search(r'\bnop\b', line) and re.search(r'/\*.*\*/', line):
                total += 4

    if total == 0:
        raise ValueError(f"Could not determine expected size from {stub_path}")

    return total


def patch_elf_text_size(in_path: str, out_path: str, target_size: int):
    """
    Truncate the .text section of an ELF32 big-endian object to target_size.
    """
    with open(in_path, 'rb') as f:
        data = bytearray(f.read())

    if data[:4] != b'\x7fELF':
        raise ValueError(f"{in_path}: not an ELF file")
    if data[4] != 1:
        raise ValueError(f"{in_path}: not ELF32")
    if data[5] != 2:
        raise ValueError(f"{in_path}: not big-endian")

    def u16(off): return struct.unpack_from('>H', data, off)[0]
    def u32(off): return struct.unpack_from('>I', data, off)[0]
    def pu32(off, v): struct.pack_into('>I', data, off, v)

    e_shoff     = u32(32)
    e_shentsize = u16(46)
    e_shnum     = u16(48)
    e_shstrndx  = u16(50)

    strtab_sh_off = e_shoff + e_shstrndx * e_shentsize
    shstrtab_offset = u32(strtab_sh_off + 16)

    for i in range(e_shnum):
        sh_off     = e_shoff + i * e_shentsize
        sh_name    = u32(sh_off + 0)
        sh_type    = u32(sh_off + 4)
        sh_offset  = u32(sh_off + 16)
        sh_size    = u32(sh_off + 20)
        name = data[shstrtab_offset + sh_name:].split(b'\x00')[0].decode('ascii', errors='replace')

        if name == '.text' and sh_type == 1:
            if target_size > sh_size:
                raise ValueError(
                    f".text current size 0x{sh_size:x} < target 0x{target_size:x}"
                )
            if sh_size == target_size:
                import shutil
                shutil.copy2(in_path, out_path)
                return

            for j in range(sh_offset + target_size, sh_offset + sh_size):
                data[j] = 0

            pu32(sh_off + 20, target_size)

            with open(out_path, 'wb') as f:
                f.write(data)
            return

    raise ValueError(f"No .text section found in {in_path}")


def main():
    import argparse
    p = argparse.ArgumentParser(description='Trim IDO .text section padding')
    p.add_argument('input',  help='Input IDO .o file')
    p.add_argument('output', help='Output trimmed .o file')
    group = p.add_mutually_exclusive_group(required=True)
    group.add_argument('stub',   nargs='?', help='.s stub file (reads size from nonmatching line)')
    group.add_argument('--size', type=lambda x: int(x, 0), help='Explicit target size (e.g. 0x24)')
    args = p.parse_args()

    if args.size is not None:
        target = args.size
    else:
        target = parse_expected_size(args.stub, args.input)

    patch_elf_text_size(args.input, args.output, target)
    print(f"Trimmed {args.input}  →  {args.output}  (.text = 0x{target:x} bytes)")


if __name__ == '__main__':
    main()
