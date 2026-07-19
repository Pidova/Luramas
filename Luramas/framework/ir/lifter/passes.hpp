#pragma once
#include "../ir.hpp"
#include "definitions.hpp"
#include "generation.hpp"

namespace luramas::ir::passes {

      /* Flags for runnning passes */
      struct flags {

            luramas_flag ffast_folder = false;  /* Allows folding to preform dead label elimination */
            luramas_flag fmodified = false;     /* Keeps calling the same pass over and over again until no changes have been made */
            luramas_flag fsingle_pass = false;  /* Only pass once */
            luramas_flag fafter_single = false; /* Keeps passing but only once after it can not anymore */
            luramas_flag fignore_ecc = false;   /* Ignore ecc if it is enabled */

            void passed() {
                  this->fpass = true;
                  return;
            }
            bool is_passed() const {
                  return this->fpass;
            }

          private:
            luramas_flag fpass = false; /* Passed over current pass */
      };

      /* Detailed flags */
      struct detailed_flags {
            luramas_flag fmain_closure = false; /* Main closure */
      };

      /* Shared data among passes */
      struct shared {
            luramas_flag fran_definition_flattening = false;                                                              /* Already ran function definition flattening */
            luramas_flag ffast_folder = false;                                                                            /* Fast folder */
            luramas_flag frunning_again = false;                                                                          /* Run again */
            luramas_flag ffirst_const_prop = true;                                                                        /* First time running constant propagation */
            boost::unordered_flat_set<std::shared_ptr<ir_stat>> scheduled_stats;                                          /* Cached stats */
            boost::unordered_flat_map<std::shared_ptr<ir_stat>, std::vector<std::shared_ptr<ir_stat>>> scheduled_inserts; /* Cached inserts */
      };

      class pass_manager {

          public:
            using pass_cb = void (*)(pass_manager &pm, shared &s);

            pass_manager(const se_ir &ir, const environment_flags &env_flags = environment_flags())
                : ir(ir), env_flags(env_flags) {
                  this->mutated.reserve(this->ir.data.size());
                  this->removals.reserve(this->ir.data.size());
                  this->insertions.reserve(this->ir.data.size());
                  this->mutations.reserve(this->ir.data.size());
                  this->update(env_flags.fallow_ecc);
                  return;
            }

            /* Passes */
            void add(const pass_cb &callback, const flags &flag = flags(), const std::string &debug = "");
            void add(const pass_cb &callback, const std::string &debug = "");
            void run();

            /* Removals */
            void remove(const std::shared_ptr<ir_stat> &i, const bool safe = false);
            void remove(const ir_stat::space &vect, const bool safe = false);
            void remove(const boost::unordered_flat_set<std::shared_ptr<ir_stat>> &set, const bool safe = false);
            void remove(const luramas_address start_idx, const luramas_address end_idx, const bool safe = false);
            void remove(const luramas_blockrange &range, const bool safe = false);
            template <typename... args>
            void remove(const std::shared_ptr<ir_stat> &i, const args &...va) {
                  this->remove(i);
                  this->remove(va...);
                  return;
            }

            /* Insertions */
            void insert(const std::shared_ptr<ir_stat> &where, const std::shared_ptr<ir_stat> &v);
            void insert(const std::shared_ptr<ir_stat> &where, const ir_stat::space &space);
            template <typename... args>
            void insert(const std::shared_ptr<ir_stat> &where, const std::shared_ptr<ir_stat> &v, const args &...va) {
                  this->insert(where, v);
                  this->insert(where, va...);
                  return;
            }

            /* Insert-fronts */
            void insert_front(luramas_address where, const std::shared_ptr<ir_stat> &v);
            template <typename... args>
            void insert_front(luramas_address where, const std::shared_ptr<ir_stat> &v, const args &...va) {
                  this->insert_front(where, v);
                  this->insert_front(where, va...);
                  return;
            }

            /* Push */
            void push_front(const std::shared_ptr<ir_stat> &v);
            void push_front(const ir_stat::space &v);
            void push_back(const std::shared_ptr<ir_stat> &v);
            void clear();
            bool is_removed(const std::shared_ptr<ir_stat> &i) const;

            /* Valids */
            template <std::size_t n>
            bool valid_prev(const std::size_t idx) const {
                  return idx >= n;
            }
            template <std::size_t n>
            bool valid_next(const std::size_t idx) const {
                  return idx + n < this->ir.data.size();
            }

            /* Contains */
            bool contains(const luramas_address n) const;
            bool contains(const luramas_address start, const luramas_address end, const luramas_address n) const;

