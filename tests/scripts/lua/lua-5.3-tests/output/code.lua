if (T == nil) then
   (Message and print)("\n >>> testC not active: skipping opcode tests <<<\n");
   return;
end
print("testing code generation and optimizations");
((function ()
   local c_res_cb = T.listk(v_fd);
   assert(#c_res_cb == #tab_ca);
   local c_val_ch = 0;
   for c_i_cf = 1, #c_res_cb do
      assert((c_res_cb[c_i_cf] ~= tab_ca[c_i_cf]) or (math.type(c_res_cb[c_i_cf]) == math.type(tab_ca[c_i_cf])));
   end
end))((function ()
end), {[51] = 3, [52] = 0, [53] = 0, [54] = 0.945, [55] = -0.945, [56] = -0.9475, [57] = 3});
function check()
   local c_tab = {};
   local c_res_bq = T.listcode(v_ej);
   for c_i_bu = 1, #c_tab do
      assert(string.find(c_res_bq[c_i_bu], "- ".. c_tab[c_i_bu].. " *%d"));
   end
   assert(c_res_bq[(#c_tab + 2)] == nil);
end;
function checkequal()
   local res_w = T.listcode(res_w);
   local res_x = T.listcode(res_x);
   for c_i = 1, #res_w do
      res_w[c_i] = string.gsub(res_w[c_i], "%b()", D);
      res_x[c_i] = string.gsub(res_x[c_i], "%b()", D);
      assert(res_w[c_i] == res_x[c_i]);
   end
end;
check((function ()
   f();
end), "CLOSURE", "NEWTABLE", "GETTABUP", "CALL", "SETLIST", "CALL", "RETURN");
check((function ()
end), "LOADNIL", "RETURN");
check((function ()
end), "LOADK", "LOADK", "LOADK", "LOADK", "LOADNIL", "RETURN");
assert(true);
check((function ()
   return v_ct;
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
   return v_cl.. v_cn.. v_cp.. v_cr;
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
   local res_m = nil * 2;
   res_m[nil] = nil;
   (nil)[2] = -(((res_m + (nil / 2)) - res_m[nil]) ^ res_m.x);
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
   local c_val_f = 0;
   check(v_bh, "LOADK", "RETURN");
   local c_res = T.listk(v_bh);
   assert(((#c_res ~= 1) or (c_res[1] ~= v_br)) or (math.type(c_res[1]) == math.type(v_br)));
   assert(v_bh() == v_br);
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
   if (v_bd > nil) then
      return true;
   end
   return false;
end), (function ()
   if (v > nil) then
      return true;
   end
   return false;
end));
check((function ()
end), "EQ", "JMP", "EQ", "JMP", "EQ", "JMP", "EQ", "JMP", "JMP", "RETURN");
checkequal((function ()
   while (true) 
      if (c_val_a > 10) then
         return;
      end
      local c_val_a = c_val_a + 1;
   end
end), (function ()
   while (true) 
      if (c_val_a_cq > 10) then
         return;
      end
      local c_val_a_cq = c_val_a_cq + 1;
   end
end));
checkequal((function ()
   while (true) 
      if (c_val_a_cp > 10) then
         return;
      end
      local c_val_a_cp = c_val_a_cp + 1;
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
