#pragma once
#include "../../../common.hpp"
#include <array>
#include <cstdint>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

namespace luramas::il::arch {

      namespace str {

            static constexpr auto OP_NOP = "nop";
            static constexpr auto OP_LOADBOOL = "loadbool";
            static constexpr auto OP_LOADINT = "loadint";
            static constexpr auto OP_LOADNONE = "loadnone";
            static constexpr auto OP_LOADKVAL = "loadkval";
            static constexpr auto OP_LOADGLOBAL = "loadglobal";
            static constexpr auto OP_GETTABUPVALUE = "gettabupvalue";
            static constexpr auto OP_SETGLOBAL = "setglobal";
            static constexpr auto OP_MOVE = "move";
            static constexpr auto OP_ADD = "add";
            static constexpr auto OP_SUB = "sub";
            static constexpr auto OP_MUL = "mul";
            static constexpr auto OP_DIV = "div";
            static constexpr auto OP_MOD = "mod";
            static constexpr auto OP_POW = "pow";
            static constexpr auto OP_AND = "and";
            static constexpr auto OP_XOR = "xor";
            static constexpr auto OP_SHL = "shl";
            static constexpr auto OP_SHR = "shr";
            static constexpr auto OP_IDIV = "idiv";
            static constexpr auto OP_OR = "or";
            static constexpr auto OP_ADDK = "addk";
            static constexpr auto OP_SUBK = "subk";
            static constexpr auto OP_MULK = "mulk";
            static constexpr auto OP_DIVK = "divk";
            static constexpr auto OP_MODK = "modk";
            static constexpr auto OP_POWK = "powk";
            static constexpr auto OP_ANDK = "andk";
            static constexpr auto OP_XORK = "xork";
            static constexpr auto OP_SHLK = "shlk";
            static constexpr auto OP_SHRK = "shrk";
            static constexpr auto OP_IDIVK = "idivk";
            static constexpr auto OP_ORK = "ork";
            static constexpr auto OP_ADDN = "addn";
            static constexpr auto OP_SUBN = "subn";
            static constexpr auto OP_MULN = "muln";
            static constexpr auto OP_DIVN = "divn";
            static constexpr auto OP_MODN = "modn";
            static constexpr auto OP_POWN = "pown";
            static constexpr auto OP_ANDN = "andn";
            static constexpr auto OP_XORN = "xorn";
            static constexpr auto OP_SHLN = "shln";
            static constexpr auto OP_SHRN = "shrn";
            static constexpr auto OP_IDIVN = "idivn";
            static constexpr auto OP_ORN = "orn";
            static constexpr auto OP_LEN = "len";
            static constexpr auto OP_NOT = "not";
            static constexpr auto OP_MINUS = "minus";
            static constexpr auto OP_BITNOT = "bitnot";
            static constexpr auto OP_PLUS = "plus";
            static constexpr auto OP_REF = "ref";
            static constexpr auto OP_CCALL = "ccall";
            static constexpr auto OP_VCALL = "vcall";
            static constexpr auto OP_VPUSH = "vpush";
            static constexpr auto OP_SELF = "self";
            static constexpr auto OP_RETURN = "return";
            static constexpr auto OP_CONCAT = "concat";
            static constexpr auto OP_JUMP = "jump";
            static constexpr auto OP_CMP = "cmp";
            static constexpr auto OP_CMPK = "cmpk";
            static constexpr auto OP_CMPN = "cmpn";
            static constexpr auto OP_CMPB = "cmpb";
            static constexpr auto OP_CMPNONE = "cmpnone";
            static constexpr auto OP_CMPS = "cmps";
            static constexpr auto OP_CMPSK = "cmpsk";
            static constexpr auto OP_CMPSN = "cmpsn";
            static constexpr auto OP_CMPSNONE = "cmpsnone";
            static constexpr auto OP_JUMPIF = "jumpif";
            static constexpr auto OP_JUMPIFNOT = "jumpifnot";
            static constexpr auto OP_JUMPIFEQUAL = "jumpifequal";
            static constexpr auto OP_JUMPIFNOTEQUAL = "jumpifnotequal";
            static constexpr auto OP_JUMPIFLESS = "jumpiflessthan";
            static constexpr auto OP_JUMPIFLESSEQUAL = "jumpiflessthanequal";
            static constexpr auto OP_JUMPIFGREATER = "jumpifgreater";
            static constexpr auto OP_JUMPIFGREATEREQUAL = "jumpifgreaterequal";
            static constexpr auto OP_SETIF = "setif";
            static constexpr auto OP_SETIFNOT = "setifnot";
            static constexpr auto OP_SETIFEQUAL = "setifequal";
            static constexpr auto OP_SETIFNOTEQUAL = "setifnotequal";
            static constexpr auto OP_SETIFLESS = "setifless";
            static constexpr auto OP_SETIFLESSEQUAL = "setiflessequal";
            static constexpr auto OP_SETIFGREATER = "setifgreater";
            static constexpr auto OP_SETIFGREATEREQUAL = "setifgreaterequal";
            static constexpr auto OP_SETUPVALUE = "setupvalue";
            static constexpr auto OP_GETUPVALUE = "getupvalue";
            static constexpr auto OP_DESTROYUPVALUES = "destroyupvalues";
            static constexpr auto OP_DESTROYUPVALUESA = "destroyupvaluesa";
            static constexpr auto OP_ADDUPVALUE = "addupvalue";
            static constexpr auto OP_INIT = "init";
            static constexpr auto OP_BITCAST = "bitcast";
            static constexpr auto OP_GETVARIADIC = "getvariadic";
            static constexpr auto OP_SETTABLE = "settable";
            static constexpr auto OP_GETTABLE = "gettable";
            static constexpr auto OP_SETTABLEN = "settablen";
            static constexpr auto OP_GETTABLEN = "gettablen";
            static constexpr auto OP_SETTABLEK = "settablek";
            static constexpr auto OP_GETTABLEK = "gettablek";
            static constexpr auto OP_INITFORLOOPN = "initforloopn";
            static constexpr auto OP_INITFORLOOPG = "initforloopg";
            static constexpr auto OP_INITFORLOOPSPECIAL = "initforloopspecial";
            static constexpr auto OP_NEWCLOSURE = "newclosure";
            static constexpr auto OP_REFCLOSURE = "refclosure";
            static constexpr auto OP_NEWTABLE = "newtable";
            static constexpr auto OP_REFTABLE = "reftable";
            static constexpr auto OP_NEWTABLEA = "newtablea";
            static constexpr auto OP_REFTABLEA = "reftablea";
            static constexpr auto OP_SETLIST = "setlist";
            static constexpr auto OP_FORLOOPG = "forloopg";
            static constexpr auto OP_FORLOOPN = "forloopn";
            static constexpr auto OP_POPTOP = "poptop";
            static constexpr auto OP_POPARG = "poparg";
            static constexpr auto OP_MEMSET = "memset";
            static constexpr auto OP_MEMREAD = "memread";
            static constexpr auto OP_SETFLAG = "setflag";
            static constexpr auto OP_SALLOC = "salloc";
            static constexpr auto OP_GETSTACK = "getstack";
            static constexpr auto OP_SETSTACK = "setstack";
            static constexpr auto OP_STACKPUSH = "stackpush";
            static constexpr auto OP_STACKPOP = "stackpop";
            static constexpr auto OP_POPTOPSTACK = "poptopstack";
            static constexpr auto OP_CLOGIC_AND = "clogic_and";
            static constexpr auto OP_CLOGIC_OR = "clogic_or";
            static constexpr auto OP_PEND = "pend";
            static constexpr auto OP_MARK = "mark";
            static constexpr auto OP_MOBJ_CAST = "mobj_cast";
            static constexpr auto OP_NCTOR_MOBJ = "nctor_mobj";
            static constexpr auto OP_SCALL = "scall";
            static constexpr auto OP_FLAGSET = "flagset";
            static constexpr auto OP_FLAGREAD = "flagread";
            static constexpr auto OP_CREATE_STACK = "create_stack";
            static constexpr auto OP_PRETURN = "preturn";
            static constexpr auto OP_STARTPAGEFUNC = "startpagefunc";
            static constexpr auto OP_ENDPAGEFUNC = "endpagefunc";
            static constexpr auto OP_PCALL = "pcall";
            static constexpr auto OP_PJUMP = "pjump";
            static constexpr auto OP_SEGREGATE = "segregate";
            static constexpr auto OP_COMBINE = "combine";
            static constexpr auto OP_FLAGJUMP = "flagjump";
            static constexpr auto OP_ICALL = "icall";
            static constexpr auto OP_TAG_START = "tag_start";
            static constexpr auto OP_TAG_KV = "tag_kv";
            static constexpr auto OP_TAG_END = "tag_end";
            static constexpr auto OP_METADATA = "metadata";
            static constexpr auto OP_ENTRY_POINT = "entry_point";
            static constexpr auto OP_COMMAND = "command";
            static constexpr auto OP_BITREAD = "bitread";
            static constexpr auto OP_BITWRITE = "bitwrite";
            static constexpr auto OP_BITWRITEA = "bitwritea";
            static constexpr auto OP_ANNOTATE_PREV = "annotate_prev";
      } // namespace str

      namespace data {

            /* Flags */
            enum class flags : std::uint8_t {

                  fno_return = 0u,          /* No return? */
                  fcall_return_on_stack,    /* ADD CALL RETURN ADDR TO THE STACK */
                  fvolatile,                /* Volatile */
                  funknown_paging,          /* Paging results, args unkown */
                  fexpanded_non_direct_cft, /* Was expanded from a non direct control flow transfer */
                  ffunc,                    /* Function in call native provided by luramas */
                  fexternal_page_goto,      /* External page goto (return can not be garunteed) */
                  fcompare,                 /* Compare */
                  fnative_global,           /* Native global */
                  fatomic,                  /* Atomic */
                  fwild_global,             /* Global is a wild card */
                  fglobal_user_defined,     /* Global is user defined */
                  finternal_store,          /* Store done internally? */
            };

            /* Binary operation kinds. OP, HINT, SHORTENED NAME(strlen <= 2) */
            enum class bin_kinds : std::uint8_t {

                  nothing = 0u,

                  /* Arith */
                  add_,  /* (+) Arithmetic Addition, (A) */
                  sub_,  /* (-) Arithmetic Subtraction (S) */
                  mul_,  /* (*) Arithmetic Multiplication (M) */
                  div_,  /* (/) Arithmetic Division (D) */
                  idiv_, /* (//) Arithmetic Floor Division (ID) */
                  mod_,  /* (%) Arithmetic Modulus (MO) */
                  pow_,  /* (^) Arithmetic Power (P) */
                  and_,  /* (&) Arithmetic And (AN) */
                  xor_,  /* (~) Arithmetic Xor (X) */
                  shl_,  /* (<<) Arithmetic Shift Left (SL) */
                  shr_,  /* (>>) Arithmetic Shift Right (SR) */
                  or_,   /* (|) Arithmetic Unary Or (O) */

                  /* Unary */
                  len_,    /* (#) Length of array/vector/table. (L) */
                  minus_,  /* (-) Unary minus (MI) */
                  not_,    /* (NOT/!) Unary not (N) */
                  bitnot_, /* (~) Unary bitnot (BN) */
                  plus_,   /* (+) Unary plus (P) */
                  ref_,    /* (&) Unary reference (R) */

                  /* Compares, for both set cmp flags and jmps with compare. */
                  eq_,  /* (==) (EQ) */
                  ne_,  /* (!=) (NE) */
                  lt_,  /* (<) (LT) */
                  lte_, /* (<=) (LE) */
                  gt_,  /* (>) (GT) */
                  gte_, /* (>=) (GE) */
                  nt_,  /* (IMPLICIT != true) (NT) */
                  et_,  /* (IMPLICIT == true) (ET) */

                  amount /* PSUEDO */
            };

            /* Kvalue kinds | Encoding */
            enum class kval_kinds : std::uint8_t {

                  nothing = 0u,
                  none,     /* None kind */
                  boolean,  /* Boolean kind */
                  integer,  /* Integer kind */
                  string,   /* String kind */
                  userdata, /* Userdata kind   */
                  table,    /* Table kind, *NODE SIZE(unsigned 64-Bits), *ARRAY SIZE(unsigned 64-Bits) */
                  function, /* Function kind  */
                  closure,  /* Proto kind, *CLOSURE ID(unsigned 32-Bits)  */
                  thread,   /* Thread kind */
                  upvalue,  /* Proto kind  */
                  vector    /* Array kind */
            };

            inline const char *const bin_kindstr(const bin_kinds kind) {
                  switch (kind) {
                        case bin_kinds::add_: {
                              return "+";
                        }
                        case bin_kinds::sub_: {
                              return "-";
                        }
                        case bin_kinds::mul_: {
                              return "*";
                        }
                        case bin_kinds::div_: {
                              return "/";
                        }
                        case bin_kinds::idiv_: {
                              return "//";
                        }
                        case bin_kinds::mod_: {
                              return "%";
                        }
                        case bin_kinds::pow_: {
                              return "^";
                        }
                        case bin_kinds::and_: {
                              return "&";
                        }
                        case bin_kinds::xor_: {
                              return "~";
                        }
                        case bin_kinds::shl_: {
                              return "<<";
                        }
                        case bin_kinds::shr_: {
                              return ">>";
                        }
                        case bin_kinds::or_: {
                              return "|";
                        }
                        case bin_kinds::len_: {
                              return "#";
                        }
                        case bin_kinds::minus_: {
                              return "-";
                        }
                        case bin_kinds::not_:
                        case bin_kinds::nt_: {
                              return "not ";
                        }
                        case bin_kinds::bitnot_: {
                              return "~";
                        }
                        case bin_kinds::ref_: {
                              return "&";
                        }
                        case bin_kinds::plus_: {
                              return "+";
                        }
                        case bin_kinds::eq_: {
                              return "==";
                        }
                        case bin_kinds::ne_: {
                              return "~=";
                        }
                        case bin_kinds::lt_: {
                              return "<";
                        }
                        case bin_kinds::lte_: {
                              return "<=";
                        }
                        case bin_kinds::gt_: {
                              return ">";
                        }
                        case bin_kinds::gte_: {
                              return ">=";
                        }
                        case bin_kinds::et_: {
                              return "ET";
                        }
                        default: {
#ifdef LURAMAS_ECC
                              luramas::error::unexpected_error("binkind " + std::to_string(static_cast<std::int32_t>(kind)));
#endif // LURAMAS_ECC
                              return "Unknown";
                        }
                  }
            }

