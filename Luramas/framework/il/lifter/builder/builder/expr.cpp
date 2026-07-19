#include "../builder.hpp"
#include <ranges>

namespace luramas::il::lifter::builder {

      void build::expr::emit(const expr &other) {
            this->b = other.b;
            this->tk = other.tk;
            switch (other.tk) {
                  case expr_tkind::global: {
                        this->id = other.id;
                        break;
                  }
                  case expr_tkind::value: {
                        this->v = other.v;
                        break;
                  }
                  case expr_tkind::reg: {
                        this->r = other.r;
                        break;
                  }
                  default: {
                        this->integral = other.integral;
                        break;
                  }
            }
            return;
      }
      void build::expr::emit(const std::shared_ptr<build> &b, const reg &r, const bool castable) {
            this->b = b;
            this->r = r;
            this->tk = expr_tkind::reg;
            this->r.cast = castable;
            return;
      }
      void build::expr::emit(const std::shared_ptr<build> &b, const std::intptr_t integral) {
            this->tk = expr_tkind::integral;
            this->b = b;
            this->integral = integral;
            return;
      }
      void build::expr::emit_flag(const std::shared_ptr<build> &b, const std::intptr_t flag) {
            this->tk = expr_tkind::flag;
            this->b = b;
            this->integral = flag;
            return;
      }
      void build::expr::emit_stack(const std::shared_ptr<build> &b, const std::intptr_t stack_id) {
            this->tk = expr_tkind::stack;
            this->b = b;
            this->integral = stack_id;
            return;
      }
      void build::expr::emit_mem(const std::shared_ptr<build> &b, const reg &r) {
            this->tk = expr_tkind::memory;
            this->b = b;
            this->r = r;
            return;
      }
      void build::expr::emit_global(const std::shared_ptr<build> &b, const std::string &global) {
            this->tk = expr_tkind::global;
            this->id = this->b->set_global(global);
            return;
      }
      void build::expr::emit_value(const std::shared_ptr<build> &b, const double v) {
            this->tk = expr_tkind::value;
            this->v = v;
            this->b = b;
            return;
      }

