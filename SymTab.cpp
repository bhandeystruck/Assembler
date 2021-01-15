//
//		Implementation of the SymbolTable class. This is the format I want for the
//commenting functions.
//
#include "stdafx.h"
#include "SymTab.h"

/**/
/*
SymbolTable::AddSymbol()

NAME

    AddSymbol - a new symbol is added to the symbol table

SYNOPSIS

    void AddSymbol(char *a_symbol, int a_loc);

DESCRIPTION

    This function sets the symbol and the location of the symbol in the sym table.


*/
/**/
void SymbolTable::AddSymbol(string &a_symbol, int a_loc)
{
    
    map<string, int>::iterator st;
    st = m_symbolTable.find( a_symbol );
    if (st != m_symbolTable.end())
	{

        st->second = multiplyDefinedSymbol;
        return;
    }
    // Record location
    m_symbolTable[a_symbol] = a_loc;
}



/**/
/*
SymbolTable::LookupSymbol()

NAME

	SymbolTable::LookupSymbol - Search  a symbol in the table.

SYNOPSIS

	bool SymbolTable::LookupSymbol(string &a_symbol, int &a_loc);

	a_symbol	is the symbol in the table
	a_loc		is the location of the symbol

DESCRIPTION

	Checks the symbol table to see if the input symbol is present in the table or not.
	If it finds the symbol we interchange the location of the symbol.

RETURNS

	True if found
	False if not found

*/
/**/


bool SymbolTable::LookupSymbol(string &a_symbol, int &a_loc)
{
	if (m_symbolTable.find(a_symbol) == m_symbolTable.end())
	{
		return false;
	}

	a_loc = m_symbolTable[a_symbol];

	return true;
}


/**/
/*
SymbolTable::DisplaySymbolTable()

NAME

	SymbolTable::DisplaySymbolTable - displays whatever is in the symbol table

SYNOPSIS

	void SymbolTable::DisplaySymbolTable();

DESCRIPTION

	This function prints the symbols and their locations.

*/
/**/

void SymbolTable::DisplaySymbolTable()
{
	int count = 0;
	cout << " The Symbol Table:" << endl;
	cout << endl;
	cout << setw(12) << left << "Symbol #" << setw(12)
		<< left << "Symbol" << setw(12) << left << "Location"
		<< endl;
	for (map<string, int>::iterator it = m_symbolTable.begin(); it != m_symbolTable.end(); count++, ++it)
	{
		cout << setw(12) << left << count << setw(12) << left << it->first
			<< setw(12) << left << it->second << endl;
	}
	cout << "-*-*-*-*-*-*-*-*-*-*-*-*-*-*" << endl;
	cout << endl << "Press ENTER to proceed" << endl;
	cin.ignore();
}