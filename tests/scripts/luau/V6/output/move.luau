local function c_func (...)
   local c_success, c_result = pcall(function, ...);
   assert(not c_success and string.find(c_result, v_ey));
end;
print("testing move");
c_func("table expected", table.move, 1, 2, 3, 4);
c_func("table expected", table.move, {}, 2, 3, 4, "foo");
local function c_func_d ()
   for k, v_cd in pairs(v_eg) do
      assert(tab[k] == v_cd);
   end
end;
c_func_d(table.move({10, 20, 30}, 1, 3, 2), {
   10, 
   10, 
   20, 
   30});
c_func_d(table.move({10, 20, 30}, 1, 3, 3), {
   10, 
   20, 
   10, 
   20, 
   30});
local v = {
   10, 
   20, 
   30, 
   40};
table.move(v, 1, 4, 2, v);
c_func_d(v, {
   10, 
   10, 
   20, 
   30, 
   40});
c_func_d(table.move({10, 20, 30}, 2, 3, 1), {20, 30, 30});
local v_s = {};
assert(table.move({10, 20, 30}, 1, 3, 1, v_s) == v_s);
c_func_d(v_s, {10, 20, 30});
v_s = {};
assert(table.move({10, 20, 30}, 1, 0, 3, v_s) == v_s);
c_func_d(v_s, {});
c_func_d(table.move({10, 20, 30}, 1, 10, 1), {10, 20, 30});
c_func_d(table.move({[2147483648] = 1, [2147483648] = 2, [2147483647] = 3}, 2147483648, 2147483647, -10, {}), {[-10] = 1, [-9] = 2, [-8] = 3});
c_func_d(table.move({[-2147483648] = 1, [-2147483648] = 2, [-2147483648] = 3}, -2147483648, -2147483648, -10, {}), {[-10] = 1, [-9] = 2, [-8] = 3});
c_func_d(table.move({45}, 1, 1, 2147483647), {45, [2147483647] = 45});
c_func_d(table.move({[2147483647] = 100}, 2147483647, 2147483647, -2147483648), {[-2147483648] = 100, [2147483647] = 100});
c_func_d(table.move({[-2147483648] = 100}, -2147483648, -2147483648, 2147483647), {[-2147483648] = 100, [2147483647] = 100});
v_s = {};
table.move({
   [-1] = 1, 
   [0] = 2, 
   [1] = 3, 
   [2] = 4}, -1, 3, 1, v_s);
c_func_d(v_s, {
   1, 
   2, 
   3, 
   4});
v_s = {};
table.move({
   [-1] = 1, 
   [0] = 2, 
   [1] = 3, 
   [2] = 4, 
   [10] = 5, 
   [100] = 6, 
   [1000] = 7}, -1, 3, 1, v_s);
c_func_d(v_s, {
   1, 
   2, 
   3, 
   4});
v = {
   1, 
   2, 
   3, 
   4, 
   5};
table.move({10}, 1, 3, 2, v);
c_func_d(v, {
   1, 
   10, 
   nil, 
   nil, 
   5});
v = {
   1, 
   2, 
   3, 
   4, 
   5};
table.move({10}, -1, 1, 2, v);
c_func_d(v, {
   1, 
   nil, 
   nil, 
   10, 
   5});
v = {[-1000] = 1, [1000] = 2, [1] = 3};
table.move({10}, -1000, 1000, -1000, v);
c_func_d(v, {10});
c_func("too many", table.move, {}, 0, 2147483647, 1);
c_func("too many", table.move, {}, -1, 2147483648, 1);
c_func("too many", table.move, {}, -2147483648, -1, 1);
c_func("too many", table.move, {}, -2147483648, 2147483647, 1);
c_func("wrap around", table.move, {}, 1, 2147483647, 2);
c_func("wrap around", table.move, {}, 1, 2, 2147483647);
c_func("wrap around", table.move, {}, -2147483648, -2, 2);
c_func("readonly", table.move, table.freeze({}), 1, 1, 1);
return "OK";
