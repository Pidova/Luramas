#pragma once
#include "../closures/closures.hpp"
#include "code/types/types.hpp"
#include "definitions.hpp"
#include "flags.hpp"
#include "warnings.hpp"

struct ir_stat : std::enable_shared_from_this<ir_stat> {

      using space = std::vector<std::shared_ptr<ir_stat>>; /* Vector of stats */

      /*   
        IR EXPRESSION:
          YOU SHOULD NOT CHANGE PRIMITIVE KINDS OR ADD ANY NEW ONES WILL MESS UP INTRINSICS     
      */
      struct ir_expr : std::enable_shared_from_this<ir_expr> {

            using space = std::vector<std::shared_ptr<ir_expr>>; /* Vector of exprs */

            /* Flags */
            luramas::ir::flags::ir_expr flags; /* IR flags */

            /* Data */
            luramas::il::arch::data::bin_kinds u = luramas::il::arch::data::bin_kinds::nothing; /* Unary kind */
            luramas::il::arch::data::bin_kinds b = luramas::il::arch::data::bin_kinds::nothing; /* Binop kind */
            expr_kinds k = expr_kinds::nothing;                                                 /* Expr kind */
            tkind tk = tkind::nothing;                                                          /* Type kind */
            expr_logical e = expr_logical::nothing;                                             /* Logical kind */
            expr_reg_kinds rk = expr_reg_kinds::reg;                                            /* Register kind */

            /* Values */
            luramas_int n = 0u;                                                     /* Numeric value */
            bool bv = false;                                                        /* Boolean value */
            luramas_register reg = 0u;                                              /* Register */
            luramas_vregister vreg = -1;                                            /* Virtual register */
            luramas_address amount = 0u;                                            /* Amount value */
            std::string v = "";                                                     /* String value */
            std::shared_ptr<luramas::ir::types::object::type> non_native = nullptr; /* Castable type (Resulting type) */
            std::shared_ptr<luramas::ir::types::object::type> xtype = nullptr;      /* Extended type (General purpose use type) */

            /* Exprs */
            std::shared_ptr<ir_expr> l = nullptr;  /* L-Value */
            std::shared_ptr<ir_expr> r = nullptr;  /* R-Value */
            std::shared_ptr<ir_expr> ev = nullptr; /* Extra-Value */
            std::shared_ptr<ir_expr> xv = nullptr; /* Extended-Value */

            /* Misc */
            space members;                                                                       /* Members of the object */
            ir_stat::space closure;                                                              /* Closure for the function */
            space captures;                                                                      /* Captured data for calls  */
            std::vector<std::pair<std::shared_ptr<ir_expr>, std::shared_ptr<ir_expr>>> tmembers; /* Table members of the object */

            std::shared_ptr<ir_stat> transform() const;                                                       /* Transform expr into stat, returns nullptr if it can't */
            void clone(std::shared_ptr<ir_expr> &expr, const bool deep = true, const bool regs = true) const; /* Clone expr into a buffer */
            std::shared_ptr<ir_expr> clone(const bool deep = true, const bool regs = true) const;             /* Clone expr as the result */

            /* Emitters */
            void emit_upvalue(const luramas_register r, const luramas_vregister vreg);
            void emit_reg(const luramas_register r);
            void emit_closure(const ir_stat::space &closure);
            void emit_reg_arg(const luramas_register r);
            void emit_global(const std::string &g);
            void emit_object(const std::shared_ptr<luramas::ir::types::object::type> &obj);
            void emit_kvalue(const std::string &k);
            void emit_flag(const std::shared_ptr<ir_expr> &id);
            void emit_capture(const std::shared_ptr<ir_expr> &l, const luramas::il::arch::operand::upvalue_kind kind);
            void emit_str(const std::string &s);
            void emit_boolean(const bool b);
            void emit_blank_lvalue();
            void emit_int(const luramas_int &i);
            void emit_extpr(const luramas_int &i);
            void emit_stack(const std::intptr_t id = 0u);
            void emit_controller();
            void emit_none();
            void emit_vcall(const std::shared_ptr<ir_expr> &vcall);
            void emit_varg(const std::shared_ptr<ir_expr> &varg);
            void emit_call(const std::shared_ptr<ir_expr> &call);
            void emit_arg(const std::shared_ptr<ir_expr> &arg);
            void emit_variadic();
            void emit_arith(const std::shared_ptr<ir_expr> &l, const std::shared_ptr<ir_expr> &r, luramas::il::arch::data::bin_kinds b);
            void emit_self(const std::shared_ptr<ir_expr> &l, const std::shared_ptr<ir_expr> &r);
            void emit_ternary(const std::shared_ptr<ir_expr> &cond, const std::shared_ptr<ir_expr> &then_v, const std::shared_ptr<ir_expr> &else_v);
            void emit_ternary(const std::shared_ptr<ir_expr> &cond_l, const std::shared_ptr<ir_expr> &cond_r, luramas::il::arch::data::bin_kinds b, const std::shared_ptr<ir_expr> &thenv, const std::shared_ptr<ir_expr> &elsev);
            void emit_idx(const std::shared_ptr<ir_expr> &l, const std::shared_ptr<ir_expr> &r);
            void emit_cond(const std::shared_ptr<ir_expr> &l, const luramas::il::arch::data::bin_kinds b, const std::shared_ptr<ir_expr> &r = nullptr);
            void emit_concat(const std::shared_ptr<ir_expr> &v);
            void emit_unpack(const std::shared_ptr<ir_expr> &v, const luramas_address amount);
            void emit_table_set(const std::shared_ptr<ir_expr> &v, const std::shared_ptr<ir_expr> &i = nullptr);
            void emit_table_get(const std::shared_ptr<ir_expr> &v, const std::shared_ptr<ir_expr> &i = nullptr);
            void emit_table();
            void emit_unary(const std::shared_ptr<ir_expr> &l, const luramas::il::arch::data::bin_kinds u);
            void emit_cond(const std::shared_ptr<ir_expr> &l, const expr_logical e, const luramas::il::arch::data::bin_kinds b, const std::shared_ptr<ir_expr> &r);
            void emit_bitread(const std::shared_ptr<ir_expr> &value, const std::shared_ptr<ir_expr> &min, const std::shared_ptr<ir_expr> &max, const std::shared_ptr<luramas::ir::types::object::type> &non_native);
            void emit_bitwrite(const std::shared_ptr<ir_expr> &value, const std::shared_ptr<ir_expr> &lvalue, const std::shared_ptr<ir_expr> &min, const std::shared_ptr<ir_expr> &max, const std::shared_ptr<luramas::ir::types::object::type> &non_native);
            void emit_memoryread(const std::shared_ptr<ir_expr> &target, const luramas_bitwidth set_bits, const std::shared_ptr<ir_expr> &offset = nullptr);
            void emit_cast(const std::shared_ptr<luramas::ir::types::object::type> &object, const std::shared_ptr<ir_expr> &value);
            void emit_page_function_call(const std::shared_ptr<ir_expr> &id, const std::shared_ptr<ir_expr> &insertion_where, const std::shared_ptr<ir_expr> &value);
            void emit_register_annotation(const std::string &str);
            void emit_nothing();
            template <expr_logical e>
            void emit_logical(const std::shared_ptr<ir_expr> &l, const std::shared_ptr<ir_expr> &r) {
                  this->k = expr_kinds::condition;
                  this->e = e;
                  this->l = l;
                  this->r = r;
                  return;
            }

