#include "formatting.hpp"

namespace luramas::ir::data::format {

      std::string formatter::replace(const std::initializer_list<std::pair<const char *, std::string>> &kp) const {

            auto result = str;
            for (const auto &[k, v] : kp) {

                  std::size_t pos = 0u;
                  while ((pos = result.find(k, pos)) != std::string::npos) {
                        result.replace(pos, std::strlen(k), v);
                        pos += v.length();
                  }
            }
            return result;
      }

      std::string format::spacing::format_function(const char *const keyword) const {

            return std::string(keyword + (this->disabled ? "" : this->spacing_function));
      }

      std::string format::spacing::format_unary_not(const char *const keyword) const {

            return std::string(keyword + (this->disabled ? "" : this->spacing_not));
      }

      std::string format::spacing::format_unary_minus(const char *const keyword) const {

            return std::string(keyword + (this->disabled ? "" : this->spacing_minus));
      }

      std::string format::spacing::format_unary_bitnot(const char *const keyword) const {

            return std::string(keyword + (this->disabled ? "" : this->spacing_bitnot));
      }

      std::string format::spacing::format_unary_length(const char *const keyword) const {

            return std::string(keyword + (this->disabled ? "" : this->spacing_length));
      }

      std::string format::spacing::format_parenthesis_open(const char *const keyword) const {

            return std::string(this->disabled ? keyword : this->spacing_parenthesis_open_pre + keyword + this->spacing_parenthesis_open_post);
      }

      std::string format::spacing::format_parenthesis_close(const char *const keyword) const {

            return std::string(this->disabled ? keyword : this->spacing_parenthesis_close_pre + keyword + this->spacing_parenthesis_close_post);
      }

      std::string format::spacing::format_parenthesis_str(const char *const open, const std::string &str, const char *const close) const {
            return this->format_parenthesis_open(open) + str + this->format_parenthesis_close(close);
      }

      std::string format::spacing::format_parenthesis_ref(const char *const open, const std::string &str, const char *const close) const {
            std::string result("");
            result += this->format_parenthesis_open(open);
            result += str;
            result += this->format_parenthesis_close(close);
            return result;
      }

      std::string format::spacing::format_index_open(const char *const keyword) const {

            return std::string(this->disabled ? keyword : this->spacing_index_open_pre + keyword + this->spacing_index_open_post);
      }

      std::string format::spacing::format_index_close(const char *const keyword) const {

            return std::string(this->disabled ? keyword : this->spacing_index_close_pre + keyword + this->spacing_index_close_post);
      }

      std::string format::spacing::format_index_str(const char *const open, const std::string &str, const char *const close) const {
            return this->format_index_open(open) + str + this->format_index_close(close);
      }

      std::string format::spacing::format_index_ref(const char *const open, const std::string &str, const char *const close) const {
            std::string result("");
            result += this->format_index_open(open);
            result += str;
            result += this->format_index_close(close);
            return result;
      }

      std::string format::spacing::format_parameter_open(const char *const keyword) const {

            return std::string(this->disabled ? keyword : keyword + this->spacing_param_parenthesis_pre);
      }

      std::string format::spacing::format_parameter_close(const char *const keyword) const {

            return std::string(this->disabled ? keyword : this->spacing_param_parenthesis_post + keyword);
      }

      void format::spacing::format_call_spacing(std::string &buffer) const {

            if (!this->disabled) {
                  buffer += this->spacing_call;
            }
            return;
      }

      void format::spacing::format_tag_spacing(std::string &buffer) const {

            if (!this->disabled) {
                  buffer += this->spacing_tag;
            }
            return;
      }

      std::string format::spacing::format_table_delimiter(const char *const keyword) const {

            return std::string(this->disabled ? keyword : this->spacing_table_delimiter_pre + keyword + this->spacing_table_delimiter_post);
      }

      std::string format::spacing::format_table_start(const char *const keyword) const {

            return std::string(this->disabled ? keyword : keyword + this->spacing_table_open);
      }

      std::string format::spacing::format_table_end(const char *const keyword) const {

            return std::string(this->disabled ? keyword : this->spacing_table_close + keyword);
      }

      std::string format::spacing::format_table_index(const char *const open, const std::string &str, const char *const close, const char *const equal) const {

            std::string result = open;

            if (!this->disabled) {
                  result += this->spacing_table_index_pre;
            }
            result += str;

            if (!this->disabled) {
                  result += this->spacing_table_index_post;
            }
            result += close;

            if (!this->disabled) {
                  result += this->spacing_assignment_pre;
            }
            result += equal;

            if (!this->disabled) {
                  result += this->spacing_assignment_post;
            }
            return result;
      }

