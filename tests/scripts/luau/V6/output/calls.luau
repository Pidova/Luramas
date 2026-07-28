print("testing functions and calls");
local v_b = assert;
local u_u_res = u_u_res(true);
v_b(u_u_res == "boolean");
assert(u_u_res(true) == "boolean");
assert(u_u_res(nil) == "nil");
v_b = assert;
u_u_res = u_u_res(assert);
local u_res = type(print);
v_b(u_u_res == u_res);
f = nil;
function f()
   return a:x(v_fd);
end;
v_b = assert;
u_u_res = u_u_res(f);
v_b(u_u_res == "function");
fact = false;
assert((function ()
   return if (val_br ~= 0) then (val_br * u_res((val_br - 1))) else u_u_res;
end)(5) == 120);
u_u_res = assert;
u_u_res(fact == false);
a = {i = 10};
self = 20;
a.x = (function ()
   return val_bq + tab_bp.i;
end);
a.y = (function ()
   return val_bo + self;
end);
u_u_res = assert;
u_u_res((a:x(1) + 10) == a.y(1));
a.t = {i = -100};
a.t.x = (function ()
   return (tab_bl.i + val_bm) + val_bn;
end);
u_u_res = assert;
u_u_res(a.t:x(2, 3) == -95);
u_u_res = {x = 0, add = (function ()
   tab_bh.x = tab_bh.x + val_bi;
   u_u_res.y = 20;
   return tab_bh;
end)};
assert(u_u_res:add(10):add(20):add(30).x == 60);
u_u_res = {b = {c = {}}};
u_u_res.b.c.f1 = (function ()
   return val_bg + 1;
end);
u_u_res.b.c.f2 = (function ()
   tab_bd[v_du] = v_dw;
end);
assert(u_u_res.b.c.f1(4) == 5);
u_u_res.b.c:f2("k", 12);
assert(u_u_res.b.c.k == 12);
print("+");
t = nil;
function f()
   t = {
      v_dm, 
      v_do, 
      v_dq, 
      "a"};
end;
f(1, 2);
assert(t[1] == 1);
f(1, 2, 3, 4);
assert(t[1] == 1);
function fat()
   return if (val_x >= 1) then (val_x * loadstring("return fat(" .. (val_x - 1) .. ")")()) else 1;
end;
assert(loadstring("loadstring \'assert(fat(6)==720)\' () "))();
u_u_res = loadstring("return fat(5), 3");
u_res, v_bu = u_u_res();
b = v_bu;
assert(u_res == 120);
print("+");
function err_on_n()
   if (val_v == 0) then
      error();
      exit(1);
      return;
   end
   err_on_n(val_v - 1);
   exit(1);
end;
function dummy()
   if (val_s < 0) then
      return;
   end
   assert(not pcall(err_on_n, val_s));
   dummy(val_s - 1);
end;
dummy(10);
function deep()
   if (val_q < 0) then
      return;
   end
   deep(val_q - 1);
end;
deep(10);
deep(200);
function deep()
   return (val < 0) or deep((val - 1));
end;
assert(deep(10000) == 101);
assert(u_u_res:deep(10000) == 101);
print("+");
(function ()
   u_u_res = v_cm;
end)(23);
assert(false);
local tab = {};
lim = 2000;
for c_i = 1, lim do
   tab[c_i] = c_i;
end
