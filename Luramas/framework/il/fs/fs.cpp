#include "fs.hpp"
#include <filesystem>
#include <fstream>

namespace luramas::il::fs {

      namespace deserializer {

            struct manager {

                  containers::map::ptrs<std::shared_ptr<il::ilang::kvalue>> kv;
                  containers::map::ptrs<std::shared_ptr<il::disassembly>> dis;
                  containers::map::ptrs<std::shared_ptr<il::ilang>> l;

                  inline void finalize() {
                        this->kv.finalize(nullptr);
                        this->dis.finalize(nullptr);
                        this->l.finalize(nullptr);
                        return;
                  }
            };

            inline std::size_t size(std::istream &is) {
                  std::size_t v = 0u;
                  is.read(reinterpret_cast<char *>(&v), sizeof(v));
                  return v;
            }

            inline std::string string(std::istream &is) {
                  std::size_t len = size(is);
                  std::string s(len, '\0');
                  is.read(&s[0], len);
                  return s;
            }

            inline std::optional<std::string> optional_string(std::istream &is) {
                  auto v = false;
                  is.read(reinterpret_cast<char *>(&v), sizeof(v));
                  if (v) {
                        return string(is);
                  }
                  return std::nullopt;
            }

            inline std::shared_ptr<il::ilang::kvalue> kvalue(std::istream &is, manager &manager) {

                  auto kv = std::make_shared<il::ilang::kvalue>();

                  std::uintptr_t ptr = 0u;
                  is.read(reinterpret_cast<char *>(&ptr), sizeof(ptr));
                  manager.kv.emit_data(ptr, kv);

                  is.read(reinterpret_cast<char *>(&kv->type), sizeof(kv->type));
                  switch (kv->type) {
                        case arch::data::kval_kinds::vector: {
                              const auto n = size(is);
                              kv->vector.vector.resize(n);
                              for (auto &v : kv->vector.vector) {
                                    is.read(reinterpret_cast<char *>(&v), sizeof(v));
                              }
                              break;
                        }
                        case arch::data::kval_kinds::boolean: {
                              is.read(reinterpret_cast<char *>(&kv->boolean.b), sizeof(kv->boolean.b));
                              break;
                        }
                        case arch::data::kval_kinds::integer: {
                              is.read(reinterpret_cast<char *>(&kv->integer.i), sizeof(kv->integer.i));
                              kv->integer.str = string(is);
                              break;
                        }
                        case arch::data::kval_kinds::string: {
                              kv->string.str = string(is);
                              break;
                        }
                        case arch::data::kval_kinds::userdata: {
                              kv->userdata.str = string(is);
                              break;
                        }
                        case arch::data::kval_kinds::table: {
                              is.read(reinterpret_cast<char *>(&kv->table.node_size), sizeof(kv->table.node_size));
                              is.read(reinterpret_cast<char *>(&kv->table.array_size), sizeof(kv->table.array_size));
                              break;
                        }
                        case arch::data::kval_kinds::function: {
                              kv->function.str = string(is);
                              break;
                        }
                        case arch::data::kval_kinds::closure: {
                              is.read(reinterpret_cast<char *>(&kv->closure.id), sizeof(kv->closure.id));
                              is.read(reinterpret_cast<char *>(&kv->closure.ilang_closure), sizeof(kv->closure.ilang_closure));
                              break;
                        }
                        case arch::data::kval_kinds::thread: {
                              kv->thread.str = string(is);
                              break;
                        }
                        case arch::data::kval_kinds::upvalue: {
                              kv->upvalue.str = string(is);
                              break;
                        }
                        default: {
                              break;
                        }
                  }
                  return kv;
            }

            inline std::shared_ptr<il::arch::operand::operand> operand(std::istream &is) {

                  auto o = std::make_shared<il::arch::operand::operand>();
                  is.read(reinterpret_cast<char *>(&o->type), sizeof(o->type));
                  is.read(reinterpret_cast<char *>(&o->k_value_kind), sizeof(o->k_value_kind));
                  is.read(reinterpret_cast<char *>(&o->ref_addr), sizeof(o->ref_addr));
                  is.read(reinterpret_cast<char *>(&o->multret), sizeof(o->multret));
                  o->annotation = optional_string(is);
                  o->k_value = string(is);
                  is.read(reinterpret_cast<char *>(&o->dis), sizeof(o->dis));
                  return o;
            }

