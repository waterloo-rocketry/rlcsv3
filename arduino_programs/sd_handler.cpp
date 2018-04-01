#include "sd_handler.h"
#include "client_pin_defines.h"
#include <SPI.h>
#include <SD.h>

#define SD_SERIAL_LOG

// set up variables using the SD utility library functions:
File output_log;

uint8_t working = 0;

static char buffer[SD_BUFFER_SIZE];
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
#ifdef SD_SERIAL_LOG
    Serial.print("call to sd_active: ");
    Serial.println(working);
    Serial.flush();
#endif
    return working;
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
#ifdef SD_SERIAL_LOG
    Serial.println("end of rlcslog function");
    Serial.print(buffer);
    Serial.println(" is the current buffer");
    Serial.flush();
#endif
}

void flush(){
#ifdef SD_SERIAL_LOG
    Serial.println("Call to flush");
    Serial.flush();
#endif
    if(!working) return;
    output_log = SD.open(output_filename, FILE_WRITE);
    if(output_log){
        output_log.write(buffer);
        buffer_index = 0;
        output_log.close();
    } else {
        working = 0;
    }
}
