print(u_val);
local u_val = 0;
function f()
   local u_tab = {};
   for c_i_gh = 1, 1000 do
      u_tab[c_i_gh] = (function ()
         u.g = u.g + 1;
         u_ms += u_mu;
         return u_ms + u_val;
      end);
   end
end;
a = f(10);
local c_tab = {{}};
setmetatable(c_tab, u_u_res);
while (c_tab[1]) do
   u_val += 1;
end
local v_s = assert;
local u_u_res = u_u_res();
v_s(u_u_res == u_glb);
v_s = assert;
u_u_res = u_u_res();
v_s(u_u_res == u_glb);
v_s = assert;
u_u_res = u_u_res();
v_s(u_u_res == u_glb);
collectgarbage();
v_s = assert;
u_u_res = u_u_res();
v_s(u_u_res == u_glb);
v_s = assert;
u_u_res = u_u_res();
v_s(u_u_res == u_glb);
v_s = assert;
u_u_res = u_u_res();
v_s(u_u_res == u_glb);
v_s = assert;
u_u_res = u_u_res();
v_s(u_u_res == u_glb);
v_s = assert;
local u_glb = getmetatable;
u_u_res = u_glb(c_tab).__mode;
v_s(u_u_res == u_glb);
assert(u_u_res == u_glb);
a = {};
for u_u_res = 1, 10 do
   a[u_u_res] = {set = (function ()
      u_glb = v_mi;
   end), get = (function ()
      return u_glb;
   end)};
   if (u_u_res == 3) then
      break;
   end
end
assert(u_u_res == u_glb);
u_u_res[u_glb].set(10);
v_s = assert;
u_u_res = u_u_res();
v_s(u_u_res == u_glb);
u_u_res[u_glb].set("a");
v_s = assert;
u_u_res = u_u_res();
v_s(u_u_res == u_glb);
v_s = assert;
u_u_res = u_u_res();
v_s(u_u_res == u_glb);
a = {};
for u_glb, i in pairs({"a", "b"}) do
   a[u_glb] = {set = (function ()
      u_glb = v_ly;
      i = v_mc;
   end), get = (function ()
      return u_glb, i;
   end)};
   if (u_glb == 2) then
      break;
   end
end
a[1].set(10, u_u_res);
u_u_res(u_glb);
u_u_res(u_glb);
u_u_res(u_glb, "b");
u_u_res(u_glb);
for i = 1, 3 do
   function f()
      return i;
   end;
   break;
end
u_glb = f() == 1;
u_u_res(u_glb);
u_glb[1] = "a";
u_glb[2] = "b";
for k, v in u_u_res(u_glb) do
   function f()
      return k, v;
   end;
   break;
end
k[1] = f();
u_u_res(u_glb);
u_u_res = assert;
k[1] = f();
u_u_res(u_glb);
function f()
   local v_ki = 1;
   while (true) do
      if (not (u_kk ~= 3) or v_ki) then
         return;
      end
      u_u_res = (function ()
         if (v_lc ~= "set") then
            return u_kq;
         end
         u_kq = u_kk + val;
      end);
      if ((u_kk == 1) or (u_kk == 2)) then
         return;
      end
      if (u_kk ~= 3) then
         error();
      end
      v_ki = nil;
   end
end;
for k = 1, 3 do
   f(k);
   assert(u_u_res("get") == "xuxu");
   u_u_res("set", 10);
   assert(u_u_res("get") == (k + 10));
end
