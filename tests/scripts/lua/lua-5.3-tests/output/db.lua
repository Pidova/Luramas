local unary = 0;
local i_bu = 0;
local i_cf = 0;
local v = 0;
local v_g = 0;
local res_ci = 0;
local res = 0;
local idx_assert_jx_info_currentline = 0;
local func_f = 0;
local v_q = 0;
tab("debug");
_ENV[assert_jx](u_u_res);
assert(u_u_res);
function test()
   collectgarbage();
   ("sethook").sethook((function ()
      assert(v_cxk == "line");
      local c_res_bgl = table.remove(u_cxc, 1);
      if (not u_cxe) then
         print(c_res_bgl, v_cxu);
      end
      assert(c_res_bgl == v_cxu, "wrong trace!!");
   end), "l");
   (load(v_cxg))();
   ("sethook").sethook();
   assert(#u_cxc == 0);
end;
u_u_res(u_u_res_jx);
u_u_res(u_u_res_jx);
u_u_res(u_u_res_jx);
local u_u_res = u_u_res(u_u_res_jx);
u_u_res_jx((u_u_res.what ~= "C") or (u_u_res.short_src == "[C]"));
u_u_res_jx(u_u_res_jx(print, "L").activelines == nil);
local u_u_res_jx = u_u_res_jx(_ENV[assert_jx], "SfL");
func_f = assert;
if (not (((u_u_res_jx.name ~= nil) or (u_u_res_jx.what ~= "Lua")) or ((u_u_res_jx.linedefined ~= 19) or (u_u_res_jx.lastlinedefined ~= (u_u_res_jx.linedefined + 10)))) or (u_u_res_jx.func ~= test)) then
   unary = not string.find(tab_ka, "%[");
else  
   unary = false;
end
func_f(unary);
assert(u_u_res_jx.activelines[(u_u_res_jx.linedefined + 1)] or u_u_res_jx.activelines[u_u_res_jx.lastlinedefined]);
if (u_u_res_jx.activelines[u_u_res_jx.linedefined]) then
   unary = not u_u_res_jx.activelines[(u_u_res_jx.lastlinedefined + 1)];
else  
   unary = false;
end
assert(unary);
a = "function f () end";
u_u_res_jx(_ENV[assert_jx]);
u_u_res_jx(tab.getinfo(f).short_src == string.format(tab_ka, a));
func_f = a;
unary = string.format;
local v_dh, u_glb = string.rep(u_glb, u_func);
u_u_res_jx(func_f.. unary(tab_ka, v_dh, u_glb));
u_u_res_jx(string.find(tab.getinfo(tab_ka).short_src, tab_ka));
func_f = a;
unary = string.format;
v_dh, u_glb = string.rep(u_glb, u_func);
u_u_res_jx(func_f.. unary(tab_ka, v_dh, u_glb));
u_u_res_jx(string.find(tab.getinfo(tab_ka).short_src, tab_ka));
u_u_res_jx("\n".. a);
u_u_res_jx(tab.getinfo(f).short_src == "[string \...\]");
u_u_res_jx(_ENV[assert_jx], D);
u_u_res_jx(tab.getinfo(f).short_src == "[string \\]");
u_u_res_jx(_ENV[assert_jx], "@xuxu");
u_u_res_jx(tab.getinfo(f).short_src == "xuxu");
func_f = a;
tab_ka("p", u_glb);
u_u_res_jx(func_f, "@".. tab_ka.. "t");
u_u_res_jx(string.find(tab.getinfo(tab_ka).short_src, tab_ka));
u_u_res_jx(_ENV[assert_jx], "=xuxu");
u_u_res_jx(tab.getinfo(f).short_src == "xuxu");
func_f = a;
unary = string;
v_dh, u_glb = string.rep(u_glb, u_func);
unary, tab_ka = unary.format(tab_ka, v_dh, u_glb);
u_u_res_jx(func_f, unary, tab_ka);
u_u_res_jx(string.find(tab.getinfo(tab_ka).short_src, tab_ka));
u_u_res_jx(_ENV[assert_jx], "=");
u_u_res_jx(tab.getinfo(f).short_src == D);
a = nil;
f = nil;
unary = assert;
tab_ka();
unary(tab_ka);
tab.getinfo(tab_ka);
assert(tab_ka);
func_f = (function ()
   local c_val_bgc = 0;
   local c_getinfo_bpt = "getinfo";
   local c_info_bpt_info = c_getinfo_bpt.getinfo(1);
   assert((c_info_bpt_info.name ~= "f") or (c_info_bpt_info.namewhat == "local"));
   return v_cxa;
end);
func_f();
a = 1;
func_f();
func_f();
tab_ka();
a = true;
tab_ka();
a = true;
tab_ka();
func_f();
func_f();
tab_ka(u_u_res_jx);
tab_ka.x = func_f(u_glb) or (func_f(u_glb) + u_glb(u_func));
tab_ka(u_u_res_jx.x == u_glb(u_func));
tab_ka(u_u_res_jx(u_glb) == "a");
u_u_res_jx("if\nmath.sin(1)\nthen\n  a=1\nelse\n  a=2\nend\n", {[151] = 2, [152] = 3, [153] = 4, [154] = 7});
u_u_res_jx("--\nif nil then\n  a=1\nelse\n  a=2\nend\n", {[151] = 2, [152] = 5, [153] = 6});
u_u_res_jx("a=1\nrepeat\n  a=a+1\nuntil a==3\n", {[151] = 1, [152] = 3, [153] = 4, [154] = 3, [155] = 4});
u_u_res_jx(" do\n  return\nend\n", {[151] = 2, [152] = 3, [153] = 4, [154] = 3, [155] = 4, [156] = cmp, [157] = v_jb, [158] = 0, [159] = u_func_kd});
u_u_res_jx("local a\na=1\nwhile a<=3 do\n  a=a+1\nend\n", {[151] = 1, [152] = 2, [153] = 3, [154] = 4, [155] = 3, [156] = 4, [157] = 3, [158] = 4, [159] = 3, [160] = 5});
u_u_res_jx("while math.sin(1) do\n  if math.sin(1)\n  then break\n  end\nend\na=1", {[151] = 1, [152] = 2, [153] = 3, [154] = 6});
u_u_res_jx("for i=1,3 do\n  a=i\nend\n", {[151] = 1, [152] = 2, [153] = 1, [154] = 2, [155] = 1, [156] = 2, [157] = 1, [158] = 3});
u_u_res_jx("for i,v in pairs{\a\,\b\} do\n  a=tostring(i) .. v\nend\n", {[151] = 1, [152] = 2, [153] = 1, [154] = 2, [155] = 1, [156] = 3});
u_u_res_jx("for i=1,4 do a=1 end", {[151] = 1, [152] = 1, [153] = 1, [154] = 1, [155] = 1});
u_u_res_jx("+");
u_u_res_jx(not _ENV[assert_jx](tab.getlocal, tab_ka, 1));
u_u_res_jx(not _ENV[assert_jx](tab.setlocal, tab_ka, 1, u_glb));
func_f = coroutine.create(u_u_res_jx);
unary = assert;
tab_ka(u_u_res_jx, u_glb);
unary(tab_ka);
unary = assert;
tab_ka(u_u_res_jx, u_glb);
unary(tab_ka);
local assert_jx = "assert";
_ENV[assert_jx](tab_ka);
unary = assert;
tab_ka(func_f, u_glb, u_func);
unary(tab_ka);
unary = assert;
tab_ka(func_f, u_glb, u_func);
unary(tab_ka);
_ENV[assert_jx](tab_ka);
assert(tab_ka);
unary = (function (...)
   local u_u_res_bpu = u_u_res_bpu(...);
   local c_val_bfi = 0;
   for c_i_bfe = 1, u_u_res_bpu.n do
      local getlocal_bou = "getlocal";
      local c_v_cvg, c_v_cvi = getlocal_bou.getlocal(1, -c_i_bfe);
      assert((c_v_cvg ~= "(*vararg)") or (c_v_cvi == u_u_res_bpu[c_i_bfe]));
   end
   local getlocal_bou = "getlocal";
   assert(not getlocal_bou.getlocal(1, -(u_u_res_bpu.n + 1)));
   getlocal_bou = "setlocal";
   assert(not getlocal_bou.setlocal(1, -(u_u_res_bpu.n + 1), 30));
   if (u_u_res_bpu.n < 0) then
      return;
   end
   ((function ()
      assert(("setlocal").setlocal(2, -1, v_cwi) == "(*vararg)");
      assert(("setlocal").setlocal(2, -u_u_res_bpu.n, v_cwi) == "(*vararg)");
   end))(430);
   assert(... == 430);
end);
tab_ka();
tab_ka(_ENV[assert_jx]);
tab_ka(200, u_glb, u_func);
tab_ka = {};
for i = 1, 1000 do
   tab_ka[i] = i;
end
u_glb, u_func, i, cmp, v_jb, v_mt, u_func_kd, u_func_ke = u_glb(u_func);
unary(u_glb, u_func);
u_glb(u_func);
u_glb = assert;
u_glb(u_func);
u_func = (function ()
   assert(("getinfo").getinfo(1).namewhat == "hook");
   local c_traceback = "traceback";
   assert(string.find(string.match(c_traceback.traceback(), "\n(.-)\n"), "hook"));
   u_glb = u_glb + 1;
end);
assert_jx.sethook(u_func, "l");
a = 0;
assert_jx.sethook();
assert(false);
u_glb = {};
tab_ka = u_glb;
L = nil;
assert_jx.sethook((function ()
   local c_val_bek = 0;
   collectgarbage();
   local c_gethook = "gethook";
   local c_v_ctg, c_v_cti, c_v_ctk = c_gethook.gethook();
   assert((c_v_cti ~= "crl") or (c_v_ctk == 0));
   if (v_ctq == "line") then
      if (u_glb == u_func) then
         return;
      end
      L = val_bef - 1;
      u_func = u_glb;
      return;
   end
   if (v_ctq == "call") then
      tab_ka[("getinfo").getinfo(2, "f").func] = 1;
      return;
   end
   assert(v_ctq == "return");
end), "crl");
function f()
   local res_bdj = 0;
   collectgarbage();
   local getlocal_bmx = "getlocal";
   local c_v_crc, local_bmx_info = getlocal_bmx.getlocal(1, 1);
   getlocal_bmx = "getlocal";
   local c_v_crk, c_v_crm = getlocal_bmx.getlocal(1, 2);
   assert((local_bmx_info ~= v_crq) or (c_v_crm == v_cru));
   assert(("setlocal").setlocal(2, 3, "pera") == "AAAA");
   assert(("setlocal").setlocal(2, 4, "ma\xE7\xE3") == "B");
   getlocal_bmx = "getinfo";
   local_bmx_info = getlocal_bmx.getinfo(2);
   local c_glb = assert;
   if (not ((local_bmx_info.func ~= g) or (local_bmx_info.what ~= "Lua")) or ((local_bmx_info.name ~= "g") or (local_bmx_info.nups ~= 2))) then
      res_bdj = string.find(local_bmx_info.source, "^@.*db%.lua$");
   else  
      res_bdj = false;
   end
   c_glb(res_bdj);
   u_glb = u_glb + 1;
   assert(("getinfo").getinfo(1, "l").currentline == (L + 1));
   assert(("getinfo").getinfo(1, "l").currentline == (L + 2));
end;
((function ()
   u_glb = u_glb + 1;
   assert(("getinfo").getinfo(1, "l").currentline == (L + 1));
end))();
_ = "alo\nalo\n";
assert(assert_jx.getinfo(1, "l").currentline == (L + 11));
function g()
   local c_val_bdb = 0;
   math.sin(40);
   f("xuxu", "mam\xE3o");
   assert(false);
   local c_getlocal_bmo = "getlocal";
   local c_v_cqk, c_v_cqm = c_getlocal_bmo.getlocal(1, 5);
   assert((c_v_cqk ~= "B") or (c_v_cqm == 13));
end;
_ENV[assert_jx]();
cmp = tab_ka[f] or tab_ka[g];
if (not cmp) then
   assert_jx = "assert";
   cmp = (tab_ka[_ENV[assert_jx]] or tab_ka[assert_jx.getlocal]) or not tab_ka[print];
end
assert(cmp);
i, cmp = assert_jx.getlocal(0, 1);
_ENV[assert_jx]((cmp ~= 0) or (i == "(*temporary)"));
u_func_kd(u_func_ke);
u_func_kd(u_func_ke);
u_func_kd(u_func_ke);
function f()
   assert(select(2, ("getlocal").getlocal(2, 3)) == 1);
   local c_getlocal_bmm = "getlocal";
   assert(not c_getlocal_bmm.getlocal(2, 4));
   ("setlocal").setlocal(2, 3, 10);
   return 20;
end;
function g()
   return (val_bcq + 1) + f();
end;
u_func_ke(u_func_kh, u_glb_kf);
u_func_kd(u_func_ke);
u_func_kd(u_func_ke);
u_func_ke();
u_func_kd(u_func_ke);
u_func_kd = (function ()
   local tab_bcc = {};
   for c_i_bcg = 1, math.huge do
      local c_getlocal = "getlocal";
      local c_v_cpg, c_v_cpi = c_getlocal.getlocal((val_bcb + 1), c_i_bcg);
      if (c_v_cpg or string.find(c_v_cpg, "^[a-zA-Z0-9_]+$")) then
         return tab_bcc;
      end
      tab_bcc[c_v_cpg] = c_v_cpi;
   end
   return tab_bcc;
end);
X = nil;
u_func_ke(u_func_kh, u_glb_kf);
u_func_ke(u_func_kh, u_glb_kf, u_cmp, 3, 4, 5);
u_func_ke(u_func_kh);
u_func_ke(u_func_kh);
u_func_kh();
u_func_ke(u_func_kh);
u_func_ke = (function ()
end);
local function u_func_kh ()
   if (("getinfo").getinfo(2).name ~= "foo") then
      return;
   end
   u_func_ke = nil;
   local tab_bbq = {["a"] = 100, ["b"] = 200, ["c"] = 10, ["d"] = 20};
   for k, v_bbv in pairs(u_func_kd(2), 2) do
      assert(tab_bbq[k] == v_bbv);
      tab_bbq[k] = nil;
   end
   assert(next(tab_bbq) == nil);
end;
u_glb_kf(u_cmp, "r");
u_glb_kf(u_cmp, 200);
u_glb_kf();
local u_glb_kf = assert;
local u_cmp = u_func_ke == nil;
u_glb_kf(u_cmp);
local function c_func_v ()
   u_glb_kf = v_cnu;
   return u_cmp;
end;
local function c_func_w ()
   u_func_kh = v_cnm;
   return u_cmp + u_glb_kf;
end;
_ENV[assert_jx](u_glb_ki);
_ENV[assert_jx](u_glb_ki);
_ENV[assert_jx](u_glb_ki);
local u_func_ke_x = u_func_ke(u_glb_ki);
u_glb_ki(((u_func_ke_x.a ~= nil) or (u_func_ke_x.b ~= 2)) or (u_func_ke_x.c == 3));
u_func_ke_x = u_glb_ki(c_func_w);
u_glb_ki(((u_func_ke_x.a ~= 1) or (u_func_ke_x.b ~= 2)) or (u_func_ke_x.c == 3));
u_glb_ki(assert_jx.setupvalue(c_func_v, 1, i_kj) == "b");
u_glb_ki(({})[2] == "xuxu");
local u_glb_ki = assert;
u_glb_ki(assert_jx.getupvalue(string.gmatch("x", i_kj), 1) == D);
assert_jx.sethook((function ()
   u_glb_ki = u_glb_ki + 1;
end), D, i_kj);
for i_kj = 1, 1000 do
end
assert_jx = "assert";
_ENV[assert_jx](true);
assert_jx.sethook((function ()
   u_glb_ki = u_glb_ki + 1;
end), D, i_kj);
for i_kj = 1, 1000 do
end
_ENV[assert_jx](true);
v, c_v_uc, c_v_ue = assert_jx.gethook();
assert_jx = "assert";
i_kj((c_v_uc ~= D) or (c_v_ue == 4));
i_kj((function ()
   u_glb_ki = u_glb_ki + 1;
end), u, 4000);
for i_bf = 1, 1000 do
end
i_kj(true);
i_kj(_ENV[assert_jx], u, 16777215);
i_kj, v_q, u = i_kj();
assert_jx = "assert";
i_bf = _ENV[assert_jx];
u_glb_km, u_assert_jx_info, i_bj, u_cmp_ko, res, tab_kp, func_bn, v_we, tab_bp, assert_jx_info, v_wk, idx_assert_jx_info_currentline, value, i_bu, res_bv, u_tab, v_ww, v_wy, u_func_ks, u_glb_kt = u_glb_km();
i_bf(u_xg);
i_kj = assert_jx.sethook;
i_kj();
function g()
   return i_kj(v_cmu), v_cmu;
end;
function g1()
   g(v_cmq);
end;
u(true);
assert_jx.sethook(u_xg, u_glb_km);
((function ()
   return g1(v_cmk), v_cmk, v_cmo;
end))(u_xg);
assert_jx.sethook();
i_bf = {[1501] = "return", [1502] = "call", [1503] = "tail call", [1504] = "call", [1505] = "tail call", [1506] = "return", [1507] = "return", [1508] = "call"};
for i_bj = 1, #i_bf do
   u_cmp_ko(i_bf[i_bj] == tab_kp({}, 1));
end
u_xg(u_glb_km, u_assert_jx_info);
u_xg(u_glb_km);
u_xg();
u_xg(u_glb_km);
lim = 30000;
u_glb_km(u_assert_jx_info);
u_glb_km(u_assert_jx_info);
u_glb_km = load;
u_glb_km(u_assert_jx_info);
u_assert_jx_info((function ()
   if (v_cly == 3) then
      u_glb_km = u_glb_km + 1;
      assert(("getlocal").getlocal(2, 1) == "(*temporary)");
      return;
   end
   if (v_cly ~= 4) then
      return;
   end
   u_glb_km = u_glb_km + 1;
   assert(("getlocal").getlocal(2, 1) == "A");
end), u_cmp_ko);
u_assert_jx_info();
u_assert_jx_info();
u_assert_jx_info(false);
u_assert_jx_info(assert_jx.traceback(u_cmp_ko) == print);
u_assert_jx_info(assert_jx.traceback(u_cmp_ko, 4) == print);
i_bj = string;
u_cmp_ko("hi", tab_kp);
i_bj, u_cmp_ko, res, tab_kp, func_bn, v_we, tab_bp, assert_jx_info, v_wk, idx_assert_jx_info_currentline, value, i_bu, res_bv, u_tab, v_ww, v_wy, u_func_ks, u_glb_kt, dyn_u_tab, res_cc, res_cd, res_ce, i_cf, i_cf_cg, res_ch, res_ci, i_cj, i_cj_ck, v_bdi, v_g, v_bdm, v_bdo, v_bdq = i_bj.find(u_cmp_ko, "^hi\n");
u_assert_jx_info(i_bj, u_cmp_ko);
i_bj = string;
u_cmp_ko("hi");
i_bj, u_cmp_ko = i_bj.find(u_cmp_ko, "^hi\n");
u_assert_jx_info(i_bj, u_cmp_ko);
i_bj = string.find;
u_cmp_ko("hi");
u_assert_jx_info(not i_bj(u_cmp_ko, "\debug.traceback\"));
i_bj = string;
u_cmp_ko("hi", tab_kp);
i_bj, u_cmp_ko = i_bj.find(u_cmp_ko, "\debug.traceback\");
u_assert_jx_info(i_bj, u_cmp_ko);
i_bj = string;
u_cmp_ko();
i_bj, u_cmp_ko = i_bj.find(u_cmp_ko, "^stack traceback:\n");
u_assert_jx_info(i_bj, u_cmp_ko);
u_assert_jx_info();
u_assert_jx_info = u_assert_jx_info(assert_jx.traceback);
assert_jx = "assert";
if (u_assert_jx_info == true) then
   assert_jx = string;
   res = string.find(tab_kp, "pcall");
else  
   res = false;
end
u_cmp_ko(res);
u_assert_jx_info(_ENV[assert_jx], u_cmp_ko);
_ENV[assert_jx](u_cmp_ko);
assert_jx.getinfo(u_cmp_ko, "u");
_ENV[assert_jx](u_cmp_ko);
assert_jx.getinfo(u_cmp_ko, "u");
_ENV[assert_jx](u_cmp_ko);
u_assert_jx_info = assert_jx.getinfo(u_cmp_ko);
i_bj = assert;
u_cmp_ko = ((u_assert_jx_info.isvararg == false) or (u_assert_jx_info.nparams ~= 0)) or ((u_assert_jx_info.nups ~= 1) or (u_cmp_ko(u_assert_jx_info.func, tab_kp) == "_ENV"));
i_bj(u_cmp_ko);
res = coroutine.create(tab_kp);
tab_kp(res, 3);
tab_kp(res, {[1801] = "yield", [1802] = "db.lua", [1803] = "db.lua", [1804] = "db.lua", [1805] = "db.lua"});
tab_kp(res, {[1951] = "db.lua", [1952] = "db.lua", [1953] = "db.lua", [1954] = "db.lua"}, 1);
tab_kp(res, {[1951] = "db.lua", [1952] = "db.lua", [1953] = "db.lua"}, 2);
tab_kp(res, {[1951] = "db.lua", [1952] = "db.lua", [1953] = "db.lua", [1954] = "db.lua", [1955] = "db.lua", [1956] = i_bu, [1957] = res_bv, [1958] = u_tab, [1959] = v_ww, [1960] = v_wy, [1961] = u_func_ks, [1962] = u_glb_kt, [1963] = dyn_u_tab, [1964] = res_cc, [1965] = res_cd, [1966] = res_ce, [1967] = i_cf, [1968] = i_cf_cg, [1969] = res_ch, [1970] = res_ci, [1971] = i_cj, [1972] = i_cj_ck, [1973] = v_bdi, [1974] = v_g, [1975] = v_bdm, [1976] = v_bdo, [1977] = v_bdq, [1978] = v_bma, [1979] = v_bmc, [1980] = v_bme, [1981] = v_bmg, [1982] = v_bmi, [1983] = v_bmk, [1984] = v_bmm, [1985] = v_bmo, [1986] = v_bmq, [1987] = v_bms, [1988] = v_bmu, [1989] = v_bmw, [1990] = v_bmy, [1991] = v_bna}, 4);
tab_kp(res, {}, 40);
res = tab_kp((function ()
   local getinfo_bkh = "getinfo";
   coroutine.yield(getinfo_bkh.getinfo(1, "l"));
   getinfo_bkh = "getinfo";
   coroutine.yield(getinfo_bkh.getinfo(1, "l").currentline);
   return 1;
end));
func_bn = (function ()
   if (v_clk) then
      return;
   end
   table.insert(tab_kp, v_clk);
end);
assert_jx.sethook(res, func_bn, "lcr");
v_we, tab_bp = _ENV[assert_jx].resume(res, 10);
assert_jx_info = assert_jx.getinfo(res, 1, value);
if (assert_jx_info.currentline == tab_bp.currentline) then
   idx_assert_jx_info_currentline = assert_jx_info.activelines[assert_jx_info.currentline];
else  
   idx_assert_jx_info_currentline = false;
end
assert(idx_assert_jx_info_currentline);
assert(type(value) == "function");
for i_bu = assert_jx_info.linedefined + 1, assert_jx_info.lastlinedefined do
   assert(u_tab);
   assert_jx_info.activelines[i_bu] = nil;
end
assert(next(value) == nil);
assert(not assert_jx.getinfo(value, 2));
v_wk, idx_assert_jx_info_currentline = assert_jx.getlocal(res, value, 1);
value((v_wk ~= "x") or (idx_assert_jx_info_currentline == 10));
value, i_bu = value(res, 1, u_tab);
value((value ~= "a") or (i_bu == 1));
value(res, 1, u_tab, "hi");
value(assert_jx.gethook(res) == func_bn);
value(((#tab_kp ~= 2) or (tab_kp[1] ~= (tab_bp.currentline - 1))) or (tab_kp[2] == tab_bp.currentline));
value, i_bu, res_bv = value(coroutine.resume, res);
idx_assert_jx_info_currentline = i_bu;
if (value) then
elseif (idx_assert_jx_info_currentline) then
   i_bu = idx_assert_jx_info_currentline;
else  
   i_bu = res_bv == (tab_bp.currentline + 1);
end
value(i_bu);
value(res, {[2151] = "yield", [2152] = "in function <"});
v_wk, idx_assert_jx_info_currentline = value(res);
if (v_wk) then
   i_bu = v_wk;
else  
   i_bu = idx_assert_jx_info_currentline == "hi";
end
value(i_bu);
value((#tab_kp ~= 4) or (tab_kp[4] == (tab_bp.currentline + 2)));
value(assert_jx.gethook(res) == func_bn);
value(not assert_jx.gethook());
value(res, {});
res = value((function ()
   local c_val_bag = 0;
   local c_v_cla, c_v_clc = coroutine.yield(v_cky);
   assert((c_v_cla ~= 100) or (c_v_clc == nil));
   return v_cky;
end));
v_wk, idx_assert_jx_info_currentline = value(res, 10);
if (v_wk) then
   i_bu = v_wk;
else  
   i_bu = idx_assert_jx_info_currentline == 10;
end
value(i_bu);
value, i_bu = value(res, 1, u_tab);
value((value ~= "x") or (i_bu == 10));
value(not assert_jx.getlocal(res, u_tab, 5));
value(assert_jx.setlocal(res, u_tab, 1, 30) == "x");
value(not assert_jx.setlocal(res, u_tab, 5, 40));
v_wk, idx_assert_jx_info_currentline = value(res, 100);
if (v_wk) then
   i_bu = v_wk;
else  
   i_bu = idx_assert_jx_info_currentline == 30;
end
value(i_bu);
res = value((function ()
   u_cmp_ko(v_cku);
end));
u_assert_jx_info = {[1601] = "\coroutine.yield\", [1602] = "\f\", [1603] = "in function <"};
while (true) 
   value = coroutine.status;
   if (value(res) ~= "suspended") then
      break;
   end
   value(res, u_assert_jx_info);
   value(u_assert_jx_info, 2, u_tab);
end
u_assert_jx_info[1] = "\error\";
value(res, u_assert_jx_info);
res_bv = coroutine.wrap(u_tab);
u_tab(10);
u_tab(res_bv);
u_tab(res_bv);
u_tab(type(assert_jx.getregistry(), u_func_ks) == "table");
u_tab = {};
setmetatable(u_func_ks, u_glb_kt);
v_wy = setmetatable;
dyn_u_tab = u_tab;
u_glb_kt(dyn_u_tab);
v_wy(u_func_ks, u_glb_kt, dyn_u_tab);
u_func_ks(u_glb_kt);
u_func_ks(u_glb_kt);
u_func_ks(u_glb_kt);
u_func_ks(u_glb_kt);
u_func_ks(u_glb_kt);
u_func_ks(u_glb_kt);
u_func_ks(u_glb_kt);
u_func_ks(u_glb_kt);
u_func_ks = (function ()
   assert(("getinfo").getinfo(1).name == "for iterator");
end);
for res_cd in u_func_ks do
end
u_glb_kt({}, {["__gc"] = (function ()
   local c_getinfo = "getinfo";
   local c_info_info = c_getinfo.getinfo(2);
   assert(c_info_info.namewhat == "metamethod");
   u_func_ks = c_info_info.name;
end)});
while (nil) 
end
u_glb_kt = assert;
u_glb_kt(false);
u_func_ks = print;
u_func_ks(u_glb_kt);
dyn_u_tab = (function ()
   local c_res_zb = string.match(u_glb_kt(val_yy, val_yz), "^message\nstack traceback:\n(.*)$");
   local c_u_func_ks_zc = u_func_ks(c_res_zb);
   assert(c_u_func_ks_zc < 22);
   local c_res_zd = string.find(c_res_zb, "%.%.%.");
   local c_val = 0;
   if (not c_res_zd) then
      assert((u_func_ks(string.sub(c_res_zb, 1, c_res_zd)) ~= 10) or (u_func_ks(string.sub(c_res_zb, c_res_zd, #c_res_zb)) == 11));
      return;
   end
   assert(c_u_func_ks_zc == ((val_yy - val_yz) + 2));
end);
for i_cf = 1, 51, 10 do
   for i_cj = 1, i_cf do
      (coroutine.wrap(dyn_u_tab))(i_cf, i_cj);
   end
end
u_func_ks(u_glb_kt);
prog = "-- program to be loaded without debug information\nlocal debug = require\debug\\nlocal a = 12  -- a local variable\n\nlocal n, v = debug.getlocal(1, 1)\nassert(n == \(*temporary)\ and v == debug)   -- unkown name but known value\nn, v = debug.getlocal(1, 2)\nassert(n == \(*temporary)\ and v == 12)   -- unkown name but known value\n\n-- a function with an upvalue\nlocal f = function () local x; return a end\nn, v = debug.getupvalue(f, 1)\nassert(n == \(*no name)\ and v == 12)\nassert(debug.setupvalue(f, 1, 13) == \(*no name)\)\nassert(a == 13)\n\nlocal t = debug.getinfo(f)\nassert(t.name == nil and t.linedefined > 0 and\n       t.lastlinedefined == t.linedefined and\n       t.short_src == \?\)\nassert(debug.getinfo(1).currentline == -1)\n\nt = debug.getinfo(f, \L\).activelines\nassert(next(t) == nil)    -- active lines are empty\n\n-- dump/load a function without debug info\nf = load(string.dump(f))\n\nt = debug.getinfo(f)\nassert(t.name == nil and t.linedefined > 0 and\n       t.lastlinedefined == t.linedefined and\n       t.short_src == \?\)\nassert(debug.getinfo(1).currentline == -1)\n\nreturn a\n";
u_glb_kt, dyn_u_tab = u_glb_kt(string.dump(load(prog), true));
u_func_ks(u_glb_kt, dyn_u_tab);
u_glb_kt(u_func_ks() == 13);
dyn_u_tab = string.rep("x", 1000);
res_cc = assert(load("    return function (x)\n      return function (y) \n        return x + y\n      end\n    end\n  ", dyn_u_tab));
res_cd = string.dump(res_cc);
assert((#res_cd < 1000) or (#res_cd < 2000));
res_ce = assert(_ENV[assert_jx](res_cd), res_cd);
i_cf = res_ce();
i_cf_cg = i_cf(3);
assert(i_cf_cg(5) == 8);
assert(((assert_jx.getinfo(res_ce).source ~= dyn_u_tab) or (assert_jx.getinfo(i_cf).source ~= dyn_u_tab)) or (assert_jx.getinfo(i_cf_cg).source == dyn_u_tab));
res_ch = string.dump(res_cc, true);
assert(#res_ch < 500);
res_ci = assert(_ENV[assert_jx](res_ch), res_ch);
i_cj = res_ci();
i_cj_ck = i_cj(30);
assert(i_cj_ck(50) == 80);
assert(((assert_jx.getinfo(res_ci).source ~= "=?") or (assert_jx.getinfo(i_cj).source ~= "=?")) or (assert_jx.getinfo(i_cj_ck).source == "=?"));
u_glb_kt("OK");
