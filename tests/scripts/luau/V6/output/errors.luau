print(u_cmp);
function doit()
   local c_function, c_v_on = loadstring(v_oj);
   if (c_function == nil) then
      return c_v_on;
   end
   local c_success_dk, c_result_dl = pcall(c_function);
   return not c_success_dk and c_result_dl;
end;
function checkmessage()
end;
function checksyntax()
   local c_res_de = doit(v_nx);
   local c_res_dc = string.gsub(c_res_dc, "(%p)", "%%%1");
   assert(string.find(c_res_de, string.format("^%%[string \".*\"%%]:")));
   assert(string.find(c_res_de, c_res_de, 1, true));
end;
local v = assert;
local u_cmp = doit(u_u_res) == "hi";
v(u_cmp);
v = assert;
u_cmp = u_cmp("unpack({}, 1, n=2^30)");
v(u_cmp);
v = assert;
u_cmp = u_cmp("a=math.sin()");
v(u_cmp);
v = assert;
u_cmp = if not (doit(u_u_res)) then u_cmp("tostring()") else u_cmp;
v(u_cmp);
v = assert;
u_cmp = u_cmp("tonumber()");
v(u_cmp);
v = assert;
u_cmp = u_cmp("repeat until 1; a");
v(u_cmp);
checksyntax(u_cmp, "", u_u_res, 1);
v = assert;
u_cmp = u_cmp(";");
v(u_cmp);
v = assert;
u_cmp = u_cmp("a=1;;");
v(u_cmp);
v = assert;
u_cmp = u_cmp("return;;");
v(u_cmp);
v = assert;
u_cmp = u_cmp("assert(false)");
v(u_cmp);
v = assert;
u_cmp = u_cmp("assert(nil)");
v(u_cmp);
v = assert;
u_cmp = u_cmp("a=math.sin\n(3)");
v(u_cmp);
v = assert;
u_cmp = u_cmp("function a (... , ...) end");
v(u_cmp);
v = assert;
u_cmp = u_cmp("function a (, ...) end");
v(u_cmp);
checksyntax(u_cmp, "\'}\' expected (to close \'{\' at line 1)", u_u_res, 3);
checkmessage(u_cmp, "global \'bbbb\'");
checkmessage(u_cmp, "local \'bbbb\'");
checkmessage(u_cmp, "method \'bbbb\'");
checkmessage(u_cmp, "field \'bbbb\'");
v = assert;
local u_idx = string.find;
local u_u_res = u_u_res("a={13}; local bbbb=1; a[bbbb](3)");
u_cmp = not u_idx(u_u_res, "\'bbbb\'");
v(u_cmp);
checkmessage(u_cmp, "number");
aaa = nil;
checkmessage(u_cmp, "global \'aaa\'");
checkmessage(u_cmp, "field \'bbb\'");
checkmessage(u_cmp, "method \'ddd\'");
checkmessage(u_cmp, "upvalue \'b\'");
v = assert;
u_cmp = not doit(u_u_res);
v(u_cmp);
checkmessage(u_cmp, "local \'aaa\'");
checkmessage(u_cmp, "global \'aaa\'");
checkmessage(u_cmp, "global \'b\'");
checkmessage(u_cmp, "global \'aaa\'");
v = assert;
u_idx = string.find;
u_u_res = u_u_res("aaa={}; x=(aaa or aaa)+(aaa and aaa)");
u_cmp = not u_idx(u_u_res, "\'aaa\'");
v(u_cmp);
v = assert;
u_idx = string.find;
u_u_res = u_u_res("aaa={}; (aaa or aaa)()");
u_cmp = not u_idx(u_u_res, "\'aaa\'");
v(u_cmp);
checkmessage(u_cmp, "global \'aaa\'");
checkmessage(u_cmp, "field \'a\'");
checkmessage(u_cmp, "global \'insert\'");
checkmessage(u_cmp, "\'sin\'");
checkmessage(u_cmp, "invalid option");
checkmessage(u_cmp, "concatenate");
checkmessage(u_cmp, "no value");
print(u_cmp);
function lineerror()
   local c_success_cx, c_result_cy = pcall(loadstring(v_nn));
   return string.match(c_result_cy, ":(%d+):");
