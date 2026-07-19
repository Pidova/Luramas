#include "../defs.hpp"

namespace luramas::ir::code::emitter::common::pages {

      /* Emits page function signature */
      inline void emit_page_function_start_signature(const syntax::emitter_syntax syn, std::string &buffer, const std::string &name, const std::vector<std::string> &args, const std::vector<ir::types::signature> &arg_types, const std::vector<ir::types::signature> &result_types, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            switch (syn) {
                  case syntax::emitter_syntax::cpp: {

                        cpp::pages::emit_page_function_signature(buffer, name, args, arg_types, result_types, format);
                        break;
                  }
                  default: {
                        luramas::error::error_stat_syn_emit("Page function start signature");
                  }
            }
            return;
      }

      /* Emits page function start */
      inline void emit_page_function_start(const syntax::emitter_syntax syn, std::string &buffer, const std::string &name, const std::vector<std::string> &args, const std::vector<ir::types::signature> &arg_types, const std::vector<ir::types::signature> &result_types, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            switch (syn) {
                  case syntax::emitter_syntax::cpp: {

                        cpp::pages::emit_page_function_start(buffer, name, args, arg_types, result_types, format);
                        break;
                  }
                  default: {
                        luramas::error::error_stat_syn_emit("Page function start");
                  }
            }
            return;
      }

      /* Emits page function end */
      inline void emit_page_function_end(const syntax::emitter_syntax syn, std::string &buffer, const luramas_id id, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            switch (syn) {
                  case syntax::emitter_syntax::cpp: {

                        cpp::pages::emit_page_function_end(buffer, id, format);
                        break;
                  }
                  default: {
                        luramas::error::error_stat_syn_emit("Page function end");
                  }
            }
            return;
      }

      /* Emits page function call */
      inline void emit_page_function_call(const syntax::emitter_syntax syn, std::string &buffer, const std::string &name, const std::optional<luramas_id> &controller, const std::string &stack, const std::string &value, const std::vector<std::string> &args, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            switch (syn) {
                  case syntax::emitter_syntax::cpp: {

                        cpp::pages::emit_page_function_call(buffer, name, controller, stack, value, args, format);
                        break;
                  }
                  default: {
                        luramas::error::error_stat_syn_emit("Page function call");
                  }
            }
            return;
      }

      /* Emits page function goto */
      inline void emit_page_function_goto(const syntax::emitter_syntax syn, std::string &buffer, const std::string &name, const std::optional<luramas_id> &controller, const std::vector<std::string> &args, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            switch (syn) {
                  case syntax::emitter_syntax::cpp: {

                        cpp::pages::emit_page_function_goto(buffer, name, controller, args, format);
                        break;
                  }
                  default: {
                        luramas::error::error_stat_syn_emit("Page function goto");
                  }
            }
            return;
      }
} // namespace luramas::ir::code::emitter::common::pages