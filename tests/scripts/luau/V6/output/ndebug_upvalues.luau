function clo_test()
   print(u);
   coroutine.yield();
end;
clo_test();
return "OK";
