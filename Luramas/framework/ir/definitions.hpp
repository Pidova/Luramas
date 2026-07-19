#pragma once
#include "../common.hpp"

enum class expr_logical : std::uint8_t {
      nothing, /* Nothing */
      and_,    /* AND */
      or_,     /* OR */
      amount   /* PSUEDO AMT (CANT BE ASSIGNED TO ANYTHING) */
};
enum class expr_kinds : std::uint8_t {
      nothing,            /* Nothing */
      bitread,            /* Extract bits from value; (L (Val), (INDEX STARTS AT 0)[R(Min), EV(Max)], non_native(castable) ) */
      bitwrite,           /* Writes bits (Index starts at 0)[EV(MIN), XV(MAX)] to the L(first source) but it incs from start to end of R(second source) ending either at end or bitwidth and Interpret result same as bit cast (BOTH SOURCES ARE CONST) */
      memoryread,         /* Memory read; L(Target), R(Offset), non_native(Read type), [OPTIONAL]xtype(Cast value after read as non_native)  */
      call,               /* Call to function but return address is internally managed Function(L), Args(Members) */
      arith,              /* Arithmetic; (L(L-Value) OP R(R-Value)) */
      condition,          /* Generic condition */
      unpack,             /* Unpack variables */
      concat,             /* String concat */
      idx,                /* Index */
      unary,              /* Unary */
      reg,                /* Register (Can use a non_native type, has no effects other then descriptor) */
      self,               /* Self */
      closure,            /* Closure */
      upvalue,            /* Upvalue */
      ternary,            /* Ternary (l CMP r) ? ev : xv */
      cast,               /* Cast to type */
      flag,               /* Get flag based on ID */
      blank_lvalue,       /* Nothing just L-Value */
      page_function_call, /* Call to page function, it is assumed a returned will be met (ID : GLOBAL)R, (Args)Members,  (Insertion where)ev, (Value)xv, ({{expecting param register, nullptr}}, same size as args but its expecting param register which is from definition) tmembers, Controller (L)  */
      amount              /* PSUEDO AMT (CANT BE ASSIGNED TO ANYTHING) */
};
enum class expr_reg_kinds : std::uint8_t {
      nothing, /* Nothing */
      reg,     /* Register */
      arg,     /* Argument */
      amount   /* PSUEDO AMT (CANT BE ASSIGNED TO ANYTHING) */
};