            /* Is kind */
            template <tkind k>
            bool is_tk() const {
                  return this->tk == k;
            }
            template <expr_kinds k>
            bool is_k() const {
                  return this->k == k;
            }
            template <luramas::il::arch::data::bin_kinds b>
            bool is_b() const {
                  return this->b == b;
            }
            template <expr_reg_kinds rk>
            bool is_rk() const {
                  return this->rk == rk;
            }

            /* Is data */
            bool is_register_reference() const;            /* Kind can reference registers? */
            bool is_name_qualifier() const;                /* Uses any sort of naming? */
            bool is_reg(const luramas_register r) const;   /* Is register? */
            bool is_flag(const luramas_int &r) const;      /* Is flag? */
            bool is_paging() const;                        /* Is paging kind? */
            bool is_primitive() const;                     /* Is primitive kind? */
            bool is_mutable_basic_tk() const;              /* Type kind can be mutated by other instructions? */
            bool is_volatile() const;                      /* Unsafe or can cause undeterministic results? */
            bool is_closure_sensitive() const;             /* Can be effected by closure? */
            bool is_primitive_kind_dest_violation() const; /* Is primitive expr kind in violation if a dest? */
            bool is_mutable_tk() const;                    /* Is type kind mutable? */
            bool is_global_tk() const;                     /* Is type kind a global? */
            bool is_integral() const;                      /* Is type kind an integer? */
            bool is_integral(const luramas_int &n) const;  /* Is type kind an integer and int == n? */
            bool is_unsafe_k() const;                      /* Is kind unsafe? */
            bool is_unsafe() const;                        /* Is expr unsafe? */
            bool is_flag() const;                          /* Is expr flag? */
            bool is_precise() const;                       /* Does int have precision? */
            bool is_concatable_tk() const;                 /* Is type kind concatable? */
            bool is_complex_k() const;                     /* Can kind produce a result? */
            bool is_complex_tk() const;                    /* Can type kind produce a result? */
            bool implicit() const;                         /* Can expr produce implicit results? */

            /* Misc */
            void clear();
            std::string str(const std::string &prefix = "", const std::string &stat_prefix = "");
            void dump(const char *const descriminator = "");
            void serialize(std::ostream &os, const std::shared_ptr<std::vector<std::pair<std::string, std::vector<luramas_address>>>> &annotations = nullptr) const;
            void load(std::istream &is);
            std::shared_ptr<ir_expr> c();

            /* Extract buffer */
            void extract_ordered_regs(luramas_registers &buffer, const bool ignore_upvalues = false) const;
            void extract_captures(ir_stat::ir_expr::space &buffer) const;
            void extract_reg_exprs(boost::unordered_flat_multiset<std::shared_ptr<ir_stat::ir_expr>> &buffer);
            void extract_exprs(boost::unordered_flat_multiset<std::shared_ptr<ir_stat::ir_expr>> &buffer);
            void extract_exprs(boost::unordered_flat_set<std::shared_ptr<ir_stat::ir_expr>> &buffer);
            void extract_ordered_exprs(ir_stat::ir_expr::space &buffer);
            void extract_order_of_operation_exprs(ir_stat::ir_expr::space &buffer);
            void extract_list(std::vector<ir_stat::ir_expr::space> &buffer);
            void extract(boost::unordered_flat_multiset<std::shared_ptr<ir_expr>> &buffer, const expr_kinds k);
            void extract_regs(boost::unordered_flat_multiset<luramas_register> &buffer, const bool ignore_upvalues = false) const;
            void extract_regs(boost::unordered_flat_set<luramas_register> &buffer, const bool ignore_upvalues) const;
            void extract(boost::unordered_flat_set<std::shared_ptr<ir_expr>> &buffer, const luramas_register target, const bool all = false);
            void extract_shallow_ordered_exprs(ir_stat::ir_expr::space &buffer) const;

