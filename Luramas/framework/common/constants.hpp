#pragma once
#include "psuedo_keywords.hpp"
#include "types/generics.hpp"

/* VERSION */
#define LURAMAS_MAJOR "6"
#define LURAMAS_MINOR "00"
#define LURAMAS_PATCH "a"
#define LURAMAS_VERSION LURAMAS_MAJOR "." LURAMAS_MINOR LURAMAS_PATCH
#define LURAMAS_COMMENT "Decompiled with Prismatic: discord.gg/Jxh7nwyYga"

/* INSTRUCTION VALUES */
static constexpr std::uint8_t LURAMAS_INST_LEN = 1u;
static constexpr luramas_register LURAMAS_REGISTER_MAX = std::numeric_limits<luramas_register>::max();
static constexpr luramas_address LURAMAS_ADDRESS_MAX = std::numeric_limits<luramas_address>::max();
static constexpr luramas_register LURAMAS_REGISTER_NEXT_SPACE = 0xFF;
static constexpr std::uint8_t LURAMAS_MAX_OPERANDS = 7u;
static constexpr std::uint8_t LURAMAS_DEFAULT_LABEL = 128u;

/* PREDICTION VALUES */
static constexpr std::uint8_t LURAMAS_PREDICTED_REGS = 5u;
static constexpr std::uint8_t LURAMAS_PREDICTED_BLOCK_REGS = 35u;
static constexpr std::uint8_t LURAMAS_PREDICTED_FLAGS = 2u;
static constexpr std::uint8_t LURAMAS_PREDICTED_FLAGS_PER_IR = 200u;
static constexpr std::uint8_t LURAMAS_PREDICTED_EXPRS = 4u;
static constexpr std::uint8_t LURAMAS_PREDICTED_UPVALUES = 6u;
static constexpr std::uint8_t LURAMAS_PREDICTED_VALUES = 7u;
static constexpr std::uint8_t LURAMAS_PREDICTED_RECURSION = 26u;
static constexpr std::uint8_t LURAMAS_PREDICTED_ALL_EXPRS = 10u;
static constexpr std::uint8_t LURAMAS_PREDICTED_ALL_LVS = 5u;
static constexpr std::uint8_t LURAMAS_PREDICTED_ALL_RVS = 15u;
static constexpr std::uint8_t LURAMAS_PREDICTED_ALL_EXPRSV = 16u;

/* IL VALUES */
static constexpr std::uint8_t LURAMAS_IL_PREDICTED_RECURSION_AMOUNT = 10u;
static constexpr std::uint8_t LURAMAS_IR_DEFAULT_SEGREGATION_ID = 1u;

/* IR VALUES */
static constexpr std::uint8_t LURAMAS_IR_DEFAULT_STACK_ID = 0u;
static constexpr std::uint8_t LURAMAS_IR_OBJECT_MAX_INIT = 8u;
static constexpr std::uint8_t LURAMAS_IR_SIMPLE_EXPR_LVALUES = 1u;
static constexpr std::uint8_t LURAMAS_IR_SIMPLE_EXPR_RVALUES = 3u;
static constexpr std::uint8_t LURAMAS_IR_SIMPLE_EXPR_EXPRS = LURAMAS_IR_SIMPLE_EXPR_LVALUES + LURAMAS_IR_SIMPLE_EXPR_RVALUES;
static constexpr std::uint8_t LURAMAS_IR_SIMPLE_STAT_LVALUES = 2u;
static constexpr std::uint8_t LURAMAS_IR_SIMPLE_STAT_RVALUES = 2u;
static constexpr std::uint8_t LURAMAS_IR_SIMPLE_STAT_EXPRS = LURAMAS_IR_SIMPLE_STAT_LVALUES + LURAMAS_IR_SIMPLE_STAT_RVALUES;
static constexpr std::uint8_t LURAMAS_IR_MAX_STR_RENDER_SIZE = 150u; /* 0 for no limit */
static constexpr std::uint8_t LURAMAS_IR_COMPARATIVE_NON_OBJECT_TRUE = 1u;
static constexpr std::uint8_t LURAMAS_IR_COMPARATIVE_NON_OBJECT_FALSE = 0u;
static constexpr std::uint64_t LURAMAS_IR_ENTRY = 0ull;
static constexpr std::uint64_t LURAMAS_IT_ENTRY = 0ull;

#define LURAMAS_IL_FS_EXTENSION ".lurail"
#define LURAMAS_IR_FS_EXTENSION ".lurair"
#define LURAMAS_PROFILE_FS_EXTENSION ".lurapf"

/* HASHING */
static constexpr std::uint64_t LURAMAS_GOLDEN_RATIO_32 = 0x9e3779b9;
static constexpr std::uint64_t LURAMAS_GOLDEN_RATIO_64 = 0x9e3779b97f4a7c16;

/* BRANCHING */
#define LURAMAS_PRETTY_BRANCH_INDENT "    "
#define LURAMAS_PRETTY_BRANCH_END "o-- "
#define LURAMAS_PRETTY_BRANCH_MID "+-- "
#define LURAMAS_PRETTY_BRANCH_VERTICLE "|   "