#ifndef GENERIC_PARSETREE_ANTLR4_WGSL_H_
#define GENERIC_PARSETREE_ANTLR4_WGSL_H_

namespace WGSL {

#define WGSL_CONTEXTS(V)                                                       \
  V(WGSL, WGSLParser, Translation_unit, Template_args_start)                         \
  V(WGSL, WGSLParser, Translation_unit, Template_args_end)                           \
  V(WGSL, WGSLParser, Translation_unit, Additive_operator)                           \
  V(WGSL, WGSLParser, Translation_unit, Multiplicative_operator)                     \
  V(WGSL, WGSLParser, Translation_unit, Argument_expression_list)                    \
  V(WGSL, WGSLParser, Translation_unit, Assignment_statement)                        \
  V(WGSL, WGSLParser, Translation_unit, Shift_expression_post_unary_expression)      \
  V(WGSL, WGSLParser, Translation_unit, Attribute)                                   \
  V(WGSL, WGSLParser, Translation_unit, Bitwise_expression_post_unary_expression)    \
  V(WGSL, WGSLParser, Translation_unit, Case_selector)                               \
  V(WGSL, WGSLParser, Translation_unit, Component_or_swizzle_specifier)              \
  V(WGSL, WGSLParser, Translation_unit, Compound_statement)                          \
  V(WGSL, WGSLParser, Translation_unit, Core_lhs_expression)                         \
  V(WGSL, WGSLParser, Translation_unit, Diagnostic_control)                          \
  V(WGSL, WGSLParser, Translation_unit, Diagnostic_rule_name)                        \
  V(WGSL, WGSLParser, Translation_unit, Expression)                                  \
  V(WGSL, WGSLParser, Translation_unit, Float_literal)                               \
  V(WGSL, WGSLParser, Translation_unit, For_init)                                    \
  V(WGSL, WGSLParser, Translation_unit, For_update)                                  \
  V(WGSL, WGSLParser, Translation_unit, Global_decl)                                 \
  V(WGSL, WGSLParser, Translation_unit, Global_directive)                            \
  V(WGSL, WGSLParser, Translation_unit, Global_value_decl)                           \
  V(WGSL, WGSLParser, Translation_unit, Ident)                                       \
  V(WGSL, WGSLParser, Translation_unit, Int_literal)                                 \
  V(WGSL, WGSLParser, Translation_unit, Lhs_expression)                              \
  V(WGSL, WGSLParser, Translation_unit, Literal)                                     \
  V(WGSL, WGSLParser, Translation_unit, Member_ident)                                \
  V(WGSL, WGSLParser, Translation_unit, Optionally_typed_ident)                      \
  V(WGSL, WGSLParser, Translation_unit, Param)                                       \
  V(WGSL, WGSLParser, Translation_unit, Primary_expression)                          \
  V(WGSL, WGSLParser, Translation_unit, Greater_than)                                \
  V(WGSL, WGSLParser, Translation_unit, Less_than)                                   \
  V(WGSL, WGSLParser, Translation_unit, Relational_expression_post_unary_expression) \
  V(WGSL, WGSLParser, Translation_unit, Statement)                                   \
  V(WGSL, WGSLParser, Translation_unit, Switch_clause)                               \
  V(WGSL, WGSLParser, Translation_unit, Template_arg_expression)                     \
  V(WGSL, WGSLParser, Translation_unit, Template_elaborated_ident_post_ident)        \
  V(WGSL, WGSLParser, Translation_unit, Translation_unit)                            \
  V(WGSL, WGSLParser, Translation_unit, Type_specifier)                              \
  V(WGSL, WGSLParser, Translation_unit, Unary_expression)                            \
  V(WGSL, WGSLParser, Translation_unit, Variable_decl)                               \
  V(WGSL, WGSLParser, Translation_unit, Variable_or_value_statement)                 \
  V(WGSL, WGSLParser, Translation_unit, Variable_updating_statement)


}


#endif // GENERIC_PARSETREE_ANTLR4_WGSL_H_
