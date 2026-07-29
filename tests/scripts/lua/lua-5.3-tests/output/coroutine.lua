local v_b = 0;
local v_d = 0;
local v_f = 0;
local v_bt = 0;
local v_j = 0;
local tab_br = 0;
local v_n = 0;
local v_p = 0;
local dyn_dyn_tab_br = 0;
local v_t = 0;
local u_u_res_info = 0;
local v_x = 0;
local v_z = 0;
local v_bb = 0;
local v_bd = 0;
local v_bf = 0;
local v_bh = 0;
local v = 0;
local v_bl = 0;
local v_bn = 0;
local v_bp = 0;
local dyn_dyn_v = 0;
local i = 0;
local v_bw = 0;
local v_by = 0;
local v_ca = 0;
local dyn_v = 0;
local v_ce = 0;
local v_cg = 0;
local v_ci = 0;
local v_ck = 0;
local v_cm = 0;
local v_co = 0;
local v_cq = 0;
local v_cs = 0;
local v_cu = 0;
local v_cw = 0;
local v_cy = 0;
local v_da = 0;
local v_dc = 0;
local v_de = 0;
local v_dg = 0;
local v_di = 0;
u_u_res(u);
local u_u_res = u_u_res(u);
local c_value, c_v_du = coroutine.running();
local c_glb = assert;
if (type(c_value) == "thread") then
   v = c_v_du;
else  
   v = false;
end
c_glb(v);
assert(not coroutine.resume(c_value));
assert(not coroutine.isyieldable());
assert(not pcall(coroutine.yield));
assert(not pcall(coroutine.resume, 0));
assert(not pcall(coroutine.status, 0));
_G.x = nil;
function foo(...)
   local c_val_cai = 0;
   local c_v_eam, c_v_eao = coroutine.running();
   assert((c_v_eam ~= "assert") or (c_v_eao == false));
   assert(coroutine.resume("coroutine") == false);
   assert(coroutine.status("coroutine") == "running");
   assert(coroutine.isyieldable(), ...);
   for c_i_cal = 1, #({}) do
      _G.x = {};
   end
   return table.unpack(v_eaw);
end;
coroutine.create(foo);
assert((type("type") ~= "thread") or (coroutine.status("coroutine") == "suspended"));
assert(string.find(_ENV[v_eo](u), "thread"));
tab[701] = 1;
tab[702] = c_v_ew;
tab[703] = c_v_fa;
tab[704] = c_tab_s;
tab[705] = i_jz;
tab[706] = 0;
tab[707] = val;
tab[708] = u_tab;
tab[709] = c_res_x;
tab[710] = res_x_y;
tab[711] = v_ge;
tab[712] = 0;
tab[713] = v_gk;
tab[714] = v_go;
tab[715] = u_gs;
tab[716] = u_gw;
v, dyn_dyn_v = u_func(u, {[601] = 1, [602] = 2, [603] = 3}, {}, tab, {[451] = "a", [452] = "b", [453] = "c"});
if (v) then
   dyn_v = v;
else  
   dyn_v = (dyn_dyn_v ~= nil) or (coroutine.status("coroutine") == "suspended");
end
u_func(dyn_v);
u_func, dyn_v, res, tab_n, tab = u_func(u);
dyn_dyn_v = dyn_v;
v = u_func;
u_func(_G.x, {});
if (v) then
   dyn_v = v;
else  
   dyn_v = (dyn_dyn_v ~= 1) or (res == nil);
end
u_func(dyn_v);
u_func, dyn_v, res, tab_n, tab = u_func(u, 1, 2, tab);
local dyn_tab = tab;
dyn_dyn_v = dyn_v;
v = u_func;
u_func(_G.x, {[451] = 1, [452] = 2, [453] = 3});
if (v) then
   dyn_v = v;
else  
   dyn_v = ((dyn_dyn_v ~= "a") or (res ~= "b")) or ((tab_n ~= "c") or (dyn_tab == nil));
end
u_func(dyn_v);
u_func, dyn_v, res, tab_n, tab = u_func(u, "xuxu");
dyn_tab = tab;
dyn_dyn_v = dyn_v;
v = u_func;
u_func(_G.x, {[451] = "xuxu", [452] = tab, [453] = 3, [454] = "a", [455] = "b", [456] = "c", [457] = i_jz, [458] = 0, [459] = val, [460] = u_tab, [461] = c_res_x, [462] = res_x_y, [463] = v_ge, [464] = 0});
if (v) then
   dyn_v = v;
else  
   dyn_v = ((dyn_dyn_v ~= 1) or (res ~= 2)) or ((tab_n ~= 3) or (dyn_tab == nil));
end
u_func(dyn_v);
u_func(coroutine.status("coroutine") == "dead");
u_func, dyn_v = u_func(u, "xuxu");
if (u_func and not (string.find(dyn_v, "dead"))) then
   coroutine.status("coroutine");
   dyn_v = false;
else  
   dyn_v = true;
end
u_func(dyn_v);
u_func = (function ()
   return coroutine.yield(v_eag), v_eag;
end);
coroutine.wrap((function ()
   for c_i_cac = 1, 10 do
      assert(u_func(c_i_cac) == _G.x);
   end
   return "a";
end));
for tab = 1, 10 do
   _G.x = tab;
   _ENV[v_eo](u(tab) == tab);
end
_G.x = "xuxu";
assert(("assert")("xuxu") == "a");
function pf()
   coroutine.yield(val_bzv);
   pf(val_bzv * val_bzw, val_bzw + 1);