            inline std::shared_ptr<il::disassembly> disassembly(std::istream &is, manager &manager) {

                  auto dism = std::make_shared<il::disassembly>();

                  std::uintptr_t ptr = 0u;
                  is.read(reinterpret_cast<char *>(&ptr), sizeof(ptr));
                  manager.dis.emit_data(ptr, dism);

                  is.read(reinterpret_cast<char *>(&dism->addr), sizeof(dism->addr));
                  is.read(reinterpret_cast<char *>(&dism->op), sizeof(dism->op));
                  is.read(reinterpret_cast<char *>(&dism->bin_kind), sizeof(dism->bin_kind));

                  /* Operands */
                  const auto ops = size(is);
                  dism->operands.resize(ops);
                  for (auto i = 0u; i < ops; ++i) {
                        dism->operands[i] = operand(is);
                  }

                  /* Xrefs */
                  const auto xrefs = size(is);
                  dism->xrefs.resize(xrefs);
                  for (auto i = 0u; i < xrefs; ++i) {
                        std::uintptr_t ptr = 0u;
                        is.read(reinterpret_cast<char *>(&ptr), sizeof(ptr));
                        manager.dis.emit_pend(ptr, &dism->xrefs[0u]);
                  }

                  is.read(reinterpret_cast<char *>(&dism->ref), sizeof(dism->ref));
                  return dism;
            }

            inline il::ilang::debug_manager debug_manager(std::istream &is, manager &manager) {

                  il::ilang::debug_manager dm(nullptr);

                  std::uintptr_t ptr = 0u;
                  is.read(reinterpret_cast<char *>(&ptr), sizeof(ptr));
                  manager.l.emit_pend(ptr, &dm.linked);

                  const auto n = size(is);
                  for (auto i = 0u; i < n; ++i) {

                        luramas_register r = 0u;
                        is.read(reinterpret_cast<char *>(&r), sizeof(r));

                        dm.defined[r] = std::vector<std::pair<std::pair<std::shared_ptr<il::disassembly>, std::shared_ptr<il::disassembly>>, std::string>>();
                        dm.defined[r].resize(size(is));

                        for (auto &[dism_p, str] : dm.defined[r]) {

                              str = string(is);
                              is.read(reinterpret_cast<char *>(&dism_p.first), sizeof(dism_p.first));
                              is.read(reinterpret_cast<char *>(&dism_p.second), sizeof(dism_p.second));
                        }
                  }
                  return dm;
            }
      } // namespace deserializer

      namespace serializer {

            template <typename T>
            inline void ptr(const std::shared_ptr<T> &p, std::ostream &os) {
                  const auto r = reinterpret_cast<std::uintptr_t>(p.get());
                  os.write(reinterpret_cast<const char *>(&r), sizeof(r));
                  return;
            }

            inline void size(const std::size_t v, std::ostream &os) {
                  os.write(reinterpret_cast<const char *>(&v), sizeof(v));
                  return;
            }

            inline void string(const std::string &s, std::ostream &os) {
                  size(s.size(), os);
                  os.write(s.data(), s.size());
                  return;
            }

            inline void optional_string(const std::optional<std::string> &s, std::ostream &os) {
                  const auto v = s.has_value();
                  os.write(reinterpret_cast<const char *>(&v), sizeof(v));
                  if (v) {
                        string(*s, os);
                  }
                  return;
            }

