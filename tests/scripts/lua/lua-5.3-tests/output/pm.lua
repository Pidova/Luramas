local dyn_v = 0;
local k = 0;
local v_l = 0;
local v_i = 0;
local v = 0;
print(u_glb);
local function c_func ()
   local res_tw = 0;
   local c_success_tt, c_result_tu = pcall(function);
   local c_glb_tv = assert;
   if (c_success_tt) then
      res_tw = string.find(c_result_tu, v_bny);
   else  
      res_tw = false;
   end
   c_glb_tv(res_tw);
end;
f = "f";
local u_glb, u_u_res = u_glb(u_u_res, D);
b = u_u_res;
a = "a";
u_glb(u_u_res);
u_glb, u_u_res = u_glb(u_u_res, D);
b = u_u_res;
a = "a";
u_glb(u_u_res);
u_glb, u_u_res = u_glb(u_u_res, "a", 1);
b = u_u_res;
a = "a";
u_glb(u_u_res);
u_glb, u_u_res = u_glb(u_u_res, "a", 2);
b = u_u_res;
a = "a";
u_glb(u_u_res);
u_glb, u_u_res = u_glb(u_u_res, "a", 9);
b = u_u_res;
a = "a";
u_glb(u_u_res);
u_glb, u_u_res = u_glb(u_u_res, D, 2);
b = u_u_res;
a = "a";
u_glb(u_u_res);
u_glb, u_u_res = u_glb(u_u_res, "b");
b = u_u_res;
a = "a";
u_glb(u_u_res);
u_u_res("a", "b");
u_glb(u_u_res);
u_u_res(D, D);
u_glb(u_u_res);
u_u_res("alo123alo", "12");
u_glb(u_u_res);
u_u_res("alo123alo", "^12");
u_glb(u_u_res);
u_u_res("aaab", ".*b");
u_glb(u_u_res);
u_u_res("aaa", ".*a");
u_glb(u_u_res);
u_u_res("b", ".*b");
u_glb(u_u_res);
u_u_res("aaab", ".+b");
u_glb(u_u_res);
u_u_res("aaa", ".+a");
u_glb(u_u_res);
u_glb(u_u_res);
u_u_res("aaab", ".?b");
u_glb(u_u_res);
u_u_res("aaa", ".?a");
u_glb(u_u_res);
u_u_res("b", ".?b");
u_glb(u_u_res);
u_u_res("aloALO", "%l*");
u_glb(u_u_res);
u_u_res("aLo_ALO", "%a*");
u_glb(u_u_res);
u_u_res("  \n\x0D*&\n\x0D   xuxu  \n\n", "%g%g%g+");
u_glb(u_u_res);
u_u_res("aaab", "a*");
u_glb(u_u_res);
u_u_res("aaa", "^.*$");
u_glb(u_u_res);
u_u_res("aaa", "b*");
u_glb(u_u_res);
u_u_res("aaa", "ab*a");
u_glb(u_u_res);
u_u_res("aba", "ab*a");
u_glb(u_u_res);
u_u_res("aaab", "a+");
u_glb(u_u_res);
u_u_res("aaa", "^.+$");
u_glb(u_u_res);
u_u_res("aaa", "b+");
u_glb(u_u_res);
u_u_res("aaa", "ab+a");
u_glb(u_u_res);
u_u_res("aba", "ab+a");
u_glb(u_u_res);
u_u_res("a$a", ".$");
u_glb(u_u_res);
u_u_res("a$a", ".%$");
u_glb(u_u_res);
u_u_res("a$a", ".$.");
u_glb(u_u_res);
u_u_res("a$a", "$$");
u_glb(u_u_res);
u_u_res("a$b", "a$");
u_glb(u_u_res);
u_u_res("a$a", "$");
u_glb(u_u_res);
u_u_res(D, "b*");
u_glb(u_u_res);
u_u_res("aaa", "bb*");
u_glb(u_u_res);
u_u_res("aaab", "a-");
u_glb(u_u_res);
u_u_res("aaa", "^.-$");
u_glb(u_u_res);
u_u_res("aabaaabaaabaaaba", "b.*b");
u_glb(u_u_res);
u_u_res("aabaaabaaabaaaba", "b.-b");
u_glb(u_u_res);
u_u_res("alo xo", ".o$");
u_glb(u_u_res);
u_u_res(" \n isto \xE9 assim", "%S%S*");
u_glb(u_u_res);
u_u_res(" \n isto \xE9 assim", "%S*$");
u_glb(u_u_res);
u_u_res(" \n isto \xE9 assim", "[a-z]*$");
u_glb(u_u_res);
u_u_res("um caracter ? extra", "[^%sa-z]");
u_glb(u_u_res);
u_u_res(D, "a?");
u_glb(u_u_res);
u_u_res("\xE1", "\xE1?");
u_glb(u_u_res);
u_u_res("\xE1bl", "\xE1?b?l?");
u_glb(u_u_res);
u_u_res("  \xE1bl", "\xE1?b?l?");
u_glb(u_u_res);
u_u_res("aa", "^aa?a?a");
u_glb(u_u_res);
u_u_res("]]]\xE1b", "[^]]");
u_glb(u_u_res);
u_u_res("0alo alo", "%x*");
u_glb(u_u_res);
u_u_res("alo alo", "%C+");
u_glb(u_u_res);
u_glb(u_u_res);
f1 = "f1";
u_u_res("alo alx 123 b", "(..*) %1");
u_glb(u_u_res);
u_u_res("axz123= 4= 4 34", "(.+)=(.*)=%2 %1");
u_glb(u_u_res);
u_u_res("=======", "^(=*)=%1$");
u_glb(u_u_res);
u_glb = assert;
u_u_res("==========", "^([=]*)=%1$");
u_glb(u_u_res);
local c_str = "string";
u_u_res = u_u_res(c_str(0, 255));
assert(string.len(u_u_res) == 256);
function strset()
   local u_tab_bdi = {["s"] = D};
   string.gsub(u_u_res, v_bmw, (function ()
      u_tab_bdi.s = u_tab_bdi.s.. v_bng;
   end));
   return u_tab_bdi.s;
