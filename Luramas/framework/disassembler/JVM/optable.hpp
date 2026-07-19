#pragma once
#include <cstdint>
#include <string>

/* Ref https://en.wikipedia.org/wiki/List_of_Java_bytecode_instructions */
namespace luramas::disassembler::JVM::optable {

      namespace data {

            enum class instructions : std::uint8_t {
                  OP_AALOAD,          /* arrayref, index -> value load onto the stack a reference from an array */
                  OP_AASTORE,         /* arrayref, index, value -> store a reference in an array */
                  OP_ACONST_NULL,     /* -> null push a null reference onto the stack */
                  OP_ALOAD,           /* 1: index -> objectref load a reference onto the stack from a local variable #index */
                  OP_ALOAD_0,         /* -> objectref load a reference onto the stack from local variable 0 */
                  OP_ALOAD_1,         /* -> objectref load a reference onto the stack from local variable 1 */
                  OP_ALOAD_2,         /* -> objectref load a reference onto the stack from local variable 2 */
                  OP_ALOAD_3,         /* -> objectref load a reference onto the stack from local variable 3 */
                  OP_ANEWARRAY,       /* 2: indexbyte1, indexbyte2 count -> arrayref create a new array of references of length count and component type identified by the class reference index (indexbyte1 << 8 | indexbyte2) in the constant pool */
                  OP_ARETURN,         /* objectref -> [empty] return a reference from a method */
                  OP_ARRAYLENGTH,     /* arrayref -> length get the length of an array */
                  OP_ASTORE,          /* 1: index objectref -> store a reference into a local variable #index */
                  OP_ASTORE_0,        /* objectref -> store a reference into local variable 0 */
                  OP_ASTORE_1,        /* objectref -> store a reference into local variable 1 */
                  OP_ASTORE_2,        /* objectref -> store a reference into local variable 2 */
                  OP_ASTORE_3,        /* objectref -> store a reference into local variable 3 */
                  OP_ATHROW,          /* objectref -> [empty], objectref throws an error or exception (notice that the rest of the stack is cleared, leaving only a reference to the Throwable) */
                  OP_BALOAD,          /* arrayref, index -> value load a byte or Boolean value from an array */
                  OP_BASTORE,         /* arrayref, index, value -> store a byte or Boolean value into an array */
                  OP_BIPUSH,          /* 1: byte -> value push a byte onto the stack as an integer value */
                  OP_BREAKPOINT,      /* reserved for breakpoints in Java debuggers; should not appear in any class file */
                  OP_CALOAD,          /* arrayref, index -> value load a char from an array */
                  OP_CASTORE,         /* arrayref, index, value -> store a char into an array */
                  OP_CHECKCAST,       /* 2: indexbyte1, indexbyte2 objectref -> objectref checks whether an objectref is of a certain type, the class reference of which is in the constant pool at index (indexbyte1 << 8 | indexbyte2) */
                  OP_D2F,             /* value -> result convert a double to a float */
                  OP_D2I,             /* value -> result convert a double to an int */
                  OP_D2L,             /* value -> result convert a double to a long */
                  OP_DADD,            /* value1, value2 -> result add two doubles */
                  OP_DALOAD,          /* arrayref, index -> value load a double from an array */
                  OP_DASTORE,         /* arrayref, index, value -> store a double into an array */
                  OP_DCMPG,           /* value1, value2 -> result compare two doubles, 1 on NaN */
                  OP_DCMPL,           /* value1, value2 -> result compare two doubles, -1 on NaN */
                  OP_DCONST_0,        /* -> 0.0 push the constant 0.0 (a double) onto the stack */
                  OP_DCONST_1,        /* -> 1.0 push the constant 1.0 (a double) onto the stack */
                  OP_DDIV,            /* value1, value2 -> result divide two doubles */
                  OP_DLOAD,           /* 1: index -> value load a double value from a local variable #index */
                  OP_DLOAD_0,         /* -> value load a double from local variable 0 */
                  OP_DLOAD_1,         /* -> value load a double from local variable 1 */
                  OP_DLOAD_2,         /* -> value load a double from local variable 2 */
                  OP_DLOAD_3,         /* -> value load a double from local variable 3 */
                  OP_DMUL,            /* value1, value2 -> result multiply two doubles */
                  OP_DNEG,            /* value -> result negate a double */
                  OP_DREM,            /* value1, value2 -> result get the remainder from a division between two doubles */
                  OP_DRETURN,         /* value -> [empty] return a double from a method */
                  OP_DSTORE,          /* 1: index value -> store a double value into a local variable #index */
                  OP_DSTORE_0,        /* value -> store a double into local variable 0 */
                  OP_DSTORE_1,        /* value -> store a double into local variable 1 */
                  OP_DSTORE_2,        /* value -> store a double into local variable 2 */
                  OP_DSTORE_3,        /* value -> store a double into local variable 3 */
                  OP_DSUB,            /* value1, value2 -> result subtract a double from another */
                  OP_DUP,             /* value -> value, value duplicate the value on top of the stack */
                  OP_DUP_X1,          /* value2, value1 -> value1, value2, value1 insert a copy of the top value into the stack two values from the top. value1 and value2 must not be of the type double or long. */
                  OP_DUP_X2,          /* value3, value2, value1 -> value1, value3, value2, value1 insert a copy of the top value into the stack two (if value2 is double or long it takes up the entry of value3, too) or three values (if value2 is neither double nor long) from the top */
                  OP_DUP2,            /* {value2, value1} -> {value2, value1}, {value2, value1} duplicate top two stack words (two values, if value1 is not double nor long; a single value, if value1 is double or long) */
                  OP_DUP2_X1,         /* value3, {value2, value1} -> {value2, value1}, value3, {value2, value1} duplicate two words and insert beneath third word (see explanation above) */
                  OP_DUP2_X2,         /* {value4, value3}, {value2, value1} -> {value2, value1}, {value4, value3}, {value2, value1} duplicate two words and insert beneath fourth word */
                  OP_F2D,             /* value -> result convert a float to a double */
                  OP_F2I,             /* value -> result convert a float to an int */
                  OP_F2L,             /* value -> result convert a float to a long */
                  OP_FADD,            /* value1, value2 -> result add two floats */
                  OP_FALOAD,          /* arrayref, index -> value load a float from an array */
                  OP_FASTORE,         /* arrayref, index, value -> store a float in an array */
                  OP_FCMPG,           /* value1, value2 -> result compare two floats, 1 on NaN */
                  OP_FCMPL,           /* value1, value2 -> result compare two floats, -1 on NaN */
                  OP_FCONST_0,        /* -> 0.0f push 0.0f on the stack */
                  OP_FCONST_1,        /* -> 1.0f push 1.0f on the stack */
                  OP_FCONST_2,        /* -> 2.0f push 2.0f on the stack */
                  OP_FDIV,            /* value1, value2 -> result divide two floats */
                  OP_FLOAD,           /* 1: index -> value load a float value from a local variable #index */
                  OP_FLOAD_0,         /* -> value load a float value from local variable 0 */
                  OP_FLOAD_1,         /* -> value load a float value from local variable 1 */
                  OP_FLOAD_2,         /* -> value load a float value from local variable 2 */
                  OP_FLOAD_3,         /* -> value load a float value from local variable 3 */
                  OP_FMUL,            /* value1, value2 -> result multiply two floats */
                  OP_FNEG,            /* value -> result negate a float */
                  OP_FREM,            /* value1, value2 -> result get the remainder from a division between two floats */
                  OP_FRETURN,         /* value -> [empty] return a float */
                  OP_FSTORE,          /* 1: index value -> store a float value into a local variable #index */
                  OP_FSTORE_0,        /* value -> store a float value into local variable 0 */
                  OP_FSTORE_1,        /* value -> store a float value into local variable 1 */
                  OP_FSTORE_2,        /* value -> store a float value into local variable 2 */
                  OP_FSTORE_3,        /* value -> store a float value into local variable 3 */
                  OP_FSUB,            /* value1, value2 -> result subtract two floats */
                  OP_GETFIELD,        /* 2: indexbyte1, indexbyte2 objectref -> value get a field value of an object objectref, where the field is identified by field reference in the constant pool index (indexbyte1 << 8 | indexbyte2) */
                  OP_GETSTATIC,       /* 2: indexbyte1, indexbyte2 -> value get a static field value of a class, where the field is identified by field reference in the constant pool index (indexbyte1 << 8 | indexbyte2) */
                  OP_GOTO,            /* 2: branchbyte1, branchbyte2 [no change] goes to another instruction at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 | branchbyte2) */
                  OP_GOTO_W,          /* 4: branchbyte1, branchbyte2, branchbyte3, branchbyte4 [no change] goes to another instruction at branchoffset (signed int constructed from unsigned bytes branchbyte1 << 24 | branchbyte2 << 16 | branchbyte3 << 8 | branchbyte4) */
                  OP_I2B,             /* value -> result convert an int into a byte */
                  OP_I2C,             /* value -> result convert an int into a character */
                  OP_I2D,             /* value -> result convert an int into a double */
                  OP_I2F,             /* value -> result convert an int into a float */
                  OP_I2L,             /* value -> result convert an int into a long */
                  OP_I2S,             /* value -> result convert an int into a short */
                  OP_IADD,            /* value1, value2 -> result add two ints */
                  OP_IALOAD,          /* arrayref, index -> value load an int from an array */
                  OP_IAND,            /* value1, value2 -> result perform a bitwise AND on two integers */
                  OP_IASTORE,         /* arrayref, index, value -> store an int into an array */
                  OP_ICONST_M1,       /* -> -1 load the int value 1 onto the stack */
                  OP_ICONST_0,        /* -> 0 load the int value 0 onto the stack */
                  OP_ICONST_1,        /* -> 1 load the int value 1 onto the stack */
                  OP_ICONST_2,        /* -> 2 load the int value 2 onto the stack */
                  OP_ICONST_3,        /* -> 3 load the int value 3 onto the stack */
                  OP_ICONST_4,        /* -> 4 load the int value 4 onto the stack */
                  OP_ICONST_5,        /* -> 5 load the int value 5 onto the stack */
                  OP_IDIV,            /* value1, value2 -> result divide two integers */
                  OP_IF_ACMPEQ,       /* 2: branchbyte1, branchbyte2 value1, value2 -> if references are equal, branch to instruction at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 | branchbyte2) */
                  OP_IF_ACMPNE,       /* 2: branchbyte1, branchbyte2 value1, value2 -> if references are not equal, branch to instruction at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 | branchbyte2) */
                  OP_IF_ICMPEQ,       /* 2: branchbyte1, branchbyte2 value1, value2 -> if ints are equal, branch to instruction at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 | branchbyte2) */
                  OP_IF_ICMPGE,       /* 2: branchbyte1, branchbyte2 value1, value2 -> if value1 is greater than or equal to value2, branch to instruction at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 | branchbyte2) */
                  OP_IF_ICMPGT,       /* 2: branchbyte1, branchbyte2 value1, value2 -> if value1 is greater than value2, branch to instruction at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 | branchbyte2) */
                  OP_IF_ICMPLE,       /* 2: branchbyte1, branchbyte2 value1, value2 -> if value1 is less than or equal to value2, branch to instruction at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 | branchbyte2) */
                  OP_IF_ICMPLT,       /* 2: branchbyte1, branchbyte2 value1, value2 -> if value1 is less than value2, branch to instruction at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 | branchbyte2) */
                  OP_IF_ICMPNE,       /* 2: branchbyte1, branchbyte2 value1, value2 -> if ints are not equal, branch to instruction at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 | branchbyte2) */
                  OP_IFEQ,            /* 2: branchbyte1, branchbyte2 value -> if value is 0, branch to instruction at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 | branchbyte2) */
                  OP_IFGE,            /* 2: branchbyte1, branchbyte2 value -> if value is greater than or equal to 0, branch to instruction at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 | branchbyte2) */
                  OP_IFGT,            /* 2: branchbyte1, branchbyte2 value -> if value is greater than 0, branch to instruction at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 | branchbyte2) */
                  OP_IFLE,            /* 2: branchbyte1, branchbyte2 value -> if value is less than or equal to 0, branch to instruction at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 | branchbyte2) */
                  OP_IFLT,            /* 2: branchbyte1, branchbyte2 value -> if value is less than 0, branch to instruction at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 | branchbyte2) */
                  OP_IFNE,            /* 2: branchbyte1, branchbyte2 value -> if value is not 0, branch to instruction at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 | branchbyte2) */
                  OP_IFNONNULL,       /* 2: branchbyte1, branchbyte2 value -> if value is not null, branch to instruction at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 | branchbyte2) */
                  OP_IFNULL,          /* 2: branchbyte1, branchbyte2 value -> if value is null, branch to instruction at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 | branchbyte2) */
                  OP_IINC,            /* 2: index, const [No change] increment local variable #index by signed byte const */
                  OP_ILOAD,           /* 1: index -> value load an int value from a local variable #index */
                  OP_ILOAD_0,         /* -> value load an int value from local variable 0 */
                  OP_ILOAD_1,         /* -> value load an int value from local variable 1 */
                  OP_ILOAD_2,         /* -> value load an int value from local variable 2 */
                  OP_ILOAD_3,         /* -> value load an int value from local variable 3 */
                  OP_IMPDEP1,         /* reserved for implementation-dependent operations within debuggers; should not appear in any class file */
                  OP_IMPDEP2,         /* reserved for implementation-dependent operations within debuggers; should not appear in any class file */
                  OP_IMUL,            /* value1, value2 -> result multiply two integers */
                  OP_INEG,            /* value -> result negate int */
                  OP_INSTANCEOF,      /* 2: indexbyte1, indexbyte2 objectref -> result determines if an object objectref is of a given type, identified by class reference index in constant pool (indexbyte1 << 8 | indexbyte2) */
                  OP_INVOKEDYNAMIC,   /* 4: indexbyte1, indexbyte2, 0, 0 [arg1, arg2, ...] -> result invokes a dynamic method and puts the result on the stack (might be void); the method is identified by method reference index in constant pool (indexbyte1 << 8 | indexbyte2) */
                  OP_INVOKEINTERFACE, /* 4: indexbyte1, indexbyte2, count, 0 objectref, [arg1, arg2, ...] -> result invokes an interface method on object objectref and puts the result on the stack (might be void); the interface method is identified by method reference index in constant pool (indexbyte1 << 8 | indexbyte2) */
                  OP_INVOKESPECIAL,   /* 2: indexbyte1, indexbyte2 objectref, [arg1, arg2, ...] -> result invoke instance method on object objectref and puts the result on the stack (might be void); the method is identified by method reference index in constant pool (indexbyte1 << 8 | indexbyte2) */
                  OP_INVOKESTATIC,    /* 2: indexbyte1, indexbyte2 [arg1, arg2, ...] -> result invoke a static method and puts the result on the stack (might be void); the method is identified by method reference index in constant pool (indexbyte1 << 8 | indexbyte2) */
                  OP_INVOKEVIRTUAL,   /* 2: indexbyte1, indexbyte2 objectref, [arg1, arg2, ...] -> result invoke virtual method on object objectref and puts the result on the stack (might be void); the method is identified by method reference index in constant pool (indexbyte1 << 8 | indexbyte2) */
                  OP_IOR,             /* value1, value2 -> result bitwise int OR */
                  OP_IREM,            /* value1, value2 -> result logical int remainder */
                  OP_IRETURN,         /* value -> [empty] return an integer from a method */
                  OP_ISHL,            /* value1, value2 -> result int shift left */
                  OP_ISHR,            /* value1, value2 -> result int arithmetic shift right */
                  OP_ISTORE,          /* 1: index value -> store int value into variable #index */
                  OP_ISTORE_0,        /* value -> store int value into variable 0 */
                  OP_ISTORE_1,        /* value -> store int value into variable 1 */
                  OP_ISTORE_2,        /* value -> store int value into variable 2 */
                  OP_ISTORE_3,        /* value -> store int value into variable 3 */
                  OP_ISUB,            /* value1, value2 -> result int subtract */
                  OP_IUSHR,           /* value1, value2 -> result int logical shift right */
                  OP_IXOR,            /* value1, value2 -> result int xor */
                  OP_JSR,             /* 2: branchbyte1, branchbyte2 -> address jump to subroutine at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 | branchbyte2) and place the return address on the stack */
                  OP_JSR_W,           /* 4: branchbyte1, branchbyte2, branchbyte3, branchbyte4 -> address jump to subroutine at branchoffset (signed int constructed from unsigned bytes branchbyte1 << 24 | branchbyte2 << 16 | branchbyte3 << 8 | branchbyte4) and place the return address on the stack */
                  OP_L2D,             /* value -> result convert a long to a double */
                  OP_L2F,             /* value -> result convert a long to a float */
                  OP_L2I,             /* value -> result convert a long to a int */
                  OP_LADD,            /* value1, value2 -> result add two longs */
                  OP_LALOAD,          /* arrayref, index -> value load a long from an array */
                  OP_LAND,            /* value1, value2 -> result bitwise AND of two longs */
                  OP_LASTORE,         /* arrayref, index, value -> store a long to an array */
                  OP_LCMP,            /* value1, value2 -> result push 0 if the two longs are the same, 1 if value1 is greater than value2, -1 otherwise */
                  OP_LCONST_0,        /* -> 0L push 0L (the number zero with type long) onto the stack */
                  OP_LCONST_1,        /* -> 1L push 1L (the number one with type long) onto the stack */
                  OP_LDC,             /* 1: index -> value push a constant #index from a constant pool (String, int, float, Class, java.lang.invoke.MethodType, java.lang.invoke.MethodHandle, or a dynamically-computed constant) onto the stack */
                  OP_LDC_W,           /* 2: indexbyte1, indexbyte2 -> value push a constant #index from a constant pool (String, int, float, Class, java.lang.invoke.MethodType, java.lang.invoke.MethodHandle, or a dynamically-computed constant) onto the stack (wide index is constructed as indexbyte1 << 8 | indexbyte2) */
                  OP_LDC2_W,          /* 2: indexbyte1, indexbyte2 -> value push a constant #index from a constant pool (double, long, or a dynamically-computed constant) onto the stack (wide index is constructed as indexbyte1 << 8 | indexbyte2) */
                  OP_LDIV,            /* value1, value2 -> result divide two longs */
                  OP_LLOAD,           /* 1: index -> value load a long value from a local variable #index */
                  OP_LLOAD_0,         /* -> value load a long value from a local variable 0 */
                  OP_LLOAD_1,         /* -> value load a long value from a local variable 1 */
                  OP_LLOAD_2,         /* -> value load a long value from a local variable 2 */
                  OP_LLOAD_3,         /* -> value load a long value from a local variable 3 */
                  OP_LMUL,            /* value1, value2 -> result multiply two longs */
                  OP_LNEG,            /* value -> result negate a long */
                  OP_LOOKUPSWITCH,    /* 8+: <0-3 bytes padding>, defaultbyte1, defaultbyte2, defaultbyte3, defaultbyte4, npairs1, npairs2, npairs3, npairs4, match-offset pairs... key -> a target address is looked up from a table using a key and execution continues from the instruction at that address */
                  OP_LOR,             /* value1, value2 -> result bitwise OR of two longs */
                  OP_LREM,            /* value1, value2 -> result remainder of division of two longs */
                  OP_LRETURN,         /* value -> [empty] return a long value */
                  OP_LSHL,            /* value1, value2 -> result bitwise shift left of a long value1 by int value2 positions */
                  OP_LSHR,            /* value1, value2 -> result bitwise shift right of a long value1 by int value2 positions */
                  OP_LSTORE,          /* 1: index value -> store a long value in a local variable #index */
                  OP_LSTORE_0,        /* value -> store a long value in a local variable 0 */
                  OP_LSTORE_1,        /* value -> store a long value in a local variable 1 */
                  OP_LSTORE_2,        /* value -> store a long value in a local variable 2 */
                  OP_LSTORE_3,        /* value -> store a long value in a local variable 3 */
                  OP_LSUB,            /* value1, value2 -> result subtract two longs */
                  OP_LUSHR,           /* value1, value2 -> result bitwise shift right of a long value1 by int value2 positions, unsigned */
                  OP_LXOR,            /* value1, value2 -> result bitwise XOR of two longs */
                  OP_MONITORENTER,    /* objectref -> enter monitor for object ("grab the lock" - start of synchronized() section) */
                  OP_MONITOREXIT,     /* objectref -> exit monitor for object ("release the lock" - end of synchronized() section) */
                  OP_MULTIANEWARRAY,  /* 3: indexbyte1, indexbyte2, dimensions count1, [count2,...] -> arrayref create a new array of dimensions dimensions of type identified by class reference in constant pool index (indexbyte1 << 8 | indexbyte2); the sizes of each dimension is identified by count1, [count2, etc.] */
                  OP_NEW,             /* 2: indexbyte1, indexbyte2 -> objectref create new object of type identified by class reference in constant pool index (indexbyte1 << 8 | indexbyte2) */
                  OP_NEWARRAY,        /* 1: atype count -> arrayref create new array with count elements of primitive type identified by atype */
                  OP_NOP,             /* [No change] perform no operation */
                  OP_POP,             /* value -> discard the top value on the stack */
                  OP_POP2,            /* {value2, value1} -> discard the top two values on the stack (or one value, if it is a double or long) */
                  OP_PUTFIELD,        /* 2: indexbyte1, indexbyte2 objectref, value -> set field to value in an object objectref, where the field is identified by a field reference index in constant pool (indexbyte1 << 8 | indexbyte2) */
                  OP_PUTSTATIC,       /* 2: indexbyte1, indexbyte2 value -> set static field to value in a class, where the field is identified by a field reference index in constant pool (indexbyte1 << 8 | indexbyte2) */
                  OP_RET,             /* 1: index [No change] continue execution from address taken from a local variable #index (the asymmetry with jsr is intentional) */
                  OP_RETURN,          /* -> [empty] return void from method */
                  OP_SALOAD,          /* arrayref, index -> value load short from array */
                  OP_SASTORE,         /* arrayref, index, value -> store short to array */
                  OP_SIPUSH,          /* 2: byte1, byte2 -> value push a short onto the stack as an integer value */
                  OP_SWAP,            /* value2, value1 -> value1, value2 swaps two top words on the stack (note that value1 and value2 must not be double or long) */
                  OP_TABLESWITCH,     /* 16+: [0-3 bytes padding], defaultbyte1, defaultbyte2, defaultbyte3, defaultbyte4, lowbyte1, lowbyte2, lowbyte3, lowbyte4, highbyte1, highbyte2, highbyte3, highbyte4, jump offsets... index -> continue execution from an address in the table at offset index */
                  OP_WIDE,            /* 3/5: opcode, indexbyte1, indexbyte2 or iinc, indexbyte1, indexbyte2, countbyte1, countbyte2 [same as for corresponding instructions] execute opcode, where opcode is either iload, fload, aload, lload, dload, istore, fstore, astore, lstore, dstore, or ret, but assume the index is 16 bit; or execute iinc, where the index is 16 bits and the constant to increment by is a signed 16 bit short */
                  OP_AMT              /* Amount. */
            };
      }

      struct opcode {
            data::instructions inst;
            std::uint32_t op = 0u;
      };
} // namespace luramas::disassembler::JVM::optable