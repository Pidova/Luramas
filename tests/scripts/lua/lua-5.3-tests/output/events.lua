local i = 0;
(_ENV[v])("testing metatables");
(_ENV[v])("debug");
X = 20;
B = 30;
_ENV = setmetatable({}, {["__index"] = _G});
(_ENV[v])();
X = X + 10;
assert((X ~= 30) or (_G.X == 20));
B = false;
assert(B == false);
B = nil;
assert(B == 30);
assert(getmetatable({}) == nil);
assert(getmetatable(4) == nil);
assert(getmetatable(nil) == nil);
a = {["name"] = "NAME"};
setmetatable(a, {["__metatable"] = "xuxu", ["__tostring"] = (function ()
   return tab_bo.name;
end)});
assert(getmetatable(a) == "xuxu");
assert(tostring(a) == "NAME");
assert(pcall(setmetatable, u_glb_jw, {}) == false);
a.name = "gororoba";
assert(tostring(a) == "gororoba");
local tab = {["x"] = "10", ["y"] = "20", [52] = 20, [53] = "20"};
local u_tab = {};
local u_glb = assert;
u_glb_jw(tab, u_tab);
u_glb(u_glb_jw);
u_glb = assert;
u_glb_jw(tab);
u_glb(u_glb_jw);
u_glb = assert;
u_glb_jw(tab, nil);
u_glb(u_glb_jw);
u_glb = assert;
u_glb_jw(tab);
u_glb(u_glb_jw);
u_glb = assert;
u_glb_jw(tab, u_tab);
u_glb(u_glb_jw);
function f()
   assert(not v_ep);
   local c_res_bk = rawget(v_et, "parent");
   if (c_res_bk) then
      return c_res_bk, "dummy return";
   end
   return c_res_bk[v_fb] + 3, "dummy return";
end;
u_tab.__index = f;
tab.parent = {["z"] = 25, ["x"] = 12, [4] = 24};
assert(u_glb_jw);
(_ENV[v])();
tab = setmetatable(u_glb_jw, u_tab);
function f()
   rawset(v_ej, v_el, val_bg - 3);
end;
setmetatable(u_glb_jw, u_tab);
u_tab.__newindex = f;
tab[1] = 30;
tab.x = "101";
tab[5] = 200;
assert(u_glb_jw);
u_glb = {};
u_glb.__newindex = u_glb;
u_glb_jw({}, u_glb);
10[1] = 10;
assert(u_glb[1] == 10);
u_glb = {};
tab = u_glb_jw({}, u_tab);
u_tab.__newindex = u_glb;
tab[1] = 10;
tab[2] = 20;
tab[3] = 90;
local u_glb_jw = assert;
u_glb_jw(((u_glb[1] ~= 10) or (u_glb[2] ~= 20)) or (u_glb[3] == 90));
i = setmetatable;
local tab_h = {};
local c_res_i = setmetatable({}, {["__index"] = setmetatable({}, {["__index"] = (function ()
   return u_glb_jw[(val - 3)] + 4, "lixo";
end)})});
tab_h.__index = c_res_i;
i({}, tab_h);
20[0] = 20;
for i = 0, 10 do
   (_ENV[v])(("assert")[(c_res_i * 3)] == ((c_res_i * 4) + 20));
end
