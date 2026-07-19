#pragma once
#include "../../generation.hpp"
#include <boost/graph/adjacency_list.hpp>

namespace luramas::ir::cfg::helpers {

      struct boost_graph {

            using g_t = boost::adjacency_list<boost::vecS, boost::vecS, boost::bidirectionalS>; /* Graph data */
            using n_t = boost::graph_traits<g_t>::vertex_descriptor;                            /* Nodes descriptor */

            g_t graph;
            boost::unordered_flat_map<std::shared_ptr<generation::cfg::block>, n_t> vertex_descriptor;
            boost::unordered_flat_map<boost::graph_traits<g_t>::edge_descriptor, generation::cfg::block_kind> edge_kinds;
            std::shared_ptr<generation::cfg::block> entry = nullptr;
      };

      /* Get string representation */
      std::string str(const se_ir &ir, const boost_graph &graph);

      /* Convert CFG to boost graph for computations */
      boost_graph generate_boost_graph(const generation::cfg::cfg &cfg);

} // namespace luramas::ir::cfg::helpers