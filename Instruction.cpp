//
//      Implementation of the Instruction class.
//
#include "stdafx.h"
#include "Instruction.h"
#include "SymTab.h"
#include "Errors.h"

/**/
/*
Instruction::ParseInstruction()

NAME

	Instruction::ParseInstruction - Parsing takes place of the instruction to see
									what kind of instruction it is
SYNOPSIS

	Instruction::InstructionType Instruction::ParseInstruction(string a_buff);

	a_buff	the line of text that needs to be parsed.

DESCRIPTION

	The funciton takes the line of the text file and parses it.
	By doing this we will be able to find the instruction type.
	There are 4 possilbilities : MLI,ALI, a comment or an END.


RETURNS

	Returns the enum of type InstructionType .
*/
/**/
Instruction::InstructionType
Instruction::ParseInstruction(string a_buff)
{
	// Initialize variables
	m_instruction = a_buff; 
	m_Label = "";
	m_OpCode = "";
	m_Operand = "";

	m_type = InstructionType(1);

	// Delete comments
	int ipos = a_buff.find(';'); // Return POS
	if (ipos != string::npos)
	{
		a_buff.erase(ipos); 
	}

	istringstream ins(a_buff); //Class object ( input stream)


	string a, b, c, d; // hold labels, opcodes, operands.
	ins >> a >> b >> c >> d;


	// If a is a blank line or commentST_Comment.
	if (a.empty())
	{
		m_type = InstructionType(2);
		return m_type;
	}

	
	if (a_buff[0] == ' ' || a_buff[0] == '\t')
	{
		m_Label = ""; // label
		m_OpCode = ToUpper(a); //  OpCode
		m_Operand = b; //  Operand

		
		//TOUPPERCASE
		a = ToUpper(a); 
		if (a == "END")
		{
			m_type = InstructionType(3);
		}
		else if (a == "ORG" || a == "DC" || a == "DS")
		{
			m_type = InstructionType(1);
		}
		else
		{
			m_type = InstructionType(0);
		}

	}
	// if a label
	else
	{
		m_Label = a;
		m_OpCode = ToUpper(b);
		m_Operand = c;
		//OPCODE TO UPPER
		b = ToUpper(b); 
		if (b == "END")
		{
			m_type = InstructionType(3);
		}
		if (b == "ORG" || b == "DC" || b == "DS")
		{
			m_type = InstructionType(1);
		}
		else
		{
			m_type = InstructionType(0);
		}
	}

	// Check opernd to be a number
	try
	{
		int check = stoi(m_Operand);
		m_IsNumericOperand = true; // this equals true if the operand is numeric.
		m_OperandValue = check;   

	}
	catch (...)
	{
		m_IsNumericOperand = false;
	}

	return m_type;
}

/**/
/*
Instruction::LocationNextInstruction()

NAME

	Instruction::LocationNextInstruction - fetch the location of the next given insturction

SYNOPSIS

	int Instruction::LocationNextInstruction(int a_loc);

	a_loc	is a varialble for the  current location of the instruction.

DESCRIPTION

	Based on the type of instruction and opcodes the function gets 
	the location for the next instruction.

RETURNS

	Returns the location of the next instruction.

*/
/**/

int Instruction::LocationNextInstruction(int a_loc)
{
	// If the opcode is DS, we need to allocate storage proportional to the value of the operand
	if (m_OpCode == "DS" && m_IsNumericOperand == true)
	{
		return a_loc + stoi(m_Operand);
	}
	else if (m_OpCode == "ORG" && m_IsNumericOperand == true)
	{
		a_loc = stoi(m_Operand);
		return a_loc;
	}
	if (m_type == 2)
	{
		return a_loc;
	}
	return a_loc + 1;

}/*int Instruction::LocationNextInstruction(int a_loc); */

