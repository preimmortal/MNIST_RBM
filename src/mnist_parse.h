#ifndef MNIST_PARSE
#define MNIST_PARSE

//If Little Endian Machine leave this define in
#define MNIST_LITTLE_ENDIAN

//Includes
#include <stdio.h>
#include <stdlib.h>

#define TRAIN_SIZE 1000
#define COLS 28
#define ROWS 28
#define COLROW 784

//Function Declarations
void parse_simple_image_file(FILE *image_fp, char data[TRAIN_SIZE][COLROW]);
void parse_simple_label_file(FILE *label_fp, char data[TRAIN_SIZE]);

void print_simple_mnist_data(
        char train_data[TRAIN_SIZE][COLROW], 
        char train_label_data[TRAIN_SIZE]);

#endif