            /* Flip binkind */
            inline bin_kinds bin_kindflip(const bin_kinds kind) {
                  switch (kind) {
                        case bin_kinds::add_: {
                              return bin_kinds::sub_;
                        }
                        case bin_kinds::sub_: {
                              return bin_kinds::add_;
                        }
                        case bin_kinds::mul_: {
                              return bin_kinds::div_;
                        }
                        case bin_kinds::div_: {
                              return bin_kinds::mul_;
                        }
                        case bin_kinds::idiv_:
                        case bin_kinds::mod_:
                        case bin_kinds::pow_:
                        case bin_kinds::and_:
                        case bin_kinds::xor_:
                        case bin_kinds::ref_:
                        case bin_kinds::bitnot_: {
                              return kind;
                        }
                        case bin_kinds::shl_: {
                              return bin_kinds::shr_;
                        }
                        case bin_kinds::shr_: {
                              return bin_kinds::shl_;
                        }
                        case bin_kinds::or_: {
                              return bin_kinds::or_;
                        }
                        case bin_kinds::len_: {
                              return bin_kinds::len_;
                        }
                        case bin_kinds::minus_: {
                              return bin_kinds::plus_;
                        }
                        case bin_kinds::not_: {
                              return bin_kinds::nothing;
                        }
                        case bin_kinds::plus_: {
                              return bin_kinds::not_;
                        }
                        case bin_kinds::eq_: {
                              return bin_kinds::ne_;
                        }
                        case bin_kinds::ne_: {
                              return bin_kinds::eq_;
                        }
                        case bin_kinds::lt_: {
                              return bin_kinds::gt_;
                        }
                        case bin_kinds::lte_: {
                              return bin_kinds::gt_;
                        }
                        case bin_kinds::gt_: {
                              return bin_kinds::lt_;
                        }
                        case bin_kinds::gte_: {
                              return bin_kinds::lt_;
                        }
                        case bin_kinds::nt_: {
                              return bin_kinds::et_;
                        }
                        case bin_kinds::et_: {
                              return bin_kinds::nt_;
                        }
                        default: {
                              return bin_kinds::nothing;
                        }
                  }
            }

            namespace is_kinds {

                  /* Equality kind? */
                  inline bool equality(const bin_kinds kind) {
                        switch (kind) {
                              case luramas::il::arch::data::bin_kinds::eq_:
                              case luramas::il::arch::data::bin_kinds::ne_:
                              case luramas::il::arch::data::bin_kinds::lt_:
                              case luramas::il::arch::data::bin_kinds::gt_:
                              case luramas::il::arch::data::bin_kinds::lte_:
                              case luramas::il::arch::data::bin_kinds::gte_: {
                                    return true;
                              }
                              default: {
                                    return false;
                              }
                        }
                  }

                  /* Non-communative conditional kind? */
                  inline bool swap_side_effects(const bin_kinds kind) {
                        switch (kind) {
                              case luramas::il::arch::data::bin_kinds::lt_:
                              case luramas::il::arch::data::bin_kinds::gt_:
                              case luramas::il::arch::data::bin_kinds::lte_:
                              case luramas::il::arch::data::bin_kinds::gte_: {
                                    return true;
                              }
                              default: {
                                    return false;
                              }
                        }
                  }

                  /* Unary kind? */
                  inline bool unary(const bin_kinds kind) {
                        switch (kind) {
                              case luramas::il::arch::data::bin_kinds::nt_:
                              case luramas::il::arch::data::bin_kinds::len_:
                              case luramas::il::arch::data::bin_kinds::not_:
                              case luramas::il::arch::data::bin_kinds::plus_:
                              case luramas::il::arch::data::bin_kinds::minus_:
                              case luramas::il::arch::data::bin_kinds::bitnot_: {
                                    return true;
                              }
                              default: {
                                    return false;
                              }
                        }
                  }

                  /* Arithmetic kind? */
                  inline bool arith(const bin_kinds kind) {
                        switch (kind) {
                              case luramas::il::arch::data::bin_kinds::or_:
                              case luramas::il::arch::data::bin_kinds::add_:
                              case luramas::il::arch::data::bin_kinds::sub_:
                              case luramas::il::arch::data::bin_kinds::mul_:
                              case luramas::il::arch::data::bin_kinds::div_:
                              case luramas::il::arch::data::bin_kinds::mod_:
                              case luramas::il::arch::data::bin_kinds::pow_:
                              case luramas::il::arch::data::bin_kinds::and_:
                              case luramas::il::arch::data::bin_kinds::xor_:
                              case luramas::il::arch::data::bin_kinds::shl_:
                              case luramas::il::arch::data::bin_kinds::shr_:
                              case luramas::il::arch::data::bin_kinds::idiv_: {
                                    return true;
                              }
                              default: {
                                    return false;
                              }
                        }
                  }

                  /* Not type kind? */
                  inline bool not_k(const bin_kinds kind) {
                        switch (kind) {
                              case luramas::il::arch::data::bin_kinds::nt_:
                              case luramas::il::arch::data::bin_kinds::not_: {
                                    return true;
                              }
                              default: {
                                    return false;
                              }
                        }
                  }

                  /* Conditional kind? */
                  inline bool condition(const bin_kinds kind) {
                        if (equality(kind)) {
                              return true;
                        }
                        switch (kind) {
                              case luramas::il::arch::data::bin_kinds::et_:
                              case luramas::il::arch::data::bin_kinds::nt_: {
                                    return true;
                              }
                              default: {
                                    return false;
                              }
                        }
                  }

                  /* Bitwise kind? */
                  inline bool bitwise(const bin_kinds kind) {
                        switch (kind) {
                              case luramas::il::arch::data::bin_kinds::xor_:
                              case luramas::il::arch::data::bin_kinds::bitnot_:
                              case luramas::il::arch::data::bin_kinds::shl_:
                              case luramas::il::arch::data::bin_kinds::shr_:
                              case luramas::il::arch::data::bin_kinds::and_:
                              case luramas::il::arch::data::bin_kinds::or_: {
                                    return true;
                              }
                              default: {
                                    return false;
                              }
                        }
                  }
            } // namespace is_kinds

      } // namespace data

      namespace operand {

            static constexpr auto OPERAND_MAX_SIZE = 7u;

            /* Encoding translation | Encoding */
            enum class operand_kind : std::uint8_t {
                  none,            /* Nothing | None object. */
                  reg,             /* reg | Register. */
                  kval,            /* idx | Kvalue. */
                  kval_string,     /* idx | Kvalue string. */
                  jmp,             /* jmp | Jump. */
                  integer,         /* integer | Integer. */
                  boolean,         /* boolean | Boolean. */
                  upvalue_kind,    /* idx | Upvalue kind. */
                  upvalue,         /* idx | Upvalue. */
                  upvalue_capture, /* reg | Capture upvalue. */
                  closure,         /* idx | Closure. */
                  table_size,      /* size | Table size. */
                  value,           /* value | Generic value. */
                  closure_index    /* idx | Closure index for closure stack. */
            };

            /* Operand encoding kinds (Bits, Functionality) */
            enum class operand_encoding : std::uint8_t {
                  reg,      /* [(signed)16-Bits] Register. */
                  idx,      /* [(unsigned)32-Bits] Generic index. */
                  jmp,      /* [(signed)64-Bits] Jump. */
                  integer,  /* [double] Integer. */
                  boolean,  /* [(unsigned)8-Bits] Boolean. */
                  enumeral, /* [(unsigned)8-Bits] Generic 8-bit enumeral type. */
                  value     /* [(signed)32-Bits] Generic value. */
            };

            /* Upvalue kinds */
            enum class upvalue_kind : std::uint8_t {
                  contents,  /* Capture contents of register. */
                  reference, /* Register reference */
                  upvalues   /* Capture contents from upvalue index. */
            };

            /* Operand disassembly */
            union operand_disassembly {
                  luramas_register reg;        /* Generic register. */
                  std::intptr_t kvalue_idx;    /* Kvalue index for kvalue stack. */
                  std::intptr_t closure_idx;   /* Closure index for closure stack. */
                  std::intptr_t upvalue_idx;   /* Upvalue index for upvalue stack. */
                  std::intptr_t jmp;           /* Jump. */
                  double integer;              /* Integer value. */
                  bool boolean;                /* Boolean value. */
                  upvalue_kind upvalue_kind;   /* Upvalue captured type. */
                  luramas_address upvalue_reg; /* Upvalue register. */
                  std::size_t closure_id;      /* Closure index for Kvalues. */
                  std::size_t table_size;      /* Size of table element. */
                  std::intptr_t val;           /* Generic value. */
            };

            /* Disassembly struct for operands */
            struct operand {

                  operand_kind type = operand_kind::none;                    /* Type of operand */
                  data::kval_kinds k_value_kind = data::kval_kinds::nothing; /* Kvalue king */

                  operand_disassembly dis; /* Disassembly */

                  luramas_address ref_addr = 0u;         /* reference address by operand. */
                  std::string k_value = "";              /* Seperate value to represent as a string and idx. Will also serve as import str. */
                  std::optional<std::string> annotation; /* Annotation for operand. */
                  bool multret = false;                  /* Original value was changed by multret. */
            };

      } // namespace operand

      /* Opcode Legend (Opcode, Hint, Operands):
                Register: "r??"
                Kvalue: "??"
                Integer(Double): "??"
                Jump: "+/-??" (When generating it goes by amount of instructions before or after)
                UpvalueID: "u??"
                GlobalID: "??"
                Boolean: "true/false"
                UpvalueKind: see upvalue_kind
                ClosureID: "c??"
                Val(Intptr): "??",
                Virtual_Function: "??",
                Table_Size: "??" ,
                Size: sizeof(int8_t), sizeof(int16_t), sizeof(in32_t), sizeof(int64_t)
       */
      enum class opcodes : std::uint8_t {

            OP_NOP, /* Nothing */

            OP_LOADBOOL,   /* Loads a boolean to the destination register | * Dest(Register), * Source(Boolean) */
            OP_LOADINT,    /* Loads a integer to the destination register | * Dest(Register), * Source(Integer) */
            OP_LOADNONE,   /* Loads a None to the destination register | * Dest(Register) */
            OP_LOADKVAL,   /* Loads a kvalue to the destination register | * Dest(Register), * Source(Kvalue) */
            OP_LOADGLOBAL, /* Loads a global to the destination register | * Dest(Register), * Source(GlobalID) */

            OP_GETTABUPVALUE, /* Loads a kvalue from structure to the destination register | * Dest(Register), * Source(Kvalue) */
            OP_SETGLOBAL,     /* Set global | * Source(Register), * Dest(GlobalID) */

            /* Move | Dest(Register), Source(Register) */
            OP_MOVE,

            /* Arith/Bitwise | * Dest(Register), * Source(Register), * Value(Register)  */
            OP_ADD,  /*  +  */
            OP_SUB,  /*  -  */
            OP_MUL,  /*  *  */
            OP_DIV,  /*  /  */
            OP_MOD,  /*  %  */
            OP_POW,  /*  ^  */
            OP_AND,  /*  &  */
            OP_XOR,  /*  ~  */
            OP_SHL,  /*  << */
            OP_SHR,  /*  >> */
            OP_IDIV, /*  // */
            OP_OR,   /*  |  */

            /* Arith/Bitwise Kvalue | * Dest(Register), * Source(Register) * Value(Kvalue) */
            OP_ADDK,  /*  +  */
            OP_SUBK,  /*  -  */
            OP_MULK,  /*  *  */
            OP_DIVK,  /*  /  */
            OP_MODK,  /*  %  */
            OP_POWK,  /*  ^  */
            OP_ANDK,  /*  &  */
            OP_XORK,  /*  ~  */
            OP_SHLK,  /*  << */
            OP_SHRK,  /*  >> */
            OP_IDIVK, /*  // */
            OP_ORK,   /*  |  */

            /* Arith/Bitwise Integer | * Dest(Register), * Source(Register), * Value(Integer) */
            OP_ADDN,  /* +  */
            OP_SUBN,  /* -  */
            OP_MULN,  /* *  */
            OP_DIVN,  /* /  */
            OP_MODN,  /* %  */
            OP_POWN,  /* ^  */
            OP_ANDN,  /* &  */
            OP_XORN,  /* ~  */
            OP_SHLN,  /* << */
            OP_SHRN,  /* >> */
            OP_IDIVN, /* // */
            OP_ORN,   /* |  */

            /* Unary | * Dest(Register), * Source(Register) */
            OP_LEN,    /* #   */
            OP_NOT,    /* not */
            OP_MINUS,  /* -   */
            OP_BITNOT, /* ~   */
            OP_PLUS,   /* +   */
            OP_REF,    /* &   */

            /* C function and closure call | * Dest(Register), * Arguement count(Val), * Return count(Val) */
            OP_CCALL,

            /* Virtual function call (clears virtual function arguement stack once executed) | * Dest(Register), * Virtual function(ID) * Arguement count(Val), * Return count(Val) */
            OP_VCALL,

            /* Pushes arguement to virtual function stack | * Dest(Register) */
            OP_VPUSH,

            /* Loads function in table to a register | * Dest(Register), * Source(Register), * Kvalue(Kvalue) */
            OP_SELF,

            /* Return from a function | * Start register(Register), * Return count(Val) */
            OP_RETURN,

            /* String concatation | * Dest(Register), * Start register(Val), * End register(Val) */
            OP_CONCAT,

            /* Jump to a address | * Target(Jump) */
            OP_JUMP,

            OP_CMP,     /* Writes two compare registers too a cmp flag | * Compare(Register), * Compare(Register) */
            OP_CMPK,    /* Writes compare register and a kvalue too cmp flag | * Compare(Register), * Compare(Kvalue) */
            OP_CMPN,    /* Writes compare register and an integer to cmp flag | * Compare(Register), * Compare(Val) */
            OP_CMPB,    /* Writes compare register and a boolean to cmp flag | * Compare(Register), * Compare(Boolean) */
            OP_CMPNONE, /* Writes compare register and a none object to cmp flag | * Compare(Register) */

