#pragma once
#include <cstdint>
#include <cstring>
#include <string>

namespace luramas::ir::data::format {

      struct formatter {

            explicit formatter(const std::string &s)
                : str(s) {
            }
            std::string replace(const std::initializer_list<std::pair<const char *, std::string>> &kp) const;

          private:
            std::string str = "";
      };

      enum class case_var_kind : std::uint8_t {
            snake_,
            pascal_,
            camel_,
            flat_,
            screaming_snake_
      };

      struct format {

            /* 
                  
                    * Amount of indent for each (Added too multiplier when hit). 
                    * 1 for normal 0 for nothing. 
                    
            */
            struct indent {

                  bool enabeled = true; /* All indents are enabeled? */

                  /* Generic indent */
                  std::string indent_space = "   "; /* Amount of indent per line e.g. a1 += 1; */
                  std::uint8_t indent_start = 0u;   /* Start on indent amount. */

                  /* End */
                  std::int8_t indent_end_pre = -1; /* Indent on end statement. */
                  std::int8_t indent_end_post = 0; /* Indent after end statement. */

                  /* If */
                  std::int8_t indent_if_pre = 0;  /* Indent on if statement. */
                  std::int8_t indent_if_post = 1; /* Indent after if statement. */

                  /* Else if  */
                  std::int8_t indent_elseif_pre = -1; /* Indent before else if statement. */
                  std::int8_t indent_elseif_post = 1; /* Indent after else if statement. */

                  /* Else */
                  std::int8_t indent_else_pre = -1; /* Indent before else if statement. */
                  std::int8_t indent_else_post = 1; /* Indent after else statement. */

                  /* Loop */
                  std::int8_t indent_loop_pre = 0;  /* Indent on loop statement. */
                  std::int8_t indent_loop_post = 1; /* Indent after loop statement. */

                  /* For */
                  std::int8_t indent_numeric_for_loop_pre = 0;  /* Indent on numeric for loop statement. */
                  std::int8_t indent_numeric_for_loop_post = 1; /* Indent after numeric for loop statement. */
                  std::int8_t indent_generic_for_loop_pre = 0;  /* Indent on generic for loop statement. */
                  std::int8_t indent_generic_for_loop_post = 1; /* Indent after generic for loop statement. */

                  /* Function */
                  std::int8_t indent_global_function_pre = 1;      /* Indent in global function statement. */
                  std::int8_t indent_global_function_post = -1;    /* Indent after global function statement. */
                  std::int8_t indent_scope_function_pre = 1;       /* Indent in scope function statement. */
                  std::int8_t indent_scope_function_post = -1;     /* Indent after scope function statement. */
                  std::int8_t indent_anonymous_function_pre = 1;   /* Indent in anonymous function statement. */
                  std::int8_t indent_anonymous_function_post = -1; /* Indent after anonymous function statement. */

                  /* Tag */
                  std::int8_t indent_tag_start_pre = 0;  /* Index before tag start statement. */
                  std::int8_t indent_tag_start_post = 1; /* Index after tag start statement. */
                  std::int8_t indent_tag_end_pre = -1;   /* Index before tag end statement. */
                  std::int8_t indent_tag_end_post = 0;   /* Index after tag end statement. */

                  /* Page function  */
                  std::int8_t indent_page_function_start_pre = 0;  /* Indent before page function start statement. */
                  std::int8_t indent_page_function_start_post = 1; /* Indent after page function start statement. */
                  std::int8_t indent_page_function_end_pre = -1;   /* Indent before page function end statement. */
                  std::int8_t indent_page_function_end_post = 0;   /* Indent after page function end statement. */

                  /* Comment */
                  std::int8_t indent_comment_expandable = 1; /* Indent for comment. [Expandable] */
                  std::int8_t indent_comment = 1;            /* Indent for comment. [NOT Expandable, Independent from preceeding indent] */

                  /* Collapse and alligns.  */
                  struct collapse {

                        bool disabled = false;
                        std::uint32_t table = 4u;      /* Collapses table 0 = disabled count >= ?? */
                        std::uint32_t parameters = 0u; /* Collapses table 0 = disabled count >= ?? */
                        std::int8_t indenting = 1u;    /* Amount of indenting */
                        bool ternaries = false;        /* Collapses ternaries */
                  } collapse;

            } indent;

            struct spacing {

