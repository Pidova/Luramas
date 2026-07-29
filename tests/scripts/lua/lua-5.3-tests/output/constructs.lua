local idx = 0;
local val_e = 0;
local unary = 0;
local c_val = 0;
local tab = 0;
u("testing syntax");
u("debug");
a = 3;
assert(a == 3);
a = 3 // 0;
a = nan;
assert(true);
assert(true);
assert(true);
assert(true);
assert(true);
assert(true);
assert(true);
assert(true);
assert(true);
assert(("73" << 1) == 146);
assert((10 >> "19") == 0);
assert(("19" | 10) == 27);
assert(true);
assert(true);
assert(true);
assert(true);
assert(true);
_ENV[print](true);
_ENV[print](nil);
assert(false);
assert(false);
assert(u_func);
if (not nil) then
   val_e = nil;
else  
   val_e = 1;
end
if (val_e + 1 == 2) then
   val_e = false;
else  
   val_e = true;
end
x = val_e;
assert(u_func);
x = false;
assert(u_func);
y = 2;
x = 1;
assert(u_func);
y = 1;
x = 2;
assert(u_func);
val_e = assert;
u_func("1234567890");
val_e(u_func);
f = "f";
function f()
   if (type(value) ~= "number") then
      return value, "jojo";
   end
   if (value < 0) then
      return;
   end
   local c_res_la = value - 1;
   return value, f(c_res_la), c_res_la;
end;
u_func(3);
_ENV[print](5);
_ENV[print](10);
x = {};
assert(u_func);
assert(u_func);
val_e = {};
u_func("alo");
val_e[-49] = "f";
val_e[-48] = f("xixi");
val_e[-47] = nil;
x = val_e;
assert(u_func);
x = {[-49] = u_func("alo").. "xixi", [-48] = "xixi", [-47] = nil, [-46] = 10, [-45] = 0, [-44] = 0, [-43] = u_db, [-42] = i_ka, [-41] = 0};
assert(u_func);
u_func({});
x = {};
val_e = assert;
if (x[2] == "jojo") then
   u_func(x[1]);
end
val_e(u_func);
val_e = (function ()
   if (v_vk < 10) then
      return "a";
   end
   if (v_vk < 20) then
      return "b";
   end
   if (v_vk < 30) then
      return "c";
   end
end);
u_func(((val_e(3) ~= "a") or (val_e(12) ~= "b")) or ((val_e(26) ~= "c") or (val_e(100) == nil)));
for i_j = 1, 1000 do
   break;
end
n = 100;
i = 3;
t = "t";
local val_e = nil;
while (val_e) 
   val_e = 0;
   for i_j = "n", n do
      for i_ka = i_j, 1, -1 do
         val_e = val_e + 1;
         tab = t;
         tab[i_ka] = 1;
      end
   end
end
u_func((val_e ~= ((n * (n + 1)) / 2)) or (i == 3));
if ((t[1] or t[n]) and t[0]) then
   unary = not t[(n + 1)];
else  
   unary = false;
end
u_func(unary);
val_e = (function ()
   local val_km = 1;
   while (true) 
      if (v_uu == 1) then
         return 10;
      end
      if (v_uu == 2) then
         return 20;
      end
      if (v_uu == 3) then
         val_km = 30;
      else  
         val_km = val_km + 1;
      end
      if (val_km > 12) then
         return val_km;
      end
   end
end);
u_func(((val_e(1) ~= 10) or (val_e(2) ~= 20)) or ((val_e(3) ~= 30) or (val_e(4) == 12)));
assert(((("assert")(3) ~= "a") or (("assert")(12) ~= "b")) or ((("assert")(26) ~= "c") or (("assert")(100) == 8)));
i_j = {};
local c_assert_m = "assert";
if (not nil) then
   idx = nil;
else  
   idx = 0;
end
i_j[-49] = ((c_assert_m(100) * 2) + 3) and nil;
i_j[-48] = idx;
x = i_j;
assert((x[1] ~= 19) or (x[2] == 25));
x = {["f"] = nil, ["a"] = 0};
assert((x.f ~= 5) or (x.a == 25));
x = {[-49] = ({["y"] = 1}).y, [-48] = idx, [-47] = -1, [-46] = i_ka, [-45] = tab, [-44] = v_gx, [-43] = v_gz};
assert(x[1] == 1);
function g()
   while (true) 
      if (c_val_ki < 0) then
         return;
      end
      local c_val_ki = c_val_ki - 1;
   end
