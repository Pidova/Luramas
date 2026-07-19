#pragma once
#include "../passes.hpp"
#include "extras/stats.hpp"

namespace luramas::ir::tools {

      struct addr_expr {

            luramas_flag stat = false;
            luramas_address n = 0u;
            std::shared_ptr<ir_stat::ir_expr> e = nullptr;

            addr_expr() = default;
            addr_expr(const luramas_address n)
                : stat(true), n(n), e(nullptr) {
            }
            addr_expr(const luramas_address n, const std::shared_ptr<ir_stat::ir_expr> &e)
                : stat(false), n(n), e(e) {
            }
      };

      /*  Thresholds */
      bool treshold(const luramas_address target, const luramas_address start, const luramas_address end);    /* [start, end] */
      bool treshold_ie(const luramas_address target, const luramas_address start, const luramas_address end); /* [start, end) */
      bool treshold_ei(const luramas_address target, const luramas_address start, const luramas_address end); /* (start, end] */
      bool treshold_ii(const luramas_address target, const luramas_address start, const luramas_address end); /* [start, end] */
      bool treshold(const luramas_address target, const luramas_blockrange &block);                           /* Block, [start, end) */

      /* Mutates */
      bool mutates(luramas::ir::passes::pass_manager &pm, const std::shared_ptr<ir_stat::ir_expr> &target, const luramas_address start, const luramas_address end);
      bool mutates(luramas::ir::passes::pass_manager &pm, const luramas_register target, const luramas_address start, const luramas_address end);
      bool mutates(luramas::ir::passes::pass_manager &pm, const std::shared_ptr<ir_stat> &single_assignment_target, const luramas_address start, const luramas_address end);

      /* Indicates start unsafely or safely breaks out of a loop */
      bool breaks_out(luramas::ir::passes::pass_manager &pm, const luramas_address start, const luramas_address label);

      /* Start can be a break? */
      bool can_breakout(luramas::ir::passes::pass_manager &pm, const luramas_address start, const luramas_address label);

      /* Start can be a continue? */
      bool can_continue(luramas::ir::passes::pass_manager &pm, const luramas_address start, const luramas_address label, const bool pending_label_loop = false);

      /* Validates condition stack until ++i = start == end */
      enum class cond_stack_reason : std::uint8_t {
            nothing,
            mismatch,
            closing,
            no_closing,
            termination
      };
      struct cond_stack {
            std::intptr_t closing_val = 0;
            std::size_t closing_index = 0u;
            bool valid = false;
            cond_stack_reason reason = cond_stack_reason::nothing;
      };
      cond_stack stack_validate(luramas::ir::passes::pass_manager &pm, const luramas_address start, const luramas_address end);

      /* Next valid jump label */
      luramas_address next_valid_jump(luramas::ir::passes::pass_manager &pm);

      /* Back track endings */
      luramas_address backtrack(luramas::ir::passes::pass_manager &pm, const luramas_address scope_end_stat, bool &valid, const luramas_address break_label = 0u);

      /* Extract valid block with start and end for range */
      bool valid_block_extract(luramas::ir::passes::pass_manager &pm, const luramas_address start, const luramas_address end, luramas_address &result, bool &stack_valid);

      /* Condition has else? */
      bool condition_has_else(luramas::ir::passes::pass_manager &pm, const luramas_address start, const luramas_address end);

      /* Index with main and a potiential closure to index */
      std::shared_ptr<ir_stat> idx(const ir_stat::space &main, const std::shared_ptr<ir_stat::ir_expr> &potiential_closure, const luramas_address idx);

      namespace block {

            /* Block has no volatiles? */
            bool independent(const ir_stat::space &data);

            /* Blocks dominant by no labels (Can be unordered) */
            ir_stat::space orphaned(luramas::ir::passes::pass_manager &pm, const luramas_blockrange &range);

      } // namespace block

      namespace trackers {

            /* Track unfinished conditions from start to end */
            std::vector<std::pair<luramas_address, std::shared_ptr<ir_stat>>> unfinished_condition(luramas::ir::passes::pass_manager &pm, const luramas_address start, const luramas_address end, const bool forward = true);

            /* Take loop break */
            luramas_address loop_break(luramas::ir::passes::pass_manager &pm, const luramas_address start);

            /* Take loop continue */
            luramas_address loop_continue(luramas::ir::passes::pass_manager &pm, const luramas_address start);

            /* Track else end */
            luramas_address else_end(luramas::ir::passes::pass_manager &pm, const luramas_address start);

            /* Tracks start of scope relative given needs to be above(y) with it being in the same scope as most_out_scope(x) */
            luramas_address relative_scope(luramas::ir::passes::pass_manager &pm, const luramas_address most_out_scope, generation::cfg::cfg *cfg = nullptr);

            /* Follows control flow until it finds the next safe executable stat ie NOT (random end, goto (MUST BE FORWARD), else). */
            luramas_address next_safe_executable(luramas::ir::passes::pass_manager &pm, luramas_address start, const bool include_implicit_gotos = false /* Include breaks, continues? */, const luramas_vaddress expecting_goto = -1 /* Stops if goto is hit */);

            /* Tracks parent loop */
            std::pair<luramas_address /* Start */, luramas_address /* End*/> parent_loop(luramas::ir::passes::pass_manager &pm, const luramas_address start);

            /* Safe trace a page from start */
            std::pair<bool /* Found? */, luramas_address /* Loc */> safe_trace_page(luramas::ir::passes::pass_manager &pm, const luramas_address start, const luramas_id id, const bool include_end = false);

            /* Tracks parent loop given end */
            luramas_address ending_parent_loop(luramas::ir::passes::pass_manager &pm, const luramas_address loop_end);

            /* Refer to (next_safe_executable) but ignoes certain keywords */
            luramas_address next_safe_executable(luramas::ir::passes::pass_manager &pm, luramas_address start, const boost::unordered_flat_set<keywords> &k, const bool include_implicit_gotos = false, const luramas_vaddress expecting_goto = -1 /* Stops if goto is hit */);

      } // namespace trackers

      namespace visitors {

            /* Visit prevs condition */
            luramas_address prev_cond(luramas::ir::passes::pass_manager &pm, const luramas_address start);

            /* Visit last end */
            luramas_address last_end(luramas::ir::passes::pass_manager &pm, const luramas_address start);
            luramas_address prev_last_end(luramas::ir::passes::pass_manager &pm, const luramas_address start);

            /* Visit last safe end */
            luramas_address last_safe_end(luramas::ir::passes::pass_manager &pm, const luramas_address start, bool &hit);
            luramas_address prev_safe_end(luramas::ir::passes::pass_manager &pm, const luramas_address start, bool &hit);

            /* Visit next loop continuous end  */
            luramas_address next_continuous_loop_end(luramas::ir::passes::pass_manager &pm, const luramas_address start);

            luramas_address prev_loc(luramas::ir::passes::pass_manager &pm, const luramas_address on);
            luramas_address next_loc(luramas::ir::passes::pass_manager &pm, const luramas_address on);
            std::shared_ptr<ir_stat> prev(luramas::ir::passes::pass_manager &pm, const luramas_address on);
            std::shared_ptr<ir_stat> next(luramas::ir::passes::pass_manager &pm, const luramas_address on);
            luramas_address next_executable(luramas::ir::passes::pass_manager &pm, const luramas_address on);
            luramas_address prev_executable(luramas::ir::passes::pass_manager &pm, const luramas_address on);
            luramas_address next_safe_executable(luramas::ir::passes::pass_manager &pm, const luramas_address on);
            luramas_address prev_safe_executable(luramas::ir::passes::pass_manager &pm, const luramas_address on);

            /* Next/Prev executable stat */
            std::shared_ptr<ir_stat> next_executable_stat(luramas::ir::passes::pass_manager &pm, const luramas_address on);
            std::shared_ptr<ir_stat> prev_executable_stat(luramas::ir::passes::pass_manager &pm, const luramas_address on);

            /* Last/Prev end stat */
            std::shared_ptr<ir_stat> last_safe_end_stat(luramas::ir::passes::pass_manager &pm, const luramas_address on);
            std::shared_ptr<ir_stat> prev_safe_end_stat(luramas::ir::passes::pass_manager &pm, const luramas_address on);

            std::shared_ptr<ir_stat> next_safe_executable_stat(luramas::ir::passes::pass_manager &pm, const luramas_address on);
            std::shared_ptr<ir_stat> prev_safe_executable_stat(luramas::ir::passes::pass_manager &pm, const luramas_address on);
            std::shared_ptr<ir_stat> end_label_stat(luramas::ir::passes::pass_manager &pm, const std::shared_ptr<ir_stat> &stat);
            luramas_address explicit_cond_end(luramas::ir::passes::pass_manager &pm, const std::shared_ptr<ir_stat> &stat);

