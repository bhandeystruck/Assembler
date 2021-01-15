//
//		Symbol table class.
//
#pragma once


class SymbolTable {

public:
    const int multiplyDefinedSymbol = -999;

    // Add symbol to table.
    void AddSymbol(string &a_symbol, int a_loc);

    // Display symbol table.
	void DisplaySymbolTable();

    // Search symbol in symbol table.
    bool LookupSymbol(string &a_symbol, int &a_loc);

private:

    // This is the actual symbol table. The symbol is the key to the map.
    map<string, int> m_symbolTable;
};