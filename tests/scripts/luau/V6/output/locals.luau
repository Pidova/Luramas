print("testing local variables plus some extra stuff");
assert(true);
assert(true);
assert(true);
assert(true);
f = nil;
x = 1;
a = nil;
loadstring("local a = {}")();
assert(type(a) ~= "table");
local function c_func ()
   assert(if (v_m == v_m) then (v_m == 2) else nil);
   assert(true);
end;
assert(false);
assert(x == 1);
c_func(2);
assert(type(c_func) == "function");
local tab = {};
for c_i = 1, 10 do
   tab[c_i] = (function ()
      A += 1;
      return A, u.getfenv(v);
   end);
end
