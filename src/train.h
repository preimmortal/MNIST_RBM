#ifndef TRAIN_H_
#define TRAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "mnist_parse.h"

#define NUM_HIDDEN 100
#define NUM_VISIBLE 784
#define TRAIN_SIZE 1000
#define NUM_EPOCHS 50
#define LEARN_RATE 0.1

#define ROWS 28
#define COLS 28
#define COLROW 784
//Function Declarations

void train_rbm(
        char train_data[TRAIN_SIZE][COLROW], 
        char train_label_data[TRAIN_SIZE]);


#endif
