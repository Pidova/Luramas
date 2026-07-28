print("safeenv reset");
(function ()
   local c_idx = setmetatable({}, {__index = (function ()
      getfenv().math = {abs = (function ()
         return val * val;
      end)};
      return 2;
   end)}).x;
   assert(math.abs(10) == 100);
end)();
return "OK";