      template <arch::data::bin_kinds b>
      build::expr evaluate(const build::expr &l, const build::expr &r = build::expr(), const bool setcond = true) {
            build::expr lv;
            build::expr rv;
            build::expr result(l.b, l.b->get_temp());
            switch (l.tk) {
                  case expr_tkind::memory: {
                        lv.emit(l.b, l.b->get_temp());
                        l.b->make<arch::opcodes::OP_MEMREAD>(lv.r.r, l.r.r, l.bits());
                        break;
                  }
                  case expr_tkind::integral: {
                        auto temp = l.b->get_temp();
                        l.b->make<arch::opcodes::OP_LOADINT>(temp.r, l.integral);
                        lv.emit(l.b, temp);
                        break;
                  }
                  case expr_tkind::value: {
                        auto temp = l.b->get_temp();
                        l.b->make_value(temp, l.v);
                        lv.emit(l.b, temp);
                        break;
                  }
                  case expr_tkind::reg: {
                        lv.emit(l);
                        break;
                  }
                  case expr_tkind::global: {
                        lv.emit(l.b, l.b->get_temp());
                        l.b->make<arch::opcodes::OP_LOADGLOBAL>(lv.r.r, l.id);
                        if (l.f.fglobal_wild) {
                              l.b->set_flag<il::arch::data::flags::fwild_global>();
                        }
                        break;
                  }
                  case expr_tkind::flag: {
                        lv.emit(l.b, l.b->get_temp());
                        l.b->make<arch::opcodes::OP_FLAGREAD>(lv.r.r, l.integral);
                        break;
                  }
                  case expr_tkind::stack: {
                        lv.emit(l.b, l.b->get_temp());
                        l.b->make<luramas::il::arch::opcodes::OP_GETSTACK>(lv.r.r, l.integral);
                        break;
                  }
                  default: {
                        break;
                  }
            }
            switch (r.tk) {
                  case expr_tkind::flag: {
                        rv.emit(l.b, l.b->get_temp());
                        l.b->make<arch::opcodes::OP_FLAGREAD>(rv.r.r, r.integral);
                        rv.cast(1u, true);
                        break;
                  }
                  case expr_tkind::global: {
                        rv.emit(l.b, l.b->get_temp());
                        l.b->make<arch::opcodes::OP_LOADGLOBAL>(rv.r.r, r.id);
                        if (r.f.fglobal_wild) {
                              l.b->set_flag<il::arch::data::flags::fwild_global>();
                        }
                        break;
                  }
                  case expr_tkind::value: {
                        auto temp = l.b->get_temp();
                        l.b->make_value(temp, r.v);
                        rv.emit(l.b, temp);
                        break;
                  }
                  case expr_tkind::stack: {
                        rv.emit(l.b, l.b->get_temp());
                        l.b->make<arch::opcodes::OP_GETSTACK>(rv.r.r, r.integral);
                        break;
                  }
                  default: {
                        rv.emit(r);
                        break;
                  }
            }
            if (l.tk == expr_tkind::reg || l.tk == expr_tkind::memory) {
                  result.r.size.dominant(l.r.size);
            }
            if (r.tk == expr_tkind::reg || r.tk == expr_tkind::memory) {
                  result.r.size.dominant(r.r.size);
            }
            switch (r.tk) {
                  case expr_tkind::integral: {
                        switch (b) {
                              case arch::data::bin_kinds::add_: {
                                    l.b->make<arch::opcodes::OP_ADDN>(result.r.r, lv.r.r, rv.integral);
                                    break;
                              }
                              case arch::data::bin_kinds::sub_: {
                                    l.b->make<arch::opcodes::OP_SUBN>(result.r.r, lv.r.r, rv.integral);
                                    break;
                              }
                              case arch::data::bin_kinds::mul_: {
                                    l.b->make<arch::opcodes::OP_MULN>(result.r.r, lv.r.r, rv.integral);
                                    break;
                              }
                              case arch::data::bin_kinds::div_: {
                                    l.b->make<arch::opcodes::OP_DIVN>(result.r.r, lv.r.r, rv.integral);
                                    break;
                              }
                              case arch::data::bin_kinds::idiv_: {
                                    l.b->make<arch::opcodes::OP_IDIVN>(result.r.r, lv.r.r, rv.integral);
                                    break;
                              }
                              case arch::data::bin_kinds::mod_: {
                                    l.b->make<arch::opcodes::OP_MODN>(result.r.r, lv.r.r, rv.integral);
                                    break;
                              }
                              case arch::data::bin_kinds::pow_: {
                                    l.b->make<arch::opcodes::OP_POWN>(result.r.r, lv.r.r, rv.integral);
                                    break;
                              }
                              case arch::data::bin_kinds::and_: {
                                    l.b->make<arch::opcodes::OP_ANDN>(result.r.r, lv.r.r, rv.integral);
                                    break;
                              }
                              case arch::data::bin_kinds::xor_: {
                                    l.b->make<arch::opcodes::OP_XORN>(result.r.r, lv.r.r, rv.integral);
                                    break;
                              }
                              case arch::data::bin_kinds::shl_: {
                                    l.b->make<arch::opcodes::OP_SHLN>(result.r.r, lv.r.r, rv.integral);
                                    break;
                              }
                              case arch::data::bin_kinds::shr_: {
                                    l.b->make<arch::opcodes::OP_SHRN>(result.r.r, lv.r.r, rv.integral);
                                    break;
                              }
                              case arch::data::bin_kinds::or_: {
                                    l.b->make<arch::opcodes::OP_ORN>(result.r.r, lv.r.r, rv.integral);
                                    break;
                              }
                              case arch::data::bin_kinds::eq_: {
                                    l.b->make<arch::opcodes::OP_SEGREGATE>(1u);
                                    l.b->make<arch::opcodes::OP_CMPN>(lv.r.r, rv.integral);
                                    if (setcond) {
                                          l.b->make<arch::opcodes::OP_SEGREGATE>(1u);
                                          l.b->make<arch::opcodes::OP_SETIFEQUAL>(result.r.r);
                                    }
                                    break;
                              }
                              case arch::data::bin_kinds::ne_: {
                                    l.b->make<arch::opcodes::OP_SEGREGATE>(1u);
                                    l.b->make<arch::opcodes::OP_CMPN>(lv.r.r, rv.integral);
                                    if (setcond) {
                                          l.b->make<arch::opcodes::OP_SEGREGATE>(1u);
                                          l.b->make<arch::opcodes::OP_SETIFNOTEQUAL>(result.r.r);
                                    }
                                    break;
                              }
                              case arch::data::bin_kinds::lt_: {
                                    l.b->make<arch::opcodes::OP_SEGREGATE>(1u);
                                    l.b->make<arch::opcodes::OP_CMPN>(lv.r.r, rv.integral);
                                    if (setcond) {
                                          l.b->make<arch::opcodes::OP_SEGREGATE>(1u);
                                          l.b->make<arch::opcodes::OP_SETIFLESS>(result.r.r);
                                    }
                                    break;
                              }
                              case arch::data::bin_kinds::lte_: {
                                    l.b->make<arch::opcodes::OP_SEGREGATE>(1u);
                                    l.b->make<arch::opcodes::OP_CMPN>(lv.r.r, rv.integral);
                                    if (setcond) {
                                          l.b->make<arch::opcodes::OP_SEGREGATE>(1u);
                                          l.b->make<arch::opcodes::OP_SETIFLESSEQUAL>(result.r.r);
                                    }
                                    break;
                              }
                              case arch::data::bin_kinds::gt_: {
                                    l.b->make<arch::opcodes::OP_SEGREGATE>(1u);
                                    l.b->make<arch::opcodes::OP_CMPN>(lv.r.r, rv.integral);
                                    if (setcond) {
                                          l.b->make<arch::opcodes::OP_SEGREGATE>(1u);
                                          l.b->make<arch::opcodes::OP_SETIFGREATER>(result.r.r);
                                    }
                                    break;
                              }
                              case arch::data::bin_kinds::gte_: {
                                    l.b->make<arch::opcodes::OP_SEGREGATE>(1u);
                                    l.b->make<arch::opcodes::OP_CMPN>(lv.r.r, rv.integral);
                                    if (setcond) {
                                          l.b->make<arch::opcodes::OP_SEGREGATE>(1u);
                                          l.b->make<arch::opcodes::OP_SETIFGREATEREQUAL>(result.r.r);
                                    }
                                    break;
                              }
                              case arch::data::bin_kinds::nt_: {
                                    l.b->make<arch::opcodes::OP_SEGREGATE>(1u);
                                    l.b->make<arch::opcodes::OP_CMPN>(lv.r.r, rv.integral);
                                    if (setcond) {
                                          l.b->make<arch::opcodes::OP_SEGREGATE>(1u);
                                          l.b->make<arch::opcodes::OP_SETIFNOT>(result.r.r);
                                    }
                                    break;
                              }
                              case arch::data::bin_kinds::et_: {
                                    l.b->make<arch::opcodes::OP_SEGREGATE>(1u);
                                    l.b->make<arch::opcodes::OP_CMPN>(lv.r.r, rv.integral);
                                    if (setcond) {
                                          l.b->make<arch::opcodes::OP_SEGREGATE>(1u);
                                          l.b->make<arch::opcodes::OP_SETIF>(result.r.r);
                                    }
                                    break;
                              }
                              default: {
                                    break;
                              }
                        }
                        break;
                  }
                  default: {
                        switch (b) {
                              case arch::data::bin_kinds::add_: {
                                    l.b->make<arch::opcodes::OP_ADD>(result.r.r, lv.r.r, rv.r.r);
                                    break;
                              }
                              case arch::data::bin_kinds::sub_: {
                                    l.b->make<arch::opcodes::OP_SUB>(result.r.r, lv.r.r, rv.r.r);
                                    break;
                              }
                              case arch::data::bin_kinds::mul_: {
                                    l.b->make<arch::opcodes::OP_MUL>(result.r.r, lv.r.r, rv.r.r);
                                    break;
                              }
                              case arch::data::bin_kinds::div_: {
                                    l.b->make<arch::opcodes::OP_DIV>(result.r.r, lv.r.r, rv.r.r);
                                    break;
                              }
                              case arch::data::bin_kinds::idiv_: {
                                    l.b->make<arch::opcodes::OP_IDIV>(result.r.r, lv.r.r, rv.r.r);
                                    break;
                              }
                              case arch::data::bin_kinds::mod_: {
                                    l.b->make<arch::opcodes::OP_MOD>(result.r.r, lv.r.r, rv.r.r);
                                    break;
                              }
                              case arch::data::bin_kinds::pow_: {
                                    l.b->make<arch::opcodes::OP_POW>(result.r.r, lv.r.r, rv.r.r);
                                    break;
                              }
                              case arch::data::bin_kinds::and_: {
                                    l.b->make<arch::opcodes::OP_AND>(result.r.r, lv.r.r, rv.r.r);
                                    break;
                              }
                              case arch::data::bin_kinds::xor_: {
                                    l.b->make<arch::opcodes::OP_XOR>(result.r.r, lv.r.r, rv.r.r);
                                    break;
                              }
                              case arch::data::bin_kinds::shl_: {
                                    l.b->make<arch::opcodes::OP_SHL>(result.r.r, lv.r.r, rv.r.r);
                                    break;
                              }
                              case arch::data::bin_kinds::shr_: {
                                    l.b->make<arch::opcodes::OP_SHR>(result.r.r, lv.r.r, rv.r.r);
                                    break;
                              }
                              case arch::data::bin_kinds::or_: {
                                    l.b->make<arch::opcodes::OP_OR>(result.r.r, lv.r.r, rv.r.r);
                                    break;
                              }
                              case arch::data::bin_kinds::len_: {
                                    l.b->make<arch::opcodes::OP_LEN>(result.r.r, lv.r.r);
                                    break;
                              }
                              case arch::data::bin_kinds::minus_: {
                                    l.b->make<arch::opcodes::OP_MINUS>(result.r.r, lv.r.r);
                                    break;
                              }
                              case arch::data::bin_kinds::not_: {
                                    l.b->make<arch::opcodes::OP_NOT>(result.r.r, lv.r.r);
                                    break;
                              }
                              case arch::data::bin_kinds::bitnot_: {
                                    l.b->make<arch::opcodes::OP_BITNOT>(result.r.r, lv.r.r);
                                    break;
                              }
                              case arch::data::bin_kinds::plus_: {
                                    l.b->make<arch::opcodes::OP_PLUS>(result.r.r, lv.r.r);
                                    break;
                              }
                              case arch::data::bin_kinds::ref_: {
                                    l.b->make<arch::opcodes::OP_REF>(result.r.r, lv.r.r);
                                    break;
                              }
                              case arch::data::bin_kinds::eq_: {
                                    l.b->make<arch::opcodes::OP_SEGREGATE>(1u);
                                    l.b->make<arch::opcodes::OP_CMP>(lv.r.r, rv.r.r);
                                    if (setcond) {
                                          l.b->make<arch::opcodes::OP_SEGREGATE>(1u);
                                          l.b->make<arch::opcodes::OP_SETIFEQUAL>(result.r.r);
                                    }
                                    break;
                              }
                              case arch::data::bin_kinds::ne_: {
                                    l.b->make<arch::opcodes::OP_SEGREGATE>(1u);
                                    l.b->make<arch::opcodes::OP_CMP>(lv.r.r, rv.r.r);
                                    if (setcond) {
                                          l.b->make<arch::opcodes::OP_SEGREGATE>(1u);
                                          l.b->make<arch::opcodes::OP_SETIFNOTEQUAL>(result.r.r);
                                    }
                                    break;
                              }
                              case arch::data::bin_kinds::lt_: {
                                    l.b->make<arch::opcodes::OP_SEGREGATE>(1u);
                                    l.b->make<arch::opcodes::OP_CMP>(lv.r.r, rv.r.r);
                                    if (setcond) {
                                          l.b->make<arch::opcodes::OP_SEGREGATE>(1u);
                                          l.b->make<arch::opcodes::OP_SETIFLESS>(result.r.r);
                                    }
                                    break;
                              }
                              case arch::data::bin_kinds::lte_: {
                                    l.b->make<arch::opcodes::OP_SEGREGATE>(1u);
                                    l.b->make<arch::opcodes::OP_CMP>(lv.r.r, rv.r.r);
                                    if (setcond) {
                                          l.b->make<arch::opcodes::OP_SEGREGATE>(1u);
                                          l.b->make<arch::opcodes::OP_SETIFLESSEQUAL>(result.r.r);
                                    }
                                    break;
                              }
                              case arch::data::bin_kinds::gt_: {
                                    l.b->make<arch::opcodes::OP_SEGREGATE>(1u);
                                    l.b->make<arch::opcodes::OP_CMP>(lv.r.r, rv.r.r);
                                    if (setcond) {
                                          l.b->make<arch::opcodes::OP_SEGREGATE>(1u);
                                          l.b->make<arch::opcodes::OP_SETIFGREATER>(result.r.r);
                                    }
                                    break;
                              }
                              case arch::data::bin_kinds::gte_: {
                                    l.b->make<arch::opcodes::OP_SEGREGATE>(1u);
                                    l.b->make<arch::opcodes::OP_CMP>(lv.r.r, rv.r.r);
                                    if (setcond) {
                                          l.b->make<arch::opcodes::OP_SEGREGATE>(1u);
                                          l.b->make<arch::opcodes::OP_SETIFGREATEREQUAL>(result.r.r);
                                    }
                                    break;
                              }
                              case arch::data::bin_kinds::nt_: {
                                    l.b->make<arch::opcodes::OP_SEGREGATE>(1u);
                                    l.b->make<arch::opcodes::OP_CMP>(lv.r.r, rv.r.r);
                                    if (setcond) {
                                          l.b->make<arch::opcodes::OP_SEGREGATE>(1u);
                                          l.b->make<arch::opcodes::OP_SETIFNOT>(result.r.r);
                                    }
                                    break;
                              }
                              case arch::data::bin_kinds::et_: {
                                    l.b->make<arch::opcodes::OP_SEGREGATE>(1u);
                                    l.b->make<arch::opcodes::OP_CMP>(lv.r.r, rv.r.r);
                                    if (setcond) {
                                          l.b->make<arch::opcodes::OP_SEGREGATE>(1u);
                                          l.b->make<arch::opcodes::OP_SETIF>(result.r.r);
                                    }
                                    break;
                              }
                              default: {
                                    break;
                              }
                        }
                        break;
                  }
            }
            if (result.bits()) {
                  result.cast(result.r);
            }
            return result;
      }
      build::expr build::expr::operator+(const expr &other) const {
            return evaluate<arch::data::bin_kinds::add_>(*this, other);
      }
      build::expr build::expr::operator-(const expr &other) const {
            return evaluate<arch::data::bin_kinds::sub_>(*this, other);
      }
      build::expr build::expr::operator*(const expr &other) const {
            return evaluate<arch::data::bin_kinds::mul_>(*this, other);
      }
      build::expr build::expr::operator/(const expr &other) const {
            return evaluate<arch::data::bin_kinds::div_>(*this, other);
      }
      build::expr build::expr::operator&(const expr &other) const {
            return evaluate<arch::data::bin_kinds::and_>(*this, other);
      }
      build::expr build::expr::operator|(const expr &other) const {
            return evaluate<arch::data::bin_kinds::or_>(*this, other);
      }
      build::expr build::expr::operator^(const expr &other) const {
            return evaluate<arch::data::bin_kinds::xor_>(*this, other);
      }
      build::expr build::expr::operator%(const expr &other) const {
            return evaluate<arch::data::bin_kinds::mod_>(*this, other);
      }
      build::expr build::expr::operator<<(const expr &other) const {
            return evaluate<arch::data::bin_kinds::shl_>(*this, other);
      }
      build::expr build::expr::operator>>(const expr &other) const {
            return evaluate<arch::data::bin_kinds::shr_>(*this, other);
      }
      build::expr build::expr::operator==(const expr &other) const {
            return evaluate<arch::data::bin_kinds::eq_>(*this, other);
      }
      build::expr build::expr::operator!=(const expr &other) const {
            return evaluate<arch::data::bin_kinds::ne_>(*this, other);
      }
      build::expr build::expr::operator<(const expr &other) const {
            return evaluate<arch::data::bin_kinds::lt_>(*this, other);
      }
      build::expr build::expr::operator<=(const expr &other) const {
            return evaluate<arch::data::bin_kinds::lte_>(*this, other);
      }
      build::expr build::expr::operator>(const expr &other) const {
            return evaluate<arch::data::bin_kinds::gt_>(*this, other);
      }
      build::expr build::expr::operator>=(const expr &other) const {
            return evaluate<arch::data::bin_kinds::gte_>(*this, other);
      }
      build::expr build::expr::operator~() const {
            return evaluate<arch::data::bin_kinds::bitnot_>(*this);
      }
      build::expr build::expr::operator!() const {
            return evaluate<arch::data::bin_kinds::not_>(*this);
      }
      build::expr build::expr::operator-() const {
            return evaluate<arch::data::bin_kinds::minus_>(*this);
      }
      build::expr build::expr::operator+() const {
            return evaluate<arch::data::bin_kinds::plus_>(*this);
      }
      build::expr build::expr::operator[](const build::expr &offset) const {
            return this->read(offset, offset + 1u);
      }

