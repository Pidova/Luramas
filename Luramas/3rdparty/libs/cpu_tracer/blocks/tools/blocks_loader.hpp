#pragma once
#include "blocks_tools.hpp"
#include <boost/smart_ptr.hpp>
#include <boost/sort/pdqsort/pdqsort.hpp>
#include <ranges>

namespace cpu_tracer::blocks::loader {

      /* Block pointer */
      template <std::uint8_t MAX_LEN>
      using block_ptr = boost::shared_ptr<block<MAX_LEN>>;

      /* Save data loaded from file */
      template <std::uint8_t MAX_LEN>
      struct save_data {
            boost::unordered_flat_set<edges::jmp_loc, edges::jmp_loc_hash> edge_map; /* Edge Map */
            boost::unordered_flat_map<address, block_ptr<MAX_LEN>> block_map;        /* {realpc -> Node} map */
            boost::container::vector<interrupts::interrupt> interrupts;              /* VCPU interrupts */
            boost::container::vector<vcpu::captured_block_state> block_states;       /* Block states */
            boost::container::vector<mmio::data> mmio;                               /* MMIO */
      };

      /* Map of edges */
      using edge_map = boost::unordered_flat_map<address, boost::unordered_flat_set<edges::edge, edges::edge_hash>>;

      /* Load file steam into data buffer */
      template <std::uint8_t MAX_LEN>
      inline bool load(save_data<MAX_LEN> &buf, std::ifstream &ifs) {

            if (!ifs) {
                  return false;
            }
            while (ifs.good()) {

                  switch (fs::get_save_type(ifs, true)) {
                        case save_type::block: {
                              auto b = boost::make_shared<block<MAX_LEN>>();
                              b->read(ifs);
                              const auto real_pc = b->insts.front().inst.real_pc;
                              buf.block_map[real_pc] = std::move(b);
                              break;
                        }
                        case save_type::edge_map: {
                              edges::read(buf.edge_map, ifs);
                              break;
                        }
                        case save_type::vcpu_states: {
                              vcpu::read(ifs, buf.block_states);
                              break;
                        }
                        case save_type::interrupts: {
                              interrupts::read(ifs, buf.interrupts);
                              break;
                        }
                        case save_type::MMIO: {
                              mmio::read(ifs, buf.mmio);
                              break;
                        }
                        case save_type::none: {
                              ifs.ignore(sizeof(save_type)); /* Step */
                              break;
                        }
                        default: {
                              return false;
                        }
                  }
            }
            return true;
      }

      namespace analyze {

            /* Basic analyzed data */
            template <std::uint8_t MAX_LEN>
            struct analyzed_data {
                  std::size_t biggest_block_id = 0u;                                                                                          /* Biggest block ID */
                  boost::container::vector<block_ptr<MAX_LEN>> sorted_blocks_global_id;                                                       /* Sorted blocks by global ID */
                  boost::unordered_flat_map<address, block_ptr<MAX_LEN>> real_pc_map;                                                         /* Real PC -> Blocks */
                  boost::unordered_flat_map<address, boost::container::vector<std::pair<block_ptr<MAX_LEN>, inst_data<MAX_LEN> *>>> inst_map; /* Instruction [VAddr -> { Inst PTR }] */
            };

            /* Analyze data */
            template <std::uint8_t MAX_LEN>
            inline void analyze(analyzed_data<MAX_LEN> &buf, save_data<MAX_LEN> &data) {

                  std::size_t real_pc_reserve_amt = 0u;
                  for (auto &[_, b] : data.block_map) {

                        if (b->id > buf.biggest_block_id) {
                              buf.biggest_block_id = b->id;
                        }
                        real_pc_reserve_amt += b->insts.size();
                        for (auto &i : b->insts) {
                              buf.inst_map[i.inst.pc].emplace_back(std::make_pair(b, &i));
                        }
                  }

                  /* sorted_blocks_global_id */
                  {
                        buf.sorted_blocks_global_id.reserve(data.block_map.size());
                        std::ranges::copy(data.block_map | std::views::values, std::back_inserter(buf.sorted_blocks_global_id));
                        boost::sort::pdqsort(buf.sorted_blocks_global_id.begin(), buf.sorted_blocks_global_id.end(), [](const auto &a, const auto &b) { return a->id < b->id; });
                  }

                  /* Interrupts sort by block ID */
                  boost::sort::pdqsort(data.interrupts.begin(), data.interrupts.end(), [](const auto &a, const auto &b) { return a.curr_global_block_id < b.curr_global_block_id; });

                  /* Block States sort by block ID */
                  boost::sort::pdqsort(data.block_states.begin(), data.block_states.end(), [](const auto &a, const auto &b) { return a.curr_global_block_id < b.curr_global_block_id; });

                  /* Real PC to block map */
                  buf.real_pc_map.reserve(real_pc_reserve_amt);
                  for (const auto &[addr, b] : data.block_map) {
                        for (const auto &i : b->insts) {
                              buf.real_pc_map[i.inst.real_pc] = b;
                        }
                  }
                  return;
            }

            /* Edge data map */
            struct edge_data {

                  edge_map successors;  /* Src -> Dest */
                  edge_map predecessor; /* Dest -> Src */

