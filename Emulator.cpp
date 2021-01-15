//
//      Implementation of the Emulator class.
//
#include "stdafx.h"
#include "Emulator.h"
#include "Errors.h"

/**/
/*
emulator::insertMemory()

NAME

	emulator::insertMemory - emulator recieves memory

SYNOPSIS

	bool emulator::insertMemory(int a_location, int a_contents);

	a_location		--> the location of memory.
	a_contents		--> the contents in which are inserted into memory.

DESCRIPTION

	The funtion inserts memory in the emulator using the instructions.
	Sets the original location to 100 if the first machine instruction is recieved.

RETURNS

	TRUE if the memory insertion was done properly.
    FALSE if the location was out of bounds and has an error.


*/
/**/
bool emulator::insertMemory(int a_location, int a_contents)
{
	// Checking for positive number and location
	if (a_location < MEMSZ && a_location > -1)
	{
		m_memory[a_location] = a_contents; 
	}
	else
	{
		Errors::RecordError(" Error: Location " + to_string(a_location) + " out of bounds.");
		return false;
	}

	// Set location to first 
	if (m_firstInstruction == true)
	{
		m_orgLoc = a_location; 
		m_firstInstruction = false;
	}

	return true;
}


/**/
/*
emulator::runProgram()

NAME

	emulator::runProgram -  the emulation of the machine language instructions is done here

SYNOPSIS

	bool emulator::runProgram();

DESCRIPTION

	Function runs the emulation

RETURNS

	TRUE if the opcode has no errors
	FALSE if the opcode has an error or a HALT statement is not present


*/
/**/
bool emulator::runProgram()
{
	cout << "Results from emulating program:" << endl;
	cout << endl;

	//Program starts at loc 100
	m_loc = m_orgLoc;
	for (int i = 0; i < MEMSZ; i++)
	{
		m_opcode = m_memory[m_loc] / 10000; 
		m_operand = m_memory[m_loc] % 10000; 

		
		if (m_opcode == 0)
		{
			m_loc++;
			continue;
		}

		switch (m_opcode)
		{
		case 1:
			Add();
			break;
		case 2:
			Subtract();
			break;
		case 3:
			Multiply();
			break;
		case 4:
			Divide();
			break;
		case 5:
			Load();
			break;
		case 6:
			Store();
			break;
		case 7:
			Read();
			break;
		case 8:
			Write();
			break;
		case 9:
			Branch();
			break;
		case 10:
			BranchMinus();
			break;
		case 11:
			BranchZero();
			break;
		case 12:
			BranchPositive();
			break;
		case 13:
			Halt();
			break;
		
			/* The default will return FALSE*/
		}
		// If HALT is reached, Emulation complete.
		if (m_finished == true)
		{
			return true;
		}
	}
	//This is for the case if we are hissing a HALT statement its gonna return false.
	return false;




}

/**/
/*
emulator::Add()

NAME

	emulator::Add - Adding memory to accum.

SYNOPSIS

	void emulator::Add();

DESCRIPTION

	The function gets the sum of the data present in the Accum and the
	memory location given by the address of the instruction.
	The output of this function will be sent to the accumulator.
*/
/**/
void emulator::Add()
{
	int sum = m_accumulator + m_memory[m_operand];
	m_accumulator = sum;
	m_loc++;
}

/**/
/*
emulator::Subtract()

NAME

	emulator::Subtract - Here we substract the memory address with
	data in the accumulator.

SYNOPSIS

	void emulator::Subtract();

DESCRIPTION

		The function substracts the data from he accumulator 
		with the memory address found in the instruction.
*/
/**/
void emulator::Subtract()
{
	int difference = m_accumulator - m_memory[m_operand];
	m_accumulator = difference;
	m_loc++;
}

/**/
/*
emulator::Multiply()

NAME

	emulator::Multiply - multiplies the data of the memory address and the data present in the accumulator.

SYNOPSIS

	void emulator::Multiply();

DESCRIPTION

	In this function the data of the accumulator is multiplied by the data of the
	memory location given by the address of the instruction/
	The ouput is sent to the accumulator.
*/
/**/
void emulator::Multiply()
{
	int product = m_accumulator * m_memory[m_operand];
	m_accumulator = product;
	m_loc++;
}

/**/
/*
emulator::Divide()

NAME

	emulator::Divide - divides the data of the accumulator by the data of the memory address.

SYNOPSIS

	void emulator::Divide();

DESCRIPTION

	The data from the accumulator and the address is divided.
	The output is sent to the accumulator.
*/
/**/
void emulator::Divide()
{
	int remainder = m_accumulator / m_memory[m_operand];
	m_accumulator = remainder;
	m_loc++;
}

