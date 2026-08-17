#!/usr/bin/env python3
from capstone import *
from capstone.x86 import *
import re

# Input bytes, paste raw machine code here
code = bytes(
    [
        0x55,
        0x48,
        0x89,
        0xE5,
        0x48,
        0x83,
        0xEC,
        0x20,
        0xC7,
        0x45,
        0xFC,
        0x00,
        0x00,
        0x00,
        0x00,
        0xC7,
        0x45,
        0xF8,
        0x09,
        0x00,
        0x00,
        0x00,
        0xC7,
        0x45,
        0xF4,
        0x00,
        0x00,
        0x00,
        0x00,
        0x81,
        0x7D,
        0xF4,
        0xE8,
        0x03,
        0x00,
        0x00,
        0x7D,
        0x37,
        0x8B,
        0x45,
        0xF4,
        0x89,
        0x45,
        0xE8,
        0x8B,
        0x45,
        0xF4,
        0x35,
        0xAA,
        0x00,
        0x00,
        0x00,
        0x89,
        0x45,
        0xEC,
        0x8B,
        0x45,
        0xF4,
        0x83,
        0xC0,
        0x03,
        0x89,
        0x45,
        0xF0,
        0x48,
        0x8D,
        0x7D,
        0xF8,
        0x48,
        0x8D,
        0x75,
        0xE8,
        0xBA,
        0x13,
        0x00,
        0x00,
        0x00,
        0xE8,
        0x13,
        0x00,
        0x00,
        0x00,
        0x8B,
        0x45,
        0xF4,
        0x83,
        0xC0,
        0x01,
        0x89,
        0x45,
        0xF4,
        0xEB,
        0xC0,
        0x31,
        0xC0,
        0x48,
        0x83,
        0xC4,
        0x20,
        0x5D,
        0xC3,
        0x55,
        0x48,
        0x89,
        0xE5,
        0x48,
        0x89,
        0x7D,
        0xF8,
        0x48,
        0x89,
        0x75,
        0xF0,
        0x89,
        0x55,
        0xEC,
        0xC7,
        0x45,
        0xE8,
        0x00,
        0x00,
        0x00,
        0x00,
        0xC7,
        0x45,
        0xE4,
        0x00,
        0x00,
        0x00,
        0x00,
        0x8B,
        0x45,
        0xEC,
        0x83,
        0xF0,
        0x5A,
        0x48,
        0x8B,
        0x4D,
        0xF0,
        0x8B,
        0x09,
        0xD1,
        0xE1,
        0x01,
        0xC8,
        0x89,
        0x45,
        0xE0,
        0x83,
        0x7D,
        0xE4,
        0x0A,
        0x0F,
        0x8D,
        0x81,
        0x00,
        0x00,
        0x00,
        0x8B,
        0x45,
        0xE0,
        0x6B,
        0x4D,
        0xE4,
        0x03,
        0x31,
        0xC8,
        0x89,
        0x45,
        0xE0,
        0x8B,
        0x45,
        0xE0,
        0x83,
        0xE0,
        0x01,
        0x83,
        0xF8,
        0x00,
        0x75,
        0x1A,
        0x48,
        0x8B,
        0x45,
        0xF8,
        0x48,
        0x63,
        0x4D,
        0xE4,
        0x8B,
        0x04,
        0x88,
        0x48,
        0x8B,
        0x4D,
        0xF0,
        0x03,
        0x41,
        0x04,
        0x03,
        0x45,
        0xE8,
        0x89,
        0x45,
        0xE8,
        0xEB,
        0x18,
        0x48,
        0x8B,
        0x45,
        0xF8,
        0x48,
        0x63,
        0x4D,
        0xE4,
        0x8B,
        0x04,
        0x88,
        0x48,
        0x8B,
        0x4D,
        0xF0,
        0x33,
        0x41,
        0x08,
        0x03,
        0x45,
        0xE8,
        0x89,
        0x45,
        0xE8,
        0x83,
        0x7D,
        0xE8,
        0x64,
        0x7E,
        0x02,
        0xEB,
        0x30,
        0x8B,
        0x45,
        0xE4,
        0x83,
        0xC0,
        0x01,
        0x89,
        0x45,
        0xE4,
        0x8B,
        0x45,
        0xE4,
        0xB9,
        0x03,
        0x00,
        0x00,
        0x00,
        0x99,
        0xF7,
        0xF9,
        0x83,
        0xFA,
        0x00,
        0x75,
        0x02,
        0xEB,
        0x8A,
        0x8B,
        0x45,
        0xE0,
        0xD1,
        0xE0,
        0x8B,
        0x4D,
        0xE0,
        0xC1,
        0xF9,
        0x1F,
        0x09,
        0xC8,
        0x89,
        0x45,
        0xE0,
        0xE9,
        0x75,
        0xFF,
        0xFF,
        0xFF,
        0x8B,
        0x45,
        0xE8,
        0xD1,
        0xE0,
        0x89,
        0x45,
        0xDC,
        0x8B,
        0x45,
        0xDC,
        0x2B,
        0x45,
        0xE8,
        0x89,
        0x45,
        0xDC,
        0x83,
        0x7D,
        0xEC,
        0x00,
        0x7D,
        0x0B,
        0x8B,
        0x45,
        0xDC,
        0x35,
        0xEF,
        0xBE,
        0xAD,
        0xDE,
        0x89,
        0x45,
        0xDC,
        0x8B,
        0x45,
        0xDC,
        0x89,
        0x05,
        0x00,
        0x00,
        0x00,
        0x00,
        0x8B,
        0x45,
        0xE8,
        0x03,
        0x45,
        0xE0,
        0x5D,
        0xC3,
    ]
)

