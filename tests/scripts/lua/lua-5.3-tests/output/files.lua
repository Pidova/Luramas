local idx_f = 0;
local c_val = 0;
local value_j = 0;
local res_t = 0;
(_ENV[v])("debug");
local c_idx = math.maxinteger;
u_glb(type(()os.getenv("PATH"), "PATH") == "string");
u_glb(()io.input(io.stdin) == io.stdin);
u_glb(not pcall(io.input, "non-existent-file"));
local u_glb = assert;
u_glb(()io.output(io.stdout) == io.stdout);
local function c_func ()
   local c_assert_jd = "assert";
   assert(c_assert_jd(v_tp, v_tr));
end;
local v_q = assert;
if (()io.close(io.stdin)) then
   idx_f = io.stdout;
   if (()idx_f:close(idx_f)) then
      idx_f = io.stderr;
      idx_f = not ()idx_f:close(idx_f);
      goto label_191;
   end
end
idx_f = false;
::label_191::
v_q(idx_f);
assert((type(()io.input(), c_value_h) ~= "userdata") or (()io.type(()io.output(), c_value_h) == "file"));
assert((type(io.stdin) ~= "userdata") or (()io.type(io.stderr) == "file"));
assert(not ()io.type(8));
v_q = {};
(_ENV[v])(v_q, {});
assert(not ()io.type(v_q));
assert(getmetatable(()io.input(), u_glb_jx).__name == "FILE*");
idx_f, c_value, c_value_h = ()io.open("xuxu_nao_existe");
local u_glb_jx = assert;
if (not (idx_f or (type(c_value) ~= "string")) or (type(c_value_h) == "number")) then
   value_j = false;
else  
   value_j = true;
end
u_glb_jx(value_j);
u_glb_jx, value_j, value_k = ()io.open("/a/b/c/d", "w");
idx_f = u_glb_jx;
u_glb_jx = assert;
if (not (idx_f or (type(value_j) ~= "string")) or (type(value_k) == "number")) then
   value_j = false;
else  
   value_j = true;
end
u_glb_jx(value_j);
u_glb_jx = ()os.tmpname();
value_j = ()io.open(u_glb_jx, "w");
if (value_j) then
   (Message and print)("\os.tmpname\ file cannot be open; skipping file tests");
   local value_n = 0;
