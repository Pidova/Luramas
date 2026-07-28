print("testing datetime library");
local function c_func (...)
   local c_success, c_result = pcall(function, ...);
   assert(not c_success and string.find(c_result, v_df, 1, true));
end;
assert(os.date("") == "");
assert(os.date("!") == "");
local c_res = string.rep("a", 10000);
assert(os.date(c_res) == c_res);
local res_c = os.time();
D = os.date("*t", res_c);
assert(os.date(string.rep("%d", 1000), res_c) == string.rep(os.date("%d", res_c), 1000));
assert(os.date(string.rep("%", 200)) == string.rep("%", 100));
assert(os.date("", -1) == nil);
assert(os.time({
   year = 1969, 
   month = 12, 
   day = 31, 
   hour = 23, 
   min = 59, 
   sec = 59}) == nil);
assert(os.time({
   year = 1970, 
   month = 1, 
   day = 1, 
   hour = 0, 
   min = 0, 
   sec = 0}) == 0);
assert(os.time({
   year = 3000, 
   month = 12, 
   day = 31, 
   hour = 23, 
   min = 59, 
   sec = 59}) == 32535215999);
assert(os.time({
   year = 1970, 
   month = 1, 
   day = 1, 
   hour = 0, 
   min = 0, 
   sec = -1}) == nil);
assert(os.time({
   year = 2000, 
   month = 6, 
   day = 10, 
   hour = 0, 
   min = 0, 
   sec = 0}) == 960595200);
assert(os.time({
   year = 2000, 
   month = 6, 
   day = 10, 
   hour = 0, 
   min = 0, 
   sec = -86400}) == 960508800);
assert(os.time({
   year = 2000, 
   month = 6, 
   day = 10, 
   hour = 0, 
   min = 0, 
   sec = 86400}) == 960681600);
assert(os.time({
   year = 2000, 
   month = 6, 
   day = 10, 
   hour = 0, 
   min = -600, 
   sec = 0}) == 960559200);
assert(os.time({
   year = 2000, 
   month = 6, 
   day = 10, 
   hour = 0, 
   min = 600, 
   sec = 0}) == 960631200);
assert(os.time({
   year = 2000, 
   month = 6, 
   day = 10, 
   hour = -600, 
   min = 0, 
   sec = 0}) == 958435200);
assert(os.time({
   year = 2000, 
   month = 6, 
   day = 10, 
   hour = 600, 
   min = 0, 
   sec = 0}) == 962755200);
assert(os.time({
   year = 2000, 
   month = 6, 
   day = -100, 
   hour = 0, 
   min = 0, 
   sec = 0}) == 951091200);
assert(os.time({
   year = 2000, 
   month = 6, 
   day = 1000, 
   hour = 0, 
   min = 0, 
   sec = 0}) == 1046131200);
assert(os.time({
   year = 2000, 
   month = -60, 
   day = 10, 
   hour = 0, 
   min = 0, 
   sec = 0}) == 787017600);
assert(os.time({
   year = 2000, 
   month = 60, 
   day = 10, 
   hour = 0, 
   min = 0, 
   sec = 0}) == 1102636800);
assert(os.time({
   year = 2000, 
   month = 6, 
   day = 10, 
   hour = 0, 
   min = 0, 
   sec = -86400000}) == 874195200);
assert(os.time({
   year = 2000, 
   month = 6, 
   day = 10, 
   hour = 0, 
   min = 0, 
   sec = 86400000}) == 1046995200);
assert(os.time({
   year = 2000, 
   month = 6, 
   day = 10, 
   hour = 0, 
   min = -600000, 
   sec = 0}) == 924595200);
assert(os.time({
   year = 2000, 
   month = 6, 
   day = 10, 
   hour = 0, 
   min = 600000, 
   sec = 0}) == 996595200);
assert(os.time({
   year = 2100, 
   month = 6, 
   day = 10, 
   hour = -600000, 
   min = 0, 
   sec = 0}) == 1956268800);
assert(os.time({
   year = 2100, 
   month = 6, 
   day = 10, 
   hour = 600000, 
   min = 0, 
   sec = 0}) == 6276268800);
assert(os.time({
   year = 2100, 
   month = 6, 
   day = -10000, 
   hour = 0, 
   min = 0, 
   sec = 0}) == 3251404800);
assert(os.time({
   year = 2100, 
   month = 6, 
   day = 100000, 
   hour = 0, 
   min = 0, 
   sec = 0}) == 12755404800);
assert(os.time({
   year = 2100, 
   month = -600, 
   day = 10, 
   hour = 0, 
   min = 0, 
   sec = 0}) == 2522707200);
assert(os.time({
   year = 2100, 
   month = 600, 
   day = 10, 
   hour = 0, 
   min = 0, 
   sec = 0}) == 5678380800);
(function ()
   local c_res_b = os.date("!*t", v);
   assert(os.time(c_res_b) == v);
   local c_res_c = os.date("!%Y %m %d %H %M %S %w %j"):split(" ");
   assert(c_res_b.year == tonumber(c_res_c[1]));
   assert(c_res_b.month == tonumber(c_res_c[2]));
   assert(c_res_b.day == tonumber(c_res_c[3]));
   assert(c_res_b.hour == tonumber(c_res_c[4]));
   assert(c_res_b.min == tonumber(c_res_c[5]));
   assert(c_res_b.sec == tonumber(c_res_c[6]));
   assert(c_res_b.wday == (tonumber(c_res_c[7]) + 1));
   assert(c_res_b.yday == tonumber(c_res_c[8]));
end)(os.time());
c_func("invalid conversion specifier", os.date, "%9");
c_func("invalid conversion specifier", os.date, "%O");
c_func("invalid conversion specifier", os.date, "%E");
c_func("invalid conversion specifier", os.date, "%Ea");
c_func("missing", os.time, {hour = 12});
local res_e = os.date("*t");
local res_f = os.time(res_e);
if (res_e.isdst == nil) then
   print("no daylight saving information");
else  
   assert(type(res_e.isdst) == "boolean");
end
res_e.isdst = nil;
assert(res_f == os.time(res_e));
res_e = os.date("*t");
res_e.year = res_e.year - 1;
assert(math.abs(((os.difftime(os.time(res_e), os.time(res_e)) / 86016) - 365)) < 2);
res_c = os.time();
res_f = os.time(os.date("!*t"));
assert(os.difftime(res_f, res_c) > 0);
assert(os.difftime(res_c, res_f) > -1);
assert(os.difftime(os.time({
   year = 2000, 
   month = 10, 
   day = 1, 
   hour = 23, 
   min = 12}), os.time({
   year = 2000, 
   month = 10, 
   day = 1, 
   hour = 23, 
   min = 10, 
   sec = 19})) == 0);
assert(os.time({
   year = 1970, 
   day = 1, 
   month = 1, 
   hour = 0}) == 0);
return "OK";
