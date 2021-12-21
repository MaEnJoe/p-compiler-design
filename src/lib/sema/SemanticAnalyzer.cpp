#include "sema/SemanticAnalyzer.hpp"
#include "visitor/AstNodeInclude.hpp"

/*static void resetExprManager(bool & w,std::vector<Expr_type_msgr*>& m)
{
    w = false;
    m.clear();
}*/
static void resetExprManager(std::vector<Expr_type_msgr*>& m,int num)
{
    for(int i = 0 ; i != num ; i++)
    {
        m.pop_back();
    }
}

static void resetErrorManager(std::vector<bool>& m,int num)
{
    for(int i = 0 ; i != num ; i++)
    {
        m.pop_back();
    }    
}
static bool isNumericScalar(PTypeSharedPtr pType)
{
    bool isNumSca = ( pType->getDimensions().size() == 0 ) && 
                    ( (pType->getPrimitiveType() == PType::PrimitiveTypeEnum::kIntegerType) || 
                      (pType->getPrimitiveType() == PType::PrimitiveTypeEnum::kRealType) );
    return isNumSca;
}



SemanticAnalyzer::SemanticAnalyzer()//consructor
{
    symbaol_table_manager = std::make_shared<SymbolTableManger>();
    isLoopVarFlag = false;
    hasParametersFlag = false;
}
bool SemanticAnalyzer::hasParameters(){ return hasParametersFlag;}
bool SemanticAnalyzer::isLoopVar(){return isLoopVarFlag;}
void SemanticAnalyzer::visit(ProgramNode &p_program) {
//1    //symbaol_table_manager need not push
//2
    auto tmpType = std::make_shared<const PType>(PType::PrimitiveTypeEnum::kVoidType);
    auto tmp = new SymbolEntry(p_program.getNameCString(),
                            SymbolEntry::SymbolsKind::kProgram,
                            symbaol_table_manager->getLevel(),
                            tmpType);

    symbaol_table_manager->acceptSymbolEntry(tmp);

//3
    p_program.visitChildNodes(*this);
//4
//5
    symbaol_table_manager->pop();

}

void SemanticAnalyzer::visit(DeclNode &p_decl) {
    p_decl.visitChildNodes(*this);
}

void SemanticAnalyzer::visit(VariableNode &p_variable) {
    //1 
    //2 insert variable
    SymbolEntry::SymbolsKind kind ;//= hasParameters() ?(SymbolEntry::SymbolsKind::kParameter):(SymbolEntry::SymbolsKind::kVariable);
    kind = hasParameters() ? (SymbolEntry::SymbolsKind::kParameter):(SymbolEntry::SymbolsKind::kVariable);
    kind = isLoopVar() ? (SymbolEntry::SymbolsKind::kLoopVar):kind;
    kind = p_variable.isConstanVar() ? (SymbolEntry::SymbolsKind::kConstant):kind;

    //--------------check redcl--------------------------------
    bool hasError = false;
    
    auto p = symbaol_table_manager->lookup(p_variable.getNameCString(),false);  
    if(p != nullptr )hasError = true;
    
    SymbolEntry* tmpEntry;
    if(hasError)
    {//if redcl, report error
        std::string error;
        Location loc = p_variable.getLocation();
        error = "<Error> Found in line "+std::to_string(loc.line)+", column "+std::to_string(loc.col)
                +": symbol "+p_variable.getNameCString()+" is redeclared\n    "+getCodeLineAt(loc)+"\n";
        for(unsigned int i = 0 ; i != loc.col-1 ; i++){
            error+=" ";
        }error+="    ^";
        errorMessageStack.emplace_back(error);
        hasError = false;
    }else//accept if no redecl
    {
        tmpEntry = new SymbolEntry(p_variable.getNameCString(),
                                kind,
                                symbaol_table_manager->getLevel(),
                                p_variable.getType());    
        symbaol_table_manager->acceptSymbolEntry(tmpEntry);
        if(kind != SymbolEntry::SymbolsKind::kConstant)
            symbaol_table_manager->resetCurrentSymbolEntry();//only kConstant need current
    }
    /*3 ------------visit children-----------------*/
    p_variable.visitChildNodes(*this);
    /*4 ------------semantic check-----------------*/
    std::vector<uint64_t> dims = p_variable.getType()->getDimensions();
    for(uint64_t dim : dims)
    {
        if(dim <= 0)
            {
                hasError = true;
                break;
            }
    }
    if(hasError)
    {   //set error message
        std::string error;
        Location loc = p_variable.getLocation();
        error = "<Error> Found in line "+std::to_string(loc.line)+", column "+std::to_string(loc.col)
                +": \'"+p_variable.getNameCString()+"\' declared as an array with an index that is not greater than 0\n    "
                +getCodeLineAt(loc)+"\n";
        for(unsigned int i = 0 ; i != loc.col-1 ; i++){
            error+=" ";
        }error+="    ^";
        //store error message
        errorMessageStack.emplace_back(error);
        hasError = false;
        //signifying Error when declared
        tmpEntry->setHasErrorDeclared();
    }
    //5

    isLoopVarFlag = false;
}

void SemanticAnalyzer::visit(ConstantValueNode &p_constant_value) {
    
    auto current = symbaol_table_manager->getcurrentSymbolEntry();
    if(current)//do not put value to loop var
        current->setAttribute(p_constant_value.getConstant());
    symbaol_table_manager->resetCurrentSymbolEntry();// final step of adding entry
    expr_type_manager.emplace_back( new Expr_type_msgr(p_constant_value.getLocation(),p_constant_value.getTypePtr()));
    error_manager.emplace_back(false);
    if(isForLoopAssign)
        condition_increment_record.emplace_back(p_constant_value);

}

