#include<stdio.h>
#include<stdlib.h>

#include "shared_types.h"

int checkBase64(void);

int main(int argc, char* argv[]){
    if(checkBase64()) {
        printf("Error on test checkBase64(), bailing\n");
        exit(1);
    }
    printf("test %s passed successfully\n", argv[0]);
    exit(0);
}

int checkBase64(){
    //check that converting a char to base64 and back is the same
    //elements of this arry in [0,63]
    char to64Test[] = {0,12,16,24,63};
    for(int i = 0; i < sizeof(to64Test); i++)
       if(fromBase64(toBase64(to64Test[i])) != to64Test[i]) {
           //error. Print problem and return zero
           printf("Error converting to base 64 and back"
                   " Number failed on was %i\n", to64Test[i]);
           return 1;
       }
    
    //chack that converting a char in [a-zA-Z0-9+/] from base64 and back works
    char from64Test[] = {'a', 'q', 'B', '7', '+'};
    for(int i = 0; i < sizeof(from64Test); i++)
       if(toBase64(fromBase64(from64Test[i])) != from64Test[i]) {
           //error. Print problem and return zero
           printf("Error converting from base 64 and back"
                   " character failed on was %c\n", from64Test[i]);
           return 1;
       }
    //test passed, return 0
    return 0;
}
