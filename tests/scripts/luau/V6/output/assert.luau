print("testing asserts");
if (not pcall(assert, false)) then
   error("catastrophic assertion failure");
end
function ecall(...)
   local c_success, c_result = pcall(function, ...);
   assert(not c_success);
   return c_result:sub((c_result:find(": ") + 2), #c_result);
end;
assert(1);
assert(true);
assert(assert(1) == 1);
assert(type(assert({})) == "table");
assert(ecall((function ()
   assert();
end)) == "missing argument #1");
assert(ecall((function ()
   assert(nil);
end)) == "assertion failed!");
assert(ecall((function ()
   assert(false);
end)) == "assertion failed!");
assert(ecall((function ()
   assert(nil, "epic fail");
end)) == "epic fail");
assert(select("#", assert(1, 2, 3)) == 3);
assert(table.concat(table.pack(assert(1, 2, 3)), "") == "123");
return "OK";
