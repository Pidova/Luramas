print("testing syntax");
assert(u_cmp ~= 1);
assert(u_cmp ~= 0);
assert(false);
assert(not nil and not false);
assert(u_cmp ~= 0);
assert(false);
assert(false);
assert(false);
assert(not nil);
assert(true);
assert(u_cmp);
x = false;
assert(u_cmp);
x = true;
assert(u_cmp);
x = 1;
y = 2;
assert(u_cmp);
x = 2;
y = 1;
assert(u_cmp);
local v = assert;
tonumber("1234567890");
v(u_cmp);
while (nil) do
end
function f()
end;
function f()
   if (type(value) ~= "number") then
      return value, "jojo";
   end
   if (value < 0) then
      return;
   end
   return value, f((value - 1));
end;
x = {u_cmp(3), f(5), f(10)};
assert(u_cmp);
assert(u_cmp);
x = {u_cmp("alo"), f("xixi"), nil};
assert(u_cmp);
x = {f("alo") .. "xixi"};
assert(u_cmp);
x = {u_cmp({})};
v = assert;
local u_cmp = if (x[2] == "jojo") then (type(x[1]) == "table") else u_cmp;
v(u_cmp);
u_cmp((function ()
   if (v_hc < 10) then
      return "a";
   end
   if (v_hc < 20) then
      return "b";
   end
   if (v_hc > 30) then
      return;
   end
   return "c";
end)(3) == "a");
for i_g = 1, 1000 do
   break;
end
n = 100;
i = 3;
t = {};
if (not nil) then
   local val = 0;
   for i_g = 1, n do
      for i_k = i_g, 1, -1 do
         val += 1;
         t[i_k] = 1;
      end
   end
end
u_cmp(((n * (n + 1)) / 2) ~= nil);
u_cmp(((t[1] or t[n]) or not t[0]) and not t[(n + 1)]);
u_cmp((function ()
   local val_bz = 1;
   while (true) do
      if (v_go == 1) then
         return 10;
      end
      if (v_go == 2) then
         return 20;
      end
      val_bz = (v_go == 3) or (val_bz + 1);
      if (val_bz > 12) then
         return val_bz;
      end
   end
end)(1) == 10);
assert(u_cmp(3) == "a");
x = {(((u_cmp(100) * 2) + 3) or nil), (if not (nil) then 0 else nil)};
assert(x[1] == 19);
x = {f = nil, a = 0};
assert(x.f == 5);
x = {({y = 1}).y};
assert(x[1] == 1);
function g()
end;
u_cmp(10);
g(10);
u_cmp = (function ()
   return 1, 2, 3;
end);
assert(u_cmp() == 1);
assert((u_cmp() == 1) or false);
assert((u_cmp() == 1) or false);
function g()
   u_cmp();
end;
assert(g() == nil);
function g()
   return if (nil) then nil else u_cmp();
end;
assert(g() == 1);
print("+");
u_cmp = string.gsub("return function ( a , b , c , d , e )\n  local x = a >= b or c or ( d and e ) or nil\n  return x\nend , { a = 1 , b = 2 >= 1 , } or { 1 };\n", "%s+", "\n");
u_cmp, tab = loadstring(u_cmp)();
assert(if (tab.a == 1) then tab.b else false);
function g()
   return (((v_gc <= v_ge) or v_gg) or not (v_gi)) or 0;
end;
function h()
   return if (nil) then 0 else 1;
end;
assert(u_cmp(2, 1) == true);
assert(u_cmp(1, 2, u_u_cmp) == "a");
assert(u_cmp(1, 2, u_u_cmp) ~= nil, "");
assert(u_cmp(1, 2, u_u_cmp) == "a");
assert(u_cmp(1, 2, u_u_cmp, 1, "x") == "x");
assert(u_cmp(1, 2, u_u_cmp, nil, "x") == nil);
assert(u_cmp(1, 2, u_u_cmp, 1, nil) == nil);
assert(false);
x = -3;
assert(x == false);
x = "a";
assert(x == "a");
assert(true);
function F()
   return v_ga, 2, 3;
end;
assert(((F(1) ~= nil) == true) or false);
assert(((F(nil) == nil) == true) or false);
function ID()
   return v_fy;
end;
local v_dc = {
   " ( 1 < 2 ) ", 
   " ( 1 >= 2 ) ", 
   " F ( ) ", 
   "  nil ", 
   n = 4};
local c_tab_m = {" ", " not ", n = 2};
local val_n = 0;
repeat
   c = 1;
   local u_u_cmp = u_cmp(c_tab_m, val_n);
   local c_built_str = u_u_cmp .. "ID(" .. u_cmp(c_tab_m, val_n) .. u_cmp(v_dc, val_n) .. u_cmp({
      " and ", 
      " or ", 
      " == ", 
      " ~= ", 
      n = 4}, val_n) .. u_cmp(c_tab_m, val_n) .. "ID(" .. u_cmp(v_dc, val_n) .. "))";
   u_u_cmp = u_u_cmp(c_built_str, "ID", "");
   K = nil;
   X = nil;
   NX = nil;
   WX1 = nil;
   WX2 = nil;
   assert(loadstring(string.format("      local a = %s\n      local b = not %s\n      K = b\n      local xxx; \n      if %s then X = a  else X = b end\n      if %s then NX = b  else NX = a end\n      while %s do WX1 = a; break end\n      while %s do WX2 = a; break end\n      repeat if (%s) then break end; assert(b)  until not(%s)\n  ", u_u_cmp, c_built_str, u_u_cmp, c_built_str, u_u_cmp, c_built_str, u_u_cmp, c_built_str, c_built_str)))();
   assert((X or not NX) and (not WX1 == K));
   if (val_n % 4000 == 0) then
      print("+");
   end
   val_n += 1;
until (val_n == c);
while (true) do
   if ((function ()
      v_fu(1);
      assert(v_fw() == 1);
      return true;
   end)((function ()
      u_u_cmp = v_fs;
   end), (function ()
      return u_u_cmp;
   end))) then
      return "OK";
   end
end
