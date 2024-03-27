/*******************************************************************************
 *
 * Module Name: libex1629_internal.h
 *
 * Copyright 2004 VXI Technology Inc. as an unpublished work.
 * All rights reserved.
 *
 * The information contained herein is confidential property of VXI Technology,
 * Inc.  The use, copying, transfer, or disclosure of such information is
 * prohibited except by express written agreement with VXI Technology, Inc.
 *
 * First written on 4 October 2004 by Gary Bernhardt
 *
 * Module Description:
 *   This module provides convenience macros for libex1629.
 *
 ******************************************************************************/


/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <ex1629_errors.h>


#define MAX_NUM_POINTERS_TO_FREE 16

/*******************************************************************************
 * Macro name:    LIBEX1629_FUNCTION_SIMPLE_INIT
 *   result_type: Data type of the variable returned by the RPC call
 * Created by:    Gary Bernhardt
 * Description:   Perform initialization that is common to all libex1629
 *                functions.
 * Notes:         This macro implicitly assumes that all RPC functions take
 *                an argument and return a value.  This is a safe assumption
 *                because the EX1629 Coding Standards specifies it.
 *                The simple init is used for RPC calls that only take a
 *                Link id (rpc_linkid)
 ******************************************************************************/
#define LIBEX1629_FUNCTION_SIMPLE_INIT(result_type) \
  result_type result; \
  xdrproc_t xdr_result_proc = (xdrproc_t) xdr_##result_type; \
  int num_pointers_to_free = 0; \
  void *pointers_to_free[MAX_NUM_POINTERS_TO_FREE]; \
  EX1629_DEBUG("%s called\n", __FUNCTION__); \
  memset(&result, 0, sizeof(result)); \

/*******************************************************************************
 * Macro name:    LIBEX1629_FUNCTION_INIT
 *   result_type: Data type of the variable returned by the RPC call
 *   rpc_arg_type:Data type of the argument to the RPC call
 * Created by:    Gary Bernhardt
 * Description:   Perform initialization that is common to all libex1629
 *                functions.
 * Notes:         This macro implicitly assumes that all RPC functions take
 *                an argument and return a value.  This is a safe assumption
 *                because the EX1629 Coding Standards specifies it.
 ******************************************************************************/
#define LIBEX1629_FUNCTION_INIT(result_type, rpc_arg_type) \
  result_type result; \
  xdrproc_t xdr_result_proc = (xdrproc_t) xdr_##result_type; \
  rpc_arg_type rpc_arg; \
  int num_pointers_to_free = 0; \
  void *pointers_to_free[MAX_NUM_POINTERS_TO_FREE]; \
  EX1629_DEBUG("%s called\n", __FUNCTION__); \
  memset(&result, 0, sizeof(result)); \
  memset(&rpc_arg, 0, sizeof(rpc_arg)); \
  rpc_arg.lid = cl->lid; 

/*******************************************************************************
 * Macro name:    LIBEX1629_CREATE_ARRAY
 *   member:      Argument structure member name for which to create an array
 *   length:      Array length to create
 * Created by:    Joe Miller
 * Description:   Allocate memory for an array for a libex1629 function.
 * Notes:         The pointer to the memory allocated by this macro is stored
 *                in an array of pointers that need freed.  The
 *                LIBEX1629_FREE_MEMORY macro frees all of the memory allocated
 *                by the LIBEX1629_CREATE_ARRAY macro.
 ******************************************************************************/
