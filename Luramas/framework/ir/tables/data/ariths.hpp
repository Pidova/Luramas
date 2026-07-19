#pragma once
#include "../common/expr_parse.hpp"

namespace luramas::ir::tables::data::arith {

      static constexpr auto flags = parser::flags{
          .fglobal_wild = true};

      /*
         Some rules to follow to add more:
            Pairs are expr_parse_map(FLAGS, INPUT, RESULT)
            You can not use functions
            Everything must be in its simplest form
            You must use arithmetic, Bitwise operations
            They can compound so no redudant rules like: "x + 0 + 0" when you have "(x + 0)"
            Variables can have any bit size, float, and any signess so must be 100% safe
            You can only have bitwise operations in the result if the input has bitwise operations example:
                If input is x * 2 you can not have bitwise in the result 
                If input is ~~x you can have bitwise in the result
            Because it is compound the smallest result should be considered
            YOU SHOULD NEVER ADD ANOTHER ENTRY AS KEY WITH ANOTHER RESULT THAT EXISTS IT WILL FAIL
      */
      static const auto table = std::to_array<expr_parse_map>({

          expr_parse_map(flags, "x&0", "0"),
          expr_parse_map(flags, "0&x", "0"),
          expr_parse_map(flags, "x|0", "x"),
          expr_parse_map(flags, "x^0", "x"),
          expr_parse_map(flags, "x&x", "x"),
          expr_parse_map(flags, "x|x", "x"),
          expr_parse_map(flags, "x^x", "0"),
          expr_parse_map(flags, "~(~x)", "x"),
          expr_parse_map(flags, "-(-x)", "x"),
          expr_parse_map(flags, "x|(-1)", "-1"),
          expr_parse_map(flags, "x&(-1)", "x"),
          expr_parse_map(flags, "(2*x)|y", "x+y"),
          expr_parse_map(flags, "(x&y)+(x|y)", "x+y"),
          expr_parse_map(flags, "(x^y)-(2*((~x)&y))", "x-y"),
          expr_parse_map(flags, "(x+y)-(x&y)", "x|y"),
          expr_parse_map(flags, "(x&y)+(x^y)", "x|y"),
          expr_parse_map(flags, "(x+y)-(x|y)", "x&y"),
          expr_parse_map(flags, "(x|y)-(x^y)", "x&y"),
          expr_parse_map(flags, "(x+y)-(2*(x&y))", "x^y"),
          expr_parse_map(flags, "((x+y)-((x&y)<<1))", "x^y"),
          expr_parse_map(flags, "x+(x+y)", "(2*x)+y"),
          expr_parse_map(flags, "(~x)&(~y)", "~(x|y)"),
          expr_parse_map(flags, "(~x)|(~y)", "~(x&y)"),
          expr_parse_map(flags, "(x|y)&(~(x&y))", "x^y"),
          expr_parse_map(flags, "(x|y)-(x&y)", "x^y"),
          expr_parse_map(flags, "(x&y)|(~(x|y))", "~(x^y)"),
          expr_parse_map(flags, "(x+y)+y", "(x+2)*y"),
          expr_parse_map(flags, "y+(x+y)", "(x+2)*y"),
          expr_parse_map(flags, "(x+y)+x", "(2*x)+y"),
          expr_parse_map(flags, "(2*x)+(2*y)", "2*(x+y)"),
          expr_parse_map(flags, "x|(x&1)", "x|1"),
          expr_parse_map(flags, "((x|y)&(~x))&y", "0"),
          expr_parse_map(flags, "x^(x&y)", "x&(~y)"),
          expr_parse_map(flags, "x^(x|y)", "(~x)&y"),
          expr_parse_map(flags, "(x|y)&(x|(~y))", "x"),
          expr_parse_map(flags, "(x&y)|(x&(~y))", "x"),
          expr_parse_map(flags, "(x+1)|((~x)-1)", "-1"),
          expr_parse_map(flags, "~(x+y)", "~(x|y)"),
          expr_parse_map(flags, "x|(~x)", "-1"),
          expr_parse_map(flags, "x&(~x)", "0"),
          expr_parse_map(flags, "x&(-x)", "x&((~x)+1)"),
          expr_parse_map(flags, "x|(x+1)", "(-1)-(~x)"),
          expr_parse_map(flags, "x^(-1)", "(~x)"),
          expr_parse_map(flags, "x+((y^x)&(z^x))", "y^(z^x)"),
          expr_parse_map(flags, "(x^y)^(y^z)", "x^z"),
          expr_parse_map(flags, "(x|y)&((~x)|z)", "(x&z)|y"),
          expr_parse_map(flags, "x+(y&(~x))", "x^y"),
          expr_parse_map(flags, "(y&(~x))+x", "x^y"),
          expr_parse_map(flags, "(x&1)==0", "(~x)&1"),
          expr_parse_map(flags, "(x&n)&n", "x&n"),
          expr_parse_map(flags, "(-(x+y))-1", "~(x|y)"),
          expr_parse_map(flags, "(x==n)&1", "x==n"),
          expr_parse_map(flags, "(x!=n)&1", "x!=n"),
          expr_parse_map(flags, "(x<n)&1", "x<n"),
          expr_parse_map(flags, "(x<=n)&1", "x<=n"),
          expr_parse_map(flags, "(x>n)&1", "x>n"),
          expr_parse_map(flags, "(x>=n)&1", "x>=n"),
          expr_parse_map(flags, "((x*y)+(y*x))", "2*(x*y)"),
          expr_parse_map(flags, "x+x", "2*x"),
          expr_parse_map(flags, "x+((y+x)+w)", "((x*2)+y)+w"),
          expr_parse_map(flags, "x+((x+y)+w)", "((x*2)+y)+w"),
          expr_parse_map(flags, "x+(x*y)", "x*(y+1)"),
          expr_parse_map(flags, "x+(y*x)", "x*(y+1)"),
          expr_parse_map(flags, "(x*y)+x", "x*(y+1)"),
          expr_parse_map(flags, "(y*x)+x", "x*(y+1)"),
          expr_parse_map(flags, "(x*y)+(z*x)", "x*(y+z)"),
          expr_parse_map(flags, "(y*x)+(x*z)", "x*(y+z)"),
          expr_parse_map(flags, "x+(y+(x*w))", "y+(x*(w+1))"),
          expr_parse_map(flags, "(x*y)+((~x)*y)", "-y"),
          expr_parse_map(flags, "(x|(~y))&((-x)|y)", "x"),
          expr_parse_map(flags, "(~(x))+1", "-x"),
          expr_parse_map(flags, "((x*y)+((~x)*(-y)))", "((2*x)+1)*y"),
      });

      /* Replaces target with member match */
      std::shared_ptr<ir_stat::ir_expr> replace(const std::shared_ptr<ir_stat::ir_expr> &target, const expr_parse_map &member);
} // namespace luramas::ir::tables::data::arith