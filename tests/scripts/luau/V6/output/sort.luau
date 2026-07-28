print("testing sort");
function checksort(...)
   assert(#v_w == select("#", ...));
   local c_res = table.clone(v_w);
   table.sort(c_res, v_be);
   for c_i_n = 1, #v_w do
      assert(c_res[c_i_n] == select(c_i_n, ...));
   end
end;
checksort({}, nil);
checksort({1}, nil, 1);
checksort({1, 2}, nil, 1, 2);
checksort({2, 1}, nil, 1, 2);
checksort({1, 2, 3}, nil, 1, 2, 3);
checksort({2, 1, 3}, nil, 1, 2, 3);
checksort({1, 3, 2}, nil, 1, 2, 3);
checksort({3, 2, 1}, nil, 1, 2, 3);
checksort({3, 1, 2}, nil, 1, 2, 3);
checksort({
   3, 
   8, 
   1, 
   7, 
   10, 
   2, 
   5, 
   4, 
   9, 
   6}, nil, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
checksort({
   "Jan", 
   "Feb", 
   "Mar", 
   "Apr", 
   "May", 
   "Jun", 
   "Jul", 
   "Aug", 
   "Sep", 
   "Oct", 
   "Nov", 
   "Dec"}, nil, "Apr", "Aug", "Dec", "Feb", "Jan", "Jul", "Jun", "Mar", "May", "Nov", "Oct", "Sep");
checksort({
   3, 
   1, 
   1, 
   7, 
   1, 
   3, 
   5, 
   1, 
   9, 
   3}, nil, 1, 1, 1, 1, 3, 3, 3, 5, 7, 9);
checksort({
   3, 
   8, 
   1, 
   7, 
   10, 
   2, 
   5, 
   4, 
   9, 
   6}, (function ()
   return v_s < v_u;
end), 10, 9, 8, 7, 6, 5, 4, 3, 2, 1);
assert(pcall(table.sort, table.freeze({2, 1})) == false);
assert(pcall(table.sort) == false);
assert(pcall(table.sort, "abc") == false);
assert(pcall(table.sort, {}, 42) == false);
assert(pcall(table.sort, {}, {}) == false);
function check()
   for c_i_e = table.getn(tab), 2, -1 do
      assert(not (v or (function ()
         return v_o < v_q;
      end))(tab[c_i_e], tab[(c_i_e - 1)]));
   end
end;
a = {
   "Jan", 
   "Feb", 
   "Mar", 
   "Apr", 
   "May", 
   "Jun", 
   "Jul", 
   "Aug", 
   "Sep", 
   "Oct", 
   "Nov", 
   "Dec"};
table.sort(a);
check(a);
limit = 30000;
limit = rawget(_G, "_soft") or limit;
a = {};
for c_i = 1, limit do
   a[c_i] = math.random();
end