            bool parent_ifcond(luramas::ir::passes::pass_manager &pm, const luramas_address loc, luramas_address &buffer);
            bool parent_loop(luramas::ir::passes::pass_manager &pm, const luramas_address loc, luramas_address &buffer);

            /* First executable instruction orphaned from pages */
            luramas_address first_orphaned_address_from_page(luramas::ir::passes::pass_manager &pm);
      } // namespace visitors

      namespace accumulate {

            /* 
                Gathers all paths in addresses that a block can take (Fast): 
                -1 = terminates (Return, call no return, global goto label, etc) 
                -2 = continue   (Continues to rest of code, Does not include goto address after block)
                => 0 = valid
            */
            luramas_vaddresses paths(luramas::ir::passes::pass_manager &pm, const luramas_blockrange &block);

            /* Gathers all jump out addresses that jump out of block range */
            luramas_addresses jump_outs(luramas::ir::passes::pass_manager &pm, const luramas_blockrange &block);

            /* Gathers all label refs */
            luramas_addresses refs(luramas::ir::passes::pass_manager &pm, const luramas_blockrange &range, const luramas_address jlabel);

            /* Gathers all dominant addresses */
            luramas_addresses dominant(luramas::ir::passes::pass_manager &pm, const luramas_address start, const luramas_address end);

            /* Extracts dominant nodes in blocks */
            std::vector<luramas_addresses> dominant(luramas::ir::passes::pass_manager &pm, const std::vector<luramas_blockrange> &v);

            /* Given condition will get all dominant nodes encapsulating it */
            std::vector<luramas_addresses> dominant(luramas::ir::passes::pass_manager &pm, const luramas_address start);

            /* Gather all keywords in block */
            luramas_addresses keyword(luramas::ir::passes::pass_manager &pm, const luramas_blockrange &block, const keywords specifier);

            /* Gather all keywords in blocks */
            std::vector<luramas_addresses> keyword(luramas::ir::passes::pass_manager &pm, const std::vector<luramas_addresses> &blocks, const keywords specifier);

            /* Gets all reverse dominant addresses */
            luramas_addresses reverse_dominant(luramas::ir::passes::pass_manager &pm, const luramas_address start);

            /* Gather all parent loops given range */
            luramas_addresses parent_loops(luramas::ir::passes::pass_manager &pm, const luramas_address start, const luramas_address end);

            /* Gather all explicit stats that jump past end */
            luramas_addresses explicit_jump_past(luramas::ir::passes::pass_manager &pm, const luramas_address start, const luramas_address end);

            /* Gathers all labels from gotos (implicit and explicit) */
            luramas_addresses goto_labels(luramas::ir::passes::pass_manager &pm, const luramas_addresses &addresses);

            /* Gathers all break outs of loop */
            luramas_addresses break_outs(luramas::ir::passes::pass_manager &pm, const luramas_address loop_start);

            /* Gathers all labels with address of where there at and addresses of where they are referenced */
            boost::unordered_flat_map<luramas_address, luramas_addresses> labels(luramas::ir::passes::pass_manager &pm, const luramas_blockrange &range);

            /* Gets all page call or jump args give page ID and idx */
            ir_stat::ir_expr::space page_arg(luramas::ir::passes::pass_manager &pm, const luramas_id page, const luramas_index idx);

            namespace orphans {

                  /* Gathers all implicit gotos */
                  luramas_addresses implicit_gotos(luramas::ir::passes::pass_manager &pm, const luramas_blockrange &range);

                  /* Gathers all page starts and end */
                  luramas_addresses page_declaration(luramas::ir::passes::pass_manager &pm, const luramas_blockrange &range);
            } // namespace orphans

            template <keywords k>
            luramas_addresses keyword(luramas::ir::passes::pass_manager &pm, const luramas_address start, const luramas_address end) {

                  luramas_addresses result;
                  for (auto i = start; i < end; ++i) {
                        if (!pm.contains(i)) {
                              break;
                        }
                        if (pm[i]->is_k<k>()) {
                              result.emplace_back(i);
                        }
                  }
                  return result;
            }

            template <typename... keywords>
            luramas_addresses keyword(luramas::ir::passes::pass_manager &pm, const luramas_address start, const luramas_address end, keywords... K) {

                  luramas_addresses result;
                  for (auto i = start; i < end; ++i) {
                        if (!pm.contains(i)) {
                              break;
                        }
                        if ((pm[i]->is_k(K) || ...)) {
                              result.emplace_back(i);
                        }
                  }
                  return result;
            }

            template <typename... keywords>
            luramas_addresses keyword(luramas::ir::passes::pass_manager &pm, const luramas_address start, const luramas_address end, const boost::unordered_flat_set<luramas_address> &ignore, keywords... K) {

                  luramas_addresses result;

                  for (auto i = start; i < end; ++i) {
                        if (ignore.contains(i)) {
                              continue;
                        }
                        if (!pm.contains(i)) {
                              break;
                        }
                        if ((pm[i]->is_k(K) || ...)) {
                              result.emplace_back(i);
                        }
                  }
                  return result;
            }
      } // namespace accumulate

      namespace find {

            /* Find stat by pointer (Returns pm.amount() if not found)  */
            luramas_address stat(luramas::ir::passes::pass_manager &pm, const std::shared_ptr<ir_stat> &stat);

            /* Find stat with call back and direction inclusive of start */
            using find_stat_cb = std::function<bool(const std::shared_ptr<ir_stat> &)>;
            std::optional<luramas_address> stat(luramas::ir::passes::pass_manager &pm, const LURAMAS_IR_DIRECTION_KINDS direction, const luramas_address start, const find_stat_cb &cb);
            luramas_address contiguous_stat(luramas::ir::passes::pass_manager &pm, const LURAMAS_IR_DIRECTION_KINDS direction, const luramas_address start, const find_stat_cb &cb);

            /* Find expr using callback */
            using find_expr_cb = std::function<bool(const std::shared_ptr<ir_stat::ir_expr> &)>;
            std::shared_ptr<ir_stat::ir_expr> expr(const std::shared_ptr<ir_stat::ir_expr> &expr, const find_expr_cb &cb);
            template <typename... Targs>
            std::shared_ptr<ir_stat::ir_expr> expr(const find_expr_cb &cb, Targs &&...args) {
                  std::shared_ptr<ir_stat::ir_expr> result = nullptr;
                  ((result = expr(std::forward<Targs>(args), cb)) || ...);
                  return result;
            }

      } // namespace find

      namespace violations {

            /* Does block have any branch violations? */
            enum class block_violation_exceptions : std::uint8_t {
                  invalid,
                  invalid_end,
                  invalid_until,
                  invalid_scope_start,
                  invalid_unfinished_conditions,
                  invalid_else_conditional,
                  invalid_goto,
                  invalid_implicit,
                  invalid_page_start,
                  invalid_page_end,
                  invalid_unfinished_page,
                  hit_closing_on
            };
            struct block_violation_results {

                  block_violation_exceptions reason = block_violation_exceptions::invalid; /* Reason of violation */
                  luramas_address ending_loc = 0u;                                         /* Ending violation */
                  bool valid = true;                                                       /* No violations? */

                  template <block_violation_exceptions reason>
                  inline void make_exception(const luramas_address ending_loc) {
                        this->valid = false;
                        this->reason = reason;
                        this->ending_loc = ending_loc;
                        return;
                  }
            };

            /* Checks if block violates in range: [start, end) */
            struct block_violates_flags {
                  luramas_flag finclude_gotos = false;                        /* Include gotos to terminate on */
                  luramas_flag finclude_terminals = false;                    /* Include terminals if in only scope */
                  luramas_flag fbackwards = false;                            /* Direction */
                  std::shared_ptr<ir_stat> close_on = nullptr;                /* Closes on stat eq if stack valid */
                  std::shared_ptr<luramas_addresses> valid_extract = nullptr; /* Extract any nodes with 0 issues */
                  std::optional<find::find_stat_cb> ovalid_cb = std::nullopt; /* If valid scope call this exit if true */
                  luramas_flag finclude_implicit = false;                     /* Include orphaned implicits */
                  luramas_flag finclude_pages = false;                        /* Include orphaned pages */
            };
            block_violation_results block_violates(luramas::ir::passes::pass_manager &pm, const luramas_address start, const luramas_address end, const block_violates_flags &flags = block_violates_flags());

            namespace accumulate {

                  /* Accumulate all violations */
                  std::vector<block_violation_results> violations(luramas::ir::passes::pass_manager &pm, luramas_address start, const luramas_address end, const block_violates_flags &flags = block_violates_flags());

                  /* Accumulates all safe(same scope) violations till start and end meet */
                  std::vector<block_violation_results> violations_safe(luramas::ir::passes::pass_manager &pm, luramas_address start, const luramas_address end);
            } // namespace accumulate

      } // namespace violations

