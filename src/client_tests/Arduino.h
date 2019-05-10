//dummy arduino.h file, used for testing

#ifndef NODE_TEST
#error "Included wrong arduino file"
#endif

class {
    public:
        void write(char c){};
        void begin(int baud){};
        bool available(){return false;};
        char read(){return 'c';};
        operator bool() const { return true; }
} Serial;
int millis(){return 3;};
void digitalWrite(int,int){};
void pinMode(int,int){};
const int HIGH = 1;
const int LOW = 0;
const int OUTPUT = 0;