            OP_CMPS,     /* Writes one compare register to cmp flag | * Compare(Register) */
            OP_CMPSK,    /* Writes one compare kvalue to cmp flag | * Compare(Kvalue) */
            OP_CMPSN,    /* Writes one compare integer to cmp flag | * Compare(Val) */
            OP_CMPSNONE, /* Writes one compare none object to cmp flag */

            OP_JUMPIF,    /* Jump if cmp flag | * Jump address(jump) */
            OP_JUMPIFNOT, /* Jump if not cmp flag | * Jump address(jump) */

            OP_JUMPIFEQUAL,        /* Jump if == comparative to cmp flag | * Jump address(jump) */
            OP_JUMPIFNOTEQUAL,     /* Jump if != comparative to cmp flag | * Jump address(jump) */
            OP_JUMPIFLESS,         /* Jump if <  comparative to cmp flag | * Jump address(jump) */
            OP_JUMPIFLESSEQUAL,    /* Jump if <= comparative to cmp flag | * Jump address(jump) */
            OP_JUMPIFGREATER,      /* Jump if >  comparative to cmp flag | * Jump address(jump) */
            OP_JUMPIFGREATEREQUAL, /* Jump if >= comparative to cmp flag | * Jump address(jump) */

            OP_SETIF,    /* Set true or false if cmp flag | * Dest(Register) */
            OP_SETIFNOT, /* Set true or false if not cmp flag | * Dest(Register) */

            OP_SETIFEQUAL,        /* Set true or false if == comparative to cmp flag | * Dest(Register) */
            OP_SETIFNOTEQUAL,     /* Set true or false if != comparative to cmp flag | * Dest(Register) */
            OP_SETIFLESS,         /* Set true or false if <  comparative to cmp flag | * Dest(Register) */
            OP_SETIFLESSEQUAL,    /* Set true or false if <= comparative to cmp flag | * Dest(Register) */
            OP_SETIFGREATER,      /* Set true or false if >  comparative to cmp flag | * Dest(Register) */
            OP_SETIFGREATEREQUAL, /* Set true or false if >= comparative to cmp flag | * Dest(Register) */

            OP_SETUPVALUE, /* Set Upvalue | * Source(Register), * Upvalue ID(UpvalueID) */
            OP_GETUPVALUE, /* Get Upvalue | * Dest(Register), * Upvalue ID(UpvalueID) */

            OP_DESTROYUPVALUES,  /* Destroy all upvalues with target. */
            OP_DESTROYUPVALUESA, /* Destroy upvalues with target | * Start(Register) */

            OP_ADDUPVALUE, /* Sets upvalue for prev closure instruction(Follows closure instruction) | * Type(UpvalueKind), * Source(Register)   */

            OP_INIT,    /* Inits */
            OP_BITCAST, /* Cast register to n amounts of bits | * Dest(Register), * Source(Register), * Bits(Val u16), * precision(Val u8), * Unsigned(Boolean) */

            OP_GETVARIADIC, /* Gets variadics | * Dest(Register), * Amount(Val) */

            OP_SETTABLE, /* Set table | * Source(Register), * Table(Register), * Index(Register) */
            OP_GETTABLE, /* Get table | * Dest(Register), * Table(Register), * Index(Register) */

            OP_SETTABLEN, /* Set table | * Source(Register), * Table(Register), * Index(Val) */
            OP_GETTABLEN, /* Get table | * Dest(Register), * Table(Register), * Index(Val) */

            OP_SETTABLEK, /* Set table | * Source(Register), * Table(Register), * Index(Kvalue) */
            OP_GETTABLEK, /* Get table | * Dest(Register), * Table(Register), * Index(Kvalue) */

            OP_INITFORLOOPN,       /* Inits numeric for loop | * Dest(Register), * Maximum/target value register(Register),  * Incrementation value register(Register), * Loop iteration location(Jump) */
            OP_INITFORLOOPG,       /* Inits generic for loop | * Start value register(Register)(+3), * Variable count (Value), * Loop iteration location(Jump) */
            OP_INITFORLOOPSPECIAL, /* Inits abstract special generic for loop reference generic loop instruction for data | * Dest/Start(Register),  * End(Register), * Step(Register), * Variables(Registers), * Loop iteration location(Jump) */

            OP_NEWCLOSURE, /* Creates new closure | * Dest(Register), * Closure ID(ClosureID) */
            OP_REFCLOSURE, /* Gets closure from kvalue | * Dest(Register), * Closure(Kvalue) */

            OP_NEWTABLE, /* Creates new table | * Dest(Register), * Exact table size(Table_Size), * Exact array size(Table_Size) */
            OP_REFTABLE, /* Gets table from kvalue | * Dest(Register), * Table(Kvalue) (Exact size, node) */

            OP_NEWTABLEA, /* Creates new table | * Dest(Register), * Approximate table size(Table_Size), * Approximate array size(Table_Size) */
            OP_REFTABLEA, /* Gets table from kvalue | * Dest(Register), * Table(Kvalue) (Approximate size, node) */

            OP_SETLIST, /* Appends elements in a table | * Dest table(Register), * Start register(Register), * Exact table size(Val),  * Index(Val) */

            OP_FORLOOPG, /* For loop generic | * Start register(Register), * Loop variable count(Val), * Jump back(Jump)  */
            OP_FORLOOPN, /* For loop numeric | * Start value register(Register), * Maximum/target value register(Register),  * Incrementation value register(Register), * Jump back(Jump) */

            OP_POPTOP, /* Pops register from top of the stack. */
            OP_POPARG, /* Adds argument to poparg flag to get popped when next OP_CALL instruction is hit | * Ignore Register(Register) */

            OP_MEMSET,  /* Sets memory |  * Target(Register), * Source(Register), * Bits(Val u16) */
            OP_MEMREAD, /* Reads memory | * Dest(Register), * Source(Register), * Bits(Val u16)  */

            OP_SETFLAG, /* Appends flag to flag stack, the next instruction after all setflags will have there flags set based on the stack with it being cleared after | *Flags ID ENUM(Val) */

            OP_SALLOC,      /* Stack allocates n bytes | * Dest(Register),  * Bytes(Val) */
            OP_GETSTACK,    /* Gets stack pointer | * Dest(Register), * ID(Val) */
            OP_SETSTACK,    /* Set stack pointer | * Dest(Register), * ID(Val) */
            OP_STACKPUSH,   /* Pushes register contents to the given stack | * Stack ID(VAL), * Source(Register) */
            OP_STACKPOP,    /* Pops register contents from the given stack | * Stack ID(VAL), * Source(Register) */
            OP_POPTOPSTACK, /* Pops top from given stack | * Stack pointer(Register) */

            OP_CLOGIC_AND, /* Performs condition logic if sources are truthy puts result in dest | * Dest(Register),  * Source(Register),  * Source(Register) */
            OP_CLOGIC_OR,  /* Performs condition logic if either sources are truthy puts result in dest | * Dest(Register),  * Source(Register),  * Source(Register) */

            OP_PEND, /* Psuedo-instruction (Pending analysis) | Userdata(Register), * Userdata(Val), * Userdata(Val), * Userdata(Val)  */
            OP_MARK, /* Psuedo-instruction (Marks spot) */

            OP_MOBJ_CAST,  /* Casts register to object from object map | * Dest(Register),  * Source(Register), * Index(Val) */
            OP_NCTOR_MOBJ, /* See if source is object from object map if not construct | * Dest(Register),  * Source(Register),  * Index(Val) */

            OP_SCALL, /* Call to symbol table (Refer to OP_CALL for: return, arg schematic) | * ID(Val) */

            OP_FLAGSET,  /* Set flag with source | ID(Val), Source(Reg) */
            OP_FLAGREAD, /* Read flag to dest | Dest(Register), Source(Val) */

            OP_CREATE_STACK,  /* Creates new stack (overrides current) | Dest(Register) */
            OP_PRETURN,       /* Return from page function if a target exist it will index its value in with that target. Opcode strung together like "OP_PRETURN f, r, x OP_PRETURN f, r, y" means that it could return to n locations; f valid flag, r being where the return loc is at, and x/y being locs.  | Valid Flag, if 0 rest of the operands are placeholders (Integral), Jump target (Register), Jump page ID (Integral)  */
            OP_STARTPAGEFUNC, /* Starts page function, not effected by isolate | * ID(Val)  */
            OP_ENDPAGEFUNC,   /* Ends page function, not effected by isolate | * ID(Val)  */
            OP_PCALL,         /* Call to page function (args, returns are unknown and will get mapped transfered to other parts of code), Opaque register to get handled by user where call will place entry in register etc. | * ID(Val), * Reg(Register), Entry (Val)  */
            OP_PJUMP,         /* Jump to page | * ID(Val)  */

            OP_SEGREGATE, /* Next instruction any native flags set will be offset (including native ones) | * OFFSET(Val) */
            OP_COMBINE,   /* Psuedo-instruction (Any instruction that needs n data combined will use this, Flag to combine data from previous instruction to next) */

            OP_FLAGJUMP, /* If flag (ID) is true jump to page | * ID(Val), * ID(Val) */
            OP_ICALL,    /* If register(reg) == ID(Val) call (Calls returns will be analyzed by IR) | * Reg(Register),  * ID(Val) */

            OP_TAG_START, /* Set tag | * Name(Kvalue) */
            OP_TAG_KV,    /* Set next tag key value pair | * Key(Kvalue), * Value(Kvalue) */
            OP_TAG_END,   /* End current tag |  */
            OP_METADATA,  /* Meta data, user handled instruction. | * Name(Kvalue), * Data(Kvalue) */

            OP_ENTRY_POINT, /* Entry point */
            OP_COMMAND,     /* Internal command refer to command table (Args follow same schema as OP_CALL start is r0) | *Command (Kvalue), *Arg count (Val)  */

            OP_BITREAD,   /* Read bits (Index starts at 0)[MIN, MAX] and interpret result same as bit cast  | * Dest(Register),  * Source(Register), * Min(Register), * Max(Register), *Cast_bits(Val u16), * Unsigned(Boolean) */
            OP_BITWRITE,  /* Writes bits (Index starts at 0)[MIN, MAX] to the first source but it incs from start to end of second source ending either at end or bitwidth and Interpret result same as bit cast (BOTH SOURCES ARE CONST)   | * Dest(Register),  * Lvalue(Register), * Source(Register), * Min(Register), * Max(Register), *Cast_bits(Val u16), * Unsigned(Boolean) */
            OP_BITWRITEA, /* Writes bits assign (Index starts at 0)[MIN, MAX] to the Dest  buffer but it but it incs from start to end of second source ending either at end or bitwidth  | * Dest(Register), * Source(Register), * Min(Register), * Max(Register) */

            OP_ANNOTATE_PREV, /* Implement annotation to previous instruction | *Str (Kvalue)  */

            OP_AMT /* Amount */
      };

      /* Virtual functions legend (Hint, Arguments, Return) */
      enum class virtual_functions : std::uint8_t {

            VTF_TABLE_SLICE, /* Slices table | */
            VTF_TABLE_UNPACK,

            VTF_PRINT
      };

      struct optable_kind {

            opcodes op = opcodes::OP_NOP;
            boost::fixed_vector<operand::operand_kind, operand::OPERAND_MAX_SIZE> kinds;

            constexpr optable_kind() = default;
            constexpr optable_kind(const opcodes op, const boost::fixed_vector<operand::operand_kind, operand::OPERAND_MAX_SIZE> &kinds)
                : op(op), kinds(kinds) {
            }
            constexpr optable_kind(const opcodes op, const std::initializer_list<operand::operand_kind> &kinds)
                : op(op), kinds(kinds) {
            }
      };

      struct optable_encoding {

            opcodes op = opcodes::OP_NOP;                                                        /* Opcode */
            boost::fixed_vector<operand::operand_encoding, operand::OPERAND_MAX_SIZE> encodings; /* Encodings */

            constexpr optable_encoding() = default;
            constexpr optable_encoding(const opcodes op, const boost::fixed_vector<operand::operand_encoding, operand::OPERAND_MAX_SIZE> &encodings)
                : op(op), encodings(encodings) {
            }
            constexpr optable_encoding(const opcodes op, const std::initializer_list<operand::operand_encoding> &encodings)
                : op(op), encodings(encodings) {
            }
      };