      namespace truncate {

            /* Gets end of block without violations, encapsulate(will inc start if it is an explicit cond) */
            luramas_address block(luramas::ir::passes::pass_manager &pm, const luramas_address start, const luramas_address end, const bool encapsulate = false, const bool include_gotos = false, const bool include_terminals = false, const std::shared_ptr<ir_stat> &close_on = nullptr);

            /* When if condition is going to get removed it checks if it can remove all or just that block */
            struct removable_cond_result {
                  bool valid = true;
                  condition_kind exception_kind = condition_kind::nothing;
                  luramas_address ending = 0u;
                  luramas_address took_jump = 0u;
            };
            removable_cond_result removable_cond(luramas::ir::passes::pass_manager &pm, const luramas_address start);

            /* Gets biggest relative valid block from start */
            luramas_address most_relative_valid_block(luramas::ir::passes::pass_manager &pm, const luramas_address start, const luramas_addresses &ends);

      } // namespace truncate

      namespace common {

            /* Gets safe end of condition block */
            template <bool encapsulate = false>
            inline luramas_address safe_cond_block_end(luramas::ir::passes::pass_manager &pm, const luramas_address start, const std::shared_ptr<ir_stat> &close_on = nullptr) {
                  return tools::truncate::block(pm, start, tools::visitors::explicit_cond_end(pm, pm[start]), encapsulate, false, false, close_on);
            }

            /* Get safe end of block */
            luramas_address safe_block_end(luramas::ir::passes::pass_manager &pm, const luramas_address start, const std::shared_ptr<ir_stat> &close_on = nullptr);
            /* Get safe end of block */
            luramas_address safe_block_end(luramas::ir::passes::pass_manager &pm, const luramas_address start, const luramas_address end, const std::shared_ptr<ir_stat> &close_on = nullptr);
            /* Is the rest of the code safe? */
            bool is_rest_safe_block_end(luramas::ir::passes::pass_manager &pm, const luramas_address start);

            /* Take jump if there is any else 0 */
            luramas_address safe_take_jump(luramas::ir::passes::pass_manager &pm, const luramas_address n);

            /* Reverse jump if there is any else returns n */
            luramas_address reverse_safe_take_jump(luramas::ir::passes::pass_manager &pm, const luramas_address n);

            /* Does start fall to loop end? */
            bool fall_loop_end(luramas::ir::passes::pass_manager &pm, const luramas_address start);

            /* Basic if condition (no else/elseif)? */
            bool basic_if_stat(luramas::ir::passes::pass_manager &pm, const luramas_address loc);

            /* Are ends of basic if condition (no else/elseif)? */
            bool basic_if_end_stat(luramas::ir::passes::pass_manager &pm, const luramas_blockrange &range);

            /* Does stat flow interrupt past or on address? */
            bool interrupt_on_past(luramas::ir::passes::pass_manager &pm, const luramas_address start, const luramas_address loc);

            /* Take else if avaliable (Will return start if cant) */
            luramas_address safe_take_else(luramas::ir::passes::pass_manager &pm, const luramas_address start);

            /* Continues in given loop? */
            bool continues_to_loop(luramas::ir::passes::pass_manager &pm, const std::shared_ptr<ir_stat> &continue_stat, const luramas_address loop);

            /* Breaks out of given loop? */
            bool breaks_to_loop(luramas::ir::passes::pass_manager &pm, const std::shared_ptr<ir_stat> &break_stat, const luramas_address loop);

            /*  Next safe executable stat is loop end*/
            luramas_address traces_to_loop_end(luramas::ir::passes::pass_manager &pm, const luramas_address on);

            /* Get register expr from assignment */
            std::shared_ptr<ir_stat::ir_expr> get_reg_expr_assignment(const std::shared_ptr<ir_stat> &assignment, const luramas_register reg);

            /* Does next instruction expect a definition */
            bool expects_definition(passes::pass_manager &pm, const luramas_address addr);
      } // namespace common

      namespace contains {

            /* Sees if an instructions refs jlabel */
            bool refs(luramas::ir::passes::pass_manager &pm, const luramas_blockrange &range, const luramas_address jlabel);

            /* See if there is any refs in block_1 to block_2 vise versa */
            bool refs(luramas::ir::passes::pass_manager &pm, const luramas_blockrange &block_1, const luramas_blockrange &block_2);

            /* Unconditional blocks */
            bool unconditional_block(luramas::ir::passes::pass_manager &pm, const std::vector<luramas_blockrange> &blocks);
            bool unconditional_block(luramas::ir::passes::pass_manager &pm, const luramas_addresses &blocks_starts);

            namespace orphans {

                  /* Any orphaned implicit gotos? */
                  bool implicit_goto(luramas::ir::passes::pass_manager &pm, const luramas_blockrange &range);

                  /* Any orphaned loop ends? */
                  bool loop_end(luramas::ir::passes::pass_manager &pm, const luramas_blockrange &range);

                  /* Any orphaned pages? */
                  bool pages(luramas::ir::passes::pass_manager &pm, const luramas_blockrange &range);
            } // namespace orphans

            namespace implicit {

                  /* Any breaks to target? */
                  bool break_to(luramas::ir::passes::pass_manager &pm, const luramas_addresses &data, const luramas_address target_loop);

                  /* Any continues to target? */
                  bool continues_to(luramas::ir::passes::pass_manager &pm, const luramas_addresses &data, const luramas_address target_loop);

                  /* Any breaks or continues to target? */
                  bool any_to(luramas::ir::passes::pass_manager &pm, const luramas_addresses &data, const luramas_address target_loop);
            } // namespace implicit

            /* Sees if an if condition has an else. */
            bool if_cond_else(luramas::ir::passes::pass_manager &pm, const luramas_address if_cond_loc);

            /* Range contains address? */
            bool address(const luramas_blockrange &range, const luramas_address n);

            /* Is there a label in scope of start? */
            bool safe_label(luramas::ir::passes::pass_manager &pm, const luramas_address start, const std::shared_ptr<ir_stat> &label);

            template <tkind k>
            bool tk(const ir_stat::ir_expr::space &v) {

                  for (const auto &i : v) {
                        if (i->is_tk<k>()) {
                              return true;
                        }
                  }
                  return false;
            }

            /* Is call back? */
            bool is(const ir_stat::ir_expr::space &v, const data::cb_tkind &cb);
            bool is(const ir_stat::ir_expr::space &v, const data::cb_kinds &cb);
            bool is(const ir_stat::ir_expr::space &v, const data::cb_bkinds &cb);
            bool is(const ir_stat::space &v, const data::cb_keywords &cb);
      } // namespace contains

      namespace types {

            enum class extraction_kind : std::uint8_t {
                  none, /* Nothing */
                  reg,  /* Register */
                  type  /* Type object */
            };
            struct extraction {

                  extraction_kind t = extraction_kind::none;               /* Extraction type */
                  std::shared_ptr<ir::types::object::type> type = nullptr; /* Object? */
                  luramas_register reg = 0u;                               /* Register? */
                  std::shared_ptr<ir_stat::ir_expr> expr = nullptr;        /* Expr? */

                  extraction(const std::shared_ptr<ir_stat::ir_expr> &expr)
                      : expr(expr) {
                  }

                  void emit(const luramas_register reg) {
                        this->t = extraction_kind::reg;
                        this->reg = reg;
                        return;
                  }
                  void emit(const std::shared_ptr<ir::types::object::type> &type) {
                        this->t = extraction_kind::type;
                        this->type = type;
                        return;
                  }
                  bool basic() const {
                        return this->t == extraction_kind::type && this->type && this->type->basic();
                  }
                  bool empty() const {
                        return this->t == extraction_kind::none;
                  }
                  operator bool() const {
                        return !this->empty();
                  }
                  void clear() {
                        *this = extraction(nullptr);
                        return;
                  }
            };
            using extraction_result = std::vector<extraction>;

            /* Extract expr type */
            extraction extract_expr_type(const std::shared_ptr<ir_stat::ir_expr> &expr);

            /* Extract all dominant types in expr */
            extraction_result extract(const std::shared_ptr<ir_stat::ir_expr> &expr);

            /* Extract types */
            std::vector<std::shared_ptr<ir::types::object::type>> extract(const std::shared_ptr<ir_stat> &parent_stat, const std::shared_ptr<ir_stat::ir_expr> &expr, const generation::ssa::ssa &ssa, const boost::unordered_flat_map<luramas_xregister, std::shared_ptr<ir::types::object::type>> &ssa_types);

            /* Gets dominant underlying type with flags */
            luramas::types::underlying_type dominant(luramas::ir::passes::pass_manager &pm, const luramas::types::underlying_type &a, const luramas::types::underlying_type &b);

