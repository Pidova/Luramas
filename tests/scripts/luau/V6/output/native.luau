print("testing native code generation");
assert((function ()
   return val_sy * 10, (val_sy * 10) + 1, {}, val_sy + 2, val_sy - 7;
end)(5, 10) == 50);
assert((function ()
   return math.abs(val_sw) * val_sw;
end)("42") == 1764);
assert(pcall((function ()
   local res_sq_sp = nil;
   while (true) do
      local c_res_sq = typeof(res_sq_sp);
      res_sq_sp = c_res_sq(c_res_sq._);
      if (res_sq_sp) then
         return;
      end
   end
end)) == false);
assert(pcall((function ()
   function _(...)
      _({_, _, true}, {...}, _, not _);
   end;
   _();
end)) == false);
assert(pcall((function ()
   local c_res_sm = setmetatable({}, setmetatable({_ = _}, _));
   return c_res_sm(c_res_sm:_());
end)) == false);
assert(pcall((function ()
   local c_idx_se = bit32.band;
   c_idx_se(c_idx_se(c_idx_se, 0), c_idx_se);
   c_idx_se(c_idx_se, c_idx_se);
end)) == false);
assert(pcall((function ()
   return bit32.extract(v_bkt, 671088640, v_bkt);
end), 1) == false);
assert(pcall((function ()
   return bit32.extract(v_bkp, v_bkp, 671088640);
end), 1) == false);
assert(pcall((function (...)
   local tab_rm = _;
   tab_rm.n0 = nil;
   tab_rm._ = nil;
   tab_rm[...] = nil;
   n0 = nil;
   l0 = nil;
   tab_rm = (function ()
   end);
   tab_rm._ = nil;
   tab_rm[...] = nil;
   n0.l0 = nil;
   tab_rm = nil;
   local tab_rm_ro = tab_rm();
   tab_rm[...] = tab_rm();
   tab_rm_ro[tab_rm] = ...;
end)) == false);
assert(pcall((function ()
   local c_idx = bit32.bor;
   local c_idx_qs = c_idx(c_idx(c_idx, c_idx), c_idx(c_idx, c_idx), c_idx(-16834560, c_idx), c_idx(c_idx(-c_idx, -2130706432)), -c_idx);
   local c_idx_qt = c_idx(c_idx(c_idx, c_idx), c_idx(-16834560, -2130706432));
end)) == false);
assert(pcall((function ()
   local unary_qm = not false;
   local c_glb_qn = l0;
   l0 = not unary_qm;
   unary_qm[c_glb_qn] = nil;
end)) == false);
assert((function (...)
   return bit32.arshift(bit32.bnot(v_bhl), ...);
end)(4294901760, 8) == 255);
assert(pcall((function ()
   local c_unary_py = not _;
   local c_unary_pz = not _;
   local c_unary_qa = not _;
   local c_unary_qb = not _;
   local c_unary_qc = not _;
   local c_unary_qd = not _;
   local c_glb_qf = _;
   _ = not _;
   _ = c_unary_py;
   _ = c_unary_pz;
   _ = c_unary_qa;
   _ = c_unary_qb;
   _ = c_unary_qc;
   _ = c_unary_qd;
   _ = not c_glb_qf;
end)) == true);
assert(pcall((function ()
   local c_unary = not _;
   local c_unary_ov = not _;
   local c_unary_ow = not _;
   local c_unary_ox = not _;
   local c_unary_oy = not _;
   local c_unary_oz = not _;
   local c_unary_pa = not _;
   local c_unary_pb = not _;
   local c_unary_pc = not _;
   local c_unary_pd = not _;
   local c_unary_pe = not _;
   local c_unary_pf = not _;
   local c_unary_pg = not _;
   local c_unary_ph = not _;
   local c_glb_pj = _;
   _ = not _;
   _ = c_unary;
   _ = c_unary_ov;
   _ = c_unary_ow;
   _ = c_unary_ox;
   _ = c_unary_oy;
   _ = c_unary_oz;
   _ = c_unary_pa;
   _ = c_unary_pb;
   _ = c_unary_pc;
   _ = c_unary_pd;
   _ = c_unary_pe;
   _ = c_unary_pf;
   _ = c_unary_pg;
   _ = c_unary_ph;
   _ = not c_glb_pj;
end)) == true);
assert(pcall((function ()
   for c_i_ot = 771751936, _ do
      for c_i_ow = 771751936, 0 do
         while (true) do
         end
      end
   end
end)) == false);
assert(pcall((function ()
   if (nil) then
      while (true) do
         if (nil) then
            return;
         end
      end
   end
   local c_format = ("%*"):format(nil);
end)) == true);
assert(pcall((function ()
   _ = {[{[2] = 77, _ = _, [2] = _}] = not _};
   _ = {
      77, 
      11008, 
      [2] = _, 
      [0] = _};
end)) == true);
assert(pcall((function ()
   return bit32.extract(1293942816, 1293942816);
end)) == false);
local function c_func ()
   return bit32.extract(7890276, 0);
