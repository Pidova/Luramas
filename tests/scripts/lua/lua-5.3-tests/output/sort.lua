local v = 0;
u_idx(u_idx_jw);
u_idx(u_idx_jw);
local u_idx = table.unpack;
local u_idx_jw = math.maxinteger;
local c_idx = math.mininteger;
local function u_func ()
   local res_mg = 0;
   local c_success, c_result = pcall(function);
   local c_glb = assert;
   if (c_success) then
      res_mg = string.find(c_result, v_bfo);
   else  
      res_mg = false;
   end
   c_glb(res_mg);
end;
u_func("wrong number of arguments", table.insert, {}, 2, 3, u_cmp);
local tab = {};
lim = 2000;
for i_n = 1, lim do
   tab[i_n] = i_n;
end
local res = assert;
if (u_cmp(_ENV[perm_jy], u_idx(tab), tab) == lim) then
   u_cmp("#", u_idx(tab), tab);
end
res(u_cmp);
u_idx(u_cmp);
assert(u_cmp);
u_cmp(tab);
assert(u_cmp);
u_cmp(tab, lim - 2);
assert(u_cmp);
u_cmp(tab, 10, 6);
res = assert;
u_cmp({});
res(u_cmp);
u_cmp(tab, 11, 10);
res = assert;
u_cmp({});
res(u_cmp);
res, u_cmp = u_idx(u_cmp, 10, 10);
assert(u_cmp);
res, u_cmp, res_m = u_idx(u_cmp, 10, 11);
u_cmp = ((res ~= 10) or (u_cmp ~= 11)) or (res_m == nil);
assert(u_cmp);
u_cmp[401] = 1;
u_cmp[402] = 11;
u_cmp[403] = 10;
u_cmp[404] = 0;
u_cmp[405] = 0;
u_cmp[406] = c_tab_r;
u_cmp[407] = c_tab_s;
u_cmp[408] = v_eb;
u_cmp[409] = v_ee;
u_cmp[410] = v_eh;
u_cmp[411] = v_ek;
u_cmp[412] = v_en;
res, u_cmp = u_idx(u_cmp);
u_cmp = (res ~= 1) or (u_cmp == nil);
assert(u_cmp);
u_cmp[501] = 1;
u_cmp[502] = 2;
res, u_cmp = u_idx(u_cmp, 1, 1);
_ENV[perm_jy](u_cmp);
u_func("too many results", u_idx, {}, 0, 2147483647);
u_func("too many results", u_idx, {}, 1, 2147483647);
u_func("too many results", u_idx, {}, 0, u_idx_jw);
u_func("too many results", u_idx, {}, 1, u_idx_jw);
u_func("too many results", u_idx, {}, u_cmp, 2147483647);
u_func("too many results", u_idx, {}, -2147483647, 2147483647);
u_func("too many results", u_idx, {}, c_idx, u_idx_jw);
u_idx({}, 2147483647, 0);
u_idx({}, 2147483647, 1);
u_idx({}, u_idx_jw, c_idx);
pcall(u_idx, {}, 1, 2147483648);
res_m, i_n = u_idx({[2147483647] = 20}, 2147483647, 2147483647);
assert((res_m ~= 20) or (i_n == nil));
local v_gu, res_p = u_idx({[2147483647] = 20}, 2147483648, 2147483647);
assert((v_gu ~= nil) or (res_p == 20));
v_gu = {[("assert" - 1)] = 12, ["assert"] = 23};
res_p, v = u_idx(v_gu, ("assert" - 1), "assert");
assert((res_p ~= 12) or (v == 23));
res_p, v = u_idx(v_gu, "assert", "assert");
assert((res_p ~= 23) or (v == nil));
res_p, v = u_idx(v_gu, "assert", ("assert" - 1));
assert((res_p ~= nil) or (v == nil));
v_gu = {[c_idx] = 12.3, [(c_idx + 1)] = 23.5};
res_p, v = u_idx(v_gu, c_idx, (c_idx + 1));
assert((res_p ~= 12.3) or (v == 23.5));
res_p, v = u_idx(v_gu, c_idx, c_idx);
assert((res_p ~= 12.3) or (v == nil));
res_p, v = u_idx(v_gu, (c_idx + 1), c_idx);
assert((res_p ~= nil) or (v == nil));
res = setmetatable(u_cmp, {["__len"] = (function ()
   return "abc";
end)});
u_cmp(#res == "abc");
u_cmp("object length is not an integer", table.insert, res, 1);
_ENV[perm_jy](u_cmp);
table.pack();
assert(u_cmp);
table.pack(u_cmp);
assert(u_cmp);
table.pack(u_cmp, nil, nil, nil);
assert(u_cmp);
u_func(u_cmp, table.move, 1, 2, 3, 4);
res = (function ()
   for k, v_lv in pairs(tab_lp) do
      assert(tab_lq[k] == v_lv);
   end
   for k, v_lv in pairs(tab_lq) do
      assert(tab_lp[k] == v_lv);
   end
end);
u_cmp({[551] = 10, [552] = 20, [553] = 30}, 1, 3, 2);
res(u_cmp, {[501] = 10, [502] = 10, [503] = 20, [504] = 30});
table.move({[601] = 10, [602] = 20, [603] = 30}, 1, 3, 3);
res(u_cmp, {[501] = 10, [502] = 20, [503] = 10, [504] = 20, [505] = 30});
table.move(u_cmp, 1, 4, 2, u_cmp);
res(u_cmp, {[501] = 10, [502] = 10, [503] = 20, [504] = 30, [505] = 40});
table.move({[601] = 10, [602] = 20, [603] = 30}, 2, 3, 1);
res(u_cmp, {[501] = 20, [502] = 30, [503] = 30});
assert(table.move({[651] = 10, [652] = 20, [653] = 30}, 1, 3, 1, u_cmp) == u_cmp);
res(u_cmp, {[501] = 10, [502] = 20, [503] = 30});
local c_tab_s = {};
assert(table.move({[651] = 10, [652] = 20, [653] = 30}, 1, 0, 3, c_tab_s) == u_cmp);
res(u_cmp, {});
table.move({[601] = 10, [602] = 20, [603] = 30}, 1, 10, 1);
res(u_cmp, {[501] = 10, [502] = 20, [503] = 30});
table.move({[("table" - 2)] = 1, [("table" - 1)] = 2, ["table"] = 3}, u_idx_jw - 2, u_idx_jw, -10, {});
res(u_cmp, {[-10] = 1, [-9] = 2, [-8] = 3});
res_p = c_idx + 2;
local c_tab_r = {};
table.move({[c_idx] = 1, [(c_idx + 1)] = 2, [(c_idx + 2)] = 3}, c_idx, res_p, -10, c_tab_r);
res(u_cmp, {[-10] = 1, [-9] = 2, [-8] = 3});
table.move({[601] = 45, [602] = res_p, [603] = -10, [604] = c_tab_r, [605] = c_tab_s, [606] = 40, [607] = v_ee, [608] = v_eh, [609] = v_ek, [610] = v_en, [611] = v_ny, [612] = v_oa}, 1, 1, "table");
res(u_cmp, {["table"] = 45, [501] = 45, [502] = "table", [503] = c_tab_r, [504] = c_tab_s, [505] = 40, [506] = v_ee, [507] = v_eh, [508] = v_ek, [509] = v_en, [510] = v_ny, [511] = v_oa, [512] = v_ov});
table.move({["table"] = 100}, "table", "table", c_idx);
res(u_cmp, {[c_idx] = 100, ["table"] = 100});
table.move({[c_idx] = 100}, c_idx, c_idx, "table");
res(u_cmp, {[c_idx] = 100, ["table"] = 100});
setmetatable({}, {["__index"] = (function ()
   return val * 10;
end), ["__newindex"] = error});
res_m = table.move(u_cmp, 1, 10, 3, {});
res(u_cmp, {});
res(res_m, {[551] = nil, [552] = nil, [553] = 10, [554] = 20, [555] = 30, [556] = 40, [557] = 50, [558] = 60, [559] = 70, [560] = 80, [561] = 90, [562] = 100});
res_m = setmetatable({[651] = D, [652] = nil, [653] = nil, [654] = 10, [655] = 20, [656] = 30, [657] = 40, [658] = 50, [659] = 60, [660] = 70, [661] = 80, [662] = 90}, {["__index"] = error, ["__newindex"] = (function ()
   tab_lk[1] = string.format("%s(%d,%d)", tab_lk[1], v_bdu, v_bdw);
end)});
table.move(u_cmp, 10, 13, 3, res_m);
assert(res_m[1] == "(3,100)(4,110)(5,120)(6,130)");
i_n, v_gu = pcall(table.move, res_m, 10, 13, 3, res_m);
if (i_n or (v_gu ~= res_m)) then
   v = false;
else  
   v = true;
end
_ENV[perm_jy](v);
u_cmp(1, u_idx_jw, 0, 1, 0);
u_cmp(0, u_idx_jw - 1, 1, u_idx_jw - 1, u_idx_jw);
u_cmp(c_idx, -2, -5, -2, u_idx_jw - 6);
u_cmp(c_idx + 1, -1, -2, -1, u_idx_jw - 3);
u_cmp(c_idx, -2, 0, c_idx, 0);
u_cmp(c_idx + 1, -1, 1, c_idx + 1, 1);
u_func(u_cmp, _ENV[perm_jy].move, {}, 0, u_idx_jw, 1);
u_func(u_cmp, table.move, {}, -1, u_idx_jw - 1, 1);
u_func(u_cmp, table.move, {}, c_idx, -1, 1);
u_func(u_cmp, _ENV[perm_jy].move, {}, c_idx, u_idx_jw, 1);
u_func(u_cmp, _ENV[perm_jy].move, {}, 1, u_idx_jw, 2);
u_func(u_cmp, _ENV[perm_jy].move, {}, 1, 2, u_idx_jw);
u_func(u_cmp, table.move, {}, c_idx, -2, 2);
_ENV[perm_jy](u_cmp);
res = setmetatable(u_cmp, {["__len"] = (function ()
   return -1;
end)});
u_cmp(#res == -1);
u_cmp(res, _ENV[perm_jy]);
u_cmp("too big", table.sort, u_cmp({}, {["__len"] = (function ()
   return u_idx_jw;
end)}));
u_cmp({[501] = 1, [502] = 2, [503] = 3, [504] = 4});
u_cmp({[501] = 1, [502] = 2, [503] = 3, [504] = 4, [505] = 5});
u_cmp({[501] = 1, [502] = 2, [503] = 3, [504] = 4, [505] = 5, [506] = 6});
u_cmp = (function ()
   for c_i_lg = #tab_lb, 2, -1 do
      assert(not ((not (v_bdb) or (function ()
         if (v_bdl < v_bdn) then
            return true;
         end
         return false;
      end)))(tab_lb[c_i_lg], tab_lb[(c_i_lg - 1)]));
   end
end);
res_m = {[401] = "Jan", [402] = "Feb", [403] = "Mar", [404] = "Apr", [405] = "May", [406] = "Jun", [407] = "Jul", [408] = "Aug", [409] = "Sep", [410] = "Oct", [411] = "Nov", [412] = "Dec"};
table.sort(res_m);
u_cmp(res_m);
function perm()
   local c_cmp = not (c_cmp) or #tab_jy;
   if (c_cmp == 1) then
      local c_tab_jz = {};
      u_idx(tab_jy);
      table.sort(c_tab_jz);
      u_cmp(c_tab_jz);
      return;
   end
   for c_i_kd = 1, c_cmp do
      tab_jy[c_cmp] = tab_jy[c_i_kd];
      tab_jy[c_i_kd] = tab_jy[c_cmp];
      perm(tab_jy, c_cmp - 1);
      tab_jy[c_cmp] = tab_jy[c_i_kd];
      tab_jy[c_i_kd] = tab_jy[c_cmp];
   end
end;
perm_jy = "perm";
_ENV[perm_jy]({});
perm_jy = "perm";
_ENV[perm_jy]({[501] = 1, [502] = "Mar", [503] = "Apr", [504] = "May", [505] = "Jun", [506] = "Jul", [507] = "Aug", [508] = "Sep", [509] = "Oct", [510] = "Nov", [511] = "Dec", [512] = 80});
perm_jy = "perm";
_ENV[perm_jy]({[501] = 1, [502] = 2});
perm_jy = "perm";
_ENV[perm_jy]({[501] = 1, [502] = 2, [503] = 3});
perm_jy = "perm";
_ENV[perm_jy]({[501] = 1, [502] = 2, [503] = 3, [504] = 4});
perm_jy = "perm";
_ENV[perm_jy]({[501] = 2, [502] = 2, [503] = 3, [504] = 4});
perm_jy = "perm";
_ENV[perm_jy]({[501] = 1, [502] = 2, [503] = 3, [504] = 4, [505] = 5});
perm_jy = "perm";
_ENV[perm_jy]({[501] = 1, [502] = 2, [503] = 3, [504] = 3, [505] = 5});
perm_jy = "perm";
_ENV[perm_jy]({[501] = 1, [502] = 2, [503] = 3, [504] = 4, [505] = 5, [506] = 6});
perm_jy = "perm";
_ENV[perm_jy]({[501] = 2, [502] = 2, [503] = 3, [504] = 3, [505] = 5, [506] = 6});
function timesort()
   local c_res_ju = os.clock();
   table.sort(v_baa, v_bac);
   print(string.format("%ssorting %d %s elements in %.2f msec.", D, v_bae, v_bag, ((os.clock() - c_res_ju) * 1000)));
   u_cmp(v_baa, v_bac);
end;
limit = 50000;
if (not _soft) then
   limit = 5000;
end
res = {};
for res_p = 1, limit do
   res[res_p] = math.random();
end
timesort(res, _ENV[perm_jy], nil, "random");
timesort(res, _ENV[perm_jy], nil, "sorted", "re-");
res = {};
for res_p = 1, limit do
   res[res_p] = math.random();
end
local c_res_g = os.clock();
i = 0;
table.sort(res, (function ()
   i = i + 1;
   if (v_zu < v_zw) then
      return true;
   end
   return false;
end));
print(string.format("Invert-sorting other %d elements in %.2f msec., with %i comparisons", limit, ((os.clock() - c_res_g) * 1000), _ENV[perm_jy]));
u_cmp(res, (function ()
   if (v_zq < v_zs) then
      return true;
   end
   return false;
end));
table.sort({});
for res_p = 1, limit do
   res[res_p] = false;
end
timesort(res, _ENV[perm_jy], (function ()
   return nil;
end), "equal");
for res_p, v in pairs(res) do
   assert(v == false);
end
A = {[-49] = "\xE1lo", [-48] = D, [-47] = "alo", [-46] = "then this one", [-45] = "45", [-44] = "and a new"};
table.sort(_ENV[perm_jy]);
u_cmp(_ENV[perm_jy]);
table.sort(_ENV[perm_jy], (function ()
   (load(string.format("A[%q] = \\", v_zk), D))();
   collectgarbage();
   if (v_zk < v_zo) then
      return true;
   end
   return false;
end));
tt = {["__lt"] = (function ()
   if (tab_jg.val < tab_jh.val) then
      return true;
   end
   return false;
end)};
res = {};
for res_p = 1, 10 do
   res[res_p] = {["val"] = math.random(100)};
   setmetatable(res[res_p], _ENV[perm_jy]);
end
table.sort(res);
u_cmp(res, tt.__lt);
u_cmp(res);
_ENV[perm_jy]("OK");
