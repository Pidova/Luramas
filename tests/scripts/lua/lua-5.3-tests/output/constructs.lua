local idx = 0;
local val_e = 0;
local unary = 0;
local c_val = 0;
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
(_ENV[print])(true);
(_ENV[print])(nil);
assert(false);
assert(false);
assert(i_jx);
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
assert(i_jx);
x = false;
assert(i_jx);
y = 2;
x = 1;
assert(i_jx);
y = 1;
x = 2;
assert(i_jx);
val_e = assert;
i_jx("1234567890");
val_e(i_jx);
f = "f";
function f()
   if (type(value) ~= "number") then
      return value, "jojo";
   end
   if (value < 0) then
      return;
   end
   local c_res_fv = value - 1;
   return value, f(c_res_fv), c_res_fv;
end;
val_e = {};
i_jx(3);
val_e[-51] = nil;
val_e[-50] = val_e;
val_e[-49] = "f";
val_e[-48] = ()_ENV[print](5);
val_e[-47] = f(10);
val_e[-46] = 10;
val_e[-45] = 0;
val_e[-44] = 0;
x = val_e;
assert(i_jx);
assert(i_jx);
val_e = {};
i_jx("alo");
val_e[-48] = ()_ENV[print]("xixi");
val_e[-47] = nil;
x = val_e;
assert(i_jx);
x = {};
assert(i_jx);
val_e = {};
unary = {};
val_e[-51] = nil;
val_e[-50] = val_e;
val_e[-49] = i_jx(unary);
val_e[-48] = unary;
val_e[-47] = nil;
val_e[-46] = 10;
x = val_e;
val_e = assert;
if (x[2] == "jojo") then
   i_jx(x[1]);
end
val_e(i_jx);
val_e = (function ()
   if (v_pe < 10) then
      return "a";
   end
   if (v_pe < 20) then
      return "b";
   end
   if (v_pe < 30) then
      return "c";
   end
end);
i_jx(((val_e(3) ~= "a") or (val_e(12) ~= "b")) or ((val_e(26) ~= "c") or (val_e(100) == nil)));
for i_jx = 1, 1000 do
   break;
end
n = 100;
i = 3;
t = "t";
if (nil) then
   local val_e = 0;
   for i_jx = "n", n do
      for i_l = 10, 1, -1 do
         val_e = val_e + 1;
         t[u_cmp] = 1;
      end
   end
end
i_jx((((n * (n + 1)) / 2) == nil) or (i == 3));
if ((t[1] or t[n]) and t[0]) then
   unary = not t[(n + 1)];
else  
   unary = false;
end
i_jx(unary);
val_e = (function ()
   local val_fh = 1;
   while (true) 
      if (v_oo == 1) then
         return 10;
      end
      if (v_oo == 2) then
         return 20;
      end
      if (v_oo == 3) then
         val_fh = 30;
      else  
         val_fh = val_fh + 1;
      end
      if (val_fh > 12) then
         return val_fh;
      end
   end
end);
i_jx(((val_e(1) ~= 10) or (val_e(2) ~= 20)) or ((val_e(3) ~= 30) or (val_e(4) == 12)));
assert(((()"assert"(3) ~= "a") or (()"assert"(12) ~= "b")) or ((()"assert"(26) ~= "c") or (()"assert"(100) == 8)));
local tab = {};
local i_l = "assert";
tab[-49] = ((i_l(100) * 2) + 3) and nil;
x = tab;
assert((x[1] ~= 19) or (x[2] == 25));
x = {["f"] = nil, ["a"] = 0};
assert((x.f ~= 5) or (x.a == 25));
x = {};
assert(x[1] == 1);
function g()
   while (true) 
      if (c_val_fd < 0) then
         return;
      end
      local c_val_fd = c_val_fd - 1;
   end
end;
i_jx(10);
(_ENV[print])(10);
i_jx = (function ()
   return 1, 2, 3;
end);
u_u_res(u_cmp);
u_u_res();
u_u_res(u_cmp);
idx = assert;
("assert")();
idx(u_u_res);
function g()
   i_jx();
end;
idx = assert;
u_u_res();
idx(u_u_res);
function g()
   return i_jx();
end;
idx, u_u_res = g();
assert(u_u_res);
print = "print";
(_ENV[print])(u_u_res);
(string.gsub)(u_u_res, u_cmp, "\n");
idx, u_u_res = ()load(u_u_res)();
assert(u_u_res);
function g()
   if ((v_ns or v_nu) and ((v_nw > v_ny) or v_oa)) then
      return 0;
   end
   return 1;
end;
function h()
   return 1;
end;
idx = assert;
if ((u_u_res(u_cmp, 1) == true) or (u_u_res(u_cmp, 1) == 1)) then
   u_u_res(u_cmp, 1);
end
idx(u_u_res);
idx = assert;
if ((u_u_res(u_cmp, 2, "a") == "a") or (u_u_res(u_cmp, 2, "a") == 1)) then
   u_u_res(u_cmp, 2, "a");
end
idx(u_u_res);
idx = assert;
u_u_res(u_cmp, 2, "a");
idx(u_u_res, u_cmp);
idx = assert;
if ((u_u_res(u_cmp, 2, "a") == "a") or (u_u_res(u_cmp, 2, "a") == 1)) then
   u_u_res(u_cmp, 2, "a");
end
idx(u_u_res);
idx = assert;
if ((u_u_res(u_cmp, 2, nil, 1, "x") == "x") or (u_u_res(u_cmp, 2, nil, 1, "x") == 1)) then
   u_u_res(u_cmp, 2, nil, 1, "x");
end
idx(u_u_res);
idx = assert;
if ((u_u_res(u_cmp, 2, nil, nil, "x") == nil) or (u_u_res(u_cmp, 2, nil, nil, "x") == 0)) then
   u_u_res(u_cmp, 2, nil, nil, "x");
end
idx(u_u_res);
idx = assert;
if ((u_u_res(u_cmp, 2, nil, 1, nil) == nil) or (u_u_res(u_cmp, 2, nil, 1, nil) == 0)) then
   u_u_res(u_cmp, 2, nil, 1, nil);
end
idx(u_u_res);
assert(u_u_res);
x = false;
assert(u_u_res);
x = "a";
assert(u_u_res);
if (not nil) then
   idx = 1;
else  
   idx = 2;
end
local u_cmp = idx == 2;
u_u_res(u_cmp);
function F()
   assert(()u.getinfo(1, "n").name == "F");
   return v_nq, 2, 3;
end;
F(u_u_res);
assert(u_u_res);
F(u_u_res);
assert(u_u_res);
idx = math.floor;
u_u_res = u_u_res();
GLOB1 = idx(u_u_res, u_cmp) % 2;
idx = {};
u_u_res[551] = "nil";
u_cmp[601] = "false";
c_tab_p[651] = "true";
idx[504] = {[701] = "10"};
idx[505] = {[451] = "(0==_ENV.GLOB1)"};
idx[506] = "(0==_ENV.GLOB1)";
idx[507] = GLOB1 ~= 0;
u_u_res(u_cmp);
u_u_res = {};
c_tab_p[501] = " or ";
u_u_res[551] = {[601] = " and "};
u_cmp = {};
local function c_tab_p ()
   for c_i_eu = 1, val_er - 1 do
      return {};
   end
end;
u_cmp[1] = idx;
for c_i_s = 2, 4 do
   u_cmp[v] = c_tab_p(v);
end
