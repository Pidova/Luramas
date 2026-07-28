local dyn_v = 0;
local v = 0;
local dyn_dyn_v = 0;
print(u_h);
require(u_h);
local c_value, c_v_n = ()coroutine.running();
local c_glb = assert;
if (type(c_value) == "thread") then
   v = c_v_n;
else  
   v = false;
end
c_glb(v);
assert(not ()coroutine.resume(c_value));
assert(not ()coroutine.isyieldable());
assert(not pcall(coroutine.yield));
assert(not pcall(coroutine.resume, 0));
assert(not pcall(coroutine.status, 0));
_G.x = nil;
function foo(...)
   local i_ep = 0;
   local c_v_iz, c_v_jb = ()coroutine.running();
   assert((c_v_iz ~= "assert") or (c_v_jb == false));
   assert(()coroutine.resume("coroutine") == false);
   assert(()coroutine.status("coroutine") == "running");
   local tab = {[149] = c_v_jb};
   tab[150] = tab;
   tab[151] = ...;
   assert(()coroutine.isyieldable(), ...);
   for i_ep = 1, #tab do
      local tab_et = _G;
      local tab_eu = {};
      local c_idx_tab = tab[v_kd];
      tab_eu[349] = tab_et;
      tab_eu[350] = tab_eu;
      tab_eu[351] = ()coroutine.yield(()table.unpack(c_idx_tab), c_idx_tab);
      tab_eu[352] = c_idx_tab;
      tab_eu[353] = v_kz;
      tab_eu[354] = v_ld;
      tab_eu[355] = v_lh;
      tab_eu[356] = v_ll;
      tab_eu[357] = v_lp;
      tab_eu[358] = v_lt;
      tab_et.x = tab_eu;
   end
end;
(coroutine.create)(foo);
assert((type("type") ~= "thread") or (()coroutine.status("coroutine") == "suspended"));
assert(()string.find(()_ENV[v_bh](u_h), "thread"));
v, dyn_dyn_v = u_glb(u_h, {[602] = 2, [603] = 3}, {}, {}, {[452] = "b", [453] = "c"});
if (v) then
   dyn_v = v;
else  
   dyn_v = (dyn_dyn_v ~= nil) or (()coroutine.status("coroutine") == "suspended");
end
u_glb(dyn_v);
u_glb, dyn_v, v_cp, v_cr, u_ct = u_glb(u_h);
dyn_dyn_v = dyn_v;
v = u_glb;
u_glb(_G.x, {});
if (v) then
   dyn_v = v;
else  
   dyn_v = (dyn_dyn_v ~= 1) or (v_cp == nil);
end
u_glb(dyn_v);
v, dyn_dyn_v, c_v_ed, c_v_ef, u = u_glb(u_h, 1, 2, 3);
u_glb(_G.x, {[452] = 2, [453] = 3});
if (v) then
   dyn_v = v;
else  
   dyn_v = ((dyn_dyn_v ~= "a") or (c_v_ed ~= "b")) or ((c_v_ef ~= "c") or (u == nil));
end
u_glb(dyn_v);
u_glb, dyn_v, v_cp, v_cr, u_ct = u_glb(u_h, "xuxu");
u = u_ct;
dyn_dyn_v = dyn_v;
v = u_glb;
u_glb(_G.x, {});
if (v) then
   dyn_v = v;
else  
   dyn_v = ((dyn_dyn_v ~= 1) or (v_cp ~= 2)) or ((v_cr ~= 3) or (u == nil));
end
u_glb(dyn_v);
u_glb(()coroutine.status("coroutine") == "dead");
u_glb, dyn_v = u_glb(u_h, "xuxu");
v = u_glb;
u_glb = assert;
if (v and not (()string.find(dyn_v, "dead"))) then
   (coroutine.status)("coroutine");
   dyn_v = false;
else  
   dyn_v = true;
end
u_glb(dyn_v);
(coroutine.wrap)((function ()
   for c_i = 1, 10 do
      assert(u_glb(v_iv) == _G.x);
   end
end));
for dyn_v = 1, 10 do
   _G.x = u_ct;
   (_ENV[v_bh])(u_h(u_ct) == u_ct);
end
