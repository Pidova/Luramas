local function c_func ()
   assert(typeof(v_bb) == "string", "left is a " .. typeof(v_bb));
   assert(typeof(v_bf) == "string", "right is a " .. typeof(v_bf));
   if (v_bb == v_bf) then
      return;
   end
   error(string.format("%q ~= %q", v_bb, v_bf));
end;
c_func(("hello %*"):format("world"), "hello world");
c_func(("Welcome %* %*!"):format("to", "Luau"), "Welcome to Luau!");
c_func(("2 + 2 = %*"):format(0), "2 + 2 = 4");
c_func(("%* %* %* %* %* %* %*"):format(1, 2, 3, 4, 5, 6, 7), "1 2 3 4 5 6 7");
c_func(("The lock combinations are: %*"):format(table.concat({
   5, 
   2, 
   8, 
   9}, ", ")), "The lock combinations are: 5, 2, 8, 9");
c_func(("true = %*"):format(true), "true = true");
c_func(("Welcome to %*!"):format("Luau"), "Welcome to Luau!");
c_func(("Welcome to %*!"):format("Luau"), "Welcome to Luau!");
c_func(("This %* does not exist"):format(localName), "This nil does not exist");
c_func(("Welcome to \n%*!"):format("Luau"), "Welcome to \nLuau!");
c_func("empty", "empty");
c_func("Escaped brace: {}", "Escaped brace: {}");
c_func(("Escaped brace {} with %*"):format("expression"), "Escaped brace {} with expression");
c_func("Backslash  that escapes the space is not a part of the string...", "Backslash  that escapes the space is not a part of the string...");
c_func("Escaped backslash \\", "Escaped backslash \\");
c_func("Escaped backtick: `", "Escaped backtick: `");
c_func(("Hello %*"):format(("from inside %*"):format("a nested string")), "Hello from inside a nested string");
c_func(("1 %*"):format(("2 %*"):format(("3 %*"):format(4))), "1 2 3 4");
assert(("You have %*%% health"):format(50) == "You have 50% health");
local function c_func_f ()
   return ("Value is %*"):format(v);
end;
c_func(c_func_f("hello"), "Value is hello");
c_func(c_func_f(1), "Value is 1");
c_func("A\t", "A\t");
return "OK";
