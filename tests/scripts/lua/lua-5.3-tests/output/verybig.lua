print(u_func);
u_func();
if (not _soft) then
   return 10;
end
u_func("testing large programs (>64k)");
prog = "$\n\nlocal a,b\n\nb = {$1$\n  b30009 = 65534,\n  b30010 = 65535,\n  b30011 = 65536,\n  b30012 = 65537,\n  b30013 = 16777214,\n  b30014 = 16777215,\n  b30015 = 16777216,\n  b30016 = 16777217,\n  b30017 = 0x7fffff,\n  b30018 = -0x7fffff,\n  b30019 = 0x1ffffff,\n  b30020 = -0x1ffffd,\n  b30021 = -65534,\n  b30022 = -65535,\n  b30023 = -65536,\n  b30024 = -0xffffff,\n  b30025 = 15012.5,\n  $2$\n};\n\nassert(b.a50008 == 25004 and b[\a11\] == -5.5)\nassert(b.a33007 == -16503.5 and b.a50009 == -25004.5)\nassert(b[\b\..30024] == -0xffffff)\n\nfunction b:xxx (a,b) return a+b end\nassert(b:xxx(10, 12) == 22)   -- pushself with non-constant index\nb.xxx = nil\n\ns = 0; n=0\nfor a,b in pairs(b) do s=s+b; n=n+1 end\n-- with 32-bit floats, exact value of \s\ depends on summation order\nassert(81800000.0 < s and s < 81860000 and n == 70001)\n\na = nil; b = nil\nprint\+\\n\nfunction f(x) b=x end\n\na = f{$3$} or 10\n\nassert(a==10)\nassert(b[1] == \a10\ and b[2] == 5 and b[#b-1] == \a50009\)\n\n\nfunction xxxx (x) return b[x] end\n\nassert(xxxx(3) == \a11\)\n\na = nil; b=nil\nxxxx = nil\n\nreturn 10\n\n";
local function u_func ()
   return "-";
end;
F = {[-48] = (function ()
   for c_i_c = 30026, 50009 do
      local c_io_jz = "io";
      (_ENV[c_io_jz].write)("b", val_g, " = ", c_io_jz(val_g), ((val_g - 30026) / 2) + 15013, ",\n");
   end
end), [-47] = (function ()
   for c_i = 10, 50009 do
      local c_io_jy = "io";
      (_ENV[c_io_jy].write)("\a", val, "\, ", c_io_jy(val), ((val - 10) / 2) + 5, ",\n");
   end
end)};
file = ()os.tmpname();
file_jx = "file";
(io.output)(_ENV[file_jx]);
(io.close)();
result = dofile(file);
local c_glb = file;
assert(()os.remove(c_glb), c_glb);
file_jx = "print";
(_ENV[file_jx])("OK");
return result;
