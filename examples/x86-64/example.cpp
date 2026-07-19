#ifdef LURAMAS_TARGET_X86

#include "example.hpp"
#include "../../framework/il/lifter/langs/x86-64/x86-64.hpp"

std::optional<std::string> luramas::decompile_x86(const std::string &code, std::shared_ptr<luramas::ir::data::format::format> &format, const bool bytecode) {

      auto buffer = std::make_shared<luramas::il::ilang>();
      boost::unordered_flat_map<luramas::profile::module_id, luramas::profile::inst_result> mid_res;
      luramas::profile::builder::manager data;

      data.emit({0x89, 0xF8});                                                  /* mov eax, edi */
      data.emit({0x6B, 0xC0, 0x07});                                            /* imul eax, eax, 7 */
      data.emit({0x31, 0xF8});                                                  /* xor eax, edi */
      data.emit({0xA9, 0x01, 0x00, 0x00, 0x00});                                /* test eax, 1 */
      data.emit({0x74, 0x18}, luramas::profile::inst_kind::jump_to, 1u, true);  /* je 0x103a */
      data.emit({0x48, 0x8B, 0x4D, 0xF0});                                      /* mov rcx, qword ptr [rbp - 0x10] */
      data.emit({0xB5, 0x90});                                                  /* mov ch, 0x90 */
      data.emit({0x48, 0x81, 0xC1, 0x34, 0x12, 0x00, 0x00});                    /* add rcx, 0x1234 */
      data.emit({0x9F});                                                        /* lahf  */
      data.emit({0x80, 0xF4, 0x5A});                                            /* xor ah, 0x5a */
      data.emit({0x9E});                                                        /* sahf  */
      data.emit({0x48, 0x13, 0x4D, 0xE8});                                      /* adc rcx, qword ptr [rbp - 0x18] */
      data.emit({0xEB, 0x11}, luramas::profile::inst_kind::jump_to, 2u, false); /* jmp 0x104b */
      data.emit_label(1u);                                                      /* LABEL */
      data.emit({0x48, 0x8B, 0x4D, 0xE8});                                      /* mov rcx, qword ptr [rbp - 0x18] */
      data.emit({0x48, 0xF7, 0xD1});                                            /* not rcx */
      data.emit({0x48, 0xFF, 0xC1});                                            /* inc rcx */
      data.emit({0x83, 0xF1, 0xFF});                                            /* xor ecx, 0xffffffff */
      data.emit({0x48, 0x83, 0xC1, 0x01});                                      /* add rcx, 1 */
      data.emit_label(2u);                                                      /* LABEL */
      data.emit({0x4C, 0x8D, 0x45, 0xD8});                                      /* lea r8, [rbp - 0x28] */
      data.emit({0x49, 0x89, 0x08});                                            /* mov qword ptr [r8], rcx */
      data.emit({0x41, 0x8B, 0x00});                                            /* mov eax, dword ptr [r8] */
      data.emit({0x48, 0x98});                                                  /* cdqe  */
      data.emit({0x41, 0xB9, 0x05, 0x00, 0x00, 0x00});                          /* mov r9d, 5 */
      data.emit_label(3u);                                                      /* LABEL */
      data.emit({0x48, 0xC1, 0xC0, 0x05});                                      /* rol rax, 5 */
      data.emit({0x48, 0x31, 0xC8});                                            /* xor rax, rcx */
      data.emit({0x48, 0xC1, 0xC8, 0x05});                                      /* ror rax, 5 */
      data.emit({0x41, 0xFF, 0xC9});                                            /* dec r9d */
      data.emit({0x75, 0xF0}, luramas::profile::inst_kind::jump_to, 3u, true);  /* jne 0x105d */
      data.emit({0x83, 0xF8, 0x00});                                            /* cmp eax, 0 */
      data.emit({0x74, 0x19}, luramas::profile::inst_kind::jump_to, 4u, true);  /* je 0x108b */
      data.emit({0x83, 0xF8, 0x01});                                            /* cmp eax, 1 */
      data.emit({0x74, 0x1E}, luramas::profile::inst_kind::jump_to, 5u, true);  /* je 0x1095 */
      data.emit({0x83, 0xF8, 0x02});                                            /* cmp eax, 2 */
      data.emit({0x74, 0x23}, luramas::profile::inst_kind::jump_to, 6u, true);  /* je 0x109f */
      data.emit({0x83, 0xF8, 0x03});                                            /* cmp eax, 3 */
      data.emit({0x74, 0x29}, luramas::profile::inst_kind::jump_to, 7u, true);  /* je 0x10aa */
      data.emit({0x48, 0x8B, 0x45, 0xF8});                                      /* mov rax, qword ptr [rbp - 8] */
      data.emit({0x48, 0x33, 0x45, 0xF0});                                      /* xor rax, qword ptr [rbp - 0x10] */
      data.emit({0xEB, 0x22}, luramas::profile::inst_kind::jump_to, 8u, false); /* jmp 0x10ad */
      data.emit_label(4u);                                                      /* LABEL */
      data.emit({0x48, 0x8B, 0x45, 0xF8});                                      /* mov rax, qword ptr [rbp - 8] */
      data.emit({0x48, 0x03, 0x45, 0xF0});                                      /* add rax, qword ptr [rbp - 0x10] */
      data.emit({0xEB, 0x18}, luramas::profile::inst_kind::jump_to, 8u, false); /* jmp 0x10ad */
      data.emit_label(5u);                                                      /* LABEL */
      data.emit({0x48, 0x8B, 0x45, 0xF8});                                      /* mov rax, qword ptr [rbp - 8] */
      data.emit({0x48, 0x2B, 0x45, 0xE8});                                      /* sub rax, qword ptr [rbp - 0x18] */
      data.emit({0xEB, 0x0E}, luramas::profile::inst_kind::jump_to, 8u, false); /* jmp 0x10ad */
      data.emit_label(6u);                                                      /* LABEL */
      data.emit({0x48, 0x8B, 0x45, 0xF0});                                      /* mov rax, qword ptr [rbp - 0x10] */
      data.emit({0x48, 0x0F, 0xAF, 0x45, 0xE8});                                /* imul rax, qword ptr [rbp - 0x18] */
      data.emit({0xEB, 0x03}, luramas::profile::inst_kind::jump_to, 8u, false); /* jmp 0x10ad */
      data.emit_label(7u);                                                      /* LABEL */
      data.emit({0x48, 0x31, 0xC0});                                            /* xor rax, rax */
      data.emit_label(8u);                                                      /* LABEL */
      data.emit({0x48, 0x89, 0xEC});                                            /* mov rsp, rbp */
      data.emit({0x5D});                                                        /* pop rbp */
      data.emit({0x48, 0x89, 0x00});
      data.emit({0xC3}); /* ret  */

      // data.emit({0x55});                                                                               /* push rbp */
      // data.emit({0x48, 0x89, 0xE5});                                                                   /* mov rbp, rsp */
      // data.emit({0x48, 0x83, 0xEC, 0x20});                                                             /* sub rsp, 0x20 */
      // data.emit({0xC7, 0x45, 0xFC, 0x00, 0x00, 0x00, 0x00});                                           /* mov dword ptr [rbp - 4], 0 */
      // data.emit({0xC7, 0x45, 0xF8, 0x09, 0x00, 0x00, 0x00});                                           /* mov dword ptr [rbp - 8], 9 */
      // data.emit({0xC7, 0x45, 0xF4, 0x00, 0x00, 0x00, 0x00});                                           /* mov dword ptr [rbp - 0xc], 0 */
      // data.emit_label(3u);                                                                             /* LABEL */
      // data.emit({0x81, 0x7D, 0xF4, 0xE8, 0x03, 0x00, 0x00});                                           /* cmp dword ptr [rbp - 0xc], 0x3e8 */
      // data.emit({0x7D, 0x37}, luramas::profile::inst_kind::jump_to, 1u, true);                         /* jge 0x105d */
      // data.emit({0x8B, 0x45, 0xF4});                                                                   /* mov eax, dword ptr [rbp - 0xc] */
      // data.emit({0x89, 0x45, 0xE8});                                                                   /* mov dword ptr [rbp - 0x18], eax */
      // data.emit({0x8B, 0x45, 0xF4});                                                                   /* mov eax, dword ptr [rbp - 0xc] */
      // data.emit({0x35, 0xAA, 0x00, 0x00, 0x00});                                                       /* xor eax, 0xaa */
      // data.emit({0x89, 0x45, 0xEC});                                                                   /* mov dword ptr [rbp - 0x14], eax */
      // data.emit({0x8B, 0x45, 0xF4});                                                                   /* mov eax, dword ptr [rbp - 0xc] */
      // data.emit({0x83, 0xC0, 0x03});                                                                   /* add eax, 3 */
      // data.emit({0x89, 0x45, 0xF0});                                                                   /* mov dword ptr [rbp - 0x10], eax */
      // data.emit({0x48, 0x8D, 0x7D, 0xF8});                                                             /* lea rdi, [rbp - 8] */
      // data.emit({0x48, 0x8D, 0x75, 0xE8});                                                             /* lea rsi, [rbp - 0x18] */
      // data.emit({0xBA, 0x13, 0x00, 0x00, 0x00});                                                       /* mov edx, 0x13 */
      // data.emit({0xE8, 0x13, 0x00, 0x00, 0x00}, luramas::profile::inst_kind::call_to, 2u);             /* call 0x1065 */
      // data.emit({0x8B, 0x45, 0xF4});                                                                   /* mov eax, dword ptr [rbp - 0xc] */
      // data.emit({0x83, 0xC0, 0x01});                                                                   /* add eax, 1 */
      // data.emit({0x89, 0x45, 0xF4});                                                                   /* mov dword ptr [rbp - 0xc], eax */
      // data.emit({0xEB, 0xC0}, luramas::profile::inst_kind::jump_to, 3u, false);                        /* jmp 0x101d */
      // data.emit_label(1u);                                                                             /* LABEL */
      // data.emit({0x31, 0xC0});                                                                         /* xor eax, eax */
      // data.emit({0x48, 0x83, 0xC4, 0x20});                                                             /* add rsp, 0x20 */
      // data.emit({0x5D});                                                                               /* pop rbp */
      // data.emit({0xC3});                                                                               /* ret  */
      // data.emit_label(2u);                                                                             /* LABEL */
      // data.emit({0x55});                                                                               /* push rbp */
      // data.emit({0x48, 0x89, 0xE5});                                                                   /* mov rbp, rsp */
      // data.emit({0x48, 0x89, 0x7D, 0xF8});                                                             /* mov qword ptr [rbp - 8], rdi */
      // data.emit({0x48, 0x89, 0x75, 0xF0});                                                             /* mov qword ptr [rbp - 0x10], rsi */
      // data.emit({0x89, 0x55, 0xEC});                                                                   /* mov dword ptr [rbp - 0x14], edx */
      // data.emit({0xC7, 0x45, 0xE8, 0x00, 0x00, 0x00, 0x00});                                           /* mov dword ptr [rbp - 0x18], 0 */
      // data.emit({0xC7, 0x45, 0xE4, 0x00, 0x00, 0x00, 0x00});                                           /* mov dword ptr [rbp - 0x1c], 0 */
      // data.emit({0x8B, 0x45, 0xEC});                                                                   /* mov eax, dword ptr [rbp - 0x14] */
      // data.emit({0x83, 0xF0, 0x5A});                                                                   /* xor eax, 0x5a */
      // data.emit({0x48, 0x8B, 0x4D, 0xF0});                                                             /* mov rcx, qword ptr [rbp - 0x10] */
      // data.emit({0x8B, 0x09});                                                                         /* mov ecx, dword ptr [rcx] */
      // data.emit({0xD1, 0xE1});                                                                         /* shl ecx, 1 */
      // data.emit({0x01, 0xC8});                                                                         /* add eax, ecx */
      // data.emit({0x89, 0x45, 0xE0});                                                                   /* mov dword ptr [rbp - 0x20], eax */
      // data.emit_label(9u);                                                                             /* LABEL */
      // data.emit({0x83, 0x7D, 0xE4, 0x0A});                                                             /* cmp dword ptr [rbp - 0x1c], 0xa */
      // data.emit({0x0F, 0x8D, 0x81, 0x00, 0x00, 0x00}, luramas::profile::inst_kind::jump_to, 4u, true); /* jge 0x1120 */
      // data.emit({0x8B, 0x45, 0xE0});                                                                   /* mov eax, dword ptr [rbp - 0x20] */
      // data.emit({0x6B, 0x4D, 0xE4, 0x03});                                                             /* imul ecx, dword ptr [rbp - 0x1c], 3 */
      // data.emit({0x31, 0xC8});                                                                         /* xor eax, ecx */
      // data.emit({0x89, 0x45, 0xE0});                                                                   /* mov dword ptr [rbp - 0x20], eax */
      // data.emit({0x8B, 0x45, 0xE0});                                                                   /* mov eax, dword ptr [rbp - 0x20] */
      // data.emit({0x83, 0xE0, 0x01});                                                                   /* and eax, 1 */
      // data.emit({0x83, 0xF8, 0x00});                                                                   /* cmp eax, 0 */
      // data.emit({0x75, 0x1A}, luramas::profile::inst_kind::jump_to, 5u, true);                         /* jne 0x10d0 */
      // data.emit({0x48, 0x8B, 0x45, 0xF8});                                                             /* mov rax, qword ptr [rbp - 8] */
      // data.emit({0x48, 0x63, 0x4D, 0xE4});                                                             /* movsxd rcx, dword ptr [rbp - 0x1c] */
      // data.emit({0x8B, 0x04, 0x88});                                                                   /* mov eax, dword ptr [rax + rcx*4] */
      // data.emit({0x48, 0x8B, 0x4D, 0xF0});                                                             /* mov rcx, qword ptr [rbp - 0x10] */
      // data.emit({0x03, 0x41, 0x04});                                                                   /* add eax, dword ptr [rcx + 4] */
      // data.emit({0x03, 0x45, 0xE8});                                                                   /* add eax, dword ptr [rbp - 0x18] */
      // data.emit({0x89, 0x45, 0xE8});                                                                   /* mov dword ptr [rbp - 0x18], eax */
      // data.emit({0xEB, 0x18}, luramas::profile::inst_kind::jump_to, 6u, false);                        /* jmp 0x10e8 */
      // data.emit_label(5u);                                                                             /* LABEL */
      // data.emit({0x48, 0x8B, 0x45, 0xF8});                                                             /* mov rax, qword ptr [rbp - 8] */
      // data.emit({0x48, 0x63, 0x4D, 0xE4});                                                             /* movsxd rcx, dword ptr [rbp - 0x1c] */
      // data.emit({0x8B, 0x04, 0x88});                                                                   /* mov eax, dword ptr [rax + rcx*4] */
      // data.emit({0x48, 0x8B, 0x4D, 0xF0});                                                             /* mov rcx, qword ptr [rbp - 0x10] */
      // data.emit({0x33, 0x41, 0x08});                                                                   /* xor eax, dword ptr [rcx + 8] */
      // data.emit({0x03, 0x45, 0xE8});                                                                   /* add eax, dword ptr [rbp - 0x18] */
      // data.emit({0x89, 0x45, 0xE8});                                                                   /* mov dword ptr [rbp - 0x18], eax */
      // data.emit_label(6u);                                                                             /* LABEL */
      // data.emit({0x83, 0x7D, 0xE8, 0x64});                                                             /* cmp dword ptr [rbp - 0x18], 0x64 */
      // data.emit({0x7E, 0x02}, luramas::profile::inst_kind::jump_to, 7u, true);                         /* jle 0x10f0 */
      // data.emit({0xEB, 0x30}, luramas::profile::inst_kind::jump_to, 4u, false);                        /* jmp 0x1120 */
      // data.emit_label(7u);                                                                             /* LABEL */
      // data.emit({0x8B, 0x45, 0xE4});                                                                   /* mov eax, dword ptr [rbp - 0x1c] */
      // data.emit({0x83, 0xC0, 0x01});                                                                   /* add eax, 1 */
      // data.emit({0x89, 0x45, 0xE4});                                                                   /* mov dword ptr [rbp - 0x1c], eax */
      // data.emit({0x8B, 0x45, 0xE4});                                                                   /* mov eax, dword ptr [rbp - 0x1c] */
      // data.emit({0xB9, 0x03, 0x00, 0x00, 0x00});                                                       /* mov ecx, 3 */
      // data.emit({0x99});                                                                               /* cdq  */
      // data.emit({0xF7, 0xF9});                                                                         /* idiv ecx */
      // data.emit({0x83, 0xFA, 0x00});                                                                   /* cmp edx, 0 */
      // data.emit({0x75, 0x02}, luramas::profile::inst_kind::jump_to, 8u, true);                         /* jne 0x110b */
      // data.emit({0xEB, 0x8A}, luramas::profile::inst_kind::jump_to, 9u, false);                        /* jmp 0x1095 */
      // data.emit_label(8u);                                                                             /* LABEL */
      // data.emit({0x8B, 0x45, 0xE0});                                                                   /* mov eax, dword ptr [rbp - 0x20] */
      // data.emit({0xD1, 0xE0});                                                                         /* shl eax, 1 */
      // data.emit({0x8B, 0x4D, 0xE0});                                                                   /* mov ecx, dword ptr [rbp - 0x20] */
      // data.emit({0xC1, 0xF9, 0x1F});                                                                   /* sar ecx, 0x1f */
      // data.emit({0x09, 0xC8});                                                                         /* or eax, ecx */
      // data.emit({0x89, 0x45, 0xE0});                                                                   /* mov dword ptr [rbp - 0x20], eax */
      // data.emit({0xE9, 0x75, 0xFF, 0xFF, 0xFF}, luramas::profile::inst_kind::jump_to, 9u, false);      /* jmp 0x1095 */
      // data.emit_label(4u);                                                                             /* LABEL */
      // data.emit({0x8B, 0x45, 0xE8});                                                                   /* mov eax, dword ptr [rbp - 0x18] */
      // data.emit({0xD1, 0xE0});                                                                         /* shl eax, 1 */
      // data.emit({0x89, 0x45, 0xDC});                                                                   /* mov dword ptr [rbp - 0x24], eax */
      // data.emit({0x8B, 0x45, 0xDC});                                                                   /* mov eax, dword ptr [rbp - 0x24] */
      // data.emit({0x2B, 0x45, 0xE8});                                                                   /* sub eax, dword ptr [rbp - 0x18] */
      // data.emit({0x89, 0x45, 0xDC});                                                                   /* mov dword ptr [rbp - 0x24], eax */
      // data.emit({0x83, 0x7D, 0xEC, 0x00});                                                             /* cmp dword ptr [rbp - 0x14], 0 */
      // data.emit({0x7D, 0x0B}, luramas::profile::inst_kind::jump_to, 10u, true);                        /* jge 0x1142 */
      // data.emit({0x8B, 0x45, 0xDC});                                                                   /* mov eax, dword ptr [rbp - 0x24] */
      // data.emit({0x35, 0xEF, 0xBE, 0xAD, 0xDE});                                                       /* xor eax, 0xdeadbeef */
      // data.emit({0x89, 0x45, 0xDC});                                                                   /* mov dword ptr [rbp - 0x24], eax */
      // data.emit_label(10u);                                                                            /* LABEL */
      // data.emit({0x8B, 0x45, 0xDC});                                                                   /* mov eax, dword ptr [rbp - 0x24] */
      // data.emit({0x89, 0x05, 0x00, 0x00, 0x00, 0x00});                                                 /* mov dword ptr [rip], eax */
      // data.emit({0x8B, 0x45, 0xE8});                                                                   /* mov eax, dword ptr [rbp - 0x18] */
      // data.emit({0x03, 0x45, 0xE0});                                                                   /* add eax, dword ptr [rbp - 0x20] */
      // data.emit({0x5D});                                                                               /* pop rbp */
      // data.emit({0xC3});                                                                               /* ret  */

      data.extract(mid_res);

      const auto gened_details = luramas::profile::analyze::generate_details(mid_res);

      std::vector<std::pair<luramas::il::vinst, cs_insn>> pinsts;
      std::vector<std::pair<cs_insn *, std::size_t>> inst_freeable;

      csh handle;
      if (cs_open(CS_ARCH_X86, CS_MODE_64, &handle) != CS_ERR_OK) {
            return "";
      }
      cs_option(handle, CS_OPT_DETAIL, CS_OPT_ON);

      const auto target_mid = 1u;

      /* Get smallest */
      {
            const auto &insts = mid_res[target_mid];
            for (const auto &i : luramas::profile::analyze::order_of_execution_organized(mid_res, target_mid)) {

                  if (const auto it = insts.map.find(i.loc.second); it != insts.map.end()) {

                        const auto &inst = i.discrepency ? (*it->second.discrepancies)[*i.discrepency] : it->second.first;

                        cs_insn *insn;
                        auto count = cs_disasm(handle, &(*inst.bytes.begin()), inst.bytes.size(), inst.pc, 1, &insn);
                        if (!count) {
                              cs_close(&handle);
                              cs_open(CS_ARCH_X86, CS_MODE_32, &handle);
                              cs_option(handle, CS_OPT_DETAIL, CS_OPT_ON);
                              count = cs_disasm(handle, &(*inst.bytes.begin()), inst.bytes.size(), inst.pc, 1, &insn);
                              cs_close(&handle);
                              cs_open(CS_ARCH_X86, CS_MODE_16, &handle);
                              cs_option(handle, CS_OPT_DETAIL, CS_OPT_ON);
                        }
                        for (auto idx = 0u; idx < count; ++idx) {
                              pinsts.emplace_back(luramas::il::vinst(inst, it->second, i.fstart_scope, i.fend_scope), insn[idx]);
                        }
                        inst_freeable.emplace_back(insn, count);
                  } else {
                        break;
                  }
            }
      }

      boost::unordered_flat_map<profile::module_id, profile::analyze::details> details;
      details[target_mid] = gened_details;

      profile::externals::data<x86_reg> external;
      //profile::externals::emit(external, 0xFFF36090, {}, {}, "UNK_FFF36090");
      //profile::externals::emit(external, 0xFFF360E0, {}, {}, "UNK_FFF360E0");
      //profile::externals::emit(external, 0x00004AC0, {}, {}, "UNK_00004AC0");
      for (const auto &[lid, v] : details[target_mid].externals) {
            for (const auto &i : v) {
                  profile::externals::emit(external, i, {x86_reg::X86_REG_RCX, x86_reg::X86_REG_RDX}, {}, "UNK_" + std::to_string(i), lid);
            }
      }

      luramas::il::X86::lifter::lift(pinsts, buffer, details, external, luramas::il::X86::lifter::bit_mode::x32);
      for (const auto &[insn, n] : inst_freeable) {
            cs_free(insn, n);
      }

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
      env_flags.options.opage_call_action_s = [](const std::shared_ptr<ir_stat> &s) {
            ir_stat::space result;
            result.emplace_back(luramas::ir::tools::stat::generate::memoryset(s->l, s->lba, 32u));
            return result;
      };
      env_flags.options.opage_call_action_e = [](const std::shared_ptr<ir_stat::ir_expr> &e) {
            ir_stat::space result;
            result.emplace_back(luramas::ir::tools::stat::generate::memoryset(e->ev, e->xv, 32u));
            return result;
      };
      env_flags.options.opage_return_read = [](const std::shared_ptr<ir_stat> &s) {
            return luramas::ir::tools::exprs::generate::memoryread(s->l, 32u);
      };
      format->linebreak.page_function_end_post = 1u;

      return luramas::ir::code::generation::generate(luramas::ir::code::emitter::syntax::emitter_syntax::cpp, luramas::ir::lift(closure, env_flags), format);
}
#endif