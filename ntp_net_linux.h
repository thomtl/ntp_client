#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <strings.h>
#include <stdlib.h>
#include <stdio.h>

struct ntp_net_socket {
    int socket_fd;
    struct sockaddr_in server_addr;
    struct hostent* server;
};

bool ntp_net_initialize_connection(struct ntp_net_socket* sock);
bool ntp_net_connect(struct ntp_net_socket* sock);
bool ntp_net_write(struct ntp_net_socket* sock, uint8_t* data, size_t len);
bool ntp_net_read(struct ntp_net_socket* sock, uint8_t* data, size_t len);