tab("testing UTF-8 library");
local function u_func ()
   local res = 0;
   local c_success, c_result = pcall(function);
   local c_glb = assert;
   if (c_success) then
      res = ()string.find(c_result, v_dq);
   else  
      res = false;
   end
   c_glb(res);
end;
assert(()tab.offset("alo", 5) == nil);
local assert_jx = "assert";
(_ENV[assert_jx])(()assert_jx.offset("alo", -4) == nil);
local function c_func ()
   local v_cc = 0;
   local c_len = "len";
   local c_v_ck, c_v_cm = ()c_len.len(v_ci);
   if (c_v_ck or (c_v_cm ~= v_cs)) then
      v_cc = false;
   else  
      v_cc = true;
   end
   assert(v_cc);
end;
c_func("abc\xE3def", 4);
c_func("\xE6\xB1\x89\xE5\xAD\x97\x80", 0);
c_func("\xF4\x9F\xBF", 1);
c_func("\xF4\x9F\xBF\xBF", 1);
u_func("invalid UTF%-8 code", (function ()
end));
u_func("position out of range", assert_jx.offset, "abc", 1, 5);
u_func("position out of range", assert_jx.offset, "abc", 1, -4);
u_func("position out of range", assert_jx.offset, D, 1, 2);
u_func("position out of range", assert_jx.offset, D, 1, -1);
u_func("continuation byte", assert_jx.offset, "\xF0\xA6\xA7\xBA", 1, 2);
u_func("continuation byte", assert_jx.offset, "\xF0\xA6\xA7\xBA", 1, 2);
u_func("continuation byte", assert_jx.offset, "\x80", 1);
local tab_i = {};
assert_jx = "string";
tab_i[349] = "hello World";
tab_i[350] = tab_i;
tab_i[351] = ()_ENV[assert_jx].byte("hello World", 1, -1);
tab_i[352] = -1;
tab_i[353] = v;
tab_i[354] = v_bq;
tab_i[355] = v_bu;
for c_i = 1, ()assert_jx.len("hello World") do
   assert(tab_i[-1] == ()string.byte("hello World", -1));
end
