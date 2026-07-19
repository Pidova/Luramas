#pragma once

#include "../../builtins.hpp"
#include "../../common/common.hpp"
#include "../../misc/types.hpp"
#include "architecture/architecture.hpp"
#include "tools/disassembler.hpp"
#include <algorithm>
#include <boost/unordered/unordered_flat_map.hpp>
#include <boost/unordered/unordered_flat_set.hpp>
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>
#include <cstdint>
#include <deque>
#include <format>
#include <luramas/formatting/formatting.hpp>
#include <luramas/profile/profile.hpp>
#include <memory>
#include <ranges>

namespace luramas::il {

      /* Virtual instruction */
      struct vinst {
            profile::inst main;
            profile::real_inst rinst;
            luramas_flag fstart_cmp_bytes = false;
            luramas_flag fend_cmp_bytes = false;
      };

      /* IL disassembly */
      struct disassembly {

            luramas_address addr = 0u;                                                  /* Address  */
            arch::opcodes op = arch::opcodes::OP_NOP;                                   /* Opcode */
            arch::data::bin_kinds bin_kind = arch::data::bin_kinds::nothing;            /* Binary kind */
            std::vector<std::shared_ptr<luramas::il::arch::operand::operand>> operands; /* Operands */
            std::vector<std::shared_ptr<disassembly>> xrefs;                            /* Cross references */
            std::shared_ptr<disassembly> ref = nullptr;                                 /* reference to the disassembly which one of the operands reference i.e. jump/memory reference. */

            /* Returns disassembly of IL instruction. */
            template <bool include_hint = false /* Includes mnemonic hint */,
                bool case_mnemonic = true /* Uppercase mnemonic? */,
                bool include_address = true /* Includes address */,
                bool include_mnemonic = true /* Includes mnemonic */,
                bool include_operands = true /* Includes mnemonic */>
            std::string disassemble(const char *const comment = NULL) {

                  std::string result = "";

                  /* Address */
                  if (include_address) {
                        result += std::to_string(this->addr) + " ";
                  }

                  /* Mnemonic */
                  if (include_mnemonic) {
                        std::string mnemonic = luramas::il::disassembler::mnemonic_string(this->op); /* Mnemonic string */

                        /* Uppercase? */
                        if (case_mnemonic) {
                              std::ranges::transform(mnemonic, mnemonic.begin(), [](const char c) { return std::toupper(c); });
                        }

                        /* Append */
                        result += mnemonic + " ";
                  }

                  /* Operands */
                  if (include_operands) {
                        const auto op_count = this->operands.size();
                        for (auto i = 0u; i < op_count; ++i) {
                              result += luramas::il::disassembler::operand_string(this->operands[i]);
                              result += ((i + 1u) == op_count) ? " " : ", ";
                        }
                  }

                  /* Comment */
                  if (comment != NULL) {
                        result += std::string("; ") + comment;
                  }

                  /* Hint */
                  if (include_hint) {
                        result += ((comment == NULL) ? std::string("; ") : std::string("  ")) + luramas::il::disassembler::mnemonic_hint_string(this->op);
                  }

                  return result;
            }

#if defined(_WIN32) || defined(_WIN64)

#include "../../color.hpp"

