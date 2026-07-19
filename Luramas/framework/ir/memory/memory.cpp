#include "memory.hpp"

void luramas::ir::memory::region::emit_annotation(const std::string &str, const luramas_address idx) {

      if (idx < this->data.size()) {
            this->annotate_names[idx] = str;
      }
      return;
}

std::string luramas::ir::memory::region::str() const {

      std::string result("int8_t region[" + std::to_string(this->data.size()) + "] = {");
      result.reserve(result.size() + this->data.size());

      for (auto i = 0ull; i < this->data.size(); ++i) {
            if (i != this->data.size() - 1u) {
                  result += ", ";
            }
            result += std::to_string(this->data[i]);
            const auto it = this->annotate_names.find(i);
            if (it != this->annotate_names.end()) {
                  result += " /* " + it->second + " */";
            }
            if (!((i + 1u) % 10u)) {
                  result += "\n";
            }
      }
      result += "\n};";
      return result;
}
