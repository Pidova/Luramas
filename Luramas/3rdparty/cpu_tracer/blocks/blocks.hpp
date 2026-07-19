#pragma once
#include "../data/basic_info.hpp"
#include "../data/implements.hpp"
#include <boost/container/vector.hpp>
#include <boost/unordered/unordered_flat_map.hpp>
#include <boost/unordered/unordered_flat_set.hpp>
#include <lz4.h>

namespace cpu_tracer::blocks {

      namespace fs {

            /* Gets serialized saved type */
            inline save_type get_save_type(std::ifstream &ifs, const bool reset = false /* Resets IFS position ie func wont change IFS position */) {
                  if (!ifs.is_open()) {
                        return save_type::none;
                  }
                  const auto pos = ifs.tellg();
                  auto t = save_type::none;
                  io::read(ifs, t);
                  if (reset) {
                        ifs.seekg(pos);
                  }
                  return t;
            }

      } // namespace fs

      namespace edges {

            /* What kind of edge happened */
            enum class kind : std::uint8_t {
                  signaled,  /* Instruction signaled to execute this */
                  next,      /* Captured from instruction execution, jumped or fell to it */
                  next_punk, /* Captured from instruction execution, jumped or fell to it but previous is unknown */
                  count      /* Count of kinds */
            };

            /* Single directed edge */
            struct edge {

                  address dst_realpc = 0u;                                     /* Dest real PC */
                  std::array<bool, std::uint8_t(kind::count)> kinds = {false}; /* Valid or no? */

                  bool operator==(const edge &o) const noexcept {
                        return this->dst_realpc == o.dst_realpc;
                  }
            };
            struct edge_hash {
                  std::size_t operator()(const edge &j) const noexcept {
                        return j.dst_realpc;
                  }
            };

            /* 
                Edge map data (NOT FINAL, UNSAFE EDGES), because of potential context switching this serves as more unsafe edges but gives context.
                This gives previous Real PC of any instruction where the previous real PC set before this was executed is different. THIS IS NOT FINAL!!!
                Edges should also be analyzed through disassembly, interrupts, etc.
            */
            struct jmp_loc {

                  kind k = kind::next;     /* Kind */
                  address dst_realpc = 0u; /* Dest real PC */
                  address src_realpc = 0u; /* Real PC source */

                  bool operator==(const jmp_loc &o) const noexcept {
                        return this->dst_realpc == o.dst_realpc && this->src_realpc == o.src_realpc && this->k == o.k;
                  }
            };
            struct jmp_loc_hash {
                  std::size_t operator()(const jmp_loc &j) const noexcept {
                        std::size_t seed = j.src_realpc;
                        boost::hash_combine(seed, j.dst_realpc);
                        boost::hash_combine(seed, std::uint8_t(j.k));
                        return seed;
                  }
            };

#pragma pack(push, 1)
            struct packed_jmp_loc {
                  kind k;
                  address dst_realpc;
                  address src_realpc;
            };
#pragma pack(pop)

            /* Read/Write functions */
            inline bool read(boost::unordered_flat_set<jmp_loc, jmp_loc_hash> &dest, std::ifstream &ifs) {

                  if (!ifs.is_open()) {
                        return false;
                  }

                  const auto pos = ifs.tellg();
                  if (fs::get_save_type(ifs) != save_type::edge_map) {
                        ifs.seekg(pos);
                        return false;
                  }

                  std::size_t vector_size = 0u;
                  io::read(ifs, vector_size);
                  if (!vector_size) {
                        return true;
                  }

                  std::int32_t compressed_size = 0;
                  io::read(ifs, compressed_size);

                  std::vector<char> compressed_buf(compressed_size);
                  ifs.read(compressed_buf.data(), compressed_size);

                  const auto uncompressed_size = static_cast<std::int32_t>(vector_size * sizeof(packed_jmp_loc));
                  std::vector<packed_jmp_loc> staging_buf(vector_size);

                  const auto decompressed_bytes = LZ4_decompress_safe(compressed_buf.data(), reinterpret_cast<char *>(staging_buf.data()), compressed_size, uncompressed_size);
                  if (decompressed_bytes != uncompressed_size) {
                        ifs.clear();
                        ifs.seekg(pos);
                        return false;
                  }

                  dest.reserve(dest.size() + vector_size);
                  for (const auto &packed : staging_buf) {
                        dest.insert({packed.k, packed.dst_realpc, packed.src_realpc});
                  }
                  return true;
            }
            inline void write(const boost::unordered_flat_set<jmp_loc, jmp_loc_hash> &src, std::ofstream &ofs) {

                  if (!ofs.is_open() || src.empty()) {
                        return;
                  }

                  const auto vector_size = src.size();
                  io::write(ofs, save_type::edge_map, vector_size);
                  std::vector<packed_jmp_loc> staging_buf;
                  staging_buf.reserve(vector_size);
                  for (const auto &i : src) {
                        staging_buf.push_back({i.k, i.dst_realpc, i.src_realpc});
                  }

                  const auto uncompressed_size = static_cast<std::int32_t>(staging_buf.size() * sizeof(packed_jmp_loc));
                  const auto max_compressed_size = LZ4_compressBound(uncompressed_size);

                  std::vector<char> compressed_buf(max_compressed_size);
                  const auto compressed_size = LZ4_compress_fast(reinterpret_cast<const char *>(staging_buf.data()), compressed_buf.data(), uncompressed_size, max_compressed_size, 3);
                  io::write(ofs, compressed_size);
                  ofs.write(compressed_buf.data(), compressed_size);
                  return;
            }
      } // namespace edges

