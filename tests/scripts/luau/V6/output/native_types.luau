print("testing native code generation with type annotations");
function call(...)
   local c_success_n, c_result_o = pcall(function_m, ...);
   assert(c_success_n);
   return c_result_o;
end;
function ecall(...)
   local c_success, c_result = pcall(function, ...);
   assert(not c_success);
   return c_result:sub((c_result:find(": ") + 2), #c_result);
end;
local function c_func_a ()
   assert(v_bx == is_native());
   return val_c + val_d;
end;
call(c_func_a, 1, 3, true);
ecall(c_func_a, nil, 2, false);
local function c_func_b ()
   assert(is_native());
   return not v_bv;
end;
call(c_func_b, nil);
ecall(c_func_b, 2);
local function c_func_c ()
   assert(is_native());
   return not not v_bt;
end;
call(c_func_c, nil, 1);
call(c_func_c, 2, 1);
call(c_func_c, {}, 1);
local function c_func_d ()
   assert(is_native());
   return v or "3";
end;
assert(call(c_func_d, nil) == "3");
assert(call(c_func_d, "two: ") == "two: 2");
ecall(c_func_d, 2);
local function c_func_e ()
   assert(is_native());
end;
local function c_func_f ()
   assert(is_native());
end;
local function c_func_g ()
   assert(is_native());
end;
local function c_func_h ()
   assert(is_native());
end;
local function c_func_i ()
   assert(is_native());
end;
local function c_func_j ()
   assert(is_native());
end;
local function c_func_k ()
   assert(is_native());
end;
call(c_func_e, {});
ecall(c_func_e, 2);
call(c_func_f, (function ()
end));
ecall(c_func_f, 2);
call(c_func_g, coroutine.create((function ()
end)));
ecall(c_func_g, 2);
call(c_func_h, newproxy());
ecall(c_func_h, 2);
call(c_func_i, vector(1, 2, 3));
ecall(c_func_i, 2);
call(c_func_j, buffer.create(10));
ecall(c_func_j, 2);
call(c_func_k, buffer.create(10));
call(c_func_k, nil);
ecall(c_func_k, 2);
assert(call((function ()
   while (true) do
      c_val += c_val_b;
      pcall((function ()
      end));
      c_val_b -= 1;
      if (c_val_b == 0) then
         return c_val;
      end
   end
end), 5, 10, 0) == 55);
return "OK";
