#include "lexer.hpp"

namespace luramas::il::lexer {

      bool lexeme::scope_start() const {
            switch (this->kind) {
                  case inst_kinds::forinit:
                  case inst_kinds::branch_condition:
                  case inst_kinds::branch: {
                        return true;
                  }
                  default: {
                        return false;
                  }
            }
      }
      bool lexeme::kind_stat() const {
            switch (this->kind) {
                  case inst_kinds::for_:
                  case inst_kinds::return_:
                  case inst_kinds::set_global:
                  case inst_kinds::forinit:
                  case inst_kinds::capture: {
                        return true;
                  }
                  case inst_kinds::ccall: {
                        return !this->has_operand_kind<operand_kinds::dest>();
                  }
                  default: {
                        return false;
                  }
            }
      }
      bool lexeme::jumps() const {
            return this->disassembly->ref != nullptr;
      }
      luramas_address lexeme::jump() const {
            return this->disassembly->ref->addr;
      }
      bool lexeme::jump_forward() const {
            return this->jumps() && this->disassembly->addr < this->disassembly->ref->addr;
      }
      bool lexeme::jump_backwards() const {
            return this->jumps() ? !this->jump_forward() : false;
      }

      std::shared_ptr<luramas::il::lexer::lexeme> lexer(const std::shared_ptr<luramas::il::disassembly> &disassembly) {

            auto result = std::make_shared<luramas::il::lexer::lexeme>();
            result->disassembly = disassembly;
            switch (disassembly->op) {
                  case luramas::il::arch::opcodes::OP_NOP: {
                        result->kind = luramas::il::lexer::inst_kinds::nothing;
                        result->operands = {};
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_CCALL: {
                        result->kind = luramas::il::lexer::inst_kinds::ccall;
                        result->operands = {(result->disassembly->operands.back()->dis.val ? luramas::il::lexer::operand_kinds::dest : luramas::il::lexer::operand_kinds::reg) /* Has return so its dest else its reg. */, luramas::il::lexer::operand_kinds::value, luramas::il::lexer::operand_kinds::value}; /* Operands are dest, int(arg), int(return) */
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_RETURN: {
                        result->kind = luramas::il::lexer::inst_kinds::return_;
                        result->operands = {luramas::il::lexer::operand_kinds::reg, luramas::il::lexer::operand_kinds::value}; /* Operands are dest, int */
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_JUMPIF:
                  case luramas::il::arch::opcodes::OP_JUMPIFNOT:
                  case luramas::il::arch::opcodes::OP_JUMPIFEQUAL:
                  case luramas::il::arch::opcodes::OP_JUMPIFNOTEQUAL:
                  case luramas::il::arch::opcodes::OP_JUMPIFLESS:
                  case luramas::il::arch::opcodes::OP_JUMPIFLESSEQUAL:
                  case luramas::il::arch::opcodes::OP_JUMPIFGREATER:
                  case luramas::il::arch::opcodes::OP_JUMPIFGREATEREQUAL: {
                        result->kind = luramas::il::lexer::inst_kinds::branch_condition;
                        result->operands = {luramas::il::lexer::operand_kinds::jmpaddr}; /* Operands are addr */
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_JUMP: {
                        result->kind = luramas::il::lexer::inst_kinds::branch;
                        result->operands = {luramas::il::lexer::operand_kinds::jmpaddr}; /* Operands are addr */
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_CMP: {
                        result->kind = luramas::il::lexer::inst_kinds::compare;
                        result->operands = {luramas::il::lexer::operand_kinds::compare, luramas::il::lexer::operand_kinds::compare};
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_CMPK: {
                        result->kind = luramas::il::lexer::inst_kinds::compare;
                        result->operands = {luramas::il::lexer::operand_kinds::compare, luramas::il::lexer::operand_kinds::kvalue};
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_CMPN: {
                        result->kind = luramas::il::lexer::inst_kinds::compare;
                        result->operands = {luramas::il::lexer::operand_kinds::compare, luramas::il::lexer::operand_kinds::integer};
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_CMPB: {
                        result->kind = luramas::il::lexer::inst_kinds::compare;
                        result->operands = {luramas::il::lexer::operand_kinds::reg, luramas::il::lexer::operand_kinds::boolean};
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_CMPNONE: {
                        result->kind = luramas::il::lexer::inst_kinds::compare;
                        result->operands = {luramas::il::lexer::operand_kinds::compare};
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_CMPS: {
                        result->kind = luramas::il::lexer::inst_kinds::compare;
                        result->operands = {luramas::il::lexer::operand_kinds::compare};
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_CMPSK: {
                        result->kind = luramas::il::lexer::inst_kinds::compare;
                        result->operands = {luramas::il::lexer::operand_kinds::kvalue};
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_CMPSN: {
                        result->kind = luramas::il::lexer::inst_kinds::compare;
                        result->operands = {luramas::il::lexer::operand_kinds::value};
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_CMPSNONE: {
                        result->kind = luramas::il::lexer::inst_kinds::compare;
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_SETIF:
                  case luramas::il::arch::opcodes::OP_SETIFNOT:
                  case luramas::il::arch::opcodes::OP_SETIFEQUAL:
                  case luramas::il::arch::opcodes::OP_SETIFNOTEQUAL:
                  case luramas::il::arch::opcodes::OP_SETIFLESS:
                  case luramas::il::arch::opcodes::OP_SETIFLESSEQUAL:
                  case luramas::il::arch::opcodes::OP_SETIFGREATER:
                  case luramas::il::arch::opcodes::OP_SETIFGREATEREQUAL: {
                        result->kind = luramas::il::lexer::inst_kinds::compare_dest;
                        result->operands = {luramas::il::lexer::operand_kinds::dest};
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_ADD:
                  case luramas::il::arch::opcodes::OP_SUB:
                  case luramas::il::arch::opcodes::OP_MUL:
                  case luramas::il::arch::opcodes::OP_DIV:
                  case luramas::il::arch::opcodes::OP_MOD:
                  case luramas::il::arch::opcodes::OP_POW:
                  case luramas::il::arch::opcodes::OP_AND:
                  case luramas::il::arch::opcodes::OP_XOR:
                  case luramas::il::arch::opcodes::OP_SHL:
                  case luramas::il::arch::opcodes::OP_SHR:
                  case luramas::il::arch::opcodes::OP_IDIV:
                  case luramas::il::arch::opcodes::OP_OR: {
                        result->kind = luramas::il::lexer::inst_kinds::arith;
                        result->operands = {luramas::il::lexer::operand_kinds::dest, luramas::il::lexer::operand_kinds::source, luramas::il::lexer::operand_kinds::source}; /* Operands are dest, source, source */
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_ADDK:
                  case luramas::il::arch::opcodes::OP_SUBK:
                  case luramas::il::arch::opcodes::OP_MULK:
                  case luramas::il::arch::opcodes::OP_DIVK:
                  case luramas::il::arch::opcodes::OP_MODK:
                  case luramas::il::arch::opcodes::OP_POWK:
                  case luramas::il::arch::opcodes::OP_ANDK:
                  case luramas::il::arch::opcodes::OP_XORK:
                  case luramas::il::arch::opcodes::OP_SHLK:
                  case luramas::il::arch::opcodes::OP_SHRK:
                  case luramas::il::arch::opcodes::OP_IDIVK:
                  case luramas::il::arch::opcodes::OP_ORK: {
                        result->kind = luramas::il::lexer::inst_kinds::arith;
                        result->operands = {luramas::il::lexer::operand_kinds::dest, luramas::il::lexer::operand_kinds::source, luramas::il::lexer::operand_kinds::kvalue}; /* Operands are dest, source, kvalue */
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_ADDN:
                  case luramas::il::arch::opcodes::OP_SUBN:
                  case luramas::il::arch::opcodes::OP_MULN:
                  case luramas::il::arch::opcodes::OP_DIVN:
                  case luramas::il::arch::opcodes::OP_MODN:
                  case luramas::il::arch::opcodes::OP_POWN:
                  case luramas::il::arch::opcodes::OP_ANDN:
                  case luramas::il::arch::opcodes::OP_XORN:
                  case luramas::il::arch::opcodes::OP_SHLN:
                  case luramas::il::arch::opcodes::OP_SHRN:
                  case luramas::il::arch::opcodes::OP_IDIVN:
                  case luramas::il::arch::opcodes::OP_ORN: {
                        result->kind = luramas::il::lexer::inst_kinds::arith;
                        result->operands = {luramas::il::lexer::operand_kinds::dest, luramas::il::lexer::operand_kinds::source, luramas::il::lexer::operand_kinds::integer}; /* Operands are dest, source, integer */
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_LOADINT: {
                        result->kind = luramas::il::lexer::inst_kinds::load;
                        result->operands = {luramas::il::lexer::operand_kinds::dest, luramas::il::lexer::operand_kinds::integer};
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_GETTABUPVALUE:
                  case luramas::il::arch::opcodes::OP_LOADKVAL: {
                        result->kind = luramas::il::lexer::inst_kinds::load;
                        result->operands = {luramas::il::lexer::operand_kinds::dest, luramas::il::lexer::operand_kinds::kvalue_embeded};
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_LOADNONE: {
                        result->kind = luramas::il::lexer::inst_kinds::load;
                        result->operands = {luramas::il::lexer::operand_kinds::dest};
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_LOADBOOL: {
                        result->kind = luramas::il::lexer::inst_kinds::load;
                        result->operands = {luramas::il::lexer::operand_kinds::dest, luramas::il::lexer::operand_kinds::value};
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_LOADGLOBAL: {
                        result->kind = luramas::il::lexer::inst_kinds::get_global;
                        result->operands = {luramas::il::lexer::operand_kinds::dest, luramas::il::lexer::operand_kinds::kvalue};
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_SETGLOBAL: {
                        result->kind = luramas::il::lexer::inst_kinds::set_global;
                        result->operands = {luramas::il::lexer::operand_kinds::source, luramas::il::lexer::operand_kinds::kvalue};
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_MOVE: {
                        result->kind = luramas::il::lexer::inst_kinds::expression;
                        result->operands = {luramas::il::lexer::operand_kinds::dest, luramas::il::lexer::operand_kinds::source};
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_GETUPVALUE: {
                        result->kind = luramas::il::lexer::inst_kinds::upvalue_gs;
                        result->operands = {luramas::il::lexer::operand_kinds::dest, luramas::il::lexer::operand_kinds::upvalue};
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_SETUPVALUE: {
                        result->kind = luramas::il::lexer::inst_kinds::upvalue_gs;
                        result->operands = {luramas::il::lexer::operand_kinds::source, luramas::il::lexer::operand_kinds::upvalue};
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_DESTROYUPVALUES: {
                        result->kind = luramas::il::lexer::inst_kinds::expression;
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_DESTROYUPVALUESA: {
                        result->kind = luramas::il::lexer::inst_kinds::expression;
                        result->operands = {luramas::il::lexer::operand_kinds::reg};
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_GETTABLE: {
                        result->kind = luramas::il::lexer::inst_kinds::table_get;
                        result->operands = {luramas::il::lexer::operand_kinds::dest, luramas::il::lexer::operand_kinds::source, luramas::il::lexer::operand_kinds::table_reg};
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_SETTABLE: {
                        result->kind = luramas::il::lexer::inst_kinds::table_set;
                        result->operands = {luramas::il::lexer::operand_kinds::source, luramas::il::lexer::operand_kinds::reg, luramas::il::lexer::operand_kinds::table_reg};
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_GETTABLEK: {
                        result->kind = luramas::il::lexer::inst_kinds::table_get;
                        result->operands = {luramas::il::lexer::operand_kinds::dest, luramas::il::lexer::operand_kinds::source, luramas::il::lexer::operand_kinds::kvalue};
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_SETTABLEK: {
                        result->kind = luramas::il::lexer::inst_kinds::table_set;
                        result->operands = {luramas::il::lexer::operand_kinds::source, luramas::il::lexer::operand_kinds::reg, luramas::il::lexer::operand_kinds::kvalue};
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_GETTABLEN: {
                        result->kind = luramas::il::lexer::inst_kinds::table_get;
                        result->operands = {luramas::il::lexer::operand_kinds::dest, luramas::il::lexer::operand_kinds::source, luramas::il::lexer::operand_kinds::table_idx};
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_SETTABLEN: {
                        result->kind = luramas::il::lexer::inst_kinds::table_set;
                        result->operands = {luramas::il::lexer::operand_kinds::source, luramas::il::lexer::operand_kinds::reg, luramas::il::lexer::operand_kinds::table_idx};
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_NEWCLOSURE: {
                        result->kind = luramas::il::lexer::inst_kinds::expression;
                        result->operands = {luramas::il::lexer::operand_kinds::dest, luramas::il::lexer::operand_kinds::closure};
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_SELF: {
                        result->kind = luramas::il::lexer::inst_kinds::expression;
                        result->operands = {luramas::il::lexer::operand_kinds::dest, luramas::il::lexer::operand_kinds::source, luramas::il::lexer::operand_kinds::kvalue};
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_CONCAT: {
                        result->kind = luramas::il::lexer::inst_kinds::expression;
                        result->operands = {luramas::il::lexer::operand_kinds::dest, luramas::il::lexer::operand_kinds::source, luramas::il::lexer::operand_kinds::source};
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_LEN:
                  case luramas::il::arch::opcodes::OP_NOT:
                  case luramas::il::arch::opcodes::OP_MINUS:
                  case luramas::il::arch::opcodes::OP_BITNOT:
                  case luramas::il::arch::opcodes::OP_PLUS:
                  case luramas::il::arch::opcodes::OP_REF: {
                        result->kind = luramas::il::lexer::inst_kinds::unary;
                        result->operands = {luramas::il::lexer::operand_kinds::dest, luramas::il::lexer::operand_kinds::source};
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_NEWTABLE:
                  case luramas::il::arch::opcodes::OP_NEWTABLEA: {
                        result->kind = luramas::il::lexer::inst_kinds::new_table;
                        result->operands = {luramas::il::lexer::operand_kinds::dest, luramas::il::lexer::operand_kinds::value, luramas::il::lexer::operand_kinds::value};
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_REFTABLE:
                  case luramas::il::arch::opcodes::OP_REFTABLEA: {
                        result->kind = luramas::il::lexer::inst_kinds::new_table;
                        result->operands = {luramas::il::lexer::operand_kinds::dest, luramas::il::lexer::operand_kinds::kvalue};
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_SETLIST: {
                        result->kind = luramas::il::lexer::inst_kinds::set_table;
                        result->operands = {luramas::il::lexer::operand_kinds::dest, luramas::il::lexer::operand_kinds::source, luramas::il::lexer::operand_kinds::value, luramas::il::lexer::operand_kinds::value};
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_POPARG: {
                        result->kind = luramas::il::lexer::inst_kinds::special_flag;
                        result->operands = {luramas::il::lexer::operand_kinds::reg};
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_MEMSET: {
                        result->kind = luramas::il::lexer::inst_kinds::expression;
                        result->operands = {luramas::il::lexer::operand_kinds::reg, luramas::il::lexer::operand_kinds::reg, luramas::il::lexer::operand_kinds::value};
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_MEMREAD: {
                        result->kind = luramas::il::lexer::inst_kinds::expression;
                        result->operands = {luramas::il::lexer::operand_kinds::dest, luramas::il::lexer::operand_kinds::reg, luramas::il::lexer::operand_kinds::value};
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_SETFLAG: {
                        result->kind = luramas::il::lexer::inst_kinds::expression;
                        result->operands = {luramas::il::lexer::operand_kinds::value};
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_SALLOC: {
                        result->kind = luramas::il::lexer::inst_kinds::expression;
                        result->operands = {luramas::il::lexer::operand_kinds::reg, luramas::il::lexer::operand_kinds::value};
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_GETSTACK: {
                        result->kind = luramas::il::lexer::inst_kinds::expression;
                        result->operands = {luramas::il::lexer::operand_kinds::dest, luramas::il::lexer::operand_kinds::value};
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_SETSTACK: {
                        result->kind = luramas::il::lexer::inst_kinds::expression;
                        result->operands = {luramas::il::lexer::operand_kinds::source, luramas::il::lexer::operand_kinds::value};
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_STACKPUSH: {
                        result->kind = luramas::il::lexer::inst_kinds::expression;
                        result->operands = {luramas::il::lexer::operand_kinds::value, luramas::il::lexer::operand_kinds::source};
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_STACKPOP: {
                        result->kind = luramas::il::lexer::inst_kinds::expression;
                        result->operands = {luramas::il::lexer::operand_kinds::value, luramas::il::lexer::operand_kinds::source};
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_POPTOPSTACK: {
                        result->kind = luramas::il::lexer::inst_kinds::expression;
                        result->operands = {luramas::il::lexer::operand_kinds::source};
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_INITFORLOOPN: {
                        result->kind = luramas::il::lexer::inst_kinds::forinit;
                        result->operands = {luramas::il::lexer::operand_kinds::dest, luramas::il::lexer::operand_kinds::reg, luramas::il::lexer::operand_kinds::reg, luramas::il::lexer::operand_kinds::jmpaddr};
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_INITFORLOOPG: {
                        result->kind = luramas::il::lexer::inst_kinds::forinit;
                        result->operands = {luramas::il::lexer::operand_kinds::reg, luramas::il::lexer::operand_kinds::value, luramas::il::lexer::operand_kinds::jmpaddr};
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_INITFORLOOPSPECIAL: {
                        result->kind = luramas::il::lexer::inst_kinds::forinit;
                        result->operands = {luramas::il::lexer::operand_kinds::dest, luramas::il::lexer::operand_kinds::dest, luramas::il::lexer::operand_kinds::source, luramas::il::lexer::operand_kinds::value, luramas::il::lexer::operand_kinds::jmpaddr};
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_FORLOOPG: {
                        result->kind = luramas::il::lexer::inst_kinds::for_;
                        result->operands = {luramas::il::lexer::operand_kinds::source, luramas::il::lexer::operand_kinds::value, luramas::il::lexer::operand_kinds::jmpaddr};
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_FORLOOPN: {
                        result->kind = luramas::il::lexer::inst_kinds::for_;
                        result->operands = {luramas::il::lexer::operand_kinds::source /* Dest is not needed because it is already set before hand by IL instruction. */, luramas::il::lexer::operand_kinds::source, luramas::il::lexer::operand_kinds::source, luramas::il::lexer::operand_kinds::jmpaddr};
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_GETVARIADIC: {
                        result->kind = luramas::il::lexer::inst_kinds::expression;
                        result->operands = {luramas::il::lexer::operand_kinds::dest, luramas::il::lexer::operand_kinds::value};
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_REFCLOSURE: {
                        result->kind = luramas::il::lexer::inst_kinds::expression;
                        result->operands = {luramas::il::lexer::operand_kinds::dest, luramas::il::lexer::operand_kinds::kvalue};
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_INIT: {
                        result->kind = luramas::il::lexer::inst_kinds::expression;
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_BITCAST: {
                        result->kind = luramas::il::lexer::inst_kinds::expression;
                        result->operands = {luramas::il::lexer::operand_kinds::dest, luramas::il::lexer::operand_kinds::source, luramas::il::lexer::operand_kinds::value, luramas::il::lexer::operand_kinds::value, luramas::il::lexer::operand_kinds::boolean};
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_POPTOP: {
                        result->kind = luramas::il::lexer::inst_kinds::expression;
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_ADDUPVALUE: {
                        result->kind = luramas::il::lexer::inst_kinds::capture;
                        result->operands = {luramas::il::lexer::operand_kinds::upvalue_kind, luramas::il::lexer::operand_kinds::source};
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_CLOGIC_AND: {
                        result->kind = luramas::il::lexer::inst_kinds::expression;
                        result->operands = {luramas::il::lexer::operand_kinds::dest, luramas::il::lexer::operand_kinds::source, luramas::il::lexer::operand_kinds::source};
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_CLOGIC_OR: {
                        result->kind = luramas::il::lexer::inst_kinds::expression;
                        result->operands = {luramas::il::lexer::operand_kinds::dest, luramas::il::lexer::operand_kinds::source, luramas::il::lexer::operand_kinds::source};
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_PEND: {
                        result->kind = luramas::il::lexer::inst_kinds::expression;
                        result->operands = {luramas::il::lexer::operand_kinds::dest, luramas::il::lexer::operand_kinds::integer, luramas::il::lexer::operand_kinds::integer, luramas::il::lexer::operand_kinds::integer};
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_MARK: {
                        result->kind = luramas::il::lexer::inst_kinds::expression;
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_MOBJ_CAST: {
                        result->kind = luramas::il::lexer::inst_kinds::expression;
                        result->operands = {luramas::il::lexer::operand_kinds::dest, luramas::il::lexer::operand_kinds::source, luramas::il::lexer::operand_kinds::integer};
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_NCTOR_MOBJ: {
                        result->kind = luramas::il::lexer::inst_kinds::expression;
                        result->operands = {luramas::il::lexer::operand_kinds::dest, luramas::il::lexer::operand_kinds::source, luramas::il::lexer::operand_kinds::integer};
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_SCALL: {
                        result->kind = luramas::il::lexer::inst_kinds::expression;
                        result->operands = {luramas::il::lexer::operand_kinds::integer};
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_FLAGSET: {
                        result->kind = luramas::il::lexer::inst_kinds::expression;
                        result->operands = {luramas::il::lexer::operand_kinds::value, luramas::il::lexer::operand_kinds::reg};
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_FLAGREAD: {
                        result->kind = luramas::il::lexer::inst_kinds::expression;
                        result->operands = {luramas::il::lexer::operand_kinds::dest, luramas::il::lexer::operand_kinds::value};
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_CREATE_STACK: {
                        result->kind = luramas::il::lexer::inst_kinds::expression;
                        result->operands = {luramas::il::lexer::operand_kinds::dest};
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_PRETURN: {
                        result->kind = luramas::il::lexer::inst_kinds::expression;
                        result->operands = {luramas::il::lexer::operand_kinds::value, luramas::il::lexer::operand_kinds::reg, luramas::il::lexer::operand_kinds::value};
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_STARTPAGEFUNC: {
                        result->kind = luramas::il::lexer::inst_kinds::expression;
                        result->operands = {luramas::il::lexer::operand_kinds::value};
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_ENDPAGEFUNC: {
                        result->kind = luramas::il::lexer::inst_kinds::expression;
                        result->operands = {luramas::il::lexer::operand_kinds::value};
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_PCALL: {
                        result->kind = luramas::il::lexer::inst_kinds::expression;
                        result->operands = {luramas::il::lexer::operand_kinds::value, luramas::il::lexer::operand_kinds::reg, luramas::il::lexer::operand_kinds::value};
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_PJUMP: {
                        result->kind = luramas::il::lexer::inst_kinds::expression;
                        result->operands = {luramas::il::lexer::operand_kinds::value};
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_SEGREGATE: {
                        result->kind = luramas::il::lexer::inst_kinds::expression;
                        result->operands = {luramas::il::lexer::operand_kinds::value};
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_TAG_END:
                  case luramas::il::arch::opcodes::OP_COMBINE:
                  case luramas::il::arch::opcodes::OP_ENTRY_POINT: {
                        result->kind = luramas::il::lexer::inst_kinds::expression;
                        result->operands = {};
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_FLAGJUMP: {
                        result->kind = luramas::il::lexer::inst_kinds::expression;
                        result->operands = {luramas::il::lexer::operand_kinds::value, luramas::il::lexer::operand_kinds::value};
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_ICALL: {
                        result->kind = luramas::il::lexer::inst_kinds::expression;
                        result->operands = {luramas::il::lexer::operand_kinds::reg, luramas::il::lexer::operand_kinds::value};
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_TAG_START: {
                        result->kind = luramas::il::lexer::inst_kinds::expression;
                        result->operands = {luramas::il::lexer::operand_kinds::kvalue_embeded};
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_TAG_KV:
                  case luramas::il::arch::opcodes::OP_METADATA: {
                        result->kind = luramas::il::lexer::inst_kinds::expression;
                        result->operands = {luramas::il::lexer::operand_kinds::kvalue_embeded, luramas::il::lexer::operand_kinds::kvalue_embeded};
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_COMMAND: {
                        result->kind = luramas::il::lexer::inst_kinds::expression;
                        result->operands = {luramas::il::lexer::operand_kinds::kvalue_embeded, luramas::il::lexer::operand_kinds::value};
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_BITREAD: {
                        result->kind = luramas::il::lexer::inst_kinds::expression;
                        result->operands = {luramas::il::lexer::operand_kinds::dest, luramas::il::lexer::operand_kinds::source, luramas::il::lexer::operand_kinds::reg, luramas::il::lexer::operand_kinds::reg, luramas::il::lexer::operand_kinds::value, luramas::il::lexer::operand_kinds::boolean};
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_BITWRITE: {
                        result->kind = luramas::il::lexer::inst_kinds::expression;
                        result->operands = {luramas::il::lexer::operand_kinds::dest, luramas::il::lexer::operand_kinds::source, luramas::il::lexer::operand_kinds::source, luramas::il::lexer::operand_kinds::reg, luramas::il::lexer::operand_kinds::reg, luramas::il::lexer::operand_kinds::value, luramas::il::lexer::operand_kinds::boolean};
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_BITWRITEA: {
                        result->kind = luramas::il::lexer::inst_kinds::expression;
                        result->operands = {luramas::il::lexer::operand_kinds::dest, luramas::il::lexer::operand_kinds::source, luramas::il::lexer::operand_kinds::reg, luramas::il::lexer::operand_kinds::reg};
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_ANNOTATE_PREV: {
                        result->kind = luramas::il::lexer::inst_kinds::expression;
                        result->operands = {luramas::il::lexer::operand_kinds::kvalue_embeded};
                        break;
                  }
                  default: {
                        luramas::error::error("Unkown opcode when lexing.");
                  }
            }
            return result;
      }
} // namespace luramas::il::lexer