#pragma once
#include "../emit.hpp"

namespace luramas::ir::code::emitter::cpp::pages {

      /* Emits page function signature */
      inline void emit_page_function_signature(std::string &buffer, const std::string &name, const std::vector<std::string> &args, const std::vector<luramas::ir::types::signature> &arg_types, const std::vector<luramas::ir::types::signature> &result_types, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            std::string buf("__forceinline ");
            cpp::types::emit_signature_list(buf, result_types, format);

            buffer += format->spacing.format_page_function_return_type(buf.c_str());
            buffer += name + cpp_langkeyword_page_function_args_start;

            const auto count = args.size();
            for (auto i = 0u; i < count; ++i) {
                  if (i < arg_types.size()) {
                        const auto &sig = arg_types[i];
                        cpp::types::emit_type(buffer, sig.t, format, sig.fconstant);
                  }
                  buffer += args[i];

                  /* Add delimiter */
                  if ((i + 1u) != count) {
                        buffer += format->spacing.format_parameter_delimiter(cpp_langkeyword_call_delimiter);
                  }
            }
            buffer += cpp_langkeyword_page_function_args_end;
            return;
      }

      /* Emits page function start */
      inline void emit_page_function_start(std::string &buffer, const std::string &name, const std::vector<std::string> &args, const std::vector<luramas::ir::types::signature> &arg_types, const std::vector<luramas::ir::types::signature> &result_types, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            emit_page_function_signature(buffer, name, args, arg_types, result_types, format);
            buffer += cpp_langkeyword_page_function_start;
            return;
      }

      /* Emits page function end */
      inline void emit_page_function_end(std::string &buffer, const luramas_id id, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            buffer += cpp_langkeyword_page_function_end;
            return;
      }

      /* Emits page function call */
      inline void emit_page_function_call(std::string &buffer, const std::string &name, const std::optional<luramas_id> &controller, const std::string &stack, const std::string &value, const std::vector<std::string> &args, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            std::string func("lura_page_function_call<" + name + (!value.empty() ? ", " + value : "") + ">");

            auto pargs = args;
            pargs.insert(pargs.begin(), {stack});
            if (controller) {
                  pargs.insert(pargs.begin(), std::to_string(*controller));
            }
            cpp::call::emit_call(buffer, func, pargs, format);
            return;
      }

      /* Emits page function goto */
      inline void emit_page_function_goto(std::string &buffer, const std::string &name, const std::optional<luramas_id> &controller, const std::vector<std::string> &args, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            std::string func("lura_page_function_goto<" + name + ">");

            auto pargs = args;
            if (controller) {
                  pargs.insert(pargs.begin(), std::to_string(*controller));
            }

            cpp::call::emit_call(buffer, func, pargs, format);
            return;
      }
} // namespace luramas::ir::code::emitter::cpp::pages