            /* Dominant type (returns nullptr if none) */
            std::shared_ptr<ir::types::object::type> dominant(const std::shared_ptr<ir::types::object::type> &l, const std::shared_ptr<ir::types::object::type> &r);
            std::shared_ptr<ir::types::object::type> dominant(const std::vector<std::shared_ptr<ir::types::object::type>> &v);

            /* Gets SSA types */
            boost::unordered_flat_map<luramas_xregister, std::shared_ptr<ir::types::object::type>> ssa_types(const generation::ssa::ssa &ssa);

            /* Gets all types a register was casted to in range (Requires all values to be inited) */
            boost::unordered_flat_map<luramas_register, std::vector<std::pair<luramas_address, std::shared_ptr<ir::types::object::type>>>> casted_regs(passes::pass_manager &pm, const luramas_blockrange &r);

            /* Get frequent register type with range */
            boost::unordered_flat_map<luramas_register, std::shared_ptr<ir::types::object::type>> frequent(const luramas_blockrange &r, const boost::unordered_flat_map<luramas_register, std::vector<std::pair<luramas_address, std::shared_ptr<ir::types::object::type>>>> &types);

            using map = boost::unordered_flat_map<std::shared_ptr<ir_stat::ir_expr>, std::vector<std::shared_ptr<ir::types::object::type>>>;

            /* Generate casts map */
            map generate_type_map(luramas::ir::passes::pass_manager &pm, const generation::ssa::ssa &ssa);

            /* Get types from type map */
            std::optional<std::vector<std::shared_ptr<ir::types::object::type>>> get_types(const std::shared_ptr<ir_stat::ir_expr> &expr, const map &m);
      } // namespace types

      namespace extract {

            /* Extracts start of high level blocks given condition (+1 FOR CONTENTS) */
            std::vector<luramas_blockrange /* [Start (after condition), end (End of condition)) */> blocks(luramas::ir::passes::pass_manager &pm, const luramas_address start);

            /* Given any addr in an executable path it will get all the blocks pertaining to it (must be apart of an if condition) */
            std::vector<luramas_blockrange> parent_ifcond_blocks(luramas::ir::passes::pass_manager &pm, const luramas_address loc);

            /* Extracts dominate blocks  (+1 FOR CONTENTS) */
            std::vector<luramas_addresses> dominate_blocks(luramas::ir::passes::pass_manager &pm, const luramas_address start);

            /* Extracts base expr from expr (if not will return nullptr) */
            std::shared_ptr<ir_stat::ir_expr> base_expr(const std::shared_ptr<ir_stat::ir_expr> &expr);

            /* Extracts all conditions for condition */
            luramas_addresses cond_conditions(luramas::ir::passes::pass_manager &pm, const luramas_address start);

            /* Extracts all exprs contains closure values */
            std::vector<std::shared_ptr<ir_stat::ir_expr>> closures(luramas::ir::passes::pass_manager &pm, const bool deep = false);

            /* Extract stats as space */
            ir_stat::space space(passes::pass_manager &pm, const luramas_blockrange &range);

            /* Extract all regs from assignment */
            luramas_registers assignment_regs(const std::shared_ptr<ir_stat> &assignment_stat);

            namespace space_stat {

                  /* Extract all gotos whos labels are unknown from space */
                  ir_stat::space unresolved_gotos(const ir_stat::space &space);

                  /* Extract keyword */
                  ir_stat::space extract(const ir_stat::space &space, const keywords k);

                  /* Extracts all upvalues from space */
                  ir_stat::ir_expr::space upvalues(const ir_stat::space &space);
            } // namespace space_stat

            namespace ir {

                  /* Get all undefined registers */
                  std::set<luramas_register> lazy_undefined_registers(se_ir &ir, const boost::unordered_flat_set<luramas_register> &upvalues = boost::unordered_flat_set<luramas_register>());
            } // namespace ir

            namespace stats {

                  /* Gets all dominant expr kinds of registers */
                  boost::unordered_flat_map<luramas_register, boost::unordered_flat_set<expr_kinds>> all_reg_doms(const std::shared_ptr<ir_stat> &curr);
            } // namespace stats

            namespace exprs {

                  /* Extracts path from start to target */
                  std::vector<std::shared_ptr<ir_stat::ir_expr>> path(const std::shared_ptr<ir_stat::ir_expr> &start, const std::shared_ptr<ir_stat::ir_expr> &target);
            } // namespace exprs

      } // namespace extract

      namespace ssa {

            /* Register is defined in scope with ssa? */
            bool defined_scope(luramas::ir::passes::pass_manager &pm, generation::ssa::ssa &ssa, const luramas_address start, const luramas_register target, const bool skip_current_scope = true);
            bool defined_scope(luramas::ir::passes::pass_manager &pm, generation::ssa::ssa &ssa, const luramas_address start, const std::shared_ptr<ir_stat::ir_expr> &target, const bool skip_current_scope = true);

            /* Register used in range? */
            bool used(luramas::ir::passes::pass_manager &pm, generation::ssa::ssa &ssa, const luramas_address start, const luramas_address end, const luramas_register target);
            bool used(luramas::ir::passes::pass_manager &pm, generation::ssa::ssa &ssa, const luramas_blockrange &range, const luramas_register target);

            namespace extract {

                  /* Extracts same assignment most recent assignment */
                  boost::unordered_flat_map<luramas_register, std::vector<luramas_blockrange /* Addr, Block end */>> same_assignments(luramas::ir::passes::pass_manager &pm, generation::ssa::ssa &ssa, const std::vector<luramas_addresses> &blocks, const bool same_rvalues = false, const bool dominant = false);

                  /* Extract blocks target assignment */
                  enum class hit_type : std::uint8_t {
                        all,
                        first,
                        dominant
                  };
                  std::vector<std::pair<luramas_address, luramas_blockrange>> block_assignment(luramas::ir::passes::pass_manager &pm, generation::ssa::ssa &ssa, const std::vector<luramas_blockrange> &blocks, const luramas_register target, const hit_type type = hit_type::all);
                  std::vector<std::pair<luramas_address, luramas_blockrange>> block_assignment(luramas::ir::passes::pass_manager &pm, generation::ssa::ssa &ssa, const std::vector<luramas_blockrange> &blocks, const boost::unordered_flat_set<luramas_register> &targets, const hit_type type = hit_type::all);

                  /* Extracts all SSA registers but if any of them is in a phi it will only count the one with highest high level scope ID an ignore the rest of the rest in the phi */
                  luramas_xregisters all_dominant_singletons(generation::ssa::ssa &ssa);

                  /* Extracts dominant assign before start, if there is a phi it will return nullptr within scope */
                  std::optional<luramas_address> dominant_define(luramas::ir::passes::pass_manager &pm, generation::ssa::ssa &ssa, const luramas_address start, const luramas_register target);

                  /* Extracts next assignment of target within scope but scope < n */
                  std::optional<luramas_address> next_assignment_inscope_assignment(luramas::ir::passes::pass_manager &pm, generation::ssa::ssa &ssa, const luramas_address start, const luramas_register target);

                  /* Extracts next assignment in the same scope (if next assignment is out of scope returns nothing) */
                  std::optional<luramas_address> next_assignment_same_scope_assignment(luramas::ir::passes::pass_manager &pm, generation::ssa::ssa &ssa, const luramas_address start, const luramas_register target);

                  /* Extracts linked register to SSA register (Not native to SSA struct because it is rarely needed) */
                  std::optional<luramas_register> linked(const generation::ssa::ssa &ssa, const luramas_xregister ssa_reg);

                  /* Extracts parent page of SSA register */
                  boost::unordered_flat_map<luramas_xregister, std::optional<luramas_address>> parent_page(luramas::ir::passes::pass_manager &pm, const generation::ssa::ssa &ssa);

                  /* Gets all exprs pts of ssa_reg */
                  ir_stat::ir_expr::space exprs(luramas::ir::passes::pass_manager &pm, const generation::ssa::ssa &ssa, const luramas_xregister ssa_reg);
            } // namespace extract

            /* Get any definition type a expr may have (returns nullptr if none) */
            std::shared_ptr<luramas::ir::types::object::type> get_type(const std::shared_ptr<ir_stat::ir_expr> &expr, generation::ssa::ssa &ssa, const luramas_xregister ssa_reg = 0u);

            /* See if all lvalues been defined before */
            luramas_registers all_undefined(luramas::ir::passes::pass_manager &pm, generation::ssa::ssa &ssa, const luramas_address start, const boost::unordered_flat_set<luramas_register> &args);

            /* See if all rvalues has been referenced out of page (Returns where the ssa regs get referenced at and the address there ssa reg assignment parent page is in) */
            std::vector<std::optional<boost::unordered_flat_map<luramas_xregister, std::optional<luramas_address>>>> referenced_out_of_page(luramas::ir::passes::pass_manager &pm, const generation::ssa::ssa &ssa, const std::vector<std::optional<luramas_address>> &pages);

