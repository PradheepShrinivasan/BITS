// standard c++ header file 
#include <iostream>
#include <vector>

// standard c files
#include <stdio.h>

//project specific files
#include "Base.h"

using namespace std;

vector<char> Base::LookUpTable;

int Base::initializeBase (FILE *basefile)
{
	char characterRead;
	if (basefile == NULL)
		return Base::ERROR_NOTVALIDFILE;

	while (fscanf (basefile, "%c", &characterRead) != EOF)
	{
		if (characterRead == ' ' || characterRead == '\n')
			continue;
		LookUpTable.push_back (characterRead);
	}
	return Base::SUCCESS;
}


int Base::lookup (char characterToFind)
{
	size_t position = 0;
	for (; position < LookUpTable.size (); ++position)
		if (characterToFind == LookUpTable [position] )
			return position;
	return Base::ERROR_CHARACTERNOTFOUND;
}

char Base::lookupChar (int position)
{
	return LookUpTable[position];
}