            /* Prints disassembly in color of IL instruction. */
            template <bool include_hint = false /* Includes mnemonic hint */,
                bool case_mnemonic = true /* Uppercase mnemonic? */,
                bool include_address = true /* Includes address */,
                bool include_mnemonic = true /* Includes mnemonic */,
                bool include_operands = true /* Includes mnemonic */>
            void dump(const char *const comment = NULL) {

                  /* Address */
                  if constexpr (include_address) {
                        luramas_color_print(luramas_color_fontcolor_green, luramas_color_background_black, std::string(std::to_string(this->addr) + " ").c_str());
                  }

                  /* Mnemonic */
                  if constexpr (include_mnemonic) {

                        std::string mnemonic = luramas::il::disassembler::mnemonic_string(this->op);
                        if (case_mnemonic) {
                              std::ranges::transform(mnemonic, mnemonic.begin(), [](const char c) { return std::toupper(c); });
                        }

                        luramas_color_print(luramas_color_fontcolor_brightblue, luramas_color_background_black, std::string(mnemonic + " ").c_str());
                  }

                  /* Operands */
                  if constexpr (include_operands) {
                        const auto op_count = this->operands.size();
                        for (auto i = 0u; i < op_count; ++i) {
                              luramas_color_print(luramas_color_fontcolor_yellow, luramas_color_background_black, luramas::il::disassembler::operand_string(this->operands[i]).c_str());
                              luramas_color_print(luramas_color_fontcolor_nothing, luramas_color_background_nothing, ((i + 1u) == op_count) ? " " : ", ");
                        }
                  }

                  /* Comment */
                  if (comment != NULL) {
                        luramas_color_print(luramas_color_fontcolor_magenta, luramas_color_background_black, std::string(std::string("; ") + comment).c_str());
                  }

                  /* Hint */
                  if constexpr (include_hint) {
                        luramas_color_print(luramas_color_fontcolor_magenta, luramas_color_background_black, std::string(((comment == NULL) ? std::string("; ") : std::string("  ")) + luramas::il::disassembler::mnemonic_hint_string(this->op)).c_str());
                  }

                  /* Line end */
                  if constexpr (include_address || include_mnemonic || include_operands || include_hint || comment != NULL) {
                        luramas_color_print(luramas_color_fontcolor_nothing, luramas_color_background_nothing, "\n");
                  }

                  return;
            }

#endif
            void clear() {
                  *this = disassembly();
                  return;
            }
      };

      /* IL validation error */
      struct commit_error {

            /* Throw error */
            void commit(const std::shared_ptr<disassembly> &il, const char *error) {
                  this->il = il;
                  this->error = error;
                  this->is_error = true;
                  return;
            }

            std::shared_ptr<disassembly> il;
            const char *error = NULL;
            bool is_error = false;
      };

      /* Programs memory */
      struct program_memory {
            std::size_t base = 0u;
            std::vector<std::uint8_t> memory;
      };

      struct flags {
            luramas_flag fannotate_instructions = false; /* At the end of lifting instruction make annotative string for it */
      };

      /* IL class */
      class ilang {

          public:
            class debug_manager {

                public:
                  /*
                      Stored as marked range
                      i.e (reg):
                          OP_MARK 
                              ...
                          OP_MARK                   
                  */
                  debug_manager(const std::shared_ptr<luramas::il::ilang> &il)
                      : linked(il) {
                  }

                  inline const char *const get(const luramas_register reg, luramas_address loc) const {
                        if (this->defined.empty()) {
                              return nullptr;
                        }
                        ++loc;
                        auto it = this->defined.find(reg);
                        if (it != this->defined.end()) {
                              for (const auto &[block, str] : it->second) {
                                    if (loc >= block.first->addr && loc <= block.second->addr) {
                                          return str.c_str();
                                    }
                              }
                        }
                        return nullptr;
                  }
                  inline void add(const luramas_register reg, const std::shared_ptr<disassembly> &start, const std::shared_ptr<disassembly> &end, const std::string &name) {

                        auto [it, inserted] = this->defined.try_emplace(reg, std::vector<std::pair<std::pair<std::shared_ptr<disassembly>, std::shared_ptr<disassembly>>, std::string>>({std::make_pair(std::make_pair(start, end), name)}));
                        if (!inserted) {
                              for (auto &[block, str] : it->second) {
                                    if (start == block.first) {
                                          return;
                                    }
                              }
                              it->second.emplace_back(std::make_pair(start, end), name);
                        }
                        return;
                  }

                  std::shared_ptr<luramas::il::ilang> linked = nullptr;
                  boost::unordered_flat_map<luramas_register, std::vector<std::pair<std::pair<std::shared_ptr<disassembly>, std::shared_ptr<disassembly>>, std::string>>> defined;
            };

            struct kvalue {

                  arch::data::kval_kinds type = arch::data::kval_kinds::none;

                  struct boolean {
                        bool b = false;
                  } boolean;

                  struct vector {
                        std::vector<std::float_t> vector;
                  } vector;

                  struct integer {
                        double i = 0.0;
                        std::string str = ""; /* Formatted */
                  } integer;

