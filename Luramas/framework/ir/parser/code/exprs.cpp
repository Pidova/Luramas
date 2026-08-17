#include "../../lifter/tools/tools.hpp"
#include "../common.hpp"

namespace luramas::ir::parser::exprs {

      struct associate {

            expr_kinds fexpecting_keyword = expr_kinds::ternary;
            bool fexpecting_rvalue = false;
            std::shared_ptr<ir_stat::ir_expr> l = nullptr;
            std::shared_ptr<ir_stat::ir_expr> extra = nullptr;
            il::arch::data::bin_kinds b = il::arch::data::bin_kinds::nothing;
            il::arch::data::bin_kinds u = il::arch::data::bin_kinds::nothing;

            void clear() {
                  *this = associate();
                  return;
            }
            void clear_weak() {
                  auto p = this->l;
                  auto extra = this->extra;
                  this->clear();
                  this->l = p;
                  this->extra = extra;
                  return;
            }
      };

      template <errors K>
      static void error(error::result<std::shared_ptr<ir_stat::ir_expr>, errors> &err, const std::string &str, const luramas_index idx) {
            err.emit<K>(nullptr, error::generation::index(idx, str, parser::str(K)));
            return;
      }

      namespace extract {

            /* Returns 0 index if no number found */
            static std::pair<luramas_int, luramas_index> number(const std::string &str, const luramas_index idx) {

                  auto i = idx;
                  bool neg = false;
                  const auto n = str.size();
                  while (i < n && (str[i] == '+' || str[i] == '-')) {
                        if (str[i++] == '-') {
                              neg = !neg;
                        }
                  }

                  const auto start = i;
                  while (i < n && std::isdigit(str[i])) {
                        ++i;
                  }

                  const auto frac = i < n && str[i] == '.';
                  if (frac) {
                        while (++i < n && std::isdigit(str[i])) {
                        }
                  }
                  if (start == i) {
                        return {luramas_int(static_cast<luramas_int_base>(0U)), 0U};
                  }

                  std::string lit;
                  if (neg) {
                        lit.push_back('-');
                  }
                  lit.append(str.data() + start, i - start);

                  if (frac) {
                        return {luramas_int(static_cast<luramas_int_pbase>(std::strtod(lit.c_str(), nullptr))), i - idx};
                  }
                  luramas_int_base v = 0U;
                  std::from_chars(lit.data(), lit.data() + lit.size(), v);
                  return {luramas_int(v), i - idx};
            }

            static std::pair<std::string, luramas_index> str(error::result<std::shared_ptr<ir_stat::ir_expr>, errors> &err, const std::string &str, const luramas_index idx) {

                  auto i = idx;
                  const auto n = str.size();
                  const auto quote = (i < n ? str[i] : '\0');
                  if (quote != '"' && quote != '\'') {
                        return {"", 0U};
                  }

                  const auto start = ++i;
                  while (i < n && str[i] != quote) {
                        ++i;
                  }
                  if (i >= n) {
                        error<errors::unclosed_string>(err, str, idx);
                        return {"", 0U};
                  }
                  return {str.substr(start, i - start), i - idx + 1U};
            }

            static std::pair<std::string, luramas_index> name(error::result<std::shared_ptr<ir_stat::ir_expr>, errors> & /*err*/, const std::string &str, const luramas_index idx) {

                  auto i = idx;
                  const auto n = str.size();
                  while (i < n && std::isalnum(str[i])) {
                        ++i;
                  }
                  return {str.substr(idx, i - idx), i - idx};
            }
      } // namespace extract

      namespace token {