      build::expr build::expr::operator=(const expr &other) const {
            build::expr rv;
            switch (other.tk) {
                  case expr_tkind::flag: {
                        rv.emit(other.b, other.b->get_temp());
                        rv.b->make<arch::opcodes::OP_FLAGREAD>(other.r.r, other.integral);
                        rv.cast(1u, true);
                        break;
                  }
                  case expr_tkind::integral: {
                        auto temp = other.b->get_temp();
                        other.b->make<arch::opcodes::OP_LOADINT>(temp.r, other.integral);
                        rv.emit(other.b, temp);
                        break;
                  }
                  case expr_tkind::value: {
                        auto temp = other.b->get_temp();
                        other.b->make_value(temp, other.v);
                        rv.emit(other.b, temp.r);
                        break;
                  }
                  case expr_tkind::global: {
                        auto temp = other.b->get_temp();
                        other.b->make<arch::opcodes::OP_LOADGLOBAL>(temp.r, other.id);
                        if (other.f.fglobal_wild) {
                              other.b->set_flag<il::arch::data::flags::fwild_global>();
                        }
                        rv.emit(other.b, temp);
                        break;
                  }
                  case expr_tkind::reg: {
                        rv.emit(other);
                        if (other.bits()) {
                              rv.cast(other.r);
                        }
                        break;
                  }
                  case expr_tkind::memory: {
                        rv.emit(other.b, other.b->get_temp());
                        rv.b->make<arch::opcodes::OP_MEMREAD>(rv.r.r, other.r.r, other.bits());
                        break;
                  }
                  case expr_tkind::stack: {
                        rv.emit(other.b, other.b->get_temp());
                        rv.b->make<luramas::il::arch::opcodes::OP_GETSTACK>(rv.r.r, other.integral);
                        break;
                  }
                  default: {
                        break;
                  }
            }
            switch (this->tk) {
                  case expr_tkind::reg: {
                        this->b->make<arch::opcodes::OP_MOVE>(this->r.r, rv.r.r);
                        break;
                  }
                  case expr_tkind::memory: {
                        this->b->make<arch::opcodes::OP_MEMSET>(this->r.r, rv.r.r, this->bits());
                        break;
                  }
                  case expr_tkind::global: {
                        this->b->make<arch::opcodes::OP_SETGLOBAL>(rv.r.r, this->id);
                        if (this->f.fglobal_wild) {
                              this->b->set_flag<il::arch::data::flags::fwild_global>();
                        }
                        break;
                  }
                  case expr_tkind::flag: {
                        this->b->make<arch::opcodes::OP_FLAGSET>(this->integral, rv.r.r);
                        break;
                  }
                  case expr_tkind::stack: {
                        this->b->make<luramas::il::arch::opcodes::OP_SETSTACK>(rv.r.r, this->integral);
                        break;
                  }
                  default: {
                        return rv;
                  }
            }
            return *this;
      }
      build::expr build::expr::operator+=(const expr &other) const {
            auto v = this->operator+(other);
            return (this->operator=(v));
      }
      build::expr build::expr::operator*=(const expr &other) const {
            auto v = this->operator*(other);
            return (this->operator=(v));
      }
      build::expr build::expr::operator/=(const expr &other) const {
            auto v = this->operator/(other);
            return (this->operator=(v));
      }
      build::expr build::expr::operator-=(const expr &other) const {
            auto v = this->operator-(other);
            return (this->operator=(v));
      }
      build::expr build::expr::operator%=(const expr &other) const {
            auto v = this->operator%(other);
            return (this->operator=(v));
      }
      build::expr build::expr::operator&=(const expr &other) const {
            auto v = this->operator&(other);
            return (this->operator=(v));
      }
      build::expr build::expr::operator|=(const expr &other) const {
            auto v = this->operator|(other);
            return (this->operator=(v));
      }
      build::expr build::expr::operator^=(const expr &other) const {
            auto v = this->operator^(other);
            return (this->operator=(v));
      }
      build::expr build::expr::operator<<=(const expr &other) const {
            auto v = this->operator<<(other);
            return (this->operator=(v));
      }
      build::expr build::expr::operator>>=(const expr &other) const {
            auto v = this->operator>>(other);
            return (this->operator=(v));
      }
      build::expr build::expr::operator&&(const expr &other) const {
            build::expr lv;
            switch (this->tk) {
                  case expr_tkind::flag: {
                        lv.emit(this->b, this->b->get_temp());
                        lv.b->make<arch::opcodes::OP_FLAGREAD>(this->r.r, this->integral);
                        lv.cast(1u, true);
                        break;
                  }
                  case expr_tkind::integral: {
                        auto temp = this->b->get_temp();
                        this->b->make<arch::opcodes::OP_LOADINT>(temp.r, this->integral);
                        lv.emit(this->b, temp);
                        break;
                  }
                  default: {
                        lv.emit(*this);
                        break;
                  }
            }
            build::expr rv;
            switch (other.tk) {
                  case expr_tkind::flag: {
                        rv.emit(other.b, other.b->get_temp());
                        rv.b->make<arch::opcodes::OP_FLAGREAD>(other.r.r, other.integral);
                        rv.cast(1u, true);
                        break;
                  }
                  case expr_tkind::integral: {
                        auto temp = other.b->get_temp();
                        other.b->make<arch::opcodes::OP_LOADINT>(temp.r, other.integral);
                        rv.emit(other.b, temp);
                        break;
                  }
                  default: {
                        rv.emit(other);
                        break;
                  }
            }
            /* TODO PROBABLY UNSAFE FLAG FOR PROPAGATION? */
            const auto result = this->b->make_temp();
            this->b->make<arch::opcodes::OP_CLOGIC_AND>(result.r.r, lv.r.r, rv.r.r);
            return result;
      }
      build::expr build::expr::operator||(const expr &other) const {
            build::expr lv;
            switch (this->tk) {
                  case expr_tkind::flag: {
                        lv.emit(this->b, this->b->get_temp());
                        lv.b->make<arch::opcodes::OP_FLAGREAD>(this->r.r, this->integral);
                        lv.cast(1u, true);
                        break;
                  }
                  case expr_tkind::integral: {
                        auto temp = this->b->get_temp();
                        this->b->make<arch::opcodes::OP_LOADINT>(temp.r, this->integral);
                        lv.emit(this->b, temp);
                        break;
                  }
                  default: {
                        lv.emit(*this);
                        break;
                  }
            }
            build::expr rv;
            switch (other.tk) {
                  case expr_tkind::flag: {
                        rv.emit(other.b, other.b->get_temp());
                        rv.b->make<arch::opcodes::OP_FLAGREAD>(other.r.r, other.integral);
                        rv.cast(1u, true);
                        break;
                  }
                  case expr_tkind::integral: {
                        auto temp = other.b->get_temp();
                        other.b->make<arch::opcodes::OP_LOADINT>(temp.r, other.integral);
                        rv.emit(other.b, temp);
                        break;
                  }
                  default: {
                        rv.emit(other);
                        break;
                  }
            }
            /* TODO PROBABLY UNSAFE FLAG FOR PROPAGATION? */
            const auto result = this->b->make_temp();
            this->b->make<arch::opcodes::OP_CLOGIC_OR>(result.r.r, lv.r.r, rv.r.r);
            return result;
      }

