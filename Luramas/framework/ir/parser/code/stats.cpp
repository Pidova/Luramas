#include <algorithm>

#include "../../lifter/tools/tools.hpp"
#include "../common.hpp"

namespace luramas::ir::parser::stats {

      struct Associate {

            luramas_flag fdefined = false;                    /* Defined? */
            luramas_flag fexpecting_rvalue = false;           /* Expecting rvalues */
            std::vector<std::shared_ptr<ir_stat::ir_expr>> l; /* Lvalues */

            void clear() {
                  *this = Associate();
                  return;
            }
      };

      template <errors K>
      static void error(error::result<std::vector<std::shared_ptr<ir_stat>>, errors> &err, const std::string &str, const luramas_index idx) {
            err.emit<K>(error::generation::index(idx, str, parser::str(K)));
            return;
      }

      namespace extract {

            static std::pair<std::string, luramas_index> name(error::result<std::vector<std::shared_ptr<ir_stat>>, errors> & /*err*/, const std::string &str, const luramas_index idx) {

                  auto i = idx;
                  const auto n = str.size();
                  while (i < n && std::isalnum(str[i])) {
                        ++i;
                  }
                  return {str.substr(idx, i - idx), i - idx};
            }
      } // namespace extract

      namespace token {

            /* Expr token */
            static std::pair<std::string, luramas_index> exprs(error::result<std::vector<std::shared_ptr<ir_stat>>, errors> &err, const std::string &str, const luramas_index idx, const bool expecting_end = false) {

                  std::pair<std::string, luramas_index> result;

                  luramas_count encapsulation = 0U;
                  auto expr_idx_start = idx;

                  auto i = idx;
                  const auto n = str.size();
                  while (i < n) {

                        /* Encapsulation */
                        {
                              if (const auto ix = str::match_substr(str, i, LURAMAS_PARSING_EXPR_OPEN); ix) {
                                    ++encapsulation;
                                    i += ix;
                                    continue;
                              }
                              if (const auto ix = str::match_substr(str, i, LURAMAS_PARSING_EXPR_CLOSE); ix) {
                                    if (!encapsulation) {
                                          if (expecting_end) {
                                                break;
                                          }
                                          error<errors::invalid_keyword>(err, str, i);
                                          break;
                                    }
                                    --encapsulation;
                                    i += ix;
                                    continue;
                              }
                        }

                        if (!encapsulation) {

                              /* Eol */
                              if (const auto ix = str::match_substr(str, i, LURAMAS_PARSING_STAT_EOL); ix) {
                                    result.first = str.substr(expr_idx_start, i - expr_idx_start);
                                    i += ix;
                                    break;
                              }

                              /* New line */
                              if (str[i] == '\n') {
                                    result.first = str.substr(expr_idx_start, i - expr_idx_start);
                                    ++i;
                                    break;
                              }
                        }
                        ++i;
                  }
                  if (encapsulation) {
                        error<errors::encapsulation_unclosed>(err, str, i);
                  }
                  result.second = i - idx;
                  return result;
            }

      } // namespace token

      namespace generate {

            /* Set flags from manager to expr */
            static void set_flags(manager &m, const std::shared_ptr<ir_stat::ir_expr> &expr) {
                  if (!expr) {
                        return;
                  }
                  expr->flags.fglobal_wild = m.flags.fglobal_wild;
                  return;
            }

            /* Generate expr from name */
            static std::shared_ptr<ir_stat::ir_expr> name(manager &m, const std::string &str) {

                  const auto v = m.get(str);
                  if (!v) {
                        auto p = tools::exprs::generate::global(str);
                        set_flags(m, p);
                        m.set(str, p);
                        return p;
                  }
                  return v;
            }
      } // namespace generate