      /* IL operand kinds */
      static constexpr optable_kind opkinds[] = {

          {opcodes::OP_NOP, {}}, /* 00 */

          {opcodes::OP_LOADBOOL, {operand::operand_kind::reg, operand::operand_kind::boolean}},          /* 01 */
          {opcodes::OP_LOADINT, {operand::operand_kind::reg, operand::operand_kind::integer}},           /* 02 */
          {opcodes::OP_LOADNONE, {operand::operand_kind::reg}},                                          /* 03 */
          {opcodes::OP_LOADKVAL, {operand::operand_kind::reg, operand::operand_kind::kval_string}},      /* 04 */
          {opcodes::OP_LOADGLOBAL, {operand::operand_kind::reg, operand::operand_kind::kval}},           /* 05 */
          {opcodes::OP_GETTABUPVALUE, {operand::operand_kind::reg, operand::operand_kind::kval_string}}, /* 07 */

          {opcodes::OP_SETGLOBAL, {operand::operand_kind::reg, operand::operand_kind::value}}, /* 08 */

          {opcodes::OP_MOVE, {operand::operand_kind::reg, operand::operand_kind::reg}}, /* 0B */

          {opcodes::OP_ADD, {operand::operand_kind::reg, operand::operand_kind::reg, operand::operand_kind::reg}},  /* 0C */
          {opcodes::OP_SUB, {operand::operand_kind::reg, operand::operand_kind::reg, operand::operand_kind::reg}},  /* 0D */
          {opcodes::OP_MUL, {operand::operand_kind::reg, operand::operand_kind::reg, operand::operand_kind::reg}},  /* 0E */
          {opcodes::OP_DIV, {operand::operand_kind::reg, operand::operand_kind::reg, operand::operand_kind::reg}},  /* 0F */
          {opcodes::OP_MOD, {operand::operand_kind::reg, operand::operand_kind::reg, operand::operand_kind::reg}},  /* 10 */
          {opcodes::OP_POW, {operand::operand_kind::reg, operand::operand_kind::reg, operand::operand_kind::reg}},  /* 11 */
          {opcodes::OP_AND, {operand::operand_kind::reg, operand::operand_kind::reg, operand::operand_kind::reg}},  /* 12 */
          {opcodes::OP_XOR, {operand::operand_kind::reg, operand::operand_kind::reg, operand::operand_kind::reg}},  /* 13 */
          {opcodes::OP_SHL, {operand::operand_kind::reg, operand::operand_kind::reg, operand::operand_kind::reg}},  /* 14 */
          {opcodes::OP_SHR, {operand::operand_kind::reg, operand::operand_kind::reg, operand::operand_kind::reg}},  /* 15 */
          {opcodes::OP_IDIV, {operand::operand_kind::reg, operand::operand_kind::reg, operand::operand_kind::reg}}, /* 16 */
          {opcodes::OP_OR, {operand::operand_kind::reg, operand::operand_kind::reg, operand::operand_kind::reg}},   /* 17 */

          {opcodes::OP_ADDK, {operand::operand_kind::reg, operand::operand_kind::reg, operand::operand_kind::kval}},  /* 18 */
          {opcodes::OP_SUBK, {operand::operand_kind::reg, operand::operand_kind::reg, operand::operand_kind::kval}},  /* 19 */
          {opcodes::OP_MULK, {operand::operand_kind::reg, operand::operand_kind::reg, operand::operand_kind::kval}},  /* 1A */
          {opcodes::OP_DIVK, {operand::operand_kind::reg, operand::operand_kind::reg, operand::operand_kind::kval}},  /* 1B */
          {opcodes::OP_MODK, {operand::operand_kind::reg, operand::operand_kind::reg, operand::operand_kind::kval}},  /* 1C */
          {opcodes::OP_POWK, {operand::operand_kind::reg, operand::operand_kind::reg, operand::operand_kind::kval}},  /* 1D */
          {opcodes::OP_ANDK, {operand::operand_kind::reg, operand::operand_kind::reg, operand::operand_kind::kval}},  /* 1E */
          {opcodes::OP_XORK, {operand::operand_kind::reg, operand::operand_kind::reg, operand::operand_kind::kval}},  /* 1F */
          {opcodes::OP_SHLK, {operand::operand_kind::reg, operand::operand_kind::reg, operand::operand_kind::kval}},  /* 20 */
          {opcodes::OP_SHRK, {operand::operand_kind::reg, operand::operand_kind::reg, operand::operand_kind::kval}},  /* 21 */
          {opcodes::OP_IDIVK, {operand::operand_kind::reg, operand::operand_kind::reg, operand::operand_kind::kval}}, /* 22 */
          {opcodes::OP_ORK, {operand::operand_kind::reg, operand::operand_kind::reg, operand::operand_kind::kval}},   /* 23 */

          {opcodes::OP_ADDN, {operand::operand_kind::reg, operand::operand_kind::reg, operand::operand_kind::integer}},  /* 24 */
          {opcodes::OP_SUBN, {operand::operand_kind::reg, operand::operand_kind::reg, operand::operand_kind::integer}},  /* 25 */
          {opcodes::OP_MULN, {operand::operand_kind::reg, operand::operand_kind::reg, operand::operand_kind::integer}},  /* 26 */
          {opcodes::OP_DIVN, {operand::operand_kind::reg, operand::operand_kind::reg, operand::operand_kind::integer}},  /* 27 */
          {opcodes::OP_MODN, {operand::operand_kind::reg, operand::operand_kind::reg, operand::operand_kind::integer}},  /* 28 */
          {opcodes::OP_POWN, {operand::operand_kind::reg, operand::operand_kind::reg, operand::operand_kind::integer}},  /* 29 */
          {opcodes::OP_ANDN, {operand::operand_kind::reg, operand::operand_kind::reg, operand::operand_kind::integer}},  /* 2A */
          {opcodes::OP_XORN, {operand::operand_kind::reg, operand::operand_kind::reg, operand::operand_kind::integer}},  /* 2B */
          {opcodes::OP_SHLN, {operand::operand_kind::reg, operand::operand_kind::reg, operand::operand_kind::integer}},  /* 2C */
          {opcodes::OP_SHRN, {operand::operand_kind::reg, operand::operand_kind::reg, operand::operand_kind::integer}},  /* 2D */
          {opcodes::OP_IDIVN, {operand::operand_kind::reg, operand::operand_kind::reg, operand::operand_kind::integer}}, /* 2E */
          {opcodes::OP_ORN, {operand::operand_kind::reg, operand::operand_kind::reg, operand::operand_kind::integer}},   /* 2F */

          {opcodes::OP_LEN, {operand::operand_kind::reg, operand::operand_kind::reg}},    /* 30 */
          {opcodes::OP_NOT, {operand::operand_kind::reg, operand::operand_kind::reg}},    /* 31 */
          {opcodes::OP_MINUS, {operand::operand_kind::reg, operand::operand_kind::reg}},  /* 32 */
          {opcodes::OP_BITNOT, {operand::operand_kind::reg, operand::operand_kind::reg}}, /* 33 */
          {opcodes::OP_PLUS, {operand::operand_kind::reg, operand::operand_kind::reg}},   /* 34 */
          {opcodes::OP_REF, {operand::operand_kind::reg, operand::operand_kind::reg}},    /* 34 */

          {opcodes::OP_CCALL, {operand::operand_kind::reg, operand::operand_kind::value, operand::operand_kind::value}},                               /* 35 */
          {opcodes::OP_VCALL, {operand::operand_kind::reg, operand::operand_kind::value, operand::operand_kind::value, operand::operand_kind::value}}, /* 36 */

          {opcodes::OP_VPUSH, {operand::operand_kind::reg}}, /* 37 */

          {opcodes::OP_SELF, {operand::operand_kind::reg, operand::operand_kind::reg, operand::operand_kind::kval}}, /* 38 */
          {opcodes::OP_RETURN, {operand::operand_kind::reg, operand::operand_kind::value}},                          /* 39 */

          {opcodes::OP_CONCAT, {operand::operand_kind::reg, operand::operand_kind::value, operand::operand_kind::value}}, /* 3A */

          {opcodes::OP_JUMP, {operand::operand_kind::jmp}}, /* 3B */

          {opcodes::OP_CMP, {operand::operand_kind::reg, operand::operand_kind::reg}},      /* 3D */
          {opcodes::OP_CMPK, {operand::operand_kind::reg, operand::operand_kind::kval}},    /* 3E */
          {opcodes::OP_CMPN, {operand::operand_kind::reg, operand::operand_kind::integer}}, /* 3F */
          {opcodes::OP_CMPB, {operand::operand_kind::reg, operand::operand_kind::boolean}}, /* 3F */
          {opcodes::OP_CMPNONE, {operand::operand_kind::reg}},                              /* 40 */

          {opcodes::OP_CMPS, {operand::operand_kind::reg}},      /* 41 */
          {opcodes::OP_CMPSK, {operand::operand_kind::kval}},    /* 42 */
          {opcodes::OP_CMPSN, {operand::operand_kind::integer}}, /* 43 */
          {opcodes::OP_CMPSNONE, {}},                            /* 44 */

          {opcodes::OP_JUMPIF, {operand::operand_kind::jmp}},    /* 45 */
          {opcodes::OP_JUMPIFNOT, {operand::operand_kind::jmp}}, /* 46 */

          {opcodes::OP_JUMPIFEQUAL, {operand::operand_kind::jmp}},        /* 47 */
          {opcodes::OP_JUMPIFNOTEQUAL, {operand::operand_kind::jmp}},     /* 48 */
          {opcodes::OP_JUMPIFLESS, {operand::operand_kind::jmp}},         /* 49 */
          {opcodes::OP_JUMPIFLESSEQUAL, {operand::operand_kind::jmp}},    /* 4A */
          {opcodes::OP_JUMPIFGREATER, {operand::operand_kind::jmp}},      /* 4B */
          {opcodes::OP_JUMPIFGREATEREQUAL, {operand::operand_kind::jmp}}, /* 4C */

          {opcodes::OP_SETIF, {operand::operand_kind::reg}},    /* 4D */
          {opcodes::OP_SETIFNOT, {operand::operand_kind::reg}}, /* 4E */

          {opcodes::OP_SETIFEQUAL, {operand::operand_kind::reg}},        /* 4F */
          {opcodes::OP_SETIFNOTEQUAL, {operand::operand_kind::reg}},     /* 50 */
          {opcodes::OP_SETIFLESS, {operand::operand_kind::reg}},         /* 51 */
          {opcodes::OP_SETIFLESSEQUAL, {operand::operand_kind::reg}},    /* 52 */
          {opcodes::OP_SETIFGREATER, {operand::operand_kind::reg}},      /* 53 */
          {opcodes::OP_SETIFGREATEREQUAL, {operand::operand_kind::reg}}, /* 54 */

          {opcodes::OP_SETUPVALUE, {operand::operand_kind::reg, operand::operand_kind::upvalue}}, /* 55 */
          {opcodes::OP_GETUPVALUE, {operand::operand_kind::reg, operand::operand_kind::upvalue}}, /* 56 */

          {opcodes::OP_DESTROYUPVALUES, {}},                            /* 57 */
          {opcodes::OP_DESTROYUPVALUESA, {operand::operand_kind::reg}}, /* 58 */

          {opcodes::OP_ADDUPVALUE, {operand::operand_kind::upvalue_kind, operand::operand_kind::reg}}, /* 59 */

          {opcodes::OP_INIT, {}},                                                                                                                                                      /* 5A */
          {opcodes::OP_BITCAST, {operand::operand_kind::reg, operand::operand_kind::reg, operand::operand_kind::value, operand::operand_kind::value, operand::operand_kind::boolean}}, /* 5A */

          {opcodes::OP_GETVARIADIC, {operand::operand_kind::reg, operand::operand_kind::value}}, /* 5B */

          {opcodes::OP_SETTABLE, {operand::operand_kind::reg, operand::operand_kind::reg, operand::operand_kind::reg}}, /* 5C */
          {opcodes::OP_GETTABLE, {operand::operand_kind::reg, operand::operand_kind::reg, operand::operand_kind::reg}}, /* 5D */

          {opcodes::OP_SETTABLEN, {operand::operand_kind::reg, operand::operand_kind::reg, operand::operand_kind::value}}, /* 5E */
          {opcodes::OP_GETTABLEN, {operand::operand_kind::reg, operand::operand_kind::reg, operand::operand_kind::value}}, /* 5F */

          {opcodes::OP_SETTABLEK, {operand::operand_kind::reg, operand::operand_kind::reg, operand::operand_kind::kval}}, /* 60 */
          {opcodes::OP_GETTABLEK, {operand::operand_kind::reg, operand::operand_kind::reg, operand::operand_kind::kval}}, /* 61 */

          {opcodes::OP_INITFORLOOPN, {operand::operand_kind::reg, operand::operand_kind::reg, operand::operand_kind::reg, operand::operand_kind::jmp}},       /* 62 */
          {opcodes::OP_INITFORLOOPG, {operand::operand_kind::jmp}},                                                                                           /* 63 */
          {opcodes::OP_INITFORLOOPSPECIAL, {operand::operand_kind::reg, operand::operand_kind::reg, operand::operand_kind::reg, operand::operand_kind::jmp}}, /* 64 */

          {opcodes::OP_NEWCLOSURE, {operand::operand_kind::reg, operand::operand_kind::closure}}, /* 65 */
          {opcodes::OP_REFCLOSURE, {operand::operand_kind::reg, operand::operand_kind::kval}},    /* 66 */

          {opcodes::OP_NEWTABLE, {operand::operand_kind::reg, operand::operand_kind::table_size, operand::operand_kind::table_size}}, /* 67 */
          {opcodes::OP_REFTABLE, {operand::operand_kind::reg, operand::operand_kind::kval}},                                          /* 68 */

          {opcodes::OP_NEWTABLEA, {operand::operand_kind::reg, operand::operand_kind::table_size, operand::operand_kind::table_size}}, /* 69 */
          {opcodes::OP_REFTABLEA, {operand::operand_kind::reg, operand::operand_kind::kval}},                                          /* 6A */

          {opcodes::OP_SETLIST, {operand::operand_kind::reg, operand::operand_kind::reg, operand::operand_kind::value, operand::operand_kind::value}}, /* 6B */

          {opcodes::OP_FORLOOPG, {operand::operand_kind::reg, operand::operand_kind::value, operand::operand_kind::jmp}},                           /* 6C */
          {opcodes::OP_FORLOOPN, {operand::operand_kind::reg, operand::operand_kind::reg, operand::operand_kind::reg, operand::operand_kind::jmp}}, /* 6D */

          {opcodes::OP_POPTOP, {}},                           /* 6E */
          {opcodes::OP_POPARG, {operand::operand_kind::reg}}, /* 6F */

          {opcodes::OP_MEMSET, {operand::operand_kind::reg, operand::operand_kind::reg, operand::operand_kind::value}},  /* 6F */
          {opcodes::OP_MEMREAD, {operand::operand_kind::reg, operand::operand_kind::reg, operand::operand_kind::value}}, /* 6F */

          {opcodes::OP_SETFLAG, {operand::operand_kind::value}}, /* 6F */

          {opcodes::OP_SALLOC, {operand::operand_kind::reg, operand::operand_kind::value}},    /* 6F */
          {opcodes::OP_GETSTACK, {operand::operand_kind::reg, operand::operand_kind::value}},  /* 6F */
          {opcodes::OP_SETSTACK, {operand::operand_kind::reg, operand::operand_kind::value}},  /* 6F */
          {opcodes::OP_STACKPUSH, {operand::operand_kind::value, operand::operand_kind::reg}}, /* 6F */
          {opcodes::OP_STACKPOP, {operand::operand_kind::value, operand::operand_kind::reg}},  /* 6F */
          {opcodes::OP_POPTOPSTACK, {operand::operand_kind::reg}},                             /* 6F */

          {opcodes::OP_CLOGIC_AND, {operand::operand_kind::reg, operand::operand_kind::reg, operand::operand_kind::reg}}, /* 6F */
          {opcodes::OP_CLOGIC_OR, {operand::operand_kind::reg, operand::operand_kind::reg, operand::operand_kind::reg}},  /* 6F */

          {opcodes::OP_PEND, {operand::operand_kind::reg, operand::operand_kind::integer, operand::operand_kind::integer, operand::operand_kind::integer}}, /* 6F */
          {opcodes::OP_MARK, {}},
          {opcodes::OP_MOBJ_CAST, {operand::operand_kind::reg, operand::operand_kind::reg, operand::operand_kind::integer}},
          {opcodes::OP_NCTOR_MOBJ, {operand::operand_kind::reg, operand::operand_kind::reg, operand::operand_kind::integer}},
          {opcodes::OP_SCALL, {operand::operand_kind::integer}},
          {opcodes::OP_FLAGSET, {operand::operand_kind::value, operand::operand_kind::reg}},
          {opcodes::OP_FLAGREAD, {operand::operand_kind::reg, operand::operand_kind::value}},
          {opcodes::OP_CREATE_STACK, {operand::operand_kind::reg}},
          {opcodes::OP_PRETURN, {operand::operand_kind::value, operand::operand_kind::reg, operand::operand_kind::value}},
          {opcodes::OP_STARTPAGEFUNC, {operand::operand_kind::value}},
          {opcodes::OP_ENDPAGEFUNC, {operand::operand_kind::value}},
          {opcodes::OP_PCALL, {operand::operand_kind::value, operand::operand_kind::reg, operand::operand_kind::value}},
          {opcodes::OP_PJUMP, {operand::operand_kind::value}},
          {opcodes::OP_SEGREGATE, {operand::operand_kind::value}},
          {opcodes::OP_COMBINE, {}},
          {opcodes::OP_FLAGJUMP, {operand::operand_kind::value, operand::operand_kind::value}},
          {opcodes::OP_ICALL, {operand::operand_kind::reg, operand::operand_kind::value}},

          {opcodes::OP_TAG_START, {operand::operand_kind::kval_string}},
          {opcodes::OP_TAG_KV, {operand::operand_kind::kval_string, operand::operand_kind::kval_string}},
          {opcodes::OP_TAG_END, {}},
          {opcodes::OP_METADATA, {operand::operand_kind::kval_string, operand::operand_kind::kval_string}},

          {opcodes::OP_ENTRY_POINT, {}},
          {opcodes::OP_COMMAND, {operand::operand_kind::kval_string, operand::operand_kind::value}},

          {opcodes::OP_BITREAD, {operand::operand_kind::reg, operand::operand_kind::reg, operand::operand_kind::reg, operand::operand_kind::reg, operand::operand_kind::value, operand::operand_kind::boolean}},
          {opcodes::OP_BITWRITE, {operand::operand_kind::reg, operand::operand_kind::reg, operand::operand_kind::reg, operand::operand_kind::reg, operand::operand_kind::reg, operand::operand_kind::value, operand::operand_kind::boolean}},
          {opcodes::OP_BITWRITEA, {operand::operand_kind::reg, operand::operand_kind::reg, operand::operand_kind::reg, operand::operand_kind::reg}},

          {opcodes::OP_ANNOTATE_PREV, {operand::operand_kind::kval_string}}};

