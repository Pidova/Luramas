print("testing pcall");
function checkresults(...)
   local c_res_es = table.pack(...);
   assert(c_res_es.n == #tab_er);
   for c_i_ev = 1, c_res_es.n do
      assert(c_res_es[c_i_ev] == tab_er[c_i_ev]);
   end
end;
function checkerror(...)
   local c_res_en = table.pack(...);
   assert(c_res_en.n == 2);
   assert(c_res_en[1] == false);
   assert(type(c_res_en[2]) == "string");
end;
function corun()
   local c_res_eg = coroutine.create(v_rc);
   local v_re = {};
   while (coroutine.status(c_res_eg) == "suspended") do
      v_re = {coroutine.resume(c_res_eg)};
   end
   assert(coroutine.status(c_res_eg) == "dead");
   return table.unpack(v_re);
end;
function colog()
   local c_res_dm = coroutine.create(v_po);
   local c_tab = {};
   while (coroutine.status(c_res_dm) == "suspended") do
      local c_tab_do = {coroutine.resume(c_res_dm)};
      if (c_tab_do[1]) then
         local c_idx = table.insert;
         coroutine.status(c_res_dm);
         c_idx(c_tab, "return");
      else  
         table.insert(c_tab, "error");
      end
      table.move(c_tab_do, 2, #c_tab_do, #c_tab + 1, c_tab);
      print(coroutine.status(c_res_dm), table.unpack(c_tab));
   end
   assert(coroutine.status(c_res_dm) == "dead");
   return table.unpack(c_tab);
end;
checkresults({true, 42}, pcall((function ()
   return 42;
end)));
local v = checkresults;
local success, u_result, u_arg2 = pcall((function ()
   return v_pi, v_pk, 42;
end), u_arg2, 2);
v({
   true, 
   1, 
   2, 
   42}, success);
v = checkresults;
success, u_result, u_arg2 = pcall((function (...)
   return select("#", ...);
end), u_arg2, 2);
v({true, 2}, success);
v = checkresults;
success, u_result, u_arg2 = pcall(math.abs, u_arg2);
v({true, 42}, success);
v = checkresults;
success, u_result, u_arg2 = pcall(setmetatable(u_arg2, {__call = (function ()
   return math.abs(v_pg);
end)}), u_arg2);
v({true, 42}, success);
checkerror(pcall((function ()
end)));
checkerror(pcall((function ()
   select(-100);
end)));
if (not limitedstack) then
   function stackinfinite()
      return stackinfinite();
   end;
   checkerror(pcall(stackinfinite));
   function stackover()
      return pcall(stackover);
   end;
   assert(#({pcall(stackover)}) == u_arg2);
end
checkresults({
   "yield", 
   "return", 
   true, 
   42}, colog((function ()
   return pcall((function ()
      coroutine.yield();
      return 42;
   end));
end)));
checkresults({
   "yield", 
   1, 
   "return", 
   true, 
   42}, colog((function ()
   return pcall((function ()
      coroutine.yield(1);
      return 42;
   end));
end)));
checkresults({
   "yield", 
   1, 
   2, 
   3, 
   "return", 
   true, 
   42}, colog((function ()
   return pcall((function ()
      coroutine.yield(1, 2, 3);
      return 42;
   end));
end)));
checkresults({
   "yield", 
   1, 
   "yield", 
   2, 
   "yield", 
   3, 
   "return", 
   true, 
   42}, colog((function ()
   return pcall((function ()
      for c_i = 1, 3 do
         coroutine.yield(c_i);
      end
   end));
end)));
checkresults({
   "yield", 
   "return", 
   true, 
   1, 
   2, 
   3}, colog((function ()
   return pcall((function ()
      coroutine.yield();
      return 1, 2, 3;
   end));
end)));
checkresults({
   "yield", 
   1, 
   "yield", 
   2, 
   "return", 
   true, 
   true, 
   3}, colog((function ()
   return pcall((function ()
      coroutine.yield(1);
      return pcall((function ()
         coroutine.yield(2);
         return 3;
      end));
   end));
end)));
checkresults({
   "yield", 
   "return", 
   false, 
   "pcall.lua:80: foo"}, colog((function ()
   return pcall((function ()
      coroutine.yield();
      error("foo");
   end));
end)));
checkresults({
   "yield", 
   "yield", 
   "return", 
   true, 
   false, 
   "pcall.lua:81: foo"}, colog((function ()
   return pcall((function ()
      coroutine.yield();
      return pcall((function ()
         coroutine.yield();
         error("foo");
      end));
   end));
end)));
checkresults({
   "yield", 
   "yield", 
   "return", 
   false, 
   "pcall.lua:82: bar"}, colog((function ()
   return pcall((function ()
      coroutine.yield();
      pcall((function ()
         coroutine.yield();
         error("foo");
      end));
      error("bar");
   end));
end)));
assert(#({pcall((function ()
   return table.unpack(table.create(100, "a"));
end))}) == 101);
assert(#({corun((function ()
   return pcall((function ()
      coroutine.yield();
      return table.unpack(table.create(100, "a"));
   end));
end))}) == 102);
success = checkresults;
u_arg2 = u_arg2((function ()
   return pcall(coroutine.yield, 1, 2, 3);
end));
success({
   "yield", 
   1, 
   2, 
   3, 
   "return", 
   true}, u_arg2);
