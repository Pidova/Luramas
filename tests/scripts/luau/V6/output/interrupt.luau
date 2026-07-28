print("testing interrupts");
function test()
   function foo()
      for c_i_q = 1, 10 do
      end
   end;
   foo();
   function bar()
      local val = 0;
      while (true) do
         if (val > 10) then
            return;
         end
         val += val + 1;
      end
   end;
   bar();
   function baz()
   end;
   baz();
end;
function infloop1()
   while (true) do
   end
end;
function infloop2()
   while (true) do
   end
end;
function infloop3()
   while (true) do
   end
end;
function infloop4()
   while (true) do
   end
end;
function infloop5()
   for c_i_k = 0, 0, 0 do
   end
end;
function infloop6()
   for c_i_j = 0, 0, 0 do
   end
end;
function infloop7()
   for c_i_i = 1, math.huge do
   end
end;
function infloop8()
   for c_i_h = 1, math.huge do
   end
end;
function infloop9()
   (function ()
      u();
      u();
   end)();
end;
function infloop10()
   for c_i_e = 4096, 0, 0 do
      while (not (function ()
      end)) do
      end
   end
end;
local u_res = string.rep("x", 100);
local u_built_str = string.rep("x?", 100) .. string.rep("x", 100);
function strhang1()
   string.find(u_res, u_built_str);
end;
function strhang2()
   string.match(u_res, u_built_str);
end;
function strhang3()
   string.gsub(u_res, u_built_str, "%0");
end;
function strhang4()
   for k, v in string.gmatch(u_res, u_built_str) do
   end
end;
function strhang5()
   string.match(string.rep("x", 1000), string.rep("x.*", 100) .. "y");
end;
function strhangpcall()
   for c_i = 1, 100 do
      local c_success, c_result = pcall(string.find, u_res, u_built_str);
      assert(c_success == false);
      assert(c_result == "timeout");
   end
end;
return "OK";
