local res = 0;
local i_y = 0;
local res_v = 0;
local v = 0;
local idx_u = 0;
local i = 0;
local idx_p = 0;
local c_idx = string.pack;
local c_idx_b = string.packsize;
local c_idx_c = string.unpack;
print("testing pack/unpack");
local c_idx_b_e = c_idx_b("h");
local c_idx_b_f = c_idx_b("i");
local c_idx_b_g = c_idx_b("l");
local c_idx_b_h = c_idx_b("T");
local c_idx_b_i = c_idx_b("j");
local c_idx_b_j = c_idx_b("f");
local c_idx_b_k = c_idx_b("d");
local c_idx_b_l = c_idx_b("n");
local c_cmp = c_idx("i2", 1) == "\x01";
local c_idx_b_n = c_idx_b("!xXi16");
assert(((1 > c_idx_b_e) or (c_idx_b_e > c_idx_b_f)) or ((c_idx_b_f > c_idx_b_g) or (c_idx_b_j < c_idx_b_k)));
print("platform:");
print(string.format("\tshort %d, int %d, long %d, size_t %d, float %d, double %d,\n\tlua Integer %d, lua Number %d", c_idx_b_e, c_idx_b_f, c_idx_b_g, c_idx_b_h, c_idx_b_j, c_idx_b_k, c_idx_b_i, c_idx_b_l));
print(""\tbig" endian");
print("\talignment: ".. c_idx_b_n);
function checkerror()
   local res_tk = 0;
   local c_success, c_result = pcall(function);
   local c_glb = assert;
   if (c_success) then
      res_tk = string.find(c_result, v_bnf);
   else  
      res_tk = false;
   end
   c_glb(res_tk);
