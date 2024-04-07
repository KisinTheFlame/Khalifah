#include <libex1629.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "net_utils.h"
#include "panic.h"
#include "try.h"

#define NUM_CHS 48

static const char *HOST = "172.21.12.246";

static const int PORT = 3000;

typedef struct {
    EX1629_CLIENT *client;
    int socket_fd;
} Server;

static Server *server_new() {
    EX1629_CLIENT *client = client_new();
    int socket_fd = socket(AF_INET, SOCK_STREAM, NULL);
    panic_on(socket_fd < 0);

    Server *server = malloc(sizeof(Server));
    server->client = client;
    server->socket_fd = socket_fd;
    return server;
}

static void server_start(const Server *server) {
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT);
    bind(server->socket_fd, (struct sockaddr *)&addr, sizeof(addr));
    try(listen(server->socket_fd, 3));
    while (true) {
        int connection_fd = accept(server->socket_fd, &addr, sizeof(addr));
        // todo: start a thread.
        ConnectionArgs *connectionArgs =
            (ConnectionArgs *)malloc(sizeof(ConnectionArgs));
        connectionArgs->client = server->client;
        connectionArgs->connection_fd = connection_fd;
        pthread_t thread;
        pthread_create(&thread, NULL, handle, connectionArgs);
    }
}

static EX1629_CLIENT *client_new() {
    EX1629_CLIENT *client = NULL;
    client = ex1629_clnt_create(HOST, LID_NONE);
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

typedef struct {
    EX1629_CLIENT *client;
    int connection_fd;
} ConnectionArgs;

static int handle(ConnectionArgs *args) {
    EX1629_CLIENT *client = args->client;
    int connection_fd = args->connection_fd;
    char prefix[255];
    int major;
    int minor;
    int build;
    ex1629_try(
        libex1629_get_firmware_version(client, prefix, &major, &minor, &build)
    );
    printf(
        "EX1629 Firmware Version: %s.%d.%d.%d\n", prefix, major, minor, build
    );
    send_string(connection_fd, prefix);
    send_uint32(connection_fd, major);
    send_uint32(connection_fd, minor);
    send_uint32(connection_fd, build);
    free(args);
    return 0;
}

static int client_new_example() {
    EX1629_CLIENT *client = NULL;
    client = ex1629_clnt_create(HOST, LID_NONE);

    if (client != NULL) {
        /* Initial Resetting of EX1629 */
        libex1629_exreset(client);

        /* Get Serial Number */
        char serial[255];
        libex1629_get_serial_num(client, serial);
        printf("EX1629 Serial: %s\n", serial);

        /* Set scanlist to desired channels */
        int i, num_chs = 48;
        int new_scanlist[48];
        for (i = 0; i < num_chs; i++)
            new_scanlist[i] = i;
        libex1629_allow_bad_channels(client);
        libex1629_set_scanlist(client, num_chs, new_scanlist);

        /* Check if Scanlist has been set */
        int nchans = 0, scanlist[48];
        libex1629_get_scanlist(client, &nchans, scanlist);
        printf("No. of Enabled Channels: %d\n", nchans);
        printf("The Channels enabled are ");
        for (i = 0; i < nchans; i++)
            printf("%d ", scanlist[i]);
        printf("\n");

        /* Set trigger parameters */
        int32_t pretrig_sample_count = 0;
        uint32_t sample_count = 1;
        uint32_t trig_delay = 0;
        uint32_t arm_delay = 0;
        uint32_t trig_count = 3;
        uint32_t arm_count = 1;
        uint32_t trig_timer_period = 0;
        uint32_t init_cont = 0;
        libex1629_set_trigger_param(
            client, pretrig_sample_count, sample_count, trig_delay, arm_delay,
            trig_count, arm_count, trig_timer_period, init_cont
        );

        /* Setting up for Voltage Measurement */

        /* Setting Input Mux type to Full Bridge for Voltage Measurement */
        libex1629_set_inputmux(
            client, num_chs, new_scanlist, INPUTMUX_BRIDGE_TYPE_FULL
        );

        /* Setting Conversion */
        libex1629_set_conversion(
            client, num_chs, new_scanlist, EUCONV_VOLT_OUTPUT
        );

        /* Disabling Excitation */
        libex1629_set_excitation_enbl(client, num_chs, new_scanlist, 0, 0);

        /* Gain Setting, for input Voltage Range */
        libex1629_set_gain(
            client, num_chs, new_scanlist,
            1
        ); // Gain = 1 ; Voltage Range = 15V

        /* Setting Sampling Frequency */
        libex1629_set_samp_freq(client, 1000);

        /* Enabling Soft Sync */
        libex1629_soft_sync(client);

        /* Inititate the measurement */
        libex1629_triginit(client);
        sleep(1);

        /* Get the data from the FIFO */
        int fifo_count;
        rpc_fifoarray *fifo_data = malloc(sizeof(rpc_fifoarray));

        int set_page_count = 3; // 1 Page can Store Data of 16 channels
        libex1629_readfifo(client, set_page_count, &fifo_count, fifo_data);

        /* Unpack the data from the RPC data structure */
        int page_count = fifo_data->datapages.datapages_len, k = 0;
        rpc_datapage page;
        rpc_dataset *data;
        float samples[16];

        printf("Page Count = %d \n", page_count);
        printf("Pages Remaining in FIFO Buffer = %d \n", fifo_count);
        for (i = 0; i < page_count; i++) {
            page = fifo_data->datapages.datapages_val[i];
            data = page.dataset.dataset_val[i];
            int data_count = data->data.data_len;
            int j;
            for (j = 0; j < data_count; j++) {
                samples[j] = data->data.data_val[j];
                printf("Channel: %d \t Data: %f \n", scanlist[k], samples[j]);
                k++;
                if (k > nchans) {
                    k = 0;
                }
            }
        }
        libex1629_free_fifoarray(fifo_data);

        ex1629_clnt_destroy(client);
    } else {
        perror("Unable to connect.\n");
    }
    return 0;
}

int main() {
    server_start(server_new());
    return 0;
}
