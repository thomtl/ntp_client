#include "ntp_net_linux.h"

int port_number = 123;
char host_name[] = "pool.ntp.org";

static void error(char* str, int code){
    char buf[64] = "";
    sprintf(buf, "%s: %d ", str, code);
    perror(buf);
    fflush(NULL); // All streams
    _exit(EXIT_FAILURE);
}

bool ntp_net_initialize_connection(struct ntp_net_socket* sock){
    sock->socket_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(sock->socket_fd < 0){
        error("socket() failed, it returned ", sock->socket_fd);
        return false;
    } 

    sock->server = gethostbyname(host_name);
    if(sock->server == NULL){
        error("gethostbyname() failed, it returned ", (uint64_t)sock->server);
        return false;
    }

    memset(&sock->server_addr, 0, sizeof(sock->server_addr));

    sock->server_addr.sin_family = AF_INET;

    memcpy((char*)&sock->server_addr.sin_addr.s_addr, (char*)sock->server->h_addr_list[0], sock->server->h_length);

    sock->server_addr.sin_port = htons(port_number);

    return true;
}

bool ntp_net_connect(struct ntp_net_socket* sock){
    int c = connect(sock->socket_fd, (struct sockaddr*)&sock->server_addr, sizeof(sock->server_addr));
    if(c < 0){
        error("connect() failed, it returned ", c);
        return false;
    }

    return true;
}

bool ntp_net_write(struct ntp_net_socket* sock, uint8_t* data, size_t len){
    int n = write(sock->socket_fd, data, len);
    if(n < 0 || n != len){
        error("write() failed, it returned ", n);
        return false;
    } 

    return true;
}

bool ntp_net_read(struct ntp_net_socket* sock, uint8_t* data, size_t len){
    int n = read(sock->socket_fd, data, len);
    if(n < 0 || n != len){
        error("read() failed, it returned ", n);
        return false;
    } 

    return true;
}