#include "../passes.hpp"
#include <chrono>

double profile_time = 0;

namespace luramas::ir {

      /* Dump */
      void dump(const char *const prefix, const ir_stat::space &space, const bool indent, const bool force) {
            luramas_count indenter = 0u;
            for (const auto &o : space) {
                  print_stat(o, indenter, prefix, indent, false, force);
            }
            return;
      }
      void dump(const ir_stat::space &space) {
            dump(nullptr, space, true, true);
            return;
      }
      void print_stat(const std::shared_ptr<ir_stat> &stat, std::size_t &indenter, const char *const prefix, const bool indent, const bool mark, const bool force) {
            if (!stat) {
                  return;
            }
            std::string indenting("");
            switch (stat->k) {
                  case keywords::end:
                  case keywords::page_function_end:
                  case keywords::condition:
                  case keywords::until:
                  case keywords::switch_case:
                  case keywords::switch_default: {
                        indenter -= (indenter && stat->c != condition_kind::if_);
                        break;
                  }
                  default: {
                        break;
                  }
            }
            const auto &str = stat->str();
            if (!str.empty()) {
                  for (auto i = 0u; i < indenter; ++i) {
                        indenting += "    ";
                  }
                  if (prefix) {
                        if (force) {
                              // std::printf(mark ? "[======%s======]%s%s\n" : "[%s]%s%s\n", prefix, indenting.c_str(), str.c_str());
                        } else {
                              LURAMAS_PRINTF(mark ? "[======%s======]%s%s\n" : "[%s]%s%s\n", prefix, indenting.c_str(), str.c_str());
                        }
                  } else {
                        if (force) {
                              //   std::printf("%s%s\n", indenting.c_str(), str.c_str());
                        } else {
                              LURAMAS_PRINTF("%s%s\n", indenting.c_str(), str.c_str());
                        }
                  }
            }
            switch (stat->k) {
                  case keywords::condition:
                  case keywords::page_function_start:
                  case keywords::switch_:
                  case keywords::switch_case:
                  case keywords::switch_default: {
                        ++indenter;
                        break;
                  }
                  default: {
                        indenter += stat->is_loop();
                        break;
                  }
            }
            return;
      }

      namespace passes {

            /* Add */
            void pass_manager::add(const pass_cb &callback, const flags &flag, const std::string &debug) {
                  if (callback) {
                        this->cbs.emplace_back(std::make_pair(callback, std::make_pair(flag, debug)));
                  }
                  return;
            }
            void pass_manager::add(const pass_cb &callback, const std::string &debug) {
                  if (callback) {
                        this->cbs.emplace_back(std::make_pair(callback, std::make_pair(flags(), debug)));
                  }
                  return;
            }

            /* Remove */
            void pass_manager::remove(const std::shared_ptr<ir_stat> &i, const bool safe) {
                  if (i) {
                        if (this->env_flags.fforce_debug_remove) {
                              std::printf("REMOVING %s\n", i->str().c_str());
                        }
#if !defined(LURAMAS_PROFILE)
                        LURAMAS_PRINTF("REMOVING %s\n", i->str().c_str());
#endif //  NDEBUG
                        this->set_safe(i);
                        if (safe && i->is_potential_side_effectable()) {
                              return;
                        }
                        this->removals.insert(i);
                  }
                  return;
            }
            void pass_manager::remove(const ir_stat::space &vect, const bool safe) {
                  for (const auto &i : vect) {
                        this->remove(i, safe);
                  }
                  return;
            }
            void pass_manager::remove(const boost::unordered_flat_set<std::shared_ptr<ir_stat>> &set, const bool safe) {
                  for (const auto &i : set) {
                        this->remove(i, safe);
                  }
                  return;
            }
            void pass_manager::remove(const luramas_address start_idx, const luramas_address end_idx, const bool safe) {
                  for (auto i = start_idx; i < end_idx; ++i) {
                        this->remove(this->ir.data[i], safe);
                  }
                  return;
            }
            void pass_manager::remove(const luramas_blockrange &range, const bool safe) {
                  this->remove(range.first, range.second);
                  return;
            }

