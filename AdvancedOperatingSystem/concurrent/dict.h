/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _DICT_H_RPCGEN
#define _DICT_H_RPCGEN

#include <rpc/rpc.h>

#include <pthread.h>

#ifdef __cplusplus
extern "C" {
#endif


struct dictonary {
	char *word;
	char *meaning;
};
typedef struct dictonary dictonary;

#define RDICTPROG 0x30090949
#define RDICTVERS 1

#if defined(__STDC__) || defined(__cplusplus)
#define INITW 1
extern  enum clnt_stat initw_1(void *, int *, CLIENT *);
extern  bool_t initw_1_svc(void *, int *, struct svc_req *);
#define INSERTW 2
extern  enum clnt_stat insertw_1(dictonary *, int *, CLIENT *);
extern  bool_t insertw_1_svc(dictonary *, int *, struct svc_req *);
#define DELETEW 3
extern  enum clnt_stat deletew_1(char **, int *, CLIENT *);
extern  bool_t deletew_1_svc(char **, int *, struct svc_req *);
#define LOOKUPW 4
extern  enum clnt_stat lookupw_1(char **, char **, CLIENT *);
extern  bool_t lookupw_1_svc(char **, char **, struct svc_req *);
extern int rdictprog_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define INITW 1
extern  enum clnt_stat initw_1();
extern  bool_t initw_1_svc();
#define INSERTW 2
extern  enum clnt_stat insertw_1();
extern  bool_t insertw_1_svc();
#define DELETEW 3
extern  enum clnt_stat deletew_1();
extern  bool_t deletew_1_svc();
#define LOOKUPW 4
extern  enum clnt_stat lookupw_1();
extern  bool_t lookupw_1_svc();
extern int rdictprog_1_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_dictonary (XDR *, dictonary*);

#else /* K&R C */
extern bool_t xdr_dictonary ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_DICT_H_RPCGEN */