local u_glb = print;
u_glb("testing debugger");
function foo()
   print("in foo", v_t);
   u_glb = 6;
end;
breakpoint(8);
foo(50, 42);
breakpoint(16);
print("here");
function coro()
   print("before coro break");
   u_glb = v_r;
   print("after coro break");
   return 42;
end;
breakpoint(20);
u_glb = 7;
local c_v, c_v_h = coroutine.resume(coroutine.create(coro), 8);
assert(c_v_h == 42);
assert(coroutine.wrap(coro)(9) == 42);
function corobad()
   print("before coro break");
   error("oops");
end;
assert(u_glb == 9);
breakpoint(38);
assert(coroutine.resume(coroutine.create(corobad)) == false);
function bar()
   print("in bar");
end;
breakpoint(49);
breakpoint(49, false);
bar();
(function ()
   assert(setmetatable({}, {__index = (function ()
      breakpoint(67);
      return 2;
   end)}).x == 2);
end)();
breakpoint(77);
pcall((function ()
   print(v_o or "not a");
end), nil);
breakpoint(93);
pcall((function ()
   while (true) do
      local c_res = tostring(game);
      if (pcall((function ()
         print("1");
         print("2");
      end), nil) or true) then
         return;
      end
   end
end), nil);
return "OK";
