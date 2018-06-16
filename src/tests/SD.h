#define FILE_WRITE 0
#include <string.h>
#include <stdio.h>

class File{
    public:
    static char *test_buffer;
    int counter;
    operator bool() { if(counter++ == 1) return false; return true;}
    void close(){}
    bool isDirectory(){return false;}
    File openNextFile(){return *this;}
    void write(const char *x){
        strcpy(test_buffer, x);
    }
};

class mock_sd {
    public:
    File f;
    File open(const char *x, int y=7){return f;}
    bool begin(int){return true;}
};

#ifndef TESTTHING
extern mock_sd SD;
#else
mock_sd SD;
#endif

unsigned long millis();