      error::result<std::vector<std::shared_ptr<ir_stat>>, errors> parse(manager &m, const std::string &str) {

            Associate curr;
            std::vector<keywords> scope_stack;
            error::result<std::vector<std::shared_ptr<ir_stat>>, errors> result;

            luramas_index idx = 0U;
            for (; idx < str.size();) {

                  const auto &i = str[idx];

                  /* Ignore spaces */
                  if (i == ' ' || i == '\n') {
                        ++idx;
                        continue;
                  }

                  /* No scope */
                  if (m.var_scope.empty()) {
                        error<errors::invalid_keyword>(result, str, idx);
                        return result;
                  }

                  /* Eol */
                  if (const auto ei = str::match_substr(str, idx, LURAMAS_PARSING_STAT_EOL); ei) {
                        curr.clear();
                        idx += ei;
                        continue;
                  }

                  /* Extract Expr */
                  if (curr.fexpecting_rvalue) {

                        const auto [expr, ix] = token::exprs(result, str, idx);
                        if (result) {
                              return result;
                        }
                        const auto rvalue = parser::exprs::parse(m, expr);
                        if (rvalue) {
                              result.emit(rvalue.h);
                              return result;
                        }
                        if (!rvalue.d) {
                              error<errors::invalid_keyword>(result, str, idx);
                              return result;
                        }
                        const auto p = tools::stat::generate::assignment(curr.l, rvalue.d);
                        p->flags.fdefine = curr.fdefined;
                        result.d.emplace_back(p);
                        curr.clear();
                        idx += ix;
                        continue;
                  }

                  /* Start keywords  */
                  {

                        /* Defined */
                        if (const auto vi = str::match_substr(str, idx, LURAMAS_PARSING_STAT_VAR); vi) {
                              if (curr.fdefined) {
                                    error<errors::invalid_keyword>(result, str, idx);
                                    return result;
                              }
                              curr.fdefined = true;
                              idx += vi;
                              continue;
                        }

                        /* While start */
                        if (const auto wi = str::match_substr(str, idx, LURAMAS_PARSING_STAT_WHILE); wi) {

                              idx += wi;
                              scope_stack.emplace_back(keywords::while_);
                              const auto [expr, ix] = token::exprs(result, str, idx);
                              if (result) {
                                    return result;
                              }
                              const auto cond = parser::exprs::parse(m, expr);
                              if (cond) {
                                    result.emit(cond.h);
                                    return result;
                              }
                              if (!cond.d) {
                                    error<errors::invalid_keyword>(result, str, idx);
                                    return result;
                              }
                              idx += ix;
                              result.d.emplace_back(tools::stat::generate::while_stat(cond.d, luramas::il::arch::data::bin_kinds::et_));
                              continue;
                        }

                        /* Until */
                        if (const auto ui = str::match_substr(str, idx, LURAMAS_PARSING_STAT_UNTIL); ui) {

                              idx += ui;
                              if (scope_stack.empty() || scope_stack.back() != keywords::repeat) {
                                    error<errors::invalid_keyword>(result, str, idx);
                                    return result;
                              }
                              const auto [expr, ix] = token::exprs(result, str, idx);
                              if (result) {
                                    return result;
                              }
                              const auto cond = parser::exprs::parse(m, expr);
                              if (cond) {
                                    result.emit(cond.h);
                                    return result;
                              }
                              if (!cond.d) {
                                    error<errors::invalid_keyword>(result, str, idx);
                                    return result;
                              }
                              idx += ix;
                              scope_stack.pop_back();
                              result.d.emplace_back(tools::stat::generate::until(cond.d, luramas::il::arch::data::bin_kinds::et_));
                              continue;
                        }

                        /* If */
                        if (const auto fi = str::match_substr(str, idx, LURAMAS_PARSING_STAT_IF); fi) {

                              idx += fi;
                              if (scope_stack.empty() || scope_stack.back() != keywords::repeat) {
                                    error<errors::invalid_keyword>(result, str, idx);
                                    return result;
                              }
                              const auto [expr, ix] = token::exprs(result, str, idx);
                              if (result) {
                                    return result;
                              }
                              const auto cond = parser::exprs::parse(m, expr);
                              if (cond) {
                                    result.emit(cond.h);
                                    return result;
                              }
                              if (!cond.d) {
                                    error<errors::invalid_keyword>(result, str, idx);
                                    return result;
                              }
                              idx += ix;
                              scope_stack.pop_back();
                              result.d.emplace_back(tools::stat::generate::cond(cond.d, luramas::il::arch::data::bin_kinds::et_));
                              continue;
                        }

                        /* Repeat */
                        if (const auto ri = str::match_substr(str, idx, LURAMAS_PARSING_STAT_REPEAT); ri) {

                              idx += ri;
                              scope_stack.emplace_back(keywords::repeat);
                              result.d.emplace_back(tools::stat::generate::repeat());
                              continue;
                        }

                        /* Else */
                        if (const auto ei = str::match_substr(str, idx, LURAMAS_PARSING_STAT_ELSE); ei) {

                              if (scope_stack.empty() || scope_stack.back() != keywords::condition) {
                                    error<errors::invalid_keyword>(result, str, idx);
                                    return result;
                              }
                              idx += ei;
                              result.d.emplace_back(tools::stat::generate::else_stat());
                              continue;
                        }

                        /* Break */
                        if (const auto bi = str::match_substr(str, idx, LURAMAS_PARSING_STAT_BREAK); bi) {

                              if (scope_stack.empty() || std::ranges::find_if(scope_stack, [&](const auto &i) { return i == keywords::while_ || i == keywords::repeat; }) == scope_stack.end()) {
                                    error<errors::invalid_keyword>(result, str, idx);
                                    return result;
                              }
                              idx += bi;
                              result.d.emplace_back(tools::stat::generate::break_stat());
                              continue;
                        }

                        /* Continue */
                        if (const auto ci = str::match_substr(str, idx, LURAMAS_PARSING_STAT_CONTINUE); ci) {

                              if (scope_stack.empty() || std::ranges::find_if(scope_stack, [&](const auto &i) { return i == keywords::while_ || i == keywords::repeat; }) == scope_stack.end()) {
                                    error<errors::invalid_keyword>(result, str, idx);
                                    return result;
                              }
                              idx += ci;
                              result.d.emplace_back(tools::stat::generate::continue_stat());
                              continue;
                        }

                        /* End */
                        if (const auto ei = str::match_substr(str, idx, LURAMAS_PARSING_STAT_SCOPE_END); ei) {

                              if (scope_stack.empty() || scope_stack.back() == keywords::repeat) {
                                    error<errors::invalid_keyword>(result, str, idx);
                                    return result;
                              }
                              idx += ei;
                              scope_stack.pop_back();
                              result.d.emplace_back(tools::stat::generate::end());
                              continue;
                        }
                  }

                  /* Defined */
                  {
                        /* Global/Register */
                        if (const auto &[ns, ni] = extract::name(result, str, idx); ni) {
                              if (curr.fdefined) {
                                    auto p = m.get(ns);
                                    if (!p) {
                                          p = tools::exprs::generate::reg(m.get_reg());
                                          m.set(ns, p);
                                    }
                                    curr.l.emplace_back(p);
                              } else {
                                    curr.l.emplace_back(tools::exprs::generate::global(ns));
                              }
                              idx += ni;
                              continue;
                        }

                        /* Delimiter */
                        if (const auto di = str::match_substr(str, idx, LURAMAS_PARSING_STAT_MULVAR_DELIMITER); di) {
                              if (curr.l.empty()) {
                                    error<errors::invalid_keyword>(result, str, idx);
                                    return result;
                              }
                              idx += di;
                              continue;
                        }

                        /* Equal */
                        if (const auto ei = str::match_substr(str, idx, LURAMAS_PARSING_STAT_EQ); ei) {
                              if (curr.fexpecting_rvalue || curr.l.empty()) {
                                    error<errors::invalid_keyword>(result, str, idx);
                                    return result;
                              }
                              idx += ei;
                              curr.fexpecting_rvalue = true;
                              continue;
                        }
                  }

                  /* Invalid keyword */
                  error<errors::invalid_keyword>(result, str, idx);
                  return result;
            }
            if (!scope_stack.empty()) {
                  error<errors::invalid_keyword>(result, str, idx);
                  return result;
            }
            return result;
      }
} // namespace luramas::ir::parser::stats