end;
assert(pcall(c_func) == true);
assert(c_func() == 0);
assert(pcall((function ()
   local c_val_oc = 0;
   c_tab_oe[1] = true;
   c_tab_oe[2] = true;
   c_tab_oe[3] = c_val_oc();
   local c_val_od = 2;
   local c_tab_oe = assert({n0 = c_val_od, c_val_od, n0 = c_val_od});
   local c_tab_of = {_ = {c_val_od[c_val_od()]}, [1] = c_val_od};
end)) == false);
assert(pcall((function ()
   assert(true);
   assert(false, _, true);
   _ = nil;
end)) == false);
assert(pcall((function (...)
   local c_glb = assert;
   if (not c_glb) then
      return c_glb / c_glb;
   end
   c_glb(c_glb);
   c_glb(c_glb, c_glb);
   assert(..., c_glb);
   c_glb(not c_glb, c_glb);
   c_glb(true, c_glb / c_glb);
   c_glb(c_glb, c_glb());
   return c_glb;
end)) == false);
assert(pcall((function ()
   local c_tab_ne = {false};
   if (not c_tab_ne) then
      return "\"\"";
   end
   tab_ng[1] = unpack(0, c_tab_ne);
   true.n126 = nil;
   return false;
end)) == false);
assert(pcall((function ()
   local c_tab_na = {false};
   if (not c_tab_na) then
      return;
   end
   tab_nc[1] = unpack(c_tab_na);
end)) == false);
assert((function ()
   local c_tab_mx = {
      1, 
      2, 
      nil, 
      nil, 
      nil, 
      nil, 
      nil, 
      nil, 
      nil, 
      true};
   table.insert(c_tab_mx, 3);
   return c_tab_mx[10];
end)() == true);
assert((function ()
   local c_tab_mu = {
      1, 
      2, 
      nil, 
      nil, 
      nil, 
      nil, 
      nil, 
      nil, 
      nil, 
      true};
   table.insert(({a = c_tab_mu}).a, 3);
   return c_tab_mu[10];
end)() == true);
(function ()
   local c_tab_ml, tab_mm = (function ()
      local c_tab_mq = {x = 1, y = 2, z = 3};
      setmetatable(c_tab_mq, {__index = (function ()
         return 42;
      end)});
      return c_tab_mq, c_tab_mq;
   end)();
   for c_i_mp = 1, 2 do
      tab_mm.x = nil;
      tab_mm.x = 1;
      assert(c_tab_ml.x == 1);
   end
end)();
assert((function ()
   tab_lw[1] = tab_lw[1] + 2;
   tab_lw[1] = tab_lw[1] * 3;
   table.insert(tab_lw, 3);
   table.insert(tab_lw, 4);
   table.insert(tab_lw, 5);
   table.insert(tab_lw, 6);
   tab_lw[1] = tab_lw[1] + 4;
   tab_lw[1] = tab_lw[1] * 5;
   return tab_lw[1] + tab_lw[5];
end)({1}) == 71);
assert((function ()
   tab_kz[v_wp] = tab_kz[v_wp] + 2;
   tab_kz[v_wp] = tab_kz[v_wp] * 3;
   table.insert(tab_kz, 3);
   table.insert(tab_kz, 4);
   table.insert(tab_kz, 5);
   table.insert(tab_kz, 6);
   tab_kz[v_wp] = tab_kz[v_wp] + 4;
   tab_kz[v_wp] = tab_kz[v_wp] * 5;
   return tab_kz[v_wp] + tab_kz[5];
end)({1}, 1) == 71);
function deadLoopBody()
   local val_ku = 0;
   if (v_wd or true) then
      return 0;
   end
   for c_i_kx = 1, v_wd do
      val_ku += 1;
   end
