#include "fuzzer.hpp"
#include "../lifter/tools/tools.hpp"
#include <random>

#define SEED_RANDOMNESS(seed) seed *= seed + 2u
#define SEED_UNIFORM_U8(seed) (std::uint8_t(seed / 7u) + 8u) * 2u
#define ASGN_SEED_UNIFORM_U8(seed) (seed = SEED_UNIFORM_U8(seed))
#define ASGN_SEED_UNIFORM_SMALL_U8(seed) (seed = SEED_UNIFORM_U8(seed) / 4u)

namespace fuzz_data {

      template <typename e>
      e wrap_enum(const std::uint8_t n) {
            constexpr auto amt = static_cast<std::uint8_t>(e::amount);
            return static_cast<e>((n % amt + amt) % amt);
      }

      /* Get first digit of a number */
      inline std::uint8_t first_digit(std::uint64_t n) {
            while (n >= 10) {
                  n /= 10;
            }
            return static_cast<std::uint8_t>(n);
      }

      inline std::uint64_t range_size(std::uint64_t seed) {

            static constexpr std::uint8_t prob1 = 50u; /* 50% */
            static constexpr std::uint8_t prob2 = 85u; /* 50% + 35% = 85% */

            const auto scaled_seed = seed % 100u + 1u;

            if (scaled_seed <= prob1) {
                  /* [1, 400] */
                  return 1u + (scaled_seed % 400u);
            } else if (scaled_seed <= prob2) {
                  /* [401, 1200] */
                  return 401u + (scaled_seed % 800u);
            }
            /* [1201, 4000] */
            return 1201u + (scaled_seed % 2800u);
      }
      inline std::shared_ptr<ir_stat::ir_expr> random_assignable(const boost::unordered_flat_map<std::uint64_t, std::shared_ptr<ir_stat::ir_expr>> &assignables, std::uint64_t seed) {

            std::mt19937 rng(static_cast<std::uint32_t>(seed));
            std::uniform_int_distribution<std::size_t> dist(0u, assignables.size() - 1u);
            return std::next(assignables.begin(), dist(rng))->second;
      }
} // namespace fuzz_data

