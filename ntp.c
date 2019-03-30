#include "ntp.h"

#include <stdio.h>

bool ntp_get_time(time_t* time){

    assert(sizeof(struct ntp_packet) == 48);

    struct ntp_packet packet;

    memset(&packet, 0, sizeof(struct ntp_packet));

    *((char*)&packet) = 0x1b; // li = 0, vn = 3, mode = 3;

    

    struct ntp_net_socket socket;

    if(!ntp_net_initialize_connection(&socket)) return false;

    if(!ntp_net_connect(&socket)) return false;

    if(!ntp_net_write(&socket, (uint8_t*)&packet, sizeof(struct ntp_packet))) return false;

    if(!ntp_net_read(&socket, (uint8_t*)&packet, sizeof(struct ntp_packet))) return false;

    uint32_t seconds = ntohl(packet.tx_tm_s);
    uint32_t fractions = ntohl(packet.tx_tm_f);

    *time = (time_t)(seconds - NTP_TIMESTAMP_DELTA);
    return true;
}
