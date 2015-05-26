#include <stdio.h>
#include <stdlib.h>

#include "rbm.h"
#include "mnist_parse.h"
#include "train.h"

#define TRAIN_SIZE 1000
#define TEST_SIZE 1000

#define ROWS 28
#define COLS 28
#define COLROW 784

char train_data[TRAIN_SIZE][COLROW];
char train_label_data[TRAIN_SIZE];
char test_data[TEST_SIZE][COLROW];
char test_label_data[TEST_SIZE];

void load_datasets(){
	FILE *train_images_fp;
	FILE *test_images_fp;
	FILE *train_labels_fp;
	FILE *test_labels_fp;
	
	//Train Images
	train_images_fp = fopen("../datasets/train-images.idx3-ubyte", "r");
	parse_simple_image_file(train_images_fp, train_data);
	fclose(train_images_fp);
	//mnist_print_image(train_data);
    
    //Test Images
    test_images_fp = fopen("../datasets/t10k-images.idx3-ubyte", "r");
    parse_simple_image_file(test_images_fp, test_data);
    fclose(test_images_fp);

	//Train Labels
	train_labels_fp = fopen("../datasets/train-labels.idx1-ubyte", "r");
	parse_simple_label_file(train_labels_fp, train_label_data);
	fclose(train_labels_fp);

    //Test Images
    test_labels_fp = fopen("../datasets/t10k-labels.idx1-ubyte", "r");
    parse_simple_label_file(test_images_fp, test_label_data);
    fclose(test_labels_fp);
}


int main(void){
    //Load Data Sets
    load_datasets();
	//print_simple_mnist_data(test_data, test_label_data);
    
    //printf("%f\n",rand_twister());

    train_rbm(train_data, train_label_data);

	return 0;
}