            /* Given target generate see what has been used before as the assignment of the target ssa register with limit. */
            struct use_def_result {
                  generation::ssa::assignment_kind k = generation::ssa::assignment_kind::single;
                  luramas_xregister scalar = 0u;
                  std::optional<luramas_xregisters> phis;
            };
            std::vector<use_def_result> use_def_chain(const generation::ssa::ssa &ssa, const luramas_xregister target, const luramas_address limit = 0u);

            /* A placeholder value assigned before all control-flow branches overwrite it, so it never affects execution */
            bool is_placeholder_variable(luramas::ir::passes::pass_manager &pm, generation::ssa::ssa &ssa, const luramas_xregister target, const luramas_address start);

            /* Same high level scope ID of two addrs? */
            inline bool same_highlevel_scope_id(luramas::ir::passes::pass_manager &pm, generation::ssa::ssa &ssa, const luramas_address l, const luramas_address r) {
                  return pm.contains(l) && pm.contains(r) && ssa.high_level_scope_id[l] == ssa.high_level_scope_id[r];
            }
      } // namespace ssa

      namespace count {

            /* Is callbacks */
            luramas_count is(const ir_stat::ir_expr::space &v, const data::cb_tkind &cb);
            luramas_count is(const ir_stat::ir_expr::space &v, const data::cb_kinds &cb);
            luramas_count is(const ir_stat::space &v, const data::cb_keywords &cb);

            /* Amount of instructions in range */
            luramas_count insts(const luramas_blockrange &b);

            /* Counts parameters in defintion */
            luramas_count definition_parameters(const std::shared_ptr<ir_stat> &definition);

            /* Count references to label loc */
            luramas_count refs(luramas::ir::passes::pass_manager &pm, const luramas_address label_loc);

            template <tkind k>
            inline luramas_count tk(const ir_stat::ir_expr::space &v) {

                  luramas_count n = 0u;
                  for (const auto &i : v) {
                        n += i->template is_tk<k>();
                  }
                  return n;
            }

            template <keywords k>
            inline luramas_count keyword(const ir_stat::ir_expr::space &v) {

                  luramas_count n = 0u;
                  for (const auto &i : v) {
                        n += i->template is_k<k>();
                  }
                  return n;
            }
      } // namespace count

      namespace mutations {

            /* Pop condition (if/elseif/else) */
            bool pop_cond(luramas::ir::passes::pass_manager &pm, const luramas_address cond, const bool truthy = true /* Is cond truthy? */);

            /* Set safe on stat and if its unsafe it will duplicate it */
            std::shared_ptr<ir_stat> safe_if_dupe(passes::pass_manager &pm, const std::shared_ptr<ir_stat> &stat);

            /* Are regs in range modifed? */
            bool modified_regs(luramas::ir::passes::pass_manager &pm, const luramas_blockrange &range, const boost::unordered_flat_set<luramas_register> &regs);
      } // namespace mutations

      namespace implicit {

            /* Will continously break out of nested loops until its possible to hit target (Target can not be a non executable stat) */
            luramas_addresses continous_break(luramas::ir::passes::pass_manager &pm, const luramas_address start, const luramas_address target);

      } // namespace implicit

      namespace simulate {

            /* 
                Will leverage basic loops:
                    while (true) do
                        ...
                        break;
                    end
                to reach a target if possible
            */
            struct loop_threading_results {

                  bool inserted = false;
                  luramas_address inserted_loc = 0u;
                  luramas_address exiting_loc = 0u;

                  keywords k = keywords::nothing;
                  luramas_address current_loc = 0u;
                  luramas_address implicitly_goto = 0u;
            };
            std::vector<loop_threading_results> loop_threading(luramas::ir::passes::pass_manager &pm, const luramas_address start, const luramas_address target);

            /* Only simulates blocks given inputs, does not include stack or memory. (only tracks registers) */
            enum class basic_block_exit_reason : std::uint8_t {
                  none,
                  hit_limit,
                  out_of_range
            };
            struct basic_block_results {

                  basic_block_exit_reason reason = basic_block_exit_reason::none;
                  luramas_address exit_loc = 0u;
                  boost::unordered_flat_map<luramas_address, std::size_t> hit_count;
                  std::optional<luramas_addresses> order_of_operations;

                  template <basic_block_exit_reason reason>
                  void make_exception(const luramas_address exit) {
                        this->reason = reason;
                        this->exit_loc = exit;
                        return;
                  }
            };
            basic_block_results basic_block(luramas::ir::passes::pass_manager &pm, const boost::unordered_flat_map<luramas_register, std::shared_ptr<ir_stat::ir_expr>> &input, const luramas_blockrange &range, const std::uint32_t limit = 1u, const bool undefine_zero = false, const bool include_order_of_operations = false);
      } // namespace simulate

      namespace rebaser {

            /* Rebase labels and jlabels (base + jlabel/label + 1) */
            void labels(luramas_address base, ir_stat::space &buffer);
      } // namespace rebaser

      namespace transform {

            /* Range [start, end) to addresses (Transformations may not be 100% accurate if fragmented) */
            luramas_addresses range_to_addresses(const luramas_blockrange &range);

            /* Range [start, end) to space (Transformations may not be 100% accurate if fragmented) */
            ir_stat::space range_to_space(luramas::ir::passes::pass_manager &pm, const luramas_blockrange &range);

            /* Addresses to range [start, end), (Transformations may not be 100% accurate if fragmented) */
            luramas_blockrange addresses_to_range(const luramas_addresses &addresses);

            /* Generates range [start, end) with start and inclusive end */
            luramas_blockrange address_to_range(const luramas_address start, const luramas_address inclusive_end);

            namespace isolate {

                  /* Isolate any new labels */
                  void labels(luramas::ir::passes::pass_manager &pm, const luramas_blockrange &range);
            } // namespace isolate
      } // namespace transform

      namespace compute {

            /* Result of compare */
            enum class comparable : std::uint8_t {
                  false_, /* False */
                  true_,  /* True */
                  none_   /* No result */
            };

            namespace strings {

                  /*  */
                  bool flatten_concat(std::shared_ptr<ir_stat::ir_expr> &expr);
            } // namespace strings

            template <typename lk, typename rk>
            bool compare_eq(const lk &l, const rk &r, const luramas::il::arch::data::bin_kinds b) {
                  switch (b) {
                        case luramas::il::arch::data::bin_kinds::ne_: {
                              return l != r;
                        }
                        case luramas::il::arch::data::bin_kinds::et_: {
                              return l == r;
                        }
                        default: {
                              return false;
                        }
                  }
            }

            template <typename lk>
            bool compute(const lk &l, const luramas::il::arch::data::bin_kinds b, const bool primitive_object = false) {
                  switch (b) {
                        case luramas::il::arch::data::bin_kinds::nt_: {
                              if (primitive_object) {
                                    if constexpr (!std::is_same_v<std::remove_cv_t<lk>, bool>) {
                                          return false;
                                    }
                              }
                              return static_cast<bool>(!l);
                        }
                        case luramas::il::arch::data::bin_kinds::et_: {
                              if (primitive_object) {
                                    if constexpr (!std::is_same_v<std::remove_cv_t<lk>, bool>) {
                                          return true;
                                    }
                              }
                              return static_cast<bool>(l);
                        }
                        default: {
                              return false;
                        }
                  }
            }

