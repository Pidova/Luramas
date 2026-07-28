u_func("testing language/library basics");
function concat(...)
   return (select("#", ...) ~= 0) or tostring(value_bph);
end;
u_func(tostring(1) == "1");
u_func(tostring(-1) == "-1");
u_func(tostring(1.125) == "1.125");
u_func(tostring(true) == "true");
u_func(tostring(nil) == "nil");
u_func(select("#", (function ()
end)()) == 0);
u_func(select("#", (function ()
end)()) == 0);
u_func(true);
u_func(true);
u_func(true);
u_func(true);
local function u_func ()
   return v_dii;
end;
assert(u_func(1) == nil);
assert(u_func(1, 2) == 2);
assert(u_func(1, 2, 3) == 2);
assert(concat(pcall((function ()
end))) == "true");
assert(concat(pcall((function ()
   return nil;
end))) == "true,nil");
assert(concat(pcall((function ()
   return 1, 2, 3;
end))) == "true,1,2,3");
assert(concat(pcall((function ()
   error("oops");
end))) == "false,basic.lua:39: oops");
assert(true);
assert((function ()
   a = 1;
   a = 2;
   return a;
end)() == 2);
assert((function ()
   b = nil;
   return 1;
end)() == 1);
assert((function ()
   b = nil;
   return b;
end)() == nil);
assert((function ()
   b = 2;
   local c_glb = b;
   b = 1;
   return c_glb;
end)() == 2);
assert((function ()
   b = 2;
   b = 1;
   return b;
end)() == 1);
assert((function ()
   _G.foo = 1;
   return _G.foo;
end)() == 1);
assert((function ()
   _G.bar = 1;
   return _G.bar;
end)() == 1);
assert((function ()
   (function ()
      u_dia = 2;
   end)();
   return 1;
end)() == 2);
assert((({-1})[1] + 43) == 42);
assert((({43})[1] - 1) == 42);
assert((function ()
   local tab_bow = {};
   local c_val_boy, c_v_dhq = (function ()
      return 43, -1;
   end)();
   tab_bow[1] = c_v_dhq;
   return c_val_boy + tab_bow[1];
end)() == 42);
assert((function ()
   local tab_boo = {};
   local c_v_dha, c_val_bot = (function ()
      return 43, -1;
   end)();
   tab_boo[1] = c_v_dha;
   return c_val_bot + tab_boo[1];
end)() == 42);
assert((function ()
   u_func = (function ()
      return u_dgs;
   end);
   return u_func();
end)() == 1);
assert((function ()
   u_func = (function ()
      return (function ()
         return u_dgk;
      end);
   end);
   return u_func()();
end)() == 1);
assert((function ()
   u_func = (function ()
      return (function ()
         return u_dge;
      end);
   end);
   return u_func(1)();
end)() == 1);
assert((function ()
   u_func = (function ()
      return (function ()
         return u_dfw;
      end);
   end);
   return u_func()();
end)() == 1);
assert((function ()
   u_func = (function ()
      return (function ()
         return u_dfo;
      end);
   end);
   return u_func()();
end)() == 2);
assert((function ()
   u_func = (function ()
      (function ()
         u_dfg = 2;
      end)();
      return 1;
   end);
   return u_func();
end)() == 2);
assert((function ()
   return ({f = 5, get = (function ()
      return (function ()
         return u_dey.f;
      end)();
   end)}):get();
end)() == 5);
assert((function ()
   u_func = (function ()
      return ({f = 5, get = (function ()
         return (function ()
            return u_deu.f;
         end);
      end)}):get();
   end);
   return u_func()();
end)() == 5);
assert(true);
assert((if not (nil) then nil else 2) == nil);
assert(false);
assert(true);
assert(false);
assert(false);
assert(false);
assert(false);
assert((function ()
   return tostring(value_bnj);
end)(-0) == "0");
assert((function ()
   return tostring(value_bni);
end)(-0) == "-0");
assert((function ()
   return tostring(-v_dek);
end)(0) == "0");
assert((function ()
   return tostring((val_bnf - val_bnf));
end)((1 / 0)) == "nan");
assert((function ()
   return tostring(0);
end)((0 / 0)) == "nan");
assert((function ()
   return tostring((val_bne / 0));
end)(0) == "1");
assert((function ()
   return tostring((val_bnd / 0));
end)(0) == "1");
assert(true);
assert(false);
assert(false);
assert(false);
assert(false);
assert(false);
assert(false);
assert(false);
assert(false);
assert(false);
assert(false);
assert((function ()
   return tostring(0);
end)() == "nan");
assert(false);
assert(false);
assert(concat(pcall((function ()
   return "1" .. nil .. "2";
end))):match("^false,.*attempt to concatenate nil with string"));
assert(true);
assert(true);
assert(true);
assert(true);
assert(true);
assert(true);
assert(true);
assert((if not (nil) then nil else 2) == nil);
assert(true);
assert((if (nil) then nil else 2) == 2);
assert(true);
assert(true);
assert(true);
assert(true);
assert((function ()
   return 12 % val_bnc;
end)(5) == 2);
assert(("2" + 1) == 3);
assert(("0xa" * 2) == 20);
assert(not true == false);
assert(not false == true);
assert(not nil == true);
assert(#_G == 0);
assert(#({1, 2}) == 2);
assert(true);
assert(true);
assert((function ()
   local c_res_bmz = newproxy(true);
   getmetatable(c_res_bmz).__len = (function ()
      return 42;
   end);
   return #c_res_bmz;
end)() == 42);
assert((function ()
   local c_tab_bmw = {};
   setmetatable(c_tab_bmw, {__len = (function ()
      return 42;
   end)});
   return #c_tab_bmw;
end)() == 42);
assert((function ()
   local val_bmo = 10;
   local val_bmp = 1;
   while (true) do
      if (val_bmo < 1) then
         return val_bmp;
      end
      val_bmp *= 2;
      val_bmo -= 1;
   end
end)() == 512);
assert((function ()
   local val_bmg = 10;
   local val_bmh = 1;
   while (true) do
      val_bmh *= 2;
      val_bmg -= 1;
      if (val_bmg == 1) then
         return val_bmh;
      end
   end
end)() == 512);
assert((function ()
   local val_bly = 10;
   local val_blz = 1;
   while (true) do
      val_blz *= 2;
      val_bly -= 1;
      if (val_bly == 1) then
         return val_blz;
      end
   end
end)() == 512);
assert((function ()
   local val_blq = 10;
   local val_blr = 1;
   repeat
      val_blr *= 2;
      val_blq -= 1;
   until (val_blq ~= 1);
   return val_blr;
end)() == 512);
assert((function ()
   local val_bli = 10;
   local val_blj = 1;
   while (true) do
      val_blj *= 2;
      val_bli -= 1;
      if ((val_bli == 1) or false) then
         return val_blj;
      end
   end
end)() == 512);
assert((function ()
   local val_bla = 10;
   local val_blb = 1;
   while (true) do
      val_blb *= 2;
      val_bla -= 1;
      if (val_bla == 1) then
         return val_blb;
      end
   end
end)() == 512);
assert((function ()
end)() == nil);
assert((function ()
   local val_bkw = 1;
   for c_i_bkz = 1, 9 do
      val_bkw *= 2;
   end
end)() == 512);
assert((function ()
   local val_bks = 1;
   for c_i_bkv = 1, 9, 2 do
      val_bks *= 2;
   end
end)() == 32);
assert((function ()
   local val_bko = 1;
   for c_i_bkr = 1, 9, -2 do
      val_bko *= 2;
   end
end)() == 1);
assert((function ()
   local val_bkk = 1;
   for c_i_bkn = 9, 1, -2 do
      val_bkk *= 2;
   end
end)() == 32);
assert((function ()
   local val_bke = 1;
   for c_i_bkh = 1, 9 do
      val_bke *= 2;
      if (val_bke == 128) then
         return val_bke;
      end
   end
end)() == 128);
assert((function ()
   local val_bjy = 1;
   for c_i_bkb = 1, 9 do
      val_bjy *= 2;
      if (val_bjy == 128) then
         return val_bjy;
      end
   end
end)() == 128);
assert((function ()
   local val_bju = 1;
   for c_i_bjx = 9, 1, -2 do
      val_bju *= 2;
   end
end)() == 32);
local u_res = tonumber("0");
assert((function ()
   local val_bjo = 0;
   for c_i_bjr = 1, 10, 0 do
      val_bjo += 1;
      if (val_bjo > 10) then
         return val_bjo;
      end
   end
end)() == 0);
assert((function ()
   local val_bji = 0;
   for c_i_bjl = 10, 1, 0 do
      val_bji += 1;
      if (val_bji > 10) then
         return val_bji;
      end
   end
end)() == 11);
assert((function ()
   local val_bjb = 0;
   for c_i_bje = 1, 10, u_res do
      val_bjb += 1;
      if (val_bjb > 10) then
         return val_bjb;
      end
   end
end)() == 0);
assert((function ()
   local val_biu = 0;
   for c_i_bix = 10, 1, u_res do
      val_biu += 1;
      if (val_biu > 10) then
         return val_biu;
      end
   end
end)() == 11);
local u_res_jy = tonumber("nan");
assert((function ()
   local val_biq = 0;
   for c_i_bit = 1, 0 / 0 do
      val_biq += 1;
   end
end)() == 0);
assert((function ()
   local val_bim = 0;
   for c_i_bip = 1, 0 / 0, -1 do
      val_bim += 1;
   end
end)() == 0);
assert((function ()
   local val_bih = 0;
   for c_i_bik = 1, u_res_jy do
      val_bih += 1;
   end
end)() == 0);
assert((function ()
   local val_bic = 0;
   for c_i_bif = 1, u_res_jy, -1 do
      val_bic += 1;
   end
end)() == 0);
assert((function ()
   local val_bhy = 0;
   for c_i_bib = 1, 10, 0 / 0 do
      val_bhy += 1;
   end
end)() == 0);
assert((function ()
   local val_bhu = 0;
   for c_i_bhx = 10, 1, 0 / 0 do
      val_bhu += 1;
   end
end)() == 1);
assert((function ()
   local val_bhp = 0;
   for c_i_bhs = 1, 10, u_res_jy do
      val_bhp += 1;
   end
end)() == 0);
assert((function ()
   local val_bhk = 0;
   for c_i_bhn = 10, 1, u_res_jy do
      val_bhk += 1;
   end
end)() == 1);
assert((function ()
   local val_bhg = 0;
   for c_i_bhj = -math.huge, 0, math.huge do
      val_bhg += 1;
   end
end)() == 1);
assert((function ()
   local val_bhc = 0;
   for c_i_bhf = math.huge, math.huge, -math.huge do
      val_bhc += 1;
   end
end)() == 1);
assert((function ()
   local built_str_bgu = "";
   local c_v_crm, c_v_cro = ipairs({5, 6, 7});
   for v_crq in c_v_cro do
      built_str_bgu = built_str_bgu .. v_crq;
   end
end)() == "123");
assert((function ()
   local built_str_bgl = "";
   local c_v_cqu, c_v_cqw = ipairs({5, 6, 7});
   for k_bgp, v_bgq in c_v_cqw do
      built_str_bgl = built_str_bgl .. k_bgp;
   end
end)() == "123");
assert((function ()
   local built_str_bgc = "";
   local c_v_cqc, c_v_cqe = ipairs({5, 6, 7});
   for k_bgg, v_bgh in c_v_cqe do
      built_str_bgc = built_str_bgc .. v_bgh;
   end
end)() == "567");
assert((function ()
   local built_str_bfu = "";
   local c_v_cpm, c_v_cpo = ipairs({
      5, 
      6, 
      7, 
      nil, 
      8});
   for v_cpq in c_v_cpo do
      built_str_bfu = built_str_bfu .. v_cpq;
   end
end)() == "123");
assert((function ()
   local built_str_bfl = "";
   local c_v_cou, c_v_cow = ipairs({
      5, 
      6, 
      7, 
      nil, 
      8});
   for k_bfp, v_bfq in c_v_cow do
      built_str_bfl = built_str_bfl .. k_bfp;
   end
end)() == "123");
assert((function ()
   local built_str_bfc = "";
   local c_v_coc, c_v_coe = ipairs({
      5, 
      6, 
      7, 
      nil, 
      8});
   for k_bfg, v_bfh in c_v_coe do
      built_str_bfc = built_str_bfc .. v_bfh;
   end
end)() == "567");
assert(concat(ipairs({5, 6, 7})({5, 6, 7}, 2)) == "3,7");
assert((function ()
   local built_str_beu = "";
   local c_v_cnm, c_v_cno = pairs({5, 6, 7});
   for v_cnq in c_v_cno do
      built_str_beu = built_str_beu .. v_cnq;
   end
end)() == "123");
assert((function ()
   local built_str_bel = "";
   local c_v_cmu, c_v_cmw = pairs({5, 6, 7});
   for k_bep, v_beq in c_v_cmw do
      built_str_bel = built_str_bel .. k_bep;
   end
end)() == "123");
assert((function ()
   local built_str_bec = "";
   local c_v_cmc, c_v_cme = pairs({5, 6, 7});
   for k_beg, v_beh in c_v_cme do
      built_str_bec = built_str_bec .. v_beh;
   end
end)() == "567");
assert((function ()
   local built_str_bdu = "";
   local c_v_clm, c_v_clo = pairs({
      5, 
      6, 
      7, 
      nil, 
      8});
   for v_clq in c_v_clo do
      built_str_bdu = built_str_bdu .. v_clq;
   end
end)() == "1235");
assert((function ()
   local built_str_bdl = "";
   local c_v_cku, c_v_ckw = pairs({
      5, 
      6, 
      7, 
      nil, 
      8});
   for k_bdp, v_bdq in c_v_ckw do
      built_str_bdl = built_str_bdl .. k_bdp;
   end
end)() == "1235");
assert((function ()
   local built_str_bdc = "";
   local c_v_ckc, c_v_cke = pairs({
      5, 
      6, 
      7, 
      nil, 
      8});
   for k_bdg, v_bdh in c_v_cke do
      built_str_bdc = built_str_bdc .. v_bdh;
   end
end)() == "5678");
assert((function ()
   local tab_bcy = {};
   for v_cju in pairs({a = 1, b = 2, c = 3}) do
      tab_bcy[v_cju] = 1;
   end
end)() == 3);
assert((function ()
   local tab_bct = {};
   for k_bcx, v_bcy in pairs({a = 1, b = 2, c = 3}) do
      tab_bct[k_bcx] = 1;
   end
end)() == 3);
assert((function ()
   local tab_bcn = {};
   for k_bcr, v_bcs in pairs({a = 1, b = 2, c = 3}) do
      tab_bcn[k_bcr] = v_bcs;
   end
end)() == 6);
assert((function ()
   local tab_bch = {};
   for k_bcl, v_bcm in pairs({
      1, 
      2, 
      3, 
      a = 5, 
      b = 6, 
      c = 7}) do
      tab_bch[#tab_bch + 1] = v_bcm;
   end
end)() == "1,2,3,5,7,6");
assert((function ()
   local tab_bcb = {};
   for k_bcf, v_bcg in pairs({
      1, 
      2, 
      3, 
      nil, 
      4, 
      a = 5, 
      b = 6, 
      c = 7}) do
      tab_bcb[#tab_bcb + 1] = v_bcg;
   end
end)() == "1,2,3,4,5,7,6");
assert((function ()
   local built_str_bbw = "";
   for v_chq in next, {5, 6, 7} do
      built_str_bbw = built_str_bbw .. v_chq;
   end
end)() == "123");
assert((function ()
   local built_str_bbq = "";
   for k_bbu, v_bbv in next, {5, 6, 7} do
      built_str_bbq = built_str_bbq .. k_bbu;
   end
end)() == "123");
assert((function ()
   local built_str_bbk = "";
   for k_bbo, v_bbp in next, {5, 6, 7} do
      built_str_bbk = built_str_bbk .. v_bbp;
   end
end)() == "567");
assert((function ()
   local tab_bbg = {};
   for v_cgk in next, {a = 1, b = 2, c = 3} do
      tab_bbg[v_cgk] = 1;
   end
end)() == 3);
assert((function ()
   local tab_bbb = {};
   for k_bbf, v_bbg in next, {a = 1, b = 2, c = 3} do
      tab_bbb[k_bbf] = 1;
   end
end)() == 3);
assert((function ()
   local tab_bav = {};
   for k_baz, v_bba in next, {a = 1, b = 2, c = 3} do
      tab_bav[k_baz] = v_bba;
   end
end)() == 6);
assert((function ()
   local built_str_bal = "";
   local c_v_ceu, c_v_cew = pairs({a = 1, b = 2, c = 3});
   for k_bap, v_baq, value_bar in c_v_cew do
      built_str_bal = built_str_bal .. tostring(value_bar);
   end
end)() == "nilnilnil");
assert((function ()
   local val_baf = 1;
   for v_cei in pairs({1, 2, 3}) do
      val_baf *= 2;
      if (val_baf == 4) then
         return val_baf;
      end
   end
end)() == 4);
assert((function ()
   local val_zz = 1;
   for v_cdw in pairs({1, 2, 3}) do
      val_zz *= 2;
      if (val_zz == 4) then
         return val_zz;
      end
   end
end)() == 4);
assert((function ()
   local val_zv = 1;
   for v_cdo in pairs({1, 2, 3}) do
      val_zv *= 2;
   end
end)() == 8);
function list_iter()
   return (function ()
      u_ccu += 1;
      if (u_ccu >= u_ccw) then
         return;
      end
      return u_ccy[u_ccu];
   end);
end;
assert((function ()
   local built_str_ze = "";
   local c_v_ccg, c_v_cci = list_iter({4, 2, 1});
   for v_cck in c_v_cci do
      built_str_ze = built_str_ze .. v_cck;
   end
end)() == "421");
assert((function ()
   local built_str_yz = "";
   for k_zd, v_ze in ipairs((function ()
      return {5, 6, 7}, 8, 9, 0;
   end)()) do
      built_str_yz = built_str_yz .. v_ze;
   end
end)() == "567");
assert(#({}) == 0);
assert(#({1, 2}) == 2);
assert((function ()
   local c_tab_yv = {1, 2};
   return c_tab_yv[1] + c_tab_yv[2];
end)() == 3);
assert(({data = 4}).data == 4);
assert(({[0] = 4})[3] == 4);
assert((function ()
   local c_tab_ys = {data = 4, [0] = 5};
   return c_tab_ys.data + c_tab_ys[3];
end)() == 9);
assert((function ()
   local c_tab_yp = {1, 2};
   return c_tab_yp[1] + c_tab_yp[2];
end)() == 3);
assert((function ()
   return table.concat({}, ",");
end)() == "");
assert((function ()
   return table.concat({1}, ",");
end)() == "1");
assert((function ()
   return table.concat({1, 2}, ",");
end)() == "1,2");
assert((function ()
   return table.concat({
      1, 
      2, 
      3, 
      4, 
      5, 
      6, 
      7, 
      8, 
      9, 
      10, 
      11, 
      12, 
      13, 
      14, 
      15}, ",");
end)() == "1,2,3,4,5,6,7,8,9,10,11,12,13,14,15");
assert((function ()
   return table.concat({
      1, 
      2, 
      3, 
      4, 
      5, 
      6, 
      7, 
      8, 
      9, 
      10, 
      11, 
      12, 
      13, 
      14, 
      15, 
      16}, ",");
end)() == "1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16");
assert((function ()
   return table.concat({
      1, 
      2, 
      3, 
      4, 
      5, 
      6, 
      7, 
      8, 
      9, 
      10, 
      11, 
      12, 
      13, 
      14, 
      15, 
      16, 
      17}, ",");
end)() == "1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17");
assert((function ()
   local built_str = "";
   for v_cas in pairs({
      Mountains = true, 
      Canyons = true, 
      Dunes = true, 
      Arctic = true, 
      Lavaflow = true, 
      Hills = true, 
      Plains = true, 
      Marsh = true, 
      Water = true}) do
      built_str = built_str .. v_cas;
   end
end)() == "ArcticDunesCanyonsWaterMountainsHillsLavaflowPlainsMarsh");
assert(({data = 4, data = nil, data = 42}).data == 42);
assert(({
   data = 4, 
   data = nil, 
   data = 42, 
   data = nil}).data == nil);
assert((function ()
   u_func = (function ()
      return 2, 3, 4;
   end);
   return "" .. u_func();
end)() == "234");
assert((function ()
   u_func = (function ()
      return 2, 3, 4;
   end);
   return """1" .. u_func();
end)() == "123");
assert((function ()
   u_func = (function ()
      return 2;
   end);
   local c_v_caa, c_value_yc = u_func();
   return """1" .. c_v_caa .. tostring(c_value_yc);
end)() == "12nil");
assert((function ()
   u_func = (function ()
      return 2, 3;
   end);
   local c_v_bzk, c_v_bzm, c_v_bzo = u_func();
   a = 1;
   b = c_v_bzk;
   c = c_v_bzm;
   d = c_v_bzo;
   return "" .. a .. b .. c .. tostring(d);
end)() == "123nil");
assert((function ()
   u_func = (function ()
      return 2, 3;
   end);
   local c_v_byu, c_v_byw, c_value_xq = u_func();
   return """1" .. c_v_byu .. c_v_byw .. tostring(c_value_xq);
end)() == "123nil");
assert((function ()
   u_func = (function (...)
      return (... + ...) + ...;
   end);
   return u_func(1, 2, 3);
end)() == 6);
assert((function ()
   u_func = (function (...)
      return (... + ...) + ...;
   end);
   return u_func(1, 2, 3, 4);
end)() == 9);
assert((function ()
   u_func = (function (...)
      a = ...;
      b = ...;
      c = ...;
      return (a + b) + c;
   end);
   return u_func(1, 2, 3);
end)() == 6);
assert((function ()
   u_func = (function (...)
      a = ...;
      b = ...;
      c = ...;
      return (a + b) + c;
   end);
   return u_func(1, 2, 3, 4);
end)() == 9);
assert((function ()
   u_func = (function (...)
      return tostring(...) .. tostring(...) .. tostring(...);
   end);
   return u_func(1, 2);
end)() == "12nil");
assert((function ()
   u_func = (function (...)
      return ...;
   end);
   return concat(u_func(1, 2, 3));
end)() == "1,2,3");
assert((function ()
   u_func = (function (...)
      return ...;
   end);
   return u_func();
end)() == nil);
assert((function ()
   u_func = (function (...)
      return val_wv + 10, ...;
   end);
   return concat(u_func(1, 2, 3));
end)() == "11,2,3");
assert((function ()
   u_func = (function (...)
      return ...;
   end);
   function bar(...)
      return u_func(...);
   end;
   return concat(bar(1, 2, 3));
end)() == "1,2,3");
assert((function ()
   u_func = (function (...)
      return ...;
   end);
   function bar(...)
      return u_func(...);
   end;
   return bar();
end)() == nil);
assert((function ()
   u_func = (function (...)
      return val_wo + 10, ...;
   end);
   function bar(...)
      return u_func((val_wm * 2), ...);
   end;
   return concat(bar(1, 2, 3));
end)() == "12,2,3");
assert((function ()
   function pack(...)
      if (not v_bwi) then
         return {};
      end
      local c_res_wh = pack(...);
      table.insert(c_res_wh, 1, v_bwi);
      return c_res_wh;
   end;
   u_func = (function (...)
      return pack(...);
   end);
   return #u_func(0, 1, 2);
end)() == 3);
assert((function ()
   u_func = (function (...)
      return {...};
   end);
   return #u_func();
end)() == 0);
assert((function ()
   u_func = (function (...)
      return {...};
   end);
   return #u_func(1, 2, 3);
end)() == 3);
assert((function ()
   u_func = (function ()
      return 1, 2, 3;
   end);
   return #({u_func()});
end)() == 3);
assert((function ()
   u_func = (function ()
      return 1, 2, 3;
   end);
   return table.concat({u_func()}, ",");
end)() == "1,2,3");
assert((function ()
   u_func = (function ()
      return 1, 2, 3;
   end);
   return table.concat({
      1, 
      2, 
      3, 
      4, 
      5, 
      6, 
      7, 
      8, 
      9, 
      10, 
      11, 
      12, 
      13, 
      14, 
      u_func()}, ",");
end)() == "1,2,3,4,5,6,7,8,9,10,11,12,13,14,1,2,3");
assert((function ()
   u_func = (function ()
      return 1, 2, 3;
   end);
   return table.concat({
      1, 
      2, 
      3, 
      4, 
      5, 
      6, 
      7, 
      8, 
      9, 
      10, 
      11, 
      12, 
      13, 
      14, 
      15, 
      u_func()}, ",");
end)() == "1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,1,2,3");
assert((function ()
   u_func = (function ()
      return 1, 2, 3;
   end);
   return table.concat({
      1, 
      2, 
      3, 
      4, 
      5, 
      6, 
      7, 
      8, 
      9, 
      10, 
      11, 
      12, 
      13, 
      14, 
      15, 
      16, 
      u_func()}, ",");
end)() == "1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,1,2,3");
assert((function ()
   u_func = (function ()
      return 1, 2, 3;
   end);
   return table.concat({
      1, 
      2, 
      3, 
      4, 
      5, 
      6, 
      7, 
      8, 
      9, 
      10, 
      11, 
      12, 
      13, 
      14, 
      15, 
      16, 
      17, 
      u_func()}, ",");
end)() == "1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,1,2,3");
assert(({6, 9, 7})[2] == 9);
assert(({6, 9, 7})[0] == nil);
assert(({6, 9, 7})[4] == nil);
assert(({6, 9, 7})[4.5] == nil);
assert(({
   6, 
   9, 
   7, 
   [4.5] = 11})[4.5] == 11);
assert(({
   6, 
   9, 
   7, 
   a = 11}).a == 11);
assert((function ()
   local c_tab_vj = {6, 9, 7};
   setmetatable(c_tab_vj, {__index = (function ()
      return val_vo * 10;
   end)});
   return concat(c_tab_vj[2], c_tab_vj[5]);
end)() == "9,50");
assert(({
   6, 
   9, 
   7, 
   [2] = 10})[2] == 10);
assert(({
   6, 
   9, 
   7, 
   [0] = 5})[0] == 5);
assert(({
   6, 
   9, 
   7, 
   10})[4] == 10);
assert(({
   6, 
   9, 
   7, 
   [4.5] = 10})[4.5] == 10);
assert(({
   6, 
   9, 
   7, 
   a = 11}).a == 11);
assert((function ()
   local tab_uz = {6, 9, 7};
   setmetatable(tab_uz, {__newindex = (function ()
      rawset(v_bui, val_vh * 10, v_bum);
   end)});
   tab_uz[1] = 17;
   tab_uz[5] = 1;
   return concat(tab_uz[1], tab_uz[5], tab_uz[50]);
end)() == "17,nil,1");
assert((function ()
   local c_res_uv = newproxy(true);
   getmetatable(c_res_uv).__index = (function ()
      return val_uz * 10;
   end);
   return c_res_uv[2];
end)() == 20);
assert((function ()
   local c_res_ur = newproxy(true);
   getmetatable(c_res_ur).__index = (function ()
      return (function ()
         return val_uv * 10;
      end);
   end);
   return c_res_ur:meow(2);
end)() == 20);
assert(true);
assert((if not (nil) then nil else 2) == nil);
assert(true);
assert((if (nil) then nil else 2) == 2);
assert(true);
assert(true);
assert(true);
assert(true);
assert((function ()
   b = 2;
   return b;
end)() == 2);
assert((function ()
   b = 2;
   return if not (nil) then nil else b;
end)() == nil);
assert((function ()
   b = 2;
   return 1;
end)() == 1);
assert((function ()
   b = 2;
   return if (nil) then nil else b;
end)() == 2);
assert((function ()
   local u_tab_bek = {};
   u_tab_bek.__index = u_tab_bek;
   u_tab_bek.new = (function ()
      local tab_um = {};
      setmetatable(tab_um, u_tab_bek);
      tab_um.field = 5;
      return tab_um;
   end);
   u_tab_bek.GetField = (function ()
      return tab_ul.field;
   end);
   return u_tab_bek.new():GetField();
end)() == 5);
assert((function ()
   local c_tab_ty = {5};
   local u_tab_bef = {6};
   setmetatable(c_tab_ty, {__index = (function ()
      return u_tab_bef[1];
   end)});
   return c_tab_ty.hi;
end)() == 6);
assert((function ()
   local c_tab_tu = {9, [1.5] = 7};
   return c_tab_tu[1], c_tab_tu[2], c_tab_tu[1.5];
end)() == 9, nil, 7);
assert((function ()
   local c_tab_tp = {9, [1.5] = 7};
   setmetatable(c_tab_tp, {__index = (function ()
      return 5;
   end)});
   return concat(c_tab_tp[1], c_tab_tp[2], c_tab_tp[1.5]);
end)() == "9,5,7");
assert((function ()
   local c_tab_tj = {9, nil, 11};
   setmetatable(c_tab_tj, {__index = (function ()
      return 5;
   end)});
   return concat(c_tab_tj[1], c_tab_tj[2], c_tab_tj[3], c_tab_tj[4]);
end)() == "9,5,11,5");
assert((function ()
   local c_res_tf = newproxy(true);
   getmetatable(c_res_tf).__namecall = (function ()
      return val_tj + 42;
   end);
   return c_res_tf:Foo(10);
end)() == 52);
assert((function ()
   local c_res_sy = newproxy(true);
   local c_tab_sz = {};
   setmetatable(c_tab_sz, {__call = (function ()
      return val_tg + 42;
   end)});
   getmetatable(c_res_sy).__namecall = c_tab_sz;
   return c_res_sy:Foo(10);
end)() == 52);
assert((function ()
   local u_tab = {};
   u_tab.__index = u_tab;
   u_tab.new = (function ()
      local c_tab_sw = {value = v_bpk};
      setmetatable(c_tab_sw, u_tab);
      return c_tab_sw;
   end);
   u_tab.get = (function ()
      return tab_ss.value;
   end);
   u_tab.set = (function ()
      tab_sq.value = v_bpe;
   end);
   local c_u_tab_new = u_tab:new(32);
   c_u_tab_new:set(42);
   return c_u_tab_new:get();
end)() == 42);
assert((function ()
   a = nil;
   return concat((a == nil), (a ~= nil));
end)() == "true,false");
assert((function ()
   a = nil;
   return concat((a == 1), (a ~= 1));
end)() == "false,true");
assert((function ()
   a = 1;
   return concat((a == 1), (a ~= 1));
end)() == "true,false");
assert((function ()
   a = 1;
   return concat((a == 2), (a ~= 2));
end)() == "false,true");
assert((function ()
   a = true;
   return concat((a == true), (a == false));
end)() == "true,false");
assert((function ()
   a = true;
   return concat((a == false), (a == true));
end)() == "false,true");
assert((function ()
   a = "a";
   return concat((a == "a"), (a ~= "a"));
end)() == "true,false");
assert((function ()
   a = "a";
   return concat((a == "b"), (a ~= "b"));
end)() == "false,true");
assert((function ()
   a = {};
   return concat(true, false);
end)() == "true,false");
assert((function ()
   a = {};
   b = {};
   return concat((a == b), (a ~= b));
end)() == "false,true");
assert((function ()
   a = {};
   setmetatable(a, {});
   return concat(true, false);
end)() == "true,false");
assert((function ()
   a = {};
   b = {};
   mt = {};
   setmetatable(a, mt);
   setmetatable(b, mt);
   return concat((a == b), (a ~= b));
end)() == "false,true");
assert((function ()
   a = {};
   b = {};
   mt = {__eq = (function ()
      return #v_boc == #v_boe;
   end)};
   setmetatable(a, mt);
   setmetatable(b, mt);
   return concat((a == b), (a ~= b));
end)() == "true,false");
assert((function ()
   a = {};
   b = {};
   function eq()
      return #v_bny == #v_boa;
   end;
   setmetatable(a, {__eq = eq});
   setmetatable(b, {__eq = eq});
   return concat((a == b), (a ~= b));
end)() == "true,false");
assert((function ()
   a = {};
   b = {};
   setmetatable(a, {__eq = (function ()
      return #v_bnu == #v_bnw;
   end)});
   setmetatable(b, {__eq = (function ()
      return #v_bnq == #v_bns;
   end)});
   return concat((a == b), (a ~= b));
end)() == "false,true");
assert((function ()
   a = newproxy();
   return concat((a == newproxy()), (a ~= newproxy()));
end)() == "false,true");
assert((function ()
   a = newproxy(true);
   return concat((a == newproxy(true)), (a ~= newproxy(true)));
end)() == "false,true");
assert(rawequal(true, 5) == false);
assert(rawequal(nil, nil) == true);
assert(rawequal(true, false) == false);
assert(rawequal(true, true) == true);
assert(rawequal(0, -0) == true);
assert(rawequal(1, 2) == false);
assert(rawequal("a", "a") == true);
assert(rawequal("a", "b") == false);
assert((function ()
   a = {};
   b = {};
   mt = {__eq = (function ()
      return #v_bnm == #v_bno;
   end)};
   setmetatable(a, mt);
   setmetatable(b, mt);
   return concat((a == b), rawequal(a, b));
end)() == "true,false");
assert(concat(pcall(rawequal, "a", "a")) == "true,true");
assert(concat(pcall(rawequal, "a", "b")) == "true,false");
assert(concat(pcall(rawequal, "a", nil)) == "true,false");
local u_glb = assert;
u_glb(pcall(rawequal, "a") == false);
u_glb = (function ()
   return setmetatable({x = v_bhm, y = v_bho, z = v_bhq}, {
      __add = (function ()
         return u_glb((tab_ro.x + tab_rp.x), (tab_ro.y + tab_rp.y), (tab_ro.z + tab_rp.z));
      end), 
      __sub = (function ()
         return u_glb((tab_rh.x - tab_ri.x), (tab_rh.y - tab_ri.y), (tab_rh.z - tab_ri.z));
      end), 
      __mul = (function ()
         if (type(value_qq) == "number") then
            local c_u_glb_qr = u_glb((tab_qp.x * value_qq), (tab_qp.y * value_qq), (tab_qp.z * value_qq));
            if (c_u_glb_qr) then
               return c_u_glb_qr;
            end
         end
         return u_glb((tab_qp.x * value_qq.x), (tab_qp.y * value_qq.y), (tab_qp.z * value_qq.z));
      end), 
      __div = (function ()
         if (type(value_py) == "number") then
            local c_u_glb_pz = u_glb((tab_px.x / value_py), (tab_px.y / value_py), (tab_px.z / value_py));
            if (c_u_glb_pz) then
               return c_u_glb_pz;
            end
         end
         return u_glb((tab_px.x / value_py.x), (tab_px.y / value_py.y), (tab_px.z / value_py.z));
      end), 
      __idiv = (function ()
         if (type(value) == "number") then
            local c_u_glb_ph = u_glb((tab_pf.x // value), (tab_pf.y // value), (tab_pf.z // value));
            if (c_u_glb_ph) then
               return c_u_glb_ph;
            end
         end
         return u_glb((tab_pf.x // value.x), (tab_pf.y // value.y), (tab_pf.z // value.z));
      end), 
      __unm = (function ()
         return u_glb(-tab_pb.x, -tab_pb.y, -tab_pb.z);
      end), 
      __tostring = (function ()
         return string.format("%g, %g, %g", tab_oy.x, tab_oy.y, tab_oy.z);
      end)});
end);
assert((function ()
   return tostring((u_glb(1, 2, 3) + u_glb(4, 5, 6)));
end)() == "5, 7, 9");
assert((function ()
   return tostring((u_glb(1, 2, 3) - u_glb(4, 5, 6)));
end)() == "-3, -3, -3");
assert((function ()
   return tostring((u_glb(1, 2, 3) * u_glb(4, 5, 6)));
end)() == "4, 10, 18");
assert((function ()
   return tostring((u_glb(1, 2, 3) / u_glb(2, 4, 8)));
end)() == "0.5, 0.5, 0.375");
assert((function ()
   return tostring((u_glb(1, 2, 3) // u_glb(2, 4, 2)));
end)() == "0, 0, 1");
assert((function ()
   return tostring((u_glb(1, 2, 3) // u_glb(-2, -4, -2)));
end)() == "-1, -1, -2");
assert((function ()
   return tostring((u_glb(1, 2, 3) * 2));
end)() == "2, 4, 6");
assert((function ()
   return tostring((u_glb(1, 2, 3) / 2));
end)() == "0.5, 1, 1.5");
assert((function ()
   return tostring((u_glb(1, 2, 3) // 2));
end)() == "0, 1, 1");
assert((function ()
   return tostring(-u_glb(1, 2, 3));
end)() == "-1, -2, -3");
assert((function ()
   function cmp()
      return v_bfq < v_bfs, v_bfq <= v_bfs, v_bfs < v_bfq, v_bfs <= v_bfq;
   end;
   return concat(cmp("a", "b"));
end)() == "true,true,false,false");
assert((function ()
   function cmp()
      return v_bfa < v_bfc, v_bfa <= v_bfc, v_bfc < v_bfa, v_bfc <= v_bfa;
   end;
   return concat(cmp("a", "a"));
end)() == "false,true,false,true");
assert((function ()
   function cmp()
      return v_bek < v_bem, v_bek <= v_bem, v_bem < v_bek, v_bem <= v_bek;
   end;
   return concat(cmp("a", ""));
end)() == "false,false,true,true");
assert((function ()
   function cmp()
      return v_bdu < v_bdw, v_bdu <= v_bdw, v_bdw < v_bdu, v_bdw <= v_bdu;
   end;
   return concat(cmp("", "\\0"));
end)() == "true,true,false,false");
assert((function ()
   function cmp()
      return v_bde < v_bdg, v_bde <= v_bdg, v_bdg < v_bde, v_bdg <= v_bde;
   end;
   return concat(cmp("abc", "abd"));
end)() == "true,true,false,false");
assert((function ()
   function cmp()
      return v_bco < v_bcq, v_bco <= v_bcq, v_bcq < v_bco, v_bcq <= v_bco;
   end;
   return concat(cmp("ab\\0c", "ab\\0d"));
end)() == "true,true,false,false");
assert((function ()
   function cmp()
      return v_bby < v_bca, v_bby <= v_bca, v_bca < v_bby, v_bca <= v_bby;
   end;
   return concat(cmp("ab\\0c", "ab\\0"));
end)() == "false,false,true,true");
assert((function ()
   function cmp()
      return v_bbi < v_bbk, v_bbi <= v_bbk, v_bbk < v_bbi, v_bbk <= v_bbi;
   end;
   return concat(cmp("\\0a", "\\0b"));
end)() == "true,true,false,false");
assert((function ()
   function cmp()
      return v_bas < v_bau, v_bas <= v_bau, v_bau < v_bas, v_bau <= v_bas;
   end;
   return concat(cmp("a", "a\\0"));
end)() == "true,true,false,false");
assert((function ()
   function cmp()
      return v_bac < v_bae, v_bac <= v_bae, v_bae < v_bac, v_bae <= v_bac;
   end;
   return concat(cmp("a", "\xC8"));
end)() == "true,true,false,false");
assert(({4, 5, 6})[3] == 6);
assert(({
   4, 
   5, 
   nil, 
   6})[3] == nil);
assert((function ()
   local c_tab_la = {
      4, 
      5, 
      nil, 
      6};
   setmetatable(c_tab_la, {__index = (function ()
      return 42;
   end)});
   return c_tab_la[4];
end)() == 6);
assert((function ()
   local c_tab_kx = {
      4, 
      5, 
      nil, 
      6};
   setmetatable(c_tab_kx, {__index = (function ()
      return 42;
   end)});
   return c_tab_kx[3];
end)() == 42);
assert(({
   4, 
   5, 
   6, 
   [3] = 8})[3] == 8);
assert(({
   4, 
   5, 
   nil, 
   6, 
   [3] = 8})[3] == 8);
assert((function ()
   local tab_kr = {
      4, 
      5, 
      nil, 
      6};
   setmetatable(tab_kr, {__newindex = (function ()
      rawset(v_zm, v_zo, 42);
   end)});
   tab_kr[4] = 0;
   return tab_kr[4];
end)() == 0);
assert((function ()
   local tab_kl = {
      4, 
      5, 
      nil, 
      6};
   setmetatable(tab_kl, {__newindex = (function ()
      rawset(v_za, v_zc, 42);
   end)});
   tab_kl[3] = 0;
   return tab_kl[3];
end)() == 42);
assert((function ()
   local c_tab_kg = {
      4, 
      5, 
      nil, 
      6};
   return concat(c_tab_kg[1], c_tab_kg[3], c_tab_kg[4], c_tab_kg[100]);
end)() == "4,nil,6,nil");
assert((function ()
   local c_tab_kb = {
      4, 
      5, 
      nil, 
      6, 
      [1] = 42, 
      [3] = 0, 
      [100] = 75};
   return concat(c_tab_kb[1], c_tab_kb[3], c_tab_kb[75], c_tab_kb[100]);
end)() == "42,0,nil,75");
assert((function ()
   return concat(loadstring("hello world"));
end)() == "nil,[string \"hello world\"]:1: Incomplete statement: expected assignment or a function call");
function f()
end;
assert(f() == nil);
assert((function ()
   local tab_jv = {};
   for c_i_ue = 1, 5 do
      tab_jv[#tab_jv + 1] = (function ()
         return c_i_ue;
      end);
   end
end)() == 15);
assert((function ()
   local tab_jp = {};
   for u_xc in ipairs({
      1, 
      2, 
      3, 
      4, 
      5}) do
      tab_jp[#tab_jp + 1] = (function ()
         return u_xc;
      end);
   end
end)() == 15);
assert((function ()
   local tab_iz = {};
   local val_ja = 0;
   while (val_ja < 5) do
      tab_iz[#tab_iz + 1] = (function ()
         return u_val_tk;
      end);
      val_ja += 1;
   end
   local u_val_tk = 0;
   for k_jf, v_jg in pairs(tab_iz) do
      u_val_tk += v_jg();
   end
end)() == 15);
assert((function ()
   local tab_ij = {};
   local val_ik = 0;
   repeat
      tab_ij[#tab_ij + 1] = (function ()
         return u_val_sv;
      end);
      val_ik += 1;
   until (val_ik > 5);
   local u_val_sv = 0;
   for k_ip, v_iq in pairs(tab_ij) do
      u_val_sv += v_iq();
   end
end)() == 15);
assert((function ()
   local tab_hv = {};
   for c_i_si = 1, 10 do
      tab_hv[#tab_hv + 1] = (function ()
         return c_i_si;
      end);
      if (c_i_si == 5) then
         break;
      end
   end
   local val_hw = 0;
   for k_ia, v_ib in pairs(tab_hv) do
      val_hw += v_ib();
   end
end)() == 15);
assert((function ()
   local tab_hh = {};
   for u_sm in ipairs({
      1, 
      2, 
      3, 
      4, 
      5, 
      6, 
      7, 
      8, 
      9, 
      10}) do
      tab_hh[#tab_hh + 1] = (function ()
         return u_sm;
      end);
      if (u_sm == 5) then
         break;
      end
   end
   local val_hi = 0;
   for k_hm, v_hn in pairs(tab_hh) do
      val_hi += v_hn();
   end
end)() == 15);
assert((function ()
   local tab_gq = {};
   local val_gr = 0;
   while (val_gr < 10) do
      tab_gq[#tab_gq + 1] = (function ()
         return u_val_rf;
      end);
      if (val_gr == 5) then
         break;
      end
      val_gr += 1;
   end
   local u_val_rf = 0;
   for k_gw, v_gx in pairs(tab_gq) do
      u_val_rf += v_gx();
   end
end)() == 15);
assert((function ()
   local tab_fz = {};
   local val_ga = 0;
   repeat
      tab_fz[#tab_fz + 1] = (function ()
         return u_val_qp;
      end);
      if (val_ga == 5) then
         break;
      end
      val_ga += 1;
   until (val_ga > 10);
   local u_val_qp = 0;
   for k_gf, v_gg in pairs(tab_fz) do
      u_val_qp += v_gg();
   end
end)() == 15);
assert((function ()
   local val_fu = 0;
   for k_fy, v_fz in ipairs({1, [42] = 42, x = 10}) do
      val_fu += v_fz;
   end
end)() == 1);
assert((function ()
   for c_i_fw = 0, v_pe do
   end
end)(100) == "v0,v100");
assert(idontexist == nil);
assert(math.idontexist == nil);
assert(pcall((function ()
   return idontexist.a;
end)) == false);
assert(pcall((function ()
   return math.pow.a;
end)) == false);
assert(pcall((function ()
   return math.a.b;
end)) == false);
local c_res = tostring((math.abs(0) / math.abs(0)));
assert(tostring(0) == c_res);
assert(tostring(1) == c_res);
assert(tostring(0) == "0");
assert(tostring(-0) == "-0");
assert((function ()
   return concat("", "\n", "foo\nbar", "foo\nbar\n");
end)() == ",\n,foo\nbar,foo\nbar\n");
assert((function ()
   return math.abs(-5);
end)() == 5);
assert((function ()
   return math.abs(-5);
end)() == 5);
assert((function ()
   u_func = (function ()
      return u_oy(-5);
   end);
   return u_func();
end)() == 5);
assert((function ()
   u_func = (function (...)
      return math.abs(...);
   end);
   return u_func(-5);
end)() == 5);
assert((function ()
   u_func = (function (...)
      return math.abs(...);
   end);
   return u_func(-5);
end)() == 5);
assert((function ()
   u_func = (function (...)
      return u_oi(...);
   end);
   return u_func(-5);
end)() == 5);
function testgetfenv()
   u_val_pa();
   local u_val_pa = -5;
   assert((function ()
      return math.abs(u_val_pa);
   end)() == 5);
   assert((function ()
      return math.abs(u_val_pa);
   end)() == 5);
   assert((function ()
      u_func = (function ()
         return u_nu(u_val_pa);
      end);
      return u_func();
   end)() == 5);
   getfenv().math = {abs = (function ()
      return val_ew * val_ew;
   end)};
   assert((function ()
      return math.abs(u_val_pa);
   end)() == 25);
   assert((function ()
      return math.abs(u_val_pa);
   end)() == 25);
   assert((function ()
      u_func = (function ()
         return u_nc(u_val_pa);
      end);
      return u_func();
   end)() == 25);
end;
assert((function ()
   return math.abs("-5");
end)() == 5);
assert((function ()
   return math.abs("-5");
end)() == 5);
assert((function ()
   u_func = (function ()
      return u_me("-5");
   end);
   return u_func();
end)() == 5);
assert(concat(pcall((function ()
   return math.abs();
end))):match("missing argument #1 to \'abs\'"));
assert(concat(pcall((function ()
   return math.abs(nil);
end))):match("invalid argument #1 to \'abs\'"));
assert(concat(pcall((function ()
   return math.abs({});
end))):match("invalid argument #1 to \'abs\'"));
assert(select("#", table.unpack({
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1, 
   1})) == 263);
assert((function ()
   local val_dy = 1;
   for c_i_eb = 1, 8 do
      val_dy = (val_dy * 2) and ((val_dy + 1) > 5);
   end
end)() == 190);
assert((function ()
   local val_dq = 1;
   while (true) do
      if (val_dq > 100) then
         return val_dq;
      end
      val_dq += 1;
      if (val_dq < 5) then
         continue;
      end
      val_dq *= 2;
   end
end)() == 190);
assert((function ()
   local val_dk = 1;
   while (true) do
      val_dk = (val_dk * 2) and ((val_dk + 1) > 5);
      if (val_dk > 100) then
         return val_dk;
      end
   end
end)() == 190);
assert((function ()
   local tab_da = {};
   for c_i_dd = 1, 10 do
      tab_da[#tab_da + 1] = (function ()
         return u_cmp;
      end);
      local u_cmp = if (c_i_dd ~= 5) then (c_i_dd * 2) else u_cmp;
   end
end)() == 105);
assert((function ()
   local tab_cq = {};
   for val_nm in ipairs({
      1, 
      2, 
      3, 
      4, 
      5, 
      6, 
      7, 
      8, 
      9, 
      10}) do
      tab_cq[#tab_cq + 1] = (function ()
         return val_nm;
      end);
      val_nm = if (val_nm ~= 5) then (val_nm * 2) else val_nm;
   end
end)() == 105);
assert((function ()
   local tab_by = {};
   local val_bz = 1;
   while (val_bz < 10) do
      tab_by[#tab_by + 1] = (function ()
         return val_mv;
      end);
      if (val_bz ~= 5) then
         val_bz += 1;
         continue;
      end
      val_bz += 1;
   end
   for k_ce, v_cf in pairs(tab_by) do
      val_mv += v_cf();
   end
end)() == 105);
assert((function ()
   local tab_bj = {};
   local val_bk = 1;
   repeat
      tab_bj[#tab_bj + 1] = (function ()
         return val_mh;
      end);
      val_bk += 1;
   until (val_bk > 10);
   for k, v_bq in pairs(tab_bj) do
      val_mh += v_bq();
   end
end)() == 105);
assert((function ()
   for c_i_bk = 1, 90 do
      table.create(100, 42)[c_i_bk] = nil;
   end
end)() == 462);
assert((function ()
   return (function ()
      return (val_bd < 1) or (val_bd * u((val_bd - 1)));
   end)(5);
end)() == 120);
assert((function ()
   b = 2;
   local tab_w = {value = 3};
   local tab_x = {4};
   tab_w.value = tab_w.value * 3;
   tab_x[1] = tab_x[1] / b;
   return concat(0, b, tab_w.value, tab_x[1], 0, 0);
end)() == "6,-4,9,-1,1,16");
assert(false);
assert((function ()
   local tab = {1, 2, 3};
   local u_val = 0;
   local res_g = (function ()
      u_val += 1;
      return u_val;
   end)();
   tab[res_g] = tab[res_g] + 5;
   res_g = (function ()
      u_val += 1;
      return u_val;
   end)();
   tab[res_g] = tab[res_g] + 6;
   res_g = (function ()
      u_val += 1;
      return u_val;
   end)();
   tab[res_g] = tab[res_g] + 7;
   return table.concat(tab, ",");
end)() == "6,8,10");
assert((function ()
   local val = 0;
   if (not v) then
      return 98304;
   end
   for c_i = 1, 100 do
      val += c_i;
   end
end)(true) == 5050);
assert(pcall(typeof) == false);
assert(pcall(type) == false);
function nothing()
end;
assert(pcall((function ()
   return typeof(nothing());
end)) == false);
assert(pcall((function ()
   return type(nothing());
end)) == false);
assert(concat(typeof(5), typeof(nil), typeof({}), typeof(newproxy())) == "number,nil,table,userdata");
assert((function ()
   local c_res_a = newproxy(true);
   getmetatable(c_res_a).__type = "number";
   return concat(type(c_res_a), typeof(c_res_a));
end)() == "userdata,userdata");
testgetfenv();
return "OK";