            /* Extract */
            luramas_registers extract_ordered_regs() const;
            ir_stat::ir_expr::space extract_shallow_ordered_exprs() const;
            ir_stat::ir_expr::space extract_ordered_exprs();
            ir_stat::ir_expr::space extract_order_of_operation_exprs();
            boost::unordered_flat_multiset<std::shared_ptr<ir_stat::ir_expr>> extract_exprs();
            boost::unordered_flat_multiset<std::shared_ptr<ir_stat::ir_expr>> extract_reg_exprs();
            std::vector<ir_stat::ir_expr::space> extract_list();
            boost::unordered_flat_multiset<std::shared_ptr<ir_expr>> extract(const expr_kinds k);
            boost::unordered_flat_multiset<luramas_register> extract_regs(const bool ignore_upvalues = false) const;
            boost::unordered_flat_set<std::shared_ptr<ir_expr>> extract(const luramas_register target, const bool all = false);
            luramas_int extract_integral() const;
            luramas_int_base extract_integral_base() const;
            bool is_min_integral() const;
            bool is_max_integral() const;
            bool safe_arith() const;

            /* Replace (Full) */
            void replace(const boost::unordered_flat_map<luramas_register, std::shared_ptr<ir_stat::ir_expr>> &exprs);

            /* Replace (Shallow successor values) */
            void shallow_replace(const boost::unordered_flat_map<std::shared_ptr<ir_stat::ir_expr>, std::shared_ptr<ir_stat::ir_expr>> &exprs);
            void shallow_replace(const boost::unordered_flat_map<luramas_register, std::shared_ptr<ir_stat::ir_expr>> &exprs);

            /* Replace (Current) */
            void curr_replace(const luramas_int &n);

            std::shared_ptr<ir_expr> visit_parent(const std::shared_ptr<ir_expr> &e);

            /* Propagations */
            void propagate_flag(const luramas_int &target, const std::shared_ptr<ir_expr> &e, bool &clone);
            void propagate(const luramas_register target, const std::shared_ptr<ir_expr> &e, bool &clone);
            bool propagate_violates(const luramas_register target) const;

            /* Contains */
            bool contains(const tkind tk) const;
            bool contains(const expr_kinds k) const;
            bool contains(const luramas_register r) const;
            bool contains(const std::shared_ptr<ir_stat::ir_expr> &expr) const;
            bool contains_volatile() const;
            bool contains_upvalue() const;

            /* Count */
            luramas_count count(const std::shared_ptr<ir_stat::ir_expr> &expr) const;

            /* Compare */
            bool compare(const ir_expr &other, const bool safe = false, const bool nest = true) const;
            bool compare(const std::shared_ptr<ir_expr> &other, const bool safe = false, const bool nest = true) const;
            bool operator==(const ir_expr &other) const;
            bool operator!=(const ir_expr &other) const;

          private:
            std::string v_s() const;
      };

      /* Flags */
      luramas::ir::flags::ir_stat flags; /* IR flags */

      /* Data */
      keywords k = keywords::nothing;                                                     /* K Kind */
      condition_kind c = condition_kind::nothing;                                         /* Condition kind */
      page_function_goto_kind pfk = page_function_goto_kind::jump;                        /* Page function kind */
      luramas::il::arch::data::bin_kinds b = luramas::il::arch::data::bin_kinds::nothing; /* Binop kind */

      /* Values */
      luramas_address label = 0u;            /* Label for goto */
      luramas_address jlabel = 0u;           /* Jump ID for label */
      luramas_address end_label = 0u;        /* End */
      luramas_address elif_end_label = 0u;   /* Else if end */
      luramas_address table_index = 0u;      /* Table index */
      luramas_address extra_bits = 0u;       /* Extras */
      luramas_vaddress underlying_jump = -1; /* Applicable to stats that dont have an associated label, IDX to IR */

      /* Data  */
      std::shared_ptr<ir_expr> lba = nullptr; /* Extra value or iterator definition */
      std::shared_ptr<ir_expr> l = nullptr;   /* Usually assigning value */
      std::shared_ptr<ir_expr> r = nullptr;   /* General purpose */
      std::shared_ptr<ir_expr> v = nullptr;   /* General purpose */

      /* Expression specific */
      std::vector<std::shared_ptr<ir_expr>> parameters;          /* Parameters */
      std::map<luramas_register, std::shared_ptr<ir_expr>> args; /* Arguments given for definition */
      std::vector<std::shared_ptr<ir_expr>> upvalues;            /* Upvalues given for definition */
      std::vector<std::shared_ptr<ir_expr>> meta;                /* Meta data (Has to be explicitly mutated) */

      /* General mutable members */
      std::vector<std::shared_ptr<ir_expr>> members;  /* Members of the object */
      std::vector<std::shared_ptr<ir_expr>> smembers; /* Secondary members of the object */
      std::vector<std::shared_ptr<ir_expr>> tmembers; /* Table members of the object */

      std::string annotation = ""; /* Not static may get optimized out */

      /* Cloners */
      void clone(std::shared_ptr<ir_stat> &buffer, const bool deep = true, const bool regs = true) const;
      std::shared_ptr<ir_stat> clone(const bool deep = true, const bool regs = true) const;

