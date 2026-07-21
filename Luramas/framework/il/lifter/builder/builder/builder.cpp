#include "../builder.hpp"
#include <algorithm>
#include <ranges>

namespace luramas::il::lifter::builder {

      template <typename... T>
      inline auto guaranteed_regs(const std::shared_ptr<build> &b, const T &...args) {
            return std::make_tuple(
                ([&b](auto &val) {
                      if (val.is_reg()) {
                            return val;
                      }
                      auto temp = b->make_temp();
                      temp = val;
                      if (!temp.r.size) {
                            temp = temp.cast(types::underlying_type(false, luramas::types::read_type::bits, 0u, b->suggested_bit_set));
                      }
                      return temp;
                }(args))...);
      }

      void build::make_goto(const std::uintptr_t ID) {
            const auto it = this->labels.find(ID);
            if (it == this->labels.end()) {
                  luramas::error::error("Label not found");
            }
            this->gen<arch::opcodes::OP_JUMP>(this->pc)->ref = it->second;
            return;
      }
      void build::make_label(const std::uintptr_t ID) {
            this->labels.emplace(ID, this->gen<luramas::il::arch::opcodes::OP_NOP>());
            return;
      }
      std::shared_ptr<luramas::il::disassembly> build::make(const luramas::il::arch::data::bin_kinds b) {

            switch (b) {
                  case luramas::il::arch::data::bin_kinds::eq_: {
                        return this->gen<arch::opcodes::OP_JUMPIFEQUAL>(this->pc);
                  }
                  case luramas::il::arch::data::bin_kinds::ne_: {
                        return this->gen<arch::opcodes::OP_JUMPIFNOTEQUAL>(this->pc);
                  }
                  case luramas::il::arch::data::bin_kinds::lt_: {
                        return this->gen<arch::opcodes::OP_JUMPIFLESS>(this->pc);
                  }
                  case luramas::il::arch::data::bin_kinds::lte_: {
                        return this->gen<arch::opcodes::OP_JUMPIFLESSEQUAL>(this->pc);
                  }
                  case luramas::il::arch::data::bin_kinds::gt_: {
                        return this->gen<arch::opcodes::OP_JUMPIFGREATER>(this->pc);
                  }
                  case luramas::il::arch::data::bin_kinds::gte_: {
                        return this->gen<arch::opcodes::OP_JUMPIFGREATEREQUAL>(this->pc);
                  }
                  case luramas::il::arch::data::bin_kinds::nt_: {
                        return this->gen<arch::opcodes::OP_JUMPIFNOT>(this->pc);
                  }
                  case luramas::il::arch::data::bin_kinds::et_: {
                        return this->gen<arch::opcodes::OP_JUMPIF>(this->pc);
                  }
                  default: {
                        break;
                  }
            }
            return this->gen<arch::opcodes::OP_JUMP>(this->pc);
      }
      void build::make_else() {
            if (this->opened_conditions.empty()) {
                  luramas::error::error("No condition to make else");
            }
            this->make_scope();
            this->make<arch::opcodes::OP_NOP>();
            this->close_scope(true, this->opened_conditions.size() - 2u);
            return;
      }
      void build::close_scope(const bool input, luramas_address loc) {
            if (!input) {
                  loc = this->opened_conditions.size() - 1u;
            }
            if (this->opened_conditions.empty()) {
                  luramas::error::error("Unclosed conditions");
            }
            this->opened_conditions[loc]->ref = this->gen<arch::opcodes::OP_NOP>();
            this->opened_conditions.erase(this->opened_conditions.begin() + loc);
            return;
      }
      void build::make_load(const std::uint64_t flag_id, const expr &reg) {
            if (reg.tk != expr_tkind::reg) {
                  luramas::error::error("Can not set non reg to flagid");
            }
            this->make<luramas::il::arch::opcodes::OP_FLAGSET>(flag_id, reg.r.r);
            return;
      }
      void build::make_flag_load(const expr &reg, const std::intptr_t i, const luramas_bitwidth bits, const bool unsign, const luramas_bitwidth precision) {
            this->make<luramas::il::arch::opcodes::OP_FLAGREAD>(reg.r.r, i);
            this->make_cast(reg.r.r, reg.r.r, bits, unsign, precision);
            return;
      }
      void build::make_load(const expr &reg, const std::intptr_t i) {
            this->make<luramas::il::arch::opcodes::OP_LOADINT>(reg.r.r, i);
            return;
      }
      void build::set_global(const std::string &str, const expr &reg) {
            this->make<luramas::il::arch::opcodes::OP_SETGLOBAL>(reg.r.r, this->il->make_kvalue<il::arch::data::kval_kinds::function>(str));
            return;
      }
      void build::make_global(const expr &reg, const std::string &str) {
            this->make<luramas::il::arch::opcodes::OP_LOADGLOBAL>(reg.r.r, this->il->make_kvalue<il::arch::data::kval_kinds::function>(str));
            return;
      }
      void build::make_string(const expr &reg, const std::string &str) {
            this->make<luramas::il::arch::opcodes::OP_LOADKVAL>(reg.r.r, this->il->make_kvalue<il::arch::data::kval_kinds::string>(str));
            return;
      }
      void build::make_value(const reg &reg, const double v) {
            this->make<luramas::il::arch::opcodes::OP_LOADKVAL>(reg.r, this->il->make_kvalue<il::arch::data::kval_kinds::integer>(v));
            return;
      }
      void build::make_cast(const luramas_register dest, const luramas_register src, const luramas_bitwidth bits, const bool unsign, const luramas_bitwidth precision) {
            this->make<luramas::il::arch::opcodes::OP_BITCAST>(dest, src, bits, precision, unsign);
            return;
      }
      build::expr build::make_temp(const expr &reg) {
            auto t = expr(shared_from_this(), this->get_temp());
            t = reg;
            return t;
      }
      build::expr build::make_temp(const types::underlying_type &size) {
            auto t = expr(shared_from_this(), this->get_temp());
            t.r.size = size;
            return t;
      }
      void format_call_args(const std::shared_ptr<build> &builder, const std::vector<build::expr> &args) {
            for (const auto &i : args) {
                  if (!i.empty()) {
                        build::expr(builder, builder->get_temp()) = i;
                  }
            }
            return;
      }
      void format_call_returns(const std::shared_ptr<build> &builder, const build::expr &calle, const std::vector<build::expr> &results) {
            for (auto i = 0u; i < results.size(); ++i) {
                  if (const auto &p = results[i]; !p.empty()) {
                        results[i] = build::expr(builder, reg(calle.r.r + i));
                  }
            }
            return;
      }
      void build::make_call(const std::string &func, const std::vector<expr> &args, const std::vector<expr> &results) {

            const auto calle = expr(shared_from_this(), this->get_temp());
            this->make_global(calle, func);
            format_call_args(shared_from_this(), args);
            this->make<luramas::il::arch::opcodes::OP_CCALL>(calle.r.r, args.size(), results.size());
            format_call_returns(shared_from_this(), calle, results);
            return;
      }
      void build::make_call(const std::string &func, const expr &result) {
            this->make_call(func, {}, {result});
            return;
      }
      build::expr build::make_standard_call(const builtin::func &default_func, const std::vector<std::pair<types::native::compiler::object, build::expr>> &sources, const std::vector<std::pair<types::native::compiler::object, build::expr>> &dests) {
            auto func = default_func.name;
            std::vector<expr> args;
            for (const auto &[def, expr] : sources) {
                  args.emplace_back(expr);
            }
            expr temp;
            std::vector<expr> result;
            for (const auto &[def, expr] : dests) {
                  if (def.empty()) {
                        temp = this->make_temp();
                        result.emplace_back(temp);
                  } else {
                        result.emplace_back(expr);
                  }
            }
            this->make_call(func, args, result);
            return temp;
      }
      build::expr build::make_built_in(const builtin::inst &data, const std::vector<build::expr> &operands, const std::vector<build::expr> &flags) {

            expr result;

            std::vector<std::pair<types::native::compiler::object, build::expr>> dests;
            std::vector<std::pair<types::native::compiler::object, build::expr>> sources;
            boost::unordered_flat_set<std::size_t> seen_operands;

            std::vector<std::pair<builtin::func, std::size_t>> valid;
            for (const auto &i : data.func_defs) {

                  seen_operands.reserve(operands.size());

                  /* Check definition */
                  bool pass = true;
                  for (const auto &j : std::ranges::join_view(std::array{i.dests, i.source})) {
                        if (j.flag > -1 && j.flag >= flags.size()) {
                              pass = false;
                              break;
                        }
                        if (j.idx > -1) {
                              if (j.idx >= operands.size() || !operands[j.idx].r.size.weak_compare(j.obj.type)) {
                                    pass = false;
                                    break;
                              }
                              seen_operands.insert(j.idx);
                        }
                        if (j.flag <= -1 && j.idx <= -1) {
                              pass = false;
                              break;
                        }
                  }
                  if (const auto neq = seen_operands.size() != operands.size(); !pass || neq) {
                        if (neq) {
                              valid.emplace_back(i, seen_operands.size());
                        }
                        seen_operands.clear();
                        continue;
                  }

                  for (const auto &j : i.dests) {
                        if (j.flag > -1 || j.idx > -1) {
                              dests.emplace_back(j.obj, j.flag > -1 ? flags[j.idx] : operands[j.idx]);
                        }
                  }
                  for (const auto &j : i.source) {
                        if (j.flag > -1 || j.idx > -1) {
                              sources.emplace_back(j.obj, j.flag > -1 ? flags[j.idx] : operands[j.idx]);
                        }
                  }
                  return this->make_standard_call(i, sources, dests);
            }
            for (const auto &[i, size] : valid) {

                  if (!operands.size() || size != operands.size() - 1u) {
                        continue;
                  }
                  for (const auto &j : i.dests) {
                        if (j.flag > -1 || j.idx > -1) {
                              dests.emplace_back(j.obj, j.flag > -1 ? flags[j.idx] : operands[j.idx]);
                        }
                  }
                  for (const auto &j : i.source) {
                        if (j.flag > -1 || j.idx > -1) {
                              sources.emplace_back(j.obj, j.flag > -1 ? flags[j.idx] : operands[j.idx]);
                        }
                  }
                  return this->make_standard_call(i, sources, dests);
            }
            return result;
      }
      void build::make_lura_built_in(const builtins::data::func &f, const std::vector<expr> &args, const std::vector<expr> &results) {

            const auto calle = expr(shared_from_this(), this->get_temp());
            this->make_global(calle, f.name);
            format_call_args(shared_from_this(), args);
            this->set_flag<arch::data::flags::ffunc>();
            this->make<luramas::il::arch::opcodes::OP_CCALL>(calle.r.r, args.size(), results.size());
            format_call_returns(shared_from_this(), calle, results);
            return;
      }
      void build::set_internal_global(const std::string &str, const expr &reg) {
            this->set_flag<arch::data::flags::fnative_global>();
            this->set_global(str, reg);
            return;
      }
      void build::load_internal_global(const std::string &str, const expr &reg) {
            this->set_flag<arch::data::flags::fnative_global>();
            this->make_global(reg, str);
            return;
      }
      luramas_id build::set_global(const std::string &global) {

            return this->globals.try_emplace(global, this->globals.size()).first->second;
      }
      void build::insert(const std::vector<std::shared_ptr<luramas::il::disassembly>> &v) {
            this->il->insert_front(this->idx, v);
            return;
      }
      void build::insert(const std::shared_ptr<luramas::il::disassembly> &v) {
            this->il->insert_front(this->idx, v);
            return;
      }
      build::expr build::make_reg(const luramas_register r) {
            reg result(r);
            result.cast = false;
            return expr(shared_from_this(), result);
      }
      build::expr build::make_var(const luramas_register r, const luramas_bitwidth bits, const bool unsign, const std::uint8_t precision) {
            reg result(r, bits, unsign, precision);
            this->make_cast(r, r, bits, precision, unsign);
            return expr(shared_from_this(), result);
      }
      reg build::get_temp() {
            return reg(++this->temp);
      }
      build::expr build::make_temp() {
            expr t(shared_from_this(), this->get_temp());
            t.cast(this->suggested_bit_set, false);
            t = 0;
            return t;
      }
      void build::violation(const expr &l) const {
            if (l.tk != expr_tkind::reg) {
                  luramas::error::error("Lvalue register");
            }
            return;
      }
      void build::precomputed() {
            luramas::il::emitter::emit_opcode<luramas::il::arch::opcodes::OP_NOP>(this->il, this->pc, this->current);
            return;
      }

