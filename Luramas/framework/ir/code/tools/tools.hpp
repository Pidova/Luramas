#pragma once
#include "../../ir.hpp"
#include <luramas/formatting/formatting.hpp>

namespace luramas::ir::code::generation::tools {

      namespace smart_variables {

            struct naming {
                  std::string name = "";
                  std::string delimeter = "";
                  std::string descriminator = "";

                  inline std::string str() const {
                        return this->name + (!this->descriminator.empty() ? this->delimeter : "") + this->descriminator;
                  }
            };

            /* Alphabetic suffix given n, concats more if n is avaliable */
            inline std::string alpha_suffix(std::size_t n) {
                  std::string result("");
                  do {
                        result += 'a' + (n % 26);
                        n /= 26;
                  } while (n > 0);
                  std::reverse(result.begin(), result.end());
                  return result;
            }

            void generate(const ir_stat::space &code, boost::unordered_flat_map<std::shared_ptr<ir_stat::ir_expr>, naming> &buffer, const std::shared_ptr<ir::data::format::format> &format, const boost::unordered_flat_set<std::string> &globals, luramas_xregister &gvn, const bool use_annotations);
      } // namespace smart_variables

} // namespace luramas::ir::code::generation::tools