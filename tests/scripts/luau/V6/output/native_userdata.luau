print("testing userdata");
function ecall(...)
   local c_success, c_result = pcall(function, ...);
   assert(not c_success);
   return c_result:sub(((c_result:find(": ") or -1) + 2), #c_result);
end;
local c_res = vec2(5, 4);
local c_res_d = vec2(1, 2);
local c_res_e = vec2(10, 20);
local c_res_f = (function ()
   return -v_bd + (val * val_h);
end)(c_res, c_res_d, c_res_e);
assert(c_res_f.X == -5);
assert(c_res_f.Y == -12);
(function ()
   assert(v:Dot(v_r) == 13);
   local c_min = v_v:Min(v);
   assert(c_min.X == 5);
   assert(c_min.Y == 4);
end)(c_res, c_res_d, c_res_e);
(function ()
   assert(tab.Magnitude == 2);
   assert(tab.Unit.X == 0);
   assert(tab.Unit.Y == 1);
end)(vec2(0, 2));
return "OK";
