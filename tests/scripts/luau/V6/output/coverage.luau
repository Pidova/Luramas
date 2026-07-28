print("testing coverage");
function foo()
   assert(0);
end;
function bar()
end;
function validate()
   local tab_d = {};
   for k, v in ipairs(v_h) do
      if (tab[v]) then
         return false, string.format("expected line %d to be hit", v);
      end
      tab_d[v] = true;
   end
end;
foo();
c = getcoverage(foo);
assert(#c == 1);
assert(c[1].name == "foo");
assert(c[1].linedefined == 4);
assert(c[1].depth == 0);
assert(validate(c[1], {5, 6, 7}, {}));
bar();
c = getcoverage(bar);
assert(#c == 3);
assert(c[1].name == "bar");
assert(c[1].linedefined == 10);
assert(c[1].depth == 0);
assert(validate(c[1], {11, 15, 19}, {}));
assert(c[2].name == "one");
assert(c[2].linedefined == 11);
assert(c[2].depth == 1);
assert(validate(c[2], {12}, {}));
assert(c[3].name == nil);
assert(c[3].linedefined == 15);
assert(c[3].depth == 1);
assert(validate(c[3], {}, {16}));
return "OK";
