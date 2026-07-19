#include <boost/icl/interval.hpp>
#include <boost/icl/interval_map.hpp>
#include <cinttypes>
#include <luramas/profile/profile.hpp>

namespace luramas::profile {

      /* Pack/Unpack */
      template <typename... T>
      constexpr std::uint8_t pack(const T... bools) {
            constexpr auto count = sizeof...(bools);
            static_assert(count <= 8u, "Can only pack till 8 bits");
            std::size_t i = 0u;
            std::uint8_t result = 0u;
            ((result |= (static_cast<bool>(bools) ? 1u : 0u) << i++, void()), ...);
            return result;
      }
      template <std::size_t N, std::size_t... Is>
      inline constexpr auto unpack_i(const std::uint8_t n, std::index_sequence<Is...>) {
            return std::make_tuple(static_cast<bool>((n >> Is) & 1)...);
      }
      template <std::size_t N>
      constexpr auto unpack(const std::uint8_t n) {
            static_assert(N <= 8, "Can only unpack up to 8 bits");
            return unpack_i<N>(n, std::make_index_sequence<N>{});
      }

      /* Inst */
      void inst::emit_jump(const address loc) {
            this->k = inst_kind::jump_to;
            this->loc = loc;
            return;
      }
      void inst::emit_return(const address loc) {
            this->k = inst_kind::return_to;
            this->loc = loc;
            return;
      }
      void inst::emit_call(const address loc) {
            this->k = inst_kind::call_to;
            this->loc = loc;
            return;
      }
      void inst::emit_memset(const std::uintptr_t loc, const std::uint8_t memset_bytes) {
            this->k = inst_kind::memset;
            this->loc = loc;
            this->memset_bytes = memset_bytes;
            return;
      }
      bool inst::cmp(const inst_bytes &other) const {
            if (this->bytes.size() != other.size()) {
                  return false;
            }
            for (auto i = 0u; i < this->bytes.size(); ++i) {
                  if (this->bytes[i] != other[i]) {
                        return false;
                  }
            }
            return true;
      }
      bool inst::cmp(const std::vector<std::uint8_t> &other, const std::size_t offset) const {
            if (offset >= other.size() || offset + this->bytes.size() > other.size() || !this->bytes.size()) {
                  return false;
            }
            for (auto i = 0u; i < this->bytes.size(); ++i) {
                  if (this->bytes[i] != other[offset + i]) {
                        return false;
                  }
            }
            return true;
      }
      bool inst::empty() const {
            return this->bytes.empty();
      }
      void inst::clear() {
            *this = inst();
            return;
      }
      bool inst::cmp(const inst &other) const {

            if (std::tie(this->k, this->interp_as, this->loc, this->lid, this->mid) !=
                std::tie(other.k, other.interp_as, other.loc, other.lid, other.mid)) {
                  return false;
            }
            if (this->k == inst_kind::memset && this->memset_bytes != other.memset_bytes) {
                  return false;
            }
            return this->cmp(other.bytes);
      }
      bool inst::operator==(const inst &other) const {
            return this->cmp(other);
      }
      bool inst::operator!=(const inst &other) const {
            return !this->cmp(other);
      }
      void inst::write(std::ofstream &ofs) const {

            const auto header_flags = pack(this->last, this->marked, this->conditional, this->entry, this->inlane);
            ofs.write(reinterpret_cast<const char *>(&header_flags), sizeof(header_flags));
            ofs.write(reinterpret_cast<const char *>(&this->interp_as), sizeof(this->interp_as));
            ofs.write(reinterpret_cast<const char *>(&this->mid), sizeof(this->mid));
            ofs.write(reinterpret_cast<const char *>(&this->pc), sizeof(this->pc));
            ofs.write(reinterpret_cast<const char *>(&this->real_pc), sizeof(this->real_pc));

            std::uint8_t flags = 0u;
            if (this->k == inst_kind::memset) {
                  flags |= 1;
            }
            if (this->k == inst_kind::jump_to) {
                  flags |= 2;
            }
            if (this->k == inst_kind::return_to) {
                  flags |= 4;
            }
            if (this->k == inst_kind::call_to) {
                  flags |= 8;
            }
            ofs.write(reinterpret_cast<const char *>(&flags), sizeof(flags));

            const std::uint8_t byte_len = this->bytes.size();
            ofs.write(reinterpret_cast<const char *>(&byte_len), sizeof(byte_len));
            ofs.write(reinterpret_cast<const char *>(&*this->bytes.begin()), static_cast<std::streamsize>(std::distance(this->bytes.begin(), this->bytes.end())));

            switch (this->k) {
                  case inst_kind::memset: {
                        ofs.write(reinterpret_cast<const char *>(&this->memset_bytes), sizeof(this->memset_bytes));
                        ofs.write(reinterpret_cast<const char *>(&this->loc), sizeof(this->loc));
                        break;
                  }
                  case inst_kind::jump_to:
                  case inst_kind::return_to:
                  case inst_kind::call_to: {
                        ofs.write(reinterpret_cast<const char *>(&this->lid), sizeof(this->lid));
                        ofs.write(reinterpret_cast<const char *>(&this->loc), sizeof(this->loc));
                        break;
                  }
                  default: {
                        break;
                  }
            }
            return;
      }
      void inst::read(std::ifstream &ifs) {

            std::uint8_t packed_headers = 0u;
            ifs.read(reinterpret_cast<char *>(&packed_headers), sizeof(packed_headers));
            std::tie(this->last, this->marked, this->conditional, this->entry, this->inlane) = unpack<5u>(packed_headers);

            ifs.read(reinterpret_cast<char *>(&this->interp_as), sizeof(this->interp_as));
            ifs.read(reinterpret_cast<char *>(&this->mid), sizeof(this->mid));
            ifs.read(reinterpret_cast<char *>(&this->pc), sizeof(this->pc));
            ifs.read(reinterpret_cast<char *>(&this->real_pc), sizeof(this->real_pc));

            std::uint8_t flags = 0u;
            ifs.read(reinterpret_cast<char *>(&flags), sizeof(flags));

            if (flags & 1) {
                  this->k = inst_kind::memset;
            } else if (flags & 2) {
                  this->k = inst_kind::jump_to;
            } else if (flags & 4) {
                  this->k = inst_kind::return_to;
            } else if (flags & 8) {
                  this->k = inst_kind::call_to;
            } else {
                  this->k = inst_kind::normal;
            }

            std::uint8_t len = 0u;
            ifs.read(reinterpret_cast<char *>(&len), sizeof(len));

            for (auto i = 0u; i < len; ++i) {
                  std::uint8_t b = 0u;
                  ifs.read(reinterpret_cast<char *>(&b), sizeof(b));
                  this->bytes.push_back(b);
            }

            switch (this->k) {
                  case inst_kind::memset: {
                        ifs.read(reinterpret_cast<char *>(&this->memset_bytes), sizeof(this->memset_bytes));
                        ifs.read(reinterpret_cast<char *>(&this->loc), sizeof(this->loc));
                        break;
                  }
                  case inst_kind::jump_to:
                  case inst_kind::return_to:
                  case inst_kind::call_to: {
                        ifs.read(reinterpret_cast<char *>(&this->lid), sizeof(this->lid));
                        ifs.read(reinterpret_cast<char *>(&this->loc), sizeof(this->loc));
                        break;
                  }
                  default: {
                        break;
                  }
            }
            return;
      }
      std::string inst::str(const bool metadata_only) const {

            std::string result("");
            if (!metadata_only) {
                  result += std::format("0x{:X}", this->real_pc) + " ";
                  for (auto i = 0u; i < this->bytes.size(); ++i) {

                        result += std::format("{:02X}", this->bytes[i]);
                        if ((i + 1u) != this->bytes.size()) {
                              result += ", ";
                        }
                  }
                  switch (this->k) {
                        case inst_kind::call_to: {
                              result += " (call_to): ";
                              break;
                        }
                        case inst_kind::memset: {
                              result += " (memset): ";
                              break;
                        }
                        case inst_kind::jump_to: {
                              result += " (jump_to): ";
                              break;
                        }
                        case inst_kind::return_to: {
                              result += " (return_to): ";
                              break;
                        }
                        default: {
                              break;
                        }
                  }
            }
            switch (this->k) {
                  case inst_kind::call_to:
                  case inst_kind::memset:
                  case inst_kind::jump_to:
                  case inst_kind::return_to: {
                        result += std::format("0x{:X}", this->loc);
                        break;
                  }
                  default: {
                        break;
                  }
            }
            return result;
      }
      bool inst::goes_to() const {
            return this->k == inst_kind::jump_to || this->k == inst_kind::return_to || this->k == inst_kind::call_to;
      }
      std::uint8_t inst::len() const {
            return this->bytes.size();
      }
      bool inst::is_terminal() const {
            return (this->k == inst_kind::jump_to && !this->conditional) || this->k == inst_kind::return_to;
      }

