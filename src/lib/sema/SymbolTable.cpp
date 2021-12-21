#include "sema/SymbolTableUtility.hpp"

SymbolTable::SymbolTable()
{

}
SymbolEntry* SymbolTable::lookup(std::string name)
{
	return symbolEntryMap[name];
}// look up within table
void SymbolTable::insert(SymbolEntry* enrty)
{
	symbolEntryMap[enrty->getName()] = enrty;
	symbalEntries.emplace_back(enrty);
}

void SymbolTable::print()
{	
	// printf("%s : %lu var\n","nice job bro",symbalEntries.size());
	dumpDemarcation('=');
	printf("%-33s%-11s%-11s%-17s%-11s\n", "Name", "Kind", "Level", "Type",
                                        "Attribute");
	dumpDemarcation('-');
	for(auto entry : symbalEntries)
	{
		printf("%s\n", entry->getEntryCString());
	}
	dumpDemarcation('-');

}
void SymbolTable::dumpDemarcation(const char chr) {
  for (size_t i = 0; i < 110; ++i) {
    printf("%c", chr);
  }
  puts("");
}