      build::expr build::expr::operator+(const std::intptr_t other) const {
            return this->operator+(expr(this->b, other));
      }
      build::expr build::expr::operator-(const std::intptr_t other) const {
            return this->operator-(expr(this->b, other));
      }
      build::expr build::expr::operator*(const std::intptr_t other) const {
            return this->operator*(expr(this->b, other));
      }
      build::expr build::expr::operator/(const std::intptr_t other) const {
            return this->operator/(expr(this->b, other));
      }
      build::expr build::expr::operator&(const std::intptr_t other) const {
            return this->operator&(expr(this->b, other));
      }
      build::expr build::expr::operator|(const std::intptr_t other) const {
            return this->operator|(expr(this->b, other));
      }
      build::expr build::expr::operator^(const std::intptr_t other) const {
            return this->operator^(expr(this->b, other));
      }
      build::expr build::expr::operator%(const std::intptr_t other) const {
            return this->operator%(expr(this->b, other));
      }
      build::expr build::expr::operator<<(const std::intptr_t other) const {
            return this->operator<<(expr(this->b, other));
      }
      build::expr build::expr::operator>>(const std::intptr_t other) const {
            return this->operator>>(expr(this->b, other));
      }
      build::expr build::expr::operator==(const std::intptr_t other) const {
            return this->operator==(expr(this->b, other));
      }
      build::expr build::expr::operator!=(const std::intptr_t other) const {
            return this->operator!=(expr(this->b, other));
      }
      build::expr build::expr::operator<(const std::intptr_t other) const {
            return this->operator<(expr(this->b, other));
      }
      build::expr build::expr::operator<=(const std::intptr_t other) const {
            return this->operator<=(expr(this->b, other));
      }
      build::expr build::expr::operator>(const std::intptr_t other) const {
            return this->operator>(expr(this->b, other));
      }
      build::expr build::expr::operator>=(const std::intptr_t other) const {
            return this->operator>=(expr(this->b, other));
      }
      build::expr build::expr::operator[](const std::intptr_t offset) const {
            return (*this >> offset) & 1u;
      }

