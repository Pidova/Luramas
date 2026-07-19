#pragma once
#include "../../common/common.hpp"

namespace luramas::ir::execution {

      namespace errors {

            enum class kinds : std::uint16_t {

                  none, /* No error */

                  /* Arithmetic Errors */
                  arithmetic_on_non_valid,              /* Attempted to perform arithmetic on a type that can not perform arithmetic */
                  arithmetic_on_non_arithmetic_binkind, /* Attempted to perform arithmetic with a non arithmetic binkind */
                  division_by_zero,                     /* Division by zero occurred */
                  invalid_unary_operand,                /* Invalid operand for unary operation */
                  invalid_unary_kind,                   /* Invalid kind for unary operation */

                  /* Logical / Conditional Errors */
                  invalid_condition_type,           /* Condition does not evaluate to a boolean-compatible value */
                  ternary_type_mismatch,            /* Ternary branches result in incompatible types */
                  comparison_on_incompatible_types, /* Comparative operation on types that cannot be compared */
                  comparative_on_different_objects, /* Compared two different object types */
                  invalid_logical_negation,         /* Logical NOT applied to invalid type */

                  /* Indexing / Access Errors */
                  index_on_non_table,          /* Attempted to index a non-table object */
                  index_out_of_bounds,         /* Index exceeded bounds of array-like object */
                  invalid_index_type,          /* Invalid type used for indexing (e.g., function or nil) */
                  read_from_undefined_index,   /* Read from an index that has not been defined */
                  assignment_to_non_indexable, /* Attempted to assign to an object that is not indexable */

                  /* Memory / Stack Errors */
                  read_from_null_pointer,  /* Attempted to read from a null memory location */
                  write_to_null_pointer,   /* Attempted to write to a null memory location */
                  invalid_memory_cast,     /* Invalid cast to memory type */
                  invalid_stack_read_type, /* Stack read attempted with invalid type */
                  stack_underflow,         /* Attempted to pop from empty stack */
                  stack_overflow,          /* Stack exceeded maximum depth */
                  stack_read_overflow,     /* Stack read attempted beyond current stack size */

                  /* Control Flow Errors */
                  invalid_jump_target,           /* Jump to non-existent or invalid block */
                  invalid_label_target,          /* Goto to undefined label */
                  end_without_loop_or_condition, /* End encountered without matching condition or loop */
                  repeat_without_until,          /* Repeat block missing terminating until */
                  break_outside_loop,            /* Break statement not inside loop */
                  continue_outside_loop,         /* Continue statement not inside loop */
                  unmatched_switch_case,         /* Case not within a switch */
                  duplicate_switch_default,      /* Multiple default branches in one switch */

                  /* Call / Function / Closure Errors */
                  call_on_non_callable,      /* Attempted to call a value that is not a function or callable closure */
                  call_on_nil,               /* Attempted to call nil */
                  invalid_closure_reference, /* Closure refers to invalid or missing environment */
                  missing_function_return,   /* Function did not return a value when one was expected */
                  stack_frame_corruption,    /* Detected corruption in call stack frame */
                  closure_env_mismatch,      /* Closure captured mismatched environment variables */

                  /* Table / Object / Type Errors */
                  set_on_constant,             /* Attempted to assign to a constant value */
                  access_on_nil,               /* Attempted to access a field of nil */
                  mutation_on_non_mutable,     /* Attempted to mutate a non-mutable type */
                  unpack_non_iterable,         /* Attempted to unpack a non-iterable type */
                  reference_to_invalid_object, /* Reference points to invalid or deleted object */

                  /* Meta Errors / Flags / Isolation */
                  set_flag_on_invalid_id,  /* Attempted to set a flag with an invalid ID */
                  isolate_on_empty_block,  /* Isolation on empty or non-executable block */
                  invalid_metadata_format, /* Metadata tag has incorrect format or type */
                  tag_mismatch,            /* Tag start and end mismatch or unclosed */

                  /* Upvalue / Register / Global Errors */
                  upvalue_not_found,            /* Upvalue does not exist in current closure */
                  register_access_out_of_scope, /* Register access beyond its valid scope */
                  global_not_defined,           /* Global accessed but not defined */
                  invalid_register_kind,        /* Register kind does not match operation */

                  /* General Semantic Errors */
                  type_cast_failed,           /* Cast to target type failed */
                  undefined_behavior,         /* Reached undefined behavior in execution */
                  unreachable_code_executed,  /* Code marked unreachable was executed */
                  closure_escape_invalid,     /* Closure captured temporary or invalid object */
                  operation_on_amount_kind,   /* Attempted operation on amount pseudo-kind */
                  lvalue_expected,            /* Expression is not a valid L-value for assignment */
                  implicit_conversion_failed, /* Implicit conversion between types failed */

                  /* Assignment errors */
                  assign_invalid_lvalue,   /* Value could not be assign to */
                  assign_invalid_constant, /* Assigned to an constant value */
                  assign_invalid_rvalue,   /* Could not use value in rvalue */

                  /* Misc */
                  null_pointer, /* Pointer is null */

                  amount /* Amount */
            };

            /* Get what string from kind */
            const char *const what(const kinds k);
      } // namespace errors

      struct environment_flags {

            luramas_flag fnative_objects = false;    /* Are native values objects or underlying values? */
            luramas_flag fprimitive_objects = false; /* Are primitives objects? */

            /* Arith */
            luramas_flag farithmetic_nan_zero = false; /* Default NaN to zero or error?  */

            /* Condition */
            luramas_flag fcondition_mismatch = false;       /* Can conditions mismatch?  */
            luramas_flag fcondition_string_int = false;     /* Can ints compare against string types? */
            luramas_flag fcondition_string_boolean = false; /* Can booleans compare against string types? */
            luramas_flag fcondition_int_boolean = false;    /* Can ints compare against boolean types? */

            /* Unaries */
            luramas_flag funary_len_int = false;    /* Can use unary len on integral? */
            luramas_flag funary_len_string = false; /* Can use unary len on string? */
            luramas_flag funary_not_int = false;    /* Can use unary not on integral? */
      };

      template <errors::kinds k, typename T>
      inline void exe_error(error::result<T, errors::kinds> &res) {
            res.h.emit(k, errors::what(k));
            return;
      }
} // namespace luramas::ir::execution