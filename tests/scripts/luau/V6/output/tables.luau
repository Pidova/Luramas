print("testing tables, next, and for");
local tab = assert;
local u_glb = select;
local u, u_e = table.insert({}, 42);
tab(u_glb("#", u) == 0);
tab = {};
for c_i = 1, 100 do
   tab[c_i .. "+"] = true;
end
