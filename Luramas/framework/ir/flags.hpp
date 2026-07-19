#pragma once
#include "../il/il/il.hpp"

namespace luramas::ir::flags {

      struct ir_expr {

            luramas_flag fvirtualized = false;                                                         /* Is virtualized? (N contains function ID) */
            luramas_flag fsynthetic = false;                                                           /* Synthetic? */
            luramas_flag fimplicit_type = false;                                                       /* Values are the same resulting in redudant type, The underlying type variable will be defined out of cast. */
            il::arch::operand::upvalue_kind fcapture_kind = il::arch::operand::upvalue_kind::contents; /* Register is referenced during capture? */
            luramas_flag funsigned = false;                                                            /* Value is unsigned? */
            luramas_flag fvcall = false;                                                               /* Is virtual call? */
            luramas_flag fdeadset = false;                                                             /* Is deadset? */
            luramas_flag fconstant = false;                                                            /* Is constant? */
            luramas_flag fproduct_mulret = false;                                                      /* Is a product of mulret? */
            luramas_flag fcaptured = false;                                                            /* Is captured? */
            luramas_flag fbuiltin = false;                                                             /* Is luramas builtin? */
            luramas_flag fnative_global = false;                                                       /* Is luramas native global? */
            luramas_flag flegacy_page = false;                                                         /* Did stat used to be an associated with a page instruction? */
            luramas_flag fglobal_wild = false;                                                         /* Global is in representation of a non-global i.e. x data? */
            luramas_flag fsafe = false;                                                                /* Is expr safe from volatile/mutable side effects? */
            luramas_flag fglobal_user_defined = false;                                                 /* Did user define this global to an arbitrary concept i.e. !(1)? */
            luramas_flag fcall_internal_intrinsic = false;                                             /* Is expr a call to an internal intrinsic? */
            luramas_flag fexternal_page_goto = false;                                                  /* Is page goto/call/jump/etc external? */
            luramas_flag fpage_referenced_out_scope = false;                                           /* Is page referenced out of scope? */
            luramas_flag foptional = false;                                                            /* Is expr optional? */
            luramas_flag fglobal_library_linked = false;                                               /* If true the global library pointer will be in EV as a library member pointer. */

            inline constexpr bool compare(const ir_expr &other) const {

                  return std::tie(this->fvirtualized, this->fsynthetic, this->fimplicit_type, this->fcapture_kind, this->funsigned, this->fvcall, this->fdeadset, this->fconstant, this->fproduct_mulret, this->fcaptured, this->fbuiltin, this->fnative_global, this->flegacy_page, this->fglobal_wild, this->fsafe, this->fglobal_user_defined, this->fcall_internal_intrinsic, this->fexternal_page_goto, this->fpage_referenced_out_scope, this->foptional, this->fglobal_library_linked) ==
                         std::tie(other.fvirtualized, other.fsynthetic, other.fimplicit_type, other.fcapture_kind, other.funsigned, other.fvcall, other.fdeadset, other.fconstant, other.fproduct_mulret, other.fcaptured, other.fbuiltin, other.fnative_global, other.flegacy_page, other.fglobal_wild, other.fsafe, other.fglobal_user_defined, other.fcall_internal_intrinsic, other.fexternal_page_goto, other.fpage_referenced_out_scope, other.foptional, other.fglobal_library_linked);
            }
            inline constexpr bool operator==(const ir_expr &other) const {
                  return this->compare(other);
            }
            inline constexpr bool operator!=(const ir_expr &other) const {
                  return !(*this == other);
            }

