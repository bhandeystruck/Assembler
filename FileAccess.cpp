//
//  Implementation of FileAccess class.
//
#include "stdafx.h"
#include "FileAccess.h"


FileAccess::FileAccess(int argc, char *argv[])
{
   //runtime para check
    if(argc != 2)
	{
        cerr << "Usage : Assem <FileName>" << endl;
        exit(1);
    }

    // Open the file.
    m_sfile.open(argv[1], ios::in);

    // If the open failed, report the error and terminate.
    if(!m_sfile)
	{
        cerr << "Source file could not be opened, assembler terminated." << endl;
        exit(1); 
    }
}


FileAccess::~FileAccess()
{
	m_sfile.close();
}

// Get the next line from the file.
bool FileAccess::GetNextLine(string& a_buff)
{
	// If there is no more data, return false.
	if (m_sfile.eof())
	{
		return false;
	}
	getline(m_sfile, a_buff);

	// Return indicating success.
	return true;
}


void FileAccess::rewind()
{
    m_sfile.clear();
    m_sfile.seekg(0, ios::beg);
}