      namespace interrupts {

            enum class type : std::uint8_t {
                  EXCEPTION, /* Normal exception */
                  INTERUPT,  /* Normal interupt */
                  ETC        /* Misc interupt */
            };
            struct interrupt {
                  type k = type::EXCEPTION;              /* Type of interrupt */
                  address dst = 0u;                      /* Destination Vaddr PC */
                  address src = 0u;                      /* Source Vaddr PC */
                  address dst_real = 0u;                 /* Destination real PC */
                  std::size_t curr_global_block_id = 0u; /* Current global block ID to map to the instruction where it came from  */
                  std::uint8_t vcpu = 0u;                /* VCPU */
            };

            /* Read/Write functions */
            inline void read(std::ifstream &ifs, interrupt &in) {
                  io::read(ifs, in.k, in.dst, in.src, in.dst_real, in.curr_global_block_id, in.vcpu);
                  return;
            }
            inline bool read(std::ifstream &ifs, boost::container::vector<interrupt> &v) {

                  if (!ifs.is_open()) {
                        return false;
                  }
                  if (const auto pos = ifs.tellg(); fs::get_save_type(ifs) != save_type::interrupts) {
                        ifs.seekg(pos);
                        return false;
                  }
                  std::size_t size = 0u;
                  io::read(ifs, size);
                  const auto vsize = v.size();
                  v.resize(size + vsize);
                  for (auto i = vsize; i < size + vsize; ++i) {
                        read(ifs, v[i]);
                  }
                  return true;
            }
            inline void write(std::ofstream &ofs, const interrupt &in) {
                  io::write(ofs, in.k, in.dst, in.src, in.dst_real, in.curr_global_block_id, in.vcpu);
                  return;
            }
            inline void write(std::ofstream &ofs, const boost::container::vector<interrupt> &v) {

                  if (!ofs.is_open() || v.empty()) {
                        return;
                  }
                  io::write(ofs, save_type::interrupts, v.size());
                  for (const auto &i : v) {
                        write(ofs, i);
                  }
                  return;
            }
      } // namespace interrupts

      namespace vcpu {

            /* When a VCPU changes state it will capture the state of all active other vcpus */
            enum class state : std::uint8_t {
                  PAUSED, /* VCPU Paused */
                  RESUME  /* VCPU Resumed */
            };
            struct captured_block_state {
                  flag fhas_recent_realpc = false;       /* Real pc exists? */
                  state k = state::PAUSED;               /* State put in */
                  std::uint8_t vcpu = 0u;                /* Related VCPU */
                  address recent_realpc = 0u;            /* Most recent real PC of VCPU */
                  std::size_t curr_global_block_id = 0u; /* Current global block ID to map to the instruction where it came from  */
            };

            /* Read/Write functions */
            inline void read(std::ifstream &ifs, captured_block_state &s) {
                  io::read(ifs, s.fhas_recent_realpc, s.k, s.vcpu, s.recent_realpc, s.curr_global_block_id);
                  return;
            }
            inline bool read(std::ifstream &ifs, boost::container::vector<captured_block_state> &v) {

                  if (!ifs.is_open()) {
                        return false;
                  }
                  const auto pos = ifs.tellg();
                  if (fs::get_save_type(ifs) != save_type::vcpu_states) {
                        ifs.seekg(pos);
                        return false;
                  }
                  std::size_t size = 0u;
                  io::read(ifs, size);
                  const auto vsize = v.size();
                  v.resize(size + vsize);
                  for (auto i = vsize; i < size + vsize; ++i) {
                        read(ifs, v[i]);
                  }
                  return true;
            }
            inline void write(std::ofstream &ofs, const captured_block_state &s) {
                  io::write(ofs, s.fhas_recent_realpc, s.k, s.vcpu, s.recent_realpc, s.curr_global_block_id);
                  return;
            }
            inline void write(std::ofstream &ofs, const boost::container::vector<captured_block_state> &s) {

                  if (!ofs.is_open() || s.empty()) {
                        return;
                  }
                  io::write(ofs, save_type::vcpu_states, static_cast<std::size_t>(s.size()));
                  for (const auto &i : s) {
                        write(ofs, i);
                  }
                  return;
            }
      } // namespace vcpu