            inline void kvalue(const std::shared_ptr<il::ilang::kvalue> &kv, std::ostream &os) {

                  ptr(kv, os);
                  os.write(reinterpret_cast<const char *>(&kv->type), sizeof(kv->type));
                  switch (kv->type) {
                        case arch::data::kval_kinds::vector: {
                              size(kv->vector.vector.size(), os);
                              for (const auto &v : kv->vector.vector) {
                                    os.write(reinterpret_cast<const char *>(&v), sizeof(v));
                              }
                              break;
                        }
                        case arch::data::kval_kinds::boolean: {
                              os.write(reinterpret_cast<const char *>(&kv->boolean.b), sizeof(kv->boolean.b));
                              break;
                        }
                        case arch::data::kval_kinds::integer: {
                              os.write(reinterpret_cast<const char *>(&kv->integer.i), sizeof(kv->integer.i));
                              string(kv->integer.str, os);
                              break;
                        }
                        case arch::data::kval_kinds::string: {
                              string(kv->string.str, os);
                              break;
                        }
                        case arch::data::kval_kinds::userdata: {
                              string(kv->userdata.str, os);
                              break;
                        }
                        case arch::data::kval_kinds::table: {
                              os.write(reinterpret_cast<const char *>(&kv->table.node_size), sizeof(kv->table.node_size));
                              os.write(reinterpret_cast<const char *>(&kv->table.array_size), sizeof(kv->table.array_size));
                              break;
                        }
                        case arch::data::kval_kinds::function: {
                              string(kv->function.str, os);
                              break;
                        }
                        case arch::data::kval_kinds::closure: {
                              os.write(reinterpret_cast<const char *>(&kv->closure.id), sizeof(kv->closure.id));
                              os.write(reinterpret_cast<const char *>(&kv->closure.ilang_closure), sizeof(kv->closure.ilang_closure));
                              break;
                        }
                        case arch::data::kval_kinds::thread: {
                              string(kv->thread.str, os);
                              break;
                        }
                        case arch::data::kval_kinds::upvalue: {
                              string(kv->upvalue.str, os);
                              break;
                        }
                        default: {
                              break;
                        }
                  }
                  return;
            }

            inline void operand(const std::shared_ptr<il::arch::operand::operand> &o, std::ostream &os) {

                  os.write(reinterpret_cast<const char *>(&o->type), sizeof(o->type));
                  os.write(reinterpret_cast<const char *>(&o->k_value_kind), sizeof(o->k_value_kind));
                  os.write(reinterpret_cast<const char *>(&o->ref_addr), sizeof(o->ref_addr));
                  os.write(reinterpret_cast<const char *>(&o->multret), sizeof(o->multret));
                  optional_string(o->annotation, os);
                  string(o->k_value, os);
                  os.write(reinterpret_cast<const char *>(&o->dis), sizeof(o->dis));
                  return;
            }

            inline void disassembly(const std::shared_ptr<il::disassembly> &dism, std::ostream &os) {

                  ptr(dism, os);
                  os.write(reinterpret_cast<const char *>(&dism->addr), sizeof(dism->addr));
                  os.write(reinterpret_cast<const char *>(&dism->op), sizeof(dism->op));
                  os.write(reinterpret_cast<const char *>(&dism->bin_kind), sizeof(dism->bin_kind));

                  /* Operands */
                  size(dism->operands.size(), os);
                  for (const auto &o : dism->operands) {
                        operand(o, os);
                  }

                  /* Xrefs */
                  size(dism->xrefs.size(), os);
                  for (const auto &o : dism->xrefs) {
                        ptr(o, os);
                  }

                  os.write(reinterpret_cast<const char *>(&dism->ref), sizeof(dism->ref));
                  return;
            }

            inline void debug_manager(const il::ilang::debug_manager &dm, std::ostream &os) {

                  /* Linked/Defins */
                  ptr(dm.linked, os);
                  size(dm.defined.size(), os);
                  for (const auto &[r, v] : dm.defined) {

                        /* Data  */
                        os.write(reinterpret_cast<const char *>(&r), sizeof(r));
                        size(v.size(), os);
                        for (const auto &[dism_p, str] : v) {

                              string(str, os);
                              ptr(dism_p.first, os);
                              ptr(dism_p.second, os);
                        }
                  }
                  return;
            }
      } // namespace serializer