      /* Real inst */
      std::optional<std::reference_wrapper<inst>> real_inst::operator[](const std::size_t idx) {
            if (!idx) {
                  return std::ref(this->first);
            }
            if (this->discrepancies && idx - 1u < this->discrepancies->size()) {
                  return std::ref(this->discrepancies->at(idx - 1u));
            }
            return std::nullopt;
      }
      std::optional<std::reference_wrapper<const inst>> real_inst::operator[](const std::size_t idx) const {
            if (!idx) {
                  return std::cref(this->first);
            }
            if (this->discrepancies && idx - 1u < this->discrepancies->size()) {
                  return std::cref(this->discrepancies->at(idx - 1u));
            }
            return std::nullopt;
      }
      std::vector<inst> real_inst::accumulate() const {
            std::vector<inst> result;
            if (this->discrepancies.has_value()) {
                  result = *this->discrepancies;
            }
            result.emplace_back(this->first);
            return result;
      }
      std::vector<inst> real_inst::accumulate(const inst_bytes &b) const {
            std::vector<inst> result;
            if (this->discrepancies.has_value()) {
                  for (const auto &i : *this->discrepancies) {
                        if (i.cmp(b)) {
                              result.emplace_back(i);
                        }
                  }
            }
            if (this->first.cmp(b)) {
                  result.emplace_back(this->first);
            }
            return result;
      }
      std::vector<module_id> real_inst::accumulate_out_of_lane_discrepancies() const {

            std::vector<module_id> result;
            if (this->discrepancies) {
                  for (const auto &i : *this->discrepancies) {
                        if (i.inlane) {
                              continue;
                        }
                        result.emplace_back(*i.did);
                  }
            }
            return result;
      }
      bool real_inst::safe_code() const {

            if (this->discrepancies.has_value()) {
                  for (const auto &i : *this->discrepancies) {
                        if (!i.cmp(this->first.bytes)) {
                              return false;
                        }
                  }
            }
            return true;
      }
      addresses real_inst::get_len() const {

            const auto addr = this->first.real_pc;
            addresses result({addr + first.len()});
            if (this->discrepancies.has_value()) {
                  for (const auto &i : *this->discrepancies) {
                        result.insert(addr + i.len());
                  }
            }
            return result;
      }
      bool real_inst::goes_to() const {
            if (this->first.goes_to()) {
                  return true;
            }
            if (this->discrepancies.has_value()) {
                  for (const auto &i : *this->discrepancies) {
                        if (i.goes_to()) {
                              return true;
                        }
                  }
            }
            return false;
      }
      void real_inst::get_gotos(addresses &result) const {

            if (this->first.goes_to()) {
                  result.insert(this->first.loc);
            }
            if (this->discrepancies.has_value()) {
                  for (const auto &i : *this->discrepancies) {
                        if (i.goes_to()) {
                              result.insert(i.loc);
                        }
                  }
            }
            return;
      }
      addresses real_inst::get_gotos() const {

            addresses result;
            this->get_gotos(result);
            return result;
      }
      address real_inst::loc() const {
            return this->first.loc;
      }
      std::optional<module_id> real_inst::compare(const std::vector<std::uint8_t> &bytes, const std::size_t offset) const {

            if (offset >= bytes.size()) {
                  return std::nullopt;
            }
            if (this->first.cmp(bytes, offset)) {
                  return 0u;
            }
            if (this->discrepancies) {
                  for (auto i = 0u; i < (*this->discrepancies).size(); ++i) {
                        if ((*this->discrepancies)[i].cmp(bytes, offset)) {
                              return i + 1u;
                        }
                  }
            }
            return std::nullopt;
      }

