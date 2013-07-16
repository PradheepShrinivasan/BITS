/*
* mc.x: remote calculator access protocol
*/

/* const int MAXWORDSIZE 512 */


/* structure definitions*/
struct dictword{
      char word[512];
      char meaning[512];
};

  /* program definition, no union or typdef definitions needed */
program DICTONARTY { /* could manage multiple servers */
	version MCVERS {
		int Insert  (dictword) = 1;
		string Lookup(dictword) = 2;
		} = 1;
} = 0x20000002;  /* program number ranges established by ONC */

