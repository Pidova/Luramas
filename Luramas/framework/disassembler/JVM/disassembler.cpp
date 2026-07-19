#include "disassembler.hpp"
#include "optable.hpp"

enum class set_action : std::uint8_t {
      instruction, /* Sets all instruction info, op, mnenomic, hint. */
      operands     /* Sets all operands including details about it. */
};

template <set_action n>
void set_data(std::shared_ptr<luramas::disassembler::JVM::disassembly> &buffer) {

      switch (n) {

            case set_action::instruction: {

                  // TODO ADD OPTABLE INDEXING

                  switch (buffer->op) {
                        case luramas::disassembler::JVM::optable::data::instructions::OP_AALOAD: {
                              buffer->mnenomic = "aaload";
                              buffer->hint = "arrayref, index -> value load onto the stack a reference from an array";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_AASTORE: {
                              buffer->mnenomic = "aastore";
                              buffer->hint = "arrayref, index, value -> store a reference in an array";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_ACONST_NULL: {
                              buffer->mnenomic = "aconst_null";
                              buffer->hint = "-> null push a null reference onto the stack";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_ALOAD: {
                              buffer->mnenomic = "aload";
                              buffer->hint = "1: index -> objectref load a reference onto the stack from a local variable #index";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_ALOAD_0: {
                              buffer->mnenomic = "aload_0";
                              buffer->hint = "-> objectref load a reference onto the stack from local variable 0";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_ALOAD_1: {
                              buffer->mnenomic = "aload_1";
                              buffer->hint = "-> objectref load a reference onto the stack from local variable 1";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_ALOAD_2: {
                              buffer->mnenomic = "aload_2";
                              buffer->hint = "-> objectref load a reference onto the stack from local variable 2";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_ALOAD_3: {
                              buffer->mnenomic = "aload_3";
                              buffer->hint = "-> objectref load a reference onto the stack from local variable 3";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_ANEWARRAY: {
                              buffer->mnenomic = "anewarray";
                              buffer->hint = "2: indexbyte1, indexbyte2 count -> arrayref create a new array of references of length count and component type identified by the class reference index (indexbyte1 << 8 | indexbyte2) in the constant pool";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_ARETURN: {
                              buffer->mnenomic = "areturn";
                              buffer->hint = "objectref -> [empty] return a reference from a method";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_ARRAYLENGTH: {
                              buffer->mnenomic = "arraylength";
                              buffer->hint = "arrayref -> length get the length of an array";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_ASTORE: {
                              buffer->mnenomic = "astore";
                              buffer->hint = "1: index objectref -> store a reference into a local variable #index";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_ASTORE_0: {
                              buffer->mnenomic = "astore_0";
                              buffer->hint = "objectref -> store a reference into local variable 0";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_ASTORE_1: {
                              buffer->mnenomic = "astore_1";
                              buffer->hint = "objectref -> store a reference into local variable 1";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_ASTORE_2: {
                              buffer->mnenomic = "astore_2";
                              buffer->hint = "objectref -> store a reference into local variable 2";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_ASTORE_3: {
                              buffer->mnenomic = "astore_3";
                              buffer->hint = "objectref -> store a reference into local variable 3";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_ATHROW: {
                              buffer->mnenomic = "athrow";
                              buffer->hint = "objectref -> [empty], objectref throws an error or exception (notice that the rest of the stack is cleared, leaving only a reference to the Throwable)";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_BALOAD: {
                              buffer->mnenomic = "baload";
                              buffer->hint = "arrayref, index -> value load a byte or Boolean value from an array";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_BASTORE: {
                              buffer->mnenomic = "bastore";
                              buffer->hint = "arrayref, index, value -> store a byte or Boolean value into an array";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_BIPUSH: {
                              buffer->mnenomic = "bipush";
                              buffer->hint = "1: byte -> value push a byte onto the stack as an integer value";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_BREAKPOINT: {
                              buffer->mnenomic = "breakpoint";
                              buffer->hint = "reserved for breakpoints in Java debuggers; should not appear in any class file";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_CALOAD: {
                              buffer->mnenomic = "caload";
                              buffer->hint = "arrayref, index -> value load a char from an array";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_CASTORE: {
                              buffer->mnenomic = "castore";
                              buffer->hint = "arrayref, index, value -> store a char into an array";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_CHECKCAST: {
                              buffer->mnenomic = "checkcast";
                              buffer->hint = "2: indexbyte1, indexbyte2 objectref -> objectref checks whether an objectref is of a certain type, the class reference of which is in the constant pool at index (indexbyte1 << 8 | indexbyte2)";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_D2F: {
                              buffer->mnenomic = "d2f";
                              buffer->hint = "value -> result convert a double to a float";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_D2I: {
                              buffer->mnenomic = "d2i";
                              buffer->hint = "value -> result convert a double to an int";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_D2L: {
                              buffer->mnenomic = "d2l";
                              buffer->hint = "value -> result convert a double to a long";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_DADD: {
                              buffer->mnenomic = "dadd";
                              buffer->hint = "value1, value2 -> result add two doubles";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_DALOAD: {
                              buffer->mnenomic = "daload";
                              buffer->hint = "arrayref, index -> value load a double from an array";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_DASTORE: {
                              buffer->mnenomic = "dastore";
                              buffer->hint = "arrayref, index, value -> store a double into an array";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_DCMPG: {
                              buffer->mnenomic = "dcmpg";
                              buffer->hint = "value1, value2 -> result compare two doubles, 1 on NaN";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_DCMPL: {
                              buffer->mnenomic = "dcmpl";
                              buffer->hint = "value1, value2 -> result compare two doubles, -1 on NaN";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_DCONST_0: {
                              buffer->mnenomic = "dconst_0";
                              buffer->hint = "-> 0.0 push the constant 0.0 (a double) onto the stack";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_DCONST_1: {
                              buffer->mnenomic = "dconst_1";
                              buffer->hint = "-> 1.0 push the constant 1.0 (a double) onto the stack";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_DDIV: {
                              buffer->mnenomic = "ddiv";
                              buffer->hint = "value1, value2 -> result divide two doubles";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_DLOAD: {
                              buffer->mnenomic = "dload";
                              buffer->hint = "1: index -> value load a double value from a local variable #index";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_DLOAD_0: {
                              buffer->mnenomic = "dload_0";
                              buffer->hint = "-> value load a double from local variable 0";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_DLOAD_1: {
                              buffer->mnenomic = "dload_1";
                              buffer->hint = "-> value load a double from local variable 1";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_DLOAD_2: {
                              buffer->mnenomic = "dload_2";
                              buffer->hint = "-> value load a double from local variable 2";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_DLOAD_3: {
                              buffer->mnenomic = "dload_3";
                              buffer->hint = "-> value load a double from local variable 3";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_DMUL: {
                              buffer->mnenomic = "dmul";
                              buffer->hint = "value1, value2 -> result multiply two doubles";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_DNEG: {
                              buffer->mnenomic = "dneg";
                              buffer->hint = "value -> result negate a double";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_DREM: {
                              buffer->mnenomic = "drem";
                              buffer->hint = "value1, value2 -> result get the remainder from a division between two doubles";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_DRETURN: {
                              buffer->mnenomic = "dreturn";
                              buffer->hint = "value -> [empty] return a double from a method";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_DSTORE: {
                              buffer->mnenomic = "dstore";
                              buffer->hint = "1: index value -> store a double value into a local variable #index";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_DSTORE_0: {
                              buffer->mnenomic = "dstore_0";
                              buffer->hint = "value -> store a double into local variable 0";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_DSTORE_1: {
                              buffer->mnenomic = "dstore_1";
                              buffer->hint = "value -> store a double into local variable 1";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_DSTORE_2: {
                              buffer->mnenomic = "dstore_2";
                              buffer->hint = "value -> store a double into local variable 2";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_DSTORE_3: {
                              buffer->mnenomic = "dstore_3";
                              buffer->hint = "value -> store a double into local variable 3";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_DSUB: {
                              buffer->mnenomic = "dsub";
                              buffer->hint = "value1, value2 -> result subtract a double from another";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_DUP: {
                              buffer->mnenomic = "dup";
                              buffer->hint = "value -> value, value duplicate the value on top of the stack";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_DUP_X1: {
                              buffer->mnenomic = "dup_x1";
                              buffer->hint = "value2, value1 -> value1, value2, value1 insert a copy of the top value into the stack two values from the top. value1 and value2 must not be of the type double or long.";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_DUP_X2: {
                              buffer->mnenomic = "dup_x2";
                              buffer->hint = "value3, value2, value1 -> value1, value3, value2, value1 insert a copy of the top value into the stack two (if value2 is double or long it takes up the entry of value3, too) or three values (if value2 is neither double nor long) from the top";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_DUP2: {
                              buffer->mnenomic = "dup2";
                              buffer->hint = "{value2, value1} -> {value2, value1}, {value2, value1} duplicate top two stack words (two values, if value1 is not double nor long; a single value, if value1 is double or long)";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_DUP2_X1: {
                              buffer->mnenomic = "dup2_x1";
                              buffer->hint = "value3, {value2, value1} -> {value2, value1}, value3, {value2, value1} duplicate two words and insert beneath third word (see explanation above)";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_DUP2_X2: {
                              buffer->mnenomic = "dup2_x2";
                              buffer->hint = "{value4, value3}, {value2, value1} -> {value2, value1}, {value4, value3}, {value2, value1} duplicate two words and insert beneath fourth word";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_F2D: {
                              buffer->mnenomic = "f2d";
                              buffer->hint = "value -> result convert a float to a double";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_F2I: {
                              buffer->mnenomic = "f2i";
                              buffer->hint = "value -> result convert a float to an int";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_F2L: {
                              buffer->mnenomic = "f2l";
                              buffer->hint = "value -> result convert a float to a long";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_FADD: {
                              buffer->mnenomic = "fadd";
                              buffer->hint = "value1, value2 -> result add two floats";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_FALOAD: {
                              buffer->mnenomic = "faload";
                              buffer->hint = "arrayref, index -> value load a float from an array";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_FASTORE: {
                              buffer->mnenomic = "fastore";
                              buffer->hint = "arrayref, index, value -> store a float in an array";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_FCMPG: {
                              buffer->mnenomic = "fcmpg";
                              buffer->hint = "value1, value2 -> result compare two floats, 1 on NaN";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_FCMPL: {
                              buffer->mnenomic = "fcmpl";
                              buffer->hint = "value1, value2 -> result compare two floats, -1 on NaN";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_FCONST_0: {
                              buffer->mnenomic = "fconst_0";
                              buffer->hint = "-> 0.0f push 0.0f on the stack";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_FCONST_1: {
                              buffer->mnenomic = "fconst_1";
                              buffer->hint = "-> 1.0f push 1.0f on the stack";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_FCONST_2: {
                              buffer->mnenomic = "fconst_2";
                              buffer->hint = "-> 2.0f push 2.0f on the stack";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_FDIV: {
                              buffer->mnenomic = "fdiv";
                              buffer->hint = "value1, value2 -> result divide two floats";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_FLOAD: {
                              buffer->mnenomic = "fload";
                              buffer->hint = "1: index -> value load a float value from a local variable #index";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_FLOAD_0: {
                              buffer->mnenomic = "fload_0";
                              buffer->hint = "-> value load a float value from local variable 0";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_FLOAD_1: {
                              buffer->mnenomic = "fload_1";
                              buffer->hint = "-> value load a float value from local variable 1";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_FLOAD_2: {
                              buffer->mnenomic = "fload_2";
                              buffer->hint = "-> value load a float value from local variable 2";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_FLOAD_3: {
                              buffer->mnenomic = "fload_3";
                              buffer->hint = "-> value load a float value from local variable 3";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_FMUL: {
                              buffer->mnenomic = "fmul";
                              buffer->hint = "value1, value2 -> result multiply two floats";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_FNEG: {
                              buffer->mnenomic = "fneg";
                              buffer->hint = "value -> result negate a float";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_FREM: {
                              buffer->mnenomic = "frem";
                              buffer->hint = "value1, value2 -> result get the remainder from a division between two floats";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_FRETURN: {
                              buffer->mnenomic = "freturn";
                              buffer->hint = "value -> [empty] return a float";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_FSTORE: {
                              buffer->mnenomic = "fstore";
                              buffer->hint = "1: index value -> store a float value into a local variable #index";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_FSTORE_0: {
                              buffer->mnenomic = "fstore_0";
                              buffer->hint = "value -> store a float value into local variable 0";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_FSTORE_1: {
                              buffer->mnenomic = "fstore_1";
                              buffer->hint = "value -> store a float value into local variable 1";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_FSTORE_2: {
                              buffer->mnenomic = "fstore_2";
                              buffer->hint = "value -> store a float value into local variable 2";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_FSTORE_3: {
                              buffer->mnenomic = "fstore_3";
                              buffer->hint = "value -> store a float value into local variable 3";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_FSUB: {
                              buffer->mnenomic = "fsub";
                              buffer->hint = "value1, value2 -> result subtract two floats";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_GETFIELD: {
                              buffer->mnenomic = "getfield";
                              buffer->hint = "2: indexbyte1, indexbyte2 objectref -> value get a field value of an object objectref, where the field is identified by field reference in the constant pool index (indexbyte1 << 8 | indexbyte2)";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_GETSTATIC: {
                              buffer->mnenomic = "getstatic";
                              buffer->hint = "2: indexbyte1, indexbyte2 -> value get a static field value of a class, where the field is identified by field reference in the constant pool index (indexbyte1 << 8 | indexbyte2)";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_GOTO: {
                              buffer->mnenomic = "goto";
                              buffer->hint = "2: branchbyte1, branchbyte2 [no change] goes to another instruction at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 | branchbyte2)";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_GOTO_W: {
                              buffer->mnenomic = "goto_w";
                              buffer->hint = "4: branchbyte1, branchbyte2, branchbyte3, branchbyte4 [no change] goes to another instruction at branchoffset (signed int constructed from unsigned bytes branchbyte1 << 24 | branchbyte2 << 16 | branchbyte3 << 8 | branchbyte4)";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_I2B: {
                              buffer->mnenomic = "i2b";
                              buffer->hint = "value -> result convert an int into a byte";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_I2C: {
                              buffer->mnenomic = "i2c";
                              buffer->hint = "value -> result convert an int into a character";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_I2D: {
                              buffer->mnenomic = "i2d";
                              buffer->hint = "value -> result convert an int into a double";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_I2F: {
                              buffer->mnenomic = "i2f";
                              buffer->hint = "value -> result convert an int into a float";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_I2L: {
                              buffer->mnenomic = "i2l";
                              buffer->hint = "value -> result convert an int into a long";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_I2S: {
                              buffer->mnenomic = "i2s";
                              buffer->hint = "value -> result convert an int into a short";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_IADD: {
                              buffer->mnenomic = "iadd";
                              buffer->hint = "value1, value2 -> result add two ints";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_IALOAD: {
                              buffer->mnenomic = "iaload";
                              buffer->hint = "arrayref, index -> value load an int from an array";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_IAND: {
                              buffer->mnenomic = "iand";
                              buffer->hint = "value1, value2 -> result perform a bitwise AND on two integers";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_IASTORE: {
                              buffer->mnenomic = "iastore";
                              buffer->hint = "arrayref, index, value -> store an int into an array";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_ICONST_M1: {
                              buffer->mnenomic = "iconst_m1";
                              buffer->hint = "-> -1 load the int value 1 onto the stack";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_ICONST_0: {
                              buffer->mnenomic = "iconst_0";
                              buffer->hint = "-> 0 load the int value 0 onto the stack";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_ICONST_1: {
                              buffer->mnenomic = "iconst_1";
                              buffer->hint = "-> 1 load the int value 1 onto the stack";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_ICONST_2: {
                              buffer->mnenomic = "iconst_2";
                              buffer->hint = "-> 2 load the int value 2 onto the stack";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_ICONST_3: {
                              buffer->mnenomic = "iconst_3";
                              buffer->hint = "-> 3 load the int value 3 onto the stack";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_ICONST_4: {
                              buffer->mnenomic = "iconst_4";
                              buffer->hint = "-> 4 load the int value 4 onto the stack";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_ICONST_5: {
                              buffer->mnenomic = "iconst_5";
                              buffer->hint = "-> 5 load the int value 5 onto the stack";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_IDIV: {
                              buffer->mnenomic = "idiv";
                              buffer->hint = "value1, value2 -> result divide two integers";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_IF_ACMPEQ: {
                              buffer->mnenomic = "if_acmpeq";
                              buffer->hint = "2: branchbyte1, branchbyte2 value1, value2 -> if references are equal, branch to instruction at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 | branchbyte2)";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_IF_ACMPNE: {
                              buffer->mnenomic = "if_acmpne";
                              buffer->hint = "2: branchbyte1, branchbyte2 value1, value2 -> if references are not equal, branch to instruction at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 | branchbyte2)";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_IF_ICMPEQ: {
                              buffer->mnenomic = "if_icmpeq";
                              buffer->hint = "2: branchbyte1, branchbyte2 value1, value2 -> if ints are equal, branch to instruction at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 | branchbyte2)";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_IF_ICMPGE: {
                              buffer->mnenomic = "if_icmpge";
                              buffer->hint = "2: branchbyte1, branchbyte2 value1, value2 -> if value1 is greater than or equal to value2, branch to instruction at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 | branchbyte2)";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_IF_ICMPGT: {
                              buffer->mnenomic = "if_icmpgt";
                              buffer->hint = "2: branchbyte1, branchbyte2 value1, value2 -> if value1 is greater than value2, branch to instruction at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 | branchbyte2)";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_IF_ICMPLE: {
                              buffer->mnenomic = "if_icmple";
                              buffer->hint = "2: branchbyte1, branchbyte2 value1, value2 -> if value1 is less than or equal to value2, branch to instruction at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 | branchbyte2)";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_IF_ICMPLT: {
                              buffer->mnenomic = "if_icmplt";
                              buffer->hint = "2: branchbyte1, branchbyte2 value1, value2 -> if value1 is less than value2, branch to instruction at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 | branchbyte2)";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_IF_ICMPNE: {
                              buffer->mnenomic = "if_icmpne";
                              buffer->hint = "2: branchbyte1, branchbyte2 value1, value2 -> if ints are not equal, branch to instruction at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 | branchbyte2)";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_IFEQ: {
                              buffer->mnenomic = "ifeq";
                              buffer->hint = "2: branchbyte1, branchbyte2 value -> if value is 0, branch to instruction at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 | branchbyte2)";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_IFGE: {
                              buffer->mnenomic = "ifge";
                              buffer->hint = "2: branchbyte1, branchbyte2 value -> if value is greater than or equal to 0, branch to instruction at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 | branchbyte2)";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_IFGT: {
                              buffer->mnenomic = "ifgt";
                              buffer->hint = "2: branchbyte1, branchbyte2 value -> if value is greater than 0, branch to instruction at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 | branchbyte2)";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_IFLE: {
                              buffer->mnenomic = "ifle";
                              buffer->hint = "2: branchbyte1, branchbyte2 value -> if value is less than or equal to 0, branch to instruction at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 | branchbyte2)";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_IFLT: {
                              buffer->mnenomic = "iflt";
                              buffer->hint = "2: branchbyte1, branchbyte2 value -> if value is less than 0, branch to instruction at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 | branchbyte2)";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_IFNE: {
                              buffer->mnenomic = "ifne";
                              buffer->hint = "2: branchbyte1, branchbyte2 value -> if value is not 0, branch to instruction at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 | branchbyte2)";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_IFNONNULL: {
                              buffer->mnenomic = "ifnonnull";
                              buffer->hint = "2: branchbyte1, branchbyte2 value -> if value is not null, branch to instruction at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 | branchbyte2)";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_IFNULL: {
                              buffer->mnenomic = "ifnull";
                              buffer->hint = "2: branchbyte1, branchbyte2 value -> if value is null, branch to instruction at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 | branchbyte2)";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_IINC: {
                              buffer->mnenomic = "iinc";
                              buffer->hint = "2: index, const [No change] increment local variable #index by signed byte const";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_ILOAD: {
                              buffer->mnenomic = "iload";
                              buffer->hint = "1: index -> value load an int value from a local variable #index";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_ILOAD_0: {
                              buffer->mnenomic = "iload_0";
                              buffer->hint = "-> value load an int value from local variable 0";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_ILOAD_1: {
                              buffer->mnenomic = "iload_1";
                              buffer->hint = "-> value load an int value from local variable 1";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_ILOAD_2: {
                              buffer->mnenomic = "iload_2";
                              buffer->hint = "-> value load an int value from local variable 2";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_ILOAD_3: {
                              buffer->mnenomic = "iload_3";
                              buffer->hint = "-> value load an int value from local variable 3";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_IMPDEP1: {
                              buffer->mnenomic = "impdep1";
                              buffer->hint = "reserved for implementation-dependent operations within debuggers; should not appear in any class file";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_IMPDEP2: {
                              buffer->mnenomic = "impdep2";
                              buffer->hint = "reserved for implementation-dependent operations within debuggers; should not appear in any class file";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_IMUL: {
                              buffer->mnenomic = "imul";
                              buffer->hint = "value1, value2 -> result multiply two integers";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_INEG: {
                              buffer->mnenomic = "ineg";
                              buffer->hint = "value -> result negate int";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_INSTANCEOF: {
                              buffer->mnenomic = "instanceof";
                              buffer->hint = "2: indexbyte1, indexbyte2 objectref -> result determines if an object objectref is of a given type, identified by class reference index in constant pool (indexbyte1 << 8 | indexbyte2)";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_INVOKEDYNAMIC: {
                              buffer->mnenomic = "invokedynamic";
                              buffer->hint = "4: indexbyte1, indexbyte2, 0, 0 [arg1, arg2, ...] -> result invokes a dynamic method and puts the result on the stack (might be void); the method is identified by method reference index in constant pool (indexbyte1 << 8 | indexbyte2)";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_INVOKEINTERFACE: {
                              buffer->mnenomic = "invokeinterface";
                              buffer->hint = "4: indexbyte1, indexbyte2, count, 0 objectref, [arg1, arg2, ...] -> result invokes an interface method on object objectref and puts the result on the stack (might be void); the interface method is identified by method reference index in constant pool (indexbyte1 << 8 | indexbyte2)";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_INVOKESPECIAL: {
                              buffer->mnenomic = "invokespecial";
                              buffer->hint = "2: indexbyte1, indexbyte2 objectref, [arg1, arg2, ...] -> result invoke instance method on object objectref and puts the result on the stack (might be void); the method is identified by method reference index in constant pool (indexbyte1 << 8 | indexbyte2)";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_INVOKESTATIC: {
                              buffer->mnenomic = "invokestatic";
                              buffer->hint = "2: indexbyte1, indexbyte2 [arg1, arg2, ...] -> result invoke a static method and puts the result on the stack (might be void); the method is identified by method reference index in constant pool (indexbyte1 << 8 | indexbyte2)";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_INVOKEVIRTUAL: {
                              buffer->mnenomic = "invokevirtual";
                              buffer->hint = "2: indexbyte1, indexbyte2 objectref, [arg1, arg2, ...] -> result invoke virtual method on object objectref and puts the result on the stack (might be void); the method is identified by method reference index in constant pool (indexbyte1 << 8 | indexbyte2)";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_IOR: {
                              buffer->mnenomic = "ior";
                              buffer->hint = "value1, value2 -> result bitwise int OR";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_IREM: {
                              buffer->mnenomic = "irem";
                              buffer->hint = "value1, value2 -> result logical int remainder";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_IRETURN: {
                              buffer->mnenomic = "ireturn";
                              buffer->hint = "value -> [empty] return an integer from a method";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_ISHL: {
                              buffer->mnenomic = "ishl";
                              buffer->hint = "value1, value2 -> result int shift left";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_ISHR: {
                              buffer->mnenomic = "ishr";
                              buffer->hint = "value1, value2 -> result int arithmetic shift right";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_ISTORE: {
                              buffer->mnenomic = "istore";
                              buffer->hint = "1: index value -> store int value into variable #index";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_ISTORE_0: {
                              buffer->mnenomic = "istore_0";
                              buffer->hint = "value -> store int value into variable 0";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_ISTORE_1: {
                              buffer->mnenomic = "istore_1";
                              buffer->hint = "value -> store int value into variable 1";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_ISTORE_2: {
                              buffer->mnenomic = "istore_2";
                              buffer->hint = "value -> store int value into variable 2";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_ISTORE_3: {
                              buffer->mnenomic = "istore_3";
                              buffer->hint = "value -> store int value into variable 3";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_ISUB: {
                              buffer->mnenomic = "isub";
                              buffer->hint = "value1, value2 -> result int subtract";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_IUSHR: {
                              buffer->mnenomic = "iushr";
                              buffer->hint = "value1, value2 -> result int logical shift right";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_IXOR: {
                              buffer->mnenomic = "ixor";
                              buffer->hint = "value1, value2 -> result int xor";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_JSR: {
                              buffer->mnenomic = "jsr";
                              buffer->hint = "2: branchbyte1, branchbyte2 -> address jump to subroutine at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 | branchbyte2) and place the return address on the stack";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_JSR_W: {
                              buffer->mnenomic = "jsr_w";
                              buffer->hint = "4: branchbyte1, branchbyte2, branchbyte3, branchbyte4 -> address jump to subroutine at branchoffset (signed int constructed from unsigned bytes branchbyte1 << 24 | branchbyte2 << 16 | branchbyte3 << 8 | branchbyte4) and place the return address on the stack";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_L2D: {
                              buffer->mnenomic = "l2d";
                              buffer->hint = "value -> result convert a long to a double";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_L2F: {
                              buffer->mnenomic = "l2f";
                              buffer->hint = "value -> result convert a long to a float";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_L2I: {
                              buffer->mnenomic = "l2i";
                              buffer->hint = "value -> result convert a long to a int";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_LADD: {
                              buffer->mnenomic = "ladd";
                              buffer->hint = "value1, value2 -> result add two longs";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_LALOAD: {
                              buffer->mnenomic = "laload";
                              buffer->hint = "arrayref, index -> value load a long from an array";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_LAND: {
                              buffer->mnenomic = "land";
                              buffer->hint = "value1, value2 -> result bitwise AND of two longs";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_LASTORE: {
                              buffer->mnenomic = "lastore";
                              buffer->hint = "arrayref, index, value -> store a long to an array";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_LCMP: {
                              buffer->mnenomic = "lcmp";
                              buffer->hint = "value1, value2 -> result push 0 if the two longs are the same, 1 if value1 is greater than value2, -1 otherwise";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_LCONST_0: {
                              buffer->mnenomic = "lconst_0";
                              buffer->hint = "-> 0L push 0L (the number zero with type long) onto the stack";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_LCONST_1: {
                              buffer->mnenomic = "lconst_1";
                              buffer->hint = "-> 1L push 1L (the number one with type long) onto the stack";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_LDC: {
                              buffer->mnenomic = "ldc";
                              buffer->hint = "1: index -> value push a constant #index from a constant pool (String, int, float, Class, java.lang.invoke.MethodType, java.lang.invoke.MethodHandle, or a dynamically-computed constant) onto the stack";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_LDC_W: {
                              buffer->mnenomic = "ldc_w";
                              buffer->hint = "2: indexbyte1, indexbyte2 -> value push a constant #index from a constant pool (String, int, float, Class, java.lang.invoke.MethodType, java.lang.invoke.MethodHandle, or a dynamically-computed constant) onto the stack (wide index is constructed as indexbyte1 << 8 | indexbyte2)";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_LDC2_W: {
                              buffer->mnenomic = "ldc2_w";
                              buffer->hint = "2: indexbyte1, indexbyte2 -> value push a constant #index from a constant pool (double, long, or a dynamically-computed constant) onto the stack (wide index is constructed as indexbyte1 << 8 | indexbyte2)";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_LDIV: {
                              buffer->mnenomic = "ldiv";
                              buffer->hint = "value1, value2 -> result divide two longs";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_LLOAD: {
                              buffer->mnenomic = "lload";
                              buffer->hint = "1: index -> value load a long value from a local variable #index";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_LLOAD_0: {
                              buffer->mnenomic = "lload_0";
                              buffer->hint = "-> value load a long value from a local variable 0";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_LLOAD_1: {
                              buffer->mnenomic = "lload_1";
                              buffer->hint = "-> value load a long value from a local variable 1";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_LLOAD_2: {
                              buffer->mnenomic = "lload_2";
                              buffer->hint = "-> value load a long value from a local variable 2";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_LLOAD_3: {
                              buffer->mnenomic = "lload_3";
                              buffer->hint = "-> value load a long value from a local variable 3";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_LMUL: {
                              buffer->mnenomic = "lmul";
                              buffer->hint = "value1, value2 -> result multiply two longs";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_LNEG: {
                              buffer->mnenomic = "lneg";
                              buffer->hint = "value -> result negate a long";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_LOOKUPSWITCH: {
                              buffer->mnenomic = "lookupswitch";
                              buffer->hint = "8+: <0-3 bytes padding>, defaultbyte1, defaultbyte2, defaultbyte3, defaultbyte4, npairs1, npairs2, npairs3, npairs4, match-offset pairs... key -> a target address is looked up from a table using a key and execution continues from the instruction at that address";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_LOR: {
                              buffer->mnenomic = "lor";
                              buffer->hint = "value1, value2 -> result bitwise OR of two longs";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_LREM: {
                              buffer->mnenomic = "lrem";
                              buffer->hint = "value1, value2 -> result remainder of division of two longs";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_LRETURN: {
                              buffer->mnenomic = "lreturn";
                              buffer->hint = "value -> [empty] return a long value";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_LSHL: {
                              buffer->mnenomic = "lshl";
                              buffer->hint = "value1, value2 -> result bitwise shift left of a long value1 by int value2 positions";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_LSHR: {
                              buffer->mnenomic = "lshr";
                              buffer->hint = "value1, value2 -> result bitwise shift right of a long value1 by int value2 positions";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_LSTORE: {
                              buffer->mnenomic = "lstore";
                              buffer->hint = "1: index value -> store a long value in a local variable #index";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_LSTORE_0: {
                              buffer->mnenomic = "lstore_0";
                              buffer->hint = "value -> store a long value in a local variable 0";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_LSTORE_1: {
                              buffer->mnenomic = "lstore_1";
                              buffer->hint = "value -> store a long value in a local variable 1";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_LSTORE_2: {
                              buffer->mnenomic = "lstore_2";
                              buffer->hint = "value -> store a long value in a local variable 2";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_LSTORE_3: {
                              buffer->mnenomic = "lstore_3";
                              buffer->hint = "value -> store a long value in a local variable 3";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_LSUB: {
                              buffer->mnenomic = "lsub";
                              buffer->hint = "value1, value2 -> result subtract two longs";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_LUSHR: {
                              buffer->mnenomic = "lushr";
                              buffer->hint = "value1, value2 -> result bitwise shift right of a long value1 by int value2 positions, unsigned";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_LXOR: {
                              buffer->mnenomic = "lxor";
                              buffer->hint = "value1, value2 -> result bitwise XOR of two longs";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_MONITORENTER: {
                              buffer->mnenomic = "monitorenter";
                              buffer->hint = "objectref -> enter monitor for object (\" grab the lock \" - start of synchronized() section)";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_MONITOREXIT: {
                              buffer->mnenomic = "monitorexit";
                              buffer->hint = "objectref -> exit monitor for object (\" release the lock \" - end of synchronized() section)";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_MULTIANEWARRAY: {
                              buffer->mnenomic = "multianewarray";
                              buffer->hint = "3: indexbyte1, indexbyte2, dimensions count1, [count2,...] -> arrayref create a new array of dimensions dimensions of type identified by class reference in constant pool index (indexbyte1 << 8 | indexbyte2); the sizes of each dimension is identified by count1, [count2, etc.]";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_NEW: {
                              buffer->mnenomic = "new";
                              buffer->hint = "2: indexbyte1, indexbyte2 -> objectref create new object of type identified by class reference in constant pool index (indexbyte1 << 8 | indexbyte2)";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_NEWARRAY: {
                              buffer->mnenomic = "newarray";
                              buffer->hint = "1: atype count -> arrayref create new array with count elements of primitive type identified by atype";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_NOP: {
                              buffer->mnenomic = "nop";
                              buffer->hint = "[No change] perform no operation";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_POP: {
                              buffer->mnenomic = "pop";
                              buffer->hint = "value -> discard the top value on the stack";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_POP2: {
                              buffer->mnenomic = "pop2";
                              buffer->hint = "{value2, value1} -> discard the top two values on the stack (or one value, if it is a double or long)";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_PUTFIELD: {
                              buffer->mnenomic = "putfield";
                              buffer->hint = "2: indexbyte1, indexbyte2 objectref, value -> set field to value in an object objectref, where the field is identified by a field reference index in constant pool (indexbyte1 << 8 | indexbyte2)";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_PUTSTATIC: {
                              buffer->mnenomic = "putstatic";
                              buffer->hint = "2: indexbyte1, indexbyte2 value -> set static field to value in a class, where the field is identified by a field reference index in constant pool (indexbyte1 << 8 | indexbyte2)";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_RET: {
                              buffer->mnenomic = "ret";
                              buffer->hint = "1: index [No change] continue execution from address taken from a local variable #index (the asymmetry with jsr is intentional)";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_RETURN: {
                              buffer->mnenomic = "return";
                              buffer->hint = "-> [empty] return void from method";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_SALOAD: {
                              buffer->mnenomic = "saload";
                              buffer->hint = "arrayref, index -> value load short from array";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_SASTORE: {
                              buffer->mnenomic = "sastore";
                              buffer->hint = "arrayref, index, value -> store short to array";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_SIPUSH: {
                              buffer->mnenomic = "sipush";
                              buffer->hint = "2: byte1, byte2 -> value push a short onto the stack as an integer value";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_SWAP: {
                              buffer->mnenomic = "swap";
                              buffer->hint = "value2, value1 -> value1, value2 swaps two top words on the stack (note that value1 and value2 must not be double or long)";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_TABLESWITCH: {
                              buffer->mnenomic = "tableswitch";
                              buffer->hint = "16+: [0-3 bytes padding], defaultbyte1, defaultbyte2, defaultbyte3, defaultbyte4, lowbyte1, lowbyte2, lowbyte3, lowbyte4, highbyte1, highbyte2, highbyte3, highbyte4, jump offsets... index -> continue execution from an address in the table at offset index";
                              break;
                        }
                        case luramas::disassembler::JVM::optable::data::instructions::OP_WIDE: {
                              buffer->mnenomic = "wide";
                              buffer->hint = "3/5: opcode, indexbyte1, indexbyte2 or iinc, indexbyte1, indexbyte2, countbyte1, countbyte2 [same as for corresponding instructions] execute opcode, where opcode is either iload, fload, aload, lload, dload, istore, fstore, astore, lstore, dstore, or ret, but assume the index is 16 bit; or execute iinc, where the index is 16 bits and the constant to increment by is a signed 16 bit short";
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