            template <typename lk, typename rk, typename ret>
            ret compute(const lk &l, const rk &r, const luramas::il::arch::data::bin_kinds b) {
                  switch (b) {
                        case luramas::il::arch::data::bin_kinds::add_: {
                              return static_cast<ret>(l + r);
                        }
                        case luramas::il::arch::data::bin_kinds::sub_: {
                              return static_cast<ret>(l - r);
                        }
                        case luramas::il::arch::data::bin_kinds::mul_: {
                              return static_cast<ret>(l * r);
                        }
                        case luramas::il::arch::data::bin_kinds::div_: {
                              return (!l || !r) ? static_cast<ret>(0) : static_cast<ret>(l / r);
                        }
                        case luramas::il::arch::data::bin_kinds::idiv_: {
                              return (!l || !r) ? static_cast<ret>(0)
                                     : (std::is_same<lk, luramas_int>::value || std::is_same<rk, luramas_int>::value)
                                         ? static_cast<ret>(math::floor(l / r))
                                         : static_cast<ret>(std::floor(static_cast<double>(l) / static_cast<double>(r)));
                        }

                        case luramas::il::arch::data::bin_kinds::mod_: {
                              if constexpr (luramas::tools::native_supported_arith<lk>() && luramas::tools::native_supported_arith<rk>()) {
                                    return static_cast<ret>(l % r);
                              }
                              return static_cast<ret>(std::fmod(static_cast<const double>(l), static_cast<const double>(r)));
                        }
                        case luramas::il::arch::data::bin_kinds::pow_: {
                              if constexpr (luramas::tools::native_supported_arith<lk>() && luramas::tools::native_supported_arith<rk>() && luramas::tools::native_supported_arith<ret>()) {
                                    return static_cast<ret>(math::pow(l, r));
                              }
                              luramas::error::error("Pow operation requires arith kinds");
                        }
                        case luramas::il::arch::data::bin_kinds::and_: {
                              if constexpr (luramas::tools::native_supported_arith<lk>() && luramas::tools::native_supported_arith<rk>()) {
                                    return static_cast<ret>(l & r);
                              } else if constexpr (std::is_floating_point_v<lk> && std::is_floating_point_v<rk>) {
                                    return static_cast<ret>(l * r);
                              }
                              break;
                        }

                        case luramas::il::arch::data::bin_kinds::xor_: {
                              if constexpr (std::is_same_v<lk, bool> && std::is_same_v<rk, bool>) {
                                    return static_cast<ret>(l != r);
                              } else if constexpr (luramas::tools::native_supported_arith<lk>() && luramas::tools::native_supported_arith<rk>()) {
                                    return static_cast<ret>(l ^ r);
                              } else if constexpr (std::is_floating_point_v<lk> && std::is_floating_point_v<rk>) {
                                    return static_cast<ret>(static_cast<const std::int32_t>(l) ^ static_cast<const std::int32_t>(r));
                              }
                              break;
                        }
                        case luramas::il::arch::data::bin_kinds::shl_: {
                              if constexpr (luramas::tools::native_supported_arith<lk>() && luramas::tools::native_supported_arith<rk>()) {
                                    if constexpr (std::is_same_v<ret, bool>) {
                                          return static_cast<ret>((l << r) != 0);
                                    } else {
                                          return static_cast<ret>(l << r);
                                    }
                              }
                              luramas::error::error("Shift left operation requires arith kinds");
                        }
                        case luramas::il::arch::data::bin_kinds::shr_: {
                              if constexpr (luramas::tools::native_supported_arith<lk>() && luramas::tools::native_supported_arith<rk>()) {
                                    if constexpr (std::is_same_v<ret, bool>) {
                                          return static_cast<ret>((l >> r) != 0);
                                    }
                                    return static_cast<ret>(l >> r);
                              }
                              luramas::error::error("Shift right operation requires arith kinds");
                        }
                        case luramas::il::arch::data::bin_kinds::or_: {
                              if constexpr (luramas::tools::native_supported_arith<lk>() && luramas::tools::native_supported_arith<rk>()) {
                                    return static_cast<ret>(l | r);
                              } else if constexpr (std::is_floating_point_v<lk> && std::is_floating_point_v<rk>) {
                                    return static_cast<ret>(static_cast<const std::int32_t>(l) | static_cast<const std::int32_t>(r));
                              }
                              break;
                        }
                        case luramas::il::arch::data::bin_kinds::eq_: {
                              return static_cast<ret>(l == r);
                        }
                        case luramas::il::arch::data::bin_kinds::ne_: {
                              return static_cast<ret>(l != r);
                        }
                        case luramas::il::arch::data::bin_kinds::lt_: {
                              return static_cast<ret>(l < r);
                        }
                        case luramas::il::arch::data::bin_kinds::lte_: {
                              return static_cast<ret>(l <= r);
                        }
                        case luramas::il::arch::data::bin_kinds::gt_: {
                              return static_cast<ret>(l > r);
                        }
                        case luramas::il::arch::data::bin_kinds::gte_: {
                              return static_cast<ret>(l >= r);
                        }
                        case luramas::il::arch::data::bin_kinds::nt_: {
                              return static_cast<ret>(!l);
                        }
                        case luramas::il::arch::data::bin_kinds::et_: {
                              return static_cast<ret>(l);
                        }
                        default: {
                              luramas::error::error("Invalid binop");
                        }
                  }
                  if constexpr (std::is_same_v<ret, bool>) {
                        return false;
                  }
                  luramas::error::error("Invalid binop");
            }

            /* Compute logical expression (Will return nullptr if can not) */
            std::shared_ptr<ir_stat::ir_expr> compute(const std::shared_ptr<ir_stat::ir_expr> &l, const std::shared_ptr<ir_stat::ir_expr> &r, expr_logical b, const bool primitive_object = false);

            comparable compare(const std::shared_ptr<ir_stat::ir_expr> &l, const std::shared_ptr<ir_stat::ir_expr> &r, luramas::il::arch::data::bin_kinds b, const bool primitive_object = false);

            namespace exprs {

                  namespace representations {

                        /* Compute boolean identity to simplify it (returns nullptr if not possible) */
                        std::shared_ptr<ir_stat::ir_expr> boolean_identity(std::shared_ptr<ir_stat::ir_expr> &l, const il::arch::data::bin_kinds b, const std::shared_ptr<ir_stat::ir_expr> &r);

                        /* Compute boolean integral i.e. (? CMP ?) ==/!= (0/1) */
                        std::shared_ptr<ir_stat::ir_expr> boolean_integral(std::shared_ptr<ir_stat::ir_expr> &l, const il::arch::data::bin_kinds b, const std::shared_ptr<ir_stat::ir_expr> &r);
                  } // namespace representations

                  /* Simplify expr with e being the buffer */
                  bool simplify(passes::pass_manager &pm, std::shared_ptr<ir_stat::ir_expr> &e, const bool singleton = false, const bool mutate_pm = true, const std::optional<generation::ssa::ssa> &ssa = std::nullopt, const std::optional<types::map> &tmap = std::nullopt);

                  /* Simplify condition */
                  std::shared_ptr<ir_stat::ir_expr> simplify_condition(passes::pass_manager &pm, std::shared_ptr<ir_stat::ir_expr> &l, const luramas::il::arch::data::bin_kinds b, const expr_logical e, const std::shared_ptr<ir_stat::ir_expr> &r, const bool mutate_pm = true, const std::optional<types::map> &tmap = std::nullopt);

                  /* Reorders expression to promote better optimization (does not add or remove any sub expressions) */
                  bool reorder(passes::pass_manager &pm, std::shared_ptr<ir_stat::ir_expr> &expr);
            } // namespace exprs

            namespace stats {

                  /* Simplify stat */
                  bool simplify(passes::pass_manager &pm, const luramas_address addr, std::shared_ptr<ir_stat> &p, const bool mutate_pm = true, const std::optional<types::map> &tmap = std::nullopt);
            } // namespace stats

            /* Compute constant expression with reg -> constant map  (nullptr if not constant) */
            std::shared_ptr<ir_stat::ir_expr> constant_evaluation(passes::pass_manager &pm, const std::shared_ptr<ir_stat::ir_expr> &expr, const boost::unordered_flat_map<luramas_register, std::shared_ptr<ir_stat::ir_expr>> &precomputed);
      } // namespace compute

      namespace control_flow {

            namespace block {

                  /* Does block just jump? */
                  bool is_jump(const std::shared_ptr<generation::cfg::block> &b);
            } // namespace block

            /* Does anywhere in the condition falls out? */
            std::vector<std::pair<generation::cfg::block_kind /* Comming edge kind */, luramas_address /* Exit Loc */>> exits(luramas::ir::passes::pass_manager &pm, const generation::cfg::cfg &cfg, const luramas_address start, const luramas_address target);

            /* Dereferences nodes in block range if they occur in range */
            void fence_region(generation::cfg::cfg &cfg, const luramas_blockrange &range, const bool include_end = false);

            /* Get all target blocks that went out of range within range {jump kind, target block} */
            std::vector<std::pair<generation::cfg::block_kind, std::shared_ptr<generation::cfg::block>>> jumps_out_range(const generation::cfg::cfg &cfg, const luramas_blockrange &range, const luramas_flag finclude_end = false);

            /* Gets all jumps within range but also the target blocks that jumped out {jump kind, target block} */
            std::vector<std::pair<generation::cfg::block_kind, std::shared_ptr<generation::cfg::block>>> accumulate_ranged_jumps_outs(const generation::cfg::cfg &cfg, const luramas_blockrange &range);

            /* Based on current instrcuction will the next instruction be executed? */
            bool next_instruction_executed(luramas::ir::passes::pass_manager &pm, const luramas_address start);
      } // namespace control_flow

      namespace memory {

      }

      namespace guarantee {

            namespace exprs {

                  /* Generate cast if it does not cast to type */
                  std::shared_ptr<ir_stat::ir_expr> cast(const std::shared_ptr<ir_stat::ir_expr> &expr, const luramas::types::underlying_type &t, const bool bits = false /* Only care about size? */);
            } // namespace exprs

            namespace stats {

                  /* Generate label is there is not any */
                  std::shared_ptr<ir_stat> label(passes::pass_manager &pm, const luramas_address loc);