      build::expr build::expr::operator=(const std::intptr_t other) const {
            return this->operator=(expr(this->b, other));
      }
      build::expr build::expr::operator+=(const std::intptr_t other) const {
            return this->operator+=(expr(this->b, other));
      }
      build::expr build::expr::operator-=(const std::intptr_t other) const {
            return this->operator-=(expr(this->b, other));
      }
      build::expr build::expr::operator*=(const std::intptr_t other) const {
            return this->operator*=(expr(this->b, other));
      }
      build::expr build::expr::operator/=(const std::intptr_t other) const {
            return this->operator/=(expr(this->b, other));
      }
      build::expr build::expr::operator%=(const std::intptr_t other) const {
            return this->operator%=(expr(this->b, other));
      }
      build::expr build::expr::operator&=(const std::intptr_t other) const {
            return this->operator&=(expr(this->b, other));
      }
      build::expr build::expr::operator|=(const std::intptr_t other) const {
            return this->operator|=(expr(this->b, other));
      }
      build::expr build::expr::operator^=(const std::intptr_t other) const {
            return this->operator^=(expr(this->b, other));
      }
      build::expr build::expr::operator<<=(const std::intptr_t other) const {
            return this->operator<<=(expr(this->b, other));
      }
      build::expr build::expr::operator>>=(const std::intptr_t other) const {
            return this->operator>>=(expr(this->b, other));
      }
      build::expr build::expr::operator++() const {
            return this->operator+=(1);
      }
      build::expr build::expr::operator--() const {
            return this->operator-=(1);
      }