                  /* Reserve amount */
                  inline void reserve(const std::size_t n) {
                        this->successors.reserve(n);
                        this->predecessor.reserve(n);
                        return;
                  }

                  /* Emits edge */
                  template <edges::kind k>
                  inline void emit(const address dest_real_pc, const address src_real_pc) {

                        /* Successors */
                        {
                              auto &succs = this->successors[src_real_pc];
                              edges::edge e;
                              e.dst_realpc = dest_real_pc;
                              auto [it, inserted] = succs.insert(e);
                              const_cast<edges::edge &>(*it).kinds[std::uint8_t(k)] = true;
                        }
                        /* Predecessors */
                        {
                              auto &succs = this->predecessor[dest_real_pc];
                              edges::edge e;
                              e.dst_realpc = src_real_pc;
                              auto [it, inserted] = succs.insert(e);
                              const_cast<edges::edge &>(*it).kinds[std::uint8_t(k)] = true;
                        }
                        return;
                  }

                  /* Generate a label given address */
                  inline static std::string gen_label(const address &addr) {
                        return "LABEL_" + std::to_string(addr);
                  }
            };

            /* Analyze edges */
            template <std::uint8_t MAX_LEN>
            inline void analyze(edge_data &buf, const save_data<MAX_LEN> &data, analyzed_data<MAX_LEN> &cd) {

                  boost::unordered_flat_set<address> vaddr_pending;             /* Pending Vaddr detected with Interrupts to get real PCs */
                  boost::unordered_flat_map<address, address> vaddr_to_real_pc; /* Vaddr to real PC map */
                  vaddr_to_real_pc.reserve(cd.sorted_blocks_global_id.size() * 5u);
                  buf.reserve(cd.sorted_blocks_global_id.size() * 3u);

                  /* Interrupts edges*/
                  std::size_t ints_idx = 0u;

                  /* Edge Map */
                  for (const auto &edge : data.edge_map) {
                        buf.emit<edges::kind::next>(edge.dst_realpc, edge.src_realpc);
                  }
                  for (auto &b : cd.sorted_blocks_global_id) {

                        std::optional<address> prev_real = std::nullopt;
                        const auto bglobal_id = b->id;
                        for (auto &i : b->insts) {
                              if (!i.fvalid) {
                                    continue;
                              }
                              if (prev_real && *prev_real == i.inst.prev_real_pc) {
                                    prev_real = i.inst.real_pc;
                                    continue;
                              }
                              prev_real = i.inst.real_pc;
                              vaddr_to_real_pc[i.inst.pc] = i.inst.real_pc;
                              buf.emit<edges::kind::next>(i.inst.real_pc, i.inst.prev_real_pc);
                        }

                        /* Add pending */
                        if (!vaddr_pending.empty()) {
                              for (auto it = vaddr_pending.begin(); it != vaddr_pending.end();) {

                                    if (auto lookup = vaddr_to_real_pc.find(*it); lookup != vaddr_to_real_pc.end()) {
                                          buf.emit<edges::kind::signaled>(lookup->second, lookup->second);
                                          it = vaddr_pending.erase(it);
                                    } else {
                                          ++it;
                                    }
                              }
                        }

                        /* INTs */
                        if (ints_idx < data.interrupts.size()) {

                              auto intr = data.interrupts[ints_idx];
                              while (intr.curr_global_block_id <= bglobal_id) {

                                    if (const auto it = vaddr_to_real_pc.find(intr.src); it != vaddr_to_real_pc.end()) {
                                          buf.emit<edges::kind::signaled>(intr.dst_real, vaddr_to_real_pc[intr.src]);
                                    } else {
                                          vaddr_pending.insert(intr.src);
                                    }
                                    if (++ints_idx >= data.interrupts.size()) {
                                          break;
                                    }
                                    intr = data.interrupts[ints_idx];
                              }
                        }
                  }
                  return;
            }
      } // namespace analyze

      namespace tools {

            /* Split blocks and rejoins them if they do not have a direct map */
            template <std::uint8_t MAX_LEN>
            inline void fix_blocks(const analyze::edge_data &edges, analyze::analyzed_data<MAX_LEN> &adata, save_data<MAX_LEN> &sdata) {

                  for (const auto &[addr, _] : edges.successors) {

                        /* See if realpc address is in block map */
                        const auto rpc_it = adata.real_pc_map.find(addr);
                        if (rpc_it == adata.real_pc_map.end()) {
                              continue;
                        }

                        /* Get index of address in insts */
                        const auto idx = blocks::tools::get_index(*rpc_it->second, addr);
                        if (!idx) {
                              continue;
                        }

                        /* Split block to create new block */
                        const auto b = blocks::tools::split_block(*rpc_it->second, *idx, ++adata.biggest_block_id);
                        if (!b) {
                              continue;
                        }

                        /* Register new block data */
                        const auto new_block = boost::make_shared<block<MAX_LEN>>(*b);
                        for (const auto &i : new_block->insts) {
                              adata.real_pc_map[i.inst.real_pc] = new_block;
                        }
                        if (!new_block->insts.empty()) {
                              sdata.block_map[new_block->insts.front().inst.real_pc] = new_block;
                        }
                  }
                  return;
            }
      } // namespace tools
} // namespace cpu_tracer::blocks::loader