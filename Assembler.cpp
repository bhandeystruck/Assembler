//
//      Implementation of the Assembler class.
//
#include "stdafx.h"
#include "Assembler.h"
#include "Errors.h"

/**/
/*
Assembler(int argc, char *argv[])

NAME

	Assembler::Assembler - This is the constructor made for the assmbler class.

SYNOPSIS

	Assembler::Assembler(int argc, char *argv[]);
	
	argc		--> argument count (1 + number of command line arguments given by the user)
	argv		--> This argument vector manages to hold each given argumet.
	

DESCRIPTION
	The following function is a constructor to the assembler
	Here we are passing argc and argv to the file access constructor.
*/
/**/
// Constructor for the assembler.  Note: we are passing argc and argv to the file access constructor.
// See main program.
Assembler::Assembler(int argc, char *argv[])
: m_facc(argc, argv)
{
    // Nothing else to do here at this point.
}/*Assembler(int argc, char *argv[]); */



/**/
/*
Assembler::PassI()

NAME

	Assembler::PassI - Here we set up the location of the labels that are present

SYNOPSIS

	void Assembler::PassI();

DESCRIPTION

	The following function is PASS I.
	The function parses each line to see what type of instruction is given.
	The functions returns if the instruction type comes out to be ST_END
	If the instruction type is ST_END, it will return.

*/
/**/
void Assembler::PassI() 
{
    int loc = 0; // Tracks the location of the instructions to be generated.

    // Successively process each line of source code.
    for( ; ; )
	{
        // Read the next line from the source file.
        string buff;
		cout << buff;
        if( ! m_facc.GetNextLine( buff ) )
		{

            // If there are no more lines, we are missing an end statement.
            // We will let this error be reported by Pass II.

            return;
        }

        // Parse the line and get the instruction type.
        Instruction::InstructionType st = m_inst.ParseInstruction( buff );

        // If this is an end statement, there is nothing left to do in pass I.
        // Pass II will determine if the end is the last statement.
        if( st == Instruction::ST_End ) return;

        // Labels can only be on machine language and assembler language
        // instructions.  So, skip other instruction types.
        if( st != Instruction::ST_MachineLanguage && st != Instruction::ST_AssemblerInstr ) 
        {
        	continue;
		}

        // If the instruction has a label, record it and its location in symbol table.
        if( m_inst.isLabel( ) )
		{

            m_symtab.AddSymbol( m_inst.GetLabel( ), loc );
        }

        // Compute the location of the next instruction.
        loc = m_inst.LocationNextInstruction( loc );
	}
}/*void Assembler::PassI(); */

/**/
/*
Assembler::PassII()

NAME

	Assembler::PassII - Error checking and the formation of instruction is done.

SYNOPSIS

	void Assembler::PassII();

DESCRIPTION

	Pass II
	Parsing of each line is done here.
	Error checking and the instructions for the emulator are built here.
	The instructions are stored in a vector.

*/
/**/
void Assembler::PassII()
{
	int loc = 0;  // location tracker to the instruction
	int symLoc = 0; //The memory location of a symbol is stored here
	



	Errors::InitErrorReporting();
	m_facc.rewind(); //File pointer get rewinded to the starting of the file

	cout << " The Translation of The Program : " << endl;
	cout << endl;
	cout << setw(12) << left << " Location " << setw(12) << left << " Contents " 
		 << setw(12) << left << " Original Statement " << endl;

	// Each line of source code is processed
	for ( ; ; )
	{
		
		string buff;//Below we read the next line from the file.
		cout << buff;
		if (!m_facc.GetNextLine(buff)) 
		{
			// Error report for Missing and end
			if (m_inst.GetInstructionType() != 3)
			{
				Errors::RecordError(" Error: Location " + to_string(loc) + ": Missing END statement here.");
			}
			return;
		}

		//Getting the instruction type by parsing.
		Instruction::InstructionType st = m_inst.ParseInstruction(buff);

		// Translate instruction
		symLoc = loc;
		bool exists = m_symtab.LookupSymbol(m_inst.GetOperand(), symLoc);
		pair<int, int> inst = m_inst.BuildInstruction(loc, symLoc, exists);
		pair<int, int> compare (-999, -999);
		if (inst  != compare)
		{
			m_machineinstruction.push_back(inst);
		}
		
		loc = m_inst.LocationNextInstruction(loc);
	}
}

/**/
/*
Assembler::RunEmulator()

NAME

	Assembler::RunEmulator - Executes the emulator.

SYNOPSIS

	void Assembler::RunEmulator();

DESCRIPTION

	The execution of the emulator takes place if there are no errors found
	while building the machine language instruction.

	Manages to report the error of memory location being out of bounds, unaccepted OPCODE.
*/
/**/
void Assembler::RunEmulator()
{
	cout << endl << "Press Enter to continue..." << endl;
	cin.ignore();

	// Stop if errors are found and display message
	if (!Errors::Empty())
	{
		cout << "Errors are present while compliling." << endl << "We are now exiting the program" << endl;
		cin.ignore();
		return;

	}

	// Emulator class recieves machine language code 
	for (vector<pair<int, int>>::iterator it = m_machineinstruction.begin(); it != m_machineinstruction.end(); ++it)
	{
		bool validMemory = m_emul.insertMemory(it->first, it->second);

		if (validMemory == false)
		{
			Errors::RecordError("Error inserting location: " + to_string(it->first) + " and contents: " + to_string(it->second) + " into the emulator memory");
		}
	}

	// illegal opcode error reporting
	bool validOpCode = m_emul.runProgram();
	if (validOpCode == false)
	{
		Errors::RecordError("Error: illegal opcode or missing HALT statement.");
	}

	// Any  errors are displayed
	if (!Errors::Empty())
	{
		Errors::DisplayErrors();
	}

	cout << endl << "Emulation Complete" << endl << endl;
	cout << "Press Enter to EXIT" << endl;
	cin.ignore();
	cin.ignore();

}/*	void Assembler::RunEmulator(); */