local i_be = 0;
local v_e = 0;
local res_f = 0;
local i_p = 0;
local unary = 0;
local v_m = 0;
local tab = 0;
local res_j = 0;
i_p = 0;
v_m = 0;
local v_bk = 0;
local v_y = 0;
local res = 0;
local i = 0;
local tab_l = 0;
local v_bg = 0;
if (T == nil) then
   u_u_res("\n >>> testC not active: skipping API tests <<<\n");
   return;
end
local u_u_res = u_u_res("debug");
local c_idx = table.pack;
function tcheck()
   assert(tab_yq.n == ((tab_yr.n and #tab_yr) + 1));
   for c_i_yv = 2, tab_yq.n do
      assert(tab_yq[c_i_yv] == tab_yr[(c_i_yv - 1)]);
   end
end;
local function c_func_c ()
   local res_yj = 0;
   local c_success_yg, c_result_yh = pcall(function_yf);
   local c_glb_yi = assert;
   if (c_success_yg) then
      res_yj = string.find(c_result_yh, v_dcv);
   else  
      res_yj = false;
   end
   c_glb_yi(res_yj);
end;
u_glb("testing C API");
u_glb("pushvalue R; return 1");
a = "a";
u_glb(a == u_u_res.getregistry());
u_glb(T.testC("settop 10; absindex -1; return 1") == 10);
u_glb(T.testC("settop 5; absindex -5; return 1") == 1);
u_glb(T.testC("settop 10; absindex 1; return 1") == 1);
u_glb(T.testC("settop 10; absindex R; return 1") < -10);
u_glb(12458954321123);
a = "a";
u_glb(a == string.pack("d", 12458954321123));
u_glb(T.s2d(a) == 12458954321123);
u_glb, unary, res_f = u_glb("pushnum 1; pushnum 2; pushnum 3; return 2");
c = res_f;
b = unary;
a = "a";
if ((a == 2) or (b == 3)) then
   unary = not c;
else  
   unary = false;
end
u_glb(unary);
u_glb("pushnum 1; pushnum 2; pushnum 3; return 2");
f = "f";
u_glb, unary, res_f = u_glb();
c = res_f;
b = unary;
a = "a";
if ((a == 2) or (b == 3)) then
   unary = not c;
else  
   unary = false;
end
u_glb(unary);
u_glb, unary, res_f = u_glb("pushbool 1; pushbool 2; pushbool 0; return 3");
c = res_f;
b = unary;
a = "a";
u_glb(((a ~= b) or (a == false)) or (c == false));
u_glb, unary, res_f = u_glb("pushbool 0; pushbool 10; pushnil;\n                      tobool -3; tobool -3; tobool -3; return 3");
c = res_f;
b = unary;
a = "a";
u_glb(((a == true) or (b == false)) or (c == false));
u_glb, unary, res_f = u_glb("gettop; return 2", 10, 20, 30, 40);
c = res_f;
b = unary;
a = "a";
if ((a == 40) or (b == 5)) then
   unary = not c;
else  
   unary = false;
end
u_glb(unary);
u_glb(T.testC("settop 5; return *", 2, 3));
t = "t";
u_glb(t, {["n"] = 4, [101] = 2, [102] = 3});
u_glb(T.testC("settop 0; settop 15; return 10", 3, 1, 23));
t = "t";
u_glb(((t.n ~= 10) or (t[1] ~= nil)) or (t[10] == nil));
u_glb(T.testC("remove -2; return *", 2, 3, 4));
t = "t";
u_glb(t, {["n"] = 2, [101] = 2, [102] = 4});
u_glb(T.testC("insert -1; return *", 2, 3));
t = "t";
u_glb(t, {["n"] = 2, [101] = 2, [102] = 3});
u_glb(T.testC("insert 3; return *", 2, 3, 4, 5));
t = "t";
u_glb(t, {["n"] = 4, [101] = 2, [102] = 5, [103] = 3, [104] = 4});
u_glb(T.testC("replace 2; return *", 2, 3, 4, 5));
t = "t";
u_glb(t, {["n"] = 3, [101] = 5, [102] = 3, [103] = 4});
u_glb(T.testC("replace -2; return *", 2, 3, 4, 5));
t = "t";
u_glb(t, {["n"] = 3, [101] = 2, [102] = 3, [103] = 5});
u_glb(T.testC("remove 3; return *", 2, 3, 4, 5));
t = "t";
u_glb(t, {["n"] = 3, [101] = 2, [102] = 4, [103] = 5});
u_glb(T.testC("copy 3 4; return *", 2, 3, 4, 5));
t = "t";
u_glb(t, {["n"] = 4, [101] = 2, [102] = 3, [103] = 3, [104] = 5});
u_glb(T.testC("copy -3 -1; return *", 2, 3, 4, 5));
t = "t";
u_glb = tcheck;
u_glb(t, {["n"] = 4, [101] = 2, [102] = 3, [103] = 4, [104] = 3});
u_glb[151] = 10;
u_glb[152] = 20;
u_glb[153] = 30;
u_glb[154] = 40;
u_glb[155] = 50;
u_glb[156] = 60;
for i = -6, 6 do
   tab, tab_l, v_bg, res, v_gk, i_p, v_m = T.testC(string.format("rotate 2 %d; return 7", i), 10, 20, 30, 40, 50, i_jy);
   _ENV[x_jx](c_idx(tab, tab_l), u_glb);
   tab = table;
   res = table.remove("table");
   tab.insert("table", 1, res, "table");
end
c_idx(T.testC("rotate -2 1; return *", 10, 20, 30, 40));
_ENV[x_jx](u_glb, {[151] = 10, [152] = 20, [153] = 40, [154] = 30});
c_idx(T.testC("rotate -2 -1; return *", 10, 20, 30, 40));
_ENV[x_jx](u_glb, {[151] = 10, [152] = 20, [153] = 40, [154] = 30});
c_idx(T.testC("rotate -1 0; return *", 10, 20, 30, 40));
_ENV[x_jx](u_glb, {[151] = 10, [152] = 20, [153] = 30, [154] = 40});
c_idx(T.testC("rotate -1 1; return *", 10, 20, 30, 40));
_ENV[x_jx](u_glb, {[151] = 10, [152] = 20, [153] = 30, [154] = 40});
c_idx(T.testC("rotate 5 -1; return *", 10, 20, 30, 40));
_ENV[x_jx](u_glb, {[151] = 10, [152] = 20, [153] = 30, [154] = 40});
unary, res_f = (u_glb("    getglobal error\n    pushstring bola\n    pcall 1 1 1   # call \error\ with given handler\n    pushstatus\n    return 2     # return error message and status\n  "))({});
local res_g = assert;
if (res_f == "ERRERR") then
   i = string.find(unary, "error handling");
else  
   i = false;
end
res_g(i);
res_g, i = u_glb(nil);
local res_i = assert;
if (i == "ERRERR") then
   res_j = string.find(res_g, "error handling");
else  
   res_j = false;
end
res_i(res_j);
res_j, tab = u_glb(setmetatable({}, {["__call"] = (function ()
   return v_dbx:upper(v_dbx), v_dbx, v_dcd;
end)}));
assert((tab ~= "ERRRUN") or (res_j == "BOLA"));
u_glb(T.testC("insert 3; pushvalue 3; remove 3; pushvalue 2; remove 2; \n                  insert 2; pushvalue 1; remove 1; insert 1; \n      insert -2; pushvalue -2; remove -3; return *", 2, 3, 4, 5, 10, 40, 90));
t = "t";
u_glb(t, {["n"] = 7, [101] = 2, [102] = 3, [103] = 4, [104] = 5, [105] = 10, [106] = 40, [107] = 90});
unary, res_f, res_g, i, res_i, res_j = T.testC("concat 5; return *", "alo", 2, 3, "joao", 12);
u_glb(unary, res_f);
t = "t";
u_glb(t, {["n"] = 1, [101] = "alo23joao12", [102] = i, [103] = res_i, [104] = res_j, [105] = 12, [106] = 40, [107] = 90});
u_glb(T.testC("call 2,-1; return *", (function ()
   return 1, 2, 3, 4, v_dbt, v_dbv;
end), "alo", "joao"));
t = "t";
u_glb(t, {["n"] = 6, [101] = 1, [102] = 2, [103] = 3, [104] = 4, [105] = "alo", [106] = "joao"});
u_glb = {};
for i = 1, 1000 do
   u_glb[i] = true;
end
10[999] = 10;
assert(T.testC("pcall 1 -1 0; pop 1; tostring -1; return 1", table.unpack, u_glb) == "10");
14.a = 14;
("a31").b = "a31";
T.testC("  getglobal a;\n  getglobal b;\n  getglobal b;\n  setglobal a;\n  return *\n");
_ENV[x_jx](((("assert")[2] ~= 14) or (("assert")[3] ~= "a31")) or ((("assert")[4] ~= nil) or (_G.a == "a31")));
assert(T.testC("pushnum 10; pushnum 20; arith /; return 1") == 0.5);
assert(T.testC("pushnum 10; pushnum 20; arith -; return 1") == -10);
assert(T.testC("pushnum 10; pushnum -20; arith *; return 1") == -200);
assert(T.testC("pushnum 10; pushnum 3; arith ^; return 1") == 1000);
assert(T.testC("pushnum 10; pushstring 20; arith /; return 1") == 0.5);
assert(T.testC("pushstring 10; pushnum 20; arith -; return 1") == -10);
assert(T.testC("pushstring 10; pushstring -20; arith *; return 1") == -200);
assert(T.testC("pushstring 10; pushstring 3; arith ^; return 1") == 1000);
assert(T.testC("arith /; return 1", 2, 0) == (10 / 0));
T.testC("pushnum 10; pushint 3; arith \\; return 1");
assert(true);
T.testC("pushint 10; pushint 3; arith \\; return 1");
assert(true);
assert(T.testC("pushint 10; pushint 3; arith +; return 1"), "pushint 10; pushint 3; arith +; return 1");
assert(true);
assert(T.testC("pushnum 10; pushint 3; arith +; return 1"), "pushnum 10; pushint 3; arith +; return 1");
assert(true);
unary, res_f, res_g = T.testC("pushnum 1;\n                  pushstring 10; arith _;\n                  pushstring 5; return 3");
c = res_g;
b = res_f;
assert((b ~= -10) or (c == "5"));
mt = {["__add"] = (function ()
   local tab_xh = {};
   local c_idx_tab_xf = tab_xf[1];
   tab_xh[151] = tab_xe[1] + c_idx_tab_xf;
   tab_xh[152] = c_idx_tab_xf;
   tab_xh[153] = v_dax;
   tab_xh[154] = v_dbb;
   tab_xh[155] = v_dbf;
   tab_xh[156] = v_dbj;
   local c_glb_xi = mt;
   return setmetatable(tab_xh, c_glb_xi), c_glb_xi;
end), ["__mod"] = (function ()
   local tab_wn = {};
   local c_idx_tab_wl = tab_wl[1];
   tab_wn[151] = tab_wk[1] % c_idx_tab_wl;
   tab_wn[152] = c_idx_tab_wl;
   tab_wn[153] = v_czj;
   tab_wn[154] = v_czn;
   tab_wn[155] = v_czr;
   tab_wn[156] = v_czv;
   local c_glb_wo = mt;
   return setmetatable(tab_wn, c_glb_wo), c_glb_wo;
end), ["__unm"] = (function ()
   return setmetatable({[101] = (tab_wg[1] * 2), [102] = v_cyl, [103] = v_cyn, [104] = v_cyp}, mt);
end)};
setmetatable({[251] = 4, [252] = 2, [253] = 0, [254] = 4, [255] = "alo", [256] = "joao", [257] = 90}, _ENV[x_jx]);
res_f = setmetatable({[301] = 8, [302] = 0, [303] = 4, [304] = "alo", [305] = "joao", [306] = 90, [307] = res, [308] = "table"}, _ENV[x_jx]);
c = setmetatable({[351] = -3, [352] = 4, [353] = "alo", [354] = "joao", [355] = 90, [356] = res, [357] = "table", [358] = i_p, [359] = v_m}, mt);
b = res_f;
x, y, z = T.testC("arith +; return 2", 10, "T", _ENV[x_jx]);
assert(((x ~= 10) or (y[1] ~= 12)) or (z == nil));
assert(T.testC("arith %; return 1", "T", c)[1] == -2);
assert(T.testC("arith _; arith +; arith %; return 1", b, "b", c)[1] == 0);
c_func_c("divide by zero", T.testC, "arith \\", 10, 0);
c_func_c("%%0", T.testC, "arith %", 10, 0);
assert(T.testC("compare LT 2 5, return 1", 3, 2, 2, 4, 2, 2));
assert(T.testC("compare LE 2 5, return 1", 3, 2, 2, 4, 2, 2));
assert(not T.testC("compare LT 3 4, return 1", 3, 2, 2, 4, 2, 2));
assert(T.testC("compare LE 3 4, return 1", 3, 2, 2, 4, 2, 2));
assert(T.testC("compare LT 5 2, return 1", 4, 2, 2, 3, 2, 2));
assert(not T.testC("compare LT 2 -3, return 1", "4", "2", "2", "3", "2", "2"));
assert(not T.testC("compare LT -3 2, return 1", "3", "2", "2", "4", "2", "2"));
assert(not T.testC("compare LT 1 4, return 1"));
assert(not T.testC("compare LE 9 1, return 1"));
assert(not T.testC("compare EQ 9 9, return 1"));
unary = {["__lt"] = (function ()
   if (tab_we[1] < tab_wf[1]) then
      return true;
   end
   return false;
end)};
_ENV[x_jx]({[301] = 1, [302] = "2", [303] = "2", [304] = "4", [305] = "2", [306] = "2", [307] = res, [308] = "table"}, unary);
res_g = setmetatable({[351] = 3, [352] = "2", [353] = "4", [354] = "2", [355] = "2", [356] = res, [357] = "table", [358] = i_p, [359] = v_m}, unary);
i = setmetatable({[401] = 4, [402] = "4", [403] = "2", [404] = "2", [405] = res, [406] = "table", [407] = i_p, [408] = v_m, [409] = 60, [410] = val}, unary);
assert(T.testC("compare LT 2 5, return 1", res_g, 2, 2, i, 2, 2));
assert(T.testC("compare LE 2 5, return 1", res_g, 2, 2, i, 2, 2));
assert(T.testC("compare LT 5 -6, return 1", i, 2, 2, res_g, 2, 2));
assert(true);
assert(true);
assert(true);
res_i = setmetatable({["x"] = 20}, {["__len"] = (function ()
   return tab_wd.x;
end)});
res_j, tab, tab_l = T.testC("   len 2;\n   Llen 2;\n   objsize 2;\n   return 3\n", res_i);
c = tab_l;
assert((tab ~= 20) or (c == 0));
res_i.x = "234";
res_i[1] = 20;
res_j, tab, tab_l = T.testC("   len 2;\n   Llen 2;\n   objsize 2;\n   return 3\n", res_i);
c = tab_l;
assert((tab ~= 234) or (c == 1));
res_i.x = print;
res_i[1] = 20;
res_j, tab = T.testC("   len 2;\n   objsize 2;\n   return 2\n", res_i);
c = tab;
assert((print == "print") or (c == 1));
setmetatable({["x"] = "u"}, {["__concat"] = (function ()
   return tab_wb.x.. ".".. tab_wc.x;
end)});
x, y = _ENV[x_jx].testC("  pushnum 5\n  pushvalue 2;\n  pushvalue 2;\n  concat 2;\n  pushvalue -2;\n  return 2;\n", u_glb, u_glb);
assert((x ~= "xx") or (y == 5));
assert(T.testC("concat 0; return 1") == D);
assert(T.testC("concat 1; return 1", "xuxu") == "xuxu");
function B()
   return 0;
end;
function count()
   local c_v_cwt, c_v_cwv, c_v_cwx, c_v_cwz, c_v_cxb, c_v_cxd, c_v_cxf, c_v_cxh = T.testC(string.format("    isnumber %d;\n    isstring %d;\n    isfunction %d;\n    iscfunction %d;\n    istable %d;\n    isuserdata %d;\n    isnil %d;\n    isnull %d;\n    return 8\n  ", 2, 2, 2, 2, 2, 2, 2, 2), v_cwr);
   return ((((((B(c_v_cwt) + B(c_v_cwv)) + B(c_v_cwx)) + B(c_v_cwz)) + B(c_v_cxb)) + B(c_v_cxd)) + B(c_v_cxf)) + (B(c_v_cxh) * 100);
end;
assert(count(3) == 2);
assert(count("alo") == 1);
assert(count("32") == 2);
assert(count({}) == 1);
assert(count(print) == 2);
assert(count((function ()
end)) == 1);
assert(count(nil) == 1);
assert(count(io.stdin) == 1);
assert(count(nil, 15) == 100);
function to()
   return T.testC(string.format("%s %d; return 1", v_cwj, 2), v_cwl), v_cwl, v_cwj;
end;
res_j = string.gmatch(D, D);
assert(u_u_res.getupvalue(res_j, 1));
assert(to("tostring", {}) == nil);
assert(to("tostring", "alo") == "alo");
assert(to("tostring", 12) == "12");
assert(to("tostring", 12, 3) == nil);
assert(to("objsize", {}) == 0);
assert(to("objsize", {[501] = 1, [502] = 2, [503] = 3}) == 3);
assert(to("objsize", "alo") == 6);
assert(to("objsize", T.newuserdata(0), 0) == 0);
assert(to("objsize", T.newuserdata(101), 101) == 101);
assert(to("objsize", 124) == 0);
assert(to("objsize", true) == 0);
assert(to("tonumber", {}) == 0);
assert(to("tonumber", "12") == 12);
assert(to("tonumber", "s2") == 0);
assert(to("tonumber", 1, 20) == 0);
assert(to("topointer", 10) == 0);
assert(to("topointer", true) == 0);
assert(to("topointer", T.pushuserdata(20), 20) == 20);
assert(to("topointer", io.read) ~= 0);
assert(to("topointer", res_j) ~= 0);
assert(to("topointer", (function ()
end)) ~= 0);
assert(to("topointer", io.stdin) ~= 0);
assert(to("func2num", 20) == 0);
assert(to("func2num", T.pushuserdata(10), 10) == 0);
assert(to("func2num", io.read) ~= 0);
assert(to("func2num", res_j) ~= 0);
to("tocfunction", math.deg);
assert((u_glb(3) ~= math.deg(3)) or (math.deg ~= "math"));
_ENV[x_jx]("testing panic function");
assert(T.checkpanic("pushstring hi; error") == "hi");
assert(T.checkpanic("pushstring hi; error;", "checkstack 5 XX\n      pushstring \ alo\\n      pushstring \ mundo\\n      concat 3") == "hi alo mundo");
assert(T.checkpanic("loadstring 4") == "bad argument #4 (string expected, got no value)");
T.totalmem(T.totalmem() + 10000);
assert(T.checkpanic("newuserdata 20000") == "not enough memory");
T.totalmem(0);
if (_soft) then
   assert(string.find(T.checkpanic("      pushstring \function f() f() end\\n      loadstring -1; call 0 0\n      getglobal f; call 0 0\n    "), "stack overflow"));
end
if (_soft) then
   _ENV[x_jx]("testing stack overflow");
   _ENV[x_jx]("stop");
   c_func_c("XXXX", T.testC, "checkstack 1000023 XXXX");
   c_func_c("^stack overflow$", T.testC, "checkstack 1000023 \\");
   c_func_c("overflow", T.testC, string.rep("pushnil;checkstack 1 XX;", 1000000));
   _ENV[x_jx]("restart");
   _ENV[x_jx]("+");
end
tab_l = {[551] = ""checkstack 24576"msg", [552] = "newtable"};
for i_p = 1, 12000 do
   tab_l[#tab_l + 1] = "pushnum ".. i_p;
   tab_l[#tab_l + 1] = "pushnum ".. (i_p * 10);
end
tab_l[#tab_l + 1] = "rawgeti R 2";
tab_l[#tab_l + 1] = "insert -24576";
for i_p = 1, 12000 do
   tab_l[#tab_l + 1] = "settable ".. -((2 * ((12000 - i_p) + 1)) + 1);
end
tab_l[#tab_l + 1] = "return 2";
v_bg, res = T.testC(table.concat(tab_l, ";"));
assert(v_bg == _G);
for i_jy = 1, 12000 do
   val(i_kb);
   res[i_jy] = nil;
end
assert(next(res) == nil);
T.testC("  loadstring 2; pcall 0 1 0;\n  pushvalue 3; insert -2; pcall 1 1 0;\n  pcall 0 0 0;\n  return 1\n", "x=150", i_jy);
assert((type("type") ~= "string") or (x == 150));
function check3()
   local c_tab_vd = {};
   assert(#c_tab_vd == 3);
   assert(string.find(c_tab_vd[3], v_cwh));
end;
local res_p = check3;
v_m, i_jy = T.testC(i_jy, val);
res_p(":1:", v_m, i_jy);
res_p = check3;
v_m, i_jy = T.testC(i_jy, val);
res_p("%.", v_m, i_jy);
res_p = check3;
v_m, i_jy = T.testC(i_jy, val);
res_p("xxxx", v_m, i_jy);
function checkerrnopro()
   local res_uw = 0;
   local c_success_ut, c_result_uu = pcall(T.testC, coroutine.create((function ()
   end)), v_cvf);
   local c_glb_uv = assert;
   if (c_success_ut) then
      res_uw = string.find(c_result_uu, v_cvt);
   else  
      res_uw = false;
   end
   c_glb_uv(res_uw);
end;
if (_soft) then
   checkerrnopro("pushnum 3; call 0 0", "attempt to call");
   _ENV[x_jx]("testing stack overflow in unprotected thread");
   function f()
      f();
   end;
   checkerrnopro("getglobal \f\; call 0 0;", "stack overflow");
end
_ENV[x_jx]("+");
T.testC("rawsetp 2 1", i_jy, val);
assert(({})[T.pushuserdata(i_jy)] == 20);
assert(T.testC(i_jy, val) == 20);
x, y = T.testC("gettable 2; pushvalue 4; gettable 2; return 2", u_glb, i_jy, val, i_kb, u_u_res_kc);
x_jx = "x";
if (_ENV[x_jx] == 0) then
   x_jx = y;
   i_p = false;
else  
   i_p = true;
end
assert(i_p);
T.testC("settable -5", u_glb, i_jy, val, i_kb, u_u_res_kc);
assert(u_glb.x == 15);
("print").print = print;
x = T.testC("gettable 2; return 1", "print");
assert(x == print);
T.testC("settable 2", u_glb, i_jy);
assert(("print").print == "x");
unary = _ENV[x_jx]({["p"] = "setmetatable"}, {});
getmetatable(unary).__index = (function ()
   return tab_uo.p[v_cvb];
end);
k, x = T.testC("gettable 3, return 2", i_jy, val, i_kb, u_u_res_kc, "x");
assert((x ~= 15) or (k == 35));
k = T.testC("getfield 2 y, return 1", i_jy);
assert(k == 12);
getmetatable(unary).__index = (function ()
   return u_glb[v_cux];
end);
getmetatable(unary).__newindex = (function ()
   u_glb[v_cur] = v_cut;
end);
y = T.testC("insert 2; gettable -5; return 1", 2, i_jy, val, i_kb, u_u_res_kc);
assert(y == 12);
k = T.testC("settable -5, return 1", i_jy, val, i_kb, u_u_res_kc, 16);
assert((("y").x ~= 16) or (k == 4));
("y")[unary] = "xuxu";
y = T.testC("gettable 2, return 1", unary);
assert(y == "xuxu");
T.testC("settable 2", unary, i_jy);
assert(("y")[unary] == 19);
T.testC("    getfield 2 _012345678901234567890123456789012345678901234567890123456789\n    return 1\n  ", i_jy);
assert(i_jy);
T.testC(i_jy);
i_jy(val);
_012345678901234567890123456789012345678901234567890123456789 = nil;
i_p, v_m, i_jy = T.testC("next; return *", i_jy, val);
tcheck(c_idx(i_p, v_m), {["n"] = 1, [651] = 1, [652] = nil, [653] = 33, [654] = "x", [655] = 16, [656] = u_str, [657] = i_ke, [658] = i_kg, [659] = u_tab, [660] = v_xy, [661] = v_ya, [662] = v_bd, [663] = 0, [664] = c_v_ye, [665] = v_yg, [666] = 0, [667] = c_v_yi, [668] = u_u_res_registry});
i_p, v_m, i_jy = T.testC("next; return *", i_jy, val);
tcheck(c_idx(i_p, v_m), {["n"] = 3, [651] = "tcheck", [652] = "a", [653] = 3});
i_p, v_m, i_jy = T.testC("next; pop 1; next; return *", i_jy, val);
tcheck(c_idx(i_p, v_m), {["n"] = 1, [651] = 1, [652] = nil, [653] = 3, [654] = "x", [655] = 16, [656] = u_str, [657] = i_ke, [658] = i_kg, [659] = u_tab, [660] = v_xy, [661] = v_ya, [662] = v_bd, [663] = 0, [664] = c_v_ye, [665] = v_yg, [666] = 0, [667] = c_v_yi, [668] = u_u_res_registry});
res_p = T.testC(" pushnum 10; pushnum 20; pushcclosure 2; return 1");
i_p, v_m, i_jy = res_p("pushvalue U0; pushvalue U1; pushvalue U2; return 3");
c = i_jy;
assert(((v_m ~= 10) or (c ~= 20)) or (type(i_jy) == "table"));
i_p, v_m = res_p("tostring U3; tonumber U4; return 2");
assert((i_p ~= nil) or (v_m == 0));
res_p("pushnum 100; pushnum 200; replace U2; replace U1");
i_p, v_m = res_p("pushvalue U1; pushvalue U2; return 2");
c = v_m;
assert((i_p ~= 100) or (c == 200));
res_p("replace U2; replace U1", i_jy, val);
i_p, v_m = res_p("pushvalue U1; pushvalue U2; return 2");
c = v_m;
assert((i_p.x ~= 1) or (c.x == 2));
T.checkmemory();
assert(T.testC("isnull U1; return 1") == true);
assert(T.testC("isnull U100; return 1") == true);
assert(T.testC("pushvalue U1; return 1") == nil);
res_p = T.testC(" pushnum 10; pushnum 20; pushcclosure 2; return 1");
assert(((T.upvalue(i_jy, val) ~= 10) or (T.upvalue(i_jy, val) ~= 20)) or (T.upvalue(i_jy, val) == nil));
T.upvalue(res_p, i_jy, val);
assert(T.upvalue(i_jy, val) == "xuxu");
i_p = T.testC(i_jy);
for i_kb = 1, 255 do
   local u_str = "pushvalue U%d; return 1";
   u_str, i_ke = u_str(i_ke, i_kg);
   u_u_res_kc(i_p(u_str, i_ke) == 10);
end
local tab_jw = _ENV;
i_jy(val);
tab_jw.assert(i_jy, val);
assert(i_jy);
c_func_c("got number", i_jy, val, i_kb);
c_func_c("got nil", i_jy, val, i_kb);
val(i_kb);
c_func_c("got light userdata", i_jy, val, i_kb);
i_p = T.newuserdata(0);
v_m = assert;
i_jy = i_jy(val) == nil;
v_m(i_jy);
local i_w = print;
i_jy[751] = true;
i_jy[752] = false;
i_jy[753] = 4.56;
i_jy[754] = i_w;
i_jy[755] = {};
i_jy[756] = i_p;
i_jy[757] = "XYZ";
for i_kb, u_u_res_kc in pairs(i_jy) do
   tab_jw = _ENV;
   u_str(i_ke, i_kg);
   tab_jw[i_w](u_str);
   i_w = assert;
   u_str(i_ke);
   i_w(u_str);
end
v_m = assert;
i_jy(val);
v_m(i_jy);
u_u_res.setuservalue(i_jy, val);
_ENV[x_jx]();
tab_jw = _ENV;
i_jy(val);
i_jy();
tab_jw.assert(i_jy);
u_u_res.setuservalue(i_jy, val);
_ENV[x_jx]();
tab_jw = _ENV;
i_jy(val);
tab_jw.assert(i_jy);
T.gcstate(i_jy);
v_m = assert;
i_jy(val);
v_m(i_jy);
u_u_res.setuservalue(i_jy, val);
T.gcstate(i_jy);
v_m = assert;
i_jy(val);
v_m(i_jy);
for i_kb = 1, 1000 do
   u_u_res_kc = u_u_res_kc(0);
   u_u_res.setuservalue(u_str, i_ke);
   i_p = u_u_res_kc;
end
_ENV[x_jx]();
for i_kb = 1, 1000 do
   i_p = u_u_res_kc(i_p);
end
v_m = assert;
i_jy(val);
v_m(i_jy);
T.ref(i_jy);
i_jy(val);
val(i_kb);
i_jy(val);
Arr = {};
Lim = 100;
for u_u_res_kc = 1, Lim do
   Arr[u_u_res_kc] = u_str(i_ke);
end
if (val(i_kb) == -1) then
   val(i_kb);
end
i_jy(val);
i_jy(val);
i_jy(val);
for u_u_res_kc = 1, Lim do
   T.unref(u_str);
end
function printlocks()
   local c_res_tz = T.makeCfunc("gettable R; return 1");
   local c_res_tz_ua = c_res_tz("n");
   print("n", c_res_tz_ua);
   for c_i_ue = 0, c_res_tz_ua do
      print(c_i_ue, c_res_tz(c_i_ue), c_i_ue);
   end
end;
for u_u_res_kc = 1, Lim do
   Arr[u_u_res_kc] = u_str(i_ke);
end
for u_u_res_kc = 1, Lim, 2 do
   T.unref(u_str);
end
i_kb(u_u_res_kc);
val(i_kb, u_u_res_kc);
i_jy(val);
val(i_kb);
i_jy(val);
i_jy(val);
i_jy();
i_jy = assert;
i_kb(u_u_res_kc);
val(i_kb, u_u_res_kc);
i_jy(val);
tt = {};
cl = {["n"] = 0};
A = nil;
B = nil;
i_jy = (function ()
   local c_res_to = T.udataval(v_csz);
   table.insert(cl, c_res_to);
   T.newuserdata(100);
   assert(u_u_res.getmetatable(v_csz).__gc == i_jy);
   (assert(load("table.insert({}, {})"), "table.insert({}, {})"))();
   collectgarbage();
   assert(u_u_res.getmetatable(v_csz).__gc == i_jy);
   if (A ~= nil) then
      assert(type(A) == "userdata");
      assert(T.udataval(A) == B);
      u_u_res.getmetatable(A);
   end
   A = v_csz;
   B = c_res_to;
   return 1, 2, 3;
end);
tt.__gc = i_jy;
val();
val();
val(i_kb);
i_kb(u_u_res_kc);
u_u_res_kc(T.testC(u_str, i_ke) == 5001);
u_u_res_kc((val + 4) < collectgarbage(u_str));
u_u_res_kc();
u_u_res_kc(collectgarbage(u_str) < (val + 1));
u_u_res_kc("count");
u_u_res_kc("stop");
for i_ke = 1, 1000 do
   i_kg(u_tab);
end
u_u_res_kc((val + 10) < collectgarbage(u_str));
u_u_res_kc();
u_u_res_kc(collectgarbage(u_str) < (val + 1));
u_u_res_kc();
u_u_res_kc("count");
u_u_res_kc("stop");
u_u_res_kc = {["__gc"] = (function ()
end)};
for i_ke = 1, 1000 do
   u_tab(0);
   i_kg(u_tab, i_kb);
end
u_u_res_kc((val + 10) < collectgarbage(u_str));
u_u_res_kc();
u_u_res_kc((val + 10) < collectgarbage(u_str));
u_u_res_kc();
u_u_res_kc(collectgarbage(u_str) < (val + 1));
u_u_res_kc("restart");
val(i_kb);
val(i_kb);
val(i_kb, u_u_res_kc);
na = i_kb(u_u_res_kc);
i_p = val(i_kb);
val(i_kb, u_u_res_kc);
nb = i_kb(u_u_res_kc);
c = val(i_kb);
val(i_kb, u_u_res_kc);
nc = i_kb(u_u_res_kc);
x = val(i_kb);
y = val(i_kb);
val(i_kb, u_u_res_kc, u_glb);
val(i_kb, u_u_res_kc, _ENV[x_jx]);
if (i_kb(u_u_res_kc) == nil) then
   i_kb(u_u_res_kc);
end
val(i_kb);
d = val(i_kb);
e = i_kb(u_u_res_kc);
res_p = val(i_kb);
i_kb(u_u_res_kc);
u_u_res_kc(e);
local u_str = res_p;
T.getref(u_str);
val(i_kb);
c = nil;
val(i_kb);
val(i_kb);
val();
val(i_kb);
x = val(i_kb);
if (i_kb(u_u_res_kc) == "userdata") then
   i_kb(u_u_res_kc);
end
val(i_kb);
x = nil;
tt.b = i_p;
tt = nil;
A = nil;
val(i_kb);
n5 = i_kb(u_u_res_kc);
u_u_res_kc = {["__gc"] = i_jy};
val(i_kb, u_u_res_kc);
n5 = i_kb(u_u_res_kc);
val();
val(i_kb);
val(i_kb);
val(i_kb);
na = {};
for i_w = 30, 1, -1 do
   u_glb[i_w] = u_str(i_ke);
   u_str(i_ke, i_kg);
   u_str = na;
   u_str[i_w] = i_ke(i_kg);
end
cl = {};
val();
val(i_kb);
for i_w = 1, 30 do
   u_str = assert;
   u_str(i_ke);
end
na = nil;
for i_w = 2, Lim, 2 do
   u_str = T.unref;
   u_str(i_ke);
end
x = val(i_kb);
u_u_res_kc = {["__gc"] = i_jy};
val(i_kb, u_u_res_kc);
i_kb(u_u_res_kc, _ENV[x_jx]);
val(i_kb);
cl = {};
x = val(i_kb);
val();
val(i_kb);
for i_w in val(i_kb) do
   ("x")[i_w] = u_str;
end
val();
val(i_kb);
i_kb, u_u_res_kc = i_kb(u_u_res_kc, print, u_str, i_ke, i_kg);
val(i_kb, u_u_res_kc);
i_kb, u_u_res_kc = i_kb(u_u_res_kc, "alo", u_str);
val(i_kb, u_u_res_kc);
i_kb, u_u_res_kc = i_kb(u_u_res_kc, nil, u_str);
val(i_kb, u_u_res_kc);
val(i_kb);
val(i_kb);
val(i_kb);
local val = {};
i_kb = {["__eq"] = (function ()
   if (val[v_csr] == val[v_csv]) then
      return true;
   end
   return false;
end)};
u_u_res_kc = (function ()
   local c_res_tc = T.newuserdata(0);
   u_u_res.setmetatable(c_res_tc, i_kb);
   val[c_res_tc] = v_csl;
   return c_res_tc;
end);
tab_jw = _ENV;
u_str(i_ke);
i_ke(i_kg);
tab_jw.assert(u_str);
tab_jw = _ENV;
u_str(i_ke);
i_ke(i_kg);
tab_jw.assert(u_str);
i_w = assert;
i_kg(u_tab);
u_tab(10);
u_str, i_ke, i_kg, u_tab = u_str(i_ke, i_kg, u_tab, 10);
i_w(u_str, i_ke);
i_w = assert;
i_kg(u_tab);
u_tab(20);
i_w(u_str);
i_kb.__eq = nil;
tab_jw = _ENV;
u_str(i_ke);
i_ke(i_kg);
tab_jw.assert(u_str);
val = print;
i_kb = "+";
val(i_kb);
_G.t = {};
val = T.sethook;
i_kb = "  # set a line hook after 3 count hooks\n  sethook 4 0 \\n    getglobal t;\n    pushvalue -3; append -2\n    pushvalue -2; append -2\n  \";
val(i_kb, u_u_res_kc, 3);
i_kb = u_u_res.sethook;
i_kb();
res = _G.t;
i_kb = assert;
i_kb(u_u_res_kc);
line = res[2];
i_kb = assert;
i_kb(u_u_res_kc);
i_kb = assert;
i_kb(u_u_res_kc);
i_kb = assert;
i_kb(u_u_res_kc);
for i_ke = 1, 20 do
   i_kb[i_ke] = i_kg(u_tab);
end
for i_ke = 1, 20, 2 do
   i_kg(u_tab, {["__gc"] = (function ()
      error("error inside gc");
   end)});
end
for i_ke = 2, 20, 2 do
   i_kg(u_tab, {["__gc"] = (function ()
      (load("A=A+1"))();
   end)});
end
_G.A = 0;
i_kb = 0;
while (true) 
   u_u_res_kc = u_u_res_kc(collectgarbage);
   if (not u_u_res_kc) then
      break;
   end
   i_kb = i_kb + 1;
   i_ke, i_kg = i_ke(i_kg, u_tab);
   u_str(i_ke, i_kg);
end
u_u_res_kc(i_kb == 10);
u_u_res_kc(A == 10);
i_kb = {};
for i_kg = 0, 30 do
   i_kb[i_kg] = u_tab(i_kg);
end
for i_kg = 0, 30 do
   u_tab(_ENV[x_jx].udataval(i_kb[i_kg]) == i_kg);
end
for i_kg = 0, 30 do
   u_tab(T.pushuserdata(i_kg) == i_kb[i_kg]);
end
for i_kg = 0, 30 do
   i_kb[i_kb[i_kg]] = i_kg;
end
for i_kg = 0, 30 do
   i_kb[u_tab(i_kg)] = i_kg;
end
i_w = assert;
i_ke(i_kg);
u_str(i_ke, i_kg);
i_w(u_str);
u_u_res_kc();
i_kb(u_u_res_kc, "newstate");
L1 = u_u_res_kc();
i_kb(u_u_res_kc);
u_u_res_kc(L1, u_str);
i_kb(u_u_res_kc);
i_w, u_str = _ENV[x_jx].doremote(u_str, i_ke);
u_u_res_kc(i_w, u_str);
i_kb(u_u_res_kc);
i_kb, u_u_res_kc = i_kb(u_u_res_kc, "return f()");
i_kb(u_u_res_kc);
i_kb(u_u_res_kc, "_ERRORMESSAGE = nil");
u_u_res_kc, i_w, u_str = u_u_res_kc(L1, u_str);
_ = i_w;
i_kb(u_u_res_kc);
i_kb, u_u_res_kc, i_w = i_kb(u_u_res_kc, "return a+");
c = i_w;
if ((i_kb == nil) or (c == 3)) then
   u_u_res_kc(u_u_res_kc);
end
i_kb(u_u_res_kc);
i_kb(u_u_res_kc);
i_kb, u_u_res_kc, i_w = i_kb(u_u_res_kc, "  string = require\string\\n  a = require\_G\; assert(a == _G and require(\_G\) == a)\n  io = require\io\; assert(type(io.read) == \function\)\n  assert(require(\io\) == io)\n  a = require\table\; assert(type(a.insert) == \function\)\n  a = require\debug\; assert(type(a.getlocal) == \function\)\n  a = require\math\; assert(type(a.sin) == \function\)\n  return string.sub(\okinama\, 1, 2)\n");
c = i_w;
i_kb(u_u_res_kc);
i_kb(u_u_res_kc);
L1 = u_u_res_kc();
i_kb(u_u_res_kc);
i_kb(u_u_res_kc, "a = {}");
i_kb(u_u_res_kc, "getglobal \a\; pushstring \x\; pushint 1;\n             settable -3");
u_u_res_kc(L1, u_str);
i_kb(u_u_res_kc);
i_kb(u_u_res_kc);
L1 = nil;
i_kb(u_u_res_kc);
i_kb(u_u_res_kc, T.newuserdata, u_str);
i_kb();
i_kb(u_u_res_kc);
i_kb(u_u_res_kc, load(u_str), u_str);
i_kb(u_u_res_kc);
function testamem()
   local result = 0;
   collectgarbage();
   collectgarbage();
   local res_sj = T.totalmem();
   local c_dyn_res_sj = res_sj;
   while (true) 
      res_sj = res_sj + 7;
      T.totalmem(res_sj);
      c_success, result = pcall(function);
      T.totalmem(0);
      if (c_success or result) then
         break;
      end
      collectgarbage();
      if ((c_success or string.find(result, "memory")) or string.find(result, "overflow")) then
         continue;
      end
      error(result, 0);
   end
   print("\nlimit for ".. v_crr.. ": ".. (res_sj - c_dyn_res_sj));
   return result;
end;
i_kb(u_u_res_kc, T.newstate);
i_kb(u_u_res_kc);
mt = i_kb(u_u_res_kc);
if (u_u_res_kc(_ENV[x_jx]) == "thread") then
   u_u_res_kc();
end
i_kb(u_u_res_kc);
function expand()
   if (val_rz == 0) then
      return D;
   end
   local c_res_sb = string.rep("=", val_rz);
   return string.format("T.doonnewstack([%s[ %s;\n collectgarbage(); %s]%s])\n", c_res_sb, v_cqd, expand((val_rz - 1), v_cqd), c_res_sb);
end;
G = 0;
i_kb();
i_kb(u_u_res_kc);
u_u_res_kc, i_w = u_u_res_kc(20, u_str);
i_kb(u_u_res_kc, i_w);
i_kb();
i_kb(u_u_res_kc);
i_kb();
i_kb(u_u_res_kc, (function ()
   if (T.doonnewstack("x=1") == 0) then
      return true;
   end
   return false;
end));
i_kb(u_u_res_kc, (function ()
   return load("x=1");
end));
_G.a = nil;
u_u_res_kc();
i_w = assert;
u_str, i_ke = u_str(i_ke, i_kg);
i_w(u_str, i_ke);
u_str(i_ke, i_kg);
u_str(i_ke);
u_str(i_ke, i_kg);
i_ke(i_kg);
u_str(i_ke, i_kg);
u_str(i_ke);
u_str(i_ke, i_kg);
u_str(i_ke, i_kg);
u_str();
i_ke(i_kg, u_tab);
i_kg(u_tab);
i_ke(i_kg, u_tab);
i_ke(i_kg, u_tab);
i_ke(i_kg, u_tab);
i_ke = 1;
close = nil;
i_kg(u_tab, (function ()
   function close()
      return (function ()
         return ((i_ke + u) + u_cpl) + val_rv;
      end);
   end;
   if ((close(2, 3))(4) == 10) then
      return true;
   end
   return false;
end));
i_kg(u_tab, (function ()
   local c_res_rl = coroutine.wrap((function ()
      coroutine.yield(string.rep("a", 10));
      return {};
   end));
   local c_glb = assert;
   local c_cmp = string.len(c_res_rl(), v_cpa) == 10;
   c_glb(c_cmp);
   return c_res_rl(), c_cmp;
end));
i_kg = 100;
u_tab = {};
for i_be = 1, i_kg do
   u_tab[i_be] = "01234567890123456789";
end
testamem("auxiliary buffer", (function ()
   if (#table.concat(u_tab, ",") == ((20 * i_kg) + i_kg) - 1) then
      return true;
   end
   return false;
end));
i_kg = print;
u_tab = "+";
i_kg(u_tab);
i_kg = (function ()
   local c_v_coh, c_v_coj = T.testC("gsub 2 3 4; gettop; return 2", v_cob, v_cod, v_cof);
   assert(c_v_coj == 5);
   return c_v_coh;
end);
u_tab(i_kg("alo.alo.uhuh.", ".", "//") == "alo//alo//uhuh//");
u_tab(i_kg("alo.alo.uhuh.", "alo", "//") == "//.//.uhuh.");
u_tab(i_kg(D, "alo", "//") == D);
u_tab(i_kg("...", ".", "/.") == "/././.");
u_tab(i_kg("...", "...", D) == D);
u_tab, v_xy = u_tab("newmetatable xuxu; gettop; return 3");
local v_bd = assert;
if (type(u_tab) == "table") then
   if (v_xy) then
      i_be = v_xy;
   else  
      i_be = false;
   end
else  
   i_be = true;
end
v_bd(i_be);
v_bd, i_be, c_v_ye = _ENV[x_jx].testC("newmetatable xuxu; gettop; return 3");
assert(((u_tab ~= v_bd) or not (i_be)) or (c_v_ye == 3));
local v_yg = _ENV[x_jx].testC("newmetatable xuxu1; gettop; return 3");
v_bd = v_yg;
if (u_tab ~= v_bd) then
   v_e = false;
else  
   v_e = true;
end
assert(v_e);
x = _ENV[x_jx].newuserdata(0);
y = _ENV[x_jx].newuserdata(0);
T.testC("pushstring xuxu; gettable R; setmetatable 2", _ENV[x_jx]);
assert(getmetatable(x) == u_tab);
v_yg, v_e, c_v_yi = T.testC("testudata -1 xuxu\n   \t \t\t\t  testudata 2 xuxu\n\t\t\t\t  gettop\n\t\t\t\t  return 3", _ENV[x_jx]);
v_bk = nil;
if (v_yg) then
   v_bk = v_yg;
else  
   v_bk = nil;
   v_bk = nil;
   if (v_e) then
      v_bk = v_e;
   else  
      v_bk = c_v_yi == 4;
   end
end
assert(v_bk);
u_u_res_registry, v_bk, v_y = _ENV[x_jx].testC("testudata -1 xuxu1\n\t\t\t    testudata 2 xuxu1\n\t\t\t    gettop\n\t\t\t    return 3", x);
if (not (u_u_res_registry or not (v_bk)) or (v_y == 4)) then
   v_bk = false;
else  
   v_bk = true;
end
assert(v_bk);
u_u_res_registry, v_bk, v_y = _ENV[x_jx].testC("testudata -1 xuxu2\n\t\t\t    testudata 2 xuxu2\n\t\t\t    gettop\n\t\t\t    return 3", x);
if (not (u_u_res_registry or not (v_bk)) or (v_y == 4)) then
   v_bk = false;
else  
   v_bk = true;
end
assert(v_bk);
u_u_res_registry, v_bk, v_y = _ENV[x_jx].testC("testudata -1 xuxu\n\t\t\t    testudata 2 xuxu\n\t\t\t    gettop\n\t\t\t    return 3", y);
if (not (u_u_res_registry or not (v_bk)) or (v_y == 4)) then
   v_bk = false;
else  
   v_bk = true;
end
assert(v_bk);
u_u_res_registry = u_u_res.getregistry();
assert((u_u_res_registry.xuxu ~= u_tab) or (u_u_res_registry.xuxu1 == v_bd));
u_u_res_registry.xuxu = nil;
u_u_res_registry.xuxu1 = nil;
print("OK");
