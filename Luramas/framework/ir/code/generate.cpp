#include "generate.hpp"
#include "../lifter/tools/extras/exprs.hpp"
#include "tools/tools.hpp"
#include <stack>

namespace extra {

      static constexpr std::array<const char *const, 22u> black_listed_idxs = {
          "and",
          "break",
          "do",
          "else",
          "elseif",
          "end",
          "false",
          "for",
          "function",
          "goto",
          "if",
          "in",
          "local",
          "nil",
          "not",
          "or",
          "repeat",
          "return",
          "then",
          "true",
          "until",
          "while"};

      enum class closure_kind : std::uint8_t {
            global,
            local,
            anonymous
      };
} // namespace extra

struct itemization {

      std::string indent = "";
      std::string pre_linebreak = "";
      std::string stat = "";
      std::string post_linebreak = "";

      std::string compile() const {
            return this->indent + this->pre_linebreak + this->stat + this->post_linebreak;
      }
};

std::string luramas::ir::code::generation::generate(const ir::code::emitter::syntax::emitter_syntax syn, const ir_stat::space &code, const std::shared_ptr<ir::data::format::format> &format, const bool use_annotations) {

      boost::unordered_flat_set<std::string> globals;
      boost::unordered_flat_map<std::shared_ptr<ir_stat::ir_expr>, tools::smart_variables::naming> vars;

      auto param_variadic = std::make_shared<ir_stat::ir_expr>();
      param_variadic->emit_variadic();

      struct signature {
            luramas_id id = 0u;
            luramas_flag fuses_controller = false;
            std::string func_name = "";
            std::vector<std::string> args;
            std::vector<ir::types::signature> arg_types;
            std::vector<ir::types::signature> result_types;
      };
      boost::unordered_flat_map<luramas_id, signature> signatures;

      /* Variable naming */
      {

            luramas_xregister gvn = 0u;
            luramas_xregister discriminator = 0u;
            const auto valid = [&](const auto &str) {
                  if (!std::none_of(vars.begin(), vars.end(), [&](const auto &pair) { return pair.second.str() == str; })) {
                        ++gvn;
                        return false;
                  }
                  if (globals.find(str) != globals.end()) {
                        ++gvn;
                        return false;
                  }
                  return true;
            };
            const auto make_valid = [&](auto &str, const auto &reg, const auto &suffix_char, const luramas_flag uppercase = false) {
                  bool first = true;
                  tools::smart_variables::naming result(str, format->vars.naming_conventions.delimeter);
                  do {
                        if (!first) {
                              result.descriminator += suffix_char ? tools::smart_variables::alpha_suffix(reg + gvn) : std::to_string(reg + gvn);
                        }
                        if (uppercase) {
                              luramas_str_uppercase(result.name);
                              luramas_str_uppercase(result.descriminator);
                        }
                        first = false;
                  } while (!valid(result.str()));
                  return result;
            };
            const auto make_basic_name = [&](const auto &r, const auto &e, const auto &t) {
                  luramas_flag suffix = false;
                  std::string result("");
                  if (e == expr_kinds::upvalue) {
                        result = format->vars.naming_conventions.prefixes.upvalue;
                        suffix = format->vars.naming_conventions.suffix.upvalue;
                  } else {
                        if (t == expr_reg_kinds::arg) {
                              result = format->vars.naming_conventions.prefixes.arg;
                              suffix = format->vars.naming_conventions.suffix.arg;
                        } else {
                              result = format->vars.naming_conventions.prefixes.var;
                              suffix = format->vars.naming_conventions.suffix.var;
                        }
                  }
                  return make_valid(result, r, suffix).str();
            };

            std::vector<ir_stat::space> codes = {code};

            /* Map globals */
            do {
                  const auto code = codes.back();
                  codes.pop_back();
                  for (const auto &c : code) {
                        for (const auto &e : c->extract_exprs()) {
                              for (const auto &o : e->extract_exprs()) {
                                    if (o->is_global_tk()) {
                                          globals.insert(o->v);
                                    }
                                    if (o->is_k<expr_kinds::closure>()) {
                                          codes.emplace_back(o->closure);
                                    }
                              }
                        }
                  }
            } while (!codes.empty());

            /* Make names */
            codes = {code};
            do {
                  const auto code = codes.back();
                  codes.pop_back();
                  if (format->vars.naming_conventions.anotations) {
                        /* TODO CACHE THIS */
                        for (const auto &c : code) {
                              for (const auto &e : c->extract_ordered_deep_exprs()) {
                                    if (e->is_register_reference() && !e->v.empty()) {
                                          vars.try_emplace(e, e->v);
                                    }
                              }
                        }
                  }
                  if (format->vars.naming_conventions.smart.enabled) {
                        generation::tools::smart_variables::generate(code, vars, format, globals, gvn, use_annotations);
                  }
                  for (const auto &c : code) {
                        for (const auto &o : c->args) {
                              vars.try_emplace(o.second, make_basic_name(discriminator++, o.second->k, o.second->rk));
                        }
                        for (const auto &e : c->extract_ordered_deep_exprs()) {
                              switch (e->k) {
                                    case expr_kinds::closure: {
                                          codes.emplace_back(e->closure);
                                          break;
                                    }
                                    case expr_kinds::reg: {
                                          if (use_annotations) {
                                                if (!e->v.empty()) {
                                                      vars.try_emplace(e, e->v);
                                                      break;
                                                }
                                          }
                                          /* Expecting fall to basic naming */
                                          [[fallthrough]];
                                    }
                                    case expr_kinds::upvalue: {
                                          vars.try_emplace(e, make_basic_name(discriminator++, e->k, e->rk));
                                          break;
                                    }
                                    default: {
                                          break;
                                    }
                              }
                        }
                  }
            } while (!codes.empty());

            /* Constant */
            if (format->vars.naming_conventions.smart.constant.enable) {
                  for (auto &[expr, str] : vars) {
                        if (expr->flags.fconstant) {
                              auto copy_str = format->vars.naming_conventions.smart.constant.prefix + str.str();
                              if (format->vars.naming_conventions.smart.constant.upper_case) {
                                    luramas_str_uppercase(copy_str);
                              }
                              if (format->vars.naming_conventions.smart.constant.include_prefix) {
                                    copy_str.insert(0u, format->vars.naming_conventions.smart.prefixes.constant);
                              }
                              str = make_valid(copy_str, expr->reg, format->vars.naming_conventions.smart.constant.discriminator_suffix, format->vars.naming_conventions.smart.constant.upper_case);
                        }
                  }
            }

            /* Casings */
            for (auto &[expr, str] : vars) {
                  switch (format->vars.naming_conventions.case_kind) {
                        case luramas::ir::data::format::case_var_kind::flat_: {
                              luramas_str_case_flatify(str.name);
                              luramas_str_case_flatify(str.descriminator);
                              break;
                        }
                        case luramas::ir::data::format::case_var_kind::camel_: {
                              luramas_str_case_camelify(str.name);
                              luramas_str_case_camelify(str.descriminator);
                              break;
                        }
                        case luramas::ir::data::format::case_var_kind::pascal_: {
                              luramas_str_case_pascalify(str.name);
                              luramas_str_case_pascalify(str.descriminator);
                              break;
                        }
                        case luramas::ir::data::format::case_var_kind::screaming_snake_: {
                              luramas_str_case_screaming_snakify(str.name);
                              luramas_str_case_screaming_snakify(str.descriminator);
                              break;
                        }
                        default: {
                              break;
                        }
                  }
            }
      }

      std::function<std::string(const std::shared_ptr<ir_stat> &, std::intptr_t &, const bool)> stat = [&](const std::shared_ptr<ir_stat> &c, std::intptr_t &indent, const bool last) {
            std::string result("");

            /* Indent pre */
            {
                  if (format->indent.enabeled) {
                        switch (c->k) {
                              case keywords::condition: {
                                    switch (c->c) {
                                          case condition_kind::elseif_: {
                                                indent += format->indent.indent_elseif_pre;
                                                break;
                                          }
                                          case condition_kind::else_: {
                                                indent += format->indent.indent_else_pre;
                                                break;
                                          }
                                          case condition_kind::if_:
                                          default: {
                                                indent += format->indent.indent_if_pre;
                                                break;
                                          }
                                    }
                                    break;
                              }
                              case keywords::end:
                              case keywords::until: {
                                    indent += format->indent.indent_end_pre;
                                    break;
                              }
                              case keywords::forloop_generic: {
                                    indent += format->indent.indent_generic_for_loop_pre;
                                    break;
                              }
                              case keywords::forloop_numeric: {
                                    indent += format->indent.indent_numeric_for_loop_pre;
                                    break;
                              }
                              case keywords::repeat:
                              case keywords::while_: {
                                    indent += format->indent.indent_loop_pre;
                                    break;
                              }
                              case keywords::tag_start: {
                                    indent += format->indent.indent_tag_start_pre;
                                    break;
                              }
                              case keywords::tag_end: {
                                    indent += format->indent.indent_tag_end_pre;
                                    break;
                              }
                              case keywords::page_function_start: {
                                    indent += format->indent.indent_page_function_start_pre;
                                    break;
                              }
                              case keywords::page_function_end: {
                                    indent += format->indent.indent_page_function_end_pre;
                                    break;
                              }
                              default: {
                                    break;
                              }
                        }
                        if (indent > 0) {
                              for (auto i = 0u; i < indent; ++i) {
                                    result += format->indent.indent_space;
                              }
                        }
                  }

                  if (!c->annotation.empty()) {
                        ir::code::emitter::common::comment::comment(syn, result, c->annotation, format, 1u);
                        for (auto i = 0u; i < indent; ++i) {
                              result += format->indent.indent_space;
                        }
                  }

                  /* Linebreak pre */
                  if (std::uint8_t linebreak = 0u; format->linebreak.enabled) {

                        switch (c->k) {
                              case keywords::condition: {
                                    switch (c->c) {
                                          case condition_kind::elseif_: {
                                                linebreak += format->linebreak.elseif_pre;
                                                break;
                                          }
                                          case condition_kind::else_: {
                                                linebreak += format->linebreak.else_pre;
                                                break;
                                          }
                                          case condition_kind::if_:
                                          default: {
                                                linebreak += format->linebreak.if_pre;
                                                break;
                                          }
                                    }
                                    break;
                              }
                              case keywords::end:
                              case keywords::until: {
                                    linebreak += format->linebreak.end_scope_pre;
                                    break;
                              }
                              case keywords::forloop_generic: {
                                    linebreak += format->linebreak.generic_for_loop_pre;
                                    break;
                              }
                              case keywords::tag_start: {
                                    linebreak += format->linebreak.tag_start_pre;
                                    break;
                              }
                              case keywords::tag_end: {
                                    linebreak += format->linebreak.tag_end_pre;
                                    break;
                              }
                              case keywords::forloop_numeric: {
                                    linebreak += format->linebreak.numeric_for_loop_pre;
                                    break;
                              }
                              case keywords::repeat:
                              case keywords::while_: {
                                    linebreak += format->linebreak.loop_pre;
                                    break;
                              }
                              case keywords::page_function_start: {
                                    linebreak += format->linebreak.page_function_start_pre;
                                    break;
                              }
                              case keywords::page_function_end: {
                                    linebreak += format->linebreak.page_function_end_pre;
                                    break;
                              }
                              default: {
                                    break;
                              }
                        }
                        if (linebreak > 0) {
                              luramas::ir::code::emitter::common::line::emit_linebreak(syn, result, linebreak, format);
                        }
                  }
            }

            /* Pre */
            ir::code::emitter::common::line::emit_pre_flags(syn, result, c->k, c->flags, format);

            /* Stats exprs */
            {
                  std::function<std::string(const std::shared_ptr<ir_stat::ir_expr> &, std::intptr_t &, const bool)> expr = [&](const std::shared_ptr<ir_stat::ir_expr> &e, std::intptr_t &indent, const bool from_stat) {
                        std::string retn("");
                        if (!e) {
                              return retn;
                        }
                        switch (e->k) {
                              case expr_kinds::self: {

                                    auto l = expr(e->l, indent, false);
                                    auto r = expr(e->r, indent, false);

                                    luramas_str_sanitize(r);
                                    if (e->l) {

                                          switch (e->l->k) {
                                                case expr_kinds::concat:
                                                case expr_kinds::unary:
                                                case expr_kinds::self:
                                                case expr_kinds::closure:
                                                case expr_kinds::ternary: {
                                                      std::string buffer("");
                                                      luramas::ir::code::emitter::common::line::emit_parenthesize(syn, buffer, l, format);
                                                      l = buffer;
                                                      break;
                                                }
                                                default: {
                                                      switch (e->l->tk) {
                                                            case tkind::none_obj:
                                                            case tkind::string:
                                                            case tkind::lura_int:
                                                            case tkind::boolean:
                                                            case tkind::object:
                                                            case tkind::table:
                                                            case tkind::variadic: {
                                                                  std::string buffer("");
                                                                  luramas::ir::code::emitter::common::line::emit_parenthesize(syn, buffer, l, format);
                                                                  l = buffer;
                                                                  break;
                                                            }
                                                            default: {
                                                                  break;
                                                            }
                                                      }
                                                }
                                          }
                                    }
                                    ir::code::emitter::common::selfcall::emit_selfcall(syn, retn, l, r, format);
                                    break;
                              }
                              case expr_kinds::unary: {

                                    retn = expr(e->l, indent, false);
                                    if (e->l->is_tk<tkind::table>()) {
                                          std::string buffer("");
                                          ir::code::emitter::common::line::emit_parenthesize(syn, buffer, retn, format);
                                          retn = buffer;
                                    }
                                    ir::code::emitter::common::unary::emit_unary(syn, retn, e->u, format);
                                    break;
                              }
                              case expr_kinds::call: {

                                    auto l = expr(e->l, indent, false);
                                    std::vector<std::string> args;
                                    for (const auto &m : e->members) {
                                          args.emplace_back(expr(m, indent, false));
                                    }
                                    ir::code::emitter::common::call::emit_call(syn, retn, l, args, format);
                                    break;
                              }
                              case expr_kinds::arith: {

                                    auto l = expr(e->l, indent, false);
                                    auto r = expr(e->r, indent, false);
                                    ir::code::emitter::common::arith::emit_arith_operation(syn, retn, e->b, l, r, format);
                                    std::string buffer("");
                                    if (!from_stat) {
                                          ir::code::emitter::common::line::emit_parenthesize(syn, buffer, retn, format);
                                    } else {
                                          buffer = retn;
                                    }
                                    retn = buffer;
                                    break;
                              }
                              case expr_kinds::cast: {

                                    ir::code::emitter::common::types::emit_cast(syn, retn, e->non_native, expr(e->l, indent, false), format);
                                    break;
                              }
                              case expr_kinds::memoryread: {

                                    std::string buffer("");
                                    auto t = expr(e->l, indent, false);
                                    if (e->r) {
                                          auto o = expr(e->r, indent, false);
                                          ir::code::emitter::common::arith::emit_arith_operation(syn, buffer, il::arch::data::bin_kinds::add_, t, o, format);
                                    } else {
                                          buffer = t;
                                    }
                                    ir::code::emitter::common::memory::emit_memread(syn, retn, e->non_native, buffer, format);
                                    break;
                              }
                              case expr_kinds::bitread: {

                                    ir::code::emitter::common::types::emit_bitread(syn, retn, e->non_native, expr(e->l, indent, false), expr(e->r, indent, false), expr(e->ev, indent, false), format);
                                    break;
                              }
                              case expr_kinds::idx: {

                                    auto l = expr(e->l, indent, false);
                                    auto r = expr(e->r, indent, false);
                                    if (e->l && e->l->is_complex_tk()) {
                                          std::string buffer("");
                                          ir::code::emitter::common::line::emit_parenthesize(syn, buffer, l, format);
                                          l = buffer;
                                    }
                                    if (e->r && e->r->is_tk<tkind::string>() && !e->r->is_register_reference()) {
                                          auto copy_r = r;
                                          luramas_str_sanitize(copy_r);
                                          if (luramas_str_valid_index(copy_r) && !std::any_of(extra::black_listed_idxs.begin(), extra::black_listed_idxs.end(), [&](const auto &i) { return copy_r == i; })) {
                                                ir::code::emitter::common::table::emit_index_generic(syn, retn, l, copy_r, format);
                                                break;
                                          }
                                    }
                                    ir::code::emitter::common::table::emit_index(syn, retn, l, r, format);
                                    break;
                              }
                              case expr_kinds::condition: {

                                    auto l = expr(e->l, indent, false);
                                    auto r = expr(e->r, indent, false);
                                    if (e->e == expr_logical::or_) {
                                          e->b = il::arch::data::bin_kinds::or_;
                                    } else if (e->e == expr_logical::and_) {
                                          e->b = il::arch::data::bin_kinds::and_;
                                    }
                                    ir::code::emitter::common::logical::emit_logical_compare(syn, retn, e->b, l, r, format, !from_stat, !from_stat);
                                    break;
                              }
                              case expr_kinds::concat: {

                                    std::vector<std::string> args;
                                    for (const auto &m : e->members) {
                                          args.emplace_back(expr(m, indent, false));
                                    }
                                    ir::code::emitter::common::concat::emit_concat(syn, retn, args, format);
                                    break;
                              }
                              case expr_kinds::ternary: {

                                    std::string cond("");
                                    auto l = expr(e->l, indent, false);
                                    auto r = expr(e->r, indent, false);
                                    if (e->e == expr_logical::or_) {
                                          e->b = il::arch::data::bin_kinds::or_;
                                    } else if (e->e == expr_logical::and_) {
                                          e->b = il::arch::data::bin_kinds::and_;
                                    }
                                    std::string else_prefix("");
                                    auto else_collapse = indent;
                                    if (format->indent.collapse.ternaries) {
                                          else_collapse += format->indent.collapse.indenting;
                                          code::emitter::common::line::emit_linebreak(syn, else_prefix, 1u, format);
                                          if (else_collapse > 0) {
                                                for (auto i = 0u; i < else_collapse; ++i) {
                                                      else_prefix += format->indent.indent_space;
                                                }
                                          }
                                    }
                                    std::string buffer("");
                                    ir::code::emitter::common::logical::emit_logical_compare(syn, cond, e->b, l, r, format);
                                    ir::code::emitter::common::ternary::emit_ternary(syn, buffer, cond, expr(e->ev, else_collapse, false), else_prefix + expr(e->xv, else_collapse, false), format);
                                    if (!from_stat) {
                                          std::string parenthesize_buffer("");
                                          ir::code::emitter::common::line::emit_parenthesize(syn, parenthesize_buffer, buffer, format);
                                          retn = parenthesize_buffer;
                                    } else {
                                          retn = buffer;
                                    }
                                    break;
                              }
                              case expr_kinds::closure: {

                                    /* Closure params */
                                    std::vector<std::string> params;
                                    if (!e->closure.empty()) {
                                          for (const auto &m : e->closure.front()->parameters) {
                                                params.emplace_back(expr(m, indent, false));
                                          }
                                          if (e->closure.front()->flags.fvariadic_def) {
                                                params.emplace_back(expr(param_variadic, indent, false));
                                          }
                                    }
                                    indent += format->indent.indent_anonymous_function_pre;
                                    std::string data("");
                                    for (auto i = 0u; i < e->closure.size(); ++i) {
                                          const auto &c = e->closure[i];
                                          data += stat(c, indent, i == e->closure.size() - 1u);
                                    }
                                    indent += format->indent.indent_anonymous_function_post;
                                    ir::code::emitter::common::function::emit_anonymous_function(syn, retn, params, data, format);
                                    if (format->indent.enabeled && indent > 0) {
                                          for (auto i = 0u; i < indent; ++i) {
                                                retn += format->indent.indent_space;
                                          }
                                    }
                                    ir::code::emitter::common::function::emit_anonymous_function_end(syn, retn, format);
                                    break;
                              }
                              case expr_kinds::flag: {

                                    ir::code::emitter::common::flags::emit_flag(syn, retn, expr(e->r, indent, false), format);
                                    break;
                              }
                              case expr_kinds::unpack: {
                                    retn = expr(e->l, indent, false);
                                    break;
                              }
                              case expr_kinds::reg:
                              case expr_kinds::upvalue: {
                                    retn = vars[e].str();
                                    break;
                              }
                              default: {
                                    switch (e->tk) {
                                          case tkind::boolean: {
                                                ir::code::emitter::common::datatype::emit_boolean(syn, retn, e->bv, format);
                                                break;
                                          }
                                          case tkind::table: {

                                                std::intptr_t member_indent = 0u;
                                                if (!format->indent.collapse.disabled && format->indent.collapse.table && format->indent.collapse.table <= e->tmembers.size() && indent + format->indent.collapse.indenting >= 0) {
                                                      member_indent = indent + format->indent.collapse.indenting;
                                                }

                                                auto mem_indent = member_indent ? member_indent : indent;
                                                std::vector<std::pair<std::string, std::string>> members;
                                                for (const auto &m : e->tmembers) {
                                                      members.emplace_back(std::make_pair(expr(m.first, mem_indent, false), expr(m.second, mem_indent, false)));
                                                }
                                                ir::code::emitter::common::table::emit_table(syn, retn, member_indent, members, format);
                                                break;
                                          }
                                          case tkind::variadic: {
                                                ir::code::emitter::common::datatype::emit_variadic(syn, retn, format);
                                                break;
                                          }
                                          case tkind::lura_int: {
                                                auto n_str = luramas::str::to_string(e->n);
                                                luramas_str_integer(n_str);
                                                ir::code::emitter::common::datatype::emit_integer(syn, retn, n_str, format);
                                                break;
                                          }
                                          case tkind::string: {
                                                ir::code::emitter::common::datatype::emit_string(syn, retn, e->v, format);
                                                break;
                                          }
                                          case tkind::global: {
                                                ir::code::emitter::common::datatype::emit_global(syn, retn, e->v, format);
                                                break;
                                          }
                                          case tkind::kvalue: {
                                                ir::code::emitter::common::datatype::emit_kval(syn, retn, e->v, format);
                                                break;
                                          }
                                          case tkind::stack: {
                                                ir::code::emitter::common::datatype::emit_stack(syn, retn, format);
                                                break;
                                          }
                                          case tkind::controller: {
                                                ir::code::emitter::common::datatype::emit_controller(syn, retn, format);
                                                break;
                                          }
                                          default: {
                                                ir::code::emitter::common::datatype::emit_none(syn, retn, format);
                                                break;
                                          }
                                    }
                                    break;
                              }
                        }
                        LURAMAS_ASSERT_DBG(retn.empty(), "EXPR is empty", {
                              e->dump("DEBUG");
                        });
                        return retn;
                  };

                  switch (c->k) {
                        case keywords::label: {
                              std::string name(format->stats.naming_convention.prefixes.label + "_" + std::to_string(c->label));
                              ir::code::emitter::common::branch::emit_label(syn, result, name, format);
                              break;
                        }
                        case keywords::repeat: {
                              ir::code::emitter::common::loop::emit_repeat(syn, result, format);
                              break;
                        }
                        case keywords::end: {
                              ir::code::emitter::common::branch::emit_scope_end(syn, result, format);
                              break;
                        }
                        case keywords::break_: {
                              ir::code::emitter::common::loop::emit_loop_break(syn, result, format);
                              break;
                        }
                        case keywords::continue_: {
                              ir::code::emitter::common::loop::emit_loop_continue(syn, result, format);
                              break;
                        }
                        case keywords::goto_label: {
                              std::string name(format->stats.naming_convention.prefixes.label + "_" + std::to_string(c->jlabel));
                              ir::code::emitter::common::branch::emit_goto_label(syn, result, name, format);
                              break;
                        }
                        case keywords::memoryset: {

                              std::string buffer("");
                              if (auto t = expr(c->l, indent, true); c->v) {
                                    ir::code::emitter::common::arith::emit_arith_operation(syn, buffer, il::arch::data::bin_kinds::add_, t, expr(c->v, indent, true), format);
                              } else {
                                    buffer = t;
                              }
                              ir::code::emitter::common::memory::emit_memwrite(syn, result, luramas::ir::types::generate::basic(static_cast<luramas_bitwidth>(c->extra_bits), false), buffer, expr(c->r, indent, true), format);
                              break;
                        }
                        case keywords::table_assign: {

                              auto l = expr(c->l->l, indent, true);
                              auto r = expr(c->l->r, indent, true);
                              auto v = expr(c->r, indent, true);
                              std::string index("");
                              if (c->l->l && (c->l->l->is_complex_k() || c->l->l->is_complex_tk())) {
                                    std::string buffer("");
                                    ir::code::emitter::common::line::emit_parenthesize(syn, buffer, l, format);
                                    l = buffer;
                              }
                              auto vi = r;
                              luramas_str_sanitize(vi);
                              if (!c->l->r->is_register_reference() && luramas_str_valid_index(vi) && !std::any_of(extra::black_listed_idxs.begin(), extra::black_listed_idxs.end(), [&](const auto &i) { return vi == i; })) {
                                    ir::code::emitter::common::table::emit_index_generic(syn, index, l, vi, format);
                              } else {
                                    ir::code::emitter::common::table::emit_index(syn, index, l, r, format);
                              }
                              ir::code::emitter::common::assignment::assignment(syn, result, {index}, {v}, format);
                              break;
                        }
                        case keywords::table_setlist: {

                              auto l = expr(c->l, indent, true);
                              std::vector<std::pair<std::string, std::string>> members;
                              for (const auto &m : c->tmembers) {
                                    members.emplace_back(std::make_pair("", expr(m, indent, true)));
                              }

                              std::string data("");
                              ir::code::emitter::common::table::emit_table(syn, data, indent, members, format);
                              ir::code::emitter::common::assignment::assignment(syn, result, {l}, {data}, format);
                              break;
                        }
                        case keywords::forloop_numeric: {

                              auto def = expr(c->lba, indent, true);
                              auto l = expr(c->l, indent, true);
                              auto r = expr(c->r, indent, true);
                              std::vector<std::string> iter({l, r});
                              if (!ir::tools::exprs::is<std::int32_t>(c->v, 1u)) {
                                    iter.emplace_back(expr(c->v, indent, true));
                              }
                              std::vector<std::string> vars({def});
                              ir::code::emitter::common::for_::emit_for<true>(syn, result, vars, iter, format);
                              break;
                        }
                        case keywords::forloop_generic: {

                              std::vector<std::string> vars;
                              for (const auto &m : c->members) {
                                    vars.emplace_back(expr(m, indent, true));
                              }
                              std::vector<std::string> iter;
                              for (const auto &m : c->smembers) {
                                    iter.emplace_back(expr(m, indent, true));
                              }
                              ir::code::emitter::common::for_::emit_for(syn, result, vars, iter, format);
                              break;
                        }
                        case keywords::call: {

                              auto call = expr(c->l, indent, true);
                              std::vector<std::string> members;
                              for (const auto &m : c->members) {
                                    if (m) {
                                          members.emplace_back(expr(m, indent, true));
                                    }
                              }
                              ir::code::emitter::common::call::emit_call(syn, result, call, members, format);
                              break;
                        }
                        case keywords::tag_start: {

                              std::vector<std::pair<std::string, std::string>> ids;
                              for (const auto &[k, v] : c->v->tmembers) {
                                    if (k && v) {
                                          ids.emplace_back(expr(k, indent, true), expr(v, indent, true));
                                    }
                              }
                              ir::code::emitter::common::tags::start(syn, result, expr(c->r, indent, true), ids, format);
                              break;
                        }
                        case keywords::tag_end: {

                              ir::code::emitter::common::tags::end(syn, result, expr(c->r, indent, true), format);
                              break;
                        }
                        case keywords::page_function_end: {

                              ir::code::emitter::common::pages::emit_page_function_end(syn, result, c->r->extract_integral_base(), format);
                              break;
                        }
                        case keywords::page_function_start: {

                              const auto id = c->r->extract_integral_base();
                              ir::code::emitter::common::pages::emit_page_function_start(syn, result, signatures[id].func_name, signatures[id].args, signatures[id].arg_types, signatures[id].result_types, format);
                              break;
                        }
                        case keywords::page_function_goto: {

                              std::vector<std::string> members;
                              for (const auto &m : c->members) {
                                    if (m) {
                                          members.emplace_back(expr(m, indent, true));
                                    }
                              }
                              const auto id = c->r->extract_integral_base();
                              const auto &sig = signatures[id];

                              /* Controller */
                              std::optional<luramas_id> ctrl = std::nullopt;
                              if (c->v && c->v->is_integral()) {
                                    ctrl = c->v->extract_integral_base();
                              } else if (sig.fuses_controller) {
                                    ctrl = 0u;
                              }

                              /* Emitter */
                              if (c->pfk == page_function_goto_kind::jump) {
                                    ir::code::emitter::common::pages::emit_page_function_goto(syn, result, sig.func_name, ctrl, members, format);
                              } else {
                                    ir::code::emitter::common::pages::emit_page_function_call(syn, result, sig.func_name, ctrl, expr(c->l, indent, true), expr(c->lba, indent, true), members, format);
                              }
                              break;
                        }
                        case keywords::retn: {

                              if (last && format->stats.useless_return && c->members.empty()) {
                                    return std::string("");
                              } else {
                                    std::vector<std::string> members;
                                    for (const auto &m : c->members) {
                                          members.emplace_back(expr(m, indent, true));
                                    }
                                    ir::code::emitter::common::return_::emit_return(syn, result, members, format);
                              }
                              break;
                        }
                        case keywords::assignment: {

                              std::vector<std::string> vars;
                              if (c->l) {
                                    vars.emplace_back(expr(c->l, indent, true));
                              } else {
                                    for (const auto &m : c->members) {
                                          vars.emplace_back(expr(m, indent, true));
                                    }
                              }
                              if (c->r && c->l) {

                                    if (format->stats.arith_assignment &&
                                        luramas::ir::code::emitter::common::supported_arith_assignment(syn, c->r->b) &&
                                        luramas::il::arch::data::is_kinds::arith(c->r->b) && c->r->l && luramas::ir::tools::exprs::values::same_reference(c->l, c->r->l)) {

                                          ir::code::emitter::common::assignment::arith::emit_arith_assignment(syn, result, c->r->b, vars, {expr(c->r->r, indent, true)}, format);
                                          break;
                                    } else if (c->r->is_k<expr_kinds::closure>()) {

                                          /* Closure params */
                                          std::vector<std::string> params;
                                          if (!c->r->closure.empty()) {
                                                for (const auto &m : c->r->closure.front()->parameters) {
                                                      params.emplace_back(expr(m, indent, true));
                                                }
                                                if (c->r->closure.front()->flags.fvariadic_def) {
                                                      params.emplace_back(expr(param_variadic, indent, true));
                                                }
                                          }

                                          const auto k = (c->flags.fdefine && c->l->is_register_reference()) ? extra::closure_kind::local : (c->l->is_global_tk() ? extra::closure_kind::global : extra::closure_kind::anonymous);
                                          if (k != extra::closure_kind::anonymous) {
                                                switch (k) {
                                                      case extra::closure_kind::local: {
                                                            indent += format->indent.indent_scope_function_pre;
                                                            break;
                                                      }
                                                      case extra::closure_kind::global: {
                                                            indent += format->indent.indent_global_function_pre;
                                                            break;
                                                      }
                                                      default: {
                                                            break;
                                                      }
                                                }
                                                std::string data("");
                                                for (auto i = 0u; i < c->r->closure.size(); ++i) {
                                                      const auto &x = c->r->closure[i];
                                                      data += stat(x, indent, i == c->r->closure.size() - 1u);
                                                }
                                                switch (k) {
                                                      case extra::closure_kind::local: {

                                                            indent += format->indent.indent_scope_function_post;
                                                            ir::code::emitter::common::function::emit_local_function(syn, result, vars.front(), params, data, format);
                                                            if (format->indent.enabeled && indent > 0) {
                                                                  for (auto i = 0u; i < indent; ++i) {
                                                                        result += format->indent.indent_space;
                                                                  }
                                                            }
                                                            ir::code::emitter::common::function::emit_local_function_end(syn, result, format);
                                                            break;
                                                      }
                                                      case extra::closure_kind::global: {

                                                            indent += format->indent.indent_global_function_post;
                                                            ir::code::emitter::common::function::emit_global_function(syn, result, vars.front(), params, data, format);
                                                            if (format->indent.enabeled && indent > 0) {
                                                                  for (auto i = 0u; i < indent; ++i) {
                                                                        result += format->indent.indent_space;
                                                                  }
                                                            }
                                                            ir::code::emitter::common::function::emit_global_function_end(syn, result, format);
                                                            break;
                                                      }
                                                      default: {
                                                            break;
                                                      }
                                                }
                                                break;
                                          }
                                    }
                              }
                              if (c->flags.fdefine) {
                                    ir::code::emitter::common::assignment::initial_assignment(syn, result, vars, {expr(c->r, indent, true)}, c->l->flags.fconstant, format);
                              } else {
                                    ir::code::emitter::common::assignment::assignment(syn, result, vars, {expr(c->r, indent, true)}, format);
                              }
                              break;
                        }
                        case keywords::condition: {

                              switch (c->c) {
                                    case condition_kind::else_: {
                                          ir::code::emitter::common::branch::emit_else(syn, result, format);
                                          break;
                                    }
                                    case condition_kind::elseif_: {
                                          auto l = expr(c->l, indent, true);
                                          auto r = expr(c->r, indent, true);
                                          ir::code::emitter::common::branch::emit_elseif(syn, result, c->b, l, r, format);
                                          break;
                                    }
                                    case condition_kind::if_:
                                    default: {
                                          auto l = expr(c->l, indent, true);
                                          auto r = expr(c->r, indent, true);
                                          ir::code::emitter::common::branch::emit_if(syn, result, c->b, l, r, format);
                                          break;
                                    }
                              }
                              break;
                        }
                        case keywords::condition_goto: {

                              /* if (?) */
                              auto l = expr(c->l, indent, true);
                              auto r = expr(c->r, indent, true);
                              ir::code::emitter::common::branch::emit_if(syn, result, c->b, l, r, format);

                              /* goto label_? */
                              std::string name(format->stats.naming_convention.prefixes.label + "_" + std::to_string(c->jlabel));
                              result += " ";
                              ir::code::emitter::common::branch::emit_goto_label(syn, result, name, format);

                              /* ; */
                              ir::code::emitter::common::line::emit_semicolon(syn, result, format);

                              /* end */
                              result += " ";
                              ir::code::emitter::common::branch::emit_scope_end(syn, result, format);
                              break;
                        }
                        case keywords::while_: {
                              auto l = expr(c->l, indent, true);
                              auto r = expr(c->r, indent, true);
                              ir::code::emitter::common::loop::emit_while(syn, result, c->b, l, r, format);
                              break;
                        }
                        case keywords::until: {
                              auto l = expr(c->l, indent, true);
                              auto r = expr(c->r, indent, true);
                              ir::code::emitter::common::loop::emit_until(syn, result, c->b, l, r, format);
                              break;
                        }
                        default: {
                              if (c->annotation.empty()) {
                                    return std::string("");
                              }
                              break;
                        }
                  }
            }

            /* Post */
            ir::code::emitter::common::line::emit_post_flags(syn, result, c->k, c->flags, format);

            /* ; */
            {
                  if (format->stats.semicolon.enabeled) {
                        switch (c->k) {
                              case keywords::end: {
                                    if (format->stats.semicolon.semi_end) {
                                          ir::code::emitter::common::line::emit_semicolon(syn, result, format);
                                    }
                                    break;
                              }
                              case keywords::break_: {
                                    if (format->stats.semicolon.semi_implicit_jump) {
                                          ir::code::emitter::common::line::emit_semicolon(syn, result, format);
                                    }
                                    break;
                              }
                              case keywords::continue_: {
                                    if (format->stats.semicolon.semi_implicit_jump) {
                                          ir::code::emitter::common::line::emit_semicolon(syn, result, format);
                                    }
                                    break;
                              }
                              case keywords::repeat: {
                                    if (format->stats.semicolon.semi_repeat) {
                                          ir::code::emitter::common::line::emit_semicolon(syn, result, format);
                                    }
                                    break;
                              }
                              case keywords::retn: {
                                    if (format->stats.semicolon.semi_return) {
                                          ir::code::emitter::common::line::emit_semicolon(syn, result, format);
                                    }
                                    break;
                              }
                              case keywords::until: {
                                    if (format->stats.semicolon.semi_until) {
                                          ir::code::emitter::common::line::emit_semicolon(syn, result, format);
                                    }
                                    break;
                              }
                              case keywords::call:
                              case keywords::assignment:
                              case keywords::goto_label:
                              case keywords::table_assign:
                              case keywords::memoryset:
                              case keywords::table_setlist:
                              case keywords::page_function_goto: {
                                    ir::code::emitter::common::line::emit_semicolon(syn, result, format);
                                    break;
                              }
                              default: {
                                    break;
                              }
                        }
                  }
            }

            /* Indent post */
            {
                  if (format->indent.enabeled) {
                        switch (c->k) {
                              case keywords::condition: {
                                    switch (c->c) {
                                          case condition_kind::elseif_: {
                                                indent += format->indent.indent_elseif_post;
                                                break;
                                          }
                                          case condition_kind::else_: {
                                                indent += format->indent.indent_else_post;
                                                break;
                                          }
                                          case condition_kind::if_:
                                          default: {
                                                indent += format->indent.indent_if_post;
                                                break;
                                          }
                                    }
                                    break;
                              }
                              case keywords::end:
                              case keywords::until: {
                                    indent += format->indent.indent_end_post;
                                    break;
                              }
                              case keywords::forloop_generic: {
                                    indent += format->indent.indent_generic_for_loop_post;
                                    break;
                              }
                              case keywords::forloop_numeric: {
                                    indent += format->indent.indent_numeric_for_loop_post;
                                    break;
                              }
                              case keywords::repeat:
                              case keywords::while_: {
                                    indent += format->indent.indent_loop_post;
                                    break;
                              }
                              case keywords::tag_start: {
                                    indent += format->indent.indent_tag_start_post;
                                    break;
                              }
                              case keywords::tag_end: {
                                    indent += format->indent.indent_tag_end_post;
                                    break;
                              }
                              case keywords::page_function_start: {
                                    indent += format->indent.indent_page_function_start_post;
                                    break;
                              }
                              case keywords::page_function_end: {
                                    indent += format->indent.indent_page_function_end_post;
                                    break;
                              }
                              default: {
                                    break;
                              }
                        }
                  }

                  /* Linebreak pre */
                  if (auto linebreak = format->linebreak.amount; format->linebreak.enabled) {

                        switch (c->k) {
                              case keywords::condition: {
                                    switch (c->c) {
                                          case condition_kind::elseif_: {
                                                linebreak += format->linebreak.elseif_post;
                                                break;
                                          }
                                          case condition_kind::else_: {
                                                linebreak += format->linebreak.else_post;
                                                break;
                                          }
                                          case condition_kind::if_:
                                          default: {
                                                linebreak += format->linebreak.if_post;
                                                break;
                                          }
                                    }
                                    break;
                              }
                              case keywords::end:
                              case keywords::until: {
                                    linebreak += format->linebreak.end_scope_post;
                                    break;
                              }
                              case keywords::forloop_generic: {
                                    linebreak += format->linebreak.generic_for_loop_post;
                                    break;
                              }
                              case keywords::forloop_numeric: {
                                    linebreak += format->linebreak.numeric_for_loop_post;
                                    break;
                              }
                              case keywords::repeat:
                              case keywords::while_: {
                                    linebreak += format->linebreak.loop_post;
                                    break;
                              }
                              case keywords::tag_start: {
                                    linebreak += format->linebreak.tag_start_post;
                                    break;
                              }
                              case keywords::tag_end: {
                                    linebreak += format->linebreak.tag_end_post;
                                    break;
                              }
                              case keywords::page_function_start: {
                                    linebreak += format->linebreak.page_function_start_post;
                                    break;
                              }
                              case keywords::page_function_end: {
                                    linebreak += format->linebreak.page_function_end_post;
                                    break;
                              }
                              default: {
                                    break;
                              }
                        }
                        if (linebreak > 0) {
                              luramas::ir::code::emitter::common::line::emit_linebreak(syn, result, linebreak, format);
                        }
                  }
            }

            return result;
      };

      std::string result("");

      /* Add pages signature and main function */
      {

            /* Generate signatures */
            std::vector<signature> sigs;
            switch (syn) {
                  case ir::code::emitter::syntax::emitter_syntax::cpp: {

                        for (auto i = LURAMAS_IR_ENTRY; i < code.size(); ++i) {

                              if (const auto &p = code[i]; p->is_k<keywords::page_function_start>() && i + 1u < code.size()) {

                                    if (const auto &def = code[i + 1u]; def->is_k<keywords::definition>()) {

                                          signature sig;
                                          sig.id = p->r->extract_integral_base();
                                          sig.func_name = format->vars.naming_conventions.prefixes.page_function + std::to_string(sig.id);
                                          sig.fuses_controller = def->flags.fdef_uses_controller;
                                          if (sig.fuses_controller) {
                                                std::string ctrl("");
                                                ir::code::emitter::common::datatype::emit_controller(syn, ctrl, format);
                                                sig.args.emplace_back(ctrl);
                                                sig.arg_types.emplace_back(ir::types::signature(types::common::i32, true));
                                          }
                                          for (const auto &[_, e] : def->args) {
                                                sig.args.emplace_back(vars[e].str());
                                          }
                                          for (const auto &e : def->meta) {
                                                if (e->is_k<expr_kinds::cast>()) {
                                                      sig.arg_types.emplace_back(ir::types::signature(e->non_native, e->l && e->l->is_register_reference() ? e->l->flags.fconstant : false));
                                                }
                                          }
                                          for (const auto &e : def->smembers) {
                                                if (e->is_k<expr_kinds::cast>()) {
                                                      sig.result_types.emplace_back(ir::types::signature(e->non_native));
                                                }
                                          }
                                          signatures[sig.id] = sig;
                                          sigs.emplace_back(sig);
                                    }
                              }
                        }
                        break;
                  }
                  default: {
                        break;
                  }
            }
            if (!sigs.empty()) {

                  /* Add signatures */
                  for (const auto &s : sigs) {
                        ir::code::emitter::common::pages::emit_page_function_start_signature(syn, result, s.func_name, s.args, s.arg_types, s.result_types, format);
                        ir::code::emitter::common::line::emit_semicolon(syn, result, format);
                        ir::code::emitter::common::line::emit_linebreak(syn, result, 1u, format);
                  }

                  /* Seperator */
                  ir::code::emitter::common::line::emit_linebreak(syn, result, 2u, format);
            }
      }

      auto indent = static_cast<const std::intptr_t>(format->indent.indent_start);
      for (auto i = 0u; i < code.size(); ++i) {
            result += stat(code[i], indent, i == code.size() - 1u);
      }
      return result;
}