/**/
/*
emulator::Load()

NAME

	emulator::Load - The information of the memory address
					is loaded into the accumulator.

SYNOPSIS

	void emulator::Load();

DESCRIPTION

	The function manages to take the data of the memory location
	and place them in the accumulator.
*/
/**/
void emulator::Load()
{
	m_accumulator = m_memory[m_operand];
	m_loc++;
}

/**/
/*
emulator::Store()

NAME

	emulator::Store - The data of the accumulator is stored into memory

SYNOPSIS

	void emulator::Store();

DESCRIPTION

	This function takes the data of the accumulator and places them 
	in the current memory address.
*/
/**/
void emulator::Store()
{
	m_memory[m_operand] = m_accumulator;
	m_loc++;
}

/**/
/*
emulator::Read()

NAME

	emulator::Read - The reading of the first 10 digits is done and is
	 placed in a specified memory location.

SYNOPSIS

	void emulator::Read();

DESCRIPTION

	This function gets a input as a string from the user
	We keep only the first 10 characters .
	The function converts the string to a number and places it into the memory address.

*/
/**/
void emulator::Read()
{
	string line;
	int number;
	cout << "? ";
	cin >> line;

	// Check to see if we have a negative number
	bool negative = false;
	if (line[0] == '-' || line[0] == '+')
	{
		if (line[0] == '-')
		{
			negative = true;
		}

		line = line.substr(1, line.length() - 1);
	}

	// Keep only first 10 digits
	if (line.length() > 10)
	{
		line = line.substr(0, 10);
	}

	// check to see if input is a digit
	for (size_t i = 0; i < line.length(); i++)
	{
		if (!isdigit(line[i]))
		{
			cout << " ERROR : The Input is not a number" << endl;
			return;
		}
	}

	number = stoi(line);

	if (negative == true)
	{
		number *= -1;
	}

	m_memory[m_operand] = number;
	
	m_loc++;
}

/**/
/*
emulator::Write()

NAME

	emulator::Write - displays the information of the memory address.

SYNOPSIS

	void emulator::Write();

DESCRIPTION

	The function diplays the information of the memory location.
*/
/**/
void emulator::Write()
{
	cout << m_memory[m_operand] << endl;
	m_loc++;
}

/**/
/*
emulator::Branch()

NAME

	emulator::Branch - this takes us to the memory address for next instruction.

SYNOPSIS

	void emulator::Branch();

DESCRIPTION

	This function goes to the memory location specified by the addres.
*/
/**/
void emulator::Branch()
{
	m_loc = m_operand;
}

/**/
/*
emulator::BranchMinus()

NAME

	emulator::BranchMinus - searches memory address for next instruction
							if the accumulator is negative.

SYNOPSIS

	void emulator::BranchMinus();

DESCRIPTION

	This function goes to the memory location specified by the address portion of the instruction
	if the content of the accumulator is < 0.
/**/
void emulator::BranchMinus()
{
	if (m_accumulator < 0)
	{
		m_loc = m_operand;
	}
	else
	{
		m_loc++;
	}
}

/**/
/*
emulator::BranchZero()

NAME

	emulator::BranchZero - If the accum = 0 this takes us to the memory address
							to fetch the next instruction.

SYNOPSIS

	void emulator::BranchZero();

DESCRIPTION

	If accum = 0 this function goes to the memory location given by the address.

*/
/**/
void emulator::BranchZero()
{
	if (m_accumulator == 0)
	{
		m_loc = m_operand;
	}
	else
	{
		m_loc++;
	}
}

/**/
/*
emulator::BranchPositive()

NAME

	emulator::BranchPositive - If accumulator is > 1 it goes to memory address looking 
								for the next instruction.

SYNOPSIS

	void emulator::BranchPositive();

DESCRIPTION

	This function goes to the memory location specified by the address portion of the instruction
	if the contents of the accumulator is postive.
*/
/**/

void emulator::BranchPositive()
{
	if (m_accumulator > 0)
	{
		m_loc = m_operand;
	}
	else
	{
		m_loc++;
	}
}

/**/
/*
emulator::Halt()

NAME

	emulator::Halt - Exits the program

SYNOPSIS

	void emulator::Halt();

DESCRIPTION

	This function terminates the process of emulation

*/
/**/
void emulator::Halt()
{
	m_finished = true;
}