      build::expr build::make_bitread(const expr &value, const expr &min, const expr &max) {
            const auto result = this->make_temp();
            const auto [rvalue, rmin, rmax] = guaranteed_regs(shared_from_this(), value, min, max);
            this->make<luramas::il::arch::opcodes::OP_BITREAD>(result.r.r, rvalue.r.r, rmin.r.r, rmax.r.r, rvalue.bits(), rvalue.signess() == luramas::types::signess::unsign);
            return result;
      }
      build::expr build::make_bitwrite(const expr &dest, const expr &src, const expr &min, const expr &max) {
            const auto [rdest, rsrc, rmin, rmax] = guaranteed_regs(shared_from_this(), dest, src, min, max);
            this->make<luramas::il::arch::opcodes::OP_BITWRITEA>(rdest.r.r, rsrc.r.r, rmin.r.r, rmax.r.r);
            return rdest;
      }

      void build::make_push(const expr &e, const std::uint32_t ID) {
            auto temp = this->make_temp(e);
            this->make<arch::opcodes::OP_STACKPUSH>(ID, temp.r.r);
            return;
      }
      void build::make_pop(const expr &e, const std::uint32_t ID) {
            auto temp = this->make_temp(e);
            this->make<arch::opcodes::OP_STACKPOP>(ID, temp.r.r);
            return;
      }
      void build::make_pop(const std::uint32_t ID) {
            this->make<arch::opcodes::OP_POPTOPSTACK>(ID);
            return;
      }
      void build::make_page(const std::intptr_t ID) {
            this->opended_pages.emplace_back(ID);
            this->make<arch::opcodes::OP_STARTPAGEFUNC>(ID);
            return;
      }
      void build::page_return() {
            this->make<arch::opcodes::OP_PRETURN>();
            return;
      }
      void build::clear() {
            *this = build();
            return;
      }
      void build::close_page() {
            if (this->opended_pages.empty()) {
                  luramas::error::error("No opened pages to close");
            }
            this->make<arch::opcodes::OP_ENDPAGEFUNC>(this->opended_pages.back());
            this->opended_pages.pop_back();
            return;
      }
      void build::reinit(const luramas_address pc, const luramas_address idx, const luramas_register temp, const std::shared_ptr<luramas::il::ilang> &il, const std::shared_ptr<luramas::il::disassembly> &current) {
            this->idx = idx;
            this->pc = pc;
            this->il = il;
            this->current = current;
            this->temp = temp;
            this->constant.clear();
            this->labels.clear();
            return;
      }

