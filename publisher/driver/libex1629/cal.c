#include "ex1629.h"
#include "libex1629.h"
#include "libex1629_internal.h"

ex1629_result_t libex1629_send_cal_prompt_response(struct ex1629_client * cl,
						   char * prompt_value)
{
  LIBEX1629_FUNCTION_INIT(rpc_result, rpc_cal_prompt_response);
  
  rpc_arg.prompt_value = prompt_value;
  LIBEX1629_CALL_RPC(send_calibration_prompt_response);
  
  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_get_factory_cal_date (struct ex1629_client *cl,
        char datestring[], int datestring_len)
{
  memset (datestring, 0, datestring_len);
  LIBEX1629_FUNCTION_SIMPLE_INIT(rpc_cal_date);

  LIBEX1629_CALL_SIMPLE_RPC(get_factory_calibration_date);
  if ( result.error_code || strlen (result.when) > datestring_len )
    return EX1629_ERROR_GENERIC;
  fprintf (stderr, "RPC call returned successfully");
  strcpy (datestring, result.when);
  
  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_is_cal_running (struct ex1629_client *cl, int *is_running)
{
  LIBEX1629_FUNCTION_SIMPLE_INIT(rpc_calibrationrunning);

  LIBEX1629_CALL_SIMPLE_RPC(get_calibration_running);
  if (result.error_code) {
    return result.error_code;
  }

  *is_running = result.cal_running;

  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_cal_query_simple (struct ex1629_client * cl,
       cal_simple_status_t *status)
{
  LIBEX1629_FUNCTION_SIMPLE_INIT(rpc_cal_simple_status);

  LIBEX1629_CALL_SIMPLE_RPC(get_calibration_simple_status);

  if ( result.error_code) {
    return result.error_code;
  }

  *status = result.status;

  LIBEX1629_FUNCTION_END();
}
  
ex1629_result_t libex1629_cal_query(struct ex1629_client * cl,
				    libex1629_cal_statuslist_t ** status)
{
  int numops;
  int i;

  LIBEX1629_FUNCTION_SIMPLE_INIT(rpc_cal_statuslist);

  LIBEX1629_CALL_SIMPLE_RPC(get_calibration_progress);

  numops = result.ops.ops_len;

  /*probably shouldn't malloc over top of anything*/
  if (*status != NULL)
  {
    return EX1629_ERROR_GENERIC;
  }
  *status = malloc (sizeof (libex1629_cal_statuslist_t));
  (*status)->list = malloc (numops * sizeof (libex1629_cal_op_status_t));

  if (!*status || !(*status)->list)
  {
    return EX1629_ERROR_OUT_OF_MEMORY;
  }

  (*status)->numops = numops;
  
  for (i = 0; i < numops; ++i)
  {
    strcpy ((*status)->list[i].desc,
             result.ops.ops_val[i].name);
    strcpy ((*status)->list[i].error,
             result.ops.ops_val[i].error);
    (*status)->list[i].statuscode = result.ops.ops_val[i].status;
  }

  LIBEX1629_FUNCTION_END();
}


ex1629_result_t libex1629_cal_free(libex1629_cal_statuslist_t **status)
{
  if ((*status)->list) {
    free ((*status)->list);
    (*status)->list = NULL;
  }
  
  if (*status) {
    free (*status);
    *status = NULL;
  }
  
  return EX1629_SUCCESS;
}

ex1629_result_t libex1629_factory_calibration_init(struct ex1629_client *cl,
        int *magic, int *recommended_uptime, int *current_uptime)
{
  LIBEX1629_FUNCTION_INIT(rpc_calresult, rpc_calmagic);
  rpc_arg.magic = (*magic);
  rpc_arg.lid = cl->lid;
  LIBEX1629_CALL_RPC(factory_calibration_init);
  *magic = result.magic;
  *recommended_uptime = result.recommended_uptime;
  *current_uptime = result.current_uptime;

  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_get_factory_calibration_status(struct ex1629_client *cl,
                                       int32_t *numfailedchannels, int32_t failedchannels[])
{
  int i;
  
  LIBEX1629_FUNCTION_SIMPLE_INIT(rpc_factorycal_status);
  LIBEX1629_CALL_SIMPLE_RPC(get_factorycal_status);
  
  *numfailedchannels = result.failedchannels.failedchannels_len;
  
  for( i = 0; i < *numfailedchannels; i++ ){
    failedchannels[i] = result.failedchannels.failedchannels_val[i];
  }
  
  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_get_bad_channel_status(struct ex1629_client *cl,
                                       int32_t *numfailedchannels, int32_t failedchannels[])
{
  int i;
  
  LIBEX1629_FUNCTION_SIMPLE_INIT(rpc_badchannel_status);
  LIBEX1629_CALL_SIMPLE_RPC(get_badchannel_status);
  
  *numfailedchannels = result.failedchannels.failedchannels_len;
  
  for( i = 0; i < *numfailedchannels; i++ ){
    failedchannels[i] = result.failedchannels.failedchannels_val[i];
  }
  
  LIBEX1629_FUNCTION_END();
}

/*************************************************************
* Function: libex1629_dmm_get
* 
* Arguments: 
* ex1629_client *cl                   client for the RPC
* libex1629_dmm_name** list           pointer to a list of the DMMs to return
* 
* Purpose: an empty rpc_dmm_list* is passed into the function,
* which calls the RPC. The RPC fills the result, which is an
* rpc_dmm_list (NOT a pointer), and assigns its address to the
* rpc_dmm_list*.
*
* Creator: Ben Fitzpatrick
**************************************************************/

ex1629_result_t libex1629_dmm_get(struct ex1629_client *cl,libex1629_dmm_name** list,int* size)
{
  //printf("Libex function enter\n");
  int counter;
  LIBEX1629_FUNCTION_SIMPLE_INIT(rpc_dmm_list);
  LIBEX1629_CALL_SIMPLE_RPC(get_dmm_identification);
  //printf("Libex RPC call OK\n");
  //TODO: Make another libex function we can call to get the number so we can malloc it a level up.
  *list = malloc(result.alldmms.alldmms_len * sizeof(libex1629_dmm_name));
  //printf("Libex malloc ok\n");
  *size = result.alldmms.alldmms_len;
  //printf("countermax = %i\n",result.alldmms.alldmms_len);
  for(counter=0 ; counter < (result.alldmms.alldmms_len) && result.alldmms.alldmms_val!=NULL; counter++ )
  {
    //printf("Counter at %i\n",counter);
    snprintf((*list)[counter].dmmname,DMM_MAX_LENGTH,"%s",result.alldmms.alldmms_val[counter].dmmname);
    //printf("DMM name set to %s\n",(*list)[counter].dmmname);
    (*list)[counter].dmmid = result.alldmms.alldmms_val[counter].dmmid;
    //printf("DMM ID set to %i\n",(*list)[counter].dmmid);
  }
  //printf("Libex function exit\n");
  LIBEX1629_FUNCTION_END();
}

/*************************************************************
* Function: libex1629_combined_cal_get
* 
* Arguments: 
* ex1629_client *cl                   client for the RPC
* char* file                          contains the file
* 
* Purpose: an empty char* is passed into the function,
* which calls the RPC. The RPC fills the result, which is an
* rpc_calfile, and then we assign the string to the char*.
* 
*
* Creator: Ben Fitzpatrick
**************************************************************/

ex1629_result_t libex1629_calfile_get(struct ex1629_client *cl, cal_file_type cal, char** file)
{
  LIBEX1629_FUNCTION_INIT(rpc_calfile, rpc_cal_file_type);
  rpc_arg.file = cal;
  LIBEX1629_CALL_RPC(get_calibration_file);
  if(file == NULL)
  {
    *file = malloc(result.file_len+1);
  }
  else
  {
    *file = realloc((void*)*file, result.file_len+1);
    memset((void*)*file, 0, (result.file_len+1));
  }
  strncpy(*file, result.file, result.file_len);
  if(file == NULL)
  {
    EX1629_TEE_ERROR("libex1629_calfile_get failure: pointer still null\n");
  }
  LIBEX1629_FUNCTION_END();
}