      /* inst_result */
      bool inst_result::reachable(const address loc) const {
            return this->map.contains(loc);
      }

      namespace builder {

            inst manager::construct(const inst_bytes &bytes) {

                  inst result;
                  result.mid = this->id;
                  result.pc = this->next;
                  result.real_pc = this->data.map.size();
                  result.bytes = bytes;
                  result.entry = 0u;
                  this->next += result.len();
                  return result;
            }
            address manager::emit(const inst_bytes &bytes) {

                  const auto i = this->construct(bytes);
                  this->data.map[i.pc] = real_inst(i);
                  this->data.entries.insert(i.entry);
                  return i.pc;
            }
            address manager::emit(const inst_bytes &bytes, const bool entry) {

                  auto i = this->construct(bytes);
                  i.entry = entry;
                  this->data.map[i.pc] = real_inst(i);
                  this->data.entries.insert(i.entry);
                  return i.pc;
            }
            address manager::emit(const inst_bytes &bytes, const address goto_loc, const inst_kind k, const bool conditional) {

                  auto i = construct(bytes);
                  i.k = k;
                  i.loc = goto_loc;
                  i.conditional = conditional;
                  i.lid = this->id;
                  this->data.map[i.pc] = real_inst(i);
                  this->data.entries.insert(i.entry);
                  return i.pc;
            }
            address manager::emit(const inst_bytes &bytes, const inst_kind k, const address label, const bool conditional) {

                  if (const auto it = this->labels.find(label); it != this->labels.end() && it->second.finalized) {
                        return this->emit(bytes, it->second.loc, k, conditional);
                  }
                  const auto addr = this->emit(bytes, 0u, k, conditional);
                  this->labels[label].pending.emplace_back(std::make_pair(addr, std::nullopt));
                  return addr;
            }
            address manager::emit(const address existing, const inst_kind k, const address label) {

                  const auto dit = this->data.map.find(existing);
                  if (dit == this->data.map.end()) {
                        return 0u;
                  }
                  if (!dit->second.discrepancies) {
                        dit->second.discrepancies.emplace();
                  }
                  auto &disc = *dit->second.discrepancies;
                  auto inst = this->construct(dit->second.first.bytes);
                  inst.k = k;
                  inst.lid = this->id;
                  if (const auto it = this->labels.find(label); it != this->labels.end() && it->second.finalized) {
                        inst.loc = it->second.loc;
                        (*dit->second.discrepancies).emplace_back(inst);
                        return existing;
                  }
                  this->labels[label].pending.emplace_back(std::make_pair(existing, disc.size()));
                  disc.emplace_back(inst);
                  return existing;
            }
            address manager::emit_label(const address label) {

                  auto &l = this->labels[label];
                  l.finalized = true;
                  for (const auto &[addr, discrepancy] : l.pending) {
                        auto &p = this->data.map[addr];
                        if (discrepancy) {
                              if (p.discrepancies && *discrepancy < (*p.discrepancies).size()) {
                                    (*p.discrepancies)[*discrepancy].loc = this->next;
                              }
                        } else {
                              p.first.loc = this->next;
                        }
                  }
                  l.loc = this->next;
                  return l.loc;
            }
            address manager::emit(const address existing, const address label, const inst_kind k) {

                  auto &p = this->data.map[existing];
                  if (!p.discrepancies) {
                        p.discrepancies = std::vector<inst>();
                  }

                  auto copy = p.first;
                  copy.k = k;
                  copy.lid = this->id;
                  if (const auto it = this->labels.find(label); it != this->labels.end() && it->second.finalized) {
                        copy.loc = it->second.loc;
                        (*p.discrepancies).emplace_back(copy);
                        return existing;
                  }
                  (*p.discrepancies).emplace_back(copy);
                  this->labels[label].pending.emplace_back(std::make_pair(existing, (*p.discrepancies).size() - 1u));
                  return existing;
            }
            void manager::extract(boost::unordered_flat_map<module_id, inst_result> &buffer) const {
                  buffer[this->id] = this->data;
                  return;
            }
            void print_inst(const inst &i, const char *indent = "") {

                  std::printf("%s0x%" PRIxPTR " ", indent, i.pc);
                  for (const auto b : i.bytes) {
                        std::printf("%02x ", b);
                  }
                  switch (i.k) {
                        case inst_kind::jump_to: {
                              std::printf("jumps to 0x%" PRIxPTR, i.loc);
                              break;
                        }
                        case inst_kind::call_to: {
                              std::printf("calls to 0x%" PRIxPTR, i.loc);
                              break;
                        }
                        case inst_kind::return_to: {
                              std::printf("return to 0x%" PRIxPTR, i.loc);
                              break;
                        }
                        case inst_kind::memset: {
                              std::printf("sets 0x%" PRIxPTR " bytes %d", i.loc, i.memset_bytes);
                              break;
                        }
                        default: {
                              break;
                        }
                  }
                  return;
            }