      build::expr build::expr::cmp(const expr &other) const {
            return evaluate<arch::data::bin_kinds::eq_>(*this, other, true);
      }
      build::expr build::expr::cmp(const std::intptr_t other) const {
            return this->cmp(expr(this->b, other));
      }

      build::expr build::expr::cast(const types::underlying_type &s) {

            switch (this->tk) {
                  case expr_tkind::reg: {
                        this->b->make<arch::opcodes::OP_BITCAST>(this->r.r, this->r.r, s.storage_size, s.precision, s.unsign);
                        this->r.size = s;
                        break;
                  }
                  case expr_tkind::memory: {
                        auto temp = build::expr(this->b, this->b->get_temp());
                        temp = *this;
                        return temp.cast(s);
                  }
                  case expr_tkind::flag: {
                        auto temp = build::expr(this->b, this->b->get_temp());
                        temp = *this;
                        return temp.cast(1u, true);
                  }
                  default: {
                        break;
                  }
            }
            return *this;
      }
      build::expr build::expr::cast(const reg &s) {

            return this->cast(s.size);
      }
      build::expr build::expr::cast(const luramas_bitwidth bits, const bool unsign, const std::uint8_t precision) {
            return this->cast(types::underlying_type(unsign, types::read_type::bits, precision, bits));
      }
      build::expr build::expr::cast(const bool unsign) {
            auto ut = this->r.size;
            ut.unsign = unsign;
            *this = this->cast(ut);
            return *this;
      }