      /* Emitters */
      void emit_label(const luramas_address &l);
      void emit_end();
      void emit_definition();
      void emit_parameters();
      void emit_definition(const luramas_register reg, const std::shared_ptr<ir_expr> &arg);
      void emit_upv_definition(const std::shared_ptr<ir_expr> &upv);
      void emit_repeat();
      void emit_create_stack(const std::shared_ptr<ir_expr> &l);
      void emit_until(const std::shared_ptr<ir_expr> &l, const luramas::il::arch::data::bin_kinds b = luramas::il::arch::data::bin_kinds::nothing, const std::shared_ptr<ir_expr> &r = nullptr);
      void emit_while(const std::shared_ptr<ir_expr> &l, const luramas::il::arch::data::bin_kinds b = luramas::il::arch::data::bin_kinds::nothing, const std::shared_ptr<ir_expr> &r = nullptr);
      void emit_break();
      void emit_continue();
      void emit_call(const std::shared_ptr<ir_expr> &c);
      void emit_page_function_call(const std::shared_ptr<ir_expr> &id, const std::shared_ptr<ir_expr> &insertion_where, const std::shared_ptr<ir_expr> &value, const std::shared_ptr<ir_expr> &controller = nullptr);
      void emit_page_function_jump(const std::shared_ptr<ir_expr> &id);
      void emit_virtual_function_call(const luramas_id key);
      void emit_arg(const std::shared_ptr<ir_expr> &c);
      void emit_assignment(const std::shared_ptr<ir_expr> &l, const std::shared_ptr<ir_expr> &r);
      void emit_page_function_closure(const std::shared_ptr<ir_expr> &id, const std::shared_ptr<ir_expr> &closure);
      void emit_page_function_start(const std::shared_ptr<ir_expr> &id);
      void emit_page_function_end(const std::shared_ptr<ir_expr> &id);
      void emit_page_function_pass();
      void emit_isolate();
      void emit_setflag(const std::shared_ptr<ir_stat::ir_expr> &flag, const std::shared_ptr<ir_stat::ir_expr> &source);
      void emit_memoryset(const std::shared_ptr<ir_expr> &target, const std::shared_ptr<ir_expr> &source, const luramas_address set_bits, const std::shared_ptr<ir_expr> &offset = nullptr);
      void emit_switch(const std::shared_ptr<ir_expr> &cmp);
      void emit_switch_case(const std::shared_ptr<ir_expr> &switch_case);
      void emit_switch_default_case();
      void emit_for_loop_init();
      void emit_tab_assign(const std::shared_ptr<ir_expr> &t, const std::shared_ptr<ir_expr> &idx, const std::shared_ptr<ir_expr> &v);
      void emit_tab_setlist(const std::shared_ptr<ir_expr> &t, const std::shared_ptr<ir_expr> &v);
      void emit_mul_lv(const std::shared_ptr<ir_expr> &l);
      void emit_return(const std::shared_ptr<ir_expr> &c = nullptr);
      void emit_return(const ir_stat::ir_expr::space &v);
      void emit_return(const std::shared_ptr<ir_expr> &read_loc, const ir_stat::ir_expr::space &v);
      void emit_return(const std::shared_ptr<ir_expr> &read_loc, const std::shared_ptr<ir_stat::ir_expr> &c);
      void emit_forloop_numeric(const std::shared_ptr<ir_expr> &lr, const std::shared_ptr<ir_expr> &init, const std::shared_ptr<ir_expr> &max, const std::shared_ptr<ir_expr> &step);
      void emit_forloop_generic(const std::shared_ptr<ir_expr> &var = nullptr, const std::shared_ptr<ir_expr> &v = nullptr);
      void emit_forloop_meta(const std::shared_ptr<ir_expr> &min, const std::shared_ptr<ir_expr> &max, const std::shared_ptr<ir_expr> &step);
      void emit_cond(const std::shared_ptr<ir_expr> &l, const luramas::il::arch::data::bin_kinds b = luramas::il::arch::data::bin_kinds::nothing, const std::shared_ptr<ir_expr> &r = nullptr);
      void emit_else();
      void emit_cond_goto(const luramas_address &loc);
      void emit_cond_goto(const std::shared_ptr<ir_expr> &l, const luramas::il::arch::data::bin_kinds b, const luramas_address &loc, const std::shared_ptr<ir_expr> &r = nullptr);
      void emit_stack_push(const std::shared_ptr<ir_expr> &v, const std::shared_ptr<ir_expr> &id);
      void emit_stack_read(const std::shared_ptr<ir_expr> &l, const std::shared_ptr<ir_expr> &amt, const std::shared_ptr<ir_expr> &id);
      void emit_stack_pop(const std::shared_ptr<ir_expr> &v, const std::shared_ptr<ir_expr> &id);
      void emit_goto(const luramas_address &loc);
      void emit_bitwrite(const std::shared_ptr<ir_expr> &dest, const std::shared_ptr<ir_expr> &src, const std::shared_ptr<ir_expr> &min, const std::shared_ptr<ir_expr> &max);
      void emit_annotation(const std::string &annotation);
      void emit_metadata(const std::shared_ptr<ir_expr> &name, const std::shared_ptr<ir_expr> &data);
      void emit_tag_start(const std::shared_ptr<ir_expr> &name, const std::shared_ptr<ir_expr> &table);
      void emit_tag_end();
      void emit_entry_point();
      void emit_command(const std::shared_ptr<ir_expr> &name);

      template <expr_logical e, bool back = false>
      inline void append_cond(const std::shared_ptr<ir_expr> &l, const luramas::il::arch::data::bin_kinds b = luramas::il::arch::data::bin_kinds::nothing, const std::shared_ptr<ir_expr> &r = nullptr) {
            if constexpr (e == expr_logical::nothing) {
                  return;
            }
            if (this->is_k<keywords::condition>() || this->is_k<keywords::condition_goto>()) {
                  auto curr = this->l;
                  if (this->r) {
                        curr = std::make_shared<ir_expr>();
                        curr->emit_cond(this->l, this->b, this->r);
                  }
                  auto t = l;
                  if (r || b != luramas::il::arch::data::bin_kinds::nothing) {
                        t = std::make_shared<ir_expr>();
                        t->emit_cond(l, b, r);
                  }
                  auto cond = std::make_shared<ir_expr>();
                  if (back) {
                        cond->emit_logical<e>(t, curr);
                  } else {
                        cond->emit_logical<e>(curr, t);
                  }
                  this->l = cond;
                  this->b = luramas::il::arch::data::bin_kinds::nothing;
                  this->r = nullptr;
            }
            return;
      }

