
#include "fnn.h"
#include <stdio.h>
#include <time.h>


//  1,1  2,1 3,1
//  1,2  2,2 3,2
//       2,3
//       2,4
//
// inputs: 2
// steps: up:1 down: 1
//

#define SELECT NEURON_WORD_THRESHOLD

const NEURON_WORD N1_OF_4[4] = { SELECT, 0x0000, 0x0000, 0x0000, };
const NEURON_WORD N2_OF_4[4] = { 0x0000, SELECT, 0x0000, 0x0000, };
const NEURON_WORD N3_OF_4[4] = { 0x0000, 0x0000, SELECT, 0x0000, };
const NEURON_WORD N4_OF_4[4] = { 0x0000, 0x0000, 0x0000, SELECT, };

const NEURON_WORD N1_OF_8[8] = { SELECT, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, };
const NEURON_WORD N2_OF_8[8] = { 0x0000, SELECT, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, };
const NEURON_WORD N3_OF_8[8] = { 0x0000, 0x0000, SELECT, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, };
const NEURON_WORD N4_OF_8[8] = { 0x0000, 0x0000, 0x0000, SELECT, 0x0000, 0x0000, 0x0000, 0x0000, };
const NEURON_WORD N5_OF_8[8] = { 0x0000, 0x0000, 0x0000, 0x0000, SELECT, 0x0000, 0x0000, 0x0000, };
const NEURON_WORD N6_OF_8[8] = { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, SELECT, 0x0000, 0x0000, };
const NEURON_WORD N7_OF_8[8] = { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, SELECT, 0x0000, };
const NEURON_WORD N8_OF_8[8] = { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8000, };


NEURON_WORD const * const COL1[8] = { N1_OF_4, N2_OF_4, N3_OF_4, N4_OF_4, N1_OF_4, N2_OF_4, N3_OF_4, N4_OF_4 };
NEURON_WORD const * const COL2[4] = { N2_OF_8, N5_OF_8, N4_OF_8, N8_OF_8};

NEURON_WORD const * const * const NETWORK[] = {COL1, COL2};

void printArray( NEURON_WORD const * inputs, int size )
{
    int i;
    for (i=0; i<size; ++i)
    {
        printf("%6d:",inputs[i]);
    }
    printf("\n");
}

void zeroArray( NEURON_WORD* inputs, int size )
{
    int i;
    for (i=0; i<size; ++i)
    {
        inputs[i]=0;
    }
}

int main( int argc, char** argv )
{
    clock_t start_time, end_time;
    NEURON_WORD inputs[]={4, 200, -1, 0x8000};
    NEURON_WORD outputs[4];
    printArray( inputs, 4);
    printArray( outputs, 4);
    printf("return: %d\n",evalNetwork( inputs, 2, 0, 0, NULL, outputs ));
    printArray( inputs, 4);
    printArray( outputs, 4);
    zeroArray( outputs, 4);
    printf("return: %d\n",evalNetwork( inputs, 2, 1, 1, NETWORK, outputs ));
    printArray( inputs, 4);
    printArray( outputs, 4);


    start_time=clock();
    for(int i=0; i<1000000; ++i)
    {
        evalNetwork( inputs, 2, 1, 1, NETWORK, outputs );
    }
    end_time=clock();

    printf("elapsedtime: %f\n",(double)(end_time - start_time) / CLOCKS_PER_SEC);


    return 0;
}
