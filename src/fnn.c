
#include "fnn.h"
#include <string.h>

static NEURON_WORD evalNeuron( NEURON_WORD const * inputs, NEURON_WORD const * weights, int magnitude )
{
    size_t size = 1 << magnitude;
    int final_shift = NEURON_WORD_BITS - magnitude;
    NEURON_LONG sum=0;

    // Multiply, Accumulate across the neurons incomming connections
    while( size-- > 0)
    {
        sum += (NEURON_LONG)(*inputs++) * (NEURON_LONG)(*weights++) >> magnitude;
    }

    // Round sum up in final shift
    sum = (sum + ((1 << final_shift) - 1)) >> final_shift;
    if (sum > NEURON_WORD_THRESHOLD)
    {
        return NEURON_WORD_THRESHOLD;
    }
    else
    {
        return (NEURON_WORD)sum;
    }
}

static void fill_column( NEURON_WORD const * inputs, const int input_magnitude, NEURON_WORD const * const * weight_sets, NEURON_WORD output[], int output_size )
{
//    int i;
//    for( i=0; i<output_size; ++i)
//    {
//        output[i] = evalNeuron( inputs, weight_sets[i], input_magnitude);
//    }
    while( output_size-- > 0)
    {
        *output++ = evalNeuron( inputs, *weight_sets++, input_magnitude);
    }
}


static int evalNetworkDownStep( NEURON_WORD const * inputs, const int input_magnitude, int downsteps, NEURON_WORD const * const * const connectionWeights[], NEURON_WORD* outputs)
{
    const int my_buf_size = 1<<(input_magnitude-1);
    NEURON_WORD my_buf[my_buf_size];
    if( downsteps <= 1 )
    {
        if( downsteps <= 0 )
        {
            memcpy( outputs, inputs, (1<<input_magnitude)*sizeof(NEURON_WORD) );
            return (1<<input_magnitude);
        }
        else
        {
            fill_column(inputs, input_magnitude, connectionWeights[0], outputs, my_buf_size);
            return my_buf_size;
        }
    }
    fill_column(inputs, input_magnitude, connectionWeights[0], my_buf, my_buf_size);

    return evalNetworkDownStep( my_buf, input_magnitude-1, downsteps-1, &connectionWeights[1], outputs );
}

int evalNetwork( NEURON_WORD const * inputs, const int input_magnitude, int upsteps, int downsteps, NEURON_WORD const * const * const connectionWeights[], NEURON_WORD* outputs)
{
    const int my_buf_size = 1<<(input_magnitude+1);
    NEURON_WORD my_buf[my_buf_size];
    if( upsteps <= 1 )
    {
        if( upsteps <= 0 )
        {
            return evalNetworkDownStep( inputs, input_magnitude, downsteps, connectionWeights, outputs );
        }
        else if( downsteps <= 0 )
        {
            fill_column(inputs, input_magnitude, connectionWeights[0], outputs, my_buf_size);
            return my_buf_size;
        }
        else
        {
            fill_column(inputs, input_magnitude, connectionWeights[0], my_buf, my_buf_size);
            return evalNetworkDownStep( my_buf, input_magnitude+1, downsteps, &connectionWeights[1], outputs );
        }
    }
    fill_column(inputs, input_magnitude, connectionWeights[0], my_buf, my_buf_size);

    return evalNetwork( my_buf, input_magnitude+1, upsteps-1, downsteps, &connectionWeights[1], outputs );
}



