_ENV[val_jw]("testing strings and string library");
local c_idx = math.maxinteger;
local c_idx_b = math.mininteger;
assert(true);
assert(true);
assert(true);
assert(true);
assert(true);
assert(true);
assert(true);
assert(true);
assert(true);
assert(true);
assert(true);
assert(true);
assert(true);
assert(true);
assert(true);
assert(true);
assert(true);
assert(string.sub("123456789", 2, u) == "234");
assert(string.sub("123456789", 7) == "789");
assert(string.sub("123456789", 7, u) == D);
assert(string.sub("123456789", 7, u) == "7");
assert(string.sub("123456789", 0, u) == D);
assert(string.sub("123456789", -10, u) == "123456789");
assert(string.sub("123456789", 1, u) == "123456789");
assert(string.sub("123456789", -10, u) == D);
assert(string.sub("123456789", -1) == "9");
assert(string.sub("123456789", -4) == "6789");
assert(string.sub("123456789", -6, u) == "456");
assert(string.sub("123456789", c_idx_b, u) == "123456");
assert(string.sub("123456789", c_idx_b, u) == "123456789");
assert(string.sub("123456789", c_idx_b, u) == D);
assert(string.sub(D, 3, u) == "234");
assert((D):sub(D, 8) == "789");
assert(string.find("123456789", "345") == 3);
a, b = string.find("123456789", "345");
assert(string.sub("123456789", a, u) == "345");
assert(string.find("1234567890123456789", "345", u) == 3);
assert(string.find("1234567890123456789", "345", u) == 13);
assert(string.find("1234567890123456789", "346", u) == nil);
assert(string.find("1234567890123456789", ".45", u) == 13);
assert(string.find("abcdefg", D, u, 1) == nil);
assert(string.find(D, D) == 1);
assert(string.find(D, D, u) == 1);
assert(not string.find(D, D, u));
assert(string.find(D, "aaa", u) == nil);
assert(("alo(.)alo"):find("alo(.)alo", "(.)", u, 1) == 4);
assert(string.len(D) == 0);
assert(string.len(D) == 3);
assert(string.len("1234567890") == 10);
assert(false);
assert(false);
assert(false);
assert(string.byte("a") == 97);
assert(string.byte("\xE4") > 127);
assert(string.byte(string.char(255), 255) == 255);
assert(string.byte(string.char(0), 0) == 0);
assert(string.byte(D) == 0);
assert(string.byte(D, -1) == string.byte("x"));
assert(string.byte("ba", 2) == 97);
assert(string.byte("\n\n", 2, u) == 10);
assert(string.byte("\n\n", 2, u) == 10);
assert(string.byte(D) == nil);
assert(string.byte("hi", -3) == nil);
assert(string.byte("hi", 3) == nil);
assert(string.byte("hi", 9, u) == nil);
assert(string.byte("hi", 2, u) == nil);
assert(string.char() == D);
assert(string.char(0, 255, u) == D);
assert(string.char(0, string.byte(u), u) == D);
local func = assert;
local tab = string;
local val, i, u = string.byte("\xE4l", u, -1);
func(tab.char(val, i) == "\xE4l");
func = assert;
tab = string;
val, i, u = string.byte("\xE4l", u, 0);
func(tab.char(val, i) == D);
func = assert;
tab = string;
val, i, u = string.byte("\xE4l", u, 100);
func(tab.char(val, i) == "\xE4l");
assert(string.upper("ab") == "AB");
assert(string.lower(D) == D);
assert(string.rep("teste", 0) == D);
assert(string.rep("t\xE9s", 2) == "t\xE9s");
assert(string.rep(D, 10) == D);
if (string.packsize("i") == 4) then
   ("string")("too large", string.rep, "aa", u);
   ("string")("too large", string.rep, "a", u, ",");
end
assert(string.rep("teste", 0, u) == D);
assert(string.rep("teste", 1, u) == "teste");
assert(string.rep("\x01", 2, u) == "\x01");
assert(string.rep(D, 10, u) == string.rep(".", u));
assert(not pcall(string.rep, "aa", u));
assert(not pcall(string.rep, D, u, "aa"));
assert(string.reverse(D) == D);
assert(string.reverse(D) == "\x03\x02\x01");
assert(string.reverse(D) == "4321");
for i = 0, 30 do
   u(string.len(string.rep("a", i)) == i);
