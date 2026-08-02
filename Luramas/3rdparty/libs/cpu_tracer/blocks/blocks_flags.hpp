#include "../data/defs.hpp"

namespace cpu_tracer::blocks::flags {

      struct finsts {

            flag fbranching = false;         /* Is the instruction jump/call/return instruction? */
            flag fconditional_jump = false;  /* Is the instruction jump conditional? */
            flag fself_modified = false;     /* Was this self modified? */
            flag fexited = false;            /* Was this instruction not excuted but previous in the block was? */
            flag fexecuted = false;          /* Instruction executed? */
            flag ftaken_condbranch = false;  /* Conditonal branch taken? */
            flag fentry = false;             /* First instruction executed on 0 vcpu? */
            flag fref = false;               /* Does the only first operand reference jump? */
            flag fother_branch_edge = false; /* Given a branching instruction was an edge found other than to the next instruction? */

            finsts() = default;
            constexpr finsts(flag_storage &linked)
                : linked(&linked) {
                  this->unpack(linked);
                  return;
            }
            constexpr ~finsts() {
                  if (this->linked) {
                        *this->linked = this->pack();
                  }
                  return;
            }
            inline constexpr bool compare(const finsts &other) const {

                  return std::tie(this->fbranching, this->fconditional_jump, this->fself_modified, this->fexited, this->fexecuted, this->ftaken_condbranch, this->fentry, this->fref, this->fother_branch_edge) ==
                         std::tie(other.fbranching, other.fconditional_jump, other.fself_modified, other.fexited, other.fexecuted, other.ftaken_condbranch, other.fentry, other.fref, other.fother_branch_edge);
            }
            inline constexpr bool operator==(const finsts &other) const {
                  return this->compare(other);
            }
            inline constexpr bool operator!=(const finsts &other) const {
                  return !(*this == other);
            }
            inline constexpr flag_storage pack() const {
                  flag_storage result = 0u;
                  flag_storage shift = 0u;
                  result |= (static_cast<flag_storage>(this->fbranching) << shift++);
                  result |= (static_cast<flag_storage>(this->fconditional_jump) << shift++);
                  result |= (static_cast<flag_storage>(this->fself_modified) << shift++);
                  result |= (static_cast<flag_storage>(this->fexited) << shift++);
                  result |= (static_cast<flag_storage>(this->fexecuted) << shift++);
                  result |= (static_cast<flag_storage>(this->ftaken_condbranch) << shift++);
                  result |= (static_cast<flag_storage>(this->fentry) << shift++);
                  result |= (static_cast<flag_storage>(this->fref) << shift++);
                  result |= (static_cast<flag_storage>(this->fother_branch_edge) << shift++);
                  return result;
            }
            inline constexpr void unpack(const flag_storage packed) {
                  flag_storage shift = 0u;
                  this->fbranching = (packed >> shift++) & 1;
                  this->fconditional_jump = (packed >> shift++) & 1;
                  this->fself_modified = (packed >> shift++) & 1;
                  this->fexited = (packed >> shift++) & 1;
                  this->fexecuted = (packed >> shift++) & 1;
                  this->ftaken_condbranch = (packed >> shift++) & 1;
                  this->fentry = (packed >> shift++) & 1;
                  this->fref = (packed >> shift++) & 1;
                  this->fother_branch_edge = (packed >> shift++) & 1;
                  return;
            }
            inline constexpr void clone(const finsts &other) {
                  this->fbranching = other.fbranching;
                  this->fconditional_jump = other.fconditional_jump;
                  this->fself_modified = other.fself_modified;
                  this->fexited = other.fexited;
                  this->fexecuted = other.fexecuted;
                  this->ftaken_condbranch = other.ftaken_condbranch;
                  this->fentry = other.fentry;
                  this->fref = other.fref;
                  this->fother_branch_edge = other.fother_branch_edge;
                  return;
            }
            inline constexpr void clear() {
                  *this = finsts();
                  return;
            }

          private:
            flag_storage *linked = nullptr;
      };
      static_assert(sizeof(finsts) < sizeof(flag_storage) * 8u, "FINST must contain 32 or under 32 flags to change this please change combine type to higher bits.");
} // namespace cpu_tracer::blocks::flags