            inline constexpr std::uint32_t pack() const {
                  std::uint32_t result = 0u;
                  std::uint32_t shift = 0u;
                  result |= (static_cast<std::uint32_t>(this->fvirtualized) << shift++);
                  result |= (static_cast<std::uint32_t>(this->fsynthetic) << shift++);
                  result |= (static_cast<std::uint32_t>(this->fimplicit_type) << shift++);
                  result |= (static_cast<std::uint32_t>(this->fcapture_kind) << shift++);
                  result |= (static_cast<std::uint32_t>(this->funsigned) << shift++);
                  result |= (static_cast<std::uint32_t>(this->fvcall) << shift++);
                  result |= (static_cast<std::uint32_t>(this->fdeadset) << shift++);
                  result |= (static_cast<std::uint32_t>(this->fconstant) << shift++);
                  result |= (static_cast<std::uint32_t>(this->fproduct_mulret) << shift++);
                  result |= (static_cast<std::uint32_t>(this->fcaptured) << shift++);
                  result |= (static_cast<std::uint32_t>(this->fbuiltin) << shift++);
                  result |= (static_cast<std::uint32_t>(this->flegacy_page) << shift++);
                  result |= (static_cast<std::uint32_t>(this->fglobal_wild) << shift++);
                  result |= (static_cast<std::uint32_t>(this->fsafe) << shift++);
                  result |= (static_cast<std::uint32_t>(this->fglobal_user_defined) << shift++);
                  result |= (static_cast<std::uint32_t>(this->fcall_internal_intrinsic) << shift++);
                  result |= (static_cast<std::uint32_t>(this->fexternal_page_goto) << shift++);
                  result |= (static_cast<std::uint32_t>(this->fpage_referenced_out_scope) << shift++);
                  result |= (static_cast<std::uint32_t>(this->foptional) << shift++);
                  result |= (static_cast<std::uint32_t>(this->fglobal_library_linked) << shift++);
                  return result;
            }
            inline constexpr void unpack(const std::uint32_t packed) {
                  std::uint32_t shift = 0u;
                  this->fvirtualized = (packed >> shift++) & 1;
                  this->fsynthetic = (packed >> shift++) & 1;
                  this->fimplicit_type = (packed >> shift++) & 1;
                  this->fcapture_kind = static_cast<luramas::il::arch::operand::upvalue_kind>((packed >> shift++) & 1);
                  this->funsigned = (packed >> shift++) & 1;
                  this->fvcall = (packed >> shift++) & 1;
                  this->fdeadset = (packed >> shift++) & 1;
                  this->fconstant = (packed >> shift++) & 1;
                  this->fproduct_mulret = (packed >> shift++) & 1;
                  this->fcaptured = (packed >> shift++) & 1;
                  this->fbuiltin = (packed >> shift++) & 1;
                  this->flegacy_page = (packed >> shift++) & 1;
                  this->fglobal_wild = (packed >> shift++) & 1;
                  this->fsafe = (packed >> shift++) & 1;
                  this->fglobal_user_defined = (packed >> shift++) & 1;
                  this->fcall_internal_intrinsic = (packed >> shift++) & 1;
                  this->fexternal_page_goto = (packed >> shift++) & 1;
                  this->fpage_referenced_out_scope = (packed >> shift++) & 1;
                  this->foptional = (packed >> shift++) & 1;
                  this->fglobal_library_linked = (packed >> shift++) & 1;
                  return;
            }
            inline constexpr void clone(const ir_expr &other) {
                  this->fvirtualized = other.fvirtualized;
                  this->fsynthetic = other.fsynthetic;
                  this->fimplicit_type = other.fimplicit_type;
                  this->fcapture_kind = other.fcapture_kind;
                  this->funsigned = other.funsigned;
                  this->fvcall = other.fvcall;
                  this->fdeadset = other.fdeadset;
                  this->fconstant = other.fconstant;
                  this->fproduct_mulret = other.fproduct_mulret;
                  this->fcaptured = other.fcaptured;
                  this->fbuiltin = other.fbuiltin;
                  this->flegacy_page = other.flegacy_page;
                  this->fglobal_wild = other.fglobal_wild;
                  this->fsafe = other.fsafe;
                  this->fglobal_user_defined = other.fglobal_user_defined;
                  this->fcall_internal_intrinsic = other.fcall_internal_intrinsic;
                  this->fexternal_page_goto = other.fexternal_page_goto;
                  this->fpage_referenced_out_scope = other.fpage_referenced_out_scope;
                  this->foptional = other.foptional;
                  this->fglobal_library_linked = other.fglobal_library_linked;
                  return;
            }
            inline constexpr void clear() {
                  *this = ir_expr();
                  return;
            }
      };
      static_assert(sizeof(ir_expr) < sizeof(std::uint32_t) * 8u, "IR-EXPR must contain 32 or under 32 flags to change this please change combine type to higher bits.");

