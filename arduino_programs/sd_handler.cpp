#include "sd_handler.h"
#ifdef CLIENT
#include "client_pin_defines.h"
#else
#include "tower_pin_defines.h"
#endif
#include <SPI.h>
#include <SD.h>

//#define SD_SERIAL_LOG

// set up variables using the SD utility library functions:
File output_log;

uint8_t working = 0;

static char buffer[SD_BUFFER_SIZE + 10];
static size_t buffer_index = 0;

char output_filename[13];

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

#ifdef CLIENT
#define BUTTON_HEADER "buttons - "
static actuator_state_t last_buttons;
void rlcslog_client_button(actuator_state_t* buttons){
    if(!working)
        return;
    if(!actuator_compare(&last_buttons, buttons)){
        //buttons have changed - log it
        char message[sizeof(BUTTON_HEADER) + 2] = BUTTON_HEADER;
        convert_state_to_radio(buttons, message + sizeof(BUTTON_HEADER) - 1);
        message[sizeof(BUTTON_HEADER) + 1] = 0;
#ifdef SD_SERIAL_LOG
        Serial.print("buttons changed: ");
        Serial.println(message);
        Serial.flush();
#endif
        rlcslog(message);
        //copy what we just received to the last_buttons
        memcpy(&last_buttons, buttons, sizeof(last_buttons));
    }
}

#define TOWER_STATE_HEADER "tstate - "
static char last_tower_state = 'A';
void rlcslog_client_tower_state(char input){
    if(!working)
        return;
    if(last_tower_state != input){
#ifdef SD_SERIAL_LOG
        Serial.print("call to rlcslog_client_tower_state  (");
        Serial.print(input,HEX);
        Serial.print(TOWER_STATE_HEADER);
        Serial.println(sizeof(TOWER_STATE_HEADER));
#endif
        last_tower_state = input;
        char message[sizeof(TOWER_STATE_HEADER) + 1] = TOWER_STATE_HEADER;
        message[sizeof(TOWER_STATE_HEADER)-1] = input;
        message[sizeof(TOWER_STATE_HEADER)] = 0;
        rlcslog(message);
    }
}
#endif

#ifdef TOWER
#define APPLY_HEADER "app state - "
static char last_logged_state = 'Z';
void rlcslog_tower_apply_state(char input){
    if(!working)
        return;
    if(last_logged_state == input)
        return;
    last_logged_state = input;
#ifdef SD_SERIAL_LOG
    Serial.print("call to rlcslog_tower_apply_state (");
    Serial.print(input, HEX);
    Serial.print(APPLY_HEADER);
    Serial.println(sizeof(APPLY_HEADER));
#endif
    char message[sizeof(APPLY_HEADER) + 1] = APPLY_HEADER;
    message[sizeof(APPLY_HEADER) - 1] = input;
    message[sizeof(APPLY_HEADER)] = 0;
    rlcslog(message);
}

#endif

#define DAQ_HEADER "daq values - "
extern unsigned long global_time_last_logged_daq;
//log all daq values every 100 ms
static const unsigned long daq_log_interval = 100;
void rlcslog_log_daq_values(daq_radio_value_t* to_log){
    if(!working)
        return;
    if( (millis() - global_time_last_logged_daq) < daq_log_interval)
        return;
    global_time_last_logged_daq = millis();

    //log all 15 characters of DAQ, plus the header, plus
    //the null terminator
    char message[sizeof(DAQ_HEADER) + DAQ_RADIO_LEN + 1] = DAQ_HEADER;

    strncpy(message + sizeof(DAQ_HEADER) - 1, to_log->data, DAQ_RADIO_LEN);

    message[sizeof(DAQ_HEADER) + DAQ_RADIO_LEN] = '\0';
    rlcslog(message);
}

