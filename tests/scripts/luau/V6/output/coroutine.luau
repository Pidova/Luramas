local u_glb = print;
u_glb("testing coroutines");
assert(coroutine.running() == nil);
assert(coroutine.isyieldable());
assert(not pcall(coroutine.resume, 0));
assert(not pcall(coroutine.status, 0));
_G.x = nil;
function foo(...)
   assert(coroutine.running() == u_glb);
   assert(coroutine.resume(u_glb) == false);
   assert(coroutine.status(u_glb) == "running");
   local c_tab = {...};
   assert(coroutine.isyieldable());
   for c_i_cz = 1, #c_tab do
      _G.x = {coroutine.yield(table.unpack(c_tab[c_i_cz]))};
   end
end;
u_glb = coroutine.create(foo);
assert(type(u_glb) == "thread");
assert(string.find(tostring(u_glb), "thread"));
local u, v = u_func(u_glb, {1, 2, 3}, {}, {1}, {"a", "b", "c"});
u_func(u and (v == nil));
local u_func, v_bf, v_bh, i, u_bl = u_func(u_glb);
u = u_func;
u_func(_G.x, {});
u_func(u and (v_bf == 1));
u_func, v_bf, v_bh, i, u_bl = u_func(u_glb, 1, 2, 3);
u = u_func;
u_func(_G.x, {1, 2, 3});
u_func(u and (v_bf == "a"));
u_func, v_bf, v_bh, i, u_bl = u_func(u_glb, "xuxu");
u = u_func;
u_func(_G.x, {"xuxu"});
u_func(u and (v_bf == 1));
u_func(coroutine.status(u_glb) == "dead");
u, v = u_func(u_glb, "xuxu");
u_func((not u or string.find(v, "dead")) and (coroutine.status(u_glb) == "dead"));
u_func = (function ()
   return coroutine.yield(v_fp);
end);
u_glb = coroutine.wrap((function ()
   for c_i_cs = 1, 10 do
      assert(u_func(c_i_cs) == _G.x);
   end
end));
for i = 1, 10 do
   _G.x = i;
   assert(u_glb(i) == i);
end