                  bool disabled = false; /* All spacings are disabled. */

                  /* Args */
                  std::string spacing_arg_post = " "; /* Amount of arguement spacing post comma e.g. a1,??a2 */
                  std::string spacing_arg_pre = "";   /* Amount of arguement spacing pre comma e.g. a1??,a2 */

                  /* Params */
                  std::string spacing_param_post = " ";            /* Amount of parameter spacing post comma e.g. (a1,??a2) */
                  std::string spacing_param_pre = "";              /* Amount of parameter spacing pre comma e.g. (a1??,a2) */
                  std::string spacing_param_parenthesis_post = ""; /* Amount of parameter parenthesis spacing post comma e.g. (a1,a2??) */
                  std::string spacing_param_parenthesis_pre = "";  /* Amount of parameter parenthesis spacing pre comma e.g. (??a1,a2) */

                  /* Table */
                  std::string spacing_table_delimiter_post = " "; /* Amount of table spacing post comma e.g. { a1,??a2 } */
                  std::string spacing_table_delimiter_pre = "";   /* Amount of table spacing pre comma e.g. { a1??,a2 } */
                  std::string spacing_table_open = "";            /* Amount of table spacing post open e.g. {??a1 */
                  std::string spacing_table_close = "";           /* Amount of table spacing pre close e.g. a2??} */
                  std::string spacing_table_index_pre = "";       /* Amount of index spacing post index e.g. [??a1 */
                  std::string spacing_table_index_post = "";      /* Amount of index spacing pre index e.g. a2??] */

                  /* Index */
                  std::string spacing_index_open_post = "";        /* Amount of index spacing post bracket e.g. a1[??1] */
                  std::string spacing_index_open_pre = "";         /* Amount of index spacing pre bracket e.g. a1??[1] */
                  std::string spacing_index_close_post = "";       /* Amount of index spacing post bracket e.g. a1[1??] */
                  std::string spacing_index_close_pre = "";        /* Amount of index spacing pre bracket e.g. a1[1]?? */
                  std::string spacing_index_assignment_post = " "; /* Amount of index equal spacing post equal e.g. a1=?? */
                  std::string spacing_index_assignment_pre = " ";  /* Amount of index equal spacing pre equal e.g. a1??= */

                  /* Arith */
                  std::string spacing_arith_post = " "; /* Amount of arith operation spacing post operation e.g. a3 = a1+??a2; */
                  std::string spacing_arith_pre = " ";  /* Amount of arith operation spacing pre operation e.g. a3 = a1??+a1 */

                  /* Concat */
                  std::string spacing_concat_post = " "; /* Amount of concat spacing post operation e.g. a1..??; */
                  std::string spacing_concat_pre = " ";  /* Amount of concat spacing pre operation e.g. a2??.. */

                  /* Logical operators */
                  std::string spacing_logical_operator_post = " "; /* Amount of arith operation spacing post operation e.g. if(a1==??a2) */
                  std::string spacing_logical_operator_pre = " ";  /* Amount of arith operation spacing pre operation e.g. if(a1??==a2) */

                  /* Parenthesis */
                  std::string spacing_parenthesis_open_post = "";  /* Amount of parenthesis spacing post open e.g. (??a1+a2) */
                  std::string spacing_parenthesis_open_pre = "";   /* Amount of parenthesis spacing pre open e.g. ??(a1+a2) */
                  std::string spacing_parenthesis_close_post = ""; /* Amount of parenthesis spacing post close e.g. (a1+a2)?? */
                  std::string spacing_parenthesis_close_pre = "";  /* Amount of parenthesis spacing pre close e.g. (a1+a2??) */

                  /* Assignment */
                  std::string spacing_assign_post = " "; /* Amount of assign spacing post equal e.g. a1=??a2 */
                  std::string spacing_assign_pre = " ";  /* Amount of assign spacing pre equal e.g. a1??=a2 */

                  /* Loop */
                  std::string spacing_forloop_generic_post = " "; /* Amount of for loop generic(LUA:"in") spacing post operation e.g. a1, a2 in??foo(bar) */
                  std::string spacing_forloop_generic_pre = " ";  /* Amount of for loop generic(LUA:"in") spacing pre operation e.g. a1, a2??in foo(bar) */
                  std::string spacing_forloop_numeric_post = " "; /* Amount of for loop numeric(LUA:"=") spacing post operation e.g. a1 =??1,2 */
                  std::string spacing_forloop_numeric_pre = " ";  /* Amount of for loop numeric(LUA:"=") spacing pre operation e.g. a1??= 1,2 */
                  std::string spacing_forloop_scope_start = " ";  /* Amount of for loop in scope start(LUA:"do") e.g. foo(bar)??do */
                  std::string spacing_forloop = " ";              /* Amount of post loop statement spacing e.g. for??() */

