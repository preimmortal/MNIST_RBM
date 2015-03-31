#ifndef TRAIN_H_
#define TRAIN_H_

#include <stdio.h>
#include <stdlib.h>

#include "mnist_parse.h"

#define NUM_EPOCHS 10
#define NUM_BATCHES 10
#define NUM_HIDDEN 100
#define NUM_FACTORS 100

//Define Restricted Boltzmann Machine Params
typedef struct{
    int *XFAC;
    int *YFAC;
    int *XYFAC;
    int *tem;

    float *hprob;
    int **h;
    
    int *HFAC;
    int *XHFAC;
    int *YHFAC;

    int *YPFAC;
    int *XYPFAC;

    int *HPFAC;
    int *XHPFAC;
    int *YPHPFAC;

    int **DELTA_WY;
    int **WY;

    int **DELTA_WX;
    int **WX;

    int **DELTA_WH;
    int **WH;
}rbm;

//Function Declartions

void train_rbm(mnist_data *train_data, mnist_data *train_label_data);



#endif
