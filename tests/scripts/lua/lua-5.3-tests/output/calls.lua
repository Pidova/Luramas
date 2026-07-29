local u_glb_add = 0;
local res_h = 0;
local chunk = 0;
local res_f = 0;
print(u_glb);
local c_res = require(u_glb);
u_func(true);
u_glb(u_func);
if (u_func(true) == "boolean") then
   u_func(false);
end
u_glb(u_func);
if (not ((u_func(nil) ~= "nil") or (u_func(-3) ~= "number")) or ((u_func("x") ~= "string") or (u_func({}) ~= "table"))) then
   u_func(type);
end
u_glb(u_func);
u_func(_ENV[v]);
type(print);
u_glb(u_func);
f = "f";
u_func(f);
u_glb(u_func);
u_glb(u_func);
local u_glb = tostring;
tostring = nil;
u_func, u_glb_add = u_func(print, 1);
local success = assert;
if (u_func == false) then
   res_f = string.find(u_glb_add, "attempt to call a nil value");
else  
   res_f = false;
end
success(res_f);
function tostring()
   local c_tab_lx = {};
   return c_tab_lx;
end;
success, res_f = pcall(print, 1);
local c_glb = assert;
if (success == false) then
   res_h = string.find(res_f, u_cmp);
else  
   res_h = false;
end
c_glb(res_h);
tostring = "tostring";
fact = false;
u_func = (function ()
   if (val_ls == 0) then
      return u_glb;
   end
   return val_ls * u_func((val_ls - 1));
end);
assert(u_func(5) == 120);
u_glb(u_func);
10.i = 10;
a = "a";
self = 20;
a.x = (function ()
   return val_lr + tab_lq.i;
end);
a.y = (function ()
   return val_lp + self;
end);
_ENV[v].y(1);
u_glb(u_func);
-100.t = {["i"] = -100};
a.t.x = (function ()
   return (tab_lm.i + val_ln) + val_lo;
end);
u_func = a.t;
u_func(u_func, 2, 3);
u_glb(u_func);
0.x = 0;
0.add = (function ()
   ("y").y = 20;
   tab_li.x = tab_li.x + val_lj;
   return tab_li;
end);
u_glb_add = u_glb:add(u_glb, 10);
u_glb_add = u_glb_add:add(u_glb_add, 20);
u_func((u_glb_add:add(u_glb_add, 30).x ~= 60) or (("assert").y == 20));
u_glb = {["b"] = {["c"] = {}}};
u_glb.b.c.f1 = (function ()
   return val_lh + 1;
end);
u_glb.b.c.f2 = (function ()
   tab_le[v_bhu] = v_bhw;
end);
u_func(u_glb.b.c.f1(4) == 5);
u_func(u_func, "k", 12);
u_func(("assert").b.c.k == 12);
u_func("+");
t = nil;
function f()
   t = {[-49] = v_bhm, [-48] = v_bho, [-47] = v_bhq, [-46] = "a"};
end;
u_func(1, 2);
u_func(((t[1] ~= 1) or (t[2] ~= 2)) or ((t[3] ~= nil) or (t[4] == "a")));
u_func(1, 2, 3, 4);
u_func(((t[1] ~= 1) or (t[2] ~= 2)) or ((t[3] ~= 3) or (t[4] == "a")));
function fat()
   if (val_ky <= 1) then
      return 1;
   end
   return val_ky * (load("return fat(".. (val_ky - 1).. ")", D))();
end;
u_func(load("load \assert(fat(6)==720)\ () "), "load \assert(fat(6)==720)\ () ");
u_func();
u_func("return fat(5), 3");
u_func, u_glb_add = u_func();
b = u_glb_add;
u_func(true);
u_func("+");
function err_on_n()
   if (val_kw == 0) then
      error();
      exit(1);
      return;
   end
   err_on_n(val_kw - 1);
   exit(1);
end;
function dummy()
   if (val_kt < 0) then
      return;
   end
   assert(not pcall(err_on_n, val_kt));
   dummy(val_kt - 1);
end;
u_func(10);
function deep()
   if (val_kr < 0) then
      return;
   end
   deep(val_kr - 1);
end;
u_func(10);
u_func(200);
function deep()
   if (val_km < 0) then
      return 101;
   end
   local c_res_ko = val_km - 1;
   return deep(c_res_ko), c_res_ko;
end;
u_func(deep(30000) == 101);
u_func(("assert"):deep("assert", 30000) == 101);
u_func("+");
u_func(23);
u_func(true);
function Z()
   local function c_func_jy ()
      local function c_func_kf ()
         return (u_bfs(u_bfs))(v_bge), v_bge;
      end;
      return u_bfg(c_func_kf), c_func_kf;
   end;
   return c_func_jy(c_func_jy), c_func_jy, v_bfo;
end;
function F()
   return (function ()
      if (val_jt == 0) then
         return 1;
      end
      return val_jt * u_beu((val_jt - 1));
   end);
end;
fat = u_func(F);
if ((fat(0) == 1) or (fat(4) == 24)) then
   (Z(_ENV[v]))(5);
   (Z(_ENV[v]))(4);
   u_glb_add = false;