void SemanticAnalyzer::visit(FunctionNode &p_function) {

    //check redclr
    bool hasError;
    auto p = symbaol_table_manager->lookup(p_function.getNameCString(),false);
    if(p != nullptr)hasError = true;
    if(hasError)
    {
        std::string error;
        Location loc = p_function.getLocation();
        error = "<Error> Found in line "+std::to_string(loc.line)+", column "+std::to_string(loc.col)
                +": symbol "+p_function.getNameCString()+" is redeclared\n    "+getCodeLineAt(loc)+"\n";
        for(unsigned int i = 0 ; i != loc.col-1 ; i++){
            error+=" ";
        }error+="    ^";
        errorMessageStack.emplace_back(error);
        hasError = false;        
    }
    else{
        auto tmp = new SymbolEntry(p_function.getNameCString(),
                                SymbolEntry::SymbolsKind::kFunction,
                                symbaol_table_manager->getLevel(),
                                p_function.getReturnType(),
                                p_function.getPrototypePTypeVec());
        p = tmp;                                    
        symbaol_table_manager->acceptSymbolEntry(tmp);
    }
    hasParametersFlag = true;//p_function.hasPrameters();

    if(p_function.isDefined())
    {
        compound_floor --; //avoiding definition compound statement increment
        funcNodeEntry.emplace_back(p);
    }
//1
    symbaol_table_manager->push(new SymbolTable());
//2
//3 
    p_function.visitChildNodes(*this);
    
    if(p_function.isDefined())
    {
        funcNodeEntry.pop_back();
    }

//4
//5
    if(!p_function.isDefined())
        symbaol_table_manager->pop();
}

void SemanticAnalyzer::visit(CompoundStatementNode &p_compound_statement) {
    compound_floor++;//indictor for how deep we are
    isForLoopAssign = false;// entering compund indicates leaving forLoop decl/assignemt 
//1
    if(!hasParametersFlag)
        symbaol_table_manager->push(new SymbolTable());
    hasParametersFlag = false;
//2
//3
    p_compound_statement.visitChildNodes(*this);
//4

//5
    symbaol_table_manager->pop();
    compound_floor--;//indicator for how deep we are
}

void SemanticAnalyzer::visit(PrintNode &p_print) {
    /*3-----------------visit child----------------*/
    p_print.visitChildNodes(*this);
    /*4 ----------------semantic analyses----------------*/
    bool hasError = false;
    // bool errChild = error_manager[error_manager.size()-1];
    Expr_type_msgr* msg = expr_type_manager[expr_type_manager.size()-1];
    PTypeSharedPtr child = expr_type_manager[expr_type_manager.size()-1]->type;

    if( child->getDimensions().size() != 0 )
    {
        hasError = true;
    }
    if(hasError)
    {
        std::string error;
        Location loc = msg->location;
        error = "<Error> Found in line "+std::to_string(loc.line)+", column "+std::to_string(loc.col)
                +": expression of print statement must be scalar type "
                +"\n    "+getCodeLineAt(loc)+"\n";
        for(unsigned int i = 0 ; i != loc.col-1 ; i++){
            error+=" ";
        }error+="    ^";
        errorMessageStack.emplace_back(error);
        resetExprManager(expr_type_manager,1);
        resetErrorManager(error_manager,1);
        error_manager.emplace_back(hasError);
        PType* typeOfRef = new PType(PType::PrimitiveTypeEnum::kVoidType);//dummy to avoid segamentation fault
        expr_type_manager.emplace_back( new Expr_type_msgr(p_print.getLocation(),typeOfRef));
        return;
    }

    PType* typeOfRef = nullptr;

    if(typeOfRef == nullptr)
        typeOfRef = new PType(PType::PrimitiveTypeEnum::kVoidType);//dummy to avoid segamentation fault
    resetExprManager(expr_type_manager,1);
    resetErrorManager(error_manager,1);
    error_manager.emplace_back(hasError);
    expr_type_manager.emplace_back( new Expr_type_msgr(p_print.getLocation(),typeOfRef));
    return ;
}

