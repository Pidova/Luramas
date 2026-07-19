#pragma once
#include "../../il/architecture/emitter.hpp"
#include "../../il/il.hpp"
#include "builtin.hpp"

/*
	Build IL functions 
	(Different from IR)
*/
namespace luramas::il::lifter::builder {

      static constexpr auto max_flags = 100u;

      struct reg {

            reg(const luramas_register r = 0u,
                const luramas_bitwidth bits = 0u,
                const bool unsign = false,
                const std::uint8_t precision = 0u,
                const bool cast = true)
                : r(r), size(types::underlying_type(unsign, types::read_type::bits, precision, bits)), cast(cast) {
            }

            luramas_register r = 0u;     /* Register container */
            types::underlying_type size; /* Size */
            bool cast = true;            /* Casted? */
      };

      struct expr_flags {
            luramas_flag fvirtualized = false; /* Is virtualized */
            luramas_flag fglobal_wild = false; /* Is a global wild card? */
      };
      enum class expr_tkind : std::uint8_t {
            nothing,  /* Nothing */
            integral, /* Integral */
            reg,      /* Register */
            flag,     /* Flag */
            memory,   /* Memory */
            global,   /* Global */
            stack,    /* Stack */
            value     /* Double */
      };
      enum class expr_error : std::uint8_t {
            nothing,       /* No error */
            bits_mismatch, /* Mismatch bit size */
            NaN            /* Not a number */
      };
      struct build : std::enable_shared_from_this<build> {

            build(const luramas_address pc, const luramas_address idx, const luramas_register temp, const std::shared_ptr<luramas::il::ilang> &il, const std::shared_ptr<luramas::il::disassembly> &current)
                : idx(idx), pc(pc), il(il), current(current), temp(temp) {
            }
            build() = default;

            struct expr {

                  /* Constructor */
                  inline expr(const std::shared_ptr<build> &b, const std::string &global)
                      : b(b) {
                        this->emit_global(b, global);
                        return;
                  }
                  inline expr(const std::shared_ptr<build> &b, const reg &r)
                      : r(r), b(b) {
                        this->tk = expr_tkind::reg;
                        return;
                  }
                  inline expr(const std::shared_ptr<build> &b, const reg &r, const bool castable)
                      : r(r), b(b) {
                        this->tk = expr_tkind::reg;
                        this->r.cast = castable;
                        return;
                  }
                  template <typename T, std::enable_if_t<std::is_integral_v<T>, std::int32_t> = 0>
                  explicit expr(const std::shared_ptr<build> &b, T value)
                      : integral(static_cast<std::intptr_t>(value)), b(b) {
                        this->tk = expr_tkind::integral;
                  }
                  template <typename T, std::enable_if_t<std::is_floating_point_v<T>, std::int32_t> = 0>
                  explicit expr(const std::shared_ptr<build> &b, T value)
                      : v(static_cast<double>(value)), b(b) {
                        this->tk = expr_tkind::value;
                  }
                  expr() {
                        this->tk = expr_tkind::nothing;
                        return;
                  }

                  /* Emitters */
                  void emit(const expr &other);
                  void emit(const std::shared_ptr<build> &b, const reg &r, const bool castable = true);
                  void emit(const std::shared_ptr<build> &b, const std::intptr_t integral);
                  void emit_flag(const std::shared_ptr<build> &b, const std::intptr_t flag);
                  void emit_stack(const std::shared_ptr<build> &b, const std::intptr_t stack_id = LURAMAS_IR_DEFAULT_STACK_ID);
                  void emit_mem(const std::shared_ptr<build> &b, const reg &r);
                  void emit_global(const std::shared_ptr<build> &b, const std::string &global);
                  void emit_value(const std::shared_ptr<build> &b, const double v);

                  /* Arith */
                  expr operator+(const expr &other) const;
                  expr operator-(const expr &other) const;
                  expr operator*(const expr &other) const;
                  expr operator/(const expr &other) const;
                  expr operator&(const expr &other) const;
                  expr operator|(const expr &other) const;
                  expr operator^(const expr &other) const;
                  expr operator%(const expr &other) const;
                  expr operator<<(const expr &other) const;
                  expr operator>>(const expr &other) const;
                  expr operator==(const expr &other) const;
                  expr operator!=(const expr &other) const;
                  expr operator<(const expr &other) const;
                  expr operator<=(const expr &other) const;
                  expr operator>(const expr &other) const;
                  expr operator>=(const expr &other) const;
                  expr operator~() const;
                  expr operator!() const;
                  expr operator-() const;
                  expr operator+() const;
                  expr operator[](const expr &offset) const;