            /* Arithmetic token */
            static il::arch::data::bin_kinds arith(const std::string &str, luramas_index &idx) {

                  for (const auto &[token_str, bin] : {
                           std::make_pair(LURAMAS_PARSING_EXPR_ARITH_ADD, il::arch::data::bin_kinds::add_),
                           std::make_pair(LURAMAS_PARSING_EXPR_ARITH_SUB, il::arch::data::bin_kinds::sub_),
                           std::make_pair(LURAMAS_PARSING_EXPR_ARITH_MUL, il::arch::data::bin_kinds::mul_),
                           std::make_pair(LURAMAS_PARSING_EXPR_ARITH_IDIV, il::arch::data::bin_kinds::idiv_),
                           std::make_pair(LURAMAS_PARSING_EXPR_ARITH_DIV, il::arch::data::bin_kinds::div_),
                           std::make_pair(LURAMAS_PARSING_EXPR_ARITH_MOD, il::arch::data::bin_kinds::mod_),
                           std::make_pair(LURAMAS_PARSING_EXPR_ARITH_AND, il::arch::data::bin_kinds::and_),
                           std::make_pair(LURAMAS_PARSING_EXPR_ARITH_OR, il::arch::data::bin_kinds::or_),
                           std::make_pair(LURAMAS_PARSING_EXPR_ARITH_POW, il::arch::data::bin_kinds::pow_),
                           std::make_pair(LURAMAS_PARSING_EXPR_ARITH_XOR, il::arch::data::bin_kinds::xor_),
                           std::make_pair(LURAMAS_PARSING_EXPR_ARITH_SHL, il::arch::data::bin_kinds::shl_),
                           std::make_pair(LURAMAS_PARSING_EXPR_ARITH_SHR, il::arch::data::bin_kinds::shr_)}) {
                        if (const auto i = str::match_substr(str, idx, token_str); i) {
                              idx += i;
                              return bin;
                        }
                  }
                  return il::arch::data::bin_kinds::nothing;
            }

            /* Condition token */
            static il::arch::data::bin_kinds cond(const std::string &str, luramas_index &idx) {

                  for (const auto &[token_str, bin] : {
                           std::make_pair(LURAMAS_PARSING_EXPR_COND_EQ, il::arch::data::bin_kinds::eq_),
                           std::make_pair(LURAMAS_PARSING_EXPR_COND_NE, il::arch::data::bin_kinds::ne_),
                           std::make_pair(LURAMAS_PARSING_EXPR_COND_LTE, il::arch::data::bin_kinds::lte_),
                           std::make_pair(LURAMAS_PARSING_EXPR_COND_GTE, il::arch::data::bin_kinds::gte_),
                           std::make_pair(LURAMAS_PARSING_EXPR_COND_LT, il::arch::data::bin_kinds::lt_),
                           std::make_pair(LURAMAS_PARSING_EXPR_COND_GT, il::arch::data::bin_kinds::gt_)}) {
                        if (const auto i = str::match_substr(str, idx, token_str); i) {
                              idx += i;
                              return bin;
                        }
                  }
                  return il::arch::data::bin_kinds::nothing;
            }

            /* Unary token */
            static std::pair<luramas_index, il::arch::data::bin_kinds> unary(const std::string &str, const luramas_index idx) {

                  for (const auto &[token_str, bin] : {
                           std::make_pair(LURAMAS_PARSING_EXPR_UNARY_BITNOT, il::arch::data::bin_kinds::bitnot_),
                           std::make_pair(LURAMAS_PARSING_EXPR_UNARY_NOT, il::arch::data::bin_kinds::not_),
                           std::make_pair(LURAMAS_PARSING_EXPR_UNARY_LEN, il::arch::data::bin_kinds::len_),
                           std::make_pair(LURAMAS_PARSING_EXPR_UNARY_MINUS, il::arch::data::bin_kinds::minus_),
                           std::make_pair(LURAMAS_PARSING_EXPR_UNARY_PLUS, il::arch::data::bin_kinds::plus_)}) {
                        if (const auto i = str::match_substr(str, idx, token_str); i) {
                              return {i, bin};
                        }
                  }
                  return {idx, il::arch::data::bin_kinds::nothing};
            }