      /* IL operand encodings */
      static constexpr optable_encoding opencodings[] = {

          {opcodes::OP_NOP, {}}, /* 00 */

          {opcodes::OP_LOADBOOL, {operand::operand_encoding::reg, operand::operand_encoding::boolean}},  /* 01 */
          {opcodes::OP_LOADINT, {operand::operand_encoding::reg, operand::operand_encoding::integer}},   /* 02 */
          {opcodes::OP_LOADNONE, {operand::operand_encoding::reg}},                                      /* 03 */
          {opcodes::OP_LOADKVAL, {operand::operand_encoding::reg, operand::operand_encoding::idx}},      /* 04 */
          {opcodes::OP_LOADGLOBAL, {operand::operand_encoding::reg, operand::operand_encoding::idx}},    /* 05 */
          {opcodes::OP_GETTABUPVALUE, {operand::operand_encoding::reg, operand::operand_encoding::idx}}, /* 07 */

          {opcodes::OP_SETGLOBAL, {operand::operand_encoding::reg, operand::operand_encoding::value}}, /* 08 */

          {opcodes::OP_MOVE, {operand::operand_encoding::reg, operand::operand_encoding::reg}}, /* 0B */

          {opcodes::OP_ADD, {operand::operand_encoding::reg, operand::operand_encoding::reg, operand::operand_encoding::reg}},  /* 0C */
          {opcodes::OP_SUB, {operand::operand_encoding::reg, operand::operand_encoding::reg, operand::operand_encoding::reg}},  /* 0D */
          {opcodes::OP_MUL, {operand::operand_encoding::reg, operand::operand_encoding::reg, operand::operand_encoding::reg}},  /* 0E */
          {opcodes::OP_DIV, {operand::operand_encoding::reg, operand::operand_encoding::reg, operand::operand_encoding::reg}},  /* 0F */
          {opcodes::OP_MOD, {operand::operand_encoding::reg, operand::operand_encoding::reg, operand::operand_encoding::reg}},  /* 10 */
          {opcodes::OP_POW, {operand::operand_encoding::reg, operand::operand_encoding::reg, operand::operand_encoding::reg}},  /* 11 */
          {opcodes::OP_AND, {operand::operand_encoding::reg, operand::operand_encoding::reg, operand::operand_encoding::reg}},  /* 12 */
          {opcodes::OP_XOR, {operand::operand_encoding::reg, operand::operand_encoding::reg, operand::operand_encoding::reg}},  /* 13 */
          {opcodes::OP_SHL, {operand::operand_encoding::reg, operand::operand_encoding::reg, operand::operand_encoding::reg}},  /* 14 */
          {opcodes::OP_SHR, {operand::operand_encoding::reg, operand::operand_encoding::reg, operand::operand_encoding::reg}},  /* 15 */
          {opcodes::OP_IDIV, {operand::operand_encoding::reg, operand::operand_encoding::reg, operand::operand_encoding::reg}}, /* 16 */
          {opcodes::OP_OR, {operand::operand_encoding::reg, operand::operand_encoding::reg, operand::operand_encoding::reg}},   /* 17 */

          {opcodes::OP_ADDK, {operand::operand_encoding::reg, operand::operand_encoding::reg, operand::operand_encoding::idx}},  /* 18 */
          {opcodes::OP_SUBK, {operand::operand_encoding::reg, operand::operand_encoding::reg, operand::operand_encoding::idx}},  /* 19 */
          {opcodes::OP_MULK, {operand::operand_encoding::reg, operand::operand_encoding::reg, operand::operand_encoding::idx}},  /* 1A */
          {opcodes::OP_DIVK, {operand::operand_encoding::reg, operand::operand_encoding::reg, operand::operand_encoding::idx}},  /* 1B */
          {opcodes::OP_MODK, {operand::operand_encoding::reg, operand::operand_encoding::reg, operand::operand_encoding::idx}},  /* 1C */
          {opcodes::OP_POWK, {operand::operand_encoding::reg, operand::operand_encoding::reg, operand::operand_encoding::idx}},  /* 1D */
          {opcodes::OP_ANDK, {operand::operand_encoding::reg, operand::operand_encoding::reg, operand::operand_encoding::idx}},  /* 1E */
          {opcodes::OP_XORK, {operand::operand_encoding::reg, operand::operand_encoding::reg, operand::operand_encoding::idx}},  /* 1F */
          {opcodes::OP_SHLK, {operand::operand_encoding::reg, operand::operand_encoding::reg, operand::operand_encoding::idx}},  /* 20 */
          {opcodes::OP_SHRK, {operand::operand_encoding::reg, operand::operand_encoding::reg, operand::operand_encoding::idx}},  /* 21 */
          {opcodes::OP_IDIVK, {operand::operand_encoding::reg, operand::operand_encoding::reg, operand::operand_encoding::idx}}, /* 22 */
          {opcodes::OP_ORK, {operand::operand_encoding::reg, operand::operand_encoding::reg, operand::operand_encoding::idx}},   /* 23 */

          {opcodes::OP_ADDN, {operand::operand_encoding::reg, operand::operand_encoding::reg, operand::operand_encoding::integer}},  /* 24 */
          {opcodes::OP_SUBN, {operand::operand_encoding::reg, operand::operand_encoding::reg, operand::operand_encoding::integer}},  /* 25 */
          {opcodes::OP_MULN, {operand::operand_encoding::reg, operand::operand_encoding::reg, operand::operand_encoding::integer}},  /* 26 */
          {opcodes::OP_DIVN, {operand::operand_encoding::reg, operand::operand_encoding::reg, operand::operand_encoding::integer}},  /* 27 */
          {opcodes::OP_MODN, {operand::operand_encoding::reg, operand::operand_encoding::reg, operand::operand_encoding::integer}},  /* 28 */
          {opcodes::OP_POWN, {operand::operand_encoding::reg, operand::operand_encoding::reg, operand::operand_encoding::integer}},  /* 29 */
          {opcodes::OP_ANDN, {operand::operand_encoding::reg, operand::operand_encoding::reg, operand::operand_encoding::integer}},  /* 2A */
          {opcodes::OP_XORN, {operand::operand_encoding::reg, operand::operand_encoding::reg, operand::operand_encoding::integer}},  /* 2B */
          {opcodes::OP_SHLN, {operand::operand_encoding::reg, operand::operand_encoding::reg, operand::operand_encoding::integer}},  /* 2C */
          {opcodes::OP_SHRN, {operand::operand_encoding::reg, operand::operand_encoding::reg, operand::operand_encoding::integer}},  /* 2D */
          {opcodes::OP_IDIVN, {operand::operand_encoding::reg, operand::operand_encoding::reg, operand::operand_encoding::integer}}, /* 2E */
          {opcodes::OP_ORN, {operand::operand_encoding::reg, operand::operand_encoding::reg, operand::operand_encoding::integer}},   /* 2F */

          {opcodes::OP_LEN, {operand::operand_encoding::reg, operand::operand_encoding::reg}},    /* 30 */
          {opcodes::OP_NOT, {operand::operand_encoding::reg, operand::operand_encoding::reg}},    /* 31 */
          {opcodes::OP_MINUS, {operand::operand_encoding::reg, operand::operand_encoding::reg}},  /* 32 */
          {opcodes::OP_BITNOT, {operand::operand_encoding::reg, operand::operand_encoding::reg}}, /* 33 */
          {opcodes::OP_PLUS, {operand::operand_encoding::reg, operand::operand_encoding::reg}},   /* 34 */
          {opcodes::OP_REF, {operand::operand_encoding::reg, operand::operand_encoding::reg}},    /* 34 */

          {opcodes::OP_CCALL, {operand::operand_encoding::reg, operand::operand_encoding::value, operand::operand_encoding::value}},                                   /* 35 */
          {opcodes::OP_VCALL, {operand::operand_encoding::reg, operand::operand_encoding::value, operand::operand_encoding::value, operand::operand_encoding::value}}, /* 36 */

          {opcodes::OP_VPUSH, {operand::operand_encoding::reg}}, /* 37 */

          {opcodes::OP_SELF, {operand::operand_encoding::reg, operand::operand_encoding::reg, operand::operand_encoding::idx}}, /* 38 */
          {opcodes::OP_RETURN, {operand::operand_encoding::reg, operand::operand_encoding::value}},                             /* 39 */

          {opcodes::OP_CONCAT, {operand::operand_encoding::reg, operand::operand_encoding::value, operand::operand_encoding::value}}, /* 3A */

          {opcodes::OP_JUMP, {operand::operand_encoding::jmp}}, /* 3B */

          {opcodes::OP_CMP, {operand::operand_encoding::reg, operand::operand_encoding::reg}},      /* 3D */
          {opcodes::OP_CMPK, {operand::operand_encoding::reg, operand::operand_encoding::idx}},     /* 3E */
          {opcodes::OP_CMPN, {operand::operand_encoding::reg, operand::operand_encoding::integer}}, /* 3F */
          {opcodes::OP_CMPB, {operand::operand_encoding::reg, operand::operand_encoding::boolean}}, /* 3F */
          {opcodes::OP_CMPNONE, {operand::operand_encoding::reg}},                                  /* 40 */

          {opcodes::OP_CMPS, {operand::operand_encoding::reg}},      /* 41 */
          {opcodes::OP_CMPSK, {operand::operand_encoding::idx}},     /* 42 */
          {opcodes::OP_CMPSN, {operand::operand_encoding::integer}}, /* 43 */
          {opcodes::OP_CMPSNONE, {}},                                /* 44 */

          {opcodes::OP_JUMPIF, {operand::operand_encoding::jmp}},    /* 45 */
          {opcodes::OP_JUMPIFNOT, {operand::operand_encoding::jmp}}, /* 46 */

          {opcodes::OP_JUMPIFEQUAL, {operand::operand_encoding::jmp}},        /* 47 */
          {opcodes::OP_JUMPIFNOTEQUAL, {operand::operand_encoding::jmp}},     /* 48 */
          {opcodes::OP_JUMPIFLESS, {operand::operand_encoding::jmp}},         /* 49 */
          {opcodes::OP_JUMPIFLESSEQUAL, {operand::operand_encoding::jmp}},    /* 4A */
          {opcodes::OP_JUMPIFGREATER, {operand::operand_encoding::jmp}},      /* 4B */
          {opcodes::OP_JUMPIFGREATEREQUAL, {operand::operand_encoding::jmp}}, /* 4C */

          {opcodes::OP_SETIF, {operand::operand_encoding::reg}},    /* 4D */
          {opcodes::OP_SETIFNOT, {operand::operand_encoding::reg}}, /* 4E */

          {opcodes::OP_SETIFEQUAL, {operand::operand_encoding::reg}},        /* 4F */
          {opcodes::OP_SETIFNOTEQUAL, {operand::operand_encoding::reg}},     /* 50 */
          {opcodes::OP_SETIFLESS, {operand::operand_encoding::reg}},         /* 51 */
          {opcodes::OP_SETIFLESSEQUAL, {operand::operand_encoding::reg}},    /* 52 */
          {opcodes::OP_SETIFGREATER, {operand::operand_encoding::reg}},      /* 53 */
          {opcodes::OP_SETIFGREATEREQUAL, {operand::operand_encoding::reg}}, /* 54 */

          {opcodes::OP_SETUPVALUE, {operand::operand_encoding::reg, operand::operand_encoding::value}}, /* 55 */
          {opcodes::OP_GETUPVALUE, {operand::operand_encoding::reg, operand::operand_encoding::value}}, /* 56 */

          {opcodes::OP_DESTROYUPVALUES, {}},                                /* 57 */
          {opcodes::OP_DESTROYUPVALUESA, {operand::operand_encoding::reg}}, /* 58 */

          {opcodes::OP_ADDUPVALUE, {operand::operand_encoding::value, operand::operand_encoding::reg}}, /* 59 */

          {opcodes::OP_INIT, {}},                                                                                                                                                                          /* 5A */
          {opcodes::OP_BITCAST, {operand::operand_encoding::reg, operand::operand_encoding::reg, operand::operand_encoding::value, operand::operand_encoding::value, operand::operand_encoding::boolean}}, /* 5A */

          {opcodes::OP_GETVARIADIC, {operand::operand_encoding::reg, operand::operand_encoding::value}}, /* 5B */

          {opcodes::OP_SETTABLE, {operand::operand_encoding::reg, operand::operand_encoding::reg, operand::operand_encoding::reg}}, /* 5C */
          {opcodes::OP_GETTABLE, {operand::operand_encoding::reg, operand::operand_encoding::reg, operand::operand_encoding::reg}}, /* 5D */

          {opcodes::OP_SETTABLEN, {operand::operand_encoding::reg, operand::operand_encoding::reg, operand::operand_encoding::value}}, /* 5E */
          {opcodes::OP_GETTABLEN, {operand::operand_encoding::reg, operand::operand_encoding::reg, operand::operand_encoding::value}}, /* 5F */

          {opcodes::OP_SETTABLEK, {operand::operand_encoding::reg, operand::operand_encoding::reg, operand::operand_encoding::idx}}, /* 60 */
          {opcodes::OP_GETTABLEK, {operand::operand_encoding::reg, operand::operand_encoding::reg, operand::operand_encoding::idx}}, /* 61 */

          {opcodes::OP_INITFORLOOPN, {operand::operand_encoding::reg, operand::operand_encoding::reg, operand::operand_encoding::reg, operand::operand_encoding::jmp}},       /* 62 */
          {opcodes::OP_INITFORLOOPG, {operand::operand_encoding::reg, operand::operand_encoding::value, operand::operand_encoding::jmp}},                                     /* 63 */
          {opcodes::OP_INITFORLOOPSPECIAL, {operand::operand_encoding::reg, operand::operand_encoding::reg, operand::operand_encoding::reg, operand::operand_encoding::jmp}}, /* 64 */

          {opcodes::OP_NEWCLOSURE, {operand::operand_encoding::reg, operand::operand_encoding::value}}, /* 65 */
          {opcodes::OP_REFCLOSURE, {operand::operand_encoding::reg, operand::operand_encoding::idx}},   /* 66 */

          {opcodes::OP_NEWTABLE, {operand::operand_encoding::reg, operand::operand_encoding::value, operand::operand_encoding::value}}, /* 67 */
          {opcodes::OP_REFTABLE, {operand::operand_encoding::reg, operand::operand_encoding::idx}},                                     /* 68 */

          {opcodes::OP_NEWTABLEA, {operand::operand_encoding::reg, operand::operand_encoding::value, operand::operand_encoding::value}}, /* 69 */
          {opcodes::OP_REFTABLEA, {operand::operand_encoding::reg, operand::operand_encoding::idx}},                                     /* 6A */

          {opcodes::OP_SETLIST, {operand::operand_encoding::reg, operand::operand_encoding::reg, operand::operand_encoding::value, operand::operand_encoding::value}}, /* 6B */

          {opcodes::OP_FORLOOPG, {operand::operand_encoding::reg, operand::operand_encoding::value, operand::operand_encoding::jmp}},                               /* 6C */
          {opcodes::OP_FORLOOPN, {operand::operand_encoding::reg, operand::operand_encoding::reg, operand::operand_encoding::reg, operand::operand_encoding::jmp}}, /* 6D */

          {opcodes::OP_POPTOP, {}},                               /* 6E */
          {opcodes::OP_POPARG, {operand::operand_encoding::reg}}, /* 6F */

          {opcodes::OP_MEMSET, {operand::operand_encoding::reg, operand::operand_encoding::reg, operand::operand_encoding::value}},  /* 6F */
          {opcodes::OP_MEMREAD, {operand::operand_encoding::reg, operand::operand_encoding::reg, operand::operand_encoding::value}}, /* 6F */

          {opcodes::OP_SETFLAG, {operand::operand_encoding::value}}, /* 6F */

          {opcodes::OP_SALLOC, {operand::operand_encoding::reg, operand::operand_encoding::value}},    /* 6F */
          {opcodes::OP_GETSTACK, {operand::operand_encoding::reg, operand::operand_encoding::value}},  /* 6F */
          {opcodes::OP_SETSTACK, {operand::operand_encoding::reg, operand::operand_encoding::value}},  /* 6F */
          {opcodes::OP_STACKPUSH, {operand::operand_encoding::value, operand::operand_encoding::reg}}, /* 6F */
          {opcodes::OP_STACKPOP, {operand::operand_encoding::value, operand::operand_encoding::reg}},  /* 6F */
          {opcodes::OP_POPTOPSTACK, {operand::operand_encoding::reg}},                                 /* 6F */

          {opcodes::OP_CLOGIC_AND, {operand::operand_encoding::reg, operand::operand_encoding::reg, operand::operand_encoding::reg}}, /* 6F */
          {opcodes::OP_CLOGIC_OR, {operand::operand_encoding::reg, operand::operand_encoding::reg, operand::operand_encoding::reg}},  /* 6F */

          {opcodes::OP_PEND, {operand::operand_encoding::reg, operand::operand_encoding::value, operand::operand_encoding::value, operand::operand_encoding::value}}, /* 6F */
          {opcodes::OP_MARK, {}},
          {opcodes::OP_MOBJ_CAST, {operand::operand_encoding::reg, operand::operand_encoding::reg, operand::operand_encoding::idx}},
          {opcodes::OP_NCTOR_MOBJ, {operand::operand_encoding::reg, operand::operand_encoding::reg, operand::operand_encoding::idx}},
          {opcodes::OP_SCALL, {operand::operand_encoding::value}},
          {opcodes::OP_FLAGSET, {operand::operand_encoding::value, operand::operand_encoding::reg}},
          {opcodes::OP_FLAGREAD, {operand::operand_encoding::reg, operand::operand_encoding::value}},
          {opcodes::OP_CREATE_STACK, {operand::operand_encoding::reg}},
          {opcodes::OP_PRETURN, {operand::operand_encoding::value, operand::operand_encoding::reg, operand::operand_encoding::value}},
          {opcodes::OP_STARTPAGEFUNC, {operand::operand_encoding::value}},
          {opcodes::OP_ENDPAGEFUNC, {operand::operand_encoding::value}},
          {opcodes::OP_PCALL, {operand::operand_encoding::value, operand::operand_encoding::reg, operand::operand_encoding::value}},
          {opcodes::OP_PJUMP, {operand::operand_encoding::value}},
          {opcodes::OP_SEGREGATE, {operand::operand_encoding::value}},
          {opcodes::OP_COMBINE, {}},
          {opcodes::OP_FLAGJUMP, {operand::operand_encoding::value, operand::operand_encoding::value}},
          {opcodes::OP_ICALL, {operand::operand_encoding::reg, operand::operand_encoding::value}},

          {opcodes::OP_TAG_START, {operand::operand_encoding::idx}},
          {opcodes::OP_TAG_KV, {operand::operand_encoding::idx, operand::operand_encoding::idx}},
          {opcodes::OP_TAG_END, {}},
          {opcodes::OP_METADATA, {operand::operand_encoding::idx, operand::operand_encoding::idx}},

          {opcodes::OP_ENTRY_POINT, {}},
          {opcodes::OP_COMMAND, {operand::operand_encoding::idx, operand::operand_encoding::value}},

          {opcodes::OP_BITREAD, {operand::operand_encoding::reg, operand::operand_encoding::reg, operand::operand_encoding::reg, operand::operand_encoding::reg, operand::operand_encoding::value, operand::operand_encoding::boolean}},
          {opcodes::OP_BITWRITE, {operand::operand_encoding::reg, operand::operand_encoding::reg, operand::operand_encoding::reg, operand::operand_encoding::reg, operand::operand_encoding::reg, operand::operand_encoding::value, operand::operand_encoding::boolean}},
          {opcodes::OP_BITWRITEA, {operand::operand_encoding::reg, operand::operand_encoding::reg, operand::operand_encoding::reg, operand::operand_encoding::reg}},

          {opcodes::OP_ANNOTATE_PREV, {operand::operand_encoding::value}}};

