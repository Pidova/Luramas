#pragma once
#include "../emit.hpp"

namespace luramas::ir::code::emitter::cpp::function {

      /* Emits global function */
      inline void emit_global_function(std::string &buffer, const std::string &name, const std::vector<std::string> &params, const std::string &data, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            buffer += format->spacing.format_function(cpp_langkeyword_function);
            buffer += name;

            std::string func_params("");
            const auto count = params.size();
            for (auto i = 0u; i < count; ++i) {

                  func_params += params[i];
                  if ((i + 1u) != count) {
                        func_params += format->spacing.format_parameter_delimiter(cpp_langkeyword_function_delimeter);
                  }
            }

            /* ( ?? ) */
            func_params = format->spacing.format_parameter_open(cpp_langkeyword_function_params_parenthesis_open) + func_params;
            func_params += format->spacing.format_parameter_close(cpp_langkeyword_function_params_parenthesis_close);
            buffer += func_params;

            /*
            
                ??
            */
            luramas::ir::code::emitter::cpp::line::emit_linebreak(buffer, 1u, format);
            buffer += data;
            return;
      }
      /* Emits global function end */
      inline void emit_global_function_end(std::string &buffer, const std::shared_ptr<luramas::ir::data::format::format> &format) {
            buffer += cpp_langkeyword_scope_end;
            return;
      }

      /* Emits local function */
      inline void emit_local_function(std::string &buffer, const std::string &name, const std::vector<std::string> &params, const std::string &data, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            buffer += format->spacing.format_assignment_initial_datatype(cpp_langkeyword_dynamic_datatype);
            buffer += format->spacing.format_function(cpp_langkeyword_function);
            buffer += name;
            buffer += format->spacing.format_function("");

            std::string func_params("");
            const auto count = params.size();
            for (auto i = 0u; i < count; ++i) {

                  func_params += params[i];
                  if ((i + 1u) != count) {
                        func_params += format->spacing.format_parameter_delimiter(cpp_langkeyword_function_delimeter);
                  }
            }

            /* ( ?? ) */
            func_params = format->spacing.format_parameter_open(cpp_langkeyword_function_params_parenthesis_open) + func_params;
            func_params += format->spacing.format_parameter_close(cpp_langkeyword_function_params_parenthesis_close);
            buffer += func_params;

            /*
            
                ??
            */
            luramas::ir::code::emitter::cpp::line::emit_linebreak(buffer, 1u, format);
            buffer += data;
            return;
      }
      /* Emits local function end */
      inline void emit_local_function_end(std::string &buffer, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            buffer += cpp_langkeyword_scope_end;
            return;
      }

      /* Emits anonymous function */
      inline void emit_anonymous_function(std::string &buffer, const std::vector<std::string> &params, const std::string &data, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            buffer += format->spacing.format_function(cpp_langkeyword_function_anonymous);

            std::string func_params("");
            const auto count = params.size();
            for (auto i = 0u; i < count; ++i) {

                  func_params += params[i];
                  if ((i + 1u) != count) {
                        func_params += format->spacing.format_parameter_delimiter(cpp_langkeyword_function_delimeter);
                  }
            }

            /* ( ?? ) */
            func_params = format->spacing.format_parameter_open(cpp_langkeyword_function_params_parenthesis_open) + func_params;
            func_params += format->spacing.format_parameter_close(cpp_langkeyword_function_params_parenthesis_close);
            buffer += func_params;

            /*
            
                ??
            */
            luramas::ir::code::emitter::cpp::line::emit_linebreak(buffer, 1u, format);
            buffer += data;
            return;
      }

      /* Emits anonymous function end */
      inline void emit_anonymous_function_end(std::string &buffer, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            buffer += cpp_langkeyword_function_anonymous_end;
            return;
      }

} // namespace luramas::ir::code::emitter::cpp::function