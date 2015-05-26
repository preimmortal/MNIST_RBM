//train.c

#include "train.h"

double weights[NUM_VISIBLE+1][NUM_HIDDEN+1];

double pos_hidden_activations[NUM_HIDDEN+1];
double pos_hidden_probs[NUM_HIDDEN+1];

double pos_assoc[NUM_VISIBLE+1][NUM_HIDDEN+1];

double neg_visible_activations[NUM_VISIBLE+1];
double neg_visible_probs[NUM_VISIBLE+1];

double neg_hidden_activations[NUM_HIDDEN+1];
double neg_hidden_probs[NUM_HIDDEN+1];

double neg_assoc[NUM_VISIBLE+1][NUM_HIDDEN+1];


//Random Number Generator
#define SEED 12345
static unsigned int s1 = SEED, s2 = SEED, s3 = SEED, b;

double taus_rng ()
{   /* Generates numbers between 0 and 1. */
    b = (((s1 << 13) ^ s1) >> 19);
    s1 = (((s1 & 4294967294) << 12) ^ b);
    b = (((s2 << 2) ^ s2) >> 25);
    s2 = (((s2 & 4294967288) << 4) ^ b);
    b = (((s3 << 3) ^ s3) >> 11);
    s3 = (((s3 & 4294967280) << 17) ^ b);
    return ((s1 ^ s2 ^ s3) * 2.3283064365386963e-10);
}

double logistic(double x){
    return (1/(1+exp(-x)));
}



void print_weights(){
    int i, j;
    printf("\nCurrent Weights\n");
    for(i=0; i<NUM_VISIBLE+1; i++){
        for(j=0; j<NUM_HIDDEN+1; j++){
            printf("%f ", weights[i][j]);
        }
        printf("\n");
    }
}

void zero_arrays(){
/* Must Zero Out These Arrays
double pos_hidden_activations[TRAIN_SIZE][NUM_HIDDEN+1];
double pos_hidden_probs[TRAIN_SIZE][NUM_HIDDEN+1];
double pos_assoc[NUM_VISIBLE+1][NUM_HIDDEN+1];

double neg_visible_activations[TRAIN_SIZE][NUM_VISIBLE+1];
double neg_visible_probs[TRAIN_SIZE][NUM_VISIBLE+1];

double neg_hidden_activations[TRAIN_SIZE][NUM_HIDDEN+1];
double neg_hidden_probs[TRAIN_SIZE][NUM_HIDDEN+1];

double neg_assoc[NUM_VISIBLE+1][NUM_HIDDEN+1];
*/
    int i, j;
    //Zero Out Pos Arrays
    for(j=0;j<NUM_HIDDEN+1;j++){
        pos_hidden_activations[j] = 0;
        pos_hidden_probs[j] = 0;
        neg_hidden_activations[j] = 0;
        neg_hidden_probs[j] = 0;
    }
    for(j=0; j<NUM_VISIBLE+1; j++){
        neg_visible_activations[j] = 0;
        neg_visible_probs[j] = 0;
    }
}

void zero_assoc(){
    int i,j;
    for(i=0; i<NUM_VISIBLE+1; i++){
        for(j=0; j<NUM_HIDDEN+1; j++){
            pos_assoc[i][j] = 0;
            neg_assoc[i][j] = 0;
        }
    }
}

void initialize_weights(){
    int i,j;
    for(i=0;i<NUM_VISIBLE+1;i++){
        for(j=0; j<NUM_HIDDEN+1;j++){
            if(i==0 || j==0){
                weights[i][j] = 0;
                continue;
            }
            weights[i][j] = (taus_rng()>0.5)?0.1*taus_rng():-0.1*taus_rng();
        }
    }
}


