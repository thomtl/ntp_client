rm -r *.o
rm -r ntp

gcc -c ntp.c -o ntp.o
gcc -c ntp_net_linux.c -o ntp_net_linux.o
gcc -c main.c -o main.o

gcc main.o ntp.o ntp_net_linux.o -o ntp