/**/
/*
Instruction::BuildInstruction()

NAME

	Instruction::BuildInstruction - creates the next instruction.

SYNOPSIS

	pair<int, int> Instruction::BuildInstruction(int a_loc, int symLoc);

	a_loc		 it holds the current location of the instruction.
	symLoc		 it holds the location of the symbol in the symbol table.

DESCRIPTION

	The function builds the instruction for the assembler .
	Handles error reporting  related to symbol,operand,opcode and label.

RETURNS

	Current location of instruction & the instruction for the compiler.



*/
/**/
pair<int, int> Instruction::BuildInstruction(int a_loc, int symLoc, bool exists)
{
	string instruction = ""; //instruction stored here

	m_NumOpCode = MachineOpCode(m_OpCode);

	string str = IntToString(m_NumOpCode);


	// Instruction turns out to be  an assembly language instruction 
	bool isDC = true;

	if (m_type == 1)
	{
		if (m_OpCode == "DC")
		{
			instruction = "00";
			string operand = IntToString(m_OperandValue);
			string zero = "0";
			while (operand.length() < 5)
			{
				operand.insert(0, zero);
			}

			instruction += operand;
		}
		else
		{
			isDC = false;
		}
	}

	// Instruction turns out to be machine language instruction
	if (m_type == 0) 
	{
		
		if (m_NumOpCode < 10 && m_NumOpCode > 0)
		{
			instruction += '0';
			instruction += str;
		}
		else
		{
			instruction += str;
		}

		string loc;
		// Add 0's to the location to get 5 digits
		if (m_OpCode == "HALT")
		{
			loc = "00000";
		}
		else
		{
			loc = IntToString(symLoc);
			string zero = "0";
			while (loc.length() < 5)
			{
				loc.insert(0, zero);
			}
		}
		instruction += loc;
	}


	if (m_type == 1 && m_OpCode == "DS" || m_OpCode == "ORG")
	{
		cout << setw(12) << left << a_loc << setw(12) << left << "" << setw(12) << left << m_instruction << endl;
		// Check valid operand
		if (GetIsNumericOperand() == false)
		{
			Errors::RecordError("Error (location " + to_string(a_loc) + "): expected a numeric operand.");
		}
	}
	else if (m_type == 2 || !isDC || m_type == 3)
	{
		cout << setw(12) << left << "" << setw(12) << left << "" << setw(12) << left << m_instruction << endl;
	}
	else
	{
		cout << setw(12) << left << a_loc << setw(12) << left << instruction << m_instruction << endl;
		// Check valid symbol
		if (m_type == 0)
		{
			if (exists == false && m_OpCode != "HALT")
			{
				Errors::RecordError("Error ( Location " + to_string(a_loc) + "): has invalid symbol: " + m_Operand + ".");
			}
		}
		
		if (m_OpCode == "DC")
		{
			// Check valid operand
			if (GetIsNumericOperand() == false)
			{
				Errors::RecordError("Error (location " + to_string(a_loc) + "): expected a numeric operand.");
			}
		}
		
		// Check valid opcode
		if (m_NumOpCode == -1 && m_OpCode != "DC")
		{
			Errors::RecordError("Error (location " + to_string(a_loc) + "): has opcode '" + string(GetOpCode()) + "' which is an invalid opcode.");
		}
		
		// Check valid label
		if (GetLabel().length() > 10)
		{
			Errors::RecordError("Error (location " + to_string(a_loc) + "): has label '" + string(GetLabel()) + "' which exceeds maximum length.");
		}

		

		return pair<int, int> (a_loc, stoi(instruction));
	}

	// Check valid label
	if (GetLabel().length() > 10)
	{
		Errors::RecordError("Error (location " + to_string(a_loc) + "): has label '" + string(GetLabel()) + "'which  exceeds maximum length.");
	}
	

	return pair<int, int> (-999, -999);
}

/**/
/*
Instruction::ToUpper()

NAME

	Instruction::ToUpper - converts the strings to uppercase.

SYNOPSIS

	string Instruction::ToUpper(string &a_buff);

	a_buff		 the string to be UPPER cased

DESCRIPTION

	This function converts each letter to uppercase.

RETURNS

	string in uppercase

*/
/**/

string Instruction::ToUpper(string &a_buff)
{
	for (size_t i = 0; i < a_buff.size(); i++)
	{
		a_buff[i] = toupper(a_buff[i]);
	}
	return a_buff;

}

/**/
/*
Instruction::IntToString()

NAME

	Instruction::IntToString - Making an integer into a string by casting it.

SYNOPSIS

	string Instruction::IntToString(int number);
	
	number		 the number that is casted

DESCRIPTION

		Takes an integer and makes it a string using stringstream.

RETURNS

	Returns a string which is the string type of the number.

*/
/**/
string Instruction::IntToString(int number)
{
	stringstream ss;
	ss << number;
	string str = ss.str();
	return str;
}

/**/
/*
Instruction::MachineOpCode()

NAME

	Instruction::MachineOpCode - fetch the value for the symbolic opcodes.

SYNOPSIS

	int Instruction::MachineOpCode(string &a_buff);

	a_buff	 the opcode to check if it exists.

DESCRIPTION

	This function takes in an opcode then It checks to see if we have a valid opcode.
RETURNS

	The value of the opcode if it exists.
	-1 if opcode cant be located.

*/
/**/
int Instruction::MachineOpCode(string &a_buff) 
{
	map<string, int> OpCode
	{
		{"ADD", 1,}, {"SUB", 2}, {"MULT", 3}, {"DIV", 4}, {"LOAD", 5}, {"STORE", 6}, 
		{"READ", 7}, {"WRITE", 8}, {"B", 9}, {"BM", 10}, {"BZ", 11}, {"BP", 12}, {"HALT", 13}
	};
	if (OpCode[a_buff] >= 1 && OpCode[a_buff] <= 13)
	{
		return OpCode[a_buff];
	}

	return -1;
}