            void manager::dump() const {

                  address on = 0;
                  auto it = data.map.find(on);
                  while (it != data.map.end()) {

                        const auto &entry = it->second;
                        print_inst(entry.first);
                        if (entry.discrepancies) {
                              for (auto const &d : *entry.discrepancies) {
                                    std::printf("\n");
                                    print_inst(d, "  ");
                              }
                        }
                        std::printf("\n");
                        on += entry.first.len();
                        it = data.map.find(on);
                  }
                  return;
            }
            void manager::clear() {
                  this->data = inst_result();
                  this->next = 0u;
                  this->labels.clear();
                  return;
            }
      } // namespace builder

      namespace fs {

            void save(const std::filesystem::path &path, const real_inst_map &map) {

                  std::ofstream ofs(path, std::ios::binary | std::ios::app);
                  if (!ofs) {
                        return;
                  }
                  for (const auto &[key, r_inst] : map) {

                        const auto count = static_cast<std::uintptr_t>((r_inst.discrepancies.has_value() ? r_inst.discrepancies->size() : 0u) + 1u);
                        ofs.write(reinterpret_cast<const char *>(&count), sizeof(count));

                        r_inst.first.write(ofs);
                        if (r_inst.discrepancies) {
                              for (const auto &d : *r_inst.discrepancies) {
                                    d.write(ofs);
                              }
                        }
                  }
                  return;
            }

