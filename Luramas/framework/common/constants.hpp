#pragma once
#include "psuedo_keywords.hpp"
#include "types/generics.hpp"

/* INSTRUCTION VALUES */
static constexpr std::uint8_t LURAMAS_INST_LEN = 1U;                                                   /* IL instruction len */
static constexpr luramas_register LURAMAS_REGISTER_MAX = std::numeric_limits<luramas_register>::max(); /* Max register */
static constexpr luramas_address LURAMAS_ADDRESS_MAX = std::numeric_limits<luramas_address>::max();    /* Max dddress */
static constexpr luramas_register LURAMAS_REGISTER_NEXT_SPACE = 0xFF;                                  /* Space >= of unallocated registers */
static constexpr std::uint8_t LURAMAS_MAX_OPERANDS = 7U;                                               /* Max operands for IL */
static constexpr std::uint8_t LURAMAS_DEFAULT_LABEL = 128U;                                            /* Default label */

/* PREDICTION VALUES */
static constexpr std::uint8_t LURAMAS_PREDICTED_REGS = 5U;           /* Predicted registers in vector */
static constexpr std::uint8_t LURAMAS_PREDICTED_BLOCK_REGS = 35U;    /* Predicted regs per block */
static constexpr std::uint8_t LURAMAS_PREDICTED_FLAGS = 2U;          /* Predicted flags in vector */
static constexpr std::uint8_t LURAMAS_PREDICTED_FLAGS_PER_IR = 200U; /* Predicted flags per IR space */
static constexpr std::uint8_t LURAMAS_PREDICTED_EXPRS = 4U;          /* Predicted exprs in vector */
static constexpr std::uint8_t LURAMAS_PREDICTED_UPVALUES = 6U;       /* Predicted upvalues in vector */
static constexpr std::uint8_t LURAMAS_PREDICTED_VALUES = 7U;         /* Predicted values in vector */
static constexpr std::uint8_t LURAMAS_PREDICTED_RECURSION = 26U;     /* Predicted generic recursion */
static constexpr std::uint8_t LURAMAS_PREDICTED_ALL_EXPRS = 10U;     /* Predicted deep exprs in vector */
static constexpr std::uint8_t LURAMAS_PREDICTED_ALL_LVS = 5U;        /* Predicted L-values in vector */
static constexpr std::uint8_t LURAMAS_PREDICTED_ALL_RVS = 15U;       /* Predicted R-values in vector */

/* IL VALUES */
static constexpr std::uint8_t LURAMAS_IL_PREDICTED_RECURSION_AMOUNT = 10U; /* Predicted amount of recursion in IL */
static constexpr std::uint8_t LURAMAS_IR_DEFAULT_SEGREGATION_ID = 1U;      /* Predicted amount of recursion in IR */

/* IR VALUES */
static constexpr std::uint8_t LURAMAS_IR_DEFAULT_STACK_ID = 0U;             /* Default internal luramas stack ID */
static constexpr std::uint8_t LURAMAS_IR_MAX_STR_RENDER_SIZE = 150U;        /* 0 for no limit, Ignores a string if size is too big  */
static constexpr std::uint8_t LURAMAS_IR_COMPARATIVE_NON_OBJECT_TRUE = 1U;  /* Implicit true value compare */
static constexpr std::uint8_t LURAMAS_IR_COMPARATIVE_NON_OBJECT_FALSE = 0U; /* Implicit false value compare */
static constexpr luramas_address LURAMAS_IR_ENTRY = 0ULL;                   /* IR entry address*/
static constexpr luramas_address LURAMAS_IT_ENTRY = 0ULL;                   /* IL entry address*/

#define LURAMAS_IL_FS_EXTENSION ".lurail"
#define LURAMAS_IR_FS_EXTENSION ".lurair"
#define LURAMAS_PROFILE_FS_EXTENSION ".lurapf"

/* BRANCHING */
#define LURAMAS_PRETTY_BRANCH_INDENT "    "
#define LURAMAS_PRETTY_BRANCH_END "o-- "
#define LURAMAS_PRETTY_BRANCH_MID "+-- "
#define LURAMAS_PRETTY_BRANCH_VERTICLE "|   "