      /* Str -> Opcode */
      constexpr frozen::unordered_map<frozen::string, opcodes, static_cast<std::uint16_t>(opcodes::OP_AMT) - 1u> str_to_opcode = {
          {frozen::string(str::OP_NOP), opcodes::OP_NOP},
          {frozen::string(str::OP_LOADBOOL), opcodes::OP_LOADBOOL},
          {frozen::string(str::OP_LOADINT), opcodes::OP_LOADINT},
          {frozen::string(str::OP_LOADNONE), opcodes::OP_LOADNONE},
          {frozen::string(str::OP_LOADKVAL), opcodes::OP_LOADKVAL},
          {frozen::string(str::OP_LOADGLOBAL), opcodes::OP_LOADGLOBAL},
          {frozen::string(str::OP_GETTABUPVALUE), opcodes::OP_GETTABUPVALUE},
          {frozen::string(str::OP_SETGLOBAL), opcodes::OP_SETGLOBAL},
          {frozen::string(str::OP_MOVE), opcodes::OP_MOVE},
          {frozen::string(str::OP_ADD), opcodes::OP_ADD},
          {frozen::string(str::OP_SUB), opcodes::OP_SUB},
          {frozen::string(str::OP_MUL), opcodes::OP_MUL},
          {frozen::string(str::OP_DIV), opcodes::OP_DIV},
          {frozen::string(str::OP_MOD), opcodes::OP_MOD},
          {frozen::string(str::OP_POW), opcodes::OP_POW},
          {frozen::string(str::OP_AND), opcodes::OP_AND},
          {frozen::string(str::OP_XOR), opcodes::OP_XOR},
          {frozen::string(str::OP_SHL), opcodes::OP_SHL},
          {frozen::string(str::OP_SHR), opcodes::OP_SHR},
          {frozen::string(str::OP_IDIV), opcodes::OP_IDIV},
          {frozen::string(str::OP_OR), opcodes::OP_OR},
          {frozen::string(str::OP_ADDK), opcodes::OP_ADDK},
          {frozen::string(str::OP_SUBK), opcodes::OP_SUBK},
          {frozen::string(str::OP_MULK), opcodes::OP_MULK},
          {frozen::string(str::OP_DIVK), opcodes::OP_DIVK},
          {frozen::string(str::OP_MODK), opcodes::OP_MODK},
          {frozen::string(str::OP_POWK), opcodes::OP_POWK},
          {frozen::string(str::OP_ANDK), opcodes::OP_ANDK},
          {frozen::string(str::OP_XORK), opcodes::OP_XORK},
          {frozen::string(str::OP_SHLK), opcodes::OP_SHLK},
          {frozen::string(str::OP_SHRK), opcodes::OP_SHRK},
          {frozen::string(str::OP_IDIVK), opcodes::OP_IDIVK},
          {frozen::string(str::OP_ORK), opcodes::OP_ORK},
          {frozen::string(str::OP_ADDN), opcodes::OP_ADDN},
          {frozen::string(str::OP_SUBN), opcodes::OP_SUBN},
          {frozen::string(str::OP_MULN), opcodes::OP_MULN},
          {frozen::string(str::OP_DIVN), opcodes::OP_DIVN},
          {frozen::string(str::OP_MODN), opcodes::OP_MODN},
          {frozen::string(str::OP_POWN), opcodes::OP_POWN},
          {frozen::string(str::OP_ANDN), opcodes::OP_ANDN},
          {frozen::string(str::OP_XORN), opcodes::OP_XORN},
          {frozen::string(str::OP_SHLN), opcodes::OP_SHLN},
          {frozen::string(str::OP_SHRN), opcodes::OP_SHRN},
          {frozen::string(str::OP_IDIVN), opcodes::OP_IDIVN},
          {frozen::string(str::OP_ORN), opcodes::OP_ORN},
          {frozen::string(str::OP_LEN), opcodes::OP_LEN},
          {frozen::string(str::OP_NOT), opcodes::OP_NOT},
          {frozen::string(str::OP_MINUS), opcodes::OP_MINUS},
          {frozen::string(str::OP_BITNOT), opcodes::OP_BITNOT},
          {frozen::string(str::OP_PLUS), opcodes::OP_PLUS},
          {frozen::string(str::OP_REF), opcodes::OP_REF},
          {frozen::string(str::OP_CCALL), opcodes::OP_CCALL},
          {frozen::string(str::OP_VCALL), opcodes::OP_VCALL},
          {frozen::string(str::OP_VPUSH), opcodes::OP_VPUSH},
          {frozen::string(str::OP_SELF), opcodes::OP_SELF},
          {frozen::string(str::OP_RETURN), opcodes::OP_RETURN},
          {frozen::string(str::OP_CONCAT), opcodes::OP_CONCAT},
          {frozen::string(str::OP_JUMP), opcodes::OP_JUMP},
          {frozen::string(str::OP_CMP), opcodes::OP_CMP},
          {frozen::string(str::OP_CMPK), opcodes::OP_CMPK},
          {frozen::string(str::OP_CMPN), opcodes::OP_CMPN},
          {frozen::string(str::OP_CMPB), opcodes::OP_CMPB},
          {frozen::string(str::OP_CMPNONE), opcodes::OP_CMPNONE},
          {frozen::string(str::OP_CMPS), opcodes::OP_CMPS},
          {frozen::string(str::OP_CMPSK), opcodes::OP_CMPSK},
          {frozen::string(str::OP_CMPSN), opcodes::OP_CMPSN},
          {frozen::string(str::OP_CMPSNONE), opcodes::OP_CMPSNONE},
          {frozen::string(str::OP_JUMPIF), opcodes::OP_JUMPIF},
          {frozen::string(str::OP_JUMPIFNOT), opcodes::OP_JUMPIFNOT},
          {frozen::string(str::OP_JUMPIFEQUAL), opcodes::OP_JUMPIFEQUAL},
          {frozen::string(str::OP_JUMPIFNOTEQUAL), opcodes::OP_JUMPIFNOTEQUAL},
          {frozen::string(str::OP_JUMPIFLESS), opcodes::OP_JUMPIFLESS},
          {frozen::string(str::OP_JUMPIFLESSEQUAL), opcodes::OP_JUMPIFLESSEQUAL},
          {frozen::string(str::OP_JUMPIFGREATER), opcodes::OP_JUMPIFGREATER},
          {frozen::string(str::OP_JUMPIFGREATEREQUAL), opcodes::OP_JUMPIFGREATEREQUAL},
          {frozen::string(str::OP_SETIF), opcodes::OP_SETIF},
          {frozen::string(str::OP_SETIFNOT), opcodes::OP_SETIFNOT},
          {frozen::string(str::OP_SETIFEQUAL), opcodes::OP_SETIFEQUAL},
          {frozen::string(str::OP_SETIFNOTEQUAL), opcodes::OP_SETIFNOTEQUAL},
          {frozen::string(str::OP_SETIFLESS), opcodes::OP_SETIFLESS},
          {frozen::string(str::OP_SETIFLESSEQUAL), opcodes::OP_SETIFLESSEQUAL},
          {frozen::string(str::OP_SETIFGREATER), opcodes::OP_SETIFGREATER},
          {frozen::string(str::OP_SETIFGREATEREQUAL), opcodes::OP_SETIFGREATEREQUAL},
          {frozen::string(str::OP_SETUPVALUE), opcodes::OP_SETUPVALUE},
          {frozen::string(str::OP_GETUPVALUE), opcodes::OP_GETUPVALUE},
          {frozen::string(str::OP_DESTROYUPVALUES), opcodes::OP_DESTROYUPVALUES},
          {frozen::string(str::OP_DESTROYUPVALUESA), opcodes::OP_DESTROYUPVALUESA},
          {frozen::string(str::OP_ADDUPVALUE), opcodes::OP_ADDUPVALUE},
          {frozen::string(str::OP_INIT), opcodes::OP_INIT},
          {frozen::string(str::OP_BITCAST), opcodes::OP_BITCAST},
          {frozen::string(str::OP_GETVARIADIC), opcodes::OP_GETVARIADIC},
          {frozen::string(str::OP_SETTABLE), opcodes::OP_SETTABLE},
          {frozen::string(str::OP_GETTABLE), opcodes::OP_GETTABLE},
          {frozen::string(str::OP_SETTABLEN), opcodes::OP_SETTABLEN},
          {frozen::string(str::OP_GETTABLEN), opcodes::OP_GETTABLEN},
          {frozen::string(str::OP_SETTABLEK), opcodes::OP_SETTABLEK},
          {frozen::string(str::OP_GETTABLEK), opcodes::OP_GETTABLEK},
          {frozen::string(str::OP_INITFORLOOPN), opcodes::OP_INITFORLOOPN},
          {frozen::string(str::OP_INITFORLOOPG), opcodes::OP_INITFORLOOPG},
          {frozen::string(str::OP_INITFORLOOPSPECIAL), opcodes::OP_INITFORLOOPSPECIAL},
          {frozen::string(str::OP_NEWCLOSURE), opcodes::OP_NEWCLOSURE},
          {frozen::string(str::OP_REFCLOSURE), opcodes::OP_REFCLOSURE},
          {frozen::string(str::OP_NEWTABLE), opcodes::OP_NEWTABLE},
          {frozen::string(str::OP_REFTABLE), opcodes::OP_REFTABLE},
          {frozen::string(str::OP_NEWTABLEA), opcodes::OP_NEWTABLEA},
          {frozen::string(str::OP_REFTABLEA), opcodes::OP_REFTABLEA},
          {frozen::string(str::OP_SETLIST), opcodes::OP_SETLIST},
          {frozen::string(str::OP_FORLOOPG), opcodes::OP_FORLOOPG},
          {frozen::string(str::OP_FORLOOPN), opcodes::OP_FORLOOPN},
          {frozen::string(str::OP_POPTOP), opcodes::OP_POPTOP},
          {frozen::string(str::OP_POPARG), opcodes::OP_POPARG},
          {frozen::string(str::OP_MEMSET), opcodes::OP_MEMSET},
          {frozen::string(str::OP_MEMREAD), opcodes::OP_MEMREAD},
          {frozen::string(str::OP_SETFLAG), opcodes::OP_SETFLAG},
          {frozen::string(str::OP_SALLOC), opcodes::OP_SALLOC},
          {frozen::string(str::OP_GETSTACK), opcodes::OP_GETSTACK},
          {frozen::string(str::OP_SETSTACK), opcodes::OP_SETSTACK},
          {frozen::string(str::OP_STACKPUSH), opcodes::OP_STACKPUSH},
          {frozen::string(str::OP_STACKPOP), opcodes::OP_STACKPOP},
          {frozen::string(str::OP_POPTOPSTACK), opcodes::OP_POPTOPSTACK},
          {frozen::string(str::OP_CLOGIC_AND), opcodes::OP_CLOGIC_AND},
          {frozen::string(str::OP_CLOGIC_OR), opcodes::OP_CLOGIC_OR},
          {frozen::string(str::OP_PEND), opcodes::OP_PEND},
          {frozen::string(str::OP_MARK), opcodes::OP_MARK},
          {frozen::string(str::OP_MOBJ_CAST), opcodes::OP_MOBJ_CAST},
          {frozen::string(str::OP_NCTOR_MOBJ), opcodes::OP_NCTOR_MOBJ},
          {frozen::string(str::OP_SCALL), opcodes::OP_SCALL},
          {frozen::string(str::OP_FLAGSET), opcodes::OP_FLAGSET},
          {frozen::string(str::OP_FLAGREAD), opcodes::OP_FLAGREAD},
          {frozen::string(str::OP_CREATE_STACK), opcodes::OP_CREATE_STACK},
          {frozen::string(str::OP_PRETURN), opcodes::OP_PRETURN},
          {frozen::string(str::OP_STARTPAGEFUNC), opcodes::OP_STARTPAGEFUNC},
          {frozen::string(str::OP_ENDPAGEFUNC), opcodes::OP_ENDPAGEFUNC},
          {frozen::string(str::OP_PCALL), opcodes::OP_PCALL},
          {frozen::string(str::OP_PJUMP), opcodes::OP_PJUMP},
          {frozen::string(str::OP_SEGREGATE), opcodes::OP_SEGREGATE},
          {frozen::string(str::OP_COMBINE), opcodes::OP_COMBINE},
          {frozen::string(str::OP_FLAGJUMP), opcodes::OP_FLAGJUMP},
          {frozen::string(str::OP_ICALL), opcodes::OP_ICALL},
          {frozen::string(str::OP_TAG_START), opcodes::OP_TAG_START},
          {frozen::string(str::OP_TAG_KV), opcodes::OP_TAG_KV},
          {frozen::string(str::OP_TAG_END), opcodes::OP_TAG_END},
          {frozen::string(str::OP_METADATA), opcodes::OP_METADATA},
          {frozen::string(str::OP_ENTRY_POINT), opcodes::OP_ENTRY_POINT},
          {frozen::string(str::OP_COMMAND), opcodes::OP_COMMAND},
          {frozen::string(str::OP_BITREAD), opcodes::OP_BITREAD},
          {frozen::string(str::OP_BITWRITE), opcodes::OP_BITWRITE},
          {frozen::string(str::OP_BITWRITEA), opcodes::OP_BITWRITEA}};

