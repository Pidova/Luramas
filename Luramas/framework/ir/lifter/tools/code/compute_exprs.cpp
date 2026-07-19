#include "../extras/stats.hpp"
#include "../tools.hpp"

namespace luramas::ir::tools::compute::exprs {

      std::shared_ptr<ir_stat::ir_expr> wrap(const std::shared_ptr<ir_stat::ir_expr> &e, const luramas_int &n) {

            return tools::exprs::generate::integral(n.wrap(e->non_native->under.storage_size, e->non_native->under.unsign, e->non_native->under.precision));
      }

      namespace representations {

            std::shared_ptr<ir_stat::ir_expr> boolean_identity(std::shared_ptr<ir_stat::ir_expr> &l, const il::arch::data::bin_kinds b, const std::shared_ptr<ir_stat::ir_expr> &r) {

                  if (!tools::exprs::values::test::is_boolean_identity(l, b, r)) {
                        return nullptr;
                  }

                  if (b == il::arch::data::bin_kinds::eq_) {
                        if (r->is_integral(LURAMAS_IR_COMPARATIVE_NON_OBJECT_FALSE)) {
                              tools::exprs::mutate::flip_cmp(l);
                        }
                        return l;
                  }
                  if (r->is_integral(LURAMAS_IR_COMPARATIVE_NON_OBJECT_TRUE)) {
                        tools::exprs::mutate::flip_cmp(l);
                  }
                  return l;
            }

            std::shared_ptr<ir_stat::ir_expr> boolean_integral(std::shared_ptr<ir_stat::ir_expr> &l, const il::arch::data::bin_kinds b, const std::shared_ptr<ir_stat::ir_expr> &r) {

                  if (!tools::exprs::values::test::is_boolean_comparision(l, b, r)) {
                        return nullptr;
                  }

                  if (b == il::arch::data::bin_kinds::eq_) {
                        if (r->is_integral(LURAMAS_IR_COMPARATIVE_NON_OBJECT_FALSE)) {
                              tools::exprs::mutate::flip_cmp(l);
                        }
                        return l;
                  }
                  if (r->is_integral(LURAMAS_IR_COMPARATIVE_NON_OBJECT_TRUE)) {
                        tools::exprs::mutate::flip_cmp(l);
                  }
                  return l;
            }
      } // namespace representations