      void build::cmp(const expr &e, const std::uintptr_t segregation) {
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
      bool build::is_page_loc(const profile::module_id mid, const profile::address addr) const {
            if (const auto it = this->details.find(mid); it != this->details.end()) {
                  return it->second.pages.contains(addr);
            }
            return false;
      }

      std::shared_ptr<disassembly> build::find_original_map(const profile::module_id mid, const luramas_address loc) {
            const auto og_data = this->original_address_data.find(mid);
            if (og_data == this->original_address_data.end()) {
                  luramas::error::error("Module ID does not exist in original address");
            }
            const auto ref = og_data->second.find(loc);
            if (ref == og_data->second.end()) {
                  luramas::error::error("Reference does not exist");
            }
            return ref->second;
      }
      void build::page_retn() {
            this->make<arch::opcodes::OP_PRETURN>(0u, 0u, 0u);
            return;
      }
      void build::page_retn(const luramas_register ret_reg, const luramas_address loc) {
            this->make<arch::opcodes::OP_PRETURN>(1u, ret_reg, loc);
            return;
      }
      void build::page_call(const profile::module_id mid, const luramas_address loc, const expr &r, const std::intptr_t v) {
            if (!this->find_original_map(mid, loc)) {
                  luramas::error::error("Unmapped Page");
            }
            auto reg = this->make_temp(r);
            this->set_flag<arch::data::flags::funknown_paging>();
            this->make<arch::opcodes::OP_PCALL>(loc, reg.r.r, v);
            return;
      }
      void build::make_goto(const profile::module_id mid, const luramas_address loc) {
            const auto r = this->find_original_map(mid, loc);
            this->gen<arch::opcodes::OP_JUMP>(r->addr)->ref = r;
            return;
      }
      void build::make_non_direct_goto(const expr &value, const profile::module_id mid, const luramas_address loc, const std::uintptr_t segregation) {

            auto v = this->make_temp(value).r.r;
            this->set_flag<arch::data::flags::fexpanded_non_direct_cft>();
            this->make<arch::opcodes::OP_SEGREGATE>(segregation);
            this->make<arch::opcodes::OP_CMPN>(v, loc);
            this->set_flag<arch::data::flags::fexpanded_non_direct_cft>();
            this->make_scope<arch::data::bin_kinds::eq_>(segregation);
            this->set_flag<arch::data::flags::fexpanded_non_direct_cft>();
            this->make_goto(mid, loc);
            this->close_scope();
            return;
      }
      void build::page_jump(const profile::module_id mid, const luramas_address loc) {
            if (!this->find_original_map(mid, loc)) {
                  luramas::error::error("Unmapped Page");
            }
            this->set_flag<arch::data::flags::funknown_paging>();
            this->make<arch::opcodes::OP_PJUMP>(loc);
            return;
      }
      void build::non_direct_page_call(const expr &value, const profile::module_id mid, const luramas_address loc, const expr &r, const std::intptr_t val, const std::uintptr_t segregation) {

            auto v = this->make_temp(value).r.r;

            this->set_flag<arch::data::flags::fexpanded_non_direct_cft>();
            this->make<arch::opcodes::OP_SEGREGATE>(segregation);
            this->make<arch::opcodes::OP_CMPN>(v, loc);
            this->set_flag<arch::data::flags::fexpanded_non_direct_cft>();
            this->make_scope<arch::data::bin_kinds::eq_>(segregation);
            this->set_flag<arch::data::flags::fexpanded_non_direct_cft>();
            this->page_call(mid, loc, r, val);
            this->close_scope();
            return;
      }
      void build::non_direct_page_jmp(const expr &value, const profile::module_id mid, const luramas_address loc, const std::uintptr_t segregation) {

            auto v = this->make_temp(value).r.r;

            this->set_flag<arch::data::flags::fexpanded_non_direct_cft>();
            this->make<arch::opcodes::OP_SEGREGATE>(segregation);
            this->make<arch::opcodes::OP_CMPN>(v, loc);
            this->set_flag<arch::data::flags::fexpanded_non_direct_cft>();
            this->make_scope<arch::data::bin_kinds::eq_>(segregation);
            this->set_flag<arch::data::flags::fexpanded_non_direct_cft>();
            this->page_jump(mid, loc);
            this->close_scope();
            return;
      }
      void build::external_page_call(const std::string &name, const std::vector<expr> &args, const std::vector<expr> &results) {

            const auto calle = expr(shared_from_this(), this->get_temp());
            this->make_global(calle, name);
            format_call_args(shared_from_this(), args);
            this->set_flag<arch::data::flags::fexternal_page_goto>();
            this->make<luramas::il::arch::opcodes::OP_CCALL>(calle.r.r, args.size(), results.size());
            format_call_returns(shared_from_this(), calle, results);
            return;
      }
      void build::non_direct_external_page_call(const expr &value, const luramas_address loc, const std::string &name, const std::vector<expr> &args, const std::vector<expr> &results, const std::uintptr_t segregation) {

            auto v = this->make_temp(value).r.r;

            this->set_flag<arch::data::flags::fexpanded_non_direct_cft>();
            this->make<arch::opcodes::OP_SEGREGATE>(segregation);
            this->make<arch::opcodes::OP_CMPN>(v, loc);
            this->set_flag<arch::data::flags::fexpanded_non_direct_cft>();
            this->make_scope<arch::data::bin_kinds::eq_>(segregation);
            this->set_flag<arch::data::flags::fexpanded_non_direct_cft>();
            this->external_page_call(name, args, results);
            this->close_scope();
            return;
      }
      void build::external_page_jmp(const luramas_address loc) {

            this->set_flag<arch::data::flags::funknown_paging>();
            this->set_flag<arch::data::flags::fexternal_page_goto>();
            this->make<arch::opcodes::OP_PJUMP>(loc);
            return;
      }
      void build::non_direct_external_page_jmp(const expr &value, const luramas_address loc, const std::uintptr_t segregation) {

            auto v = this->make_temp(value).r.r;

            this->set_flag<arch::data::flags::fexpanded_non_direct_cft>();
            this->make<arch::opcodes::OP_SEGREGATE>(segregation);
            this->make<arch::opcodes::OP_CMPN>(v, loc);
            this->set_flag<arch::data::flags::fexpanded_non_direct_cft>();
            this->make_scope<arch::data::bin_kinds::eq_>(segregation);
            this->set_flag<arch::data::flags::fexpanded_non_direct_cft>();
            this->external_page_jmp(loc);
            this->close_scope();
            return;
      }

} // namespace luramas::il::lifter::builder