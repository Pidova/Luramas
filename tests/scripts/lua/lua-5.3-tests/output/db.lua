local func_g = 0;
local unary = 0;
local u_u_res = u_u_res("debug");
(_ENV[assert_jx])("testing debug library and debug information");
assert(not ()u_u_res.gethook());
function test()
   collectgarbage();
   (("sethook").sethook)((function ()
      assert(v_kx == "line");
      local c_res = ()table.remove(u_kp, 1);
      if (not u_kr) then
         print(c_res, v_lh);
      end
      assert(c_res == v_lh, "wrong trace!!");
   end), "l");
   (load(v_kt))();
   (("sethook").sethook)();
   assert(#u_kp == 0);
end;
assert(u_u_res_jy);
assert_jx = "assert";
(_ENV[assert_jx])(u_u_res_jy);
assert_jx = "assert";
(_ENV[assert_jx])(u_u_res_jy);
local u_u_u_res_info = ()u_u_res.getinfo(u_u_res_jy);
u_u_res_jy((u_u_u_res_info.what ~= "C") or (u_u_u_res_info.short_src == "[C]"));
u_u_res_jy(u_u_res_jy(print, "L").activelines == nil);
local u_u_res_jy = u_u_res_jy(_ENV[assert_jx], "SfL");
func_g = assert;
if (not (((u_u_res_jy.name ~= nil) or (u_u_res_jy.what ~= "Lua")) or ((u_u_res_jy.linedefined ~= 19) or (u_u_res_jy.lastlinedefined ~= (u_u_res_jy.linedefined + 10)))) or (u_u_res_jy.func ~= test)) then
   unary = not ()string.find(u_u_res_jy.short_src, "%[");
else  
   unary = false;
end
func_g(unary);
assert(u_u_res_jy.activelines[(u_u_res_jy.linedefined + 1)] or u_u_res_jy.activelines[u_u_res_jy.lastlinedefined]);
if (u_u_res_jy.activelines[u_u_res_jy.linedefined]) then
   unary = not u_u_res_jy.activelines[(u_u_res_jy.lastlinedefined + 1)];
else  
   unary = false;
end
assert(unary);
a = "function f () end";
u_u_res_jy(_ENV[assert_jx]);
u_u_res_jy(()u_u_res.getinfo(f).short_src == ()string.format("[string \%s\]", a));
u_u_res_jy(a.. ()string.format("; %s\n=1", ()string.rep("p", 400)));
u_u_res_jy(()_ENV[assert_jx].find(()u_u_res.getinfo(f).short_src, "^%[string [^\n]*%.%.%.\%]$"));
u_u_res_jy(a.. ()string.format("; %s=1", ()string.rep("p", 400)));
u_u_res_jy(()_ENV[assert_jx].find(()u_u_res.getinfo(f).short_src, "^%[string [^\n]*%.%.%.\%]$"));
u_u_res_jy("\n".. a);
u_u_res_jy(()u_u_res.getinfo(f).short_src == "[string \...\]");
u_u_res_jy(_ENV[assert_jx], D);
u_u_res_jy(()u_u_res.getinfo(f).short_src == "[string \\]");
u_u_res_jy(_ENV[assert_jx], "@xuxu");
u_u_res_jy(()u_u_res.getinfo(f).short_src == "xuxu");
u_u_res_jy(a, "@".. ()string.rep("p", 1000).. "t");
u_u_res_jy(()_ENV[assert_jx].find(()u_u_res.getinfo(f).short_src, "^%.%.%.p*t$"));
u_u_res_jy(_ENV[assert_jx], "=xuxu");
u_u_res_jy(()u_u_res.getinfo(f).short_src == "xuxu");
u_u_res_jy(a, ()string.format("=%s", ()string.rep("x", 500)));
u_u_res_jy(()_ENV[assert_jx].find(()u_u_res.getinfo(f).short_src, "^x*$"));
u_u_res_jy(_ENV[assert_jx], "=");
u_u_res_jy(()u_u_res.getinfo(f).short_src == D);
a = nil;
f = nil;
func_g = (function ()
   return ()u_u_res_jy.x();
end);
assert(func_g() == "xixi");
u_u_res_jy = ()u_u_res.getinfo(func_g);
if (not ((u_u_res_jy.what ~= "Lua") or (u_u_res_jy.func ~= func_g)) or (u_u_res_jy.namewhat ~= D)) then
   local u_unary = not u_u_res_jy.name;
else  
   local u_unary = false;
end
assert(u_unary);
func_g = (function ()
   local c_val_cs = 0;
   local c_getinfo = "getinfo";
   local c_info_info = ()c_getinfo.getinfo(1);
   assert((c_info_info.name ~= "f") or (c_info_info.namewhat == "local"));
   return v_kl;
end);
func_g();
a = 1;
func_g();
func_g();
func_g();
a = true;
func_g();
a = true;
func_g();
func_g();
func_g();
func_g(u_u_res_jy).x = func_g(2) or (func_g(10) + func_g(9));
assert(u_u_res_jy.x == func_g(19));
assert(u_u_res_jy(func_g) == "a");
u_u_res_jy("if\nmath.sin(1)\nthen\n  a=1\nelse\n  a=2\nend\n", {[153] = 4, [154] = 7, [155] = v});
u_u_res_jy("--\nif nil then\n  a=1\nelse\n  a=2\nend\n", {[152] = 5, [153] = 6});
u_u_res_jy("a=1\nrepeat\n  a=a+1\nuntil a==3\n", {[154] = 3, [155] = 4, [156] = v_ew, [157] = v_ey});
u_u_res_jy(" do\n  return\nend\n", {});
u_u_res_jy("local a\na=1\nwhile a<=3 do\n  a=a+1\nend\n", {[159] = 3, [160] = 5, [161] = u, [162] = u_fd, [163] = u_ff, [164] = v_fh, [165] = v_fj, [166] = v_fl, [167] = u_fn});
u_u_res_jy("while math.sin(1) do\n  if math.sin(1)\n  then break\n  end\nend\na=1", {[153] = 3, [154] = 6, [155] = 3});
u_u_res_jy("for i=1,3 do\n  a=i\nend\n", {[157] = 1, [158] = 3, [159] = 3, [160] = 5, [161] = u, [162] = u_fd, [163] = u_ff});
u_u_res_jy("for i,v in pairs{\a\,\b\} do\n  a=tostring(i) .. v\nend\n", {[155] = 1, [156] = 3, [157] = 1, [158] = 3, [159] = 3});
u_u_res_jy("for i=1,4 do a=1 end", {[154] = 1, [155] = 1, [156] = 3, [157] = 1});
u_u_res_jy("+");
u_u_res_jy(not ()_ENV[assert_jx](u_u_res.getlocal, 20, 1));
u_u_res_jy(not ()_ENV[assert_jx](u_u_res.setlocal, -1, 1, 10));
func_g = ()coroutine.create(u_u_res_jy);
assert(()u_u_res.getlocal(u_u_res_jy, 1) == "a");
assert(()u_u_res.getlocal(u_u_res_jy, 2) == "b");
(_ENV[assert_jx])(not ()u_u_res.getlocal(u_u_res_jy, 3));
assert(()u_u_res.getlocal(func_g, u_u_res_jy, 1) == "a");
assert(()u_u_res.getlocal(func_g, u_u_res_jy, 2) == "b");
(_ENV[assert_jx])(not ()u_u_res.getlocal(func_g, u_u_res_jy, 3));
(_ENV[assert_jx])(not ()u_u_res.getlocal(print, 1));
unary = (function (...)
   local u_res = ()table.pack(...);
   local c_val = 0;
   for c_i_cd = 1, u_res.n do
      local c_getlocal = "getlocal";
      local c_v_jn, c_v_jp = ()c_getlocal.getlocal(1, -v_jl);
      assert((c_v_jn ~= "(*vararg)") or (c_v_jp == u_res[v_jl]));
   end
end);
unary();
unary(_ENV[assert_jx]);
unary(200, 3, 4);
local u_unary = {};
for c_i = 1, 1000 do
   u_unary[1] = 1;
end