                  /* Assignment */
                  expr operator=(const expr &other) const;
                  expr operator+=(const expr &other) const;
                  expr operator*=(const expr &other) const;
                  expr operator/=(const expr &other) const;
                  expr operator-=(const expr &other) const;
                  expr operator%=(const expr &other) const;
                  expr operator&=(const expr &other) const;
                  expr operator|=(const expr &other) const;
                  expr operator^=(const expr &other) const;
                  expr operator<<=(const expr &other) const;
                  expr operator>>=(const expr &other) const;
                  expr operator&&(const expr &other) const;
                  expr operator||(const expr &other) const;

                  /* Arith */
                  expr operator+(const std::intptr_t other) const;
                  expr operator-(const std::intptr_t other) const;
                  expr operator*(const std::intptr_t other) const;
                  expr operator/(const std::intptr_t other) const;
                  expr operator&(const std::intptr_t other) const;
                  expr operator|(const std::intptr_t other) const;
                  expr operator^(const std::intptr_t other) const;
                  expr operator%(const std::intptr_t other) const;
                  expr operator<<(const std::intptr_t other) const;
                  expr operator>>(const std::intptr_t other) const;
                  expr operator==(const std::intptr_t other) const;
                  expr operator!=(const std::intptr_t other) const;
                  expr operator<(const std::intptr_t other) const;
                  expr operator<=(const std::intptr_t other) const;
                  expr operator>(const std::intptr_t other) const;
                  expr operator>=(const std::intptr_t other) const;
                  expr operator[](const std::intptr_t offset) const;

                  /* Arith */
                  friend expr operator+(const std::intptr_t l, const expr &r) {
                        return expr(r.b, l) + r;
                  }
                  friend expr operator-(const std::intptr_t l, const expr &r) {
                        return expr(r.b, l) - r;
                  }
                  friend expr operator*(const std::intptr_t l, const expr &r) {
                        return expr(r.b, l) * r;
                  }
                  friend expr operator/(const std::intptr_t l, const expr &r) {
                        return expr(r.b, l) / r;
                  }
                  friend expr operator&(const std::intptr_t l, const expr &r) {
                        return expr(r.b, l) & r;
                  }
                  friend expr operator|(const std::intptr_t l, const expr &r) {
                        return expr(r.b, l) & r;
                  }
                  friend expr operator^(const std::intptr_t l, const expr &r) {
                        return expr(r.b, l) ^ r;
                  }
                  friend expr operator%(const std::intptr_t l, const expr &r) {
                        return expr(r.b, l) % r;
                  }
                  friend expr operator<<(const std::intptr_t l, const expr &r) {
                        return expr(r.b, l) << r;
                  }
                  friend expr operator>>(const std::intptr_t l, const expr &r) {
                        return expr(r.b, l) >> r;
                  }
                  friend expr operator==(const std::intptr_t l, const expr &r) {
                        return expr(r.b, l) == r;
                  }
                  friend expr operator!=(const std::intptr_t l, const expr &r) {
                        return expr(r.b, l) != r;
                  }
                  friend expr operator<(const std::intptr_t l, const expr &r) {
                        return expr(r.b, l) < r;
                  }
                  friend expr operator<=(const std::intptr_t l, const expr &r) {
                        return expr(r.b, l) <= r;
                  }
                  friend expr operator>(const std::intptr_t l, const expr &r) {
                        return expr(r.b, l) > r;
                  }
                  friend expr operator>=(const std::intptr_t l, const expr &r) {
                        return expr(r.b, l) >= r;
                  }

                  /* Assign */
                  expr operator=(const std::intptr_t other) const;
                  expr operator+=(const std::intptr_t other) const;
                  expr operator*=(const std::intptr_t other) const;
                  expr operator/=(const std::intptr_t other) const;
                  expr operator-=(const std::intptr_t other) const;
                  expr operator%=(const std::intptr_t other) const;
                  expr operator&=(const std::intptr_t other) const;
                  expr operator|=(const std::intptr_t other) const;
                  expr operator^=(const std::intptr_t other) const;
                  expr operator<<=(const std::intptr_t other) const;
                  expr operator>>=(const std::intptr_t other) const;
                  expr operator++() const;
                  expr operator--() const;

                  /* Compare/Cast */
                  expr cmp(const expr &other) const;
                  expr cmp(const std::intptr_t other) const;
                  expr cast(const types::underlying_type &s);
                  expr cast(const reg &s);
                  expr cast(const luramas_bitwidth bits, const bool unsign = false, const std::uint8_t precision = 0u);
                  expr cast(const bool unsign);