            void load(boost::unordered_flat_map<module_id, inst_result> &buffer, const std::filesystem::path &path) {

                  std::ifstream ifs(path, std::ios::binary);
                  if (!ifs) {
                        return;
                  }

                  boost::unordered_flat_map<module_id, std::vector<inst>> mid_insts;
                  do {

                        std::uintptr_t count = 0u;
                        if (!ifs.read(reinterpret_cast<char *>(&count), sizeof(count))) {
                              break;
                        }

                        for (auto i = 0u; i < count; ++i) {
                              inst d;
                              d.read(ifs);
                              mid_insts.try_emplace(d.mid, std::vector<inst>()).first->second.emplace_back(d);
                        }

                        for (auto &[mid, vect_minst] : mid_insts) {

                              real_inst rinst;
                              if (vect_minst.size() > 1u) {
                                    rinst.discrepancies.emplace(std::vector<inst>()).reserve(vect_minst.size());
                              }
                              for (auto &minst : vect_minst) {

                                    if (rinst.first.empty()) {
                                          rinst.first = std::move(minst);
                                    } else {
                                          minst.did = rinst.discrepancies->size();
                                          rinst.discrepancies->emplace_back(minst);
                                    }
                                    if (minst.entry) {
                                          buffer[mid].entries.insert(rinst.first.pc);
                                    }
                                    if (minst.goes_to()) {
                                          buffer[mid].labels.insert(minst.loc);
                                    }
                              }
                              if (rinst.first.entry) {
                                    buffer[mid].entries.insert(rinst.first.pc);
                              }
                              buffer[mid].map.try_emplace(rinst.first.pc, rinst);
                        }
                        mid_insts.clear();
                  } while (true);
                  return;
            }

            boost::unordered_flat_map<module_id, inst_result> load(const std::filesystem::path &path) {

                  boost::unordered_flat_map<module_id, inst_result> result;
                  load(result, path);
                  return result;
            }

      } // namespace fs

      namespace analyze {

