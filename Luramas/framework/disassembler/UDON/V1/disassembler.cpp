#include "disassembler.hpp"
#include "optable.hpp"

enum class set_action : std::uint8_t {
      instruction, /* Sets all instruction info, op, mnenomic, hint. */
      operands     /* Sets all operands including details about it. */
};

template <set_action n>
void set_data(std::shared_ptr<luramas::disassembler::UDON::V1::disassembly> &buffer) {

      switch (n) {

            case set_action::instruction: {

                  // TODO ADD OPTABLE INDEXING

                  switch (buffer->op) {
                        case luramas::disassembler::UDON::V1::optable::data::instructions::OP_NOP: {
                              buffer->mnenomic = "nop";
                              buffer->hint = "This opcode does nothing. There is generally no reason to use this, unless you get the Address aliasing detected: error.";
                              break;
                        }
                        case luramas::disassembler::UDON::V1::optable::data::instructions::OP_PUSH: {
                              buffer->mnenomic = "push";
                              buffer->hint = "This opcode pushes an integer to the top of the stack.";
                              break;
                        }
                        case luramas::disassembler::UDON::V1::optable::data::instructions::OP_POP: {
                              buffer->mnenomic = "pop";
                              buffer->hint = "This opcode removes the top integer from the stack, with no further effects.";
                              break;
                        }
                        case luramas::disassembler::UDON::V1::optable::data::instructions::OP_JUMP_IF_FALSE: {
                              buffer->mnenomic = "jump_if_false";
                              buffer->hint = "Pops a heap index from the stack and reads a SystemBoolean from it.";
                              break;
                        }
                        case luramas::disassembler::UDON::V1::optable::data::instructions::OP_JUMP: {
                              buffer->mnenomic = "jump";
                              buffer->hint = "Jumps to the bytecode position given by the parameter.";
                              break;
                        }
                        case luramas::disassembler::UDON::V1::optable::data::instructions::OP_EXTERN: {
                              buffer->mnenomic = "extern";
                              buffer->hint = "The parameters to the extern are given in PUSH order; that is, the first value pushed is the first argument. These heap values are read for normal (i.e. in) arguments, read and written for ref arguments, and written for out arguments. If the extern is not static (i.e. if it has a this argument), the this argument is added at the start. If there is a return value (i.e. the return type is not SystemVoid), it is treated like an out argument at the end.";
                              break;
                        }
                        case luramas::disassembler::UDON::V1::optable::data::instructions::OP_ANNOTATION: {
                              buffer->mnenomic = "annotation";
                              buffer->hint = "This is effectively a \" long NOP \". The parameter is ignored.";
                              break;
                        }
                        case luramas::disassembler::UDON::V1::optable::data::instructions::OP_JUMP_INDIRECT: {
                              buffer->mnenomic = "jump_indirect";
                              buffer->hint = "Gets a heap index from the parameter and reads a SystemUInt32 from it.";
                              break;
                        }
                        case luramas::disassembler::UDON::V1::optable::data::instructions::OP_COPY: {
                              buffer->mnenomic = "copy";
                              buffer->hint = "Pops two heap indexes. The value from the second heap index popped (aka the first heap index pushed) is copied to the first heap index popped (aka the second heap index pushed).";
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