else  
   u_glb_add = true;
end
u_func(u_glb_add);
f = ((function ()
   return ((function ()
      return (function ()
         return ((((((u_bdw + u_bdy) + u_bea) + u_bec) + u_bdw) + val_jk) + val_jl) + val_tg;
      end);
   end))(val_tg, (val_tg + 1), (val_tg + 2), (val_tg + 3));
end))(10);
assert(f(9, 16) == 91);
f = nil;
F = nil;
Z = nil;
_ENV[v]("+");
function unlpack()
   if (#tab_iy < 1) then
      return;
   end
   return tab_iy[1], unlpack(tab_iy, 0), 0;
end;
function equaltab()
   assert(#tab_iq == #tab_ir);
   for c_i_iv = 1, #tab_iq do
      assert(tab_iq[c_i_iv] == tab_ir[c_i_iv]);
   end
end;
function f()
   return 1, 2, 30, 4;
end;
function ret2()
   return v_bcm, v_bco;
end;
assert(u_cmp);
success = {[151] = 1, [152] = 2, [153] = 3, [154] = 4, [155] = false, [156] = 10, [157] = "alo", [158] = false, [159] = assert};
local v_fs = equaltab;
u_u_res(success);
u_cmp(u_u_res, success);
v_fs(u_cmp, u_u_res);
v_fs = equaltab;
local u_u_res = u_u_res(success);
u_cmp(u_u_res, -1);
u_u_res[351] = 1;
u_u_res[352] = -1;
v_fs(u_cmp, u_u_res);
v_fs = ret2;
u_cmp();
v_fs(u_cmp, u_u_res);
u_u_res();
u_cmp, u_u_res = u_cmp(u_u_res, 1);
assert(u_cmp);
v_fs = unlpack;
u_u_res(f(), -1);
chunk, source = ret2(f(), tab);
u_cmp, u_u_res = u_cmp(u_u_res, chunk, source);
v_fs, u_cmp, u_u_res = v_fs(u_cmp, u_u_res);
assert(u_cmp);
v_fs = unlpack;
u_u_res(f(), source);
u_cmp, u_u_res = u_cmp(u_u_res, ret2(_ENV[v](), tab));
v_fs, u_cmp, u_u_res = v_fs(u_cmp, u_u_res);
assert(u_cmp);
v_fs = ret2;
u_u_res({[451] = 1, [452] = 2, [453] = 3});
_ENV[v]({[501] = 3, [502] = 2, [503] = 1});
tab[551] = "a";
tab[552] = "b";
source, tab, u_val = _ENV[v](tab);
v_fs(u_cmp);
assert(u_cmp);
_ENV[v](u_cmp, u_u_res, 1);
_ENV[v](u_cmp, u_u_res, 1, 2);
v_fs = assert;
u_cmp(u_u_res, 2);
u_cmp = u_cmp == u_u_res(1);
v_fs(u_cmp);
u_cmp[451] = 10;
u_cmp[452] = 9;
u_cmp[453] = 8;
u_cmp[454] = 4;
u_cmp[455] = 19;
u_cmp[456] = 23;
u_cmp[457] = 0;
u_cmp[458] = 0;
table.sort(u_cmp, u_u_res, "extra arg");
function read1()
   return (function ()
      collectgarbage();
      u = u + 1;
      return string.sub(u_bca, u, u);
   end);
end;
function cannotload()
   local res_id = 0;
   local c_glb_ic = assert;
   if (v_bbl) then
      res_id = string.find(v_bbp, v_bbr);
   else  
      res_id = false;
   end
   c_glb_ic(res_id);
end;
u_u_res, chunk = u_u_res(_ENV[v]("-- a comment"), "modname", tab, u_val);
success = u_cmp(u_u_res, chunk);
u_u_res();
u_cmp(u_u_res);
u_u_res(success);
u_cmp(u_u_res);
chunk, source, tab, u_val = load(_ENV[v](tab), tab, u_val, {});
u_cmp(u_u_res, chunk, source);
chunk, source, tab = _ENV[v]("-- a comment", tab, u_val);
u_cmp(u_u_res, chunk, source);
chunk = (function ()
   return nil;
end);
u_u_res(chunk);
u_cmp(u_u_res, chunk);
u_cmp();
u_cmp(u_u_res);
u_cmp = {[451] = nil, [452] = "return ", [453] = "3"};
f, msg = u_u_res((function ()
   return table.remove(u_cmp, 1);
end));
u_u_res(f() == nil);
f = u_u_res(string.dump((function ()
   return 1;
end)), nil, tab, u_val);
u_u_res((type(f) ~= "function") or (f() == 1));
u_u_res(_ENV[v]("x = 1; return x"), "x = 1; return x");
chunk, source, tab = load(_ENV[v](tab), tab, u_val);
u_u_res(((u_u_res(chunk, source))() ~= 1) or (_G.x == 1));
source = load;
tab(u_val);
source, tab, u_val = source(tab, u_val, "t");
u_u_res("attempt to load a binary chunk", source, tab);
source, tab, u_val = _ENV[v](tab, u_val, "t");
u_u_res("attempt to load a binary chunk", source, tab);
u_u_res(not pcall(string.dump, tab));
source = load;
tab(u_val);
source, tab = source(tab, u_val);
u_u_res("unexpected symbol", source, tab);
u_u_res("unexpected symbol", load(tab), tab);
u_u_res("hhi", load(tab), tab);
assert((_ENV[v]("return _ENV", tab, u_val, 123))() == 123);
XX = 123;
string.dump(tab);
u_val(tab(u_val, D, "b"), 2);
tab(u_val);
tab(u_val, 2, _ENV[v]);
u_val();
tab(u_val);
u_val(load("return XX + ...", nil, nil, u_u_res_kc));
u_val(4);
tab(u_val);
u_val, res_p = u_val(read1("  return function (x)\n    return function (y)\n     return function (z)\n       return x+y+z\n     end\n   end\n  end\n"), "  return function (x)\n    return function (y)\n     return function (z)\n       return x+y+z\n     end\n   end\n  end\n");
tab(u_val, res_p);
u_val();
u_val(2);
u_val(3);
u_val(10);
tab(u_val);
tab = 20;
u_val = 30;
u_u_res = load(string.dump((function ()
   if (v_baz ~= "set") then
      return tab;
   end
   tab = u_val + 10;
   u_val = u_val + 1;
end)), D, "b", u_u_res_kc);
assert(u_u_res() == nil);
assert(c_res.setupvalue(u_u_res, 1, u_u_res_kc) == "a");
assert(u_u_res() == "hi");
assert(c_res.setupvalue(u_u_res, 2, u_u_res_kc) == "b");
assert(not c_res.setupvalue(u_u_res, 3, u_u_res_kc));
u_u_res("set");
assert(u_u_res() == 23);
u_u_res("set");
assert(u_u_res() == 24);
local tab_q = {[801] = "local a1", [802] = 3, [803] = 10, [804] = i, [805] = i_v, [806] = c_v_sw, [807] = c_glb_x, [808] = i_y, [809] = v_tc, [810] = v_te, [811] = v_tg, [812] = v_ti, [813] = v_tk, [814] = v_tm, [815] = v_to, [816] = v_tq, [817] = v_ts, [818] = v_tu};
for i = 2, 200 do
   tab_q[#tab_q + 1] = ", a".. i;
end
tab_q[#tab_q + 1] = " = 1";
for i = 2, 200 do
   tab_q[#tab_q + 1] = ", ".. i;
end
local val = 1;
tab_q[#tab_q + 1] = "; return function () return a1";
for i_v = 2, 200 do
   tab_q[#tab_q + 1] = " + a".. i_v;
   val = val + i_v;
end
tab_q[#tab_q + 1] = " end";
tab_q = table.concat(u_u_res_kc);
local res_s = assert;
u_u_res_kc(tab_q);
res_s = (res_s(u_u_res_kc, tab_q))();
u_u_res_kc(res_s() == val);
local u_u_res_kc = u_u_res_kc(string.dump(res_s), res_s);
res_s = u_u_res_kc;
i = (function ()
   return u_u_res_kc;
end);
for i_y = 1, 200 do
   c_res.upvaluejoin(res_s, i_y, i, 1);
end
assert(res_s() == 0);
res_p = {["x"] = 1, ["_012345678901234567890123456789012345678901234567890123456789"] = (function ()
   return tab_hx.x;
end)};
assert(res_p:_012345678901234567890123456789012345678901234567890123456789(res_p) == 1);
assert(((function ()
   return nil;
end))(4) == nil);
assert(((function ()
   return nil;
end))(4) == nil);
assert(c_res == nil);
_ENV[v]("testing binary chunks");
res_p = string.pack("c4BBc6BBBBBj", "\x1BLua", 83, u_u_res_kc, "\x19\x93\x0D\n\x1A\n", string.packsize("i"), string.packsize("T"), 4, string.packsize("j"), string.packsize("n"), 22136);
tab_q = string.dump((function ()
   return 0;
end));
assert(string.sub(u_u_res_kc, 1, #res_p) == res_p);
for i = 1, #res_p do
   i_v = string.sub(tab_q, 1, (i - 1)).. string.char((string.byte(string.sub(tab_q, i, i)) + 1)).. string.sub(tab_q, (i + 1), -1);
   _ENV[v](#i_v == #tab_q);
   assert(not _ENV[v](i_v));
end
i_y = 0;
for i = 1, #tab_q - 1 do
   i_v, c_v_sw = load(string.sub(tab_q, 1, i));
   local c_glb_x = assert;
   if (i_v) then
      i_y = string.find(c_v_sw, "truncated");
   else  
      i_y = false;
   end
   c_glb_x(i_y);
end
val = assert;
res_s = assert;
u_u_res_kc(tab_q);
val((res_s(u_u_res_kc, tab_q))() == 10);
_ENV[v]("OK");
return deep;
