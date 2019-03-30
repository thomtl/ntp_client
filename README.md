# ntp_client
ntp_client is a simple ntp client, it does NOT set the current system time or correct it. It just contacts an NTP server and prints the system time.

| Filename | Purpose |
|------|---------|
| build.sh | Simple build script for testing |
| ntp.h | Header file for the main client |
| ntp.c | Main client source file |
| ntp_net_linux.h | Header file containing the abstractions used in the main client file for UDP |
| ntp_net_linux.c | Source file containing the abstractions used in the main client file for UDP |
| main.c | Example use of the client |

The library is licensed with the MIT license