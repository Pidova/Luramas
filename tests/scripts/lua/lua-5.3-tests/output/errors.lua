local tab = 0;
local success = 0;
local u_func_jw_i = 0;
local i_o = 0;
local result = 0;
local success_v = 0;
u_u_res("testing errors");
local u_u_res = u_u_res("debug");
local cmp = getmetatable(_ENV[v]) and {};
cmp.__index = nil;
local function u_func ()
   local res_km = 0;
   local c_success_kj, c_result_kk = pcall(function);
   local c_glb_kl = assert;
   if (c_success_kj) then
      res_km = string.find(c_result_kk, v_bis);
   else  
      res_km = false;
   end
   c_glb_kl(res_km);
end;
local function u_func_jw ()
   local c_chunk, c_source = load(v_bhi);
   if (c_chunk == nil) then
      return c_source;
   end
   local c_success_ka, c_result_kb = pcall(c_chunk);
   if (not c_success_ka) then
      return false;
   end
   return c_result_kb;
end;
local function u_func_ke ()
   assert(string.find(u_func_jw(v_bhe), v_bhg, 1, true));
end;
local function c_func ()
   local v_bgi = 0;
   local c_u_func_jw_jo = u_func_jw(v_bgo);
   if (not string.find(0, "^<%a") or not (string.find(0, "^char%("))) then
      v_bgi = ""\0"\";
   end
   assert(string.find(c_u_func_jw_jo, string.format("^%%[string \.*\%%]:%d: .- near %s$", v_bgu, string.gsub(v_bgi, "(%p)", "%%%1"))));
   assert(string.find(c_u_func_jw_jo, c_u_func_jw_jo, 1, true));
end;
assert(("assert")(u_dyn_u_func_ke) == "hi");
assert(("assert")(u_dyn_u_func_ke) == nil);
_ENV[v](u_func_jw(u_dyn_u_func_ke), u_dyn_u_func_ke);
_ENV[v](u_func_jw(u_dyn_u_func_ke), u_dyn_u_func_ke);
local c_glb = _ENV;
if (u_func_jw(u_dyn_u_func_ke)) then
   u_func_jw_i = u_func_jw(u_dyn_u_func_ke);
else  
   u_func_jw_i = false;
