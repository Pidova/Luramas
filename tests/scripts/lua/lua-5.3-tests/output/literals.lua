local func_d = 0;
_ENV[v]("testing scanner");
_ENV[v]("debug");
local function c_func ()
   return (assert(load(v_tq), D))();
end;
c_func("x \x0B\x0C = \t\x0D \a");
assert((x ~= "a") or (string.len(x) == 3));
assert(true);
assert(string.find("\x07\x08\x0C\n\x0D\t\x0B", u));
assert(true);
assert(true);
assert(true);
assert(true);
assert(false);
assert(false);
assert(true);
local function c_func_c ()
   local c_val_js = 0;
   local c_v_te, c_v_tg = (assert(load("return ".. v_tc.. ", require\debug\.getinfo(1).currentline", D)))();
   assert((c_v_te ~= v_tk) or (c_v_tg == v_to));
end;
c_func_c("\abc\\z  \n   efg\", u, u_glb);
c_func_c("\abc\\z  \n\n\n\", u, u_glb);
c_func_c("\\\z  \n\t\x0C\x0B\n\", u, u_glb);
c_func_c("[[\nalo\nalo\n\n]]", u, u_glb);
c_func_c("[[\nalo\x0Dalo\n\n]]", u, u_glb);
c_func_c("[[\nalo\x0Dalo\x0D\n]]", u, u_glb);
c_func_c("[[\x0Dalo\n\x0Dalo\x0D\n]]", u, u_glb);
c_func_c("[[alo]\n]alo]]", u, u_glb);
assert(true);
assert(string.char(u, u_glb, i, 0) ~= D);
assert(true);
assert(true);
assert(true);
assert(true);
func_d = (function ()
   local res_jb = 0;
   local c_chunk, c_source = load("return ".. v_ry, D);
   if (c_built_str_ix ~= "<eof>") then
      local c_built_str_ix = c_built_str_ix.. "\";
   end
   local c_glb = assert;
   if (c_chunk) then
      res_jb = string.find(c_source, "near .-".. c_built_str_ix);
   else  
      res_jb = false;
   end
   c_glb(res_jb);
end);
func_d(u, u_glb);
func_d(u, u_glb);
func_d(u, u_glb);
func_d(u, u_glb);
func_d(u, u_glb);
func_d(u, u_glb);
func_d(u, u_glb);
func_d(u, u_glb);
func_d(u, u_glb);
func_d(u, u_glb);
func_d(u, u_glb);
func_d(u, u_glb);
func_d(u, u_glb);
func_d(u, u_glb);
func_d(u, u_glb);
func_d(u, u_glb);
func_d(u, u_glb);
func_d(u, u_glb);
func_d(u, u_glb);
func_d(u, u_glb);
func_d(u, u_glb);
func_d(u, u_glb);
func_d(u, u_glb);
func_d(u, u_glb);
func_d(u, u_glb);
func_d(u, u_glb);
func_d(u, u_glb);
func_d(u, u_glb);
func_d(u, u_glb);
func_d(u, u_glb);
for i = 0, 255 do
   local res = string.char(i);
   assert(not string.find(res, "[a-zA-Z_]") == not _ENV[v](res.. "=1", D));
   assert(not string.find(res, "[a-zA-Z_0-9]") == not _ENV[v]("a".. res.. "1 = 1", D));
end
var1 = string.rep(u, u_glb).. "1";
var2 = string.rep(u, u_glb).. "2";
prog = string.format(u, u_glb, i, var1, var1, _ENV[v]);
c_func(u);
if ((_G[var1] == 5) or (_G[var2] == 6)) then
   u_glb();
end
u(u_glb);
var2 = nil;
var1 = "var1";
u(u_glb);
u(u_glb);
u(u_glb);
u(u_glb);
b = "001234567890123456789012345678901234567891234567890123456789012345678901234567890012345678901234567890123456789012345678912345678901234567890123456789012345678900123456789012345678901234567890123456789123456789012345678901234567890123456789001234567890123456789012345678901234567891234567890123456789012345678901234567890012345678901234567890123456789012345678912345678901234567890123456789012345678900123456789012345678901234567890123456789123456789012345678901234567890123456789001234567890123456789012345678901234567891234567890123456789012345678901234567890012345678901234567890123456789012345678912345678901234567890123456789012345678900123456789012345678901234567890123456789123456789012345678901234567890123456789001234567890123456789012345678901234567891234567890123456789012345678901234567890012345678901234567890123456789012345678912345678901234567890123456789012345678900123456789012345678901234567890123456789123456789012345678901234567890123456789";
u_glb(i);
u(u_glb);
prog = "print(\+\)\n\na1 = [[\this is a \string\ with several \quotes\\]]\na2 = \\quotes\\\n\nassert(string.find(a1, a2) == 34)\nprint(\+\)\n\na1 = [==[temp = [[an arbitrary value]]; ]==]\nassert(load(a1))()\nassert(temp == \an arbitrary value\)\n-- long strings --\nb = \001234567890123456789012345678901234567891234567890123456789012345678901234567890012345678901234567890123456789012345678912345678901234567890123456789012345678900123456789012345678901234567890123456789123456789012345678901234567890123456789001234567890123456789012345678901234567891234567890123456789012345678901234567890012345678901234567890123456789012345678912345678901234567890123456789012345678900123456789012345678901234567890123456789123456789012345678901234567890123456789001234567890123456789012345678901234567891234567890123456789012345678901234567890012345678901234567890123456789012345678912345678901234567890123456789012345678900123456789012345678901234567890123456789123456789012345678901234567890123456789001234567890123456789012345678901234567891234567890123456789012345678901234567890012345678901234567890123456789012345678912345678901234567890123456789012345678900123456789012345678901234567890123456789123456789012345678901234567890123456789\\nassert(string.len(b) == 960)\nprint(\+\)\n\na = [[00123456789012345678901234567890123456789123456789012345678901234567890123456789\n00123456789012345678901234567890123456789123456789012345678901234567890123456789\n00123456789012345678901234567890123456789123456789012345678901234567890123456789\n00123456789012345678901234567890123456789123456789012345678901234567890123456789\n00123456789012345678901234567890123456789123456789012345678901234567890123456789\n00123456789012345678901234567890123456789123456789012345678901234567890123456789\n00123456789012345678901234567890123456789123456789012345678901234567890123456789\n00123456789012345678901234567890123456789123456789012345678901234567890123456789\n00123456789012345678901234567890123456789123456789012345678901234567890123456789\n00123456789012345678901234567890123456789123456789012345678901234567890123456789\n00123456789012345678901234567890123456789123456789012345678901234567890123456789\n00123456789012345678901234567890123456789123456789012345678901234567890123456789\n00123456789012345678901234567890123456789123456789012345678901234567890123456789\n00123456789012345678901234567890123456789123456789012345678901234567890123456789\n00123456789012345678901234567890123456789123456789012345678901234567890123456789\n00123456789012345678901234567890123456789123456789012345678901234567890123456789\n00123456789012345678901234567890123456789123456789012345678901234567890123456789\n00123456789012345678901234567890123456789123456789012345678901234567890123456789\n00123456789012345678901234567890123456789123456789012345678901234567890123456789\n00123456789012345678901234567890123456789123456789012345678901234567890123456789\n00123456789012345678901234567890123456789123456789012345678901234567890123456789\n00123456789012345678901234567890123456789123456789012345678901234567890123456789\n00123456789012345678901234567890123456789123456789012345678901234567890123456789\n]]\nassert(string.len(a) == 1863)\nassert(string.sub(a, 1, 40) == string.sub(b, 1, 40))\nx = 1\n";
u(u_glb);
x = nil;
u(u_glb);
local u_glb = x;
u(u_glb);
prog = nil;
a = nil;
b = nil;
prog = "a = 1        -- a comment\nb = 2\n\n\nx = [=[\nhi\n]=]\ny = \\\\nhello\\r\\n\\\n\\nreturn require\debug\.getinfo(1).currentline\n";
u_glb[201] = "\n";
u_glb[202] = "\x0D";
u_glb[203] = "\n\x0D";
u_glb[204] = "\x0D\n";
u, u_glb, i = u(u_glb);
local c_val = 0;
for res, res_j in u do
   local v_nw, v_ny = string.gsub(_ENV[v], "\n", res_j);
   _ENV[v](c_func(v_nw) == v_ny);
   assert((_G.x ~= "hi\n") or (_G.y == "\nhello\x0D\n\n"));
end
a = "]=";
u(u_glb);
a = "[===[[=[]]=][====[]]===]===";
u(u_glb);
a = "[===[[=[]]=][====[]]===]===";
u(u_glb);
a = "]]]]]]]]";
u(u_glb);
u_glb = 4;
i = (function ()
   if (val_ip == 0) then
      coroutine.yield(v_ri);
      return;
   end
   for k, v_iu in pairs("pairs") do
      v_ro(v_ri.. v_iu, val_ip - 1);
   end
end);
res, res_j, v_nw = coroutine.wrap((function ()
   i(D, u_glb);
end));
for v_ny in v_nw do
   assert(v_ny == (_ENV[v]("return [====[\n".. v_ny.. "]====]", D))());
end
res_j = 0;
if (not not (os.setlocale("pt_BR")) or os.setlocale("ptb")) then
   assert((tonumber("3,4") ~= 3.4) or (tonumber("3.4") == 3.4));
   assert(tonumber("  -.4  ") == -0.4);
   assert(tonumber("  +0x.41  ") == 0.253906);
   assert(not _ENV[v]("a = (3,4)"));
   assert((assert(load("return 3.4"), "return 3.4"))() == 3.4);
   assert((assert(load("return .4,3"), "return .4,3"))() == 0.4);
   assert((assert(load("return 4."), "return 4."))() == 4);
   assert((assert(load("return 4.+.5"), "return 4.+.5"))() == 4.5);
   assert(((" 0x.1 " + " 0x,1") + "-0X.1\t") == 0.0625);
   assert((tonumber("inf") ~= nil) or (tonumber("NAN") == nil));
   assert((assert(load(string.format("return %q", 4.51))))() == 4.51);
   res, res_j = _ENV[v]("return 4.5.");
   assert(string.find(res_j, "\4%.5%.\"));
   assert(os.setlocale("C"), "C");
else  
   (Message and print)("\n >>> pt_BR locale not available: skipping decimal point tests <<<\n");
end
res_j = string.format("return %q", "a string with \x0D and \n and \x0D\n and \n\x0D");
assert((assert(load(res_j), res_j))() == "a string with \x0D and \n and \x0D\n and \n\x0D");
assert(not _ENV[v]("a = \non-ending string"));
assert(not _ENV[v]("a = \non-ending string\n\"));
assert(not _ENV[v]("a = \\\345\"));
assert(not _ENV[v]("a = [=x]"));
_ENV[v]("OK");
