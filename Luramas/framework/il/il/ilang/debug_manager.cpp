#include "../il.hpp"

namespace luramas::il {

      const char *const ilang::debug_manager::get(const luramas_register reg, luramas_address loc) const {

            if (this->defined.empty()) {
                  return nullptr;
            }
            ++loc;
            if (auto it = this->defined.find(reg); it != this->defined.end()) {
                  for (const auto &i : it->second) {
                        if (loc >= i.range.first->addr && loc <= i.range.second->addr) {
                              return i.name.c_str();
                        }
                  }
            }
            return nullptr;
      }
      void ilang::debug_manager::add(const luramas_register reg, const std::shared_ptr<disassembly> &start, const std::shared_ptr<disassembly> &end, const std::string &name) {

            auto [it, inserted] = this->defined.try_emplace(reg, std::vector<context>({context(std::make_pair(start, end), name)}));
            if (!inserted) {
                  for (const auto &[block, str] : it->second) {
                        if (start == block.first) {
                              return;
                        }
                  }
                  it->second.emplace_back(context(std::make_pair(start, end), name));
            }
            return;
      }

} // namespace luramas::il