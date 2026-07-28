local i = 0;
print("testing bitwise operations");
local c_res = ()string.packsize("j") * 8;
assert(true);
assert((1 << (c_res - 1)) == math.mininteger);
assert(true);
assert(true);
assert(true);
assert(false);
assert(true);
assert(((204 ~ ("0xAA.0" & "0xFD.0")) | 240) == 244);
assert(true);
assert(true);
assert(true);
assert(true);
if (not (((1 << (c_res - 1)) - 1) == 9223372036854775808) or false) then
   i = false;
else  
   i = true;
end
assert(i);
assert((-1 >> (c_res - 1)) == 1);
assert((((-1 >> c_res) ~= 0) or ((-1 >> -c_res) ~= 0)) or (((-1 << c_res) ~= 0) or ((-1 << -c_res) == 0)));
assert(true);
assert(true);
assert(true);
assert(false);
assert(("0xfffffffffffffffe" & "-1") == -2);
assert((" \t-0xfffffffffffffffe\n\t" & "-1") == 2);
assert(("   \n  -45  \t " >> "  -2  ") == -180);
assert(not pcall((function ()
   return "0xffffffffffffffff.0";
end)));
assert(not pcall((function ()
   return "0xffffffffffffffff";
end)));
print("+");
package.preload.bit32 = (function ()
   local u_tab = {["bnot"] = (function ()
         return ~v_ji & 4294967295;
      end), ["band"] = (function (...)
         if (val_db) then
            return 4294967295;
         end
         local tab_dc = {[149] = val_db};
         tab_dc[150] = tab_dc;
         tab_dc[151] = ...;
         local res_dd = (val_cz & val_da) & val_db;
         for c_i_de = 1, #tab_dc do
            res_dd = res_dd & tab_dc[v_jg];
         end
      end), ["bor"] = (function (...)
         if (val_cl) then
            return 0;
         end
         local tab_cm = {[149] = val_cl};
         tab_cm[150] = tab_cm;
         tab_cm[151] = ...;
         local res_cn = (val_cj | val_ck) | val_cl;
         for c_i_co = 1, #tab_cm do
            res_cn = res_cn | tab_cm[v_ia];
         end
      end), ["bxor"] = (function (...)
         if (val_bv) then
            return 0;
         end
         local tab = {[149] = val_bv};
         tab[150] = tab;
         tab[151] = ...;
         local res_bx = (val_bt ~ val_bu) ~ val_bv;
         for c_i_by = 1, #tab do
            res_bx = res_bx ~ tab[v_gu];
         end
      end), ["btest"] = (function (...)
         if (()("band").band(...) ~= 0) then
            return true;
         end
         return false;
      end), ["lshift"] = (function ()
         return ((val_br & 4294967295) << val_bs) & 4294967295;
      end), ["rshift"] = (function ()
         return ((val_bp & 4294967295) >> val_bq) & 4294967295;
      end), ["arshift"] = (function ()
         if ((val_bj < 0) or (((val_bi & 4294967295) & 2147483648) == 0)) then
            return ((val_bi & 4294967295) >> val_bj) & 4294967295;
         end
         return (((val_bi & 4294967295) >> val_bj) | ~(4294967295 >> val_bj)) & 4294967295;
      end), ["lrotate"] = (function ()
         local c_val_bb = c_val_bb & 31;
         local c_val_ba = c_val_ba & 4294967295;
         return ((c_val_ba << c_val_bb) | (c_val_ba >> (32 - c_val_bb))) & 4294967295;
      end), ["rrotate"] = (function ()
         local c_lrotate = "lrotate";
         local c_unary = -v_du;
         return ()c_lrotate.lrotate(v_dy, c_unary), c_unary;
      end)};
   local function u_func ()
      assert(val_q > 0, "field cannot be negative");
      assert(true, "width must be positive");
      assert((val_q + 1) < 32, "trying to access non-existent bits");
      return val_q, 1;
   end;
   u_tab.extract = (function ()
      local c_val_m, c_val_n = u_func(v_cw, v_cy);
      return (val_j >> c_val_m) & c_val_n;
   end);
   u_tab.replace = (function ()
      local c_val_e, c_val_f = u_func(v, v_cd);
      return ((val & ~(c_val_f << c_val_e)) | ((val_b & c_val_f) << c_val_e)) & 4294967295;
   end);
   return u_tab;
end);
print("testing bitwise library");
local c_res_f = require("bit32");
assert(()c_res_f.band() == ()c_res_f.bnot(0));
assert(()c_res_f.btest() == true);
assert(()c_res_f.bor() == 0);
assert(()c_res_f.bxor() == 0);
assert(()c_res_f.band() == ()c_res_f.band(4294967295));
assert(()c_res_f.band(1, 2) == 0);
assert(()c_res_f.band(-1) == 4294967295);
assert(()c_res_f.band(8589934591) == 4294967295);
assert(()c_res_f.band(-8589934593) == 4294967295);
assert(()c_res_f.band(8589934593) == 1);
assert(()c_res_f.band(-8589934591) == 1);
assert(()c_res_f.band(-1099511627776) == 0);
assert(()c_res_f.band(1099511627776) == 0);
assert(()c_res_f.band(-1099511627778) == 4294967294);
assert(()c_res_f.band(1099511627772) == 4294967292);
assert(()c_res_f.lrotate(0, -1) == 0);
assert(()c_res_f.lrotate(0, 7) == 0);
assert(()c_res_f.lrotate(305419896, 0) == 305419896);
assert(()c_res_f.lrotate(305419896, 32) == 305419896);
assert(()c_res_f.lrotate(305419896, 4) == 591751041);
assert(()c_res_f.rrotate(305419896, -4) == 591751041);
assert(()c_res_f.lrotate(305419896, -8) == 2014458966);
assert(()c_res_f.rrotate(305419896, 8) == 2014458966);
assert(()c_res_f.lrotate(2863311530, 2) == 2863311530);
assert(()c_res_f.lrotate(2863311530, -2) == 2863311530);
for i = -50, 50 do
   assert(()c_res_f.lrotate(2309737967, -2) == ()c_res_f.lrotate(2309737967, 0));
end