      /* Is */
      inline bool is_k(const keywords k) const {
            return this->k == k;
      }
      template <keywords k>
      inline bool is_k() const {
            return this->is_k(k);
      }
      template <condition_kind k>
      inline bool is() const {
            return this->c == k;
      }

      /* Is kind */
      bool is_scoped() const;
      bool is_psuedo() const;
      bool is_terminator() const;
      bool is_terminal() const;
      bool is_trivial_terminal() const;
      bool is_interrupt() const;
      bool is_paging() const;
      bool is_paging_control_flow_transfer() const;
      bool is_scope_start() const;
      bool is_scopeable() const;
      bool is_implicit_flow_interrupt() const;
      bool is_potential_side_effectable() const;
      bool is_scope_start_highlevel() const;
      bool is_control_flow_transfer() const;
      bool is_scope_end() const;
      bool is_loop() const;
      bool is_breakable() const;
      bool is_continueable() const;
      bool is_isolation() const;
      bool is_for_loop() const;
      bool is_defines() const;
      bool is_goto_label() const;
      bool is_primitive_kind_dest_violation() const;
      bool is_assignment() const;
      bool is_data_assignment() const;
      bool is_meta() const;
      bool is_flow_interrupt() const;
      bool is_volatile() const;
      bool is_flag_volatile() const;
      bool is_self_referential_assignment() const;

      void extract_ordered_source_regs(luramas_registers &buffer, const bool ignore_upvalues = false) const;
      void extract_source_captures(ir_stat::ir_expr::space &buffer) const;
      void extract_ordered_dest_regs(luramas_registers &buffer, const bool ignore_upvalues = false) const;
      void extract_shallow_ordered_exprs(ir_stat::ir_expr::space &buffer) const;
      void extract_ordered_deep_exprs(ir_stat::ir_expr::space &buffer) const;
      void extract_ordered_exprs(ir_stat::ir_expr::space &buffer) const;
      void extract_exprs(boost::unordered_flat_multiset<std::shared_ptr<ir_stat::ir_expr>> &buffer) const;
      void extract_dests(boost::unordered_flat_multiset<std::shared_ptr<ir_stat::ir_expr>> &buffer) const;

      void extract_rvalues(boost::unordered_flat_multiset<std::shared_ptr<ir_stat::ir_expr>> &buffer) const;
      void extract_set_rvalues(boost::unordered_flat_set<std::shared_ptr<ir_stat::ir_expr>> &buffer) const;
      void extract_ordered_rvalues(ir_stat::ir_expr::space &buffer) const;
      void extract_deep_set_rvalues(boost::unordered_flat_set<std::shared_ptr<ir_stat::ir_expr>> &buffer) const;
      void extract_deep_ordered_rvalues(ir_stat::ir_expr::space &buffer) const;
      void extract_lvalues(boost::unordered_flat_multiset<std::shared_ptr<ir_stat::ir_expr>> &buffer) const;
      void extract_set_lvalues(boost::unordered_flat_set<std::shared_ptr<ir_stat::ir_expr>> &buffer) const;
      void extract_ordered_lvalues(ir_stat::ir_expr::space &buffer) const;
      void extract_deep_set_lvalues(boost::unordered_flat_set<std::shared_ptr<ir_stat::ir_expr>> &buffer) const;
      void extract_deep_ordered_lvalues(ir_stat::ir_expr::space &buffer) const;
      void extract_list(std::vector<ir_stat::ir_expr::space> &buffer);
      void extract_source_regs(boost::unordered_flat_multiset<luramas_register> &buffer, const bool ignore_upvalues = false) const;
      void extract_dest_regs(boost::unordered_flat_multiset<luramas_register> &buffer, const bool ignore_upvalues = false) const;
      void extract_set_dest_regs(boost::unordered_flat_set<luramas_register> &buffer, const bool ignore_upvalues = false) const;

      std::vector<std::vector<std::shared_ptr<ir_expr>>> extract_list();
      boost::unordered_flat_multiset<luramas_register> extract_source_regs(const bool ignore_upvalues = false) const;
      boost::unordered_flat_multiset<luramas_register> extract_dest_regs(const bool ignore_upvalues = false) const;
      boost::unordered_flat_set<luramas_register> extract_set_dest_regs(const bool ignore_upvalues = false) const;

      luramas_registers extract_ordered_source_regs(const bool ignore_upvalues = false) const;
      luramas_registers extract_ordered_dest_regs(const bool ignore_upvalues = false) const;

      ir_stat::ir_expr::space extract_ordered_source_captures() const;
      boost::unordered_flat_multiset<std::shared_ptr<ir_stat::ir_expr>> extract_rvalues() const;
      boost::unordered_flat_set<std::shared_ptr<ir_stat::ir_expr>> extract_set_rvalues() const;
      ir_stat::ir_expr::space extract_ordered_rvalues() const;
      boost::unordered_flat_set<std::shared_ptr<ir_stat::ir_expr>> extract_deep_set_rvalues() const;
      ir_stat::ir_expr::space extract_deep_ordered_rvalues() const;
      boost::unordered_flat_multiset<std::shared_ptr<ir_stat::ir_expr>> extract_lvalues() const;
      boost::unordered_flat_set<std::shared_ptr<ir_stat::ir_expr>> extract_set_lvalues() const;
      boost::unordered_flat_set<std::shared_ptr<ir_stat::ir_expr>> extract_deep_set_lvalues() const;
      ir_stat::ir_expr::space extract_deep_ordered_lvalues() const;
      ir_stat::ir_expr::space extract_ordered_lvalues() const;