      std::string format::spacing::format_table_close(const char *const keyword) const {

            return std::string(this->disabled ? keyword : this->spacing_table_close + keyword);
      }

      std::string format::spacing::format_ternary_start(const char *const keyword) const {

            return std::string(this->disabled ? keyword : keyword + this->spacing_ternary_start);
      }

      std::string format::spacing::format_ternary_then(const char *const keyword) const {

            return std::string(this->disabled ? keyword : this->spacing_ternary_then_pre + keyword + this->spacing_ternary_then_post);
      }

      std::string format::spacing::format_ternary_else(const char *const keyword) const {

            return std::string(this->disabled ? keyword : this->spacing_ternary_else_pre + keyword + this->spacing_ternary_else_post);
      }

      std::string format::spacing::format_arith(const char *const keyword) const {

            return std::string(this->disabled ? keyword : this->spacing_arith_pre + keyword + this->spacing_arith_post);
      }

      std::string format::spacing::format_logical_operation(const char *const keyword) const {

            return std::string(this->disabled ? keyword : this->spacing_logical_operator_pre + keyword + this->spacing_logical_operator_post);
      }

      std::string format::spacing::format_parameter_delimiter(const char *const keyword) const {

            return std::string(this->disabled ? keyword : this->spacing_param_pre + keyword + this->spacing_param_post);
      }

      std::string format::spacing::format_concat(const char *const keyword) const {

            return std::string(this->disabled ? keyword : this->spacing_concat_pre + keyword + this->spacing_concat_post);
      }

      std::string format::spacing::format_compare(const char *const keyword) const {

            return std::string(this->disabled ? keyword : keyword + this->spacing_compare);
      }

      std::string format::spacing::format_goto(const char *const keyword) const {

            return std::string(this->disabled ? keyword : keyword + this->spacing_goto);
      }

      std::string format::spacing::format_while(const char *const keyword) const {

            return std::string(this->disabled ? keyword : keyword + this->spacing_loop_while);
      }

      std::string format::spacing::format_until(const char *const keyword) const {

            return std::string(this->disabled ? keyword : keyword + this->spacing_loop_until);
      }

      std::string format::spacing::format_return(const char *const keyword) const {

            return std::string(this->disabled ? keyword : keyword + this->spacing_return);
      }

      std::string format::spacing::format_while_scope_start(const char *const keyword) const {

            return std::string(this->disabled ? keyword : this->spacing_loop_while_scope_start + keyword);
      }

      std::string format::spacing::format_scope_begin(const char *const keyword) const {

            return std::string(this->disabled ? keyword : this->spacing_then + keyword);
      }

      std::string format::spacing::format_loop_begin(const char *const keyword) const {

            return std::string(keyword + (this->disabled ? "" : this->spacing_compare));
      }

      std::string format::spacing::format_semicolon(const char *const keyword) const {

            return std::string(this->disabled ? keyword : this->spacing_semicolon + keyword);
      }

      std::string format::spacing::format_assignment(const char *const keyword) const {

            return std::string(this->disabled ? keyword : this->spacing_assignment_pre + keyword + this->spacing_assignment_post);
      }

      std::string format::spacing::format_assignment_lvalue(const char *const keyword) const {

            return std::string(this->disabled ? keyword : this->spacing_assignment_lvalue_pre + keyword + this->spacing_assignment_lvalue_post);
      }

      std::string format::spacing::format_assignment_rvalue(const char *const keyword) const {

            return std::string(this->disabled ? keyword : this->spacing_assignment_rvalue_pre + keyword + this->spacing_assignment_rvalue_post);
      }

      std::string format::spacing::format_assignment_initial(const char *const keyword) const {

            return std::string(this->disabled ? keyword : this->spacing_initial_assignment_pre + keyword + this->spacing_initial_assignment_post);
      }

      std::string format::spacing::format_assignment_initial_lvalue(const char *const keyword) const {

            return std::string(this->disabled ? keyword : this->spacing_initial_assignment_lvalue_pre + keyword + this->spacing_initial_assignment_lvalue_post);
      }

      std::string format::spacing::format_assignment_initial_rvalue(const char *const keyword) const {

            return std::string(this->disabled ? keyword : this->spacing_initial_assignment_rvalue_pre + keyword + this->spacing_initial_assignment_rvalue_post);
      }

      std::string format::spacing::format_assignment_initial_datatype(const char *const keyword) const {

            return std::string(keyword + (this->disabled ? "" : this->spacing_initial_datatype_assignment));
      }

      std::string format::spacing::format_page_function_return_type(const char *const keyword) const {

            return std::string(keyword + (this->disabled ? "" : this->spacing_page_function_return_type));
      }
} // namespace luramas::ir::data::format