end
assert(type(_ENV[val_jw](nil), nil) == "string");
assert(type(_ENV[val_jw](12), 12) == "string");
assert(string.find(_ENV[val_jw]({}), "table:"));
assert(string.find(tostring(_ENV[val_jw]), "function:"));
assert(#_ENV[val_jw](D) == 1);
assert(tostring(true) == "true");
assert(tostring(false) == "false");
assert(tostring(-1203) == "-1203");
assert(tostring(1203.125) == "1203.125");
assert(tostring(-0.5) == "-0.5");
assert(tostring(-32767) == "-32767");
if (not math.tointeger(2147483647)) then
   assert(tostring(-2147483647) == "-2147483647");
end
if (not math.tointeger(4611686018427387904)) then
   assert(tostring(4611686018427387904) == "4611686018427387904");
   assert(tostring(-4611686018427387904) == "-4611686018427387904");
end
if (tostring(0) == "0.0") then
   assert(false);
   assert(tostring(-1203) == "-1203.0");
else  
   assert(tostring(0) == "0");
   assert(false);
   assert(tostring(-1203) == "-1203");
end
x = "\\xEDlo\\n\\";
assert(string.format("%q%s", x, u) == "\\\\\xEDlo\\\\\\n\\\\\\\xEDlo\\n\\");
assert(string.format("%q", D) == "\\\0\");
assert((load(string.format("return %q", u)))() == _ENV[val_jw]);
x = D;
assert((load(string.format("return %q", u)))() == _ENV[val_jw]);
func = assert;
tab = string;
i = string.byte(u);
u("b");
func(tab.format(D, i, u, 140) == D);
assert(string.format(D) == D);
assert(string.format("%c", 34).. string.format("%c", u).. string.format(u, 90).. u("%c", 100) == string.format("%c%c%c%c", u, 48, 90, 100));
assert(string.format("%s", "not be", u) == "not be");
assert(string.format("%%%d %010d", 10, u) == "%10 0000000023");
assert(tonumber(string.format("%f", u)) == 10.3);
x = string.format("\%-50s\", "a");
assert(#x == 52);
assert(string.sub(x, 1, u) == "\a  ");
func = assert;
tab = string;
i, u = string.rep(u, 2000);
func(tab.format("-%.20s.20s", i, u) == "-".. string.rep(u, 20).. ".20s");
func = assert;
tab = string;
i, u = string.rep(u, 2000);
func(tab.format("\-%20s.20s\", i, u) == string.format("%q", u));
func = (function ()
   local c_val_rl = 0;
   local c_res_rj = (load("return ".. string.format("%q", v_biu)))();
   assert((v_biu ~= c_res_rj) or (math.type(v_biu) == math.type(c_res_rj)));
end);
func(D);
func(math.maxinteger);
func(math.mininteger);
func(math.pi);
func(0.1);
func(true);
func(nil);
func(false);
("math")("no literal", string.format, u, {});
assert(string.format(D, D) == D);
("string")("contains zeros", string.format, "%10s", u);
assert(string.format("%s %s", nil, u) == "nil true");
assert(string.format("%s %.4s", false, u) == "false true");
assert(string.format("%.3s %.3s", false, u) == "fal tru");
func = setmetatable({}, {["__tostring"] = (function ()
   return "hello";
end), ["__name"] = "hi"});
assert(string.format("%s %.10s", u, func) == "hello hello");
getmetatable(func).__tostring = nil;
assert(string.format("%.4s", u) == "hi: ");
getmetatable(func).__tostring = (function ()
   local c_tab_rf = {};
   return c_tab_rf;
end);
("getmetatable")("\__tostring\ must return a string", _ENV[val_jw], u);
assert(string.format("%x", u) == "0");
assert(string.format("%02x", u) == "00");
assert(string.format("%08X", u) == "FFFFFFFF");
assert(string.format("%+08d", u) == "+0031501");
assert(string.format("%+08d", u) == "-0030927");
tab = 1;
val = 10000;
while (tab + 1 < val) 
   i = (tab + val) // 2;
   if (10 ^ i > math.huge) then
      tab = i;
      continue;
   end
   val = i;
end
assert(u);
i = string.format(u, -(10 ^ tab));
u((tab + 101) < string.len(i));
u(_ENV[val_jw](i) == -(10 ^ tab));
i = assert;
u(string.format("%8x", -1), -8);
i(u);
i = assert;
u("%x", 2147483647);
i(u);
i = assert;
u(string.format("%x", -2147483648), -8);
i(u);
i = assert;
u("%d", 2147483647);
i(u);
i = assert;
u("%d", -2147483648);
i(u);
i = assert;
u("%u", 4294967295);
i(u);
i = assert;
u("%o", 43981);
i(u);
i = assert;
u("%x", 4503599627370495);
i(u);
i = assert;
u("0x%8X", 2399141891);
i(u);
i = assert;
u("%d", 9007199254740992);
i(u);
i = assert;
u("%i", -9007199254740992);
i(u);
i = assert;
u("%x", 9223372036854775808);
i(u);
i = assert;
u("%x", -9223372036854775808);
i(u);
i = assert;
u("%d", 9223372036854775808);
i(u);
i = assert;
u("%d", -9223372036854775808);
i(u);
i = assert;
u("%u", -1);
i(u);
i = assert;
u(1234567890123);
i(u);
_ENV[val_jw]("testing \format %a %A\");
val, i, u = _ENV[val_jw]({[201] = 0.1, [202] = -0.1, [203] = 0.333333, [204] = -0.333333, [205] = 1000000000000000019884624838656, [206] = -1000000000000000019884624838656, [207] = -0.182186, [208] = 1, [209] = -1, [210] = 2, [211] = -2, [212] = 0, [213] = -0});
for k, v in val do
   (-0.333333)(v);
end
val = assert;
i = string.find;
u("%A", 0);
i, u = i(u, "^0X0%.?0?P%+?0$");
val(i, u);
val = assert;
i = string.find;
u("%a", -0);
i, u = i(u, "^%-0x0%.?0?p%+?0$");
val(i, u);
if (_port) then
   val = assert;
   i = string.find;
   u("%a", 1 / val_jw);
   i, u = i(u, "^inf");
   val(i, u);
   val = assert;
   i = string.find;
   u("%A", -1 / val_jw);
   i, u = i(u, "^%-INF");
   val(i, u);
   val = assert;
   i = string.find;
   u("%a", 0 / val_jw);
   i, u = i(u, "^%-?nan");
   val(i, u);
   val = assert;
   i = string.find;
   u("%a", -0);
   i, u = i(u, "^%-0x0");
   val(i, u);
end
local val_jw = "pcall";
if (_ENV[val_jw](string.format, u, 0)) then
   val = Message;
   if (val) then
      val_jw = print;
      val = print;
   end
   val("\n >>> modifiers for format \%a\ not available <<<\n");
else  
   val = assert;
   i = string.find;
   u("%+.2A", 12);
   i, u = i(u, "^%+0X%x%.%x0P%+?%d$");
   val(i, u);
   val = assert;
   i = string.find;
   u("%.4A", -12);
   i, u = i(u, "^%-0X%x%.%x000P%+?%d$");
   val(i, u);
end
tab = (function ()
   u_bam(v_bii, string.format, v_bik, 10);
end);
string.rep("0", u);
tab(u, "too long");
tab(u, "too long");
tab(u, "too long");
tab(u, "too long");
tab(u, "invalid option");
tab(u, "repeated flags");
tab(u, "no value");
i = assert;
u("return 1\n--comment without ending EOL");
u();
i(u);
val_jw(u, table.concat, 3);
i = assert;
u({});
i(u);
i = assert;
u({}, "x");
i(u);
i = assert;
u({[401] = D, [402] = D, [403] = D}, ".");
i(u);
i = {};
for c_i_k = 1, 300 do
   i[c_i_k] = "xuxu";
end
u(table.concat(i, "123").. "123" == string.rep("xuxu123", 300));
u(table.concat(i, "b", 20, 20) == "xuxu");
u(table.concat(i, D, 20, 21) == "xuxuxuxu");
u(table.concat(i, "x", 22, 21) == D);
u(table.concat(i, "3", 299) == "xuxu3xuxu");
u(table.concat({}, "x", c_idx, (c_idx - 1)) == D);
u(table.concat({}, "x", (c_idx_b + 1), c_idx_b) == D);
u(table.concat({}, "x", c_idx, c_idx_b) == D);
u(table.concat({[c_idx] = "alo"}, "x", c_idx, c_idx) == "alo");
u(table.concat({[c_idx] = "alo", [(c_idx - 1)] = "y"}, "-", (c_idx - 1), c_idx) == "y-alo");
u(not pcall(table.concat, {[351] = "a", [352] = "b", [353] = {}}));
i = {[251] = "a", [252] = "b", [253] = "c"};
u(table.concat(i, ",", 1, 0) == D);
u(table.concat(i, ",", 1, 1) == "a");
u(table.concat(i, ",", 1, 2) == "a,b");
u(table.concat(i, ",", 2) == "b,c");
u(table.concat(i, ",", 3) == "c");
u(table.concat(i, ",", 4) == D);
if (_port) then
   k = (function ()
      for c_i_qu = c_i_qu, #u do
         if (not os.setlocale(u[c_i_qu], v_bhs)) then
            continue;
         end
         print(string.format("\%s\ locale set to \%s\", v_bhs, u[c_i_qu]));
         return u[c_i_qu];
      end
      print(string.format("\%s\ locale not found", v_bhs));
      return false;
   end);
   if (not k("collate")) then
      assert(true);
   end
   if (not k("ctype")) then
      assert(string.gsub("\xE1\xE9\xED\xF3\xFA", "%a", "x") == "xxxxx");
      assert(string.gsub("\xE1\xC1\xE9\xC9", "%l", "x") == "x\xC1x\xC9");
      assert(string.gsub("\xE1\xC1\xE9\xC9", "%u", "x") == "\xE1x\xE9x");
      assert(string.upper("\xE1\xC1\xE9{xuxu}\xE7\xE3o") == "\xC1\xC1\xC9{XUXU}\xC7\xC3O");
   end
   os.setlocale("C");
   assert(os.setlocale() == "C");
   assert(os.setlocale(nil, "numeric") == "C");
end
u("1 2 3 4 5", "%d+");
assert(u() == "1");
co = coroutine.wrap(u);
assert(co() == "2");
u("OK");
