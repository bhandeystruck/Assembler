//
//		Emulator class - supports the emulation of Duck2200 programs
//
#ifndef _EMULATOR_H      // UNIX way of preventing multiple inclusions.
#define _EMULATOR_H

class emulator {

public:

    const static int MEMSZ = 10000;	// The size of the memory of the Duck2200
    
	
	emulator()
	{
        memset(m_memory, 0, MEMSZ * sizeof(int));
		m_orgLoc = 0;
		m_firstInstruction = true;
		m_finished = false;
		m_accumulator = 0;

    }
	// Records instructions and data into Duck2200 memory.
    bool insertMemory( int a_location, int a_contents );
    
	// Runs the Duck2200 program recorded in memory.
    bool runProgram( );

private:

    int m_memory[MEMSZ];		// The memory of the Duck2200
    int m_accumulator;			// The accumulator for the Duck2200
	int m_operand;				// The current operand
	int m_opcode;				// The current opcode 
	bool m_firstInstruction;	
	int m_loc;					// The current location 
	int m_orgLoc;				
	bool m_finished;			// Check for HALT

	// Functions for emulator
	void Add();
	void Subtract();
	void Divide();
	void Multiply();
	void Store();
	void Load();
	void Write();
	void Read();
	void Branch();
	void BranchMinus();
	void BranchZero();
	void BranchPositive();
	void Halt();
};

#endif