      namespace mmio {

            /* Read or Write? */
            enum class rw : std::uint8_t {
                  read, /* Read MMIO  */
                  write /* Write to MMIO */
            };

            /* MMIO/Memory specific data  */
            struct data {

                  address dest = 0u;       /* Destination address */
                  address src_realpc = 0u; /* Real PC inst of source inst */
                  bool operator==(const data &o) const noexcept {
                        return this->dest == o.dest && this->src_realpc == o.src_realpc;
                  }
            };
            struct hash {
                  std::size_t operator()(const data &j) const noexcept {
                        std::size_t seed = j.dest;
                        boost::hash_combine(seed, j.src_realpc);
                        return seed;
                  }
            };

            /* Read/Writes */
            inline void read(std::ifstream &ifs, data &d) {
                  io::read(ifs, d.dest, d.src_realpc);
                  return;
            }
            inline bool read(std::ifstream &ifs, boost::container::vector<data> &v) {

                  if (!ifs.is_open()) {
                        return false;
                  }
                  if (const auto pos = ifs.tellg(); fs::get_save_type(ifs) != save_type::MMIO) {
                        ifs.seekg(pos);
                        return false;
                  }
                  std::size_t size = 0u;
                  io::read(ifs, size);
                  const auto vsize = v.size();
                  v.resize(size + vsize);
                  for (auto i = vsize; i < size + vsize; ++i) {
                        read(ifs, v[i]);
                  }
                  return true;
            }
            inline void write(std::ofstream &ofs, const data &d) {
                  io::write(ofs, d.dest, d.src_realpc);
                  return;
            }
            inline void write(std::ofstream &ofs, const boost::container::vector<data> &v) {

                  if (!ofs.is_open() || v.empty()) {
                        return;
                  }
                  io::write(ofs, save_type::MMIO, v.size());
                  for (const auto &i : v) {
                        write(ofs, i);
                  }
                  return;
            }
      } // namespace mmio

      /* Per-instruction data */
      template <std::uint8_t MAX_LEN>
      struct inst_data {

            flag_storage flags = 0u;        /* Flags to disassemble with inst_data_flags */
            flag fvalid = false;            /* See if instruction has been executed, not included in flags for speed? */
            basic_info::inst<MAX_LEN> inst; /* Instruction data */
#ifdef QEMU_PLUGIN_DEBUG
            char DEBUG_DISM[120u]; /* Debug disassembly */
#endif
      };

      /* Translation block */
      template <std::uint8_t MAX_LEN>
      struct block {

            time_t time = 0u;                                                                /* Time Block was translated */
            std::size_t id = 0u;                                                             /* Block ID relative to other blocks */
            flag fretranslated = false;                                                      /* Has block been retranslated? */
            boost::container::vector<inst_data<MAX_LEN>> insts;                              /* Instruction data translated on tb exec */
            address loc = 0u;                                                                /* Start virtual pc  */
            std::size_t inst_count = 0u;                                                     /* Instruction count in block */
            archs::interpretation_mode interpretation_id = archs::interpretation_mode::none; /* What is it get interpreted as? */
            std::uint8_t vcpu_n = 0u;                                                        /* Count of vcpus */

            /* Read/Write functions */
            inline bool read(std::ifstream &ifs) {

                  if (!ifs.is_open()) {
                        return false;
                  }
                  if (const auto pos = ifs.tellg(); fs::get_save_type(ifs) != save_type::block) {
                        ifs.seekg(pos);
                        return false;
                  }
                  std::size_t size = 0u;
                  io::read(ifs, this->time, this->id, this->fretranslated, this->loc, this->inst_count, this->interpretation_id, this->vcpu_n, size);
                  this->insts.resize(size);
                  for (auto i = 0u; i < size; ++i) {
                        auto &entry = this->insts[i];
                        io::read(ifs, entry.flags, entry.fvalid);
                        entry.inst.read(ifs);
                  }
                  return true;
            }
            inline void write(std::ofstream &ofs) const {

                  if (!ofs.is_open()) {
                        return;
                  }
                  io::write(ofs, save_type::block, this->time, this->id, this->fretranslated, this->loc, this->inst_count, this->interpretation_id, this->vcpu_n, static_cast<std::size_t>(this->insts.size()));
                  for (const auto &i : this->insts) {
                        io::write(ofs, i.flags, i.fvalid);
                        i.inst.write(ofs);
                  }
                  return;
            }
      };

} // namespace cpu_tracer::blocks