void SemanticAnalyzer::visit(BinaryOperatorNode &p_bin_op) {
        
    bool hasError = false;
    bool isArithmetic = ((p_bin_op.getOp() == Operator::kMultiplyOp)||
                        (p_bin_op.getOp() == Operator::kDivideOp)||
                        (p_bin_op.getOp() == Operator::kPlusOp)||
                        (p_bin_op.getOp() == Operator::kMinusOp));
    bool isBoolOperator = ((p_bin_op.getOp() == Operator::kOrOp)||
                          (p_bin_op.getOp() == Operator::kAndOp)||
                          (p_bin_op.getOp() == Operator::kNotOp));
    bool isRelational = ((p_bin_op.getOp() == Operator::kNotEqualOp)||
                        (p_bin_op.getOp() == Operator::kEqualOp)||
                        (p_bin_op.getOp() == Operator::kGreaterOrEqualOp)||
                        (p_bin_op.getOp() == Operator::kGreaterOp)||
                        (p_bin_op.getOp() == Operator::kLessOrEqualOp)||
                        (p_bin_op.getOp() == Operator::kLessOp));                      
    bool isMod = p_bin_op.getOp() == Operator::kModOp;

    p_bin_op.visitChildNodes(*this);



/*    for(auto iterator = expr_type_manager.rbegin() ; iterator != expr_type_manager.rbegin() + 2 ; iterator++)
    {
        printf("\texpr found in %d,%d \n",(*iterator)->location.line,(*iterator)->location.col);
    }
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");*/

    PTypeSharedPtr left = expr_type_manager[expr_type_manager.size()-2]->type;
    PTypeSharedPtr right = expr_type_manager[expr_type_manager.size()-1]->type;

    // printf("%d,%d ::: %s<->%s\n",expr_type_manager[expr_type_manager.size()-2]->location.line 
    //                             ,expr_type_manager[expr_type_manager.size()-2]->location.col
    //                             , left->getPTypeCString(),right->getPTypeCString());
    // printf("\t%s\n", (*left)==(*right) ? "true" : "false" );

    bool errLeft = error_manager[error_manager.size()-2];
    bool errRight = error_manager[error_manager.size()-1];

    if(errLeft || errRight)
    {   
        resetExprManager(expr_type_manager,2);
        resetErrorManager(error_manager,2);
        error_manager.emplace_back(true);
        PType* typeOfRef = new PType(PType::PrimitiveTypeEnum::kVoidType);//dummy to avoid segamentation fault
        expr_type_manager.emplace_back( new Expr_type_msgr(p_bin_op.getLocation(),typeOfRef));
        return;
    }

    //Arithmetic operator : Operands must be an integer or real type
    PType* typeOfRef = nullptr;
    if( isArithmetic && left->isNumericScalar() && right->isNumericScalar() )
    {   
        if( left->getPrimitiveType() == PType::PrimitiveTypeEnum::kRealType ||  right->getPrimitiveType() == PType::PrimitiveTypeEnum::kRealType )
            typeOfRef = new PType(PType::PrimitiveTypeEnum::kRealType);
        typeOfRef = new PType(PType::PrimitiveTypeEnum::kIntegerType);
    }
    //string concatenation
    else if( (p_bin_op.getOp() == Operator::kPlusOp ) && left->isStringScalar() && right->isStringScalar() )
    {   
        typeOfRef = new PType(PType::PrimitiveTypeEnum::kStringType);
    }
    else if(isBoolOperator && left->isBoolScalar() && right->isBoolScalar())
    {
        typeOfRef = new PType(PType::PrimitiveTypeEnum::kBoolType);        
    }
    else if(isRelational && left->isNumericScalar() && right->isNumericScalar())
    {
        typeOfRef = new PType(PType::PrimitiveTypeEnum::kBoolType);                
    }
    else if(isMod && left->isIntegerScalr() && right->isIntegerScalr() )
    {
        typeOfRef = new PType(PType::PrimitiveTypeEnum::kIntegerType);
    }
    else if(isArithmetic || isBoolOperator ||isRelational || isMod)
    {   
        // typeOfRef = new PType(PType::PrimitiveTypeEnum::kVoidType);//dummy to avoid segamentation fault
        hasError = true;        
    }
    if(hasError)
    {
        std::string error;
        Location loc = p_bin_op.getLocation();
        error = "<Error> Found in line "+std::to_string(loc.line)+", column "+std::to_string(loc.col)
                +": invalid operands to binary operator \'"+p_bin_op.getOpCString()+"\' (\'"+left->getPTypeCString()+"\' and \'"+right->getPTypeCString()
                +"\')"
                +"\n    "+getCodeLineAt(loc)+"\n";
        for(unsigned int i = 0 ; i != loc.col-1 ; i++){
            error+=" ";
        }error+="    ^";
        
        errorMessageStack.emplace_back(error);
        resetExprManager(expr_type_manager,2);
        resetErrorManager(error_manager,2);
        error_manager.emplace_back(hasError);
        typeOfRef = new PType(PType::PrimitiveTypeEnum::kVoidType);//dummy to avoid segamentation fault
        expr_type_manager.emplace_back( new Expr_type_msgr(p_bin_op.getLocation(),typeOfRef));
        return ;
    }

    if(typeOfRef == nullptr)
        typeOfRef = new PType(PType::PrimitiveTypeEnum::kVoidType);//dummy to avoid segamentation fault
    resetExprManager(expr_type_manager,2);
    resetErrorManager(error_manager,2);
    error_manager.emplace_back(hasError);
    expr_type_manager.emplace_back( new Expr_type_msgr(p_bin_op.getLocation(),typeOfRef));
    return ;
    /*routine of leaving: reset reset push push */

}

void SemanticAnalyzer::visit(UnaryOperatorNode &p_un_op) {

    bool hasError = false;
    /*3-----------visit childen node ------------------- */
    p_un_op.visitChildNodes(*this);
    /*4 ----------------semantic analyses----------------*/
    bool isNegOperator = p_un_op.getOp() == Operator::kNegOp;
    bool isBoolOperator = p_un_op.getOp() == Operator::kNotOp;
    PTypeSharedPtr child = expr_type_manager[expr_type_manager.size()-1]->type;
    bool errChild = error_manager[error_manager.size()-1];
    PType* typeOfRef = nullptr;

    if(errChild)
    {
        resetExprManager(expr_type_manager,1);
        resetErrorManager(error_manager,1);
        error_manager.emplace_back(true);
        typeOfRef = new PType(PType::PrimitiveTypeEnum::kVoidType);//dummy to avoid segamentation fault
        expr_type_manager.emplace_back( new Expr_type_msgr(p_un_op.getLocation(),typeOfRef));
        return ;
    }

    if(isNegOperator && child->isNumericScalar())
    {
        typeOfRef = new PType(child->getPrimitiveType());        
    }
    else if(isBoolOperator && child-> isBoolScalar())
    {
        typeOfRef = new PType(PType::PrimitiveTypeEnum::kBoolType);
    }
    else if(isNegOperator || isBoolOperator)
    {
        hasError = true;
    }
    if(hasError)
    {
        std::string error;
        Location loc = p_un_op.getLocation();
        error = "<Error> Found in line "+std::to_string(loc.line)+", column "+std::to_string(loc.col)
                +": invalid operand to unary operator \'"+p_un_op.getOpCString()+"\' (\'"+child->getPTypeCString()
                +"\')"
                +"\n    "+getCodeLineAt(loc)+"\n";
        for(unsigned int i = 0 ; i != loc.col-1 ; i++){
            error+=" ";
        }error+="    ^";
        
        errorMessageStack.emplace_back(error);
        resetExprManager(expr_type_manager,1);
        resetErrorManager(error_manager,1);
        error_manager.emplace_back(hasError);
        typeOfRef = new PType(PType::PrimitiveTypeEnum::kVoidType);//dummy to avoid segamentation fault
        expr_type_manager.emplace_back( new Expr_type_msgr(p_un_op.getLocation(),typeOfRef));
        return ;
    }


    resetExprManager(expr_type_manager,1);
    resetErrorManager(error_manager,1);
    error_manager.emplace_back(hasError);
    expr_type_manager.emplace_back( new Expr_type_msgr(p_un_op.getLocation(),typeOfRef));

}

