print("testing metatables");
assert(getmetatable({}) == nil);
assert(getmetatable(4) == nil);
assert(getmetatable(nil) == nil);
a = {};
setmetatable(a, {__metatable = "xuxu", __tostring = (function ()
   return tab_j.name;
end)});
assert(getmetatable(a) == "xuxu");
ud = newproxy(true);
getmetatable(ud).__metatable = "xuxu";
assert(getmetatable(ud) == "xuxu");
assert(pcall(getmetatable) == false);
assert(pcall((function ()
   return getmetatable();
end)) == false);
local success_b = assert;
local tab = select;
local success, function = pcall(function, {});
success_b(tab(2, success) == nil);
success_b = assert;
tab = select;
success, function = pcall(function, ud);
success_b(tab(2, success) == "xuxu");
success_b, c_result = pcall(tostring, a);
assert(not success_b and (c_result == "\'__tostring\' must return a string"));
assert(pcall(function, a, {}) == function);
a.name = "gororoba";
assert(tostring(function) == function);
tab = {
   10, 
   20, 
   30, 
   x = "10", 
   y = "20"};
local u_tab = {};
success = assert;
function = setmetatable(tab, u_tab) == tab;
success(function);
success = assert;
function = getmetatable(tab) == u_tab;
success(function);
success = assert;
function = setmetatable(tab, nil) == tab;
success(function);
success = assert;
function = getmetatable(tab) == nil;
success(function);
success = assert;
function = setmetatable(tab, u_tab) == tab;
success(function);
function f()
   assert(not v_dp);
   local c_res_f = rawget(v_dt, "parent");
   if (not c_res_f) then
      return c_res_f, "dummy return";
   end
   return c_res_f[v_eb] + 3, "dummy return";
end;
u_tab.__index = f;
tab.parent = {z = 25, x = 12, [4] = 24};
assert(function);
collectgarbage();
tab = setmetatable(function, u_tab);
function f()
   rawset(v, v_dl, val_c - 3);
end;
u_tab.__newindex = f;
tab[1] = 30;
tab.x = "101";
tab[5] = 200;
assert(function);
success = {};
tab = function({}, u_tab);
u_tab.__newindex = success;
tab[1] = 10;
tab[2] = 20;
tab[3] = 90;
function = assert;
function(success[1] == 10);
setmetatable({}, {__index = setmetatable({}, {__index = setmetatable({}, {__index = (function ()
   return function[(val - 3)] + 4, "lixo";
end)})})})[0] = 20;
for c_i = 0, 10 do
   assert(function[(c_i * 3)] == ((c_i * 4) + 20));
end