            boost::unordered_flat_set<address> generate_pages(const boost::unordered_flat_map<module_id, inst_result> &insts) {

                  boost::unordered_flat_set<address> result;

                  for (const auto &[mid, insts] : insts) {

                        for (const auto &[addr, inst] : insts.map) {

                              for (const auto &i : inst.accumulate()) {

                                    switch (i.k) {
                                          case inst_kind::call_to:
                                          case inst_kind::return_to: {
                                                result.insert(i.loc);
                                                break;
                                          }
                                          default: {
                                                break;
                                          }
                                    }
                              }
                        }
                  }
                  return result;
            }

            boost::unordered_flat_map<address, luramas::profile::inst> real_pc_map(const inst_result &insts) {

                  boost::unordered_flat_map<address, luramas::profile::inst> result;
                  for (const auto &[_, inst] : insts.map) {
                        result[inst.first.real_pc] = inst.first;
                        if (inst.discrepancies) {
                              for (const auto &i : *inst.discrepancies) {
                                    result[i.real_pc] = i;
                              }
                        }
                  }
                  return result;
            }

            boost::unordered_flat_map<module_id, boost::unordered_flat_set<address>> get_externals(const boost::unordered_flat_map<module_id, inst_result> &insts) {

                  boost::unordered_flat_map<module_id, boost::unordered_flat_set<address>> result;

                  for (const auto &[mid, linsts] : insts) {

                        for (const auto &[addr, inst] : linsts.map) {

                              for (const auto &i : inst.accumulate()) {

                                    switch (i.k) {
                                          case inst_kind::call_to:
                                          case inst_kind::jump_to:
                                          case inst_kind::return_to: {
                                                const auto it = insts.find(i.lid);
                                                if (it == insts.end()) {
                                                      result[i.lid].insert(i.loc);
                                                      break;
                                                }
                                                if (!it->second.map.contains(i.loc)) {
                                                      result[i.lid].insert(i.loc);
                                                }
                                                break;
                                          }
                                          default: {
                                                break;
                                          }
                                    }
                              }
                        }
                  }
                  return result;
            }

            details generate_details(const boost::unordered_flat_map<module_id, inst_result> &inst_res) {

                  details result;
                  result.res = inst_res;
                  result.pages = generate_pages(inst_res);
                  result.externals = get_externals(inst_res);
                  return result;
            }

            std::vector<std::pair<address, address>> order_of_execution(const boost::unordered_flat_map<module_id, inst_result> &inst_res, const module_id mid) {

                  std::vector<std::pair<address, address>> result;
                  if (const auto it = inst_res.find(mid); it != inst_res.end()) {
                        for (const auto &[key, value] : it->second.map) {
                              if (value.first.len()) {
                                    result.emplace_back(std::make_pair(value.first.real_pc, key));
                              }
                        }
                        std::sort(result.begin(), result.end(), [](const auto &a, const auto &b) {
                              return a.first < b.first;
                        });
                  }
                  return result;
            }

            boost::unordered_flat_map<address, std::vector<std::pair<address, std::optional<module_id>>>> inlane_discrepancies(const inst_result &data) {

                  boost::unordered_flat_map<address, std::vector<std::pair<address, std::optional<module_id>>>> result;

                  /* Sort map */
                  const auto map = real_pc_map(data);
                  std::vector<std::pair<address, luramas::profile::inst>> sorted;
                  sorted.reserve(map.size());
                  for (const auto &i : map) {
                        sorted.emplace_back(i);
                  }
                  std::ranges::sort(sorted, {}, &decltype(sorted)::value_type::first);

                  /* Run through */
                  address start = 0u;
                  bool in_run = false;
                  for (const auto &[i, inst] : sorted) {

                        if (inst.did && inst.inlane) {
                              if (!in_run) {
                                    start = i;
                                    auto &vec = result[inst.pc];
                                    vec.reserve(8u);
                                    in_run = true;
                              }
                              result[start].emplace_back(inst.pc, inst.did);
                              continue;
                        }
                        in_run = false;
                  }
                  return result;
            }

