#ifdef LURAMAS_TARGET_X86
#include "example.hpp"
#include "../../framework/common/debug.hpp"
#include "../../framework/il/lifter/langs/x86-64/x86-64.hpp"

/* X86 Data */
static constexpr auto MAX_LEN = luramas::il::X86::lifter::MAX_LEN;                                          /* Maximum X86 instruction length */
static constexpr auto X64 = cpu_tracer::archs::interpretation_mode::x64;                                    /* X64 bit mode */
static constexpr auto X32 = cpu_tracer::archs::interpretation_mode::x32;                                    /* X32 bit mode */
static constexpr auto X16 = cpu_tracer::archs::interpretation_mode::x16;                                    /* X16 bit mode */
static constexpr auto JUMP = static_cast<cpu_tracer::flag_storage>(luramas::profile::inst_kind::jump_to);   /* Jump to Flag storage */
static constexpr auto CALL = static_cast<cpu_tracer::flag_storage>(luramas::profile::inst_kind::call_to);   /* Call to Flag storage */
static constexpr auto RETN = static_cast<cpu_tracer::flag_storage>(luramas::profile::inst_kind::return_to); /* Return to Flag storage */

/* Defs */
using edges = cpu_tracer::blocks::edges::addr_k_v; /* Addr edges */
using edges_k = cpu_tracer::blocks::edges::kind;   /* Edges kinds */