                  /* Memory */
                  expr memread(const luramas_bitwidth bits) const;

                  /* R/W bit in range i.e [0, 7] */
                  expr read(const expr &min, const expr &max) const;
                  expr read(const expr &bit_index) const;
                  expr read(const luramas_bitwidth bit_index) const;
                  expr read(const luramas_bitwidth min, const luramas_bitwidth max) const;
                  expr write(const expr &min, const expr &max, const expr &value) const;
                  expr write(const luramas_bitwidth min, const luramas_bitwidth max, const expr &value) const;
                  expr write(const luramas_bitwidth min, const luramas_bitwidth max, const std::intptr_t value) const;
                  expr write(const expr &min, const expr &max, const std::intptr_t value) const;
                  expr write(const expr &min, const std::intptr_t max, const std::intptr_t value) const;
                  expr write(const expr &min, const std::intptr_t max, const expr &value) const;
                  expr write(const expr &value) const;

                  /* Misc */
                  expr fill(const luramas_bitwidth start, const std::intptr_t value) const;
                  luramas_bitwidth bits() const;
                  luramas::types::signess signess() const;
                  luramas::types::underlying_type type() const;

                  /* Debug */
                  template <expr_error e>
                  void error() {
                        this->err = e;
                        return;
                  }
                  bool empty() const;
                  void dump() const;

                  /* Is */
                  bool is_mem() const;
                  bool is_reg() const;
                  bool is_reg(const luramas_bitwidth bits) const;

                  /* Data */
                  union {
                        reg r;                  /* Register */
                        std::intptr_t integral; /* Integral */
                        double v;               /* Double */
                        luramas_id id;          /* ID */
                  };
                  expr_tkind tk = expr_tkind::nothing;  /* Type of expression */
                  std::shared_ptr<build> b = nullptr;   /* Builder */
                  expr_flags f;                         /* Flags */
                  expr_error err = expr_error::nothing; /* Any errors thrown? */
            };
            using flag_vector = boost::fixed_vector<expr, max_flags>;

            /* Make opcode */
            template <arch::opcodes op>
            std::shared_ptr<luramas::il::disassembly> gen(const std::int64_t A = 0ll, const std::int64_t B = 0ll, const std::int64_t C = 0ll, const std::int64_t D = 0ll, const std::int64_t E = 0ll, const std::int64_t F = 0ll, const std::int64_t G = 0ll) {
                  const auto inst = luramas::il::emitter::generate_opcode<op>(this->il, ++this->pc, A, B, C, D, E, F, G);
                  this->il->insert(this->idx, inst);
                  return inst;
            }
            template <arch::opcodes op>
            void make(const std::int64_t A = 0ll, const std::int64_t B = 0ll, const std::int64_t C = 0ll, const std::int64_t D = 0ll, const std::int64_t E = 0ll, const std::int64_t F = 0ll, const std::int64_t G = 0ll) {
                  this->il->insert(this->idx, luramas::il::emitter::generate_opcode<op>(this->il, ++this->pc, A, B, C, D, E, F, G));
                  return;
            }

