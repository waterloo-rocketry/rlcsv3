#ifndef SD_HANDLER_H
#define SD_HANDLER_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define SD_BUFFER_SIZE 1024

void sd_init();

//returns true if logging is working
uint8_t sd_active();

//logs to the current log file. Buffered, so.. bear that in mind?
void rlcslog(const char* message);

//flushes the buffered output. Should we be hand buffering our logs?
void flush();

#ifdef __cplusplus
}
#endif

#endif
