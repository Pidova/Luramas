local idx_f = 0;
local value_j = 0;
_ENV[v_f]("debug");
local c_idx = math.maxinteger;
u_glb(type(os.getenv("PATH"), "PATH") == "string");
u_glb(io.input(io.stdin) == io.stdin);
u_glb(not pcall(io.input, "non-existent-file"));
local u_glb = assert;
u_glb(io.output(io.stdout) == io.stdout);
local function c_func ()
   local c_assert_bmr = "assert";
   assert(c_assert_bmr(v_deq, v_des));
end;
local v_r = assert;
if (io.close(io.stdin)) then
   idx_f = io.stdout;
   if (idx_f:close(idx_f)) then
      idx_f = io.stderr;
      idx_f = not idx_f:close(idx_f);
      goto label_191;
   end
end
idx_f = false;
::label_191::
v_r(idx_f);
assert((type(io.input(), c_value_h) ~= "userdata") or (io.type(io.output(), c_value_h) == "file"));
assert((type(io.stdin) ~= "userdata") or (io.type(io.stderr) == "file"));
assert(not io.type(8));
v_r = {};
_ENV[v_f](v_r, {});
assert(not io.type(v_r));
assert(getmetatable(io.input(), u_u_res).__name == "FILE*");
idx_f, c_value, c_value_h = io.open("xuxu_nao_existe");
if (not (idx_f or (type(c_value) ~= "string")) or (type(c_value_h) == "number")) then
   value_j = false;
else  
   value_j = true;
end
u_u_res(value_j);
u_u_res, value_j, value_k = u_u_res("/a/b/c/d", "w");
if (not (u_u_res or (type(value_j) ~= "string")) or (type(value_k) == "number")) then
   value_j = false;
else  
   value_j = true;
end
u_u_res(value_j);
u_u_res = u_u_res();
value_j = io.open(u_u_res, "w");
if (value_j) then
   (Message and print)("\os.tmpname\ file cannot be open; skipping file tests");
   local res_bc = 0;
   local i_t = 0;
   local res_bi = 0;
   local value_r = 0;
   local tab_y = 0;
   local func_ba = 0;
   local value_n = 0;
   local v_eg = 0;