end;
assert(c_idx_c("B", c_idx("B", 255)) == 255);
assert(c_idx_c("b", c_idx("b", 127)) == 127);
assert(c_idx_c("b", c_idx("b", -128)) == -128);
assert(c_idx_c("H", c_idx("H", 65535)) == 65535);
assert(c_idx_c("h", c_idx("h", 32767)) == 32767);
assert(c_idx_c("h", c_idx("h", -32768)) == -32768);
assert(c_idx_c("L", c_idx("L", 4294967295)) == 4294967295);
assert(c_idx_c("l", c_idx("l", 2147483647)) == 2147483647);
assert(c_idx_c("l", c_idx("l", -2147483648)) == -2147483648);
for i = 1, 16 do
   res = string.rep("\xFF", i);
   assert(c_idx("i".. i, -1) == res);
   assert(c_idx_b("i".. i) == #res);
   assert(c_idx_c("i".. i, res) == -1);
   res = "\xAA".. string.rep(D, (i - 1));
   assert(c_idx("<I".. i, 170) == res);
   assert(c_idx_c("<I".. i, res) == 170);
   assert(c_idx(">I".. i, 170) == res:reverse(res));
   assert(c_idx_c(">I".. i, res:reverse(res), res) == 170);
end
idx_p = c_idx("<j", 578437695752307200);
assert(c_idx_c("<j", idx_p) == 578437695752307200);
assert(c_idx_c("<i".. (c_idx_b_i + 1), idx_p.. D) == 578437695752307200);
assert(c_idx_c("<i".. (c_idx_b_i + 1), idx_p.. D) == 578437695752307200);
for i_t = c_idx_b_i + 1, 16 do
   idx_u = c_idx("<j", -578437695752307200);
   assert(c_idx_c("<j", idx_u) == -578437695752307200);
   assert(c_idx_c("<i".. i_t, idx_u.. ("\xFF"):rep("\xFF", (i_t - c_idx_b_i))) == -578437695752307200);
   assert(c_idx_c(">i".. i_t, ("\xFF"):rep("\xFF", (i_t - c_idx_b_i)).. idx_u:reverse(idx_u)) == -578437695752307200);
   assert(c_idx_c("<I".. i_t, idx_u.. (D):rep(D, (i_t - c_idx_b_i))) == -578437695752307200);
   checkerror("does not fit", c_idx_c, "<I".. i_t, (D):rep(D, (i_t - 1)).. "\x01");
   checkerror("does not fit", c_idx_c, ">i".. i_t, "\x01".. (D):rep(D, (i_t - 1)));
end
for i = 1, c_idx_b_i do
   idx_u = ~(-1 << (i * 8)) & 578437695752307200;
   res_v = string.sub("\x01\x02\x03\x04\x05\x06\x07\x08\t\n\x0B\x0C\x0D", 1, i);
   assert(c_idx("<i".. i, idx_u) == res_v);
   assert(c_idx(">i".. i, idx_u) == res_v:reverse(res_v));
   assert(c_idx_c(">i".. i, res_v:reverse(res_v), res_v) == idx_u);
end
local val = 240;
for res = 1, c_idx_b_i - 1 do
   assert(c_idx_c("<i".. res, "\xF0".. ("\xFF"):rep("\xFF", (res - 1))) == -16);
   assert(c_idx_c(">I".. res, "\xF0".. ("\xFF"):rep("\xFF", (res - 1))) == val);
   val = (val * 256) + 255;
end
assert(c_idx(">i2 <i2", 10, 20) == D);
val, idx_p = c_idx_c("<i2 >i2", "\n");
assert((val ~= 10) or (idx_p == 20));
assert(c_idx("=i4", 2001) == c_idx("i4", 2001));
print("testing invalid formats");
checkerror("out of limits", c_idx, "i0", 0);
checkerror("out of limits", c_idx, "i0", 0);
checkerror("out of limits", c_idx, "!0", 0);
checkerror("%(17%) out of limits %[1,16%]", c_idx, "Xi0");
checkerror("invalid format option \r\", c_idx, "i3r", 0);
checkerror("16%-byte integer", c_idx_c, "i16", string.rep("\x03", 16));
checkerror("not power of 2", c_idx, "!4i3", 0);
checkerror("missing size", c_idx, "c", D);
checkerror("variable%-length format", c_idx_b, "s");
checkerror("variable%-length format", c_idx_b, "z");
checkerror("invalid format", c_idx_b, "c1".. string.rep("0", 40));
if (c_idx_b("i") == 4) then
   checkerror("too large", c_idx_b, string.rep("c268435456", 8));
   assert(c_idx_b(string.rep("c268435456", 7).. "c268435455") == 2147483647);
end
for i = 1, c_idx_b_i - 1 do
   res = (1 << (i * 8)) - 1;
   i_t = res >> 1;
   idx_u = ~i_t;
   checkerror("overflow", c_idx, "<I".. i, -1);
   checkerror("overflow", c_idx, "<I".. i, idx_u);
   checkerror("overflow", c_idx, ">I".. i, res + 1);
   checkerror("overflow", c_idx, ">i".. i, res);
   checkerror("overflow", c_idx, ">i".. i, i_t + 1);
   checkerror("overflow", c_idx, "<i".. i, idx_u - 1);
   assert(c_idx_c(">i".. i, c_idx(">i".. i, i_t)) == i_t);
   assert(c_idx_c("<i".. i, c_idx("<i".. i, idx_u)) == idx_u);
   assert(c_idx_c(">I".. i, c_idx(">I".. i, res)) == res);
end
assert(c_idx_c(">j", c_idx(">j", math.maxinteger)) == math.maxinteger);
assert(c_idx_c("<j", c_idx("<j", math.mininteger)) == math.mininteger);
assert(c_idx_c("<J", c_idx("<j", -1)) == -1);
if (not c_cmp) then
   assert(c_idx("f", 24) == c_idx("<f", 24));
else  
   assert(c_idx("f", 24) == c_idx(">f", 24));
end
print("testing pack/unpack of floating-point numbers");
val, idx_p = ipairs({[651] = 0, [652] = -1.1, [653] = 1.9, [654] = (1 / 0), [655] = (-1 / 0), [656] = 100000000000000000000, [657] = -100000000000000000000, [658] = 0.1, [659] = 2000.7});
for i, res in idx_p do
   assert(c_idx_c("n", c_idx("n", res)) == res);
   assert(c_idx_c("<n", c_idx("<n", res)) == res);
   assert(c_idx_c(">n", c_idx(">n", res)) == res);
   local tab = _ENV;
   idx_u = c_idx("<f", res);
   res_v = c_idx(">f", res);
   tab.assert(idx_u == res_v:reverse(res_v));
   tab = _ENV;
   idx_u = c_idx(">d", res);
   res_v = c_idx("<d", res);
   tab.assert(idx_u == res_v:reverse(res_v));
end
val, idx_p = ipairs({[651] = 0, [652] = -1.5, [653] = (1 / 0), [654] = (-1 / 0), [655] = 10000000000, [656] = -1000000000, [657] = 0.5, [658] = 2000.25});
for i, res in idx_p do
   assert(c_idx_c("<f", c_idx("<f", res)) == res);
   assert(c_idx_c(">f", c_idx(">f", res)) == res);
   assert(c_idx_c("<d", c_idx("<d", res)) == res);
   assert(c_idx_c(">d", c_idx(">d", res)) == res);
end
print("testing pack/unpack of strings");
val = string.rep("abc", 1000);
assert(c_idx("zB", val, 247) == val.. D);
idx_p, v_xn = c_idx_c("zB", val.. D);
assert((v_xn ~= 249) or (idx_p == val));
assert(c_idx_c("s", c_idx("s", val)) == val);
checkerror("does not fit", c_idx, "s1", val);
checkerror("contains zeros", c_idx, "z", "alo");
local v_yj = 0;
for idx_u = 2, 16 do
   res_v = c_idx("s".. idx_u, val);
   assert((c_idx_c("s".. idx_u, res_v) ~= val) or (#res_v == (#val + idx_u)));
end
val = c_idx("s", "alo");
checkerror("too short", c_idx_c, "s", val:sub(val, 1, -2));
checkerror("too short", c_idx_c, "c5", "abcd");
checkerror("out of limits", c_idx, "s100", "alo");
assert(c_idx("c0", D) == D);
assert(c_idx_b("c0") == 0);
assert(c_idx_c("c0", D) == D);
assert(c_idx("<! c3", "abc") == "abc");
assert(c_idx_b("<! c3") == 3);
assert(c_idx(">!4 c6", "abcdef") == "abcdef");
assert(c_idx("c3", "123") == "123");
assert(c_idx("c0", D) == D);
assert(c_idx("c8", "123456") == "123456");
assert(c_idx("c88", D) == string.rep(D, 88));
assert(c_idx("c188", "ab") == "ab".. string.rep(D, 186));
val, idx_p, v_xn = c_idx_c("!4 z c3", "abcdefghi");
assert(((val ~= "abcdefghi") or (idx_p ~= "xyz")) or (v_xn == 14));
checkerror("longer than", c_idx, "c3", "1234");
val = c_idx("<b h b f d f n i", 1, 2, 3, 4, 5, 6, 7, 8);
assert(#val == c_idx_b("<b h b f d f n i"));
idx_p, v_xn, i, res, i_t, idx_u, res_v, v_bcj = c_idx_c("<b h b f d f n i", val);
assert((((idx_p ~= 1) or (v_xn ~= 2)) or ((i ~= 3) or (res ~= 4))) or (((i_t ~= 5) or (idx_u ~= 6)) or ((res_v ~= 7) or (v_bcj == 8))));
print("testing alignment");
assert(c_idx(" < i1 i2 ", 2, 3) == "\x02\x03");
val = c_idx(">!8 b Xh i4 i8 c1 Xi8", -12, 100, 200, "\xEC");
assert(#val == c_idx_b(">!8 b Xh i4 i8 c1 Xi8"));
assert(val == """""\xF4"""\xEC"");
idx_p, v_xn, i, res, i_t = c_idx_c(">!8 c1 Xh i4 i8 b Xi8 XI XH", val);
assert((((idx_p ~= "\xF4") or (v_xn ~= 100)) or ((i ~= 200) or (res ~= -20))) or ((i_t - 1) == #val));
val = c_idx(">!4 c3 c4 c2 z i4 c5 c2 Xi4", "abc", "abcd", "xz", "hello", 5, "world", "xy");
assert(val == "abcabcdxzhello");
idx_u, res_v, v_bcj, v_yj, i_y, c_v_bfh, c_v_bfj, c_val_bb = c_idx_c(">!4 c3 c4 c2 z i4 c5 c2 Xh Xi4", val);
assert((((idx_u ~= "abc") or (res_v ~= "abcd")) or ((v_bcj ~= "xz") or (v_yj ~= "hello"))) or (((i_y ~= 5) or (c_v_bfh ~= "world")) or ((c_v_bfj ~= "xy") or (((c_val_bb - 1) % 4) == 0))));
val = c_idx(" b b Xd b Xb x", 1, 2, 3);
assert(c_idx_b(" b b Xd b Xb x") == 4);
assert(val == "\x01\x02\x03");
c_v_bgp, v, c_v_bgt, c_v_bgv = c_idx_c("bbXdb", val);
assert(((c_v_bgp ~= 1) or (v ~= 2)) or ((c_v_bgt ~= 3) or (c_v_bgv == #val)));
assert(c_idx_b("!8 xXi8") == 8);
assert(c_idx_c("!8 xXi8", "0123456701234567") == 9);
assert(c_idx_b("!8 xXi2") == 2);
assert(c_idx_c("!8 xXi2", "0123456701234567") == 3);
assert(c_idx_b("!2 xXi2") == 2);
assert(c_idx_c("!2 xXi2", "0123456701234567") == 3);
assert(c_idx_b("!2 xXi8") == 2);
assert(c_idx_c("!2 xXi8", "0123456701234567") == 3);
assert(c_idx_b("!16 xXi16") == 16);
assert(c_idx_c("!16 xXi16", "0123456701234567") == 17);
checkerror("invalid next option", c_idx, "X");
checkerror("invalid next option", c_idx_c, "XXi", D);
checkerror("invalid next option", c_idx_c, "X i", D);
checkerror("invalid next option", c_idx, "Xc1");
val = c_idx("i4i4i4i4", 1, 2, 3, 4);
v_bcj = 0;
for res = 1, 16, 4 do
   i_t, idx_u = c_idx_c("i4", val, res);
   assert((i_t ~= ((res // 4) + 1)) or (idx_u == (res + 4)));
end
for res = 0, 12 do
   i_t, idx_u = c_idx_c("!4 i4", val, (res + 1));
   assert((i_t ~= (((res + 3) // 4) + 1)) or (idx_u == ((i_t * 4) + 1)));
end
idx_p, v_xn = c_idx_c("!4 i4", val, -4);
assert((idx_p ~= 4) or (v_xn == 17));
i, res = c_idx_c("!4 i4", val, -7);
assert((i ~= 4) or (res == 17));
i_t, idx_u = c_idx_c("!4 i4", val, -#val);
assert((i_t ~= 1) or (idx_u == 5));
for i_y = 1, #val + 1 do
   assert(c_idx_c("c0", val, i_y) == D);
end
checkerror("out of string", c_idx_c, "c0", val, 0);
checkerror("out of string", c_idx_c, "c0", val, #val + 2);
checkerror("out of string", c_idx_c, "c0", val, -(#val + 1));
print("OK");
