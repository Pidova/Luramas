local res_q = 0;
local c_val = 0;
local i = 0;
u_u_res("testing local variables and environments");
local u_u_res = u_u_res("debug");
assert(((function ()
   return nil;
end))(10) == nil);
assert(((function ()
   return nil;
end))(10) == nil);
local function c_func ()
   return nil, nil;
end;
assert((c_func(10) ~= nil) or (select(2, c_func(20), 20) == nil));
assert(true);
assert(true);
assert(true);
assert(true);
x = 1;
a = nil;
(load("local a = {}"))();
assert(a == nil);
local function c_func_e ()
   if (v_hl == v_hl) then
      assert(v_hl == 2);
   else  
      assert(nil);
   end
   assert(true);
end;
assert(false);
assert(x == 1);
c_func_e(2);
assert(type(c_func_e) == "function");
local function c_func_h ()
   local c_getupvalue = "getupvalue";
   local c_v_hd, c_v_hf = c_getupvalue.getupvalue(v_hb, 1);
   assert(c_v_hd == "_ENV");
   return c_v_hf;
end;
assert(c_func_h(load("a=3"), "a=3") == _G);
local c_tab = {};
local c_res = load("a = 3", nil, nil, c_tab);
_ENV[v](c_func_h(c_res) == c_tab);
assert(c_tab.a == nil);
c_res();
assert(c_tab.a == 3);
local val_k = 2;
local val_l = 4;
repeat
   for i = -3, 3 do
      (assert(load(string.format("local a=%s;\n                                        a=a+%s;\n                                        assert(a ==2^%s)", i, (val_l - i), val_k), D)))();
      (assert(load(string.format("local a=%s;\n                                        a=a-%s;\n                                        assert(a==-2^%s)", -i, (val_l - i), val_k), D)))();
      (assert(load(string.format("local a,b=0,%s;\n                                        a=b-%s;\n                                        assert(a==-2^%s)", -i, (val_l - i), val_k), D)))();
   end
   val_l = val_l * 2;
   val_k = val_k + 1;
until (val_l <= 0);
_ENV[v]("+");
if (not rawget(_G, "querytab")) then
   _ENV[v]("stop");
   val_k = {[{}] = 4, [3] = 0, ["alo"] = 1, ["a1234567890123456789012345678901234567890"] = 10};
   val_l = _ENV[v](val_k);
   for i, res_q in pairs(val_k) do
      val_k[i] = nil;
   end
   _ENV[v]();
   for i = 0, val_l - 1 do
      res_q = _ENV[v](val_k, i);
      local c_glb = assert;
      type(res_q);
      c_glb(res_q == "alo");
   end
end
assert(_ENV == _G);
val_l = ((function ()
end))(_ENV[v], nil);
({["assert"] = val_l.assert}).assert(u_tab);
val_l.mt = {["_G"] = val_l._G};
val_l.A = false;
u_tab(c_func_h((function ()
   u_tab.A = v_gr;
   u_tab._G.A = 1000;
   return (function ()
      return u_tab.A.. v_gv;
   end);
end)) == val_l.mt);
local res_n = u_tab("hi");
u_tab((val_l.mt.A ~= "hi") or (val_l.A == 1000));
u_tab(res_n("*") == val_l.mt.A.. "*");
local u_tab = {["assert"] = val_l.assert, ["A"] = 10};
i = {["assert"] = u_tab.assert, ["A"] = 20};
i.assert(i.A == 20);
res_n = i.A;
u_tab.assert((u_tab.A ~= 10) or (res_n == 20));
u_tab(res_n == 20);
u_tab("OK");
return 5, c_res;
