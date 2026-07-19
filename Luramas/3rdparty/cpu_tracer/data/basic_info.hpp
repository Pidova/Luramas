#pragma once
#include "../boostpp/vector.hpp"
#include "defs.hpp"
#include "io.hpp"

namespace cpu_tracer::basic_info {

      /* Basic instruction data */
      template <std::uint8_t MAX_LEN>
      struct inst {

            flag fvalid_prev_real_pc = true; /* Is prev_real_pc valid? */
            address pc = 0u;                 /* Virtual pc */
            address real_pc = 0u;            /* Logical pc */
            address prev_real_pc = 0u;       /* Previous logical PC */
            std::uint8_t vcpu = 0u;          /* Virtual CPU it got executed on */
            inst_bytes<MAX_LEN> bytes;       /* Bytes */

            /* Contains bytes? */
            inline bool contains(const inst_bytes<MAX_LEN> &b) const {

                  return b.size() <= this->bytes.size() && std::equal(b.begin(), b.end(), this->bytes.data());
            }

            /* Read/Write */
            inline bool read(std::ifstream &ifs) {

                  if (!ifs.is_open() || !ifs.good()) {
                        return false;
                  }
                  io::read(ifs, this->fvalid_prev_real_pc, this->pc, this->real_pc, this->prev_real_pc, this->vcpu);
                  io::readv(ifs, this->bytes);
                  return ifs.good();
            }
            inline bool write(std::ofstream &ofs) const {

                  if (!ofs.is_open() || !ofs.good()) {
                        return false;
                  }
                  io::write(ofs, this->fvalid_prev_real_pc, this->pc, this->real_pc, this->prev_real_pc, this->vcpu);
                  io::writev(ofs, this->bytes);
                  return ofs.good();
            }
      };
} // namespace cpu_tracer::basic_info