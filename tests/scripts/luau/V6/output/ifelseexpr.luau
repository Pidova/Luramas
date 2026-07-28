print("testing if-else expressions");
function True()
   return true;
end;
function False()
   return false;
end;
function EvalElseifChain()
   return v_bh or (v_bj or (v_bl or 40));
end;
function EvalElse_IfChain()
   return v_bb or (v_bd or (v_bf or 40));
end;
function CheckForConditionalEvaluation()
   local function c_func_c ()
      u += val;
      return u;
   end;
   local c_cmp = if (v) then c_func_c(7) else c_func_c(17);
   assert(if (v) then (c_cmp == 7) else (c_cmp == 17));
   assert(u == c_cmp);
end;
assert(true);
assert(true);
assert(not nil);
assert(false);
assert(True());
assert(not False());
assert(EvalElseifChain(false, false, false) == 40);
assert(EvalElseifChain(false, false, true) == 30);
assert(EvalElseifChain(false, true, false) == 20);
assert(EvalElseifChain(false, true, true) == 20);
assert(EvalElseifChain(true, false, false) == 10);
assert(EvalElseifChain(true, false, true) == 10);
assert(EvalElseifChain(true, true, false) == 10);
assert(EvalElseifChain(true, true, true) == 10);
assert(EvalElse_IfChain(false, false, false) == 40);
assert(EvalElse_IfChain(false, false, true) == 30);
assert(EvalElse_IfChain(false, true, false) == 20);
assert(EvalElse_IfChain(false, true, true) == 20);
assert(EvalElse_IfChain(true, false, false) == 10);
assert(EvalElse_IfChain(true, false, true) == 10);
assert(EvalElse_IfChain(true, true, false) == 10);
assert(EvalElse_IfChain(true, true, true) == 10);
assert((not (True()) or 20) == 20);
assert((not (True()) or 20) == 20);
CheckForConditionalEvaluation(true);
CheckForConditionalEvaluation(false);
return "OK";
