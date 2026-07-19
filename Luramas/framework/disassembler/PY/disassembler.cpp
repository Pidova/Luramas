#include "disassembler.hpp"
#include "optable.hpp"

enum class set_action : std::uint8_t {
      instruction, /* Sets all instruction info, op, mnenomic, hint. */
      operands     /* Sets all operands including details about it. */
};

template <set_action n>
void set_data(std::shared_ptr<luramas::disassembler::PY::disassembly> &buffer) {

      switch (n) {

            case set_action::instruction: {

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