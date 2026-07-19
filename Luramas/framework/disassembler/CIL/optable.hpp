#pragma once
#include <cstdint>
#include <string>

/* Ref https://en.wikipedia.org/wiki/List_of_CIL_instructions */
namespace luramas::disassembler::CIL::optable {

      namespace data {

            enum class instructions : std::uint8_t {
                  OP_ADD,            /* Add two values, returning a new value. Base instruction */
                  OP_ADD_OVF,        /* Add signed integer values with overflow check. Base instruction */
                  OP_ADD_OVF_UN,     /* Add unsigned integer values with overflow check. Base instruction */
                  OP_AND,            /* Bitwise AND of two integral values, returns an integral value. Base instruction */
                  OP_ARGLIST,        /* Return argument list handle for the current method. Base instruction */
                  OP_BEQ,            /* <int32 (target)> Branch to target if equal. Base instruction */
                  OP_BEQ_S,          /* <int8 (target)> Branch to target if equal, short form. Base instruction */
                  OP_BGE,            /* <int32 (target)> Branch to target if greater than or equal to. Base instruction */
                  OP_BGE_S,          /* <int8 (target)> Branch to target if greater than or equal to, short form. Base instruction */
                  OP_BGE_UN,         /* <int32 (target)> Branch to target if greater than or equal to (unsigned or unordered). Base instruction */
                  OP_BGE_UN_S,       /* <int8 (target)> Branch to target if greater than or equal to (unsigned or unordered), short form. Base instruction */
                  OP_BGT,            /* <int32 (target)> Branch to target if greater than. Base instruction */
                  OP_BGT_S,          /* <int8 (target)> Branch to target if greater than, short form. Base instruction */
                  OP_BGT_UN,         /* <int32 (target)> Branch to target if greater than (unsigned or unordered). Base instruction */
                  OP_BGT_UN_S,       /* <int8 (target)> Branch to target if greater than (unsigned or unordered), short form. Base instruction */
                  OP_BLE,            /* <int32 (target)> Branch to target if less than or equal to. Base instruction */
                  OP_BLE_S,          /* <int8 (target)> Branch to target if less than or equal to, short form. Base instruction */
                  OP_BLE_UN,         /* <int32 (target)> Branch to target if less than or equal to (unsigned or unordered). Base instruction */
                  OP_BLE_UN_S,       /* <int8 (target)> Branch to target if less than or equal to (unsigned or unordered), short form. Base instruction */
                  OP_BLT,            /* <int32 (target)> Branch to target if less than. Base instruction */
                  OP_BLT_S,          /* <int8 (target)> Branch to target if less than, short form. Base instruction */
                  OP_BLT_UN,         /* <int32 (target)> Branch to target if less than (unsigned or unordered). Base instruction */
                  OP_BLT_UN_S,       /* <int8 (target)> Branch to target if less than (unsigned or unordered), short form. Base instruction */
                  OP_BNE_UN,         /* <int32 (target)> Branch to target if unequal or unordered. Base instruction */
                  OP_BNE_UN_S,       /* <int8 (target)> Branch to target if unequal or unordered, short form. Base instruction */
                  OP_BOX,            /* <typeTok> Convert a boxable value to its boxed form. Object model instruction */
                  OP_BR,             /* <int32 (target)> Branch to target. Base instruction */
                  OP_BR_S,           /* <int8 (target)> Branch to target, short form. Base instruction */
                  OP_BREAK,          /* Inform a debugger that a breakpoint has been reached. Base instruction */
                  OP_BRFALSE,        /* <int32 (target)> Branch to target if value is zero (false). Base instruction */
                  OP_BRFALSE_S,      /* <int8 (target)> Branch to target if value is zero (false), short form. Base instruction */
                  OP_BRINST,         /* <int32 (target)> Branch to target if value is a non-null object reference (alias for brtrue). Base instruction */
                  OP_BRINST_S,       /* <int8 (target)> Branch to target if value is a non-null object reference, short form (alias for brtrue.s). Base instruction */
                  OP_BRNULL,         /* <int32 (target)> Branch to target if value is null (alias for brfalse). Base instruction */
                  OP_BRNULL_S,       /* <int8 (target)> Branch to target if value is null (alias for brfalse.s), short form. Base instruction */
                  OP_BRTRUE,         /* <int32 (target)> Branch to target if value is non-zero (true). Base instruction */
                  OP_BRTRUE_S,       /* <int8 (target)> Branch to target if value is non-zero (true), short form. Base instruction */
                  OP_BRZERO,         /* <int32 (target)> Branch to target if value is zero (alias for brfalse). Base instruction */
                  OP_BRZERO_S,       /* <int8 (target)> Branch to target if value is zero (alias for brfalse.s), short form. Base instruction */
                  OP_CALL,           /* <method> Call method described by method. Base instruction */
                  OP_CALLI,          /* <callsitedescr> Call method indicated on the stack with arguments described by callsitedescr. Base instruction */
                  OP_CALLVIRT,       /* <method> Call a method associated with an object. Object model instruction */
                  OP_CASTCLASS,      /* <class> Cast obj to class. Object model instruction */
                  OP_CEQ,            /* Push 1 (of type int32) if value1 equals value2, else push 0. Base instruction */
                  OP_CGT,            /* Push 1 (of type int32) if value1 greater than value2, else push 0. Base instruction */
                  OP_CGT_UN,         /* Push 1 (of type int32) if value1 greater than value2, unsigned or unordered, else push 0. Base instruction */
                  OP_CKFINITE,       /* Throw ArithmeticException if value is not a finite number. Base instruction */
                  OP_CLT,            /* Push 1 (of type int32) if value1 lower than value2, else push 0. Base instruction */
                  OP_CLT_UN,         /* Push 1 (of type int32) if value1 lower than value2, unsigned or unordered, else push 0. Base instruction */
                  OP_CONSTRAINED_,   /* <thisType> Call a virtual method on a type constrained to be type T. Prefix to instruction */
                  OP_CONV_I,         /* Convert to native int, pushing native int on stack. Base instruction */
                  OP_CONV_I1,        /* Convert to int8, pushing int32 on stack. Base instruction */
                  OP_CONV_I2,        /* Convert to int16, pushing int32 on stack. Base instruction */
                  OP_CONV_I4,        /* Convert to int32, pushing int32 on stack. Base instruction */
                  OP_CONV_I8,        /* Convert to int64, pushing int64 on stack. Base instruction */
                  OP_CONV_OVF_I,     /* Convert to a native int (on the stack as native int) and throw an exception on overflow. Base instruction */
                  OP_CONV_OVF_I_UN,  /* Convert unsigned to a native int (on the stack as native int) and throw an exception on overflow. Base instruction */
                  OP_CONV_OVF_I1,    /* Convert to an int8 (on the stack as int32) and throw an exception on overflow. Base instruction */
                  OP_CONV_OVF_I1_UN, /* Convert unsigned to an int8 (on the stack as int32) and throw an exception on overflow. Base instruction */
                  OP_CONV_OVF_I2,    /* Convert to an int16 (on the stack as int32) and throw an exception on overflow. Base instruction */
                  OP_CONV_OVF_I2_UN, /* Convert unsigned to an int16 (on the stack as int32) and throw an exception on overflow. Base instruction */
                  OP_CONV_OVF_I4,    /* Convert to an int32 (on the stack as int32) and throw an exception on overflow. Base instruction */
                  OP_CONV_OVF_I4_UN, /* Convert unsigned to an int32 (on the stack as int32) and throw an exception on overflow. Base instruction */
                  OP_CONV_OVF_I8,    /* Convert to an int64 (on the stack as int64) and throw an exception on overflow. Base instruction */
                  OP_CONV_OVF_I8_UN, /* Convert unsigned to an int64 (on the stack as int64) and throw an exception on overflow. Base instruction */
                  OP_CONV_OVF_U,     /* Convert to a native unsigned int (on the stack as native int) and throw an exception on overflow. Base instruction */
                  OP_CONV_OVF_U_UN,  /* Convert unsigned to a native unsigned int (on the stack as native int) and throw an exception on overflow. Base instruction */
                  OP_CONV_OVF_U1,    /* Convert to an unsigned int8 (on the stack as int32) and throw an exception on overflow. Base instruction */
                  OP_CONV_OVF_U1_UN, /* Convert unsigned to an unsigned int8 (on the stack as int32) and throw an exception on overflow. Base instruction */
                  OP_CONV_OVF_U2,    /* Convert to an unsigned int16 (on the stack as int32) and throw an exception on overflow. Base instruction */
                  OP_CONV_OVF_U2_UN, /* Convert unsigned to an unsigned int16 (on the stack as int32) and throw an exception on overflow. Base instruction */
                  OP_CONV_OVF_U4,    /* Convert to an unsigned int32 (on the stack as int32) and throw an exception on overflow. Base instruction */
                  OP_CONV_OVF_U4_UN, /* Convert unsigned to an unsigned int32 (on the stack as int32) and throw an exception on overflow. Base instruction */
                  OP_CONV_OVF_U8,    /* Convert to an unsigned int64 (on the stack as int64) and throw an exception on overflow. Base instruction */
                  OP_CONV_OVF_U8_UN, /* Convert unsigned to an unsigned int64 (on the stack as int64) and throw an exception on overflow. Base instruction */
                  OP_CONV_R_UN,      /* Convert unsigned integer to floating-point, pushing F on stack. Base instruction */
                  OP_CONV_R4,        /* Convert to float32, pushing F on stack. Base instruction */
                  OP_CONV_R8,        /* Convert to float64, pushing F on stack. Base instruction */
                  OP_CONV_U,         /* Convert to native unsigned int, pushing native int on stack. Base instruction */
                  OP_CONV_U1,        /* Convert to unsigned int8, pushing int32 on stack. Base instruction */
                  OP_CONV_U2,        /* Convert to unsigned int16, pushing int32 on stack. Base instruction */
                  OP_CONV_U4,        /* Convert to unsigned int32, pushing int32 on stack. Base instruction */
                  OP_CONV_U8,        /* Convert to unsigned int64, pushing int64 on stack. Base instruction */
                  OP_CPBLK,          /* Copy data from memory to memory. Base instruction */
                  OP_CPOBJ,          /* <typeTok> Copy a value type from src to dest. Object model instruction */
                  OP_DIV,            /* Divide two values to return a quotient or floating-point result. Base instruction */
                  OP_DIV_UN,         /* Divide two values, unsigned, returning a quotient. Base instruction */
                  OP_DUP,            /* Duplicate the value on the top of the stack. Base instruction */
                  OP_ENDFAULT,       /* End fault clause of an exception block. Base instruction */
                  OP_ENDFILTER,      /* End an exception handling filter clause. Base instruction */
                  OP_ENDFINALLY,     /* End finally clause of an exception block. Base instruction */
                  OP_INITBLK,        /* Set all bytes in a block of memory to a given byte value. Base instruction */
                  OP_INITOBJ,        /* <typeTok> Initialize the value at address dest. Object model instruction */
                  OP_ISINST,         /* <class> Test if obj is an instance of class, returning null or an instance of that class or interface. Object model instruction */
                  OP_JMP,            /* <method> Exit current method and jump to the specified method. Base instruction */
                  OP_LDARG,          /* <uint16 (num)> Load argument numbered num onto the stack. Base instruction */
                  OP_LDARG_0,        /* Load argument 0 onto the stack. Base instruction */
                  OP_LDARG_1,        /* Load argument 1 onto the stack. Base instruction */
                  OP_LDARG_2,        /* Load argument 2 onto the stack. Base instruction */
                  OP_LDARG_3,        /* Load argument 3 onto the stack. Base instruction */
                  OP_LDARG_S,        /* <uint8 (num)> Load argument numbered num onto the stack, short form. Base instruction */
                  OP_LDARGA,         /* <uint16 (argNum)> Fetch the address of argument argNum. Base instruction */
                  OP_LDARGA_S,       /* <uint8 (argNum)> Fetch the address of argument argNum, short form. Base instruction */
                  OP_LDC_I4,         /* <int32 (num)> Push num of type int32 onto the stack as int32. Base instruction */
                  OP_LDC_I4_0,       /* Push 0 onto the stack as int32. Base instruction */
                  OP_LDC_I4_1,       /* Push 1 onto the stack as int32. Base instruction */
                  OP_LDC_I4_2,       /* Push 2 onto the stack as int32. Base instruction */
                  OP_LDC_I4_3,       /* Push 3 onto the stack as int32. Base instruction */
                  OP_LDC_I4_4,       /* Push 4 onto the stack as int32. Base instruction */
                  OP_LDC_I4_5,       /* Push 5 onto the stack as int32. Base instruction */
                  OP_LDC_I4_6,       /* Push 6 onto the stack as int32. Base instruction */
                  OP_LDC_I4_7,       /* Push 7 onto the stack as int32. Base instruction */
                  OP_LDC_I4_8,       /* Push 8 onto the stack as int32. Base instruction */
                  OP_LDC_I4_M1_I32,  /* Push -1 onto the stack as int32. Base instruction */
                  OP_LDC_I4_M1,      /* Push -1 onto the stack as int32 (alias for ldc.i4.m1). Base instruction */
                  OP_LDC_I4_S,       /* <int8 (num)> Push num onto the stack as int32, short form. Base instruction */
                  OP_LDC_I8,         /* <int64 (num)> Push num of type int64 onto the stack as int64. Base instruction */
                  OP_LDC_R4,         /* <float32 (num)> Push num of type float32 onto the stack as F. Base instruction */
                  OP_LDC_R8,         /* <float64 (num)> Push num of type float64 onto the stack as F. Base instruction */
                  OP_LDELEM,         /* <typeTok> Load the element at index onto the top of the stack. Object model instruction */
                  OP_LDELEM_I,       /* Load the element with type native int at index onto the top of the stack as a native int. Object model instruction */
                  OP_LDELEM_I1,      /* Load the element with type int8 at index onto the top of the stack as an int32. Object model instruction */
                  OP_LDELEM_I2,      /* Load the element with type int16 at index onto the top of the stack as an int32. Object model instruction */
                  OP_LDELEM_I4,      /* Load the element with type int32 at index onto the top of the stack as an int32. Object model instruction */
                  OP_LDELEM_I8,      /* Load the element with type int64 at index onto the top of the stack as an int64. Object model instruction */
                  OP_LDELEM_R4,      /* Load the element with type float32 at index onto the top of the stack as an F. Object model instruction */
                  OP_LDELEM_R8,      /* Load the element with type float64 at index onto the top of the stack as an F. Object model instruction */
                  OP_LDELEM_REF,     /* Load the element at index onto the top of the stack as an O. The type of the O is the same as the element type of the array pushed on the CIL stack. Object model instruction */
                  OP_LDELEM_U1,      /* Load the element with type unsigned int8 at index onto the top of the stack as an int32. Object model instruction */
                  OP_LDELEM_U2,      /* Load the element with type unsigned int16 at index onto the top of the stack as an int32. Object model instruction */
                  OP_LDELEM_U4,      /* Load the element with type unsigned int32 at index onto the top of the stack as an int32. Object model instruction */
                  OP_LDELEM_U8,      /* Load the element with type unsigned int64 at index onto the top of the stack as an int64 (alias for ldelem.i8). Object model instruction */
                  OP_LDELEMA,        /* <class> Load the address of element at index onto the top of the stack. Object model instruction */
                  OP_LDFLD,          /* <field> Push the value of field of object (or value type) obj, onto the stack. Object model instruction */
                  OP_LDFLDA,         /* <field> Push the address of field of object obj on the stack. Object model instruction */
                  OP_LDFTN,          /* <method> Push a pointer to a method referenced by method, on the stack. Base instruction */
                  OP_LDIND_I,        /* Indirect load value of type native int as native int on the stack. Base instruction */
                  OP_LDIND_I1,       /* Indirect load value of type int8 as int32 on the stack. Base instruction */
                  OP_LDIND_I2,       /* Indirect load value of type int16 as int32 on the stack. Base instruction */
                  OP_LDIND_I4,       /* Indirect load value of type int32 as int32 on the stack. Base instruction */
                  OP_LDIND_I8,       /* Indirect load value of type int64 as int64 on the stack. Base instruction */
                  OP_LDIND_R4,       /* Indirect load value of type float32 as F on the stack. Base instruction */
                  OP_LDIND_R8,       /* Indirect load value of type float64 as F on the stack. Base instruction */
                  OP_LDIND_REF,      /* Indirect load value of type object ref as O on the stack. Base instruction */
                  OP_LDIND_U1,       /* Indirect load value of type unsigned int8 as int32 on the stack. Base instruction */
                  OP_LDIND_U2,       /* Indirect load value of type unsigned int16 as int32 on the stack. Base instruction */
                  OP_LDIND_U4,       /* Indirect load value of type unsigned int32 as int32 on the stack. Base instruction */
                  OP_LDIND_U8,       /* Indirect load value of type unsigned int64 as int64 on the stack (alias for ldind.i8). Base instruction */
                  OP_LDLEN,          /* Push the length (of type native unsigned int) of array on the stack. Object model instruction */
                  OP_LDLOC,          /* <uint16 (indx)> Load local variable of index indx onto stack. Base instruction */
                  OP_LDLOC_0,        /* Load local variable 0 onto stack. Base instruction */
                  OP_LDLOC_1,        /* Load local variable 1 onto stack. Base instruction */
                  OP_LDLOC_2,        /* Load local variable 2 onto stack. Base instruction */
                  OP_LDLOC_3,        /* Load local variable 3 onto stack. Base instruction */
                  OP_LDLOC_S,        /* <uint8 (indx)> Load local variable of index indx onto stack, short form. Base instruction */
                  OP_LDLOCA,         /* <uint16 (indx)> Load address of local variable with index indx. Base instruction */
                  OP_LDLOCA_S,       /* <uint8 (indx)> Load address of local variable with index indx, short form. Base instruction */
                  OP_LDNULL,         /* Push a null reference on the stack. Base instruction */
                  OP_LDOBJ,          /* <typeTok> Copy the value stored at address src to the stack. Object model instruction */
                  OP_LDSFLD,         /* <field> Push the value of the static field on the stack. Object model instruction */
                  OP_LDSFLDA,        /* <field> Push the address of the static field, field, on the stack. Object model instruction */
                  OP_LDSTR,          /* <string> Push a string object for the literal string. Object model instruction */
                  OP_LDTOKEN,        /* <token> Convert metadata token to its runtime representation. Object model instruction */
                  OP_LDVIRTFTN,      /* <method> Push address of virtual method on the stack. Object model instruction */
                  OP_LEAVE,          /* <int32 (target)> Exit a protected region of code. Base instruction */
                  OP_LEAVE_S,        /* <int8 (target)> Exit a protected region of code, short form. Base instruction */
                  OP_LOCALLOC,       /* Allocate space from the local memory pool. Base instruction */
                  OP_MKREFANY,       /* <class> Push a typed reference to ptr of type class onto the stack. Object model instruction */
                  OP_MUL,            /* Multiply values. Base instruction */
                  OP_MUL_OVF,        /* Multiply signed integer values. Signed result shall fit in same size. Base instruction */
                  OP_MUL_OVF_UN,     /* Multiply unsigned integer values. Unsigned result shall fit in same size. Base instruction */
                  OP_NEG,            /* Negate value. Base instruction */
                  OP_NEWARR,         /* <etype> Create a new array with elements of type etype. Object model instruction */
                  OP_NEWOBJ,         /* <ctor> Allocate an uninitialized object or value type and call ctor. Object model instruction */
                  OP_NOP,            /* Do nothing (No operation). Base instruction */
                  OP_NOT,            /* Bitwise complement. Base instruction */
                  OP_OR,             /* Bitwise OR of two integer values, returns an integer. Base instruction */
                  OP_POP,            /* Pop value from the stack. Base instruction */
                  OP_READONLY_,      /* Specify that the subsequent array address operation performs no type check at runtime, and that it returns a controlled-mutability managed pointer. Prefix to instruction */
                  OP_REFANYTYPE,     /* Push the type token stored in a typed reference. Object model instruction */
                  OP_REFANYVAL,      /* <type> Push the address stored in a typed reference. Object model instruction */
                  OP_REM,            /* Remainder when dividing one value by another. Base instruction */
                  OP_REM_UN,         /* Remainder when dividing one unsigned value by another. Base instruction */
                  OP_RET,            /* Return from method, possibly with a value. Base instruction */
                  OP_RETHROW,        /* Rethrow the current exception. Object model instruction */
                  OP_SHL,            /* Shift an integer left (shifting in zeros), return an integer. Base instruction */
                  OP_SHR,            /* Shift an integer right (shift in sign), return an integer. Base instruction */
                  OP_SHR_UN,         /* Shift an integer right (shift in zero), return an integer. Base instruction */
                  OP_SIZEOF,         /* <typeTok> Push the size, in bytes, of a type as an unsigned int32. Object model instruction */
                  OP_STARG,          /* <uint16 (num)> Store value to the argument numbered num. Base instruction */
                  OP_STARG_S,        /* <uint8 (num)> Store value to the argument numbered num, short form. Base instruction */
                  OP_STELEM,         /* <typeTok> Replace array element at index with the value on the stack. Object model instruction */
                  OP_STELEM_I,       /* Replace array element at index with the native int value on the stack. Object model instruction */
                  OP_STELEM_I1,      /* Replace array element at index with the int8 value on the stack. Object model instruction */
                  OP_STELEM_I2,      /* Replace array element at index with the int16 value on the stack. Object model instruction */
                  OP_STELEM_I4,      /* Replace array element at index with the int32 value on the stack. Object model instruction */
                  OP_STELEM_I8,      /* Replace array element at index with the int64 value on the stack. Object model instruction */
                  OP_STELEM_R4,      /* Replace array element at index with the float32 value on the stack. Object model instruction */
                  OP_STELEM_R8,      /* Replace array element at index with the float64 value on the stack. Object model instruction */
                  OP_STELEM_REF,     /* Replace array element at index with the ref value on the stack. Object model instruction */
                  OP_STFLD,          /* <field> Replace the value of field of the object obj with value. Object model instruction */
                  OP_STIND_I,        /* Store value of type native int into memory at address. Base instruction */
                  OP_STIND_I1,       /* Store value of type int8 into memory at address. Base instruction */
                  OP_STIND_I2,       /* Store value of type int16 into memory at address. Base instruction */
                  OP_STIND_I4,       /* Store value of type int32 into memory at address. Base instruction */
                  OP_STIND_I8,       /* Store value of type int64 into memory at address. Base instruction */
                  OP_STIND_R4,       /* Store value of type float32 into memory at address. Base instruction */
                  OP_STIND_R8,       /* Store value of type float64 into memory at address. Base instruction */
                  OP_STIND_REF,      /* Store value of type object ref (type O) into memory at address. Base instruction */
                  OP_STLOC,          /* <uint16 (indx)> Pop a value from stack into local variable indx. Base instruction */
                  OP_STLOC_0,        /* Pop a value from stack into local variable 0. Base instruction */
                  OP_STLOC_1,        /* Pop a value from stack into local variable 1. Base instruction */
                  OP_STLOC_2,        /* Pop a value from stack into local variable 2. Base instruction */
                  OP_STLOC_3,        /* Pop a value from stack into local variable 3. Base instruction */
                  OP_STLOC_S,        /* <uint8 (indx)> Pop a value from stack into local variable indx, short form. Base instruction */
                  OP_STOBJ,          /* <typeTok> Store a value of type typeTok at an address. Object model instruction */
                  OP_STSFLD,         /* <field> Replace the value of the static field with val. Object model instruction */
                  OP_SUB,            /* Subtract value2 from value1, returning a new value. Base instruction */
                  OP_SUB_OVF,        /* Subtract native int from a native int. Signed result shall fit in same size. Base instruction */
                  OP_SUB_OVF_UN,     /* Subtract native unsigned int from a native unsigned int. Unsigned result shall fit in same size. Base instruction */
                  OP_SWITCH,         /* <uint32, int32, int32 (t1..tN)> Jump to one of n values. Base instruction */
                  OP_TAIL_,          /* Subsequent call terminates current method. Prefix to instruction */
                  OP_THROW,          /* Throw an exception. Object model instruction */
                  OP_UNALIGNED_,     /* (alignment) Subsequent pointer instruction might be unaligned. Prefix to instruction */
                  OP_UNBOX,          /* <valuetype> Extract a value-type from obj, its boxed representation, and push a controlled-mutability managed pointer to it to the top of the stack. Object model instruction */
                  OP_UNBOX_ANY,      /* <typeTok> Extract a value-type from obj, its boxed representation, and copy to the top of the stack. Object model instruction */
                  OP_VOLATILE_,      /* Subsequent pointer reference is volatile. Prefix to instruction */
                  OP_XOR,            /* Bitwise XOR of integer values, returns an integer. Base instruction */
                  OP_AMT             /* Amount. */
            };
      }

      struct opcode {
            data::instructions inst;
            std::uint32_t op = 0u;
      };
} // namespace luramas::disassembler::CIL::optable