            /* Make generic */
            template <luramas::il::arch::data::bin_kinds b>
            void make(const expr &dest, const expr &l, const expr &r = expr()) {

                  this->violation(l);
                  this->violation(dest);
                  if (r.tk == expr_tkind::integral) {
                        if (l.tk == expr_tkind::reg && l.r.cast) {
                              this->make_cast(l.r.r, l.r.r, l.bits(), l.r.size.precision, l.r.size.unsign);
                        }
                  } else {
                        if (l.tk == expr_tkind::reg && l.r.cast) {
                              this->make_cast(l.r.r, l.r.r, l.bits(), l.r.size.precision, l.r.size.unsign);
                        }
                        if (r.tk == expr_tkind::reg && r.r.cast) {
                              this->make_cast(r.r.r, r.r.r, r.bits(), r.r.size.precision, r.r.size.unsign);
                        }
                  }
                  switch (b) {
                        case luramas::il::arch::data::bin_kinds::add_: {
                              if (r.tk == expr_tkind::integral) {
                                    this->make<luramas::il::arch::opcodes::OP_ADDN>(dest.r.r, l.r.r, r.integral);
                              } else {
                                    this->make<luramas::il::arch::opcodes::OP_ADD>(dest.r.r, l.r.r, r.r.r);
                              }
                              break;
                        }
                        case luramas::il::arch::data::bin_kinds::sub_: {
                              if (r.tk == expr_tkind::integral) {
                                    this->make<luramas::il::arch::opcodes::OP_SUBN>(dest.r.r, l.r.r, r.integral);
                              } else {
                                    this->make<luramas::il::arch::opcodes::OP_SUB>(dest.r.r, l.r.r, r.r.r);
                              }
                              break;
                        }
                        case luramas::il::arch::data::bin_kinds::mul_: {
                              if (r.tk == expr_tkind::integral) {
                                    this->make<luramas::il::arch::opcodes::OP_MULN>(dest.r.r, l.r.r, r.integral);
                              } else {
                                    this->make<luramas::il::arch::opcodes::OP_MUL>(dest.r.r, l.r.r, r.r.r);
                              }
                              break;
                        }
                        case luramas::il::arch::data::bin_kinds::div_: {
                              if (r.tk == expr_tkind::integral) {
                                    this->make<luramas::il::arch::opcodes::OP_DIVN>(dest.r.r, l.r.r, r.integral);
                              } else {
                                    this->make<luramas::il::arch::opcodes::OP_DIV>(dest.r.r, l.r.r, r.r.r);
                              }
                              break;
                        }
                        case luramas::il::arch::data::bin_kinds::idiv_: {
                              if (r.tk == expr_tkind::integral) {
                                    this->make<luramas::il::arch::opcodes::OP_IDIVN>(dest.r.r, l.r.r, r.integral);
                              } else {
                                    this->make<luramas::il::arch::opcodes::OP_DIV>(dest.r.r, l.r.r, r.r.r);
                              }
                              break;
                        }
                        case luramas::il::arch::data::bin_kinds::mod_: {
                              if (r.tk == expr_tkind::integral) {
                                    this->make<luramas::il::arch::opcodes::OP_MODN>(dest.r.r, l.r.r, r.integral);
                              } else {
                                    this->make<luramas::il::arch::opcodes::OP_MOD>(dest.r.r, l.r.r, r.r.r);
                              }
                              break;
                        }
                        case luramas::il::arch::data::bin_kinds::pow_: {
                              if (r.tk == expr_tkind::integral) {
                                    this->make<luramas::il::arch::opcodes::OP_POWN>(dest.r.r, l.r.r, r.integral);
                              } else {
                                    this->make<luramas::il::arch::opcodes::OP_POW>(dest.r.r, l.r.r, r.r.r);
                              }
                              break;
                        }
                        case luramas::il::arch::data::bin_kinds::and_: {
                              if (r.tk == expr_tkind::integral) {
                                    this->make<luramas::il::arch::opcodes::OP_ANDN>(dest.r.r, l.r.r, r.integral);
                              } else {
                                    this->make<luramas::il::arch::opcodes::OP_AND>(dest.r.r, l.r.r, r.r.r);
                              }
                              break;
                        }
                        case luramas::il::arch::data::bin_kinds::xor_: {
                              if (r.tk == expr_tkind::integral) {
                                    this->make<luramas::il::arch::opcodes::OP_XORN>(dest.r.r, l.r.r, r.integral);
                              } else {
                                    this->make<luramas::il::arch::opcodes::OP_XOR>(dest.r.r, l.r.r, r.r.r);
                              }
                              break;
                        }
                        case luramas::il::arch::data::bin_kinds::shl_: {
                              if (r.tk == expr_tkind::integral) {
                                    this->make<luramas::il::arch::opcodes::OP_SHLN>(dest.r.r, l.r.r, r.integral);
                              } else {
                                    this->make<luramas::il::arch::opcodes::OP_SHL>(dest.r.r, l.r.r, r.r.r);
                              }
                              break;
                        }
                        case luramas::il::arch::data::bin_kinds::shr_: {
                              if (r.tk == expr_tkind::integral) {
                                    this->make<luramas::il::arch::opcodes::OP_SHRN>(dest.r.r, l.r.r, r.integral);
                              } else {
                                    this->make<luramas::il::arch::opcodes::OP_SHR>(dest.r.r, l.r.r, r.r.r);
                              }
                              break;
                        }
                        case luramas::il::arch::data::bin_kinds::or_: {
                              if (r.tk == expr_tkind::integral) {
                                    this->make<luramas::il::arch::opcodes::OP_ORN>(dest.r.r, l.r.r, r.integral);
                              } else {
                                    this->make<luramas::il::arch::opcodes::OP_OR>(dest.r.r, l.r.r, r.r.r);
                              }
                              break;
                        }
                        case luramas::il::arch::data::bin_kinds::len_: {
                              this->make<luramas::il::arch::opcodes::OP_LEN>(dest.r.r, l.r.r);
                              break;
                        }
                        case luramas::il::arch::data::bin_kinds::minus_: {
                              this->make<luramas::il::arch::opcodes::OP_MINUS>(dest.r.r, l.r.r);
                              break;
                        }
                        case luramas::il::arch::data::bin_kinds::not_: {
                              this->make<luramas::il::arch::opcodes::OP_NOT>(dest.r.r, l.r.r);
                              break;
                        }
                        case luramas::il::arch::data::bin_kinds::bitnot_: {
                              this->make<luramas::il::arch::opcodes::OP_BITNOT>(dest.r.r, l.r.r);
                              break;
                        }
                        case luramas::il::arch::data::bin_kinds::plus_: {
                              this->make<luramas::il::arch::opcodes::OP_PLUS>(dest.r.r, l.r.r);
                              break;
                        }
                        case luramas::il::arch::data::bin_kinds::ref_: {
                              this->make<luramas::il::arch::opcodes::OP_REF>(dest.r.r, l.r.r);
                              break;
                        }
                        default: {
                              luramas::error::error("Unkown binkind");
                        }
                  }
                  if (dest.tk == expr_tkind::reg && dest.r.cast) {
                        this->make_cast(dest.r.r, dest.r.r, dest.bits(), dest.r.size.unsign, dest.r.size.precision);
                  }
                  return;
            }
            template <luramas::il::arch::data::bin_kinds b>
            void make(const expr &dest, const expr &l, const std::intptr_t i) {
                  this->make<b>(dest, l, expr(shared_from_this(), i));
                  return;
            }

