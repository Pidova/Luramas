#pragma once

/* Unary */
#define cpp_langkeyword_not "!"
#define cpp_langkeyword_minus "-"
#define cpp_langkeyword_bitnot "~"

/* Arith */
#define cpp_langkeyword_arith_add "+"
#define cpp_langkeyword_arith_sub "-"
#define cpp_langkeyword_arith_mul "*"
#define cpp_langkeyword_arith_div "/"
#define cpp_langkeyword_arith_pow "std::pow"
#define cpp_langkeyword_arith_idiv "std::floor"
#define cpp_langkeyword_arith_mod "%"
#define cpp_langkeyword_arith_xor "^"
#define cpp_langkeyword_arith_or "|"
#define cpp_langkeyword_arith_and "&"
#define cpp_langkeyword_arith_shr ">>"
#define cpp_langkeyword_arith_shl "<<"
#define cpp_langkeyword_arith_assignment_add "+="
#define cpp_langkeyword_arith_assignment_sub "-="
#define cpp_langkeyword_arith_assignment_pow "^="
#define cpp_langkeyword_arith_assignment_mul "*="
#define cpp_langkeyword_arith_assignment_div "/="
#define cpp_langkeyword_arith_assignment_mod "%="
#define cpp_langkeyword_arith_assignment_xor "^="
#define cpp_langkeyword_arith_assignment_or "|="
#define cpp_langkeyword_arith_assignment_and "&="
#define cpp_langkeyword_arith_assignment_shr ">>="
#define cpp_langkeyword_arith_assignment_shl "<<="

/* Compare */
#define cpp_langkeyword_compare_lessthan "<"
#define cpp_langkeyword_compare_lessthanequal "<="
#define cpp_langkeyword_compare_equal "=="
#define cpp_langkeyword_compare_notequal "!="
#define cpp_langkeyword_compare_greaterthan ">"
#define cpp_langkeyword_compare_greaterthanequal ">="
#define cpp_langkeyword_compare_and "lura_and"
#define cpp_langkeyword_compare_or "lura_or"

/* Parenthesis */
#define cpp_langkeyword_parenthesis_open "("
#define cpp_langkeyword_parenthesis_close ")"

/* Index */
#define cpp_langkeyword_index_open "["
#define cpp_langkeyword_index_close "]"
#define cpp_langkeyword_index_generic "."

/* Keyword */
#define cpp_langkeyword_nil "nil"
#define cpp_langkeyword_true "1"
#define cpp_langkeyword_false "0"
#define cpp_langkeyword_stack "lura_stack"
#define cpp_langkeyword_controller "lura_controller"
#define cpp_langkeyword_variadic "..."
#define cpp_langkeyword_nothing ""

/* Selfcall */
#define cpp_langkeyword_selfcall ":"

/* Call */
#define cpp_langkeyword_call_parenthesis_open "("
#define cpp_langkeyword_call_parenthesis_close ")"
#define cpp_langkeyword_call_delimiter ","

/* Return */
#define cpp_langkeyword_return "return"
#define cpp_langkeyword_return_seprator ","

/* Loop */

/* do */
#define cpp_langkeyword_loop_do " {"

/* while */
#define cpp_langkeyword_loop_while "while"
#define cpp_langkeyword_loop_while_end " do"

/* Repeat */
#define cpp_langkeyword_loop_repeat "do"

/* until, break, continue */
#define cpp_langkeyword_loop_until "} while"
#define cpp_langkeyword_loop_break "break"
#define cpp_langkeyword_loop_continue "continue"

/* Scope */

/* if */
#define cpp_langkeyword_scope_if "if"
#define cpp_langkeyword_scope_if_begin "{"

/* elseif */
#define cpp_langkeyword_scope_elseif "else if"
#define cpp_langkeyword_scope_elseif_begin "{"

/* else */
#define cpp_langkeyword_scope_else "} else"
#define cpp_langkeyword_scope_else_begin " { "

/* end */
#define cpp_langkeyword_scope_end "}"

/* goto */
#define cpp_langkeyword_scope_goto "goto"

/* label */
#define cpp_langkeyword_scope_label_begin ""
#define cpp_langkeyword_scope_label_end ":"