            /* Valid */
            bool valid_prev(const std::size_t idx, std::size_t n) const;
            bool valid_next(const std::size_t idx, std::size_t n) const;
            bool valid(const std::size_t idx) const;

            /* Is safe */
            bool is_safe_flags(const std::shared_ptr<ir_stat> &se) const;
            bool is_safe(const std::shared_ptr<ir_stat> &se) const;
            bool is_safe(const std::size_t start_idx, const std::size_t end_idx) const;
            bool is_safe(const luramas_blockrange &r) const;
            template <typename... args>
            bool is_safe(const std::shared_ptr<ir_stat> &se, const args &...va) const {
                  return this->is_safe(se) && this->is_safe(va...);
            }

            /* Set safe */
            void set_safe(const std::shared_ptr<ir_stat> &se);
            void set_safe(const std::size_t start_idx, const std::size_t end_idx);
            template <typename... args>
            void set_safe(const std::shared_ptr<ir_stat> &se, const args &...va) {
                  this->set_safe(se);
                  this->set_safe(va...);
                  return;
            }
            void force_mutable_safe(const std::shared_ptr<ir_stat> &stat);

            /* Check safety and set */
            bool safe(const std::shared_ptr<ir_stat> &se, boost::unordered_flat_set<std::shared_ptr<ir_stat>> *ignore = nullptr);
            template <typename... args>
            bool safe(const std::shared_ptr<ir_stat> &se, boost::unordered_flat_set<std::shared_ptr<ir_stat>> *ignore, const args &...va) {
                  return this->is_safe(se, va...) && this->safe(se, ignore) && (this->safe(va, ignore) && ...);
            }
            template <typename... args>
            bool safe(const std::shared_ptr<ir_stat> &se, const args &...va) {
                  boost::unordered_flat_set<std::shared_ptr<ir_stat>> ignore;
                  return this->safe(se, &ignore) && (this->safe(va, &ignore) && ...);
            }

            /* Move */
            void move(const std::shared_ptr<ir_stat> &where, const std::shared_ptr<ir_stat> &stat);
            void move(const std::shared_ptr<ir_stat> &where, const luramas_blockrange &range);
            void move_front(luramas_address where, const std::shared_ptr<ir_stat> &v);

            /* Mutate */
            void mut(const char *const debug = "", const bool marked = false);
            bool is_mut() const;
            bool is_mut(const std::shared_ptr<ir_stat> &stat) const;
            void remove_mut(const std::shared_ptr<ir_stat> &stat);

            luramas_address amount() const;

            /* Dump */
            void dump(const char *const prefix = nullptr, const bool indent = false, const std::shared_ptr<ir_stat> &mark = nullptr, const bool force = false, const bool trun_to_mark = false) const;
            void dump(const char *const prefix, const bool indent, const boost::unordered_flat_set<std::shared_ptr<ir_stat>> &mark, const bool force = false) const;
            void dump(const luramas_address start, const luramas_address end, const char *const prefix = nullptr, const bool indent = false, const bool force = false) const;
            std::string str(const luramas_blockrange &range, const char *const prefix = nullptr) const;
            std::string str(const char *const prefix = nullptr) const;
            void force_debug();
            void unenforce_debug();

            /* Misc */
            std::shared_ptr<ir_stat> &operator[](const luramas_address idx);
            const std::shared_ptr<ir_stat> &operator[](const luramas_address idx) const;
            bool valid_range(const luramas_blockrange &range) const;
            luramas_address safe_entry() const;

            /* Ranges  */
            luramas_blockrange range() const;
            luramas_blockrange range(const luramas_address curr) const;
            luramas_range_iter iter() const;
            luramas_range_reverse_iter riter() const;

            /* Data */
            se_ir ir;
            environment_flags env_flags;
            detailed_flags det_flags;
            environment_data env_data;

            /* Processed data (all references are indexes) */
            struct processed {

                  boost::unordered_flat_map<luramas_address, std::pair<luramas_address /* Condition */, luramas_address /* End */>> end_labels; /* End labels */
                  boost::unordered_flat_map<luramas_address, boost::unordered_flat_set<luramas_address>> jlabels_refs;                          /* Jump labels references */
                  boost::unordered_flat_map<luramas_address, luramas_address> labels;                                                           /* Label locations */
                  boost::unordered_flat_map<luramas_address, luramas_address> parent_loops;                                                     /* Parent loops given address */
                  boost::unordered_flat_map<std::shared_ptr<ir_stat>, definitions::exprs> values;                                               /* EXPR Values */
                  boost::unordered_flat_map<luramas_id, std::pair<luramas_address, luramas_address>> pages;                                     /* Page ID, {Page start, Page end} */

