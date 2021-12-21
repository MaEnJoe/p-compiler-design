#ifndef __EXPR_MANAGER__
#define __EXPR_MANAGER__

#include "AST/PType.hpp"
#include "AST/ast.hpp"

struct Expr_type_msgr
{
	Expr_type_msgr(Location location,PTypeSharedPtr type):location(location),type(type),p(nullptr){}
	Expr_type_msgr(Location location,const PType* type):location(location),type(type),p(nullptr){}
	Expr_type_msgr(Location location,const PType* type,SymbolEntry* p):location(location),type(type),p(p){}

    const Location location;
    PTypeSharedPtr type;
    SymbolEntry* p;
};

#endif