      bool simplify(passes::pass_manager &pm, std::shared_ptr<ir_stat::ir_expr> &e, const bool singleton, const bool mutate_pm, const std::optional<generation::ssa::ssa> &ssa, const std::optional<types::map> &tmap) {

            if (!e) {
                  return false;
            }

            switch (e->tk) {
                  case tkind::boolean: {

                        /* BOOLEAN UNARY == NOT */
                        if (e->u == il::arch::data::bin_kinds::not_) {
                              e->bv = !e->bv;
                              e->u = il::arch::data::bin_kinds::nothing;
                        }
                        break;
                  }
                  case tkind::lura_int: {

                        /* MINUS UNARY n */
                        if (e->u == il::arch::data::bin_kinds::minus_) {
                              e->n = -e->n;
                              e->u = il::arch::data::bin_kinds::nothing;
                        }
                        break;
                  }
                  default: {
                        break;
                  }
            }

            switch (e->k) {
                  case expr_kinds::condition: {

                        /* Combined */
                        if (const auto combined = tools::combine::cond(pm, e); combined) {
                              e = combined;
                              if (mutate_pm) {
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }
                              return true;
                        }

                        if (const auto cond = tools::compute::exprs::simplify_condition(pm, e->l, e->b, e->e, e->r, mutate_pm, tmap); cond) {
                              e = cond;
                              if (mutate_pm) {
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }
                              return true;
                        }
                        break;
                  }
                  case expr_kinds::ternary: {

                        /* Comparative true or false */
                        const auto comparative = compare(e->l, e->r, e->b, pm.env_flags.fprimitive_object);
                        switch (comparative) {
                              case compute::comparable::true_: {
                                    e = e->ev;
                                    return true;
                              }
                              case compute::comparable::false_: {
                                    e = e->xv;
                                    return true;
                              }
                              default: {
                                    break;
                              }
                        }

                        if (const auto cond = tools::compute::exprs::simplify_condition(pm, e->l, e->b, e->e, e->r, mutate_pm, tmap); cond) {
                              e->l = cond->l;
                              e->b = cond->b;
                              e->e = cond->e;
                              e->r = cond->r;
                              return true;
                        }

                        /* (NO VOLATILES) ? SAME EXPR : SAME EXPR */
                        if (e->ev && e->xv && !tools::exprs::common::ternary_compare_volatile(e) && tools::exprs::common::ternary_same_then_else(e)) {
                              e = e->ev;
                              if (mutate_pm) {
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }
                              return true;
                        }

                        /* (?) ? BOOLEAN : BOOLEAN */
                        if (tools::exprs::values::is_boolean(e->ev) && tools::exprs::values::is_boolean(e->xv)) {
                              const auto l = e->l;
                              const auto r = e->r;
                              if (e->ev->bv != e->xv->bv) {
                                    const auto b = e->ev->bv ? e->b : il::arch::data::bin_kindflip(e->b);
                                    e->clear();
                                    e->emit_cond(l, b, r);
                                    if (mutate_pm) {
                                          pm.mut(LURAMAS_DEBUG_LINE);
                                    }
                              } else if (!l->contains_volatile() && (!r || !r->contains_volatile())) {
                                    e = e->ev;
                                    if (mutate_pm) {
                                          pm.mut(LURAMAS_DEBUG_LINE);
                                    }
                              }
                              return true;
                        }

                        /* (?) ? IMPLICIT TRUE : PRIMITIVE/IMPLICIT TRUE/SINGLETON */
                        if (e->ev && e->xv && e->ev->implicit() && (e->xv->is_primitive() || e->xv->implicit() || singleton)) {
                              e = tools::exprs::generate::logical<expr_logical::or_>(tools::exprs::generate::logical<expr_logical::and_>(tools::exprs::generate::cond(e->l, e->b, e->r), e->ev), e->xv);
                              if (mutate_pm) {
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }
                              return true;
                        }

                        /* (true/false) ? ? : ? */
                        if (tools::exprs::branch::is_ternary_singlecmp(e) && e->l->is_tk<tkind::boolean>()) {
                              e = (!e->l->bv) ? e->xv : e->ev;
                              if (mutate_pm) {
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }
                              return true;
                        }

                        /* (?) ? {ALWAYS TRUE} : BOOLEAN */
                        if (e->ev) {
                              switch (e->ev->tk) {
                                    case tkind::string: {
                                          e = tools::exprs::generate::logical<expr_logical::or_>(tools::exprs::generate::logical<expr_logical::and_>(tools::exprs::generate::cond(e->l, e->b, e->r), e->ev), e->xv);
                                          if (mutate_pm) {
                                                pm.mut(LURAMAS_DEBUG_LINE);
                                          }
                                          return true;
                                    }
                                    default: {
                                          break;
                                    }
                              }
                        }

                        if (!pm.env_flags.fcomparative_results_binvals) {

                              /* (?? (!=/==) ??) (!=/==) (0/1) */
                              if (const auto bopt = tools::compute::exprs::representations::boolean_identity(e->l, e->b, e->r); bopt) {
                                    e->l = bopt->l;
                                    e->b = bopt->b;
                                    e->r = bopt->r;
                                    if (mutate_pm) {
                                          pm.mut(LURAMAS_DEBUG_LINE);
                                    }
                                    return true;
                              }

                              /* (??) ? 1 : 0 */
                              if (e->ev->is_integral(LURAMAS_IR_COMPARATIVE_NON_OBJECT_TRUE) && e->xv->is_integral(LURAMAS_IR_COMPARATIVE_NON_OBJECT_FALSE)) {

                                    const auto l = e->l;
                                    const auto r = e->r;
                                    const auto b = e->b;
                                    e->clear();
                                    e->emit_cond(l, b, r);
                                    if (mutate_pm) {
                                          pm.mut(LURAMAS_DEBUG_LINE);
                                    }
                                    return true;
                              }

                              /* (??) ? 0 : 1 */
                              if (e->ev->is_integral(LURAMAS_IR_COMPARATIVE_NON_OBJECT_FALSE) && e->xv->is_integral(LURAMAS_IR_COMPARATIVE_NON_OBJECT_TRUE)) {

                                    const auto l = e->l;
                                    const auto r = e->r;
                                    const auto b = e->b;
                                    e->clear();
                                    e->emit_cond(l, luramas::il::arch::data::bin_kindflip(b), r);
                                    if (mutate_pm) {
                                          pm.mut(LURAMAS_DEBUG_LINE);
                                    }
                                    return true;
                              }
                        }

                        /* (?? > ??) ? ? : ?? */
                        if (e->b == il::arch::data::bin_kinds::gt_) {
                              e->b = il::arch::data::bin_kinds::lt_;
                              std::swap(e->ev, e->xv);
                              if (mutate_pm) {
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }
                              return true;
                        }

                        /* B empty NOT LOGICAL r == nullptr and L == cmp */
                        if (e->e == expr_logical::nothing && e->b == il::arch::data::bin_kinds::nothing && !e->r && tools::exprs::values::is_condition(e->l, false)) {
                              e->b = e->l->b;
                              e->r = e->l->r;
                              e->l = e->l->l;
                              if (mutate_pm) {
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }
                              return true;
                        }

                        /* 
                        CMP_0 ? (CMP_1 ? CMP_2 : CMP_3) : CMP_4  
                        IF (CMP_0 == CMP_1) then  CMP_0 ? CMP_2 : CMP_4 
                        */
                        if (tools::exprs::values::is_ternary_cmp(e, e->ev)) {

                              e->ev = e->ev->ev;
                              if (mutate_pm) {
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }
                              return true;
                        }
                        break;
                  }
                  case expr_kinds::arith: {

                        /* INTEGRAL ARITH INTEGRAL */
                        if (e->l && e->r) {

                              if (e->l->is_integral() && e->r->is_integral()) {

                                    if (!safety::arith::is_safe(pm, e)) {
                                          return false;
                                    }

                                    bool unsign = false;
                                    const auto bits = tools::exprs::evaluate::arithmetic_bits(pm, e, unsign);
                                    e = tools::exprs::generate::integral(tools::compute::compute<luramas_int, luramas_int, luramas_int>(e->l->extract_integral(), e->r->extract_integral(), e->b).wrap(bits, unsign));
                                    if (mutate_pm) {
                                          pm.mut(LURAMAS_DEBUG_LINE);
                                    }
                                    return true;
                              }

                              /* Combined */
                              if (const auto combined = tools::combine::arith(pm, e, tmap); combined) {
                                    e = combined;
                                    if (mutate_pm) {
                                          pm.mut(LURAMAS_DEBUG_LINE);
                                    }
                                    return true;
                              }
                        }
                        break;
                  }
                  case expr_kinds::bitread: {

                        if (e->l && e->r && e->ev && e->non_native) {

                              /* Value == Integral */
                              if (tools::exprs::basic::is_integral(e->l, e->r, e->ev)) {

                                    e = tools::exprs::generate::cast(tools::exprs::generate::integral(e->l->n.read(e->r->extract_integral(), e->ev->extract_integral())), e->non_native);
                                    if (mutate_pm) {
                                          pm.mut(LURAMAS_DEBUG_LINE);
                                    }
                              }

                              /* min == 0 && max + 1u == cast_size */
                              if (tools::exprs::basic::is_integral(e->r, e->ev) && e->non_native->basic()) {

                                    const auto min = e->r->extract_integral();
                                    const auto max = e->ev->extract_integral();
                                    if (!min && max > min && max + 1u == e->non_native->under.bits()) {

                                          e = tools::exprs::generate::cast(e->l, e->non_native);
                                          if (mutate_pm) {
                                                pm.mut(LURAMAS_DEBUG_LINE);
                                          }
                                    }
                              }
                        }
                        break;
                  }
                  case expr_kinds::concat: {

                        if (tools::compute::strings::flatten_concat(e)) {
                              if (mutate_pm) {
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }
                              return true;
                        }
                        break;
                  }
                  case expr_kinds::unary: {

                        if (const auto combined = tools::combine::unary(pm, e); combined) {
                              e = combined;
                              if (mutate_pm) {
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }
                              return true;
                        }
                        break;
                  }
                  case expr_kinds::cast: {

                        if (e->non_native) {

                              /* cast<x>(cast<x>()) */
                              if (tools::exprs::values::is_cast(e->l) && !e->l->non_native->is<ir::types::type_kind::object>()) {
                                    e->l = e->l->l;
                                    if (mutate_pm) {
                                          pm.mut(LURAMAS_DEBUG_LINE);
                                    }
                                    return true;
                              }

                              /* Next is already a type */
                              if (e->l->non_native) {
                                    e->l->non_native = e->non_native;
                                    e = e->l;
                                    if (mutate_pm) {
                                          pm.mut(LURAMAS_DEBUG_LINE);
                                    }
                                    return true;
                              }

                              /* cast == next object */
                              if (const auto v = e->l->non_native; v && e->non_native->compare(*v)) {
                                    e = e->l;
                                    if (mutate_pm) {
                                          pm.mut(LURAMAS_DEBUG_LINE);
                                    }
                                    return true;
                              }

                              if (!pm.env_flags.fcomparative_results_binvals) {

                                    /* cast<[PRIMTIVE]>(CMP) */
                                    if (e->non_native->is<ir::types::type_kind::primitive>() && tools::exprs::values::is_condition(e->l, false)) {
                                          e = e->l;
                                          if (mutate_pm) {
                                                pm.mut(LURAMAS_DEBUG_LINE);
                                          }
                                          return true;
                                    }
                              }

                              /* Cast == Evaluated cast */
                              const auto types = tools::types::extract(e->l);
                              if (types.size() == 1u) {
                                    if (const auto &f = types.front(); f.t == tools::types::extraction_kind::type && e->non_native->compare(*f.type)) {
                                          e = e->l;
                                          if (mutate_pm) {
                                                pm.mut(LURAMAS_DEBUG_LINE);
                                          }
                                    }
                                    return true;
                              }

                              switch (e->l->k) {
                                    case expr_kinds::arith: {

                                          /* Extract dominant then promote it keeps types the same */
                                          if (pm.env_flags.options.ounarith_operands_signess_no_side_effects.contains(e->l->b)) {

                                                if (types.size() == 2u) {

                                                      const auto l = types.front();
                                                      const auto r = types.back();
                                                      if (l.basic() && r.basic() && luramas::types::is::diff_signess(l.type->under, r.type->under)) {

                                                            const auto dom = tools::types::dominant(pm, l.type->under, r.type->under);
                                                            l.expr->non_native->under.unsign = !dom.unsign;
                                                            r.expr->non_native->under.unsign = !dom.unsign;
                                                            e->l = tools::exprs::generate::cast(e->l, dom);
                                                            if (mutate_pm) {
                                                                  pm.mut(LURAMAS_DEBUG_LINE);
                                                            }
                                                            return true;
                                                      }
                                                }
                                          }
                                          break;
                                    }
                                    default: {
                                          break;
                                    }
                              }

                              /* cast<[PRIMTIVE]>(???) */
                              if (e->non_native->basic() && e->l) {

                                    /* INTEGRAL */
                                    if (e->l->is_integral()) {
                                          e = wrap(e, e->l->extract_integral());
                                          if (mutate_pm) {
                                                pm.mut(LURAMAS_DEBUG_LINE);
                                          }
                                          return true;
                                    }

                                    /* BOOLEAN */
                                    if (tools::exprs::values::is_boolean(e->l)) {
                                          e = wrap(e, e->l->bv);
                                          if (mutate_pm) {
                                                pm.mut(LURAMAS_DEBUG_LINE);
                                          }
                                          return true;
                                    }

                                    /* SAME MEMREAD */
                                    if (tools::exprs::values::is_memoryread(e->l) &&
                                        (e->l->non_native->compare(*e->non_native) ||
                                            (tools::exprs::values::types::has_xtype(e->l) && e->l->xtype->compare(*e->non_native)))) {

                                          e = e->l;
                                          if (mutate_pm) {
                                                pm.mut(LURAMAS_DEBUG_LINE);
                                          }
                                          return true;
                                    }

                                    /* Cast(memread), diff types, no cast type */
                                    if (tools::exprs::values::is_memoryread(e->l) &&
                                        !e->l->non_native->compare(*e->non_native) &&
                                        !tools::exprs::values::types::has_xtype(e->l)) {

                                          e->l->xtype = e->non_native;
                                          e = e->l;
                                          if (mutate_pm) {
                                                pm.mut(LURAMAS_DEBUG_LINE);
                                          }
                                          return true;
                                    }

                                    /* ALL THE SAME TO CAST */
                                    if (!types.empty() && std::all_of(types.begin(), types.end(), [&](const auto &i) { return i.basic() && i.type->compare(*e->non_native); })) {
                                          e = e->l;
                                          if (mutate_pm) {
                                                pm.mut(LURAMAS_DEBUG_LINE);
                                          }
                                          return true;
                                    }
                              }
                        }
                        break;
                  }
                  case expr_kinds::blank_lvalue: {

                        e = e->l;
                        if (mutate_pm) {
                              pm.mut(LURAMAS_DEBUG_LINE);
                        }
                        return true;
                  }
                  default: {

                        break;
                  }
            }
            return false;
      };