                  void clear() {
                        *this = processed();
                        return;
                  }
            } processed;
            luramas_address label_padding = 0u; /* Pad labels */
            luramas_flag fpmut = false;         /* Pass mutated? */

          private:
            std::vector<std::pair<pass_cb, std::pair<flags, std::string>>> cbs;             /* Passes */
            boost::unordered_flat_multiset<std::shared_ptr<ir_stat>> removals;              /* Removals */
            boost::unordered_flat_map<std::shared_ptr<ir_stat>, ir_stat::space> insertions; /* Insertions */
            boost::unordered_flat_set<std::shared_ptr<ir_stat>> mutations;                  /* Mutations */
            ir_stat::space mutated;                                                         /* Mutated */
            ir_stat::space front;                                                           /* Front insertions */
            ir_stat::space back;                                                            /* Back insertions */

#if defined(DEBUG)
            std::vector<std::string> dbg_pass_callstack;
#endif

            inline void reset() {
                  this->label_padding = 0u;
                  this->mutate = false;
                  this->marked = false;
                  this->removals.clear();
                  this->insertions.clear();
                  this->mutations.clear();
                  this->front.clear();
                  this->back.clear();
                  this->processed.values.clear();
                  this->processed.parent_loops.clear();
                  return;
            }

            bool mutate = false;
            bool marked = false; /* Force to pass again */
            inline void commit(const luramas_flag fignore_ecc, const char *const last_pass = "") {
                  if (!this->removals.empty() || !this->insertions.empty() || !this->front.empty() || !this->back.empty()) {
                        this->mutated = std::move(this->front);
                        this->mutated.reserve(this->mutated.size() + this->ir.data.size() + this->insertions.size() * 2u);
                        for (const auto &i : this->ir.data) {
                              if (!this->is_removed(i) && !i->is_k<keywords::nothing>()) {
                                    this->mutated.emplace_back(i);
                              }
                              if (const auto it = this->insertions.find(i); it != this->insertions.end()) {
                                    this->mutated.reserve(this->mutated.size() + it->second.size());
                                    this->mutated.insert(this->mutated.end(), std::make_move_iterator(it->second.begin()), std::make_move_iterator(it->second.end()));
                              }
                        }
                        this->mutated.reserve(this->mutated.size() + this->back.size());
                        this->mutated.insert(this->mutated.end(), this->back.begin(), this->back.end());
                        this->ir.data.reserve(this->mutated.size());
                        this->ir.data = this->mutated;
                  }
#ifdef DEBUG
                  //this->dump("OPT", true);
                  //std::cin.get();
#endif
                  this->reset();
                  this->update(!fignore_ecc, last_pass);
                  for (const auto &i : this->mutated) {
                        if (i->flags.fimmutable) {
                              this->mutations.insert(i);
                        }
                  }
                  return;
            }

            inline void validate() {
                  boost::unordered_flat_set<luramas_address> labels;
                  boost::unordered_flat_set<luramas_address> jlabels;
                  for (const auto &i : this->ir.data) {
                        if (i->is_goto_label()) {
                              jlabels.insert(i->jlabel);
                        }
                        if (i->is_k<keywords::label>()) {
                              labels.insert(i->label);
                        }
                  }
                  for (const auto &i : jlabels) {
                        if (!labels.contains(i)) {
                              luramas::error::error("Undeclared goto found");
                        }
                  }
                  return;
            }
            inline void repair() {
                  std::size_t stack = 0u;
                  for (const auto &p : this->ir.data) {
                        switch (p->k) {
                              case keywords::condition: {
                                    if (p->c == condition_kind::if_) {
                                          ++stack;
                                    }
                                    break;
                              }
                              case keywords::forloop_generic:
                              case keywords::forloop_numeric:
                              case keywords::repeat:
                              case keywords::while_: {
                                    ++stack;
                                    break;
                              }
                              case keywords::end:
                              case keywords::until: {
                                    if (!stack) {
                                          this->remove(p);
                                    } else if (!this->is_removed(p)) {
                                          --stack;
                                    }
                                    break;
                              }
                              default: {
                                    break;
                              }
                        }
                  }
                  return;
            }
            void update(const luramas_flag fallow_ecc, const char *const last_pass = "");
      };

