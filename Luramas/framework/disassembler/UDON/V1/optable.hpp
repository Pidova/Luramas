#pragma once
#include <cstdint>
#include <string>

/* Ref https://creators.vrchat.com/worlds/udon/vm-and-assembly */
namespace luramas::disassembler::UDON::V1::optable {

      namespace data {

            enum class instructions : std::uint8_t {
                  OP_NOP,           /* This opcode does nothing. There is generally no reason to use this, unless you get the Address aliasing detected: error. */
                  OP_PUSH,          /* This opcode pushes an integer to the top of the stack. */
                  OP_POP,           /* This opcode removes the top integer from the stack, with no further effects. */
                  OP_JUMP_IF_FALSE, /* Pops a heap index from the stack and reads a SystemBoolean from it. */
                  OP_JUMP,          /* Jumps to the bytecode position given by the parameter. */
                  OP_EXTERN,        /* The parameters to the extern are given in PUSH order; that is, the first value pushed is the first argument. These heap values are read for normal (i.e. in) arguments, read and written for ref arguments, and written for out arguments. If the extern is not static (i.e. if it has a this argument), the this argument is added at the start. If there is a return value (i.e. the return type is not SystemVoid), it is treated like an out argument at the end. */
                  OP_ANNOTATION,    /* This is effectively a "long NOP". The parameter is ignored. */
                  OP_JUMP_INDIRECT, /* Gets a heap index from the parameter and reads a SystemUInt32 from it. */
                  OP_COPY,          /* Pops two heap indexes. The value from the second heap index popped (aka the first heap index pushed) is copied to the first heap index popped (aka the second heap index pushed). */
                  OP_AMT            /* Amount. */
            };
      }

      struct opcode {
            data::instructions inst;
            std::uint32_t op = 0u;
      };
} // namespace luramas::disassembler::UDON::V1::optable