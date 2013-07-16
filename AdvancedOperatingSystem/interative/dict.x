/* dict.x */

/* RPC declarations for dictionary program */



struct dictonary {		/* unused structure declared here to	*/
	string 	word<128>;		/* illustrate how rpcgen builds XDR	*/
	string	meaning<128>;	/* routines to convert structures.	*/
};


/*------------------------------------------------------------------------
   * RDICTPROG - remote program that provides insert, delete, and lookup
    *------------------------------------------------------------------------
     */
program RDICTPROG {		/* name of remote program (not used)	*/
	version RDICTVERS {		/* declaration of version (see below)	*/
	  	int INITW(void)     = 1;/* first procedure in this program	*/ 
		int INSERTW(dictonary) = 2;/* second procedure in this program	*/
		int DELETEW(string) = 3;/* third procedure in this program	*/
		string LOOKUPW(string) = 4;/* fourth procedure in this program	*/
		} = 1;			/* definition of the program version	*/
	} = 0x30090949;			/* remote program number (must be	*/
				/*  unique)				*/

