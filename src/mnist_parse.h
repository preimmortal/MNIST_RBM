#ifndef MNIST_PARSE
#define MNIST_PARSE

//If Little Endian Machine leave this define in
#define MNIST_LITTLE_ENDIAN

//Includes
#include <stdio.h>
#include <stdlib.h>

#define TRAIN_SIZE 1000
#define TEST_SIZE 500

//Struct Definition
typedef struct{
	unsigned int magic_num;
	unsigned int num_items;
	unsigned int num_rows;
	unsigned int num_cols;
	char *data;
}mnist_data;

//Function Declarations
void parse_image_file(FILE *image_fp, mnist_data * mh);
void parse_label_file(FILE *label_fp, mnist_data * mh);

void mnist_print_image(mnist_data *d);
void mnist_print_label(mnist_data *d);

void print_mnist_data(mnist_data *train_data, mnist_data *train_label_data);

#endif
