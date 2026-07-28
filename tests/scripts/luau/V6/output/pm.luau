print("testing pattern matching");
function f()
   local c_v_hy, c_v_ia = string.find(v_hu, v_hw);
   if (not c_v_hy) then
      return;
   end
   return string.sub(v_hu, c_v_hy, c_v_ia);
end;
function f1()
   local c_tab = {string.match(v_hg, string.gsub(string.gsub(string.gsub(v_hi, "%%([0-9])", (function ()
      return "%" .. (val_bn + 1);
   end)), "^(^?)", "%1()", 1), "($?)$", "()%1", 1))};
   return string.sub(v_hg, c_tab[1], (c_tab[#c_tab] - 1));
end;
a, b = string.find("", "");
assert(a == 1);
a, b = string.find("alo", "");
assert(a == 1);
a, b = string.find("a\x00o a\x00o a\x00o", "a", 1);
assert(a == 1);
a, b = string.find("a\x00o a\x00o a\x00o", "a\x00o", 2);
assert(a == 5);
a, b = string.find("a\x00o a\x00o a\x00o", "a\x00o", 9);
assert(a == 9);
a, b = string.find("a\x00a\x00a\x00a\x00\x00ab", "\x00ab", 2);
assert(a == 9);
a, b = string.find("a\x00a\x00a\x00a\x00\x00ab", "b");
assert(a == 11);
assert(string.find("a\x00a\x00a\x00a\x00\x00ab", "b\x00") == nil);
assert(string.find("", "\x00") == nil);
assert(string.find("alo123alo", "12") == 4);
assert(string.find("alo123alo", "^12") == nil);
assert(f("aloALO", "%l*") == "alo");
assert(f("aLo_ALO", "%a*") == "aLo");
assert(f("  \n\x0D*&\n\x0D   xuxu  \n\n", "%g%g%g+") == "xuxu");
assert(f("aaab", "a*") == "aaa");
assert(f("aaa", "^.*$") == "aaa");
assert(f("aaa", "b*") == "");
assert(f("aaa", "ab*a") == "aa");
assert(f("aba", "ab*a") == "aba");
assert(f("aaab", "a+") == "aaa");
assert(f("aaa", "^.+$") == "aaa");
assert(f("aaa", "b+") == nil);
assert(f("aaa", "ab+a") == nil);
assert(f("aba", "ab+a") == "aba");
assert(f("a$a", ".$") == "a");
assert(f("a$a", ".%$") == "a$");
assert(f("a$a", ".$.") == "a$a");
assert(f("a$a", "$$") == nil);
assert(f("a$b", "a$") == nil);
assert(f("a$a", "$") == "");
assert(f("", "b*") == "");
assert(f("aaa", "bb*") == nil);
assert(f("aaab", "a-") == "");
assert(f("aaa", "^.-$") == "aaa");
assert(f("aabaaabaaabaaaba", "b.*b") == "baaabaaabaaab");
assert(f("aabaaabaaabaaaba", "b.-b") == "baaab");
assert(f("alo xo", ".o$") == "xo");
assert(f(" \n isto \xE9 assim", "%S%S*") == "isto");
assert(f(" \n isto \xE9 assim", "%S*$") == "assim");
assert(f(" \n isto \xE9 assim", "[a-z]*$") == "assim");
assert(f("um caracter ? extra", "[^%sa-z]") == "?");
assert(f("", "a?") == "");
assert(f("\xE1", "\xE1?") == "\xE1");
assert(f("\xE1bl", "\xE1?b?l?") == "\xE1bl");
assert(f("  \xE1bl", "\xE1?b?l?") == "");
assert(f("aa", "^aa?a?a") == "aa");
assert(f("]]]\xE1b", "[^]]") == "\xE1");
assert(f("0alo alo", "%x*") == "0a");
assert(f("alo alo", "%C+") == "alo alo");
print("+");
assert(f1("alo alx 123 b\x00o b\x00o", "(..*) %1") == "b\x00o b\x00o");
assert(f1("axz123= 4= 4 34", "(.+)=(.*)=%2 %1") == "3= 4= 4 3");
assert(f1("=======", "^(=*)=%1$") == "=======");
local u_glb = assert;
u_glb(string.match("==========", "^([=]*)=%1$") == nil);
local u_res = string.char((function ()
   if (val_bb >= v_gv) then
      return;
   end
   return val_bb, u_glb((val_bb + 1), v_gv);
end)(0, 255));
assert(string.len(u_res) == 256);
function strset()
   local u_tab = {s = ""};
   string.gsub(u_res, v_gl, (function ()
      u_tab.s = u_tab.s .. v_gr;
   end));
   return u_tab.s;
end;
assert(string.len(strset("[\xC8-\xD2]")) == 11);
assert(strset("[a-z]") == "abcdefghijklmnopqrstuvwxyz");
assert(strset("[a-z%d]") == strset("[%da-uu-z]"));
assert(strset("[a-]") == "-a");
assert(strset("[^%W]") == strset("[%w]"));
assert(strset("[]%%]") == "%]");
assert(strset("[a%-z]") == "-az");
assert(strset("[%^%[%-a%]%-b]") == "-[]^ab");
assert(strset("%Z") == strset("[\x01-\xFF]"));
assert(strset(".") == strset("[\x01-\xFF%z]"));
print("+");
assert(string.match("alo xyzK", "(%w+)K") == "xyz");
assert(string.match("254 K", "(%d*)K") == "");
assert(string.match("alo ", "(%w*)$") == "");
assert(string.match("alo ", "(%w+)$") == nil);
assert(string.find("(\xE1lo)", "%(\xE1") == 1);
assert(u_cmp);
local func_h, u_cmp = string.match(u_cmp, "(.+(.?)())");
assert(u_cmp);
print(u_cmp);
func_h = assert;
u_cmp = string.gsub("\xFClo \xFClo", "\xFC", "x") == "xlo xlo";
func_h(u_cmp);
func_h = assert;
u_cmp = string.gsub("alo \xFAlo  ", " +$", "") == "alo \xFAlo";
func_h(u_cmp);
func_h = assert;
u_cmp = string.gsub("  alo alo  ", "^%s*(.-)%s*$", "%1") == "alo alo";
func_h(u_cmp);
func_h = assert;
u_cmp = string.gsub("alo  alo  \n 123\n ", "%s+", " ") == "alo alo 123 ";
func_h(u_cmp);
t = "ab\xE7 d";
func_h = assert;
string.gsub(t, "", "@");
func_h(u_cmp);
func_h, u_cmp = string.gsub(u_cmp, "(.)", "%0@", 2);
assert(u_cmp);
func_h = assert;
u_cmp = string.gsub("alo alo", "()[al]", "%1") == "12o 56o";
func_h(u_cmp);
func_h = assert;
u_cmp = string.gsub("abc=xyz", "(%w*)(%p)(%w+)", "%3%2%1-%0") == "xyz=abc-abc=xyz";
func_h(u_cmp);
func_h = assert;
u_cmp = string.gsub("abc", "%w", "%1%0") == "aabbcc";
func_h(u_cmp);
func_h = assert;
u_cmp = string.gsub("abc", "%w+", "%0%1") == "abcabc";
func_h(u_cmp);
func_h = assert;
u_cmp = string.gsub("\xE1\xE9\xED", "$", "\x00\xF3\xFA") == "\xE1\xE9\xED\x00\xF3\xFA";
func_h(u_cmp);
func_h = assert;
u_cmp = string.gsub("", "^", "r") == "r";
func_h(u_cmp);
func_h = assert;
u_cmp = string.gsub("", "$", "r") == "r";
func_h(u_cmp);
print(u_cmp);
func_h = assert;
u_cmp = string.gsub("um (dois) tres (quatro)", "(%(%w+%))", string.upper) == "um (DOIS) tres (QUATRO)";
func_h(u_cmp);
u_cmp("a=roberto,roberto=a", "(%w+)=(%w%w*)", (function ()
   rawset(_G, v_gf, v_gh);
end));
u_cmp(_G.a == "roberto");
function f()
   return string.gsub(v_gb, ".", v_gd);
end;
func_h = assert;
u_cmp = string.gsub("trocar tudo em |teste|b| \xE9 |beleza|al|", "|([^|]*)|([^|]*)|", f) == "trocar tudo em bbbbb \xE9 alalalalalal";
func_h(u_cmp);
func_h = (function ()
   local c_res_s = loadstring(v_fv)();
   return if (c_res_s) then c_res_s else "";
end);
u_cmp(string.gsub("alo $a=1$ novamente $return a$", "$([^$]*)%$", func_h) == "alo  novamente 1");
x = u_cmp("$x=string.gsub(\'alo\', \'.\', string.upper)$ assim vai para $return x$", "$([^$]*)%$", func_h);
u_cmp(x == " assim vai para ALO");
t = {};
s = "a alo jose  joao";
r = u_cmp(s, "()(%w+)()", (function ()
   assert(string.len(v_fh) == (val_n - val_l));
   t[val_l] = val_n - val_l;
end));
u_cmp(s == r);
function isbalanced()
   return string.find(string.gsub(v_ff, "%b()", ""), "[()]") == nil;
end;
u_cmp(isbalanced("(9 ((8))(\x00) 7) \x00\x00 a b ()(c)() a"));
u_cmp(not isbalanced("(9 ((8) 7) a b (\x00 c) a"));
u_cmp(string.gsub("alo \'oi\' alo", "%b\'\'", "\"") == "alo \" alo");
u_cmp = {
   "apple", 
   "orange", 
   "lime", 
   n = 0};
assert(string.gsub("x and x and x", "x", (function ()
   u_cmp.n = u_cmp.n + 1;
   return u_cmp[u_cmp.n];
end)) == "apple and orange and lime");
u_cmp = {n = 0};
string.gsub("first second word", "%w%w*", (function ()
   u_cmp.n = u_cmp.n + 1;
   u_cmp[u_cmp.n] = v_ez;
end));
assert(u_cmp[1] == "first");
assert(string.gsub("first second word", "%w+", (function ()
   u_cmp.n = u_cmp.n + 1;
   u_cmp[u_cmp.n] = v_et;
end), 2) == "first second word");
assert(({n = 0})[1] == "first");
assert(not pcall(string.gsub, "alo", "(.", print));
assert(not pcall(string.gsub, "alo", ".)", print));
assert(not pcall(string.gsub, "alo", "(.", {}));
assert(not pcall(string.gsub, "alo", "(.)", "%2"));
assert(not pcall(string.gsub, "alo", "(%1)", "a"));
assert(not pcall(string.gsub, "alo", "(%0)", "a"));
local c_res_j = string.rep("a", 300000);
assert(string.find(c_res_j, "^a*.?$"));
assert(not string.find(c_res_j, "^a*.?b$"));
assert(string.find(c_res_j, "^a-.?$"));
function rev()
   return string.gsub(v_ej, "(.)(.+)", (function ()
      return rev(v_el) .. v_en;
   end));
end;
local c_res_k = string.rep("012345", 10);
assert(rev(rev(c_res_k)) == c_res_k);
assert(string.gsub("alo alo", ".", {}) == "alo alo");
assert(string.gsub("alo alo", "(.)", {a = "AA", l = ""}) == "AAo AAo");
assert(string.gsub("alo alo", "(.).", {a = "AA", l = "K"}) == "AAo AAo");
assert(string.gsub("alo alo", "((.)(.?))", {al = "AA", o = false}) == "AAo AAo");
assert(string.gsub("alo alo", "().", {2, 5, 6}) == "256 alo");
setmetatable(u_cmp, {__index = (function ()
   return string.upper(v_eh);
end)});
assert(string.gsub("a alo b hi", "%w%w+", u_cmp) == "a ALO b HI");
local val = 0;
for v in string.gmatch("abcde", "()") do
   assert(v == (val + 1));
   val = v;
end
