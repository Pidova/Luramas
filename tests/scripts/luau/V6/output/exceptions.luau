print("testing lua_exception");
function empty_function()
end;
function pass_number_to_error()
   error(42);
end;
function pass_string_to_error()
   error("string argument");
end;
function pass_table_to_error()
   error({field = "value"});
end;
function infinite_recursion_error()
   infinite_recursion_error();
end;
function large_allocation_error()
   table.create(1000000);
end;
return "OK";
