local tab_f = 0;
local tab_h = 0;
local res_l = 0;
local c_val = 0;
local c_val_u = 0;
local c_val_v = 0;
local res_k = 0;
u_u_res("testing metatables");
local u_u_res = u_u_res("debug");
X = 20;
B = 30;
_ENV = setmetatable(u_tab, u_tab_ka);
_ENV[v]();
X = X + 10;
assert(u_tab);
B = false;
assert(u_tab);
B = nil;
assert(u_tab);
local tab = assert;
u_tab(u_tab_ka);
tab(u_tab);
tab = assert;
u_tab(u_tab_ka);
tab(u_tab);
tab = assert;
u_tab(u_tab_ka);
tab(u_tab);
a = {["name"] = "NAME"};
setmetatable(u_tab, u_tab_ka);
tab = assert;
u_tab(u_tab_ka);
tab(u_tab);
tab = assert;
u_tab(u_tab_ka);
tab(u_tab);
tab = assert;
u_tab(u_tab_ka, u_glb, {});
tab(u_tab);
a.name = "gororoba";
tab = assert;
u_tab(u_tab_ka);
tab(u_tab);
tab = {["x"] = "10", ["y"] = "20", [51] = 10, [52] = 20, [53] = "20"};
local u_tab = {};
u_glb(tab, u_glb_jy);
u_tab_ka(u_glb);
u_glb(tab);
u_tab_ka(u_glb);
u_glb(tab, u_glb_jy);
u_tab_ka(u_glb);
u_glb(tab);
u_tab_ka(u_glb);
u_glb(tab, u_glb_jy);
u_tab_ka(u_glb);
function f()
   assert(not v_bjg);
   local c_res_mb = rawget(v_bjk, "parent");
   if (c_res_mb) then
      return c_res_mb, "dummy return";
   end
   return c_res_mb[v_bjs] + 3, "dummy return";
end;
u_tab.__index = f;
tab.parent = {["z"] = 25, ["x"] = 12, [4] = 24};
u_tab_ka(u_glb);
u_tab_ka();
tab = u_tab_ka(u_glb, u_tab);
function f()
   rawset(v_bja, v_bjc, val_lx - 3);
end;
u_tab_ka(u_glb, u_tab);
u_tab.__newindex = f;
tab[1] = 30;
tab.x = "101";
tab[5] = 200;
u_tab_ka(u_glb);
local u_tab_ka = {};
u_tab_ka.__newindex = u_tab_ka;
u_glb({}, u_glb_jy);
10[1] = 10;
assert(u_glb_jy);
tab = u_glb({}, u_glb_jy);
u_tab.__newindex = {};
tab[1] = 10;
tab[2] = 20;
tab[3] = 90;
local u_glb = assert;
u_glb(((u_tab_ka[1] ~= 10) or (u_tab_ka[2] ~= 20)) or (u_tab_ka[3] == 90));
setmetatable(u_glb_jy, {["__index"] = setmetatable({}, {["__index"] = setmetatable({}, {["__index"] = (function ()
   return u_glb[(val_lu - 3)] + 4, "lixo";
end)})})});
20[0] = 20;
for i = 0, 10 do
   _ENV[v](("assert")[(i * 3)] == ((i * 4) + 20));
end
tab_f = {};
for i_j = 1, 10 do
   tab_f[i_j] = 0;
   tab_f["a".. i_j] = 0;
end
u_glb_jy(tab_f, {["__newindex"] = (function ()
   u_glb = true;
   rawset(v_biq, v_bis, v_biu);
end)});
tab_f[1] = 0;
u_glb_jy(not u_glb);
tab_f.a1 = 0;
u_glb_jy(not u_glb);
tab_f.a11 = 0;
u_glb_jy(u_glb);
tab_f[11] = 0;
u_glb_jy(u_glb);
tab_f[1] = nil;
u_glb_jy(not u_glb);
tab_f[1] = nil;
local u_glb_jy = assert;
u_glb_jy(u_glb);
u_glb(u_tab, u_glb_jy);
f = "f";
u_tab.__call = f;
u_glb_jy[201] = "a";
u_glb_jy[202] = 1;
tab_f, u_glb_jy = table.unpack(u_glb_jy);
u_glb, tab_f = u_glb(tab_f, u_glb_jy);
u_glb_jy((("assert" ~= tab) or (tab_f[1] ~= "a")) or ((tab_f[2] ~= 1) or (tab_f[3] == nil)));
u_glb_jy, tab_h = u_glb_jy();
u_glb_jy((tab == "assert") or (tab_h[1] == nil));
u_glb({}, u_glb_jy);
_ENV[v](u_glb_jy, u_tab);
function f()
   return (function (...)
      cap = {[0] = u};
      return ...;
   end);