                  /* Constant */
                  std::string spacing_compare = " ";  /* Amount of pre compare statement spacing e.g. if??() */
                  std::string spacing_then = " ";     /* Amount of pre then statement spacing e.g. if()??then */
                  std::string spacing_call = "";      /* Amount of call spacing e.g. call??(); */
                  std::string spacing_goto = " ";     /* Amount of pre goto statement spacing e.g. goto?? */
                  std::string spacing_tag = " ";      /* Amount of pre tag statement spacing e.g. <??"" */
                  std::string spacing_function = " "; /* Amount of global function spacing e.g. ??function??(); */

                  /* Loop constants */
                  std::string spacing_loop_until = " ";             /* Amount of post until statement spacing e.g. until??()/while??(); */
                  std::string spacing_loop_while = " ";             /* Amount of post while statement spacing e.g. while??() */
                  std::string spacing_loop_while_scope_start = " "; /* Amount of while scope start spacing e.g. ??do */

                  /* Unary */
                  std::string spacing_not = " ";   /* Amount of not spacing e.g. not??a1; */
                  std::string spacing_length = ""; /* Amount of length spacing e.g. #??a1; */
                  std::string spacing_minus = "";  /* Amount of minus spacing e.g. -??a1; */
                  std::string spacing_bitnot = ""; /* Amount of minus spacing e.g. ~??a1; */

                  /* ";" */
                  std::string spacing_semicolon = ""; /* Amount of semicolon spacing e.g. a1 = a2??; */

                  /* Assignment */
                  std::string spacing_assignment_post = " "; /* Amount of assignment equal spacing post equal e.g. a1=?? */
                  std::string spacing_assignment_pre = " ";  /* Amount of assignment equal spacing pre equal e.g. a1??= */

                  std::string spacing_assignment_lvalue_post = " "; /* Amount of assignment lvalue spacing post equal e.g. a1,??a2 */
                  std::string spacing_assignment_lvalue_pre = "";   /* Amount of assignment lvalue spacing pre equal e.g. a1??,a2 */
                  std::string spacing_assignment_rvalue_post = " "; /* Amount of assignment rvalue spacing post equal e.g. a1,??a2 */
                  std::string spacing_assignment_rvalue_pre = "";   /* Amount of assignment rvalue spacing pre equal e.g. a1??,a2 */

                  /* Initial Assignment */
                  std::string spacing_initial_assignment_post = " ";     /* Amount of initial assignment spacing post equal e.g. a1=?? */
                  std::string spacing_initial_assignment_pre = " ";      /* Amount of initial assignment spacing pre equal e.g. a1??= */
                  std::string spacing_initial_datatype_assignment = " "; /* Amount of initial datatype assignment equal spacing equal e.g. var_type ??a1 */

                  std::string spacing_initial_assignment_lvalue_post = " "; /* Amount of initial assignment lvalue spacing post equal e.g. a1,??a2 */
                  std::string spacing_initial_assignment_lvalue_pre = "";   /* Amount of initial assignment lvalue spacing pre equal e.g. a1??,a2 */
                  std::string spacing_initial_assignment_rvalue_post = " "; /* Amount of initial assignment rvalue spacing post equal e.g. a1,??a2 */
                  std::string spacing_initial_assignment_rvalue_pre = "";   /* Amount of initial assignment rvalue spacing pre equal e.g. a1??,a2 */

                  /* Ternary */
                  std::string spacing_ternary_start = " ";     /* Amount of ternary spacing pre then e.g.  if??() */
                  std::string spacing_ternary_then_pre = " ";  /* Amount of ternary spacing pre then e.g. ()??then */
                  std::string spacing_ternary_then_post = " "; /* Amount of ternary spacing post then e.g. ()then?? */
                  std::string spacing_ternary_else_pre = " ";  /* Amount of ternary spacing pre else e.g. ??else */
                  std::string spacing_ternary_else_post = " "; /* Amount of ternary spacing post else e.g. else?? */

