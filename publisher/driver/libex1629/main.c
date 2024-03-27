/*******************************************************************************
 *
 * Module Name: main.c
 *
 * Copyright 2004 VXI Technology Inc. as an unpublished work.
 * All rights reserved.
 *
 * The information contained herein is confidential property of VXI Technology,
 * Inc.  The use, copying, transfer, or disclosure of such information is
 * prohibited except by express written agreement with VXI Technology, Inc.
 *
 * First written on 6 October 2004 by Gary Bernhardt
 *
 * Module Description:
 *   This is the main source file for libex1629.  It contains the connect and
 *   disconnect functions.
 *
 ******************************************************************************/


/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <ex1629_errors.h>
#include <ex1629_files.h>
#include "libex1629.h"
#include "libex1629_internal.h"
#include "ex1629.h"

static EX1629_CLIENT * ex1629_connect(const char *host);
static void ex1629_disconnect( EX1629_CLIENT * client);



/*******************************************************************************
 * Function name: generic_connect
 *   host         Remote host to connect to
 *   version      RPC version to request
 *   Returns      Valid EX1629 client handle on success, NULL on failure
 * Created by:    Gary Bernhardt
 * Description:   This function is called by the ex1629_connect and core_connect
 *                functions.  It encapsulates the common code between them
 *                (which is almost all of it).
 * Notes:         THIS FUNCTION IS FOR LOCAL USE IN THIS FILE ONLY
 ******************************************************************************/
EX1629_CLIENT * generic_connect(const char *host, const int version) {
  int sockfd;
  int sockopt, sockoptlength;
  int err;
  struct ex1629_client *ex_cl;
  
  fflush(stdout);
  
  ex_cl = malloc(sizeof(struct ex1629_client));
  memset(ex_cl, 0, sizeof(struct ex1629_client));
  
  ex_cl->rpc_cl = clnt_create(host, VXITECH_PROG, version, "tcp");
  if (ex_cl->rpc_cl == NULL) {
    fprintf(stderr, "Error connecting to server %s prog=%d ver=%d\n",
	   host, VXITECH_PROG, version);
    clnt_pcreateerror(host);
    free(ex_cl);
    return NULL;
  }
  
  /* disable the nagle algorithm */
  
  /* get the socket */
#ifndef _WRS_KERNEL // If we're not targeting VxWorks, get the socket the normal, sane way
    /* get the socket */
    if (!clnt_control(ex_cl->rpc_cl, CLGET_FD, (char *)&sockfd)) {
      fprintf(stderr, "Error getting socket from CLIENT\n");
      clnt_pcreateerror(host);
      free(ex_cl);
      return NULL;
    }
#else
  /*
   * VxWorks doesn't have CLGET_FD, so we can't get the socket FD from the RPC library
   * However, the socket FD is stored as the first element in the cl_private struct...
   * As long as the compiler complies with the C standard, this should always work
   */
    sockfd = *(int *)ex_cl->rpc_cl->cl_private;
#endif
  
  /* disable nagle algorithm */
  sockopt = 1;
  sockoptlength  = sizeof(sockopt);
  err = setsockopt(sockfd, IPPROTO_TCP, TCP_NODELAY, &sockopt, sockoptlength);
  if(err) {
    fprintf(stderr,"setsockopt returned %d\n", err);
  }
  
  return ex_cl;
}
/*******************************************************************************
 * Function name: generic_disconnect
 *  client        Client Handle
 * Created by:    Gary Bernhardt
 * Description:   This function is called by the ex1629_disconnect and core_disconnect
 *                functions.  It encapsulates the common code between them
 *                (which is almost all of it).
 * Notes:         THIS FUNCTION IS FOR LOCAL USE IN THIS FILE ONLY
 ******************************************************************************/
void generic_disconnect(EX1629_CLIENT * client) {
  clnt_destroy(client->rpc_cl);
  free(client);
}


/*******************************************************************************
 * Function name: core_connect
 *   host         Remote host to connect to
 *   version      RPC version to request
 *   Returns      Valid EX1629 client handle on success, NULL on failure
 * Created by:    Gary Bernhardt
 * Description:   This function connects to a remote core RPC server and
 *                returns a handle to the connection.
 * Notes:         N/A
 ******************************************************************************/
EX1629_CLIENT * core_clnt_create(const char *host) {
  return generic_connect(host, CORE_VERS);
}


/*******************************************************************************
 * Function name: ex1629_connect
 *   host         Remote host to connect to
 *   version      RPC version to request
 *   Returns      Valid EX1629 client handle on success, NULL on failure
 * Created by:    Gary Bernhardt
 * Description:   This function connects to a remote EX1629 RPC server and
 *                returns a handle to the connection.
 * Notes:         N/A
 ******************************************************************************/
EX1629_CLIENT * ex1629_connect(const char *host) {
  return generic_connect(host, EX1629_PROG_VERS);
}


/*******************************************************************************
 * Function name: core_disconnect
 *   client       EX1629 Client
 *   Returns      N/A
 * Created by:    Nick Barendt
 * Description:   Disconnect the given client handle and free up any associated
 *                resources.
 * Notes:         N/A
 ******************************************************************************/
void core_clnt_destroy(EX1629_CLIENT * client) {
  return generic_disconnect( client );
}

/*******************************************************************************
 * Function name: ex1629_disconnect
 *   client       EX1629 Client
 *   Returns      N/A
 * Created by:    Gary Bernhardt
 * Description:   Disconnect the given client handle and free up any associated
 *                resources.
 * Notes:         N/A
 ******************************************************************************/
void ex1629_disconnect(EX1629_CLIENT * client) {
  return generic_disconnect( client );
}

EX1629_CLIENT *ex1629_clnt_create( const char *host, int lid )
{
  rpc_link result; 
  rpc_void rpc_arg; 
  EX1629_CLIENT *ex_cl = NULL;

  EX1629_DEBUG("%s calledn", __FUNCTION__); 
  memset(&result, 0, sizeof(result)); 
  memset(&rpc_arg, 0, sizeof(rpc_arg));

  ex_cl = ex1629_connect( host );

  if( ex_cl ) {
    /* if the user didn't give a link ID, get one from the server */
    if (lid == LID_NONE) {
      create_clntlink_0x00000201(rpc_arg, &result, ex_cl->rpc_cl);
      if (result.error_code != EX1629_SUCCESS) {
	clnt_destroy(ex_cl->rpc_cl);
	free(ex_cl);
	return NULL;
      }
      ex_cl->manual_lid = 0;  /* auto generated lid */
      ex_cl->lid = result.lid;
    } else {
      ex_cl->manual_lid = 1;  /* lid passed in */
      ex_cl->lid = lid;
    }
  }
  return ex_cl;
}

void ex1629_clnt_destroy( EX1629_CLIENT *cl ) {
  rpc_result result;
  rpc_link link;
  
  memset(&result, 0, sizeof(result));
  memset(&link, 0, sizeof(link));
  
  if (LID_NONE != cl->lid && !cl->manual_lid) {  /* we have a lid and it
						    was not manually created */
    link.lid = cl->lid;
    destroy_clntlink_0x00000201(link, &result, cl->rpc_cl);
  }
  ex1629_disconnect(cl);
}

