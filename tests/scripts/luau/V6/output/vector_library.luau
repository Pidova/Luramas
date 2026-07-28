print("testing vector library");
pcall((function ()
   return vector(0, 0, 0).w;
end));
function ecall(...)
   local c_success, c_result = pcall(function, ...);
   assert(not c_success);
   return c_result:sub(((c_result:find(": ") or -1) + 2), #c_result);
end;
assert(vector.create(1, 2, 4) == vector.create("1", "2", "4"));
assert(vector.dot(vector.create(1, 2, 4), vector.create(5, 6, 7)) == 45);
assert(ecall((function ()
   vector.dot(vector.create(1, 2, 4));
end)) == "missing argument #2 to \'dot\' (vector expected)");
assert(ecall((function ()
   vector.dot(vector.create(1, 2, 4), 2);
end)) == "invalid argument #2 to \'dot\' (vector expected, got number)");
local function u_func ()
   return vector.dot(v_cm, v_co);
end;
local function u_func_jy ()
   return vector.dot(v_ci, v_ck);
end;
local u_res = vector.create(1, 2, 4);
assert(u_func(u_res, vector.create(5, 6, 7)) == 45);
assert(u_func_jy(u_res, vector.create(5, 6, 7)) == 45);
assert(ecall((function ()
   u_func(u_res, "a");
end)) == "invalid argument #2 to \'dot\' (vector expected, got string)");
assert(ecall((function ()
   u_func_jy(u_res, "a");
end)) == "invalid argument #2 to \'dot\' (vector expected, got string)");
assert(select("#", u_func(u_res, vector.create(5, 6, 7))) == 1);
assert(select("#", u_func_jy(u_res, vector.create(5, 6, 7))) == 1);
assert(vector.cross(vector.create(1, 0, 0), vector.create(0, 1, 0)) == vector.create(0, 0, 1));
assert(vector.cross(vector.create(0, 1, 0), vector.create(1, 0, 0)) == vector.create(0, 0, -1));
assert(select("#", vector.cross(vector.zero, vector.one)) == 1);
assert(vector.normalize(vector.create(0.5, 0, 0)) == vector.create(1, 0, 0));
assert(select("#", vector.normalize(vector.one)) == 1);
assert(vector.magnitude(vector.create(1, 2, 2)) == 3);
assert(select("#", vector.magnitude(vector.one)) == 1);
assert(vector.abs(-vector.one) == vector.one);
assert(vector.abs(vector.create(math.huge, 0, 0)).x == math.abs(math.huge));
assert(vector.abs(vector.create((0 / 0), 0, 0)).x ~= (0 / 0));
assert(select("#", vector.abs(vector.one)) == 1);
assert(vector.floor(vector.create(1, 2, 3)) == vector.create(1, 2, 3));
assert(vector.floor(vector.create(1.5, 2.4, 3)) == vector.create(1, 2, 3));
assert(vector.floor(vector.create(-1.5, -2.4, -3)) == vector.create(-2, -3, -3));
assert(select("#", vector.floor(vector.one)) == 1);
assert(vector.ceil(vector.create(1, 2, 3)) == vector.create(1, 2, 3));
assert(vector.ceil(vector.create(1.5, 2.4, 3)) == vector.create(2, 3, 3));
assert(vector.ceil(vector.create(-1.5, -2.4, -3)) == vector.create(-1, -2, -3));
assert(select("#", vector.ceil(vector.one)) == 1);
assert(vector.sign(vector.zero) == vector.zero);
assert(vector.sign(vector.one) == vector.one);
assert(vector.sign(vector.create(-10, 0, 10)) == vector.create(-1, 0, 1));
assert(vector.sign(vector.create(math.huge, 0, -math.huge)) == vector.create(1, 0, -1));
assert(vector.sign(vector.create(-0, 0, 0)).x == math.sign(-0));
assert(vector.sign(vector.create((0 / 0), 0, 0)).x == math.sign((0 / 0)));
assert(select("#", vector.sign(vector.one)) == 1);
assert(math.abs((vector.angle(vector.create(1, 2, 3), vector.create(4, 5, 6)) - 0.225726)) < 0.00001);
assert(select("#", vector.angle(vector.zero, vector.one)) == 1);
local tab = assert;
tab(select("#", vector.angle(vector.one, -vector.one, vector.zero)) == 1);
tab[1] = vector.create(-1.05, -0.04, 1.06);
tab[2] = vector.create(-0.75, 1.71, 1.29);
tab[3] = vector.create(1.94, 0.76, -0.93);
tab[4] = vector.create(0.02, -1.58, 0.2);
tab[5] = vector.create(1.64, -0.76, -0.73);
tab[6] = vector.create(-2.44, 0.66, 1.06);
tab[7] = vector.create(-2.61, 1.01, 0.5);
tab[8] = vector.create(1.21, -2.28, -0.45);
tab[9] = vector.create(-0.31, -0.12, 1.96);
tab[10] = vector.create(1.16, -0.07, -1.93);
local tab_f = {
   -105.1702, 
   -69.49491, 
   0, 
   -102.9083, 
   0, 
   0, 
   180, 
   -0.027976, 
   -90, 
   165.8858};
for k, v in tab_f do
   tab_f[k] = math.rad(tab_f[k]);
end
