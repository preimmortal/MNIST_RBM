#include <stdio.h>
#include <stdlib.h>

#include "rbm.h"
#include "mnist_parse.h"

#define TRAIN_SIZE 1000
#define TEST_SIZE 500

#define NUM_EPOCHS 10
#define NUM_BATCHES 10
#define NUM_HIDDEN 100
#define BATCH_SIZE 10

void load_datasets(mnist_data *train_data, mnist_data *train_label_data, mnist_data *test_data, mnist_data *test_label_data){
	FILE *train_images_fp;
	FILE *test_images_fp;
	FILE *train_labels_fp;
	FILE *test_labels_fp;
	//mnist_data *train_data;
	//mnist_data *train_label_data;
	//mnist_data *test_data;
	//mnist_data *test_label_data;
	
	//Train Images
	train_images_fp = fopen("../datasets/train-images.idx3-ubyte", "r");
	parse_image_file(train_images_fp, train_data, TRAIN_SIZE);
	fclose(train_images_fp);
	//mnist_print_image(train_data);
    
    //Test Images
    test_images_fp = fopen("../datasets/t10k-images.idx3-ubyte", "r");
    parse_image_file(test_images_fp, test_data, TEST_SIZE);
    fclose(test_images_fp);
	

	//Train Labels
	train_labels_fp = fopen("../datasets/train-labels.idx1-ubyte", "r");
	parse_label_file(train_labels_fp, train_label_data, TRAIN_SIZE);
	fclose(train_labels_fp);

    //Test Images
    test_labels_fp = fopen("../datasets/t10k-labels.idx1-ubyte", "r");
    parse_label_file(test_images_fp, test_label_data, TEST_SIZE);
    fclose(test_labels_fp);

	//mnist_print_label(train_label_data);
}



void train_rbm(mnist_data *train_data, mnist_data *train_label_data){
    printf("Training RBM\n");
    int e, b, f;
    //Train over Epochs
    for(e=0; e<NUM_EPOCHS; e++){
        for(b=0; b<NUM_BATCHES; b++){
            //Phase 1


        }
    }
}

int main(void){
	mnist_data *train_data = (mnist_data *)malloc(sizeof(mnist_data));
	mnist_data *train_label_data = (mnist_data *)malloc(sizeof(mnist_data));
    mnist_data *test_data = (mnist_data *)malloc(sizeof(mnist_data));
	mnist_data *test_label_data = (mnist_data *)malloc(sizeof(mnist_data));

	
    //Load Data Sets
    load_datasets(train_data, train_label_data, test_data, test_label_data);
	//print_mnist_data(train_data, train_label_data);
    
    //printf("%f\n",rand_twister());

    train_rbm(train_data, train_label_data);

    //Free Malloc Data
	free(train_data);
	free(train_label_data);
	free(test_data);
	free(test_label_data);


	return 0;
}

