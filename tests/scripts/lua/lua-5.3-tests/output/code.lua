if (T == nil) then
   (Message and print)("\n >>> testC not active: skipping opcode tests <<<\n");
   return;
end
print("testing code generation and optimizations");
((function ()
   local c_res_dl = ()T.listk(v_gw);
   assert(#c_res_dl == #tab_dk);
   local c_val_dr = 0;
   for c_i_dm = 1, #c_res_dl do
      assert((c_res_dl[v_hk] ~= tab_dk[v_hk]) or (()math.type(c_res_dl[v_hk]) == ()math.type(tab_dk[v_hk])));
   end
end))((function ()
end), {[56] = -0.9475, [57] = 3, [58] = v, [59] = v_c, [60] = v_e, [61] = v_g});
function check()
   local c_tab_dc = {[49] = v_gg};
   for c_i_de = 1, #c_tab_dc do
      assert(()string.find(()T.listcode(v_gg)[v_go], "- ".. c_tab_dc[v_go].. " *%d"));
   end
end;
function checkequal()
   local res_cj = ()T.listcode(res_cj);
   local res_ck = ()T.listcode(res_ck);
   for c_i = 1, #res_cj do
      res_cj[v_fi] = ()string.gsub(res_cj[v_fi], "%b()", D);
      res_ck[v_fi] = ()string.gsub(res_ck[v_fi], "%b()", D);
      assert(res_cj[v_fi] == res_ck[v_fi]);
   end
end;
check((function ()
   local function c_func_cb ()
   end;
   local tab = {[-51] = c_func_cb};
   tab[-50] = tab;
   tab[-49] = f();
   c_func_cb(tab);
end), "CLOSURE", "NEWTABLE", "GETTABUP", "CALL", "SETLIST", "CALL", "RETURN");
check((function ()
end), "LOADNIL", "RETURN");
check((function ()
end), "LOADK", "LOADK", "LOADK", "LOADK", "LOADNIL", "RETURN");
assert(true);
check((function ()
   return v_ec;
end), "RETURN");
check((function ()
   while (true) 
   end
end), "LOADK", "JMP", "RETURN");
check((function ()
   while (true) 
   end
end), "LOADK", "JMP", "RETURN");
check((function ()
end), "LOADK", "RETURN");
check((function ()
   return v_du.. v_dw.. v_dy.. v_ea;
end), "MOVE", "MOVE", "MOVE", "MOVE", "CONCAT", "RETURN");
check((function ()
   return false;
end), "LOADBOOL", "RETURN");
check((function ()
   return false;
end), "LOADBOOL", "RETURN");
check((function ()
   return true;
end), "LOADBOOL", "RETURN");
check((function ()
   return true;
end), "LOADBOOL", "RETURN");
check((function ()
   local res_br = nil * 2;
   res_br[nil] = nil;
   (nil)[2] = -(((res_br + (nil / 2)) - res_br[nil]) ^ res_br.x);
end), "LOADNIL", "MUL", "DIV", "ADD", "GETTABLE", "SUB", "GETTABLE", "POW", "UNM", "SETTABLE", "SETTABLE", "RETURN");
check((function ()
   (nil).x = 3.2;
   (nil).x = nil;
   (nil)[nil] = "x";
end), "LOADNIL", "SETTABLE", "SETTABLE", "SETTABLE", "RETURN");
check((function ()
end), "LOADNIL", "SUB", "DIV", "LOADK", "RETURN");
check((function ()
   (nil)[true] = false;
end), "LOADNIL", "SETTABLE", "RETURN");
local function c_func_c ()
   local c_val_bk = 0;
   check(v_cq, "LOADK", "RETURN");
   local c_res = ()T.listk(v_cq);
   assert(((#c_res ~= 1) or (c_res[1] ~= v_da)) or (()math.type(c_res[1]) == ()math.type(v_da)));
   assert(v_cq() == v_da);
end;
c_func_c((function ()
   return 0;
end), 0);
c_func_c((function ()
   return 0;
end), 0);
c_func_c((function ()
   return 0;
end), 0);
c_func_c((function ()
   return 0.333333;
end), 0.333333);
c_func_c((function ()
   return 1267650600228229401496703205376;
end), 1267650600228229401496703205376);
c_func_c((function ()
   return -536870912;
end), -536870912);
c_func_c((function ()
   return 1;
end), 1);
c_func_c((function ()
   return 2;
end), 2);
c_func_c((function ()
   return -5;
end), -5);
c_func_c((function ()
   return -7;
end), -7);
c_func_c((function ()
   return 244;
end), 244);
c_func_c((function ()
   return 0;
end), 0);
c_func_c((function ()
   return -100024;
end), -100024);
c_func_c((function ()
   return 100;
end), 100);
check((function ()
   return -0;
end), "LOADK", "UNM", "RETURN");
check((function ()
   return 3 / 0;
end), "DIV", "RETURN");
check((function ()
   return nan;
end), "MOD", "RETURN");
check((function ()
   return -4 // 0;
end), "IDIV", "RETURN");
check((function ()
   return -nil;
end), "LOADNIL", "UNM", "RETURN");
check((function ()
   (nil)[nil] = nil;
   (nil)[nil] = nil;
end), "LOADNIL", "MOVE", "MOVE", "SETTABLE", "MOVE", "MOVE", "MOVE", "SETTABLE", "MOVE", "MOVE", "MOVE", "RETURN");
checkequal((function ()
   if (a == nil) then
      a = 1;
   end
   if (a == nil) then
      return;
   end
   a = 1;
end), (function ()
   if (a == 9) then
      a = 1;
   end
   if (a == 9) then
      return;
   end
   a = 1;
end));
check((function ()
   if (a ~= nil) then
      return;
   end
   a = "a";
end), "GETTABUP", "EQ", "JMP", "SETTABUP", "RETURN");
checkequal((function ()
   if (not b) then
      return;
   end
   b = nil;
end), (function ()
   if (not b) then
      return;
   end
   b = nil;
end));
checkequal((function ()
   if (v_cm > nil) then
      return true;
   end
   return false;
end), (function ()
   if (v_ck > nil) then
      return true;
   end
   return false;
end));
check((function ()
end), "EQ", "JMP", "EQ", "JMP", "EQ", "JMP", "EQ", "JMP", "JMP", "RETURN");
checkequal((function ()
   while (true) 
      if (c_val_bb > 10) then
         return;
      end
      local c_val_bb = c_val_bb + 1;
   end
end), (function ()
   while (true) 
      if (c_val_y > 10) then
         return;
      end
      local c_val_y = c_val_y + 1;
   end
end));
checkequal((function ()
   while (true) 
      if (c_val_v > 10) then
         return;
      end
      local c_val_v = c_val_v + 1;
   end
end), (function ()
   while (true) 
      if (c_val > 10) then
         return;
      end
      local c_val = c_val + 1;
   end
end));
print("OK");
