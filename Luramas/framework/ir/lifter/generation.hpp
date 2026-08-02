#pragma once
#include "../ir.hpp"
#include "definitions.hpp"

namespace luramas::ir::generation {

      namespace cfg {

            /* Less ambigous edge kinds */
            enum class block_kind : std::uint8_t {
                  none, /* Nothing */
                  jump, /* Jump to node */
                  then, /* Then node */
                  fall  /* Fall to node */
            };
            /* Kind of edges */
            enum class edge_kind : std::uint8_t {
                  none, /* Nothing */
                  jump, /* Jump to node */
                  back  /* Back edge */
            };

            struct block {

                  luramas_flag fpart_of_nedges = false; /* Does node jump to a new block but falls to the same instruction but different node pointer? (Ordered) */
                  luramas_flag fforced_end = false;     /* Was block forced to end prematurely? */
                  luramas_flag fanalyzed = false;       /* Analyzed (if marked false block could be dead) */

                  std::shared_ptr<block> jump = nullptr; /* Jump node */
                  edge_kind jumpk = edge_kind::jump;     /* Jump kind */
                  std::shared_ptr<block> then = nullptr; /* Then node */
                  edge_kind thenk = edge_kind::jump;     /* Then kind */
                  std::shared_ptr<block> fall = nullptr; /* Fall node */
                  edge_kind fallk = edge_kind::jump;     /* Fall kind */

                  luramas_address entry = 0u;    /* Entry point */
                  luramas_address ending = 0u;   /* Ending point */
                  luramas_blockrange node_range; /* Nodes begin */

                  /* Emitters */
                  void emit(const std::shared_ptr<block> &jump, const std::shared_ptr<block> &then = nullptr, const std::shared_ptr<block> &fall = nullptr);
                  void emit(const luramas_address entry, const luramas_address ending = 0u, const luramas_address nodes_begin = 0u, const luramas_address nodes_end = 0u);
                  void emit(const luramas_address entry, const luramas_address ending = 0u, const luramas_blockrange range = {0u, 0u});

                  /* Get successors */
                  boost::fixed_vector<std::pair<edge_kind, std::shared_ptr<block>>, 3u> get_successors() const;     /* Get successors with edge kinds */
                  boost::fixed_vector<std::pair<block_kind, std::shared_ptr<block>>, 3u> get_successors_bk() const; /* Get successors with block kinds */
                  boost::fixed_vector<std::shared_ptr<generation::cfg::block>, 3u> get_block_successors() const;    /* Get block successors */

                  /* Determines the edge kind connecting to the target block, prioritizing back-edges over forward successors */
                  edge_kind dominant_successor_edge(const std::shared_ptr<block> &target) const;

                  /* Ranges */
                  luramas_address get_end() const;   /* Gets front: [front, ...) */
                  luramas_address get_front() const; /* Gets end: [..., end) */

                  /* Iterations */
                  luramas_range_iter get_iter() const;          /* Normal range iterator */
                  luramas_range_reverse_iter get_riter() const; /* Reverse range iterator */
            };

            struct cfg {

                  std::shared_ptr<block> entry = nullptr;                                                                            /* Entry node */
                  std::vector<std::shared_ptr<block>> blocks;                                                                        /* Organized block by dominance fall -> then -> jump */
                  std::vector<luramas_id> highlevel_scope_ids;                                                                       /* High level scope IDS */
                  boost::unordered_flat_set<luramas_address> interacted_nodes;                                                       /* Nodes hit */
                  boost::unordered_flat_map<std::shared_ptr<block>, boost::unordered_flat_set<std::shared_ptr<block>>> predecessors; /* Predecessors for blocks */

                  /* Visits all blocks with an edge kind targeting it */
                  template <edge_kind k>
                  boost::unordered_flat_set<std::shared_ptr<block>> visit_edges() const {
                        boost::unordered_flat_set<std::shared_ptr<block>> result;
                        for (const auto &b : this->blocks) {
                              if (b->jumpk == k || b->thenk == k || b->fallk == k) {
                                    result.insert(b);
                              }
                        }
                        return result;
                  }

                  /* Visit block given address */
                  std::shared_ptr<block> visit(const luramas_address n) const;

                  /* Returns the index of the last element in the first contiguous sequence of the specified scope ID, or 0 if no such bounded sequence is found */
                  std::size_t contiguous_firstlast_scopeid(const std::size_t n) const;

                  /* Returns the first block that contains the most scope id for a given address range */
                  std::shared_ptr<block> most_scope_id(const std::vector<std::shared_ptr<block>> &v) const;

                  /* Maps block to its index in blocks vector */
                  boost::unordered_flat_map<std::shared_ptr<block>, luramas_index> map() const;

                  ~cfg() {

                        for (auto &p : this->predecessors) {
                              p.second.clear();
                        }
                        this->predecessors.clear();
                        this->entry.reset();

                        for (auto &b : this->blocks) {
                              b.reset();
                        }
                        this->blocks.clear();
                        this->interacted_nodes.clear();
                        return;
                  }
            };
            cfg generate(se_ir &ir, const luramas_address entry = 0u, const luramas_flag finclude_pages = false);
      } // namespace cfg

      namespace types {

            /* SSA values seen with predicted count size */
            template <std::uint8_t p>
            using ssa_values = boost::unordered_flat_smallpolyset<luramas_xregister, p>;

            template <std::uint8_t p>
            using block_seen = boost::unordered_flat_map<std::shared_ptr<cfg::block>, boost::unordered_flat_set<luramas_xregister>>;

      } // namespace types

