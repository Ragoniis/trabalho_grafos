#include <stdio.h>
#include <stdlib.h>

int main(void){
    
    FILE *fp;
    fp=fopen("test.txt", "r");
    unsigned a,b,d,u;
    double c;
    char line[100];
    fscanf(fp,"%u", &u);
    fgets(line,100,fp);
    d = sscanf(line, "%u %u %lf",&a,&b,&c);
    fscanf(fp,"%u %u %lf \n",&a,&b,&c);
    printf("a:%u b:%u c:%lf d:%u \n",a,b,c,d);
    return 0;
    /*
   unsigned i = 0;
   do
   {
       printf("i:%u \n",i++);
   } while (i<5);
   */
}