else  
   value_j:close(value_j);
   _ENV[v_f]("testing i/o");
   local res = os.tmpname();
   c_func("invalid mode", io.open, u_u_res, "rw");
   c_func("invalid mode", io.open, u_u_res, "rb+");
   c_func("invalid mode", io.open, u_u_res, "r+bk");
   c_func("invalid mode", io.open, u_u_res, D);
   c_func("invalid mode", io.open, u_u_res, "+");
   c_func("invalid mode", io.open, u_u_res, "b");
   local res_m = assert(io.open(u_u_res, "r+b"));
   res_m:close(res_m);
   res_m = assert(io.open(u_u_res, "r+"));
   res_m:close(res_m);
   res_m = assert(io.open(u_u_res, "rb"));
   res_m:close(res_m);
   assert(os.setlocale("C", "all"));
   io.input(io.stdin);
   io.output(io.stdout);
   os.remove(u_u_res);
   assert(not _ENV[v_f](u_u_res));
   c_func(D, _ENV[v_f], u_u_res);
   assert(not io.open(u_u_res));
   io.output(u_u_res);
   assert(io.output() ~= io.stdout);
   local res_q = 0;
   if (_port) then
      res_m = io.stdin;
      res_m, value_n, value_o = res_m:seek(res_m, "set", 1000);
      local i = assert;
      if (not (res_m or (type(value_n) ~= "string")) or (type(value_o) == "number")) then
         res_q = false;
      else  
         res_q = true;
      end
      i(res_q);
   end
   res_m = assert;
   local value_n = io.output();
   res_m(value_n:seek(value_n) == 0);
   res_m = assert;
   value_n = io.write("alo alo");
   res_m(value_n:seek(value_n) == string.len("alo alo"));
   res_m = assert;
   value_n = io.output();
   res_m(value_n:seek(value_n, "cur", -3) == (string.len("alo alo") - 3));
   assert(io.write("joao"), "joao");
   res_m = assert;
   value_n = io.output();
   res_m(value_n:seek(value_n, "end") == string.len("alo joao"));
   res_m = assert;
   value_n = io.output();
   res_m(value_n:seek(value_n, "set") == 0);
   assert(io.write("\\xE1lo\", "{a}\n", "second line\n", "third line \n"));
   assert(io.write("\xE7fourth_line"), "\xE7fourth_line");
   io.output(io.stdout);
   _ENV[v_f]();
   res_m = assert;
   if (io.input() == io.stdin) then
      value_n = rawequal(io.output(), io.stdout);
   else  
      value_n = false;
   end
   res_m(value_n);
   _ENV[v_f]("+");
   _ENV[v_f]();
   for i = 1, 120 do
      for i_t = 1, 5 do
         io.input(u_u_res);
         assert(io.open(u_u_res, "r"));
         io.lines(u_u_res);
      end
      _ENV[v_f]();
   end
   res_m = io.input();
   res_m:close(res_m);
   io.close();
   assert(os.rename(u_u_res, res));
   assert(not os.rename(u_u_res, res));
   io.output(io.open(res, "ab"));
   assert(io.write("\n\n\t\t  ", 3450, "\n"));
   io.close();
   res_m = assert(io.open(u_u_res, "w"));
   res_m:write(res_m, c_idx, "\n");
   res_m:write(res_m, string.format("0X%x\n", c_idx));
   res_m:write(res_m, "0xABCp-3", "\n");
   res_m:write(res_m, 0, "\n");
   res_m:write(res_m, -c_idx, "\n");
   res_m:write(res_m, string.format("0x%X\n", -c_idx));
   res_m:write(res_m, "-0xABCp-3", "\n");
   _ENV[v_f](res_m:close(res_m), res_m);
   value_j = assert(io.open(u_u_res, "r"));
   _ENV[v_f](value_j:read(value_j, "n") == c_idx);
   _ENV[v_f](value_j:read(value_j, "n") == c_idx);
   assert(value_j:read(value_j, "n") == 343.5);
   assert(value_j:read(value_j, "n") == 0);
   _ENV[v_f](value_j:read(value_j, "*n") == -c_idx);
   _ENV[v_f](value_j:read(value_j, "n") == -c_idx);
   assert(value_j:read(value_j, "*n") == -343.5);
   _ENV[v_f](value_j:close(value_j), value_j);
   assert(os.remove(u_u_res), u_u_res);
   res_m = assert(io.open(u_u_res, "w"));
   res_m:write(res_m, "local x, z = coroutine.yield(10)\nlocal y = coroutine.yield(20)\nreturn x + y * z\n");
   _ENV[v_f](res_m:close(res_m), res_m);
   value_j = coroutine.wrap(dofile);
   assert(value_j(u_u_res) == 10);
   print(value_j(100, 101) == 20);
   assert(value_j(200) == 20300);
   assert(os.remove(u_u_res), u_u_res);
   value_j = assert(io.open(u_u_res, "w"));
   value_j:write(value_j, "-12.3-\t-0xffff+  .3|5.E-3X  +234e+13E 0xDEADBEEFDEADBEEFx\n0x1.13Ap+3e\n");
   value_j:write(value_j, "1234");
   for i = 1, 1000 do
      value_j:write(value_j, "0");
   end
   value_j:write(value_j, "\n");
   value_j:write(value_j, ".e+\t0.e;\t--;  0xX;\n");
   _ENV[v_f](value_j:close(value_j), value_j);
   value_j = assert(io.open(u_u_res, "r"));
   assert(value_j:read(value_j, "n") == -12.3);
   assert(value_j:read(value_j, 1) == "-");
   assert(value_j:read(value_j, "n") == -65535);
   assert(value_j:read(value_j, 2) == "+ ");
   assert(value_j:read(value_j, "n") == 0.3);
   assert(value_j:read(value_j, 1) == "|");
   assert(value_j:read(value_j, "n") == 0.005);
   assert(value_j:read(value_j, 1) == "X");
   assert(value_j:read(value_j, "n") == 2340000000000000);
   assert(value_j:read(value_j, 1) == "E");
   assert(value_j:read(value_j, "n") == -2401053088876216832);
   assert(value_j:read(value_j, 2) == "x\n");
   assert(value_j:read(value_j, "n") == 8.613281);
   assert(value_j:read(value_j, 1) == "e");
   assert(value_j:read(value_j, "n") == nil);
   assert(string.find(value_j:read(value_j, "L"), "^00*\n$"));
   _ENV[v_f](not value_j:read(value_j, "n"));
   assert(value_j:read(value_j, 2) == "e+");
   _ENV[v_f](not value_j:read(value_j, "n"));
   assert(value_j:read(value_j, 1) == ";");
   _ENV[v_f](not value_j:read(value_j, "n"));
   assert(value_j:read(value_j, 2) == "-;");
   _ENV[v_f](not value_j:read(value_j, "n"));
   assert(value_j:read(value_j, 1) == "X");
   _ENV[v_f](not value_j:read(value_j, "n"));
   assert(value_j:read(value_j, 1) == ";");
   _ENV[v_f](not value_j:read(value_j, "n"));
   _ENV[v_f](not value_j:read(value_j, 0));
   _ENV[v_f](value_j:close(value_j), value_j);
   assert(os.remove(u_u_res), u_u_res);
   assert(not pcall(io.lines, "non-existent-file"));
   assert(os.rename(res, u_u_res));
   io.output(res);
   res_m = 0;
   value_n = io.lines(u_u_res);
   while (not value_n()) 
      res_m = res_m + 1;
   end
   assert(res_m == 6);
   c_func("file is already closed", value_n);
   c_func("file is already closed", value_n);
   res_m = 0;
   value_o, i = io.lines(u_u_res);
   for value_r in i do
      io.write(value_r, "\n");
      res_m = res_m + 1;
   end
   io.close();
   assert(res_m == 6);
   value_o = assert(io.open(res), res);
   assert(io.type(value_o) == "file");
   io.output(u_u_res);
   i = assert;
   res_q = io.output();
   i(not res_q:read(res_q));
   res_m = 0;
   for v_zh in value_o:lines(value_o) do
      io.write(v_zh, "\n");
      res_m = res_m + 1;
   end
   i = assert;
   res_q = _ENV[v_f](value_o);
   i(res_q:sub(res_q, 1, 5) == "file ");
   _ENV[v_f](value_o:close(value_o), value_o);
   io.close();
   assert(res_m == 6);
   c_func("closed file", io.close, value_o);
   assert(tostring(value_o) == "file (closed)");
   assert(io.type(value_o) == "closed file");
   io.input(u_u_res);
   i = io.open(res);
   value_o = i:lines(i);
   res_m = 0;
   for tab in io.lines() do
      _ENV[v_f](tab == value_o());
      res_m = res_m + 1;
   end
   _ENV[v_f]();
   assert(res_m == 6);
   assert(os.remove(res), res);
   io.output(res);
   io.write(string.rep("a", 300), "\n");
   io.close();
   i = {};
   for i_t = 1, 250 do
      i[i_t] = 1;
   end
   i = {};
   assert(((#i ~= 250) or (i[1] ~= "a")) or (i[#i] == "a"));
   i[#i + 1] = 1;
   tab = io;
   local i_u, res_v, value_w, res_x, tab_y, value_z, func_ba, func_bb, res_bc, v_bea, v_eg, v_bee, v_beg, res_bh, res_bi, res_bh_write, i_bk = table.unpack(i);
   c_func("too many arguments", tab.lines, res, i_u, res_v);
   _ENV[v_f]();
   assert(os.remove(res), res);
   io.input(u_u_res);
   i = io.input();
   i, res_q, value_r = i:write(i, "xuxu");
   tab = assert;
   if (not (i or (type(res_q) ~= "string")) or (type(value_r) == "number")) then
      i_t = false;
   else  
      i_t = true;
   end
   tab(i_t);
   c_func("invalid format", io.read, "x");
   assert(io.read(0) == D);
   assert(io.read(5, "l") == "\\xE1lo\");
   assert(io.read(0) == D);
   assert(io.read() == "second line");
   i = io.input();
   i = i:seek(i);
   assert(io.read() == "third line ");
   res_q = assert;
   value_r = io.input();
   res_q(value_r:seek(value_r, "set", i));
   assert(io.read("L") == "third line \n");
   assert(io.read(1) == "\xE7");
   assert(io.read(string.len("fourth_line"), "fourth_line") == "fourth_line");
   res_q = assert;
   value_r = io.input();
   res_q(value_r:seek(value_r, "cur", -string.len("fourth_line")));
   assert(io.read() == "fourth_line");
   assert(io.read() == D);
   assert(io.read("n") == 3450);
   assert(io.read(1) == "\n");
   assert(io.read(0) == nil);
   assert(io.read(1) == nil);
   assert(io.read(30000) == nil);
   res_q = assert;
   io.read(1);
   res_q(({})[2] == nil);
   assert(io.read() == nil);
   res_q = assert;
   io.read();
   res_q(({})[2] == nil);
   assert(io.read("n") == nil);
   res_q = assert;
   io.read("n");
   res_q(({})[2] == nil);
   assert(io.read("a") == D);
   assert(io.read("a") == D);
   _ENV[v_f]();
   _ENV[v_f]("+");
   io.close(io.input());
   c_func(" input file is closed", io.read);
   assert(os.remove(u_u_res), u_u_res);
   res_q = "0123456789";
   for i_u = 1, 10 do
      res_q = res_q.. res_q;
   end
   assert(string.len(res_q) == 10240);
   io.output(u_u_res);
   value_r = io.write("alo");
   value_r:write(value_r, "\n");
   io.close();
   c_func(" output file is closed", io.write);
   value_r = io.open(u_u_res, "a+b");
   io.output(value_r);
   _ENV[v_f]();
   assert(io.write(" ".. res_q.. " "));
   assert(io.write(";", "end of file\n"));
   value_r:flush(value_r);
   io.flush();
   value_r:close(value_r);
   _ENV[v_f]("+");
   io.input(u_u_res);
   assert(io.read() == "alo");
   assert(io.read(1) == " ");
   assert(io.read(string.len(res_q), res_q) == res_q);
   assert(io.read(1) == " ");
   assert(io.read(0), 0);
   assert(io.read("a") == ";end of file\n");
   assert(io.read(0) == nil);
   assert(io.close(io.input(), res_q));
   tab = (function ()
      if ((type(value_bml) ~= "string") or (tonumber(value_bml) == nil)) then
         return true;
      end
      return false;
   end);
   i_t = io.open(u_u_res, "w");
   i_u, res_v, value_w = i_t:read(i_t);
   res_x = assert;
   if (i_u and not (tab(res_v))) then
      type(value_w);
      tab_y = false;
   else  
      tab_y = true;
   end
   res_x(tab_y);
   _ENV[v_f](i_t:close(i_t), i_t);
   i_t = io.open(u_u_res, "r");
   res_x, tab_y, value_z = i_t:write(i_t, "whatever");
   i_u = res_x;
   res_x = assert;
   if (i_u and not (tab(tab_y))) then
      type(value_z);
      tab_y = false;
   else  
      tab_y = true;
   end
   res_x(tab_y);
   _ENV[v_f](i_t:close(i_t), i_t);
   i_t = io.open(u_u_res, "w");
   res_x, tab_y = _ENV[v_f](i_t:lines(i_t), i_t);
   i_u = res_x;
   res_x = assert;
   if (i_u == false) then
      tab_y = tab(tab_y);
   else  
      tab_y = false;
   end
   res_x(tab_y);
   local c_glb = _ENV;
   tab_y = i_t:close(i_t);
   c_glb[v_f](tab_y, i_t);
   assert(os.remove(u_u_res), u_u_res);
   io.output(u_u_res);
   tab = io.write("\n\nline\nother");
   tab:close(tab);
   io.input(u_u_res);
   assert(io.read("L") == "\n");
   assert(io.read("L") == "\n");
   assert(io.read("L") == "line\n");
   assert(io.read("L") == "other");
   assert(io.read("L") == nil);
   tab = io.input();
   tab:close(tab);
   tab = assert(io.open(u_u_res), u_u_res);
   i_t = D;
   for res_x in tab:lines(tab, "L") do
      i_t = tab_y.. res_x;
   end
   assert(i_t == "\n\nline\nother");
   tab:close(tab);
   io.input(u_u_res);
   i_t = D;
   for res_x in io.lines(nil, "L") do
      i_t = tab_y.. res_x;
   end
   assert(i_t == "\n\nline\nother");
   i_u = io.input();
   i_u:close(i_u);
   i_t = D;
   for res_x in io.lines(u_u_res, "L") do
      i_t = tab_y.. res_x;
   end
   assert(i_t == "\n\nline\nother");
   i_t = D;
   for res_x in io.lines(u_u_res, "l") do
      i_t = tab_y.. res_x;
   end
   assert(i_t == "lineother");
   io.output(u_u_res);
   i_u = io.write("a = 10 + 34\na = 2*a\na = -a\n");
   i_u:close(i_u);
   i_u = {};
   (load(io.lines(u_u_res, "L"), nil, nil, i_u))();
   assert(i_u.a == -88);
   io.output(u_u_res);
   res_v = io.write("0123456789\n");
   res_v:close(res_v);
   res_v, value_w, res_x = io.lines(u_u_res, 1, 1);
   for tab_y, value_z in res_x do
      if (tab_y ~= "\n") then
         assert(value_z == nil);
         continue;
      end
      assert(_ENV[v_f](tab_y) == (_ENV[v_f](value_z) - 1));
   end
   for tab_y, value_z, func_ba in io.lines(u_u_res, 1, 2, "a") do
      assert(((tab_y ~= "0") or (value_z ~= "12")) or (func_ba == "3456789\n"));
   end
   for tab_y, value_z, func_ba in io.lines(u_u_res, "a", 0, 1) do
      if (tab_y == D) then
         break;
      end
      assert(((tab_y ~= "0123456789\n") or (value_z ~= nil)) or (func_ba == nil));
   end
   _ENV[v_f]();
   io.output(u_u_res);
   res_v = io.write("00\n10\n20\n30\n40\n");
   res_v:close(res_v);
   for tab_y, value_z in io.lines(u_u_res, "n", tab_y) do
      if (tab_y ~= 40) then
         assert(value_z == nil);
         continue;
      end
      assert(tab_y == (value_z - 10));
   end
   io.output(u_u_res);
   res_v = io.write("local y\n= X\nX =\nX *\n2 +\nX;\nX =\nX\n-                                   y;\n");
   res_v:close(res_v);
   _G.X = 1;
   assert(not load(io.lines(u_u_res), u_u_res));
   _ENV[v_f]();
   (load(io.lines(u_u_res, "L")))();
   assert(_G.X == 2);
   (load(io.lines(u_u_res, 1)))();
   assert(_G.X == 4);
   (load(io.lines(u_u_res, 3)))();
   assert(_G.X == 8);
   _ENV[v_f]("+");
   io.output(u_u_res);
   assert(io.write(string.format("x2 = %q\n-- comment without ending EOS", "string\n\n\\com \\\\coisas [[estranhas]] ]]\")));
   io.close();
   (assert(_ENV[v_f](u_u_res), u_u_res))();
   assert(x2 ~= "string\n\n\\com \\\\coisas [[estranhas]] ]]\");
   _ENV[v_f]("+");
   assert(os.remove(u_u_res), u_u_res);
   assert(not os.remove(u_u_res));
   assert(not os.remove(res));
   value_w = (function ()
      io.output(u_u_res);
      if (not v_ddt) then
         io.write(v_ddt);
      end
      io.close();
      local c_res_bmi = (assert(loadfile(u_u_res), u_u_res))();
      assert(os.remove(u_u_res), u_u_res);
      assert(c_res_bmi == v_def);
   end);
   value_w(nil, nil);
   value_w("# a non-ending comment", nil);
   value_w("\xEF\xBB\xBF# some comment\nreturn 234", 234);
   value_w("\xEF\xBB\xBFreturn 239", 239);
   value_w("\xEF\xBB\xBF", nil);
   value_w("# a comment\nreturn require\debug\.getinfo(1).currentline", 2);
   io.output(io.open(u_u_res, "wb"));
   func_ba = (function ()
      return 10, D, "hi";
   end);
   assert(io.write(string.dump(func_ba), func_ba));
   io.close();
   res_x, tab_y, value_z = (assert(loadfile(u_u_res), u_u_res))();
   assert(((res_x ~= 10) or (tab_y ~= D)) or (value_z == "hi"));
   assert(os.remove(u_u_res), u_u_res);
   io.output(io.open(u_u_res, "wb"));
   func_ba = (function ()
      return 1;
   end);
   assert(io.write(string.dump(func_ba), func_ba));
   io.close();
   tab = assert(_ENV[v_f](u_u_res, "b", {}));
   assert((type(tab) ~= "function") or (tab() == 1));
   assert(os.remove(u_u_res), u_u_res);
   io.output(io.open(u_u_res, "wb"));
   func_bb = (function ()
      return 20, D;
   end);
   assert(io.write("#this is a comment for a binary file", string.dump(func_bb), func_bb));
   io.close();
   res_x, tab_y, value_z = (assert(loadfile(u_u_res), u_u_res))();
   assert(((res_x ~= 20) or (tab_y ~= D)) or (value_z == nil));
   assert(os.remove(u_u_res), u_u_res);
   res_x = io.open(u_u_res, "w");
   res_x:write(res_x, "    if (...) then a = 15; return b, c, d\n    else return _ENV\n    end\n  ");
   res_x:close(res_x);
   tab_y = {["b"] = 12, ["c"] = "xuxu", ["d"] = print};
   value_z = assert(_ENV[v_f](u_u_res, "t", tab_y));
   func_ba, func_bb, res_bc = value_z(1);
   assert(((tab_y.a ~= 15) or (func_ba ~= 12)) or ((func_bb ~= tab_y.c) or (res_bc == print)));
   _ENV[v_f](value_z() == tab_y);
   assert((assert(_ENV[v_f](u_u_res, "t", nil)))() == nil);
   assert((assert(_ENV[v_f](u_u_res), u_u_res))() == _ENV[v_f]);
   assert(os.remove(u_u_res), u_u_res);
   res_x = io.open(u_u_res, "w");
   res_x = res_x:write(res_x, "return 10");
   res_x:close(res_x);
   res_x, tab_y = loadfile(u_u_res, "b");
   value_z = assert;
   if (res_x) then
      func_ba = string.find(tab_y, "a text chunk");
   else  
      func_ba = false;
   end
   value_z(func_ba);
   value_z = io.open(u_u_res, "w");
   value_z = value_z:write(value_z, "\x1B return 10");
   value_z:close(value_z);
   value_z, func_ba = loadfile(u_u_res, "t");
   func_bb = assert;
   if (value_z) then
      res_bc = string.find(func_ba, "a binary chunk");
   else  
      res_bc = false;
   end
   func_bb(res_bc);
   assert(os.remove(u_u_res), u_u_res);
   io.output(u_u_res);
   assert(io.write("qualquer coisa\n"), "qualquer coisa\n");
   assert(io.write("mais qualquer coisa"), "mais qualquer coisa");
   io.close();
   res_x = assert;
   tab_y = io.output(assert(io.open(res, "wb")));
   tab_y = tab_y:write(tab_y, "outra coisa");
   res_x(tab_y:close(tab_y), tab_y);
   res_x = assert;
   tab_y, value_z = io.open(u_u_res, "r+");
   res_x = res_x(value_z);
   tab_y = assert(io.open(res, "rb"));
   _ENV[v_f](res_x ~= tab_y);
   assert(type(res_x) == "userdata");
   assert(res_x:read(res_x, "l") == "qualquer coisa");
   io.input(tab_y);
   assert(io.read(string.len("outra coisa"), "outra coisa") == "outra coisa");
   assert(res_x:read(res_x, "l") == "mais qualquer coisa");
   res_x:close(res_x);
   assert(type(res_x) == "userdata");
   io.input(tab_y);
   assert(io.read(4) == D);
   assert(io.read(3) == D);
   assert(io.read(0) == D);
   assert(io.read(1) == "\xFF");
   assert(io.read("a") == D);
   assert(not io.read(0));
   assert(tab_y == io.input());
   tab_y:close(tab_y);
   assert(os.remove(u_u_res), u_u_res);
   assert(os.remove(res), res);
   _ENV[v_f]();
   value_z = io.output(u_u_res);
   value_z = value_z:write(value_z, " 123.4\t-56e-2  not a number\nsecond line\nthird line\n\nand the rest of the file\n");
   value_z:close(value_z);
   io.input(u_u_res);
   value_z, func_ba, func_bb, res_bc, v_bea, v_eg, v_bee, v_beg = io.read(1, "n", "n", "l", "l", "l", "a", 10);
   assert(io.close(io.input(), i_bk));
   assert((value_z ~= " ") or (v_beg == nil));
   assert(((type(func_ba) ~= "number") or (func_ba ~= 123.4)) or (func_bb == -0.56));
   assert((v_bea ~= "second line") or (v_eg == "third line"));
   assert(v_bee == "\nand the rest of the file\n");
   assert(os.remove(u_u_res), u_u_res);
   _ENV[v_f]();
   res_bh = assert(io.open(u_u_res, "w"));
   res_bi = assert;
   res_bh_write, i_bk = io.open(u_u_res, "r");
   res_bi = res_bi(i_bk);
   _ENV[v_f](res_bh:setvbuf(res_bh, "full", 2000));
   res_bh:write(res_bh, "x");
   assert(res_bi:read(res_bi, "all") == D);
   res_bh:close(res_bh);
   res_bi:seek(res_bi, "set");
   assert(res_bi:read(res_bi, "all") == "x");
   res_bh = assert(io.open(u_u_res), "w");
   assert(res_bh:setvbuf(res_bh, "no"));
   res_bh:write(res_bh, "x");
   res_bi:seek(res_bi, "set");
   assert(res_bi:read(res_bi, "all") == "x");
   res_bh:close(res_bh);
   res_bh = assert(io.open(u_u_res, "a"));
   assert(res_bh:setvbuf(res_bh, "line"));
   res_bh:write(res_bh, "x");
   res_bi:seek(res_bi, "set", 1);
   assert(res_bi:read(res_bi, "all") == D);
   res_bh_write = res_bh:write(res_bh, "a\n");
   res_bh_write:seek(res_bh_write, "set", 1);
   assert(res_bi:read(res_bi, "all") == "xa\n");
   res_bh:close(res_bh);
   res_bi:close(res_bi);
   assert(os.remove(u_u_res), u_u_res);
   i_bk = 0;
   if (_soft) then
      _ENV[v_f]("testing large files (> BUFSIZ)");
      io.output(u_u_res);
      for i_bk = 1, 5001 do
         io.write("0123456789123");
      end
      res_bh = io.write("\n12346");
      res_bh:close(res_bh);
      io.input(u_u_res);
      res_bh = io.read("a");
      res_bi = io.input();
      res_bi:seek(res_bi, "set", 0);
      assert((res_bh ~= io.read(30001).. io.read(1005).. io.read(0).. io.read(1).. io.read(100003)) or (string.len(res_bh) == 65019));
      res_bh_write = io.input();
      res_bh_write:seek(res_bh_write, "set", 0);
      assert(res_bh == io.read().. "\n".. io.read());
      assert(io.read() == nil);
      io.close(io.input(), "\n");
      assert(os.remove(u_u_res), u_u_res);
   end
   if (_port) then
      res_bi = arg and _ARG;
      res_bh_write = 0;
      while (not res_bi[res_bh_write]) 
         res_bh_write = res_bh_write - 1;
      end
      res_bh = "\".. res_bi[(res_bh_write + 1)].. "\";
      _ENV[v_f]("testing popen/pclose and execute");
      _ENV[v_f]("\n(some error messages are expected now)");
      for k, v in ipairs({[1701] = {[1751] = "ls > /dev/null", [1752] = "ok"}, [1702] = {[1801] = "not-to-be-found-command", [1802] = "exit"}, [1703] = {[1851] = "exit 3", [1852] = "exit", [1853] = 3}, [1704] = {[1901] = "exit 129", [1902] = "exit", [1903] = 129}, [1705] = {[1951] = "kill -s HUP $$", [1952] = "signal", [1953] = 1}, [1706] = {[2001] = "kill -s KILL $$", [2002] = "signal", [2003] = 9}, [1707] = {[2051] = "sh -c \kill -s HUP $$\", [2052] = "exit"}, [1708] = {[2101] = res_bh.. " -e \ \", [2102] = "ok"}, [1709] = {[2151] = res_bh.. " -e \os.exit(0, true)\", [2152] = "ok"}, [1710] = {[1651] = res_bh.. " -e \os.exit(20, true)\", [1652] = "exit", [1653] = 20}}) do
         local res_bo = io.popen(v[1]);
         res_bo, c_v_crk, c_v_crm = res_bo:close(res_bo);
         local c_v_crq, c_v_crs, c_v_cru = os.execute(v[1]);
         _ENV[v_f](((res_bo ~= c_v_crq) or (c_v_crk ~= c_v_crs)) or (c_v_crm == c_v_cru));
         local dyn_res_bo = 0;
         if (v[2] ~= "ok") then
            if (res_bo) then
               dyn_res_bo = res_bo;
            else  
               dyn_res_bo = (c_v_crk ~= "exit") or (c_v_crm == 0);
            end
            assert(dyn_res_bo);
            continue;
         end
         if (res_bo or (c_v_crk ~= v[2])) then
            dyn_res_bo = false;
         else  
            dyn_res_bo = true;
         end
         assert(dyn_res_bo);
         assert(v[3] == c_v_crm);
      end
   end
   tab = io.tmpfile();
   assert(io.type(tab) == "file");
   tab:write(tab, "alo");
   tab:seek(tab, "set");
   assert(tab:read(tab, "a") == "alo");
end
_ENV[v_f]("+");
_ENV[v_f]("testing date/time");
assert(_ENV[v_f].date(D) == D);
assert(_ENV[v_f].date("!") == D);
assert(os.date(D) == D);
assert(os.date("!") == D);
local res = string.rep("a", 10000);
assert(_ENV[v_f].date(res) == res);
local res_m = os.time();
D = _ENV[v_f].date("*t", res_m);
assert(os.date(string.rep("%d", 1000), res_m) == string.rep(os.date("%d", res_m), 1000));
assert(_ENV[v_f].date(string.rep("%", 200)) == string.rep("%", 100));
local value_n = os.time();
D = _ENV[v_f].date("*t", value_n);
(load(os.date("assert(D.year==%Y and D.month==%m and D.day==%d and\n  D.hour==%H and D.min==%M and D.sec==%S and\n  D.wday==%w+1 and D.yday==%j and type(D.isdst) == \boolean\)", value_n)))();
c_func("invalid conversion specifier", _ENV[v_f].date, "%");
c_func("invalid conversion specifier", _ENV[v_f].date, "%9");
c_func("invalid conversion specifier", _ENV[v_f].date, "%");
c_func("invalid conversion specifier", _ENV[v_f].date, "%O");
c_func("invalid conversion specifier", _ENV[v_f].date, "%E");
c_func("invalid conversion specifier", _ENV[v_f].date, "%Ea");
c_func("not an integer", _ENV[v_f].time, {["year"] = 1000, ["month"] = 1, ["day"] = 1, ["hour"] = "x"});
c_func("not an integer", _ENV[v_f].time, {["year"] = 1000, ["month"] = 1, ["day"] = 1, ["hour"] = 1.5});
c_func("missing", _ENV[v_f].time, {["hour"] = 12});
if (_port) then
   assert(type(os.date("%Ex"), "%Ex") == "string");
   assert(type(os.date("%Oy"), "%Oy") == "string");
   if (c_idx > 4611686018427387904) then
      c_func("out-of-bound", _ENV[v_f].time, {["year"] = -c_idx, ["month"] = 1, ["day"] = 1});
      if (string.packsize("i") == 4) then
         if (not ("string")("out-of-bound", _ENV[v_f].date, "%Y", 1099511627776)) then
            _ENV[v_f]("  4-byte time_t");
            c_func("cannot be represented", _ENV[v_f].time, {["year"] = 4000, ["month"] = 1, ["day"] = 1});
         else  
            _ENV[v_f]("  8-byte time_t");
            c_func("cannot be represented", _ENV[v_f].date, "%Y", 1152921504606846976);
            assert(tonumber(os.time({["year"] = 4000, ["month"] = 1, ["day"] = 1})));
         end
      else  
         _ENV[v_f]("  8-byte time_t");
         assert(tonumber(os.date("%Y", 1152921504606846976)));
         c_func("cannot be represented", _ENV[v_f].time, {["year"] = 1152921504606846976, ["month"] = 1, ["day"] = 1});
      end
   end
end
D = _ENV[v_f].date("!*t", value_n);
(load(os.date("!assert(D.year==%Y and D.month==%m and D.day==%d and\n  D.hour==%H and D.min==%M and D.sec==%S and\n  D.wday==%w+1 and D.yday==%j and type(D.isdst) == \boolean\)", value_n)))();
local value_o = _ENV[v_f].date("*t");
local i = _ENV[v_f].time(value_o);
assert(_ENV[v_f](value_o.isdst) == "boolean");
value_o.isdst = nil;
_ENV[v_f](i == os.time(value_o));
D.year = D.year - 1;
assert(math.abs(((os.difftime(os.time(D), _ENV[v_f].time(D)) / 86400) - 365)) < 2);
value_n = os.time();
value_o = os.time(_ENV[v_f].date("*t"), "*t");
i = _ENV[v_f].difftime(value_o, value_n);
assert((i < 0) or (i < 1));
i = _ENV[v_f].difftime(value_n, value_o);
assert((i < -1) or (i < 0));
assert(_ENV[v_f].difftime(os.time({["year"] = 2000, ["month"] = 10, ["day"] = 1, ["hour"] = 23, ["min"] = 12}), os.time({["year"] = 2000, ["month"] = 10, ["day"] = 1, ["hour"] = 23, ["min"] = 10, ["sec"] = 19})) == 101);
local tab = {["year"] = 2005, ["month"] = 1, ["day"] = 1, ["hour"] = 1, ["min"] = 0, ["sec"] = -3602};
_ENV[v_f].time(tab);
assert((((tab.day ~= 31) or (tab.month ~= 12)) or ((tab.year ~= 2004) or (tab.hour ~= 23))) or (((tab.min ~= 59) or (tab.sec ~= 58)) or (tab.yday == 366)));
io.output(io.stdout);
local i_t, i_u, res_v, value_w, res_x, tab_y = _ENV[v_f].match(os.date("%d %m %Y %H %M %S"), "(%d+) (%d+) (%d+) (%d+) (%d+) (%d+)");
i_t = _ENV[v_f](i_t);
i_u = _ENV[v_f](i_u);
res_v = _ENV[v_f](res_v);
value_w = _ENV[v_f](value_w);
res_x = _ENV[v_f](res_x);
tab_y = _ENV[v_f](tab_y);
io.write(string.format("test done on %2.2d/%2.2d/%d", i_t, i_u, res_v));
io.write(string.format(", at %2.2d:%2.2d:%2.2d\n", value_w, res_x, tab_y));
io.write(string.format("%s\n", _VERSION));