ir_stat::space luramas::ir::fuzzer::generate(std::uint64_t seed) {
      ir_stat::space result;

      boost::unordered_flat_map<std::uint64_t, std::shared_ptr<ir_stat::ir_expr>> assignables;

      const auto get_assignable = [&](const bool known_var = false) {
            if (assignables.empty() || seed % 3u) {

                  luramas_register reg = static_cast<luramas_register>(seed);
                  if (auto it = assignables.find(reg); it != assignables.end()) {
                        return it->second;
                  }
                  if (seed % 2u) {
                        assignables.emplace(reg, tools::exprs::generate::global("g_" + std::to_string(reg)));
                        return assignables[reg];
                  }
                  if (!known_var) {
                        assignables.emplace(reg, tools::exprs::generate::reg(reg));
                        return assignables[reg];
                  }
            }
            return fuzz_data::random_assignable(assignables, seed);
      };
      const auto fuzz_tkind = [&](const tkind tk = tkind::nothing) {
            switch (tk) {
                  case tkind::boolean: {
                        return tools::exprs::generate::boolean(seed % 2u);
                  }
                  case tkind::variadic: {
                        return tools::exprs::generate::variadic();
                  }
                  case tkind::none_obj: {
                        return tools::exprs::generate::none_object();
                  }
                  case tkind::string: {
                        return tools::exprs::generate::string("str_" + std::to_string(seed));
                  }
                  case tkind::lura_int:
                  default: {
                        return tools::exprs::generate::integral(seed);
                  }
            }
      };
      std::function<std::shared_ptr<ir_stat::ir_expr>(std::uint8_t, tkind)> fuzz_expr =
          [&](std::uint8_t pseed, const tkind perfered) {
                if (perfered != tkind::nothing) {
                      return fuzz_tkind(perfered);
                }
                pseed /= 2u;
                const auto uniform_pseed = SEED_UNIFORM_U8(pseed);
                switch (fuzz_data::wrap_enum<expr_kinds>(uniform_pseed)) {
                      case expr_kinds::unary: {
                            auto b = il::arch::data::bin_kinds::not_;
                            const auto tb = fuzz_data::wrap_enum<il::arch::data::bin_kinds>(uniform_pseed);
                            switch (tb) {
                                  case luramas::il::arch::data::bin_kinds::len_:
                                  case luramas::il::arch::data::bin_kinds::minus_:
                                  case luramas::il::arch::data::bin_kinds::not_:
                                  case luramas::il::arch::data::bin_kinds::bitnot_:
                                  case luramas::il::arch::data::bin_kinds::plus_:
                                  case luramas::il::arch::data::bin_kinds::ref_: {
                                        b = tb;
                                        break;
                                  }
                                  default: {
                                        break;
                                  }
                            }
                            return tools::exprs::generate::unary(fuzz_expr(pseed, tkind::nothing), b);
                      }
                      default: {
                            if (assignables.empty() || pseed % 2u) {
                                  return fuzz_tkind(fuzz_data::wrap_enum<tkind>(uniform_pseed));
                            }
                            break;
                      }
                }
                return get_assignable(true);
          };

      std::vector<std::pair<keywords, std::vector<condition_kind>>> pending;

      const auto init_size = fuzz_data::range_size(seed) * 2u;
      result.reserve(init_size);

      for (auto o = 0u; o < init_size; ++o) {

            auto uniform_pseed = SEED_UNIFORM_U8(seed);
            switch (fuzz_data::wrap_enum<keywords>(uniform_pseed)) {
                  case keywords::table_assign: {
                        const auto t = fuzz_expr(ASGN_SEED_UNIFORM_U8(uniform_pseed), tkind::nothing);
                        const auto idx = fuzz_expr(ASGN_SEED_UNIFORM_U8(uniform_pseed), tkind::nothing);
                        const auto v = fuzz_expr(ASGN_SEED_UNIFORM_U8(uniform_pseed), tkind::nothing);
                        result.emplace_back(tools::stat::generate::table_assignment(t, idx, v));
                        break;
                  }
                  case keywords::call: {
                        ir_stat::ir_expr::space params;
                        for (auto c = 0u; c < ASGN_SEED_UNIFORM_SMALL_U8(uniform_pseed); ++c) {
                              params.emplace_back(fuzz_expr(ASGN_SEED_UNIFORM_U8(c), tkind::nothing));
                        }
                        result.emplace_back(tools::stat::generate::call(fuzz_expr(ASGN_SEED_UNIFORM_U8(uniform_pseed), tkind::nothing), params));
                        break;
                  }
                  case keywords::retn: {
                        if (!(SEED_UNIFORM_U8(seed) % 9u)) {
                              continue;
                        }
                        ir_stat::ir_expr::space params;
                        for (auto c = 0u; c < ASGN_SEED_UNIFORM_SMALL_U8(uniform_pseed); ++c) {
                              params.emplace_back(fuzz_expr(ASGN_SEED_UNIFORM_U8(c), tkind::nothing));
                        }
                        result.emplace_back(tools::stat::generate::retn(params));
                        break;
                  }
                  case keywords::condition: {

                        switch (fuzz_data::wrap_enum<condition_kind>(ASGN_SEED_UNIFORM_SMALL_U8(uniform_pseed))) {
                              case condition_kind::elseif_: {
                              }
                              case condition_kind::if_:
                              default: {
                                    break;
                              }
                        }
                        break;
                  }
                  case keywords::assignment:
                  default: {
                        const auto rv = fuzz_expr(ASGN_SEED_UNIFORM_U8(uniform_pseed), tkind::nothing);
                        result.emplace_back(tools::stat::generate::assignment(get_assignable(), rv));
                        break;
                  }
            }
            SEED_RANDOMNESS(seed);
      }
      return result;
}