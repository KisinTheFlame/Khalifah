#include "ex1629.h"
#include "libex1629.h"
#include "libex1629_internal.h"

ex1629_result_t libex1629_self_test_init(struct ex1629_client *cl, int *magic)
{
  LIBEX1629_FUNCTION_INIT(rpc_calresult, rpc_calmagic);
  rpc_arg.magic = (*magic);
  rpc_arg.lid = cl->lid;
  LIBEX1629_CALL_RPC(self_test_init);

  LIBEX1629_FUNCTION_END();
}

ex1629_result_t libex1629_self_test_query_simple (struct ex1629_client * cl,
       cal_simple_status_t *status)
{
  return libex1629_cal_query_simple (cl, status);
}


