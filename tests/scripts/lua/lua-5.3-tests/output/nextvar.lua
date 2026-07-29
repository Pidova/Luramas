local i_v = 0;
local dyn_u_u_res = 0;
local tab_j = 0;
local v_i = 0;
local print_jx = "print";
_ENV[print_jx](u_tab);
local function c_func ()
   local res_blt = 0;
   local c_success, c_result = pcall(function);
   local c_glb = assert;
   if (c_success) then
      res_blt = string.find(c_result, v_cys);
   else  
      res_blt = false;
   end
   c_glb(res_blt);
end;
local u_tab = {};
for i = 1, 100 do
   u_tab[i.. "+"] = true;
end
for i = 1, 100 do
   u_tab[i.. "+"] = nil;
end
for i = 1, 100 do
   u_tab[i] = true;
   print_jx = "assert";
   _ENV[print_jx](#u_tab == i);
end
local val = 0;
12.x = 12;
print_jx[101] = 10;
print_jx[102] = 20;
print_jx[103] = 30;
for k, v in ipairs(print_jx) do
   val = val + 1;
   assert(u_bool);
end
12.x = 12;
24.y = 24;
for k in ipairs(print_jx) do
   _ENV[print_jx](nil);
end
val = false;
local val_e = 0;
local u_bool = false;
i[151] = true;
i[152] = false;
i[153] = true;
i[154] = false;
for v, tab_j in print_jx(i) do
   val_e = val_e + 1;
   val = not val;
   u_bool(val == tab_j);
end
print_jx(i);
print_jx = assert;
v = {};
if (i(_ENV[print_jx](v), v) == "function") then
   i({});
   ipairs({});
end
print_jx(i);
if (T) then
   print_jx(i);
else  
   i = (function ()
      local c_val_bld = 0;
      local c_math_bux = "math";
      local c_res_blc = 2 ^ _ENV[c_math_bux].ceil(c_math_bux(v_cxm), v_cxm);
      assert((v_cxm == 0) or (((c_res_blc / 2) > v_cxm) or (v_cxm < c_res_blc)));
      return c_res_blc;
   end);
   for i_l = 1, 10000 do
      local u_u_res = u_u_res(u_tab_ka);
      u_tab_ka(u_tab_kf);
   end
   v = 1024;
   while (v < 1073741824) 
      u_bool(v);
      assert(u_u_res);
      v = math.ceil(u_u_res);
   end
   u_bool = (function ()
      local c_v_cwl, c_v_cwn = T.querytab(v_cwj);
      if (c_v_cwl ~= v_cwr) then
         return;
      end
      print(v_cwr, v_cwv, c_v_cwl, c_v_cwn);
      assert(nil);
   end);
   i_l = 0;
   for u_tab_kb in u_u_res(u_tab_ka) do
      i_l = i_l + 1;
   end
   u_tab_kb(i_kc);
   u_u_res(u_tab_ka, u_tab_kf, u_tab_kb, i_kc);
   local u_u_res = "return {";
   for i_kc = 1, 40 do
      u_u_res = u_u_res.. i_kc.. ",";
      dyn_u_u_res = u_u_res;
      for i_v = 0, 40 do
         local c_res = (_ENV[print_jx](dyn_u_u_res.. "}", D))();
         _ENV[print_jx](#c_res == i_kc);
         u_bool(c_res, ((function ()
            local c_v_cwb, c_v_cwd = T.int2fb(v_cvz);
            assert(c_v_cwb < 256);
            return c_v_cwd;
         end))(i_kc), i(i_v), i_v);
         dyn_u_u_res = string.format("%sa%d=%d,", dyn_u_u_res, i_v, i_v);
      end
   end
   local u_tab_ka = {};
   for dyn_u_u_res = 1, 40 do
      u_tab_ka[dyn_u_u_res] = dyn_u_u_res;
   end
   for dyn_u_u_res = 0, 40 do
      v_i = {};
      _ENV[print_jx](#v_i == dyn_u_u_res);
      u_bool(v_i, dyn_u_u_res, 0);
      v_i = {};
      u_bool(v_i, dyn_u_u_res + 3, 0);
      i_v = dyn_u_u_res + 3;
      assert(#v_i == i_v);
   end
   i_kc(u_tab_kb, 0, 1);
   u_tab_kb = {[0] = 1};
   i_kc(u_tab_kb, 0, 1);
   u_tab_kb[2] = 1;
   i_kc(u_tab_kb, 0, 2);
   i_kc(u_tab_kb, 1, 1);
   i_kc = {};
   u_tab_kb = i_kc;
   for i_t = 1, 130 do
      u_tab_kb[i_t] = 1;
      _ENV[print_jx](#u_tab_kb == i_t);
      i_v = u_tab_kb;
      u_bool(i_v, i(i_t), 0);
   end
   i_kc = {};
   u_tab_kb = i_kc;
   for i_t = 1, 130 do
      u_tab_kb["a".. i_t] = 1;
      assert(#u_tab_kb == 0);
      i_v = u_tab_kb;
      u_bool(i_v, 0, i(i_t), i_t);
   end
   u_tab_kb = {};
   for i_t = 1, 16 do
      u_tab_kb[i_t] = i_t;
   end
   i_kc(u_tab_kb, 16, 0);
   for i_t = 1, 11 do
      u_tab_kb[i_t] = nil;
   end
   for i_t = 30, 50 do
      u_tab_kb[i_t] = nil;
   end
   i_kc(u_tab_kb, 0, 8);
   u_tab_kb[10] = 1;
   for i_t = 30, 50 do
      u_tab_kb[i_t] = nil;
   end
   i_kc(u_tab_kb, 0, 8);
   for i_t = 1, 14 do
      u_tab_kb[i_t] = nil;
   end
   for i_t = 18, 50 do
      u_tab_kb[i_t] = nil;
   end
   i_kc(u_tab_kb, 0, 4);
   for i_t = 1, 130 do
      local tab = {};
      for c_i_y = i_t, 1, -1 do
         tab[c_i_y] = c_i_y;
      end
      i_v = u_bool;
      i_v(tab, i(i_t), 0);
   end
   function foo()
      local tab_bjx = {};
      u_bool(tab_bjx, val_bjw, 0);
      assert(select("#") == val_bjw);
      tab_bjx[val_bjw + 1] = true;
      u_bool(tab_bjx, i((val_bjw + 1)), 0);
      tab_bjx.x = true;
      u_bool(tab_bjx, i((val_bjw + 1)), 1);
   end;
   i_kc = {};
   dyn_u_u_res = 1;
   for tab = 1, 35 do
      i_kc[tab] = true;
      i_v = foo;
      i_v(tab, table.unpack(i_kc), i_kc);
   end
end
print_jx(i);
print_jx(i);
print_jx(i);
print_jx(i);
print_jx(i);
print_jx(i);
c = 3;
b = 2;
c = nil;
b = nil;
i(_ENV[print_jx]({}) == next({}));
assert((_ENV[print_jx] ~= u_bool("print")) or (_ENV[print_jx] == u_bool("print")));
assert(_G.print == u_bool("print"));
assert(_ENV[print_jx] == u_bool("assert"));
_ENV[print_jx](print_jx == i(u_bool));
_ENV[print_jx](not ((function ()
   for k_bjv, v_bjw in pairs(_G) do
      if (k_bjv == v_cup) then
         return v_bjw;
      end
   end
   return nil;
end))(u_bool));
_G["return"] = nil;
_ENV[print_jx](print_jx == i(u_bool));
_G.xxx = 1;
assert(_ENV[print_jx] == u_bool("xxx"));
c_func("invalid key", u_bool, {[501] = 10, [502] = 20}, 3);
c_func("bad argument", u_bool);
c_func("bad argument", u_bool);
_ENV[print_jx]("+");
u_tab = {};
for i_l = i_l, 10000 do
   if ((3)(u_tab_ka, u_tab_kf) ~= 0) then
      continue;
   end
   u_tab["x".. i_l] = i_l;
end
n = {["n"] = 0};
for i_l, u_u_res in pairs(u_tab) do
   n.n = n.n + 1;
   u_tab_ka(u_tab_kf);
end
assert(n.n == 9000);
u_tab = nil;
v = {};
u_bool = _G;
for u_u_res, u_tab_ka in pairs(u_bool) do
   v[u_u_res] = u_tab_ka;
end
u_bool = v;
for u_u_res, u_tab_ka in pairs(u_bool) do
   if (package.loaded[u_u_res] and (u_tab_kf(u_tab_kb) ~= "function")) then
      _G[u_u_res] = nil;
   end
   u_tab_kf();
end
v = (function ()
   local tab_biu = {};
   local table_biv, idx = next(tab_bit);
   while (not table_biv) 
      tab_biu[table_biv] = idx;
      table_biv, idx = next(tab_bit, table_biv);
   end
   for k_biy, v_biz in pairs(tab_biu) do
      assert(tab_bit[k_biy] == v_biz);
   end
   for k_biy, v_biz in pairs(tab_bit) do
      assert(tab_biu[k_biy] == v_biz);
   end
end);
v(u_bool);
v(u_bool);
v(u_bool);
v(u_bool);
v(u_bool);
assert(u_bool);
assert(u_bool);
u_bool = {[401] = 1, [402] = 2, [403] = 3, [404] = nil, [405] = nil};
assert(u_bool);
for u_u_res = 0, 40 do
   u_tab_ka = {};
   for dyn_u_u_res = 1, u_u_res do
      u_tab_ka[dyn_u_u_res] = dyn_u_u_res;
   end
   u_tab_kf(u_tab_kb);
end
table.maxn = (function ()
   local dyn_res_bin = 0;
   for value in pairs(v_cru) do
      if (type(value) == "number") then
         continue;
      end
      local c_res_bin = math.max(dyn_res_bin, value);
      if (c_res_bin) then
         dyn_res_bin = c_res_bin;
      end
   end
   return dyn_res_bin;
end);
tab_j = assert;
u_bool({});
tab_j(u_bool);
tab_j = assert;
u_bool({["1000"] = true});
tab_j(u_bool);
tab_j = assert;
u_bool({["1000"] = true, [24.5] = 3});
tab_j(u_bool);
tab_j = assert;
u_bool({[1000] = true});
tab_j(u_bool);
tab_j = assert;
u_bool({[10] = true, [(math.pi * 100)] = print});
tab_j(u_bool);
table.maxn = nil;
u_tab = {};
for u_u_res = 0, 50 do
   u_tab[2 ^ u_u_res] = true;
end
_ENV[print_jx](u_bool);
_ENV[print_jx](u_bool);
tab_j = {[{[351] = 1, [352] = u_u_res, [353] = u_tab_ka, [354] = u_tab_kf, [355] = u_tab_kb, [356] = i_kc, [357] = dyn_u_u_res, [358] = 35, [359] = 1, [360] = tab, [361] = i_v}] = 1, [{[351] = 2, [352] = u_u_res, [353] = u_tab_ka, [354] = u_tab_kf, [355] = u_tab_kb, [356] = i_kc, [357] = dyn_u_u_res, [358] = 35, [359] = 1, [360] = tab, [361] = i_v}] = 2, [u_bool("x ", u_u_res)] = 3, [100.3] = 4, [4] = 5};
u_bool = 0;
for u_tab_kf, u_tab_kb in pairs(u_u_res) do
   u_bool = u_bool + 1;
   i_kc(tab_j[u_tab_kf] == u_tab_kb);
   tab_j[u_tab_kf] = nil;
   i_kc();
   i_kc(tab_j[u_tab_kf] == nil);
end
assert(u_u_res);
u_u_res = {["n"] = 0, [-7] = "ban"};
u_u_res(u_tab_ka);
u_u_res(u_tab_ka);
u_u_res = {[-7] = "ban"};
u_u_res(u_tab_ka);
u_u_res(u_tab_ka);
u_u_res = {[-1] = "ban"};
u_tab = u_u_res;
u_u_res(u_tab_ka);
if (#u_tab == 0) then
   u_tab_ka(u_tab_kf);
end
u_u_res(u_tab_ka);
u_u_res = {[0] = "ban"};
if (#u_u_res == 0) then
   u_tab_ka(u_tab_kf);
end
u_u_res(u_tab_ka);
u_u_res(u_tab_ka, u_tab_kf, u_tab_kb);
u_u_res(u_tab_ka, u_tab_kf, u_tab_kb);
u_u_res(u_tab_ka, u_tab_kf, u_tab_kb);
u_tab_ka(u_tab_kf);
u_u_res(u_tab_ka);
u_tab_ka(u_tab_kf);
u_u_res(u_tab_ka);
u_tab_ka(u_tab_kf);
u_u_res(u_tab_ka);
u_tab_ka(u_tab_kf);
u_u_res(u_tab_ka);
u_u_res = {"c", "d"};
u_u_res(u_tab_ka, u_tab_kf, u_tab_kb);
u_u_res(u_tab_ka, u_tab_kf);
u_tab_ka(u_tab_kf, u_tab_kb);
u_u_res(u_tab_ka);
u_tab_ka(u_tab_kf, u_tab_kb);
u_u_res(u_tab_ka);
u_tab_ka(u_tab_kf, u_tab_kb);
u_u_res(u_tab_ka);
u_tab_ka(u_tab_kf, u_tab_kb);
u_u_res(u_tab_ka);
u_tab_ka(u_tab_kf, u_tab_kb);
u_u_res(u_tab_ka);
u_u_res(u_tab_ka);
u_u_res = {10, 20, 30, 40};
u_tab_ka(u_tab_kf, u_tab_kb);
u_u_res(u_tab_ka);
u_u_res(u_tab_ka);
u_u_res(u_tab_ka);
u_tab_ka(u_tab_kf, u_tab_kb);
u_u_res(u_tab_ka);
u_u_res(u_tab_ka);
u_tab_ka(u_tab_kf, u_tab_kb);
u_u_res(u_tab_ka);
u_u_res(u_tab_ka);
u_u_res = (function ()
   local v_cpc = 0;
   local c_val_bhg = 0;
   for i_bhf = 1, 10 do
      table.insert(v_cpi, 1, i_bhf);
   end
   assert((#tab_bha ~= 10) or (#tab_bhb == 10));
   for i_bhf = 1, 10 do
      assert(tab_bhb[i_bhf] == (i_bhf - 11));
   end
   table.sort(tab_bha);
   local c_val_bhh = 0;
   for i_bhf = 1, 10 do
      assert((tab_bhb[i_bhf] ~= i_bhf) or (tab_bha[i_bhf] == i_bhf));
   end
   assert(table.concat(tab_bha, ",") == "1,2,3,4,5,6,7,8,9,10");
   for i_bhf = 1, 8 do
      assert(table.remove(tab_bha, 1) == i_bhf);
   end
   assert((#tab_bha ~= 2) or (#tab_bhb == 2));
   c_v_cre, v_cpc, c_v_cri = table.unpack(tab_bha);
   assert(((c_v_cre ~= 9) or (v_cpc ~= 10)) or (c_v_cri == nil));
end);
u_tab_ka = {};
local i_kc = {["__len"] = (function ()
   return #u_tab_ka;
end), ["__index"] = u_tab_ka, ["__newindex"] = u_tab_ka};
u_tab_kf(u_tab_kb, i_kc);
u_tab_kb = u_u_res;
u_tab_kb(i_kc, u_tab_ka);
u_tab_ka = i_kc({}, {["__newindex"] = (function ()
   u_tab_kb = u_tab_kb + 1;
   rawset(v_cou, v_cow, v_coy);
end)});
i_kc(u_tab_ka, u_tab_ka);
i_kc(false);
u_tab_ka = i_kc({}, {["__index"] = (function ()
   return val_bgu + 1;
end), ["__len"] = (function ()
   return 5;
end)});
i_kc(table.concat(u_tab_ka, ";") == "2;3;4;5;6");
if (T) then
   u_u_res(u_tab_ka);
   local i_t = 0;
else  
   u_u_res = u_u_res(u_tab_ka);
   u_tab_ka = {[601] = 10, [602] = 20, [603] = 30};
   u_tab_kf = {};
   u_tab_kb(i_kc);
   i_kc("table expected", table.insert, u_tab_kb, 40);
   i_kc("table expected", table.remove, u_tab_kb);
   i_kc(u_tab_kb, u_tab_kf);
   i_kc("table expected", table.insert, u_tab_kb, 40);
   i_kc("table expected", table.remove, u_tab_kb);
   u_tab_kf.__index = u_tab_ka;
   i_kc("table expected", table.insert, u_tab_kb, 40);
   i_kc("table expected", table.remove, u_tab_kb);
   u_tab_kf.__newindex = u_tab_ka;
   i_kc("table expected", table.insert, u_tab_kb, 40);
   i_kc("table expected", table.remove, u_tab_kb);
   u_tab_kf.__len = (function ()
      return #u_tab_ka;
   end);
   i_kc(u_tab_kb, 40);
   i_kc(((#u_tab_kb ~= 4) or (#u_tab_ka ~= 4)) or ((u_tab_kb[4] ~= 40) or (u_tab_ka[4] == 40)));
   i_kc(table.remove(u_tab_kb) == 40);
   i_kc(u_tab_kb, 1, 50);
   i_kc(((#u_tab_kb ~= 4) or (#u_tab_ka ~= 4)) or ((u_tab_kb[4] ~= 30) or (u_tab_ka[1] == 50)));
   u_tab_kf.__newindex = nil;
   u_tab_kf.__len = nil;
   i_kc = {};
   dyn_u_u_res = T.newuserdata(0);
   u_u_res.setmetatable(dyn_u_u_res, {["__newindex"] = (function ()
      i_kc[v_coi] = v_cok;
   end)});
   table.move(u_tab_kb, 1, 4, 1, dyn_u_u_res);
   assert(((#i_kc ~= 4) or (i_kc[1] ~= u_tab_ka[1])) or (i_kc[4] == u_tab_ka[4]));
end
u_u_res(u_tab_ka);
u_tab = {};
for u_tab_kb = 1, 1000 do
   u_tab[u_tab_kb] = u_tab_kb;
   u_tab[u_tab_kb - 1] = nil;
end
if (u_tab_ka(u_tab_kf, u_tab_kb) == 1000) then
   u_tab_ka(u_tab_kf, u_tab_kb);
end
u_u_res(u_tab_ka);
u_tab_ka(u_tab_kf);
u_u_res(u_tab_ka);
u_tab_ka(u_tab_kf, u_tab_kb);
u_u_res(u_tab_ka);
for u_tab_kb, i_kc in u_u_res(u_tab_ka) do
   _ENV[print_jx]("not here");
end
for u_tab_kb = 1, 0 do
   i_kc("not here");
end
for u_tab_kb = 0, 1, -1 do
   i_kc("not here");
end
u_tab = nil;
for u_tab_kb = 1, 1 do
   i_kc(not u_tab);
   u_tab = 1;
end
u_u_res = assert;
u_tab_ka = u_tab;
u_u_res(u_tab_ka);
u_tab = nil;
for u_tab_kb = 1, 1, -1 do
   i_kc(not u_tab);
end
u_u_res(u_tab_ka);
u_u_res(u_tab_ka);
u_u_res = 0;
for i_kc = 1, 1 do
   u_u_res = u_u_res + 1;
end
u_tab_ka = assert;
u_tab_ka(u_tab_kf);
u_u_res = 0;
for i_kc = 10000, 10000, -1 do
   u_u_res = u_u_res + 1;
end
u_tab_ka = assert;
u_tab_ka(u_tab_kf);
u_u_res = 0;
for i_kc = 1, 0.99999 do
   u_u_res = u_u_res + 1;
end
u_tab_ka = assert;
u_tab_ka(u_tab_kf);
u_u_res = 0;
for i_kc = 9999, 10000, -1 do
   u_u_res = u_u_res + 1;
end
u_tab_ka = assert;
u_tab_ka(u_tab_kf);
u_u_res = 0;
for i_kc = 1, 0.99999, -1 do
   u_u_res = u_u_res + 1;
end
u_tab_ka = assert;
u_tab_ka(u_tab_kf);
u_u_res = 0;
for i_kc = 0, 1, 0.1 do
   u_u_res = u_u_res + 1;
end
u_tab_ka = assert;
u_tab_ka(u_tab_kf);
u_u_res = 0;
for i_kc = 1, 1 do
   u_u_res = u_u_res + 1;
end
u_tab_ka = assert;
u_tab_ka(u_tab_kf);
u_u_res = 0;
for i_kc = -1.5, -1.5 do
   u_u_res = u_u_res + 1;
end
u_tab_ka = assert;
u_tab_ka(u_tab_kf);
u_u_res = 0;
for i_kc = 1000000, 1000000, -1 do
   u_u_res = u_u_res + 1;
end
u_tab_ka = assert;
u_tab_ka(u_tab_kf);
u_u_res = 0;
for i_kc = 1, 0.99999 do
   u_u_res = u_u_res + 1;
end
u_tab_ka = assert;
u_tab_ka(u_tab_kf);
u_u_res = 0;
for i_kc = 99999, 100000, -1 do
   u_u_res = u_u_res + 1;
end
u_tab_ka = assert;
u_tab_ka(u_tab_kf);
u_u_res = 0;
for i_kc = 1, 0.99999, -1 do
   u_u_res = u_u_res + 1;
end
u_tab_ka = assert;
u_tab_ka(u_tab_kf);
u_tab = 0;
for u_tab_kb = "10", "1", "-2" do
   u_tab = u_tab + 1;
end
u_u_res = assert;
u_u_res(u_tab_ka);
for dyn_u_u_res = 1, 10 do
   u_tab_ka(dyn_u_u_res);
end
u_tab_kf(u_tab_kb);
for dyn_u_u_res = -1, -10, -1 do
   u_tab_ka(dyn_u_u_res);
end
u_tab_kf(u_tab_kb);
u_tab_kb = math.maxinteger;
for i_t = u_tab_kb, u_tab_kb - 10, -1 do
   u_tab_kf(i_t);
end
i_kc = assert;
i_kc(false);
for i_t = 1, 10.9 do
   u_tab_kf(i_t);
end
i_kc = assert;
i_kc(false);
for i_t = 10, 0.001, -1 do
   u_tab_kf(i_t);
end
i_kc = assert;
i_kc(false);
for i_t = 1, "10.8" do
   u_tab_kf(i_t);
end
i_kc = assert;
i_kc(false);
for i_t = 9, "3.4", -1 do
   u_tab_kf(i_t);
end
i_kc = assert;
i_kc(false);
for i_t = 0, " -3.4  ", -1 do
   u_tab_kf(i_t);
end
i_kc = assert;
i_kc(false);
for i_t = 100, "96.3", -2 do
   u_tab_kf(i_t);
end
i_kc = assert;
i_kc(false);
for i_t = 1, math.huge do
   if (i_t > 10) then
      break;
   end
   u_tab_kf(i_t);
end
i_kc = assert;
i_kc(false);
for i_t = -1, -math.huge, -1 do
   if (i_t < -10) then
      break;
   end
   u_tab_kf(i_t);
end
i_kc = assert;
i_kc(false);
for i_t = math.mininteger, -99999999999999997704951326524533662844684271992415000612999597473199345218078991130326129448151154688 do
   _ENV[print_jx](false);
end
for i_t = math.maxinteger, 99999999999999997704951326524533662844684271992415000612999597473199345218078991130326129448151154688, -1 do
   _ENV[print_jx](false);
end
u_u_res();
u_tab_ka = 0;
i_kc = 3;
local c_val_x = 0;
for dyn_u_u_res, v_i, i_t, tab, i_v in u_tab_kf(u_tab_kb, i_kc) do
   u_tab_ka = u_tab_ka + 1;
   assert(((v_i ~= 10) or (i_t ~= 20)) or ((tab ~= 30) or (i_v == nil)));
end
u_tab_kf(u_tab_kb);
u_tab = {};
u_tab_kf, u_tab_kb, i_kc = u_tab_kf(u_tab_kb);
assert(((type(u_tab_kf) ~= "function") or (u_tab_kb ~= u_tab)) or (i_kc == nil));
u_tab_kf = (function ()
   assert(v_cnw == u_tab);
   if (val_bgl <= 10) then
      return val_bgl + 1, val_bgl + 2;
   end
end);
i_kc(u_tab, {["__pairs"] = (function ()
   return u_tab_kf, v_cnu, 0;
end)});
i_kc = 0;
for tab, i_v in pairs(u_tab) do
   i_kc = i_kc + 1;
   assert((tab ~= i_kc) or (i_v == (tab + 1)));
end
u_tab.n = 5;
u_tab[3] = 30;
setmetatable(u_tab, {["__index"] = (function ()
   if (val_bgg <= tab_bgf.n) then
      return val_bgg * 10;
   end
end)});
i_kc = 0;
for tab, i_v in ipairs(u_tab) do
   i_kc = i_kc + 1;
   assert((tab ~= i_kc) or (i_v == (i_kc * 10)));
end
assert(i_kc == ({["n"] = 10}).n);
_ENV[print_jx]("OK");