success = checkresults;
u_arg2 = u_arg2((function ()
   return pcall(pcall, pcall, coroutine.yield, 1, 2, 3);
end));
success({
   "yield", 
   1, 
   2, 
   3, 
   "return", 
   true, 
   true, 
   true}, u_arg2);
success = checkresults;
u_arg2 = u_arg2((function ()
   return pcall(pcall, pcall, (function ()
      coroutine.yield();
      return 42;
   end));
end));
success({
   "yield", 
   "return", 
   true, 
   true, 
   true, 
   42}, u_arg2);
success = checkresults;
u_arg2, u_success = u_arg2((function ()
   return 42;
end), u_u_res);
success({true, 42}, u_arg2);
success = checkresults;
u_arg2, u_success, u_u_res, u_glb = u_arg2((function ()
   return v_oy, v_pa, 42;
end), u_u_res, 1, 2);
success({
   true, 
   1, 
   2, 
   42}, u_arg2);
success = checkresults;
u_arg2, u_success, u_u_res, u_glb = u_arg2((function (...)
   return select("#", ...);
end), u_u_res, 1, 2);
success({true, 2}, u_arg2);
success = checkresults;
u_arg2 = u_arg2((function ()
   return xpcall((function ()
      coroutine.yield();
      return 42;
   end), error);
end));
success({
   "yield", 
   "return", 
   true, 
   42}, u_arg2);
success = checkresults;
u_arg2, u_success = u_arg2((function ()
   error("foo");
end), u_u_res);
success({false, "pcall.lua:103: foo"}, u_arg2);
success = checkresults;
u_arg2, u_success = u_arg2((function ()
   error("foo");
end), u_u_res);
success({false, "bar"}, u_arg2);
success = checkresults;
u_arg2, u_success = u_arg2((function ()
   error("foo");
end), u_u_res);
success({false, 1}, u_arg2);
success = checkresults;
u_arg2, u_success, u_u_res = u_arg2((function ()
   error("foo");
end), u_u_res);
success({false, "pcall.lua:106: foo\npcall.lua:106\npcall.lua:106\n"}, u_arg2);
success = checkresults;
u_arg2, u_success = u_arg2((function ()
   error("foo");
end), u_u_res);
success({false, "error in error handling"}, u_arg2);
success = checkresults;
u_arg2 = u_arg2((function ()
   return xpcall((function ()
      coroutine.yield();
      error("foo");
   end), (function ()
      return v_ow;
   end));
end));
success({
   "yield", 
   "return", 
   false, 
   "pcall.lua:110: foo"}, u_arg2);
success = checkresults;
u_arg2 = u_arg2((function ()
   return xpcall((function ()
      coroutine.yield();
      error("foo");
   end), debug.traceback);
end));
success({
   "yield", 
   "return", 
   false, 
   "pcall.lua:111: foo\npcall.lua:111\npcall.lua:111\n"}, u_arg2);
success = checkresults;
u_arg2 = u_arg2((function ()
   return xpcall((function ()
      return xpcall((function ()
         coroutine.yield();
         error("foo");
      end), (function ()
         error("bar");
      end));
   end), error);
end));
success({
   "yield", 
   "return", 
   true, 
   false, 
   "error in error handling"}, u_arg2);
success = checkresults;
u_arg2 = u_arg2((function ()
   return xpcall(pcall, (function (...)
      return ...;
   end), (function ()
      return pcall((function ()
         coroutine.yield(42);
      end));
   end));
end));
success({
   "yield", 
   42, 
   "return", 
   true, 
   true, 
   true}, u_arg2);
success = checkresults;
u_arg2, u_success = u_arg2(xpcall, u_u_res);
success({false, "missing argument #2 to \'xpcall\' (function expected)"}, u_arg2);
success = checkresults;
u_arg2, u_success, u_u_res = u_arg2(xpcall, u_u_res, true);
success({false, "invalid argument #2 to \'xpcall\' (function expected, got boolean)"}, u_arg2);
function weird()
   coroutine.yield(weird);
   weird();
