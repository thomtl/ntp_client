#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>


#include "ntp_net_linux.h" // Include header for own net stuff

struct ntp_packet {
    uint8_t li_vn_mode; // li, vn and mode
                        // li 2bits leap indicator
                        // vn 3bits protocol version number
                        // mode 3bits client picks 3 for client

    uint8_t stratum; // Stratum level of the local clock
    uint8_t poll; // Maximum interval between successive messages
    uint8_t precision; // Presision of the local clock

    uint32_t root_delay; // Round trip delay time
    uint32_t root_dispersion; // Max error from primary clock source
    uint32_t ref_id; // Reference clock identifier

    uint32_t ref_tm_s; // Reference time-stamp seconds
    uint32_t ref_tm_f; // Reference time-stamp fractions of a second

    uint32_t orig_tm_s; // Origin time-stamp seconds
    uint32_t orig_tm_f; // Origin time-stamp fractions of a second

    uint32_t rx_tm_s; // Received time-stamp seconds
    uint32_t rx_tm_f; // Received time-stamp fractions of a second

    uint32_t tx_tm_s; // Transmit time seconds
    uint32_t tx_tm_f; // Transmit time fraction of second
};


struct ntp_packet_info {
    uint8_t stratum; // Stratum level of the local clock

    uint32_t root_delay; // Round trip delay time
    uint32_t root_dispersion; // Max error from primary clock source
    uint32_t ref_id; // Reference clock identifier

    uint32_t ref_tm_s; // Reference time-stamp seconds
    uint32_t ref_tm_f; // Reference time-stamp fractions of a second

    uint32_t orig_tm_s; // Origin time-stamp seconds
    uint32_t orig_tm_f; // Origin time-stamp fractions of a second

    uint32_t rx_tm_s; // Received time-stamp seconds
    uint32_t rx_tm_f; // Received time-stamp fractions of a second

    uint32_t tx_tm_s; // Transmit time seconds
    uint32_t tx_tm_f; // Transmit time fraction of second
};

#define NTP_GET_LI (li_vn_mode) (((li_vn_mode) >> 6) & (0x3))
#define NTP_GET_VN (li_vn_mode) (((li_vn_mode) >> 3) & (0x7))
#define NTP_GET_MODE (li_vn_mode) ((li_vn_mode) & (0x7))

#define NTP_LI_VN_MODE_VERSION_3 0x1b

#define NTP_TIMESTAMP_DELTA 2208988800ull

bool ntp_get_time(time_t* time);
bool ntp_get_packet_info(struct ntp_packet_info* packet_info);

void ntp_ref_id_to_string(char* buf, struct ntp_packet_info* info);