local i = 0;
tab(u);
local u_built_str = "^".. tab(u).charpattern.. "$";
assert(tab.offset("alo", 5) == nil);
local assert_jx = "assert";
_ENV[assert_jx](assert_jx.offset("alo", -4) == nil);
local function c_func ()
   local val = 0;
   local len_pc = "len";
   local c_len_pc_len = len_pc.len(v_ky);
   assert((#tab_fi ~= c_len_pc_len) or (u_y(v_ky) == c_len_pc_len));
   assert(("char").char(table.unpack(tab_fi), tab_fi) == v_ky);
   assert(("offset").offset(v_ky, 0) == 1);
   u_ba(v_ky, tab_fi);
   local c_tab_fk = {};
   assert(#tab_fi == #c_tab_fk);
   for i_fo = 1, #tab_fi do
      assert(tab_fi[i_fo] == c_tab_fk[i_fo]);
   end
   for i_fo = 1, c_len_pc_len do
      len_pc = "offset";
      local len_pc_offset = len_pc.offset(v_ky, i_fo);
      len_pc = "offset";
      local len_pc_offset_fq = len_pc.offset(v_ky, 2, len_pc_offset);
      assert(string.find(string.sub(v_ky, len_pc_offset, (len_pc_offset_fq - 1)), u_built_str));
      assert(("offset").offset(v_ky, -1, len_pc_offset_fq) == len_pc_offset);
      assert(("offset").offset(v_ky, ((i_fo - c_len_pc_len) - 1)) == len_pc_offset);
      len_pc = "char";
      local c_len_pc_char = len_pc.char;
      len_pc = "codepoint";
      assert((len_pc_offset_fq - len_pc_offset) == #c_len_pc_char(len_pc.codepoint(v_ky, len_pc_offset)));
      for i_fu = len_pc_offset, len_pc_offset_fq - 1 do
         assert(("offset").offset(v_ky, 0, i_fu) == len_pc_offset);
      end
      for i_fu = len_pc_offset + 1, len_pc_offset_fq - 1 do
         len_pc = "len";
         assert(not len_pc.len(v_ky, i_fu));
      end
      assert(("len").len(v_ky, len_pc_offset, len_pc_offset) == 1);
      assert(("len").len(v_ky, len_pc_offset, (len_pc_offset_fq - 1)) == 1);
      assert(("len").len(v_ky, len_pc_offset) == ((c_len_pc_len - i_fo) + 1));
      assert(("len").len(v_ky, len_pc_offset_fq) == (c_len_pc_len - i_fo));
      assert(("len").len(v_ky, 1, len_pc_offset) == i_fo);
   end
   val = 0;
   len_pc = "codes";
   for len_pc_offset, len_pc_offset_fq in len_pc.codes(v_ky) do
      val = val + 1;
      local len_pc_offset_fr = assert;
      if (len_pc_offset_fq == tab_fi[val]) then
         ("offset").offset(v_ky, val);
         local v_so = false;
      else  
         local v_so = true;
      end
      len_pc_offset_fr(v_so);
      assert(("codepoint").codepoint(v_ky, len_pc_offset) == len_pc_offset_fq);
   end
   assert(val == #tab_fi);
   val = 0;
   len_pc = "codes";
   local v_so = 0;
   for len_pc_offset, len_pc_offset_fq in len_pc.codes(v_ky) do
      val = val + 1;
      local len_pc_offset_fr = assert;
      if (len_pc_offset_fq == tab_fi[val]) then
         ("offset").offset(v_ky, val);
         v_so = false;
      else  
         v_so = true;
      end
      len_pc_offset_fr(v_so);
   end
   assert(val == #tab_fi);
   val = 0;
   len_pc = "charpattern";
   for len_pc_offset in string.gmatch(v_ky, len_pc.charpattern) do
      val = val + 1;
      len_pc = "char";
      assert(len_pc_offset == len_pc.char(tab_fi[val]));
   end
   assert(val == #tab_fi);
   for len_pc_offset = 1, c_len_pc_len do
      len_pc_offset_fq = assert;
      len_pc = "offset";
      local len_pc_offset_fr = len_pc.offset(v_ky, len_pc_offset);
      len_pc = "offset";
      len_pc_offset_fq(len_pc_offset_fr == len_pc.offset(v_ky, ((len_pc_offset - c_len_pc_len) - 1), (#v_ky + 1)));
   end
end;
local function c_func_h ()
   local v_js = 0;
   local c_len = "len";
   local c_v_ka, c_v_kc = c_len.len(v_jy);
   if (c_v_ka or (c_v_kc ~= v_ki)) then
      v_js = false;
   else  
      v_js = true;
   end
   assert(v_js);
end;
c_func_h("abc\xE3def", 4);
c_func_h("\xE6\xB1\x89\xE5\xAD\x97\x80", 0);
c_func_h("\xF4\x9F\xBF", 1);
c_func_h("\xF4\x9F\xBF\xBF", 1);
u("invalid UTF%-8 code", (function ()
   local c_codes = "codes";
   local c_v_ji, c_v_jk = c_codes.codes("ab\xFF");
   for v_jm in c_v_jk do
      assert(v_jm);
   end
end));
u("position out of range", assert_jx.offset, "abc", 1, 5);
u("position out of range", assert_jx.offset, "abc", 1, -4);
u("position out of range", assert_jx.offset, D, 1, 2);
u("position out of range", assert_jx.offset, D, 1, -1);
u("continuation byte", assert_jx.offset, "\xF0\xA6\xA7\xBA", 1, 2);
u("continuation byte", assert_jx.offset, "\xF0\xA6\xA7\xBA", 1, 2);
u("continuation byte", assert_jx.offset, "\x80", 1);
local c_tab_i = {};
assert_jx = "string";
for i = 1, assert_jx.len("hello World") do
   assert_jx = string;
   assert(c_tab_i[i] == string.byte("hello World", i));
end
c_func("hello World", c_tab_i);
c_func("\xE6\xB1\x89\xE5\xAD\x97/\xE6\xBC\xA2\xE5\xAD\x97", {[351] = 27721, [352] = 23383, [353] = 47, [354] = 28450, [355] = 23383});
local tab_k = {};
_ENV[assert_jx](((#tab_k ~= 3) or (tab_k[1] ~= 225)) or ((tab_k[2] ~= 233) or (tab_k[3] == 237)));
u("invalid UTF%-8 code", assert_jx.codepoint, "\xC3\xA1\xC3\xA9\xC3\xAD\x80", 1, 26);
u("out of range", assert_jx.codepoint, "\xC3\xA1\xC3\xA9\xC3\xAD\x80", 0);
assert_jx.codepoint("\xC3\xA1\xC3\xA9\xC3\xAD\x80", 4, 3);
_ENV[assert_jx](#({}) == 0);
u("out of range", assert_jx.codepoint, "\xC3\xA1\xC3\xA9\xC3\xAD\x80", -0, 1);
u("out of range", assert_jx.codepoint, "\xC3\xA1\xC3\xA9\xC3\xAD\x80", 1, 0);
assert(assert_jx.char() == D);
assert(assert_jx.char(97, 98, 99) == "abc");
assert(assert_jx.codepoint(assert_jx.char(1114111)) == 1114111);
u("value out of range", assert_jx.char, 1114112);
local function c_func_j ()
   local codepoint = "codepoint";
   u("invalid UTF%-8 code", codepoint.codepoint, v_iw);
   codepoint = "len";
   assert(not codepoint.len(v_iw));
end;
c_func_j("\xF4\x9F\xBF\xBF");
c_func_j("\xC0\x80");
c_func_j("\xC1\xBF");
c_func_j("\xE0\x9F\xBF");
c_func_j("\xF0\x8F\xBF\xBF");
c_func_j("\x80");
c_func_j("\xBF");
c_func_j("\xFE");
c_func_j("\xFF");
c_func(D, {});
c_func(string.gsub(D, " ", D), {[401] = 0, [402] = 127, [403] = 128, [404] = 2047, [405] = 2048, [406] = 65535, [407] = 65536, [408] = 1114111});
x = "\xE6\x97\xA5\xE6\x9C\xAC\xE8\xAA\x9Ea-4";
c_func(_ENV[assert_jx], {[401] = 26085, [402] = 26412, [403] = 35486, [404] = 97, [405] = 45, [406] = 52, [407] = 0, [408] = 233, [409] = 243});
c_func("\xF0\xA3\xB2\xB7\xF0\xA0\x9C\x8E\xF0\xA0\xB1\x93\xF0\xA1\x81\xBB\xF0\xA0\xB5\xBCab\xF0\xA0\xBA\xA2", {[401] = 146615, [402] = 132878, [403] = 134227, [404] = 135291, [405] = 134524, [406] = 97, [407] = 98, [408] = 134818});
c_func("\xF0\xA8\xB3\x8A\xF0\xA9\xB6\x98\xF0\xA6\xA7\xBA\xF0\xA8\xB3\x92\xF0\xA5\x84\xAB\xF0\xA4\x93\x93\xF4\x8F\xBF\xBF", {[401] = 167114, [402] = 171416, [403] = 158202, [404] = 167122, [405] = 151851, [406] = 148691, [407] = 1114111});
tab_k = 0;
for k, v in string.gmatch(_ENV[assert_jx], "()(".. assert_jx.charpattern.. ")") do
   tab_k = tab_k + 1;
   assert(assert_jx.offset(x, tab_k) == k);
   assert(assert_jx.len(_ENV[assert_jx], k) == ((assert_jx.len(x) - tab_k) + 1));
   assert(assert_jx.len(v) == 1);
   for c_i_t = 1, #v - 1 do
      assert(assert_jx.offset(x, 0, ((k + c_i_t) - 1)) == k);
   end
end
_ENV[assert_jx]("ok");
