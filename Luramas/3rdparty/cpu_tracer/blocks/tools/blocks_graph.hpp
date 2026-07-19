#pragma once
#include "blocks_loader.hpp"
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>

namespace cpu_tracer::blocks::graph {

      /* Boost graph */
      template <std::uint8_t MAX_LEN>
      using Graph = boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, loader::block_ptr<MAX_LEN>>;

      /* Vertex desc */
      template <std::uint8_t MAX_LEN>
      using VertexDesc = typename boost::graph_traits<Graph<MAX_LEN>>::vertex_descriptor;

      /* Generate boost graph */
      template <std::uint8_t MAX_LEN>
      inline Graph<MAX_LEN> generate_graph(const loader::analyze::analyzed_data<MAX_LEN> &adata, const loader::analyze::edge_data &edges) {

            Graph<MAX_LEN> g;

            /* Vertex map */
            boost::unordered_flat_map<address, VertexDesc<MAX_LEN>> addr_to_vertex;
            for (const auto &[addr, blk] : adata.real_pc_map) {
                  addr_to_vertex[addr] = std::int32_t(boost::add_vertex(blk, g));
            }

            /* Inset all successors */
            for (const auto &[src_addr, edge_set] : edges.successors) {

                  const auto src_it = addr_to_vertex.find(src_addr);
                  if (src_it == addr_to_vertex.end()) {
                        continue;
                  }

                  const auto u = src_it->second;
                  for (const auto &i : edge_set) {

                        const auto dest_it = addr_to_vertex.find(i.dst_realpc);
                        if (dest_it == addr_to_vertex.end()) {
                              continue;
                        }
                        boost::add_edge(u, dest_it->second, g);
                  }
            }
            return g;
      }
} // namespace cpu_tracer::blocks::graph