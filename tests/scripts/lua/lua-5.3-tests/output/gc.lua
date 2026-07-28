print("testing garbage collection");
require("debug");
collectgarbage();
assert(collectgarbage("isrunning"), "isrunning");
collectgarbage("setpause", 200);
collectgarbage("setstepmul", 200);
local c_tab = {[207] = 30000, [208] = 2147483646, [209] = u, [210] = u_idx_tab, [211] = v, [212] = v_g, [213] = v_i};
for c_i = 1, #c_tab do
   for c_i_k = 1, #c_tab do
      local u_idx_tab = c_tab[u];
      collectgarbage("setpause", c_tab[90]);
      collectgarbage("setstepmul", u_idx_tab);
      collectgarbage("step", 0);
      collectgarbage("step", 10000);
   end
end
