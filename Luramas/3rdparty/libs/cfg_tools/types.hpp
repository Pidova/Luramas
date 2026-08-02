#pragma once
#include <boost/container/vector.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/unordered/unordered_flat_map.hpp>
#include <boost/unordered/unordered_flat_set.hpp>
#include <cstdint>
#include <functional>
#include <type_traits>

namespace cfg_tools {

      namespace check {

            /* Default to false for any generic type */
            template <typename T>
            struct is_adjacency_list : std::false_type {};

            /* Partial specialization : Match boost::adjacency_list */
            template <typename OEL, typename VL, typename Dir, typename VP, typename EP, typename GP, typename EL>
            struct is_adjacency_list<boost::adjacency_list<OEL, VL, Dir, VP, EP, GP, EL>> : std::true_type {};

            /* Check if boost adjency list type */
            template <typename T>
            inline constexpr bool is_adjacency_list_v = is_adjacency_list<T>::value;
      } // namespace check

      /* Simple basic block, graph node */
      template <typename Graph>
      using basic_block = typename boost::graph_traits<Graph>::vertex_descriptor;

      /* Simple basic edge, graph edge */
      template <typename Graph>
      using basic_edge = typename boost::graph_traits<Graph>::edge_descriptor;

      /* Single-Entry (Internal do not count) Multiple(s)-Exit pair (Node with edge(s) comming to a node but can be abstracted out or grouped safely due to it having internal edges and node(s) with exit points) */
      template <typename Graph>
      using SEME = boost::unordered_flat_map<basic_block<Graph>, boost::container::vector<basic_block<Graph>>>;

      /* Given graph and node returns string representation of node */
      template <typename Graph>
      using cb_node_string = std::function<std::string(const Graph &, const basic_block<Graph> &)>;

} // namespace cfg_tools