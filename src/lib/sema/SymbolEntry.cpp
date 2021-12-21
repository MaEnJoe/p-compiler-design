#include "sema/SymbolTableUtility.hpp"

//SymbolEntry

SymbolEntry::SymbolEntry(const std::string name,SymbolsKind kind,int level,
	PTypeSharedPtr type,std::shared_ptr<const Constant> attribute)
:name(name),kind(kind),level(level),type(type),attribute(attribute)
{
	this->prototype = "";
}
// SymbolEntry::SymbolEntry(const std::string name,SymbolsKind kind,int level,
// 	PTypeSharedPtr type,std::string prototype)
// :name(name),kind(kind),level(level),type(type),prototype(prototype)
// {
// //attribute default is nullptr
// } //discard
SymbolEntry::SymbolEntry(const std::string name,SymbolsKind kind,int level,
	PTypeSharedPtr type,std::vector<PTypeSharedPtr> prototypePTypeVec)
:name(name),kind(kind),level(level),type(type),prototypePTypeVec(prototypePTypeVec)
{
//attribute default is nullptr
}

SymbolEntry::SymbolEntry(const std::string name,SymbolsKind kind,int level,
	PTypeSharedPtr type)
:name(name),kind(kind),level(level),type(type)	
{
	this->prototype = "";
}

const char *kKindString[] = {"program", "function", "parameter", "variable", "loop_var","constant"};
const char* SymbolEntry::getPrototypeCStr() const
{// get c string from vector of prototype AKA prototypePTypeVec
	for(auto type : prototypePTypeVec)
	{
		prototype += type->getPTypeCString();
		prototype += ", ";
	}
	if (prototype != "") {
		// remove the trailing ", "
        prototype.erase(prototype.end() - 2,
                            prototype.end());
    }
	return prototype.c_str();
}

const char *SymbolEntry::getEntryCString() const
{	
	char str[512];
	sprintf(str,"%-33s%-11s%d%-10s%-17s%-11s",
		name.c_str(),
		kKindString[static_cast<int>(kind)],
		level,(level>0)?"(local)":"(global)",
		type->getPTypeCString(),
		(attribute==nullptr)?getPrototypeCStr():attribute->getConstantValueCString()
		);
	entry_string += std::string(str);
	return entry_string.c_str();
}
void SymbolEntry::setName(std::string name)
{
	this->name = name;
}
void SymbolEntry::setKind(SymbolsKind kind)
{
	this->kind = kind;
}
void SymbolEntry::setLevel(int level)
{
	this->level = level;
}
void SymbolEntry::setType(PTypeSharedPtr type)
{
	this->type = type;
}
void SymbolEntry::setAttribute(std::shared_ptr<const Constant> attribute)
{
	this->attribute = attribute;
}
void SymbolEntry::setAttribute(const char* prototype)
{
	this->prototype = prototype;
}
void SymbolEntry::setHasErrorDeclared()
{
	hasErrorDeclared = true;
}
std::string SymbolEntry::getName()
{
	return name;
}
SymbolEntry::SymbolsKind SymbolEntry::getKind()
{
	return kind;
}
int SymbolEntry::getLevel()
{
	return level;
}
PTypeSharedPtr SymbolEntry::getType()
{
	return type;
}
std::shared_ptr<const Constant> SymbolEntry::getAttributeConst()
{
	return attribute;
}
std::string SymbolEntry::getAttributePrototype()
{
	return prototype;
}    
bool SymbolEntry::getHasErrorDeclared()
{
	return hasErrorDeclared;
}

std::vector<PTypeSharedPtr> SymbolEntry::getPrototypePTypeVec()
{
	return prototypePTypeVec;
}