end;
assert(deadLoopBody(5) == 0);
function arrayIndexingSpecialNumbers1()
   local res_ka = table.create(100000);
   res_ka[v_un] = 9;
   res_ka[val_jy - 1] = 80;
   res_ka[val_jy] = 700;
   res_ka[val_jy + 1] = 6000;
   res_ka[val_jz - 1] = 50000;
   res_ka[val_jz] = 400000;
   res_ka[val_jz + 1] = 3000000;
   return (((((res_ka[1] + res_ka[255]) + res_ka[256]) + res_ka[257]) + res_ka[65535]) + res_ka[65536]) + res_ka[65537];
end;
assert(arrayIndexingSpecialNumbers1(1, 256, 65536) == 3456789);
function loopIteratorProtocol()
   local val_jq = 0;
   for k, v_jv in ipairs(v_tx) do
      val_jq = (if (k == 10) then (val_jq + math.abs("-8")) else val_jq) + k;
   end
end;
assert(loopIteratorProtocol(0, table.create(100, 5)) == 5058);
function valueTrackingIssue1()
   local u_res = buffer.create(u_idx);
   local u_idx = buffer.writeu8;
   u_idx(u_res, 0, 0);
   (function ()
      assert(type(u_res) == "buffer");
      u_idx = nil;
      for c_i_jl = 1, 100 do
         print(("%* is %*"):format(u_res, u_res));
      end
   end)();
