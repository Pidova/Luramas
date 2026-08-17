#include "disassembler.hpp"
#include "optable.hpp"

enum class set_action : std::uint8_t {
      INSTRUCTION, /* Sets all instruction info, op, mnenomic, hint. */
      OPERANDS     /* Sets all operands including details about it. */
};

template <set_action N>
static void set_data(std::shared_ptr<luramas::disassembler::PY::disassembly> &buffer) {

      switch (N) {

            case set_action::INSTRUCTION: {

                  // TODO ADD OPTABLE INDEXING

                  switch (buffer->op) {

                        default: {
                              break;
                        }
                  }
                  break;
            }
      }
      return;
}