      build::expr build::expr::memread(const luramas_bitwidth bits) const {

            auto result = this->b->make_temp();
            auto r = this->b->make_temp();
            r = *this;
            this->b->make<arch::opcodes::OP_MEMREAD>(result.r.r, r.r.r, bits);
            return result;
      }

      build::expr build::expr::read(const expr &min, const expr &max) const {
            return this->b->make_bitread(*this, min, max);
      }
      build::expr build::expr::read(const expr &bit_index) const {
            return this->b->make_bitread(*this, bit_index, bit_index + 1u);
      }
      build::expr build::expr::read(const luramas_bitwidth bit_index) const {
            if (bit_index >= this->bits()) {
                  luramas::error::error("Invalid bit range");
            }
            return this->read(expr(this->b, bit_index));
      }
      build::expr build::expr::read(const luramas_bitwidth min, const luramas_bitwidth max) const {
            if (min > max || max >= this->bits()) {
                  luramas::error::error("Invalid bit range");
            }
            if (min == max) {
                  return (*this)[min];
            }
            if (!min && max + 1u == this->bits()) {
                  return *this;
            }
            return this->read(expr(this->b, min), expr(this->b, max));
      }

      build::expr build::expr::write(const expr &min, const expr &max, const expr &value) const {
            return this->b->make_bitwrite(*this, value, min, max);
      }
      build::expr build::expr::write(const luramas_bitwidth min, const luramas_bitwidth max, const expr &value) const {
            if (min > max) {
                  return *this;
            }
            if (!min && max + 1u == this->bits()) {
                  return (*this = value);
            }
            return write(expr(this->b, min), expr(this->b, max), value);
      }
      build::expr build::expr::write(const luramas_bitwidth min, const luramas_bitwidth max, const std::intptr_t value) const {
            return this->write(min, max, expr(this->b, value));
      }
      build::expr build::expr::write(const expr &min, const expr &max, const std::intptr_t value) const {
            return this->write(min, max, expr(this->b, value));
      }
      build::expr build::expr::write(const expr &min, const std::intptr_t max, const std::intptr_t value) const {
            return this->write(min, expr(this->b, max), expr(this->b, value));
      }
      build::expr build::expr::write(const expr &min, const std::intptr_t max, const expr &value) const {
            return this->write(min, expr(this->b, max), value);
      }
      build::expr build::expr::write(const expr &value) const {
            return this->write(0u, this->bits() - 1u, value);
      }

