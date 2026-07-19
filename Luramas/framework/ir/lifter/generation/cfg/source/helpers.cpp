#include "../helpers.hpp"
#include <boost/graph/graphviz.hpp>
#include <sstream>

namespace luramas::ir::cfg::helpers {

      struct edge_writer {
            const boost::unordered_flat_map<boost::graph_traits<boost_graph::g_t>::edge_descriptor, generation::cfg::block_kind> &edge_kinds;

            template <class edge>
            void operator()(std::ostream &out, const edge &e) const {
                  if (const auto it = edge_kinds.find(e); it != edge_kinds.end()) {
                        switch (it->second) {
                              case generation::cfg::block_kind::jump: {
                                    out << "[color=red]";
                                    break;
                              }
                              case generation::cfg::block_kind::then: {
                                    out << "[color=green]";
                                    break;
                              }
                              case generation::cfg::block_kind::fall: {
                                    out << "[color=purple]";
                                    break;
                              }
                              default: {
                                    out << "[color=black]";
                                    break;
                              }
                        }
                  } else {
                        out << "[color=black]";
                  }
                  return;
            }
      };

      std::string str(const se_ir &ir, const boost_graph &graph) {

            boost::unordered_flat_map<boost_graph::g_t::vertex_descriptor, std::string> labels;
            for (const auto &[b, v] : graph.vertex_descriptor) {
                  if (const auto &s = ir.data[b->get_end() - 1u]; s) {
                        labels[v] = !s->annotation.empty() ? s->annotation : s->str();
                  } else {
                        labels[v] = std::to_string(b->get_front());
                  }
            }
            std::ostringstream oss;
            boost::write_graphviz(oss, graph.graph, boost::make_label_writer(boost::make_assoc_property_map(labels)), edge_writer{graph.edge_kinds});
            return oss.str();
      }

      boost_graph generate_boost_graph(const generation::cfg::cfg &cfg) {

            boost_graph result;
            for (const auto &b : cfg.blocks) {
                  result.vertex_descriptor[b] = boost::add_vertex(result.graph);
            }
            for (const auto &b : cfg.blocks) {
                  for (const auto &[kind, succ] : b->get_successors_bk()) {
                        if (const auto [e, inserted] = boost::add_edge(result.vertex_descriptor[b], result.vertex_descriptor[succ], result.graph); inserted) {
                              result.edge_kinds[e] = kind;
                        }
                  }
            }
            result.entry = cfg.entry;
            return result;
      }

} // namespace luramas::ir::cfg::helpers