else  
   (value_j:close)(value_j);
   (_ENV[v])("testing i/o");
   (os.tmpname)();
   c_func("invalid mode", io.open, u_glb_jx, "rw");
   c_func("invalid mode", io.open, u_glb_jx, "rb+");
   c_func("invalid mode", io.open, u_glb_jx, "r+bk");
   c_func("invalid mode", io.open, u_glb_jx, D);
   c_func("invalid mode", io.open, u_glb_jx, "+");
   c_func("invalid mode", io.open, u_glb_jx, "b");
   local res = assert(()io.open(u_glb_jx, "r+b"));
   (res:close)(res);
   res = assert(()io.open(u_glb_jx, "r+"));
   (res:close)(res);
   res = assert(()io.open(u_glb_jx, "rb"));
   (res:close)(res);
   assert(()os.setlocale("C", "all"));
   (io.input)(io.stdin);
   (io.output)(io.stdout);
   (os.remove)(u_glb_jx);
   assert(not ()_ENV[v](u_glb_jx));
   c_func(D, _ENV[v], u_glb_jx);
   assert(not ()io.open(u_glb_jx));
   (io.output)(u_glb_jx);
   assert(()io.output() ~= io.stdout);
   local i = 0;
   if (_port) then
      res = io.stdin;
      res, value_n, value_o = ()res:seek(res, "set", 1000);
      local idx_time = assert;
      if (not (res or (type(value_n) ~= "string")) or (type(value_o) == "number")) then
         i = false;
      else  
         i = true;
      end
      idx_time(i);
   end
   res = assert;
   local value_n = ()io.output();
   res(()value_n:seek(value_n) == 0);
   res = assert;
   value_n = ()io.write("alo alo");
   res(()value_n:seek(value_n) == ()string.len("alo alo"));
   res = assert;
   value_n = ()io.output();
   res(()value_n:seek(value_n, "cur", -3) == (()string.len("alo alo") - 3));
   assert(()io.write("joao"), "joao");
   res = assert;
   value_n = ()io.output();
   res(()value_n:seek(value_n, "end") == ()string.len("alo joao"));
   res = assert;
   value_n = ()io.output();
   res(()value_n:seek(value_n, "set") == 0);
   assert(()io.write("\\xE1lo\", "{a}\n", "second line\n", "third line \n"));
   assert(()io.write("\xE7fourth_line"), "\xE7fourth_line");
   (io.output)(io.stdout);
   (_ENV[v])();
   res = assert;
   if (()io.input() == io.stdin) then
      value_n = rawequal(()io.output(), io.stdout);
   else  
      value_n = false;
   end
   res(value_n);
   (_ENV[v])("+");
   (_ENV[v])();
   for res = 1, 120 do
      for i = 1, 5 do
         (io.input)(u_glb_jx);
         assert(()io.open(u_glb_jx, "r"));
         (io.lines)(u_glb_jx);
      end
   end
end
(_ENV[v])("+");
(_ENV[v])("testing date/time");
assert(()_ENV[v].date(D) == D);
assert(()_ENV[v].date("!") == D);
assert(()os.date(D) == D);
assert(()os.date("!") == D);
local c_res_l = ()string.rep("a", 10000);
assert(()_ENV[v].date(c_res_l) == c_res_l);
local res = ()os.time();
D = ()_ENV[v].date("*t", res);
assert(()os.date(()string.rep("%d", 1000), res) == ()string.rep(()os.date("%d", res), 1000));
assert(()_ENV[v].date(()string.rep("%", 200)) == ()string.rep("%", 100));
local value_n = ()os.time();
D = ()_ENV[v].date("*t", value_n);
(load(()os.date("assert(D.year==%Y and D.month==%m and D.day==%d and\n  D.hour==%H and D.min==%M and D.sec==%S and\n  D.wday==%w+1 and D.yday==%j and type(D.isdst) == \boolean\)", value_n)))();
c_func("invalid conversion specifier", _ENV[v].date, "%");
c_func("invalid conversion specifier", _ENV[v].date, "%9");
c_func("invalid conversion specifier", _ENV[v].date, "%");
c_func("invalid conversion specifier", _ENV[v].date, "%O");
c_func("invalid conversion specifier", _ENV[v].date, "%E");
c_func("invalid conversion specifier", _ENV[v].date, "%Ea");
c_func("not an integer", _ENV[v].time, {["year"] = 1000, ["month"] = 1, ["day"] = 1, ["hour"] = "x"});
c_func("not an integer", _ENV[v].time, {["year"] = 1000, ["month"] = 1, ["day"] = 1, ["hour"] = 1.5});
c_func("missing", _ENV[v].time, {["hour"] = 12});
if (_port) then
   assert(type(()os.date("%Ex"), "%Ex") == "string");
   assert(type(()os.date("%Oy"), "%Oy") == "string");
   if (c_idx > 4611686018427387904) then
      c_func("out-of-bound", _ENV[v].time, {["year"] = -c_idx, ["month"] = 1, ["day"] = 1});
      if (()string.packsize("i") == 4) then
         if (not ()"string"("out-of-bound", _ENV[v].date, "%Y", 1099511627776)) then
            (_ENV[v])("  4-byte time_t");
            c_func("cannot be represented", _ENV[v].time, {["year"] = 4000, ["month"] = 1, ["day"] = 1});
         else  
            (_ENV[v])("  8-byte time_t");
            c_func("cannot be represented", _ENV[v].date, "%Y", 1152921504606846976);
            assert(tonumber(()os.time({["year"] = 4000, ["month"] = 1, ["day"] = 1})));
         end
      else  
         (_ENV[v])("  8-byte time_t");
         assert(tonumber(()os.date("%Y", 1152921504606846976)));
         c_func("cannot be represented", _ENV[v].time, {["year"] = 1152921504606846976, ["month"] = 1, ["day"] = 1});
      end
   end
end
D = ()_ENV[v].date("!*t", value_n);
(load(()os.date("!assert(D.year==%Y and D.month==%m and D.day==%d and\n  D.hour==%H and D.min==%M and D.sec==%S and\n  D.wday==%w+1 and D.yday==%j and type(D.isdst) == \boolean\)", value_n)))();
local value_o = ()_ENV[v].date("*t");
local idx_time = ()_ENV[v].time(value_o);
assert(()_ENV[v](value_o.isdst) == "boolean");
value_o.isdst = nil;
(_ENV[v])(idx_time == ()os.time(value_o));
D.year = D.year - 1;
assert(()math.abs(((()os.difftime(()os.time(D), ()_ENV[v].time(D)) / 86400) - 365)) < 2);
value_n = ()os.time();
value_o = ()os.time(()_ENV[v].date("*t"), "*t");
idx_time = ()_ENV[v].difftime(value_o, value_n);
assert((idx_time < 0) or (idx_time < 1));
idx_time = ()_ENV[v].difftime(value_n, value_o);
assert((idx_time < -1) or (idx_time < 0));
assert(()_ENV[v].difftime(()os.time({["year"] = 2000, ["month"] = 10, ["day"] = 1, ["hour"] = 23, ["min"] = 12}), ()os.time({["year"] = 2000, ["month"] = 10, ["day"] = 1, ["hour"] = 23, ["min"] = 10, ["sec"] = 19})) == 101);
local c_tab = {["year"] = 2005, ["month"] = 1, ["day"] = 1, ["hour"] = 1, ["min"] = 0, ["sec"] = -3602};
(_ENV[v].time)(c_tab);
assert((((c_tab.day ~= 31) or (c_tab.month ~= 12)) or ((c_tab.year ~= 2004) or (c_tab.hour ~= 23))) or (((c_tab.min ~= 59) or (c_tab.sec ~= 58)) or (c_tab.yday == 366)));
(io.output)(io.stdout);
res_t, res_u, res_v, res_w, res_x, res_y = ()_ENV[v].match(()os.date("%d %m %Y %H %M %S"), "(%d+) (%d+) (%d+) (%d+) (%d+) (%d+)");
res_t = ()_ENV[v](res_t);
res_u = ()_ENV[v](res_u);
res_v = ()_ENV[v](res_v);
res_w = ()_ENV[v](res_w);
res_x = ()_ENV[v](res_x);
res_y = ()_ENV[v](res_y);
(io.write)(()string.format("test done on %2.2d/%2.2d/%d", res_t, res_u, res_v));
(io.write)(()string.format(", at %2.2d:%2.2d:%2.2d\n", res_w, res_x, res_y));
(io.write)(()string.format("%s\n", _VERSION));