      /* Extracts parent exprs */
      ir_stat::ir_expr::space extract_shallow_ordered_exprs() const;
      ir_stat::ir_expr::space extract_ordered_deep_exprs() const;
      ir_stat::ir_expr::space extract_ordered_exprs() const;
      boost::unordered_flat_multiset<std::shared_ptr<ir_expr>> extract_exprs() const;
      boost::unordered_flat_multiset<std::shared_ptr<ir_stat::ir_expr>> extract_dests() const;

      /* Replace (Full) */
      void replace(const boost::unordered_flat_map<luramas_register, std::shared_ptr<ir_stat::ir_expr>> &exprs);

      /* Replace (Shallow) */
      void shallow_replace(const boost::unordered_flat_map<luramas_register, std::shared_ptr<ir_stat::ir_expr>> &exprs);

      /* Propagates target when expression is not nullptr if it is it will remove target. */
      void propagate_flag(const luramas_int &target, const std::shared_ptr<ir_expr> &e, bool &clone);
      void propagate(const luramas_register target, const std::shared_ptr<ir_expr> &e, bool &clone);
      bool propagate_violates(const luramas_register target) const;

      /* Visitors */
      boost::unordered_flat_set<std::shared_ptr<ir_expr>> visit(const luramas_register target, const bool all = false);
      boost::unordered_flat_set<std::shared_ptr<ir_expr>> visit_sources(const luramas_register target, const bool all = false);
      std::shared_ptr<ir_stat::ir_expr> visit_lvalue(const luramas_register reg) const;
      std::pair<std::shared_ptr<ir_stat::ir_expr>, std::shared_ptr<ir_stat>> visit_parent(const std::shared_ptr<ir_stat::ir_expr> &expr);

      /* Contains */
      bool contains(const tkind tk) const;
      bool contains(const expr_kinds k) const;

      /* Count */
      luramas_count count(const std::shared_ptr<ir_stat::ir_expr> &expr) const;

      /* Compare */
      bool compare(const ir_stat &other, const bool safe = false, const bool include_labels = false) const;
      bool compare(const std::shared_ptr<ir_stat> &other, const bool safe = false, const bool include_labels = false) const;
      bool operator==(const ir_stat &other) const;
      bool operator!=(const ir_stat &other) const;

      std::string str(const std::string &stat_prefix = "") const;
      std::string str_type() const;
      void dump(const char *const descriminator = "") const;
      void clear_underlying_labels();
      void serialize(std::ostream &os, const std::shared_ptr<std::vector<std::pair<std::string, std::vector<luramas_address>>>> &annotations = nullptr) const;
      void load(std::istream &is);
      void clear();
};

using virtual_function_table = boost::unordered_flat_map<std::size_t /*IDX*/, std::vector<std::shared_ptr<ir_stat> /* DATA */>>;

class se_ir {

    public:
      se_ir(const ir_stat::space &data)
          : data(data) {
            return;
      }

      /* Next avaliable unused page ID */
      static luramas_address avaliable_page(const ir_stat::space &data);
      luramas_address avaliable_page();

      /* Next avaliable unused label ID */
      static luramas_address avaliable_label(const ir_stat::space &data);
      luramas_address avaliable_label();

      /* Next avaliable unused end label ID */
      static luramas_address avaliable_end_label(const ir_stat::space &data);
      luramas_address avaliable_end_label() const;

      /* Next avaliable unused register */
      static luramas_register avaliable_register(const ir_stat::space &data);
      luramas_register avaliable_register() const;

      /* Reference count of label */
      static luramas_count ref_count(const ir_stat::space &data, const luramas_address label);
      luramas_count ref_count(const luramas_address label) const;

      /*
             OPTIONAL (CLOSURE DEFINITION)
             {CODE}
      */
      ir_stat::space data;                  /* IR data */
      std::vector<ir_stat::space> closures; /* Closures */
      luramas_flag fhas_pages = false;      /* Has pages? */

    private:
      luramas_address ava_page = 0u;  /* Avaliable page */
      luramas_address ava_label = 0u; /* Avaliable label */
};

namespace luramas::ir {

      namespace data {

            using cb_bkinds = bool (*)(const il::arch::data::bin_kinds k); /* Callback to bin kinds */
            using cb_tkind = bool (*)(const tkind k);                      /* Callback to type kinds  */
            using cb_kinds = bool (*)(const expr_kinds k);                 /* Callback to expr kinds */
            using cb_keywords = bool (*)(const keywords k);                /* Callback to keywords */

            /* References a read value? */
            bool reference(const tkind k);

            /* Primitive kind? */
            bool primitive(const tkind k);

            /* Concatable kind? */
            bool concatable(const tkind k);

            /* TK can be mutated? */
            bool mutable_basic(const tkind k);

            /* Kind references a register? */
            bool register_reference(const expr_kinds k);

            /* Kind may contian multiple values? */
            bool is_complex(const expr_kinds k);

            /* Can TK have a string associated with it? */
            bool is_name_qualifier(const tkind k);

            /* Is type kind complex? */
            bool is_complex(const tkind k);

            /* Type kind is mutable */
            bool mutable_(const tkind k);

            /* Global type kind? */
            bool global(const tkind k);

            /* Integral type kind? */
            bool integral(const tkind k);