end
c_glb[v](u_func_jw_i);
_ENV[v](u_func_jw(u_dyn_u_func_ke), u_dyn_u_func_ke);
_ENV[v](u_func_jw(u_dyn_u_func_ke), u_dyn_u_func_ke);
_ENV[v](u_func_jw(u_dyn_u_func_ke), u_dyn_u_func_ke);
_ENV[v](u_func_jw(u_dyn_u_func_ke), u_dyn_u_func_ke);
_ENV[v](u_func_jw(u_dyn_u_func_ke), u_dyn_u_func_ke);
_ENV[v](u_func_jw(u_dyn_u_func_ke), u_dyn_u_func_ke);
_ENV[v](u_func_jw(u_dyn_u_func_ke), u_dyn_u_func_ke);
_ENV[v](u_func_jw(u_dyn_u_func_ke), u_dyn_u_func_ke);
c_func("  local a = {4\n\n", u_dyn_u_func_ke, "<eof>", 3);
u_func_ke("a = {} + 1", u_dyn_u_func_ke);
u_func_ke("a = {} | 1", u_dyn_u_func_ke);
u_func_ke("a = {} < 1", u_dyn_u_func_ke);
u_func_ke("a = {} <= 1", u_dyn_u_func_ke);
u_func_ke("a=1; bbbb=2; a=math.sin(3)+bbbb(3)", u_dyn_u_func_ke);
u_func_ke("a={}; do local a=1 end a:bbbb(3)", u_dyn_u_func_ke);
u_func_ke("local a={}; a.bbbb(3)", u_dyn_u_func_ke);
local u_func_jw_i_h = assert;
u_func_jw_i = string;
u_dyn_u_func_ke("a={13}; local bbbb=1; a[bbbb](3)");
u_func_jw_i_h(not u_func_jw_i.find(u_dyn_u_func_ke, "\bbbb\"));
u_func_ke("a={13}; local bbbb=1; a[bbbb](3)", u_dyn_u_func_ke);
u_func_ke("a=(1)..{}", u_dyn_u_func_ke);
u_func_ke("a = #print", u_dyn_u_func_ke);
u_func_ke("a = #3", u_dyn_u_func_ke);
aaa = nil;
u_func_ke("aaa.bbb:ddd(9)", u_dyn_u_func_ke);
u_func_ke("local aaa={bbb=1}; aaa.bbb:ddd(9)", u_dyn_u_func_ke);
u_func_ke("local aaa={bbb={}}; aaa.bbb:ddd(9)", u_dyn_u_func_ke);
u_func_ke("local a,b,c; (function () a = b+1 end)()", u_dyn_u_func_ke);
_ENV[v](not u_func_jw(u_dyn_u_func_ke));
u_func_ke("local a,b,cc; (function () a = cc[1] end)()", u_dyn_u_func_ke);
u_func_ke("local a,b,cc; (function () a.x = 1 end)()", u_dyn_u_func_ke);
u_func_ke("local _ENV = {x={}}; a = a + 1", u_dyn_u_func_ke);
u_func_ke("b=1; local aaa=\a\; x=aaa+b", u_dyn_u_func_ke);
u_func_ke("aaa={}; x=3/aaa", u_dyn_u_func_ke);
u_func_ke("aaa=\2\; b=nil;x=aaa*b", u_dyn_u_func_ke);
u_func_ke("aaa={}; x=-aaa", u_dyn_u_func_ke);
u_func_ke("a=1; local a,bbbb=2,3; a = math.sin(1) and bbbb(3)", u_dyn_u_func_ke);
u_func_ke("a=1; local a,bbbb=2,3; a = bbbb(1) or a(3)", u_dyn_u_func_ke);
u_func_ke("local a,b,c,f = 1,1,1; f((a and b) or c)", u_dyn_u_func_ke);
u_func_ke("local a,b,c = 1,1,1; ((a and b) or c)()", u_dyn_u_func_ke);
u_func_jw_i_h = assert;
u_func_jw_i = string;
u_dyn_u_func_ke("aaa={}; x=(aaa or aaa)+(aaa and aaa)");
u_func_jw_i_h(not u_func_jw_i.find(u_dyn_u_func_ke, "\aaa\"));
u_func_jw_i_h = assert;
u_func_jw_i = string;
u_dyn_u_func_ke("aaa={}; (aaa or aaa)()");
u_func_jw_i_h(not u_func_jw_i.find(u_dyn_u_func_ke, "\aaa\"));
u_func_ke("print(print < 10)", u_dyn_u_func_ke);
u_func_ke("print(print < print)", u_dyn_u_func_ke);
u_func_ke("print(\10\ < 10)", u_dyn_u_func_ke);
u_func_ke("print(10 < \23\)", u_dyn_u_func_ke);
u_func_ke("local a = 2.0^100; x = a << 2", u_dyn_u_func_ke);
u_func_ke("local a = 1 >> 2.0^100", u_dyn_u_func_ke);
u_func_ke("local a = \10\ << 2.0^100", u_dyn_u_func_ke);
u_func_ke("local a = 2.0^100 & 1", u_dyn_u_func_ke);
u_func_ke("local a = 2.0^100 & \1\", u_dyn_u_func_ke);
u_func_ke("local a = 2.0 | 1e40", u_dyn_u_func_ke);
u_func_ke("local a = 2e100 ~ 1", u_dyn_u_func_ke);
u_func_ke("string.sub(\a\, 2.0^100)", u_dyn_u_func_ke);
u_func_ke("string.rep(\a\, 3.3)", u_dyn_u_func_ke);
u_func_ke("return 6e40 & 7", u_dyn_u_func_ke);
u_func_ke("return 34 << 7e30", u_dyn_u_func_ke);
u_func_ke("return ~-3e40", u_dyn_u_func_ke);
u_func_ke("return ~-3.009", u_dyn_u_func_ke);
u_func_ke("return 3.009 & 1", u_dyn_u_func_ke);
u_func_ke("return 34 >> {}", u_dyn_u_func_ke);
u_func_ke("a = 24 // 0", u_dyn_u_func_ke);
u_func_ke("a = 1 % 0", u_dyn_u_func_ke);
_G.D = u_u_res;
u_func_ke("  -- create light udata\n  local x = D.upvalueid(function () return debug end, 1)\n  D.setuservalue(x, {})\n", u_dyn_u_func_ke);
_G.D = nil;
u_func_ke("math.sin(io.input())", u_dyn_u_func_ke);
_G.XX = setmetatable(u_dyn_u_func_ke, {["__name"] = "My Type"});
u_func_jw_i_h = assert;
u_func_jw_i = string;
u_dyn_u_func_ke(_ENV[v]);
u_func_jw_i, u_dyn_u_func_ke = u_func_jw_i.find(u_dyn_u_func_ke, "^My Type");
u_func_jw_i_h(u_func_jw_i, u_dyn_u_func_ke);
u_func_ke("io.input(XX)", u_dyn_u_func_ke);
u_func_ke("return XX + 1", u_dyn_u_func_ke);
u_func_ke("return ~io.stdin", u_dyn_u_func_ke);
u_func_ke("return XX < XX", u_dyn_u_func_ke);
u_func_ke("return {} < XX", u_dyn_u_func_ke);
u_func_ke("return XX < io.stdin", u_dyn_u_func_ke);
_G.XX = nil;
u_func_ke("(io.write or print){}", u_dyn_u_func_ke);
u_func_ke("(collectgarbage or print){}", u_dyn_u_func_ke);
u_func_jw_i = assert;
u_dyn_u_func_ke, v_ke = u_dyn_u_func_ke(string.dump((function ()
   return val_jj + 1;
end), true));
u_func_jw_i_h = u_func_jw_i(u_dyn_u_func_ke, v_ke);
u_func_jw_i = assert;
u_dyn_u_func_ke(3);
u_func_jw_i(u_dyn_u_func_ke);
u_func(u_dyn_u_func_ke, u_func_jw_i_h, {});
u_func_jw_i = assert;
u_dyn_u_func_ke, v_ke = u_dyn_u_func_ke(string.dump((function ()
   return {} + 2;
end), true));
u_func(u_dyn_u_func_ke, u_func_jw_i(u_dyn_u_func_ke, v_ke));
u_func_jw_i_h = {};
for i = 1, 1000 do
   u_func_jw_i_h[i] = "a = x".. i;
end
u_func_jw_i = table.concat(u_dyn_u_func_ke, "; ");
u_dyn_u_func_ke(u_func_jw_i.. "; a = bbb + 1", "global \bbb\");
u_dyn_u_func_ke("local _ENV=_ENV;".. u_func_jw_i.. "; a = bbb + 1", "global \bbb\");
u_dyn_u_func_ke(u_func_jw_i.. "; local t = {}; a = t.bbb + 1", "field \bbb\");
u_dyn_u_func_ke(u_func_jw_i.. "; local t = {}; t:bbb()", "method \bbb\");
u_dyn_u_func_ke("aaa=9\nrepeat until 3==3\nlocal x=math.sin(math.cos(3))\nif math.sin(1) == x then return math.sin(1) end   -- tail call\nlocal a,b = 1, {\n  {x=\a\..\b\..\c\, y=\b\, z=x},\n  {1,2,3,4,5} or 3+3<=3+3,\n  3+1>3+1,\n  {d = x and aaa[x or y]}}\n", "global \aaa\");
u_dyn_u_func_ke("local x,y = {},1\nif math.sin(1) == 0 then return 3 end    -- return\nx.a()", "field \a\");
u_dyn_u_func_ke("prefix = nil\ninsert = nil\nwhile 1 do\n  local a\n  if nil then break end\n  insert(prefix, a)\nend", "global \insert\");
u_dyn_u_func_ke("  -- tail call\n  return math.sin(\a\)\n", "\sin\");
u_dyn_u_func_ke("collectgarbage(\nooption\)", "invalid option");
u_dyn_u_func_ke("x = print .. \a\", "concatenate");
u_dyn_u_func_ke("x = \a\ .. false", "concatenate");
u_dyn_u_func_ke("x = {} .. 2", "concatenate");
u_dyn_u_func_ke("getmetatable(io.stdin).__gc()", "no value");
u_dyn_u_func_ke("local Var\nlocal function main()\n  NoSuchName (function() Var=0 end)\nend\nmain()\n", "global \NoSuchName\");
u_dyn_u_func_ke("+");
a = {};
u_dyn_u_func_ke(a, {["__index"] = string});
u_dyn_u_func_ke("a:sub()", "bad self");
u_dyn_u_func_ke("string.sub(\a\, {})", "#2");
u_dyn_u_func_ke("(\a\):sub{}", "#1");
u_dyn_u_func_ke("table.sort({1,2,3}, table.sort)", "\table.sort\");
u_dyn_u_func_ke = u_func_ke;
u_dyn_u_func_ke("string.gsub(\s\, \s\, setmetatable)", "\setmetatable\");
u_dyn_u_func_ke = (function ()
   local c_v_bga, c_v_bgc = coroutine.resume(coroutine.create(u_dyn_u_func_ke));
   return c_v_bgc;
end);
assert(string.find(u_dyn_u_func_ke(), u_u_idx_currentline));
u_func_ke("coroutine.yield()", "outside a coroutine");
u_dyn_u_func_ke = coroutine.wrap((function ()
   table.sort({[51] = 1, [52] = 2, [53] = 3}, coroutine.yield);
end));
u_func("yield across", u_dyn_u_func_ke);
idsize = 59;
for i_o = 50, 70 do
   u_glb("@".. string.rep("x", i_o));
   u_glb(string.rep("x", (i_o - 10)));
   u_glb("=".. string.rep("x", i_o));
end
i = (function ()
   local dyn_res_it = 0;
   local c_success_ir, c_result_is = pcall(load(v_beu), v_beu);
   local c_res_it = string.match(c_result_is, ":(%d+):");
   dyn_res_it = nil;
   dyn_res_it = nil;
   if (c_res_it) then
      dyn_res_it = c_res_it;
   else  
      dyn_res_it = c_res_it;
   end
   assert(dyn_res_it == v_bfw);
end);
i(u_u_idx_currentline, 2);
i(u_u_idx_currentline, 3);
i(u_u_idx_currentline, 4);
i(u_u_idx_currentline, 1);
i(u_u_idx_currentline, 3);
i(u_u_idx_currentline, 6);
i(u_u_idx_currentline, 3);
i(u_u_idx_currentline, 3);
i(u_u_idx_currentline, 1);
i(u_u_idx_currentline, 2);
i(u_u_idx_currentline, 6);
X = 3;
u_u_idx_currentline("  function g() f() end\n  function f(x) error(\a\, X) end\ng()\n", u_glb);
X = 0;
u_u_idx_currentline("  function g() f() end\n  function f(x) error(\a\, X) end\ng()\n", u_glb);
X = 1;
u_u_idx_currentline("  function g() f() end\n  function f(x) error(\a\, X) end\ng()\n", u_glb);
X = 2;
u_u_idx_currentline("  function g() f() end\n  function f(x) error(\a\, X) end\ng()\n", u_glb);
if (_soft) then
   u_u_idx_currentline();
   u_u_idx_currentline("testing stack overflow");
   C = 0;
   local u_u_idx_currentline = u_u_idx_currentline(1, u_glb).currentline;
   function y()
      C = C + 1;
      y();
   end;
   i_o = (function ()
      return string.find(v_beq, "^.-:%d+: stack overflow");
   end);
   u_glb(i_o(u_func_jw("y()"), "y()"));
   u_glb("+");
   u_glb(i_o(u_func_jw("y()"), "y()"));
   u_glb("+");
   u_glb(i_o(u_func_jw("y()"), "y()"));
   local u_glb = print;
   u_glb("+");
   C = 0;
   success, result = xpcall((function ()
      u_glb = u_u_res.getinfo(v_beo, "l").currentline;
      y();
   end), u_u_res.traceback, 1);
   _ENV[v]("+");
   tab = {};
   for u_glb_ka in string.gmatch(result, "[^\n]*") do
      if (not str_value(u_glb_ka, ":(%d+):")) then
         continue;
      end
      table.insert(tab, tonumber(str_value), str_value);
   end
   local val = 1;
   while (tab[val] ~= nil) 
      _ENV[v](tab[val] == u_u_idx_currentline);
      val = val + 1;
   end
   assert(val > 15);
   success_v, result_w = xpcall(error, u_glb_ka);
   u_glb_ka = assert;
   if (success_v) then
      str_value(result_w);
   end
   u_glb_ka(str_value);
   u_glb_ka(str_value);
   u_glb_ka = (function ()
      if (u == 0) then
         error("a\n");
         return;
      end
      local function c_func_ig ()
         return u_glb_ka((u - 1));
      end;
      return xpcall(c_func_ig, c_func_ig);
   end);
   local str_value = u_glb_ka;
   str_value(3);
   str_value = (function ()
      return str_value(v_bdr, v_bdt, v_bdv) + 1;
   end);
   local c_v_sx, c_v_sz = _ENV[v](str_value, (function ()
      assert(string.find(v_bdm, "stack overflow"));
      u_func("error handling", str_value);
      assert(math.sin(0) == 0);
      return 15;
   end));
   assert(c_v_sz == 15);
   u_func("too many results", (function ()
      for c_i_ic = 999900, 1000000 do
         table.unpack({}, 1, c_i_ic);
      end
   end));
end
local u_u_idx_currentline = {};
i_o, u_glb = _ENV[v](u_glb);
if (i_o or (u_glb ~= u_u_idx_currentline)) then
   success = false;
else  
   success = true;
end
_ENV[v](success);
success_q, success = pcall((function ()
   error(nil);
end));
if (success_q or (success ~= nil)) then
   success = false;
else  
   success = true;
end
assert(success);
success, result = xpcall((function ()
   error({["msg"] = "x"});
end), (function ()
   return {["msg"] = tab_hy.msg.. "y"};
end));
assert(result.msg == "xy");
success, result = pcall(assert, false, "X", u_u_idx_currentline);
if (success or (result ~= "X")) then
   result = false;
else  
   result = true;
end
assert(result);
success, result = pcall((function ()
   assert(false);
end));
assert(_ENV[v](string.match(result, "%w+%.lua:(%d+): assertion failed!$")) == (u_u_res.getinfo(1, "l").currentline - 2));
result, tab = pcall(assert, false, u_u_idx_currentline);
if (result or (tab ~= u_u_idx_currentline)) then
   tab = false;
else  
   tab = true;
end
_ENV[v](tab);
result, tab = pcall(assert, nil, nil);
if (result or (tab ~= nil)) then
   tab = false;
else  
   tab = true;
end
assert(tab);
i_o, u_glb = pcall(_ENV[v]);
result = assert;
if (i_o) then
   tab = _ENV[v].find(u_glb, "value expected");
else  
   tab = false;
end
result(tab);
a, b, c = u_glb(string.find, error, "alo", "al");
if (a and ((b == 1) or (c ~= 2))) then
   i_o = false;
else  
   i_o = true;
end
u_u_idx_currentline(i_o);
a, b, c = u_glb(_ENV[v].find, (function ()
   local c_tab_hx = {};
   return c_tab_hx;
end), true, "al");
if (not (a or (type(u_glb) ~= "table")) or (c == nil)) then
   i_o = false;
else  
   i_o = true;
end
u_u_idx_currentline(i_o);
u_u_idx_currentline("testing tokens in error messages");
u_u_idx_currentline("syntax error", u_glb, "error", 1);
u_u_idx_currentline("1.000", u_glb, "1.000", 1);
u_u_idx_currentline("[[a]]", u_glb, "[[a]]", 1);
u_u_idx_currentline("\aa\", u_glb, "\aa\", 1);
u_u_idx_currentline("while << do end", u_glb, "<<", 1);
u_u_idx_currentline("for >> do end", u_glb, ">>", 1);
u_u_idx_currentline("a\x01a = 1", u_glb, "<\\1>", 1);
u_u_idx_currentline("\xFFa = 1", u_glb, "<\\255>", 1);
u_u_idx_currentline("I = load(\a=9+\); a=3");
u_u_idx_currentline((a ~= 3) or (I == nil));
print("+");
lim = 1000;
if (not _soft) then
   lim = 100;
end
for success_q = 1, lim do
   u_func_jw("a = ");
   u_func_jw("a = 4+nil");
end
u_glb("local a; a", ",a", "= 1", ",1");
u_glb("local a; a=", "{", "0", "}");
u_glb("local a; a=", "(", "2", ")");
u_glb("local a; ", "a(", "2", ")");
u_glb(D, "do ", D, " end");
u_glb(D, "while a do ", D, " end");
u_glb("local a; ", "if a then else ", D, " end");
u_glb(D, "function foo () ", D, " end");
u_glb("local a; a=", "a..", "a", D);
u_glb("local a; a=", "a^", "a", D);
u_glb("a = f(x".. string.rep(",x", 260).. ")", "too many registers");
success_q = "local function fooA ()\n  local ";
for val = 1, 127 do
   success_q = success_q.. "a".. val.. ", ";
end
success_q = success_q.. "b,c\n".. "local function fooB ()\n  local ";
for val = 1, 127 do
   success_q = success_q.. "b".. val.. ", ";
end
success_q = success_q.. "b\n".. "function fooC () return b+c";
success = 3;
for success_v = 1, 127 do
   success_q = success_q.. "+a".. success_v.. "+b".. success_v;
   success = success + 2;
end
result, tab = load(success_q.. "\nend  end end");
val = assert;
if (success > 255) then
   success_v = string.find(tab, u_glb_ka) or string.find(tab, u_glb_ka);
else  
   success_v = false;
end
val(success_v);
success_q = "\nfunction foo ()\n  local ";
for u_glb_ka = 1, 300 do
   success_q = success_q.. "a".. u_glb_ka.. ", ";
end
local result_w = assert;
if (not u_glb_ka(str_value, "line 2")) then
   u_glb_ka(str_value, "too many local variables");
end
result_w(u_glb_ka);
cmp.__index = cmp.__index;
_ENV[v](u_glb_ka);
