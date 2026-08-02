#pragma once

/* Imports gaurd from Lua */
#pragma push_macro("cast")
#pragma push_macro("check_exp")
#pragma push_macro("MAX_SIZE")
#undef cast
#undef check_exp
#undef MAX_SIZE
#include "blocks_loader.hpp"
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#pragma pop_macro("MAX_SIZE")
#pragma pop_macro("check_exp")
#pragma pop_macro("cast")

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

            /* Block map */
            boost::unordered_flat_map<loader::block_ptr<MAX_LEN>, VertexDesc<MAX_LEN>> blk_to_vertex;
            for (const auto &blk : adata.sorted_blocks_global_id) {
                  blk_to_vertex[blk] = std::int32_t(boost::add_vertex(blk, g));
            }

            /* Vertex map */
            boost::unordered_flat_map<address, VertexDesc<MAX_LEN>> addr_to_vertex;
            for (const auto &[rpc, blk] : adata.real_pc_map) {
                  addr_to_vertex[rpc] = blk_to_vertex[blk];
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