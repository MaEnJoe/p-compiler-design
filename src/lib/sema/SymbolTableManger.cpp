#include "sema/SymbolTableUtility.hpp"

// SymbolTableManger

SymbolTableManger::SymbolTableManger()
{
	this->level = 0;
	this->cuurentSymbolEntry = nullptr;
	tables.emplace_back(new SymbolTable());//global

}
void SymbolTableManger::pop()
{	
	tables.back()->print();
	tables.pop_back();
	resetCurrentSymbolEntry();
	levelDecrement();
}//print table, and pop table
void SymbolTableManger::push(SymbolTable* table)
{
	levelIncrement();
	tables.emplace_back(table);
}

typedef std::vector<SymbolTable*>::reverse_iterator tablesIter;
//check id, loop_var redecl, then accept
bool SymbolTableManger::acceptSymbolEntry(SymbolEntry* entry)
{	
/*	if(entry->getKind() == SymbolEntry::SymbolsKind::kLoopVar)//look for loop_var redecl
	{	
		for(tablesIter table = tables.rbegin(); table != tables.rend(); table++)
		// for(auto &table : tables)
		{	
			SymbolEntry* tmp = (*table)->lookup(entry->getName());
			if(tmp && tmp->getKind() == SymbolEntry::SymbolsKind::kLoopVar)
				return false;
		}
	}
	else// look for var redecl
	{
		if(tables.back()->lookup(entry->getName()))
			return false;
	}*/

	/* always search all */
	for(tablesIter table = tables.rbegin(); table != tables.rend(); table++)
	// for(auto &table : tables)
	{	
		SymbolEntry* tmp = (*table)->lookup(entry->getName());
		if(tmp && tmp->getKind() == SymbolEntry::SymbolsKind::kLoopVar)
			return false;
	}	


	tables.back()->insert(entry);
	this->cuurentSymbolEntry = entry;
	return true;
}

//look up through tables
SymbolEntry* SymbolTableManger::lookup(std::string name,bool allKinds)
{
	SymbolEntry* tmp;
	for(tablesIter table = tables.rbegin(); table != tables.rend(); table++)
	{	
		if(table == tables.rbegin()){
			tmp = (*table)->lookup(name);
			if(tmp)
				return tmp;
		}
		else{//looking up in outer scope 
			tmp = (*table)->lookup(name);
			//return only kLoopVar: to avoid loop_var redcl
			if( (!allKinds) && tmp && tmp->getKind() == SymbolEntry::SymbolsKind::kLoopVar)
				return tmp;
			//return all kind: just check whther a cetain symbol exits
			if((allKinds) && tmp)
				return tmp;
		}
	}

	return nullptr;
}
void SymbolTableManger::levelIncrement(){this->level += 1;}
void SymbolTableManger::levelDecrement(){this->level -= 1;}
int SymbolTableManger::getLevel(){return this->level;}
SymbolEntry* SymbolTableManger::getcurrentSymbolEntry()
{
	return this->cuurentSymbolEntry;
}
SymbolTable* SymbolTableManger::getcurrentSymbolTable()
{
	return this->tables.back();
}

void SymbolTableManger::resetCurrentSymbolEntry()
{
	this->cuurentSymbolEntry = nullptr;
}


