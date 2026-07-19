#pragma once
#include "../../il/il.hpp"
#include <functional>
#include <optional>

namespace luramas::il::lifter::parser {

      /* 
         Parse data from original bytecode to IL. (Init should map directly to original) 
      */
      template <typename T /* Original disassembly vector i.e. disassembly. */>
      class parser_manager {

          public:
            /* Parse callback function follows format (parser_manager&) returns void. */
            using parse_callback = void (*)(parser_manager<T> &pm);

            /* Sets il, dism, and calls init commits instructions. */
            parser_manager(std::shared_ptr<luramas::il::ilang> &buffer, const std::vector<T> &dism, const parse_callback &init, const bool resolve = true) {
                  this->il = buffer;
                  this->dism = dism;
                  if (init) {
                        init(*this);
                        buffer->commit_dis(nullptr, resolve);
                  }
                  return;
            }

            /* Add parser callback */
            void add(const parse_callback &callback) {
                  this->parse_callbacks.emplace_back(callback);
                  return;
            }

            /* Call callbacks */
            template <bool clear = true /* Clears callback vector after use.*/>
            void run() {

                  /* Call callbacks */
                  for (const auto &callback : this->parse_callbacks) {
                        callback(*this);
                  }

                  this->il->commit_dis();
                  return;
            }

            std::vector<T> dism;                              /* Original disassembly vector */
            std::shared_ptr<luramas::il::ilang> il = nullptr; /* IL buffer */

          private:
            std::vector<parse_callback> parse_callbacks;
      };

} // namespace luramas::il::lifter::parser