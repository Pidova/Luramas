print("testing debug library");
function foo(...)
   return debug.traceback(...);
end;
function bar()
   coroutine.yield();
end;
assert(foo():find("foo") > 0);
assert(foo("hello"):find("hello") > 0);
assert(foo("hello"):find("foo") > 0);
assert(foo("hello", 2):find("hello") > 0);
assert(foo("hello", 2):find("foo") == nil);
local c_res = coroutine.create(bar);
coroutine.resume(c_res);
assert(debug.traceback(c_res):find("bar") > 0);
assert(debug.traceback(c_res, "hello"):find("hello") > 0);
assert(debug.traceback(c_res, "hello"):find("bar") > 0);
assert(debug.traceback(c_res, "hello", 2):find("hello") > 0);
assert(debug.traceback(c_res, "hello", 2):find("bar") == nil);
function halp()
   return {v_cs = v_cu};
end;
local c_res_b = coroutine.create(halp);
coroutine.resume(c_res_b, 0 / 0, 42);
assert(debug.traceback(c_res_b) == "debug.lua:31 function halp\n");
assert(debug.info(c_res_b, 0, "l") == 31);
assert(debug.info(c_res_b, 0, "f") == halp);
function qux(...)
   local c_success, c_result = pcall(debug.info, ...);
   assert(not c_success);
   return c_result;
end;
assert(qux():find("function or level expected"));
assert(qux(1):find("string expected"));
assert(qux(-1):find("level can\'t be negative"));
assert(qux(1, "?"):find("invalid option"));
assert(qux(1, "nn"):find("duplicate option"));
assert(qux(c_res):find("function or level expected"));
assert(qux(c_res, 1):find("string expected"));
function baz(...)
   return debug.info(...);
end;
assert(baz(0, "n") == "info");
assert(baz(1, "n") == "baz");
assert(baz(2, "n") == "");
assert(baz(3, "n") == nil);
assert(baz(0, "s") == "[C]");
assert(baz(1, "s") == "debug.lua");
assert(baz(0, "l") == -1);
assert(baz(1, "l") > 42);
assert(baz(0, "f") == debug.info);
assert(baz(1, "f") == baz);
assert(baz(0, "a") == 0);
assert(baz(1, "a") == 0);
assert(baz(c_res, 1, "n") == "bar");
assert(baz(c_res, 2, "n") == nil);
assert(baz(math.sqrt, "n") == "sqrt");
assert(baz(math.sqrt, "f") == math.sqrt);
assert(baz(({foo = (function ()
   return 1;
end)}).foo, "n") == "foo");
function quux(...)
   return {debug.info(...)};
end;
assert(#quux(1, "nlsf") == 4);
assert(quux(1, "nlsf")[1] == "quux");
assert(quux(1, "nlsf")[2] > 64);
assert(quux(1, "nlsf")[3] == "debug.lua");
assert(quux(1, "nlsf")[4] == quux);
function quuz()
   local c_value, c_value_t = debug.info(v_ca, "a");
   return tostring(c_value) .. " " .. tostring(c_value_t);
end;
assert(quuz(math.cos) == "0 true");
assert(quuz((function ()
end)) == "0 false");
assert(quuz((function ()
end)) == "0 true");
assert(quuz((function ()
end)) == "2 false");
assert(quuz((function ()
end)) == "2 true");
function testlinedefined()
   assert((debug.info(testlinedefined, "l") + 1) == debug.info(1, "l"));
end;
testlinedefined();
coroutine.resume(coroutine.create((function ()
   local c_v_bo, c_v_bq = coroutine.resume(coroutine.create((function ()
      for c_i_s = 1, 100 do
         pcall(debug.info, v_by, 0, "llf");
      end
   end)), coroutine.running());
   assert(c_v_bo);
   assert(c_v_bq == 123);
end)));
coroutine.resume(coroutine.create((function ()
   local c_v_bc, c_v_be = coroutine.resume(coroutine.create((function ()
      for c_i_m = 1, 100 do
         pcall(debug.info, v_bm, 0, "ff");
      end
   end)), coroutine.running());
   assert(c_v_bc);
   assert(c_v_be == 123);
end)));
coroutine.resume(coroutine.create((function ()
   local c_v, c_v_s = coroutine.resume(coroutine.create((function ()
      for c_i = 1, 100 do
         pcall(debug.info, v_ba, 0, "?f");
      end
   end)), coroutine.running());
   assert(c_v);
   assert(c_v_s == 123);
end)));
return "OK";
