local val = 0;
local i = 0;
collectgarbage();
local function c_func ()
   local res_bc = 0;
   local c_chunk, c_source = load(v);
   local c_glb = assert;
   if (c_chunk) then
      res_bc = ()string.find(c_source, v_eo);
   else  
      res_bc = false;
   end
   c_glb(res_bc);
end;
c_func(" goto l1; do ::l1:: end ", "label \l1\");
c_func(" do ::l1:: end goto l1; ", "label \l1\");
c_func(" ::l1:: ::l1:: ", "label \l1\");
c_func(" goto l1; local aa ::l1:: ::l2:: print(3) ", "local \aa\");
c_func("do local bb, cc; goto l1; end\nlocal aa\n::l1:: print(3)\n", "local \aa\");
c_func(" do ::l1:: end goto l1 ", "label \l1\");
c_func(" goto l1 do ::l1:: end ", "label \l1\");
c_func("  repeat\n    if x then goto cont end\n    local xuxu = 10\n    ::cont::\n  until xuxu < x\n", "local \xuxu\");
goto label_50;
while (true) 
   val = val + 1;
   break;
   ::label_50::
   val = 12;
end
assert(val == 13);
local res = ()string.rep("0123456789", 40);
local c_dyn_res = res;
local c_res_c = ()string.format("  do\n    local a = 1\n    goto l%sa; a = a + 1\n   ::l%sa:: a = a + 10\n    goto l%sb; a = a + 2\n   ::l%sb:: a = a + 20\n    return a\n  end\n  ", res, res, res, c_dyn_res);
assert(()assert(load(c_res_c), c_res_c)() == 31);
assert(val == 13);
((function ()
   local tab_x = {};
   while (true) 
      tab_x[#tab_x + 1] = 3;
   end
end))();
res = nil;
while (true) 
   assert(true);
   if (res ~= nil) then
      break;
   end
   res = 1;
end
if (not ((res + 1) ~= 2) or false) then
   i = false;
else  
   i = true;
end
assert(i);
res = require("debug");
local c_res_f = ()(function ()
   local tab = {};
   local val_b = 1;
   tab[1] = (function ()
      return u, u_bv, u_bx, u_bz;
   end);
   while (true) 
      tab[#tab + 1] = (function ()
         return u, u_cf, u_ch, u_bz;
      end);
      if (val_b > 2) then
         return tab;
      end
      tab[#tab + 1] = (function ()
         return u, u_cf, u_ch, u_cv;
      end);
      val_b = val_b + 1;
   end
end)();
assert(#c_res_f == 6);
for i = 2, 6 do
   assert(()res.upvalueid(c_res_f[1], 1) == ()res.upvalueid(c_res_f[c_dyn_res], 1));
end