      build::expr build::expr::fill(const luramas_bitwidth start, const std::intptr_t value) const {
            return this->write(start, this->bits() - 1u, value);
      }
      bool build::expr::empty() const {
            return !this->b && this->tk == expr_tkind::nothing;
      }
      luramas_bitwidth build::expr::bits() const {

            switch (this->tk) {
                  case expr_tkind::reg:
                  case expr_tkind::memory: {
                        return this->r.size.bits();
                  }
                  case expr_tkind::flag: {
                        return 1u;
                  }
                  default: {
                        break;
                  }
            }
            return this->b->suggested_bit_set;
      }
      luramas::types::signess build::expr::signess() const {

            switch (this->tk) {
                  case expr_tkind::reg:
                  case expr_tkind::memory: {
                        return this->r.size.signess_t();
                  }
                  case expr_tkind::flag: {
                        return luramas::types::signess::unsign;
                  }
                  default: {
                        break;
                  }
            }
            return luramas::types::signess::sign;
      }
      luramas::types::underlying_type build::expr::type() const {
            return luramas::types::underlying_type(this->signess() == luramas::types::signess::unsign, luramas::types::read_type::bits, 0u, this->bits());
      }

      void build::expr::dump() const {
            switch (this->tk) {
                  case expr_tkind::integral: {
                        std::printf("[integral] %lld\n", this->integral);
                        break;
                  }
                  case expr_tkind::flag: {
                        std::printf("[flag] %lld\n", this->integral);
                        break;
                  }
                  case expr_tkind::reg: {
                        std::printf("[reg] %d\n", this->r.r);
                        std::printf("   [bit] %d\n", this->bits());
                        std::printf("   [precision] %d\n", this->r.size.precision);
                        std::printf("   [unsign] %d\n", this->r.size.unsign);
                        break;
                  }
                  case expr_tkind::memory: {
                        std::printf("[Memory]:\n");
                        std::printf("   [bit] %d\n", this->bits());
                        std::printf("   [unsign] %d\n", this->r.size.unsign);
                        break;
                  }
                  default: {
                        break;
                  }
            }
            return;
      }
      bool build::expr::is_mem() const {
            return this->tk == expr_tkind::memory;
      }
      bool build::expr::is_reg() const {
            return this->tk == expr_tkind::reg;
      }
      bool build::expr::is_reg(const luramas_bitwidth bits) const {
            return this->is_reg() && this->bits() == bits;
      }
} // namespace luramas::il::lifter::builder