      /* Opcode -> Str */
      constexpr frozen::unordered_map<opcodes, const char *const, static_cast<std::uint16_t>(opcodes::OP_AMT) - 1u> opcode_to_str = {
          {opcodes::OP_NOP, str::OP_NOP},
          {opcodes::OP_LOADBOOL, str::OP_LOADBOOL},
          {opcodes::OP_LOADINT, str::OP_LOADINT},
          {opcodes::OP_LOADNONE, str::OP_LOADNONE},
          {opcodes::OP_LOADKVAL, str::OP_LOADKVAL},
          {opcodes::OP_LOADGLOBAL, str::OP_LOADGLOBAL},
          {opcodes::OP_GETTABUPVALUE, str::OP_GETTABUPVALUE},
          {opcodes::OP_SETGLOBAL, str::OP_SETGLOBAL},
          {opcodes::OP_MOVE, str::OP_MOVE},
          {opcodes::OP_ADD, str::OP_ADD},
          {opcodes::OP_SUB, str::OP_SUB},
          {opcodes::OP_MUL, str::OP_MUL},
          {opcodes::OP_DIV, str::OP_DIV},
          {opcodes::OP_MOD, str::OP_MOD},
          {opcodes::OP_POW, str::OP_POW},
          {opcodes::OP_AND, str::OP_AND},
          {opcodes::OP_XOR, str::OP_XOR},
          {opcodes::OP_SHL, str::OP_SHL},
          {opcodes::OP_SHR, str::OP_SHR},
          {opcodes::OP_IDIV, str::OP_IDIV},
          {opcodes::OP_OR, str::OP_OR},
          {opcodes::OP_ADDK, str::OP_ADDK},
          {opcodes::OP_SUBK, str::OP_SUBK},
          {opcodes::OP_MULK, str::OP_MULK},
          {opcodes::OP_DIVK, str::OP_DIVK},
          {opcodes::OP_MODK, str::OP_MODK},
          {opcodes::OP_POWK, str::OP_POWK},
          {opcodes::OP_ANDK, str::OP_ANDK},
          {opcodes::OP_XORK, str::OP_XORK},
          {opcodes::OP_SHLK, str::OP_SHLK},
          {opcodes::OP_SHRK, str::OP_SHRK},
          {opcodes::OP_IDIVK, str::OP_IDIVK},
          {opcodes::OP_ORK, str::OP_ORK},
          {opcodes::OP_ADDN, str::OP_ADDN},
          {opcodes::OP_SUBN, str::OP_SUBN},
          {opcodes::OP_MULN, str::OP_MULN},
          {opcodes::OP_DIVN, str::OP_DIVN},
          {opcodes::OP_MODN, str::OP_MODN},
          {opcodes::OP_POWN, str::OP_POWN},
          {opcodes::OP_ANDN, str::OP_ANDN},
          {opcodes::OP_XORN, str::OP_XORN},
          {opcodes::OP_SHLN, str::OP_SHLN},
          {opcodes::OP_SHRN, str::OP_SHRN},
          {opcodes::OP_IDIVN, str::OP_IDIVN},
          {opcodes::OP_ORN, str::OP_ORN},
          {opcodes::OP_LEN, str::OP_LEN},
          {opcodes::OP_NOT, str::OP_NOT},
          {opcodes::OP_MINUS, str::OP_MINUS},
          {opcodes::OP_BITNOT, str::OP_BITNOT},
          {opcodes::OP_PLUS, str::OP_PLUS},
          {opcodes::OP_REF, str::OP_REF},
          {opcodes::OP_CCALL, str::OP_CCALL},
          {opcodes::OP_VCALL, str::OP_VCALL},
          {opcodes::OP_VPUSH, str::OP_VPUSH},
          {opcodes::OP_SELF, str::OP_SELF},
          {opcodes::OP_RETURN, str::OP_RETURN},
          {opcodes::OP_CONCAT, str::OP_CONCAT},
          {opcodes::OP_JUMP, str::OP_JUMP},
          {opcodes::OP_CMP, str::OP_CMP},
          {opcodes::OP_CMPK, str::OP_CMPK},
          {opcodes::OP_CMPN, str::OP_CMPN},
          {opcodes::OP_CMPB, str::OP_CMPB},
          {opcodes::OP_CMPNONE, str::OP_CMPNONE},
          {opcodes::OP_CMPS, str::OP_CMPS},
          {opcodes::OP_CMPSK, str::OP_CMPSK},
          {opcodes::OP_CMPSN, str::OP_CMPSN},
          {opcodes::OP_CMPSNONE, str::OP_CMPSNONE},
          {opcodes::OP_JUMPIF, str::OP_JUMPIF},
          {opcodes::OP_JUMPIFNOT, str::OP_JUMPIFNOT},
          {opcodes::OP_JUMPIFEQUAL, str::OP_JUMPIFEQUAL},
          {opcodes::OP_JUMPIFNOTEQUAL, str::OP_JUMPIFNOTEQUAL},
          {opcodes::OP_JUMPIFLESS, str::OP_JUMPIFLESS},
          {opcodes::OP_JUMPIFLESSEQUAL, str::OP_JUMPIFLESSEQUAL},
          {opcodes::OP_JUMPIFGREATER, str::OP_JUMPIFGREATER},
          {opcodes::OP_JUMPIFGREATEREQUAL, str::OP_JUMPIFGREATEREQUAL},
          {opcodes::OP_SETIF, str::OP_SETIF},
          {opcodes::OP_SETIFNOT, str::OP_SETIFNOT},
          {opcodes::OP_SETIFEQUAL, str::OP_SETIFEQUAL},
          {opcodes::OP_SETIFNOTEQUAL, str::OP_SETIFNOTEQUAL},
          {opcodes::OP_SETIFLESS, str::OP_SETIFLESS},
          {opcodes::OP_SETIFLESSEQUAL, str::OP_SETIFLESSEQUAL},
          {opcodes::OP_SETIFGREATER, str::OP_SETIFGREATER},
          {opcodes::OP_SETIFGREATEREQUAL, str::OP_SETIFGREATEREQUAL},
          {opcodes::OP_SETUPVALUE, str::OP_SETUPVALUE},
          {opcodes::OP_GETUPVALUE, str::OP_GETUPVALUE},
          {opcodes::OP_DESTROYUPVALUES, str::OP_DESTROYUPVALUES},
          {opcodes::OP_DESTROYUPVALUESA, str::OP_DESTROYUPVALUESA},
          {opcodes::OP_ADDUPVALUE, str::OP_ADDUPVALUE},
          {opcodes::OP_INIT, str::OP_INIT},
          {opcodes::OP_BITCAST, str::OP_BITCAST},
          {opcodes::OP_GETVARIADIC, str::OP_GETVARIADIC},
          {opcodes::OP_SETTABLE, str::OP_SETTABLE},
          {opcodes::OP_GETTABLE, str::OP_GETTABLE},
          {opcodes::OP_SETTABLEN, str::OP_SETTABLEN},
          {opcodes::OP_GETTABLEN, str::OP_GETTABLEN},
          {opcodes::OP_SETTABLEK, str::OP_SETTABLEK},
          {opcodes::OP_GETTABLEK, str::OP_GETTABLEK},
          {opcodes::OP_INITFORLOOPN, str::OP_INITFORLOOPN},
          {opcodes::OP_INITFORLOOPG, str::OP_INITFORLOOPG},
          {opcodes::OP_INITFORLOOPSPECIAL, str::OP_INITFORLOOPSPECIAL},
          {opcodes::OP_NEWCLOSURE, str::OP_NEWCLOSURE},
          {opcodes::OP_REFCLOSURE, str::OP_REFCLOSURE},
          {opcodes::OP_NEWTABLE, str::OP_NEWTABLE},
          {opcodes::OP_REFTABLE, str::OP_REFTABLE},
          {opcodes::OP_NEWTABLEA, str::OP_NEWTABLEA},
          {opcodes::OP_REFTABLEA, str::OP_REFTABLEA},
          {opcodes::OP_SETLIST, str::OP_SETLIST},
          {opcodes::OP_FORLOOPG, str::OP_FORLOOPG},
          {opcodes::OP_FORLOOPN, str::OP_FORLOOPN},
          {opcodes::OP_POPTOP, str::OP_POPTOP},
          {opcodes::OP_POPARG, str::OP_POPARG},
          {opcodes::OP_MEMSET, str::OP_MEMSET},
          {opcodes::OP_MEMREAD, str::OP_MEMREAD},
          {opcodes::OP_SETFLAG, str::OP_SETFLAG},
          {opcodes::OP_SALLOC, str::OP_SALLOC},
          {opcodes::OP_GETSTACK, str::OP_GETSTACK},
          {opcodes::OP_SETSTACK, str::OP_SETSTACK},
          {opcodes::OP_STACKPUSH, str::OP_STACKPUSH},
          {opcodes::OP_STACKPOP, str::OP_STACKPOP},
          {opcodes::OP_POPTOPSTACK, str::OP_POPTOPSTACK},
          {opcodes::OP_CLOGIC_AND, str::OP_CLOGIC_AND},
          {opcodes::OP_CLOGIC_OR, str::OP_CLOGIC_OR},
          {opcodes::OP_PEND, str::OP_PEND},
          {opcodes::OP_MARK, str::OP_MARK},
          {opcodes::OP_MOBJ_CAST, str::OP_MOBJ_CAST},
          {opcodes::OP_NCTOR_MOBJ, str::OP_NCTOR_MOBJ},
          {opcodes::OP_SCALL, str::OP_SCALL},
          {opcodes::OP_FLAGSET, str::OP_FLAGSET},
          {opcodes::OP_FLAGREAD, str::OP_FLAGREAD},
          {opcodes::OP_CREATE_STACK, str::OP_CREATE_STACK},
          {opcodes::OP_PRETURN, str::OP_PRETURN},
          {opcodes::OP_STARTPAGEFUNC, str::OP_STARTPAGEFUNC},
          {opcodes::OP_ENDPAGEFUNC, str::OP_ENDPAGEFUNC},
          {opcodes::OP_PCALL, str::OP_PCALL},
          {opcodes::OP_PJUMP, str::OP_PJUMP},
          {opcodes::OP_SEGREGATE, str::OP_SEGREGATE},
          {opcodes::OP_COMBINE, str::OP_COMBINE},
          {opcodes::OP_FLAGJUMP, str::OP_FLAGJUMP},
          {opcodes::OP_ICALL, str::OP_ICALL},
          {opcodes::OP_TAG_START, str::OP_TAG_START},
          {opcodes::OP_TAG_KV, str::OP_TAG_KV},
          {opcodes::OP_TAG_END, str::OP_TAG_END},
          {opcodes::OP_METADATA, str::OP_METADATA},
          {opcodes::OP_ENTRY_POINT, str::OP_ENTRY_POINT},
          {opcodes::OP_COMMAND, str::OP_COMMAND},
          {opcodes::OP_BITREAD, str::OP_BITREAD},
          {opcodes::OP_BITWRITE, str::OP_BITWRITE},
          {opcodes::OP_BITWRITEA, str::OP_BITWRITEA}};

