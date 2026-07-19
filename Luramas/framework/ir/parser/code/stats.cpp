#include "../../lifter/tools/tools.hpp"
#include "../common.hpp"

namespace luramas::ir::parser::stats {

      struct associate {

            luramas_flag fdefined = false;                    /* Defined? */
            luramas_flag fexpecting_rvalue = false;           /* Expecting rvalues */
            std::vector<std::shared_ptr<ir_stat::ir_expr>> l; /* Lvalues */

            void clear() {
                  *this = associate();
                  return;
            }
      };

      template <errors k>
      void error(error::result<std::vector<std::shared_ptr<ir_stat>>, errors> &err, const std::string &str, const luramas_index idx) {
            err.emit<k>(error::generation::index(idx, str, parser::str(k)));
            return;
      }

      namespace extract {

            std::pair<std::string, luramas_index> name(error::result<std::vector<std::shared_ptr<ir_stat>>, errors> &err, const std::string &str, const luramas_index idx) {

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
            std::pair<std::string, luramas_index> exprs(error::result<std::vector<std::shared_ptr<ir_stat>>, errors> &err, const std::string &str, const luramas_index idx, const bool expecting_end = false) {

                  std::pair<std::string, luramas_index> result;

                  luramas_count encapsulation = 0u;
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
            void set_flags(manager &m, const std::shared_ptr<ir_stat::ir_expr> &expr) {
                  if (!expr) {
                        return;
                  }
                  expr->flags.fglobal_wild = m.flags.fglobal_wild;
                  return;
            }

            /* Generate expr from name */
            std::shared_ptr<ir_stat::ir_expr> name(manager &m, const std::string &str) {

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

            associate curr;
            std::vector<keywords> scope_stack;
            error::result<std::vector<std::shared_ptr<ir_stat>>, errors> result;

            luramas_index idx = 0u;
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
                  if (const auto i = str::match_substr(str, idx, LURAMAS_PARSING_STAT_EOL); i) {
                        curr.clear();
                        idx += i;
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
                        if (const auto i = str::match_substr(str, idx, LURAMAS_PARSING_STAT_VAR); i) {
                              if (curr.fdefined) {
                                    error<errors::invalid_keyword>(result, str, idx);
                                    return result;
                              }
                              curr.fdefined = true;
                              idx += i;
                              continue;
                        }

                        /* While start */
                        if (const auto i = str::match_substr(str, idx, LURAMAS_PARSING_STAT_WHILE); i) {

                              idx += i;
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
                        if (const auto i = str::match_substr(str, idx, LURAMAS_PARSING_STAT_UNTIL); i) {

                              idx += i;
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
                        if (const auto i = str::match_substr(str, idx, LURAMAS_PARSING_STAT_IF); i) {

                              idx += i;
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
                        if (const auto i = str::match_substr(str, idx, LURAMAS_PARSING_STAT_REPEAT); i) {

                              idx += i;
                              scope_stack.emplace_back(keywords::repeat);
                              result.d.emplace_back(tools::stat::generate::repeat());
                              continue;
                        }

                        /* Else */
                        if (const auto i = str::match_substr(str, idx, LURAMAS_PARSING_STAT_ELSE); i) {

                              if (scope_stack.empty() || scope_stack.back() != keywords::condition) {
                                    error<errors::invalid_keyword>(result, str, idx);
                                    return result;
                              }
                              idx += i;
                              result.d.emplace_back(tools::stat::generate::else_stat());
                              continue;
                        }

                        /* Break */
                        if (const auto i = str::match_substr(str, idx, LURAMAS_PARSING_STAT_BREAK); i) {

                              if (scope_stack.empty() || std::find_if(scope_stack.begin(), scope_stack.end(), [&](const auto &i) { return i == keywords::while_ || i == keywords::repeat; }) == scope_stack.end()) {
                                    error<errors::invalid_keyword>(result, str, idx);
                                    return result;
                              }
                              idx += i;
                              result.d.emplace_back(tools::stat::generate::break_stat());
                              continue;
                        }

                        /* Continue */
                        if (const auto i = str::match_substr(str, idx, LURAMAS_PARSING_STAT_CONTINUE); i) {

                              if (scope_stack.empty() || std::find_if(scope_stack.begin(), scope_stack.end(), [&](const auto &i) { return i == keywords::while_ || i == keywords::repeat; }) == scope_stack.end()) {
                                    error<errors::invalid_keyword>(result, str, idx);
                                    return result;
                              }
                              idx += i;
                              result.d.emplace_back(tools::stat::generate::continue_stat());
                              continue;
                        }

                        /* End */
                        if (const auto i = str::match_substr(str, idx, LURAMAS_PARSING_STAT_SCOPE_END); i) {

                              if (scope_stack.empty() || scope_stack.back() == keywords::repeat) {
                                    error<errors::invalid_keyword>(result, str, idx);
                                    return result;
                              }
                              idx += i;
                              scope_stack.pop_back();
                              result.d.emplace_back(tools::stat::generate::end());
                              continue;
                        }
                  }

                  /* Defined */
                  {
                        /* Global/Register */
                        if (const auto &[s, i] = extract::name(result, str, idx); i) {
                              if (curr.fdefined) {
                                    auto p = m.get(s);
                                    if (!p) {
                                          p = tools::exprs::generate::reg(m.get_reg());
                                          m.set(s, p);
                                    }
                                    curr.l.emplace_back(p);
                              } else {
                                    curr.l.emplace_back(tools::exprs::generate::global(s));
                              }
                              idx += i;
                              continue;
                        }

                        /* Delimiter */
                        if (const auto i = str::match_substr(str, idx, LURAMAS_PARSING_STAT_MULVAR_DELIMITER); i) {
                              if (curr.l.empty()) {
                                    error<errors::invalid_keyword>(result, str, idx);
                                    return result;
                              }
                              idx += i;
                              continue;
                        }

                        /* Equal */
                        if (const auto i = str::match_substr(str, idx, LURAMAS_PARSING_STAT_EQ); i) {
                              if (curr.fexpecting_rvalue || curr.l.empty()) {
                                    error<errors::invalid_keyword>(result, str, idx);
                                    return result;
                              }
                              idx += i;
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