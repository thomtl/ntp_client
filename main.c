#include "ntp.h"
#include <stdio.h>
#include <time.h>
int main(void){
    time_t time;
    if(ntp_get_time(&time)) printf("%s", ctime((const time_t*)&time));
}