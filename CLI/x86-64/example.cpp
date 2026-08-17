#ifdef LURAMAS_TARGET_X86
#include "example.hpp"
#include "../../framework/common/debug.hpp"
#include "../../framework/il/lifter/langs/x86-64/x86-64.hpp"

/* X86 Data */
static constexpr auto kMaxLen = luramas::il::X86::lifter::MAX_LEN;                                          /* Maximum X86 instruction length */
static constexpr auto kX64 = cpu_tracer::archs::interpretation_mode::x64;                                    /* X64 bit mode */
static constexpr auto kX32 = cpu_tracer::archs::interpretation_mode::x32;                                    /* X32 bit mode */
static constexpr auto kX16 = cpu_tracer::archs::interpretation_mode::x16;                                    /* X16 bit mode */
static constexpr auto kJump = static_cast<cpu_tracer::flag_storage>(luramas::profile::inst_kind::jump_to);   /* Jump to Flag storage */
static constexpr auto kCall = static_cast<cpu_tracer::flag_storage>(luramas::profile::inst_kind::call_to);   /* Call to Flag storage */
static constexpr auto kRetn = static_cast<cpu_tracer::flag_storage>(luramas::profile::inst_kind::return_to); /* Return to Flag storage */

/* Defs */
using edges = cpu_tracer::blocks::edges::addr_k_v; /* Addr edges */
using edges_k = cpu_tracer::blocks::edges::kind;   /* Edges kinds */