base_addr = 0x0
# Base address

# Indentation of emitted C++
BLOCK_INDENT = " " * 6
BODY_INDENT = " " * 12


md = Cs(CS_ARCH_X86, CS_MODE_64)
md.detail = True

instructions = list(md.disasm(code, base_addr))
addr_to_insn = {insn.address: insn for insn in instructions}


# Description capstone
def desc(insn):
    hex_op_str = re.sub(r"\b\d+\b", lambda m: "0x%x" % int(m.group()), insn.op_str)
    return f"{insn.mnemonic} {hex_op_str}".strip()


# Construct labels
labels = {}
# addr -> "label_XX"
referenced_targets = set()
for insn in instructions:
    if insn.group(X86_GRP_JUMP) or insn.group(X86_GRP_CALL):
        if insn.operands and insn.operands[0].type == X86_OP_IMM:
            target = insn.operands[0].imm
            referenced_targets.add(target)
            if target in addr_to_insn and target not in labels:
                labels[target] = f"label_{target:X}"


# Build sections
data_lines = []
# -> /* Build data */
edge_lines = []
# -> /* Connect Edges */
ret_edges = []
# -> ret edges the user must connect manually
last_label_addr = None

for insn in instructions:

    # Label goes immediately before the instruction at its address
    if insn.address in labels:
        lbl = labels[insn.address]
        data_lines.append(
            (f"const auto {lbl} = *b.emit_label(0x{insn.address:X});", f"{lbl}:")
        )
        last_label_addr = insn.address

    bl = "{" + ", ".join(f"0x{b:02X}" for b in insn.bytes) + "}"
    is_jump = insn.group(X86_GRP_JUMP)
    is_call = insn.group(X86_GRP_CALL)
    is_ret = insn.group(X86_GRP_RET)
    has_imm_target = (
        (is_jump or is_call) and insn.operands and insn.operands[0].type == X86_OP_IMM
    )

    if has_imm_target:

        target = insn.operands[0].imm
        kind = "CALL" if is_call else "JUMP"
        if target in labels:
            # Internal branch: capture the instruction, connect the edge
            lbl = labels[target]
            var = f"i_{insn.mnemonic}_{target:x}_rpc"
            insn_desc = (
                f"{insn.mnemonic} {target:x}" if is_call else f"{insn.mnemonic} {lbl}"
            )
            data_lines.append(
                (
                    f"const auto {var} = b.emitd({bl}, edges{{{{0x{target:X}, edges_k::next}}}}, {kind}).first;",
                    insn_desc,
                )
            )
            edge_lines.append(
                (
                    f"b.connect_edge<edges_k::next>({lbl}, {var});",
                    f"{insn_desc} -> {lbl}",
                )
            )
        else:
            # External branch: record the address, no edge
            data_lines.append(
                (
                    f"external_addresses[b.emitd({bl}, std::nullopt, {kind}).first].insert(0x{target:x});",
                    f"{insn.mnemonic} {target:x} [EXTERNAL]",
                )
            )
            data_lines.append(
                (
                    f"external_addrs.insert(0x{target:x});",
                    f"External: 0x{target:x}",
                )
            )

    elif is_ret:

        # ret has a next-edge back to the start of its block
        if last_label_addr is not None:
            lbl = labels.get(last_label_addr, f"label_{last_label_addr:X}")
            var = f"i_retn_{last_label_addr:x}_rpc"
            data_lines.append(
                (
                    f"const auto {var} = b.emitd({bl}, edges{{{{0x{last_label_addr:X}, edges_k::next}}}}, RETN).first;",
                    desc(insn),
                )
            )
            # Do NOT auto-connect ret edges, leave it for the user to wire up
            ret_edges.append((lbl, var, desc(insn)))
        else:
            data_lines.append((f"b.emitd({bl}, std::nullopt, RETN);", desc(insn)))

    elif is_jump or is_call:
        # Indirect branch: tag the kind, no edge. (USERED HANDLED)
        kind = "CALL" if is_call else "JUMP"
        data_lines.append((f"b.emitd({bl}, std::nullopt, {kind});", desc(insn)))
    else:
        data_lines.append((f"b.emitd({bl});", desc(insn)))


# Emit, aligning each section trailing comments to one column
def render(lines, indent):
    if not lines:
        return []
    width = max(len(indent + c) for c, _ in lines)
    out = []
    for c, comment in lines:
        full = indent + c
        out.append(f"{full}{' ' * (width - len(full) + 1)}/* {comment} */")
    return out


print(f"{BLOCK_INDENT}/* Build assembly */")
print(f"{BLOCK_INDENT}{{")
print(f"{BODY_INDENT}/* Build data */")
for ln in render(data_lines, BODY_INDENT):
    print(ln)
if edge_lines:
    print(f"{BODY_INDENT}/* Connect Edges */")
    for ln in render(edge_lines, BODY_INDENT):
        print(ln)
print(f"{BLOCK_INDENT}}}")

# Return edges manually connected
if ret_edges:
    print(f"\n/* Connect these ret edges manually: */")
    for lbl, var, d in ret_edges:
        print(f"// b.connect_edge<edges_k::next>({lbl}, {var});   /* {d} -> {lbl} */")

# Output
missing = [t for t in referenced_targets if t not in addr_to_insn]
if missing:
    print("\n/* Missing jump/call targets not in code: */")
    for t in sorted(missing):
        print(f"// 0x{t:x}")
