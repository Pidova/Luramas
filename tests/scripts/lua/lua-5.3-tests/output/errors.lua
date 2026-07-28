local u_func_jw_i = 0;
(_ENV[v])("testing errors");
local u_res = ()_ENV[v]("debug");
getmetatable(_ENV[v]) and {}.__index = nil;
local function u_func ()
   local res_co = 0;
   local c_success_cl, c_result_cm = pcall(function);
   local c_glb_cn = assert;
   if (c_success_cl) then
      res_co = ()string.find(c_result_cm, v_it);
   else  
      res_co = false;
   end
   c_glb_cn(res_co);
end;
local function u_func_jw ()
   local c_chunk, c_source = load(v_hj);
   if (c_chunk == nil) then
      return c_source;
   end
   local c_success, c_result = pcall(c_chunk);
   if (not c_success) then
      return false;
   end
   return c_result;
end;
local function u_func_ke ()
   assert(()string.find(u_func_jw(v_hf), v_hh, 1, true));
end;
local function c_func ()
   local v_gl = 0;
   local c_u_func_jw_bs = u_func_jw(v_gq);
   if (not ()string.find(0, "^<%a") or not (()string.find(0, "^char%("))) then
      v_gl = ""\0"\";
   end
   assert(()string.find(c_u_func_jw_bs, ()string.format("^%%[string \.*\%%]:%d: .- near %s$", v_gw, ()string.gsub(v_gl, "(%p)", "%%%1"))));
   assert(()string.find(c_u_func_jw_bs, c_u_func_jw_bs, 1, true));
end;
assert(()"assert"("error(\hi\, 0)") == "hi");
assert(()"assert"("error()") == nil);
(_ENV[v])(u_func_jw("table.unpack({}, 1, n=2^30)"), "table.unpack({}, 1, n=2^30)");
(_ENV[v])(u_func_jw("a=math.sin()"), "a=math.sin()");
local c_glb = _ENV;
if (u_func_jw("tostring(1)")) then
   u_func_jw_i = u_func_jw("tostring()");
else  
   u_func_jw_i = false;