end;
valueTrackingIssue1();
assert((function ()
   return (tab.X + tab.Y) + tab.Z;
end)(vector(1, 2, 4)) == 7);
assert((function ()
   return val_ix + val_iy;
end)(vector(10, 20, 40), vector(1, 0, 2)) == vector(11, 20, 42));
assert((function ()
   return val_iv - val_iw;
end)(vector(10, 20, 40), vector(1, 0, 2)) == vector(9, 20, 38));
assert((function ()
   return val_it * val_iu;
end)(vector(10, 20, 40), vector(1, 0, 2)) == vector(10, 0, 80));
assert((function ()
   return val_ir / val_is;
end)(vector(10, 20, 40), vector(1, 0, 2)) == vector(10, math.huge, 20));
assert((function ()
   return -v_rv;
end)(vector(10, 20, 40)) == vector(-10, -20, -40));
assert((function ()
   return val_io * val_ip;
end)(vector(10, 20, 40), 4) == vector(40, 80, 160));
assert((function ()
   return val_in * 4;
end)(vector(10, 20, 40), 4) == vector(40, 80, 160));
(function ()
   local c_res = buffer.create(1);
   local c_res_s = buffer.create(2);
   local c_res_t = buffer.create(4);
   local c_res_u = buffer.create(8);
   local c_res_v = buffer.create(10);
   buffer.writei8(c_res, val, buffer.readi8(c_res, val));
   buffer.writeu8(c_res, val, buffer.readu8(c_res, val));
   buffer.writei8(c_res_s, val, buffer.readi8(c_res_s, val));
   buffer.writeu8(c_res_s, val, buffer.readu8(c_res_s, val));
   buffer.writei8(c_res_s, val + 1, buffer.readi8(c_res_s, (val + 1)));
   buffer.writeu8(c_res_s, val + 1, buffer.readu8(c_res_s, (val + 1)));
   buffer.writei16(c_res_s, val, buffer.readi16(c_res_s, val));
   buffer.writeu16(c_res_s, val, buffer.readu16(c_res_s, val));
   buffer.writei8(c_res_t, val, buffer.readi8(c_res_t, val));
   buffer.writeu8(c_res_t, val, buffer.readu8(c_res_t, val));
   buffer.writei8(c_res_t, val + 3, buffer.readi8(c_res_t, (val + 3)));
   buffer.writeu8(c_res_t, val + 3, buffer.readu8(c_res_t, (val + 3)));
   buffer.writei16(c_res_t, val, buffer.readi16(c_res_t, val));
   buffer.writeu16(c_res_t, val, buffer.readu16(c_res_t, val));
   buffer.writei16(c_res_t, val + 2, buffer.readi16(c_res_t, (val + 2)));
   buffer.writeu16(c_res_t, val + 2, buffer.readu16(c_res_t, (val + 2)));
   buffer.writei32(c_res_t, val, buffer.readi32(c_res_t, val));
   buffer.writeu32(c_res_t, val, buffer.readu32(c_res_t, val));
   buffer.writef32(c_res_t, val, buffer.readf32(c_res_t, val));
   buffer.writei8(c_res_u, val, buffer.readi8(c_res_u, val));
   buffer.writeu8(c_res_u, val, buffer.readu8(c_res_u, val));
   buffer.writei8(c_res_u, val + 7, buffer.readi8(c_res_u, (val + 7)));
   buffer.writeu8(c_res_u, val + 7, buffer.readu8(c_res_u, (val + 7)));
   buffer.writei16(c_res_u, val, buffer.readi16(c_res_u, val));
   buffer.writeu16(c_res_u, val, buffer.readu16(c_res_u, val));
   buffer.writei16(c_res_u, val + 6, buffer.readi16(c_res_u, (val + 6)));
   buffer.writeu16(c_res_u, val + 6, buffer.readu16(c_res_u, (val + 6)));
   buffer.writei32(c_res_u, val, buffer.readi32(c_res_u, val));
   buffer.writeu32(c_res_u, val, buffer.readu32(c_res_u, val));
   buffer.writef32(c_res_u, val, buffer.readf32(c_res_u, val));
   buffer.writei32(c_res_u, val + 4, buffer.readi32(c_res_u, (val + 4)));
   buffer.writeu32(c_res_u, val + 4, buffer.readu32(c_res_u, (val + 4)));
   buffer.writef32(c_res_u, val + 4, buffer.readf32(c_res_u, (val + 4)));
   buffer.writef64(c_res_u, val, buffer.readf64(c_res_u, val));
   buffer.writei8(c_res_v, val, buffer.readi8(c_res_v, val));
   buffer.writeu8(c_res_v, val, buffer.readu8(c_res_v, val));
   buffer.writei8(c_res_v, val + 9, buffer.readi8(c_res_v, (val + 9)));
   buffer.writeu8(c_res_v, val + 9, buffer.readu8(c_res_v, (val + 9)));
   buffer.writei16(c_res_v, val, buffer.readi16(c_res_v, val));
   buffer.writeu16(c_res_v, val, buffer.readu16(c_res_v, val));
   buffer.writei16(c_res_v, val + 8, buffer.readi16(c_res_v, (val + 8)));
   buffer.writeu16(c_res_v, val + 8, buffer.readu16(c_res_v, (val + 8)));
   buffer.writei32(c_res_v, val, buffer.readi32(c_res_v, val));
   buffer.writeu32(c_res_v, val, buffer.readu32(c_res_v, val));
   buffer.writef32(c_res_v, val, buffer.readf32(c_res_v, val));
   buffer.writei32(c_res_v, val + 6, buffer.readi32(c_res_v, (val + 6)));
   buffer.writeu32(c_res_v, val + 6, buffer.readu32(c_res_v, (val + 6)));
   buffer.writef32(c_res_v, val + 6, buffer.readf32(c_res_v, (val + 6)));
   buffer.writef64(c_res_v, val, buffer.readf64(c_res_v, val));
   buffer.writef64(c_res_v, val + 2, buffer.readf64(c_res_v, (val + 2)));
   assert(is_native());
end)(0);
function deadStoreChecks1()
   local function c_func_h ()
      u += u_bb;
      for c_i = 1, 100 do
         print(("%* is %*"):format(u, u));
      end
   end;
   c_func_h();
   c_func_h();
   c_func_h();
   return 0;
end;
assert(deadStoreChecks1() == 111);
local function c_func_bl ()
   return type(math.sign(v_w));
end;
assert(c_func_bl(2) == "number");
assert(c_func_bl("2") == "number");
local function c_func_bm ()
   return type(math.modf(v_u));
end;
assert(c_func_bm(2) == "number");
assert(c_func_bm("2") == "number");
local function c_func_bn ()
   local c_v_o, c_value = math.modf(v);
   return type(c_value);
end;
assert(c_func_bn(2) == "number");
assert(c_func_bn("2") == "number");
return "OK";
