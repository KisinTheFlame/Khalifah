#include <libex1629.h>

#include "client.h"
#include "try.h"

EX1629_CLIENT *client_new(const char *host) {
    EX1629_CLIENT *client = NULL;
    client = ex1629_clnt_create(host, LID_NONE);
    panic_on(client == NULL);

    ex1629_try(libex1629_exreset(client));
    int num_chs = 48;
    int scanlist[48];
    for (int i = 0; i < num_chs; i++)
        scanlist[i] = i;
    libex1629_allow_bad_channels(client);
    libex1629_set_scanlist(client, num_chs, scanlist);
    return client;
}