            /* Is paging expr kind? */
            bool paging(const expr_kinds k);

            /* Expression can be mutated by other calls etc? */
            bool unsafe(const expr_kinds k);

            /* Expression is volatile? */
            bool volatile_(const expr_kinds k);

            /* Is primitive kind in violation if a dest? */
            bool primitive_kind_dest_violation(const keywords k);

            /* Is keyword a self referential assignment? */
            bool self_referential_assignment(const keywords k);

            /* Is primitive expr kind in violation if a dest? */
            bool primitive_expr_kind_dest_violation(const expr_kinds k);

            /* Mutable if taken out of closure */
            bool closure_sensitive(const expr_kinds k);

            /* Is flag? */
            bool flag(const expr_kinds k);

            /* Defines a variable in scope */
            bool defines(const keywords k);

            /* Assigns something to something else */
            bool assignment(const keywords k);

            /* Assigns to some form of data? */
            bool is_data_assignment(const keywords k);

            /* Meta keyword (Stat that is implicitly executed) */
            bool is_meta(const keywords k);

            /* Termination keyword */
            bool terminator(const keywords k);

            /* Terminates keyword */
            bool terminal(const keywords k);

            /* Keyword is volatile? */
            bool volatile_(const keywords k);

            /* Flag volatile? */
            bool flag_volatile(const keywords k);

            /* Keyword is apart of a scope */
            bool scoped(const keywords k);

            /* Is keyword a psuedo keyword? */
            bool psuedo(const keywords k);

            /* Flow interrupt */
            bool interrupt(const keywords k);

            /* Control flow interrupt */
            bool flow_interrupt(const keywords k);

            /* Keyword indicates start of a new scope */
            bool scope_start(const keywords k);

            /* Keyword is a paging keyword */
            bool paging(const keywords k);

            /* Keyword is a paging control flow transfer */
            bool paging_control_flow_transfer(const keywords k);

            /* Keyword is scopeable */
            bool scopeable(const keywords k);

            /* Keyword implicit of a flow interrupt */
            bool implicit_flow_interrupt(const keywords k);

            /* Keyword has potential side effects */
            bool potential_side_effects(const keywords k);

            /* Keyword implicitly or explicitly changes control flow */
            bool control_flow_transfer(const keywords k);

            /* Start of scope highlevel */
            bool scope_start_highlevel(const keywords k, const condition_kind c);

            /* Keyword indicates end of scope */
            bool scope_end(const keywords k);

            /* Looping keyword */
            bool loop(const keywords k);

            /* For loop?*/
            bool for_loop(const keywords k);

            /* Can break out of it? */
            bool breakable(const keywords k);

            /* Can continue from it? */
            bool continueable(const keywords k);

            /* Is isolate keyword? */
            bool isolation(const keywords k);

            /* Gotos label */
            bool goto_label(const keywords k);

      } // namespace data

      namespace passes {

            /* Defs */
            using cb_valid_stat = std::function<bool(const std::shared_ptr<ir_stat> &)>;
            using cb_stat_results = std::function<std::vector<std::shared_ptr<ir_stat>>(const std::shared_ptr<ir_stat> &)>;
            using cb_expr_results = std::function<std::vector<std::shared_ptr<ir_stat>>(const std::shared_ptr<ir_stat::ir_expr> &)>;
            using cb_stat_result = std::function<std::shared_ptr<ir_stat::ir_expr>(const std::shared_ptr<ir_stat> &)>;
            using cb_gen_stats = std::function<std::vector<std::shared_ptr<ir_stat>>()>;

            /* Environment flags */
            struct environment_flags {

                  /* Flags */
                  luramas_flag fhas_pages = false;                        /* Has pages? */
                  luramas_flag fhas_types = false;                        /* Has types? */
                  luramas_flag fhas_memory = false;                       /* Has Memory? */
                  luramas_flag fhas_nan = true;                           /* NaN can be deduced from arithmetics? */
                  luramas_flag fhas_references = false;                   /* Has references? */
                  luramas_flag fallow_definition_flattening = false;      /* Allow variables to be flattened? */
                  luramas_flag fallow_advance_constant_prop = false;      /* Allow advanced constant propagation? */
                  luramas_flag fsafe_stack = false;                       /* Is the stack is safe? */
                  luramas_flag fcomparative_results_binvals = true;       /* Comparative results are objects (i.e. compare results become integrals)? */
                  luramas_flag fdefault_value_arith = true;               /* Default value for arithmetics? */
                  luramas_flag fforloop_iterator_cmps = false;            /* For loop has iterator comparisons? */
                  luramas_flag fprimitive_object = false;                 /* Primitives are objects? */
                  luramas_flag feliminate_flags = false;                  /* Eliminate flags? */
                  luramas_flag fstring_basic_len = true;                  /* String basic length? */
                  luramas_flag freal_objects = true;                      /* Are objects represented in seperate types or pointers? */
                  luramas_flag fcast_power_of_2 = true;                   /* Only generate casts for power of 2 when required? */
                  luramas_flag fexprcanon_use_table = false;              /* Allow Expression Canonicalization to OPT table? */
                  luramas_flag fuse_bitwise = false;                      /* Allow optimizations to bitwise? */
                  luramas_flag funsafe_pages = false;                     /* Mark pages as unsafe? */
                  luramas_flag fecc_unsafe_pages = false;                 /* Are pages unsafe and should ecc ignore them? */
                  luramas_flag fmemory_assign_safe = false;               /* Are memory assignments completely safe i.e. can fold without side effects? */
                  luramas_flag fmemory_read_safe = false;                 /* Are memory reads completely safe i.e. can remove an expr that has a memread without side effects? */
                  luramas_flag fremove_page_dead_args = false;            /* Can remove dead args from page? */
                  luramas_flag fremove_main_dead_args = false;            /* Remove args from main closure? */
                  luramas_flag fallow_definition_cast = false;            /* Allow definition in casts to be anlyzed? */
                  luramas_flag fremove_dead_synthetics = false;           /* Synthetics are usually immune to being removed setting this will remove it if its completely dead */
                  luramas_flag fallow_ecc = true;                         /* Allow ECC to be preformed per run? */
                  luramas_flag fforce_debug_remove = false;               /* Force print debug on remove */
                  luramas_flag fforce_debug_mut = false;                  /* Force print debug on mutate */
                  luramas_flag fforce_debug_issafe = false;               /* Force print debug on is safe */
                  luramas_flag fforce_debug_setsafe = false;              /* Force print debug on set safe */
                  luramas_flag fpage_call_store_return_address = true;    /* Do page calls store return address onto stack? */
                  luramas_flag fallow_page_function_call_inline = true;   /* Are page function calls allowed to be inlined? */
                  luramas_flag fallow_page_function_return_inline = true; /* Are page function returns allowed to be inlined? */
                  luramas_flag fallow_lura_functions = false;             /* Allow optimization to lura functions */
                  luramas_flag fpromote_safety = false;                   /* Makes stuff more strictly forbidden*/
                  luramas_flag fwrite_read_permissions = true;            /* If there is a write to address then it can also read it? */
                  luramas_flag fallow_page_falls = false;                 /* Allow falling to page on certain optimizations? */
                  luramas_flag fallow_concat_ints = false;                /* Can ints be concated i.e. 2 .. 2 = 22? */
                  luramas_flag fuse_opaque_predicate_solver_z3 = false;   /* Use z3 to solve opaque predicates? */
                  luramas_flag fallow_multithreading = false;             /* Allows certain passes to utalize multithreading if needed? (CHECK options.multirheading_threads) */
                  luramas_flag fallow_expr_opt_type_constraints = false;  /* Allow bitvectors to be used in constraints for expression optimizations */