                  /* Generate definition is there is not any */
                  std::shared_ptr<ir_stat> definition(passes::pass_manager &pm, const luramas_address loc, const luramas_address where);
                  std::shared_ptr<ir_stat> definition(passes::pass_manager &pm, const luramas_address loc, const luramas_address where, const luramas_register reg, const std::shared_ptr<ir_stat::ir_expr> &def_expr = nullptr);
            } // namespace stats
      } // namespace guarantee

      namespace paging {

            /* Anything with page expr if is nullptr its main closure */
            struct details {

                  struct page {

                        luramas_flag fpromoted = false;       /* Did page get promoted to a closure? */
                        luramas_flag fcall_exclusive = false; /* Does the page need to be jumped to or called to use? */
                        luramas_flag fhas_start = false;      /* Does page have a start stat? */
                        luramas_flag fvalid = false;          /* Is page valid ie spotted start - end stats? */

                        luramas_id id = 0u;                                                                              /* ID of page */
                        std::optional<luramas_id> parent_id = std::nullopt;                                              /* ID of parent page */
                        std::shared_ptr<ir_stat::ir_expr> index = nullptr;                                               /* Expr key page is in */
                        luramas_blockrange range;                                                                        /* Range (Contains start and page end) */
                        std::vector<luramas_id> encapsulating_pages;                                                     /* Pages inside current page (Does not nest) */
                        boost::unordered_flat_map<std::shared_ptr<ir_stat::ir_expr>, std::vector<addr_expr>> references; /* References to the page */
                        std::shared_ptr<ir_stat> definition = nullptr;                                                   /* Page definition */

                        /* Should and can the page be recovered? */
                        inline bool is_recoverable() const {
                              return !this->references.empty() && this->fhas_start;
                        }

                        /* Real inst range (Not including start and end headers) */
                        inline luramas_blockrange code_range(const ir_stat::space &p) const {
                              if (this->fvalid) {
                                    auto result = this->range;
                                    result.first += tools::stat::is_definition(p[++result.first]);
                                    --result.second;
                                    return result;
                              }
                              return this->range;
                        }
                  };
                  boost::unordered_flat_map<std::shared_ptr<ir_stat::ir_expr>, boost::unordered_flat_map<luramas_id, page>> pages; /* Nested pages by closure (0u will always be current closure, decending order from 0u) */

                  /* Get page from loc and current parent closure expr */
                  std::optional<luramas_id> get_page(const luramas_address &loc, const std::shared_ptr<ir_stat::ir_expr> &parent_closure_expr = nullptr) const;

                  /* See if all addresses are apart of the same page */
                  std::optional<luramas_id> same_page(const luramas_addresses &loc, const std::shared_ptr<ir_stat::ir_expr> &parent_closure_expr = nullptr) const;

                  /* Index a pagye from ID */
                  std::optional<std::pair<std::shared_ptr<ir_stat::ir_expr>, details::page>> index_page(const luramas_id id) const;
            };

            /* Generated page details, should be called with main closure to encapsulate all details. */
            details gen_details(passes::pass_manager &pm, const bool deep = false);

            enum class promotion_kind : std::uint8_t {
                  none,          /* No information to gather about the page (Page may be deleted) */
                  page_label,    /* Convert page to Label */
                  page_closure,  /* Convert page to Closure */
                  closure_label, /* Convert closure page to label */
                  immutable      /* Nothing wrong*/
            };
            /* Suggests promotion that should happen, should be called with main closure to encapsulate all details. */
            promotion_kind suggest_promotion(passes::pass_manager &pm, const details::page &target);

            /* Get pending page end (returns 0 if page is valid or not a page) */
            std::optional<luramas_address> get_pending_page_end_loc(passes::pass_manager &pm, const generation::cfg::cfg &cfg, const details::page &page);

            /* Gets parent page address */
            std::optional<luramas_address> parent_page(passes::pass_manager &pm, const luramas_address curr);

            /* Gets parent page address for every address */
            std::vector<std::optional<luramas_address>> parent_pages(passes::pass_manager &pm);

            /* Gets all the pages that a page is encapsulating */
            boost::unordered_flat_map<luramas_id, std::vector<std::pair<std::shared_ptr<ir_stat::ir_expr>, luramas_id>>> encapsulating_pages(passes::pass_manager &pm, const details &pages, const std::vector<std::optional<luramas_address>> &parent_pages);

            /* Gets all parents that are encapsulating a page */
            boost::unordered_flat_map<luramas_id, std::vector<std::pair<std::shared_ptr<ir_stat::ir_expr>, luramas_id>>> parents_encapsulating_pages(const boost::unordered_flat_map<luramas_id, std::vector<std::pair<std::shared_ptr<ir_stat::ir_expr>, luramas_id>>> &encapsulating_pages);

            /* Gets all pages that ID has jumped to (Excludes all parents, does not include all other successors) */
            boost::unordered_flat_map<luramas_id, std::vector<std::pair<std::shared_ptr<ir_stat::ir_expr>, luramas_id>>> successor_pages(passes::pass_manager &pm, const details &pages, const generation::cfg::cfg &cfg, const std::vector<std::optional<luramas_address>> &parent_pages, const boost::unordered_flat_map<luramas_id, std::vector<std::pair<std::shared_ptr<ir_stat::ir_expr>, luramas_id>>> &encapsulated_parents);

            /* Map valid page definitions to their page ID */
            boost::unordered_flat_map<luramas_id, std::shared_ptr<ir_stat>> map_definitions(const details &det);

            struct page_falls_result {
                  luramas_flag ffalls_into = false;  /* Falls into page? */
                  luramas_ids dependant_pages_into;  /* Pages that it depends on above it for it to not fall into */
                  luramas_flag ffalls_out = false;   /* Falls out of page? */
                  luramas_ids dependant_pages_out;   /* Pages that it depend on to not fall out */
                  luramas_flag findependant = false; /* Does not fall out or in */
            };
            /* Analyze page falls i.e does it go out or in? */
            page_falls_result analyze_page_falls(passes::pass_manager &pm, const details::page &target);

            /* Get safe page end thats in scope */
            std::optional<luramas_address> page_safe_end(luramas::ir::passes::pass_manager &pm, const details::page &page);

            /* Move organized pages */
            void move_organized_pages(luramas::ir::passes::pass_manager &pm, const std::vector<tools::paging::details::page> &organized_pages);

            /* Given location and target page would it be recursive (ONLY INCLUDES SELF REFERENCE)? */
            bool is_recursive(const details &det, const luramas_id tid, const luramas_address loc, const std::vector<std::optional<luramas_address>> &parent_pages);

            /* Is page referenced in page? */
            bool referenced_in_page(const details::page &page);

            struct return_data {
                  luramas_count garunteed = 0u; /* Count of garunteed returns */
                  luramas_count maximum = 0u;   /* Max returns of members */
            };
            /* Get return data */
            return_data gen_return_data(luramas::ir::passes::pass_manager &pm, const details::page &page, const std::vector<std::optional<luramas_address>> &parent_pages);

            /* 
                Page must meet this criteria to be procedural:
                    * Can only be entered by calling or jumping to it
                    * Can not fall in or out of it
                    * Can not jump out of it
                    * Can not call or jump to other pages (UNLESS VIRTUALIZED)
                    * Page is also safe unless flagged otherwise 
                    * Has no child pages
            */
            luramas_flag is_procedural(luramas::ir::passes::pass_manager &pm, const details::page &page, const std::vector<std::optional<luramas_address>> &parent_pages, const luramas_flag fcheck_safety = false);
      } // namespace paging

      namespace combine {

            /* Sees if you can safely arbitrarly combine binkinds */
            bool can(const il::arch::data::bin_kinds l, const il::arch::data::bin_kinds r);

            /* Combines unary expr (SOLVES BASIC UNARIES, MUTATES SUB EXPRS IF DOES NOT RETURNS NULLPTR) */
            std::shared_ptr<ir_stat::ir_expr> unary(passes::pass_manager &pm, const std::shared_ptr<ir_stat::ir_expr> &expr);

            /* Combine arith expr (DOES NOT SOLVE ARITH, WILL IGNORE BOTH INTEGRALS,  MUTATES SUB EXPRS ELSE RETURNS NULLPTR) */
            std::shared_ptr<ir_stat::ir_expr> arith(passes::pass_manager &pm, const std::shared_ptr<ir_stat::ir_expr> &expr, const std::optional<types::map> &tmap = std::nullopt);

            /* Combine condition expr (DOES NOT SOLVE CONDITION, MUTATES SUB EXPRS IF DOES NOT RETURNS NULLPTR) */
            std::shared_ptr<ir_stat::ir_expr> cond(passes::pass_manager &pm, std::shared_ptr<ir_stat::ir_expr> &expr);
      } // namespace combine

      namespace safety {

            namespace arith {

