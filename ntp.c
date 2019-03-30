#include "ntp.h"

#include <stdio.h>

bool ntp_get_time(time_t* time){

    assert(sizeof(struct ntp_packet) == 48);

    struct ntp_packet packet;

    memset(&packet, 0, sizeof(struct ntp_packet));

    packet.li_vn_mode = NTP_LI_VN_MODE_VERSION_3;

    struct ntp_net_socket socket;

    if(!ntp_net_initialize_connection(&socket)) return false;
    if(!ntp_net_connect(&socket)) return false;
    if(!ntp_net_write(&socket, (uint8_t*)&packet, sizeof(struct ntp_packet))) return false;
    if(!ntp_net_read(&socket, (uint8_t*)&packet, sizeof(struct ntp_packet))) return false;

    uint32_t seconds = ntohl(packet.tx_tm_s);

    *time = (time_t)(seconds - NTP_TIMESTAMP_DELTA);

    return true;
}

bool ntp_get_packet_info(struct ntp_packet_info* packet_info){
    assert(sizeof(struct ntp_packet) == 48);

    struct ntp_packet packet;

    memset(&packet, 0, sizeof(struct ntp_packet));

    packet.li_vn_mode = NTP_LI_VN_MODE_VERSION_3;

    struct ntp_net_socket socket;

    if(!ntp_net_initialize_connection(&socket)) return false;

    if(!ntp_net_connect(&socket)) return false;

    if(!ntp_net_write(&socket, (uint8_t*)&packet, sizeof(struct ntp_packet))) return false;

    if(!ntp_net_read(&socket, (uint8_t*)&packet, sizeof(struct ntp_packet))) return false;

    packet_info->stratum = packet.stratum;

    packet_info->root_delay = ntohl(packet.root_delay);
    packet_info->root_dispersion = ntohl(packet.root_dispersion);
    packet_info->ref_id = packet.ref_id;

    packet_info->ref_tm_s = ntohl(packet.ref_tm_s);
    packet_info->ref_tm_f = ntohl(packet.ref_tm_f);

    packet_info->orig_tm_s = ntohl(packet.orig_tm_s);
    packet_info->orig_tm_f = ntohl(packet.orig_tm_f);

    packet_info->rx_tm_s = ntohl(packet.rx_tm_s);
    packet_info->rx_tm_f = ntohl(packet.rx_tm_f);

    packet_info->tx_tm_s = ntohl(packet.tx_tm_s);
    packet_info->tx_tm_f = ntohl(packet.tx_tm_f);

    return true;
}

void ntp_ref_id_to_string(char* buf, struct ntp_packet_info* info){
    uint8_t item1 = ((uint8_t*)&info->ref_id)[0];
    uint8_t item2 = ((uint8_t*)&info->ref_id)[1];
    uint8_t item3 = ((uint8_t*)&info->ref_id)[2];
    uint8_t item4 = ((uint8_t*)&info->ref_id)[3];
    if(info->stratum <= 1){
        sprintf(buf, "%c%c%c%c", item1, item2, item3, item4);
    } else {
        sprintf(buf, "%d.%d.%d.%d", item1, item2, item3, item4);
    }
    
}