                  /* Arith safety */
                  struct safety {

                        /* Arith */
                        boost::unordered_flat_set<il::arch::data::bin_kinds> sarith_lvalue_neg;  /* Left values or singular values negative */
                        boost::unordered_flat_set<il::arch::data::bin_kinds> sarith_lvalue_zero; /* Left values or singular values zero */
                        boost::unordered_flat_set<il::arch::data::bin_kinds> sarith_rvalue_neg;  /* Right values or singular values negative */
                        boost::unordered_flat_set<il::arch::data::bin_kinds> sarith_rvalue_zero; /* Right values or singular values zero */

                        /* Even if not explicitly casting to will allow exprs to be casted to if its avaliable cast is allowed */
                        boost::unordered_flat_set<luramas::types::underlying_type> scasts_allowed_dynamic;

                        /* Stack */
                        std::optional<types::object::type> spage_function_call_stack_size = std::nullopt; /* Every time a page function is called push address to stack but with n size */
                        std::optional<luramas_id> spage_function_call_stack_id = std::nullopt;            /* Add return value to where to what stack? */
                  } safety;

                  /* Keywords */
                  luramas_flag fcan_pack_registers = true; /* Can registers be packed? */

                  struct options {

                        luramas_count multirheading_threads = 4u; /* Amount of threads to use for multithreading */
                        luramas_bitwidth odefault_bits = 64u;     /* Default bits to wrap */

                        /* Which signess is more dominant in an expression? (None does not matter) */
                        luramas::types::signess osign_dominance = luramas::types::signess::unsign;

                        /* 
                       Operands for unary/arithmetic operators do not care about signess and unless needed will promote signess outside of the operands into expression
                       It will also promote unsigness to expression based its dominance ("osign_dominance") but still demote any unsigness
                            i.e. (u32(x) | 32(a)) -> u32((32(x) | 32(a)) ; Promotes better optimizations
                  */
                        boost::unordered_flat_set<il::arch::data::bin_kinds> ounarith_operands_signess_no_side_effects;

                        /* If propagation is possible but expression is complex with more then 1 references it will reference threshold to check references if in [1, threshold) range */
                        luramas_count oforce_propagation_depth_threshold = 0u;

                        /* 
                    Optimize Stats or exprs into a common known call 
                    See tools::replace::match_wild_cards for more details on usage
                  */
                        std::vector<std::pair<ir_stat::space, std::shared_ptr<ir_stat::ir_expr>>> ostat_virtual_functions;
                        std::vector<std::pair<std::shared_ptr<ir_stat::ir_expr>, std::shared_ptr<ir_stat::ir_expr>>> oexpr_virtual_functions;

                        /* Default type */
                        luramas::types::underlying_type odefault_type = luramas::types::native::t_none;

                        /* Cbs */
                        cb_stat_results opage_call_action_s = nullptr;  /* Action when page function call stat is executed */
                        cb_expr_results opage_call_action_e = nullptr;  /* Action when page function call expr is executed */
                        cb_stat_result opage_return_read = nullptr;     /* Read value for page return */
                        cb_gen_stats opage_return_action = nullptr;     /* Action when pagen return stat is executed */
                        cb_valid_stat opropagation_exception = nullptr; /* If assignment is not phi and variables in expression does not get mutated it will check this if valid */
                  } options;
            };

            /* Data shared between environment */
            struct environment_data {
                  luramas_flag fseperated_pages = false;                           /* Pages haev been seperated? */
                  std::vector<std::shared_ptr<ir_stat::ir_expr>> unanalyzed_pages; /* Pages that has been generated but needs passes applied to it */
            };
      } // namespace passes
} // namespace luramas::ir