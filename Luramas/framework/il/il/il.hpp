#pragma once
#include "../../builtins.hpp"
#include "../../common/common.hpp"
#include "../../misc/types.hpp"
#include "architecture/architecture.hpp"
#include "architecture\disassembly.hpp"
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

      /* Virtual instruction, instruction that can emit multiple instructions or do something very specific that has no direct translation */
      template <std::uint8_t MAX_LEN>
      struct vinst {
            cpu_tracer::blocks::inst_data<MAX_LEN> inst;                                         /* Instruction data */
            std::optional<std::vector<profile::edge>> edges = std::nullopt;                      /* Edges to real PC */
            std::optional<std::vector<std::shared_ptr<disassembly>>> insert_dism = std::nullopt; /* Synthetically insert IL disassembly after lifted instruction */
            luramas_flag fstart_cmp_bytes = false;                                               /* Start of scope for SMC i.e (CODE INSTRUCTIONS == SMC START REGION) add it to stack */
            luramas_flag fend_cmp_bytes = false;                                                 /* End of scope for SMC with the back of stack */
            luramas_flag fentry = false;                                                         /* Inst is entry? */
      };

      /* Programs memory */
      struct program_memory {
            std::size_t base = 0u;            /* Base pointer */
            std::vector<std::uint8_t> memory; /* Memory region */
      };

      /* IL manager */
      class ilang {

          public:
            /* IL processing flags */
            struct flags {
                  luramas_flag fannotate_instructions = false; /* At the end of lifting instruction make annotative string for it */
            };

            /* Manager with a reference to the IL context */
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

                  /* Gets the variable name associated with a register at a specific address location */
                  const char *const get(const luramas_register reg, luramas_address loc) const;

                  /* Registers a variable name for a specified register over instruction scope: [start, end] */
                  void add(const luramas_register reg, const std::shared_ptr<disassembly> &start, const std::shared_ptr<disassembly> &end, const std::string &name);

                  std::shared_ptr<luramas::il::ilang> linked = nullptr; /* Parent ILang */
                private:
                  /* Context of regions strings */
                  struct context {
                        luramas_irange<std::shared_ptr<disassembly>> range; /* Range [start, end] */
                        std::string name = "";                              /* Register name */
                  };
                  boost::unordered_flat_map<luramas_register, std::vector<context>> defined; /* Register ranges [start, end] and name */
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
                  std::string str() const;
            };

            flags flags;                                               /* IL flags */
            std::optional<debug_manager> debug;                        /* Debug Manager */
            std::vector<std::shared_ptr<disassembly>> dis;             /* IL disassembly */
            std::vector<std::shared_ptr<kvalue>> kval;                 /* IL Kvalues */
            std::vector<std::shared_ptr<luramas::il::ilang>> closures; /* IL Closures */

            template <arch::data::kval_kinds k>
            luramas_index make_kvalue(const std::string &str) {

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
            luramas_index make_kvalue(const double v) {

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
            void commit_dis(std::vector<std::shared_ptr<disassembly>> *il = nullptr, const bool resolve = true /* Resolve?? */);

            /* Emplaces disassembly back to IL. */
            void insert_front(const std::shared_ptr<disassembly> &d);
            void insert_back(const std::shared_ptr<disassembly> &d);
            void insert(const std::shared_ptr<disassembly> &where, const std::shared_ptr<disassembly> &v);
            void insert_front(const std::shared_ptr<disassembly> &where, const std::shared_ptr<disassembly> &v);
            void insert(const luramas_address where, const std::shared_ptr<disassembly> &v);
            void insert(const luramas_address where, const std::vector<std::shared_ptr<disassembly>> &v);
            void insert_front(luramas_address where, const std::shared_ptr<disassembly> &v);
            void insert_front(luramas_address where, const std::vector<std::shared_ptr<disassembly>> &v);
            void insert_original_unsafe(const luramas_address where, const std::shared_ptr<disassembly> &v);
            void remove(const std::shared_ptr<disassembly> &dis);

            /* Index is contained in IL */
            bool valid(const std::size_t idx) const;

            /* Disassembly has been removed? */
            bool is_remove(const std::shared_ptr<luramas::il::disassembly> &disassembly) const;

            /* Visits addr of Original IL disassembly. */
            std::shared_ptr<disassembly> visit(const luramas_address addr);

            /* Visits instructions that references addr. */
            std::vector<std::shared_ptr<disassembly>> visit_ref(const luramas_address addr) const;

            /* Validate IL makes sures there is no error in IL disassembly, returns error if any. */
            errors::error validate();

            /* Returns an available temporary register */
            luramas_register get_temp_reg();

            /* Resets temp temporary register */
            void reset_temp_reg();

            boost::unordered_flat_map<std::shared_ptr<disassembly>, std::vector<std::shared_ptr<disassembly>>> insertions; /* Data to inserts, public to allow jump passes to properly link */
            luramas_register ctemp_reg = 0u;                                                                               /* Current temporary register */

          private:
            luramas_register temp_reg = 0u;                                                   /* Original temporary register */
            boost::unordered_flat_map<luramas_address, std::shared_ptr<disassembly>> dis_map; /* Original ADDR map of dism -> IL (Maps diretly to how the original dism is) */
            std::vector<std::shared_ptr<disassembly>> front;                                  /* Data to insert in the front */
            std::vector<std::shared_ptr<disassembly>> back;                                   /* Data to insert in the back */
            boost::unordered_flat_set<std::shared_ptr<disassembly>> ignore;                   /* Data to ignore */

            /* Throws error if IL is not valid */
            void validate(const errors::error &valid);

            /* Validates operands for IL */
            errors::error validate_operands();

            /* Resolves mutated or missing addresses */
            void resolve_addresses();

            /* Resolves jump location and reference */
            void resolve_jumps();

            /* Resolves xrefs */
            void resolve_xrefs();
      };

      namespace helpers {

            namespace low {

                  /* Operand type kind */
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

                  /* Operand */
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
                  template <std::uint8_t MAX_LEN, typename T>
                  struct disassembly_manager {

                        disassembly_manager(const std::vector<std::pair<vinst<MAX_LEN>, T>> &data,
                            const std::shared_ptr<il::ilang> &il,
                            const profile::details &details,
                            const luramas_register temp_reg = 0u,
                            const luramas_flag ffill_pending = false)
                            : data(data), temp_reg(temp_reg), il(il), details(details) {

                              /* Fill all instructions with pending */
                              if (!ffill_pending) {
                                    return;
                              }
                              for (const auto &[i, d] : data) {
                                    const auto ptr = std::make_shared<disassembly>();
                                    ptr->op = arch::opcodes::OP_PEND;
                                    ptr->addr = i.inst.inst.pc;
                                    this->original_address_data[i.inst.inst.real_pc] = std::make_pair(ptr->addr, ptr);
                                    this->il->insert_front(ptr);
                              }
                              this->il->commit_dis();
                              return;
                        };

                        std::vector<std::pair<luramas::il::vinst<MAX_LEN>, T>> data;                                                                 /* Data */
                        luramas_register temp_reg = 0u;                                                                                              /* Allocated largest temp reg: temp_reg <= temp_reg + 1... unused */
                        std::shared_ptr<luramas::il::ilang> il = nullptr;                                                                            /* Linked IL */
                        profile::details details;                                                                                                    /* Profile details */
                        boost::unordered_flat_map<luramas_raddress, std::pair<luramas_address, std::shared_ptr<disassembly>>> original_address_data; /* Real PC -> {Original address, Disassembly pointer} */
                  };
            } // namespace low
      } // namespace helpers
} // namespace luramas::il