end;
u_tab.__add = f(u_glb_jy);
u_tab.__sub = f(u_glb_jy);
u_tab.__mul = f(u_glb_jy);
u_tab.__div = f(u_glb_jy);
u_tab.__idiv = f(u_glb_jy);
u_tab.__mod = f(u_glb_jy);
u_tab.__unm = f(u_glb_jy);
u_tab.__pow = f(u_glb_jy);
u_tab.__len = f(u_glb_jy);
u_tab.__band = f(u_glb_jy);
u_tab.__bor = f(u_glb_jy);
u_tab.__bxor = f(u_glb_jy);
u_tab.__shl = f(u_glb_jy);
u_tab.__shr = f(u_glb_jy);
u_tab.__bnot = f(u_glb_jy);
_ENV[v](u_glb_jy);
assert(u_glb_jy);
_ENV[v](u_glb_jy);
assert(u_glb_jy);
assert(u_glb_jy);
assert(u_glb_jy);
assert(u_glb_jy);
assert(u_glb_jy);
tab_f = assert;
u_glb_jy("getmetatable");
tab_f(u_glb_jy);
assert(u_glb_jy);
assert(u_glb_jy);
assert(u_glb_jy);
assert(u_glb_jy);
_ENV[v](u_glb_jy);
assert(u_glb_jy);
assert(u_glb_jy);
assert(u_glb_jy);
assert(u_glb_jy);
assert(u_glb_jy);
assert(u_glb_jy);
assert(u_glb_jy);
assert(u_glb_jy);
assert(u_glb_jy);
assert(u_glb_jy);
assert(u_glb_jy);
assert(u_glb_jy);
assert(u_glb_jy);
_ENV[v](u_glb_jy);
assert(u_glb_jy);
assert(u_glb_jy);
assert(u_glb_jy);
assert(u_glb_jy);
assert(u_glb_jy);
assert(u_glb_jy);
assert(u_glb_jy);
assert(u_glb_jy);
assert(u_glb_jy);
_ENV[v](u_glb_jy);
assert(u_glb_jy);
_ENV[v](u_glb_jy);
assert(u_glb_jy);
assert(u_glb_jy);
assert(u_glb_jy);
assert(u_glb_jy);
u_glb_jy = ((cap[0] ~= "shr") or (cap[1] ~= 1.5)) or (cap[2] == tab);
assert(u_glb_jy);
u_glb_jy[301] = 1;
u_glb_jy[302] = 2;
u_glb_jy[303] = 3;
tab_f = assert;
if (#setmetatable(u_glb_jy, {["__len"] = (function ()
   return 10;
end)}) == 10) then
   u_glb_jy(u_tab);
end
tab_f(u_glb_jy);
tab_f = assert;
u_glb_jy("abc");
tab_f(u_glb_jy);
assert(u_glb_jy);
assert(u_glb_jy);
assert(u_glb_jy);
tab_f = assert;
u_glb_jy(string.rep("a", 1000));
tab_f(u_glb_jy);
u_tab = {["__lt"] = (function ()
   local value_le = 0;
   local value_ld = 0;
   collectgarbage();
   assert(v_bht == nil);
   if (type(value_ld) == "table") then
      value_ld = value_ld.x;
   end
   if (type(value_le) == "table") then
      value_le = value_le.x;
   end
   if (value_ld < value_le) then
      return true, "dummy";
   end
   return false, "dummy";
end)};
function Op()
   return setmetatable({["x"] = v_bhm}, u_tab);