      std::shared_ptr<ir_stat::ir_expr> simplify_condition(passes::pass_manager &pm, std::shared_ptr<ir_stat::ir_expr> &l, const luramas::il::arch::data::bin_kinds b, const expr_logical e, const std::shared_ptr<ir_stat::ir_expr> &r, const bool mutate_pm, const std::optional<types::map> &tmap) {

            const auto k = tools::compute::compare(l, r, b, pm.env_flags.fprimitive_object);
            switch (k) {
                  case tools::compute::comparable::true_: {

                        return tools::exprs::generate::cond(tools::exprs::generate::boolean(true), il::arch::data::bin_kinds::et_);
                  }
                  case tools::compute::comparable::false_: {

                        return tools::exprs::generate::cond(tools::exprs::generate::boolean(false), il::arch::data::bin_kinds::et_);
                  }
                  default: {
                        break;
                  }
            }

            if (!pm.env_flags.fcomparative_results_binvals) {

                  /* (?? (!=/==) ??) (!=/==) (0/1) */
                  if (const auto bopt = tools::compute::exprs::representations::boolean_identity(l, b, r); bopt) {

                        if (mutate_pm) {
                              pm.mut(LURAMAS_DEBUG_LINE);
                        }
                        return bopt;
                  }

                  /* ? CMP ? (!=/==) (0/1) */
                  if (const auto bopt = tools::compute::exprs::representations::boolean_integral(l, b, r); bopt) {

                        if (mutate_pm) {
                              pm.mut(LURAMAS_DEBUG_LINE);
                        }
                        return bopt;
                  }

                  /* ? CMP ? != false */
                  if (b == il::arch::data::bin_kinds::ne_ && tools::exprs::values::is_boolean(r, false) && tools::exprs::values::is_condition(l, false)) {

                        if (mutate_pm) {
                              pm.mut(LURAMAS_DEBUG_LINE);
                        }
                        return l;
                  }

                  if (tools::exprs::values::is_condition(l, false)) {

                        /* (? ?? ?) or (0/1) */
                        if (e == expr_logical::or_ || e == expr_logical::and_) {
                              if (tools::exprs::values::test::is_comparative_integral(r, true) && !l->contains_volatile()) {

                                    if (mutate_pm) {
                                          pm.mut(LURAMAS_DEBUG_LINE);
                                    }
                                    return r;
                              } else if (tools::exprs::values::test::is_comparative_integral(r, false)) {

                                    if (mutate_pm) {
                                          pm.mut(LURAMAS_DEBUG_LINE);
                                    }
                                    return l;
                              }
                        }

                        /* (? ?? ?) and (0/1) */
                        if (e == expr_logical::and_) {

                              if (tools::exprs::values::test::is_comparative_integral(r, true)) {

                                    if (mutate_pm) {
                                          pm.mut(LURAMAS_DEBUG_LINE);
                                    }
                                    return l;
                              } else if (tools::exprs::values::test::is_comparative_integral(r, false) && !l->contains_volatile()) {

                                    if (mutate_pm) {
                                          pm.mut(LURAMAS_DEBUG_LINE);
                                    }
                                    return r;
                              }
                        }
                  }

                  /* CMP == true */
                  if (b == il::arch::data::bin_kinds::eq_ && tools::exprs::values::is_boolean(r, true) && tools::exprs::values::is_condition(l, false)) {
                        return l;
                  }
            }

            /* not (cmp) */
            if (luramas::il::arch::data::is_kinds::not_k(b) && tools::exprs::values::is_condition(l, false)) {

                  if (mutate_pm) {
                        pm.mut(LURAMAS_DEBUG_LINE);
                  }
                  return tools::exprs::generate::cond(l->l, luramas::il::arch::data::bin_kindflip(l->b), l->r);
            }

            /* (? ?? ?) and true */
            if (e == expr_logical::and_ && tools::exprs::values::is_condition(l, false)) {
                  if (mutate_pm) {
                        pm.mut(LURAMAS_DEBUG_LINE);
                  }
                  return l;
            }

            /* BOOLEAN != true */
            if (b == il::arch::data::bin_kinds::nt_ && tools::exprs::values::is_boolean(l)) {
                  if (mutate_pm) {
                        pm.mut(LURAMAS_DEBUG_LINE);
                  }
                  l->bv = !l->bv;
                  return tools::exprs::generate::cond(l, luramas::il::arch::data::bin_kindflip(b), r);
            }

            /* != BOOLEAN */
            if (b == il::arch::data::bin_kinds::ne_ && tools::exprs::values::is_boolean(r)) {
                  if (mutate_pm) {
                        pm.mut(LURAMAS_DEBUG_LINE);
                  }
                  r->bv = !r->bv;
                  return tools::exprs::generate::cond(l, luramas::il::arch::data::bin_kindflip(b), r);
            }

            /* not (not ) */
            if (luramas::il::arch::data::is_kinds::not_k(b) && !r && (luramas::il::arch::data::is_kinds::not_k(l->u) || luramas::il::arch::data::is_kinds::not_k(l->b))) {

                  if (mutate_pm) {
                        pm.mut(LURAMAS_DEBUG_LINE);
                  }
                  l->u = luramas::il::arch::data::bin_kinds::nothing;
                  l->b = luramas::il::arch::data::bin_kinds::et_;
                  l->k = expr_kinds::condition;
                  return tools::exprs::generate::cond(l, luramas::il::arch::data::bin_kinds::et_, r);
            }

            /* not (cmp) */
            if (luramas::il::arch::data::is_kinds::not_k(b) && tools::exprs::values::is_condition(l, false)) {

                  if (mutate_pm) {
                        pm.mut(LURAMAS_DEBUG_LINE);
                  }
                  return tools::exprs::generate::cond(l->l, luramas::il::arch::data::bin_kindflip(l->b), l->r);
            }

            /* ((??))*/
            if (b == luramas::il::arch::data::bin_kinds::et_ && !r && l->b == luramas::il::arch::data::bin_kinds::et_ && !l->r) {

                  if (mutate_pm) {
                        pm.mut(LURAMAS_DEBUG_LINE);
                  }
                  return tools::exprs::generate::cond(l->l, b, r);
            }

            if (r) {

                  /* (? - ?) == 0 */
                  if (!pm.env_flags.freal_objects) {

                        if (b == il::arch::data::bin_kinds::eq_ && r->is_integral(0) && tools::exprs::values::is_arith<luramas::il::arch::data::bin_kinds::sub_>(l)) {

                              if (mutate_pm) {
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }
                              return tools::exprs::generate::cond(l->l, b, l->r);
                        }

                        /* (? - ?) != 0 */
                        if (b == il::arch::data::bin_kinds::ne_ && r->is_integral(0) && tools::exprs::values::is_arith<luramas::il::arch::data::bin_kinds::sub_>(l)) {

                              if (mutate_pm) {
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }
                              return tools::exprs::generate::cond(l->l, b, l->r);
                        }
                  }

                  /* (? ?? ?) or (? ?? ?)  *AND* ? == ?*/
                  if (e == expr_logical::or_ && tools::exprs::branch::same_logical_operands(l, r)) {

                        /* (? < ?) or (? == ?) */
                        if (l->is_b<il::arch::data::bin_kinds::lt_>() && r->is_b<il::arch::data::bin_kinds::eq_>()) {

                              if (mutate_pm) {
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }
                              return tools::exprs::generate::cond(l->l, il::arch::data::bin_kinds::lte_, l->r);
                        }
                        /* (? == ?) or (? < ?) */
                        if (l->is_b<il::arch::data::bin_kinds::eq_>() && r->is_b<il::arch::data::bin_kinds::lt_>()) {

                              if (mutate_pm) {
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }
                              return tools::exprs::generate::cond(l->l, il::arch::data::bin_kinds::lte_, l->r);
                        }

                        /* (? > ?) or (? == ?) */
                        if (l->is_b<il::arch::data::bin_kinds::gt_>() && r->is_b<il::arch::data::bin_kinds::eq_>()) {

                              if (mutate_pm) {
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }
                              return tools::exprs::generate::cond(l->l, il::arch::data::bin_kinds::gte_, l->r);
                        }
                        /* (? == ?) or (? > ?) */
                        if (l->is_b<il::arch::data::bin_kinds::eq_>() && r->is_b<il::arch::data::bin_kinds::gt_>()) {

                              if (mutate_pm) {
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }
                              return tools::exprs::generate::cond(l->l, il::arch::data::bin_kinds::gte_, l->r);
                        }
                  }

                  /* (((?? - 1) % 2) - 1) != 0 */
                  if (b == il::arch::data::bin_kinds::ne_ && r->is_integral(0) &&
                      tools::exprs::values::is_arith<il::arch::data::bin_kinds::sub_>(l, 1u) &&
                      tools::exprs::values::is_arith<il::arch::data::bin_kinds::mod_>(l->l, 2u) &&
                      tools::exprs::values::is_arith<il::arch::data::bin_kinds::sub_>(l->l->l, 1u)) {

                        if (mutate_pm) {
                              pm.mut(LURAMAS_DEBUG_LINE);
                        }
                        return tools::exprs::generate::cond(tools::exprs::generate::arith(l->l->l->l, tools::exprs::generate::integral(2u), il::arch::data::bin_kinds::mod_), il::arch::data::bin_kinds::ne_, r);
                  }

                  /* (??[SINGLE TYPE NO UNSIGNED] - INT) != 0 */
                  if (b == il::arch::data::bin_kinds::ne_ && tools::exprs::values::is_integer(r, 0u) &&
                      tools::exprs::values::is_arith<il::arch::data::bin_kinds::sub_>(l) && tools::exprs::values::is_integer(l->r)) {

                        auto t = pm.env_flags.options.odefault_type;
                        if (tmap) {
                              if (const auto it = (*tmap).find(l->l); it != (*tmap).end() && !it->second.empty()) {

                                    if (const auto &first = it->second.front(); std::all_of(it->second.begin(), it->second.end(), [&](const std::shared_ptr<ir::types::object::type> &p) {
                                              return p && first && (*p == *first);
                                        })) {
                                          t = first->under;
                                    }
                              }
                        }
                        if (!t.empty() && !t.unsign) {

                              if (mutate_pm) {
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }
                              /* ?? != INT */
                              return tools::exprs::generate::cond(l->l, il::arch::data::bin_kinds::ne_, l->r);
                        }
                  }
            }
            return nullptr;
      }