            template <luramas::il::arch::data::flags f>
            void set_flag() {
                  this->make<luramas::il::arch::opcodes::OP_SETFLAG>(static_cast<std::intptr_t>(f));
                  return;
            }

            std::shared_ptr<disassembly> find_original_map(const profile::module_id mid, const luramas_address loc);

            /* Pages */
            void page_retn();
            void page_retn(const luramas_register ret_reg, const luramas_address loc);
            void page_call(const profile::module_id mid, const luramas_address loc, const expr &r, const std::intptr_t v);
            void page_jump(const profile::module_id mid, const luramas_address loc);

            void make_goto(const profile::module_id mid, const luramas_address loc);
            void make_non_direct_goto(const expr &value, const profile::module_id mid, const luramas_address loc, const std::uintptr_t segregation = LURAMAS_IR_DEFAULT_SEGREGATION_ID);
            void non_direct_page_call(const expr &value, const profile::module_id mid, const luramas_address loc, const expr &r, const std::intptr_t val, const std::uintptr_t segregation = LURAMAS_IR_DEFAULT_SEGREGATION_ID);
            void non_direct_page_jmp(const expr &value, const profile::module_id mid, const luramas_address loc, const std::uintptr_t segregation = LURAMAS_IR_DEFAULT_SEGREGATION_ID);
            void external_page_call(const std::string &name, const std::vector<expr> &args, const std::vector<expr> &results);
            void non_direct_external_page_call(const expr &value, const luramas_address loc, const std::string &name, const std::vector<expr> &args, const std::vector<expr> &results, const std::uintptr_t segregation = LURAMAS_IR_DEFAULT_SEGREGATION_ID);
            void external_page_jmp(const luramas_address loc);
            void non_direct_external_page_jmp(const expr &value, const luramas_address loc, const std::uintptr_t segregation = LURAMAS_IR_DEFAULT_SEGREGATION_ID);

            /* If you create a scope you need to only insert values here so it can keep track of it. */
            template <luramas::il::arch::data::bin_kinds b = luramas::il::arch::data::bin_kinds::nothing>
            void make_scope(const std::uintptr_t segregation = LURAMAS_IR_DEFAULT_SEGREGATION_ID) {

                  if (segregation) {
                        this->make<arch::opcodes::OP_SEGREGATE>(segregation);
                  }
                  this->opened_conditions.emplace_back(this->make(il::arch::data::bin_kindflip(b)));
                  return;
            }