                  struct closure {
                        std::size_t id = 0u;
                        std::shared_ptr<ilang> ilang_closure = nullptr;
                  } closure;

                  struct table {
                        std::size_t node_size = 0u;
                        std::size_t array_size = 0u;
                  } table;

                  struct userdata {
                        std::string str = "";
                  } userdata;

                  struct function {
                        std::string str = "";
                  } function;

                  struct thread {
                        std::string str = "";
                  } thread;

                  struct upvalue {
                        std::string str = "";
                  } upvalue;

                  struct string {
                        std::string str = "";
                  } string;

                  /* Kvalue string */
                  std::string str() {

                        std::string result("");

                        switch (this->type) {
                              case arch::data::kval_kinds::vector: {
                                    result = "VECTOR { ";
                                    for (const auto &i : this->vector.vector) {
                                          result += std::to_string(i) + " ";
                                    }
                                    result = "}";
                                    break;
                              }
                              case arch::data::kval_kinds::none: {
                                    result = "none";
                                    break;
                              }
                              case arch::data::kval_kinds::boolean: {
                                    result = (this->boolean.b) ? "true" : "false";
                                    break;
                              }
                              case arch::data::kval_kinds::integer: {
                                    result = this->integer.str;
                                    break;
                              }
                              case arch::data::kval_kinds::string: {
                                    result = "\"" + this->string.str + "\"";
                                    break;
                              }
                              case arch::data::kval_kinds::userdata: {
                                    result = this->userdata.str;
                                    break;
                              }
                              case arch::data::kval_kinds::table: {
                                    result = "node_" + std::to_string(this->table.node_size) + ", array_" + std::to_string(this->table.array_size);
                                    break;
                              }
                              case arch::data::kval_kinds::function: {
                                    result = this->function.str;
                                    break;
                              }
                              case arch::data::kval_kinds::closure: {
                                    result = "closure_" + std::to_string(this->closure.id);
                                    break;
                              }
                              case arch::data::kval_kinds::thread: {
                                    result = this->thread.str;
                                    break;
                              }
                              case arch::data::kval_kinds::upvalue: {
                                    result = this->upvalue.str;
                                    break;
                              }
                              default: {
                                    luramas::error::error("Unkown IL kvalue type.");
                              }
                        }

                        return result;
                  }
            };

            flags flags;                                               /* IL flags */
            std::optional<debug_manager> debug;                        /* Debug Manager */
            std::vector<std::shared_ptr<disassembly>> dis;             /* IL disassembly */
            std::vector<std::shared_ptr<kvalue>> kval;                 /* IL Kvalues */
            std::vector<std::shared_ptr<luramas::il::ilang>> closures; /* IL Closures */

            template <arch::data::kval_kinds k>
            std::size_t make_kvalue(const std::string &str) {

                  for (auto i = 0u; i < this->kval.size(); ++i) {
                        const auto &kv = this->kval[i];
                        if (kv->type == arch::data::kval_kinds::string && kv->string.str == str) {
                              return i;
                        }
                  }
                  auto ptr = std::make_shared<kvalue>();
                  ptr->type = k;
                  switch (k) {
                        case arch::data::kval_kinds::string: {
                              ptr->string.str = str;
                              break;
                        }
                        case arch::data::kval_kinds::function: {
                              ptr->function.str = str;
                              break;
                        }
                        default: {
                              luramas::error::error("Unkown kv kind");
                              break;
                        }
                  }
                  this->kval.emplace_back(ptr);
                  return this->kval.size() - 1u;
            }
            template <arch::data::kval_kinds k>
            std::size_t make_kvalue(const double v) {

                  for (auto i = 0u; i < this->kval.size(); ++i) {
                        const auto &kv = this->kval[i];
                        if (kv->type == arch::data::kval_kinds::integer && kv->integer.i == v) {
                              return i;
                        }
                  }
                  auto ptr = std::make_shared<kvalue>();
                  ptr->type = k;
                  switch (k) {
                        case arch::data::kval_kinds::integer: {
                              ptr->integer.i = v;
                              break;
                        }
                        default: {
                              luramas::error::error("Unkown kv kind");
                              break;
                        }
                  }
                  this->kval.emplace_back(ptr);
                  return this->kval.size() - 1u;
            }

