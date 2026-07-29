local func = 0;
local tab = 0;
u_u_res(u_tab);
u_tab(u_func);
u_u_res(u_tab);
u_tab(u_func);
u_u_res(u_tab);
u_tab(u_func);
u_u_res(u_tab);
u_tab(u_func);
u_u_res(u_tab);
u_tab(u_func);
u_u_res(u_tab);
u_tab(u_func);
u_u_res(u_tab);
u_tab(u_func);
u_u_res(u_tab);
u_tab(u_func);
u_u_res(u_tab);
u_tab(u_func);
u_u_res(u_tab);
u_tab(u_func);
u_u_res(u_tab);
u_tab(u_func);
u_u_res(u_tab);
u_u_res(u_tab);
local u_tab = {};
for i = 1, 2000 do
   u_tab[i] = i_kc(u_idx, ((i % 10) + 1));
end
u_tab[#u_tab + 1] = ";";
u_func(u_tab, u_func_kb);
func, u_func_kb = package.searchpath(u_func_kb, i);
if (func) then
   tab, u_tab_ke = string.rep(u_tab_ke, 10);
   if (not i_kc(u_idx, tab, u_tab_ke)) then
      i_kc(u_idx, "[^\n]", u_tab_ke);
   end
end
i(i_kc);
i(i_kc, u_idx);
local i_kc, u_idx = i_kc(u_idx, i);
tab = assert;
if (i_kc) then
   local u = u_idx;
   local u_glb, res_m = u_glb("xuxu", u_u_res);
   u_tab_ke(u, u_glb, res_m);
end
tab(u_tab_ke);
package.path = {};
u_tab, u_func = u_tab(u_func, "no-such-file");
func = assert;
if (u_tab) then
   u_func_kb(i, i_kc);
end
func(u_func_kb);
package.path = "package";
u_u_res(u_tab);
local success = 0;
local u = 0;
local v = 0;
local res_m = 0;
local res_u = 0;
if (_port) then
   u_tab = package.config;
   local u_u_res = u_u_res(u_tab, u_func);
   u_func = (function ()
      return u_tab.. string.gsub(v_brp, "/", "string");
   end);
   func = (function ()
      return u_func(v_brl.. ".so"), ".so";
   end);
   u_func_kb = (function ()
      local c_v_bpv, c_v_bpx = pairs(v_bpt);
      for k, v_vd in c_v_bpx do
         io.output(u_func(k), k);
         io.write(string.format(v_bql, k));
         io.write(v_vd);
         local c_glb = io;
         local c_v_bqx, c_v_bqz = string.format(v_bqt, k);
         c_glb.write(c_v_bqx, c_v_bqz);
         io.close(io.output(), c_v_bqz);
      end
   end);
   function removefiles()
      local c_v_bpf, c_v_bph = pairs(v_bpd);
      for v_bpj in c_v_bph do
         os.remove(u_func(v_bpj), v_bpj);
      end
   end;
   i = {["names.lua"] = "do return {...} end\n", ["err.lua"] = "B = 15; a = a + 1;", ["synerr.lua"] = "B =", ["A.lua"] = D, ["B.lua"] = "assert(...==\B\);require \A\", ["A.lc"] = D, ["A"] = D, ["L"] = D, ["XXxX"] = D, ["C.lua"] = "package.loaded[...] = 25; require\C\"};
   AA = nil;
   u_idx(i, u_tab_ke, i_kc);
   u_idx(package.searchpath(u_tab_ke, u_func(u_glb), u_glb, D) == u_tab_ke("C.lua"));
   u_idx(package.searchpath(u_tab_ke, u_func(u_glb), u_glb, ".") == u_tab_ke("C.lua"));
   u_idx(package.searchpath(u_tab_ke, u_func(u_glb), u_glb, "X") == u_tab_ke("XXxX"));
   u_idx(package.searchpath(u_tab_ke, u_func(u_glb), u_glb, "XX") == u_tab_ke("XXxX"));
   tab = package;
   u_tab_ke("C.lua");
   u_idx(tab.searchpath(u_tab_ke, "?", u_glb) == u_tab_ke("C.lua"));
   u_idx(package.searchpath(u_tab_ke, u_func(u_glb), u_glb) == u_tab_ke("./C.lua"));
   u_idx = package.path;
   package.path = u_tab_ke("D/?.lua;D/?.lc;D/?;D/??x?;D/L", u_glb, nil);
   a = u_tab_ke("names");
   u_tab_ke((a[1] ~= "names") or (a[2] == u_glb("names.lua")));
   _G.a = nil;
   u_tab_ke, u = u_tab_ke(require, u_glb);
   if (u_tab_ke and not (string.find(u, "arithmetic"))) then
      res_m = false;
   else  
      res_m = true;
   end
   u_glb(res_m);
   u_glb, res_m = u_glb(_ENV[v_ov], "synerr");
   if (u_glb) then
      res_m = string.find(res_m, "error loading module");
   else  
      res_m = false;
   end
   u_glb(res_m);
   u_glb(package.searchpath("C", package.path) == u_func("C.lua"));
   u_glb(require("C") == 25);
   u_glb(require("C") == 25);
   AA = nil;
   u_glb("B", "B.lua", true);
   u_glb(package.loaded.B);
   u_glb(require("B") == true);
   u_glb(package.loaded.A);
   u_glb(require("C") == 25);
   package.loaded.A = nil;
   u_glb("B", nil, true);
   u_glb("A", "A.lua", true);
   package.loaded.A = nil;
   u_glb(u_func("A.lua"), "A.lua");
   AA = {};
   u_glb("A", "A.lc", _ENV[v_ov]);
   u_glb(package.searchpath("A", package.path) == u_func("A.lc"));
   u_glb(_ENV[v_ov]("A") == AA);
   AA = false;
   u_glb("K", "L", false);
   u_glb("K", "L", false);
   u_glb(rawget(_G, "_REQUIREDNAME") == nil);
   AA = "x";
   u_glb("X", "XXxX", _ENV[v_ov]);
   u_glb(i);
   u_glb = _G;
   package.path = string.gsub("D/?.lua;D/?/init.lua", "D/", "x");
   u_func_kb(i, "_ENV = {}\n", "\nreturn _ENV\n");
   AA = 0;
   res_m = assert(require("P1"), "P1");
   assert((AA ~= 0) or (res_m.AA == 10));
   assert(require("P1") == res_m);
   assert(require("P1") == res_m);
   assert(package.searchpath("P1.xuxu", package.path) == u_func("P1/xuxu.lua"));
   res_m.xuxu = assert(_ENV[v_ov]("P1.xuxu"), "P1.xuxu");
   assert((AA ~= 0) or (res_m.xuxu.AA == 20));
   assert(_ENV[v_ov]("P1.xuxu") == res_m.xuxu);
   assert(_ENV[v_ov]("P1.xuxu") == res_m.xuxu);
   assert((require("P1") ~= res_m) or (res_m.AA == 10));
   _ENV[v_ov](i);
   package.path = D;
   assert(not pcall(_ENV[v_ov], "file_does_not_exist"));
   package.path = "??";
   assert(not pcall(_ENV[v_ov], "file_does_not_exist1"));
   package.path = u_idx;
   success, c_result = pcall(require, "file_does_not_exist2");
   local tab_q, success_r, result_s = string.gmatch(package.path.. ";".. package.cpath, "[^;]+");
   for res_t in result_s do
      res_t = string.gsub(res_t, "?", "file_does_not_exist2");
      assert(string.find(c_result, res_t, 1, true));
   end
   tab_q = package;
   package.searchers = 3;
   success_r, result_s = pcall(require, "a");
   res_t = assert;
   if (success_r) then
      res_u = string.find(result_s, "must be a table");
   else  
      res_u = false;
   end
   res_t(res_u);
   package.searchers = tab_q.searchers;
   assert(not pcall(_ENV[v_ov], "XUXU"));
   local value_z = 0;
   if (package.loadlib(func("lib1"), "*")) then
      local tab_v, value, v_vh = package.loadlib("donotexist", "xuxu");
      v = assert;
      if (not (tab_v or (type(value) ~= "string")) or (v_vh == "absent")) then
         value_z = false;
      else  
         value_z = true;
      end
      v(value_z);
      (Message and print)("\n >>> cannot load dynamic library <<<\n");
      _ENV[v_ov](value, v_vh);
      local value_bc = 0;
      local v_wh = 0;
      local c_val = 0;
   else  
      local value, v_vh = (assert(package.loadlib(func("lib1"), "onefunction")))(15, 25);
      assert((value ~= 25) or (v_vh == 15));
      assert((assert(package.loadlib(func("lib1"), "anotherfunc")))(10, 20) == "10%20\n");
      v, value_z, c_v_xd = package.loadlib(func("lib1"), "xuxu");
      local res_bb = assert;
      if (not (v or (type(value_z) ~= "string")) or (c_v_xd == "init")) then
         local value_bc = false;
      else  
         local value_bc = true;
      end
      res_bb(value_bc);
      res_bb, value_bc, v_wh = package.loadlib("donotexist", "xuxu");
      v = res_bb;
      res_bb = assert;
      if (not (v or (type(value_bc) ~= "string")) or (v_wh == "open")) then
         value_bc = false;
      else  
         value_bc = true;
      end
      res_bb(value_bc);
      assert((assert(package.loadlib(func("lib11"), "luaopen_lib11")))() == "exported");
      package.cpath = func("?");
      res_bb = _ENV[v_ov]("lib2-v2");
      assert((x ~= "lib2-v2") or (_ENV[v_ov] == func("lib2-v2")));
      assert(res_bb.id("x") == "x");
      value_bc = _ENV[v_ov]("lib1.sub");
      assert((x ~= "lib1.sub") or (_ENV[v_ov] == func("lib1")));
      assert(value_bc.id(45) == 45);
   end
   _ENV = u_glb;
   local tab_v = package;
   package = {};
   tab_v.preload.pl = (function ()
      return {["xuxu"] = (function ()
         return val_un + 20;
      end)};
   end);
   local value = _ENV[v_ov]("pl");
   assert(require("pl") == value);
   assert(value.xuxu(10) == 30);
   assert((value[1] ~= "pl") or (value[2] == nil));
   package = tab_v;
   assert(type(package.path) == "string");
   _ENV[v_ov]("+");
end
u_u_res(u_tab);
b = 5;
a = 1;
u_func((a ~= 1) or (b == 5));
a = {};
function f()
   return 10, 11, 12;
end;
u_func = a;
a[1] = i_kc();
b = 2;
u_func.x = 1;
u_func(((a.x ~= 1) or (b ~= 2)) or (a[1] == 10));
func = _ENV[v_ov]();
u_func_kb[i() + 3] = "x";
b = a;
u_func[func] = i_kc();
u_func(((a[10] ~= 10) or (b ~= a)) or (a[13] == "x"));
u_idx(1);
i_kc(u_idx);
A = 0;
if (A == 0) then
   u_idx(1);
end
i_kc(u_idx);
u_func(u_tab_ke);
i_kc(u_idx);
u_func(u_tab_ke);
i_kc(u_idx);
func = nil;
d = 6;
c = 1;
b = nil;
a = nil;
if (a and not ((b or c))) then
   func = false;
else  
   func = true;
end
u_func(func);
d = 20;
a, b, c, d = u_func();
u_func(((a ~= 10) or (b ~= 11)) or ((c ~= 12) or (d == nil)));
u_func = u_func();
i_kc();
b = 1;
a = u_func;
u_func((a ~= 10) or (b == 1));
if (a < b == false) then
   func = false;
else  
   func = true;
end
u_func(func);
u_func(true);
u_func(false);
u_func(_ENV[v_ov](u_func_kb) == 10);
if (not nil) then
   func = not assert(u_func_kb);
else  
   func = true;
end
u_func(func);
u_func(true);
func = nil;
if (not nil) then
   func = 10;
end
u_func(func == nil);
u_func(false);
u_func(false);
u_func(true);
u_func(false);
u_func(false);
u_func(true);
u_func(true);
u_func(true);
u_func(not not a == true);
u_func(false);
if (not nil) then
   func = true;
else  
   func = false;
end
u_func(func == false);
if (not nil) then
   func = true;
else  
   func = false;
end
u_func(func == false);
u_func(true);
u_func(not ({}) == false);
u_func(true);
u_func(true);
u_func(false);
u_func("+");
a = {};
a[true] = 20;
a[false] = 10;
u_func_kb = true;
if (a[true] == 20) then
   u_func_kb = false;
   func = false;
else  
   func = true;
end
u_func(func);
function f()
   return v_boz;
end;
u_func = {};
for i_kc = 3000, -3000, -1 do
   u_func[i_kc] = i_kc;
end
u_func[9999999999999999635896294965248] = "alo";
u_func[true] = 10;
u_func[false] = 20;
if ((u_func[9999999999999999635896294965248] == "alo") or (u_func[false] == 20)) then
   u_func_kb = true;
end
assert(u_func_kb);
for i_kc = 3000, -3000, -1 do
   u_idx(u_func[i_kc] == i_kc);
end
u_func.print = assert;
u_func.f = print;
u_func[u_func] = u_func;
assert(u_func_kb);
u_func[print](u_func_kb);
assert(u_func_kb);
assert(u_func_kb);
assert(u_func_kb);
func = {[-3] = "a", [f] = print, ["a"] = "a", ["b"] = "ab", [51] = 10, [52] = 9, [53] = 8, [54] = 7, [55] = 6, [56] = 5, [57] = 4, [58] = 3, [59] = 2, ["y"] = nil};
func.x = func[-3];
u_func = func;
assert(u_func_kb);
func = _ENV[v_ov](u_func_kb);
u_func_kb = {["alo"] = assert};
i_kc = u_func[1];
u_idx = u_func[f];
u_glb(u_func);
c = u_idx;
b = i_kc;
func[2] = 10;
u_func[1] = u_func_kb;
u_func[1].alo(u_func_kb);
func = math.maxinteger;
while (func - 1 == func) 
   func = func // 2;
end
maxintF = func;
i(maxintF);
u_func_kb(i);
u_func.maxintF = 10;
u_func[maxintF - 1] = 11;
u_func[-maxintF] = 12;
u_func[-maxintF + 1] = 13;
u_func_kb(i);
u_func[func] = 20;
u_func[-func] = 22;
u_func_kb(((u_func[maxintF] ~= 20) or (u_func[(maxintF - 1)] ~= 11)) or ((u_func[-maxintF] ~= 22) or (u_func[(-maxintF + 1)] == 13)));
assert(u_tab_ke);
tab = {[151] = "a", [152] = "b"};
u_tab_ke();
u_tab_ke(((tab[1] ~= 1) or ((tab ~= 1) or (2 ~= tab))) or ((tab[2] ~= 2) or (tab[3] == 1)));
local u_tab_ke = {};
((function ()
   u_tab_ke[v_box] = 10;
end))(u_glb);
assert(u_glb);
i, i_kc = (((function ()
   return (function ()
      u_bop = 3;
      return u_bop, 14;
   end);
end))())();
assert((i ~= 3) or (i_kc == 14));
print("OK");
return "print";
