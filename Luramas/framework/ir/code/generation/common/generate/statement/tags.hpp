#pragma once
#include "../generate.hpp"
#include "../line/line.hpp"
#include "../supported.hpp"

namespace luramas::ir::code::emitter::common::tags {

      /* Emit tag start. */
      inline void start(const syntax::emitter_syntax syn, std::string &buffer, const std::string &name, const std::vector<std::pair<std::string, std::string>> &ids, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            switch (syn) {
                  case syntax::emitter_syntax::html: {
                        html::tags::start(buffer, name, ids, format);
                        break;
                  }
                  case syntax::emitter_syntax::css: {
                        css::tags::start(buffer, name, ids, format);
                        break;
                  }
                  default: {
                        luramas::error::error_stat_syn_emit("Tag start");
                  }
            }
            return;
      }

      /* Emit tag end. */
      inline void end(const syntax::emitter_syntax syn, std::string &buffer, const std::string &name, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            switch (syn) {
                  case syntax::emitter_syntax::html: {
                        html::tags::end(buffer, name, format);
                        break;
                  }
                  case syntax::emitter_syntax::css: {
                        css::tags::end(buffer, name, format);
                        break;
                  }
                  default: {
                        luramas::error::error_stat_syn_emit("Tag end");
                  }
            }
            return;
      }

} // namespace luramas::ir::code::emitter::common::tags