#include "../../lifter/tools/extras/stats.hpp"
#include "../../lifter/tools/tools.hpp"
#include "data/renaming/acronyms.hpp"
#include "data/renaming/functions.hpp"
#include "data/renaming/words.hpp"
#include "tools.hpp"

namespace naming_conventions {

      namespace prefix {

            /* Get prefix of expr K */
            std::string str(const std::shared_ptr<ir_stat::ir_expr> &expr, const std::shared_ptr<luramas::ir::data::format::format> &format) {

                  if (expr) {
                        switch (expr->k) {
                              case expr_kinds::reg: {
                                    switch (expr->rk) {
                                          case expr_reg_kinds::arg: {
                                                return format->vars.naming_conventions.smart.prefixes.argument;
                                          }
                                          default: {
                                                break;
                                          }
                                    }
                                    return format->vars.naming_conventions.smart.prefixes.variable;
                              }
                              case expr_kinds::upvalue: {
                                    return format->vars.naming_conventions.smart.prefixes.upvalue;
                              }
                              default: {
                                    break;
                              }
                        }
                  }
                  return "";
            }
      } // namespace prefix

      /*  
            Extracts up to `num` segments from `str`, split by `module_delimiter` from the end.  
            Joins segments with `delimiter`, converts to lowercase, and returns the result.  
      */
      std::string split_constants(const std::string &str, const std::string &delimiter, const char module_delimiter, const std::size_t num = 2u) {

            std::vector<std::string> segments;
            auto end = str.size();
            auto pos = str.find_last_of(module_delimiter);
            while (pos != std::string::npos && segments.size() < num) {
                  segments.push_back(str.substr(pos + 1, end - pos - 1));
                  end = pos;
                  pos = str.find_last_of(module_delimiter, pos - 1);
            }

            if (segments.size() < num && end) {
                  segments.push_back(str.substr(0u, end));
            }

            std::string result("");
            for (auto it = segments.rbegin(); it != segments.rend(); ++it) {
                  if (!result.empty()) {
                        result += delimiter;
                  }
                  result += *it;
            }

            luramas_str_lowercase(result);
            return result;
      }

      const char *const str(const tkind k) {
            switch (k) {
                  case tkind::none_obj: {
                        return "obj";
                  }
                  case tkind::string: {
                        return "str";
                  }
                  case tkind::lura_int: {
                        return "val";
                  }
                  case tkind::global: {
                        return "glb";
                  }
                  case tkind::boolean: {
                        return "bool";
                  }
                  case tkind::kvalue: {
                        return "kv";
                  }
                  case tkind::table: {
                        return "tab";
                  }
                  case tkind::stack: {
                        return "stk";
                  }
                  case tkind::controller: {
                        return "ctr";
                  }
                  case tkind::extpr: {
                        return "extpr";
                  }
                  case tkind::variadic: {
                        return "vai";
                  }
                  default: {
                        break;
                  }
            }
            return nullptr;
      }
      const char *const str(const expr_kinds k) {
            switch (k) {
                  case expr_kinds::call: {
                        return "res";
                  }
                  case expr_kinds::arith: {
                        return "res";
                  }
                  case expr_kinds::ternary:
                  case expr_kinds::condition: {
                        return "cmp";
                  }
                  case expr_kinds::concat: {
                        return "built_str";
                  }
                  case expr_kinds::unary: {
                        return "unary";
                  }
                  case expr_kinds::idx: {
                        return "idx";
                  }
                  case expr_kinds::reg: {
                        return "v";
                  }
                  case expr_kinds::self: {
                        return "scall";
                  }
                  case expr_kinds::closure: {
                        return "func";
                  }
                  case expr_kinds::upvalue: {
                        return "u";
                  }
                  case expr_kinds::unpack: {
                        return "unpacked";
                  }
                  case expr_kinds::cast: {
                        return "cst";
                  }
                  case expr_kinds::memoryread: {
                        return "mem";
                  }
                  case expr_kinds::bitwrite: {
                        return "bitw";
                  }
                  case expr_kinds::bitread: {
                        return "bits";
                  }
                  case expr_kinds::flag: {
                        return "flg";
                  }
                  case expr_kinds::page_function_call: {
                        return "pf";
                  }
                  default: {
                        break;
                  }
            }
            return nullptr;
      }

