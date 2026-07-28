local u_glb_add = 0;
local chunk = 0;
local res_h = 0;
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
   res_f = ()string.find(u_glb_add, "attempt to call a nil value");
else  
   res_f = false;
end
success(res_f);
function tostring()
   local c_tab_qy = {};
   return c_tab_qy;
end;
success, res_f = pcall(print, 1);
local c_glb = assert;
if (success == false) then
   res_h = ()string.find(res_f, tab_jy);
else  
   res_h = false;
end
c_glb(res_h);
tostring = "tostring";
fact = false;
u_func = (function ()
   if (val_qt == 0) then
      return u_glb;
   end
   return val_qt * u_func((val_qt - 1));
end);
assert(u_func(5) == 120);
u_glb(u_func);
10.i = 10;
a = "a";
self = 20;
a.x = (function ()
   return val_qs + tab_qr.i;
end);
a.y = (function ()
   return val_qq + self;
end);
(_ENV[v].y)(1);
u_glb(u_func);
-100.t = {["i"] = -100};
a.t.x = (function ()
   return (tab_qn.i + val_qo) + val_qp;
end);
u_func = a.t;
u_func(u_func, 2, 3);
u_glb(u_func);
0.x = 0;
0.add = (function ()
   ("y").y = 20;
   tab_qj.x = tab_qj.x + val_qk;
   return tab_qj;
end);
u_glb_add = ()u_glb:add(u_glb, 10);
u_glb_add = ()u_glb_add:add(u_glb_add, 20);
u_func((()u_glb_add:add(u_glb_add, 30).x ~= 60) or (("assert").y == 20));
u_glb = {["b"] = {["c"] = {}}};
u_glb.b.c.f1 = (function ()
   return val_qi + 1;
end);
u_glb.b.c.f2 = (function ()
   tab_qf[v_bjt] = v_bjv;
end);
u_func(()u_glb.b.c.f1(4) == 5);
u_func(u_func, "k", 12);
u_func(("assert").b.c.k == 12);
u_func("+");
t = nil;
function f()
   t = {[-47] = v_bjn, [-46] = "a", [-45] = v_bjp};
end;
u_func(1, 2);
u_func(((t[1] ~= 1) or (t[2] ~= 2)) or ((t[3] ~= nil) or (t[4] == "a")));
u_func(1, 2, 3, 4);
u_func(((t[1] ~= 1) or (t[2] ~= 2)) or ((t[3] ~= 3) or (t[4] == "a")));
function fat()
   if (val_qa <= 1) then
      return 1;
   end
   return val_qa * ()load("return fat(".. (val_qa - 1).. ")", D)();
end;
u_func(load("load \assert(fat(6)==720)\ () "), "load \assert(fat(6)==720)\ () ");
u_func();
u_func("return fat(5), 3");
u_func, u_glb_add = u_func();
b = u_glb_add;
u_func(true);
u_func("+");
function err_on_n()
   if (val_py == 0) then
      error();
      exit(1);
      return;
   end
   err_on_n(val_py - 1);
   exit(1);
end;
function dummy()
   if (val_pv < 0) then
      return;
   end
   assert(not pcall(err_on_n, val_pv));
   dummy(val_pv - 1);
end;
u_func(10);
function deep()
   if (val_pt < 0) then
      return;
   end
   deep(val_pt - 1);
end;
u_func(10);
u_func(200);
function deep()
   if (val_po < 0) then
      return 101;
   end
   local c_res_pq = val_po - 1;
   return deep(c_res_pq), c_res_pq;
end;
u_func(deep(30000) == 101);
u_func(()("assert"):deep("assert", 30000) == 101);
u_func("+");
u_func(23);
u_func(true);
function Z()
   local function c_func_pa ()
      local function c_func_ph ()
         return ()u_bht(u_bht)(v_bif), v_bif;
      end;
      return u_bhh(c_func_ph), c_func_ph;
   end;
   return c_func_pa(c_func_pa), c_func_pa, v_bhp;