            void make_goto(const std::uintptr_t ID);
            void make_label(const std::uintptr_t ID);
            std::shared_ptr<luramas::il::disassembly> make(const luramas::il::arch::data::bin_kinds b);
            void make_else();
            void close_scope(const bool input = false, luramas_address loc = 0u);
            void make_do();
            expr make_reg(const luramas_register r);
            void make_load(const std::uint64_t flag_id, const expr &reg);
            void make_load(const expr &reg, const std::intptr_t i);
            void set_global(const std::string &str, const expr &reg);
            void make_global(const expr &reg, const std::string &str);
            void make_string(const expr &reg, const std::string &str);
            void make_value(const reg &reg, const double v);
            void make_flag_load(const expr &reg, const std::intptr_t i, const luramas_bitwidth bits = 1u, const bool unsign = false, const luramas_bitwidth precision = 0u);
            void make_cast(const luramas_register dest, const luramas_register src, const luramas_bitwidth bits, const bool unsign = false, const luramas_bitwidth precision = 0u);
            expr make_temp(const expr &reg);
            expr make_temp(const types::underlying_type &size);
            void make_call(const std::string &func, const std::vector<expr> &args, const std::vector<expr> &results = std::vector<expr>());
            void make_call(const std::string &func, const expr &result);
            expr make_standard_call(const builtin::func &default_func, const std::vector<std::pair<types::native::compiler::object, build::expr>> &sources, const std::vector<std::pair<types::native::compiler::object, build::expr>> &dests);
            expr make_built_in(const builtin::inst &data, const std::vector<build::expr> &operands, const flag_vector &flags);
            void make_lura_built_in(const builtins::data::func &f, const std::vector<expr> &args, const std::vector<expr> &results = std::vector<expr>());
            void set_internal_global(const std::string &str, const expr &reg);
            void load_internal_global(const std::string &str, const expr &reg);

            luramas_id set_global(const std::string &global);

            void insert(const std::vector<std::shared_ptr<luramas::il::disassembly>> &v);
            void insert(const std::shared_ptr<luramas::il::disassembly> &v);

            expr make_var(const luramas_register r, const luramas_bitwidth bits, const bool unsign = false, const std::uint8_t precision = 0u);
            reg get_temp();
            expr make_temp();

            void violation(const expr &l) const;
            void precomputed();

            /* Bit */
            expr make_bitread(const expr &value, const expr &min, const expr &max);
            expr make_bitwrite(const expr &dest, const expr &src, const expr &min, const expr &max);

            void make_push(const expr &e, const std::uint32_t ID = LURAMAS_IR_DEFAULT_STACK_ID) {
                  auto temp = this->make_temp(e);
                  this->make<arch::opcodes::OP_STACKPUSH>(ID, temp.r.r);
                  return;
            }
            void make_pop(const expr &e, const std::uint32_t ID = LURAMAS_IR_DEFAULT_STACK_ID) {
                  auto temp = this->make_temp(e);
                  this->make<arch::opcodes::OP_STACKPOP>(ID, temp.r.r);
                  return;
            }
            void make_pop(const std::uint32_t ID = LURAMAS_IR_DEFAULT_STACK_ID) {
                  this->make<arch::opcodes::OP_POPTOPSTACK>(ID);
                  return;
            }
            void make_page(const std::intptr_t ID) {
                  this->opended_pages.emplace_back(ID);
                  this->make<arch::opcodes::OP_STARTPAGEFUNC>(ID);
                  return;
            }
            void page_return() {
                  this->make<arch::opcodes::OP_PRETURN>();
                  return;
            }
            void clear() {
                  *this = build();
                  return;
            }
            void close_page() {
                  if (this->opended_pages.empty()) {
                        luramas::error::error("No opened pages to close");
                  }
                  this->make<arch::opcodes::OP_ENDPAGEFUNC>(this->opended_pages.back());
                  this->opended_pages.pop_back();
                  return;
            }
            void reinit(const luramas_address pc, const luramas_address idx, const luramas_register temp, const std::shared_ptr<luramas::il::ilang> &il, const std::shared_ptr<luramas::il::disassembly> &current) {
                  this->idx = idx;
                  this->pc = pc;
                  this->il = il;
                  this->current = current;
                  this->temp = temp;
                  this->constant.clear();
                  this->labels.clear();
                  return;
            }

