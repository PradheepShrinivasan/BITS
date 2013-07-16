
#include "dict.h"
#include "dict_server.h"

bool_t initw_1_svc(void *argp, int *result, struct svc_req *rqstp)
{
	
	*result = initw ();

	return 1;
}

bool_t insertw_1_svc(dictonary *argp, int *result, struct svc_req *rqstp)
{

	*result = insertw (argp->word, argp->meaning);
	return 1;

}

bool_t deletew_1_svc(char **argp, int *result, struct svc_req *rqstp)
{

	*result = deletew (*argp);

	return 1;
}

bool_t lookupw_1_svc(char **argp, char **result, struct svc_req *rqstp)
{
	
	*result = lookupw (*argp);

	return 1;
}

int rdictprog_1_freeresult (SVCXPRT *transp, xdrproc_t xdr_result, caddr_t result)
{
	xdr_free (xdr_result, result);

	return 1;
}