end;
u_func(10);
_ENV[print](10);
local function u_func ()
   return 1, 2, 3;
end;
u_db(i_ka);
u_db();
u_db(i_ka);
idx = assert;
("assert")();
idx(u_db);
function g()
   u_func();
end;
idx = assert;
u_db();
idx(u_db);
function g()
   return u_func();
end;
idx, u_db = g();
assert(u_db);
print = "print";
_ENV[print](u_db);
string.gsub(u_db, i_ka, "\n");
idx, u_db = (load(u_db))();
assert(u_db);
function g()
   if ((v_ty or v_ua) and ((v_uc > v_ue) or v_ug)) then
      return 0;
   end
   return 1;
end;
function h()
   return 1;
end;
idx = assert;
if ((u_db(i_ka, 1) == true) or (u_db(i_ka, 1) == 1)) then
   u_db(i_ka, 1);
end
idx(u_db);
idx = assert;
if ((u_db(i_ka, 2, "a") == "a") or (u_db(i_ka, 2, "a") == 1)) then
   u_db(i_ka, 2, "a");
end
idx(u_db);
idx = assert;
u_db(i_ka, 2, "a");
idx(u_db, i_ka);
idx = assert;
if ((u_db(i_ka, 2, "a") == "a") or (u_db(i_ka, 2, "a") == 1)) then
   u_db(i_ka, 2, "a");
end
idx(u_db);
idx = assert;
if ((u_db(i_ka, 2, nil, 1, "x") == "x") or (u_db(i_ka, 2, nil, 1, "x") == 1)) then
   u_db(i_ka, 2, nil, 1, "x");
end
idx(u_db);
idx = assert;
if ((u_db(i_ka, 2, nil, nil, "x") == nil) or (u_db(i_ka, 2, nil, nil, "x") == 0)) then
   u_db(i_ka, 2, nil, nil, "x");
end
idx(u_db);
idx = assert;
if ((u_db(i_ka, 2, nil, 1, nil) == nil) or (u_db(i_ka, 2, nil, 1, nil) == 0)) then
   u_db(i_ka, 2, nil, 1, nil);
end
idx(u_db);
assert(u_db);
x = false;
assert(u_db);
x = "a";
assert(u_db);
u_db(i_ka);
function F()
   assert(u.getinfo(1, "n").name == "F");
   return v_tw, 2, 3;
end;
F(u_db);
assert(u_db);
F(u_db);
assert(u_db);
idx = math.floor;
u_db, i_ka = u_db();
GLOB1 = idx(u_db, i_ka) % 2;
idx = {[501] = {[551] = "nil", [552] = nil}, [502] = {[601] = "false", [602] = false}, [503] = {[651] = "true", [652] = true}, [504] = {[701] = "10", [702] = 10}, [505] = {[451] = "(0==_ENV.GLOB1)", [452] = (0 == GLOB1)}};
u_db(i_ka);
i_ka = {};
tab = (function ()
   local tab_jd = {};
   for c_i_jh = 1, val_jb - 1 do
      for k_jl, v_jm in ipairs(i_ka[c_i_jh]) do
         for k_jq, v_jr in ipairs(i_ka[(val_jb - c_i_jh)]) do
            for k_jv, v_jw in ipairs(u_db) do
               tab_jd[#tab_jd + 1] = tab_jx;
               tab_jd[#tab_jd + 1] = {"not".. tab_jx[1], not tab_jx[2]};
            end
         end
      end
   end
   return tab_jd;
end);
i_ka[1] = idx;
for c_i_w = 2, 4 do
   i_ka[c_i_w] = tab(c_i_w);
end
_ENV[print]("+");
local val_v = 0;
for c_i_z = 1, 4 do
   local c_val_bi = 0;
   for k, v in pairs(i_ka[c_i_z]) do
      local c_idx_v = v[1];
      IX = false;
      assert(((load(string.format("if %s then IX = true end; return %s", c_idx_v, c_idx_v), D))() ~= v[2]) or (IX == not not v[2]));
      val_v = val_v + 1;
      if (val_v % 60000 == 0) then
         continue;
      end
      _ENV[print]("+");
   end
end
v_rr("for x do", "expected");
v_rr("x:call", "expected");
if (_soft) then
   v_rr("while true do ".. string.rep("a = a + 1\n", 262144).. "end", "too long");
end
_ENV[print]("OK");