      void save(const std::shared_ptr<ilang> &lang, std::ostream &buffer) {

            std::vector<std::shared_ptr<ilang>> vect;
            boost::unordered_flat_set<std::shared_ptr<ilang>> done;
            vect.reserve(LURAMAS_IL_PREDICTED_RECURSION_AMOUNT);
            vect.emplace_back(lang);

            while (!vect.empty()) {

                  auto curr = vect.back();
                  vect.pop_back();
                  done.insert(curr);

                  serializer::ptr(curr, buffer);

                  /* Debug */
                  const auto v = curr->debug.has_value();
                  buffer.write(reinterpret_cast<const char *>(&v), sizeof(v));
                  if (v) {
                        serializer::debug_manager(*curr->debug, buffer);
                  }

                  /* Disassembly */
                  serializer::size(curr->dis.size(), buffer);
                  for (const auto &d : curr->dis) {
                        serializer::disassembly(d, buffer);
                  }

                  /* Kvalues */
                  serializer::size(curr->kval.size(), buffer);
                  for (const auto &k : curr->kval) {
                        serializer::kvalue(k, buffer);
                  }

                  /* Closures */
                  serializer::size(curr->closures.size(), buffer);
                  for (const auto &c : curr->closures) {
                        serializer::ptr(c, buffer);
                  }

                  std::copy_if(curr->closures.begin(), curr->closures.end(), std::back_inserter(vect), [&](const auto &i) { return !done.contains(i); });
            }
            return;
      }

      void save(const std::shared_ptr<ilang> &lang, const std::string &directory, const std::string &name) {

            auto dir_opt = luramas::fs::get_directory(directory);
            if (!dir_opt) {
                  return;
            }
            auto dir = std::move(*dir_opt);

            std::ostringstream oss;
            save(lang, oss);

            const auto &serialized_data = oss.str();
            auto ofs_opt = luramas::fs::file_output(dir, name, LURAMAS_IL_FS_EXTENSION);
            if (!ofs_opt) {
                  return;
            }

            ofs_opt->write(serialized_data.data(), serialized_data.size());
            return;
      }

      std::shared_ptr<ilang> load(std::istream &is) {

            deserializer::manager manager;

            auto result = std::make_shared<ilang>();
            std::vector<std::shared_ptr<ilang>> vect;
            vect.emplace_back(result);

            while (!vect.empty()) {

                  auto curr = vect.back();
                  vect.pop_back();

                  std::uintptr_t ptr = 0u;
                  is.read(reinterpret_cast<char *>(&ptr), sizeof(ptr));
                  manager.l.emit_data(ptr, result);

                  /* Debug */
                  bool dbg = false;
                  is.read(reinterpret_cast<char *>(&dbg), sizeof(dbg));
                  if (dbg) {
                        curr->debug = deserializer::debug_manager(is, manager);
                  }

                  /* Dism */
                  const auto dis_n = deserializer::size(is);
                  curr->dis.clear();
                  curr->dis.reserve(dis_n);
                  for (auto i = 0u; i < dis_n; ++i) {
                        curr->dis.emplace_back(deserializer::disassembly(is, manager));
                  }

                  /* KValues */
                  const auto kval_n = deserializer::size(is);
                  curr->kval.clear();
                  curr->kval.reserve(kval_n);
                  for (auto i = 0u; i < kval_n; ++i) {
                        curr->kval.emplace_back(deserializer::kvalue(is, manager));
                  }

                  /* Closures */
                  const auto cls_n = deserializer::size(is);
                  curr->closures.reserve(cls_n);
                  for (auto i = 0u; i < cls_n; ++i) {

                        std::uintptr_t ptr = 0u;
                        is.read(reinterpret_cast<char *>(&ptr), sizeof(ptr));
                        curr->closures.emplace_back(nullptr);
                        manager.l.emit_pend(ptr, &curr->closures.back());
                        if (!manager.l.map.contains(ptr)) {
                              vect.emplace_back(std::make_shared<ilang>());
                        }
                  }
            }

            manager.finalize();
            return result;
      }
      std::shared_ptr<ilang> load(const std::string &directory, const std::string &name) {

            auto input_opt = luramas::fs::file_input(directory, name, LURAMAS_IL_FS_EXTENSION);
            if (!input_opt) {
                  return nullptr;
            }
            auto ifs = std::move(*input_opt);

            std::ostringstream oss;
            oss << ifs.rdbuf();

            std::istringstream iss(oss.str());
            return load(iss);
      }

} // namespace luramas::il::fs