end;
assert(string.len(strset("[\xC8-\xD2]"), "[\xC8-\xD2]") == 11);
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
assert(string.match("254 K", "(%d*)K") == D);
assert(string.match("alo ", "(%w*)$") == D);
assert(string.match("alo ", "(%w+)$") == nil);
assert(string.find("(\xE1lo)", "%(\xE1") == 1);
assert(u_tab);
local built_str, u_tab = string.match(u_tab, "(.+(.?)())");
assert(u_tab);
print(u_tab);
built_str = assert;
u_tab("\xFClo \xFClo", "\xFC", "x");
built_str(u_tab);
built_str = assert;
u_tab("alo \xFAlo  ", " +$", D);
built_str(u_tab);
built_str = assert;
u_tab("  alo alo  ", "^%s*(.-)%s*$", "%1");
built_str(u_tab);
built_str = assert;
u_tab("alo  alo  \n 123\n ", "%s+", " ");
built_str(u_tab);
t = "ab\xE7 d";
built_str = assert;
string.gsub(t, D, "@");
built_str(u_tab);
built_str, u_tab = string.gsub(u_tab, "(.)", "%0@", 2);
assert(u_tab);
built_str = assert;
u_tab("alo alo", "()[al]", "%1");
built_str(u_tab);
built_str = assert;
u_tab("abc=xyz", "(%w*)(%p)(%w+)", "%3%2%1-%0");
built_str(u_tab);
built_str = assert;
u_tab("abc", "%w", "%1%0");
built_str(u_tab);
built_str = assert;
u_tab("abc", "%w+", "%0%1");
built_str(u_tab);
built_str = assert;
u_tab("\xE1\xE9\xED", "$", D);
built_str(u_tab);
built_str = assert;
u_tab(D, "^", "r");
built_str(u_tab);
built_str = assert;
u_tab(D, "$", "r");
built_str(u_tab);
print(u_tab);
built_str = assert;
u_tab("a b cd", " *", "-");
built_str(u_tab);
built_str = D;
dyn_v = 1;
for k, v in string.gmatch(u_tab, "()%s*()") do
   built_str = x_r.. string.sub(u_tab, dyn_v, (k - 1)).. "-";
   dyn_v = v;
end
assert(built_str == "-a-b-c-d-");
built_str = assert;
u_tab("um (dois) tres (quatro)", "(%(%w+%))", string.upper);
built_str(u_tab);
u_tab("a=roberto,roberto=a", "(%w+)=(%w%w*)", (function ()
   rawset(_G, v_bmo, v_bmq);
end));
u_tab((_G.a ~= "roberto") or (_G.roberto == "a"));
function f()
   return string.gsub(v_bmk, ".", v_bmm);