void SemanticAnalyzer::visit(FunctionInvocationNode &p_func_invocation) {
    
    bool hasError = false;
    SymbolEntry* p = symbaol_table_manager->lookup(p_func_invocation.getNameCString(),true);
    size_t argNum = p_func_invocation.getArgumentNum();
    /*-------------- visit child node -----------*/
    p_func_invocation.visitChildNodes(*this);
    /*------------- semantic analysis -----------*/
    //The identifier has to be in symbol tables.
    if(p == nullptr)hasError = true;
    if(hasError)
    {
        std::string error;
        Location loc = p_func_invocation.getLocation();
        error = "<Error> Found in line "+std::to_string(loc.line)+", column "+std::to_string(loc.col)
                +": use of undeclared symbol \'"+p_func_invocation.getNameCString()+"\'\n    "+getCodeLineAt(loc)+"\n";
        for(unsigned int i = 0 ; i != loc.col-1 ; i++){
            error+=" ";
        }error+="    ^";
        errorMessageStack.emplace_back(error);
        resetExprManager(expr_type_manager,argNum);
        resetErrorManager(error_manager,argNum);
        error_manager.emplace_back(hasError);
        PType* typeOfRef = new PType(PType::PrimitiveTypeEnum::kVoidType);//dummy to avoid segamentation fault
        expr_type_manager.emplace_back( new Expr_type_msgr(p_func_invocation.getLocation(),typeOfRef));
        return;
    }
    //The kind of symbol has to be function.
    if(p->getKind() != SymbolEntry::SymbolsKind::kFunction )
        hasError = true;
    if(hasError)
    {
        std::string error;
        Location loc = p_func_invocation.getLocation();
        error = "<Error> Found in line "+std::to_string(loc.line)+", column "+std::to_string(loc.col)
                +": call of non-function symbol \'"+p_func_invocation.getNameCString()+"\'\n    "+getCodeLineAt(loc)+"\n";
        for(unsigned int i = 0 ; i != loc.col-1 ; i++){
            error+=" ";
        }error+="    ^";
        errorMessageStack.emplace_back(error);
        resetExprManager(expr_type_manager,argNum);
        resetErrorManager(error_manager,argNum);
        error_manager.emplace_back(hasError);
        PType* typeOfRef = new PType(PType::PrimitiveTypeEnum::kVoidType);//dummy to avoid segamentation fault
        expr_type_manager.emplace_back( new Expr_type_msgr(p_func_invocation.getLocation(),typeOfRef));
        return ;
    }
    //The number of arguments must be the same as one of the parameters.
    std::vector<PTypeSharedPtr> prototypePTypeVec = p->getPrototypePTypeVec();
    if( argNum != prototypePTypeVec.size())hasError = true;
    if(hasError)
    {
        std::string error;
        Location loc = p_func_invocation.getLocation();
        error = "<Error> Found in line "+std::to_string(loc.line)+", column "+std::to_string(loc.col)
                +": too few/much arguments provided for function \'"+p_func_invocation.getNameCString()+"\'\n    "+getCodeLineAt(loc)+"\n";
        for(unsigned int i = 0 ; i != loc.col-1 ; i++){
            error+=" ";
        }error+="    ^";
        errorMessageStack.emplace_back(error);
        resetExprManager(expr_type_manager,argNum);
        resetErrorManager(error_manager,argNum);
        error_manager.emplace_back(hasError);
        PType* typeOfRef = new PType(PType::PrimitiveTypeEnum::kVoidType);//dummy to avoid segamentation fault
        expr_type_manager.emplace_back( new Expr_type_msgr(p_func_invocation.getLocation(),typeOfRef));
        return ;
    }
    //The type of the result of the expression (argument) must be the same type 
    Expr_type_msgr* msg = nullptr;
    size_t i = 0;
    for( i = 0 ; i != argNum ; i++)
    {   
        msg = expr_type_manager[expr_type_manager.size()-argNum+i]; 
        if( !((*prototypePTypeVec[i]) == *(msg->type))) {
            hasError = true;
            break;
        }
    }
    if(hasError)
    {
        std::string error;
        Location loc = msg->location;
        error = "<Error> Found in line "+std::to_string(loc.line)+", column "+std::to_string(loc.col)
                +": incompatible type passing \'"+msg->type->getPTypeCString()+"\' to parameter of type \'"
                +prototypePTypeVec[i]->getPTypeCString()
                +"\'\n    "+getCodeLineAt(loc)+"\n";
        for(unsigned int i = 0 ; i != loc.col-1 ; i++){
            error+=" ";
        }error+="    ^";
        errorMessageStack.emplace_back(error);
        resetExprManager(expr_type_manager,argNum);
        resetErrorManager(error_manager,argNum);
        error_manager.emplace_back(hasError);
        PType* typeOfRef = new PType(PType::PrimitiveTypeEnum::kVoidType);//dummy to avoid segamentation fault
        expr_type_manager.emplace_back( new Expr_type_msgr(p_func_invocation.getLocation(),typeOfRef));
        return ;       
    }

    resetExprManager(expr_type_manager,argNum);
    resetErrorManager(error_manager,argNum);
    error_manager.emplace_back(hasError);
    expr_type_manager.emplace_back(new Expr_type_msgr(p_func_invocation.getLocation(),p->getType()));
    return;
}

