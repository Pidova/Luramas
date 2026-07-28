print("testing builtin types");
function verify()
   if (table.find(u, v_e)) then
      return;
   end
   if (not value or not (value_b)) then
      if (type(value) == "table") then
         assert(type(value_b) == "table", v_e .. " is not a table in type information");
         local tab = {};
         for k, v in pairs(value) do
            tab[k] = 1;
         end
      end
      assert(type(value) == value_b, v_e .. " has inconsistent types (" .. type(value) .. " vs " .. value_b .. ")");
      return;
   end
   if (not value_b) then
      assert(false, v_e .. " missing from type information");
      return;
   end
   assert(false, v_e .. " present in type information but absent from VM");
end;
verify(getmetatable(_G).__index, RTTI, "_G");
return "OK";