      namespace check {

            /* Bunch of checks to insure backwards compatibility */
            static_assert(static_cast<std::uint8_t>(opcodes::OP_NOP) == 0u, "OP_NOP changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_LOADBOOL) == 1u, "OP_LOADBOOL changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_LOADINT) == 2u, "OP_LOADINT changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_LOADNONE) == 3u, "OP_LOADNONE changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_LOADKVAL) == 4u, "OP_LOADKVAL changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_LOADGLOBAL) == 5u, "OP_LOADGLOBAL changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_GETTABUPVALUE) == 6u, "OP_GETTABUPVALUE changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_SETGLOBAL) == 7u, "OP_SETGLOBAL changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_MOVE) == 8u, "OP_MOVE changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_ADD) == 9u, "OP_ADD changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_SUB) == 10u, "OP_SUB changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_MUL) == 11u, "OP_MUL changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_DIV) == 12u, "OP_DIV changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_MOD) == 13u, "OP_MOD changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_POW) == 14u, "OP_POW changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_AND) == 15u, "OP_AND changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_XOR) == 16u, "OP_XOR changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_SHL) == 17u, "OP_SHL changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_SHR) == 18u, "OP_SHR changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_IDIV) == 19u, "OP_IDIV changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_OR) == 20u, "OP_OR changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_ADDK) == 21u, "OP_ADDK changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_SUBK) == 22u, "OP_SUBK changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_MULK) == 23u, "OP_MULK changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_DIVK) == 24u, "OP_DIVK changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_MODK) == 25u, "OP_MODK changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_POWK) == 26u, "OP_POWK changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_ANDK) == 27u, "OP_ANDK changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_XORK) == 28u, "OP_XORK changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_SHLK) == 29u, "OP_SHLK changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_SHRK) == 30u, "OP_SHRK changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_IDIVK) == 31u, "OP_IDIVK changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_ORK) == 32u, "OP_ORK changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_ADDN) == 33u, "OP_ADDN changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_SUBN) == 34u, "OP_SUBN changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_MULN) == 35u, "OP_MULN changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_DIVN) == 36u, "OP_DIVN changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_MODN) == 37u, "OP_MODN changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_POWN) == 38u, "OP_POWN changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_ANDN) == 39u, "OP_ANDN changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_XORN) == 40u, "OP_XORN changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_SHLN) == 41u, "OP_SHLN changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_SHRN) == 42u, "OP_SHRN changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_IDIVN) == 43u, "OP_IDIVN changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_ORN) == 44u, "OP_ORN changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_LEN) == 45u, "OP_LEN changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_NOT) == 46u, "OP_NOT changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_MINUS) == 47u, "OP_MINUS changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_BITNOT) == 48u, "OP_BITNOT changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_PLUS) == 49u, "OP_PLUS changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_REF) == 50u, "OP_REF changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_CCALL) == 51u, "OP_CCALL changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_VCALL) == 52u, "OP_VCALL changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_VPUSH) == 53u, "OP_VPUSH changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_SELF) == 54u, "OP_SELF changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_RETURN) == 55u, "OP_RETURN changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_CONCAT) == 56u, "OP_CONCAT changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_JUMP) == 57u, "OP_JUMP changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_CMP) == 58u, "OP_CMP changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_CMPK) == 59u, "OP_CMPK changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_CMPN) == 60u, "OP_CMPN changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_CMPB) == 61u, "OP_CMPB changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_CMPNONE) == 62u, "OP_CMPNONE changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_CMPS) == 63u, "OP_CMPS changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_CMPSK) == 64u, "OP_CMPSK changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_CMPSN) == 65u, "OP_CMPSN changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_CMPSNONE) == 66u, "OP_CMPSNONE changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_JUMPIF) == 67u, "OP_JUMPIF changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_JUMPIFNOT) == 68u, "OP_JUMPIFNOT changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_JUMPIFEQUAL) == 69u, "OP_JUMPIFEQUAL changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_JUMPIFNOTEQUAL) == 70u, "OP_JUMPIFNOTEQUAL changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_JUMPIFLESS) == 71u, "OP_JUMPIFLESS changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_JUMPIFLESSEQUAL) == 72u, "OP_JUMPIFLESSEQUAL changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_JUMPIFGREATER) == 73u, "OP_JUMPIFGREATER changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_JUMPIFGREATEREQUAL) == 74u, "OP_JUMPIFGREATEREQUAL changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_SETIF) == 75u, "OP_SETIF changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_SETIFNOT) == 76u, "OP_SETIFNOT changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_SETIFEQUAL) == 77u, "OP_SETIFEQUAL changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_SETIFNOTEQUAL) == 78u, "OP_SETIFNOTEQUAL changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_SETIFLESS) == 79u, "OP_SETIFLESS changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_SETIFLESSEQUAL) == 80u, "OP_SETIFLESSEQUAL changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_SETIFGREATER) == 81u, "OP_SETIFGREATER changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_SETIFGREATEREQUAL) == 82u, "OP_SETIFGREATEREQUAL changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_SETUPVALUE) == 83u, "OP_SETUPVALUE changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_GETUPVALUE) == 84u, "OP_GETUPVALUE changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_DESTROYUPVALUES) == 85u, "OP_DESTROYUPVALUES changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_DESTROYUPVALUESA) == 86u, "OP_DESTROYUPVALUESA changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_ADDUPVALUE) == 87u, "OP_ADDUPVALUE changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_INIT) == 88u, "OP_INIT changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_BITCAST) == 89u, "OP_BITCAST changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_GETVARIADIC) == 90u, "OP_GETVARIADIC changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_SETTABLE) == 91u, "OP_SETTABLE changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_GETTABLE) == 92u, "OP_GETTABLE changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_SETTABLEN) == 93u, "OP_SETTABLEN changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_GETTABLEN) == 94u, "OP_GETTABLEN changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_SETTABLEK) == 95u, "OP_SETTABLEK changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_GETTABLEK) == 96u, "OP_GETTABLEK changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_INITFORLOOPN) == 97u, "OP_INITFORLOOPN changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_INITFORLOOPG) == 98u, "OP_INITFORLOOPG changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_INITFORLOOPSPECIAL) == 99u, "OP_INITFORLOOPSPECIAL changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_NEWCLOSURE) == 100u, "OP_NEWCLOSURE changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_REFCLOSURE) == 101u, "OP_REFCLOSURE changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_NEWTABLE) == 102u, "OP_NEWTABLE changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_REFTABLE) == 103u, "OP_REFTABLE changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_NEWTABLEA) == 104u, "OP_NEWTABLEA changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_REFTABLEA) == 105u, "OP_REFTABLEA changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_SETLIST) == 106u, "OP_SETLIST changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_FORLOOPG) == 107u, "OP_FORLOOPG changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_FORLOOPN) == 108u, "OP_FORLOOPN changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_POPTOP) == 109u, "OP_POPTOP changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_POPARG) == 110u, "OP_POPARG changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_MEMSET) == 111u, "OP_MEMSET changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_MEMREAD) == 112u, "OP_MEMREAD changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_SETFLAG) == 113u, "OP_SETFLAG changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_SALLOC) == 114u, "OP_SALLOC changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_GETSTACK) == 115u, "OP_GETSTACK changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_SETSTACK) == 116u, "OP_SETSTACK changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_STACKPUSH) == 117u, "OP_STACKPUSH changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_STACKPOP) == 118u, "OP_STACKPOP changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_POPTOPSTACK) == 119u, "OP_POPTOPSTACK changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_CLOGIC_AND) == 120u, "OP_CLOGIC_AND changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_CLOGIC_OR) == 121u, "OP_CLOGIC_OR changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_PEND) == 122u, "OP_PEND changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_MARK) == 123u, "OP_MARK changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_MOBJ_CAST) == 124u, "OP_MOBJ_CAST changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_NCTOR_MOBJ) == 125u, "OP_NCTOR_MOBJ changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_SCALL) == 126u, "OP_SCALL changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_FLAGSET) == 127u, "OP_FLAGSET changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_FLAGREAD) == 128u, "OP_FLAGREAD changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_CREATE_STACK) == 129u, "OP_CREATE_STACK changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_PRETURN) == 130u, "OP_PRETURN changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_STARTPAGEFUNC) == 131u, "OP_STARTPAGEFUNC changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_ENDPAGEFUNC) == 132u, "OP_ENDPAGEFUNC changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_PCALL) == 133u, "OP_PCALL changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_PJUMP) == 134u, "OP_PJUMP changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_SEGREGATE) == 135u, "OP_SEGREGATE changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_COMBINE) == 136u, "OP_COMBINE changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_FLAGJUMP) == 137u, "OP_FLAGJUMP changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_ICALL) == 138u, "OP_ICALL changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_TAG_START) == 139u, "OP_TAG_START changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_TAG_KV) == 140u, "OP_TAG_KV changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_TAG_END) == 141u, "OP_TAG_END changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_METADATA) == 142u, "OP_METADATA changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_ENTRY_POINT) == 143u, "OP_ENTRY_POINT changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_COMMAND) == 144u, "OP_COMMAND changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_BITREAD) == 145u, "OP_BITREAD changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_BITWRITE) == 146u, "OP_BITWRITE changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_BITWRITEA) == 147u, "OP_BITWRITEA changed, will break compatibility!");
            static_assert(static_cast<std::uint8_t>(opcodes::OP_ANNOTATE_PREV) == 148u, "OP_ANNOTATE_PREV changed, will break compatibility!");

      } // namespace check

      namespace is_op {

            /* Psuedo instruction? */
            inline constexpr bool psuedo(const opcodes op) {
                  switch (op) {
                        case opcodes::OP_NOP:
                        case opcodes::OP_MARK:
                        case opcodes::OP_PEND:
                        case opcodes::OP_INIT:
                        case opcodes::OP_SEGREGATE:
                        case opcodes::OP_COMBINE:
                        case opcodes::OP_ENTRY_POINT: {
                              return true;
                        }
                        default: {
                              return false;
                        }
                  }
            }

            /* Does upvalue kind gets a value? */
            inline constexpr bool upvalue_kind_reg_reference(const operand::upvalue_kind k) {
                  return k == operand::upvalue_kind::contents || k == operand::upvalue_kind::reference;
            }
      } // namespace is_op
} // namespace luramas::il::arch