      std::string str(boost::unordered_flat_map<std::shared_ptr<ir_stat::ir_expr>, luramas::ir::code::generation::tools::smart_variables::naming> &expr_map, const std::shared_ptr<ir_stat::ir_expr> &e, luramas_address &depth, luramas_address &valid_depth, const luramas_address max_depth, const char module_delimiter, const std::string &delimeter) {

            if (e == nullptr || ++depth >= max_depth) {
                  return "";
            }

            const auto transform = [&](std::string &s) {
                  if (!s.empty()) {
                        luramas_str_sanitize(s);
                        switch (luramas::ir::code::generation::tools::smart_variables::data::functions::common(s)) {
                              case luramas::ir::code::generation::tools::smart_variables::data::functions::kind::first_arg: {

                                    if (!e->members.empty()) {
                                          s = str(expr_map, e->members.front(), depth, valid_depth, max_depth, module_delimiter, delimeter);
                                    }
                                    break;
                              }
                              default: {
                                    luramas::ir::code::generation::tools::smart_variables::data::words::common_prefix(s);
                                    break;
                              }
                        }
                        luramas_str_sanitize(s);
                        luramas_str_case_snakify(s);
                  }
                  return;
            };

            switch (e->tk) {
                  case tkind::string:
                  case tkind::kvalue: {
                        auto str = e->v;
                        luramas_str_sanitize(str);
                        return str;
                  }
                  default: {
                        break;
                  }
            }
            switch (e->k) {
                  case expr_kinds::condition: {
                        break;
                  }
                  case expr_kinds::idx: {

                        auto l = (e->l && e->l->k == expr_kinds::idx) ? str(e->l->k) : str(expr_map, e->l, depth, valid_depth, max_depth, module_delimiter, delimeter);
                        auto r = str(expr_map, e->r, depth, valid_depth, max_depth, module_delimiter, delimeter);

                        transform(l);
                        transform(r);

                        const auto valid = luramas_str_valid_index(r);
                        if (!l.empty() && !r.empty() && valid) {
                              ++valid_depth;
                              return l + "." + r;
                        }

                        l = split_constants(l, delimeter, module_delimiter, valid + 1u);
                        if (!l.empty()) {
                              return (valid) ? l : (str(e->k) + delimeter + l);
                        }
                        break;
                  }
                  case expr_kinds::call: {

                        /* STRING/KVALUE:[KNOWN]() */
                        std::string v("");
                        if (e->l && e->l->is_k<expr_kinds::self>() && e->l->r && e->l->r->is_name_qualifier()) {

                              v = str(expr_map, e->l->r, depth, valid_depth, max_depth, module_delimiter, delimeter);
                              if (luramas::ir::code::generation::tools::smart_variables::data::functions::common(v) == luramas::ir::code::generation::tools::smart_variables::data::functions::kind::first_arg) {

                                    if (!e->members.empty()) {
                                          v = str(expr_map, e->members.front(), depth, valid_depth, max_depth, module_delimiter, delimeter);
                                          luramas_str_sanitize(v);
                                          luramas_str_case_snakify(v);
                                    } else {
                                          v.clear();
                                    }
                              } else {
                                    v.clear();
                              }
                        }

                        auto function = str(expr_map, v.empty() ? e->l : e->l->l, depth, valid_depth, max_depth, module_delimiter, delimeter);
                        transform(function);

                        ++valid_depth;
                        if (v.empty()) {
                              return function;
                        }
                        if (function.empty()) {
                              return v;
                        }
                        return function + delimeter + v;
                  }
                  case expr_kinds::self: {

                        auto lvalue = str(expr_map, e->l, depth, valid_depth, max_depth, module_delimiter, delimeter);
                        transform(lvalue);

                        auto rvalue = str(expr_map, e->r, depth, valid_depth, max_depth, module_delimiter, delimeter);
                        transform(rvalue);

                        ++valid_depth;
                        if (rvalue.empty()) {
                              return lvalue;
                        }
                        if (lvalue.empty()) {
                              return rvalue;
                        }
                        return lvalue + delimeter + rvalue;
                  }
                  case expr_kinds::reg:
                  case expr_kinds::upvalue: {
                        auto it = expr_map.find(e);
                        if (it != expr_map.end()) {
                              return it->second.str();
                        }
                  }
                  default: {
                        break;
                  }
            }
            return "";
      }
} // namespace naming_conventions

