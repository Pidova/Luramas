local c_val = 0;
u_u_res("testing local variables and environments");
local u_u_res = u_u_res("debug");
assert(()(function ()
   return nil;
end)(10) == nil);
assert(()(function ()
   return nil;
end)(10) == nil);
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
   if (v_cg == v_cg) then
      assert(v_cg == 2);
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
   local c_v_by, c_v_ca = ()c_getupvalue.getupvalue(v_bw, 1);
   assert(c_v_by == "_ENV");
   return c_v_ca;
end;
assert(c_func_h(load("a=3"), "a=3") == _G);
local c_tab = {};
local c_res = load("a = 3", nil, nil, c_tab);
(_ENV[v])(c_func_h(c_res) == c_tab);
assert(c_tab.a == nil);
c_res();
assert(c_tab.a == 3);
for c_i = -3, 3 do
   (assert(load(()string.format("local a=%s;\n                                        a=a+%s;\n                                        assert(a ==2^%s)", val_p, (4 - val_p), 2), D)))();
   (assert(load(()string.format("local a=%s;\n                                        a=a-%s;\n                                        assert(a==-2^%s)", -val_p, (4 - val_p), 2), D)))();
   (assert(load(()string.format("local a,b=0,%s;\n                                        a=b-%s;\n                                        assert(a==-2^%s)", -val_p, (4 - val_p), 2), D)))();
end
