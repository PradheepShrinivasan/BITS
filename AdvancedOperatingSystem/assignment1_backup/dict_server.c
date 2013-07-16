
#include "dict.h"
#include "dict_server.h"

int * initw_1_svc(void *argp, struct svc_req *rqstp)
{
	static int  result;
	
	result = initw ();

	return &result;
}

int *
insertw_1_svc(dictonary *argp, struct svc_req *rqstp)
{
	static int  result;
	
	result = insertw (argp->word, argp->meaning);

	return &result;
}

int *
deletew_1_svc(char **argp, struct svc_req *rqstp)
{
	static int  result;
	
	result = deletew (*argp);
	
	return &result;
}

char **
lookupw_1_svc(char **argp, struct svc_req *rqstp)
{
	static char * result;
	result = lookupw (*argp);
	return &result;
}
