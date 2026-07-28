print("testing bitwise operations");
assert(bit32.band() == bit32.bnot(0));
assert(bit32.btest() == true);
assert(bit32.bor() == 0);
assert(bit32.bxor() == 0);
assert(bit32.band() == bit32.band(4294967295));
assert(bit32.band(1, 2) == 0);
assert(bit32.band(-1) == 4294967295);
assert(bit32.band(8589934592) == 4294967295);
assert(bit32.band(-8589934592) == 4294967295);
assert(bit32.band(8589934592) == 1);
assert(bit32.band(-8589934592) == 1);
assert(bit32.band(-1099511627776) == 0);
assert(bit32.band(1099511627776) == 0);
assert(bit32.band(-1099511627776) == 4294967294);
assert(bit32.band(1099511627776) == 4294967292);
assert(bit32.lrotate(0, -1) == 0);
assert(bit32.lrotate(0, 7) == 0);
assert(bit32.lrotate(305419896, 4) == 591751041);
assert(bit32.rrotate(305419896, -4) == 591751041);
assert(bit32.lrotate(305419896, -8) == 2014458966);
assert(bit32.rrotate(305419896, 8) == 2014458966);
assert(bit32.lrotate(2863311530, 2) == 2863311530);
assert(bit32.lrotate(2863311530, -2) == 2863311530);
for c_i = -50, 50 do
   assert(bit32.lrotate(2309737967, c_i) == bit32.lrotate(2309737967, (c_i % 32)));
end
