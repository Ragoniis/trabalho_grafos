#include "readers.h"


//status 0 = tudo um, 1 = negativo, 2 = todos os pesos positvos maior que zero
// Elemento ij da matriz igual à zero significa peso zero e igual 
//à DBL_MAX significa que não há adjacência 
double** read_matrix_w(unsigned* v_number_pointer, unsigned* array_number,char* status,char* file_name){
    FILE *fp;
    fp=fopen(file_name, "r");
    fscanf(fp,"%u", v_number_pointer);
    unsigned v_number = *v_number_pointer;
    //aloca Espaco para matriz
    double** p;
    if((p = (double** ) malloc(v_number * sizeof(double*))) == NULL){
        printf("Fatal Error Out of Memory\n");
        exit(1);
    }
    for(unsigned i = 0;i<v_number;i++){
        if((p[i] = (double *) malloc(v_number * sizeof(double))) == NULL){
            printf("Fatal Error Out of Memory");
            exit(1);
        }
    }
    double** row = p;
    double* collum;
    for(double** max_row = (p+v_number);row<max_row;row++){
        collum = (*row);
        for(double* max_collum=((*row) + v_number);
        collum< max_collum;collum++){
            (*collum) = DBL_MAX;

        }

    }
    unsigned a,b; 
    double c;
    unsigned ones_number=0;
    (*status) = 2;
    while((fscanf(fp,"%u %u %lf",&a,&b,&c)) != EOF){
        if(c < 0.0){
            (*status) = 1;
            printf("flaaag c:%lf e linha: %u",c,*array_number);
        }else if(c == 1){
            ones_number++;
        }
        p[a-1][b-1] =c;
        p[b-1][a-1] =c;
        (*array_number)++;
    }
    if(ones_number == (*array_number)){
        (*status) = 0;
    }
    fclose(fp);
    return p;

}



//status 0 = tudo um, 1 = negativo, 2 = todos os pesos positvos maior que zero
WeightedN** read_list_w_int(unsigned* v_number_pointer, unsigned* array_number,char* status, char* file_name){
    FILE *fp;
    fp=fopen(file_name, "r");
    fscanf(fp,"%u", v_number_pointer);
    unsigned v_number = *v_number_pointer;
    WeightedN** p;
    if((p = (WeightedN **) calloc(v_number,sizeof(WeightedN *)))== NULL){
        printf("Out of Memory");
        exit(1);

    }
    unsigned int a,b;
    double c;
    unsigned ones_number = 0;
    (*status) = 2;
    while((fscanf(fp,"%u %u %lf",&a,&b,&c)) != EOF){
        //fprintf(out,"Fazendo a %d  e b %d %d \n",a,b,v_number);
        if(c < 0.0){
            (*status) = 1;

        }else if(!(c)){
            ones_number++;
        }
        p[a-1] = put_wnode(p[a-1],b-1,c);
        p[b-1] = put_wnode(p[b-1],a-1,c);
        (*array_number)++;
    }

    if(ones_number == (*array_number)){
        (*status) = 0;
    }
    fclose(fp);
    return p;
}

//testar o array number com ponteiros
IntNode** read_list_int(unsigned* v_number_pointer, unsigned* array_number, char* file_name){
    FILE *fp;
    fp=fopen(file_name, "r");
    fscanf(fp,"%u", v_number_pointer);
    unsigned v_number = *v_number_pointer;
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
    fclose(fp);
    return p;
}

//testar o array number com ponteiros
char** readMatrix(unsigned* v_number_pointer, unsigned* array_number, char* file_name){
    FILE *fp;
    fp=fopen(file_name, "r");
    fscanf(fp,"%u", v_number_pointer);
    unsigned v_number = *v_number_pointer;
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
    unsigned a,b;
    while((fscanf(fp,"%u %u",&a,&b)) != EOF){
        p[a-1][b-1] =1;
        p[b-1][a-1] =1;
        (*array_number)++;
    }
    fclose(fp);
    return p;

}
