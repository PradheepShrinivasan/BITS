#ifndef __HASHTABLE_H__
#define __HASHTABLE_H__

// standard libraries
#include <stdio.h>
#include <string.h>


// constants declaration
#define HASHTABLESIZE  2000


// RETURN CODES DECLARATION
#define SUCCESS			0

#define ERROR_NOHASHTABLE	1
#define ERROR_MALLOCFAIL	2
#define ERROR_REACHEDTABLESIZE	3
#define ERROR_ELEMENTNOTFOUND   4

// This structure is used to hold the phoneBook data
struct phonedataNode
{
	char *name;
	long phoneNumber;
	char *emailId;
};

/* this is the structure of the hash table
   that will hold the  pointer to the data and 
   the hash value of the node that it will point
*/
struct hashTableNode
{
	struct phonedataNode *dataNode;		// the actual data node
	int hashValue;				// holds the hash value for probing
	struct hashTableNode *next; 		// holds the next pointer for chaining 
};

// the hash table is a collection of hash table nodes 
// so typedefing 
typedef struct hashTableNode hashTable;

// hash functions that can be used for manipulating the nodes
// of a hastable
int hashfunction (const char* name);

// creation functions
hashTable** 		createhashTable ();
struct hashTableNode* 	createHashTableNode (struct phonedataNode *node);
struct phonedataNode* 	createDataNode (const char *name, long phoneNumber, const char* emailId);

// deletion functions
void deleteDataNode 	 (struct phonedataNode *dataNode);
void deletehashTable 	 (hashTable** hashtable);

// insertion functions
unsigned short int insertHashElementByChaining 		(hashTable **hashtable, struct phonedataNode *node, unsigned int* numofOperations);
unsigned short int insertHashElementByLinearProbing 	(hashTable **hashtable, struct phonedataNode *node, unsigned int* numofOperations);
unsigned short int insertHashElementByQuadraticProbing 	(hashTable **hashtable, struct phonedataNode *node, unsigned int* numofOperations);

// find functions
unsigned short int findHashElementByChaining 		(hashTable **hashtable, const char *name, unsigned int* numofOperations);
unsigned short int findHashElementByLinearProbing 	(hashTable **hashtable, const char *name, unsigned int* numofOperations);
unsigned short int findHashElementByQuadraticProbing 	(hashTable **hashtable, const char *name, unsigned int* numofOperations);

// debugging functions
void printHashTable (hashTable **hashtableptr, const char* outputFile);

#endif