                  /* Is arith safe */
                  bool is_safe(luramas::ir::passes::pass_manager &pm, const std::shared_ptr<ir_stat::ir_expr> &expr);
            } // namespace arith

            /* See if combining 2 integrals is safe? */
            bool combine_integrals(const std::shared_ptr<ir_stat::ir_expr> &a, const std::shared_ptr<ir_stat::ir_expr> &b, luramas_int &buffer, const il::arch::data::bin_kinds arith_k, const bool allow_overflow = false);
      } // namespace safety

      namespace closure {

            namespace space_stat {

                  namespace definition {

                        /* Emit args to buffer */
                        void emit_args(const std::shared_ptr<ir_stat> &buffer, const ir_stat::space &space, const boost::unordered_flat_set<luramas_register> &upvals);

                        /* Generates definition stat given space and upvalues */
                        std::shared_ptr<ir_stat> generate(const ir_stat::space &space, const ir_stat::ir_expr::space &upvalues);

                        /* Update definition */
                        void update(const ir_stat::space &space);

                        /* Add definition to space */
                        void add(ir_stat::space &space, const std::shared_ptr<ir_stat> &definition);
                  } // namespace definition
            } // namespace space_stat

            /* Generate closure based on range */
            struct generation_result {
                  ir_stat::space unresolved_labels;                 /* Unresolved labels that will need to be resolved into a page */
                  std::shared_ptr<ir_stat::ir_expr> expr = nullptr; /* Completed expr */
            };
            generation_result generate(passes::pass_manager &pm, const luramas_blockrange &range);
      } // namespace closure

      namespace match {

            /* Matches value with match with respects of wild cards and return if compare is coreect and wild cards values */
            std::pair<bool, boost::unordered_flat_map<std::string, std::shared_ptr<ir_stat::ir_expr>>> wild_cards(const std::shared_ptr<ir_stat::ir_expr> &value, const std::shared_ptr<ir_stat::ir_expr> &match);
      } // namespace match

      namespace replace {

            /* Replace all wild cards in value */
            void wild_cards(std::shared_ptr<ir_stat::ir_expr> &value, const boost::unordered_flat_map<std::string, std::shared_ptr<ir_stat::ir_expr>> &exprs);

            /* 
                Ses if value matches with match if so it will extract wild card everything in it and replace them in dest, no match returns nullptr 
                To use specific wild cards like these flag it(fglobal_wild for exprs) as a wild card then use 
                (ANYTHING WITH UNIQUE STRING INTERPRETATION TO TELL THEM APART) globals suggested.
                The occurance is mapped as example if you have as for a key 
                * (X + X) + Y
                To use them in the result you must use the same variables.
                All input exprs are constant so you do not need to clone dest ahead of time.
            */
            std::shared_ptr<ir_stat::ir_expr> match_wild_cards(const std::shared_ptr<ir_stat::ir_expr> &value, const std::shared_ptr<ir_stat::ir_expr> &match, const std::shared_ptr<ir_stat::ir_expr> &dest);
      } // namespace replace

      namespace entry {

            /* 
                Finds all entry points in IR and splits then into IR with entry point as start thought omitted following rest of the code.
                It will also move any code above the entry point below the rest of the code. If you want to insure safety append a terminal at the end before calling.
                Will return nullopt if there are no entry points or just one at the start (which will be removed).
            */
            std::optional<std::vector<se_ir>> unsafe_split(se_ir &ir);
      } // namespace entry

      namespace inliner {

            namespace cva {

                  /* Can function be inlined? */
                  bool can_inline(const ir_stat::space &data, const ir_stat::ir_expr::space &args);

                  /* Can page be inlined */
                  bool can_inline(luramas::ir::passes::pass_manager &pm, const std::vector<std::optional<luramas_address>> &parent_pages, const tools::paging::details::page &page, const luramas_count max_references = 1u);
            } // namespace cva

            /* 
                Inlines based on what stat is:
                    Definition - Inlines it and links with casts
                    Page_function_call - Links args from call with definition in page target if everything exists
            */
            ir_stat::space inline_dynamic(luramas::ir::passes::pass_manager &pm, const std::shared_ptr<ir_stat> &tstat, const std::optional<luramas_address> &loc_target = std::nullopt);
            ir_stat::space inline_dynamic(luramas::ir::passes::pass_manager &pm, const std::shared_ptr<ir_stat::ir_expr> &texpr, const std::optional<luramas_address> &loc_target = std::nullopt);

            /*           
                Inline data  (Must be pre ignored for recursion)     
                High level variadics can not be safely inlined and therefore will return empty
            */
            ir_stat::space inline_data(luramas::ir::passes::pass_manager &pm, const ir_stat::space &data, const ir_stat::ir_expr::space &calle_assigns, const ir_stat::ir_expr::space args, const bool register_calle_assigns = true);

            /* Inline page reference */
            struct inline_page_flags {
                  luramas_flag fclone = true;
            };
            struct inlined_page_results {
                  ir_stat::space data;
                  boost::unordered_flat_map<luramas_register, std::shared_ptr<ir_stat::ir_expr>> results;
            };
            inlined_page_results page(luramas::ir::passes::pass_manager &pm, const addr_expr &ref, const paging::details &page_details, const paging::details::page &page, const inline_page_flags &flags = inline_page_flags());
      } // namespace inliner

      namespace eliminate {

            /* Deletes page and inlines it */
            void page(luramas::ir::passes::pass_manager &pm, const paging::details &page_details, const paging::details::page &p);
      } // namespace eliminate

      namespace errors {

            /* See if idx is in range of n (>=) */
            void in_range(const luramas_index idx, const luramas_count n);
      } // namespace errors

      namespace loops {

            /* Does loop or end of a loop is infinite */
            bool infitely(luramas::ir::passes::pass_manager &pm, luramas_address start);
      } // namespace loops

      namespace linked {

            namespace parameters {

                  /* Adjust params based off referenced outs */
                  void adjust_referenced_out(luramas::ir::passes::pass_manager &pm, const generation::ssa::ssa &ssa, const std::vector<std::optional<luramas_address>> &parent_pages);

                  /* Adjust params based off successor params */
                  void adjust_by_successors(luramas::ir::passes::pass_manager &pm, const generation::cfg::cfg &cfg, const tools::paging::details &page_details, const std::vector<std::optional<luramas_address>> &parent_pages);

                  /* Perform all params adjustments */
                  void pre_adjust(luramas::ir::passes::pass_manager &pm, const generation::cfg::cfg &cfg, const generation::ssa::ssa &ssa, const tools::paging::details &page_details, const std::vector<std::optional<luramas_address>> &parent_pages);
            } // namespace parameters

            namespace args {

                  /* Adjust args based on definitions */
                  bool adjust(luramas::ir::passes::pass_manager &pm, const tools::paging::details &page_details);
            } // namespace args
      } // namespace linked

      namespace controllers {

            /* Get all condition controller returns {id, {loc, OPTIONAL(goto loc)}}, ... */
            struct flags {
                  luramas_flag fcond = false;
                  luramas_flag fcond_gotos = true;
            };
            boost::unordered_flat_map<luramas_id, std::pair<luramas_address, std::optional<luramas_address>>> get(luramas::ir::passes::pass_manager &pm, const std::vector<std::optional<luramas_address>> &parent_pages, const paging::details::page &page, const flags &f = flags());

            /* Gets all controller ids set by either a page goto or call */
            boost::unordered_flat_map<luramas_id, boost::unordered_flat_set<luramas_id>> set(luramas::ir::passes::pass_manager &pm);
      } // namespace controllers

      namespace debug {

            /* Debug graph */
            std::string graph(luramas::ir::passes::pass_manager &pm);
      } // namespace debug

      namespace propagations {

            /* Counts amount of time that constant folding can occur given target */
            luramas_count constant_folds(luramas::ir::passes::pass_manager &pm, const generation::ssa::ssa &ssa, const luramas_xregister target_ssa);
      } // namespace propagations

      namespace dominant {

            namespace extract {

                  /* Gets immidate volatile expr if there is any */
                  std::shared_ptr<ir_stat::ir_expr> immediate_volatile_expr(luramas::ir::passes::pass_manager &pm, const luramas_address loc, const std::shared_ptr<ir_stat::ir_expr> &target);

                  /* Gets dominant expr of expr target */
                  std::shared_ptr<ir_stat::ir_expr> expr(luramas::ir::passes::pass_manager &pm, const luramas_address loc, const std::shared_ptr<ir_stat::ir_expr> &target);
            } // namespace extract
      } // namespace dominant

      /* Is page code safe i.e does not violate anything and does not contain orphaned pages */
      bool safe_page_code_no_loops(luramas::ir::passes::pass_manager &pm, const luramas_blockrange &range);

      /*  Is start with close on safe? */
      bool safe(luramas::ir::passes::pass_manager &pm, const luramas_blockrange &range);
} // namespace luramas::ir::tools