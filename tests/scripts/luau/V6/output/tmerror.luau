local u_tab = {};
setmetatable(u_tab, {__index = (function ()
   error("Error");
end)});
pcall((function ()
   u_tab.missingmethod();
end));
local u_tab_jx = {};
setmetatable(u_tab_jx, {__index = (function ()
   pcall((function ()
      error("Error");
   end));
end)});
pcall((function ()
   u_tab_jx.missingmethod();
end));
local u_tab_jy = {};
setmetatable(u_tab_jy, {__index = (function ()
   pcall(error, "Error");
end)});
pcall((function ()
   u_tab_jy.missingmethod();
end));
setmetatable({}, {__index = (function ()
   pcall(error);
end)});
return "OK";
