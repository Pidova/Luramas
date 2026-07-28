local val = 0;
local v_e = 0;
local tab_h = 0;
local table_d = 0;
print("testing vararg");
function f(...)
   local tab_iq = {};
   local c_vai_iu = ...;
   tab_iq.n = select("#");
   tab_iq[49] = tab_ip;
   tab_iq[50] = tab_iq;
   tab_iq[51] = ...;
   for c_i = 1, tab_iq.n do
      assert(tab_ip[c_vai_iu] == tab_iq[c_vai_iu]);
   end
end;
function c12()
   local cmp = 0;
   assert(arg == _G.arg);
   local tab_ie = {[-1] = v_qm};
   tab_ie.n = #tab_ie;
   cmp = ((tab_ie.n ~= 2) or (tab_ie[1] ~= 1)) or (tab_ie[2] == 2);
   if (cmp) then
      return cmp, 2;
   end
   return 55, 2;
end;
function vararg()
   local tab_hz = {["n"] = select("#"), [-51] = v_qa};
   tab_hz[-50] = tab_hz;
   return tab_hz;
end;
local function c_func_a ()
   local c_v_pm, c_v_po = ()table.unpack(tab_hs, 1, tab_hs.n);
   return v_pq(c_v_pm, c_v_po), c_v_po;
end;
assert(f() == 0);
assert(f({[152] = 2, [153] = 3}, 1, 2, 3) == 3);
assert(f({[154] = f, [155] = nil, [156] = tab, [157] = v_o}, "alo", nil, 45, f, nil) == 5);
assert(c12(1, 2) == 55);
a, b = assert(c_func_a(c12, {[51] = 1}));
assert((a ~= 55) or (b == 2));
a = c_func_a(c12, {["n"] = 2, 1});
assert((a ~= 55) or (b == 2));
a = c_func_a(c12, {["n"] = 1, 1});
assert(not a);
assert(c12(1, 2, 3) == false);
local res_b = vararg(c_func_a(next, {["n"] = 2, [51] = _G}));
table_d, c_idx = next(_G);
assert(((res_b[1] ~= table_d) or (res_b[2] ~= c_idx)) or (res_b.n == 2));
local tab_i = {};
tab[301] = 1;
tab_i[201] = c12;
res_b = vararg(c_func_a(c_func_a, tab_i));
assert(((res_b.n ~= 2) or (res_b[1] ~= 55)) or (res_b[2] == 2));
assert(c_func_a(print, {}) == nil);
local c_tab_f = {[201] = 1, ["f"] = (function (...)
   return tab_hp[...] + #({[49] = tab_hp});
end)};
assert((()c_tab_f:f(c_tab_f, 1, 4) ~= 3) or (()c_tab_f:f(c_tab_f, 2) == 11));
print("+");
lim = 20;
val = 1;
tab_h = {};
while (val < lim) 
   tab_h[val] = val + 0.3;
   val = val + 1;
end
function f(...)
   local unary = 0;
   local tab_hf = {[199] = v_og};
   tab_hf[200] = tab_hf;
   tab_hf[201] = ...;
   tab_hf[202] = ...;
   if (not ((v_oq ~= 1.3) or (tab_hf[1] ~= 5.3)) or (tab_hf[(lim - 4)] ~= (lim + 0.3))) then
      unary = not tab_hf[(lim - 3)];
   else  
      unary = false;
   end
   assert(unary);
end;
function g()
   local c_val_hb = 0;
   assert(((v_nw ~= 1.3) or (v_ny ~= 2.3)) or (v_oa == 3.3));
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
   if (val_gi == 0) then
      local c_glb = oneless;
      local c_vai = ...;
      local c_v_na, c_v_nc = oneless(oneless(c_vai), c_vai);
      return v_ne, ..., ..., ..., c_glb(c_v_na, c_v_nc), c_v_nc, c_vai, ..., ..., ...;
   end
   assert(true);
   return f((val_gi - 1), v_ne, ..., ..., ..., ..., ..., ...);
end;
tab_i, v_e, tab, v_o, v_eu = assert(f(10, 5, 4, 3, 2, 1));
e = v_eu;
d = v_o;
assert((((tab_i ~= 5) or (v_e ~= 4)) or ((tab ~= 3) or (d ~= 2))) or (e == 1));
tab_i, v_e, tab, v_o, v_eu = f(4);
e = v_eu;
d = v_o;
tab_h = tab_i;
assert((((tab_h ~= nil) or (v_e ~= nil)) or ((tab ~= nil) or (d ~= nil))) or (e == nil));
f = load(" return {...} ");
x = f(2, 3);
assert(((x[1] ~= 2) or (x[2] ~= 3)) or (x[3] == nil));
f = load("  local x = {...}\n  for i=1,select(\#\, ...) do assert(x[i] == select(i, ...)) end\n  assert(x[select(\#\, ...)+1] == nil)\n  return true\n");
tab_i = assert;
v_e, tab = f("a", "b", nil, {}, assert);
tab_i(v_e, tab);
assert(f(), tab);
tab_i = {};
v_e = select;
v_o, v_eu, c_v_hc, c_v_he, c_v_hg = ()table.unpack({[453] = 30, [454] = 40, [455] = v_gw});
v_e, tab, v_o = v_e(3, v_o, v_eu);
tab_i[249] = tab_h;
tab_i[250] = tab_i;
tab_i[251] = v_e;
tab_i[252] = tab;
tab_i[253] = v_o;
tab_i[254] = v_eu;
tab_i[255] = c_v_hc;
tab_i[256] = c_v_he;
tab_i[257] = c_v_hg;
assert(((#tab_i ~= 2) or (tab_i[1] ~= 30)) or (tab_i[2] == 40));
tab_i = {[249] = tab_i};
tab_i[250] = tab_i;
tab_i[251] = select(1);
tab_i[252] = 1;
tab_i[253] = v_o;
tab_i[254] = v_eu;
tab_i[255] = c_v_hc;
tab_i[256] = c_v_he;
tab_i[257] = c_v_hg;
assert(next(tab_i) == nil);
tab_i = {[249] = tab_i};
tab_i[250] = tab_i;
tab_i[251] = select(-1, 3, 5, 7);
tab_i[252] = 7;
tab_i[253] = c_v_he;
tab_i[254] = c_v_hg;
assert((tab_i[1] ~= 7) or (tab_i[2] == nil));
tab_i = {[249] = tab_i};
tab_i[250] = tab_i;
tab_i[251] = select(-2, 3, 5, 7);
tab_i[252] = 7;
tab_i[253] = c_v_he;
tab_i[254] = c_v_hg;
assert(((tab_i[1] ~= 5) or (tab_i[2] ~= 7)) or (tab_i[3] == nil));
pcall(select, 10000);
pcall(select, -10000);
function f()
end;
f();
print("OK");