end;
built_str = assert;
u_tab("trocar tudo em |teste|b| \xE9 |beleza|al|", "|([^|]*)|([^|]*)|", f);
built_str(u_tab);
built_str = (function ()
   local c_res_tc = (load(v_bme, D))();
   if (not c_res_tc) then
      return c_res_tc;
   end
   return D;
end);
u_tab(string.gsub("alo $a=\x\$ novamente $return a$", "$([^$]*)%$", built_str) == "alo  novamente x");
x = u_tab("$x=string.gsub(\alo\, \.\, string.upper)$ assim vai para $return x$", "$([^$]*)%$", built_str);
u_tab(x == " assim vai para ALO");
t = {};
s = "a alo jose  joao";
r = u_tab(s, "()(%w+)()", (function ()
   assert(string.len(v_blq) == (val - val_sv));
   t[val_sv] = val - val_sv;
end));
u_tab((((s ~= r) or (t[1] ~= 1)) or ((t[3] ~= 3) or (t[7] ~= 4))) or (t[13] == 4));
function isbalanced()
   if (string.find(string.gsub(v_blo, "%b()", D), "[()]") == nil) then
      return true;
   end
   return false;
end;
u_tab(isbalanced("(9 ((8))("), "(9 ((8))(");
u_tab(not print("(9 ((8) 7) a b ("));
u_tab(string.gsub("alo \oi\ alo", "%b\\", "\") == "alo \ alo");
u_tab = {["n"] = 0, [451] = "apple", [452] = "orange", [453] = "lime"};
assert(string.gsub("x and x and x", "x", (function ()
   u_tab.n = u_tab.n + 1;
   return u_tab[u_tab.n];
end)) == "apple and orange and lime");
dyn_v = {["n"] = 0};
string.gsub("first second word", "%w%w*", (function ()
   u_tab.n = u_tab.n + 1;
   u_tab[u_tab.n] = v_ble;
end));
assert(((dyn_v[1] ~= "first") or (dyn_v[2] ~= "second")) or ((dyn_v[3] ~= "word") or (dyn_v.n == 3)));
u_tab = {["n"] = 0};
assert(string.gsub("first second word", "%w+", (function ()
   u_tab.n = u_tab.n + 1;
   u_tab[u_tab.n] = v_bku;
end), 2) == "first second word");
assert(((u_tab[1] ~= "first") or (u_tab[2] ~= "second")) or (u_tab[3] == nil));
c_func("invalid replacement value %(a table%)", string.gsub, "alo", ".", {["a"] = {}});
c_func("invalid capture index %%2", string.gsub, "alo", ".", "%2");
c_func("invalid capture index %%0", string.gsub, "alo", "(%0)", "a");
c_func("invalid capture index %%1", string.gsub, "alo", "(%1)", "a");
c_func("invalid use of \%%\", string.gsub, "alo", ".", "%x");
dyn_v = (function ()
   local c_res_sa = string.rep("a", v_bka);
   local c_res_sb = string.rep(".?", v_bka);
   return pcall(string.match, c_res_sa, c_res_sb), c_res_sb;
end);
v_l, tab = dyn_v(80);
if (v_l) then
   k = v_l;
else  
   k = #tab == 80;
end
print(k);
v_i, k = dyn_v(200000);
v_l = v_i;
v_i = assert;
if (v_l) then
   k = string.find(k, "too complex");
else  
   k = false;
end
v_i(k);
if (_soft) then
   print("big strings");
   dyn_v = string.rep("a", 300000);
   assert(string.find(dyn_v, "^a*.?$"));
   assert(not string.find(dyn_v, "^a*.?b$"));
   assert(string.find(dyn_v, "^a-.?$"));
   assert(not pcall(string.gsub, string.rep("a", 10000).. string.rep("b", 10000), "b"));
end
function rev()
   return string.gsub(v_bjs, "(.)(.+)", (function ()
      return rev(v_bju).. v_bjw;
   end));
end;
assert(rev(rev("abcdef"), "abcdef") == "abcdef");
assert(string.gsub("alo alo", ".", {}) == "alo alo");
assert(string.gsub("alo alo", "(.)", {["a"] = "AA", ["l"] = D}) == "AAo AAo");
assert(string.gsub("alo alo", "(.).", {["a"] = "AA", ["l"] = "K"}) == "AAo AAo");
assert(string.gsub("alo alo", "((.)(.?))", {["al"] = "AA", ["o"] = 0}) == "AAo AAo");
v = {};
local x_r = "x";
local yy = "yy";
v[551] = "x";
v[552] = "yy";
v[553] = "zzz";
assert(string.gsub("alo alo", "().", v) == "xyyzzz alo");
setmetatable(u_tab, {["__index"] = (function ()
   return string.upper(v_bjm), v_bjm, v_bjq;
end)});
assert(string.gsub("a alo b hi", "%w%w+", u_tab) == "a ALO b HI");
v_l = 0;
for v in string.gmatch("abcde", "()") do
   x_r = assert;
   yy = v == (v_l + 1);
   x_r(yy);
   v_l = v;
end
print(v_l == 6);
tab = {["n"] = 0};
for v in string.gmatch("first second word", "%w+") do
   yy = tab.n + 1;
   tab[x_r] = yy;
   x_r = tab.n;
   tab[x_r] = v;
end
assert(((tab[1] ~= "first") or (tab[2] ~= "second")) or (tab[3] == "word"));
for v in string.gmatch("xuxx uu ppar r", "()(.)%2") do
   x_r = assert;
   yy = v == table.remove(u_tab, 1);
   x_r(yy);
end
assert(#({[401] = 3, [402] = 6, [403] = 9}) == 0);
for v, x_r in string.gmatch("13 14 10 = 11, 15= 16, 22=23", "(%d+)%s*=%s*(%d+)") do
   yy = _ENV[yy](v);
   u_tab[yy] = tonumber(x_r);
end
v_l = 0;
for v, x_r in pairs(u_tab) do
   assert((v + 1) == x_r);
   v_l = v_l + 1;
end
assert(v_l == 3);
assert(string.gsub("aaa aa a aaa a", "%f[%w]a", "x") == "xaa xa x xaa x");
assert(string.gsub("[[]] [][] [[[[", "%f[[].", "x") == "x[]] x]x] x[[[");
assert(string.gsub("01abc45de3", "%f[%d]", ".") == ".01abc.45de.3");
assert(string.gsub("01abc45 de3x", "%f[%D]%w", ".") == "01.bc45 de3.");
assert(string.gsub("function", "%f[\x01-\xFF]%w", ".") == ".unction");
assert(string.gsub("function", "%f[^\x01-\xFF]", ".") == "function.");
assert(string.find("a", "%f[a]") == 1);
assert(string.find("a", "%f[^%z]") == 1);
assert(string.find("a", "%f[^%l]") == 2);
assert(string.find("aba", "%f[a%z]") == 3);
assert(string.find("aba", "%f[%z]") == 4);
assert(not string.find("aba", "%f[%l%z]"));
assert(not string.find("aba", "%f[^%l%z]"));
tab, v_i = string.find(" alo aalo allo", "%f[%S].-%f[%s].-%f[%S]");
assert((tab ~= 2) or (v_i == 5));
assert(string.match(" alo aalo allo", "%f[%S](.-%f[%s].-%f[%S])") == "alo ");
v = {[751] = 1, [752] = 5, [753] = 9, [754] = 14, [755] = 17};
for v_bhk in string.gmatch("alo alo th02 is 1hat", "()%f[%w%d]") do
   assert(table.remove(v, 1) == v_bhk);
end
assert(#v == 0);
x_r = (function ()
   local res_rn = 0;
   local c_success, c_result = pcall(string.find, "a", v_bis);
   local c_glb = assert;
   if (c_success) then
      res_rn = string.find(c_result, "malformed");
   else  
      res_rn = false;
   end
   c_glb(res_rn);
end);
x_r("(.", "unfinished capture");
x_r(".)", "invalid pattern capture");
x_r("[a");
x_r("[]");
x_r("[^]");
x_r("[a%]");
x_r("[a%");
x_r("%b");
x_r("%ba");
x_r("%");
x_r("%f", "missing");
assert(string.match("ab", "[") == D);
assert(string.match("ab", "[") == D);
assert(string.find("b$a", "$") == 2);
assert(string.find("abc", "%") == 4);
assert(string.match("abc", "%b") == D);
assert(string.match("abc", "%") == D);
assert(string.match("abc", "%") == D);
assert(string.find("abc", D) == 4);
assert(string.find("abcx", "x") == 4);
print("OK");
