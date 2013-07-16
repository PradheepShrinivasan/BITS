
/* dict_serv.h - initw, nextin, insertw, deletew, lookupw */

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <pthread.h>

#define	MAXWORD	50		/* maximum length of a command or word	*/
#define MEANSIZ	100		/* maximum number of meanings for a word */

int DICTSIZ = 100 ;		/* maximum number of entries in dictonary */


typedef struct 
{
	char *word;		/* stores the word */
	char **meaning;		/* array of pointers storing the list of meaning */
	int numMeaning;		/* the number of meaning */
}Dictonary;

pthread_rwlock_t dictlock ;

Dictonary **dictonaryList;  /* list that would store all the dictonary words */

int	nwords = 0;		/* number of words in the dictionary	*/

int 	initw();
int 	insertw(const char *word, const char* meaning);
int	deletew(const char *word);
char* 	lookupw(const char *word);

/*------------------------------------------------------------------------
 * initw - initialize the dictionary to contain no words at all
 *------------------------------------------------------------------------
 */
int initw()
{
	// initialize the dictonary to the original state
	pthread_rwlock_wrlock (&dictlock);
	if (dictonaryList)
	{
		free (dictonaryList);
	}

	dictonaryList = calloc (sizeof (dictonary), DICTSIZ);
	if (!dictonaryList)
	{
		perror ("Memory allocation failed");
		exit (1);
	}
	nwords = 0;
	pthread_rwlock_unlock (&dictlock);
	return 1;
}


/*------------------------------------------------------------------------
 * insertw - insert a word in the dictionary
 *------------------------------------------------------------------------
 */
int insertw(const char *word, const char *meaning)
{
	int count = 0;
	Dictonary *currentWord 	= NULL;
	
	pthread_rwlock_wrlock (&dictlock);
	// search for the word in the dictonary
	for (; count < nwords; count++)
	{
		// match the words
		if (!strcmp(dictonaryList[count]->word,word))
		{
			// check if the word is already present
			int loop = 0;				
			for (; loop < dictonaryList[count]->numMeaning ; loop++)
			{
				if (!strcmp(dictonaryList[count]->meaning[loop],meaning))
				{
					pthread_rwlock_unlock (&dictlock);
					return 1;
				}
			}
			// add the meaning to the available list if the word
			// if the word is not already present
			dictonaryList[count]->meaning[loop]= calloc (sizeof (char), strlen (meaning)+1);
			strcpy (dictonaryList[count]->meaning[loop], meaning);
			dictonaryList[count]->numMeaning++;
			pthread_rwlock_unlock (&dictlock);
			return 1;
		}

	}

	/* there are no words with the same matching name .. so add a new word to dictonary */
	currentWord 		= calloc (sizeof(dictonary), 1);
	currentWord->word 	= calloc (sizeof (char)  , strlen (word)+1);
	currentWord->meaning	= calloc (sizeof (char *), MEANSIZ);
	
	currentWord->meaning[0] = calloc (sizeof (char), strlen (meaning)+1);
	strcpy (currentWord->meaning[0], meaning);
	currentWord->numMeaning++;
	strcpy (currentWord->word, word);

	/* increase the size if the dict size is reached  */
	if ( nwords+1 > DICTSIZ )
	{
		dictonaryList =	realloc (dictonaryList, DICTSIZ+100);
		DICTSIZ += 100;
	} 

	/* add it to the list of words */
	dictonaryList [nwords++] = currentWord;  
	pthread_rwlock_unlock (&dictlock);
	return nwords;
}

/*------------------------------------------------------------------------
 * deletew - delete a word from the dictionary
 *------------------------------------------------------------------------
 */
int deletew(const char *word)
{
	return 0;
}

/*------------------------------------------------------------------------
 * lookupw - look up a word in the dictionary
 *------------------------------------------------------------------------
 */
 char* lookupw(const char *word)
{
	int	count = 0;
	// search for the word in the dictonary
	for (; count < nwords; count++)
	{
		pthread_rwlock_rdlock (&dictlock);

		// match the words
		if (!strcmp(dictonaryList[count]->word, word))
		{
			char * result;
			int randword = (rand () % dictonaryList[count]->numMeaning);
			result = calloc (sizeof(char),strlen(dictonaryList[count]->meaning[randword])+1);
			strcpy (result, dictonaryList[count]->meaning[randword]);
			pthread_rwlock_unlock (&dictlock);
			return result;
		}
	}
	pthread_rwlock_unlock (&dictlock);
	return 0;
}
