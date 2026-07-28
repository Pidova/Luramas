local function c_func (...)
   local c_success, c_result = pcall(function, ...);
   assert(not c_success and string.find(c_result, v_bk));
end;
function generateClearedTable()
   local tab = {};
   for c_i_f = 1, v do
      tab[c_i_f] = c_i_f;
   end
end;
c_func("table expected", table.clear);
c_func("table expected", table.clear, 1, 2);
assert(#generateClearedTable(0, 0) == 0, "table array part should stay empty");
assert(#generateClearedTable(10, 0) == 0, "table array part should be empty (had array)");
assert(#generateClearedTable(0, 10) == 0, "table array part should be empty (had hash)");
assert(#generateClearedTable(10, 10) == 0, "table array part should be empty (had both)");
assert(next(generateClearedTable(0, 0)) == nil, "table hash part should stay empty");
assert(next(generateClearedTable(10, 0)) == nil, "table hash part should be empty (had array)");
assert(next(generateClearedTable(0, 10)) == nil, "table hash part should be empty (had hash)");
assert(next(generateClearedTable(10, 10)) == nil, "table hash part should be empty (had both)");
for c_i = 1, 16 do
   local res = generateClearedTable(16, 0);
   local res_f = table.create(16);
   res[c_i] = true;
   res_f[c_i] = true;
   assert(#res == #res_f, "table length mismatch with i=" .. c_i .. "(" .. #res .. " vs " .. #res_f .. ")");
end