void SemanticAnalyzer::visit(VariableReferenceNode &p_variable_ref) {
    //1,2
    /*3 ----------------Travere child nodes----------------*/
    p_variable_ref.visitChildNodes(*this);
    /*4 ----------------semantic analyses----------------*/
    bool hasError = false;
    size_t indiceDim = p_variable_ref.getDim();//number of indice to dereference 
    PType* typeOfRef = nullptr;

    //The identifier has to be in symbol tables
    SymbolEntry* p = symbaol_table_manager->lookup(p_variable_ref.getNameCString(),true);
    if(p == nullptr)hasError = true;
    if(hasError)
    {
        std::string error;
        Location loc = p_variable_ref.getLocation();
        error = "<Error> Found in line "+std::to_string(loc.line)+", column "+std::to_string(loc.col)
                +": use of undeclared symbol \'"+p_variable_ref.getNameCString()+"\'\n    "+getCodeLineAt(loc)+"\n";
        for(unsigned int i = 0 ; i != loc.col-1 ; i++){
            error+=" ";
        }error+="    ^";
        errorMessageStack.emplace_back(error);
        resetExprManager(expr_type_manager,indiceDim);
        resetErrorManager(error_manager,indiceDim);
        error_manager.emplace_back(hasError);
        typeOfRef = new PType(PType::PrimitiveTypeEnum::kVoidType);//dummy to avoid segamentation fault
        expr_type_manager.emplace_back( new Expr_type_msgr(p_variable_ref.getLocation(),typeOfRef));
        return;
    }
    //The kind of symbol has to be a parameter, variable, loop_var, or constant.
    if(p->getKind() == SymbolEntry::SymbolsKind::kFunction || p->getKind() == SymbolEntry::SymbolsKind::kProgram)
        hasError = true;
    if(hasError)
    {
        std::string error;
        Location loc = p_variable_ref.getLocation();
        error = "<Error> Found in line "+std::to_string(loc.line)+", column "+std::to_string(loc.col)
                +": use of non-variable symbol \'"+p_variable_ref.getNameCString()+"\'\n    "+getCodeLineAt(loc)+"\n";
        for(unsigned int i = 0 ; i != loc.col-1 ; i++){
            error+=" ";
        }error+="    ^";
        errorMessageStack.emplace_back(error);
        resetExprManager(expr_type_manager,indiceDim);
        resetErrorManager(error_manager,indiceDim);
        error_manager.emplace_back(hasError);
        typeOfRef = new PType(PType::PrimitiveTypeEnum::kVoidType);//dummy to avoid segamentation fault
        expr_type_manager.emplace_back( new Expr_type_msgr(p_variable_ref.getLocation(),typeOfRef));
        return ;
    }
    //There is no error in the node of the declaration of this symbol. 
    if(p->getHasErrorDeclared()){
        resetExprManager(expr_type_manager,indiceDim);
        resetErrorManager(error_manager,indiceDim);        
        error_manager.emplace_back(true);
        typeOfRef = new PType(PType::PrimitiveTypeEnum::kVoidType);//dummy to avoid segamentation fault
        expr_type_manager.emplace_back( new Expr_type_msgr(p_variable_ref.getLocation(),typeOfRef));
        return;
    }
    //Each index of an array reference must be of the integer type. 
    Expr_type_msgr* ptr;
    for(auto iterator = expr_type_manager.rbegin() ; iterator != expr_type_manager.rbegin() + indiceDim ; iterator++)
    {   
        if( (*iterator)->type->getPrimitiveType() != PType::PrimitiveTypeEnum::kIntegerType)
        {
            ptr = (*iterator);
            hasError = true;
            break;
        }
    }
    if(hasError)
    {
        std::string error;
        Location loc = ptr->location;
        error = "<Error> Found in line "+std::to_string(loc.line)+", column "+std::to_string(loc.col)
                +": index of array reference must be an integer"+"\n    "+getCodeLineAt(loc)+"\n";
        for(unsigned int i = 0 ; i != loc.col-1; i++){
            error+=" ";
        }
        error+="    ^";
        errorMessageStack.emplace_back(error);  
        resetExprManager(expr_type_manager,indiceDim);
        resetErrorManager(error_manager,indiceDim);        
        error_manager.emplace_back(hasError);
        typeOfRef = new PType(PType::PrimitiveTypeEnum::kVoidType);//dummy to avoid segamentation fault
        expr_type_manager.emplace_back( new Expr_type_msgr(p_variable_ref.getLocation(),typeOfRef));
        return;
    }
    //An over array subscript is forbidden
    if(indiceDim > p->getType()->getDimensions().size())hasError = true;
    if(hasError)
    {
        std::string error;
        Location loc = p_variable_ref.getLocation();
        error = "<Error> Found in line "+std::to_string(loc.line)+", column "+std::to_string(loc.col)
                +": there is an over array subscript on \'"+p_variable_ref.getNameCString()+"\'\n    "+getCodeLineAt(loc)+"\n";
        for(unsigned int i = 0 ; i != loc.col-1 ; i++){
            error+=" ";
        }error+="    ^";
        errorMessageStack.emplace_back(error); 
        resetExprManager(expr_type_manager,indiceDim);
        resetErrorManager(error_manager,indiceDim);        
        error_manager.emplace_back(hasError);        
        typeOfRef = new PType(PType::PrimitiveTypeEnum::kVoidType);//dummy to avoid segamentation fault
        expr_type_manager.emplace_back( new Expr_type_msgr(p_variable_ref.getLocation(),typeOfRef));
        return ;        
    }

    resetExprManager(expr_type_manager,indiceDim);
    resetErrorManager(error_manager,indiceDim);

    //to get dereferenced type of the Variable reference, and push back
    typeOfRef = new PType(p->getType()->getPrimitiveType());
    std::vector<uint64_t> dimensions = p->getType()->getDimensions();
    // dimensions.erase(dimensions.begin(),dimensions.begin()+indiceDim);
    for(size_t i = 0 ; i != indiceDim ; i++)
    {
        dimensions.erase(dimensions.begin());
        // dimensions.pop_back();
    }
    typeOfRef->setDimensions(dimensions);
    error_manager.emplace_back(hasError);
    // printf("\t%p\n", p );
    expr_type_manager.emplace_back( new Expr_type_msgr(p_variable_ref.getLocation(),/*TODO here->*/typeOfRef ,p));
    
    // printf("\t%s\n",typeOfRef->getPTypeCString() );
    // printf("\t\t origin : %s\n",p->getType()->getPTypeCString() );

}

