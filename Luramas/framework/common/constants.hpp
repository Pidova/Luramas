#pragma once
#include "psuedo_keywords.hpp"
#include "types/generics.hpp"

/* INSTRUCTION VALUES */
static constexpr std::uint8_t LURAMAS_INST_LEN = 1u;                                                   /* IL instruction len */
static constexpr luramas_register LURAMAS_REGISTER_MAX = std::numeric_limits<luramas_register>::max(); /* Max register */
static constexpr luramas_address LURAMAS_ADDRESS_MAX = std::numeric_limits<luramas_address>::max();    /* Max dddress */
static constexpr luramas_register LURAMAS_REGISTER_NEXT_SPACE = 0xFF;                                  /* Space >= of unallocated registers */
static constexpr std::uint8_t LURAMAS_MAX_OPERANDS = 7u;                                               /* Max operands for IL */
static constexpr std::uint8_t LURAMAS_DEFAULT_LABEL = 128u;                                            /* Default label */

/* PREDICTION VALUES */
static constexpr std::uint8_t LURAMAS_PREDICTED_REGS = 5u;           /* Predicted registers in vector */
static constexpr std::uint8_t LURAMAS_PREDICTED_BLOCK_REGS = 35u;    /* Predicted regs per block */
static constexpr std::uint8_t LURAMAS_PREDICTED_FLAGS = 2u;          /* Predicted flags in vector */
static constexpr std::uint8_t LURAMAS_PREDICTED_FLAGS_PER_IR = 200u; /* Predicted flags per IR space */
static constexpr std::uint8_t LURAMAS_PREDICTED_EXPRS = 4u;          /* Predicted exprs in vector */
static constexpr std::uint8_t LURAMAS_PREDICTED_UPVALUES = 6u;       /* Predicted upvalues in vector */
static constexpr std::uint8_t LURAMAS_PREDICTED_VALUES = 7u;         /* Predicted values in vector */
static constexpr std::uint8_t LURAMAS_PREDICTED_RECURSION = 26u;     /* Predicted generic recursion */
static constexpr std::uint8_t LURAMAS_PREDICTED_ALL_EXPRS = 10u;     /* Predicted deep exprs in vector */
static constexpr std::uint8_t LURAMAS_PREDICTED_ALL_LVS = 5u;        /* Predicted L-values in vector */
static constexpr std::uint8_t LURAMAS_PREDICTED_ALL_RVS = 15u;       /* Predicted R-values in vector */

/* IL VALUES */
static constexpr std::uint8_t LURAMAS_IL_PREDICTED_RECURSION_AMOUNT = 10u; /* Predicted amount of recursion in IL */
static constexpr std::uint8_t LURAMAS_IR_DEFAULT_SEGREGATION_ID = 1u;      /* Predicted amount of recursion in IR */

/* IR VALUES */
static constexpr std::uint8_t LURAMAS_IR_DEFAULT_STACK_ID = 0u;             /* Default internal luramas stack ID */
static constexpr std::uint8_t LURAMAS_IR_MAX_STR_RENDER_SIZE = 150u;        /* 0 for no limit, Ignores a string if size is too big  */
static constexpr std::uint8_t LURAMAS_IR_COMPARATIVE_NON_OBJECT_TRUE = 1u;  /* Implicit true value compare */
static constexpr std::uint8_t LURAMAS_IR_COMPARATIVE_NON_OBJECT_FALSE = 0u; /* Implicit false value compare */
static constexpr luramas_address LURAMAS_IR_ENTRY = 0ull;                   /* IR entry address*/
static constexpr luramas_address LURAMAS_IT_ENTRY = 0ull;                   /* IL entry address*/

#define LURAMAS_IL_FS_EXTENSION ".lurail"
#define LURAMAS_IR_FS_EXTENSION ".lurair"
#define LURAMAS_PROFILE_FS_EXTENSION ".lurapf"

/* BRANCHING */
#define LURAMAS_PRETTY_BRANCH_INDENT "    "
#define LURAMAS_PRETTY_BRANCH_END "o-- "
#define LURAMAS_PRETTY_BRANCH_MID "+-- "
#define LURAMAS_PRETTY_BRANCH_VERTICLE "|   "