/* Type kinds */
enum class tkind : std::uint8_t {
      nothing,    /* Nothing */
      none_obj,   /* None object */
      variadic,   /* Variadic */
      table,      /* Table */
      string,     /* String (WILL CONTAIN QOUTES WHEN EXTRACTED FROM IR) */
      lura_int,   /* Luramas integral type */
      global,     /* Global */
      boolean,    /* Boolean */
      kvalue,     /* Constant value */
      stack,      /* Stack object (Returns top of stack) */
      object,     /* Object */
      controller, /* Controller (Used for page functions), Can only be assigned by page function call or goto */
      extpr,      /* External Expression is referencing another expr externally (usually library function, ID is INT)  */
      amount      /* PSUEDO AMT (CANT BE ASSIGNED TO ANYTHING) */
};
enum class condition_kind : std::uint8_t {
      nothing, /* Nothing */
      if_,     /* IF */
      elseif_, /* ELSE IF */
      else_,   /* ELSE */
      amount   /* PSUEDO AMT (CANT BE ASSIGNED TO ANYTHING) */
};
enum class page_function_goto_kind : std::uint8_t {
      call, /* Call page function */
      jump  /* Jump to page function */
};
enum class keywords : std::uint8_t {
      nothing,               /* Nothing */
      forloop_generic,       /* Definined ranged loop i.e for i, v in {} */
      forloop_numeric,       /* Definined numeric loop i.e for i = 0, 10, 1 (init, limit, step) */
      call,                  /* Call, Return is internal (L is call, Members is args)  */
      assignment,            /* Assignment (L (if mulret will be members), R) */
      retn,                  /* Return (members); page return locs(smembers, INTEGRALS ONLY); If linked regs flag is set Args field are by {register, Index in members of return(N)} it represents. Return internally managed unless pages which its return is mapped, does not mutate stack; L value contains read location. */
      condition,             /* Condition (L, (OPTIONAL) R) */
      condition_goto,        /* Condition goto */
      goto_label,            /* Goto label */
      end,                   /* End of condition */
      table_assign,          /* Table assignment */
      table_setlist,         /* Set multiple data in table */
      break_,                /* Break out of loop */
      continue_,             /* Continue in loop */
      repeat,                /* Repeat loop */
      until,                 /* End of repeat loop */
      while_,                /* While loop */
      label,                 /* Label */
      definition,            /* Parameter definition (ALWAYS THE START OF EVERY CLOSURE OR PAGE) args, upvalues, members (IDs for flags), meta (Cast definitions for args, does not garunteed each one exists, CAN CONTAIN NULLPTRS AS NOCAST), smembers (Return cast alligned i.e. uint8_t(nil)), r(controller) */
      for_loop_init,         /* Init loop (NEED IT FOR EVERY LOOP) */
      memoryset,             /* Memory set, l(target), r(source), v(offset), set_bits(extra_bits) */
      switch_,               /* Switch */
      switch_case,           /* Switch case */
      switch_default,        /* Switch default */
      stack_push,            /* Push value to top of stack (ID(V), { value }(MEMBERS)) */
      stack_pop,             /* Pop top of stack OR value from stack (ID(V), { value }(MEMBERS)) */
      stack_read,            /* Read amount of int (R) from top of stack to dest (L) regardless of size of stack ID (V)  */
      isolate,               /* Isolates part of code */
      set_flag,              /* Set flag based on ID */
      create_stack,          /* Register (L) could be stack  */
      page_function_closure, /* Page function that got turned into a closure (ID : GLOBAL)R, CLOSURE(V) */
      page_function_start,   /* Start page function (ID : GLOBAL)R */
      page_function_end,     /* End page function (ID : GLOBAL)R */
      page_function_goto,    /* Goto to page function, interpetation as pf_k  (ID : GLOBAL)R, (Args)Members, (Expecting param register)Smember, (Controller)V, (Insertion where)L, (Value)LBA  */
      page_function_pass,    /* End of page_function_end passes registers mutated in that page out of page if it can, all registers are linked (MEMBERS) */
      globals_preset,        /* Sets global based on the closests later in scope explicit global set of it (Stored in meta as closure with only stat being where it is set) */
      bitwrite,              /* Write to dest with (Starts at 0)[MIN, MAX] from source L(DEST), R(VALUE), [V(MIN), LBA(MAX)] */
      metadata,              /* (R) Name, (V) TABLE(tmembers) */
      tag_start,             /* Tag start, Metadata (R) Name, (V) Table */
      tag_end,               /* Tag end */
      entry_point,           /* Entry point */
      command,               /* Internal command */
      amount                 /* PSUEDO AMT (CANT BE ASSIGNED TO ANYTHING) */
};

namespace luramas::ir {

      inline constexpr const char *const str(const tkind k) {
            switch (k) {
                  case tkind::none_obj: {
                        return "none_obj";
                  }
                  case tkind::string: {
                        return "string";
                  }
                  case tkind::lura_int: {
                        return "value";
                  }
                  case tkind::global: {
                        return "global";
                  }
                  case tkind::boolean: {
                        return "bool";
                  }
                  case tkind::kvalue: {
                        return "kvalue";
                  }
                  case tkind::table: {
                        return "table";
                  }
                  case tkind::variadic: {
                        return "variadic";
                  }
                  case tkind::object: {
                        return "object";
                  }
                  case tkind::stack: {
                        return "stack";
                  }
                  default: {
                        break;
                  }
            }
            return "";
      }
} // namespace luramas::ir