void SemanticAnalyzer::visit(AssignmentNode &p_assignment) {
    /*4 ----------------semantic analyses----------------*/
    p_assignment.visitChildNodes(*this);

    bool hasError = false;
    PTypeSharedPtr left = expr_type_manager[expr_type_manager.size()-2]->type;
    PTypeSharedPtr right = expr_type_manager[expr_type_manager.size()-1]->type;

    bool errLeft = error_manager[error_manager.size()-2];
    bool errRight = error_manager[error_manager.size()-1];

    //There is no error in the node of the variable reference
    if(errLeft)
    {
        hasError = true;
    }
    if(hasError)
    {
        resetExprManager(expr_type_manager,2);
        resetErrorManager(error_manager,2);
        error_manager.emplace_back(hasError);
        PType* typeOfRef = new PType(PType::PrimitiveTypeEnum::kVoidType);//dummy to avoid segamentation fault
        expr_type_manager.emplace_back( new Expr_type_msgr(p_assignment.getLocation(),typeOfRef));
        return;        
    }
    //The type of the result of the variable reference cannot be an array type
    if(left->getDimensions().size() != 0)
    {
        hasError = true;
    }
    if(hasError)
    {
        std::string error;
        Location loc = expr_type_manager[expr_type_manager.size()-2]->location;
        error = "<Error> Found in line "+std::to_string(loc.line)+", column "+std::to_string(loc.col)
                +": array assignment is not allowed "
                +"\n    "+getCodeLineAt(loc)+"\n";
        for(unsigned int i = 0 ; i != loc.col-1 ; i++){
            error+=" ";
        }error+="    ^";
        errorMessageStack.emplace_back(error);

        resetExprManager(expr_type_manager,2);
        resetErrorManager(error_manager,2);
        error_manager.emplace_back(hasError);
        PType* typeOfRef = new PType(PType::PrimitiveTypeEnum::kVoidType);//dummy to avoid segamentation fault
        expr_type_manager.emplace_back( new Expr_type_msgr(p_assignment.getLocation(),typeOfRef));
        return;
    }
    //The variable reference cannot be a reference to a constant variable
    auto leftMsg = expr_type_manager[expr_type_manager.size()-2];
    auto rightMsg = expr_type_manager[expr_type_manager.size()-1];
    if( leftMsg->p && leftMsg->p->getKind() == SymbolEntry::SymbolsKind::kConstant )
    {
        hasError = true;
    }
    if(hasError)
    {
        std::string error;
        Location loc = leftMsg->location;
        error = "<Error> Found in line "+std::to_string(loc.line)+", column "+std::to_string(loc.col)
                +": cannot assign to variable \'"+leftMsg->p->getName()+"\' which is a constant"
                +"\n    "+getCodeLineAt(loc)+"\n";
        for(unsigned int i = 0 ; i != loc.col-1 ; i++){
            error+=" ";
        }error+="    ^";
        errorMessageStack.emplace_back(error);

        resetExprManager(expr_type_manager,2);
        resetErrorManager(error_manager,2);
        error_manager.emplace_back(hasError);
        PType* typeOfRef = new PType(PType::PrimitiveTypeEnum::kVoidType);//dummy to avoid segamentation fault
        expr_type_manager.emplace_back( new Expr_type_msgr(p_assignment.getLocation(),typeOfRef));
        return;   
    }
    //The variable reference cannot be a reference to a loop variable when the context is within a loop body.
    if( !isForLoopAssign && leftMsg->p && leftMsg->p->getKind() == SymbolEntry::SymbolsKind::kLoopVar)
    {
        std::string error;
        Location loc = leftMsg->location;
        error = "<Error> Found in line "+std::to_string(loc.line)+", column "+std::to_string(loc.col)
                +": the value of loop variable cannot be modified inside the loop body"
                +"\n    "+getCodeLineAt(loc)+"\n";
        for(unsigned int i = 0 ; i != loc.col-1 ; i++){
            error+=" ";
        }error+="    ^";
        errorMessageStack.emplace_back(error);

        resetExprManager(expr_type_manager,2);
        resetErrorManager(error_manager,2);
        error_manager.emplace_back(hasError);
        PType* typeOfRef = new PType(PType::PrimitiveTypeEnum::kVoidType);//dummy to avoid segamentation fault
        expr_type_manager.emplace_back( new Expr_type_msgr(p_assignment.getLocation(),typeOfRef));
        return; 
    }
    //There is no error in the node of the expression
    if(errRight)
    {
        hasError = true;
    }
    if(hasError)
    {
        resetExprManager(expr_type_manager,2);
        resetErrorManager(error_manager,2);
        error_manager.emplace_back(hasError);
        PType* typeOfRef = new PType(PType::PrimitiveTypeEnum::kVoidType);//dummy to avoid segamentation fault
        expr_type_manager.emplace_back( new Expr_type_msgr(p_assignment.getLocation(),typeOfRef));
        return;        
    }
    //The type of the result of the expression cannot be an array type.
    if(right->getDimensions().size() != 0)
    {
        hasError = true;
    }
    if(hasError)
    {
        std::string error;
        Location loc = expr_type_manager[expr_type_manager.size()-1]->location;
        error = "<Error> Found in line "+std::to_string(loc.line)+", column "+std::to_string(loc.col)
                +": array assignment is not allowed "
                +"\n    "+getCodeLineAt(loc)+"\n";
        for(unsigned int i = 0 ; i != loc.col-1 ; i++){
            error+=" ";
        }error+="    ^";
        errorMessageStack.emplace_back(error);

        resetExprManager(expr_type_manager,2);
        resetErrorManager(error_manager,2);
        error_manager.emplace_back(hasError);
        PType* typeOfRef = new PType(PType::PrimitiveTypeEnum::kVoidType);//dummy to avoid segamentation fault
        expr_type_manager.emplace_back( new Expr_type_msgr(p_assignment.getLocation(),typeOfRef));
        return;
    }
    if( !(leftMsg->type == rightMsg->type) )
    {
        hasError = true;
        if( (isNumericScalar(leftMsg->type) && isNumericScalar(rightMsg->type)) )
        {
            hasError = false;
        }
    }
    if(hasError)
    {
        std::string error;
        Location loc = p_assignment.getLocation();
        error = "<Error> Found in line "+std::to_string(loc.line)+", column "+std::to_string(loc.col)
                +": assigning to \'"+leftMsg->type->getPTypeCString()+"\' from incompatible type \'"
                +rightMsg->type->getPTypeCString()
                +"\'\n    "+getCodeLineAt(loc)+"\n";
        for(unsigned int i = 0 ; i != loc.col-1 ; i++){
            error+=" ";
        }error+="    ^";
        errorMessageStack.emplace_back(error);

        resetExprManager(expr_type_manager,2);
        resetErrorManager(error_manager,2);
        error_manager.emplace_back(hasError);
        PType* typeOfRef = new PType(PType::PrimitiveTypeEnum::kVoidType);//dummy to avoid segamentation fault
        expr_type_manager.emplace_back( new Expr_type_msgr(p_assignment.getLocation(),typeOfRef));
        return;

    }


    PType* typeOfRef = new PType(PType::PrimitiveTypeEnum::kVoidType);//dummy to avoid segamentation fault
    resetExprManager(expr_type_manager,2);
    resetErrorManager(error_manager,2);
    error_manager.emplace_back(hasError);
    expr_type_manager.emplace_back( new Expr_type_msgr(p_assignment.getLocation(),typeOfRef));
    return ;    

}