            /* Insert */
            void pass_manager::insert(const std::shared_ptr<ir_stat> &where, const std::shared_ptr<ir_stat> &v) {
                  if (where && v) {
                        if (auto [it, inserted] = this->insertions.try_emplace(where, ir_stat::space({v})); !inserted) {
                              it->second.emplace_back(v);
                        }
#if !defined(LURAMAS_PROFILE)
                        LURAMAS_PRINTF("INSERTED %s ON %s\n", v->str().c_str(), where->str().c_str());
#endif //  NDEBUG
                  }
                  return;
            }
            void pass_manager::insert(const std::shared_ptr<ir_stat> &where, const ir_stat::space &space) {
                  for (const auto &i : space) {
                        this->insert(where, i);
                  }
                  return;
            }
            void pass_manager::insert_front(luramas_address where, const std::shared_ptr<ir_stat> &v) {
                  if (where) {
                        --where;
                  } else {
                        this->push_front(v);
                        return;
                  }
                  this->insert(this->ir.data[where], v);
                  return;
            }

            /* Push */
            void pass_manager::push_front(const std::shared_ptr<ir_stat> &v) {
                  if (v) {
                        this->front.emplace_back(v);
                  }
                  return;
            }
            void pass_manager::push_front(const ir_stat::space &v) {
                  for (const auto &i : v) {
                        this->front.emplace_back(i);
                  }
                  return;
            }
            void pass_manager::push_back(const std::shared_ptr<ir_stat> &v) {
                  if (v) {
                        this->back.emplace_back(v);
                  }
                  return;
            }

            /* Contains */
            bool pass_manager::contains(const luramas_address n) const {
                  return this->valid(n);
            }
            bool pass_manager::contains(const luramas_address start, const luramas_address end, const luramas_address n) const {
                  return std::clamp(n, start, end) == n;
            }

            /* Valid */
            bool pass_manager::valid_prev(const std::size_t idx, std::size_t n) const {
                  return idx >= n;
            }
            bool pass_manager::valid_next(const std::size_t idx, std::size_t n) const {
                  return idx + n < this->ir.data.size();
            }
            bool pass_manager::valid(const std::size_t idx) const {
                  return idx < this->ir.data.size();
            }

            /* Is safe */
            bool pass_manager::is_safe_flags(const std::shared_ptr<ir_stat> &se) const {
                  return se && !se->flags.funsafe && !se->flags.fpage_export;
            }
            bool pass_manager::is_safe(const std::shared_ptr<ir_stat> &se) const {
                  if (this->env_flags.fforce_debug_issafe) {
                        std::printf("IS SAFE ON %s\n", se->str().c_str());
                  }
#if !defined(LURAMAS_PROFILE)
                  // if (se) {
                  //       LURAMAS_PRINTF("IS SAFE ON %s\n", se->str().c_str());
                  // }
#endif //  NDEBUG
                  return this->is_safe_flags(se) && !this->mutations.contains(se);
            }
            bool pass_manager::is_safe(const std::size_t start_idx, const std::size_t end_idx) const {
                  for (auto i = start_idx; i < end_idx; ++i) {
                        if (!this->valid(i)) {
                              return false;
                        }
                        if (!this->is_safe(this->ir.data[i])) {
                              return false;
                        }
                  }
                  return true;
            }
            bool pass_manager::is_safe(const luramas_blockrange &r) const {
                  for (auto i = r.first; i < r.second; ++i) {
                        if (!this->valid(i) || !this->is_safe(this->ir.data[i])) {
                              return false;
                        }
                  }
                  return true;
            }

