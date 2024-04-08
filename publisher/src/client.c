#include <libex1629.h>

#include "client.h"
#include "try.h"

int client_new(EX1629_CLIENT **client, const char *host) {
    EX1629_CLIENT *cl = ex1629_clnt_create(host, LID_NONE);
    panic_on(cl == NULL);

    ex1629_try(libex1629_exreset(cl));
    int num_chs = 48;
    int scanlist[48];
    for (int i = 0; i < num_chs; i++)
        scanlist[i] = i;
    ex1629_try(libex1629_allow_bad_channels(cl));
    ex1629_try(libex1629_set_scanlist(cl, num_chs, scanlist));
    *client = cl;
    return 0;
}