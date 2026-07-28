if (not _soft) then
   return "a";
end
print("testing large tables");
require("debug");
local tab = {};
for c_i = 1, 263144 do
   tab[#tab + 1] = v;
end