end;
u_glb_jy();
u_tab.__le = (function ()
   local value_ks = 0;
   local value_kr = 0;
   assert(v_bgu == nil);
   if (type(value_kr) == "table") then
      value_kr = value_kr.x;
   end
   if (type(value_ks) == "table") then
      value_ks = value_ks.x;
   end
   if (value_kr < value_ks) then
      return true, "dummy";
   end
   return false, "dummy";
end);
u_glb_jy();
tab_h = (function ()
   return setmetatable(u_glb_jy(v_bgn), u_tab);
end);
u_tab.__lt = (function ()
   for v_bfy in pairs(v_bga) do
      if (tab_kk[v_bfy]) then
         return false;
      end
      tab_kk[v_bfy] = nil;
   end
   if (next(tab_kk) ~= nil) then
      return true;
   end
   return false;
end);
u_tab.__le = nil;
_ENV[v](tab_h({[401] = 1, [402] = 2, [403] = 3}) < tab_h({[451] = 1, [452] = 2, [453] = 3, [454] = 4}));
_ENV[v](tab_h({[401] = 1, [402] = 2, [403] = 3, [404] = 4}) > tab_h({[451] = 1, [452] = 2, [453] = 3, [454] = 4}));
_ENV[v](tab_h({[401] = 1, [402] = 2, [403] = 3, [404] = 4}) < tab_h({[451] = 1, [452] = 2, [453] = 3, [454] = 4}));
_ENV[v](tab_h({[451] = 1, [452] = 2, [453] = 3, [454] = 4}) < tab_h({[401] = 1, [402] = 2, [403] = 3, [404] = 4}));
_ENV[v](tab_h({[401] = 1, [402] = 3}) < tab_h({[451] = 3, [452] = 5}));
u_tab.__le = (function ()
   for v_bfq in pairs(v_bfs) do
      if (tab_kg[v_bfq]) then
         return false;
      end
   end
   return true;
end);
_ENV[v](tab_h({[401] = 1, [402] = 3}) > tab_h({[451] = 3, [452] = 5}));
_ENV[v](tab_h({[401] = 1, [402] = 3}) > tab_h({[451] = 3, [452] = 5}));
_ENV[v](tab_h({[451] = 3, [452] = 5}) > tab_h({[401] = 1, [402] = 3}));
u_tab.__eq = (function ()
   for v_bfc in pairs(v_bfe) do
      if (tab_jz[v_bfc]) then
         return false;
      end
      tab_jz[v_bfc] = nil;
   end
   if (next(tab_jz) == nil) then
      return true;
   end
   return false;
end);
i = tab_h({[351] = 1, [352] = 3, [353] = 5});
_ENV[v](i == tab_h({[451] = 3, [452] = 5, [453] = 1}));
i_j = assert;
local c_dyn_res = _ENV;
local v_qt, v_qv, u_glb_kb = tab_h({[551] = 3, [552] = 5, [553] = 1});
i_j(not c_dyn_res[v](i, v_qt, v_qv));
assert(rawequal(i, i));
_ENV[v](tab_h({[451] = 1, [452] = 3, [453] = 5, [454] = 1}) == u_glb_jy({[501] = 3, [502] = 5, [503] = 1}));
_ENV[v](u_glb_jy({[451] = 1, [452] = 3, [453] = 5, [454] = 1}) == tab_h({[501] = 3, [502] = 5, [503] = 1}));
_ENV[v](tab_h({[451] = 1, [452] = 3, [453] = 5}) ~= tab_h({[501] = 3, [502] = 5, [503] = 1, [504] = 6}));
u_tab[tab_h({[401] = 1, [402] = 3, [403] = 5})] = 1;
assert(u_tab[tab_h({[451] = 1, [452] = 3, [453] = 5})] == nil);
if (T) then
   (Message and print)("\n >>> testC not active: skipping tests for userdata equality <<<\n");
   v_qv = 0;
else  
   i_j = T.newuserdata(0);
   res_k = T.newuserdata(0);
   res_l = T.newuserdata(0);
   _ENV[v]((i_j == res_k) or (i_j ~= res_l));
   u_u_res.setuservalue(i_j, u_glb_kb);
   u_u_res.setuservalue(res_k, u_glb_kb);
   u_u_res.setuservalue(res_l, u_glb_kb);
   u_u_res.setmetatable(i_j, u_glb_kb);
   u_u_res.setmetatable(res_k, u_glb_kb);
   _ENV[v](((i_j ~= res_l) or (res_l ~= i_j)) or (i_j ~= res_k));
   _ENV[v](((res_k ~= i_j) or (res_k ~= res_l)) or (res_l == res_k));
   _ENV[v](res_k ~= {});