void luramas::ir::code::generation::tools::smart_variables::generate(const ir_stat::space &code, boost::unordered_flat_map<std::shared_ptr<ir_stat::ir_expr>, naming> &buffer, const std::shared_ptr<ir::data::format::format> &format, const boost::unordered_flat_set<std::string> &globals, luramas_xregister &gvn, const bool use_annotations) {

      bool new_var = false;
      const auto valid = [&](naming &str) {
            if (globals.find(str.str()) != globals.end()) {
                  ++gvn;
                  return false;
            }
            return true;
      };
      const auto add_valid = [&](const std::string &str, const auto &expr, const auto &delimeter, const bool make_unique = false) {
            if (!str.empty()) {
                  naming temp(str);
                  if (format->vars.naming_conventions.smart.acronyms) {
                        data::acronyms::str(temp.name);
                  }
                  if (!make_unique) {
                        auto unique = std::none_of(buffer.begin(), buffer.end(), [&](const auto &pair) { return pair.second.str() == str; });
                        luramas_str_remove_trailing(temp.name, delimeter);
                        temp.delimeter = delimeter;
                        do {
                              if (!unique) {
                                    temp.descriminator += format->vars.naming_conventions.smart.suffix_char ? tools::smart_variables::alpha_suffix(expr->reg + gvn) : std::to_string(expr->reg + gvn);
                              }
                              unique = false;
                        } while (!valid(temp));
                        new_var = true;
                  }
                  buffer[expr] = temp;
            }
            return;
      };

      /* Map deep exprs */
      std::vector<std::pair<boost::unordered_flat_multiset<std::shared_ptr<ir_stat::ir_expr>> /* DESTS */, ir_stat::ir_expr::space /* EXPRS */>> exprs;
      for (const auto &c : code) {
            exprs.emplace_back(std::make_pair(c->extract_dests(), c->extract_ordered_deep_exprs()));
      }

      /* Add annotations if specified */
      if (use_annotations) {
            for (const auto &i : exprs) {
                  for (const auto &expr : i.second) {
                        if (ir::tools::exprs::values::is_reg(expr) && !expr->v.empty()) {
                              buffer.try_emplace(expr, expr->v);
                        }
                  }
            }
      }

      /* Loop through stats */
      do {
            new_var = false;
            for (auto i = 0u; i < code.size(); ++i) {

                  const auto &c = code[i];

                  for (const auto &e : exprs[i].second) {
                        switch (e->k) {
                              case expr_kinds::call: {

                                    if (format->vars.naming_conventions.smart.common_libary_arg && e->l && e->l->is_name_qualifier()) {

                                          const auto names = luramas::ir::code::generation::tools::smart_variables::data::functions::args::name(e->l->v);
                                          for (auto n = 0u; n < names.size(); ++n) {

                                                const auto str = names[n];
                                                if (!str || n >= e->members.size() || buffer.find(e->members[n]) != buffer.end() || !e->members[n]->is_register_reference()) {
                                                      break;
                                                }
                                                add_valid(str, e->members[n], format->vars.naming_conventions.delimeter);
                                          }
                                    }
                                    break;
                              }
                              case expr_kinds::arith: {

                                    if (format->vars.naming_conventions.smart.expression_canonicalization) {

                                          for (const auto &e : {e->l, e->r}) {
                                                if (e && e->is_register_reference() && buffer.find(e) == buffer.end()) {
                                                      add_valid(format->vars.naming_conventions.smart.basic_naming.value, e, format->vars.naming_conventions.delimeter);
                                                }
                                          }
                                    }
                                    break;
                              }
                              case expr_kinds::idx: {

                                    if (format->vars.naming_conventions.smart.expression_canonicalization && e->l && e->l->is_register_reference() && buffer.find(e->l) == buffer.end()) {
                                          add_valid(format->vars.naming_conventions.smart.basic_naming.table, e->l, format->vars.naming_conventions.delimeter);
                                    }
                                    break;
                              }
                              default: {
                                    break;
                              }
                        }
                  }

                  /* Any deadsets? */
                  for (const auto &d : exprs[i].first) {
                        if (d->flags.fdeadset && buffer.find(d) == buffer.end()) {
                              add_valid(format->vars.naming_conventions.smart.basic_naming.deadset, d, "", true);
                        }
                  }

                  switch (c->k) {
                        case keywords::assignment: {

                              const auto safe = buffer.find(c->l) == buffer.end();
                              const auto prefix = naming_conventions::prefix::str(c->l, format);
                              if (safe && buffer.contains(c->r)) {

                                    add_valid(prefix + format->vars.naming_conventions.smart.prefixes.copy + format->vars.naming_conventions.delimeter + buffer[c->r].str(), c->l, format->vars.naming_conventions.delimeter);

                              } else if (!c->members.empty() && c->r && c->r->is_k<expr_kinds::call>() && c->r->l && c->r->l->is_name_qualifier()) {

                                    /* ??, ?? = CALL() */
                                    if (format->vars.naming_conventions.smart.common_library) {

                                          const auto names = luramas::ir::code::generation::tools::smart_variables::data::functions::common_mulret(c->r->l->v);
                                          for (auto n = 0u; n < names.size(); ++n) {

                                                const auto str = names[n];
                                                if (!str || n >= c->members.size() || buffer.find(c->members[n]) != buffer.end()) {
                                                      break;
                                                }
                                                add_valid(naming_conventions::prefix::str(c->members[n], format) + str, c->members[n], format->vars.naming_conventions.delimeter);
                                          }
                                    }
                              } else if (safe && ir::tools::stat::assignment::is_reg_assignment_has_rvalue(c) && !buffer.contains(c->l)) {

                                    /* RVALUE == PRIMITIVE OR ABSTRACT PRIMITIVE */
                                    if (format->vars.naming_conventions.smart.primitive && (c->l->flags.fconstant || c->l->contains_upvalue())) {
                                          add_valid(prefix + format->vars.naming_conventions.smart.prefixes.primitive + (c->r->tk != tkind::nothing ? naming_conventions::str(c->r->tk) : naming_conventions::str(c->r->k)), c->l, format->vars.naming_conventions.delimeter);
                                    }

                                    luramas_address depth = 0ull;
                                    const auto s = naming_conventions::str(buffer, c->r, depth, format->vars.naming_conventions.smart.valid_depth, format->vars.naming_conventions.smart.max_depth, format->vars.module_delimiter, "_");
                                    if (!s.empty()) {

                                          auto copy_r = naming_conventions::split_constants(s, "_", format->vars.module_delimiter);
                                          luramas_str_sanitize(copy_r);
                                          if (luramas_str_valid_index(copy_r)) {
                                                luramas_str_case_snakify(copy_r);
                                                add_valid(prefix + format->vars.naming_conventions.smart.prefixes.table + copy_r, c->l, format->vars.naming_conventions.delimeter);
                                          }
                                    }
                              }

                              /* Didn't construct a name for it yet, make one */
                              if (c->l && !buffer.contains(c->l)) {
                                    if (const auto str = naming_conventions::str(c->r->k); str) {
                                          add_valid(str, c->l, format->vars.naming_conventions.delimeter);
                                    }
                              }
                              break;
                        }
                        case keywords::forloop_generic: {
                              if (c->members.size() >= 2u && buffer.find(c->members.front()) == buffer.end() && buffer.find(c->members[1u]) == buffer.end()) {
                                    add_valid(format->vars.naming_conventions.smart.basic_naming.pair_key, c->members.front(), format->vars.naming_conventions.delimeter);
                                    add_valid(format->vars.naming_conventions.smart.basic_naming.pair_value, c->members[1u], format->vars.naming_conventions.delimeter);
                              }
                              break;
                        }
                        case keywords::forloop_numeric: {
                              if (c->lba && buffer.find(c->lba) == buffer.end()) {
                                    add_valid(format->vars.naming_conventions.smart.basic_naming.iter, c->lba, format->vars.naming_conventions.delimeter);
                              }
                              break;
                        }
                        case keywords::call: {

                              if (c->l && c->l->is_name_qualifier()) {

                                    const auto names = luramas::ir::code::generation::tools::smart_variables::data::functions::args::name(c->l->v);
                                    for (auto n = 0u; n < names.size(); ++n) {

                                          const auto str = names[n];
                                          if (!str || n >= c->members.size() || buffer.find(c->members[n]) != buffer.end() || !c->members[n]->is_register_reference()) {
                                                break;
                                          }
                                          add_valid(naming_conventions::prefix::str(c->members[n], format) + str, c->members[n], format->vars.naming_conventions.delimeter);
                                    }
                              }
                              break;
                        }
                        default: {
                              break;
                        }
                  }
            }
      } while (new_var);
      return;
}