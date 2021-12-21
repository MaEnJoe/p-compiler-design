#ifndef __SEMA_SEMANTIC_ANALYZER_H
#define __SEMA_SEMANTIC_ANALYZER_H

#include "visitor/AstNodeVisitor.hpp"
#include "SymbolTableUtility.hpp"
#include "AST/ast.hpp"
#include "sema/ExprManager.hpp"
#include <string.h>
#include <memory>
#include <fstream>


class SemanticAnalyzer : public AstNodeVisitor {
  public:
    SemanticAnalyzer();
    ~SemanticAnalyzer() = default;

    void visit(ProgramNode &p_program) override;
    void visit(DeclNode &p_decl) override;
    void visit(VariableNode &p_variable) override;
    void visit(ConstantValueNode &p_constant_value) override;
    void visit(FunctionNode &p_function) override;
    void visit(CompoundStatementNode &p_compound_statement) override;
    void visit(PrintNode &p_print) override;
    void visit(BinaryOperatorNode &p_bin_op) override;
    void visit(UnaryOperatorNode &p_un_op) override;
    void visit(FunctionInvocationNode &p_func_invocation) override;
    void visit(VariableReferenceNode &p_variable_ref) override;
    void visit(AssignmentNode &p_assignment) override;
    void visit(ReadNode &p_read) override;
    void visit(IfNode &p_if) override;
    void visit(WhileNode &p_while) override;
    void visit(ForNode &p_for) override;
    void visit(ReturnNode &p_return) override;
    bool isLoopVar();//returm whether loop_var awaits
    bool hasParameters();//return whether parameters awaits
    const char* getCodeLineAt(Location location);
    void printErrorMessage();


  private:
    bool isLoopVarFlag = false;
    bool hasParametersFlag = false;
    bool errorInChildNode = false;
    bool expr_type_manager_works = false;
    bool isForLoopAssign = false;
    uint8_t compound_floor = 0;//this is for RetunNoe

    std::shared_ptr<SymbolTableManger> symbaol_table_manager;
    std::vector<Expr_type_msgr*> expr_type_manager;    
    std::vector<bool> error_manager;
    std::vector<ConstantValueNode> condition_increment_record;//for checking for_loop init/assing in increment order?
    std::vector<SymbolEntry*> funcNodeEntry;//for return_node info
    std::vector<std::string> errorMessageStack;
    // TODO: something like symbol manager (manage symbol tables)
    //       context manager, return type manager
};

#endif