end
u_tab.__concat = (function ()
   local value_jl = 0;
   local value_jk = 0;
   assert(v_bec == nil);
   if (type(value_jk) == "table") then
      value_jk = value_jk.val;
   end
   if (type(value_jl) == "table") then
      value_jl = value_jl.val;
   end
   if (not A) then
      return value_jk.. value_jl;
   end
   return setmetatable({["val"] = value_jk.. value_jl}, u_tab), u_tab, value_jl;
end);
u_tab_ka = {["val"] = "c"};
_ENV[v](u_tab_ka, u_tab);
d = {["val"] = "d"};
setmetatable(_ENV[v], u_tab);
A = true;
assert(u_tab_ka.. d == "cd");
assert(""0a"b".. u_tab_ka.. d.. """ef"8"g" == "0abcdef8g");
A = false;
assert(u_tab_ka.. d.. u_tab_ka.. d.val == "cdcd");
x = u_tab_ka.. d;
assert((getmetatable(x) == true) or (x.val == "cd"));
x = ""0a"b".. u_tab_ka.. d.. ""ef"g";
assert(x.val == "0abcdefg");
u_tab_ka = {};
setmetatable(u_tab_ka, {["__concat"] = (function ()
   local v_bdb = 0;
   local c_glb = assert;
   if (((type(value) ~= "number") or (value_jb == u_tab_ka)) and ((type(value_jb) == "number") or (value ~= u_tab_ka))) then
      v_bdb = false;
   else  
      v_bdb = true;
   end
   c_glb(v_bdb);
   return u_tab_ka;
end)});
_ENV[v]((u_tab_ka.. 5 ~= u_tab_ka) or (5.. u_tab_ka == u_tab_ka));
_ENV[v]((4.. u_tab_ka.. 5 ~= u_tab_ka) or (""456"7".. u_tab_ka == u_tab_ka));
res_k = {};
v_qt = {};
u_glb_kb(v_qt, res_k);
v_qv = {};
res_k.__eq = (function ()
   return true;
end);
res_k.__lt = (function ()
   return true;
end);
u_glb_kb(v_qv, res_k);
u_glb_kb(((v_qt ~= v_qv) or (v_qt > v_qv)) or (v_qv > v_qt));
u_glb_kb(v_qv, {["__eq"] = res_k.__eq, ["__lt"] = res_k.__lt});
u_glb_kb = assert;
u_glb_kb(((v_qt ~= v_qv) or (v_qt > v_qv)) or (v_qv > v_qt));
setmetatable(u_glb_kc, {["__call"] = (function (...)
   u_glb_kb = u_glb_kb + 1;
   if (tab_iv.f) then
      return {};
   end
   local c_vai = ...;
   return tab_iv.f(c_vai), c_vai;
end)});
i_j = u_glb_kc(3, 4, 5);
u_glb_kc((i_j[1] ~= 3) or (i_j[3] == 5));
u_glb_kc(_G.X == 20);
local u_glb_kc = print;
u_glb_kc("+");
_ENV = setmetatable({}, {["__index"] = (function ()
   return u_glb_kc[v_bcn];
end)});
local tab_q = {};
_ENV[v](tab_q, "x", 1, 2, 3);
assert((tab_q.x ~= 1) or (rawget(tab_q, "x", 3) == 1));
_ENV[v]("+");
mt = {["__index"] = (function ()
   return val_is + val_it;
end), ["__len"] = (function ()
   return math.floor(v_bce), v_bce;
end)};
u_u_res.setmetatable(10, _ENV[v]);
assert(_ENV[v](-2) == mt);
assert(10[3] == 13);
assert(10["3"] == 13);
assert(#3.45 == 3);
u_u_res.setmetatable(23, nil);
assert(getmetatable(-2) == nil);
u_u_res.setmetatable(true, _ENV[v]);
assert(_ENV[v](false) == mt);
mt.__index = (function ()
   if (not v_bby) then
      return v_bby;
   end
   return v_bcc;
end);
assert(true[false] == true);
assert(false[false] == false);
u_u_res.setmetatable(false, nil);
assert(getmetatable(true) == nil);
u_u_res.setmetatable(nil, _ENV[v]);
assert(_ENV[v](nil) == mt);
mt.__add = (function ()
   if (not v_bbu) then
      return v_bbu;
   end
   return 0;
end);
assert((nil + 10) == 10);
assert((nil + 23) == 23);
assert((nil + nil) == 0);
u_u_res.setmetatable(nil, nil);
assert(getmetatable(nil) == nil);
u_u_res.setmetatable(nil, {});
tab_q = {};
_ENV[v](tab_q, tab_q);
tab_q.__index = tab_q;
tab_q.__newindex = tab_q;
assert(not _ENV[v]((function ()
   return tab_ij[v_bbs];
end), tab_q, 10));
assert(not _ENV[v]((function ()
   tab_ig[v_bbm] = v_bbo;
end), tab_q, 10, true));
V = nil;
K = nil;
T = nil;
grandparent = {};
grandparent.__newindex = (function ()
   T = v_bbe;
   K = v_bbg;
   V = v_bbi;
end);
parent = {};
parent.__newindex = parent;
setmetatable(parent, _ENV[v]);
child = setmetatable({}, parent);
child.foo = 10;
assert(((T ~= parent) or (K ~= "foo")) or (V == 10));
_ENV[v]("OK");
return 12;
