#include "disassembler.hpp"
#include "optable.hpp"

enum class set_action : std::uint8_t {
      instruction, /* Sets all instruction info, op, mnenomic, hint. */
      operands     /* Sets all operands including details about it. */
};

template <set_action n>
void set_data(std::shared_ptr<luramas::disassembler::CIL::disassembly> &buffer) {

      switch (n) {

            case set_action::instruction: {

                  // TODO ADD OPTABLE INDEXING

                  switch (buffer->op) {
                        case luramas::disassembler::CIL::optable::data::instructions::OP_ADD: {
                              buffer->mnenomic = "add";
                              buffer->hint = "Add two values, returning a new value. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_ADD_OVF: {
                              buffer->mnenomic = "add_ovf";
                              buffer->hint = "Add signed integer values with overflow check. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_ADD_OVF_UN: {
                              buffer->mnenomic = "add_ovf_un";
                              buffer->hint = "Add unsigned integer values with overflow check. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_AND: {
                              buffer->mnenomic = "and";
                              buffer->hint = "Bitwise AND of two integral values, returns an integral value. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_ARGLIST: {
                              buffer->mnenomic = "arglist";
                              buffer->hint = "Return argument list handle for the current method. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_BEQ: {
                              buffer->mnenomic = "beq";
                              buffer->hint = "<int32 (target)> Branch to target if equal. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_BEQ_S: {
                              buffer->mnenomic = "beq_s";
                              buffer->hint = "<int8 (target)> Branch to target if equal, short form. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_BGE: {
                              buffer->mnenomic = "bge";
                              buffer->hint = "<int32 (target)> Branch to target if greater than or equal to. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_BGE_S: {
                              buffer->mnenomic = "bge_s";
                              buffer->hint = "<int8 (target)> Branch to target if greater than or equal to, short form. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_BGE_UN: {
                              buffer->mnenomic = "bge_un";
                              buffer->hint = "<int32 (target)> Branch to target if greater than or equal to (unsigned or unordered). Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_BGE_UN_S: {
                              buffer->mnenomic = "bge_un_s";
                              buffer->hint = "<int8 (target)> Branch to target if greater than or equal to (unsigned or unordered), short form. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_BGT: {
                              buffer->mnenomic = "bgt";
                              buffer->hint = "<int32 (target)> Branch to target if greater than. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_BGT_S: {
                              buffer->mnenomic = "bgt_s";
                              buffer->hint = "<int8 (target)> Branch to target if greater than, short form. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_BGT_UN: {
                              buffer->mnenomic = "bgt_un";
                              buffer->hint = "<int32 (target)> Branch to target if greater than (unsigned or unordered). Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_BGT_UN_S: {
                              buffer->mnenomic = "bgt_un_s";
                              buffer->hint = "<int8 (target)> Branch to target if greater than (unsigned or unordered), short form. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_BLE: {
                              buffer->mnenomic = "ble";
                              buffer->hint = "<int32 (target)> Branch to target if less than or equal to. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_BLE_S: {
                              buffer->mnenomic = "ble_s";
                              buffer->hint = "<int8 (target)> Branch to target if less than or equal to, short form. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_BLE_UN: {
                              buffer->mnenomic = "ble_un";
                              buffer->hint = "<int32 (target)> Branch to target if less than or equal to (unsigned or unordered). Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_BLE_UN_S: {
                              buffer->mnenomic = "ble_un_s";
                              buffer->hint = "<int8 (target)> Branch to target if less than or equal to (unsigned or unordered), short form. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_BLT: {
                              buffer->mnenomic = "blt";
                              buffer->hint = "<int32 (target)> Branch to target if less than. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_BLT_S: {
                              buffer->mnenomic = "blt_s";
                              buffer->hint = "<int8 (target)> Branch to target if less than, short form. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_BLT_UN: {
                              buffer->mnenomic = "blt_un";
                              buffer->hint = "<int32 (target)> Branch to target if less than (unsigned or unordered). Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_BLT_UN_S: {
                              buffer->mnenomic = "blt_un_s";
                              buffer->hint = "<int8 (target)> Branch to target if less than (unsigned or unordered), short form. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_BNE_UN: {
                              buffer->mnenomic = "bne_un";
                              buffer->hint = "<int32 (target)> Branch to target if unequal or unordered. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_BNE_UN_S: {
                              buffer->mnenomic = "bne_un_s";
                              buffer->hint = "<int8 (target)> Branch to target if unequal or unordered, short form. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_BOX: {
                              buffer->mnenomic = "box";
                              buffer->hint = "<typeTok> Convert a boxable value to its boxed form. Object model instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_BR: {
                              buffer->mnenomic = "br";
                              buffer->hint = "<int32 (target)> Branch to target. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_BR_S: {
                              buffer->mnenomic = "br_s";
                              buffer->hint = "<int8 (target)> Branch to target, short form. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_BREAK: {
                              buffer->mnenomic = "break";
                              buffer->hint = "Inform a debugger that a breakpoint has been reached. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_BRFALSE: {
                              buffer->mnenomic = "brfalse";
                              buffer->hint = "<int32 (target)> Branch to target if value is zero (false). Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_BRFALSE_S: {
                              buffer->mnenomic = "brfalse_s";
                              buffer->hint = "<int8 (target)> Branch to target if value is zero (false), short form. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_BRINST: {
                              buffer->mnenomic = "brinst";
                              buffer->hint = "<int32 (target)> Branch to target if value is a non-null object reference (alias for brtrue). Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_BRINST_S: {
                              buffer->mnenomic = "brinst_s";
                              buffer->hint = "<int8 (target)> Branch to target if value is a non-null object reference, short form (alias for brtrue.s). Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_BRNULL: {
                              buffer->mnenomic = "brnull";
                              buffer->hint = "<int32 (target)> Branch to target if value is null (alias for brfalse). Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_BRNULL_S: {
                              buffer->mnenomic = "brnull_s";
                              buffer->hint = "<int8 (target)> Branch to target if value is null (alias for brfalse.s), short form. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_BRTRUE: {
                              buffer->mnenomic = "brtrue";
                              buffer->hint = "<int32 (target)> Branch to target if value is non-zero (true). Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_BRTRUE_S: {
                              buffer->mnenomic = "brtrue_s";
                              buffer->hint = "<int8 (target)> Branch to target if value is non-zero (true), short form. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_BRZERO: {
                              buffer->mnenomic = "brzero";
                              buffer->hint = "<int32 (target)> Branch to target if value is zero (alias for brfalse). Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_BRZERO_S: {
                              buffer->mnenomic = "brzero_s";
                              buffer->hint = "<int8 (target)> Branch to target if value is zero (alias for brfalse.s), short form. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_CALL: {
                              buffer->mnenomic = "call";
                              buffer->hint = "<method> Call method described by method. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_CALLI: {
                              buffer->mnenomic = "calli";
                              buffer->hint = "<callsitedescr> Call method indicated on the stack with arguments described by callsitedescr. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_CALLVIRT: {
                              buffer->mnenomic = "callvirt";
                              buffer->hint = "<method> Call a method associated with an object. Object model instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_CASTCLASS: {
                              buffer->mnenomic = "castclass";
                              buffer->hint = "<class> Cast obj to class. Object model instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_CEQ: {
                              buffer->mnenomic = "ceq";
                              buffer->hint = "Push 1 (of type int32) if value1 equals value2, else push 0. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_CGT: {
                              buffer->mnenomic = "cgt";
                              buffer->hint = "Push 1 (of type int32) if value1 greater than value2, else push 0. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_CGT_UN: {
                              buffer->mnenomic = "cgt_un";
                              buffer->hint = "Push 1 (of type int32) if value1 greater than value2, unsigned or unordered, else push 0. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_CKFINITE: {
                              buffer->mnenomic = "ckfinite";
                              buffer->hint = "Throw ArithmeticException if value is not a finite number. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_CLT: {
                              buffer->mnenomic = "clt";
                              buffer->hint = "Push 1 (of type int32) if value1 lower than value2, else push 0. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_CLT_UN: {
                              buffer->mnenomic = "clt_un";
                              buffer->hint = "Push 1 (of type int32) if value1 lower than value2, unsigned or unordered, else push 0. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_CONSTRAINED_: {
                              buffer->mnenomic = "constrained_";
                              buffer->hint = "<thisType> Call a virtual method on a type constrained to be type T. Prefix to instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_CONV_I: {
                              buffer->mnenomic = "conv_i";
                              buffer->hint = "Convert to native int, pushing native int on stack. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_CONV_I1: {
                              buffer->mnenomic = "conv_i1";
                              buffer->hint = "Convert to int8, pushing int32 on stack. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_CONV_I2: {
                              buffer->mnenomic = "conv_i2";
                              buffer->hint = "Convert to int16, pushing int32 on stack. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_CONV_I4: {
                              buffer->mnenomic = "conv_i4";
                              buffer->hint = "Convert to int32, pushing int32 on stack. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_CONV_I8: {
                              buffer->mnenomic = "conv_i8";
                              buffer->hint = "Convert to int64, pushing int64 on stack. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_CONV_OVF_I: {
                              buffer->mnenomic = "conv_ovf_i";
                              buffer->hint = "Convert to a native int (on the stack as native int) and throw an exception on overflow. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_CONV_OVF_I_UN: {
                              buffer->mnenomic = "conv_ovf_i_un";
                              buffer->hint = "Convert unsigned to a native int (on the stack as native int) and throw an exception on overflow. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_CONV_OVF_I1: {
                              buffer->mnenomic = "conv_ovf_i1";
                              buffer->hint = "Convert to an int8 (on the stack as int32) and throw an exception on overflow. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_CONV_OVF_I1_UN: {
                              buffer->mnenomic = "conv_ovf_i1_un";
                              buffer->hint = "Convert unsigned to an int8 (on the stack as int32) and throw an exception on overflow. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_CONV_OVF_I2: {
                              buffer->mnenomic = "conv_ovf_i2";
                              buffer->hint = "Convert to an int16 (on the stack as int32) and throw an exception on overflow. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_CONV_OVF_I2_UN: {
                              buffer->mnenomic = "conv_ovf_i2_un";
                              buffer->hint = "Convert unsigned to an int16 (on the stack as int32) and throw an exception on overflow. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_CONV_OVF_I4: {
                              buffer->mnenomic = "conv_ovf_i4";
                              buffer->hint = "Convert to an int32 (on the stack as int32) and throw an exception on overflow. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_CONV_OVF_I4_UN: {
                              buffer->mnenomic = "conv_ovf_i4_un";
                              buffer->hint = "Convert unsigned to an int32 (on the stack as int32) and throw an exception on overflow. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_CONV_OVF_I8: {
                              buffer->mnenomic = "conv_ovf_i8";
                              buffer->hint = "Convert to an int64 (on the stack as int64) and throw an exception on overflow. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_CONV_OVF_I8_UN: {
                              buffer->mnenomic = "conv_ovf_i8_un";
                              buffer->hint = "Convert unsigned to an int64 (on the stack as int64) and throw an exception on overflow. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_CONV_OVF_U: {
                              buffer->mnenomic = "conv_ovf_u";
                              buffer->hint = "Convert to a native unsigned int (on the stack as native int) and throw an exception on overflow. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_CONV_OVF_U_UN: {
                              buffer->mnenomic = "conv_ovf_u_un";
                              buffer->hint = "Convert unsigned to a native unsigned int (on the stack as native int) and throw an exception on overflow. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_CONV_OVF_U1: {
                              buffer->mnenomic = "conv_ovf_u1";
                              buffer->hint = "Convert to an unsigned int8 (on the stack as int32) and throw an exception on overflow. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_CONV_OVF_U1_UN: {
                              buffer->mnenomic = "conv_ovf_u1_un";
                              buffer->hint = "Convert unsigned to an unsigned int8 (on the stack as int32) and throw an exception on overflow. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_CONV_OVF_U2: {
                              buffer->mnenomic = "conv_ovf_u2";
                              buffer->hint = "Convert to an unsigned int16 (on the stack as int32) and throw an exception on overflow. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_CONV_OVF_U2_UN: {
                              buffer->mnenomic = "conv_ovf_u2_un";
                              buffer->hint = "Convert unsigned to an unsigned int16 (on the stack as int32) and throw an exception on overflow. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_CONV_OVF_U4: {
                              buffer->mnenomic = "conv_ovf_u4";
                              buffer->hint = "Convert to an unsigned int32 (on the stack as int32) and throw an exception on overflow. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_CONV_OVF_U4_UN: {
                              buffer->mnenomic = "conv_ovf_u4_un";
                              buffer->hint = "Convert unsigned to an unsigned int32 (on the stack as int32) and throw an exception on overflow. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_CONV_OVF_U8: {
                              buffer->mnenomic = "conv_ovf_u8";
                              buffer->hint = "Convert to an unsigned int64 (on the stack as int64) and throw an exception on overflow. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_CONV_OVF_U8_UN: {
                              buffer->mnenomic = "conv_ovf_u8_un";
                              buffer->hint = "Convert unsigned to an unsigned int64 (on the stack as int64) and throw an exception on overflow. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_CONV_R_UN: {
                              buffer->mnenomic = "conv_r_un";
                              buffer->hint = "Convert unsigned integer to floating-point, pushing F on stack. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_CONV_R4: {
                              buffer->mnenomic = "conv_r4";
                              buffer->hint = "Convert to float32, pushing F on stack. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_CONV_R8: {
                              buffer->mnenomic = "conv_r8";
                              buffer->hint = "Convert to float64, pushing F on stack. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_CONV_U: {
                              buffer->mnenomic = "conv_u";
                              buffer->hint = "Convert to native unsigned int, pushing native int on stack. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_CONV_U1: {
                              buffer->mnenomic = "conv_u1";
                              buffer->hint = "Convert to unsigned int8, pushing int32 on stack. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_CONV_U2: {
                              buffer->mnenomic = "conv_u2";
                              buffer->hint = "Convert to unsigned int16, pushing int32 on stack. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_CONV_U4: {
                              buffer->mnenomic = "conv_u4";
                              buffer->hint = "Convert to unsigned int32, pushing int32 on stack. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_CONV_U8: {
                              buffer->mnenomic = "conv_u8";
                              buffer->hint = "Convert to unsigned int64, pushing int64 on stack. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_CPBLK: {
                              buffer->mnenomic = "cpblk";
                              buffer->hint = "Copy data from memory to memory. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_CPOBJ: {
                              buffer->mnenomic = "cpobj";
                              buffer->hint = "<typeTok> Copy a value type from src to dest. Object model instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_DIV: {
                              buffer->mnenomic = "div";
                              buffer->hint = "Divide two values to return a quotient or floating-point result. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_DIV_UN: {
                              buffer->mnenomic = "div_un";
                              buffer->hint = "Divide two values, unsigned, returning a quotient. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_DUP: {
                              buffer->mnenomic = "dup";
                              buffer->hint = "Duplicate the value on the top of the stack. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_ENDFAULT: {
                              buffer->mnenomic = "endfault";
                              buffer->hint = "End fault clause of an exception block. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_ENDFILTER: {
                              buffer->mnenomic = "endfilter";
                              buffer->hint = "End an exception handling filter clause. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_ENDFINALLY: {
                              buffer->mnenomic = "endfinally";
                              buffer->hint = "End finally clause of an exception block. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_INITBLK: {
                              buffer->mnenomic = "initblk";
                              buffer->hint = "Set all bytes in a block of memory to a given byte value. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_INITOBJ: {
                              buffer->mnenomic = "initobj";
                              buffer->hint = "<typeTok> Initialize the value at address dest. Object model instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_ISINST: {
                              buffer->mnenomic = "isinst";
                              buffer->hint = "<class> Test if obj is an instance of class, returning null or an instance of that class or interface. Object model instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_JMP: {
                              buffer->mnenomic = "jmp";
                              buffer->hint = "<method> Exit current method and jump to the specified method. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_LDARG: {
                              buffer->mnenomic = "ldarg";
                              buffer->hint = "<uint16 (num)> Load argument numbered num onto the stack. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_LDARG_0: {
                              buffer->mnenomic = "ldarg_0";
                              buffer->hint = "Load argument 0 onto the stack. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_LDARG_1: {
                              buffer->mnenomic = "ldarg_1";
                              buffer->hint = "Load argument 1 onto the stack. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_LDARG_2: {
                              buffer->mnenomic = "ldarg_2";
                              buffer->hint = "Load argument 2 onto the stack. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_LDARG_3: {
                              buffer->mnenomic = "ldarg_3";
                              buffer->hint = "Load argument 3 onto the stack. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_LDARG_S: {
                              buffer->mnenomic = "ldarg_s";
                              buffer->hint = "<uint8 (num)> Load argument numbered num onto the stack, short form. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_LDARGA: {
                              buffer->mnenomic = "ldarga";
                              buffer->hint = "<uint16 (argNum)> Fetch the address of argument argNum. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_LDARGA_S: {
                              buffer->mnenomic = "ldarga_s";
                              buffer->hint = "<uint8 (argNum)> Fetch the address of argument argNum, short form. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_LDC_I4: {
                              buffer->mnenomic = "ldc_i4";
                              buffer->hint = "<int32 (num)> Push num of type int32 onto the stack as int32. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_LDC_I4_0: {
                              buffer->mnenomic = "ldc_i4_0";
                              buffer->hint = "Push 0 onto the stack as int32. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_LDC_I4_1: {
                              buffer->mnenomic = "ldc_i4_1";
                              buffer->hint = "Push 1 onto the stack as int32. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_LDC_I4_2: {
                              buffer->mnenomic = "ldc_i4_2";
                              buffer->hint = "Push 2 onto the stack as int32. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_LDC_I4_3: {
                              buffer->mnenomic = "ldc_i4_3";
                              buffer->hint = "Push 3 onto the stack as int32. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_LDC_I4_4: {
                              buffer->mnenomic = "ldc_i4_4";
                              buffer->hint = "Push 4 onto the stack as int32. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_LDC_I4_5: {
                              buffer->mnenomic = "ldc_i4_5";
                              buffer->hint = "Push 5 onto the stack as int32. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_LDC_I4_6: {
                              buffer->mnenomic = "ldc_i4_6";
                              buffer->hint = "Push 6 onto the stack as int32. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_LDC_I4_7: {
                              buffer->mnenomic = "ldc_i4_7";
                              buffer->hint = "Push 7 onto the stack as int32. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_LDC_I4_8: {
                              buffer->mnenomic = "ldc_i4_8";
                              buffer->hint = "Push 8 onto the stack as int32. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_LDC_I4_M1_I32: {
                              buffer->mnenomic = "ldc_i4_m1_i32";
                              buffer->hint = "Push -1 onto the stack as int32. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_LDC_I4_M1: {
                              buffer->mnenomic = "ldc_i4_m1";
                              buffer->hint = "Push -1 onto the stack as int32 (alias for ldc.i4.m1). Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_LDC_I4_S: {
                              buffer->mnenomic = "ldc_i4_s";
                              buffer->hint = "<int8 (num)> Push num onto the stack as int32, short form. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_LDC_I8: {
                              buffer->mnenomic = "ldc_i8";
                              buffer->hint = "<int64 (num)> Push num of type int64 onto the stack as int64. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_LDC_R4: {
                              buffer->mnenomic = "ldc_r4";
                              buffer->hint = "<float32 (num)> Push num of type float32 onto the stack as F. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_LDC_R8: {
                              buffer->mnenomic = "ldc_r8";
                              buffer->hint = "<float64 (num)> Push num of type float64 onto the stack as F. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_LDELEM: {
                              buffer->mnenomic = "ldelem";
                              buffer->hint = "<typeTok> Load the element at index onto the top of the stack. Object model instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_LDELEM_I: {
                              buffer->mnenomic = "ldelem_i";
                              buffer->hint = "Load the element with type native int at index onto the top of the stack as a native int. Object model instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_LDELEM_I1: {
                              buffer->mnenomic = "ldelem_i1";
                              buffer->hint = "Load the element with type int8 at index onto the top of the stack as an int32. Object model instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_LDELEM_I2: {
                              buffer->mnenomic = "ldelem_i2";
                              buffer->hint = "Load the element with type int16 at index onto the top of the stack as an int32. Object model instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_LDELEM_I4: {
                              buffer->mnenomic = "ldelem_i4";
                              buffer->hint = "Load the element with type int32 at index onto the top of the stack as an int32. Object model instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_LDELEM_I8: {
                              buffer->mnenomic = "ldelem_i8";
                              buffer->hint = "Load the element with type int64 at index onto the top of the stack as an int64. Object model instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_LDELEM_R4: {
                              buffer->mnenomic = "ldelem_r4";
                              buffer->hint = "Load the element with type float32 at index onto the top of the stack as an F. Object model instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_LDELEM_R8: {
                              buffer->mnenomic = "ldelem_r8";
                              buffer->hint = "Load the element with type float64 at index onto the top of the stack as an F. Object model instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_LDELEM_REF: {
                              buffer->mnenomic = "ldelem_ref";
                              buffer->hint = "Load the element at index onto the top of the stack as an O. The type of the O is the same as the element type of the array pushed on the CIL stack. Object model instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_LDELEM_U1: {
                              buffer->mnenomic = "ldelem_u1";
                              buffer->hint = "Load the element with type unsigned int8 at index onto the top of the stack as an int32. Object model instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_LDELEM_U2: {
                              buffer->mnenomic = "ldelem_u2";
                              buffer->hint = "Load the element with type unsigned int16 at index onto the top of the stack as an int32. Object model instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_LDELEM_U4: {
                              buffer->mnenomic = "ldelem_u4";
                              buffer->hint = "Load the element with type unsigned int32 at index onto the top of the stack as an int32. Object model instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_LDELEM_U8: {
                              buffer->mnenomic = "ldelem_u8";
                              buffer->hint = "Load the element with type unsigned int64 at index onto the top of the stack as an int64 (alias for ldelem.i8). Object model instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_LDELEMA: {
                              buffer->mnenomic = "ldelema";
                              buffer->hint = "<class> Load the address of element at index onto the top of the stack. Object model instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_LDFLD: {
                              buffer->mnenomic = "ldfld";
                              buffer->hint = "<field> Push the value of field of object (or value type) obj, onto the stack. Object model instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_LDFLDA: {
                              buffer->mnenomic = "ldflda";
                              buffer->hint = "<field> Push the address of field of object obj on the stack. Object model instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_LDFTN: {
                              buffer->mnenomic = "ldftn";
                              buffer->hint = "<method> Push a pointer to a method referenced by method, on the stack. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_LDIND_I: {
                              buffer->mnenomic = "ldind_i";
                              buffer->hint = "Indirect load value of type native int as native int on the stack. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_LDIND_I1: {
                              buffer->mnenomic = "ldind_i1";
                              buffer->hint = "Indirect load value of type int8 as int32 on the stack. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_LDIND_I2: {
                              buffer->mnenomic = "ldind_i2";
                              buffer->hint = "Indirect load value of type int16 as int32 on the stack. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_LDIND_I4: {
                              buffer->mnenomic = "ldind_i4";
                              buffer->hint = "Indirect load value of type int32 as int32 on the stack. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_LDIND_I8: {
                              buffer->mnenomic = "ldind_i8";
                              buffer->hint = "Indirect load value of type int64 as int64 on the stack. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_LDIND_R4: {
                              buffer->mnenomic = "ldind_r4";
                              buffer->hint = "Indirect load value of type float32 as F on the stack. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_LDIND_R8: {
                              buffer->mnenomic = "ldind_r8";
                              buffer->hint = "Indirect load value of type float64 as F on the stack. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_LDIND_REF: {
                              buffer->mnenomic = "ldind_ref";
                              buffer->hint = "Indirect load value of type object ref as O on the stack. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_LDIND_U1: {
                              buffer->mnenomic = "ldind_u1";
                              buffer->hint = "Indirect load value of type unsigned int8 as int32 on the stack. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_LDIND_U2: {
                              buffer->mnenomic = "ldind_u2";
                              buffer->hint = "Indirect load value of type unsigned int16 as int32 on the stack. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_LDIND_U4: {
                              buffer->mnenomic = "ldind_u4";
                              buffer->hint = "Indirect load value of type unsigned int32 as int32 on the stack. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_LDIND_U8: {
                              buffer->mnenomic = "ldind_u8";
                              buffer->hint = "Indirect load value of type unsigned int64 as int64 on the stack (alias for ldind.i8). Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_LDLEN: {
                              buffer->mnenomic = "ldlen";
                              buffer->hint = "Push the length (of type native unsigned int) of array on the stack. Object model instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_LDLOC: {
                              buffer->mnenomic = "ldloc";
                              buffer->hint = "<uint16 (indx)> Load local variable of index indx onto stack. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_LDLOC_0: {
                              buffer->mnenomic = "ldloc_0";
                              buffer->hint = "Load local variable 0 onto stack. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_LDLOC_1: {
                              buffer->mnenomic = "ldloc_1";
                              buffer->hint = "Load local variable 1 onto stack. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_LDLOC_2: {
                              buffer->mnenomic = "ldloc_2";
                              buffer->hint = "Load local variable 2 onto stack. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_LDLOC_3: {
                              buffer->mnenomic = "ldloc_3";
                              buffer->hint = "Load local variable 3 onto stack. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_LDLOC_S: {
                              buffer->mnenomic = "ldloc_s";
                              buffer->hint = "<uint8 (indx)> Load local variable of index indx onto stack, short form. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_LDLOCA: {
                              buffer->mnenomic = "ldloca";
                              buffer->hint = "<uint16 (indx)> Load address of local variable with index indx. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_LDLOCA_S: {
                              buffer->mnenomic = "ldloca_s";
                              buffer->hint = "<uint8 (indx)> Load address of local variable with index indx, short form. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_LDNULL: {
                              buffer->mnenomic = "ldnull";
                              buffer->hint = "Push a null reference on the stack. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_LDOBJ: {
                              buffer->mnenomic = "ldobj";
                              buffer->hint = "<typeTok> Copy the value stored at address src to the stack. Object model instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_LDSFLD: {
                              buffer->mnenomic = "ldsfld";
                              buffer->hint = "<field> Push the value of the static field on the stack. Object model instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_LDSFLDA: {
                              buffer->mnenomic = "ldsflda";
                              buffer->hint = "<field> Push the address of the static field, field, on the stack. Object model instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_LDSTR: {
                              buffer->mnenomic = "ldstr";
                              buffer->hint = "<string> Push a string object for the literal string. Object model instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_LDTOKEN: {
                              buffer->mnenomic = "ldtoken";
                              buffer->hint = "<token> Convert metadata token to its runtime representation. Object model instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_LDVIRTFTN: {
                              buffer->mnenomic = "ldvirtftn";
                              buffer->hint = "<method> Push address of virtual method on the stack. Object model instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_LEAVE: {
                              buffer->mnenomic = "leave";
                              buffer->hint = "<int32 (target)> Exit a protected region of code. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_LEAVE_S: {
                              buffer->mnenomic = "leave_s";
                              buffer->hint = "<int8 (target)> Exit a protected region of code, short form. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_LOCALLOC: {
                              buffer->mnenomic = "localloc";
                              buffer->hint = "Allocate space from the local memory pool. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_MKREFANY: {
                              buffer->mnenomic = "mkrefany";
                              buffer->hint = "<class> Push a typed reference to ptr of type class onto the stack. Object model instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_MUL: {
                              buffer->mnenomic = "mul";
                              buffer->hint = "Multiply values. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_MUL_OVF: {
                              buffer->mnenomic = "mul_ovf";
                              buffer->hint = "Multiply signed integer values. Signed result shall fit in same size. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_MUL_OVF_UN: {
                              buffer->mnenomic = "mul_ovf_un";
                              buffer->hint = "Multiply unsigned integer values. Unsigned result shall fit in same size. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_NEG: {
                              buffer->mnenomic = "neg";
                              buffer->hint = "Negate value. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_NEWARR: {
                              buffer->mnenomic = "newarr";
                              buffer->hint = "<etype> Create a new array with elements of type etype. Object model instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_NEWOBJ: {
                              buffer->mnenomic = "newobj";
                              buffer->hint = "<ctor> Allocate an uninitialized object or value type and call ctor. Object model instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_NOP: {
                              buffer->mnenomic = "nop";
                              buffer->hint = "Do nothing (No operation). Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_NOT: {
                              buffer->mnenomic = "not";
                              buffer->hint = "Bitwise complement. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_OR: {
                              buffer->mnenomic = "or";
                              buffer->hint = "Bitwise OR of two integer values, returns an integer. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_POP: {
                              buffer->mnenomic = "pop";
                              buffer->hint = "Pop value from the stack. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_READONLY_: {
                              buffer->mnenomic = "readonly_";
                              buffer->hint = "Specify that the subsequent array address operation performs no type check at runtime, and that it returns a controlled-mutability managed pointer. Prefix to instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_REFANYTYPE: {
                              buffer->mnenomic = "refanytype";
                              buffer->hint = "Push the type token stored in a typed reference. Object model instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_REFANYVAL: {
                              buffer->mnenomic = "refanyval";
                              buffer->hint = "<type> Push the address stored in a typed reference. Object model instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_REM: {
                              buffer->mnenomic = "rem";
                              buffer->hint = "Remainder when dividing one value by another. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_REM_UN: {
                              buffer->mnenomic = "rem_un";
                              buffer->hint = "Remainder when dividing one unsigned value by another. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_RET: {
                              buffer->mnenomic = "ret";
                              buffer->hint = "Return from method, possibly with a value. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_RETHROW: {
                              buffer->mnenomic = "rethrow";
                              buffer->hint = "Rethrow the current exception. Object model instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_SHL: {
                              buffer->mnenomic = "shl";
                              buffer->hint = "Shift an integer left (shifting in zeros), return an integer. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_SHR: {
                              buffer->mnenomic = "shr";
                              buffer->hint = "Shift an integer right (shift in sign), return an integer. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_SHR_UN: {
                              buffer->mnenomic = "shr_un";
                              buffer->hint = "Shift an integer right (shift in zero), return an integer. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_SIZEOF: {
                              buffer->mnenomic = "sizeof";
                              buffer->hint = "<typeTok> Push the size, in bytes, of a type as an unsigned int32. Object model instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_STARG: {
                              buffer->mnenomic = "starg";
                              buffer->hint = "<uint16 (num)> Store value to the argument numbered num. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_STARG_S: {
                              buffer->mnenomic = "starg_s";
                              buffer->hint = "<uint8 (num)> Store value to the argument numbered num, short form. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_STELEM: {
                              buffer->mnenomic = "stelem";
                              buffer->hint = "<typeTok> Replace array element at index with the value on the stack. Object model instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_STELEM_I: {
                              buffer->mnenomic = "stelem_i";
                              buffer->hint = "Replace array element at index with the native int value on the stack. Object model instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_STELEM_I1: {
                              buffer->mnenomic = "stelem_i1";
                              buffer->hint = "Replace array element at index with the int8 value on the stack. Object model instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_STELEM_I2: {
                              buffer->mnenomic = "stelem_i2";
                              buffer->hint = "Replace array element at index with the int16 value on the stack. Object model instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_STELEM_I4: {
                              buffer->mnenomic = "stelem_i4";
                              buffer->hint = "Replace array element at index with the int32 value on the stack. Object model instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_STELEM_I8: {
                              buffer->mnenomic = "stelem_i8";
                              buffer->hint = "Replace array element at index with the int64 value on the stack. Object model instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_STELEM_R4: {
                              buffer->mnenomic = "stelem_r4";
                              buffer->hint = "Replace array element at index with the float32 value on the stack. Object model instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_STELEM_R8: {
                              buffer->mnenomic = "stelem_r8";
                              buffer->hint = "Replace array element at index with the float64 value on the stack. Object model instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_STELEM_REF: {
                              buffer->mnenomic = "stelem_ref";
                              buffer->hint = "Replace array element at index with the ref value on the stack. Object model instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_STFLD: {
                              buffer->mnenomic = "stfld";
                              buffer->hint = "<field> Replace the value of field of the object obj with value. Object model instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_STIND_I: {
                              buffer->mnenomic = "stind_i";
                              buffer->hint = "Store value of type native int into memory at address. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_STIND_I1: {
                              buffer->mnenomic = "stind_i1";
                              buffer->hint = "Store value of type int8 into memory at address. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_STIND_I2: {
                              buffer->mnenomic = "stind_i2";
                              buffer->hint = "Store value of type int16 into memory at address. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_STIND_I4: {
                              buffer->mnenomic = "stind_i4";
                              buffer->hint = "Store value of type int32 into memory at address. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_STIND_I8: {
                              buffer->mnenomic = "stind_i8";
                              buffer->hint = "Store value of type int64 into memory at address. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_STIND_R4: {
                              buffer->mnenomic = "stind_r4";
                              buffer->hint = "Store value of type float32 into memory at address. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_STIND_R8: {
                              buffer->mnenomic = "stind_r8";
                              buffer->hint = "Store value of type float64 into memory at address. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_STIND_REF: {
                              buffer->mnenomic = "stind_ref";
                              buffer->hint = "Store value of type object ref (type O) into memory at address. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_STLOC: {
                              buffer->mnenomic = "stloc";
                              buffer->hint = "<uint16 (indx)> Pop a value from stack into local variable indx. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_STLOC_0: {
                              buffer->mnenomic = "stloc_0";
                              buffer->hint = "Pop a value from stack into local variable 0. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_STLOC_1: {
                              buffer->mnenomic = "stloc_1";
                              buffer->hint = "Pop a value from stack into local variable 1. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_STLOC_2: {
                              buffer->mnenomic = "stloc_2";
                              buffer->hint = "Pop a value from stack into local variable 2. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_STLOC_3: {
                              buffer->mnenomic = "stloc_3";
                              buffer->hint = "Pop a value from stack into local variable 3. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_STLOC_S: {
                              buffer->mnenomic = "stloc_s";
                              buffer->hint = "<uint8 (indx)> Pop a value from stack into local variable indx, short form. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_STOBJ: {
                              buffer->mnenomic = "stobj";
                              buffer->hint = "<typeTok> Store a value of type typeTok at an address. Object model instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_STSFLD: {
                              buffer->mnenomic = "stsfld";
                              buffer->hint = "<field> Replace the value of the static field with val. Object model instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_SUB: {
                              buffer->mnenomic = "sub";
                              buffer->hint = "Subtract value2 from value1, returning a new value. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_SUB_OVF: {
                              buffer->mnenomic = "sub_ovf";
                              buffer->hint = "Subtract native int from a native int. Signed result shall fit in same size. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_SUB_OVF_UN: {
                              buffer->mnenomic = "sub_ovf_un";
                              buffer->hint = "Subtract native unsigned int from a native unsigned int. Unsigned result shall fit in same size. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_SWITCH: {
                              buffer->mnenomic = "switch";
                              buffer->hint = "<uint32, int32, int32 (t1..tN)> Jump to one of n values. Base instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_TAIL_: {
                              buffer->mnenomic = "tail_";
                              buffer->hint = "Subsequent call terminates current method. Prefix to instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_THROW: {
                              buffer->mnenomic = "throw";
                              buffer->hint = "Throw an exception. Object model instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_UNALIGNED_: {
                              buffer->mnenomic = "unaligned_";
                              buffer->hint = "(alignment) Subsequent pointer instruction might be unaligned. Prefix to instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_UNBOX: {
                              buffer->mnenomic = "unbox";
                              buffer->hint = "<valuetype> Extract a value-type from obj, its boxed representation, and push a controlled-mutability managed pointer to it to the top of the stack. Object model instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_UNBOX_ANY: {
                              buffer->mnenomic = "unbox_any";
                              buffer->hint = "<typeTok> Extract a value-type from obj, its boxed representation, and copy to the top of the stack. Object model instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_VOLATILE_: {
                              buffer->mnenomic = "volatile_";
                              buffer->hint = "Subsequent pointer reference is volatile. Prefix to instruction";
                              break;
                        }
                        case luramas::disassembler::CIL::optable::data::instructions::OP_XOR: {
                              buffer->mnenomic = "xor";
                              buffer->hint = "Bitwise XOR of integer values, returns an integer. Base instruction";
                              break;
                        }
                        default: {
                              break;
                        }
                  }
                  break;
            }
      }
      return;
}