#include <stdio.h>
#include <stdlib.h>

int main(void){
    unsigned v_number = 4000000000; 
    unsigned* dist;
    if(!(dist = (unsigned*) malloc(sizeof(unsigned)*1000000*v_number))){
        printf("Error : Out of memory\n");
        exit(1);
    }
    free(dist);
}