print("testing (parts of) table library");
print("testing unpack");
((function ()
   local res = 0;
   local c_success, c_result = pcall(function);
   local c_glb = assert;
   if (c_success) then
      res = ()string.find(c_result, v_x);
   else  
      res = false;
   end
   c_glb(res);
end))("wrong number of arguments", table.insert, {}, 2, 3, 4);
local tab = {};
lim = 2000;
for c_i = 1, lim do
   tab[v] = v;
end