            /* Logical token */
            static expr_logical logical(const std::string &str, luramas_index &idx) {

                  for (const auto &[token_str, bin] : {
                           std::make_pair(LURAMAS_PARSING_EXPR_COND_OR, expr_logical::or_),
                           std::make_pair(LURAMAS_PARSING_EXPR_COND_AND, expr_logical::and_)}) {
                        if (const auto i = str::match_substr(str, idx, token_str); i) {
                              idx += i;
                              return bin;
                        }
                  }
                  return expr_logical::nothing;
            }

            /* Encapsulation token */
            static luramas_count encapsulate(error::result<std::shared_ptr<ir_stat::ir_expr>, errors> &err, const std::string &str, const luramas_index idx, std::vector<associate> &stack) {

                  if (const auto i = str::match_substr(str, idx, LURAMAS_PARSING_EXPR_OPEN); i) {

                        stack.emplace_back();
                        return i;
                  }
                  if (const auto i = str::match_substr(str, idx, LURAMAS_PARSING_EXPR_CLOSE); i) {

                        if (stack.size() <= 1U) {
                              error<errors::encapsulation_close>(err, str, idx);
                              return 0U;
                        }

                        const auto top = stack.back();
                        stack.pop_back();

                        if (top.fexpecting_rvalue) {
                              error<errors::encapsulation_close>(err, str, idx);
                              return 0U;
                        }

                        auto &b = stack.back();
                        if (b.fexpecting_rvalue) {
                              b.fexpecting_rvalue = false;
                              b.l = tools::exprs::generate::bin_kind(b.l, b.b, top.l);
                        } else {
                              if (b.l) {
                                    error<errors::encapsulation_close>(err, str, idx);
                                    return 0U;
                              }
                              b.l = top.l;
                        }
                        if (il::arch::data::is_kinds::unary(b.u)) {
                              b.l = ir::tools::exprs::generate::unary(b.l, b.u);
                              b.u = il::arch::data::bin_kinds::nothing;
                        }

                        switch (b.fexpecting_keyword) {
                              case expr_kinds::ternary: {

                                    //if (pm.env_flags.fallow_ternaries && !b.extra) {
                                    //      b.extra = tools::exprs::generate::ternary(tools::)
                                    //}
                                    break;
                              }
                              default: {
                                    break;
                              }
                        }
                        return i;
                  }
                  return 0U;
            }