            std::vector<execution_order_organized> order_of_execution_organized(const boost::unordered_flat_map<module_id, inst_result> &inst_res, const module_id mid) {

                  std::vector<execution_order_organized> result;

                  const auto rit = inst_res.find(mid);
                  if (rit == inst_res.end()) {
                        return result;
                  }

                  const auto disc_map = inlane_discrepancies(rit->second);
                  const auto execution_order = order_of_execution(inst_res, mid);
                  result.reserve(execution_order.size());

                  for (const auto &[real_pc, pc] : execution_order) {

                        bool inserted = false;
                        execution_order_organized first;
                        first.loc = {real_pc, pc};

                        /* Out of lane */
                        if (const auto mit = rit->second.map.find(pc); mit != rit->second.map.end()) {

                              if (const auto out_of_lane = mit->second.accumulate_out_of_lane_discrepancies(); !out_of_lane.empty()) {

                                    /* First */
                                    inserted = true;
                                    first.k = execution_order_organized::kinds::first;
                                    result.emplace_back(first);
                                    for (const auto &id : out_of_lane) {

                                          /* Insert */
                                          const auto &discrepancy = (*mit->second.discrepancies)[id];
                                          execution_order_organized optional;
                                          optional.k = execution_order_organized::kinds::optional;
                                          optional.loc = {discrepancy.real_pc, discrepancy.pc};
                                          optional.discrepency = discrepancy.did;
                                          optional.fstart_scope = true;
                                          optional.fend_scope = true;
                                          result.emplace_back(optional);
                                    }
                              }
                        }

                        /* Inlane */
                        if (const auto it = disc_map.find(pc); it != disc_map.end()) {

                              /* First */
                              for (const auto &[pc, did] : it->second) {

                                    if (const auto mit = rit->second.map.find(pc); mit != rit->second.map.end()) {

                                          const auto &inst = did ? (*mit->second.discrepancies)[*did] : mit->second.first;
                                          execution_order_organized inlane;
                                          inlane.discrepency = did;
                                          inlane.loc = {inst.real_pc, inst.pc};
                                          inlane.k = execution_order_organized::kinds::inlaned;

                                          if (!inserted) {
                                                inserted = true;
                                                inlane.fstart_scope = true;
                                                first.k = execution_order_organized::kinds::first;
                                                result.emplace_back(first);
                                          }
                                          result.emplace_back(inlane);
                                    }
                              }
                              if (inserted) {
                                    result.back().fend_scope = true;
                                    continue;
                              }
                        }
                        if (!inserted) {
                              result.emplace_back(first);
                        }
                  }
                  return result;
            }

            namespace find {

                  std::optional<std::reference_wrapper<const real_inst>> next(const boost::unordered_flat_map<module_id, inst_result> &d, const inst &i) {

                        const auto lookup = [&](const auto mid, const auto addr) -> std::optional<std::reference_wrapper<const real_inst>> {
                              if (const auto dit = d.find(mid); dit != d.end()) {
                                    if (const auto it = dit->second.map.find(addr); it != dit->second.map.end()) {
                                          return std::cref(it->second);
                                    }
                              }
                              return std::nullopt;
                        };
                        return i.goes_to() ? lookup(i.lid, i.loc) : lookup(i.mid, i.pc + i.len());
                  }

                  std::optional<std::pair<module_id, address>> addr(const details &det, const std::vector<std::uint8_t> &bytes) {

                        for (const auto &[mid, data] : det.res) {

                              for (const auto &[addr, inst] : data.map) {

                                    auto curr = addr;
                                    std::size_t offset = 0u;
                                    while (offset < bytes.size()) {

                                          if (curr == addr) {
                                                if (const auto opt = inst.compare(bytes, offset); opt) {
                                                      offset += !(*opt) ? inst.first.len() : (*inst.discrepancies)[*opt].len();
                                                      continue;
                                                }
                                          } else if (const auto it = data.map.find(addr); it != data.map.end()) {
                                                if (const auto opt = it->second.compare(bytes, offset); opt) {
                                                      offset += !(*opt) ? inst.first.len() : (*inst.discrepancies)[*opt].len();
                                                      continue;
                                                }
                                          }
                                          break;
                                    }
                                    if (offset >= bytes.size()) {
                                          return std::make_pair(mid, addr);
                                    }
                              }
                        }
                        return std::nullopt;
                  }
            } // namespace find
      } // namespace analyze
} // namespace luramas::profile