      bool reorder(passes::pass_manager &pm, std::shared_ptr<ir_stat::ir_expr> &expr) {

            if (!expr) {
                  return false;
            }
            switch (expr->k) {
                  case expr_kinds::ternary:
                  case expr_kinds::condition: {

                        if (expr->l && expr->r && expr->l->is_primitive()) {
                              std::swap(expr->l, expr->r);
                              tools::exprs::mutate::flip_cmp(expr);
                              return true;
                        }
                        break;
                  }
                  case expr_kinds::arith: {

                        switch (expr->b) {
                              case il::arch::data::bin_kinds::add_: {

                                    /* INTEGRAL + (NOT INTEGRAL) */
                                    if (expr->l->is_integral() && !expr->r->is_integral()) {
                                          std::swap(expr->l, expr->r);
                                          return true;
                                    }
                                    break;
                              }
                              case il::arch::data::bin_kinds::sub_: {

                                    /* INTEGRAL - (NOT INTEGRAL) */
                                    if (expr->l->is_integral() && !expr->r->is_integral()) {
                                          expr->l->n = -expr->l->n;
                                          std::swap(expr->l, expr->r);
                                          expr->b = il::arch::data::bin_kinds::add_;
                                          return true;
                                    }
                                    break;
                              }
                              case il::arch::data::bin_kinds::mul_: {

                                    /* INTEGRAL * (NOT INTEGRAL) */
                                    if (expr->l->is_integral() && !expr->r->is_integral()) {
                                          std::swap(expr->l, expr->r);
                                          return true;
                                    }
                                    break;
                              }
                              case il::arch::data::bin_kinds::xor_: {

                                    /* INTEGRAL ^ (NOT INTEGRAL) */
                                    if (expr->l->is_integral() && !expr->r->is_integral()) {
                                          std::swap(expr->l, expr->r);
                                          return true;
                                    }
                                    break;
                              }
                              case il::arch::data::bin_kinds::or_: {

                                    /* INTEGRAL | (NOT INTEGRAL) */
                                    if (expr->l->is_integral() && !expr->r->is_integral()) {
                                          std::swap(expr->l, expr->r);
                                          return true;
                                    }
                                    break;
                              }
                              case il::arch::data::bin_kinds::and_: {

                                    /* INTEGRAL & (NOT INTEGRAL) */
                                    if (expr->l->is_integral() && !expr->r->is_integral()) {
                                          std::swap(expr->l, expr->r);
                                          return true;
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
                        break;
                  }
            }
            return false;
      }
} // namespace luramas::ir::tools::compute::exprs