      struct ir_stat {

            luramas_flag funsafe = false;                       /* Stat always unsafe? */
            luramas_flag fdynamic = false;                      /* Stat is dynamic? (Means stat needs further analysys i.e. return with unkown results) */
            luramas_flag fvirtualized = false;                  /* Is virtualized? */
            luramas_flag funsigned = false;                     /* Value is unsigned? */
            luramas_flag fsynthetic = false;                    /* Is synthetic? */
            luramas_flag fflagable = false;                     /* Is flagable? */
            luramas_flag fdefine = false;                       /* Is defined? */
            luramas_flag fvolatile = false;                     /* Is volatile keyword? */
            luramas_flag fvariadic_def = false;                 /* Is variadic definition? */
            luramas_flag fnoreturn = false;                     /* Call has no return? */
            luramas_flag freconstructed_inlined = false;        /* Was inlined function reconstructed? */
            luramas_flag fimmutable = false;                    /* Stat can be changed? */
            luramas_flag fexpanded_non_direct_cft = false;      /* Was stat expanded from a non direct control flow transfer? */
            luramas_flag funknown_paging = false;               /* Is paging args or results are unknown (only member will be page id)? */
            luramas_flag fbuiltin = false;                      /* Is luramas builtin? */
            luramas_flag fatomic = false;                       /* Is atomic sensitive?  */
            luramas_flag flegacy_page = false;                  /* Did stat used to be an associated with a page instruction? */
            luramas_flag fpage_keyword = false;                 /* Keyword is apart of page? */
            luramas_flag fpage_export = false;                  /* Page exported? */
            luramas_flag flink_regs = false;                    /* Can keyword abstractly link registers that may not be liked i.e. (definition, return) */
            luramas_flag fend_main_page = false;                /* Is stat the end of the main closure? (Only active is pages are present) */
            luramas_flag fsafe = false;                         /* Is stat safe from volatile/mutable side effects? */
            luramas_flag fexternal_page_goto = false;           /* Is page goto/call/jump/etc external? */
            luramas_flag finternal_store = false;               /* Is stat an internal store? */
            luramas_flag fdead_sideeffects = false;             /* The stat is dead but could contain side effects */
            luramas_flag fpage_referenced_out_scope = false;    /* Is page referenced out of scope? */
            luramas_flag fpage_seperator = false;               /* Goto ?? label used ot seperate page data */
            luramas_flag fpage_main = false;                    /* Main page? */
            luramas_flag fdef_uses_controller = false;          /* Definition uses controller? */
            luramas_flag fpage_seperated = false;               /* Was page seperated? */
            luramas_flag fpage_call_internally_managed = false; /* Will page call go to next instruction? */

            inline constexpr bool compare(const ir_stat &other) const {

                  return std::tie(this->funsafe, this->fdynamic, this->fvirtualized, this->funsigned, this->fsynthetic, this->fflagable, this->fdefine, this->fvolatile, this->fvariadic_def, this->fnoreturn, this->freconstructed_inlined, this->fimmutable, this->fexpanded_non_direct_cft, this->funknown_paging, this->fbuiltin, this->fatomic, this->flegacy_page, this->fpage_keyword, this->fpage_export, this->flink_regs, this->fend_main_page, this->fsafe, this->fexternal_page_goto, this->finternal_store, this->fdead_sideeffects, this->fpage_referenced_out_scope, this->fpage_seperator, this->fpage_main, this->fdef_uses_controller, this->fpage_seperated, this->fpage_call_internally_managed) ==
                         std::tie(other.funsafe, other.fdynamic, other.fvirtualized, other.funsigned, other.fsynthetic, other.fflagable, other.fdefine, other.fvolatile, other.fvariadic_def, other.fnoreturn, other.freconstructed_inlined, other.fimmutable, other.fexpanded_non_direct_cft, other.funknown_paging, other.fbuiltin, other.fatomic, other.flegacy_page, other.fpage_keyword, other.fpage_export, other.flink_regs, other.fend_main_page, other.fsafe, other.fexternal_page_goto, other.finternal_store, other.fdead_sideeffects, other.fpage_referenced_out_scope, other.fpage_seperator, other.fpage_main, other.fdef_uses_controller, other.fpage_seperated, other.fpage_call_internally_managed);
            }
            inline constexpr bool operator==(const ir_stat &other) const {
                  return this->compare(other);
            }
            inline constexpr bool operator!=(const ir_stat &other) const {
                  return !(*this == other);
            }

