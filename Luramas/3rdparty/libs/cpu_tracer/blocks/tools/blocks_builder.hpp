#pragma once
#include "blocks_loader.hpp"

namespace cpu_tracer::blocks::builder {

      /* Manually build blocks */
      template <std::uint8_t MAX_LEN, archs::interpretation_mode DEFAULT_MODE = archs::interpretation_mode::none>
      struct builder {

            /* Main instruction data */
            template <std::uint8_t MAX_LEN>
            struct instruction {
                  inst_data<MAX_LEN> inst;                                                   /* Instruction data  */
                  archs::interpretation_mode interp_mode = archs::interpretation_mode::none; /* Interpretation mode */
                  std::optional<edges::addr_k_v> jump_to_labels = std::nullopt;              /* Jump to labels */
                  std::optional<edges::addr_k_v> jump_to_realpc = std::nullopt;              /* Jump to realpc */
            };

            /* Emit instruction, returns {Real PC, Virtual PC], You can input PC but without it it will inc based on byte size and base */
            inline std::pair<address, address> emit(const inst_bytes<MAX_LEN> &bytes, const archs::interpretation_mode interp_mode = DEFAULT_MODE, const std::optional<address> prev_realpc = std::nullopt, const std::optional<address> pc = std::nullopt, const std::optional<edges::addr_k_v> &jump_to_labels = std::nullopt /* {Label name, kind} */, const flag_storage fs = 0u) {

                  instruction<MAX_LEN> result;
                  result.inst.flags = fs;
                  result.inst.inst.bytes = bytes;
                  result.inst.inst.real_pc = this->insts.size();
                  result.inst.inst.prev_real_pc = prev_realpc.value_or(!result.inst.inst.real_pc ? 0u : result.inst.inst.real_pc - 1u);
                  result.inst.inst.pc = pc.value_or(this->base);
                  if (!pc) {
                        this->base += bytes.size();
                  }
                  result.inst.inst.vcpu = 0u;
                  result.interp_mode = interp_mode;
                  result.jump_to_labels = jump_to_labels;
                  this->insts.emplace_back(result);
                  return std::make_pair(result.inst.inst.real_pc, result.inst.inst.pc);
            }

            /* Emit with input interp mode, returns {Real PC, Virtual PC] */
            template <archs::interpretation_mode m>
            inline std::pair<address, address> emit(const inst_bytes<MAX_LEN> &bytes, const std::optional<edges::addr_k_v> &jump_to_labels = std::nullopt, const flag_storage fs = 0u) {

                  return this->emit(bytes, m, std::nullopt, std::nullopt, jump_to_labels, fs);
            }

            /* Emit with default mode, returns {Real PC, Virtual PC] */
            inline std::pair<address, address> emitd(const inst_bytes<MAX_LEN> &bytes, const std::optional<edges::addr_k_v> &jump_to_labels = std::nullopt, const flag_storage fs = 0u) {

                  return this->emit(bytes, DEFAULT_MODE, std::nullopt, std::nullopt, jump_to_labels, fs);
            }

            /* Emit label, returns nullopt if label was already emmited. Returns next real PC if success. */
            inline std::optional<address> emit_label(const address label) {
                  if (!this->label_map.insert({label, this->insts.size()}).second) {
                        return std::nullopt;
                  }
                  this->label_idx_map[this->insts.size()] = label;
                  return this->insts.size();
            }

            /* Connect edge from RealPC -> RealPC, returns if successful of not */
            template <edges::kind k>
            inline bool connect_edge(const address dst_realpc, const address src_realpc) {
                  if (dst_realpc > this->insts.size() || src_realpc > this->insts.size()) {
                        return false;
                  }
                  auto &dst = this->insts[dst_realpc];
                  dst.jump_to_realpc = dst.jump_to_realpc.value_or(edges::addr_k_v{});
                  dst.jump_to_realpc->emplace_back(std::make_pair(src_realpc, k));
                  return true;
            }

