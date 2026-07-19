#pragma once
#include "../../il/il.hpp"
#include <functional>

namespace luramas::il::lifter::resolver {

      template <typename T /* Original datastruct pointer i.e. Python not Python* for template. */>
      class resolver_manager {

          public:
            /* Resolver callback function follows format (resolver_manager&) returns void. */
            using resolver_callback = void (*)(resolver_manager<T> &pm);

            /* Set buffer and ptr */
            resolver_manager(std::shared_ptr<luramas::il::ilang> &buffer, T ptr) {
                  this->il = buffer;
                  this->ptr = ptr;
                  return;
            }

            /* Add callback */
            void add(const resolver_callback &callback) {
                  this->resolver_callbacks.emplace_back(callback);
                  return;
            }

            /* Call callbacks */
            void run() {

                  /* Call operand callbacks */
                  for (const auto &callback : this->resolver_callbacks) {
                        callback(*this);
                  }
                  this->il->commit_dis();
                  return;
            }

            std::shared_ptr<luramas::il::ilang> il = nullptr;
            T ptr;

          private:
            std::vector<resolver_callback> resolver_callbacks; /* Resolver callbacks */
      };

} // namespace luramas::il::lifter::resolver