            /* Validates, corrects, and then commits uncommited disassembly. */
            void commit_dis(std::vector<std::shared_ptr<disassembly>> *il = nullptr, const bool resolve = true /* Resolve?? */) {

                  if (il) {
                        this->dis = std::move(*il);
                  }

                  /* Validate */
                  this->validate(this->validate_operands());
                  this->resolve_xrefs();

                  luramas_address addr = 0u;
                  if (!this->front.empty() || !this->back.empty() || !this->ignore.empty() || !this->insertions.empty()) {
                        auto mutated = std::move(this->front);
                        mutated.reserve(mutated.size() + this->dis.size() + this->insertions.size() * 2u);
                        for (const auto &i : this->dis) {
                              if (!this->ignore.contains(i) && i) {
                                    mutated.emplace_back(i);
                                    for (const auto &operand : i->operands) {
                                          if (operand->type == arch::operand::operand_kind::reg) {
                                                if (const auto reg = operand->dis.reg; reg > this->temp_reg) {
                                                      this->temp_reg = reg;
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

                  if (resolve) {
                        this->resolve_addresses();
                        this->resolve_jumps();
                  }
                  if (this->dis_map.empty()) {
                        for (const auto &i : this->dis) {
                              this->dis_map.try_emplace(i->addr, i);
                        }
                  }
                  for (const auto &i : this->dis) {
                        i->addr = addr++;
                  }

                  ++this->temp_reg;
                  this->back.clear();
                  this->front.clear();
                  this->ignore.clear();
                  this->insertions.clear();
                  return;
            }

            /* Emplaces disassembly back to IL. */
            inline void insert_front(const std::shared_ptr<disassembly> &d) {
                  this->front.emplace_back(d);
                  return;
            }
            inline void insert_back(const std::shared_ptr<disassembly> &d) {
                  this->back.emplace_back(d);
                  return;
            }
            inline void insert(const std::shared_ptr<disassembly> &where, const std::shared_ptr<disassembly> &v) {
                  if (where && v) {
                        auto [it, inserted] = this->insertions.try_emplace(where, std::vector<std::shared_ptr<disassembly>>({v}));
                        if (!inserted) {
                              it->second.emplace_back(v);
                        }
                  }
                  return;
            }
            inline void insert_front(const std::shared_ptr<disassembly> &where, const std::shared_ptr<disassembly> &v) {
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
            inline void insert(const luramas_address where, const std::shared_ptr<disassembly> &v) {
                  if (!this->valid(where)) {
                        luramas::error::error("Invalid index");
                  }
                  this->insert(this->dis[where], v);
                  return;
            }
            inline void insert_front(luramas_address where, const std::shared_ptr<disassembly> &v) {
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
                        this->insert(this->dis[where], v);
                  }
                  return;
            }
            inline void insert_front(luramas_address where, const std::vector<std::shared_ptr<disassembly>> &v) {
                  for (const auto &i : v) {
                        this->insert_front(where, i);
                  }
                  return;
            }
            inline void insert_original_unsafe(const luramas_address where, const std::shared_ptr<disassembly> &v) {
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
            template <bool safe = false /* If its pending will just become NOP*/>
            inline void remove(const std::shared_ptr<disassembly> &dis) {
                  if (dis && dis->op == il::arch::opcodes::OP_PEND) {
                        dis->op = il::arch::opcodes::OP_NOP;
                  } else {
                        this->ignore.insert(dis);
                  }
                  return;
            }
            inline bool valid(const std::size_t idx) const {
                  return idx < this->dis.size();
            }
            inline bool is_remove(const std::shared_ptr<luramas::il::disassembly> &disassembly) const {
                  return this->ignore.contains(disassembly);
            }

            /* Visits addr of Original IL disassembly. */
            std::shared_ptr<disassembly> visit(const luramas_address addr) {
                  return this->dis_map[addr];
            }

            /* Visits instructions that references addr. */
            std::vector<std::shared_ptr<disassembly>> visit_ref(const luramas_address addr) const {

                  std::vector<std::shared_ptr<disassembly>> result;

                  for (const auto &i : this->dis) {
                        if (i->ref && i->ref->addr == addr) {
                              result.emplace_back(i);
                        }
                  }
                  return result;
            }
            /* Validate IL makes sures there is no error in IL disassembly, returns error if any. */
            luramas::il::commit_error validate() {

                  auto valid = this->validate_operands();
                  if (valid.is_error) {
                        return valid;
                  }
                  return luramas::il::commit_error();
            }

            luramas_register temp_reg = 0u; /* Temporary register */

          private:
            boost::unordered_flat_map<luramas_address, std::shared_ptr<disassembly>> dis_map; /* Original ADDR map of dism -> IL (Maps diretly to how the original dism is) */

            std::vector<std::shared_ptr<disassembly>> front;                                                               /* Data to insert in the front */
            std::vector<std::shared_ptr<disassembly>> back;                                                                /* Data to insert in the back */
            boost::unordered_flat_set<std::shared_ptr<disassembly>> ignore;                                                /* Data to ignore */
            boost::unordered_flat_map<std::shared_ptr<disassembly>, std::vector<std::shared_ptr<disassembly>>> insertions; /* Data to inserts */

            /* Throws error if IL is not valid. */
            void validate(const luramas::il::commit_error &valid);

            /* Validates operands for IL. */
            commit_error validate_operands();

            /* Resolves mutated or missing addresses. */
            void resolve_addresses();

            /* Resolves jump location and reference. */
            void resolve_jumps();

            /* Resolves xrefs. */
            void resolve_xrefs();
      };

      namespace helpers {

            namespace low {

                  enum class operand_kinds : std::uint8_t {
                        reg,           /* Source register operand */
                        dest,          /* Destination */
                        value,         /* Value */
                        jmp,           /* Jump */
                        indirect_call, /* Indirect calls */
                        indirect_goto, /* Indirect goto */
                        integer,       /* Integer */
                        memloc,        /* Memory location */
                        flag           /* Flag */
                  };

                  struct operand {

                        operand_kinds kind = operand_kinds::reg; /* Operand encoding type */

                        union {
                              std::uint32_t flag;   /* Flag */
                              luramas_register reg; /* Register */
                              std::intptr_t val;    /* Value */
                              double integer;       /* Integer */
                        };
                        luramas_address ref_addr = 0u; /* reference address */
                  };

                  /* 
                         Used for dissassembly with little to none information about disassembly
                         (ENTRY IS ASSUMED TO BE FRONT OF DATA)  
                         Data is usually pre-parsed into parser when a lot of mutations need to be made
                         Everything is mapped out making it easier
                  */
                  template <typename T>
                  struct disassembly_manager {

                        disassembly_manager(const std::vector<std::pair<luramas::il::vinst, T>> &data,
                            const std::shared_ptr<il::ilang> &il,
                            const boost::unordered_flat_map<profile::module_id, profile::analyze::details> &details,
                            const luramas_register temp_reg = 0u,
                            const bool fill_pending = false)
                            : data(data), temp_reg(temp_reg), il(il), details(details) {

                              if (fill_pending) {
                                    for (const auto &[i, d] : data) {
                                          auto ptr = std::make_shared<disassembly>();
                                          ptr->op = arch::opcodes::OP_PEND;
                                          ptr->addr = i.main.pc;
                                          auto [it, inserted] = this->original_address_data.try_emplace(i.main.mid, boost::unordered_flat_map<luramas_address, std::shared_ptr<disassembly>>());
                                          it->second.try_emplace(i.main.pc, ptr);
                                          this->il->insert_front(ptr);
                                    }
                                    this->il->commit_dis();
                              }
                        };

                        std::vector<std::pair<luramas::il::vinst, T>> data;
                        luramas_register temp_reg = 0u;
                        std::shared_ptr<luramas::il::ilang> il = nullptr;
                        boost::unordered_flat_map<profile::module_id, boost::unordered_flat_map<luramas_address, std::shared_ptr<disassembly>>> original_address_data;
                        boost::unordered_flat_map<profile::module_id, profile::analyze::details> details;
                  };
            } // namespace low
      } // namespace helpers
} // namespace luramas::il