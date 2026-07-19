#include "../data.hpp"

namespace luramas::ir::execution::errors {

      const char *const what(const kinds k) {
            switch (k) {
                  case kinds::none: {
                        return "No error";
                  }

                  /* Arithmetic Errors */
                  case kinds::arithmetic_on_non_valid: {
                        return "Attempted to perform arithmetic on a type that can not perform arithmetic";
                  }
                  case kinds::arithmetic_on_non_arithmetic_binkind: {
                        return "Attempted to perform arithmetic with a non arithmetic binkind";
                  }
                  case kinds::division_by_zero: {
                        return "Division by zero occurred";
                  }
                  case kinds::invalid_unary_operand: {
                        return "Invalid operand for unary operation";
                  }
                  case kinds::invalid_unary_kind: {
                        return "Invalid unary kind";
                  }

                  /* Logical / Conditional Errors */
                  case kinds::invalid_condition_type: {
                        return "Condition does not evaluate to a boolean-compatible value";
                  }
                  case kinds::ternary_type_mismatch: {
                        return "Ternary branches result in incompatible types";
                  }
                  case kinds::comparison_on_incompatible_types: {
                        return "Comparative operation on types that cannot be compared";
                  }
                  case kinds::comparative_on_different_objects: {
                        return "Compared two different object types";
                  }
                  case kinds::invalid_logical_negation: {
                        return "Logical NOT applied to invalid type";
                  }

                  /* Indexing / Access Errors */
                  case kinds::index_on_non_table: {
                        return "Attempted to index a non-table object";
                  }
                  case kinds::index_out_of_bounds: {
                        return "Index exceeded bounds of array-like object";
                  }
                  case kinds::invalid_index_type: {
                        return "Invalid type used for indexing";
                  }
                  case kinds::read_from_undefined_index: {
                        return "Read from an index that has not been defined";
                  }
                  case kinds::assignment_to_non_indexable: {
                        return "Attempted to assign to an object that is not indexable";
                  }

                        /* Memory / Stack Errors */
                  case kinds::read_from_null_pointer: {
                        return "Attempted to read from a null memory location";
                  }
                  case kinds::write_to_null_pointer: {
                        return "Attempted to write to a null memory location";
                  }
                  case kinds::invalid_memory_cast: {
                        return "Invalid cast to memory type";
                  }
                  case kinds::invalid_stack_read_type: {
                        return "Stack read attempted with invalid type";
                  }
                  case kinds::stack_underflow: {
                        return "Attempted to pop from empty stack";
                  }
                  case kinds::stack_overflow: {
                        return "Stack exceeded maximum depth";
                  }
                  case kinds::stack_read_overflow: {
                        return "Stack read attempted beyond current stack size";
                  }

                        /* Control Flow Errors */
                  case kinds::invalid_jump_target: {
                        return "Jump to non-existent or invalid block";
                  }
                  case kinds::invalid_label_target: {
                        return "Goto to undefined label";
                  }
                  case kinds::end_without_loop_or_condition: {
                        return "End encountered without matching condition or loop";
                  }
                  case kinds::repeat_without_until: {
                        return "Repeat block missing terminating until";
                  }
                  case kinds::break_outside_loop: {
                        return "Break statement not inside loop";
                  }
                  case kinds::continue_outside_loop: {
                        return "Continue statement not inside loop";
                  }
                  case kinds::unmatched_switch_case: {
                        return "Case not within a switch";
                  }
                  case kinds::duplicate_switch_default: {
                        return "Multiple default branches in one switch";
                  }

                        /* Call / Function / Closure Errors */
                  case kinds::call_on_non_callable: {
                        return "Attempted to call a value that is not a function or callable closure";
                  }
                  case kinds::call_on_nil: {
                        return "Attempted to call nil";
                  }
                  case kinds::invalid_closure_reference: {
                        return "Closure refers to invalid or missing environment";
                  }
                  case kinds::missing_function_return: {
                        return "Function did not return a value when one was expected";
                  }
                  case kinds::stack_frame_corruption: {
                        return "Detected corruption in call stack frame";
                  }
                  case kinds::closure_env_mismatch: {
                        return "Closure captured mismatched environment variables";
                  }

                        /* Table / Object / Type Errors */
                  case kinds::set_on_constant: {
                        return "Attempted to assign to a constant value";
                  }
                  case kinds::access_on_nil: {
                        return "Attempted to access a field of nil";
                  }
                  case kinds::mutation_on_non_mutable: {
                        return "Attempted to mutate a non-mutable type";
                  }
                  case kinds::unpack_non_iterable: {
                        return "Attempted to unpack a non-iterable type";
                  }
                  case kinds::reference_to_invalid_object: {
                        return "Reference points to invalid or deleted object";
                  }

                        /* Meta Errors / Flags / Isolation */
                  case kinds::set_flag_on_invalid_id: {
                        return "Attempted to set a flag with an invalid ID";
                  }
                  case kinds::isolate_on_empty_block: {
                        return "Isolation on empty or non-executable block";
                  }
                  case kinds::invalid_metadata_format: {
                        return "Metadata tag has incorrect format or type";
                  }
                  case kinds::tag_mismatch: {
                        return "Tag start and end mismatch or unclosed";
                  }

                        /* Upvalue / Register / Global Errors */
                  case kinds::upvalue_not_found: {
                        return "Upvalue does not exist in current closure";
                  }
                  case kinds::register_access_out_of_scope: {
                        return "Register access beyond its valid scope";
                  }
                  case kinds::global_not_defined: {
                        return "Global accessed but not defined";
                  }
                  case kinds::invalid_register_kind: {
                        return "Register kind does not match operation";
                  }

                        /* General Semantic Errors */
                  case kinds::type_cast_failed: {
                        return "Cast to target type failed";
                  }
                  case kinds::undefined_behavior: {
                        return "Reached undefined behavior in execution";
                  }
                  case kinds::unreachable_code_executed: {
                        return "Code marked unreachable was executed";
                  }
                  case kinds::closure_escape_invalid: {
                        return "Closure captured temporary or invalid object";
                  }
                  case kinds::operation_on_amount_kind: {
                        return "Attempted operation on amount pseudo-kind";
                  }
                  case kinds::lvalue_expected: {
                        return "Expression is not a valid L-value for assignment";
                  }
                  case kinds::implicit_conversion_failed: {
                        return "Implicit conversion between types failed";
                  }

                        /* Assignment errors */
                  case kinds::assign_invalid_lvalue: {
                        return "Cannot assign to value";
                  }
                  case kinds::assign_invalid_constant: {
                        return "Cannot assign to a constant value";
                  }
                  case kinds::assign_invalid_rvalue: {
                        return "Invalid rvalue to assign to";
                  }

                        /* Misc */
                  case kinds::null_pointer: {
                        return "Pointer is null";
                  }
                  default: {
                        return "Unknown";
                  }
            }
      }
} // namespace luramas::ir::execution::errors