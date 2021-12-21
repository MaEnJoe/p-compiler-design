#ifndef __AST_EXPRESSION_NODE_H
#define __AST_EXPRESSION_NODE_H

#include "AST/PType.hpp"
#include "AST/ast.hpp"

class ExpressionNode : public AstNode {
  public:
    ExpressionNode(const uint32_t line, const uint32_t col);
    ~ExpressionNode() = default;
    virtual const PTypeSharedPtr &getTypePtr() const;
    void setTypePtr(PTypeSharedPtr);
  protected:
    // for carrying type of result of an expression
    PTypeSharedPtr type = nullptr;
};

#endif