                  /* Return */
                  std::string spacing_return = " "; /* Amount of return statement spacing e.g. return??a1; (WILL ONLY FORMAT IF THERE IS OUTPUT) */

                  /* Page functions */
                  std::string spacing_page_function_return_type = " "; /* Amount of page function return type spacing e.g. void??page_function() */
#pragma region spacing_keywords

                  /* Formats global function too new string. */
                  std::string format_function(const char *const keyword) const;

                  /* Formats not too new string. */
                  std::string format_unary_not(const char *const keyword) const;

                  /* Formats minus too new string. */
                  std::string format_unary_minus(const char *const keyword) const;

                  /* Formats bit not too new string. */
                  std::string format_unary_bitnot(const char *const keyword) const;

                  /* Formats length too new string. */
                  std::string format_unary_length(const char *const keyword) const;

                  /* Formats open parenthesis too new string. */
                  std::string format_parenthesis_open(const char *const keyword) const;

                  /* Formats close parenthesis too new string. */
                  std::string format_parenthesis_close(const char *const keyword) const;

                  /* Turns string into parenthesis. **STRING NOT reference** */
                  std::string format_parenthesis_str(const char *const open, const std::string &str, const char *const close) const;

                  /* Turns string into parenthesis. */
                  std::string format_parenthesis_ref(const char *const open, const std::string &str, const char *const close) const;

                  /* Formats open parenthesis too new string. */
                  std::string format_index_open(const char *const keyword) const;

                  /* Formats close parenthesis too new string. */
                  std::string format_index_close(const char *const keyword) const;

                  /* Turns string into parenthesis. **STRING NOT reference** */
                  std::string format_index_str(const char *const open, const std::string &str, const char *const close) const;

                  /* Formats indent reference too buffer. */
                  std::string format_index_ref(const char *const open, const std::string &str, const char *const close) const;

                  /* Formats open parameter parenthesis too new string. */
                  std::string format_parameter_open(const char *const keyword) const;

                  /* Formats close parameter parenthesis too new string. */
                  std::string format_parameter_close(const char *const keyword) const;

                  /* Adds spacing too format call for call routine. */
                  void format_call_spacing(std::string &buffer) const;

                  /* Adds spacing spacing pre name */
                  void format_tag_spacing(std::string &buffer) const;

                  /* Formats table delimiter too new string. */
                  std::string format_table_delimiter(const char *const keyword) const;

                  /* Formats table start too new string. */
                  std::string format_table_start(const char *const keyword) const;

                  /* Formats table start too new string. */
                  std::string format_table_end(const char *const keyword) const;

                  /* Formats table start too new string. */
                  std::string format_table_index(const char *const open, const std::string &str, const char *const close, const char *const equal) const;

                  /* Formats table close too new string. */
                  std::string format_table_close(const char *const keyword) const;

                  /* Formats ternary start too new string. */
                  std::string format_ternary_start(const char *const keyword) const;

                  /* Formats ternary then too new string. */
                  std::string format_ternary_then(const char *const keyword) const;

                  /* Formats ternary else too new string. */
                  std::string format_ternary_else(const char *const keyword) const;

                  /* Formats arith too new string. */
                  std::string format_arith(const char *const keyword) const;

                  /* Formats logical operation too new string. */
                  std::string format_logical_operation(const char *const keyword) const;

                  /* Formats parameter delimiter too new string. */
                  std::string format_parameter_delimiter(const char *const keyword) const;

                  /* Formats concat too new string. */
                  std::string format_concat(const char *const keyword) const;

                  /* Formats compare too new string. */
                  std::string format_compare(const char *const keyword) const;

                  /* Formats compare too new string. */
                  std::string format_goto(const char *const keyword) const;

                  /* Formats while too new string. */
                  std::string format_while(const char *const keyword) const;

                  /* Formats until too new string. */
                  std::string format_until(const char *const keyword) const;

                  /* Formats return too new string. */
                  std::string format_return(const char *const keyword) const;

                  /* Formats while scope start LUA:"do" too new string. */
                  std::string format_while_scope_start(const char *const keyword) const;

                  /* Formats scope begin too new string. */
                  std::string format_scope_begin(const char *const keyword) const;

                  /* Formats compare too new string. */
                  std::string format_loop_begin(const char *const keyword) const;

