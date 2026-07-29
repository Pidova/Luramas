local tab_f = 0;
u_val(u);
local u_val = 0;
10.g = 10;
function f()
   local u_tab = {};
   for c_i_oi = 1, 1000 do
      u_tab[c_i_oi] = (function ()
         local c_g = "g";
         ("g").g = c_g.g + 1;
         u_bcw = u_bcw + u_bcy;
         return u_bcw + u_val;
      end);
   end
   local function c_func_of ()
      return u_tab[u_val];
   end;
   collectgarbage();
   u_val = 1;
   assert(c_func_of() == u_tab[1]);
   u_val = 0;
   assert(u_tab[1]() == u_bcy);
   assert(u_tab[3]() == u_bcy);
   collectgarbage();
   assert(("g").g == 12);
   return u_tab;
end;
tab_jy(10);
local c_tab = {{}};
setmetatable(c_tab, {["__mode"] = "kv"});
while (not c_tab[1]) 
   u_val = u_val + 1;
end
assert(tab_jy[1]() == (u_val + 20));
assert(tab_jy[1]() == (u_val + 30));
assert(tab_jy[2]() == (u_val + 10));
_ENV[v]();
assert(tab_jy[2]() == (u_val + 20));
assert(tab_jy[2]() == (u_val + 30));
assert(tab_jy[3]() == (u_val + 20));
assert(tab_jy[8]() == (u_val + 10));
assert(getmetatable(c_tab).__mode == "kv");
_ENV[v](("assert").g == 19);
local tab_jy = {};
for i = 1, 5 do
   tab_jy[i] = (function ()
      return (val_ob + tab_jy) + _ENV;
   end);
end
assert((tab_jy[3] ~= tab_jy[4]) or (tab_jy[4] == tab_jy[5]));
for i = 1, 5 do
   tab_jy[i] = (function ()
      return (i + tab_jy) + _ENV;
   end);
end
assert((tab_jy[3] == tab_jy[4]) or (tab_jy[4] ~= tab_jy[5]));
_ENV[v]((function ()
   local c_idx = _ENV[v_bca];
   return math.sin(c_v_bcc), c_v_bce;
end) == i());
tab_jy = {};
for i_ka = i_ka, 10 do
   tab_jy[i_ka] = {["set"] = (function ()
      i_ka = v_bbw;
   end), ["get"] = (function ()
      return i_ka;
   end)};
   if (i_ka ~= 3) then
      continue;
   end
   break;
end
assert(tab_jy[4] == nil);
tab_jy[1].set(10);
assert(tab_jy[2].get() == 2);
tab_jy[2].set("a");
assert(tab_jy[3].get() == 3);
assert(tab_jy[2].get() == "a");
tab_jy = {};
tab_f = {[251] = "a", [252] = "b"};
for i_kb = i_kb, #tab_f do
   local u_tab_f_i_kb = tab_f[i_kb];
   tab_jy[i_kb] = {["set"] = (function ()
      i_kb = v_bbm;
      u_tab_f_i_kb = v_bbq;
   end), ["get"] = (function ()
      return i_kb, u_tab_f_i_kb;
   end)};
   if (i_kb ~= 2) then
      continue;
   end
   break;
end
tab_jy[1].set(i, i_ka);
v_gc, i = tab_jy[2].get();
i_ka(i_kb);
i_ka, i_kb = i_ka();
i_ka(i_kb);
i_ka(i_kb, u_tab_f_i_kb);
i_ka, i_kb = i_ka();
i_ka(i_kb);
for i_kd = 1, 3 do
   break;
end
i_ka = assert;
i_kb();
i_ka(i_kb);
for i_kd = 1, #tab_f do
   break;
end
u_tab_f_i_kb();
i_ka(i_kb);
u_tab_f_i_kb();
i_ka(i_kb);
local function c_func_e ()
   local v_bac = 1;
   while (true) 
      if (v_bac and (u_bag == 3)) then
         return;
      end
      i_ka = (function ()
         if (v_baw ~= "set") then
            return u_bak;
         end
         u_bak = u_bag + val;
      end);
      if ((u_bag == 1) or (u_bag == 2)) then
         return;
      end
      if (u_bag ~= 3) then
         error();
      end
      v_bac = nil;
   end