            /* Set safety */
            void pass_manager::set_safe(const std::shared_ptr<ir_stat> &se) {
                  if (se) {
                        if (this->env_flags.fforce_debug_setsafe) {
                              std::printf("SET SAFE ON %s\n", se->str().c_str());
                        }
#if !defined(LURAMAS_PROFILE)
                        //        LURAMAS_PRINTF("SET SAFE ON %s\n", se->str().c_str());
#endif //  NDEBUG
                        this->mutations.insert(se);
                  }
                  return;
            }
            void pass_manager::set_safe(const std::size_t start_idx, const std::size_t end_idx) {
                  for (auto i = start_idx; i < end_idx; ++i) {
                        this->set_safe(this->ir.data[i]);
                  }
                  return;
            }
            void pass_manager::force_mutable_safe(const std::shared_ptr<ir_stat> &stat) {
                  if (this->is_safe_flags(stat) && this->is_mut(stat) && stat->flags.fimmutable) {
                        stat->flags.fimmutable = false;
                        this->remove_mut(stat);
                  }
                  return;
            }

            bool pass_manager::safe(const std::shared_ptr<ir_stat> &se, boost::unordered_flat_set<std::shared_ptr<ir_stat>> *ignore) {
                  if (this->is_safe(se)) {
                        if (ignore) {
                              ignore->insert(se);
                        }
                        this->set_safe(se);
                        return true;
                  }
                  return (ignore && ignore->contains(se));
            }

            /* Move */
            void pass_manager::move(const std::shared_ptr<ir_stat> &where, const std::shared_ptr<ir_stat> &stat) {
                  this->remove(stat);
                  this->insert(where, stat);
                  return;
            }
            void pass_manager::move(const std::shared_ptr<ir_stat> &where, const luramas_blockrange &range) {
                  for (auto i = range.first; i < range.second; ++i) {
                        this->move(where, this->ir.data[i]);
                  }
                  return;
            }
            void pass_manager::move_front(luramas_address where, const std::shared_ptr<ir_stat> &v) {
                  if (where) {
                        --where;
                  } else {
                        this->push_front(v);
                        this->remove(v);
                        return;
                  }
                  this->move(this->ir.data[where], v);
                  return;
            }

            /* Mutate */
            void pass_manager::mut(const char *const debug, const bool marked) {
                  if (this->env_flags.fforce_debug_mut) {
                        std::printf("MUTATED ON %s\n", debug);
                  }
#if !defined(LURAMAS_PROFILE)
                  LURAMAS_PRINTF("MUTATED ON %s\n", debug);
#endif //  NDEBUG
                  this->mutate = true;
                  if (!this->marked) {
                        this->marked = marked;
                  }
                  return;
            }
            bool pass_manager::is_mut() const {
                  return this->mutate;
            }
            bool pass_manager::is_mut(const std::shared_ptr<ir_stat> &stat) const {
                  return this->mutations.contains(stat);
            }
            void pass_manager::remove_mut(const std::shared_ptr<ir_stat> &stat) {
                  this->mutations.erase(stat);
                  return;
            }

