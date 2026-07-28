print("testing vararg");
local u_idx = table.unpack;
_G.arg = nil;
function f(...)
   local c_tab_cu = {n = select("#", ...), ...};
   assert(if (tab_ct) then (#c_tab_cu == #tab_ct) else (#c_tab_cu == 0));
   for c_i = 1, #c_tab_cu do
      assert(tab_ct[c_i] == c_tab_cu[c_i]);
   end
end;
function c12(...)
   local tab_cm = {...};
   tab_cm.n = table.getn(tab_cm);
   local c_cmp = tab_cm.n == 2;
   if (not c_cmp) then
      return c_cmp, 2;
   end
   return 55, 2;
end;
function vararg(...)
   return {n = select("#", ...), ...};
end;
local function c_func_b ()
   return v_ew(u_idx(tab_ck, 1, tab_ck.n));
end;
assert(f() == 0);
assert(f({1, 2, 3}, 1, 2, 3) == 3);
assert(f({
   "alo", 
   nil, 
   45, 
   f, 
   nil}, "alo", nil, 45, f, nil) == 5);
assert(c12(1, 2) == 55);
a, b = assert(c_func_b(c12, {1, 2}));
assert(a == 55);
a = c_func_b(c12, {1, 2, n = 2});
assert(a == 55);
a = c_func_b(c12, {1, 2, n = 1});
assert(not a);
assert(c12(1, 2, 3) == false);
local c_tab = {foo = 1, bar = 2, foobar = 3};
assert(vararg(c_func_b(next, {c_tab, nil, n = 2}))[1] == next(c_tab));
assert(vararg(c_func_b(c_func_b, {c12, {1, 2}})).n == 2);
assert(c_func_b(print, {"+"}) == nil);
assert(({1, 10, f = (function (...)
   local c_tab_cg = {n = select("#", ...), ...};
   return tab_cf[c_tab_cg[1]] + c_tab_cg.n;
end)}):f(1, 4) == 3);
print("+");
lim = 20;
local val = 1;
local tab_i = {};
while (val < lim) do
   tab_i[val] = val + 0.3;
   val += 1;
end
function f(...)
   assert(if (v_em == 1.3) then not ({...})[(lim - 3)] else false);
end;
function g()
   assert(v_ek == 1.3);
end;
c_func_b(f, tab_i);
c_func_b(g, tab_i);
tab_i = {};
val = 1;
while (val < lim) do
   tab_i[val] = val;
   val += 1;
end
assert(c_func_b(math.max, tab_i) == lim);
print("+");
function oneless(...)
   return ...;
end;
function f(...)
   assert(arg == nil);
   if (val_bz == 0) then
      return v_ee, ..., ..., ..., oneless(oneless(oneless(...)));
   end
   assert(true);
   return f((val_bz - 1), v_ee, ...);
end;
local condition_j, message_k, v_cv, v_cx, v_cz = assert(f(10, 5, 4, 3, 2, 1));
d = v_cx;
e = v_cz;
assert(condition_j == 5);
condition_j, message_k, v_cv, v_cx, v_cz = f(4);
d = v_cx;
e = v_cz;
assert(condition_j == nil);
assert(table.getn({select(3, u_idx({
   10, 
   20, 
   30, 
   40}))}) == 2);
assert(next({select(1)}) == nil);
assert(({select(-1, 3, 5, 7)})[1] == 7);
assert(({select(-2, 3, 5, 7)})[1] == 5);
pcall(select, 10000);
pcall(select, -10000);
function selectone(...)
   return select(v_ea, ...);
end;
function selectmany(...)
   return table.concat({select(v_dy, ...)}, ",");
end;
assert(selectone("#") == 0);
assert(selectmany("#") == "0");
assert(selectone("#", 10, 20, 30) == 3);
assert(selectmany("#", 10, 20, 30) == "3");
assert(selectone(1, 10, 20, 30) == 10);
assert(selectmany(1, 10, 20, 30) == "10,20,30");
assert(selectone(2, 10, 20, 30) == 20);
assert(selectmany(2, 10, 20, 30) == "20,30");
assert(selectone(3, 10, 20, 30) == 30);
assert(selectmany(3, 10, 20, 30) == "30");
assert(selectone(4, 10, 20, 30) == nil);
assert(selectmany(4, 10, 20, 30) == "");
assert(selectone(-2, 10, 20, 30) == 20);
assert(selectmany(-2, 10, 20, 30) == "20,30");
assert(selectone("3", 10, 20, 30) == 30);
assert(selectmany("3", 10, 20, 30) == "30");
f = loadstring(" return {...} ");
x = f(2, 3);
assert(x[1] == 2);
f = loadstring("  local x = {...}\n  for i=1,select(\'#\', ...) do assert(x[i] == select(i, ...)) end\n  assert(x[select(\'#\', ...)+1] == nil)\n  return true\n");
assert(f("a", "b", nil, {}, assert));
assert(f());
return "OK";
