#ifndef __SYMBOLTABLEUTILITY__
#define __SYMBOLTABLEUTILITY__

#include <string>
#include <cstdint>
#include <memory>
#include <vector>
#include <map>

#include <AST/PType.hpp>
#include <AST/constant.hpp>

class SymbolEntry
{
public:
    enum class SymbolsKind : uint8_t {
        kProgram,
        kFunction,
        kParameter,
        kVariable,
        kLoopVar,
        kConstant
    };
    SymbolEntry(const std::string name,SymbolsKind kind,int level,
    	PTypeSharedPtr type,std::shared_ptr<const Constant> attribute);
    // SymbolEntry(const std::string name,SymbolsKind kind,int level,
    // 	PTypeSharedPtr type,std::string prototype);// ready to dicard
    SymbolEntry(const std::string name,SymbolsKind kind,int level,
    	PTypeSharedPtr type,std::vector<PTypeSharedPtr> prototypePTypeVec);    
    SymbolEntry(const std::string name,SymbolsKind kind,int level,
    	PTypeSharedPtr type);    
    // std::string getNameString() const;
    const char *getEntryCString() const;
    void setName(std::string name);
    void setKind(SymbolsKind kind);
    void setLevel(int level);
    void setType(PTypeSharedPtr type);
    void setAttribute(std::shared_ptr<const Constant> attribute);
    void setAttribute(const char* prototype);
    void setHasErrorDeclared();
    std::string getName();
    SymbolsKind getKind();
    int getLevel();
    PTypeSharedPtr getType();
    std::shared_ptr<const Constant> getAttributeConst();
    std::string getAttributePrototype();  
    std::vector<PTypeSharedPtr> getPrototypePTypeVec();
    bool getHasErrorDeclared();  
private:
	/*field of the Entry class*/
	std::string name;
	SymbolsKind kind;
	int level;
	PTypeSharedPtr type;
	std::shared_ptr<const Constant> attribute;
	std::vector<PTypeSharedPtr> prototypePTypeVec;
	bool hasErrorDeclared = false;

	mutable std::string prototype;
	mutable std::string entry_string;

	const char* getPrototypeCStr() const;
};

//typedef std::shared_ptr<SymbolEntry> SymbolEntryPtr;



class SymbolTable
{
public:
	SymbolTable();

	SymbolEntry* lookup(std::string name);// look up within table
	void insert(SymbolEntry* enrty);
	void print();
private:
	void dumpDemarcation(const char chr);
	std::vector<SymbolEntry*> symbalEntries;
	std::map<std::string,SymbolEntry*> symbolEntryMap;
};

//typedef std::shared_ptr<SymbolTable> SymbolTablePtr;

class SymbolTableManger
{
public:
	SymbolTableManger();
	void pop();//print table, and pop table
	void push(SymbolTable* table);
	bool acceptSymbolEntry(SymbolEntry* entry);//check id, loop_var redecl, then accept
	SymbolEntry* lookup(std::string,bool);//look up through tables
	int getLevel();
	SymbolEntry* getcurrentSymbolEntry();
	SymbolTable* getcurrentSymbolTable();
	void resetCurrentSymbolEntry();
private:
	void levelIncrement();
	void levelDecrement();
	std::vector<SymbolTable*> tables;
	SymbolEntry* cuurentSymbolEntry = nullptr;
	int level;
	// std::vector<SymbolTablePtr> forVar

};

#endif