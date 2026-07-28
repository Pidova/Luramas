print("testing byte buffer library");
function call(...)
   local c_success_vm, c_result_vn = pcall(function_vl, ...);
   assert(c_success_vm);
   return c_result_vn;
end;
function ecall(...)
   local c_success, c_result = pcall(function, ...);
   assert(not c_success);
   return c_result:sub(((c_result:find(": ") or -1) + 2), #c_result);
end;
local function u_func ()
   local c_res_vl_vs = buffer.create(1024);
   assert(buffer.len(c_res_vl_vs) == 1024);
   assert(buffer.readi8(c_res_vl_vs, 5) == 0);
   buffer.writei8(c_res_vl_vs, 10, 32);
   assert(buffer.readi8(c_res_vl_vs, 10) == 32);
   buffer.writei8(c_res_vl_vs, 15, 5);
   buffer.writei8(c_res_vl_vs, 14, 4);
   buffer.writei8(c_res_vl_vs, 13, 3);
   buffer.writei8(c_res_vl_vs, 12, 2);
   buffer.writei8(c_res_vl_vs, 11, 1);
   assert(buffer.readi8(c_res_vl_vs, 11) == 1);
   assert(buffer.readi8(c_res_vl_vs, 12) == 2);
   assert(buffer.readi8(c_res_vl_vs, 13) == 3);
   assert(buffer.readi8(c_res_vl_vs, 14) == 4);
   assert(buffer.readi8(c_res_vl_vs, 15) == 5);
   local c_res_vm_vy = buffer.readi8(c_res_vl_vs, 14) + buffer.readi8(c_res_vl_vs, 13);
   assert(c_res_vm_vy == 7);
   buffer.writei8(c_res_vl_vs, 16, c_res_vm_vy);
end;
u_func();
local function u_func_jx ()
   local c_res_vm_vn = buffer.create(1024);
   buffer.writei8(c_res_vm_vn, val, 32);
   assert(buffer.readi8(c_res_vm_vn, val) == 32);
   buffer.writei8(c_res_vm_vn, val + 5, 5);
   buffer.writei8(c_res_vm_vn, val + 4, 4);
   buffer.writei8(c_res_vm_vn, val + 3, 3);
   buffer.writei8(c_res_vm_vn, val + 2, 2);
   buffer.writei8(c_res_vm_vn, val + 1, 1);
   assert(buffer.readi8(c_res_vm_vn, (val + 1)) == 1);
   assert(buffer.readi8(c_res_vm_vn, (val + 2)) == 2);
   assert(buffer.readi8(c_res_vm_vn, (val + 3)) == 3);
   assert(buffer.readi8(c_res_vm_vn, (val + 4)) == 4);
   assert(buffer.readi8(c_res_vm_vn, (val + 5)) == 5);
   assert((buffer.readi8(c_res_vm_vn, (val + 4)) + buffer.readi8(c_res_vm_vn, (val + 3))) == 7);
end;
u_func_jx(5);
u_func_jx(30);
local function u_func_jy ()
   local c_res_vl = buffer.create(1024);
   buffer.writei32(c_res_vl, 10, 1065353216);
   local c_res_vm = buffer.readf32(c_res_vl, 10);
   assert(c_res_vm == 1);
   buffer.writef32(c_res_vl, 10, 2.75197);
   assert(buffer.readi32(c_res_vl, 10) == 1076895815);
   buffer.writef32(c_res_vl, 10, c_res_vm);
   assert(buffer.readi32(c_res_vl, 10) == 1065353216);
end;
u_func_jy();
local function u_func_jz ()
   local c_res_vl_vu = buffer.create(1024);
   buffer.writei32(c_res_vl_vu, 10, 0);
   buffer.writei32(c_res_vl_vu, 14, 1072693248);
   local c_res_vm_vo = buffer.readf64(c_res_vl_vu, 10);
   assert(c_res_vm_vo == 1);
   buffer.writef64(c_res_vl_vu, 10, 1.437577);
   local c_res_vn = buffer.readi32(c_res_vl_vu, 10);
   local c_res_vo = buffer.readi32(c_res_vl_vu, 14);
   assert(c_res_vn == 1076895760);
   assert(c_res_vo == 1073152080);
   buffer.writef64(c_res_vl_vu, 10, c_res_vm_vo);
   local c_res_vp = buffer.readi32(c_res_vl_vu, 10);
   local c_res_vq = buffer.readi32(c_res_vl_vu, 14);
   assert(c_res_vp == 0);
   assert(c_res_vq == 1072693248);
end;
u_func_jz();
local function u_func_ka ()
   local c_res_vl_vt = buffer.create(1024);
   buffer.writestring(c_res_vl_vt, 15, " world");
   buffer.writestring(c_res_vl_vt, 10, "hello");
   buffer.writei8(c_res_vl_vt, 21, string.byte("!"));
   assert(buffer.readstring(c_res_vl_vt, 10, 12) == "hello world!");
   buffer.writestring(c_res_vl_vt, 10, "hellommm", 5);
   assert(buffer.readstring(c_res_vl_vt, 10, 12) == "hello world!");
   buffer.writestring(c_res_vl_vt, 10, string.rep("hellommm", 1000), 5);
   assert(buffer.readstring(c_res_vl_vt, 10, 12) == "hello world!");
end;
u_func_ka();
(function ()
   local c_res_vl_vq = buffer.create(1024);
   local c_res_vm_vx = buffer.create(1024);
   buffer.writestring(c_res_vl_vq, 200, "hello");
   buffer.writestring(c_res_vl_vq, 100, "world");
   buffer.copy(c_res_vl_vq, 300, c_res_vl_vq, 100, 5);
   buffer.writei8(c_res_vm_vx, 35, string.byte(" "));
   buffer.writei8(c_res_vm_vx, 41, string.byte("!"));
   buffer.copy(c_res_vm_vx, 30, c_res_vl_vq, 200, 5);
   buffer.copy(c_res_vm_vx, 36, c_res_vl_vq, 300, 5);
   assert(buffer.readstring(c_res_vm_vx, 30, 12) == "hello world!");
   local c_res_vn_vr = buffer.create(9);
   buffer.writestring(c_res_vn_vr, 0, "say hello");
   buffer.copy(c_res_vm_vx, 36, c_res_vn_vr, 4);
   assert(buffer.readstring(c_res_vm_vx, 30, 12) == "hello hello!");
   local c_res_vo_vu = buffer.create(5);
   buffer.writestring(c_res_vo_vu, 0, "world");
   buffer.copy(c_res_vm_vx, 36, c_res_vo_vu);
   assert(buffer.readstring(c_res_vm_vx, 30, 12) == "hello world!");
   buffer.writestring(c_res_vl_vq, 200, "abcdefgh");
   buffer.copy(c_res_vl_vq, 200, c_res_vl_vq, 202, 6);
   assert(buffer.readstring(c_res_vl_vq, 200, 8) == "cdefghgh");
   buffer.copy(c_res_vl_vq, 202, c_res_vl_vq, 200, 6);
   assert(buffer.readstring(c_res_vl_vq, 200, 8) == "cdcdefgh");
end)();
local function u_func_kb ()
   assert(ecall((function ()
      buffer.create(-1);
   end)) == "invalid argument #1 to \'create\' (size)");
   assert(ecall((function ()
      buffer.create(-1000000);
   end)) == "invalid argument #1 to \'create\' (size)");
end;
u_func_kb();
local function u_func_kc ()
   local u_res_baq = buffer.create(1024);
   assert(call((function ()
      return buffer.readi8(u_res_baq, 1023);
   end)) == 0);
   assert(ecall((function ()
      buffer.readi8(u_res_baq, 1024);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.readi8(u_res_baq, -1);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.readi8(u_res_baq, -100000);
   end)) == "buffer access out of bounds");
   call((function ()
      buffer.writei8(u_res_baq, 1023, 0);
   end));
   assert(ecall((function ()
      buffer.writei8(u_res_baq, 1024, 0);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.writei8(u_res_baq, -1, 0);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.writei8(u_res_baq, -100000, 0);
   end)) == "buffer access out of bounds");
   assert(call((function ()
      return buffer.readi16(u_res_baq, 1022);
   end)) == 0);
   assert(ecall((function ()
      buffer.readi16(u_res_baq, 1023);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.readi16(u_res_baq, -1);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.readi16(u_res_baq, -100000);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.readi16(u_res_baq, 2147483647);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.readi16(u_res_baq, 2147483646);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.readi16(u_res_baq, 2147483645);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.readi16(u_res_baq, 2147483648);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.readi16(u_res_baq, 268435455);
   end)) == "buffer access out of bounds");
   call((function ()
      buffer.writei16(u_res_baq, 1022, 0);
   end));
   assert(ecall((function ()
      buffer.writei16(u_res_baq, 1023, 0);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.writei16(u_res_baq, -1, 0);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.writei16(u_res_baq, -100000, 0);
   end)) == "buffer access out of bounds");
   assert(call((function ()
      return buffer.readi32(u_res_baq, 1020);
   end)) == 0);
   assert(ecall((function ()
      buffer.readi32(u_res_baq, 1021);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.readi32(u_res_baq, -1);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.readi32(u_res_baq, -100000);
   end)) == "buffer access out of bounds");
   call((function ()
      buffer.writei32(u_res_baq, 1020, 0);
   end));
   assert(ecall((function ()
      buffer.writei32(u_res_baq, 1021, 0);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.writei32(u_res_baq, -1, 0);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.writei32(u_res_baq, -100000, 0);
   end)) == "buffer access out of bounds");
   assert(call((function ()
      return buffer.readf32(u_res_baq, 1020);
   end)) == 0);
   assert(ecall((function ()
      buffer.readf32(u_res_baq, 1021);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.readf32(u_res_baq, -1);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.readf32(u_res_baq, -100000);
   end)) == "buffer access out of bounds");
   call((function ()
      buffer.writef32(u_res_baq, 1020, 0);
   end));
   assert(ecall((function ()
      buffer.writef32(u_res_baq, 1021, 0);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.writef32(u_res_baq, -1, 0);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.writef32(u_res_baq, -100000, 0);
   end)) == "buffer access out of bounds");
   assert(call((function ()
      return buffer.readf64(u_res_baq, 1016);
   end)) == 0);
   assert(ecall((function ()
      buffer.readf64(u_res_baq, 1017);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.readf64(u_res_baq, -1);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.readf64(u_res_baq, -100000);
   end)) == "buffer access out of bounds");
   call((function ()
      buffer.writef64(u_res_baq, 1016, 0);
   end));
   assert(ecall((function ()
      buffer.writef64(u_res_baq, 1017, 0);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.writef64(u_res_baq, -1, 0);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.writef64(u_res_baq, -100000, 0);
   end)) == "buffer access out of bounds");
   assert(call((function ()
      return buffer.readstring(u_res_baq, 1016, 8);
   end)) == "\x00\x00\x00\x00\x00\x00\x00\x00");
   assert(ecall((function ()
      buffer.readstring(u_res_baq, 1017, 8);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.readstring(u_res_baq, -1, -8);
   end)) == "invalid argument #3 to \'readstring\' (size)");
   assert(ecall((function ()
      buffer.readstring(u_res_baq, -100000, 8);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.readstring(u_res_baq, -100000, 8);
   end)) == "buffer access out of bounds");
   call((function ()
      buffer.writestring(u_res_baq, 1016, "abcdefgh");
   end));
   assert(ecall((function ()
      buffer.writestring(u_res_baq, 1017, "abcdefgh");
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.writestring(u_res_baq, -1, "abcdefgh");
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.writestring(u_res_baq, -100000, "abcdefgh");
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.writestring(u_res_baq, 100, "abcd", -5);
   end)) == "invalid argument #4 to \'writestring\' (count)");
   assert(ecall((function ()
      buffer.writestring(u_res_baq, 100, "abcd", 50);
   end)) == "string length overflow");
   assert(ecall((function ()
      buffer.copy(u_res_baq, 30, u_res_baq, 200, 1000);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.copy(u_res_baq, 30, u_res_baq, 200, -5);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.copy(u_res_baq, 30, u_res_baq, 2000, 10);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.copy(u_res_baq, 30, u_res_baq, -1, 10);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.copy(u_res_baq, 30, u_res_baq, -10, 10);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.copy(u_res_baq, 30, u_res_baq, -100000, 10);
   end)) == "buffer access out of bounds");
   local c_res_qf = buffer.create(1024);
   assert(ecall((function ()
      buffer.copy(u_res_baq, -200, u_res_baq, 200, 200);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.copy(u_res_baq, 825, u_res_baq, 200, 200);
   end)) == "buffer access out of bounds");
end;
u_func_kc();
local function u_func_kd ()
   local u_res_sp = buffer.create(u_xp);
   assert(call((function ()
      return buffer.readi8(u_res_sp, (u_xp - 1));
   end)) == 0);
   assert(ecall((function ()
      buffer.readi8(u_res_sp, u_xp);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.readi8(u_res_sp, u_yb);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.readi8(u_res_sp, u_yf);
   end)) == "buffer access out of bounds");
   call((function ()
      buffer.writei8(u_res_sp, u_xp - 1, 0);
   end));
   assert(ecall((function ()
      buffer.writei8(u_res_sp, u_xp, 0);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.writei8(u_res_sp, u_yb, 0);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.writei8(u_res_sp, u_yf, 0);
   end)) == "buffer access out of bounds");
   assert(call((function ()
      return buffer.readi16(u_res_sp, (u_xp - 2));
   end)) == 0);
   assert(ecall((function ()
      buffer.readi16(u_res_sp, u_xp - 1);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.readi16(u_res_sp, u_yb);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.readi16(u_res_sp, u_yf);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.readi16(u_res_sp, u_zp);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.readi16(u_res_sp, u_zp - 1);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.readi16(u_res_sp, u_zp - 2);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.readi16(u_res_sp, u_zp + 1);
   end)) == "buffer access out of bounds");
   call((function ()
      buffer.writei16(u_res_sp, u_xp - 2, 0);
   end));
   assert(ecall((function ()
      buffer.writei16(u_res_sp, u_xp - 1, 0);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.writei16(u_res_sp, u_yb, 0);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.writei16(u_res_sp, u_yf, 0);
   end)) == "buffer access out of bounds");
   assert(call((function ()
      return buffer.readi32(u_res_sp, (u_xp - 4));
   end)) == 0);
   assert(ecall((function ()
      buffer.readi32(u_res_sp, u_xp - 3);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.readi32(u_res_sp, u_yb);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.readi32(u_res_sp, u_yf);
   end)) == "buffer access out of bounds");
   call((function ()
      buffer.writei32(u_res_sp, u_xp - 4, 0);
   end));
   assert(ecall((function ()
      buffer.writei32(u_res_sp, u_xp - 3, 0);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.writei32(u_res_sp, u_yb, 0);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.writei32(u_res_sp, u_yf, 0);
   end)) == "buffer access out of bounds");
   assert(call((function ()
      return buffer.readf32(u_res_sp, (u_xp - 4));
   end)) == 0);
   assert(ecall((function ()
      buffer.readf32(u_res_sp, u_xp - 3);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.readf32(u_res_sp, u_yb);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.readf32(u_res_sp, u_yf);
   end)) == "buffer access out of bounds");
   call((function ()
      buffer.writef32(u_res_sp, u_xp - 4, 0);
   end));
   assert(ecall((function ()
      buffer.writef32(u_res_sp, u_xp - 3, 0);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.writef32(u_res_sp, u_yb, 0);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.writef32(u_res_sp, u_yf, 0);
   end)) == "buffer access out of bounds");
   assert(call((function ()
      return buffer.readf64(u_res_sp, (u_xp - 8));
   end)) == 0);
   assert(ecall((function ()
      buffer.readf64(u_res_sp, u_xp - 7);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.readf64(u_res_sp, u_yb);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.readf64(u_res_sp, u_yf);
   end)) == "buffer access out of bounds");
   call((function ()
      buffer.writef64(u_res_sp, u_xp - 8, 0);
   end));
   assert(ecall((function ()
      buffer.writef64(u_res_sp, u_xp - 7, 0);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.writef64(u_res_sp, u_yb, 0);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.writef64(u_res_sp, u_yf, 0);
   end)) == "buffer access out of bounds");
   assert(call((function ()
      return buffer.readstring(u_res_sp, (u_xp - 8), 8);
   end)) == "\x00\x00\x00\x00\x00\x00\x00\x00");
   assert(ecall((function ()
      buffer.readstring(u_res_sp, u_xp - 7, 8);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.readstring(u_res_sp, u_yb, 8);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.readstring(u_res_sp, u_yf, 8);
   end)) == "buffer access out of bounds");
   call((function ()
      buffer.writestring(u_res_sp, u_xp - 8, "abcdefgh");
   end));
   assert(ecall((function ()
      buffer.writestring(u_res_sp, u_xp - 7, "abcdefgh");
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.writestring(u_res_sp, u_yb, "abcdefgh");
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.writestring(u_res_sp, u_yf, "abcdefgh");
   end)) == "buffer access out of bounds");
end;
u_func_kd(1024, -1, -100000, 2147483647);
local function u_func_ke ()
   local u_res_pz = buffer.create(1);
   assert(call((function ()
      return buffer.readi8(u_res_pz, 0);
   end)) == 0);
   assert(ecall((function ()
      buffer.readi8(u_res_pz, 1);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.readi8(u_res_pz, -1);
   end)) == "buffer access out of bounds");
   call((function ()
      buffer.writei8(u_res_pz, 0, 0);
   end));
   assert(ecall((function ()
      buffer.writei8(u_res_pz, 1, 0);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.writei8(u_res_pz, -1, 0);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.readi16(u_res_pz, 0);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.readi16(u_res_pz, -1);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.readi16(u_res_pz, -2);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.writei16(u_res_pz, 0, 0);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.writei16(u_res_pz, -1, 0);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.writei16(u_res_pz, -2, 0);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.readi32(u_res_pz, 0);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.readi32(u_res_pz, -1);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.readi32(u_res_pz, -4);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.writei32(u_res_pz, 0, 0);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.writei32(u_res_pz, -1, 0);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.writei32(u_res_pz, -4, 0);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.readf32(u_res_pz, 0);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.readf32(u_res_pz, -1);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.readf32(u_res_pz, -4);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.writef32(u_res_pz, 0, 0);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.writef32(u_res_pz, -1, 0);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.writef32(u_res_pz, -4, 0);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.readf64(u_res_pz, 0);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.readf64(u_res_pz, -1);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.readf64(u_res_pz, -8);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.writef64(u_res_pz, 0, 0);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.writef64(u_res_pz, -1, 0);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.writef64(u_res_pz, -7, 0);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.readstring(u_res_pz, 0, 8);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.readstring(u_res_pz, -1, 8);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.readstring(u_res_pz, -8, 8);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.writestring(u_res_pz, 0, "abcdefgh");
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.writestring(u_res_pz, -1, "abcdefgh");
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.writestring(u_res_pz, -7, "abcdefgh");
   end)) == "buffer access out of bounds");
end;
u_func_ke();
local function u_func_kf ()
   local u_res_kt = buffer.create(1);
   assert(call((function ()
      return buffer.readi8(u_res_kt, 0);
   end)) == 0);
   assert(ecall((function ()
      buffer.readi8(u_res_kt, u);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.readi8(u_res_kt, u_hl);
   end)) == "buffer access out of bounds");
   call((function ()
      buffer.writei8(u_res_kt, 0, 0);
   end));
   assert(ecall((function ()
      buffer.writei8(u_res_kt, u, 0);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.writei8(u_res_kt, u_hl, 0);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.readi16(u_res_kt, u_hz);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.readi16(u_res_kt, u_hl);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.readi16(u_res_kt, u_ih);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.writei16(u_res_kt, u_hz, 0);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.writei16(u_res_kt, u_hl, 0);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.writei16(u_res_kt, u_ih, 0);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.readi32(u_res_kt, u_hz);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.readi32(u_res_kt, u_hl);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.readi32(u_res_kt, u_jf);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.writei32(u_res_kt, u_hz, 0);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.writei32(u_res_kt, u_hl, 0);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.writei32(u_res_kt, u_jf, 0);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.readf32(u_res_kt, u_hz);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.readf32(u_res_kt, u_hl);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.readf32(u_res_kt, u_jf);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.writef32(u_res_kt, u_hz, 0);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.writef32(u_res_kt, u_hl, 0);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.writef32(u_res_kt, u_jf, 0);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.readf64(u_res_kt, u_hz);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.readf64(u_res_kt, u_hl);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.readf64(u_res_kt, u_lb);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.writef64(u_res_kt, u_hz, 0);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.writef64(u_res_kt, u_hl, 0);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.writef64(u_res_kt, u_ln, 0);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.readstring(u_res_kt, u_hz, 8);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.readstring(u_res_kt, u_hl, 8);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.readstring(u_res_kt, u_lb, 8);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.writestring(u_res_kt, u_hz, "abcdefgh");
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.writestring(u_res_kt, u_hl, "abcdefgh");
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.writestring(u_res_kt, u_ln, "abcdefgh");
   end)) == "buffer access out of bounds");
end;
u_func_kf(0, 1, -1, -2, -4, -7, -8);
local function u_func_kg ()
   local u_res_lb = buffer.create(0);
   assert(ecall((function ()
      buffer.readi8(u_res_lb, 1);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.readi8(u_res_lb, 0);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.readi8(u_res_lb, -1);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.writei8(u_res_lb, 1, 0);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.writei8(u_res_lb, 0, 0);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.writei8(u_res_lb, -1, 0);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.readi16(u_res_lb, 0);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.readi32(u_res_lb, 0);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.readf32(u_res_lb, 0);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.readf64(u_res_lb, 0);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.readstring(u_res_lb, 0, 1);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.readstring(u_res_lb, 0, 8);
   end)) == "buffer access out of bounds");
end;
u_func_kg();
local function u_func_kh ()
   local c_res_a = buffer.create(32);
   buffer.writeu32(c_res_a, 0, 4294967295);
   assert(buffer.readi8(c_res_a, 0) == -1);
   assert(buffer.readu8(c_res_a, 0) == 255);
   assert(buffer.readi16(c_res_a, 0) == -1);
   assert(buffer.readu16(c_res_a, 0) == 65535);
   assert(buffer.readi32(c_res_a, 0) == -1);
   assert(buffer.readu32(c_res_a, 0) == 4294967295);
   buffer.writei32(c_res_a, 0, -1);
   assert(buffer.readi8(c_res_a, 0) == -1);
   assert(buffer.readu8(c_res_a, 0) == 255);
   assert(buffer.readi16(c_res_a, 0) == -1);
   assert(buffer.readu16(c_res_a, 0) == 65535);
   assert(buffer.readi32(c_res_a, 0) == -1);
   assert(buffer.readu32(c_res_a, 0) == 4294967295);
   buffer.writei16(c_res_a, 0, 65535);
   buffer.writei16(c_res_a, 2, -1);
   assert(buffer.readi8(c_res_a, 0) == -1);
   assert(buffer.readu8(c_res_a, 0) == 255);
   assert(buffer.readi16(c_res_a, 0) == -1);
   assert(buffer.readu16(c_res_a, 0) == 65535);
   assert(buffer.readi32(c_res_a, 0) == -1);
   assert(buffer.readu32(c_res_a, 0) == 4294967295);
   buffer.writeu16(c_res_a, 0, 65535);
   buffer.writeu16(c_res_a, 2, -1);
   assert(buffer.readi8(c_res_a, 0) == -1);
   assert(buffer.readu8(c_res_a, 0) == 255);
   assert(buffer.readi16(c_res_a, 0) == -1);
   assert(buffer.readu16(c_res_a, 0) == 65535);
   assert(buffer.readi32(c_res_a, 0) == -1);
   assert(buffer.readu32(c_res_a, 0) == 4294967295);
end;
u_func_kh();
local function u_func_ki ()
   local c_res_a_vo = buffer.create(32);
   buffer.writeu8(c_res_a_vo, 0, 4294967295);
   assert(buffer.readi8(c_res_a_vo, 0) == -1);
   assert(buffer.readu8(c_res_a_vo, 0) == 255);
   assert(buffer.readi16(c_res_a_vo, 0) == 255);
   assert(buffer.readu16(c_res_a_vo, 0) == 255);
   assert(buffer.readi32(c_res_a_vo, 0) == 255);
   assert(buffer.readu32(c_res_a_vo, 0) == 255);
   buffer.writeu16(c_res_a_vo, 0, 4294967295);
   assert(buffer.readi8(c_res_a_vo, 0) == -1);
   assert(buffer.readu8(c_res_a_vo, 0) == 255);
   assert(buffer.readi16(c_res_a_vo, 0) == -1);
   assert(buffer.readu16(c_res_a_vo, 0) == 65535);
   assert(buffer.readi32(c_res_a_vo, 0) == 65535);
   assert(buffer.readu32(c_res_a_vo, 0) == 65535);
   buffer.writei32(c_res_a_vo, 8, 4294967295);
   buffer.writeu32(c_res_a_vo, 12, 4294967295);
   assert(buffer.readstring(c_res_a_vo, 8, 4) == buffer.readstring(c_res_a_vo, 12, 4));
   buffer.writei32(c_res_a_vo, 8, -2147483648);
   buffer.writeu32(c_res_a_vo, 12, 2147483648);
   assert(buffer.readstring(c_res_a_vo, 8, 4) == buffer.readstring(c_res_a_vo, 12, 4));
end;
u_func_ki();
local function u_func_kj ()
   local c_res_a_vv = buffer.fromstring("1234567890");
   assert(buffer.tostring(c_res_a_vv) == "1234567890");
   buffer.writestring(c_res_a_vv, 4, "xyz");
   assert(buffer.tostring(c_res_a_vv) == "1234xyz890");
   assert(buffer.tostring(buffer.fromstring("abcd\x00ef")) == "abcd\x00ef");
end;
u_func_kj();
local function u_func_kk ()
   local u_res = buffer.create(10);
   buffer.fill(u_res, 0, 97);
   assert(buffer.tostring(u_res) == "aaaaaaaaaa");
   buffer.fill(u_res, 0, 98, 5);
   assert(buffer.tostring(u_res) == "bbbbbaaaaa");
   buffer.fill(u_res, 4, 99);
   assert(buffer.tostring(u_res) == "bbbbcccccc");
   buffer.fill(u_res, 6, 100, 3);
   assert(buffer.tostring(u_res) == "bbbbccdddc");
   buffer.fill(u_res, 2, 4294967141, 8);
   assert(buffer.tostring(u_res) == "bbeeeeeeee");
   assert(ecall((function ()
      buffer.fill(u_res, -10, 1);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.fill(u_res, 11, 1);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.fill(u_res, 0, 1, 11);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.fill(u_res, 5, 1, 6);
   end)) == "buffer access out of bounds");
   assert(ecall((function ()
      buffer.fill(u_res, 5, 1, -1);
   end)) == "buffer access out of bounds");
end;
u_func_kk();
local function u_func_kl ()
   local c_res = buffer.create(1000);
   assert(select("#", buffer.writei32(c_res, 10, 40)) == 0);
   assert(select("#", buffer.writef32(c_res, 20, 40)) == 0);
   tab[1] = 10;
   tab[15] = 20;
   buffer.writei32(c_res, #tab, 10);
   assert(buffer.readi32(c_res, 16) == 10);
   buffer.writeu8(c_res, 100, 255);
   buffer.writeu8(c_res, 110, 128);
   assert(buffer.readu32(c_res, 100) == 255);
   assert(buffer.readu32(c_res, 110) == 128);
   buffer.writeu16(c_res, 200, 65535);
   buffer.writeu16(c_res, 210, 32768);
   assert(buffer.readu32(c_res, 200) == 65535);
   assert(buffer.readu32(c_res, 210) == 32768);
end;
u_func_kl(table.create(16, 0));
(function ()
   getfenv();
   u_func();
   u_func_jx(5);
   u_func_jx(30);
   u_func_jy();
   u_func_jz();
   u_func_ka();
   u_func_kb();
   u_func_kc();
   u_func_kd(1024, -1, -100000, 2147483647);
   u_func_ke();
   u_func_kf(0, 1, -1, -2, -4, -7, -8);
   u_func_kg();
   u_func_kh();
   u_func_ki();
   u_func_kj();
   u_func_kk();
   u_func_kl(table.create(16, 0));
end)();
return "OK";