/* Table */
#define cpp_langkeyword_table_start "{"
#define cpp_langkeyword_table_end "}"
#define cpp_langkeyword_table_delimiter ","
#define cpp_langkeyword_table_index_start "["
#define cpp_langkeyword_table_index_end "]"
#define cpp_langkeyword_table_index_assignment "="

/* Comment */
#define cpp_langkeyword_comment "//"
#define cpp_langkeyword_comment_expandable_start "/*"
#define cpp_langkeyword_comment_expandable_end "*/"

/* for */
#define cpp_langkeyword_for "for"
#define cpp_langkeyword_for_generic "in"
#define cpp_langkeyword_for_numeric "="
#define cpp_langkeyword_for_scope_start "do"
#define cpp_langkeyword_for_delimiter ","

/* String */
#define cpp_langkeyword_string_start '\"'
#define cpp_langkeyword_string_end '\"'

/* Line */
#define cpp_langkeyword_line_break '\n'
#define cpp_langkeyword_semicolon ";"

/* Assignment */
#define cpp_langkeyword_assignment "="
#define cpp_langkeyword_list_rvalue ","
#define cpp_langkeyword_list_lvalue ","

/* function */
#define cpp_langkeyword_function_delimeter ","
#define cpp_langkeyword_function "function"
#define cpp_langkeyword_function_anonymous "(function"
#define cpp_langkeyword_function_anonymous_end "end)"
#define cpp_langkeyword_function_params_parenthesis_open "("
#define cpp_langkeyword_function_params_parenthesis_close ")"

/* Ternary */
#define cpp_langkeyword_ternary_start ""
#define cpp_langkeyword_ternary_then "?"
#define cpp_langkeyword_ternary_else ":"

/* Variable datatype */
#define cpp_langkeyword_dynamic_datatype "auto"

/* Cast */
#define cpp_langkeyword_cast_pre "std::"
#define cpp_langkeyword_cast_post ""

/* Memread */
#define cpp_langkeyword_memread_pre ""
#define cpp_langkeyword_memread_Tpre "lura_memread<std::"
#define cpp_langkeyword_memread_Tpost ">("
#define cpp_langkeyword_memread_post ")"

/* Memwrite */
#define cpp_langkeyword_memwrite_pre ""
#define cpp_langkeyword_memwrite_Tpre "lura_memset<std::"
#define cpp_langkeyword_memwrite_Tpost ">("
#define cpp_langkeyword_memwrite_v_pre ""
#define cpp_langkeyword_memwrite_v_post ")"
#define cpp_langkeyword_memwrite_asgn_pre " = "
#define cpp_langkeyword_memwrite_asgn_post ""

/* Bitread */
#define cpp_langkeyword_bitread_pre ""
#define cpp_langkeyword_bitread_Tpre "lura_bitread<std::"
#define cpp_langkeyword_bitread_Tpost ">("
#define cpp_langkeyword_bitread_v_pre ""
#define cpp_langkeyword_bitread_v_post ", "
#define cpp_langkeyword_bitread_min_pre ""
#define cpp_langkeyword_bitread_min_post ", "
#define cpp_langkeyword_bitread_max_pre ""
#define cpp_langkeyword_bitread_max_post ")"

/* Dead */
#define cpp_langkeyword_dynamic_deadv_sideeffects_pre "lura_deadv("
#define cpp_langkeyword_dynamic_deadv_sideeffects_post ")"
#define cpp_langkeyword_dynamic_dead_sideeffects_pre "lura_dead("
#define cpp_langkeyword_dynamic_dead_sideeffects_post ")"

/* Types */
#define cpp_langkeyword_types_no_return "void"

/* Flags */
#define cpp_langkeyword_flags_get "get_flag"

/* Page */
#define cpp_langkeyword_page_function_args_start "("
#define cpp_langkeyword_page_function_args_end ")"
#define cpp_langkeyword_page_function_start " {"
#define cpp_langkeyword_page_function_end "}"

/* Keywords */
#define cpp_langkeyword_dynamic_spush "spush"
#define cpp_langkeyword_dynamic_bitread "lura_bitread"
#define cpp_langkeyword_dynamic_memset_end "*>"

#define cpp_langkeyword_empty ""