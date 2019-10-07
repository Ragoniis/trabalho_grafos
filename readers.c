#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_structures.h"

//status 0 = tudo zero, 1 = negativo, 2 = todos os pesos positvos maior que zero
WeightedN** read_list_w_int(unsigned v_number,FILE* fp, unsigned* array_number,char* status){
    WeightedN** p;
    if((p = (WeightedN **) calloc(v_number,sizeof(WeightedN *)))== NULL){
        printf("Out of Memory");
        exit(1);

    }
    unsigned int a,b;
    double c;
    unsigned zero_number = 0;
    (*status) = 2;
    while((fscanf(fp,"%u %u %lf",&a,&b,&c)) != EOF){
        //fprintf(out,"Fazendo a %d  e b %d %d \n",a,b,v_number);
        if(c < 0.0){
            (*status) = 1;

        }else if(!(c)){
            zero_number++;
        }
        p[a-1] = put_wnode(p[a-1],b-1,c);
        p[b-1] = put_wnode(p[b-1],a-1,c);
        (*array_number)++;
        //printf("Index %d ",a);
        //print_list_int(p[a]);
        //printf("Index %d ",b);
        //print_list_int(p[b]);
        //printf("Atualmente p[a] : %u e p[b]: %u \n", p[a]->value,p[b]->value);
    }

    if(zero_number == (*array_number)){
        (*status) = 0;
    }

    return p;
}

//testar o array number com ponteiros
IntNode** read_list_int(unsigned v_number,FILE* fp, unsigned* array_number){
    IntNode** p;
    if((p = (IntNode **) calloc(v_number,sizeof(IntNode *)))== NULL){
        printf("Out of Memory");
        exit(1);

    }
    unsigned int a,b;
    while((fscanf(fp,"%u %u",&a,&b)) != EOF){
        //fprintf(out,"Fazendo a %d  e b %d %d \n",a,b,v_number);
        p[a-1] = put_inode(p[a-1],b-1);
        p[b-1] = put_inode(p[b-1],a-1);
        (*array_number)++;
        //printf("Index %d ",a);
        //print_list_int(p[a]);
        //printf("Index %d ",b);
        //print_list_int(p[b]);
        //printf("Atualmente p[a] : %u e p[b]: %u \n", p[a]->value,p[b]->value);
    }
    return p;
}

//testar o array number com ponteiros
char** readMatrix(unsigned v_number, FILE* fp, unsigned* array_number){
    //aloca Espaco para matriz
    char** p;
    if((p = (char** ) calloc(v_number, sizeof(char*))) == NULL){
        printf("Fatal Error FLAG\n");
        exit(1);
    }
    for(unsigned i = 0;i<v_number;i++){
        if((p[i] = (char *) calloc(v_number,sizeof(char))) == NULL){
            printf("Fatal Error Out of Memory");
            exit(1);
        }
    }
    /*
    for(unsigned i = 1; i<=(v_number) ; i++){
        if((p[i-1] = (char *) calloc((v_number-i), sizeof(char))) == NULL){
            printf("Fatal Error FLAG2\n");
            exit(1);
        }
        //printf("Flag %d \n" ,p[i][1]);
    }
    */
    int a,b;
    //unsigned count=0;
    //unsigned count2=0;
    while((fscanf(fp,"%u %u",&a,&b)) != EOF){
        //printf("a= %d b = %d %d\n ",a,b,v_number);
        /*
        if((a) == 1 && (b) == 22){
            printf(" a %u e b %u\n",a,b);
        }
        if(a == 1){
            count++;
            if(p[a-1][b-1]== 1){
                printf("Matrix %d a %d e b %d",p[a-1][b-1],a,b);
            }
        }
        */
        p[a-1][b-1] =1;
        p[b-1][a-1] =1;
        (*array_number)++;
    }
    return p;

}