            template <arch::opcodes op>
            void mut(const std::int64_t A = 0ll, const std::int64_t B = 0ll, const std::int64_t C = 0ll, const std::int64_t D = 0ll, const std::int64_t E = 0ll) {
                  luramas::il::emitter::emit_opcode<op>(this->il, this->pc, this->current, A, B, C, D, E);
                  return;
            }
            void cmp(const expr &e, const std::uintptr_t segregation = LURAMAS_IR_DEFAULT_SEGREGATION_ID) {
                  build::expr rv;
                  switch (e.tk) {
                        case expr_tkind::flag: {
                              rv.emit(e.b, e.b->get_temp());
                              rv.b->make<arch::opcodes::OP_FLAGREAD>(e.r.r, e.integral);
                              rv.cast(1u, true);
                              break;
                        }
                        case expr_tkind::integral: {
                              auto temp = e.b->get_temp();
                              e.b->make<arch::opcodes::OP_LOADINT>(temp.r, e.integral);
                              rv.emit(e.b, temp);
                              break;
                        }
                        default: {
                              rv.emit(e);
                              break;
                        }
                  }
                  this->make<arch::opcodes::OP_SEGREGATE>(segregation);
                  this->make<arch::opcodes::OP_CMPS>(rv.r.r);
                  return;
            }
            bool is_page_loc(const profile::module_id mid, const profile::address addr) const {
                  if (const auto it = this->details.find(mid); it != this->details.end()) {
                        return it->second.pages.contains(addr);
                  }
                  return false;
            }

            boost::unordered_flat_map<luramas_register, luramas_register_contents> constant;
            luramas_address idx = 0u;
            luramas_address pc = 0u;
            std::shared_ptr<luramas::il::ilang> il = nullptr;
            std::shared_ptr<luramas::il::disassembly> current = nullptr;
            boost::unordered_flat_map<profile::module_id, profile::analyze::details> details;
            boost::unordered_flat_map<profile::module_id, boost::unordered_flat_map<luramas_address, std::shared_ptr<disassembly>>> original_address_data;
            std::uint8_t suggested_bit_set = 0u;

          private:
            luramas_register temp = 0u;
            std::vector<std::intptr_t> opended_pages;
            std::vector<std::shared_ptr<luramas::il::disassembly>> opened_conditions;
            boost::unordered_flat_map<luramas_address, std::shared_ptr<luramas::il::disassembly>> labels;
            boost::unordered_flat_map<std::string, luramas_id> globals;
      };

      template <typename inst_T, typename regs_T, typename flags_T>
      struct registrar {

            registrar(const inst_T inst, const std::shared_ptr<build> &build, const luramas::profile::externals::data<regs_T> &externals, const std::uint8_t suggested_bit_set, const luramas::profile::inst_bytes &bytes = {})
                : inst(inst), build(build), suggested_bit_set(suggested_bit_set), bytes(bytes), externals(externals) {
                  return;
            }

            inline void clear() {
                  this->flags.clear();
                  this->regs.clear();
                  return;
            }

            /* Get */
            template <regs_T r>
            inline build::expr getr() const {
                  return this->regs.at(static_cast<std::size_t>(r));
            }
            template <flags_T r>
            inline build::expr getf() const {
                  return this->flags.at(static_cast<std::size_t>(r));
            }

            /* Set */
            template <regs_T r>
            inline constexpr void setr(const build::expr &expr) {
                  this->regs.try_emplace(static_cast<std::size_t>(r), expr);
                  return;
            }
            template <flags_T r>
            inline constexpr void setf(const build::expr &expr) {
                  this->flags.try_emplace(static_cast<std::size_t>(r), expr);
                  return;
            }
            inline constexpr void setr(const regs_T r, const build::expr &expr) {
                  this->regs.try_emplace(static_cast<std::size_t>(r), expr);
                  return;
            }

            /* Zero out */
            inline void zero_regs() {
                  for (auto &[t, expr] : this->regs) {
                        expr = 0u;
                  }
                  return;
            }
            inline void zero_flags() {
                  for (auto &[t, expr] : this->flags) {
                        expr = 0u;
                  }
                  return;
            }

            inline std::vector<profile::inst> get_details() const {

                  std::vector<profile::inst> result;

                  if (this->original.first.cmp(this->bytes)) {
                        result.emplace_back(this->original.first);
                  }
                  if (this->original.discrepancies) {
                        for (const auto &i : *this->original.discrepancies) {
                              if (i.cmp(this->bytes)) {
                                    result.emplace_back(i);
                              }
                        }
                  }
                  return result;
            }
            inline std::vector<build::expr> get(const std::vector<regs_T> &regs) const {

                  std::vector<build::expr> result;
                  result.reserve(regs.size());
                  for (const auto &i : regs) {
                        if (const auto it = this->regs.find(static_cast<std::size_t>(i)); it != this->regs.end()) {
                              result.emplace_back(it->second);
                        }
                  }
                  return result;
            }

            /* Data */
            inst_T inst;
            std::shared_ptr<build> build = nullptr;
            std::uint8_t suggested_bit_set = 0u;
            luramas::profile::inst_bytes bytes;
            luramas::profile::real_inst original;
            luramas::profile::externals::data<regs_T> externals;
            boost::unordered_flat_map<std::size_t, build::expr> regs;
            boost::unordered_flat_map<std::size_t, build::expr> flags;
      };