void SemanticAnalyzer::visit(ReadNode &p_read) {
    /*4 ----------------semantic analyses----------------*/
    p_read.visitChildNodes(*this);
    bool hasError = false;
    // bool errChild = error_manager[error_manager.size()-1];
    Expr_type_msgr* msg = expr_type_manager[expr_type_manager.size()-1];
    PTypeSharedPtr child = expr_type_manager[expr_type_manager.size()-1]->type;

    if( child->getDimensions().size() != 0 )
    {
        hasError = true;
    }
    if(hasError)
    {
        std::string error;
        Location loc = msg->location;
        error = "<Error> Found in line "+std::to_string(loc.line)+", column "+std::to_string(loc.col)
                +": variable reference of read statement must be scalar type "
                +"\n    "+getCodeLineAt(loc)+"\n";
        for(unsigned int i = 0 ; i != loc.col-1 ; i++){
            error+=" ";
        }error+="    ^";
        errorMessageStack.emplace_back(error);
        resetExprManager(expr_type_manager,1);
        resetErrorManager(error_manager,1);
        error_manager.emplace_back(hasError);
        PType* typeOfRef = new PType(PType::PrimitiveTypeEnum::kVoidType);//dummy to avoid segamentation fault
        expr_type_manager.emplace_back( new Expr_type_msgr(p_read.getLocation(),typeOfRef));
        return;
    }
    //variable reference of read statement cannot be a constant or loop variable
    if( (msg->p) && (msg->p->getKind() == SymbolEntry::SymbolsKind::kLoopVar|| msg->p->getKind() == SymbolEntry::SymbolsKind::kConstant))
        hasError = true;
    if(hasError)
    {
        std::string error;
        Location loc = msg->location;
        error = "<Error> Found in line "+std::to_string(loc.line)+", column "+std::to_string(loc.col)
                +": variable reference of read statement cannot be a constant or loop variable "
                +"\n    "+getCodeLineAt(loc)+"\n";
        for(unsigned int i = 0 ; i != loc.col-1 ; i++){
            error+=" ";
        }error+="    ^";
        errorMessageStack.emplace_back(error);
        resetExprManager(expr_type_manager,1);
        resetErrorManager(error_manager,1);
        error_manager.emplace_back(hasError);
        PType* typeOfRef = new PType(PType::PrimitiveTypeEnum::kVoidType);//dummy to avoid segamentation fault
        expr_type_manager.emplace_back( new Expr_type_msgr(p_read.getLocation(),typeOfRef));
        return;
    }

    PType* typeOfRef = nullptr;

    if(typeOfRef == nullptr)
        typeOfRef = new PType(PType::PrimitiveTypeEnum::kVoidType);//dummy to avoid segamentation fault
    resetExprManager(expr_type_manager,1);
    resetErrorManager(error_manager,1);
    error_manager.emplace_back(hasError);
    expr_type_manager.emplace_back( new Expr_type_msgr(p_read.getLocation(),typeOfRef));
    return ;
}

void SemanticAnalyzer::visit(IfNode &p_if) {


    p_if.visitChildNodes(*this);

    bool hasError = false;
    PTypeSharedPtr conditionKid = expr_type_manager[expr_type_manager.size()-1]->type;
    auto msg = expr_type_manager[expr_type_manager.size()-1];

    bool errCon= error_manager[error_manager.size()-1];

    if(errCon)
    {
        hasError = true;
    }
    if(hasError)
    {
        resetExprManager(expr_type_manager,1);
        resetErrorManager(error_manager,1);
        error_manager.emplace_back(hasError);
        PType* typeOfRef = new PType(PType::PrimitiveTypeEnum::kVoidType);//dummy to avoid segamentation fault
        expr_type_manager.emplace_back( new Expr_type_msgr(p_if.getLocation(),typeOfRef));
        
        // symbaol_table_manager->pop();
        return;
    }
    //The type of the result of the expression (condition) must be boolean type.
    if(conditionKid->getPrimitiveType() != PType::PrimitiveTypeEnum::kBoolType)
    {
        hasError = true;
    }
    if(hasError)
    {
        std::string error;
        Location loc = msg->location;
        error = "<Error> Found in line "+std::to_string(loc.line)+", column "+std::to_string(loc.col)
                +": the expression of condition must be boolean type "
                +"\n    "+getCodeLineAt(loc)+"\n";
        for(unsigned int i = 0 ; i != loc.col-1 ; i++){
            error+=" ";
        }error+="    ^";
        errorMessageStack.emplace_back(error);
        resetExprManager(expr_type_manager,1);
        resetErrorManager(error_manager,1);
        error_manager.emplace_back(hasError);
        PType* typeOfRef = new PType(PType::PrimitiveTypeEnum::kVoidType);//dummy to avoid segamentation fault
        expr_type_manager.emplace_back( new Expr_type_msgr(p_if.getLocation(),typeOfRef));
        
        // symbaol_table_manager->pop();
        return;
    }

        
    resetExprManager(expr_type_manager,1);
    resetErrorManager(error_manager,1);
    error_manager.emplace_back(hasError);
    PType* typeOfRef = new PType(PType::PrimitiveTypeEnum::kVoidType);//dummy to avoid segamentation fault
    expr_type_manager.emplace_back( new Expr_type_msgr(p_if.getLocation(),typeOfRef));


    // symbaol_table_manager->pop();   
    return;

}

