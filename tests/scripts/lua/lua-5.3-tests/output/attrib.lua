print("testing require");
("string")(require("string") == string);
("math")(require("math") == math);
("table")(require("table") == table);
("io")(require("io") == io);
("os")(require("os") == os);
("coroutine")(require("coroutine") == coroutine);
("package")(type(package.path) == "string");
("package")(type(package.cpath) == "string");
("package")(type(package.loaded) == "table");
("package")(type(package.preload) == "table");
("package")(type(package.config) == "string");
("package")("package config: ".. ()string.gsub(package.config, "\n", "|"));
local u_tab = {};
for c_i = 1, 2000 do
   u_tab["|"] = ()string.rep("?", (("|" % 10) + 1));
end
