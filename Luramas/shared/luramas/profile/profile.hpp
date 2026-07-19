#include <boost\unordered\unordered_flat_map.hpp>
#include <boost\unordered\unordered_flat_set.hpp>
#include <boostpp\vector.hpp>
#include <cstdint>
#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <istream>
#include <optional>
#include <ostream>
#include <rapidjson\ostreamwrapper.h>
#include <rapidjson\writer.h>
#include <string>
#include <variant>
#include <vector>

namespace luramas::profile {

      static constexpr auto MAX_INST_LEN = 15u;

      using module_id = std::uint8_t;                                                   /* Module ID */
      using address = std::uintptr_t;                                                   /* Address */
      using address_len = std::uint8_t;                                                 /* Address length */
      using range = std::pair<address, address>;                                        /* Range is [Start, End) */
      using inst_bytes = boost::fixed_vector<std::uint8_t, MAX_INST_LEN, std::uint8_t>; /* Instruction bytes */

      static constexpr std::uint8_t READ_BYTES = sizeof(address);

      inline constexpr auto contains(const range &range, const address loc) {
            return loc >= range.first && loc < range.second;
      }
      inline constexpr auto make(const address start, const address end) {
            return std::make_pair(start, end + 1u);
      }

      enum class inst_kind : std::uint8_t {
            normal,    /* Normal instruction */
            jump_to,   /* Jump instruction */
            call_to,   /* Call instruction */
            return_to, /* Return instruction (Instructions that use this will need to have every location documentated as possible else it will assume return is internally managed) */
            memset     /* Memory set instruction */
      };

      struct inst {

            bool last = false;        /* Last instruction */
            bool marked = false;      /* Marked instruction */
            bool conditional = false; /* Conditional instruction */
            bool entry = false;       /* Entry point */
            bool inlane = true;       /* Did discrepancy only stepped into the next discrepancy? */
            bool discrepancy = false; /* Is part of a discrepancy */

            inst_kind k = inst_kind::normal;             /* Instruction kind */
            std::uint8_t interp_as = 0u;                 /* Interpret instructions as? */
            std::uint8_t memset_bytes = 0u;              /* Bytes set by instruction */
            address pc = 0u;                             /* Address as in memory */
            address real_pc = 0u;                        /* PC relative to other insts */
            address loc = 0u;                            /* Location to either referenced call, jump, return, memset */
            address next_real_pc = 0u;                   /* Next real pc */
            inst_bytes bytes;                            /* Byte data */
            module_id lid = 0u;                          /* Location reference Module-ID (for loc member) */
            module_id mid = 0u;                          /* Module ID */
            module_id tid = 0u;                          /* Thread ID */
            std::optional<module_id> did = std::nullopt; /* Discrepency ID */

            void emit_jump(const address loc);
            void emit_return(const address loc);
            void emit_call(const address loc);
            void emit_memset(const std::uintptr_t loc, const std::uint8_t memset_bytes);

            bool cmp(const inst_bytes &other) const;
            bool cmp(const std::vector<std::uint8_t> &other, const std::size_t offset) const;
            bool cmp(const inst &other) const;
            bool operator==(const inst &other) const;
            bool operator!=(const inst &other) const;

            void write(std::ofstream &ofs) const;
            void read(std::ifstream &ifs);

            std::string str(const bool metadata_only = false) const;
            bool goes_to() const;
            std::uint8_t len() const;
            bool is_terminal() const;
            bool empty() const;
            void clear();
      };
      using addresses = boost::unordered_flat_set<address>;

      struct real_inst {

            inst first; /* Tip: If you are iterating through unsafe code for each iteration first should be dominant */
            std::optional<std::vector<inst>> discrepancies;

            real_inst() = default;
            explicit real_inst(const inst &first)
                : first(first) {
            }
            explicit real_inst(const std::vector<inst> &discrepancies)
                : discrepancies(discrepancies) {
            }
            explicit real_inst(const inst &first, const std::vector<inst> &discrepancies)
                : first(first), discrepancies(discrepancies) {
            }

            /* Indexs */
            std::optional<std::reference_wrapper<inst>> operator[](const std::size_t idx);
            std::optional<std::reference_wrapper<const inst>> operator[](const std::size_t idx) const;

            std::vector<inst> accumulate() const;
            std::vector<inst> accumulate(const inst_bytes &b) const;
            std::vector<module_id> accumulate_out_of_lane_discrepancies() const; /* Accumulate discrepency IDs that are not inlaned */

            bool safe_code() const;
            addresses get_len() const;
            bool goes_to() const;
            void get_gotos(addresses &result) const;
            addresses get_gotos() const;
            address loc() const;

            /* Compare see if bytes (Does not compare bytes fully on see if this->bytes matches with front of bytes) exist with offset, returns module_id, 0 = first */
            std::optional<module_id> compare(const std::vector<std::uint8_t> &bytes, const std::size_t offset) const;
      };

