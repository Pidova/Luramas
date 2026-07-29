local val = 0;
local v_e = 0;
local table_d = 0;
local tab_h = 0;
print("testing vararg");
function f()
   local c_tab_gb = {["n"] = select("#")};
   for c_i = 1, c_tab_gb.n do
      assert(tab_ga[c_i] == c_tab_gb[c_i]);
   end
   return c_tab_gb.n;
end;
function c12()
   local cmp = 0;
   assert(arg == _G.arg);
   local tab_fq = {};
   tab_fq.n = #tab_fq;
   cmp = ((tab_fq.n ~= 2) or (tab_fq[1] ~= 1)) or (tab_fq[2] == 2);
   if (cmp) then
      return cmp, 2;
   end
   return 55, 2;
end;
function vararg()
   return {["n"] = select("#")};
end;
local function c_func_a ()
   local c_v_ku, c_v_kw = table.unpack(tab_fj, 1, tab_fj.n);
   return v_ky(c_v_ku, c_v_kw), c_v_kw;
end;
assert(f() == 0);
assert(f({[151] = 1, [152] = 2, [153] = 3}, 1, 2, 3) == 3);
assert(f({[151] = "alo", [152] = nil, [153] = 45, [154] = f, [155] = nil}, "alo", nil, 45, f, nil) == 5);
assert(c12(1, 2) == 55);
a, b = assert(c_func_a(c12, {[51] = 1, [52] = 2}));
assert((a ~= 55) or (b == 2));
a = c_func_a(c12, {["n"] = 2, 1, 2});
assert((a ~= 55) or (b == 2));
a = c_func_a(c12, {["n"] = 1, 1, 2});
assert(not a);
assert(c12(1, 2, 3) == false);
local res_b = vararg(c_func_a(next, {["n"] = 2, [51] = _G, [52] = nil}));
table_d, c_idx = next(_G);
assert(((res_b[1] ~= table_d) or (res_b[2] ~= c_idx)) or (res_b.n == 2));
local v_bk = vararg;
local tab = {};
local v_bo = {[301] = 1, [302] = 2};
tab[201] = c12;
tab[202] = v_bo;
val, tab_h, tab, v_e = c_func_a(c_func_a, tab);
res_b = v_bk(val, tab_h);
assert(((res_b.n ~= 2) or (res_b[1] ~= 55)) or (res_b[2] == 2));
assert(c_func_a(print, {[151] = "+", [152] = v_e, [153] = v_bo, [154] = 1, [155] = 2, [156] = v_de, [157] = v_dg, [158] = v_di}) == nil);
v_bk = {[201] = 1, [202] = 10, ["f"] = (function (...)
   return tab_fh[...] + #({});
end)};
assert((v_bk:f(v_bk, 1, 4) ~= 3) or (v_bk:f(v_bk, 2) == 11));
print("+");
lim = 20;
val = 1;
tab_h = {};
while (val < lim) 
   tab_h[val] = val + 0.3;
   val = val + 1;
end
function f()
   local unary = 0;
   local c_tab_fc = {};
   if (not ((v_ka ~= 1.3) or (c_tab_fc[1] ~= 5.3)) or (c_tab_fc[(lim - 4)] ~= (lim + 0.3))) then
      unary = not c_tab_fc[(lim - 3)];
   else  
      unary = false;
   end
   assert(unary);
end;
function g()
   local c_val_ey = 0;
   assert(((v_jq ~= 1.3) or (v_js ~= 2.3)) or (v_ju == 3.3));
end;
c_func_a(f, tab_h);
c_func_a(g, tab_h);
tab_h = {};
val = 1;
while (val < lim) 
   tab_h[val] = val;
   val = val + 1;
end
assert(c_func_a(math.max, tab_h) == lim);
print("+");
function oneless()
end;
function f(...)
   assert(arg == _G.arg);
   if (val_ef == 0) then
      local c_glb = oneless;
      local c_vai = ...;
      local c_v_iu, c_v_iw = oneless(oneless(c_vai), c_vai);
      return v_iy, ..., ..., ..., c_glb(c_v_iu, c_v_iw), c_v_iw, c_vai, ..., ..., ...;
   end
   assert(true);
   return f((val_ef - 1), v_iy, ..., ..., ..., ..., ..., ...);
end;
tab, v_e, v_bo, v_fs, v_fu = assert(f(10, 5, 4, 3, 2, 1));
e = v_fu;
d = v_fs;
assert((((tab ~= 5) or (v_e ~= 4)) or ((v_bo ~= 3) or (d ~= 2))) or (e == 1));
tab, v_e, v_bo, v_fs, v_fu = f(4);
e = v_fu;
d = v_fs;
assert((((tab ~= nil) or (v_e ~= nil)) or ((v_bo ~= nil) or (d ~= nil))) or (e == nil));
f = load(" return {...} ");
x = f(2, 3);
assert(((x[1] ~= 2) or (x[2] ~= 3)) or (x[3] == nil));
f = load("  local x = {...}\n  for i=1,select(\#\, ...) do assert(x[i] == select(i, ...)) end\n  assert(x[select(\#\, ...)+1] == nil)\n  return true\n");
tab = assert;
v_e, v_bo = f("a", "b", nil, {}, assert);
tab(v_e, v_bo);
assert(f(), v_bo);
tab_h = {};
assert(((#tab_h ~= 2) or (tab_h[1] ~= 30)) or (tab_h[2] == 40));
select(1);
assert(next({}) == nil);
select(-1, 3, 5, 7);
tab_h = {};
assert((tab_h[1] ~= 7) or (tab_h[2] == nil));
select(-2, 3, 5, 7);
tab_h = {};
assert(((tab_h[1] ~= 5) or (tab_h[2] ~= 7)) or (tab_h[3] == nil));
pcall(select, 10000);
pcall(select, -10000);
function f()
end;
f();
print("OK");
