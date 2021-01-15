//
// Class to parse and provide information about instructions.  Note: you will be adding more functionality.
//
#pragma once

// The elements of an instruction.
class Instruction {

public:

    Instruction( ) { };

    ~Instruction( ) { };

    // Codes to indicate the type of instruction we are processing.  Why is this inside the
    // class?
    enum InstructionType
	{
        ST_MachineLanguage,		// A machine language instruction.
        ST_AssemblerInstr,		// Assembler Language instruction.
        ST_Comment,				// Comment or blank line
        ST_End                  // End instruction.
    };
	
	// Parse the Instruction.
	InstructionType ParseInstruction(string a_buff);

	// Compute the location of the next instruction.
	int LocationNextInstruction(int a_loc);

    // To access the label.
    inline string &GetLabel()
	{
        return m_Label;
    }

	// To access the opcode.
	inline string &GetOpCode()
	{
		return m_OpCode;
	}

	
	// To access the m_IsNumericOperand.
	inline bool& GetIsNumericOperand()
	{
		return m_IsNumericOperand;
	}

	// To access the Instruction Type.
	inline InstructionType &GetInstructionType()
	{
		return m_type;
	}

	// To access the operand.
	inline string& GetOperand()
	{
		return m_Operand;
	}

    // To determine if a label is blank.
    inline bool isLabel( )
	{
        return !m_Label.empty();
    };

	// Get numeric opcode for machine instruction
	int MachineOpCode(string& a_buff);

	// Build instruction.
	pair <int, int> BuildInstruction(int a_loc, int symLoc, bool exists);

	//Int to string
	string IntToString(int num);

	// String to UPPERCASE
	static string ToUpper(string& a_buff);

private:
	
    // The elemements of a instruction.
    string m_Label;          // The label.
    string m_OpCode;         // The symbolic op code.
    string m_Operand;        // The operand.

    string m_instruction;    // The original instruction.

    // Derived values.
    int m_NumOpCode;         // The numerical value of the op code.
    InstructionType m_type;  // The type of instruction.
    bool m_IsNumericOperand; // == true if the operand is numeric.
    int m_OperandValue;		 // The value of the operand if it is numeric.
};