end
(c_glb[v])(u_func_jw_i);
(_ENV[v])(u_func_jw("tonumber()"), "tonumber()");
(_ENV[v])(u_func_jw("repeat until 1; a"), "repeat until 1; a");
(_ENV[v])(u_func_jw("return;;"), "return;;");
(_ENV[v])(u_func_jw("assert(false)"), "assert(false)");
(_ENV[v])(u_func_jw("assert(nil)"), "assert(nil)");
(_ENV[v])(u_func_jw("function a (... , ...) end"), "function a (... , ...) end");
(_ENV[v])(u_func_jw("function a (, ...) end"), "function a (, ...) end");
(_ENV[v])(u_func_jw("local t={}; t = t[#t] + 1"), "local t={}; t = t[#t] + 1");
c_func("  local a = {4\n\n", "\}\ expected (to close \{\ at line 1)", "<eof>", 3);
u_func_ke("a = {} + 1", "arithmetic");
u_func_ke("a = {} | 1", "bitwise operation");
u_func_ke("a = {} < 1", "attempt to compare");
u_func_ke("a = {} <= 1", "attempt to compare");
u_func_ke("a=1; bbbb=2; a=math.sin(3)+bbbb(3)", "global \bbbb\");
u_func_ke("a={}; do local a=1 end a:bbbb(3)", "method \bbbb\");
u_func_ke("local a={}; a.bbbb(3)", "field \bbbb\");
assert(not ()_ENV[v].find(u_func_jw("a={13}; local bbbb=1; a[bbbb](3)"), "\bbbb\"));
u_func_ke("a={13}; local bbbb=1; a[bbbb](3)", "number");
u_func_ke("a=(1)..{}", "a table value");
u_func_ke("a = #print", "length of a function value");
u_func_ke("a = #3", "length of a number value");
aaa = nil;
u_func_ke("aaa.bbb:ddd(9)", "global \aaa\");
u_func_ke("local aaa={bbb=1}; aaa.bbb:ddd(9)", "field \bbb\");
u_func_ke("local aaa={bbb={}}; aaa.bbb:ddd(9)", "method \ddd\");
u_func_ke("local a,b,c; (function () a = b+1 end)()", "upvalue \b\");
(_ENV[v])(not u_func_jw("local aaa={bbb={ddd=next}}; aaa.bbb:ddd(nil)"));
u_func_ke("local a,b,cc; (function () a = cc[1] end)()", "upvalue \cc\");
u_func_ke("local a,b,cc; (function () a.x = 1 end)()", "upvalue \a\");
u_func_ke("local _ENV = {x={}}; a = a + 1", "global \a\");
u_func_ke("b=1; local aaa=\a\; x=aaa+b", "local \aaa\");
u_func_ke("aaa={}; x=3/aaa", "global \aaa\");
u_func_ke("aaa=\2\; b=nil;x=aaa*b", "global \b\");
u_func_ke("aaa={}; x=-aaa", "global \aaa\");
u_func_ke("a=1; local a,bbbb=2,3; a = math.sin(1) and bbbb(3)", "local \bbbb\");
u_func_ke("a=1; local a,bbbb=2,3; a = bbbb(1) or a(3)", "local \bbbb\");
u_func_ke("local a,b,c,f = 1,1,1; f((a and b) or c)", "local \f\");
u_func_ke("local a,b,c = 1,1,1; ((a and b) or c)()", "call a number value");
assert(not ()_ENV[v].find(u_func_jw("aaa={}; x=(aaa or aaa)+(aaa and aaa)"), "\aaa\"));
assert(not ()_ENV[v].find(u_func_jw("aaa={}; (aaa or aaa)()"), "\aaa\"));
u_func_ke("print(print < 10)", "function with number");
u_func_ke("print(print < print)", "two function values");
u_func_ke("print(\10\ < 10)", "string with number");
u_func_ke("print(10 < \23\)", "number with string");
u_func_ke("local a = 2.0^100; x = a << 2", "local a");
u_func_ke("local a = 1 >> 2.0^100", "has no integer representation");
u_func_ke("local a = \10\ << 2.0^100", "has no integer representation");
u_func_ke("local a = 2.0^100 & 1", "has no integer representation");
u_func_ke("local a = 2.0^100 & \1\", "has no integer representation");
u_func_ke("local a = 2.0 | 1e40", "has no integer representation");
u_func_ke("local a = 2e100 ~ 1", "has no integer representation");
u_func_ke("string.sub(\a\, 2.0^100)", "has no integer representation");
u_func_ke("string.rep(\a\, 3.3)", "has no integer representation");
u_func_ke("return 6e40 & 7", "has no integer representation");
u_func_ke("return 34 << 7e30", "has no integer representation");
u_func_ke("return ~-3e40", "has no integer representation");
u_func_ke("return ~-3.009", "has no integer representation");
u_func_ke("return 3.009 & 1", "has no integer representation");
u_func_ke("return 34 >> {}", "table value");
u_func_ke("a = 24 // 0", "divide by zero");
u_func_ke("a = 1 % 0", "\n%0\");
_G.D = u_res;
u_func_ke("  -- create light udata\n  local x = D.upvalueid(function () return debug end, 1)\n  D.setuservalue(x, {})\n", "light userdata");
_G.D = nil;
u_func_ke("math.sin(io.input())", "(number expected, got FILE*)");
_G.XX = setmetatable({}, {["__name"] = "My Type"});
assert(()string.find(tostring(_ENV[v]), "^My Type"));
u_func_ke("io.input(XX)", "(FILE* expected, got My Type)");
u_func_ke("return XX + 1", "on a My Type value");
u_func_ke("return ~io.stdin", "on a FILE* value");
u_func_ke("return XX < XX", "two My Type values");
u_func_ke("return {} < XX", "table with My Type");
u_func_ke("return XX < io.stdin", "My Type with FILE*");
_G.XX = nil;
u_func_ke("(io.write or print){}", "io.write");
u_func_ke("(collectgarbage or print){}", "collectgarbage");
local res = assert(load(()string.dump((function ()
   return val + 1;
end), true)));
assert(res(3) == 4);
u_func("^%?:%-1:", res, {});
u_func_jw_i = assert;
local u_glb = load;
local c_v_fn, c_v_fp = ()string.dump((function ()
   return {} + 2;
end), true);
u_func("^%?:%-1:.*table value", u_func_jw_i(u_glb(c_v_fn, c_v_fp)));
res = {};
for u_func_jw_i = 1, 1000 do
   res[c_v_fp] = "a = x".. c_v_fp;
end