                  /* Formats semicolon too new string. */
                  std::string format_semicolon(const char *const keyword) const;

                  /* Formats assignment too new string. */
                  std::string format_assignment(const char *const keyword) const;

                  /* Formats assignment lvalue too new string. */
                  std::string format_assignment_lvalue(const char *const keyword) const;

                  /* Formats assignment rvalue too new string. */
                  std::string format_assignment_rvalue(const char *const keyword) const;

                  /* Formats initial assignment too new string. */
                  std::string format_assignment_initial(const char *const keyword) const;

                  /* Formats initial assignment lvalue too new string. */
                  std::string format_assignment_initial_lvalue(const char *const keyword) const;

                  /* Formats initial assignment rvalue too new string. */
                  std::string format_assignment_initial_rvalue(const char *const keyword) const;

                  /* Formats initial assignment too new string. */
                  std::string format_assignment_initial_datatype(const char *const keyword) const;

                  /* Formats page function return type */
                  std::string format_page_function_return_type(const char *const keyword) const;
#pragma endregion

            } spacing;

            struct linebreak {

                  bool enabled = true;      /* Disables all line breaks? */
                  std::uint8_t amount = 1u; /* Amount of linebreaks start per line. */

                  /* Scoped expandable comments. */
                  std::uint8_t expandable_comment_pre = 1u;  /* Amount of linebreaks for expandable comments pre e.g. --[[?? */
                  std::uint8_t expandable_comment_post = 1u; /* Amount of linebreaks for expandable comments pre e.g. ??]] */

                  /* End scope */
                  std::uint8_t end_scope_pre = 0u;  /* Amount of linebreaks before end scope statement. */
                  std::uint8_t end_scope_post = 0u; /* Amount of linebreaks after end scope statement. */

                  /* if */
                  std::uint8_t if_pre = 0u;  /* Amount of linebreaks before if statement. */
                  std::uint8_t if_post = 0u; /* Amount of linebreaks after if statement. */

                  /* else if  */
                  std::uint8_t elseif_pre = 0u;  /* Amount of linebreaks before else if statement. */
                  std::uint8_t elseif_post = 0u; /* Amount of linebreaks after else if statement. */

                  /* else */
                  std::uint8_t else_pre = 0u;  /* Amount of linebreaks before else statement. */
                  std::uint8_t else_post = 0u; /* Amount of linebreaks after else statement. */

                  /* loop */
                  std::uint8_t loop_pre = 0u;  /* Amount of linebreaks before loop statement. */
                  std::uint8_t loop_post = 0u; /* Amount of linebreaks after loop statement. */

                  /* For */
                  std::uint8_t numeric_for_loop_pre = 0u;  /* Amount of linebreaks before numeric for loop statement. */
                  std::uint8_t numeric_for_loop_post = 0u; /* Amount of linebreaks after numeric for loop statement. */
                  std::uint8_t generic_for_loop_pre = 0u;  /* Amount of linebreaks before generic for loop statement. */
                  std::uint8_t generic_for_loop_post = 0u; /* Amount of linebreaks after generic for loop statement. */

                  /* Function */
                  std::uint8_t global_function_pre = 0u;     /* Amount of linebreaks before global function statement. */
                  std::uint8_t global_function_post = 0u;    /* Amount of linebreaks after global function statement. */
                  std::uint8_t scope_function_pre = 0u;      /* Amount of linebreaks before scope function statement. */
                  std::uint8_t scope_function_post = 0u;     /* Amount of linebreaks after scope function statement. */
                  std::uint8_t anonymous_function_pre = 0u;  /* Amount of linebreaks before anonymous function statement. */
                  std::uint8_t anonymous_function_post = 0u; /* Amount of linebreaks after anonymous function statement. */

                  /* Tag */
                  std::uint8_t tag_start_pre = 0u;  /* Amount of linebreaks before tag start statement. */
                  std::uint8_t tag_start_post = 0u; /* Amount of linebreaks after tag start statement. */
                  std::uint8_t tag_end_pre = 0u;    /* Amount of linebreaks before tag end statement. */
                  std::uint8_t tag_end_post = 0u;   /* Amount of linebreaks after tag end statement. */