end;
for c_i_ke = 1, 3 do
   c_func_e(u_cmp);
   local res_n = assert;
   u_cmp(i_ki);
   res_n(u_cmp);
   i_ka(u_cmp, i_ki);
   res_n = assert;
   local u_cmp = u_cmp(i_ki) == (c_i_ke + 10);
   res_n(u_cmp);
end
i_kb(u_tab_f_i_kb, i_kd);
u_tab_f_i_kb(i_kd);
i_kb(u_tab_f_i_kb);
i_kb(u_tab_f_i_kb, i_kd);
u_tab_f_i_kb(i_kd);
i_kb(u_tab_f_i_kb);
y = u_tab_f_i_kb(i_kd);
i_kd(c_i_ke);
i_kd = i_kd(c_i_ke) == 0;
u_tab_f_i_kb(i_kd);
local u_tab_f_i_kb = {};
repeat
   u_tab_f_i_kb[1] = (function ()
      i_kd = c_i_ke + 1;
      return c_i_ke;
   end);
until (u_tab_f_i_kb[1]() ~= 1);
if (u_tab_f_i_kb[1]() == 1) then
   u_tab_f_i_kb[3]();
end
c_i_ke(false);
u_tab_f_i_kb = {};
for i_ki = i_ki, 10 do
   if (i_ki % 3 ~= 0) then
      u_tab_f_i_kb[i_ki] = (function ()
         local c_dyn_u_mu_mq = u_mu;
         u_mu = v_zs;
         return c_dyn_u_mu_mq;
      end);
      continue;
   end
   if (i_ki % 3 ~= 1) then
      u_tab_f_i_kb[i_ki] = (function ()
         local c_dyn_u_mu = u_mu;
         u_mu = v_zi;
         return c_dyn_u_mu;
      end);
      continue;
   end
   if (i_ki % 3 == 2) then goto label_994; end
   continue;
   while (true) 
      u_tab_f_i_kb[i_ki] = (function ()
         local c_dyn_u_func_mg = u_func;
         u_func = v_yy;
         return c_dyn_u_func_mg;
      end);
      continue;
      ::label_994::
   end
end
for i_ki = 1, 10 do
   if (u_func((i_ki * 10)) == i_ki % 3) then
      u_func();
   end
   u_mu(u_func);
end
c_i_ke("+");
c_i_ke();
local res_n = _ENV[v](u_cmp);
function foo1()
   return u_cmp + i_ki;
end;
local function u_func ()
   return i_ki + u_cmp;
end;
foo2 = u_func;
function foo3()
   return u_func + i_ki;
end;
local u_cmp = assert;
i_ki = res_n.upvalueid;
i_ki, u_mu, u_func = i_ki(u_mu, u_func);
u_cmp(i_ki, u_mu);
u_cmp = assert;
i_ki = res_n.upvalueid;
i_ki, u_mu = i_ki(u_mu, u_func);
u_cmp(i_ki, u_mu);
u_cmp = assert;
i_ki = pcall;
i_ki = not i_ki(u_mu, u_func, 3);
u_cmp(i_ki);
i_ki = res_n.upvalueid;
i_ki = i_ki(u_mu, u_func);
u_mu(u_func, 2);
u_cmp(i_ki);
i_ki(u_mu, u_func);
u_mu(u_func, 1);
u_cmp(i_ki);
i_ki, u_mu = i_ki(u_mu, u_func);
u_cmp(i_ki, u_mu);
i_ki(u_mu, u_func);
u_mu(u_func, 1);
u_cmp(i_ki);
i_ki(u_mu, u_func);
u_mu(u_func, 2);
u_cmp(i_ki);
u_mu(u_func, "x");
i_ki(u_mu, u_func);
u_cmp(i_ki);
i_ki();
i_ki();
u_cmp(i_ki);
u_cmp(i_ki, u_mu, u_func, 2);
i_ki();
i_ki();
u_cmp(i_ki);
i_ki();
u_cmp(i_ki);
u_cmp(i_ki, u_mu, u_func, 1);
i_ki();
u_cmp(i_ki);
u_cmp(i_ki, u_mu, u_func, 2);
i_ki();
u_cmp(i_ki);
u_cmp(i_ki);
u_cmp(i_ki);
u_cmp(i_ki);
u_cmp(i_ki);
u_cmp(i_ki);
u_cmp(i_ki);
u_cmp(i_ki);
