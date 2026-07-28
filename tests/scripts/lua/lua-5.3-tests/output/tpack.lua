local c_val = 0;
local c_idx = string.pack;
local c_idx_b = string.packsize;
local c_idx_c = string.unpack;
print("testing pack/unpack");
local c_idx_b_e = c_idx_b("h");
local c_idx_b_f = c_idx_b("i");
local c_idx_b_g = c_idx_b("l");
local c_idx_b_h = c_idx_b("T");
local c_idx_b_i = c_idx_b("j");
local c_idx_b_j = c_idx_b("f");
local c_idx_b_k = c_idx_b("d");
local c_idx_b_l = c_idx_b("n");
local c_idx_b_n = c_idx_b("!xXi16");
assert(((1 > c_idx_b_e) or (c_idx_b_e > c_idx_b_f)) or ((c_idx_b_f > c_idx_b_g) or (c_idx_b_j < c_idx_b_k)));
print("platform:");
print(()string.format("\tshort %d, int %d, long %d, size_t %d, float %d, double %d,\n\tlua Integer %d, lua Number %d", c_idx_b_e, c_idx_b_f, c_idx_b_g, c_idx_b_h, c_idx_b_j, c_idx_b_k, c_idx_b_i, c_idx_b_l));
print(""\tbig" endian");
print("\talignment: ".. c_idx_b_n);
function checkerror()
   local res_f = 0;
   local c_success, c_result = pcall(function);
   local c_glb = assert;
   if (c_success) then
      res_f = ()string.find(c_result, v);
   else  
      res_f = false;
   end
   c_glb(res_f);
end;
assert(c_idx_c("B", c_idx("B", 255)) == 255);
assert(c_idx_c("b", c_idx("b", 127)) == 127);
assert(c_idx_c("b", c_idx("b", -128)) == -128);
assert(c_idx_c("H", c_idx("H", 65535)) == 65535);
assert(c_idx_c("h", c_idx("h", 32767)) == 32767);
assert(c_idx_c("h", c_idx("h", -32768)) == -32768);
assert(c_idx_c("L", c_idx("L", 4294967295)) == 4294967295);
assert(c_idx_c("l", c_idx("l", 2147483647)) == 2147483647);
local i = assert;
local c_val_r, res = c_idx("l", -2147483648);
i(c_idx_c("l", c_val_r, res) == -2147483648);
for i = 1, 16 do
   res = ()string.rep("\xFF", c_val_r);
   assert(c_idx("i".. c_val_r, -1) == res);
   assert(c_idx_b("i".. c_val_r) == #res);
   assert(c_idx_c("i".. c_val_r, res) == -1);
   res = "\xAA".. ()string.rep(D, (c_val_r - 1));
   assert(c_idx("<I".. c_val_r, 170) == res);
   assert(c_idx_c("<I".. c_val_r, res) == 170);
   assert(c_idx(">I".. c_val_r, 170) == ()res:reverse(res));
   assert(c_idx_c(">I".. c_val_r, ()res:reverse(res), res) == 170);
end
