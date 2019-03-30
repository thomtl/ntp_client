#include "ntp.h"
#include <stdio.h>
#include <time.h>
int main(void){
    struct ntp_packet_info packet;
    if(!ntp_get_packet_info(&packet)) printf("ERROR");


    time_t time = (time_t)(packet.tx_tm_s - NTP_TIMESTAMP_DELTA);

    

    printf("%sStratum Level: %i \n", ctime((const time_t*)&time), packet.stratum);
    char ip[64];
    ntp_ref_id_to_string(ip, &packet);
    printf(ip);

    printf("\n");
}