/* dict.c - main, initw, nextin, insertw, deletew, lookupw */

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define	MAXWORD	50		/* maximum length of a command or word	*/
#define MEANSIZ	100		/* maximum number of meanings for a word */

int DICTSIZ = 100 ;		/* maximum number of entries in dictonary */


typedef struct 
{
	char *word;		/* stores the word */
	char **meaning;		/* array of pointers storing the list of meaning */
	int numMeaning;		/* the number of meaning */
}dictonary;


dictonary **dictonaryList;  /* list that would store all the dictonary words */

int	nwords = 0;		/* number of words in the dictionary	*/

int	nextin(char *cmd, char *word);
int 	initw();
int 	insertw(const char *word, const char* meaning);
int	deletew(const char *word);
char* 	lookupw(const char *word);
int	getCmd ();
int 	getword ();

/*------------------------------------------------------------------------
 * main - insert, delete, or look up words in a dictionary as specified
 *------------------------------------------------------------------------
 */
int main(int argc, char argv[])
{
	char	word[MAXWORD+1]; 	/* space to hold word from input line	*/
	char	meaning[MAXWORD+1]; 	/* space to hold meaning from input line	*/
	char	cmd;

	printf ("Welcome to the dictonary program \n");
	while (1) {

		cmd = getCmd ();	
		switch (cmd) {
		case 'I':	/* "initialize" */
			initw();
			printf("Dictionary initialized to empty.\n");
			break;
		case 'i':	/* "insert" */
			printf ("Enter the word to be inserted ");
			if (getword (word))
			{
				printf ("Enter the meaning of the word ");
				if (getword (meaning))
				{
					insertw(word, meaning);
					printf("%s inserted with meaning %s\n",word, meaning);
				}
			}
			break;
		case 'd':	/* "delete" */
			printf ("Enter the word to be deleted  ");
			if (getword (word))
			{
				if (deletew(word))
					printf("%s deleted.\n",word);
				else
					printf("%s not found.\n",word);
			}
			break;
		case 'l':	/* "lookup" */
			printf ("Enter the word to be looked up ");
			if (getword (word))
			{
				char *meaning = lookupw (word);
				if (word)
					printf("%s meaning %s .\n", word, meaning);
				else
					printf(" meaning for %s was not found.\n", word);
			}
			break;
		case 'q':	/* quit */
			printf("program quits.\n");
			exit(0);
		case '?':
			printf ("command        Function \n");
			printf ("------         -----------------------------  \n");
			printf (" \"I\"         for initialize the database    \n");
			printf (" \"i\"         for insert data to database    \n");
			printf (" \"d\"         for delete word from database  \n");
			printf (" \"l\"         for lookup word and q for quit \n");
			break;
		default:	/* illegal input */
			printf("command %c invalid.\n", cmd);
			break;
		}
	}
}

/*------------------------------------------------------------------------
 *  getCmd - Reads a command from the user input
 *------------------------------------------------------------------------
 */
int getCmd ()
{
	char ch;
	printf (" Enter the command and ? for help ");
	ch = getc(stdin);
	while (isspace(ch))
		ch = getc(stdin);
	if (ch == EOF)
		return -1;
	return ch;
}

/*------------------------------------------------------------------------
 * nextin - read a command and (possibly) a word from the next input line
 *------------------------------------------------------------------------
 */
int getword( char *word)
{
	int	i, ch;
	
	ch = getc (stdin);
	while (isspace(ch))
		ch = getc(stdin);
	if (ch == EOF)
		return -1;
	if (ch == '\n')
		return 0;
	i = 0;
	while (!isspace(ch)) {
		if (++i > MAXWORD) {
			printf("error: word too long.\n");
			exit(1);
		}
		*word++ = ch;
		ch = getc(stdin);
	}
	*word = '\0';
	return i;
}

/*------------------------------------------------------------------------
 * initw - initialize the dictionary to contain no words at all
 *------------------------------------------------------------------------
 */
int initw()
{
	// initialize the dictonary to the original state
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
	return 1;
}


/*------------------------------------------------------------------------
 * insertw - insert a word in the dictionary
 *------------------------------------------------------------------------
 */
int insertw(const char *word, const char *meaning)
{
	int count = 0;
	dictonary *currentWord 	= NULL;
	
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
					return 1;
			}
			// add the meaning to the available list if the word
			// if the word is not already present
			dictonaryList[count]->meaning[loop]= calloc (sizeof (char), strlen (meaning)+1);
			strcpy (dictonaryList[count]->meaning[loop], meaning);
			dictonaryList[count]->numMeaning++;
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

		// match the words
		if (!strcmp(dictonaryList[count]->word, word))
		{
			int randword = (rand () % dictonaryList[count]->numMeaning);
			return dictonaryList[count]->meaning[randword];
		}
	}
	return 0;
}