                  /* Page function  */
                  std::uint8_t page_function_start_pre = 0u;  /* Amount of linebreaks before page function start statement. */
                  std::uint8_t page_function_start_post = 0u; /* Amount of linebreaks after page function start statement. */
                  std::uint8_t page_function_end_pre = 0u;    /* Amount of linebreaks before page function end statement. */
                  std::uint8_t page_function_end_post = 0u;   /* Amount of linebreaks after page function end statement. */
            } linebreak;

            struct stats {

                  bool comments = true; /* Uses non expandable comment when not nessary. */

                  struct semicolon {

                        bool enabeled = true;           /* Enable semicolon emittions? */
                        bool semi_until = true;         /* Semicolon after until e.g. until(??); */
                        bool semi_repeat = false;       /* Semicolon after repeat e.g. repeat; */
                        bool semi_end = false;          /* Semicolon after end e.g. end; */
                        bool semi_return = true;        /* Semicolon after return e.g. return; */
                        bool semi_implicit_jump = true; /* Semicolon after implicit jumps breaks/continues e.g. continue; */
                  } semicolon;

                  struct naming_convention {

                        struct prefixes {

                              std::string label = "label"; /* Label prefix */
                        } prefixes;

                  } naming_convention;

                  std::size_t default_stack_id = 0u; /* Will not emit stack ID if it is the default */
                  bool arith_assignment = true;      /* Arith assignment e.g. a1 += a2; -> a1 = a1 + a2; */
                  bool useless_return = true;        /* Does not emit useless return if it is not needed. */
            } stats;

            struct vars {

                  struct naming_convention {

                        bool anotations = false;                         /* Use annotations if avaliable */
                        const char *const delimeter = "_";               /* Split data up by delimeter (Should remain as "_") */
                        bool unique_anotations = false;                  /* Will structure anotations but use prefix and suffix to make them unique*/
                        case_var_kind case_kind = case_var_kind::snake_; /* Case kind */

                        /* Prefixs. (DEFAULT) */
                        struct prefixes {

                              struct flags {

                                    bool enabled = true;           /* Enable flags for prefixes */
                                    std::string atomic = "atm";    /* Atomic */
                                    std::string unsign = "usgn";   /* Usigned */
                                    std::string synthetic = "syn"; /* Synthetic */
                              } flags;

                              std::string var = "v";            /* Variable */
                              std::string arg = "a";            /* Arguement */
                              std::string upvalue = "u";        /* Upvalue */
                              std::string page_function = "pf"; /* Page function */
                        } prefixes;

                        /* Suffix is a char? */
                        struct suffix {

                              bool var = true;
                              bool arg = true;
                              bool upvalue = true;
                        } suffix;

                        struct smart {

                              bool enabled = true;                     /* Enable smart naming conventions */
                              bool suffix_char = true;                 /* Suffix is a char when needed. */
                              bool primitive = true;                   /* Naming for primitives */
                              bool common_library = true;              /* Names variable after results of common libraries */
                              bool common_libary_arg = true;           /* Names variable after arg used in common libaries */
                              bool expression_canonicalization = true; /* Expression canonicalization */
                              bool acronyms = true;                    /* Uses common most recognized acronyms */
                              std::uintptr_t max_depth = 6u;           /* Max depth for naming */
                              std::uintptr_t valid_depth = 3u;         /* Max valid depth for naming */

                              struct constant {

                                    bool enable = true;               /* Enable constant renaming */
                                    bool upper_case = false;          /* Uppercase constant */
                                    bool include_prefix = false;      /* Include constant prefix? */
                                    bool discriminator_suffix = true; /* Include char as suffix */
                                    std::string prefix = "c_";
                              } constant;

                              struct prefixes {

                                    std::string module = "m";
                                    std::string index = "";
                                    std::string table = "";
                                    std::string constant = "";
                                    std::string primitive = "";
                                    std::string copy = "dyn";
                                    std::string upvalue = "u_";
                                    std::string variable = "";
                                    std::string argument = "";
                              } prefixes;

                              struct basic_naming {

                                    std::string pair_key = "k";
                                    std::string pair_value = "v";
                                    std::string value = "val";
                                    std::string iter = "i";
                                    std::string table = "tab";
                                    std::string deadset = "_";
                              } basic_naming;

                        } smart;

                  } naming_conventions;

                  bool include_types = false;  /* Include variable types e.g. int32_t x = 0; */
                  char module_delimiter = '.'; /* Delimiter for user modules */
            } vars;
      };

} // namespace luramas::ir::data::format