            /* Emit internal build data to analyze, edge data */
            inline void build(loader::save_data<MAX_LEN> &sdata, loader::analyze::analyzed_data<MAX_LEN> &adata, loader::analyze::edge_data &edata) {

                  /* Reset */
                  sdata = loader::save_data<MAX_LEN>{};
                  adata = loader::analyze::analyzed_data<MAX_LEN>{};
                  edata = loader::analyze::edge_data{};

                  if (this->insts.empty()) {
                        return;
                  }

                  const auto n = this->insts.size();

                  /* Block leaders */
                  boost::unordered_flat_set<address> leaders;
                  leaders.reserve(n);
                  leaders.insert(0u); /* Entry */

                  /* Label targets */
                  for (const auto &[idx, _] : this->label_idx_map) {
                        if (idx < n) {
                              leaders.insert(idx);
                        }
                  }

                  for (auto i = 0u; i < n; ++i) {

                        auto &ins = this->insts[i];

                        /* Outgoing this -> label  */
                        if (ins.jump_to_labels && !ins.jump_to_labels->empty()) {
                              for (const auto &[label, _] : *ins.jump_to_labels) {
                                    if (const auto lit = this->label_map.find(label); lit != this->label_map.end() && lit->second < n) {
                                          leaders.insert(lit->second);
                                    }
                              }
                              if (i + 1u < n) {
                                    leaders.insert(i + 1u);
                              }
                        }

                        /* Incoming src -> this */
                        if (ins.jump_to_realpc && !ins.jump_to_realpc->empty()) {
                              leaders.insert(i);
                              for (const auto &[src, _] : *ins.jump_to_realpc) {
                                    if (src + 1u < n) {
                                          leaders.insert(src + 1u);
                                    }
                              }
                        }
                  }

                  /* Cut instructions into blocks at leader boundaries and register them in sdata */
                  std::size_t running_id = 0u;
                  std::size_t start = 0u;

                  const auto flush_block = [&](const std::size_t from, const std::size_t to /* exclusive */) {
                        if (from >= to) {
                              return;
                        }
                        auto b = boost::make_shared<block<MAX_LEN>>();
                        b->id = running_id++;
                        b->time = std::time(nullptr);
                        b->fretranslated = false;
                        b->interpretation_id = this->insts[from].interp_mode;
                        b->insts.reserve(to - from);
                        for (auto j = from; j < to; ++j) {

                              auto &entry = this->insts[j].inst;
                              entry.fvalid = true;
                              b->insts.emplace_back(entry);
                        }
                        b->inst_count = b->insts.size();
                        b->loc = b->insts.front().inst.pc;
                        b->vcpu_n = 1u;
                        sdata.block_map[b->insts.front().inst.real_pc] = std::move(b);
                        return;
                  };
                  for (auto i = 1u; i < n; ++i) {

                        if (!leaders.contains(i)) {
                              continue;
                        }
                        flush_block(start, i);
                        start = i;
                  }
                  flush_block(start, n);                           /* trailing block */
                  loader::analyze::analyze(adata, sdata);          /* Analyze */
                  edata.reserve(sdata.block_map.size() * 3u + 1u); /* Emit edges into edata  */

                  /* Emit edge */
                  const auto emit_edge = [&](const edges::kind k, const address dst, const address src) {
                        switch (k) {
                              case edges::kind::signaled: {
                                    edata.emit<edges::kind::signaled>(dst, src);
                                    break;
                              }
                              case edges::kind::next: {
                                    edata.emit<edges::kind::next>(dst, src);
                                    break;
                              }
                              case edges::kind::next_punk: {
                                    edata.emit<edges::kind::next_punk>(dst, src);
                                    break;
                              }
                              default: {
                                    break;
                              }
                        }
                  };

                  /* Fall through from prev_real_pc */
                  for (auto i = 0u; i < n; ++i) {

                        const auto &bi = this->insts[i].inst.inst;
                        if (!this->insts[i].inst.inst.fvalid_prev_real_pc || bi.real_pc == bi.prev_real_pc) {
                              continue;
                        }
                        emit_edge(edges::kind::next, bi.real_pc, bi.prev_real_pc);
                  }

                  /* Explicit tracked emissions */
                  for (auto i = 0u; i < n; ++i) {

                        auto &ins = this->insts[i];
                        const auto self = ins.inst.inst.real_pc;

                        /* Outgoing: self -> label */
                        if (ins.jump_to_labels) {
                              for (const auto &[label, k] : *ins.jump_to_labels) {

                                    const auto lit = this->label_map.find(label);
                                    if (lit == this->label_map.end() || lit->second >= n) {
                                          continue;
                                    }
                                    emit_edge(k, lit->second, self);
                                    sdata.edge_map.insert(edges::jmp_loc(k, lit->second, self));
                              }
                        }

                        /* Incoming: src -> self */
                        if (ins.jump_to_realpc) {
                              for (const auto &[src, k] : *ins.jump_to_realpc) {

                                    if (src >= n) {
                                          continue;
                                    }
                                    emit_edge(k, self, src);
                                    sdata.edge_map.insert(edges::jmp_loc(k, self, src));
                              }
                        }
                  }
                  return;
            }

            address base = 0u; /* Base start address */
          private:
            boost::container::vector<instruction<MAX_LEN>> insts;      /* Instruction data */
            boost::unordered_flat_map<address, address> label_map;     /* Maps label -> next instruction index */
            boost::unordered_flat_map<address, address> label_idx_map; /* Idx of Label ->  Label name */
      };
} // namespace cpu_tracer::blocks::builder