std::optional<std::string> luramas::decompile_x86(const std::string &code, std::shared_ptr<luramas::ir::data::format::format> &format, const bool bytecode) {

      static constexpr auto DEFAULT_MODE = X64;
      luramas::il::X86::lifter::hardware_constants hw_constants;
      hw_constants.suggested_bit_set = 32u;
      hw_constants.MAXVL = 512u;

      auto buffer = std::make_shared<luramas::il::ilang>(); /* IL buffer */

      profile::externals::data<x86_reg> externals;                                                               /* Externals */
      cpu_tracer::blocks::builder::builder<MAX_LEN, DEFAULT_MODE> b;                                             /* Bytecode builder */
      boost::unordered_flat_set<luramas_address> external_addrs;                                                 /* External addresses */
      boost::unordered_flat_map<luramas_address, boost::unordered_flat_set<luramas_address>> external_addresses; /* External addresses to compile {realpc -> external addr] */

      /* Build assembly */
      {
            /* Build data */
            b.emitd({0xB8, 0x05, 0x00, 0x00, 0x00});                                                                      /* mov eax, 0x5 */
            b.emitd({0xBB, 0x05, 0x00, 0x00, 0x00});                                                                      /* mov ebx, 0x5 */
            b.emitd({0x39, 0xD8});                                                                                        /* cmp eax, ebx */
            const auto i_je_10_rpc = b.emitd({0x74, 0x02}, edges{{0x10, edges_k::next}}, JUMP).first;                     /* je label_10 */
            const auto i_jmp_15_rpc = b.emitd({0xEB, 0x05}, edges{{0x15, edges_k::next}}, JUMP).first;                    /* jmp label_15 */
            const auto label_10 = *b.emit_label(0x10);                                                                    /* label_10: */
            const auto i_call_1e_rpc = b.emitd({0xE8, 0x09, 0x00, 0x00, 0x00}, edges{{0x1E, edges_k::next}}, CALL).first; /* call 1e */
            const auto label_15 = *b.emit_label(0x15);                                                                    /* label_15: */
            b.emitd({0xB8, 0x01, 0x00, 0x00, 0x00});                                                                      /* mov eax, 0x1 */
            b.emitd({0x31, 0xDB});                                                                                        /* xor ebx, ebx */
            b.emitd({0xCD, 0x80});                                                                                        /* int 0x80 */
            const auto label_1E = *b.emit_label(0x1E);                                                                    /* label_1E: */
            external_addresses[b.emitd({0xE8, 0x95, 0x99, 0x92, 0x02}, std::nullopt, CALL).first].insert(0x29299b8);      /* call 29299b8 [EXTERNAL] */
            external_addrs.insert(0x29299b8);                                                                             /* External: 0x29299b8 */
            const auto i_retn_1e_rpc = b.emitd({0xC3}, edges{{0x1E, edges_k::next}}, RETN).first;                         /* ret */
            /* Connect Edges */
            b.connect_edge<edges_k::next>(label_10, i_je_10_rpc);   /* je label_10 -> label_10 */
            b.connect_edge<edges_k::next>(label_15, i_jmp_15_rpc);  /* jmp label_15 -> label_15 */
            b.connect_edge<edges_k::next>(label_1E, i_call_1e_rpc); /* call 1e -> label_1E */
            b.connect_edge<edges_k::next>(label_1E, i_retn_1e_rpc); /* ret -> label_1E */
      }

      /* Build builder */
      luramas::profile::raw_data<MAX_LEN> raw_data;                                                          /* Raw cpu tracer data */
      b.build(raw_data.sdata, raw_data.adata, raw_data.edata);                                               /* Build data */
      const auto graph = cpu_tracer::blocks::graph::generate_graph<MAX_LEN>(raw_data.adata, raw_data.edata); /* Graphed out builderc */

      /* Emit externals */
      for (const auto &i : external_addrs) {
            profile::externals::emit(externals, i, {}, {}, "UNK_" + std::to_string(i));
      }

      /* Capstone handler */
      std::vector<std::pair<cs_insn *, std::size_t>> insts; /* Capstone instruction, count */
      csh x64_handle;                                       /* X64 capstone handle */
      csh x32_handle;                                       /* X32 capstone handle */
      csh x16_handle;                                       /* X16 capstone handle */

      /* Init capstone handle */
      {
            /* X64 */
            if (cs_open(CS_ARCH_X86, CS_MODE_64, &x64_handle) != CS_ERR_OK) {
                  return "";
            }
            cs_option(x64_handle, CS_OPT_DETAIL, CS_OPT_ON);
            /* X32 */
            if (cs_open(CS_ARCH_X86, CS_MODE_32, &x32_handle) != CS_ERR_OK) {
                  return "";
            }
            cs_option(x32_handle, CS_OPT_DETAIL, CS_OPT_ON);
            /* X16 */
            if (cs_open(CS_ARCH_X86, CS_MODE_16, &x16_handle) != CS_ERR_OK) {
                  return "";
            }
            cs_option(x16_handle, CS_OPT_DETAIL, CS_OPT_ON);
      }

      std::vector<std::pair<luramas::il::vinst<MAX_LEN>, cs_insn>> pinsts; /* Instructions */

      /* Generate instruction pointers */
      {
            for (const auto &i : luramas::profile::analyze::linearize(graph)) {

                  csh handle;                  /* Current capstone handle */
                  const auto &node = graph[i]; /* On node */

                  /* Get capstone handle */
                  switch (node->interpretation_id) {
                        case X64: {
                              handle = x64_handle;
                              break;
                        }
                        case X32: {
                              handle = x32_handle;
                              break;
                        }
                        case X16: {
                              handle = x16_handle;
                              break;
                        }
                        default: {
                              switch (DEFAULT_MODE) {
                                    case X64: {
                                          handle = x64_handle;
                                          break;
                                    }
                                    case X32: {
                                          handle = x32_handle;
                                          break;
                                    }
                                    case X16: {
                                          handle = x16_handle;
                                          break;
                                    }
                                    default: {
                                          break;
                                    }
                              }
                        }
                  }

                  /* Disassemble */
                  for (auto i = 0u; i < node->insts.size(); ++i) {

                        const auto &ninst = node->insts[i];

                        cs_insn *insn; /* Instruction ptr */
                        const auto count = cs_disasm(handle, &(*ninst.inst.bytes.begin()), ninst.inst.bytes.size(), ninst.inst.pc, 1, &insn);
                        for (auto idx = 0u; idx < count; ++idx) {

                              luramas::il::vinst<MAX_LEN> vinst;
                              vinst.inst = ninst;

                              /* Get Real PC edges */
                              if (i + 1u == node->insts.size()) {
                                    if (const auto eit = raw_data.edata.successors.find(ninst.inst.real_pc); eit != raw_data.edata.successors.end()) {

                                          if (!vinst.edges) {
                                                vinst.edges.emplace();
                                          }
                                          auto &v = *vinst.edges;
                                          for (const auto &ei : eit->second) {
                                                profile::edge e;
                                                e.second = luramas::profile::inst_kind(ninst.flags);
                                                if (ei.kinds[std::uint8_t(cpu_tracer::blocks::edges::kind::signaled)]) {
                                                      e.second = luramas::profile::inst_kind::signaled_to;
                                                }
                                                e.first = luramas::profile::real_or_addr(true, ei.dst_realpc);
                                                v.emplace_back(e);
                                          }
                                    }
                              }

                              /* Get external edges */
                              if (const auto exit = external_addresses.find(ninst.inst.real_pc); exit != external_addresses.end()) {

                                    /* Emit externals */
                                    if (!vinst.edges) {
                                          vinst.edges.emplace();
                                    }
                                    auto &v = *vinst.edges;
                                    for (const auto &ei : exit->second) {
                                          v.emplace_back(luramas::profile::real_or_addr(false, ei), luramas::profile::inst_kind(ninst.flags));
                                    }
                              }
                              pinsts.emplace_back(vinst, insn[idx]);
                        }
                        insts.emplace_back(insn, count);
                  }
            }
      }

      /* Generate page/label data */
      profile::details details;
      details.pages = luramas::profile::analyze::generate_pages(raw_data);

      /* Lift X86 to IL */
      luramas::il::X86::lifter::lift(buffer, pinsts, hw_constants, externals, details);

      /* Free capstone instructions */
      for (const auto &[insn, n] : insts) {
            cs_free(insn, n);
      }

      /* Generate closure */
      auto closure = luramas::closures::gen_closure(buffer);
      closure->flags.fassociated_args = true;

      /* Setup environment flags */
      luramas::ir::passes::environment_flags env_flags;
      env_flags.feliminate_flags = true;
      env_flags.fprimitive_object = true;
      env_flags.fdefault_value_arith = false;
      env_flags.fcomparative_results_binvals = false;
      env_flags.fhas_pages = true;
      env_flags.fhas_types = true;
      env_flags.fuse_bitwise = true;
      env_flags.fhas_memory = true;
      env_flags.fexprcanon_use_table = true;
      env_flags.fhas_references = true;
      env_flags.fremove_page_dead_args = true;
      env_flags.fallow_definition_cast = true;
      env_flags.fremove_main_dead_args = true;
      env_flags.fremove_dead_synthetics = true;
      env_flags.fpromote_safety = true;
      env_flags.fallow_expr_opt_type_constraints = true;
      env_flags.options.odefault_bits = 1024u;
      env_flags.options.odefault_type = luramas::types::native::t_int64;
      env_flags.safety.sarith_rvalue_neg.insert({luramas::il::arch::data::bin_kinds::shl_, luramas::il::arch::data::bin_kinds::shr_});
      env_flags.safety.sarith_rvalue_zero.insert({luramas::il::arch::data::bin_kinds::mod_});
      env_flags.options.ounarith_operands_signess_no_side_effects.insert({luramas::il::arch::data::bin_kinds::or_, luramas::il::arch::data::bin_kinds::and_, luramas::il::arch::data::bin_kinds::xor_, luramas::il::arch::data::bin_kinds::bitnot_});
      env_flags.options.opage_call_action_s = [](const std::shared_ptr<luramas::ir::ir_stat> &s) {
            luramas::ir::ir_stat::space result;
            result.emplace_back(luramas::ir::tools::stat::generate::memoryset(s->l, s->lba, 32u));
            return result;
      };
      env_flags.options.opage_call_action_e = [](const std::shared_ptr<luramas::ir::ir_stat::ir_expr> &e) {
            luramas::ir::ir_stat::space result;
            result.emplace_back(luramas::ir::tools::stat::generate::memoryset(e->ev, e->xv, 32u));
            return result;
      };
      env_flags.options.opage_return_read = [](const std::shared_ptr<luramas::ir::ir_stat> &s) {
            return luramas::ir::tools::exprs::generate::memoryread(s->l, 32u);
      };
      format->linebreak.page_function_end_post = 1u;

      std::cout << luramas::ir::code::generation::generate(luramas::ir::code::emitter::syntax::emitter_syntax::cpp, luramas::ir::lift(closure, env_flags), format) << std::endl;
      std::cin.get();
      return luramas::ir::code::generation::generate(luramas::ir::code::emitter::syntax::emitter_syntax::cpp, luramas::ir::lift(closure, env_flags), format);
}
#endif