            /* Misc */
            luramas_address pass_manager::amount() const {
                  return this->ir.data.size();
            }
            void pass_manager::run() {

                  bool mark = false;
                  shared s;

#ifdef DEBUG
#ifndef LURAMAS_PROFILE
#ifndef LURAMAS_DEBUG_NO_DUMP
                  this->dump();
#endif
                  LURAMAS_PRINTF("RUNNING\n");
                  //std::cin.get();
#endif
#endif

                  do {
                        this->fpmut = false;
                        for (auto &callback : this->cbs) {
                              bool muted = false;
                              s.frunning_again = false;
                              s.ffast_folder = callback.second.first.ffast_folder;
                              do {
                                    if ((!callback.second.first.fsingle_pass || !callback.second.first.is_passed()) && !this->ir.data.empty()) {

#if defined(DEBUG) || defined(LURAMAS_PROFILE)
                                          std::printf("INTITIAL PASS ON %s, %zu\n", callback.second.second.c_str(), this->ir.data.size());
                                          const auto start = std::chrono::high_resolution_clock::now();
#endif
                                          callback.first(*this, s);
#if defined(DEBUG)
                                          this->dbg_pass_callstack.emplace_back(callback.second.second);
#endif
#if defined(DEBUG) || defined(LURAMAS_PROFILE)
                                          const auto end = std::chrono::high_resolution_clock::now();
                                          const std::chrono::duration<double> duration = end - start;
                                          profile_time += duration.count();
                                          LURAMAS_PRINTF("ENDED PASS ON %s, %f, %zu\n", callback.second.second.c_str(), profile_time, this->ir.data.size());
#endif
                                          callback.second.first.passed();
                                          if (!this->fpmut) {
                                                this->fpmut = this->mutate;
                                          }
                                          s.frunning_again = true;
                                          muted = this->mutate;
                                          mark = this->marked;
                                          this->commit(!this->env_flags.fallow_ecc || callback.second.first.fignore_ecc, callback.second.second.c_str());
                                          // luramas::debug::copy_to_clipboard(this->str());
#ifdef DEBUG
#ifndef LURAMAS_PROFILE
                                          if (muted) {
#ifndef LURAMAS_DEBUG_NO_DUMP
                                                this->dump();
#endif
                                                LURAMAS_PRINTF("ENDING PASS ON %s =================================================\n", callback.second.second.c_str());
                                          } else {
#ifndef LURAMAS_DEBUG_NO_DUMP
                                                this->dump();
#endif
                                                LURAMAS_PRINTF("NON MUTATED PASS ON %s =================================================\n", callback.second.second.c_str());
                                          }
                                          //std::cin.get();
#endif
#endif
                                    }
                              } while ((callback.second.first.fmodified || mark) && muted);
                              if (callback.second.first.fafter_single) {
                                    callback.second.first.fsingle_pass = true;
                                    callback.second.first.passed();
                              }
                        }
                  } while (this->fpmut);
                  if (this->mutate && this->cbs.empty()) {
                        this->commit(!this->env_flags.fallow_ecc);
                  }
                  return;
            }
            void pass_manager::clear() {
                  this->cbs.clear();
                  this->mutate = false;
                  this->marked = false;
                  return;
            }
            bool pass_manager::is_removed(const std::shared_ptr<ir_stat> &i) const {
                  return this->removals.contains(i);
            }

            /* Dump */
            void pass_manager::dump(const char *const prefix, const bool indent, const std::shared_ptr<ir_stat> &mark, const bool force, const bool trun_to_mark) const {
                  luramas_count indenter = 0u;
                  for (const auto &o : this->ir.data) {
                        print_stat(o, indenter, prefix, indent, mark && mark == o, force);
                        if (trun_to_mark && mark && mark == o) {
                              return;
                        }
                  }
                  return;
            }
            void pass_manager::dump(const char *const prefix, const bool indent, const boost::unordered_flat_set<std::shared_ptr<ir_stat>> &mark, const bool force) const {
                  luramas_count indenter = 0u;
                  for (const auto &o : this->ir.data) {
                        print_stat(o, indenter, prefix, indent, mark.contains(o), force);
                  }
                  return;
            }
            void pass_manager::dump(const luramas_address start, const luramas_address end, const char *const prefix, const bool indent, const bool force) const {
                  luramas_count indenter = 0u;
                  for (auto i = start; i < end; ++i) {
                        print_stat(this->ir.data[i], indenter, prefix, indent, force);
                  }
                  return;
            }
            std::string pass_manager::str(const luramas_blockrange &range, const char *const prefix) const {
                  std::string result("");
                  for (auto i = range.first; i < range.second; ++i) {
                        result += this->ir.data[i]->str(prefix ? prefix : "") + "\n";
                  }
                  return result;
            }
            std::string pass_manager::str(const char *const prefix) const {

                  return this->str({LURAMAS_IR_ENTRY, this->amount()}, prefix);
            }
            void pass_manager::force_debug() {
                  this->env_flags.fforce_debug_mut = true;
                  this->env_flags.fforce_debug_remove = true;
                  this->env_flags.fforce_debug_setsafe = true;
                  return;
            }
            void pass_manager::unenforce_debug() {
                  this->env_flags.fforce_debug_mut = false;
                  this->env_flags.fforce_debug_remove = false;
                  this->env_flags.fforce_debug_setsafe = false;
                  return;
            }