#define LIBEX1629_CREATE_ARRAY(member, length) \
  if(num_pointers_to_free < MAX_NUM_POINTERS_TO_FREE) { \
    rpc_arg.member.member##_len = length; \
    rpc_arg.member.member##_val = malloc( sizeof(rpc_arg.member.member##_val[0]) * length); \
    if((rpc_arg.member.member##_val == NULL) && (length > 0)){ \
      EX1629_TEE_ERROR("LIBEX1629_CREATE_ARRAY:malloc error\n"); \
      LIBEX1629_RETURN(-1); \
    } \
    pointers_to_free[num_pointers_to_free] = rpc_arg.member.member##_val; \
    num_pointers_to_free++; \
  } \
  else { \
    EX1629_TEE_ERROR("LIBEX1629_CREATE_ARRAY:Array of dynamically allocated pointers is full\n"); \
    LIBEX1629_RETURN(-1); \
  }

/*******************************************************************************
 * Macro name:    LIBEX1629_FREE_MEMORY
 * Created by:    Joe Miller
 * Description:   Free all of the memory allocated by LIBEX1629_CREATE_ARRAY
 * Notes:         Pointers to memory allocated by LIBEX1629_CREATE_ARRAY are
 *                stored in an array.  This macro frees all of those pointers.
 ******************************************************************************/
#define LIBEX1629_FREE_MEMORY() \
  while(num_pointers_to_free > 0) { \
    num_pointers_to_free--; \
    free(pointers_to_free[num_pointers_to_free]); \
  }

/*******************************************************************************
 * Macro name:    LIBEX1629_CALL_SIMPLE_RPC
 *   rpc_name:    The name of the RPC function to call
 * Created by:    Gary Bernhardt
 * Description:   Call an RPC function
 * Notes:         This macro simply replaces a complex four-line RPC call with
 *                a one-line macro call.
 *                The Simple version is used for RPC's that only take a Link ID
 *                for an argument (rpc_linkid)
 ******************************************************************************/
#define LIBEX1629_CALL_SIMPLE_RPC(rpc_name) \
  { \
    int rpc_result; \
    rpc_result = rpc_name##_0x00000201(cl->lid, &result, cl->rpc_cl); \
    if (rpc_result != RPC_SUCCESS) { \
      printf("RPC call to %s returned error %d\n", #rpc_name, rpc_result); \
      result.error_code = EX1629_ERROR_RPC_ERROR; \
      LIBEX1629_RETURN(result.error_code); \
    } \
  }

/*******************************************************************************
 * Macro name:    LIBEX1629_CALL_CORE_RPC
 *   rpc_name:    The name of the RPC function to call
 * Created by:    Gary Bernhardt
 * Description:   Call an RPC function
 * Notes:         This macro simply replaces a complex four-line RPC call with
 *                a one-line macro call.
 *                The Core version is used for RPC's that are part of the core
 *                function that only require the LID as an argument.
 ******************************************************************************/
#define LIBEX1629_CALL_CORE_RPC(rpc_name) \
  { \
    int rpc_result; \
    rpc_result = rpc_name##_0x00000001(&result, cl->rpc_cl); \
    if (rpc_result != RPC_SUCCESS) { \
      printf("RPC call to %s returned error %d\n", #rpc_name, rpc_result); \
      result.error_code = EX1629_ERROR_RPC_ERROR; \
      LIBEX1629_RETURN(result.error_code); \
    } \
  }

/*******************************************************************************
 * Macro name:    LIBEX1629_CALL_RPC
 *   rpc_name:    The name of the RPC function to call
 * Created by:    Gary Bernhardt
 * Description:   Call an RPC function
 * Notes:         This macro simply replaces a complex four-line RPC call with
 *                a one-line macro call.
 ******************************************************************************/
#define LIBEX1629_CALL_RPC(rpc_name) \
  { \
    int rpc_result; \
    rpc_result = rpc_name##_0x00000201(rpc_arg, &result, cl->rpc_cl); \
    if (rpc_result != RPC_SUCCESS) { \
      printf("RPC call to %s returned error %d\n", #rpc_name, rpc_result); \
      result.error_code = EX1629_ERROR_RPC_ERROR; \
      LIBEX1629_RETURN(result.error_code); \
    } \
  }

/*******************************************************************************
 * Macro name:    LIBEX1629_RETURN
 * Created by:    Joe Miller
 * Description:   Perform cleanup and return
 * Notes:         N/A
 ******************************************************************************/
#define LIBEX1629_RETURN(return_code) \
  LIBEX1629_FREE_MEMORY(); \
  xdr_free( xdr_result_proc, (char *) &result); \
  return return_code;

/*******************************************************************************
 * Macro name:    LIBEX1629_FUNCTION_END
 * Created by:    Gary Bernhardt
 * Description:   Perform cleanup that is common to all libex1629 functions.
 * Notes:         N/A
 ******************************************************************************/
#define LIBEX1629_FUNCTION_END() \
  LIBEX1629_RETURN(result.error_code);

/*******************************************************************************
 * Macro name:    LIBEX1629_RETURN_WITHOUT_XDR_FREE
 * Created by:    Joe Miller
 * Description:   Perform cleanup and return
 * Notes:         N/A
 ******************************************************************************/
#define LIBEX1629_RETURN_WITHOUT_XDR_FREE(return_code) \
  LIBEX1629_FREE_MEMORY(); \
  return return_code;

/*******************************************************************************
 * Macro name:    LIBEX1629_FUNCTION_END_WITHOUT_XDR_FREE
 * Created by:    Joe Miller
 * Description:   Perform cleanup but do not free the RPC result structure.
 *                This can be used when the result structure is returned to
 *                the client.  The client then must call another libex1629
 *                function to free the memory after it has processed it.
 * Notes:         N/A
 ******************************************************************************/
#define LIBEX1629_FUNCTION_END_WITHOUT_XDR_FREE() \
  LIBEX1629_RETURN_WITHOUT_XDR_FREE(result.error_code);

/*******************************************************************************
 * Macro name:    LIBEX1629_XDR_FREE
 *   result_type: Data type of the variable returned by the RPC call
 *   myresultptr: Pointer to RPC variable to free
 * Created by:    Joe Miller
 * Description:   Call XDR free routine for a RPC variable
 * Notes:         N/A
 ******************************************************************************/
#define LIBEX1629_XDR_FREE(result_type, myresultptr) \
  xdr_free( (xdrproc_t) xdr_##result_type, (char *) myresultptr);
