/* This file contains the functions for 
   creating and manipulating the nodes of 
   a hashtable
*/


// geneeral headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// project specific headers
#include "hashtable.h"

// function that computes the hash value
int hashfunction (const char* name)
{
	int hashvalue = 0;

	while (*name)
	{
		hashvalue += *name;
		++name;
	}

	return hashvalue%HASHTABLESIZE;
}

// the function creates a hash table 
//  A hash table is nothing but a collection of hash table nodes
// so create a array of pointers for storing hash table nodes and then call it as  the hash table
hashTable** createhashTable ()
{
	hashTable **hashtable = calloc (HASHTABLESIZE, sizeof (struct hashTableNode*));
	return hashtable;
}




// function inserts a elemet into the hash table and handles the collision by chaining
unsigned short int insertHashElementByChaining (hashTable **hashtable, struct phonedataNode *node, unsigned int* numofOperations)
{
 
	int key = 0;
	struct hashTableNode  *hashtableNode = NULL; 
	*numofOperations = 0; // initalize with zero values

	if (!hashtable)	
		return ERROR_NOHASHTABLE;

	hashtableNode = createHashTableNode (node);
	if (!hashtableNode)
		return ERROR_MALLOCFAIL;

	*numofOperations += 1;
	key = hashtableNode->hashValue;
	if (hashtable[key] == NULL)
	{
		hashtable[key] = hashtableNode;
		return SUCCESS;
	}
	// handling of collision 
	struct hashTableNode* currentNode = hashtable[key];
	while (currentNode->next)
	{
		*numofOperations += 1;
		currentNode = currentNode->next;
	}
	
	// insert the element as the last element
	currentNode->next = hashtableNode;
	return SUCCESS;
}

// function inserts a element into the hash table and handles the collision by linear probing
unsigned short int insertHashElementByLinearProbing (hashTable **hashtable, struct phonedataNode *node, unsigned int* numofOperations)
{
	int key = 0;
	struct hashTableNode *hashtableNode = NULL; 
	*numofOperations = 0;

	if (!hashtable)	
		return ERROR_NOHASHTABLE;

	hashtableNode = createHashTableNode (node);
	if (!hashtableNode)
		return ERROR_MALLOCFAIL;

	*numofOperations += 1;
	key = hashtableNode->hashValue;
	if (hashtable[key] == NULL)
	{

		hashtable[key] = hashtableNode;
		return SUCCESS;
	}
	else
	{
		long valuecounter  = 1;
		
		// The step size is 1 (assumed) so searching ever node after the key node 
		// for a free node to insert the hashNode
		long tempkey  = (key + valuecounter)% HASHTABLESIZE;
		for ( ;valuecounter < HASHTABLESIZE && hashtable [tempkey]; valuecounter++)
		{
			tempkey = (key + valuecounter)% HASHTABLESIZE;
			*numofOperations += 1;
		}
		
		if (valuecounter != HASHTABLESIZE)
		{
			hashtable[tempkey] = hashtableNode;
			return SUCCESS;
		}
	}
	return ERROR_REACHEDTABLESIZE;
}


// function inserts a element into hash table and handles the collision by quadratic probing
unsigned short int insertHashElementByQuadraticProbing (hashTable **hashtable, struct phonedataNode *node, unsigned int* numofOperations)
{
	int key = 0;
	struct hashTableNode *hashtableNode = NULL; 
	*numofOperations = 0;

	if (!hashtable)	
		return ERROR_NOHASHTABLE;

	hashtableNode = createHashTableNode (node);
	if (!hashtableNode)
		return ERROR_MALLOCFAIL;

	*numofOperations += 1;
	key = hashtableNode->hashValue;
	if (hashtable[key] == NULL)
	{
		hashtable[key] = hashtableNode;
		return SUCCESS;
	}
	else
	{
		long valuecounter  = 1;
		long tempkey  = (key + valuecounter*valuecounter) % HASHTABLESIZE;
		for ( ;valuecounter < HASHTABLESIZE && hashtable [tempkey]; valuecounter++)
		{
			tempkey = (key+ valuecounter*valuecounter)% HASHTABLESIZE;
			*numofOperations += 1;
		}
		if (valuecounter != HASHTABLESIZE)
		{
			hashtable[tempkey] = hashtableNode;
			return SUCCESS;
		}
	}
	return ERROR_REACHEDTABLESIZE;
}

// function find a elemet into the hash table, that handles the collision by chaining
unsigned short int findHashElementByChaining (hashTable **hashtable, const char* name, unsigned int* numofOperations)
{
 
	int key = 0;
	*numofOperations = 0; // initalize with zero values

	if (!hashtable)	
		return ERROR_NOHASHTABLE;

	*numofOperations += 1;
	key =  hashfunction (name);
	if (hashtable[key])
	{
		struct hashTableNode* currentNode = hashtable[key];
		if (!strcmp (currentNode->dataNode->name, name))
			return SUCCESS;
		
		while (currentNode)
		{
			if (!strcmp (currentNode->dataNode->name, name))
				return SUCCESS;
			currentNode = currentNode->next;
			*numofOperations += 1;
		}
	}
	return ERROR_ELEMENTNOTFOUND;
}

