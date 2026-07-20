from capstone import *
from capstone.x86 import *
import struct

# Input bytes
code = bytes([ 

0x83, 0xC0, 0x05

 ]);

base_addr = 0x1000;

md = Cs(CS_ARCH_X86, CS_MODE_64);
md.detail = True;

instructions = list(md.disasm(code, base_addr));
addr_to_insn = {insn.address: insn for insn in instructions};
labels = {};
label_counter = 1;

# Track all referenced jump/call targets
referenced_targets = set();

# Get labels for reachable jump/call targets
for insn in instructions:
    if insn.group(X86_GRP_JUMP) or insn.group(X86_GRP_CALL):
        if insn.operands[0].type == X86_OP_IMM:
            target = insn.operands[0].imm;
            referenced_targets.add(target);
            if target in addr_to_insn and target not in labels:
                labels[target] = label_counter;
                label_counter += 1;

# Emit code
for insn in instructions:
    if insn.address in labels:
        print(f"data.emit_label({labels[insn.address]}u); /* LABEL */");

    bytes_str = ', '.join(f'0x{b:02X}' for b in insn.bytes);
    line = f"data.emit({{{bytes_str}}}";

    is_jump = insn.group(X86_GRP_JUMP);
    is_call = insn.group(X86_GRP_CALL);
    is_unconditional = insn.mnemonic == "jmp";

    if (is_jump or is_call) and insn.operands[0].type == X86_OP_IMM:
        target = insn.operands[0].imm;

        if is_call:
            kind = "call_to";
            if target in labels:
                label_id = labels[target];
                line += f", luramas::profile::inst_kind::{kind}, {label_id}u);";
            else:
                line += f", 0x{target & 0xFFFFFFFF:08X}, luramas::profile::inst_kind::{kind});";

        else:
            kind = "jump_to";
            is_conditional = "false" if is_unconditional else "true";
            if target in labels:
                label_id = labels[target];
                line += f", luramas::profile::inst_kind::{kind}, {label_id}u, {is_conditional});";
            else:
                line += f", 0x{target & 0xFFFFFFFF:08X}, luramas::profile::inst_kind::{kind}, {is_conditional});";

    else:
        line += ");";

    line += f" /* {insn.mnemonic} {insn.op_str} */";
    print(line);

# List missing jump/call targets
missing_targets = [t for t in referenced_targets if t not in addr_to_insn];
if missing_targets:
    print("\n/* Missing jump/call targets not in code: */");
    for t in sorted(missing_targets):
        print(f"// 0x{t & 0xFFFFFFFF:08X}");
