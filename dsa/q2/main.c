// header file declaration
#include <stdio.h>
#include <malloc.h>
#include <string.h>

#include "hashtable.h"

#define MAXNAMESIZE 100

int main ()
{
	unsigned int numofFailedInsertionsForChaining = 0;
	unsigned int numofFailedInsertionsForLProbing = 0;
	unsigned int numofFailedInsertionsForQProbing = 0;

	unsigned int numOfFailedSearchesForChaining = 0;
	unsigned int numOfFailedSearchesForLProbing = 0;
	unsigned int numOfFailedSearchesForQProbing = 0;

	unsigned int totalNumofChainingOperations = 0;
	unsigned int totalNumofLProbingOperations = 0;
	unsigned int totalNumofQProbingOperations = 0;

	unsigned int maxNumOperationsForChaining = 0;
	unsigned int maxNumOperationsForLProbing = 0;
	unsigned int maxNumOperationsForQProbing = 0;

	unsigned int totalNumberOfInsertions = 0;
	unsigned int totalNumberOfSearches   = 0;
	unsigned int numofOperations 	     = 0;
	
	unsigned int totalNumofChainingSearches = 0;
	unsigned int totalNumofLProbingSearches = 0;
	unsigned int totalNumofQProbingSearches = 0;

	unsigned int maxSearchesForChaining = 0;
	unsigned int maxSearchesForLProbing = 0;
	unsigned int maxSearchesForQProbing = 0;

	struct phonedataNode * currentNode = NULL;

	hashTable **chainingHashTable = NULL;
	hashTable **lProbingHashTable = NULL;
	hashTable **qProbingHashTable = NULL;

	char name [MAXNAMESIZE];
	FILE *fp = fopen ("names.txt", "r");
	if (fp == NULL)
	{
		perror ("Error Opening file");
		return 0;
	}

	// create a hash table for the 3 types 
	chainingHashTable = createhashTable ();
	lProbingHashTable = createhashTable ();
	qProbingHashTable = createhashTable ();

	// in the below code, the names are read  from the text file 
	// and the other variables are hard codes as its not required currently for 
	// analysis of algorithmn. the code is robust enough to allow the addition 
	// if necessary in the future

	while (fscanf(fp,"%s", name) != EOF)
	{
		totalNumberOfInsertions ++;
		
		// insert name into the chaining hash table
		currentNode = createDataNode (name, 12345566, "pradheep.sh@gmail.com");
		if (insertHashElementByChaining (chainingHashTable, currentNode, &numofOperations) != SUCCESS) {
			numofFailedInsertionsForChaining++;
		} else {
			totalNumofChainingOperations += numofOperations;
			if (numofOperations > maxNumOperationsForChaining)
				maxNumOperationsForChaining = numofOperations;
		}


		// insert name into the LinearProbing  hash table
		currentNode = createDataNode (name, 12345566, "pradheep.sh@gmail.com");
		if (insertHashElementByLinearProbing(lProbingHashTable, currentNode, &numofOperations) != SUCCESS) {
			numofFailedInsertionsForLProbing ++;
		} else {
			totalNumofLProbingOperations += numofOperations;
			if (numofOperations > maxNumOperationsForLProbing)
				maxNumOperationsForLProbing = numofOperations;
		}
		

		// insert name into the Quadratic Probing hash table
		currentNode = createDataNode (name, 12345566, "pradheep.sh@gmail.com");
		if (insertHashElementByQuadraticProbing (qProbingHashTable, currentNode, &numofOperations) != SUCCESS) {
			numofFailedInsertionsForQProbing ++;
		} else {
			totalNumofQProbingOperations += numofOperations;
			if (numofOperations > maxNumOperationsForQProbing)
				maxNumOperationsForQProbing = numofOperations;
		}
	}
	
	// write the hashing table to file to help in debugging and to get a visual output
	// note the file can be opened in excel 
	printHashTable (chainingHashTable, "chaining.csv");
	printHashTable (lProbingHashTable, "lprobing.csv");
	printHashTable (qProbingHashTable, "qProbing.csv");

	// reset the file pointer to the start of file
	rewind (fp);


	// search for all the names that are inserted into hash tables
	while (fscanf(fp,"%s", name) != EOF)
	{
		totalNumberOfSearches++;
		if (findHashElementByChaining (chainingHashTable, name, &numofOperations) != SUCCESS) {
			numOfFailedSearchesForChaining ++;
		} else {
			totalNumofChainingSearches += numofOperations;
			if (numofOperations > maxSearchesForChaining)
				maxSearchesForChaining = numofOperations;
		}

		if (findHashElementByLinearProbing (lProbingHashTable, name, &numofOperations) != SUCCESS) {
			numOfFailedSearchesForLProbing ++;
		} else {
			totalNumofLProbingSearches += numofOperations;
			if (numofOperations > maxSearchesForLProbing)
				maxSearchesForLProbing = numofOperations;
		}


		if (findHashElementByQuadraticProbing (qProbingHashTable, name, &numofOperations) != SUCCESS) {
			numOfFailedSearchesForQProbing ++;
		} else {
			totalNumofQProbingSearches += numofOperations;
			if (numofOperations > maxSearchesForQProbing)
				maxSearchesForQProbing = numofOperations;
		}
	}
	fclose (fp);


	printf ("---------------------------------------------------------------- \n");
	printf ("Insertion case - Total insertions %d in a hash table of %d\n ", totalNumberOfInsertions, HASHTABLESIZE);
	printf ("---------------------------------------------------------------- \n");
	printf ("\t\t\t%s\t\t%s\t\t%s\n", "Maximum number", "Average number", "failed cases");
	printf ("%s\t\t%d\t\t\t%d\t\t\t%d\n", "Chaining", maxNumOperationsForChaining, totalNumofChainingOperations/ \
					(totalNumberOfInsertions-numofFailedInsertionsForChaining), numofFailedInsertionsForChaining);
	printf ("%s\t\t%d\t\t\t%d\t\t\t%d\n", "LProbing", maxNumOperationsForLProbing, totalNumofLProbingOperations/ \
					(totalNumberOfInsertions-numofFailedInsertionsForLProbing), numofFailedInsertionsForLProbing);	
	printf ("%s\t\t%d\t\t\t%d\t\t\t%d\n", "QProbing", maxNumOperationsForQProbing, totalNumofQProbingOperations/ \
					(totalNumberOfInsertions-numofFailedInsertionsForQProbing), numofFailedInsertionsForQProbing);
	printf ("---------------------------------------------------------------- \n");
	


	printf ("Searching case - Total searches %d in a hash table of %d\n ", totalNumberOfSearches, HASHTABLESIZE);
	printf ("---------------------------------------------------------------- \n");
	printf ("\t\t\t%s\t\t%s\t\t%s\n", "Maximum number", "Average number", "failed cases");
	printf ("%s\t\t%d\t\t\t%d\t\t\t%d\n", "Chaining", maxSearchesForChaining, totalNumofChainingSearches/ \
					(totalNumberOfSearches- numOfFailedSearchesForChaining), numOfFailedSearchesForChaining);
	printf ("%s\t\t%d\t\t\t%d\t\t\t%d\n", "LProbing", maxSearchesForLProbing, totalNumofLProbingSearches/ \
					(totalNumberOfSearches- numOfFailedSearchesForLProbing), numOfFailedSearchesForLProbing);
	printf ("%s\t\t%d\t\t\t%d\t\t\t%d\n", "QProbing", maxSearchesForQProbing, totalNumofQProbingSearches/ \
					(totalNumberOfSearches- numOfFailedSearchesForQProbing), numOfFailedSearchesForQProbing);
	printf ("---------------------------------------------------------------- \n");

	deletehashTable (chainingHashTable);		
	deletehashTable (lProbingHashTable);		
	deletehashTable (qProbingHashTable);		
	
	return 0;
}