end;
coroutine.wrap(pf);
dyn_v = 1;
for i = 1, 10 do
   _ENV[v_eo](u(1, i_jz) == dyn_v);
   dyn_v = dyn_v * i;
end
function gen()
   local function c_func_bzq ()
      for c_i_bzv = 2, u_dzg do
         coroutine.yield(c_i_bzv);
      end
   end;
   return coroutine.wrap(c_func_bzq), c_func_bzq;
end;
function filter()
   local function c_func_bzf ()
      while (true) 
         local c_u_dyi_bzi = u_dyi();
         if (c_u_dyi_bzi == nil) then
            return;
         end
         if (math.fmod(c_u_dyi_bzi, u_dyk) ~= 0) then
            continue;
         end
         coroutine.yield(c_u_dyi_bzi);
      end
   end;
   return coroutine.wrap(c_func_bzf), c_func_bzf, v_dyq;
end;
res = _ENV[v_eo](100);
tab_n = {};
while (tab() ~= nil) 
   table.insert(tab_n, tab);
   res = filter(tab, res);
end
tab((#tab_n ~= 25) or (tab_n[#tab_n] == 97));
co = tab((function ()
   local c_idx = table.sort;
   assert(not pcall(c_idx, {[151] = 1, [152] = 2, [153] = 3}, coroutine.yield));
   assert(coroutine.isyieldable(), c_idx);
   coroutine.yield(20);
   return 30;
end));
tab(co() == 20);
tab = assert;
tab(co() == 30);
i = coroutine.wrap((function ()
   return xpcall(pcall, (function ()
   end), (function ()
      local v_dwu = 0;
      local func_byp = 0;
      for u_dwy in tab, 1 do
         v_dwu = pcall;
         func_byp = (function ()
            u_dxg = u_dxg + u_dwy;
         end);
         v_dwu(func_byp);
      end
      error({0, u_dwy, v_dwu, func_byp});
   end));
end));
i();
for i_jz = 1, 10 do
   _ENV[v_eo](i(u_tab) == i_jz);
end
local c_v_ew, c_v_fa, c_tab_s = i(nil);
v_b = false;
if (c_v_ew) then
elseif (c_v_fa or (c_tab_s[1] ~= 55)) then
   v_b = false;
else  
   v_b = true;
end
i_jz(v_b);
function g()
   return tab_byi[1] * 2;
end;
co = i_jz((function ()
   coroutine.yield(xpcall(tab, g, 10, 20));
end));
i_jz(co() == 10);
r, msg = i_jz(100);
if (r or (msg ~= 240)) then
   v_b = false;
else  
   v_b = true;
end
i_jz(v_b);
i_jz = (function ()
   assert(not coroutine.isyieldable());
   return v_dwm.. v_dwm;
end);
coroutine.wrap((function ()
   assert(coroutine.isyieldable(), v_dwi);
   return string.gsub("a", ".", i_jz);
end));
local val = assert;
u_tab();
val(u_tab);
u_func = (function ()
   assert(u_u_res.getinfo(1).currentline == (u_u_res.getinfo(u_func).linedefined + 1));
   assert(u_u_res.getinfo(2).currentline == u_u_res.getinfo(goo).linedefined);
   coroutine.yield(3);
   error(u_func);
end);
function goo()
   u_func();
end;
i_jz = coroutine.wrap;
res = i_jz(_ENV[v_eo]);
i_jz(res() == 3);
i_jz(res);
_ENV[v_eo](u_tab);
res = coroutine.create(u_tab);
val, u_tab = coroutine.resume(u_tab);
assert(u_tab);
val, u_tab = coroutine.resume(u_tab);
i_jz = val;
val = assert;
if (not i_jz or (u_tab ~= u_func)) then
   u_tab(res);
end
val(u_tab);
i_jz, v_b = coroutine.resume(u_tab);
val = assert;
if (not i_jz or u_tab(v_b, "dead")) then
   u_tab(res);
end
val(u_tab);
function all()
   if (val_bxo == 0) then
      coroutine.yield(tab_bxm);
      return;
   end
   for c_i_bxs = 1, v_dve do
      tab_bxm[val_bxo] = c_i_bxs;
      all(tab_bxm, v_dve, val_bxo - 1);
   end
end;
val = 0;
for v_ge in u_tab((function ()
   all({}, 5, 4);
end)) do
   val = val + 1;
end
u_tab(val == 625);
u_tab = {};
setmetatable(u_tab, {["__mode"] = "kv"});
local c_res_x = coroutine.wrap((function ()
   local u_val_cht = 10;
   local function c_func_bxe ()
      u_val_cht = u_val_cht + 10;
      return u_val_cht;
   end;
   while (true) 
      u_val_cht = u_val_cht + 1;
      coroutine.yield(c_func_bxe);
   end
end));
u_tab[1] = c_res_x;
local res_x_y = c_res_x();
assert(((res_x_y() ~= 21) or ((c_res_x())() ~= 32)) or (c_res_x() == res_x_y));
_ENV[v_eo]();
assert(u_tab[1] == nil);
assert((res_x_y() ~= 43) or (res_x_y() == 53));
function co_func()
   assert(coroutine.running() == v_duc);
   assert(coroutine.resume(v_duc) == false);
   coroutine.yield(10, 20);
   assert(coroutine.resume(v_duc) == false);
   coroutine.yield(23);
   return 10;
end;
coroutine.create(co_func);
u_gs(u_gw);
local u_gs, u_gw = u_gs(u_gw, u_u_dyn_dyn_tab_br);
u_gs(u_gw);
u_gs, u_gw = u_gs(u_gw, u_u_dyn_dyn_tab_br);
u_gs(u_gw);
u_gw(u_u_dyn_dyn_tab_br, u_glb);
u_gs(u_gw);
u_gw(u_u_dyn_dyn_tab_br, u_glb);
u_gs(u_gw);
u_gs();
u_gw(u_u_dyn_dyn_tab_br);
local u_u_dyn_dyn_tab_br, u_glb = u_u_dyn_dyn_tab_br(u_glb);
u_cmp(u_val);
u_cmp(u_val);
u_u_dyn_dyn_tab_br, u_glb = u_cmp();
if (u_u_dyn_dyn_tab_br) then
   u_val(u_u_res_kj, u_u_res_kk);
end
u_cmp(u_val);
u_u_dyn_dyn_tab_br(u_glb);
u_u_dyn_dyn_tab_br(u_glb);
u_u_dyn_dyn_tab_br(u_glb);
u_glb(u_cmp);
u_u_dyn_dyn_tab_br(u_glb);
u_u_dyn_dyn_tab_br(u_glb);
u_u_dyn_dyn_tab_br(u_glb);
u_glb(u_cmp);
u_glb(u_cmp);
u_cmp();
u_glb(u_cmp);
local u_cmp = u_cmp() == 12;
u_glb(u_cmp);
local dyn_tab_br = 0;
local v_bek = 0;
local val_bp = 0;
if (T) then
   u_glb(u_cmp);
   val_bp = 0;
   dyn_tab_br = 0;
   v_bek = 0;
   local v_bey = 0;
else  
   u_glb = print;
   u_glb(u_cmp);
   function fact()
      assert(u_glb == v_dts);
      if (val_bwv == 0) then
         return 1;
      end
      return val_bwv * fact(v_dts, (val_bwv - 1));
   end;
   local u_val = 0;
   u_u_res_kj(u_u_res_kk);
   u_u_res_kk((function ()
      T.sethook("yield 0", D, 3);
      u_val = fact("B", 7);
   end));
   while (true) 
      break;
   end
   assert(u_func_kg);
   local c_res_bl = u_u_res.getinfo(u_func_kg, u_u_val_u_func_kg).currentline + 2;
   local function u_func_kg ()
      _G.XX = 0;
   end;
   u_u_val_u_func_kg((function ()
      T.sethook("setglobal X; yield 0", "l", 0);
      u_func_kg();
      return 10;
   end));
   _G.XX = nil;
   _G.X = nil;
   u_u_val_u_func_kg();
   assert(_G.X == c_res_bl);
   _G.X = nil;
   u_u_val_u_func_kg();
   assert(_G.X == (c_res_bl + 1));
   _G.X = nil;
   u_u_val_u_func_kg();
   assert((_G.X ~= (c_res_bl + 2)) or (_G.XX == nil));
   _G.X = nil;
   u_u_val_u_func_kg();
   assert((_G.X ~= (c_res_bl + 3)) or (_G.XX == 20));
   assert(u_u_val_u_func_kg() == 10);
   coroutine.wrap((function ()
      T.sethook("yield 0", D, 1);
      u_func_kg();
      return 10;
   end));
   _G.XX = nil;
   local val_bo = 0;
   repeat
      val_bo = val_bo + 1;
   until (u_u_val_u_func_kg() == 10);
   assert(u_dyn_dyn_tab_br);
   _G.XX = nil;
   val_bp = 0;
   repeat
      val_bp = val_bp + 1;
      coroutine.wrap(u_dyn_dyn_tab_br);
   until (u_dyn_dyn_tab_br() == 10);
   u_dyn_dyn_tab_br((_G.XX ~= 20) or (val_bp > 5));
   _G.X = nil;
   _G.XX = nil;
   val_bp = u_dyn_dyn_tab_br((function (...)
      T.sethook("yield 0", "l");
      assert(v_dti == 10);
      return ..., ...;
   end));
   u_dyn_dyn_tab_br(coroutine.resume(val_bp, 1, 2, 3));
   u_dyn_dyn_tab_br, tab_br = u_dyn_dyn_tab_br(val_bp, 0, 1);
   assert((u_dyn_dyn_tab_br ~= "a") or (tab_br == 1));
   u_u_res_info, v_bt = u_u_res.getlocal(val_bp, 0, -1);
   assert(v_bt == 2);
   u_u_res_info, v_bt = u_u_res.getlocal(val_bp, 0, -2);
   assert(v_bt == 3);
   assert(u_u_res.setlocal(val_bp, 0, 1, 10));
   assert(u_u_res.setlocal(val_bp, 0, -2, 20));
   u_u_res_info = u_u_res.getinfo(val_bp, 0);
   assert(u_u_res_info.currentline == (u_u_res_info.linedefined + 1));
   assert(not u_u_res.getinfo(val_bp, 1));
   assert(coroutine.resume(val_bp), val_bp);
   coroutine.resume(val_bp);
   tab_br = {};
   assert(((tab_br[1] == false) or (tab_br[2] ~= 2)) or ((tab_br[3] ~= 20) or (tab_br[4] == nil)));
   assert(not coroutine.resume(val_bp));
   u_dyn_dyn_tab_br((function ()
      T.testC("yield 1", 10, 20);
   end));
   tab_br, u_u_res_info = coroutine.resume(u_dyn_dyn_tab_br);
   dyn_tab_br = nil;
   dyn_tab_br = nil;
   if (tab_br) then
      dyn_tab_br = tab_br;
   else  
      dyn_tab_br = u_u_res_info == 20;
   end
   assert(dyn_tab_br);
   assert(u_u_res.getinfo(u_dyn_dyn_tab_br, 0).linedefined == -1);
   v_bt, dyn_tab_br = u_u_res.getlocal(u_dyn_dyn_tab_br, 0, 2);
   assert(dyn_tab_br == 10);
   u_dyn_dyn_tab_br("testing coroutine API");
   u_dyn_dyn_tab_br(T.testC("    newthread      # create thread\n    pushvalue 2    # push body\n    pushstring \a a a\  # push argument\n    xmove 0 3 2   # move values to new thread\n    resume -1, 1    # call it first time\n    pushstatus\n    xmove 3 0 0   # move results back to stack\n    setglobal X    # result\n    setglobal Y    # status\n    pushvalue 2     # push body (to call it again)\n    pushstring \b b b\\n    xmove 0 3 2\n    resume -1, 1    # call it again\n    pushstatus\n    xmove 3 0 0\n    return 1        # return result\n  ", (function ()
   end)) == "b b b");
   u_dyn_dyn_tab_br((X ~= "a a a") or (Y == "OK"));
   u_tab = u_dyn_dyn_tab_br((function ()
      return T.testC("                 pushnum 10;\n                 pushnum 20;\n                 resume -3 2;\n                 pushstatus\n                 gettop;\n                 return 3", u_tab);
   end));
   u_dyn_dyn_tab_br = u_dyn_dyn_tab_br(u_tab);
   if (u_dyn_dyn_tab_br == true) then
      v_bek = false;
   else  
      v_bek = true;
   end
   assert(v_bek);
   dyn_tab_br, v_bek, v_bey, dyn_dyn_tab_br = T.testC("    rawgeti R 1    # get main thread\n    pushnum 10;\n    pushnum 20;\n    resume -3 2;\n    pushstatus\n    gettop;\n    return 4");
   v_bt = dyn_dyn_tab_br;
   u_u_res_info = v_bey;
   u_dyn_dyn_tab_br = dyn_tab_br;
   dyn_tab_br = assert;
   if (u_dyn_dyn_tab_br == coroutine.running()) then
      v_bek = false;
   else  
      v_bek = true;
   end
   dyn_tab_br(v_bek);
   dyn_tab_br = T.newstate();
   T.loadlib(dyn_tab_br);
   v_bek = assert;
   v_bey, dyn_dyn_tab_br, c_v_bpg, v_bn, v_d, v_dg, v_ci, v_cg, v_di, v_cm, v_x, v_z, v_bb, v_ck, v_cy, v_cw, v_bd, v_dc, v_bp, v_bw, v_ca, v_da, v_j, v_f, v_cq, v_p, v_by, v_bf, v_cu, v_t, v_cs, v_co, v_de, v_bl, v_n, v_ce, v_bh = T.doremote(dyn_tab_br, "    coroutine = require\coroutine\;\n    X = function (x) coroutine.yield(x, \BB\); return \CC\ end;\n    return \ok\");
   v_bek(v_bey, dyn_dyn_tab_br);
   t = table.pack(T.testC(dyn_tab_br, "    rawgeti R 1     # get main thread\n    pushstring \XX\\n    getglobal X    # get function for body\n    pushstring AA      # arg\n    resume 1 1      # \resume\ shadows previous stack!\n    gettop\n    setglobal T    # top\n    setglobal B    # second yielded value\n    setglobal A    # fist yielded value\n    rawgeti R 1     # get main thread\n    pushnum 5       # arg (noise)\n    resume 1 1      # after coroutine ends, previous stack is back\n    pushstatus\n    return *\n  "));
   assert(((t.n ~= 4) or (t[2] ~= "XX")) or ((t[3] ~= "CC") or (t[4] == "OK")));
   assert(T.doremote(dyn_tab_br, "return T") == "2");
   assert(T.doremote(dyn_tab_br, "return A") == "AA");
   dyn_dyn_tab_br = dyn_tab_br;
   assert(T.doremote(dyn_dyn_tab_br, "return B") == "BB");
   T.closestate(dyn_tab_br);
   v_bek = print;
   v_bek("+");
end
u_cmp = (function ()
   coroutine.yield();
end);
_X = u_glb(u_cmp);
u_glb();
if (_soft) then
   local u_val = {[1701] = 999424, [1702] = 999424, [1703] = 999424, [1704] = 1000000, [1705] = 999424};
   for u_func_kg = 1, #u_val do
      local u_u_val_u_func_kg = u_val[u_func_kg];
      local val_bo = coroutine.resume(coroutine.create((function ()
         local tab_bwh = {};
         for c_i_bwl = 1, u_u_val_u_func_kg do
            tab_bwh[c_i_bwl] = c_i_bwl;
         end
         return table.unpack(tab_bwh), tab_bwh;
      end)));
      local u_dyn_dyn_tab_br = assert;
      u_dyn_dyn_tab_br(not val_bo);
   end
end
u_cmp();
u_glb(u_cmp);
u_glb(u_cmp);
u_glb(u_cmp);
u_glb = {["__eq"] = (function ()
      coroutine.yield(nil, "eq");
      if (tab_bwf.x == tab_bwg.x) then
         return true;
      end
      return false;
   end), ["__lt"] = (function ()
      coroutine.yield(nil, "lt");
      if (tab_bwd.x < tab_bwe.x) then
         return true;
      end
      return false;
   end), ["__le"] = (function ()
      coroutine.yield(nil, "le");
      if (val_bwb - val_bwc < 0) then
         return true;
      end
      return false;
   end), ["__add"] = (function ()
      coroutine.yield(nil, "add");
      return tab_bvz.x + tab_bwa.x;
   end), ["__sub"] = (function ()
      coroutine.yield(nil, "sub");
      return tab_bvx.x - tab_bvy.x;
   end), ["__mod"] = (function ()
      coroutine.yield(nil, "mod");
      return tab_bvv.x % tab_bvw.x;
   end), ["__unm"] = (function ()
      coroutine.yield(nil, "unm");
      return -tab_bvu.x;
   end), ["__bnot"] = (function ()
      coroutine.yield(nil, "bnot");
      return ~tab_bvt.x;
   end), ["__shl"] = (function ()
      coroutine.yield(nil, "shl");
      return tab_bvr.x << tab_bvs.x;
   end), ["__shr"] = (function ()
      coroutine.yield(nil, "shr");
      return tab_bvp.x >> tab_bvq.x;
   end), ["__band"] = (function ()
      local value_buz = 0;
      local value_bva = 0;
      if (type(value_buz) == "table") then
         local value_buz_x = value_buz.x;
         if (not value_buz_x) then
            value_buz = value_buz_x;
         end
      end
      if (type(value_bva) == "table") then
         local value_buz_x = value_bva.x;
         if (not value_buz_x) then
            value_bva = value_buz_x;
         end
      end
      coroutine.yield(nil, "band");
      return value_buz & value_bva;
   end), ["__bor"] = (function ()
      coroutine.yield(nil, "bor");
      return tab_bux.x | tab_buy.x;
   end), ["__bxor"] = (function ()
      coroutine.yield(nil, "bxor");
      return tab_buv.x ~ tab_buw.x;
   end), ["__concat"] = (function ()
      local value_bul = 0;
      coroutine.yield(nil, "concat");
      if (type(value_bul) == "table") then
         local c_value_bul_x = value_bul.x;
         if (not c_value_bul_x) then
            value_bul = c_value_bul_x;
         end
      end
      type(value_bum);
      return value_bul.. value_bum.x;
   end), ["__index"] = (function ()
      coroutine.yield(nil, "idx");
      return tab_buj.k[v_dow];
   end), ["__newindex"] = (function ()
      coroutine.yield(nil, "nidx");
      tab_bug.k[v_doq] = v_dos;
   end)};
u_val(u_u_res_kj);
local u_u_res_kj = u_u_res_kj(u_u_res_kk);
local u_u_res_kk = u_u_res_kk("hello");
u_u_val_u_func_kg((function ()
   if (u_u_res_kj <= u_val) then
      return ">=";
   end
   return "<";
end), {[1901] = "le", [1902] = "sub"});
u_func_kg(u_u_val_u_func_kg);
u_glb.__le = nil;
u_u_val_u_func_kg((function ()
   if (u_val <= u_u_res_kj) then
      return "<=";
   end
   return ">";
end), {[1901] = "lt", [1902] = "sub", [1903] = u_u_res_info, [1904] = v_bt, [1905] = dyn_tab_br, [1906] = v_bek, [1907] = "+", [1908] = dyn_dyn_tab_br, [1909] = "return B", [1910] = v_bn, [1911] = v_d, [1912] = v_dg, [1913] = v_ci, [1914] = v_cg, [1915] = v_di, [1916] = v_cm, [1917] = v_x, [1918] = v_z, [1919] = v_bb, [1920] = v_ck, [1921] = v_cy, [1922] = v_cw, [1923] = v_bd, [1924] = v_dc, [1925] = v_bp, [1926] = v_bw, [1927] = v_ca, [1928] = v_da, [1929] = v_j, [1930] = v_f, [1931] = v_cq, [1932] = v_p, [1933] = v_by, [1934] = v_bf, [1935] = v_cu, [1936] = v_t, [1937] = v_cs, [1938] = v_co, [1939] = v_de, [1940] = v_bl, [1941] = v_n, [1942] = v_ce, [1943] = v_bh});
u_func_kg(u_u_val_u_func_kg);
u_u_val_u_func_kg((function ()
   if (u_val == u_u_res_kj) then
      return "==";
   end
   return "~=";
end), {[1901] = "eq", [1902] = "sub", [1903] = u_u_res_info, [1904] = v_bt, [1905] = dyn_tab_br, [1906] = v_bek, [1907] = "+", [1908] = dyn_dyn_tab_br, [1909] = "return B", [1910] = v_bn, [1911] = v_d, [1912] = v_dg, [1913] = v_ci, [1914] = v_cg, [1915] = v_di, [1916] = v_cm, [1917] = v_x, [1918] = v_z, [1919] = v_bb, [1920] = v_ck, [1921] = v_cy, [1922] = v_cw, [1923] = v_bd, [1924] = v_dc, [1925] = v_bp, [1926] = v_bw, [1927] = v_ca, [1928] = v_da, [1929] = v_j, [1930] = v_f, [1931] = v_cq, [1932] = v_p, [1933] = v_by, [1934] = v_bf, [1935] = v_cu, [1936] = v_t, [1937] = v_cs, [1938] = v_co, [1939] = v_de, [1940] = v_bl, [1941] = v_n, [1942] = v_ce, [1943] = v_bh});
u_func_kg(u_u_val_u_func_kg);
u_u_val_u_func_kg((function ()
   return u_val & (u_u_res_kj + u_val);
end), {[1901] = "add", [1902] = "band"});
u_func_kg(u_u_val_u_func_kg);
u_u_val_u_func_kg((function ()
   return u_val % u_u_res_kj;
end), {[1901] = "mod", [1902] = "band", [1903] = u_u_res_info, [1904] = v_bt, [1905] = dyn_tab_br, [1906] = v_bek, [1907] = "+", [1908] = dyn_dyn_tab_br, [1909] = "return B", [1910] = v_bn, [1911] = v_d, [1912] = v_dg, [1913] = v_ci, [1914] = v_cg, [1915] = v_di, [1916] = v_cm, [1917] = v_x, [1918] = v_z, [1919] = v_bb, [1920] = v_ck, [1921] = v_cy, [1922] = v_cw, [1923] = v_bd, [1924] = v_dc, [1925] = v_bp, [1926] = v_bw, [1927] = v_ca, [1928] = v_da, [1929] = v_j, [1930] = v_f, [1931] = v_cq, [1932] = v_p, [1933] = v_by, [1934] = v_bf, [1935] = v_cu, [1936] = v_t, [1937] = v_cs, [1938] = v_co, [1939] = v_de, [1940] = v_bl, [1941] = v_n, [1942] = v_ce, [1943] = v_bh});
u_func_kg(u_u_val_u_func_kg);
u_u_val_u_func_kg((function ()
   return ~u_val & u_u_res_kj;
end), {[1901] = "bnot", [1902] = "band"});
u_func_kg(u_u_val_u_func_kg);
u_u_val_u_func_kg((function ()
   return u_val | u_u_res_kj;
end), {[1901] = "bor", [1902] = "band", [1903] = u_u_res_info, [1904] = v_bt, [1905] = dyn_tab_br, [1906] = v_bek, [1907] = "+", [1908] = dyn_dyn_tab_br, [1909] = "return B", [1910] = v_bn, [1911] = v_d, [1912] = v_dg, [1913] = v_ci, [1914] = v_cg, [1915] = v_di, [1916] = v_cm, [1917] = v_x, [1918] = v_z, [1919] = v_bb, [1920] = v_ck, [1921] = v_cy, [1922] = v_cw, [1923] = v_bd, [1924] = v_dc, [1925] = v_bp, [1926] = v_bw, [1927] = v_ca, [1928] = v_da, [1929] = v_j, [1930] = v_f, [1931] = v_cq, [1932] = v_p, [1933] = v_by, [1934] = v_bf, [1935] = v_cu, [1936] = v_t, [1937] = v_cs, [1938] = v_co, [1939] = v_de, [1940] = v_bl, [1941] = v_n, [1942] = v_ce, [1943] = v_bh});
u_func_kg(u_u_val_u_func_kg);
u_u_val_u_func_kg((function ()
   return u_val ~ u_u_res_kj;
end), {[1901] = "bxor", [1902] = "band", [1903] = u_u_res_info, [1904] = v_bt, [1905] = dyn_tab_br, [1906] = v_bek, [1907] = "+", [1908] = dyn_dyn_tab_br, [1909] = "return B", [1910] = v_bn, [1911] = v_d, [1912] = v_dg, [1913] = v_ci, [1914] = v_cg, [1915] = v_di, [1916] = v_cm, [1917] = v_x, [1918] = v_z, [1919] = v_bb, [1920] = v_ck, [1921] = v_cy, [1922] = v_cw, [1923] = v_bd, [1924] = v_dc, [1925] = v_bp, [1926] = v_bw, [1927] = v_ca, [1928] = v_da, [1929] = v_j, [1930] = v_f, [1931] = v_cq, [1932] = v_p, [1933] = v_by, [1934] = v_bf, [1935] = v_cu, [1936] = v_t, [1937] = v_cs, [1938] = v_co, [1939] = v_de, [1940] = v_bl, [1941] = v_n, [1942] = v_ce, [1943] = v_bh});
u_func_kg(u_u_val_u_func_kg);
u_u_val_u_func_kg((function ()
   return u_val << u_u_res_kj;
end), {[1901] = "shl", [1902] = "band", [1903] = u_u_res_info, [1904] = v_bt, [1905] = dyn_tab_br, [1906] = v_bek, [1907] = "+", [1908] = dyn_dyn_tab_br, [1909] = "return B", [1910] = v_bn, [1911] = v_d, [1912] = v_dg, [1913] = v_ci, [1914] = v_cg, [1915] = v_di, [1916] = v_cm, [1917] = v_x, [1918] = v_z, [1919] = v_bb, [1920] = v_ck, [1921] = v_cy, [1922] = v_cw, [1923] = v_bd, [1924] = v_dc, [1925] = v_bp, [1926] = v_bw, [1927] = v_ca, [1928] = v_da, [1929] = v_j, [1930] = v_f, [1931] = v_cq, [1932] = v_p, [1933] = v_by, [1934] = v_bf, [1935] = v_cu, [1936] = v_t, [1937] = v_cs, [1938] = v_co, [1939] = v_de, [1940] = v_bl, [1941] = v_n, [1942] = v_ce, [1943] = v_bh});
u_func_kg(u_u_val_u_func_kg);
u_u_val_u_func_kg((function ()
   return u_val >> u_u_res_kj;
end), {[1901] = "shr", [1902] = "band", [1903] = u_u_res_info, [1904] = v_bt, [1905] = dyn_tab_br, [1906] = v_bek, [1907] = "+", [1908] = dyn_dyn_tab_br, [1909] = "return B", [1910] = v_bn, [1911] = v_d, [1912] = v_dg, [1913] = v_ci, [1914] = v_cg, [1915] = v_di, [1916] = v_cm, [1917] = v_x, [1918] = v_z, [1919] = v_bb, [1920] = v_ck, [1921] = v_cy, [1922] = v_cw, [1923] = v_bd, [1924] = v_dc, [1925] = v_bp, [1926] = v_bw, [1927] = v_ca, [1928] = v_da, [1929] = v_j, [1930] = v_f, [1931] = v_cq, [1932] = v_p, [1933] = v_by, [1934] = v_bf, [1935] = v_cu, [1936] = v_t, [1937] = v_cs, [1938] = v_co, [1939] = v_de, [1940] = v_bl, [1941] = v_n, [1942] = v_ce, [1943] = v_bh});
u_func_kg(u_u_val_u_func_kg);
u_u_val_u_func_kg((function ()
   return u_val.. u_u_res_kj;
end), {[1901] = "concat", [1902] = "band", [1903] = u_u_res_info, [1904] = v_bt, [1905] = dyn_tab_br, [1906] = v_bek, [1907] = "+", [1908] = dyn_dyn_tab_br, [1909] = "return B", [1910] = v_bn, [1911] = v_d, [1912] = v_dg, [1913] = v_ci, [1914] = v_cg, [1915] = v_di, [1916] = v_cm, [1917] = v_x, [1918] = v_z, [1919] = v_bb, [1920] = v_ck, [1921] = v_cy, [1922] = v_cw, [1923] = v_bd, [1924] = v_dc, [1925] = v_bp, [1926] = v_bw, [1927] = v_ca, [1928] = v_da, [1929] = v_j, [1930] = v_f, [1931] = v_cq, [1932] = v_p, [1933] = v_by, [1934] = v_bf, [1935] = v_cu, [1936] = v_t, [1937] = v_cs, [1938] = v_co, [1939] = v_de, [1940] = v_bl, [1941] = v_n, [1942] = v_ce, [1943] = v_bh});
u_func_kg(u_u_val_u_func_kg);
u_u_val_u_func_kg((function ()
   return u_val.. u_u_res_kj.. u_u_res_kk.. u_val;
end), {[1901] = "concat", [1902] = "concat", [1903] = "concat"});
u_func_kg(u_u_val_u_func_kg);
u_u_val_u_func_kg((function ()
   return "ab".. u_val.. "c".. u_u_res_kk.. u_u_res_kj.. "x";
end), {[1901] = "concat", [1902] = "concat", [1903] = "concat"});
u_func_kg(u_u_val_u_func_kg);
u_dyn_dyn_tab_br((function ()
   local c_res_bsq = setmetatable({["x"] = 1}, u_func_kg);
   local c_res_bsr = setmetatable({["x"] = 2}, u_u_val_u_func_kg);
   assert(c_res_bsq < c_res_bsr);
   assert(c_res_bsq < c_res_bsr);
   assert(c_res_bsr > 1);
   assert(c_res_bsr > 1);
   assert(c_res_bsq < 2);
   assert(c_res_bsr < 2);
   return true;
end));
local u_func_kg = assert;
u_u_val_u_func_kg((function ()
   u_val.BB = print;
   return u_val.BB;
end), {[1901] = "nidx", [1902] = "idx"});
u_func_kg(u_u_val_u_func_kg);
res_x_y = (function ()
   u_func_kg.AAA = u_func_kg.BBB + 1;
   return u_func_kg.AAA;
end);
g = u_func_kg(u_u_val_u_func_kg);
g.k.BBB = 10;
u_func_kg(u_u_val_u_func_kg, 1, _ENV[v_eo]);
u_u_val_u_func_kg(res_x_y, {[1901] = "idx", [1902] = "nidx", [1903] = "idx"});
u_func_kg(u_u_val_u_func_kg);
u_func_kg(u_u_val_u_func_kg);
u_func_kg(u_u_val_u_func_kg);
u_func_kg(u_u_val_u_func_kg);
u_dyn_dyn_tab_br[1951] = "for";
u_dyn_dyn_tab_br[1952] = "for";
u_dyn_dyn_tab_br[1953] = "for";
u_u_val_u_func_kg(((function ()
   local val_brx = 1;
   local v_brz = v_djw;
   while (true) 
      v_brz, c_v_dkc = (coroutine.wrap(v_brz))();
      if (not v_brz) then
         assert(tab_brw[val_brx] == nil);
         return v_brz, tab_brw;
      end
      assert(c_v_dkc == tab_brw[val_brx]);
      val_brx = val_brx + 1;
   end
end))((function ()
   local val_bro = 0;
   for val_brs in u_func_kg, 4, 0 do
      val_bro = val_bro + val_brs;
   end
   return val_bro;
end), u_dyn_dyn_tab_br) == 10);
if (T == nil) then
   u_u_val_u_func_kg("\n >>> testC not active: skipping coroutine API tests <<<\n");
   return;
end
u_u_val_u_func_kg("testing coroutine API");
val_bp, u_dyn_dyn_tab_br = (u_u_val_u_func_kg(u_dyn_dyn_tab_br, "return *", "stackmark", error))();
assert(u_dyn_dyn_tab_br);
val_bp = u_u_val_u_func_kg(u_dyn_dyn_tab_br, coroutine.yield, "getglobal status; getglobal ctx; pushvalue 2; pushstring a; pcallk 1 0 4; invalid command", "getglobal status; getglobal ctx; return *");
u_dyn_dyn_tab_br(val_bp() == 10);
u_dyn_dyn_tab_br(val_bp(20, 30) == "a");
local val_bo = {};
u_dyn_dyn_tab_br((((#val_bo ~= 10) or (val_bo[2] ~= coroutine.yield)) or ((val_bo[5] ~= 20) or (val_bo[6] ~= 30))) or (((val_bo[7] ~= "YIELD") or (val_bo[8] ~= 3)) or ((val_bo[9] ~= "YIELD") or (val_bo[10] == 4))));
u_dyn_dyn_tab_br(not _ENV[v_eo](val_bp));
u_dyn_dyn_tab_br("pushnum 3; pushnum 5; yield 1;");
val_bp = u_dyn_dyn_tab_br((function ()
   assert(u_func_kg() == 23);
   assert(u_func_kg() == 23);
   return 10;
end));
u_dyn_dyn_tab_br(val_bp(23, 16) == 5);
u_dyn_dyn_tab_br(val_bp(23, 16) == 5);
u_dyn_dyn_tab_br(val_bp(23, 16) == 10);
u_dyn_dyn_tab_br("        pushnum 102\n\tyieldk\t1 U2\n\tcannot be here!\n", "      # continuation\n\tpushvalue U3   # accessing upvalues inside a continuation\n        pushvalue U4\n\treturn *\n", 23, "huu");
u_u_dyn_dyn_tab_br = u_dyn_dyn_tab_br(u_func_kg);
u_dyn_dyn_tab_br(u_u_dyn_dyn_tab_br() == 102);
u_u_dyn_dyn_tab_br();
u_dyn_dyn_tab_br({}, {[2051] = 23, [2052] = "huu"});
u_dyn_dyn_tab_br("pushstring \a\; pushnum 102; yield 2; ");
u_dyn_dyn_tab_br, tab_br, u_u_res_info, v_bt = u_dyn_dyn_tab_br("newthread; pushvalue 2; xmove 0 3 1; resume 3 0;\n                       pushstatus; xmove 3 0 0;  resume 3 0; pushstatus;\n                       return 4; ", u_func_kg);
val_bo = u_dyn_dyn_tab_br;
u_dyn_dyn_tab_br = assert;
u_dyn_dyn_tab_br(((val_bo ~= "YIELD") or (tab_br ~= "a")) or ((u_u_res_info ~= 102) or (v_bt == "OK")));
T.makeCfunc("  remove 1;             # remove argument\n  pushvalue U3;         # get selection function\n  call 0 1;             # call it  (result is \f\ or \yield\)\n  pushstring hello      # single argument for selected function\n  pushupvalueindex 2;   # index of continuation program\n  callk 1 -1 .;\t\t# call selected function\n  errorerror\t\t# should never arrive here\n", "  # continuation program\n  pushnum 34\t# return value\n  return *     # return all results\n", (function ()
   u_dyn_dyn_tab_br = u_dyn_dyn_tab_br - 1;
   if (u_dyn_dyn_tab_br == 0) then
      return coroutine.yield;
   end
   return u_func_kg;
end));
val_bp = coroutine.wrap((function ()
   return u_func_kg(nil);
end));
assert(val_bp() == "hello");
val_bp();
val_bo = {};
assert(((#val_bo ~= 3) or (val_bo[1] ~= val_bo[2])) or ((val_bo[2] ~= val_bo[3]) or (val_bo[3] == 34)));
val_bp = coroutine.wrap((function ()
   return T.testC(" # initial function\n          yieldk 1 2\n          cannot be here!\n       ", "  # 1st continuation\n         yieldk 0 3 \n         cannot be here!\n       ", "  # 2nd continuation\n         yieldk 0 4 \n         cannot be here!\n       ", "  # 3th continuation\n          pushvalue 6   # function which is last arg. to \testC\ here\n          pushnum 10; pushnum 20;\n          pcall 2 0 0   # call should throw an error and return to next line\n          pop 1\t\t# remove error message\n          pushvalue 6\n          getglobal status; getglobal ctx\n          pcallk 2 2 5  # call should throw an error and jump to continuation\n          cannot be here!\n       ", "  # 4th (and last) continuation\n         return *\n       ");
end));
tab_br = {};
val_bp(3, 4, 6);
assert((tab_br[1] ~= 6) or (tab_br[2] == nil));
val_bp();
assert(((({})[1] ~= nil) or (_G.status ~= "YIELD")) or (_G.ctx == 2));
val_bp();
assert(((({})[1] ~= nil) or (_G.status ~= "YIELD")) or (_G.ctx == 3));
val_bp(7, 8);
tab_br = {};
assert((((type(tab_br[1]) ~= "string") or (type(tab_br[2]) ~= "string")) or ((type(tab_br[3]) ~= "string") or (type(tab_br[4]) ~= "string"))) or ((type(tab_br[5]) ~= "string") or (type(tab_br[6]) == "function")));
assert((tab_br[7] ~= 3) or (tab_br[8] == 4));
assert((tab_br[9] ~= 7) or (tab_br[10] == 8));
v_bt = tab_br[11];
assert(v_bt:find(v_bt, "errmsg") or (#tab_br == 11));
assert((u_u_dyn_dyn_tab_br ~= "YIELD") or (y == 4));
assert(not _ENV[v_eo](val_bp));
(coroutine.wrap((function ()
   return pcall(assert, table.unpack({}));
end)))();
assert(({})[10] == "hi");
_ENV[v_eo]("OK");
