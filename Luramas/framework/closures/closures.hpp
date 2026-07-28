#pragma once
#include "../common.hpp"
#include "../debug.hpp"
#include "../il/lexer/lexer.hpp"
#include "closures.hpp"
#include <algorithm>
#include <boost/pool/object_pool.hpp>
#include <boost/unordered/unordered_flat_map.hpp>
#include <boost/unordered/unordered_flat_set.hpp>
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>
#include <boostpp/flat_sets.hpp>
#include <inttypes.h>
#include <iostream>
#include <iterator>
#include <map>
#include <optional>
#include <ostream>
#include <ranges>
#include <set>
#include <tuple>
#include <variant>
#include <vector>

namespace luramas::closures {

      /* Wrap lex to help simplify things */
      struct node : std::enable_shared_from_this<node> {

            luramas_address address = 0u;           /* Address of lexed */
            std::shared_ptr<il::lexer::lexeme> lex; /* Linked lexed data */

            /* Extra information for flag instructions. */
            struct flags {

                  struct poparg_flag {

                        /* Pops args from stack for OP_CCALL. */
                        boost::unordered_flat_set<luramas_register> call_pop;
                        bool pop_call_dest = false;
                  } poparg_flag;

            } flags;

            /* Throws error with IL disassembly string */
            [[noreturn]] void error(const std::string &what) const;

            /* Extract all dest registers. (All registers that get overwritten, not only from "dest" operand) */
            luramas_registers extract_dest_regs();

            /* Extract all source registers. (All registers that get read but not overwritten, not only from "source" operand) */
            luramas_registers extract_source_regs();

            /* Prints out node */
            void dump(const char *const comment = nullptr) const;
      };

      /* Flags to how the closure should be processed */
      struct flags {
            luramas_flag fcarry_args = false;         /* Args are implicitly carried over to callee function? */
            luramas_flag fassociated_args = false;    /* Args are guaranteed to be in the registers of the callee?  */
            luramas_flag funknown_args = false;       /* Args need to be analyzed? */
            luramas_flag funknown_returns = false;    /* Returns need to be analyzed? */
            luramas_flag finclude_annotations = true; /* Includes annotations if avaliable? */
      };

      /* Type to wrap IL to help simplify analysis */
      class closure {

          public:
            flags flags; /* Flags related to closure */

            std::shared_ptr<luramas::il::ilang> il = nullptr;                     /* Linked IL */
            std::shared_ptr<luramas::il::program_memory> shared_memory = nullptr; /* Shared memory in the closure */

            std::vector<std::shared_ptr<node>> nodes;       /* Nodes/Instructions in the closure */
            std::vector<std::shared_ptr<closure>> closures; /* Child closures */

            /* String representation */
            std::string str() const;

            /* Prints representation string */
            void dump() const;

            /* Generates and prints C++ emitter code for the closure non-pseudo instructions, substituting register names using the provided map. */
            void extract(const boost::unordered_flat_map<luramas_register, std::string> &reg = boost::unordered_flat_map<luramas_register, std::string>()) const;

            /* Goes through IL and set closure flags based on what it finds */
            void set_flags();
      };

      /* Generate a closure given IL */
      std::shared_ptr<closure> gen_closure(std::shared_ptr<luramas::il::ilang> &il_data);

} // namespace luramas::closures