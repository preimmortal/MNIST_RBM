#include <stdio.h>
#include <stdlib.h>

#include "mnist_parse.h"


void load_datasets(mnist_data *train_data, mnist_data *train_label_data){
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
	parse_image_file(train_images_fp, train_data);
	fclose(train_images_fp);
	//mnist_print_image(train_data);
	

	//Train Labels
	train_labels_fp = fopen("../datasets/train-labels.idx1-ubyte", "r");
	parse_label_file(train_labels_fp, train_label_data);
	fclose(train_labels_fp);
	//mnist_print_label(train_label_data);
}


int main(void){
	mnist_data *train_data = (mnist_data *)malloc(sizeof(mnist_data));
	mnist_data *train_label_data = (mnist_data *)malloc(sizeof(mnist_data));
	load_datasets(train_data, train_label_data);
	print_mnist_data(train_data, train_label_data);
	free(train_data);
	free(train_label_data);
	return 0;
}

