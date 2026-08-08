#include "../il.hpp"

namespace luramas::il {

      void ilang::commit_dis(std::vector<std::shared_ptr<disassembly>> *il, const bool resolve) {

            if (il) {
                  this->dis = std::move(*il);
            }

            /* Validate */
            this->validate(this->validate_operands());
            this->resolve_xrefs();

            /* Apply mutations, insertions, and track highest temporary register */
            luramas_address addr = 0u;
            if (!this->front.empty() || !this->back.empty() || !this->ignore.empty() || !this->insertions.empty()) {
                  auto mutated = std::move(this->front);
                  mutated.reserve(mutated.size() + this->dis.size() + this->insertions.size() * 2u);
                  for (const auto &i : this->dis) {
                        if (!this->ignore.contains(i) && i) {
                              mutated.emplace_back(i);
                              for (const auto &operand : i->operands) {
                                    if (operand->type == arch::operand::operand_kind::reg) {
                                          if (const auto reg = operand->dis.reg; reg > this->ctemp_reg) {
                                                this->ctemp_reg = reg;
                                          }
                                    }
                              }
                        }
                        if (const auto it = this->insertions.find(i); it != this->insertions.end()) {
                              mutated.reserve(mutated.size() + it->second.size());
                              mutated.insert(mutated.end(), std::make_move_iterator(it->second.begin()), std::make_move_iterator(it->second.end()));
                        }
                  }
                  mutated.reserve(mutated.size() + this->back.size());
                  mutated.insert(mutated.end(), this->back.begin(), this->back.end());
                  this->dis = std::move(mutated);
            }

            /* Resolve addresses and jumps */
            if (resolve) {
                  this->resolve_addresses();
                  this->resolve_jumps();
            }

            /* If original dismap is empty propagate it */
            if (this->dis_map.empty()) {
                  for (const auto &i : this->dis) {
                        this->dis_map.try_emplace(i->addr, i);
                  }
            }

            /* Set a new address to each disassembly */
            for (const auto &i : this->dis) {
                  i->addr = addr++;
            }

            /* Clean up */
            this->back.clear();
            this->front.clear();
            this->ignore.clear();
            this->insertions.clear();
            return;
      }

      void ilang::insert_front(const std::shared_ptr<disassembly> &d) {
            this->front.emplace_back(d);
            return;
      }
      void ilang::insert_back(const std::shared_ptr<disassembly> &d) {
            this->back.emplace_back(d);
            return;
      }
      void ilang::insert(const std::shared_ptr<disassembly> &where, const std::shared_ptr<disassembly> &v) {
            if (where && v) {
                  auto [it, inserted] = this->insertions.try_emplace(where, std::vector<std::shared_ptr<disassembly>>({v}));
                  if (!inserted) {
                        it->second.emplace_back(v);
                  }
            }
            return;
      }
      void ilang::insert_front(const std::shared_ptr<disassembly> &where, const std::shared_ptr<disassembly> &v) {
            if (where && v) {
                  luramas_address idx = 0u;
                  for (auto i = 0u; i < this->dis.size(); ++i) {
                        if (this->dis[i] == where) {
                              if (i) {
                                    --i;
                              }
                              idx = i;
                              break;
                        }
                  }
                  if (idx) {
                        this->insert(this->dis[idx], v);
                  } else {
                        this->insert_front(v);
                  }
            }
            return;
      }

      void ilang::insert(const luramas_address where, const std::shared_ptr<disassembly> &v) {
            if (!this->valid(where)) {
                  luramas::error::error("Invalid index");
            }
            this->insert(this->dis[where], v);
            return;
      }
      void ilang::insert(const luramas_address where, const std::vector<std::shared_ptr<disassembly>> &v) {
            for (const auto &i : v) {
                  this->insert(where, i);
            }
            return;
      }

      void ilang::insert_front(luramas_address where, const std::shared_ptr<disassembly> &v) {
            if (!v) {
                  return;
            }
            if (!where) {
                  this->insert_front(v);
            } else {
                  if (where) {
                        --where;
                  }
                  if (!this->valid(where)) {
                        luramas::error::error("Invalid index");
                  }
                  if (!where) {
                        this->insert_front(v);
                  } else {
                        this->insert(this->dis[where], v);
                  }
            }
            return;
      }
      void ilang::insert_front(luramas_address where, const std::vector<std::shared_ptr<disassembly>> &v) {
            for (const auto &i : v) {
                  this->insert_front(where, i);
            }
            return;
      }
      void ilang::insert_original_unsafe(const luramas_address where, const std::shared_ptr<disassembly> &v) {
            if (auto i = this->dis_map.find(where); i != this->dis_map.end()) {
                  this->insert(i->second, v);
            } else {
                  auto n = this->dis.size();
                  if (n) {
                        --n;
                  }
                  if (n) {
                        --n;
                  }
                  this->insert(this->dis[n], v);
            }
            return;
      }
      void ilang::remove(const std::shared_ptr<disassembly> &dis) {
            if (dis && dis->op == il::arch::opcodes::OP_PEND) {
                  dis->op = il::arch::opcodes::OP_NOP;
            } else {
                  this->ignore.insert(dis);
            }
            return;
      }
      bool ilang::valid(const std::size_t idx) const {
            return idx < this->dis.size();
      }
      bool ilang::is_remove(const std::shared_ptr<luramas::il::disassembly> &disassembly) const {
            return this->ignore.contains(disassembly);
      }

      std::shared_ptr<disassembly> ilang::visit(const luramas_address addr) {
            return this->dis_map[addr];
      }

      std::vector<std::shared_ptr<disassembly>> ilang::visit_ref(const luramas_address addr) const {

            std::vector<std::shared_ptr<disassembly>> result;

            for (const auto &i : this->dis) {
                  if (i->ref && i->ref->addr == addr) {
                        result.emplace_back(i);
                  }
            }
            return result;
      }

      errors::error ilang::validate() {

            auto valid = this->validate_operands();
            if (valid) {
                  return valid;
            }
            return errors::error();
      }

      luramas_register ilang::get_temp_reg() {
            return this->temp_reg++;
      }
      void ilang::reset_temp_reg() {
            this->temp_reg = this->ctemp_reg;
            return;
      }
} // namespace luramas::il