      /* Basic */
      void allign_pages(pass_manager &pm, shared &s);
      void agressive_thread_out(pass_manager &pm, shared &s);
      void block_merger(pass_manager &pm, shared &s);
      void branch_optimization(pass_manager &pm, shared &s);
      void branch_redirection(pass_manager &pm, shared &s);
      void branch_simplification(pass_manager &pm, shared &s);
      void branch_threading(pass_manager &pm, shared &s);
      void expression_canonicalization_elimination(pass_manager &pm, shared &s);
      void constant_fold(pass_manager &pm, shared &s);
      void constant_propagation(pass_manager &pm, shared &s);
      void control_flow_simplification(pass_manager &pm, shared &s);
      void complete_pages(pass_manager &pm, shared &s);
      void close_pages(pass_manager &pm, shared &s);
      void dead_controller_removal(pass_manager &pm, shared &s);
      void dead_code_elimination(pass_manager &pm, shared &s);
      void dead_label_elimination(pass_manager &pm, shared &s);
      void dead_page_elimination(pass_manager &pm, shared &s);
      void dead_store_elimination(pass_manager &pm, shared &s);
      void definition_inference(pass_manager &pm, shared &s);
      void definition_types(pass_manager &pm, shared &s);
      void definition_flattening(pass_manager &pm, shared &s);
      void flag_optimization(pass_manager &pm, shared &s);
      void generate_page_pass(pass_manager &pm, shared &s);
      void inline_functions(pass_manager &pm, shared &s);
      void jump_threading(pass_manager &pm, shared &s);
      void label_flatten(pass_manager &pm, shared &s);
      void loop_canonicalize_exits(pass_manager &pm, shared &s);
      void loop_simplification(pass_manager &pm, shared &s);
      void loop_unroll(pass_manager &pm, shared &s);
      void loop_winding(pass_manager &pm, shared &s);
      void make_registers_unique(pass_manager &pm, shared &s);
      void memory_inference(pass_manager &pm, shared &s);
      void merge_label_page(pass_manager &pm, shared &s);
      void organize_pages(pass_manager &pm, shared &s);
      void page_adjust_linked(pass_manager &pm, shared &s);
      void page_code_organization(pass_manager &pm, shared &s);
      void page_promotion(pass_manager &pm, shared &s);
      void page_referenced_out_of_scope(pass_manager &pm, shared &s);
      void page_return_params_adjust(pass_manager &pm, shared &s);
      void page_return_promotion(pass_manager &pm, shared &s);
      void page_generate_main_page(pass_manager &pm, shared &s);
      void page_inliner(pass_manager &pm, shared &s);
      void page_promote_global_gotos_controllers(pass_manager &pm, shared &s);
      void page_promote_orphans(pass_manager &pm, shared &s);
      void pages_set_controller_flag(pass_manager &pm, shared &s);
      void psuedo_instruction_elimination(pass_manager &pm, shared &s);
      void redundant_condition_elimination(pass_manager &pm, shared &s);
      void set_descriptor_types(pass_manager &pm, shared &s);
      void stack_to_register_promote(pass_manager &pm, shared &s);
      void static_definition_inference(pass_manager &pm, shared &s);
      void sub_expression_reordering(pass_manager &pm, shared &s);
      void unreachable_code_elimination(pass_manager &pm, shared &s);
      void update_closure_definition(pass_manager &pm, shared &s);
      void variadic_function(pass_manager &pm, shared &s);
      void virtual_function_inline(pass_manager &pm, shared &s);
      void virtual_function_reconstruction(pass_manager &pm, shared &s);

      /* Multipasses */
      void add_page_promote_nofall(pass_manager &pm, const flags &flag, const std::string &debug);

      /* FSSA requirement */
      void dead_flag_elimination(pass_manager &pm, shared &s, generation::flag_ssa::fssa &fssa);
      void flag_propagation(pass_manager &pm, shared &s, generation::flag_ssa::fssa &fssa);

      /* SSA requirement */
      void definition_flattening(pass_manager &pm, shared &s, generation::ssa::ssa &ssa);
      void dead_type_elimination(pass_manager &pm, shared &s, generation::ssa::ssa &ssa);
      void dead_page_definition_elimination(pass_manager &pm, shared &s, generation::ssa::ssa &ssa);
      void dead_main_definition_elimination(pass_manager &pm, shared &s, generation::ssa::ssa &ssa);
      void instruction_hoisting(pass_manager &pm, shared &s, generation::ssa::ssa &ssa);
      void instruction_scheduling(pass_manager &pm, shared &s, generation::ssa::ssa &ssa);

      /* SSA and Types requirement */
      void dead_type_dependant_elimination(pass_manager &pm, shared &s, generation::ssa::ssa &ssa, const boost::unordered_flat_map<luramas_xregister, std::shared_ptr<ir::types::object::type>> &types);

} // namespace luramas::ir::passes