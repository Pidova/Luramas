#pragma once
#include <array>
#include <cstdint>

namespace luramas::ir::code::generation::tools::smart_variables::data::functions::args {

      static constexpr std::pair<const char *, std::array<const char *, 5u>> common[] = {

#if defined(LURAMAS_TARGET_LUA) || defined(LURAMAS_TARGET_LUAU)
          {"string.gsub", {"source_str", "pattern_str", "replacement_str", "max_replacements", nullptr}},
          {"string.find", {"source_str", "pattern_str", "start_pos", "searchable", nullptr}},
          {"string.match", {"source_str", "pattern_str", "start_pos", nullptr, nullptr}},
          {"string.format", {"format_str", "value", "value", "value", nullptr}},
          {"string.rep", {"source_str", "repeat_count", "separator_str", nullptr, nullptr}},
          {"string.reverse", {"source_str", nullptr, nullptr, nullptr, nullptr}},
          {"string.byte", {"source_str", "start_pos", "end_pos", nullptr, nullptr}},
          {"string.char", {"byte", "byte", "byte", nullptr, nullptr}},
          {"string.len", {"source_str", nullptr, nullptr, nullptr, nullptr}},
          {"string.lower", {"source_str", nullptr, nullptr, nullptr, nullptr}},
          {"string.upper", {"source_str", nullptr, nullptr, nullptr, nullptr}},
          {"string.sub", {"source_str", "start_pos", "end_pos", nullptr, nullptr}},

          {"table.insert", {"table", "pos", "value", nullptr, nullptr}},
          {"table.remove", {"table", "pos", nullptr, nullptr, nullptr}},
          {"table.concat", {"table", "separator_str", "start_pos", "end_pos", nullptr}},
          {"table.sort", {"table", "compare_func", nullptr, nullptr, nullptr}},

          {"math.abs", {"number", nullptr, nullptr, nullptr, nullptr}},
          {"math.ceil", {"number", nullptr, nullptr, nullptr, nullptr}},
          {"math.floor", {"number", nullptr, nullptr, nullptr, nullptr}},
          {"math.max", {"num", "num", "num", nullptr, nullptr}},
          {"math.min", {"num", "num", "num", nullptr, nullptr}},
          {"math.pow", {"base", "exponent", nullptr, nullptr, nullptr}},
          {"math.sqrt", {"number", nullptr, nullptr, nullptr, nullptr}},
          {"math.random", {"lower_bound", "upper_bound", nullptr, nullptr, nullptr}},
          {"math.randomseed", {"seed", nullptr, nullptr, nullptr, nullptr}},

          {"io.open", {"filename_str", "mode_str", nullptr, nullptr, nullptr}},
          {"io.read", {"format1", "format2", "formatN", nullptr, nullptr}},
          {"io.write", {"output1", "output2", "outputN", nullptr, nullptr}},
          {"io.close", {"file_handle", nullptr, nullptr, nullptr, nullptr}},

          {"os.date", {"format_str", "time_value", nullptr, nullptr, nullptr}},
          {"os.time", {"time_table", nullptr, nullptr, nullptr, nullptr}},
          {"os.difftime", {"time1", "time2", nullptr, nullptr, nullptr}},
          {"os.execute", {"command_str", nullptr, nullptr, nullptr, nullptr}},

          {"coroutine.create", {"function", nullptr, nullptr, nullptr, nullptr}},
          {"coroutine.resume", {"coroutine_obj", nullptr, nullptr}},
          {"coroutine.yield", {"yielding_thread", "arg2", nullptr, nullptr, nullptr}},
          {"coroutine.status", {"coroutine_obj", nullptr, nullptr, nullptr, nullptr}},
          {"coroutine.wrap", {"function", nullptr, nullptr, nullptr, nullptr}},

          {"tonumber", {"str_value", "base", nullptr, nullptr, nullptr}},
          {"tostring", {"value", nullptr, nullptr, nullptr, nullptr}},
          {"type", {"value", nullptr, nullptr, nullptr, nullptr}},
          {"pcall", {"function", nullptr}},
          {"xpcall", {"function", "error_handler"}},

#endif
          {nullptr, {nullptr, nullptr, nullptr, nullptr, nullptr}}};

      namespace first {

            static constexpr const char *const common[] = {

#ifdef LURAMAS_TARGET_LUAU
                "GetService",
                "GetDataStore",
                "WaitForChild",
                "FindFirstChild",
                "FindFirstChildOfClass",
                "IsA",
                "GetDescendants",
                "GetPropertyChangedSignal",
                "WaitForDescendant",
                "FindFirstAncestor",
                "FindFirstAncestorOfClass",
                "FindFirstChildWhichIsA",
                "IsDescendantOf",
                "IsAncestorOf",
                "Instance.new",
#endif

#if defined(LURAMAS_TARGET_LUA) || defined(LURAMAS_TARGET_LUAU)
                "require",
#endif
                nullptr};
      } // namespace first
} // namespace luramas::ir::code::generation::tools::smart_variables::data::functions::args
