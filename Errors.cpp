//
//      Implementation of the Errors class.
//
#include "stdafx.h"
#include "Errors.h"

//declare vect
static vector<string> m_ErrorMsgs;


/**/
/*
Errors::RecordError()

NAME

	Errors::RecordError() - The errors that are found are recorded.

SYNOPSIS

	void Errors::RecordError(string a_emsg);

DESCRIPTION

	All the errors found by  m_ErrorMsgs vector will be stored by this function.



*/
/**/
void Errors::RecordError(string a_emsg)
{
	m_ErrorMsgs.push_back(a_emsg);
	cout << a_emsg << endl;
}



/**/
/*
Errors::InitErrorReporting()

NAME

	Errors::InitErrorReporting - initializes the m_ErrorMsgs 
								a vector that reports errors.

SYNOPSIS

	void Errors::InitErrorReporting();

DESCRIPTION

		All the error message present in the vector are cleared.
	

*/
/**/
void Errors::InitErrorReporting()
{
	m_ErrorMsgs.clear();
}

/**/
/*
Errors::Empty()

NAME

	Errors::InitErrorReporting -  the m_ErrorMsgs vector id initialized here.

SYNOPSIS

	bool Errors::Empty();

DESCRIPTION

	All error messages in the m_ErrorMsgs vector are cleared.

RETURNS

	TRUE if there are no errors in the vector
	FALSE if there are more than 0 errors in the vector.


/**/
bool Errors::Empty()
{
	if (m_ErrorMsgs.size() == 0)
	{
		return true;
	}
	return false;
}


/**/
/*
Errors::DisplayErrors()

NAME

	Errors::DisplayErrors - displays the error first and clears errors.

SYNOPSIS

	void Errors::DisplayErrors();

DESCRIPTION

	This function will display the errors as they come in and then clear it.
*/
/**/
void Errors::DisplayErrors()
{
	for (size_t i = 0; i < m_ErrorMsgs.size(); i++)
	{
		cout << "\t" << m_ErrorMsgs[i] << endl;
	}
	m_ErrorMsgs.clear();
}

