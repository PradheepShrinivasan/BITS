
#include "dict.h"

#define MAXWORD 100

char 	*host;
int	getCmd ();
int 	getWord (char *word);

int main (int argc, char *argv[])
{
	char	*word = calloc ( MAXWORD+1 , sizeof (char)); 	/* space to hold word from input line	*/
	char	meaning[MAXWORD+1]; 	/* space to hold meaning from input line	*/
	char	cmd;
	CLIENT *clnt;
	enum clnt_stat retval;
	int  result;
	char *initw_1_arg;

	if (argc < 2) {
		printf ("usage: %s server_host\n", argv[0]);
		exit (1);
	}
	host = argv[1];

	clnt = clnt_create (host, RDICTPROG, RDICTVERS, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}

	printf ("Welcome to the dictonary program \n");
	while (1) {

		cmd = getCmd ();	
		switch (cmd) {
		case 'I':	/* "initialize" */
			retval = initw_1((void*)&initw_1_arg, &result, clnt);
			if (retval != RPC_SUCCESS) {
				clnt_perror (clnt, "call failed");
				break;
			}
			printf("Dictionary initialized to empty.\n");
			break;
		case 'i':	/* "insert" */
			printf ("Enter the word to be inserted ");
			if (getword (word))
			{
				printf ("Enter the meaning of the %s ", word);
				if (getword (meaning))
				{
					dictonary currentWord;
					
					currentWord.word= calloc (strlen (word)+1, sizeof (char));
					strcpy (currentWord.word, word);

					currentWord.meaning = calloc (strlen (meaning)+1, sizeof (char));
					strcpy (currentWord.meaning, meaning);
					retval = insertw_1(&currentWord, &result, clnt);
					if (retval != RPC_SUCCESS) {
						clnt_perror (clnt, "call failed");
						break;
					}
					printf("%s inserted with meaning %s\n",word, meaning);
				}
			}
			break;
		case 'd':	/* "delete" */
			printf ("Enter the word to be deleted  ");
			if (getword (word))
			{
				retval = deletew_1(&word, &result, clnt);
				if (retval != RPC_SUCCESS) {
					clnt_perror (clnt, "call failed");
					break;
				}
				printf ("Call not supported \n");
			}
			break;
		case 'l':	/* "lookup" */
			printf ("Enter the word to be looked up ");
			if (getword (word))
			{
				char *r_meaning;
				retval = lookupw_1(&word, &r_meaning, clnt);
				if (retval != RPC_SUCCESS ) {
					clnt_perror (clnt, "call failed");
					break;
				}
				if (*r_meaning)
					printf("%s meaning %s .\n", word, r_meaning);
				else
					printf(" meaning for %s was not found.\n", word);
			}
			break;
		case 'q':	/* quit */
			printf("program quits.\n");
			clnt_destroy (clnt);
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


