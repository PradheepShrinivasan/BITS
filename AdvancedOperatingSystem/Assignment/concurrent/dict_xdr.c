/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "dict.h"

bool_t
xdr_dictonary (XDR *xdrs, dictonary *objp)
{
	register int32_t *buf;

	 if (!xdr_string (xdrs, &objp->word, 128))
		 return FALSE;
	 if (!xdr_string (xdrs, &objp->meaning, 128))
		 return FALSE;
	return TRUE;
}
