print("testing vectors");
local c_cmp = pcall((function ()
   return vector(0, 0, 0).w;
end)) or 3;
function ecall(...)
   local c_success, c_result = pcall(function, ...);
   assert(not c_success);
   return c_result:sub(((c_result:find(": ") or -1) + 2), #c_result);
end;
assert(vector(1, 2, 3) == vector(1, 2, 3));
assert(vector(0, 1, 2) == vector(-0, 1, 2));
assert(vector(1, 2, 3) ~= vector(1, 2, 4));
local tab = assert;
local res_c = rawequal;
local res = vector(1, 2, 3);
local u_res, u_func, u_res_jx = vector(1, 2, 3);
tab(res_c(res, u_res));
tab = assert;
res_c = rawequal;
res = vector(0, 1, 2);
u_res, u_func, u_res_jx = vector(-0, 1, 2);
tab(res_c(res, u_res));
tab = assert;
res = rawequal;
u_res = vector(1, 2, 3);
u_func, u_res_jx = vector(1, 2, 4);
tab(not res(u_res, u_func));
tab = assert;
res = type;
u_res, u_func, u_res_jx = vector(1, 2, 3);
tab(res(u_res) == "vector");
if (c_cmp == 4) then
   tab = assert;
   res = tostring;
   u_res, u_func, u_res_jx = vector(1, 2, 3, 4);
   tab(res(u_res) == "1, 2, 3, 4");
   tab = assert;
   res = tostring;
   u_res, u_func, u_res_jx = vector(-1, 2, 0.5, 0);
   tab(res(u_res) == "-1, 2, 0.5, 0");
else  
   tab = assert;
   res = tostring;
   u_res, u_func, u_res_jx = vector(1, 2, 3);
   tab(res(u_res) == "1, 2, 3");
   tab = assert;
   res = tostring;
   u_res, u_func, u_res_jx = vector(-1, 2, 0.5);
   tab(res(u_res) == "-1, 2, 0.5");
end
tab = {[vector(1, 2, 3)] = 42};
assert(tab[vector(1, 2, 3)] == 42);
assert(tab[vector(1, 2, 4)] == nil);
assert(tab[vector(0, 0, 0)] == nil);
tab[vector(0, 0, 0)] = "hello";
assert(tab[vector(0, 0, 0)] == "hello");
assert(tab[vector(0, -0, 0)] == "hello");
assert((vector(1, 2, 4) + vector(8, 16, 24)) == vector(9, 18, 28));
assert((vector(1, 2, 4) - vector(8, 16, 24)) == vector(-7, -14, -20));
res_c = 1 / "8";
assert((vector(1, 2, 4) * vector(8, 16, 24)) == vector(8, 32, 96));
assert((vector(1, 2, 4) * 8) == vector(8, 16, 32));
assert((vector(1, 2, 4) * (1 / res_c)) == vector(8, 16, 32));
assert((vector(8, 16, 24) * 8) == vector(64, 128, 192));
assert((vector(1, 2, 4) * "8") == vector(8, 16, 32));
assert(("8" * vector(8, 16, 24)) == vector(64, 128, 192));
assert((vector(1, 2, 4) * -0.125) == vector(-0.125, -0.25, -0.5));
assert((vector(1, 2, 4) * -0.125) == vector(-0.125, -0.25, -0.5));
assert((vector(1, 2, 4) * 100) == vector(100, 200, 400));
assert((vector(1, 2, 4) * 100) == vector(100, 200, 400));
if (c_cmp == 4) then
   assert((vector(1, 2, 4, 8) / vector(8, 16, 24, 32)) == vector(0, 0, 0, 0));
   assert((8 / vector(8, 16, 24, 32)) == vector(1, 0, 0, 0));
   assert(("8" / vector(8, 16, 24, 32)) == vector(1, 0, 0, 0));
else  
   assert((vector(1, 2, 4) / vector(8, 16, 24, 1)) == vector(0, 0, 0));
   assert((8 / vector(8, 16, 24)) == vector(1, 0, 0));
   assert(("8" / vector(8, 16, 24)) == vector(1, 0, 0));
end
assert((vector(1, 2, 4) / 8) == vector(0, 0, 0));
assert((vector(1, 2, 4) / (1 / res_c)) == vector(0, 0, 0));
assert((vector(1, 2, 4) / "8") == vector(0, 0, 0));
assert(-vector(1, 2, 4) == vector(-1, -2, -4));
assert((vector(1, 3, 5) // 2) == vector(0, 1, 2));
assert((vector(1, 3, 5) // res_c) == vector(8, 24, 40));
if (c_cmp == 4) then
   assert((10 // vector(1, 2, 3, 4)) == vector(10, 5, 3, 2));
   assert((vector(10, 9, 8, 7) // vector(1, 2, 3, 4)) == vector(10, 4, 2, 1));
else  
   assert((10 // vector(1, 2, 3)) == vector(10, 5, 3));
   assert((vector(10, 9, 8) // vector(1, 2, 3)) == vector(10, 4, 2));
end
res = vector((0 / 0), (0 / 0), (0 / 0));
assert(false);
assert(vector(1, 2, 2).Magnitude == 3);
assert(vector(0, 0, 0).Dot(vector(1, 2, 4), vector(5, 6, 7)) == 45);
assert(vector(2, 0, 0).Unit == vector(1, 0, 0));
assert(vector(1, 2, 4):Dot(vector(5, 6, 7)) == 45);
assert(ecall((function ()
   vector(1, 2, 4):Dot();
end)) == "missing argument #2 (vector expected)");
assert(ecall((function ()
   vector(1, 2, 4):Dot("a");
end)) == "invalid argument #2 (vector expected, got string)");
u_res = (function ()
   return v_em:Dot(v_eo);
end);
u_func = (function ()
   return v:Dot(v_ek);
end);
u_res_jx = vector(1, 2, 4);
assert(u_res(u_res_jx, vector(5, 6, 7)) == 45);
assert(u_func(u_res_jx, vector(5, 6, 7)) == 45);
assert(ecall((function ()
   u_res(u_res_jx, "a");
end)) == "invalid argument #2 (vector expected, got string)");
assert(ecall((function ()
   u_func(u_res_jx, "a");
end)) == "invalid argument #2 (vector expected, got string)");
assert(select("#", u_res(u_res_jx, vector(5, 6, 7))) == 1);
assert(select("#", u_func(u_res_jx, vector(5, 6, 7))) == 1);
assert(pcall((function ()
   local c_tab_a_l = {[vector((0 / 0), 2, 3)] = 1};
end)) == false);
assert(pcall((function ()
   local c_tab_a = {[vector(1, (0 / 0), 3)] = 1};
end)) == false);
assert(pcall((function ()
   local c_tab_a_m = {[vector(1, 2, (0 / 0))] = 1};
end)) == false);
assert(pcall((function ()
   rawset({}, vector((0 / 0), 2, 3), 1);
end)) == false);
assert(vector(1, 0, 0):Cross(vector(0, 1, 0)) == vector(0, 0, 1));
assert(vector(0, 1, 0):Cross(vector(1, 0, 0)) == vector(0, 0, -1));
assert(vector(1, 2, 4) == vector("1", "2", "4"));
assert(vector(1, 2, 3).x == 1);
assert(vector(1, 2, 3).X == 1);
assert(vector(1, 2, 3).y == 2);
assert(vector(1, 2, 3).Y == 2);
assert(vector(1, 2, 3).z == 3);
assert(vector(1, 2, 3).Z == 3);
if (c_cmp == 4) then
   assert(vector(1, 2, 3, 4).w == 4);
   assert(vector(1, 2, 3, 4).W == 4);
end
local tab_h = {};
for c_i = 1, 16384 do
   tab_h[vector(0, 0, c_i)] = true;
end
