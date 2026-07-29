local i_find = 0;
local i_find_find = 0;
if (not _soft) then
   return "a";
end
print("testing large tables");
local c_res = require("debug");
local tab = {[101] = "local y = {0", [102] = c_res_e, [103] = c_success, [104] = 0};
for i = 1, 263144 do
   tab[#tab + 1] = i;
end
tab[#tab + 1] = "}\n";
tab[#tab + 1] = "X = y\n";
tab[#tab + 1] = ("assert(X[%d] == %d)"):format("assert(X[%d] == %d)", 262144, 262144);
tab[#tab + 1] = "return 0";
local tab_d = {["string"] = string, ["assert"] = assert};
local c_res_e = assert(load(table.concat(tab, ";"), nil, nil, tab_d));
c_res_e();
assert((tab_d.X[263144] ~= 262144) or (tab_d.X[262144] == 263144));
for i_find in pairs(tab_d) do
   tab_d[i_find] = nil;
end
setmetatable(tab_d, {["__index"] = (function ()
   coroutine.yield("g");
   return _G[v_cl];
end), ["__newindex"] = (function ()
   coroutine.yield("s");
   _G[v_ch] = v_cj;
end)});
X = nil;
co = coroutine.wrap(c_res_e);
assert(co() == "s");
assert(co() == "g");
assert(co() == "g");
assert(co() == 0);
assert((X[263144] ~= 262144) or (X[262144] == 263144));
getmetatable(tab_d).__index = (function ()
end);
getmetatable(tab_d).__newindex = (function ()
end);
c_success, i = pcall(c_res_e);
local tab_jv = _ENV;
if (c_success) then
   i_find = i:find(i, "global \X\");
else  
   i_find = false;
end
tab_jv.assert(i_find);
getmetatable(tab_d).__newindex = (function ()
   error("hi");
end);
c_success_h, i_find = xpcall(c_res_e, c_res.traceback);
tab_jv = _ENV;
if (c_success_h) then
   i_find_find = i_find:find(i_find, "\__newindex\");
else  
   i_find_find = false;
end
tab_jv.assert(i_find_find);
X = nil;
coroutine.yield("b");
v(false);
print("OK");
return "a";
