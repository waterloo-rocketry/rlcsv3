#define TESTTHING

#include <stdio.h>
#include <string>
#include <stdlib.h>
#include "SD.h"
#include "../shared_types.h"

#define COMP(x,y) if(strcmp(SD.f.test_buffer, "\n0000010000 -\t\t" x)) { printf("Failure in test \"" y "\"\n"); exit(1); }
/*File mock_sd::open(const char *x, int y){
    File z;
    return z;
}*/

unsigned long millis(){return 10000;}
#include "sd_handler.h"

char* File::test_buffer;
daq_radio_value_t test_daq_data = {
    .data = {
        [0] = 'A',
        [1] = 'A',
        [2] = 'A',
        [3] = 'A',
        [4] = 'A',
        [5] = 'A',
        [6] = 'A',
        [7] = 'A',
        [8] = 'A',
        [9] = 'A',
        [10] = 'A',
        [11] = 'A',
        [12] = 'A',
        [13] = 'A',
    }
};

unsigned long global_time_last_output_flush = 0;
unsigned long global_time_last_logged_daq = 0;
int main(int argc, char *argv[]){
    SD.f.test_buffer = (char*) malloc(4096);
    sd_init();
    flush();

    rlcslog("test test test test");
    flush();
    COMP("test test test test", "plain rlcslog test");

    rlcslog_log_daq_values( &test_daq_data );
    flush();
    COMP("daq values - AAAAAAAAAAAAAA", "daq values logging test");

    printf("test %s passed successfully\n", argv[0]);
    exit(0);
}