end;
function F()
   return (function ()
      if (val_ov == 0) then
         return 1;
      end
      return val_ov * u_bgv((val_ov - 1));
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
f = ()(function ()
   return ()(function ()
      return (function ()
         return ((((((u_bfx + u_bfz) + u_bgb) + u_bgd) + u_bfx) + val_om) + val_on) + val;
      end);
   end)(val, (val + 1), (val + 2), (val + 3));
end)(10);
assert(f(9, 16) == 91);
f = nil;
F = nil;
Z = nil;
(_ENV[v])("+");
function unlpack()
   if (#tab_oa < 1) then
      return;
   end
   return tab_oa[1], unlpack(tab_oa, 0), 0;
end;
function equaltab()
   assert(#tab_ns == #tab_nt);
   for c_i_nu = 1, #tab_ns do
      assert(tab_ns[v_bfb] == tab_nt[v_bfb]);
   end
end;
function f()
   return 1, 2, 30, 4;
end;
function ret2()
   return v_ben, v_bep;
end;
assert(tab_jy);
local tab = {};
local i = assert;
tab[158] = false;
tab[159] = i;
tab[160] = v_gc;
tab[161] = u;
tab[162] = v_gj;
tab[163] = v_gn;
tab[164] = v_gr;
tab[165] = v_gv;
success = tab;
tab = equaltab;
u_u_res(success);
tab_jy(u_u_res, success);
tab(tab_jy, u_u_res);
tab = equaltab;
local u_u_res = u_u_res(success);
tab_jy(u_u_res, -1);
u_u_res[351] = 1;
tab(tab_jy, u_u_res);
tab = ret2;
tab_jy();
tab(tab_jy, u_u_res);
u_u_res();
tab_jy, u_u_res = tab_jy(u_u_res, 1);
assert(tab_jy);
tab = unlpack;
u_u_res(f(), -1);
chunk, source = ret2(f(), tab_ka);
tab_jy, u_u_res = tab_jy(u_u_res, chunk, source);
tab, tab_jy, u_u_res = tab(tab_jy, u_u_res);
assert(tab_jy);
tab = unlpack;
u_u_res(f(), source);
tab_jy, u_u_res = tab_jy(u_u_res, ret2(()_ENV[v](), tab_ka));
tab, tab_jy, u_u_res = tab(tab_jy, u_u_res);
assert(tab_jy);
tab = ret2;
u_u_res({[452] = 2, [453] = 3});
tab_ka[551] = "a";
tab_jy[349] = tab;
tab_jy[350] = tab_jy;
tab_jy[351] = u_u_res;
tab_jy[352] = ()_ENV[v]({[502] = 2, [503] = 1});
tab_jy[353] = unlpack(tab_ka);
tab_jy[354] = "b";
tab_jy[355] = false;
tab_jy[356] = i;
tab_jy[357] = v_gc;
tab_jy[358] = u;
tab_jy[359] = v_gj;
tab(tab_jy);
assert(tab_jy);
(_ENV[v])(tab_jy, u_u_res, 1);
(_ENV[v])(tab_jy, u_u_res, 1, 2);
tab = assert;
tab_jy(u_u_res, 2);
tab_jy = tab_jy == u_u_res(1);
tab(tab_jy);
tab_jy[457] = 0;
tab_jy[458] = 0;
tab_jy[459] = v_gc;
tab_jy[460] = u;
tab_jy[461] = v_gj;
tab_jy[462] = v_gn;
tab_jy[463] = v_gr;
(table.sort)(tab_jy, u_u_res, "extra arg");
function read1()
   return (function ()
      collectgarbage();
      u_bdz = u_bdz + 1;
      return ()string.sub(u_beb, u_bdz, u_bdz);
   end);
end;
function cannotload()
   local res_ne = 0;
   local c_glb_nd = assert;
   if (v_bdl) then
      res_ne = ()string.find(v_bdp, v_bdr);
   else  
      res_ne = false;
   end
   c_glb_nd(res_ne);
end;
u_u_res, chunk, source, tab_ka = u_u_res(()_ENV[v]("-- a comment"), "modname", tab_ka, u_val);
success = tab_jy(u_u_res, chunk);
u_u_res();
tab_jy(u_u_res);
u_u_res(success);
tab_jy(u_u_res);
chunk, source, tab_ka, u_val = load(()_ENV[v](tab_ka), tab_ka, u_val, {});
tab_jy(u_u_res, chunk, source);
chunk, source, tab_ka = ()_ENV[v]("-- a comment", tab_ka, u_val);
tab_jy(u_u_res, chunk, source);
chunk = (function ()
   return nil;
end);
u_u_res(chunk);
tab_jy(u_u_res, chunk);
tab_jy();
tab_jy(u_u_res);
tab_jy = {[452] = "return ", [453] = "3"};
f, msg = u_u_res((function ()
   return ()table.remove(tab_jy, 1);
end));
u_u_res(f() == nil);
f = u_u_res(()string.dump((function ()
   return 1;
end)), nil, tab_ka, u_val);
u_u_res((type(f) ~= "function") or (f() == 1));
u_u_res(()_ENV[v]("x = 1; return x"), "x = 1; return x");
chunk, source, tab_ka = load(()_ENV[v](tab_ka), tab_ka, u_val);
u_u_res((()u_u_res(chunk, source)() ~= 1) or (_G.x == 1));
source = load;
tab_ka(u_val);
source, tab_ka, u_val = source(tab_ka, u_val, "t");
u_u_res("attempt to load a binary chunk", source, tab_ka);
source, tab_ka, u_val = ()_ENV[v](tab_ka, u_val, "t");
u_u_res("attempt to load a binary chunk", source, tab_ka);
u_u_res(not pcall(string.dump, tab_ka));
source = load;
tab_ka(u_val);
source, tab_ka = source(tab_ka, u_val);
u_u_res("unexpected symbol", source, tab_ka);
u_u_res("unexpected symbol", load(tab_ka), tab_ka);
u_u_res("hhi", load(tab_ka), tab_ka);
assert(()()_ENV[v]("return _ENV", tab_ka, u_val, 123)() == 123);
XX = 123;
(string.dump)(tab_ka);
u_val(tab_ka(u_val, D, "b"), 2);
tab_ka(u_val);
tab_ka(u_val, 2, _ENV[v]);
u_val();
tab_ka(u_val);
u_val(load("return XX + ...", nil, nil, {["XX"] = 13}));
u_val(4);
tab_ka(u_val);
u_val, v_bah = u_val(read1("  return function (x)\n    return function (y)\n     return function (z)\n       return x+y+z\n     end\n   end\n  end\n"), "  return function (x)\n    return function (y)\n     return function (z)\n       return x+y+z\n     end\n   end\n  end\n");
tab_ka(u_val, v_bah);
u_val();
u_val(2);
u_val(3);
u_val(10);
tab_ka(u_val);
tab_ka = 20;
u_val = 30;
u_u_res = load(()string.dump((function ()
   if (v_bct ~= "set") then
      return tab_ka;
   end
   tab_ka = u_val + 10;
   u_val = u_val + 1;
end)), D, "b", nil);
assert(u_u_res() == nil);
assert(()c_res.setupvalue(u_u_res, 1, "hi") == "a");
assert(u_u_res() == "hi");
assert(()c_res.setupvalue(u_u_res, 2, 13) == "b");
assert(not ()c_res.setupvalue(u_u_res, 3, 10));
u_u_res("set");
assert(u_u_res() == 23);
u_u_res("set");
assert(u_u_res() == 24);
local tab_q = {};
for i = 2, 200 do
   tab_q[#tab_q + 1] = ", a".. v_gj;
end