void train_rbm(char train_data[TRAIN_SIZE][COLROW], 
        char train_label_data[TRAIN_SIZE]){
    printf("Training RBM\n");

    int e, t;
    int i,j;

    //Insert Bias into Data
    int data[TRAIN_SIZE][NUM_VISIBLE+1]; 
    for(t=0; t<TRAIN_SIZE; t++){
        for(j=0; j<NUM_VISIBLE+1; j++){
            if(j==0){
                data[t][j] = 1;
            }else{
                data[t][j] = train_data[t][j-1];
            }
        }
    }

    //Initialize Weights
    initialize_weights();


#ifdef DEBUG
    printf("\nTest Printing Data\n");
    int k;
    for(i=0; i<TRAIN_SIZE; i++){
        /*
        for(j=0; j<NUM_VISIBLE+1; j++){
            printf("%d ", data[i][j]);
        }
        printf("\n");
        */
        for(j=0;j<COLS;j++){
            for(k=0;k<ROWS+1;k++){
                printf("%d ", data[i][j*COLS+k]);
            }
            printf("\n");
        }
        printf("\n");
    }   
#endif
 
    //Run Training for Desired number of epochs
    for(e=0; e<NUM_EPOCHS; e++){
        //Calculate dot product of positive activations
        //Dot product of data and weights
        zero_assoc();
        double ERROR = 0;

        for(t=0; t<TRAIN_SIZE; t++){
            zero_arrays();

            //Calculate Pos Hidden Activations
            for(i=0; i<NUM_HIDDEN+1; i++){
                for(j=0; j<NUM_VISIBLE+1; j++){
                    pos_hidden_activations[i] += data[t][j]*weights[j][i];
                }
            }


            //Calculate Hidden Probability
            for(i=0; i<NUM_HIDDEN+1; i++){
                pos_hidden_probs[i] = logistic(pos_hidden_activations[i]);
            }

            //Calculate Positive Associations
            //Dot product of data and positive hidden probabilities
            for(i=0; i<NUM_HIDDEN+1; i++){
                for(j=0; j<NUM_VISIBLE+1; j++){
                    pos_assoc[j][i] += data[t][j]*pos_hidden_probs[i];
                }
            }

            //Calculate Negative Visible Activations
            for(i=0; i<NUM_HIDDEN+1; i++){
                if(pos_hidden_probs[i] > taus_rng()){
                    for(j=0; j<NUM_VISIBLE+1; j++){
                        //Gibbs Sampling
                        neg_visible_activations[j] += weights[j][i];
                    }
                }
            }

            //Calculate Neg Visible Probability
            for(j=0; j<NUM_VISIBLE+1; j++){
                neg_visible_probs[j] = logistic(neg_visible_activations[j]);
                if(j==0){
                    neg_visible_probs[j] = 1;
                }
            }

            //Calculate Neg Hidden Activations
            for(i=0; i<NUM_HIDDEN+1; i++){
                for(j=0; j<NUM_VISIBLE+1; j++){
                    neg_hidden_activations[i] += 
                        neg_visible_probs[j] * weights[j][i];
                }
            }

            //Calculate Neg Hidden Probabilities
            for(i=0; i<NUM_HIDDEN+1; i++){
                neg_hidden_probs[i] = logistic(neg_hidden_activations[i]);
            }


            //Calculate Neg Associations
            for(i=0; i<NUM_HIDDEN+1; i++){
                for(j=0; j<NUM_VISIBLE+1; j++){
                    neg_assoc[j][i] += neg_visible_probs[j]*neg_hidden_probs[i];
                }
            }

            //Calculate Error
            for(j=0; j<NUM_VISIBLE+1; j++){
                ERROR += pow((double)data[t][j] - neg_visible_probs[j], 2);
            }

        } //End Training Data

        //zero_weights();
        //Recalculate Weights
        for(i=0; i<NUM_HIDDEN+1; i++){
            for(j=0; j<NUM_VISIBLE+1; j++){
                weights[j][i] += LEARN_RATE * 
                    ((pos_assoc[j][i]-neg_assoc[j][i])/TRAIN_SIZE);
            }
        }
        printf("Epoch %d - Error: %f\n", e, ERROR);
    } //End Epoch

    printf("Done Training - Calculated Weights\n");
    print_weights();
}