            inline constexpr std::uint32_t pack() const {
                  std::uint32_t result = 0u;
                  std::uint32_t shift = 0u;
                  result |= (static_cast<std::uint32_t>(this->funsafe) << shift++);
                  result |= (static_cast<std::uint32_t>(this->fdynamic) << shift++);
                  result |= (static_cast<std::uint32_t>(this->fvirtualized) << shift++);
                  result |= (static_cast<std::uint32_t>(this->funsigned) << shift++);
                  result |= (static_cast<std::uint32_t>(this->fsynthetic) << shift++);
                  result |= (static_cast<std::uint32_t>(this->fflagable) << shift++);
                  result |= (static_cast<std::uint32_t>(this->fdefine) << shift++);
                  result |= (static_cast<std::uint32_t>(this->fvolatile) << shift++);
                  result |= (static_cast<std::uint32_t>(this->fvariadic_def) << shift++);
                  result |= (static_cast<std::uint32_t>(this->fnoreturn) << shift++);
                  result |= (static_cast<std::uint32_t>(this->freconstructed_inlined) << shift++);
                  result |= (static_cast<std::uint32_t>(this->fimmutable) << shift++);
                  result |= (static_cast<std::uint32_t>(this->fexpanded_non_direct_cft) << shift++);
                  result |= (static_cast<std::uint32_t>(this->funknown_paging) << shift++);
                  result |= (static_cast<std::uint32_t>(this->fbuiltin) << shift++);
                  result |= (static_cast<std::uint32_t>(this->fatomic) << shift++);
                  result |= (static_cast<std::uint32_t>(this->flegacy_page) << shift++);
                  result |= (static_cast<std::uint32_t>(this->fpage_keyword) << shift++);
                  result |= (static_cast<std::uint32_t>(this->fpage_export) << shift++);
                  result |= (static_cast<std::uint32_t>(this->flink_regs) << shift++);
                  result |= (static_cast<std::uint32_t>(this->fend_main_page) << shift++);
                  result |= (static_cast<std::uint32_t>(this->fsafe) << shift++);
                  result |= (static_cast<std::uint32_t>(this->fexternal_page_goto) << shift++);
                  result |= (static_cast<std::uint32_t>(this->finternal_store) << shift++);
                  result |= (static_cast<std::uint32_t>(this->fdead_sideeffects) << shift++);
                  result |= (static_cast<std::uint32_t>(this->fpage_referenced_out_scope) << shift++);
                  result |= (static_cast<std::uint32_t>(this->fpage_seperator) << shift++);
                  result |= (static_cast<std::uint32_t>(this->fpage_main) << shift++);
                  result |= (static_cast<std::uint32_t>(this->fdef_uses_controller) << shift++);
                  result |= (static_cast<std::uint32_t>(this->fpage_seperated) << shift++);
                  result |= (static_cast<std::uint32_t>(this->fpage_call_internally_managed) << shift++);
                  return result;
            }
            inline constexpr void unpack(const std::uint32_t packed) {
                  std::uint32_t shift = 0u;
                  this->funsafe = (packed >> shift++) & 1;
                  this->fdynamic = (packed >> shift++) & 1;
                  this->fvirtualized = (packed >> shift++) & 1;
                  this->funsigned = (packed >> shift++) & 1;
                  this->fsynthetic = (packed >> shift++) & 1;
                  this->fflagable = (packed >> shift++) & 1;
                  this->fdefine = (packed >> shift++) & 1;
                  this->fvolatile = (packed >> shift++) & 1;
                  this->fvariadic_def = (packed >> shift++) & 1;
                  this->fnoreturn = (packed >> shift++) & 1;
                  this->freconstructed_inlined = (packed >> shift++) & 1;
                  this->fimmutable = (packed >> shift++) & 1;
                  this->fexpanded_non_direct_cft = (packed >> shift++) & 1;
                  this->funknown_paging = (packed >> shift++) & 1;
                  this->fbuiltin = (packed >> shift++) & 1;
                  this->fatomic = (packed >> shift++) & 1;
                  this->flegacy_page = (packed >> shift++) & 1;
                  this->fpage_keyword = (packed >> shift++) & 1;
                  this->fpage_export = (packed >> shift++) & 1;
                  this->flink_regs = (packed >> shift++) & 1;
                  this->fend_main_page = (packed >> shift++) & 1;
                  this->fsafe = (packed >> shift++) & 1;
                  this->fexternal_page_goto = (packed >> shift++) & 1;
                  this->finternal_store = (packed >> shift++) & 1;
                  this->fdead_sideeffects = (packed >> shift++) & 1;
                  this->fpage_referenced_out_scope = (packed >> shift++) & 1;
                  this->fpage_seperator = (packed >> shift++) & 1;
                  this->fpage_main = (packed >> shift++) & 1;
                  this->fdef_uses_controller = (packed >> shift++) & 1;
                  this->fpage_seperated = (packed >> shift++) & 1;
                  this->fpage_call_internally_managed = (packed >> shift++) & 1;
                  return;
            }
            inline constexpr void clone(const ir_stat &other) {
                  this->funsafe = other.funsafe;
                  this->fdynamic = other.fdynamic;
                  this->fvirtualized = other.fvirtualized;
                  this->funsigned = other.funsigned;
                  this->fsynthetic = other.fsynthetic;
                  this->fflagable = other.fflagable;
                  this->fdefine = other.fdefine;
                  this->fvolatile = other.fvolatile;
                  this->fvariadic_def = other.fvariadic_def;
                  this->fnoreturn = other.fnoreturn;
                  this->freconstructed_inlined = other.freconstructed_inlined;
                  this->fimmutable = other.fimmutable;
                  this->fexpanded_non_direct_cft = other.fexpanded_non_direct_cft;
                  this->funknown_paging = other.funknown_paging;
                  this->fbuiltin = other.fbuiltin;
                  this->fatomic = other.fatomic;
                  this->flegacy_page = other.flegacy_page;
                  this->fpage_keyword = other.fpage_keyword;
                  this->fpage_export = other.fpage_export;
                  this->flink_regs = other.flink_regs;
                  this->fend_main_page = other.fend_main_page;
                  this->fsafe = other.fsafe;
                  this->fexternal_page_goto = other.fexternal_page_goto;
                  this->finternal_store = other.finternal_store;
                  this->fdead_sideeffects = other.fdead_sideeffects;
                  this->fpage_referenced_out_scope = other.fpage_referenced_out_scope;
                  this->fpage_seperator = other.fpage_seperator;
                  this->fpage_main = other.fpage_main;
                  this->fdef_uses_controller = other.fdef_uses_controller;
                  this->fpage_seperated = other.fpage_seperated;
                  this->fpage_call_internally_managed = other.fpage_call_internally_managed;
                  return;
            }
            inline constexpr void clear() {
                  *this = ir_stat();
                  return;
            }
      };
      static_assert(sizeof(ir_stat) < sizeof(std::uint32_t) * 8u, "IR-STAT must contain 32 or under 32 flags to change this please change combine type to higher bits.");

} // namespace luramas::ir::flags