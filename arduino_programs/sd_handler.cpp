#include "sd_handler.h"
#include "client_pin_defines.h"
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
void rlcslog_tower_apply_state(char input){
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


#define DAQ_HEADER "daq values - "
static unsigned long time_last_daq_logged = 0;
//log all daq values every 100 ms
static const unsigned long daq_log_interval = 100;
void rlcslog_tower_daq(uint16_t mass,
                       uint16_t pressure1,
                       uint16_t pressure2,
                       uint16_t primary_current,
                       uint16_t secondary_current){
    if( (millis() - time_last_daq_logged) < daq_log_interval)
        return;
    time_last_daq_logged = millis();

    //we only log the mass, pressures, and ignition currents
    //that's 5 values, each is 4 characters plus two prefixes
    char message[sizeof(DAQ_HEADER) + (5 * (4 + 2))] = DAQ_HEADER;

    //tack the mass onto the end
    snprintf(message + sizeof(DAQ_HEADER) + 6*0 - 1, 7, "MA%04u", mass);

    //tack the first pressure on. I'm sorry for the magic numbers. Here's hoping it works!
    snprintf(message + sizeof(DAQ_HEADER) + 6*1 - 1, 7, "P1%04u", pressure1);

    //tack the second pressure on
    snprintf(message + sizeof(DAQ_HEADER) + 6*2 - 1, 7, "P2%04u", pressure2);

    //tack the first current on
    snprintf(message + sizeof(DAQ_HEADER) + 6*3 - 1, 7, "IP%04u", primary_current);

    //tack the second current on
    snprintf(message + sizeof(DAQ_HEADER) + 6*4 - 1, 7, "IP%04u", secondary_current);

    message[sizeof(DAQ_HEADER) + (5 * (4+2)) - 1] = '\0';
    rlcslog(message);
}

#endif
