//train.c
//Creates RBM Structure

#include "train.h"

rbm *init_rbm(void){
    rbm *RBM = (rbm *)malloc(sizeof(rbm));

    RBM->XFAC = (int *)malloc(sizeof(int) * NUM_FACTORS);
    RBM->YFAC = (int *)malloc(sizeof(int) * NUM_FACTORS);
    RBM->XYFAC = (int *)malloc(sizeof(int) * NUM_FACTORS);
    RBM->tem = (int *)malloc(sizeof(int) * NUM_HIDDEN);

    return RBM;
}

void free_rbm(rbm *R){
    free(R);
}

void train_rbm(mnist_data *train_data, mnist_data *train_label_data){
    printf("Training RBM\n");

    rbm *RBM = init_rbm(); 

    int e, b, f, p;
    int i, j;
    int BATCH_SIZE = train_data->num_items/NUM_BATCHES;
    //Train over Epochs
    for(e=0; e<NUM_EPOCHS; e++){
        for(b=0; b<NUM_BATCHES; b++){
            for(p=b*BATCH_SIZE; p<(b*BATCH_SIZE+BATCH_SIZE); p++){
                //printf("Batch: %d - %d\n", b, p);
                
                //Phase 1
                for(f=0; f<NUM_FACTORS; f++){ //Serial Loop
                }
            }
        }
    }
}

