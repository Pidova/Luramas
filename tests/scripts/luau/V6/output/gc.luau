print("testing garbage collection");
collectgarbage();
_G["while"] = 234;
limit = 5000;
contCreate = 0;
print("tables");
while (contCreate < limit) do
   contCreate += 1;
end
a = "a";
contCreate = 0;
print("strings");
while (contCreate < limit) do
   a = contCreate .. "b";
   a = string.gsub(a, "(%d%d*)", string.upper);
   a = "a";
   contCreate += 1;
end
contCreate = 0;
a = {};
print("functions");
a.test = (function ()
   while (true) do
      if (contCreate >= limit) then
         return;
      end
      loadstring(string.format("function temp(a) return \'a%d\' end", contCreate))();
      assert(temp() == string.format("a%d", contCreate));
      contCreate += 1;
   end
end);
a:test();
print("long strings");
x = "01234567890123456789012345678901234567890123456789012345678901234567890123456789";
assert(string.len(x) == 80);
s = "";
n = 0;
k = 300;
while (n < k) do
   s = s .. x;
   n += 1;
   j = tostring(n);
end
assert(string.len(s) == (k * 80));
s = string.sub(s, 1, 20000);
s, i = string.gsub(s, "(%d%d%d%d)", math.sin);
assert(i == 4096);
s = nil;
x = nil;
assert(_G["while"] == 234);
local res_a = gcinfo();
while (true) do
   local res_b = gcinfo();
   if (res_b < res_a) then
      break;
   end
   res_a = res_b;
   a = {};
end
local function res_b ()
   collectgarbage();
   collectgarbage("stop");
   local tab = {};
   for c_i_g = 1, 100 do
      tab[c_i_g] = {{}};
   end
end;
assert(res_b(0) > 10);
assert(res_b(6) < res_b(2));
assert(res_b(10000) == 1);
local c_res_c = gcinfo();
collectgarbage();
collectgarbage("stop");
while (gcinfo() < 1000) do
end
collectgarbage("restart");
while (gcinfo() > 1000) do
end
lim = 15;
a = {};
for c_i_f = 1, lim do
   a[{}] = c_i_f;
end
