#include "mnist_parse.h"

//Endian Reverse Function
unsigned int reverse_endian(unsigned int value){
	return ((value>>24)&0x000000ff)
		|((value<<24)&0xff000000)
		|((value>>8)&0x0000ff00)
		|((value<<8)&0x00ff0000);
}

void parse_simple_image_file(FILE *image_fp, char data[TRAIN_SIZE][COLROW]){
    //Read Header
    unsigned int magic_num;
    unsigned int num_items;
    unsigned int num_rows;
    unsigned int num_cols;
	fread(&magic_num, 1, 4, image_fp);
	fread(&num_items, 1, 4, image_fp);
	fread(&num_rows, 1, 4, image_fp);
	fread(&num_cols, 1, 4, image_fp);

	//Reverse Endianess if Little Endian
	#ifdef MNIST_LITTLE_ENDIAN
	magic_num = reverse_endian(magic_num);
	num_items = reverse_endian(num_items);
	num_rows = reverse_endian(num_rows);
	num_cols = reverse_endian(num_cols);
	#endif

	//Read Only Read_Size Items
	num_items = TRAIN_SIZE;

	printf("------------------------\n");
	printf("Magic_Number: %d\nNum_Items: %d\nNum_Rows: %d\nNum_Cols: %d\n", magic_num, num_items, num_rows, num_cols); 
	
	if(magic_num != 0x0803){
		error("MNUM Incorrect - Check Endian\n");	
		return;
	}

    //Declare Data
	printf("Reading Data..\n");
	int i, j, k;
    
	for(i=0; i<num_items; i++){
		for(j=0; j<num_rows; j++){
			for(k=0; k<num_cols; k++){
				fread(&data[i][j*num_cols+k], 1, 1, image_fp);
				//Parse into binary input values only
				if(data[i][j*num_cols+k] != 0){
					data[i][j*num_cols+k] = 1;
				}
			}
		}
	}
	printf("Done Reading Data\n");
	printf("------------------------\n");
}

void parse_simple_label_file(FILE *label_fp, char data[TRAIN_SIZE]){
    unsigned int magic_num;
    unsigned int num_items;
	unsigned int num_rows = 0;
	unsigned int num_cols = 0;

	//Read Header
	fread(&magic_num, 1, 4, label_fp);
	fread(&num_items, 1, 4, label_fp);

	//Reverse Endianess if Little Endian
	#ifdef MNIST_LITTLE_ENDIAN
	magic_num = reverse_endian(magic_num);
	num_items = reverse_endian(num_items);
	#endif

	//Read Only Size of items Items
	num_items = TRAIN_SIZE;
	
	printf("------------------------\n");
	printf("Magic_Number: %d\nNum_Items: %d\n", magic_num, num_items); 
	
	if(magic_num != 0x0801){
		error("MNUM Incorrect - Check Endian\n");	
		return;
	}

	printf("Reading Data..\n");
	int i;
	for(i=0; i<num_items; i++){
		fread(&data[i], 1, 1, label_fp);
		//printf("data[%d]: %d\n", i, data[i]); 
	}
	printf("Done Reading Data\n");
	printf("------------------------\n");
}

void print_simple_mnist_data(
        char train_data[TRAIN_SIZE][COLROW],
        char train_label_data[TRAIN_SIZE]){
	int i, j, k;
	for(i=0; i<TRAIN_SIZE; i++){
		printf("IDX: %d\n", i);
		for(j=0; j<ROWS; j++){
			for(k=0; k<COLS; k++){
				if(train_data[i][j*COLS+k]!=0) printf("  ");
				else printf("0 ");
			}
			printf("\n");
		}
		printf("%d \n", train_label_data[i]);
		printf("\n");
	}
}

