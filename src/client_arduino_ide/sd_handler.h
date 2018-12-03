#ifndef SD_HANDLER_H
#define SD_HANDLER_H

#include <stdint.h>
#include "shared_types.h"

#ifdef __cplusplus
extern "C" {
#endif


void sd_init();

//returns true if logging is working
uint8_t sd_active();
uint8_t sd_buffer_dirty();

//logs to the current log file. Buffered, so.. bear that in mind?
void rlcslog(const char* message);

//flushes the buffered output. Should we be hand buffering our logs?
void flush();

//logs daq values
void rlcslog_log_daq_values(const daq_radio_value_t* to_log);

//client only functions
//log the current button state
void rlcslog_client_button(const actuator_state_t* buttons);
void rlcslog_client_tower_state(char state);


#ifdef __cplusplus
}
#endif

#endif