// function find a element into the hash table, that handles the collision by linear probing
unsigned short int findHashElementByLinearProbing (hashTable **hashtable, const char* name, unsigned int* numofOperations)
{
	int key = 0;
	*numofOperations = 0;

	if (!hashtable)	
		return ERROR_NOHASHTABLE;

	*numofOperations += 1;
	key = hashfunction (name);
	if (hashtable[key])
	{
		if (!strcmp (hashtable[key]->dataNode->name,name))
			return SUCCESS;

		long valuecounter  = 1;
		// The step size is 1 (assumed) so searching ever node after the key node 
		long tempkey  = (key + valuecounter) % HASHTABLESIZE;
		for ( ;valuecounter < HASHTABLESIZE && hashtable [tempkey]; valuecounter++)
		{

			*numofOperations += 1;
			if (!strcmp (hashtable[tempkey]->dataNode->name,name))
				return SUCCESS;

			tempkey = (key + valuecounter)% HASHTABLESIZE;
		}
	}

	return ERROR_ELEMENTNOTFOUND;	
}


// function finds an element into hash table that handles the collision by quadratic probing
unsigned short int findHashElementByQuadraticProbing (hashTable **hashtable, const char* name, unsigned int* numofOperations)
{
	int key = 0;
	*numofOperations = 0;

	if (!hashtable)	
		return ERROR_NOHASHTABLE;

	*numofOperations += 1;
	key = hashfunction (name);
	if (hashtable[key])
	{
		if (!strcmp (hashtable[key]->dataNode->name,name))
			return SUCCESS;

		long valuecounter  = 1;
		long tempkey  = (key + valuecounter*valuecounter)% HASHTABLESIZE;
		for ( ;valuecounter < HASHTABLESIZE && hashtable [tempkey]; valuecounter++)
		{
			*numofOperations += 1;
			if (!strcmp (hashtable[tempkey]->dataNode->name,name))
				return SUCCESS;

			tempkey = (key+ valuecounter*valuecounter)% HASHTABLESIZE;
		}
	}
	return ERROR_ELEMENTNOTFOUND;
}


// function to print the hash table 
// writes the value in comma separated value so that we can use a excel
// to view the data easily
void printHashTable (hashTable **hashtableptr, const char* outputFile)
{
	int key = 0;

	if (!hashtableptr)
		return;

	// open the file for reading or writing
	FILE *fp = fopen (outputFile, "w+");
	if (fp == NULL)
	{
		printf (" Error opening the file output.csv check file persmission \n");
		return;
	}

	// write the header for the csv file
	fprintf (fp, "%s","position,hashvalue,name,phone Number,email Id \n");

	// write the data to the comma separated file
	for (key = 0; key < HASHTABLESIZE; key++)
	{
		if (hashtableptr [key])
		{
			// a node is present		
			struct hashTableNode *currentNode = hashtableptr [key];
			fprintf (fp, "%d,%d ", key, currentNode->hashValue);
			while (currentNode)
			{
				struct phonedataNode *phoneDataValue = currentNode->dataNode;
				fprintf(fp, ",%s,%ld,%s ",phoneDataValue->name, \
					phoneDataValue->phoneNumber, phoneDataValue->emailId);
				currentNode = currentNode->next;
			}
			fprintf(fp, "%s", "\n");
		}
	}
	fclose (fp);
	return; 
}

//function that creates a hash table node 
struct hashTableNode* createHashTableNode (struct phonedataNode *node)
{
	struct hashTableNode* hashNode = (struct hashTableNode*) calloc (1, sizeof (struct hashTableNode));
	if (hashNode == NULL)
		return NULL;
	
	hashNode->dataNode 	= node;
	hashNode->hashValue 	= hashfunction (node->name);
	hashNode->next		= NULL; 

	return hashNode;
}

// function that creates node that can be stored in the hash table
struct phonedataNode* createDataNode (const char *name, long phoneNumber, const char* emailId)
{
	struct phonedataNode* node = (struct phonedataNode*) calloc (1, sizeof (struct phonedataNode));
	if (node == NULL)
		return NULL;

	node->name 	= (char *)calloc (strlen (name)+1, sizeof (char));
	node->emailId 	= (char *)calloc (strlen (emailId)+1, sizeof (char));

	strncpy (node->name, name, strlen (name)+1);
	strncpy (node->emailId, emailId, strlen (emailId)+1);

	node->phoneNumber = phoneNumber;
	return node;
}


// the function deletetes the hash table
// deleting a hash table is nothing deleting  every node in the hash table 
// and in case of chaining we have to make sure that all the chained nodes are aslso deleted
void deletehashTable (hashTable** hashtable)
{

	if (!hashtable)
		return;

	unsigned int loop = 0;
	for (loop = 0; loop < HASHTABLESIZE ; loop++)
	{
		struct hashTableNode *currentNode = hashtable[loop];

		// check if the node is using chaining the values
		// if so delete the linked nodes
		while  (currentNode)
		{
				struct hashTableNode *temp = currentNode;
				currentNode = currentNode->next;	
				deleteDataNode (temp->dataNode);		
		}
		// free the hash table node
		if (hashtable [loop])
			free (hashtable[loop]);
	}
	// free the hash table
	free (hashtable);
}

// function that deletes the phonedata node
void deleteDataNode (struct phonedataNode *dataNode)
{
	if (!dataNode)
		return;

	free (dataNode->name);
	free (dataNode->emailId);

	return;
}