      template <std::size_t N, typename... EXPS>
      void cast(EXPS &...exprs) {
            static_assert(sizeof...(exprs) > 0u, "requires at least one expr");

            ((
                 exprs = exprs.cast(types::underlying_type(false, types::read_type::bits, 0u, N))),
                ...);
            return;
      }

} // namespace luramas::il::lifter::builder

/* BUILDER HELPER FUNCTIONS */

#define LURAMAS_FBUILD_SIGNMASK(expr) (1ull >> ((expr).bits() - 1u))
#define LURAMAS_FBUILD_SIGNBIT(expr) (((expr) >> ((expr).bits() - 1u)) & 1u)
#define LURAMAS_FBUILD_EXTENDLONGDOUBLE(expr) ((expr).cast(luramas::types::native::t_ldouble))
#define LURAMAS_FBUILD_CONVERT_TO_INTEGER(expr) ((expr).cast(luramas::types::native::t_int32))
#define LURAMAS_FBUILD_SIGNEXTEND(expr) ((((expr) & ((1 << (expr.bits())) - 1)) ^ (1 << ((expr).bits() - 1))) - (1 << ((expr).bits() - 1)))
#define LURAMAS_FBUILD_ZEROEXTEND(expr, size_expr) ((expr).cast((size_expr).r.size))
#define LURAMAS_FBUILD_UPPER_BITS(expr) ((expr) >> (((expr).bits()) / 2))
#define LURAMAS_FBUILD_LOWER_BITS(expr) ((expr) & ((1ULL << (((expr).bits()) / 2)) - 1))
#define LURAMAS_FBUILD_PAIR(expr, expr1, unsign) ((((expr) << ((expr).bits())) | (expr1)).cast(luramas::types::underlying_type(unsign, luramas::types::read_type::bits, 0u, expr.bits() + expr1.bits())))
#define LURAMAS_FBUILD_UPAIR(expr, expr1) (LURAMAS_FBUILD_PAIR((expr), (expr1), true))
#define LURAMAS_FBUILD_SPAIR(expr, expr1) (LURAMAS_FBUILD_PAIR((expr), (expr1), false))
#define LURAMAS_FBUILD_EXTEND_U1024(expr) ((expr).cast(luramas::types::native::t_uint1024))
#define LURAMAS_FBUILD_EXTEND_U512(expr) ((expr).cast(luramas::types::native::t_uint512))
#define LURAMAS_FBUILD_EXTEND_U256(expr) ((expr).cast(luramas::types::native::t_uint256))
#define LURAMAS_FBUILD_EXTEND_U128(expr) ((expr).cast(luramas::types::native::t_uint128))
#define LURAMAS_FBUILD_EXTEND_U64(expr) ((expr).cast(luramas::types::native::t_uint64))
#define LURAMAS_FBUILD_EXTEND_U32(expr) ((expr).cast(luramas::types::native::t_uint32))
#define LURAMAS_FBUILD_EXTEND_U16(expr) ((expr).cast(luramas::types::native::t_uint16))
#define LURAMAS_FBUILD_EXTEND_U8(expr) ((expr).cast(luramas::types::native::t_uint8))
#define LURAMAS_FBUILD_EXTEND_1024(expr) ((expr).cast(luramas::types::native::t_int1024))
#define LURAMAS_FBUILD_EXTEND_512(expr) ((expr).cast(luramas::types::native::t_int512))
#define LURAMAS_FBUILD_EXTEND_256(expr) ((expr).cast(luramas::types::native::t_int256))
#define LURAMAS_FBUILD_EXTEND_128(expr) ((expr).cast(luramas::types::native::t_int128))
#define LURAMAS_FBUILD_EXTEND_64(expr) ((expr).cast(luramas::types::native::t_int64))
#define LURAMAS_FBUILD_EXTEND_32(expr) ((expr).cast(luramas::types::native::t_int32))
#define LURAMAS_FBUILD_EXTEND_16(expr) ((expr).cast(luramas::types::native::t_int16))
#define LURAMAS_FBUILD_EXTEND_8(expr) ((expr).cast(luramas::types::native::t_int8))
#define LURAMAS_FBUILD_EXTEND_FLOAT(expr) ((expr).cast(luramas::types::native::t_float))
#define LURAMAS_FBUILD_EXTEND_DOUBLE(expr) ((expr).cast(luramas::types::native::t_double))