      using real_inst_map = boost::unordered_flat_map<address, luramas::profile::real_inst>;
      struct inst_result {

            addresses labels;  /* PC labels */
            addresses entries; /* PC entries */
            real_inst_map map; /* PC to inst */

            bool reachable(const address loc) const;
      };

      namespace builder {

            struct manager {

                  module_id id = 1u;

                  inst construct(const inst_bytes &bytes);
                  address emit(const inst_bytes &bytes);
                  address emit(const inst_bytes &bytes, const bool entry);
                  address emit(const inst_bytes &bytes, const address goto_loc, const inst_kind k, const bool conditional = false);
                  address emit(const inst_bytes &bytes, const inst_kind k, const address label, const bool conditional = false);
                  address emit(const address existing, const inst_kind k, const address label);
                  address emit_label(const address label);

                  /* Emit another label */
                  address emit(const address existing, const address label, const inst_kind k);

                  void extract(boost::unordered_flat_map<module_id, inst_result> &buffer) const;
                  void dump() const;
                  void clear();

                private:
                  struct label {

                        bool finalized = false;
                        address loc = 0u;
                        std::vector<std::pair<address, std::optional<std::size_t> /* Descrepency ID */>> pending;
                  };
                  address next = 0u;
                  inst_result data;
                  boost::unordered_flat_map<address, label> labels;
            };
      } // namespace builder

      namespace fs {

            void save(const std::filesystem::path &path, const real_inst_map &map);
            void load(boost::unordered_flat_map<module_id, inst_result> &buffer, const std::filesystem::path &path);
            boost::unordered_flat_map<module_id, inst_result> load(const std::filesystem::path &path);
      } // namespace fs

      namespace externals {

            template <typename T>
            struct external {
                  module_id mid = 0u;
                  address loc = 0u;
                  std::vector<T> args;
                  std::vector<T> results;
                  std::string name = "";
            };

            template <typename T>
            using data = boost::unordered_flat_map<module_id, boost::unordered_flat_map<address, external<T>>>;

            template <typename T>
            void emit(data<T> &d, address func_loc, std::vector<T> args, std::vector<T> results, const std::string &name, module_id mid = 1u) {
                  d[mid][func_loc] = external<T>(mid, func_loc, args, results, name);
                  return;
            }
      } // namespace externals

      namespace analyze {

            /* Generate page entries */
            boost::unordered_flat_set<address> generate_pages(const boost::unordered_flat_map<module_id, inst_result> &insts);

            /* Generate map based on real pc */
            boost::unordered_flat_map<address, luramas::profile::inst> real_pc_map(const inst_result &insts);

            /* Get external call locations */
            boost::unordered_flat_map<module_id, boost::unordered_flat_set<address>> get_externals(const boost::unordered_flat_map<module_id, inst_result> &insts);

            struct details {
                  boost::unordered_flat_set<address> pages;                                           /* Pages start */
                  boost::unordered_flat_map<module_id, inst_result> res;                              /* Inst data */
                  boost::unordered_flat_map<module_id, boost::unordered_flat_set<address>> externals; /* External locs */
            };
            details generate_details(const boost::unordered_flat_map<module_id, inst_result> &inst_res);

            /* Generate order of execution with MID, {real_pc, pc} */
            std::vector<std::pair<address, address>> order_of_execution(const boost::unordered_flat_map<module_id, inst_result> &inst_res, const module_id mid);

            /* Generate inlane discrepncies {PC, {{PC, INLANE ID}, ...}} */
            boost::unordered_flat_map<address, std::vector<std::pair<address, std::optional<module_id>>>> inlane_discrepancies(const inst_result &data);

            struct execution_order_organized {

                  enum class kinds : std::uint8_t {
                        normal,   /* First nothing wrong with it */
                        inlaned,  /* Part of inlaned */
                        optional, /* Instruction will appear at some point but it is garunteed to appear. */
                        first     /* First instruction next will either be optional or inlaned */
                  };
                  bool fstart_scope = false;                           /* (Discrepency) start scope? */
                  bool fend_scope = false;                             /* (Discrepency) end scope? */
                  kinds k = kinds::normal;                             /* Kind */
                  std::pair<address, address> loc;                     /* Location {real_pc, PC} */
                  std::optional<module_id> discrepency = std::nullopt; /* Discrepency ID */
            };
            std::vector<execution_order_organized> order_of_execution_organized(const boost::unordered_flat_map<module_id, inst_result> &inst_res, const module_id mid);

            namespace find {

                  /* Finds next insts by address */
                  std::optional<std::reference_wrapper<const real_inst>> next(const boost::unordered_flat_map<module_id, inst_result> &d, const inst &i);

                  /* Find address and module ID given bytes */
                  std::optional<std::pair<module_id, address>> addr(const details &det, const std::vector<std::uint8_t> &bytes);
            } // namespace find
      } // namespace analyze

} // namespace luramas::profile