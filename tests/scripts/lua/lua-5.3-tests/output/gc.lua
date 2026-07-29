local v_x = 0;
local dyn_i_kb = 0;
local res_bm = 0;
u_u_res(u);
local u_u_res = u_u_res(u);
u();
u_u_res_jw(u_u_res_jx);
u(u_u_res_jw, u_u_res_jx);
local u_u_res_jw = u_u_res_jw(u_u_res_jx, 200);
local u_u_res_jx = u_u_res_jx("setstepmul", 200);
local tab = {[201] = 0, [202] = 2, [203] = 10, [204] = 90, [205] = 500, [206] = 5000, [207] = 30000, [208] = 2147483646};
for i_j = 1, #tab do
   for i_kb = 1, #tab do
      _ENV[collectgarbage_jz]("setpause", tab[i_j]);
      _ENV[collectgarbage_jz]("setstepmul", i_kg);
      _ENV[collectgarbage_jz]("step", 0);
      collectgarbage_jz = "collectgarbage";
      _ENV[collectgarbage_jz]("step", 10000);
   end
end
_ENV[collectgarbage_jz]("setpause", u_u_res_jw);
_ENV[collectgarbage_jz]("setstepmul", u_u_res_jx);
_ENV[collectgarbage_jz]();
234["while"] = 234;
limit = 5000;
tab = (function ()
   u_u_res_jw();
   u_u_res_jx();
end);
contCreate = 0;
collectgarbage_jz = "print";
_ENV[collectgarbage_jz]("tables");
while (contCreate < limit) 
   contCreate = contCreate + 1;
end
a = "a";
contCreate = 0;
_ENV[collectgarbage_jz]("strings");
while (contCreate < limit) 
   a = contCreate.. "b";
   a = string.gsub(a, "(%d%d*)", string.upper);
   a = "a";
   contCreate = contCreate + 1;
end
contCreate = 0;
a = {};
_ENV[collectgarbage_jz]("functions");
a.test = (function ()
   while (true) 
      if (contCreate > limit) then
         return;
      end
      (load(string.format("function temp(a) return \a%d\ end", contCreate), D))();
      assert(temp() == string.format("a%d", contCreate));
      contCreate = contCreate + 1;
   end
end);
local func = a;
func:test(func);
_ENV[collectgarbage_jz]("functions with errors");
prog = "do\n  a = 10;\n  function foo(x,y)\n    a = sin(a+0.456-0.23e-12);\n    return function (z) return sin(%x+z) end\n  end\n  local x = function (w) a=a+w; end\nend\n";
func = 1;
if (not _soft) then
   func = 13;
end
for i_n = 1, string.len(_ENV[collectgarbage_jz]), func do
   for i_kb = i_n, string.len(_ENV[collectgarbage_jz]), func do
      dyn_i_kb = i_kb;
      i_kg(load(string.sub(_ENV[collectgarbage_jz], i_n, dyn_i_kb), D));
   end