end;
success = checkresults;
u_arg2 = u_arg2((function ()
   for v_ou in coroutine.wrap(pcall), weird do
   end
end));
success({false, "pcall.lua:129: cannot resume dead coroutine"}, u_arg2);
success = checkresults;
u_result = {false, "oops"};
u_arg2 = u_arg2(cxxthrow);
success(u_result, u_arg2);
success = coroutine.create((function ()
   local c_v_oq = pcall((function ()
      coroutine.yield();
   end));
   coroutine.yield();
   return c_v_oq;
end));
coroutine.resume(u_arg2);
resumeerror(u_arg2, "fail");
u_arg2[1] = true;
u_arg2[2] = false;
u_arg2[3] = "fail";
checkresults(u_arg2, coroutine.resume(u_u_res));
function recurse()
   return (val < 1) or (recurse((val - 1)) + 1);
end;
u_u_res = u_u_res(20480);
u_arg2(u_u_res == 20480);
u_u_res, u_glb = u_u_res(recurse, 20480);
u_arg2({true, 20480}, u_u_res);
u_success, u_u_res, u_glb = pcall(u_u_res, 20480);
u_arg2(u_success);
u_u_res, u_glb = u_u_res(recurse, (function ()
   return string.reverse("ko");
end), 20480);
u_arg2({false, "ok"}, u_u_res);
u_u_res, u_glb = u_u_res(recurse, (function ()
   return recurse(u_result);
end), 20480);
u_arg2({false, "error in error handling"}, u_u_res);
u_u_res = u_u_res((function ()
   table.create(1000000);
end));
u_arg2({false, "not enough memory"}, u_u_res);
u_u_res, u_glb = u_u_res((function ()
   table.create(1000000);
end), (function ()
   return v_oi;
end));
u_arg2({false, "not enough memory"}, u_u_res);
u_u_res, u_glb = u_u_res((function ()
   table.create(1000000);
end), (function ()
   return "oops";
end));
u_arg2({false, "oops"}, u_u_res);
u_u_res, u_glb = u_u_res((function ()
   error("oops");
end), (function ()
   table.create(1000000);
end));
u_arg2({false, "error in error handling"}, u_u_res);
u_u_res, u_glb = u_u_res((function ()
   table.create(1000000);
end), (function ()
   table.create(1000000);
end));
u_arg2({false, "not enough memory"}, u_u_res);
success = u_arg2((function ()
   table.create(1000000);
end));
u_arg2(success);
u_arg2 = checkresults;
u_u_res = u_u_res(success);
u_arg2({false, "not enough memory"}, u_u_res);
u_success = (function ()
   u_arg2 = (function ()
      local c_res = table.pack("a", "b", "d", "e", "f", "g", "h", "i");
      assert(u == 1);
      assert(u_ne == 2);
      assert(u_ng == 3);
      assert(u_ni == 4);
      local u, u_ne, u_ng, u_ni = table.unpack(c_res);
      return "ok";
   end);
   if (v_nk) then
      v_nk();
   end
   error("oops");
end);
u_arg2 = nil;
u_u_res(u_success, nil);
u_u_res(u_arg2() == "ok");
u_arg2 = nil;
u_u_res(u_success, (function ()
end), nil);
u_u_res(u_arg2() == "ok");
u_arg2 = nil;
u_u_res(u_success, (function ()
   return "e", "e", "e", "e", "e", "e", "e", "e";
end), nil);
u_u_res(u_arg2() == "ok");
u_u_res({"yield", "return", "ok"}, colog((function ()
   pcall(u_success, coroutine.yield);
   return u_arg2();
end)));
u_u_res({"yield", "return", "ok"}, colog((function ()
   xpcall(u_success, (function ()
   end), coroutine.yield);
   return u_arg2();
end)));
u_u_res({"yield", "return", "ok"}, colog((function ()
   xpcall(u_success, (function ()
      return "e", "e", "e", "e", "e", "e", "e", "e";
   end), coroutine.yield);
   return u_arg2();
end)));
u_u_res = nil;
xpcall(u_success, (function ()
   u_u_res = u_arg2();
end), nil);
assert(u_u_res == "ok");
u_u_res = nil;
checkresults({"yield", "return"}, colog((function ()
   xpcall(u_success, (function ()
      u_u_res = u_arg2();
   end), coroutine.yield);
end)));
u_glb = assert;
u_glb(u_u_res == "ok");
if (limitedstack) then
   return "OK";
end
checkerror(pcall((function ()
   u_u_res += 1;
   pcall(1);
   coroutine.wrap(u_glb)();
end)));
assert(false);
return "OK";
