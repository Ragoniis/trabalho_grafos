#include <stdio.h>
#include <float.h>

int main(void){
    double teste = DBL_MAX;
    double new_test = (DBL_MAX-10000000000000000000000000000000000.45);
    printf("%f \n",teste);
    printf("%f \n",new_test);

}
