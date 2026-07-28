print("testing UTF-8 library");
local function u_func (...)
   local c_success, c_result = pcall(function, ...);
   assert(not c_success and string.find(c_result, v_co));
end;
assert(not utf8.offset("alo", 5));
assert(not utf8.offset("alo", -4));
local function func ()
   local c_v_bu, c_v_bw = utf8.len(v_bs);
   assert(not c_v_bu and (c_v_bw == v_cc));
end;
func("abc\xE3def", 4);
func("\xF4\x9F\xBF", 1);
func("\xF4\x9F\xBF\xBF", 1);
func("\xE6\xB1\x89\xE5\xAD\x97\x80", 0);
func("\x80hello", 1);
func("hel\x80lo", 4);
func("\xE6\xB1\x89\xE5\xAD\x97\xBF", 0);
func("\xBFhello", 1);
func("hel\xBFlo", 4);
func = (function ()
   u_func("invalid UTF%-8 code", (function ()
      for v in utf8.codes(u) do
         assert(v);
      end
   end));
end);
func("ab\xFF");
func("\xF4\x90\x80\x80");
func("in\x80valid");
func("\xBFinvalid");
func("\xCE\xB1\xCE\xBB\xCF\x86\xBF\xCE\xB1");
local res = utf8.codes("");
assert(res("", 2) == nil);
assert(res("", -1) == nil);
assert(res("", math.mininteger) == nil);
u_func("position out of range", utf8.offset, "abc", 1, 5);
u_func("position out of range", utf8.offset, "abc", 1, -4);
u_func("position out of range", utf8.offset, "", 1, 2);
u_func("position out of range", utf8.offset, "", 1, -1);
u_func("continuation byte", utf8.offset, "\xF0\xA6\xA7\xBA", 1, 2);
u_func("continuation byte", utf8.offset, "\xF0\xA6\xA7\xBA", 1, 2);
u_func("continuation byte", utf8.offset, "\x80", 1);
u_func("out of string", utf8.len, "abc", 0, 2);
u_func("out of string", utf8.len, "abc", 1, 4);
res = {string.byte("hello World", 1, -1)};
for c_i = 1, utf8.len("hello World") do
   assert(res[c_i] == string.byte("hello World", c_i));
end
