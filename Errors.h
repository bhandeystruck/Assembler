//
// Class to manage error reporting. Note: all members are static so we can access them anywhere.
//
#ifndef _ERRORS_H
#define _ERRORS_H

#include <string>
#include <vector>
using namespace std;

class Errors {

public:
	
    // Initializes error reports.
	static void InitErrorReporting();

    // Records an error message.
	static void RecordError(string a_emsg);

    // Displays the collected error message.
	static void DisplayErrors();

	// empty error box check
	static bool Empty();

private:
	static vector <string> m_ErrorMsgs;
};
#endif