std::optional<std::string> luramas::decompile_x86(const std::string & /*code*/, std::shared_ptr<luramas::ir::data::format::format> &format, const bool  /*bytecode*/) {

      static constexpr auto kDefaultMode = kX64;
      luramas::il::X86::lifter::hardware_constants hw_constants;
      hw_constants.suggested_bit_set = 32U;
      hw_constants.MAXVL = 512U;

      auto buffer = std::make_shared<luramas::il::ilang>(); /* IL buffer */

      profile::externals::data<x86_reg> externals;                                                               /* Externals */
      cpu_tracer::blocks::builder::builder<kMaxLen, kDefaultMode> b;                                             /* Bytecode builder */
      boost::unordered_flat_set<luramas_address> external_addrs;                                                 /* External addresses */
      boost::unordered_flat_map<luramas_address, boost::unordered_flat_set<luramas_address>> external_addresses; /* External addresses to compile {realpc -> external addr] */

      std::optional<luramas_address> main_ret = std::nullopt; // TEST

      /* Build assembly */
      {
            /* Build data */
            b.emitd({0x55});                                                                                                     /* push rbp */
            b.emitd({0x48, 0x89, 0xE5});                                                                                         /* mov rbp, rsp */
            b.emitd({0x48, 0x83, 0xEC, 0x20});                                                                                   /* sub rsp, 0x20 */
            b.emitd({0xC7, 0x45, 0xFC, 0x00, 0x00, 0x00, 0x00});                                                                 /* mov dword ptr [rbp - 0x4], 0x0 */
            b.emitd({0xC7, 0x45, 0xF8, 0x09, 0x00, 0x00, 0x00});                                                                 /* mov dword ptr [rbp - 0x8], 0x9 */
            b.emitd({0xC7, 0x45, 0xF4, 0x00, 0x00, 0x00, 0x00});                                                                 /* mov dword ptr [rbp - 0xc], 0x0 */
            const auto label_1_d = *b.emit_label(0x1D);                                                                           /* label_1D: */
            b.emitd({0x81, 0x7D, 0xF4, 0xE8, 0x03, 0x00, 0x00});                                                                 /* cmp dword ptr [rbp - 0xc], 0x3e8 */
            const auto i_jge_5d_rpc = b.emitd({0x7D, 0x37}, edges{{0x5D, edges_k::next}}, kJump).first;                           /* jge label_5D */
            b.emitd({0x8B, 0x45, 0xF4});                                                                                         /* mov eax, dword ptr [rbp - 0xc] */
            b.emitd({0x89, 0x45, 0xE8});                                                                                         /* mov dword ptr [rbp - 0x18], eax */
            b.emitd({0x8B, 0x45, 0xF4});                                                                                         /* mov eax, dword ptr [rbp - 0xc] */
            b.emitd({0x35, 0xAA, 0x00, 0x00, 0x00});                                                                             /* xor eax, 0xaa */
            b.emitd({0x89, 0x45, 0xEC});                                                                                         /* mov dword ptr [rbp - 0x14], eax */
            b.emitd({0x8B, 0x45, 0xF4});                                                                                         /* mov eax, dword ptr [rbp - 0xc] */
            b.emitd({0x83, 0xC0, 0x03});                                                                                         /* add eax, 0x3 */
            b.emitd({0x89, 0x45, 0xF0});                                                                                         /* mov dword ptr [rbp - 0x10], eax */
            b.emitd({0x48, 0x8D, 0x7D, 0xF8});                                                                                   /* lea rdi, [rbp - 0x8] */
            b.emitd({0x48, 0x8D, 0x75, 0xE8});                                                                                   /* lea rsi, [rbp - 0x18] */
            b.emitd({0xBA, 0x13, 0x00, 0x00, 0x00});                                                                             /* mov edx, 0x13 */
            const auto i_call_65_rpc = b.emitd({0xE8, 0x13, 0x00, 0x00, 0x00}, edges{{0x65, edges_k::next}}, kCall).first;        /* call 65 */
            const auto label_625 = *b.emit_label(0x625);                                                                         /* label_65: */
            b.emitd({0x8B, 0x45, 0xF4});                                                                                         /* mov eax, dword ptr [rbp - 0xc] */
            b.emitd({0x83, 0xC0, 0x01});                                                                                         /* add eax, 0x1 */
            b.emitd({0x89, 0x45, 0xF4});                                                                                         /* mov dword ptr [rbp - 0xc], eax */
            const auto i_jmp_1d_rpc = b.emitd({0xEB, 0xC0}, edges{{0x1D, edges_k::next}}, kJump).first;                           /* jmp label_1D */
            const auto label_5_d = *b.emit_label(0x5D);                                                                           /* label_5D: */
            b.emitd({0x31, 0xC0});                                                                                               /* xor eax, eax */
            b.emitd({0x48, 0x83, 0xC4, 0x20});                                                                                   /* add rsp, 0x20 */
            b.emitd({0x5D});                                                                                                     /* pop rbp */
            main_ret = b.emitd({0x90}, edges{{0x5D, edges_k::next}}).first;                                                      /* (nop)ret */
            const auto label_65 = *b.emit_label(0x65);                                                                           /* label_65: */
            b.emitd({0x55});                                                                                                     /* push rbp */
            b.emitd({0x48, 0x89, 0xE5});                                                                                         /* mov rbp, rsp */
            b.emitd({0x48, 0x89, 0x7D, 0xF8});                                                                                   /* mov qword ptr [rbp - 0x8], rdi */
            b.emitd({0x48, 0x89, 0x75, 0xF0});                                                                                   /* mov qword ptr [rbp - 0x10], rsi */
            b.emitd({0x89, 0x55, 0xEC});                                                                                         /* mov dword ptr [rbp - 0x14], edx */
            b.emitd({0xC7, 0x45, 0xE8, 0x00, 0x00, 0x00, 0x00});                                                                 /* mov dword ptr [rbp - 0x18], 0x0 */
            b.emitd({0xC7, 0x45, 0xE4, 0x00, 0x00, 0x00, 0x00});                                                                 /* mov dword ptr [rbp - 0x1c], 0x0 */
            b.emitd({0x8B, 0x45, 0xEC});                                                                                         /* mov eax, dword ptr [rbp - 0x14] */
            b.emitd({0x83, 0xF0, 0x5A});                                                                                         /* xor eax, 0x5a */
            b.emitd({0x48, 0x8B, 0x4D, 0xF0});                                                                                   /* mov rcx, qword ptr [rbp - 0x10] */
            b.emitd({0x8B, 0x09});                                                                                               /* mov ecx, dword ptr [rcx] */
            b.emitd({0xD1, 0xE1});                                                                                               /* shl ecx, 0x1 */
            b.emitd({0x01, 0xC8});                                                                                               /* add eax, ecx */
            b.emitd({0x89, 0x45, 0xE0});                                                                                         /* mov dword ptr [rbp - 0x20], eax */
            const auto label_95 = *b.emit_label(0x95);                                                                           /* label_95: */
            b.emitd({0x83, 0x7D, 0xE4, 0x0A});                                                                                   /* cmp dword ptr [rbp - 0x1c], 0xa */
            const auto i_jge_120_rpc = b.emitd({0x0F, 0x8D, 0x81, 0x00, 0x00, 0x00}, edges{{0x120, edges_k::next}}, kJump).first; /* jge label_120 */
            b.emitd({0x8B, 0x45, 0xE0});                                                                                         /* mov eax, dword ptr [rbp - 0x20] */
            b.emitd({0x6B, 0x4D, 0xE4, 0x03});                                                                                   /* imul ecx, dword ptr [rbp - 0x1c], 0x3 */
            b.emitd({0x31, 0xC8});                                                                                               /* xor eax, ecx */
            b.emitd({0x89, 0x45, 0xE0});                                                                                         /* mov dword ptr [rbp - 0x20], eax */
            b.emitd({0x8B, 0x45, 0xE0});                                                                                         /* mov eax, dword ptr [rbp - 0x20] */
            b.emitd({0x83, 0xE0, 0x01});                                                                                         /* and eax, 0x1 */
            b.emitd({0x83, 0xF8, 0x00});                                                                                         /* cmp eax, 0x0 */
            const auto i_jne_d0_rpc = b.emitd({0x75, 0x1A}, edges{{0xD0, edges_k::next}}, kJump).first;                           /* jne label_D0 */
            b.emitd({0x48, 0x8B, 0x45, 0xF8});                                                                                   /* mov rax, qword ptr [rbp - 0x8] */
            b.emitd({0x48, 0x63, 0x4D, 0xE4});                                                                                   /* movsxd rcx, dword ptr [rbp - 0x1c] */
            b.emitd({0x8B, 0x04, 0x88});                                                                                         /* mov eax, dword ptr [rax + rcx*0x4] */
            b.emitd({0x48, 0x8B, 0x4D, 0xF0});                                                                                   /* mov rcx, qword ptr [rbp - 0x10] */
            b.emitd({0x03, 0x41, 0x04});                                                                                         /* add eax, dword ptr [rcx + 0x4] */
            b.emitd({0x03, 0x45, 0xE8});                                                                                         /* add eax, dword ptr [rbp - 0x18] */
            b.emitd({0x89, 0x45, 0xE8});                                                                                         /* mov dword ptr [rbp - 0x18], eax */
            const auto i_jmp_e8_rpc = b.emitd({0xEB, 0x18}, edges{{0xE8, edges_k::next}}, kJump).first;                           /* jmp label_E8 */
            const auto label_d0 = *b.emit_label(0xD0);                                                                           /* label_D0: */
            b.emitd({0x48, 0x8B, 0x45, 0xF8});                                                                                   /* mov rax, qword ptr [rbp - 0x8] */
            b.emitd({0x48, 0x63, 0x4D, 0xE4});                                                                                   /* movsxd rcx, dword ptr [rbp - 0x1c] */
            b.emitd({0x8B, 0x04, 0x88});                                                                                         /* mov eax, dword ptr [rax + rcx*0x4] */
            b.emitd({0x48, 0x8B, 0x4D, 0xF0});                                                                                   /* mov rcx, qword ptr [rbp - 0x10] */
            b.emitd({0x33, 0x41, 0x08});                                                                                         /* xor eax, dword ptr [rcx + 0x8] */
            b.emitd({0x03, 0x45, 0xE8});                                                                                         /* add eax, dword ptr [rbp - 0x18] */
            b.emitd({0x89, 0x45, 0xE8});                                                                                         /* mov dword ptr [rbp - 0x18], eax */
            const auto label_e8 = *b.emit_label(0xE8);                                                                           /* label_E8: */
            b.emitd({0x83, 0x7D, 0xE8, 0x64});                                                                                   /* cmp dword ptr [rbp - 0x18], 0x64 */
            const auto i_jle_f0_rpc = b.emitd({0x7E, 0x02}, edges{{0xF0, edges_k::next}}, kJump).first;                           /* jle label_F0 */
            const auto i_jmp_120_rpc = b.emitd({0xEB, 0x30}, edges{{0x120, edges_k::next}}, kJump).first;                         /* jmp label_120 */
            const auto label_f0 = *b.emit_label(0xF0);                                                                           /* label_F0: */
            b.emitd({0x8B, 0x45, 0xE4});                                                                                         /* mov eax, dword ptr [rbp - 0x1c] */
            b.emitd({0x83, 0xC0, 0x01});                                                                                         /* add eax, 0x1 */
            b.emitd({0x89, 0x45, 0xE4});                                                                                         /* mov dword ptr [rbp - 0x1c], eax */
            b.emitd({0x8B, 0x45, 0xE4});                                                                                         /* mov eax, dword ptr [rbp - 0x1c] */
            b.emitd({0xB9, 0x03, 0x00, 0x00, 0x00});                                                                             /* mov ecx, 0x3 */
            b.emitd({0x99});                                                                                                     /* cdq */
            b.emitd({0xF7, 0xF9});                                                                                               /* idiv ecx */
            b.emitd({0x83, 0xFA, 0x00});                                                                                         /* cmp edx, 0x0 */
            const auto i_jne_10b_rpc = b.emitd({0x75, 0x02}, edges{{0x10B, edges_k::next}}, kJump).first;                         /* jne label_10B */
            const auto i_jmp_95_rpc = b.emitd({0xEB, 0x8A}, edges{{0x95, edges_k::next}}, kJump).first;                           /* jmp label_95 */
            const auto label_10_b = *b.emit_label(0x10B);                                                                         /* label_10B: */
            b.emitd({0x8B, 0x45, 0xE0});                                                                                         /* mov eax, dword ptr [rbp - 0x20] */
            b.emitd({0xD1, 0xE0});                                                                                               /* shl eax, 0x1 */
            b.emitd({0x8B, 0x4D, 0xE0});                                                                                         /* mov ecx, dword ptr [rbp - 0x20] */
            b.emitd({0xC1, 0xF9, 0x1F});                                                                                         /* sar ecx, 0x1f */
            b.emitd({0x09, 0xC8});                                                                                               /* or eax, ecx */
            b.emitd({0x89, 0x45, 0xE0});                                                                                         /* mov dword ptr [rbp - 0x20], eax */
            const auto i_jmp_95_rpc_j = b.emitd({0xE9, 0x75, 0xFF, 0xFF, 0xFF}, edges{{0x95, edges_k::next}}, kJump).first;        /* jmp label_95 */
            const auto label_120 = *b.emit_label(0x120);                                                                         /* label_120: */
            b.emitd({0x8B, 0x45, 0xE8});                                                                                         /* mov eax, dword ptr [rbp - 0x18] */
            b.emitd({0xD1, 0xE0});                                                                                               /* shl eax, 0x1 */
            b.emitd({0x89, 0x45, 0xDC});                                                                                         /* mov dword ptr [rbp - 0x24], eax */
            b.emitd({0x8B, 0x45, 0xDC});                                                                                         /* mov eax, dword ptr [rbp - 0x24] */
            b.emitd({0x2B, 0x45, 0xE8});                                                                                         /* sub eax, dword ptr [rbp - 0x18] */
            b.emitd({0x89, 0x45, 0xDC});                                                                                         /* mov dword ptr [rbp - 0x24], eax */
            b.emitd({0x83, 0x7D, 0xEC, 0x00});                                                                                   /* cmp dword ptr [rbp - 0x14], 0x0 */
            const auto i_jge_142_rpc = b.emitd({0x7D, 0x0B}, edges{{0x142, edges_k::next}}, kJump).first;                         /* jge label_142 */
            b.emitd({0x8B, 0x45, 0xDC});                                                                                         /* mov eax, dword ptr [rbp - 0x24] */
            b.emitd({0x35, 0xEF, 0xBE, 0xAD, 0xDE});                                                                             /* xor eax, 0xdeadbeef */
            b.emitd({0x89, 0x45, 0xDC});                                                                                         /* mov dword ptr [rbp - 0x24], eax */
            const auto label_142 = *b.emit_label(0x142);                                                                         /* label_142: */
            b.emitd({0x8B, 0x45, 0xDC});                                                                                         /* mov eax, dword ptr [rbp - 0x24] */
            b.emitd({0x89, 0x05, 0x00, 0x00, 0x00, 0x00});                                                                       /* mov dword ptr [rip], eax */
            b.emitd({0x8B, 0x45, 0xE8});                                                                                         /* mov eax, dword ptr [rbp - 0x18] */
            b.emitd({0x03, 0x45, 0xE0});                                                                                         /* add eax, dword ptr [rbp - 0x20] */
            b.emitd({0x5D});                                                                                                     /* pop rbp */
            const auto i_retn_142_rpc = b.emitd({0xC3}, edges{{0x142, edges_k::next}}, kRetn).first;                              /* ret */
            /* Connect Edges */
            b.connect_edge<edges_k::next>(label_5_d, i_jge_5d_rpc);    /* jge label_5D -> label_5D */
            b.connect_edge<edges_k::next>(label_65, i_call_65_rpc);   /* call 65 -> label_65 */
            b.connect_edge<edges_k::next>(label_1_d, i_jmp_1d_rpc);    /* jmp label_1D -> label_1D */
            b.connect_edge<edges_k::next>(label_120, i_jge_120_rpc);  /* jge label_120 -> label_120 */
            b.connect_edge<edges_k::next>(label_d0, i_jne_d0_rpc);    /* jne label_D0 -> label_D0 */
            b.connect_edge<edges_k::next>(label_e8, i_jmp_e8_rpc);    /* jmp label_E8 -> label_E8 */
            b.connect_edge<edges_k::next>(label_f0, i_jle_f0_rpc);    /* jle label_F0 -> label_F0 */
            b.connect_edge<edges_k::next>(label_120, i_jmp_120_rpc);  /* jmp label_120 -> label_120 */
            b.connect_edge<edges_k::next>(label_10_b, i_jne_10b_rpc);  /* jne label_10B -> label_10B */
            b.connect_edge<edges_k::next>(label_95, i_jmp_95_rpc_j);  /* jmp label_95 -> label_95 */
            b.connect_edge<edges_k::next>(label_95, i_jmp_95_rpc);    /* jmp label_95 -> label_95 */
            b.connect_edge<edges_k::next>(label_142, i_jge_142_rpc);  /* jge label_142 -> label_142 */
            b.connect_edge<edges_k::next>(label_625, i_retn_142_rpc); /* ret -> label_625 */
      }

      /* Build builder */
      luramas::profile::raw_data<kMaxLen> raw_data;                                                          /* Raw cpu tracer data */
      b.build(raw_data.sdata, raw_data.adata, raw_data.edata);                                               /* Build data */
      const auto graph = cpu_tracer::blocks::graph::generate_graph<kMaxLen>(raw_data.adata, raw_data.edata); /* Graphed out builderc */

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

      std::vector<std::pair<luramas::il::vinst<kMaxLen>, cs_insn>> pinsts; /* Instructions */

      /* Generate instruction pointers */
      {
            for (const auto &id : luramas::profile::analyze::linearize(graph)) {

                  csh handle = 0U;              /* Current capstone handle */
                  const auto &node = graph[id]; /* On node */

                  /* Get capstone handle */
                  switch (node->interpretation_id) {
                        case kX64: {
                              handle = x64_handle;
                              break;
                        }
                        case kX32: {
                              handle = x32_handle;
                              break;
                        }
                        case kX16: {
                              handle = x16_handle;
                              break;
                        }
                        default: {
                              switch (kDefaultMode) {
                                    case kX64: {
                                          handle = x64_handle;
                                          break;
                                    }
                                    case kX32: {
                                          handle = x32_handle;
                                          break;
                                    }
                                    case kX16: {
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
                  for (auto i = 0U; i < node->insts.size(); ++i) {

                        const auto &ninst = node->insts[i];

                        cs_insn *insn; /* Instruction ptr */
                        const auto count = cs_disasm(handle, &(*ninst.inst.bytes.begin()), ninst.inst.bytes.size(), ninst.inst.pc, 1, &insn);
                        for (auto idx = 0U; idx < count; ++idx) {

                              luramas::il::vinst<kMaxLen> vinst;
                              vinst.inst = ninst;

                              /* Get Real PC edges */
                              if (i + 1U == node->insts.size()) {
                                    if (const auto eit = raw_data.edata.successors.find(ninst.inst.real_pc); eit != raw_data.edata.successors.end()) {

                                          if (!vinst.edges) {
                                                vinst.edges.emplace();
                                          }
                                          auto &v = *vinst.edges;
                                          for (const auto &ei : eit->second) {
                                                profile::edge e;
                                                e.second = luramas::profile::inst_kind(ninst.flags);
                                                if (ei.kinds[static_cast<std::uint8_t>(cpu_tracer::blocks::edges::kind::signaled)]) {
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

      // TEST
      if (main_ret) {
            auto ptr = std::make_shared<luramas::il::disassembly>();
            ptr->op = luramas::il::arch::opcodes::OP_RETURN;
            pinsts[*main_ret].first.insert_dism = {ptr};
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
      env_flags.options.odefault_bits = 1024U;
      env_flags.options.odefault_type = luramas::types::native::t_int64;
      env_flags.safety.sarith_rvalue_neg.insert({luramas::il::arch::data::bin_kinds::shl_, luramas::il::arch::data::bin_kinds::shr_});
      env_flags.safety.sarith_rvalue_zero.insert({luramas::il::arch::data::bin_kinds::mod_});
      env_flags.options.ounarith_operands_signess_no_side_effects.insert({luramas::il::arch::data::bin_kinds::or_, luramas::il::arch::data::bin_kinds::and_, luramas::il::arch::data::bin_kinds::xor_, luramas::il::arch::data::bin_kinds::bitnot_});
      env_flags.options.opage_call_action_s = [](const std::shared_ptr<luramas::ir::ir_stat> &s) {
            luramas::ir::ir_stat::space result;
            result.emplace_back(luramas::ir::tools::stat::generate::memoryset(s->l, s->lba, 32U));
            return result;
      };
      env_flags.options.opage_call_action_e = [](const std::shared_ptr<luramas::ir::ir_stat::ir_expr> &e) {
            luramas::ir::ir_stat::space result;
            result.emplace_back(luramas::ir::tools::stat::generate::memoryset(e->ev, e->xv, 32U));
            return result;
      };
      env_flags.options.opage_return_read = [](const std::shared_ptr<luramas::ir::ir_stat> &s) {
            return luramas::ir::tools::exprs::generate::memoryread(s->l, 32U);
      };
      format->linebreak.page_function_end_post = 1U;

      for (const auto &u : luramas::ir::lift(closure, env_flags)) {
            std::cout << u->str() << std::endl;
      }
      std::cin.get();
      std::cout << luramas::ir::code::generation::generate(luramas::ir::code::emitter::syntax::emitter_syntax::cpp, luramas::ir::lift(closure, env_flags), format) << std::endl;
      std::cin.get();
      return luramas::ir::code::generation::generate(luramas::ir::code::emitter::syntax::emitter_syntax::cpp, luramas::ir::lift(closure, env_flags), format);
}
#endif