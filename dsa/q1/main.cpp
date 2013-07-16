#include <iostream>
#include <string.h>
#include <stdlib.h>

#include "sorting.h"
#include "Number.h"
#include "Base.h"

using namespace std;

#define MAXSTRINGSIZE	200	

int main (int argc, char **argv)
{
	if (argc != 5)
	{
		cout << "The number of arguments is less . Check README.txt" << endl;
		return 0;
	}

	FILE*fp = fopen (argv[1], "r");
	if (fp == NULL)
	{
		perror ("Error in opening file base.txt");
		return 0;
	}
	
	// Get all the files that contains all  the inumbers 
	FILE *fp2 = fopen (argv[2],"r");
	if (fp2  == NULL)
	{
		perror ("Error in opening file numbers.txt");
		return 0;
	}

	int k = atoi (argv[3]);
	
	// output file 
	FILE *outFile = fopen (argv[4],"w+");
	if (outFile == NULL)
	{
		perror("Error in opening file output");
		return 0;
	}

	// initalize the look up table 
	Base::initializeBase (fp);
	
	// calculate the number of lines
	int numlines = 0;	
	char stringRead [MAXSTRINGSIZE];
	while (fgets (stringRead, MAXSTRINGSIZE, fp2) != NULL)
		numlines++;
	rewind (fp2);

	// allocate memorry for the lines	
	Number numberList[numlines];
	int size = 0;
	// read line by line and add to the list
	while (fgets (stringRead, MAXSTRINGSIZE, fp2) != NULL)
	{
		// remove teh \n charavter at the end
	 	stringRead[strlen(stringRead)-1] = '\0';
		numberList [size].insertNumber (stringRead);
		size++;
	}

	// choose the value of k
	if (k > size)
		k = size/2;

	// do the sorting and writte it out 
	Number value = quickSelect (numberList, size, k);

	//write the output to a file
	fprintf (outFile, "%s", value.getNumberWithBase ().c_str());

	fclose (fp);
	fclose (fp2);
	fclose (outFile);

	return 0;
}