            std::shared_ptr<ir_stat> &pass_manager::operator[](const luramas_address idx) {
                  return this->ir.data[idx];
            }
            const std::shared_ptr<ir_stat> &pass_manager::operator[](const luramas_address idx) const {
                  return this->ir.data[idx];
            }
            bool pass_manager::valid_range(const luramas_blockrange &range) const {
                  if (range.second < range.first) {
                        return false;
                  }
                  if (range.second >= this->amount()) {
                        return false;
                  }
                  return true;
            }
            luramas_address pass_manager::safe_entry() const {
                  return LURAMAS_IR_ENTRY + (this->ir.data[LURAMAS_IR_ENTRY]->is_k<keywords::definition>() && this->valid_next<1u>(LURAMAS_IR_ENTRY));
            }

            luramas_blockrange pass_manager::range() const {
                  return std::make_pair(LURAMAS_IR_ENTRY, this->amount());
            }
            luramas_blockrange pass_manager::range(const luramas_address curr) const {
                  return std::make_pair(curr, this->amount());
            }
            luramas_range_iter pass_manager::iter() const {
                  return luramas_iter(this->range());
            }
            luramas_range_reverse_iter pass_manager::riter() const {
                  return luramas_riter(this->range());
            }

            void pass_manager::reset() {
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

            void pass_manager::commit(const luramas_flag fignore_ecc, const char *const last_pass) {
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

            void pass_manager::validate() {
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

            void pass_manager::repair() {
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

            void pass_manager::update(const luramas_flag fallow_ecc, const char *const last_pass) {

                  this->processed.clear();
                  luramas_count tag_stack = 0u;
                  std::size_t available = 1u;
                  luramas_addresses breakable_stack;
                  luramas_addresses continueable_stack;
                  std::vector<ir_stat::space> pending_breaks;
                  std::vector<std::pair<std::shared_ptr<ir_stat>, std::size_t>> stack;
                  std::vector<std::vector<std::pair<luramas_address, luramas_address *>>> elif_stack;
                  boost::unordered_flat_map<luramas_id, std::pair<std::optional<luramas_address>, std::optional<luramas_address>>> pages;

#ifdef LURAMAS_ECC
                  /* ECC data */
                  luramas_flag fallow_def = true;
                  boost::unordered_flat_map<luramas_id, bool> unclosed_pages;
                  boost::unordered_flat_map<luramas_address, boost::unordered_flat_set<std::shared_ptr<ir_stat>>> unresolved_labels;
                  boost::unordered_flat_set<luramas_address> labels;
                  boost::unordered_flat_set<std::shared_ptr<ir_stat>> hit;
                  if (fallow_ecc) {
                        hit.reserve(this->ir.data.size());
                  }
#endif

                  for (auto i = LURAMAS_IR_ENTRY; i < this->ir.data.size(); ++i) {

                        const auto &p = this->ir.data[i];
#ifdef LURAMAS_ECC
                        if (fallow_ecc) {
                              if (hit.contains(p)) {
#ifndef LURAMAS_DEBUG_NO_DUMP
                                    this->dump("DEBUG", true, p, true);
#endif
                                    luramas::error::debug_print(last_pass);
                                    luramas::debug::copy_to_clipboard(this->str());
                              } else {
                                    hit.insert(p);
                              }
                              if (p->is_k<keywords::label>()) {
                                    labels.insert(p->label);
                                    unresolved_labels.erase(p->label);
                              }
                              if (p->is_goto_label() && !labels.contains(p->jlabel)) {
                                    auto [it, inserted] = unresolved_labels.emplace(p->jlabel, boost::unordered_flat_set<std::shared_ptr<ir_stat>>{});
                                    it->second.insert(p);
                              }
                        }
#endif
                        if (p->jlabel) {
                              auto [it, inserted] = this->processed.jlabels_refs.try_emplace(p->jlabel, boost::unordered_flat_set<luramas_address>({i}));
                              if (!inserted) {
                                    it->second.insert(i);
                              }
                        }
                        if (p->label) {
                              this->processed.labels.try_emplace(p->label, i);
                        }
                        if (p->is_breakable()) {
                              breakable_stack.emplace_back(i);
                              pending_breaks.emplace_back(ir_stat::space());
                        }
                        if (p->is_continueable()) {
                              continueable_stack.emplace_back(i);
                        }
                        if (!p->is_goto_label()) {
                              p->clear_underlying_labels();
                        }
                        switch (p->k) {
                              case keywords::condition: {
                                    if (p->c != condition_kind::else_ && p->c != condition_kind::elseif_) {
                                          stack.emplace_back(p, i);
                                          elif_stack.emplace_back(std::vector<std::pair<luramas_address, luramas_address *>>());
                                    } else {
                                          if (!elif_stack.empty()) {

                                                elif_stack.back().emplace_back(i, &p->elif_end_label);
#ifdef LURAMAS_ECC
                                                if (fallow_ecc) {
                                                      bool got_else = false;
                                                      for (const auto &[loc, ptr] : elif_stack.back()) {
                                                            const auto &e = this->ir.data[loc];
                                                            if (got_else) {
#ifndef LURAMAS_DEBUG_NO_DUMP
                                                                  this->dump("DEBUG", true, this->ir.data[loc], true);
#endif
#ifdef DEBUG
                                                                  luramas::error::debug_callstack(this->dbg_pass_callstack);
#endif
                                                                  luramas::error::debug_print(last_pass);
                                                                  luramas::error::unexpected_error("else", loc);
                                                            }
                                                            if (e->is<condition_kind::else_>()) {
                                                                  got_else = true;
                                                            }
                                                      }
                                                }
#endif
                                          } else {
#ifdef LURAMAS_ECC
                                                if (fallow_ecc) {
#ifndef LURAMAS_DEBUG_NO_DUMP
                                                      this->dump("DEBUG", true, p, true);
#endif
#ifdef DEBUG
                                                      luramas::error::debug_callstack(this->dbg_pass_callstack);
#endif
                                                      luramas::error::debug_print(last_pass);
                                                      luramas::error::unexpected_error("else", i);
                                                }
#endif
                                          }
                                    }
                                    break;
                              }
                              case keywords::forloop_generic:
                              case keywords::forloop_numeric:
                              case keywords::repeat:
                              case keywords::while_: {
                                    stack.emplace_back(std::make_pair(p, i));
                                    break;
                              }
                              case keywords::end:
                              case keywords::until: {
                                    if (!stack.empty()) {
#ifdef LURAMAS_ECC
                                          if (fallow_ecc) {
                                                if (p->is_k<keywords::until>() && !stack.back().first->is_k<keywords::repeat>()) {
#ifndef LURAMAS_DEBUG_NO_DUMP
                                                      this->dump("DEBUG", true, {p, stack.back().first}, true);
#endif
#ifdef DEBUG
                                                      luramas::error::debug_callstack(this->dbg_pass_callstack);
#endif
                                                      luramas::error::debug_print(last_pass);
                                                      luramas::error::unexpected_error("post exit loop mismatch", i);
                                                }
                                          }
#endif
                                          p->end_label = ++available;
                                          if (stack.back().first->is_k<keywords::condition>() && !elif_stack.empty()) {
                                                for (auto &[loc, addr] : elif_stack.back()) {
                                                      *addr = available;
                                                }
                                                elif_stack.pop_back();
                                          }
                                          stack.back().first->end_label = available;
                                          this->processed.end_labels.try_emplace(available, std::make_pair(stack.back().second, i));
                                          if (!breakable_stack.empty() && breakable_stack.back() == stack.back().second) {
                                                this->processed.parent_loops.try_emplace(i, stack.back().second);
                                                for (const auto &e : pending_breaks.back()) {
                                                      e->underlying_jump = i + 1u;
                                                }
                                                pending_breaks.pop_back();
                                                breakable_stack.pop_back();
                                                continueable_stack.pop_back();
                                          }
                                          stack.pop_back();
                                    } else {
#ifdef LURAMAS_ECC
                                          if (fallow_ecc) {
#ifndef LURAMAS_DEBUG_NO_DUMP
                                                this->dump("DEBUG", true, p, true);
#endif
#ifdef DEBUG
                                                luramas::error::debug_callstack(this->dbg_pass_callstack);
#endif
                                                luramas::error::debug_print(last_pass);
                                                luramas::error::unexpected_error("end", i);
                                          }
#endif
                                    }
                                    break;
                              }
                              case keywords::break_: {
#ifdef LURAMAS_ECC
                                    if (fallow_ecc) {
                                          if (breakable_stack.empty()) {
#ifndef LURAMAS_DEBUG_NO_DUMP
                                                this->dump("DEBUG", true, p, true);
#endif
#ifdef DEBUG
                                                luramas::error::debug_callstack(this->dbg_pass_callstack);
#endif
                                                luramas::error::debug_print(last_pass);
                                                luramas::error::unexpected_error("break", i);
                                          }
                                    }
#endif
                                    if (!breakable_stack.empty()) {
                                          pending_breaks.back().emplace_back(p);
                                    }
                                    break;
                              }
                              case keywords::continue_: {
#ifdef LURAMAS_ECC
                                    if (fallow_ecc) {
                                          if (continueable_stack.empty()) {
#ifndef LURAMAS_DEBUG_NO_DUMP
                                                this->dump("DEBUG", true, p, true);
#endif
#ifdef DEBUG
                                                luramas::error::debug_callstack(this->dbg_pass_callstack);
#endif
                                                luramas::error::debug_print(last_pass);
                                                luramas::error::unexpected_error("continue", i);
                                          }
                                    }
#endif
                                    if (!continueable_stack.empty()) {
                                          p->underlying_jump = continueable_stack.back();
                                    }
                                    break;
                              }
                              case keywords::tag_start: {
#ifdef LURAMAS_ECC
                                    if (fallow_ecc) {
                                          ++tag_stack;
                                    }
#endif
                                    break;
                              }
                              case keywords::tag_end: {
#ifdef LURAMAS_ECC
                                    if (fallow_ecc) {
                                          if (!tag_stack) {
#ifdef DEBUG
                                                luramas::error::debug_callstack(this->dbg_pass_callstack);
#endif
                                                luramas::error::unexpected_error("No tags", i);
                                          }
                                          --tag_stack;
                                    }
#endif
                                    break;
                              }
                              case keywords::page_function_start: {
                                    const auto id = p->r->extract_integral_base();
                                    pages[id].first = i;
#ifdef LURAMAS_ECC
                                    if (fallow_ecc) {
                                          if (!this->env_flags.fecc_unsafe_pages) {
                                                const auto [it, inserted] = unclosed_pages.try_emplace(id, false);
                                                if (!inserted) {
#ifndef LURAMAS_DEBUG_NO_DUMP
                                                      this->dump("DEBUG", true, p, true, true);
#endif
#ifdef DEBUG
                                                      luramas::error::debug_callstack(this->dbg_pass_callstack);
#endif
                                                      luramas::error::debug_print(last_pass);
                                                      luramas::error::unexpected_error("Page already defined: " + p->str(), i);
                                                }
                                                if (it->second) {
#ifndef LURAMAS_DEBUG_NO_DUMP
                                                      this->dump("DEBUG", true, p, true, true);
#endif
#ifdef DEBUG
                                                      luramas::error::debug_callstack(this->dbg_pass_callstack);
#endif
                                                      luramas::error::debug_print(last_pass);
                                                      luramas::error::unexpected_error("Page already completed: " + p->str(), i);
                                                }
                                          }
                                    }
#endif
                                    break;
                              }
                              case keywords::page_function_end: {
                                    const auto id = p->r->extract_integral_base();
                                    pages[id].second = i;
#ifdef LURAMAS_ECC
                                    if (fallow_ecc) {
                                          if (!this->env_flags.fecc_unsafe_pages) {
                                                const auto it = unclosed_pages.find(id);
                                                if (it == unclosed_pages.end()) {
#ifndef LURAMAS_DEBUG_NO_DUMP
                                                      this->dump("DEBUG", true, p, true);
#endif
#ifdef DEBUG
                                                      luramas::error::debug_callstack(this->dbg_pass_callstack);
#endif
                                                      luramas::error::debug_print(last_pass);
                                                      luramas::error::unexpected_error("Page not defined", i);
                                                }
                                                if (it->second) {
#ifndef LURAMAS_DEBUG_NO_DUMP
                                                      this->dump("DEBUG", true, p, true);
#endif
#ifdef DEBUG
                                                      luramas::error::debug_callstack(this->dbg_pass_callstack);
#endif
                                                      luramas::error::debug_print(last_pass);
                                                      luramas::error::unexpected_error("Page already completed", i);
                                                }
                                                it->second = true;
                                          }
                                    }
#endif
                                    break;
                              }
                              case keywords::definition: {
#ifdef LURAMAS_ECC
                                    if (fallow_ecc && !fallow_def) {
#ifndef LURAMAS_DEBUG_NO_DUMP
                                          this->dump("DEBUG", true, p, true, true);
#endif
#ifdef DEBUG
                                          luramas::error::debug_callstack(this->dbg_pass_callstack);
#endif
                                          luramas::error::debug_print(last_pass);
                                          luramas::error::unexpected_error("Definition not allowed here", i);
                                    }
#endif
                                    break;
                              }
                              default: {
                                    break;
                              }
                        }
#ifdef LURAMAS_ECC
                        if (fallow_ecc) {
                              fallow_def = p->k == keywords::page_function_start;
                        }
#endif
                  }
#ifdef LURAMAS_ECC
                  if (fallow_ecc) {
                        boost::unordered_flat_set<std::shared_ptr<ir_stat>> unfinished;
                        if (!stack.empty()) {
                              for (const auto &[stat, loc] : stack) {
                                    unfinished.insert(stat);
                              }
#ifndef LURAMAS_DEBUG_NO_DUMP
                              this->dump("DEBUG", true, unfinished, true);
#endif
#ifdef DEBUG
                              luramas::error::debug_callstack(this->dbg_pass_callstack);
#endif
                              luramas::error::debug_print(last_pass);
                              luramas::error::unexpected_error("UNCLOSED STATS");
                        }
                        for (const auto &[label, refs] : unresolved_labels) {
                              unfinished.insert(refs.begin(), refs.end());
                        }
                        if (!unfinished.empty()) {
#ifndef LURAMAS_DEBUG_NO_DUMP
                              this->dump("DEBUG", true, unfinished, true);
#endif
#ifdef DEBUG
                              luramas::error::debug_callstack(this->dbg_pass_callstack);
#endif
                              luramas::error::debug_print(last_pass);
                              luramas::error::unexpected_error("REFS NO LABELS");
                        }
                        if (tag_stack) {
#ifdef DEBUG
                              luramas::error::debug_callstack(this->dbg_pass_callstack);
#endif
                              luramas::error::unexpected_error("Unclosed tags");
                        }
                        if (!this->env_flags.fecc_unsafe_pages) {
                              for (const auto &[id, completed] : unclosed_pages) {
                                    if (!completed) {
#ifdef DEBUG
                                          luramas::error::debug_callstack(this->dbg_pass_callstack);
#endif
                                          luramas::error::unexpected_error("Unclosed page: " + std::to_string(id));
                                    }
                              }
                        }
                  }
#endif
                  /* Finalize */
                  for (const auto [id, data] : pages) {

                        if (const auto &[start, end] = data; start && end) {
                              this->processed.pages[id] = std::make_pair(*start, *end);
                        }
                  }
                  return;
            }
      } // namespace passes
} // namespace luramas::ir