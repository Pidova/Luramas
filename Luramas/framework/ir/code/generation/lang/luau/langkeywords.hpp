#pragma once

/* Unary */
#define luau_langkeyword_not "not"
#define luau_langkeyword_minus "-"
#define luau_langkeyword_lenght "#"
#define luau_langkeyword_bitnot "~"

/* Arith */
#define luau_langkeyword_arith_add "+"
#define luau_langkeyword_arith_sub "-"
#define luau_langkeyword_arith_pow "^"
#define luau_langkeyword_arith_mul "*"
#define luau_langkeyword_arith_div "/"
#define luau_langkeyword_arith_idiv "//"
#define luau_langkeyword_arith_mod "%"
#define luau_langkeyword_arith_and "and"
#define luau_langkeyword_arith_or "or"
#define luau_langkeyword_arith_assignment_add "+="
#define luau_langkeyword_arith_assignment_sub "-="
#define luau_langkeyword_arith_assignment_pow "^="
#define luau_langkeyword_arith_assignment_mul "*="
#define luau_langkeyword_arith_assignment_div "/="
#define luau_langkeyword_arith_assignment_mod "%="
#define luau_langkeyword_arith_assignment_idiv "//="

/* Compare */
#define luau_langkeyword_compare_lessthan "<"
#define luau_langkeyword_compare_lessthanequal "<="
#define luau_langkeyword_compare_equal "=="
#define luau_langkeyword_compare_notequal "~="
#define luau_langkeyword_compare_greaterthan ">"
#define luau_langkeyword_compare_greaterthanequal ">="
#define luau_langkeyword_compare_and "and"
#define luau_langkeyword_compare_or "or"

/* Parenthesis */
#define luau_langkeyword_parenthesis_open "("
#define luau_langkeyword_parenthesis_close ")"

/* Index */
#define luau_langkeyword_index_open "["
#define luau_langkeyword_index_close "]"
#define luau_langkeyword_index_generic "."

/* Keyword */
#define luau_langkeyword_nil "nil"
#define luau_langkeyword_true "true"
#define luau_langkeyword_false "false"
#define luau_langkeyword_variadic "..."
#define luau_langkeyword_nothing ""

/* Selfcall */
#define luau_langkeyword_selfcall ":"

/* Call */
#define luau_langkeyword_call_parenthesis_open "("
#define luau_langkeyword_call_parenthesis_close ")"
#define luau_langkeyword_call_delimiter ","

/* Return */
#define luau_langkeyword_return "return"
#define luau_langkeyword_return_seprator ","

/* Concat */
#define luau_langkeyword_concat ".."

/* Loop */

/* do */
#define luau_langkeyword_loop_do "do"

/* while */
#define luau_langkeyword_loop_while "while"
#define luau_langkeyword_loop_while_end " do"

/* Repeat */
#define luau_langkeyword_loop_repeat "repeat"

/* until, break, continue */
#define luau_langkeyword_loop_until "until"
#define luau_langkeyword_loop_break "break"
#define luau_langkeyword_loop_continue "continue"

/* Scope */

/* if */
#define luau_langkeyword_scope_if "if"
#define luau_langkeyword_scope_if_begin "then"

/* elseif */
#define luau_langkeyword_scope_elseif "elseif"
#define luau_langkeyword_scope_elseif_begin "then"

/* else */
#define luau_langkeyword_scope_else "else"
#define luau_langkeyword_scope_else_begin ""

/* end */
#define luau_langkeyword_scope_end "end"

/* goto */
#define luau_langkeyword_scope_goto "goto"

/* label */
#define luau_langkeyword_scope_label_begin "::"
#define luau_langkeyword_scope_label_end "::"

/* Table */
#define luau_langkeyword_table_start "{"
#define luau_langkeyword_table_end "}"
#define luau_langkeyword_table_delimiter ","
#define luau_langkeyword_table_index_start "["
#define luau_langkeyword_table_index_end "]"
#define luau_langkeyword_table_index_assignment "="

/* Comment */
#define luau_langkeyword_comment "--"
#define luau_langkeyword_comment_expandable_start "--[["
#define luau_langkeyword_comment_expandable_end "]]--"

/* for */
#define luau_langkeyword_for "for"
#define luau_langkeyword_for_generic "in"
#define luau_langkeyword_for_numeric "="
#define luau_langkeyword_for_scope_start "do"
#define luau_langkeyword_for_delimiter ","

/* String */
#define luau_langkeyword_string_start '\"'
#define luau_langkeyword_string_end '\"'

/* Line */
#define luau_langkeyword_line_break '\n'
#define luau_langkeyword_semicolon ";"

/* Assignment */
#define luau_langkeyword_assignment "="
#define luau_langkeyword_list_rvalue ","
#define luau_langkeyword_list_lvalue ","

/* function */
#define luau_langkeyword_function_delimeter ","
#define luau_langkeyword_function "function"
#define luau_langkeyword_function_anonymous "(function"
#define luau_langkeyword_function_anonymous_end "end)"
#define luau_langkeyword_function_params_parenthesis_open "("
#define luau_langkeyword_function_params_parenthesis_close ")"

/* Ternary */
#define luau_langkeyword_ternary_start "if"
#define luau_langkeyword_ternary_then "then"
#define luau_langkeyword_ternary_else "else"

/* Variable datatype */
#define luau_langkeyword_dynamic_datatype "local"

#define luau_langkeyword_empty ""