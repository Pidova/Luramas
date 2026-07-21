#ifdef LURAMAS_TARGET_X86
#include "private/simd.hpp"
#include "private/tools.hpp"
#include "private/vm.hpp"
#include <immintrin.h>

/* 
    Ref: 
        * https://c9x.me/x86/
        * http://ref.x86asm.net/coder32.html
        * http://ref.x86asm.net/coder64.html
        * https://sandpile.org
        * https://www.felixcloutier.com/x86/
        * https://www.intel.com/content/www/us/en/developer/articles/technical/intel-sdm.html
*/

/* Parses instructions. */
void parser::parse_instruction(const luramas::il::helpers::low::disassembly_manager<cs_insn> &dism, const luramas::il::X86::lifter::hardware_constants &hw_constants, const luramas::profile::externals::data<x86_reg> &external) {

      bool inited = false;
      luramas_address pc = 0u;
      const auto &il = dism.il;
      vm::registrar registrar(x86_insn::X86_INS_NOP, nullptr, hw_constants, external);

      boost::unordered_flat_set<luramas_address> set_pages;
      std::vector<std::vector<std::shared_ptr<luramas::il::disassembly>>> opened_conditions;

      auto build = std::make_shared<luramas::il::lifter::builder::build>();
      build->details = std::move(dism.details);
      build->original_address_data = std::move(dism.original_address_data);
      build->suggested_bit_set = registrar.hw_constants.suggested_bit_set;

      for (auto idx = 0u; idx < dism.data.size(); ++idx) {

            const auto &[vinst, d] = dism.data[idx];

            const auto &original_mid = build->original_address_data.find(vinst.main.mid)->second;
            auto &details_mid = build->details.find(vinst.main.mid)->second;

            /* Original */
            auto &il_dism = original_mid.find(vinst.main.pc)->second;
            il_dism->clear();

            /* Init registrar */
            registrar.build = build;
            registrar.original = vinst.rinst;
            registrar.bytes = vinst.main.bytes;

            /* Open scope */
            if (vinst.fstart_cmp_bytes) {
                  std::vector<std::shared_ptr<luramas::il::disassembly>> cmps;
                  for (auto i = 0u; i < vinst.main.bytes.size(); ++i) {
                        build->cmp(luramas::il::lifter::builder::build::expr(build, vinst.main.pc + i).memread(luramas::types::native::t_int8.bits()) == vinst.main.bytes[i]);
                        build->make<luramas::il::arch::opcodes::OP_SEGREGATE>(LURAMAS_IR_DEFAULT_SEGREGATION_ID);
                        cmps.emplace_back(build->make(luramas::il::arch::data::bin_kindflip(luramas::il::arch::data::bin_kinds::et_)));
                  }
                  opened_conditions.emplace_back(cmps);
            }

            /* Init builder */
            build->reinit(pc, idx, dism.temp_reg, il, il_dism);
            build->precomputed();
            if (vinst.main.entry) {
                  registrar.build->make<luramas::il::arch::opcodes::OP_ENTRY_POINT>();
            }

            const auto af = tools::make(build, xeflags::AF);
            const auto cf = tools::make(build, xeflags::CF);
            const auto sf = tools::make(build, xeflags::SF);
            const auto zf = tools::make(build, xeflags::ZF);
            const auto pf = tools::make(build, xeflags::PF);
            const auto of = tools::make(build, xeflags::OF);
            const auto tf = tools::make(build, xeflags::TF);
            const auto itf = tools::make(build, xeflags::IF);
            const auto df = tools::make(build, xeflags::DF);
            const auto nf = tools::make(build, xeflags::NT);
            const auto rf = tools::make(build, xeflags::RF);
            const auto vm = tools::make(build, xeflags::VM);
            const auto ac = tools::make(build, xeflags::AC);
            const auto vif = tools::make(build, xeflags::VIF);
            const auto vip = tools::make(build, xeflags::VIP);
            const auto gi = tools::make(build, xeflags::GI);
            const auto id = tools::make(build, xeflags::ID);
            const auto ai = tools::make(build, xeflags::AI);
            const auto c0 = tools::make(build, xeflags::C0);
            const auto c1 = tools::make(build, xeflags::C1);
            const auto c2 = tools::make(build, xeflags::C2);
            const auto c3 = tools::make(build, xeflags::C3);
            if (!inited) {
                  
                  /* Init Flags */
                  registrar.setf<xeflags::AF>(af);
                  registrar.setf<xeflags::CF>(cf);
                  registrar.setf<xeflags::SF>(sf);
                  registrar.setf<xeflags::ZF>(zf);
                  registrar.setf<xeflags::PF>(pf);
                  registrar.setf<xeflags::OF>(of);
                  registrar.setf<xeflags::TF>(tf);
                  registrar.setf<xeflags::IF>(itf);
                  registrar.setf<xeflags::DF>(df);
                  registrar.setf<xeflags::NT>(nf);
                  registrar.setf<xeflags::RF>(rf);
                  registrar.setf<xeflags::VM>(vm);
                  registrar.setf<xeflags::AC>(ac);
                  registrar.setf<xeflags::VIF>(vif);
                  registrar.setf<xeflags::VIP>(vip);
                  registrar.setf<xeflags::GI>(gi);
                  registrar.setf<xeflags::ID>(id);
                  registrar.setf<xeflags::AI>(ai);
                  registrar.setf<xeflags::C0>(c0);
                  registrar.setf<xeflags::C1>(c1);
                  registrar.setf<xeflags::C2>(c2);
                  registrar.setf<xeflags::C3>(c3);
                 
                  /* Init registers */
                  {
                        constexpr auto START = static_cast<std::size_t>(X86_REG_INVALID) + 1u;
                        constexpr auto END = static_cast<std::size_t>(X86_REG_BND3);
                        constexpr auto COUNT = END - START + 1u;
                        [&]<std::size_t... Is>(std::index_sequence<Is...>) {
                              (registrar.setr<static_cast<x86_reg>(START + Is)>(tools::make(build, static_cast<x86_reg>(START + Is))), ...);
                        }(std::make_index_sequence<COUNT>{});
                  }
                  registrar.zero_flags();
                  inited = true;
            } else {
                  for (auto &[t, expr] : registrar.regs) {
                        expr.b = build;
                  }
                  for (auto &[t, expr] : registrar.flags) {
                        expr.b = build;
                  }
            }
            if (const auto it = details_mid.pages.find(vinst.main.pc); it != details_mid.pages.end() && !set_pages.contains(*it)) {
                  set_pages.insert(*it);
                  registrar.build->make_page(*it);
            }

            /* Set data (Can not be optable because some stuff may need too resolved dynamically) */
            const auto operands = tools::common::canonicalize_insert(vinst.main, build, d.detail->x86, tools::flags(d.id == x86_insn::X86_INS_LEA, kinds::unsign(static_cast<x86_insn>(d.id))));
            registrar.inst = static_cast<x86_insn>(d.id);
            if (!vm::parse(registrar, operands)) {

                  if (const auto bint = simd::get(registrar.inst); !bint.empty()) {
                        build->make_built_in(bint, operands, {af, cf, sf, zf, pf, of, tf, itf, df, nf, rf, c0, c1, c2, c3});
                  }
            }
            if (dism.il->flags.fannotate_instructions) {
                  build->make<luramas::il::arch::opcodes::OP_ANNOTATE_PREV>(dism.il->make_kvalue<luramas::il::arch::data::kval_kinds::string>(d.mnemonic + std::string("   ") + d.op_str));
            }
            if (vinst.fend_cmp_bytes && !opened_conditions.empty()) {
                  if (const auto &b = opened_conditions.back(); !b.empty()) {
                        const auto marker = build->gen<luramas::il::arch::opcodes::OP_NOP>();
                        for (const auto &i : opened_conditions.back()) {
                              i->ref = marker;
                        }
                  }
                  opened_conditions.pop_back();
            }
            pc += d.size;
      }
      if (!opened_conditions.empty()) {
            luramas::error::error("Unclosed conditions");
      }
      il->commit_dis();
      return;
}

#endif