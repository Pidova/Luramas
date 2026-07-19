#pragma once
#include "../../generation.hpp"
#include "../cfg/compute.hpp"
#include "../cfg/iterate.hpp"
#include "../cfg/sort.hpp"

namespace luramas::ssa_builder {

      enum class kind : std::uint8_t {
            scalar, /* Singles */
            phi     /* Phis */
      };

      struct node {
            luramas_registers lvalues; /* Lvalues */
            luramas_registers rvalues; /* Rvalues */
            luramas_registers locals;  /* Values that are only local to current block */
      };
      struct ssa_rv_reg {

            luramas_flag fvalid = true;                      /* See if ssa value is valid (exists in the original), faster flagging it then removing it */
            luramas_flag fset_unknown = false;               /* Explicit set to be unknown? */
            kind k = kind::scalar;                           /* SSA kind */
            luramas_xregisters v;                            /* Values */
            boost::unordered_flat_set<luramas_xregister> uv; /* Unique values */

            operator bool() const;
      };
      struct ssa_node {
            boost::unordered_flat_map<luramas_register, luramas_xregister> lvalues; /* SSA versions of Lvalues */
            boost::unordered_flat_map<luramas_register, ssa_rv_reg> rvalues;        /* SSA versions of Rvalues */

            /* Misc */
            std::pair<luramas_flag, std::string> str() const;
      };

      std::vector<ssa_node> generate(const std::vector<node> &nodes, const generation::cfg::cfg &cfg);

      namespace tools {

            void global_version(std::vector<ssa_node> &buffer);
      }
} // namespace luramas::ssa_builder