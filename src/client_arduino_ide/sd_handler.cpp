#include "sd_handler.h"

#include "client_pin_defines.h"

#include <SPI.h>
#include <SD.h>

//remember kids, always do development in 4K
#define SD_BUFFER_SIZE 4096

//#define SD_SERIAL_LOG

// set up variables using the SD utility library functions:
File output_log;

static uint8_t working = 0;

static char buffer[SD_BUFFER_SIZE + 10];
static size_t buffer_index = 0;

static char output_filename[13];

//set working to true if this works
void sd_init() {
    if (!SD.begin(PIN_SD_SS)) {
#ifdef SD_SERIAL_LOG
        Serial.println("couldn't start SD card");
#endif
        return;
    }

    int file_count = 0;
    output_log = SD.open("/");
    if(output_log){
#ifdef SD_SERIAL_LOG
        Serial.println("successfully opened root");
        Serial.flush();
#endif
        while(true){
            File s = output_log.openNextFile();
            if(s.isDirectory()){
#ifdef SD_SERIAL_LOG
                Serial.println("found another directory");
                Serial.flush();
#endif
                s.close();
                continue;
            }
            if(!s){
#ifdef SD_SERIAL_LOG
                Serial.println("ran out of files");
                Serial.flush();
#endif
                break;
            }
#ifdef SD_SERIAL_LOG
            Serial.println(s.name());
#endif
            s.close();
            file_count++;
        }
        output_log.close();
    } else {
#ifdef SD_SERIAL_LOG
        Serial.println("couldn't open root");
        Serial.flush();
#endif
        return;
    }

#ifdef SD_SERIAL_LOG
    Serial.print("found ");
    Serial.print(file_count);
    Serial.println(" files");
    Serial.flush();
#endif

    sprintf(output_filename, "%08i.TXT",file_count);
    // open the file. note that only one file can be open at a time,
    output_log = SD.open(output_filename, FILE_WRITE);
    // if the file opened okay, write to it:
    if (output_log) {
#ifdef SD_SERIAL_LOG
        Serial.print("Writing to");
        Serial.print(output_filename);
        Serial.print("....");
        Serial.flush();
#endif
        output_log.close();
    } else {
        // if the file didn't open, print an error:
#ifdef SD_SERIAL_LOG
        Serial.println("error opening 00000001.txt");
        Serial.flush();
#endif
        return;
    }
    working = 1;
    rlcslog("========RLCS LOG=========");
    flush();
}

uint8_t sd_active(){
    return working;
}

uint8_t sd_buffer_dirty(){
    return buffer_index != 0;
}


const int header_len = 20;
char header[header_len];
void rlcslog(const char* message){
    if(!working)
        return;
#ifdef SD_SERIAL_LOG
    Serial.println("Call to rlcslog");
    Serial.println(message);
    Serial.flush();
#endif
    int len = strlen(message);
    if(header_len + len + buffer_index >= SD_BUFFER_SIZE){
        flush();
    }
    sprintf(header,"\n%010lu -\t\t", millis());
    buffer_index += sprintf(buffer + buffer_index, header);
    buffer_index += sprintf(buffer + buffer_index, message);
}

extern unsigned long global_time_last_output_flush;
void flush(){
    global_time_last_output_flush = millis();
#ifdef SD_SERIAL_LOG
    Serial.println("Call to flush");
    Serial.flush();
#endif
    if(!working || !buffer_index) return;
    output_log = SD.open(output_filename, FILE_WRITE);
    if(output_log){
        output_log.write(buffer);
        buffer_index = 0;
        output_log.close();
    } else {
        working = 0;
    }
}

#define BUTTON_HEADER "buttons - "
static actuator_state_t last_buttons;
void rlcslog_client_button(const actuator_state_t* buttons){
    if(!working)
        return;
    if(!actuator_compare(&last_buttons, buttons)){
        //buttons have changed - log it

        // TODO: find a logging format
    }
}

#define TOWER_STATE_HEADER "tstate - "
static char last_tower_state = 'A';
void rlcslog_client_tower_state(const actuator_state_t* to_log){
    if(!working)
        return;

    // TODO: find a logging format
}

#define DAQ_HEADER "daq values - "
extern unsigned long global_time_last_logged_daq;
//log all daq values every 100 ms
static const unsigned long daq_log_interval = 100;
void rlcslog_log_daq_values(const daq_holder_t* to_log){
    if(!working)
        return;
    if( (millis() - global_time_last_logged_daq) < daq_log_interval)
        return;
    global_time_last_logged_daq = millis();

    // TODO: Need to find a logging format
}