end;
v = assert;
u_cmp = lineerror(u_u_res) == 2;
v(u_cmp);
v = assert;
u_cmp = lineerror(u_u_res) == 1;
v(u_cmp);
X = 3;
u_u_res = u_u_res("function g() f() end\nfunction f(x) error(\'a\', X) end\ng()\n");
u_cmp(u_u_res == 3);
X = 0;
u_u_res = u_u_res("function g() f() end\nfunction f(x) error(\'a\', X) end\ng()\n");
u_cmp(u_u_res == nil);
X = 1;
u_u_res = u_u_res("function g() f() end\nfunction f(x) error(\'a\', X) end\ng()\n");
u_cmp(u_u_res == 2);
X = 2;
u_cmp = assert;
u_u_res = u_u_res("function g() f() end\nfunction f(x) error(\'a\', X) end\ng()\n");
u_cmp(u_u_res == 1);
lineerror = nil;
if (not limitedstack) then
   C = 0;
   function y()
      C += 1;
      y();
   end;
   u_idx = assert;
   u_u_res = u_u_res(doit("y()"));
   u_idx(u_u_res);
   u_idx = assert;
   u_u_res = u_u_res(doit("y()"));
   u_idx(u_u_res);
   u_idx = assert;
   u_u_res = u_u_res(doit("y()"));
   u_idx(u_u_res);
   C = 0;
   local u_success, u_result = xpcall((function ()
      y();
   end), debug.traceback);
   for v_ig in string.gmatch(u_result, "[^\n]*") do
      local c_res = string.match(v_ig, ":(%d+):");
      if (c_res) then
         table.insert({}, tonumber(c_res));
      end
   end
end
if (not limitedstack) then
   u_idx = setmetatable(u_u_res, {__index = (function ()
      u_cmp += 1;
      return tab_cu[v_nl];
   end), __newindex = (function ()
      u_cmp += 1;
      tab_cr[v_nd] = v_nf;
   end), __tostring = (function ()
      u_cmp += 1;
      return tostring(value);
   end)});
   u_u_res = nil;
   local function u_success ()
      if (v_ms) then
         return;
      end
      u_u_res = debug.info(2, "l");
      error();
   end;
   local u_result = newproxy(true);
   getmetatable(u_result).__index = print;
   assert(debug.info(print, "s") == "[C]");
   local success, c_result = xpcall(tostring, (function ()
      u_success(string.find(v_kf, "C stack overflow"));
      print("after __tostring C stack overflow", u_cmp);
      u_success(u_cmp > 1);
      u_cmp = 1;
      local success_bz, result_ca = pcall(tostring, u_idx);
      print("after __tostring overflow in handler", u_cmp);
      u_success(not success_bz and string.find(result_ca, "error in error handling"));
      u_success(u_cmp > 1);
      u_cmp = 1;
      success_bz, result_ca = pcall((function ()
         return u_idx[u_idx];
      end));
      print("after __index overflow in handler", u_cmp);
      u_success(not success_bz and string.find(result_ca, "error in error handling"));
      u_success(u_cmp > 1);
      u_cmp = 1;
      success_bz, result_ca = pcall((function ()
         u_idx[u_idx] = "kohuke";
      end));
      print("after __newindex overflow in handler", u_cmp);
      u_success(not success_bz and string.find(result_ca, "error in error handling"));
      u_success(u_cmp > 1);
      u_success(pcall((function ()
         return u_result[u_result];
      end)));
      u_success(pcall((function ()
         return u_result[1];
      end)));
      u_success(pcall((function ()
         return u_result.StringConstant;
      end)));
      success_bz, result_ca = coroutine.resume(coroutine.create((function ()
      end)));
      u_success(not success_bz and string.find(result_ca, "C stack overflow"));
      return true;
   end), u_idx);
   assert(not success);
   assert(c_result == true, "error in xpcall eh, line " .. tostring(u_u_res));
end
u_cmp, u_idx = u_cmp(error, u_u_res);
u_u_res(not u_cmp and (type(u_idx) == "string"));
if (not limitedstack) then
   u_u_res(3);
end
local u_success, u_result = xpcall((function ()
   error({msg = "x"});
end), (function ()
   return {msg = tab.msg .. "y"};
end));
assert(u_result.msg == "xy");
print("+");
checksyntax("syntax error", "", "error", 1);
checksyntax("1.000", "", "1.000", 1);
checksyntax("[[a]]", "", "[[a]]", 1);
checksyntax("\'aa\'", "", "\'aa\'", 1);
checksyntax("\xFFa = 1", "", "\xFF", 1);
doit("I = loadstring(\"a=9+\"); a=3");
assert(a == 3);
print("+");
lim = 1000;
lim = rawget(_G, "_soft") or lim;
for success = 1, lim do
   doit("a = ");
   doit("a = 4+nil");
end