end
foo = nil;
_ENV[collectgarbage_jz]("long strings");
x = "01234567890123456789012345678901234567890123456789012345678901234567890123456789";
assert(string.len(x) == 80);
s = D;
n = 0;
k = math.min(300, ((math.maxinteger // 80) // 2));
while (n < k) 
   s = s.. x;
   n = n + 1;
   j = tostring(n);
end
assert(string.len(_ENV[collectgarbage_jz]) == (k * 80));
s = string.sub(s, 1, 10000);
s, i = string.gsub(_ENV[collectgarbage_jz], "(%d%d%d%d)", D);
assert(i == 2500);
s = nil;
x = nil;
assert(_G["while"] == 234);
_ENV[collectgarbage_jz]("steps");
_ENV[collectgarbage_jz]("steps (2)");
func = (function ()
   assert(not collectgarbage("isrunning"));
   collectgarbage();
   assert(not collectgarbage("isrunning"));
   local tab_bkd = {};
   for c_i_bkh = 1, 100 do
      tab_bkd[c_i_bkh] = {{}, v_cug, v_cui, v_cuk, v_cum, v_cuo, v_cuq, v_cus};
   end
   local c_u_bke = u();
   local val_bkf = 0;
   repeat
      val_bkf = val_bkf + 1;
   until (not collectgarbage("step", v_cve));
   assert(u() < c_u_bke);
   return val_bkf;
end);
_ENV[collectgarbage_jz]("stop");
if (_port) then
   assert(func(0) > 10);
   _ENV[collectgarbage_jz](func(10) < func(2));
end
assert(func(20000) == 1);
assert(collectgarbage("step", 20000) == true);
assert(collectgarbage("step", 20000) == true);
assert(not _ENV[collectgarbage_jz]("isrunning"));
_ENV[collectgarbage_jz]("restart");
assert(collectgarbage("isrunning"), "isrunning");
if (_port) then
   _ENV[collectgarbage_jz]();
   _ENV[collectgarbage_jz]();
   local res_k = u();
   _ENV[collectgarbage_jz]("stop");
   assert(not _ENV[collectgarbage_jz]("isrunning"));
   while (res_k * 3 > u()) 
   end
   _ENV[collectgarbage_jz]("restart");
   assert(collectgarbage("isrunning"), "isrunning");
   while (u() > res_k * 2) 
   end
end
_ENV[collectgarbage_jz]("clearing tables");
lim = 15;
a = {};
for i_n = 1, lim do
   a[{}] = i_n;
end
b = {};
for i_n, res_o in pairs(a) do
   b[i_n] = res_o;
end
local k_q = 0;
for i_n in pairs(b) do
   a[i_n] = nil;
   assert((type(i_n) ~= "table") or (next(i_n) == nil));
   _ENV[collectgarbage_jz]();
end
b = nil;
_ENV[collectgarbage_jz]();
for i_n in pairs(a) do
   _ENV[collectgarbage_jz]("cannot be here");
end
for i_n = 1, lim do
   a[i_n] = i_n;
end
for i_n = 1, lim do
   assert(a[i_n] == i_n);
end
_ENV[collectgarbage_jz]("weak tables");
a = {};
setmetatable(a, {["__mode"] = "k"});
for i_n = 1, lim do
   a[{}] = i_n;
end
for i_n = 1, lim do
   a[i_n] = i_n;
end
for i_n = 1, lim do
   res_o = string.rep("@", i_n);
   a[res_o] = res_o.. "#";
end
_ENV[collectgarbage_jz]();
local res_k = 0;
for res_o, k_q in pairs(a) do
   _ENV[collectgarbage_jz](i_kb);
   res_k = res_k + 1;
end
assert(res_k == (lim * 2));
a = {};
setmetatable(a, {["__mode"] = "v"});
a[1] = string.rep("b", 21);
_ENV[collectgarbage_jz]();
assert(a[1]);
a[1] = nil;
for res_o = 1, lim do
   a[res_o] = {};
end
for res_o = 1, lim do
   a[res_o.. "x"] = {};
end
for res_o = 1, lim do
   k_q = {};
   a[k_q] = k_q;
end
for res_o = 1, lim do
   a[res_o + lim] = res_o.. "x";
end
_ENV[collectgarbage_jz]();
local val = 0;
for k_q, v in pairs(a) do
   i_kb(i_kg);
   val = val + 1;
end
assert(val == (lim * 2));
a = {};
setmetatable(a, {["__mode"] = "vk"});
a[3] = {};
a[2] = {};
a[1] = {};
a[string.rep(i_kb, i_kg)] = i_kb(i_kg, 11);
for i_kg = 4, lim do
   a[i_kg] = {};
end
for i_kg = 1, lim do
   a[{}] = i_kg;
end
for i_kg = 1, lim do
   local k_w = {};
   a[k_w] = k_w;
end
_ENV[collectgarbage_jz]();
assert(next(i_kb) ~= nil);
k_q = 0;
for k_w, v_x in pairs(i_kb) do
   assert(k_w == v_x);
   k_q = k_q + 1;
end
assert(i_kb);
_ENV[collectgarbage_jz]();
v = assert;
i_kb(i_kg);
i_kg("$", 11);
v(i_kb);
a = {};
v = {["x"] = 10};
local i_kb = i_kb(i_kg, {["__mode"] = "v"});
i_kg = i_kg({[v] = 1}, {["__mode"] = "k"});
a.x = v;
setmetatable(a, {["__gc"] = (function ()
   assert(i_kb.key == nil);
   assert(type(next(i_kg), i_kg) == "table");
end)});
a = nil;
_ENV[collectgarbage_jz]();
_ENV[collectgarbage_jz]();
assert((next(i_kb) ~= nil) or (next(i_kg) == nil));
a = {[-49] = {[851] = 10, [852] = dyn_i_kb, [853] = dyn_i_j, [854] = i_bd, [855] = tab_bd, [856] = u_tab, [857] = u_tab_km, [858] = u_res, [859] = u_tab_ko, [860] = u_tab_kn, [861] = u_dyn_i_j, [862] = u_tab_kp, [863] = 0, [864] = u_dyn_tab_bd, [865] = u_u_res_kr, [866] = u_dyn_u_tab, [867] = v_ql, [868] = v_qn, [869] = v_qp}, [-48] = {[901] = 20, [902] = dyn_i_j, [903] = i_bd, [904] = tab_bd, [905] = u_tab, [906] = u_tab_km, [907] = u_res, [908] = u_tab_ko, [909] = u_tab_kn, [910] = u_dyn_i_j, [911] = u_tab_kp, [912] = 0, [913] = u_dyn_tab_bd, [914] = u_u_res_kr, [915] = u_dyn_u_tab, [916] = v_ql, [917] = v_qn, [918] = v_qp, [919] = v_rx, [920] = v_rz}, [-47] = {[951] = 30, [952] = i_bd, [953] = tab_bd, [954] = u_tab, [955] = u_tab_km, [956] = u_res, [957] = u_tab_ko, [958] = u_tab_kn, [959] = u_dyn_i_j, [960] = u_tab_kp, [961] = 0, [962] = u_dyn_tab_bd, [963] = u_u_res_kr, [964] = u_dyn_u_tab, [965] = v_ql, [966] = v_qn, [967] = v_qp, [968] = v_rx, [969] = v_rz, [970] = v_tj, [971] = v_tl}, [-46] = {[751] = 40, [752] = tab_bd, [753] = u_tab, [754] = u_tab_km, [755] = u_res, [756] = u_tab_ko, [757] = u_tab_kn, [758] = u_dyn_i_j, [759] = u_tab_kp, [760] = 0, [761] = u_dyn_tab_bd, [762] = u_u_res_kr, [763] = u_dyn_u_tab, [764] = v_ql, [765] = v_qn, [766] = v_qp, [767] = v_rx, [768] = v_rz, [769] = v_tj, [770] = v_tl, [771] = v_ux, [772] = v_uz}};
setmetatable(_ENV[collectgarbage_jz], {["__mode"] = "k"});
i_j = nil;
for dyn_i_kb = 1, 100 do
   local dyn_i_j = {};
   local tab_bd = {};
   local u_tab = {[1051] = i_j, [1052] = u_res, [1053] = u_tab_ko, [1054] = u_tab_kn, [1055] = u_dyn_i_j, [1056] = u_tab_kp, [1057] = 0, [1058] = u_dyn_tab_bd, [1059] = u_u_res_kr, [1060] = u_dyn_u_tab, [1061] = v_ql, [1062] = v_qn, [1063] = v_qp, [1064] = v_rx, [1065] = v_rz, [1066] = v_tj, [1067] = v_tl, [1068] = v_ux, [1069] = v_uz, [1070] = v_wx, [1071] = v_wz, [1072] = v_xb, [1073] = v_xd, [1074] = v_xf, [1075] = v_xh};
   tab_bd.k = u_tab;
   a[dyn_i_j] = tab_bd;
   i_j = dyn_i_j;
end
tab();
v_x = i_j;
local val_y = 0;
while (not v_x) 
   v_x = a[v_x].k[1];
   val_y = val_y + 1;
end
assert(val_y == 100);
i_j = nil;
tab();
for i_bd = 1, 4 do
   assert(u_tab);
   a[i_bd] = nil;
end
assert(next(a) == nil);
local c_tab_ba = {};
a[c_tab_ba] = {};
for tab_bd = 1, 10 do
   a[c_tab_ba][tab_bd] = {};
   u_tab[u_tab_km] = u_res(u_tab_ko, u_tab_kn);
end
i_j = nil;
dyn_i_kb = 1;
for u_tab = 1, 100 do
   local u_tab_km = {};
   local u_res = (dyn_i_kb % 10) + 1;
   local u_tab_kn = {};
   local u_dyn_i_j = i_j;
   u_tab_kn.k = dyn_i_kb;
   u_tab_kn[1251] = u_dyn_i_j;
   u_tab_kn[1252] = u_tab_kp;
   u_tab_kn[1253] = 0;
   u_tab_kn[1254] = u_dyn_tab_bd;
   u_tab_kn[1255] = u_u_res_kr;
   u_tab_kn[1256] = u_dyn_u_tab;
   u_tab_kn[1257] = v_ql;
   u_tab_kn[1258] = v_qn;
   u_tab_kn[1259] = v_qp;
   u_tab_kn[1260] = v_rx;
   u_tab_kn[1261] = v_rz;
   u_tab_kn[1262] = v_tj;
   u_tab_kn[1263] = v_tl;
   u_tab_kn[1264] = v_ux;
   u_tab_kn[1265] = v_uz;
   u_tab_kn[1266] = v_bcx;
   u_tab_kn[1267] = v_bdb;
   u_tab_kn[1268] = v_bdf;
   u_tab_kn[1269] = v_bdj;
   u_tab_kn[1270] = v_bdn;
   u_tab_kn[1271] = v_bdr;
   u_tab_kn[1272] = v_bdv;
   u_tab_kn[1273] = v_bdz;
   u_tab_kn[1274] = v_bed;
   u_tab_kn[1275] = v_beh;
   u_tab_kn[1276] = v_bel;
   u_tab_kn[1277] = v_bep;
   u_tab_kn[1278] = v_bet;
   u_tab_kn[1279] = v_bex;
   a[a[c_tab_ba][u_res]][u_tab_km] = u_tab_kn;
   i_j = u_tab_km;
   dyn_i_kb = u_res;
end
tab();
local dyn_i_j = i_j;
i_bd = 0;
while (not dyn_i_j) 
   tab_bd = a[a[c_tab_ba][dyn_i_kb]][dyn_i_j];
   dyn_i_j = tab_bd[1];
   dyn_i_kb = tab_bd.k;
   i_bd = i_bd + 1;
end
assert(u_tab);
tab();
_ENV[collectgarbage_jz](u_tab);
tab_bd = {};
u_tab = {};
u_tab_km(u_res, u_tab_ko);
u_tab_km(u_res, u_tab_ko);
for u_tab_kn = 6, 10 do
   local u_tab_kp = {};
   local u_dyn_tab_bd = tab_bd;
   res_bm = _ENV[collectgarbage_jz](u_dyn_tab_bd);
   local u_dyn_i_j = u_dyn_i_j(u_tab_kp, res_bm, u_dyn_tab_bd);
   u_tab[u_dyn_i_j] = u_tab_kn;
end
u_tab_km(u_res);
for u_tab_kn = 8, 10 do
   local u_dyn_i_j = assert;
   local u_tab_kp = u_tab[u_tab_kn];
   u_dyn_i_j(u_tab_kp);
end
for u_tab_kn = 1, 5 do
   local u_tab_kp = {};
   local u_dyn_tab_bd = tab_bd;
   res_bm = _ENV[collectgarbage_jz](u_dyn_tab_bd);
   local u_dyn_i_j = u_dyn_i_j(u_tab_kp, res_bm, u_dyn_tab_bd);
   u_tab[u_dyn_i_j] = u_tab_kn;
end
u_tab_km();
for u_tab_kn = 1, 10 do
   local u_dyn_i_j = assert;
   local u_tab_kp = u_tab[u_tab_kn];
   u_dyn_i_j(u_tab_kp);
end
u_tab_km(u_res).__gc = false;
u_tab_km(u_res, u_tab_ko);
local u_tab_km, u_res = u_tab_km(u_res);
if (u_tab_km) then
   local u_dyn_i_j = u_res;
   if (u_tab_kn(u_dyn_i_j) == "string") then
      u_dyn_i_j = u_res;
      local u_tab_kp = "error in __gc";
      u_tab_kn(u_dyn_i_j, u_tab_kp);
   end
end
u_tab_ko(u_tab_kn);
_ENV[collectgarbage_jz](u_tab);
if (T == nil) then
   (Message and print)(u_tab);
else  
   tab_bd = (function ()
      return u_u_res.setmetatable(T.newuserdata(0), u_u_res.getmetatable(v_ctn), v_ctn);
   end);
   u_tab(u_tab_km);
   u_tab = u_tab(u_tab_km);
   u_tab_km = u_u_res.setmetatable;
   u_tab_km(u_res, u_tab_ko);
   u_res = {[u_tab] = 0};
   u_tab_ko(u_tab_kn, u_dyn_i_j);
   for u_tab_kp = 1, 10 do
      u_res[tab_bd(u_dyn_tab_bd)] = u_tab_kp;
   end
   for u_tab_kp in u_tab_ko(u_tab_kn) do
      res_bm = assert;
      u_dyn_tab_bd(u_u_res_kr);
      local u_dyn_u_tab = u_tab;
      local u_u_res_kr = u_u_res_kr(u_dyn_u_tab);
      res_bm(u_dyn_tab_bd);
   end
   local u_tab_ko = {};
   for res_bm, u_dyn_tab_bd in u_tab_kn(u_dyn_i_j) do
      u_tab_ko[res_bm] = u_dyn_tab_bd;
   end
   for res_bm, u_dyn_tab_bd in u_tab_kn(u_dyn_i_j) do
      u_res[u_dyn_tab_bd] = res_bm;
   end
   for res_bm = 1, 10 do
      u_dyn_tab_bd = assert;
      local u_u_res_kr = u_res[res_bm];
      u_dyn_tab_bd(u_u_res_kr);
   end
   u_tab_kn(u_dyn_i_j).a = u_tab_ko;
   u_tab_kn(u_dyn_i_j).u = u_tab;
   u_tab_kn = u_tab;
   u_dyn_i_j(u_tab_kp).__gc = (function ()
      assert(u_res[v_csn] == (u_tab_km - 10));
      assert(u_res[(10 - u_tab_km)] == nil);
      assert(getmetatable(v_csn) == getmetatable(u_tab_kn));
      assert(getmetatable(v_csn).a[v_csn] == (u_tab_km - 10));
      u_tab_km = u_tab_km + 1;
   end);
   u_tab_kn = assert;
   u_dyn_i_j(u_tab_kp);
   u_tab_kn(u_dyn_i_j);
   u_tab_kn = collectgarbage;
   u_tab_kn();
   u_tab_kn = assert;
   u_tab_kn(u_dyn_i_j);
   u_tab_kn = collectgarbage;
   u_tab_kn();
   u_tab_kp = u_res;
   local u_dyn_i_j = u_dyn_i_j(u_tab_kp) == nil;
   u_tab_kn(u_dyn_i_j);
end
setmetatable(u_tab, u_tab_km);
u_tab_km(u_res);
u_tab(u_tab_km, u_res);
u_tab(u_tab_km).__gc = (function ()
   os.exit(1);
end);
u_tab();
u_tab(u_tab_km, u_res);
u_tab_km = u_tab_km(u_res);
u_res = {[{[1201] = 0, [1202] = u_dyn_i_j, [1203] = u_tab_kp, [1204] = res_bm, [1205] = u_dyn_tab_bd, [1206] = u_u_res_kr, [1207] = u_dyn_u_tab, [1208] = v_ql, [1209] = v_qn, [1210] = v_qp, [1211] = v_rx, [1212] = v_rz, [1213] = v_tj, [1214] = v_tl, [1215] = v_ux, [1216] = v_uz, [1217] = v_bwn, [1218] = v_bwp, [1219] = v_bwr, [1220] = v_bwt, [1221] = v_bwv, [1222] = v_bwx, [1223] = v_bwz, [1224] = v_bxb, [1225] = v_bxd, [1226] = v_bxf, [1227] = v_bxh, [1228] = v_bxj}] = 1};
local u_tab_ko = {[1201] = 1, [1202] = u_dyn_i_j, [1203] = u_tab_kp, [1204] = res_bm, [1205] = u_dyn_tab_bd, [1206] = u_u_res_kr, [1207] = u_dyn_u_tab, [1208] = v_ql, [1209] = v_qn, [1210] = v_qp, [1211] = v_rx, [1212] = v_rz, [1213] = v_tj, [1214] = v_tl, [1215] = v_ux, [1216] = v_uz, [1217] = v_bwn, [1218] = v_bwp, [1219] = v_bwr, [1220] = v_bwt, [1221] = v_bwv, [1222] = v_bwx, [1223] = v_bwz, [1224] = v_bxb, [1225] = v_bxd, [1226] = v_bxf, [1227] = v_bxh, [1228] = v_bxj};
u_res[0] = u_tab_ko;
u_tab_km.x = u_res;
u_res(u_tab_ko, u_tab_kn);
u_tab_km.__gc = (function ()
   assert(next(getmetatable(v_csh).x) == nil);
   u_tab_km = 10;
end);
u_res();
u_res(u_tab_ko);
u_res(u_tab_ko, u_tab_kn);
u_tab_ko = not u_tab_ko(u_tab_kn);
u_res(u_tab_ko);
if (_soft) then
   u_res(u_tab_ko);
   u_res = {};
   for u_tab_kp = 1, 200000 do
      u_res = {["next"] = u_res};
   end
   u_tab_ko = collectgarbage;
   u_tab_ko();
end
u_res(u_tab_ko);
u_res = 0;
while (u_res < 1000) 
   u_dyn_i_j(u_tab_kp);
   u_tab_kp(u_dyn_i_j, u_dyn_tab_bd);
   u_res = u_res + 1;
end
u_tab_kp();
u_tab_kp("stop");
local u_u_res_kr, u_dyn_u_tab = u_u_res_kr(u_dyn_u_tab, coroutine.create(u_dyn_tab_bd));
u_dyn_tab_bd(u_u_res_kr, u_dyn_u_tab);
u_tab_kp();
u_tab_kp(not u_dyn_i_j);
u_tab_kp();
u_tab_kp(u_dyn_i_j);
u_tab_kp("restart");
u_dyn_i_j();
u_dyn_i_j(u_tab_kp);
local u_dyn_i_j = u_dyn_i_j();
repeat
   for u_u_res_kr = 1, 1000 do
      a = {};
   end
   local u_dyn_tab_bd = 0;
   u_tab_kp("step", u_dyn_tab_bd);
until (u_dyn_i_j * 2 < u_tab_kp());
local u_tab_kp = collectgarbage;
u_tab_kp("restart");
if (not T) then
   u_tab_kp = u_tab_kp({}, u_dyn_tab_bd);
   _ENV[collectgarbage_jz]();
   _ENV[collectgarbage_jz](u_dyn_tab_bd);
   u_tab_kp.co = coroutine.wrap(u_dyn_tab_bd);
   u_tab_kp.co();
   u_dyn_tab_bd(u_u_res_kr);
   u_u_res_kr();
   u_dyn_tab_bd(u_u_res_kr);
   u_u_res_kr();
   u_dyn_tab_bd(u_u_res_kr);
   u_u_res_kr(u_dyn_u_tab);
   u_dyn_tab_bd(u_u_res_kr);
   u_dyn_tab_bd(u_u_res_kr);
   if (u_tab_kp.co == nil) then
      u_u_res_kr();
   end
   u_dyn_tab_bd(u_u_res_kr);
   u_dyn_tab_bd(u_u_res_kr);
   local u_dyn_tab_bd = u_dyn_tab_bd(u_u_res_kr);
   u_u_res_kr();
   u_u_res_kr(u_dyn_u_tab);
   u_u_res_kr(u_dyn_u_tab);
   u_u_res_kr(u_dyn_u_tab);
   u_u_res_kr = {};
   u_dyn_u_tab(T.gccolor(u_dyn_tab_bd) == "black");
   u_dyn_u_tab(T.gccolor(u_u_res_kr) == "white");
   u_dyn_u_tab(u_dyn_tab_bd, u_u_res_kr);
   u_dyn_u_tab(T.gccolor(u_dyn_tab_bd) == "white");
   u_dyn_u_tab("restart");
   u_dyn_u_tab("+");
end
if (not T) then
   u_dyn_i_j = u_dyn_i_j(u_tab_kp);
   u_tab_kp("stop");
   u_tab_kp = u_tab_kp(0);
   T.newuserdata(u_dyn_tab_bd);
   u_dyn_tab_bd(u_u_res_kr, u_dyn_u_tab);
   u_dyn_u_tab = {["__gc"] = true};
   u_dyn_tab_bd(u_u_res_kr, u_dyn_u_tab);
   u_u_res_kr(u_dyn_u_tab);
   u_dyn_tab_bd(u_u_res_kr);
   u_dyn_tab_bd();
   local u_dyn_tab_bd = collectgarbage;
   u_u_res_kr = "restart";
   u_dyn_tab_bd(u_u_res_kr);
end
if (not T) then
   u_dyn_i_j(u_tab_kp);
   u_dyn_i_j();
   u_dyn_i_j();
   u_tab_kp = u_tab_kp() + 200;
   u_dyn_i_j(u_tab_kp);
   for u_dyn_tab_bd = 1, 200 do
   end
   u_dyn_i_j(u_tab_kp);
   u_dyn_i_j();
   u_dyn_i_j(u_tab_kp);
   u_tab_kp[1451] = {};
   u_tab_kp[1452] = {};
   u_tab_kp[1453] = {};
   res_bm = assert;
   u_dyn_tab_bd(u_u_res_kr);
   res_bm(u_dyn_tab_bd);
   T.totalmem(u_dyn_tab_bd);
   res_bm = assert;
   u_dyn_tab_bd(u_u_res_kr);
   res_bm(u_dyn_tab_bd);
   u_dyn_i_j = T.totalmem(u_dyn_tab_bd);
   u_tab_kp = coroutine.create(u_dyn_tab_bd);
   res_bm = assert;
   u_u_res_kr = "thread";
   u_dyn_tab_bd = u_dyn_tab_bd(u_u_res_kr) == (u_dyn_i_j + 1);
   res_bm(u_dyn_tab_bd);
end
u_dyn_u_tab = {["__gc"] = (function ()
   u_tab_kp(u_u_res_kr(v_crv) == u_dyn_u_tab);
   ___Glob = v_crv;
   u_dyn_i_j({}, u_dyn_u_tab);
   u_dyn_tab_bd(">>> closing state <<<\n");
end)};
___Glob = {[-49] = u_dyn_i_j({}, u_dyn_u_tab), [-48] = v_rx, [-47] = v_rz, [-46] = v_tj, [-45] = v_tl, [-44] = v_ux, [-43] = v_uz, [-42] = v_bwn, [-41] = v_bwp, [-40] = v_bwr, [-39] = v_bwt, [-38] = v_bwv, [-37] = v_bwx, [-36] = v_bwz, [-35] = v_bxb, [-34] = v_bxd, [-33] = v_bxf, [-32] = v_bxh, [-31] = v_bxj, [-30] = v_cpr, [-29] = v_cpt, [-28] = v_cpv, [-27] = v_cpx, [-26] = v_cpz, [-25] = v_cqb, [-24] = v_cqd, [-23] = v_cqf, [-22] = v_cqh, [-21] = v_cqj, [-20] = v_cql, [-19] = v_cqn, [-18] = v_cqp, [-17] = v_cqr, [-16] = v_cqt, [-15] = v_cqv, [-14] = v_cqx, [-13] = v_cqz};
for u_u_res_kr = 1, 10 do
   u_dyn_u_tab(___Glob, setmetatable({}, u_dyn_i_j));
end
u_tab_kp("isrunning");
u_dyn_i_j(u_tab_kp, "isrunning");
u_dyn_i_j(u_tab_kp);
