#include "linac.h"

void setup()
{
    linac_init();
    while(1){
        while(!linac_extend())
            linac_refresh();
        while(!linac_retract())
            linac_refresh();
    }
}

void loop()
{

}