      namespace ssa {

            static constexpr auto UNKNOWN_SSA_VERSION = 0u; /* Placeholder SSA verision or an unknown version */

            /* Type of SSA assignment */
            enum class assignment_kind : std::uint8_t {
                  phi,   /* PHI */
                  single /* Single SSA */
            };

            struct assignment {

                  boost::unordered_flat_smallpolyset<luramas_register, LURAMAS_PREDICTED_REGS> regs; /* Cached registers */
                  boost::unordered_flat_map<luramas_register, luramas_count> refrence_regs;          /* Reference count of reg */
                  boost::unordered_flat_map<luramas_register /* Linked */, std::pair<assignment_kind, boost::unordered_flat_set<luramas_xregister> /* SSA */>> assigns;

                  template <bool force_phi = false>
                  inline void assign(const luramas_xregister s, const luramas_register l, const bool cache_register = true) {
                        if (cache_register) {
                              this->regs.insert(l);
                        }
                        auto [it, inserted] = this->assigns.try_emplace(l, std::make_pair(assignment_kind::single, boost::unordered_flat_set<luramas_xregister>({s})));
                        if (!inserted) {
                              auto &[kind, reg_set] = it->second;
                              if (reg_set.insert(s).second && reg_set.size() > 1u) {
                                    kind = assignment_kind::phi;
                              }
                        }
                        if (force_phi) {
                              it->second.first = assignment_kind::phi;
                        }
                        return;
                  }
                  inline void reference(const luramas_register reg) {
                        auto it = this->refrence_regs.find(reg);
                        if (it == this->refrence_regs.end()) {
                              this->refrence_regs.insert(std::make_pair(reg, 1u));
                        } else {
                              ++it->second;
                        }
                        return;
                  }
            };
            struct node {
                  assignment l; /* L value */
                  assignment r; /* R value */
            };
            struct ssa {
                  se_ir &linked;                                                                                                                                                                                                                                                 /* Linked IR */
                  boost::unordered_flat_map<std::shared_ptr<ir_stat>, node> nodes;                                                                                                                                                                                               /* Stat -> Node */
                  boost::unordered_flat_multiset<luramas_register> assignments;                                                                                                                                                                                                  /* Registers that are used in SSA */
                  boost::unordered_flat_map<luramas_xregister /* SSA */, std::pair<std::shared_ptr<ir_stat> /* Assignment */, std::pair<luramas_address /* Index */, std::pair<boost::unordered_multiset<luramas_address> /* Ref Locs */, std::size_t /* Ref amount */>>>> defs; /* Definition data */
                  boost::unordered_flat_set<luramas_xregister> phis;                                                                                                                                                                                                             /* SSA values that are used in PHI nodes */
                  boost::unordered_flat_set<luramas_xregister> captures;                                                                                                                                                                                                         /* SSA values that are used in captures */
                  boost::unordered_flat_set<luramas_xregister> referenced;                                                                                                                                                                                                       /* Referenced SSA regs */
                  boost::unordered_flat_map<luramas_address, boost::unordered_flat_set<luramas_register>> unknown;                                                                                                                                                               /* Unknown SSA versions */
                  std::vector<luramas_id> high_level_scope_id;                                                                                                                                                                                                                   /* High level scope ID to help determine other scopes from others. Based on the amount of addresses */
                  ssa(se_ir &ir)
                      : linked(ir) {
                        this->nodes.reserve(ir.data.size());
                        for (const auto &n : ir.data) {
                              this->nodes.try_emplace(n, node());
                        }
                        return;
                  }
            };

            struct ssa_flags {
                  luramas_flag finclude_captures = false;   /* Include any captures? */
                  luramas_flag finclude_references = false; /* Include any references? */
            };

            /* Generates SSA Note. Indexes are considered R values opposed to Lvalues. */
            ssa generate(se_ir &ir, const ssa_flags &f = ssa_flags(), const std::optional<boost::unordered_flat_map<std::shared_ptr<ir_stat>, luramas::ir::definitions::exprs>> &exprs = std::nullopt, const std::optional<cfg::cfg> &ocfg = std::nullopt);

      } // namespace ssa

      namespace flag_ssa {

            struct fssa {
                  se_ir &linked;                                                                                                                    /* Linked IR */
                  boost::unordered_flat_map<luramas_address, luramas_xregister> set;                                                                /* Set addresses to FSSA value */
                  boost::unordered_flat_map<luramas_xregister, std::pair<std::size_t /* Refs */, boost::unordered_flat_set<luramas_address>>> used; /* FSSA value to amount of references and reference locations */
                  boost::unordered_flat_set<luramas_xregister> phis;                                                                                /* FSSA values that are used in PHI nodes */
                  boost::unordered_flat_set<luramas_xregister> unsafe;                                                                              /* FSSA values that are used in unsafe locations i.e. other closures */

                  fssa(se_ir &ir)
                      : linked(ir) {
                        this->set.reserve(ir.data.size() / LURAMAS_PREDICTED_FLAGS_PER_IR);
                        return;
                  }
            };
            /* Generate SSA version of flags Note. Should be only called with main closure, calling with other closures that arent visible will lead to unsafe FSSA values. */
            fssa generate(se_ir &ir, const boost::unordered_flat_map<std::shared_ptr<ir_stat>, luramas::ir::definitions::exprs> &exprs);
      } // namespace flag_ssa

} // namespace luramas::ir::generation