void SemanticAnalyzer::visit(WhileNode &p_while) {
    
    p_while.visitChildNodes(*this);
    bool hasError = false;
    PTypeSharedPtr conditionKid = expr_type_manager[expr_type_manager.size()-1]->type;
    auto msg = expr_type_manager[expr_type_manager.size()-1];

    bool errCon= error_manager[error_manager.size()-1];

    if(errCon)
    {
        hasError = true;
    }
    if(hasError)
    {
        resetExprManager(expr_type_manager,1);
        resetErrorManager(error_manager,1);
        error_manager.emplace_back(hasError);
        PType* typeOfRef = new PType(PType::PrimitiveTypeEnum::kVoidType);//dummy to avoid segamentation fault
        expr_type_manager.emplace_back( new Expr_type_msgr(p_while.getLocation(),typeOfRef));
        
        // symbaol_table_manager->pop();
        return;
    }
    //The type of the result of the expression (condition) must be boolean type.
    if(conditionKid->getPrimitiveType() != PType::PrimitiveTypeEnum::kBoolType)
    {
        hasError = true;
    }
    if(hasError)
    {
        std::string error;
        Location loc = msg->location;
        error = "<Error> Found in line "+std::to_string(loc.line)+", column "+std::to_string(loc.col)
                +": the expression of condition must be boolean type "
                +"\n    "+getCodeLineAt(loc)+"\n";
        for(unsigned int i = 0 ; i != loc.col-1 ; i++){
            error+=" ";
        }error+="    ^";
        errorMessageStack.emplace_back(error);
        resetExprManager(expr_type_manager,1);
        resetErrorManager(error_manager,1);
        error_manager.emplace_back(hasError);
        PType* typeOfRef = new PType(PType::PrimitiveTypeEnum::kVoidType);//dummy to avoid segamentation fault
        expr_type_manager.emplace_back( new Expr_type_msgr(p_while.getLocation(),typeOfRef));
        
        // symbaol_table_manager->pop();
        return;
    }

        
    resetExprManager(expr_type_manager,1);
    resetErrorManager(error_manager,1);
    error_manager.emplace_back(hasError);
    PType* typeOfRef = new PType(PType::PrimitiveTypeEnum::kVoidType);//dummy to avoid segamentation fault
    expr_type_manager.emplace_back( new Expr_type_msgr(p_while.getLocation(),typeOfRef));


    // symbaol_table_manager->pop();   
    return;
}

void SemanticAnalyzer::visit(ForNode &p_for) {
    
    bool hasError = false;

    //1
    symbaol_table_manager->push(new SymbolTable());
    isLoopVarFlag = true;
    //2
    //3
    isForLoopAssign = true;
    p_for.visitChildNodes(*this);
    //4
    ConstantValueNode forInit = condition_increment_record[0];
    ConstantValueNode forDestination = condition_increment_record[1];

    int a1 = atoi(forInit.getConstantValueCString());
    int a2 = atoi(forDestination.getConstantValueCString());
    
    if(a1 > a2)
    {
        hasError = true;
    }
    if(hasError)
    {
        std::string error;
        Location loc = p_for.getLocation();
        error = "<Error> Found in line "+std::to_string(loc.line)+", column "+std::to_string(loc.col)
                +": the lower bound and upper bound of iteration count must be in the incremental order "
                +"\n    "+getCodeLineAt(loc)+"\n";
        for(unsigned int i = 0 ; i != loc.col-1 ; i++){
            error+=" ";
        }error+="    ^";
        errorMessageStack.emplace_back(error);
        resetExprManager(expr_type_manager,1);
        resetErrorManager(error_manager,1);
    }


    //5
    condition_increment_record.clear();//clear for_loop increment info
    symbaol_table_manager->pop();
}

void SemanticAnalyzer::visit(ReturnNode &p_return) {

    symbaol_table_manager->resetCurrentSymbolEntry();//only constant variable needs current entry
    /*3-----------visit childen node ------------------- */
    p_return.visitChildNodes(*this);
    /*4 ----------------semantic analyses----------------*/
    bool hasError = false;

    PTypeSharedPtr child = expr_type_manager[expr_type_manager.size()-1]->type;
    bool errChild = error_manager[error_manager.size()-1];
    auto msg =  expr_type_manager[expr_type_manager.size()-1];

    //The current context shouldn't be in the program or a procedure
    if(compound_floor <= 2 && funcNodeEntry.size() == 0 )
    {
        hasError = true;
    }
    if(hasError)
    {
        std::string error;
        Location loc = p_return.getLocation();
        error = "<Error> Found in line "+std::to_string(loc.line)+", column "+std::to_string(loc.col)
                +": program/procedure should not return a value "
                +"\n    "+getCodeLineAt(loc)+"\n";
        for(unsigned int i = 0 ; i != loc.col-1 ; i++){
            error+=" ";
        }error+="    ^";
        errorMessageStack.emplace_back(error);
        resetExprManager(expr_type_manager,1);
        resetErrorManager(error_manager,1);
    }
    //There is no error in the node of the expression
    if(errChild)
    {
        hasError = true;
    }
    if(hasError)
    {
        resetExprManager(expr_type_manager,1);
        resetErrorManager(error_manager,1);
        return;
    }
    //The type of the result of the expression (return value) must be the same type as the return type of current function
    if( (funcNodeEntry.size() != 0) && ( !( *child == *funcNodeEntry[0]->getType()) ))
    {
        hasError = true;
        if( isNumericScalar(child) && isNumericScalar(funcNodeEntry[0]->getType()) )
            hasError = false;
    }
    if(hasError)
    {   
        std::string error;
        Location loc = msg->location;
        error = "<Error> Found in line "+std::to_string(loc.line)+", column "+std::to_string(loc.col)
                +": return \'"+msg->type->getPTypeCString()+"\' from a function with return type \'"
                + (funcNodeEntry[0]->getType()->getPTypeCString())
                +"\'\n    "+getCodeLineAt(loc)+"\n";
        for(unsigned int i = 0 ; i != loc.col-1 ; i++){
            error+=" ";
        }error+="    ^";
        errorMessageStack.emplace_back(error);
        resetExprManager(expr_type_manager,1);
        resetErrorManager(error_manager,1);
    }

}

extern const char* filename;
extern std::string lineBuffer;

const char* SemanticAnalyzer::getCodeLineAt(Location location)
{
    std::ifstream in(filename);
    for(unsigned int i = 0 ; i != location.line ; i++)    {
        getline(in,lineBuffer);
    }
    in.close();
    return lineBuffer.c_str();
}

void SemanticAnalyzer::printErrorMessage()
{
    for(auto m : errorMessageStack)
    {
        fprintf(stderr,"%s\n",m.c_str());
    }
    if(errorMessageStack.empty())
    {
        printf("\n"
       "|---------------------------------------------------|\n"
       "|  There is no syntactic error and semantic error!  |\n"
       "|---------------------------------------------------|\n");
    }
}