            /* Tokent that countains left and right values */
            static il::arch::data::bin_kinds lr_values(const std::string &str, luramas_index &idx) {
                  const auto a = token::arith(str, idx);
                  return a != il::arch::data::bin_kinds::nothing ? a : token::cond(str, idx);
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

      static void add_value(error::result<std::shared_ptr<ir_stat::ir_expr>, errors> &err, const std::string &str, const std::shared_ptr<ir_stat::ir_expr> &expr, const luramas_index idx, std::vector<associate> &stack) {

            if (!expr || stack.empty()) {
                  error<errors::invalid_keyword>(err, str, idx);
                  return;
            }

            auto &top = stack.back();
            if (top.l && top.b == il::arch::data::bin_kinds::nothing) {
                  error<errors::invalid_keyword>(err, str, idx);
                  return;
            }
            if (top.l) {
                  top.l = tools::exprs::generate::bin_kind(top.l, top.b, expr);
                  if (il::arch::data::is_kinds::unary(top.u)) {
                        top.l = ir::tools::exprs::generate::unary(top.l, top.u);
                        top.u = il::arch::data::bin_kinds::nothing;
                  }
                  top.clear_weak();
                  return;
            }
            top.l = expr;
            if (il::arch::data::is_kinds::unary(top.u)) {
                  top.l = ir::tools::exprs::generate::unary(top.l, top.u);
                  top.u = il::arch::data::bin_kinds::nothing;
            }
            return;
      }

      error::result<std::shared_ptr<ir_stat::ir_expr>, errors> parse(manager &m, const std::string &str) {

            std::vector<associate> stack = {associate()};
            stack.reserve(5U);
            error::result<std::shared_ptr<ir_stat::ir_expr>, errors> result = nullptr;

            luramas_index idx = 0U;
            for (; idx < str.size();) {

                  const auto &i = str[idx];

                  /* Ignore spaces */
                  if (i == ' ') {
                        ++idx;
                        continue;
                  }

                  /* Parenthesis */
                  {

                        if (const auto es = token::encapsulate(result, str, idx, stack); es && (idx += es)) {
                              continue;
                        }
                        if (result) {
                              return result;
                        }
                  }

                  /* Keywords */
                  {

                        if (const auto ts = str::match_substr(str, idx, LURAMAS_PARSING_EXPR_TERNARY_START); ts) {

                              if (stack.empty()) {
                                    error<errors::invalid_keyword>(result, str, idx);
                                    return result;
                              }

                              auto &top = stack.back();
                              if (top.fexpecting_keyword != expr_kinds::nothing) {
                                    error<errors::invalid_keyword>(result, str, idx);
                                    return result;
                              }
                              top.fexpecting_keyword = expr_kinds::ternary;
                              continue;
                        }
                  }

                  /* Unary */
                  {

                        if (const auto [ix, b] = token::unary(str, idx); b != il::arch::data::bin_kinds::nothing) {

                              if (stack.empty()) {
                                    error<errors::invalid_keyword>(result, str, idx);
                                    return result;
                              }

                              if (auto &top = stack.back(); !top.l) {
                                    idx += ix;
                                    top.u = b;
                                    continue;
                              }
                        }
                  }

                  /* Operators */
                  {

                        /* LR values operators */
                        if (const auto b = token::lr_values(str, idx); b != il::arch::data::bin_kinds::nothing) {

                              /* Invalid keyword */
                              if (stack.empty()) {
                                    error<errors::invalid_keyword>(result, str, idx);
                                    return result;
                              }

                              auto &top = stack.back();
                              if (top.fexpecting_rvalue) {
                                    error<errors::no_rvalue>(result, str, idx);
                                    return result;
                              }
                              top.fexpecting_rvalue = true;

                              /* No lvalue */
                              if (!top.l) {
                                    error<errors::no_lvalue>(result, str, idx);
                                    return result;
                              }
                              top.b = b;
                              continue;
                        }
                  }

                  /* Values */
                  {

                        /* Number */
                        if (const auto [ni, nix] = extract::number(str, idx); nix && (idx += nix)) {
                              add_value(result, str, tools::exprs::generate::integral(ni), idx, stack);
                              continue;
                        }

                        /* String */
                        auto [si, six] = extract::str(result, str, idx);
                        if (result) {
                              return result;
                        }
                        if (six && (idx += six)) {
                              add_value(result, str, tools::exprs::generate::string(si), idx, stack);
                              if (result) {
                                    return result;
                              }
                              continue;
                        }

                        /* Name */
                        std::tie(si, six) = extract::name(result, str, idx);
                        if (result) {
                              return result;
                        }
                        if (six && (idx += six)) {
                              add_value(result, str, generate::name(m, si), idx, stack);
                              if (result) {
                                    return result;
                              }
                              continue;
                        }
                  }

                  /* Invalid keyword */
                  error<errors::invalid_keyword>(result, str, idx);
                  return result;
            }

            /* Unclosed */
            if (stack.size() != 1U) {
                  error<errors::encapsulation_unclosed>(result, str, idx);
                  return result;
            }

            const auto &b = stack.back();

            /* Expecting RValue */
            if (b.fexpecting_rvalue) {
                  error<errors::no_rvalue>(result, str, idx);
                  return result;
            }
            result.d = b.l;
            return result;
      }
} // namespace luramas::ir::parser::exprs