/**
 * Header file for the Fast Neural Network Evaluator.
 *
 * @author Ted Kotz
 * @version 0.1
 * @see "fnn.c"
 */
#ifndef FAST_NUERAL_NETWORK_H
#define FAST_NUERAL_NETWORK_H

/** Includes *****************************************************************/
#include <stdint.h>

/** Constants and Macros *****************************************************/
#define NEURON_WORD_BITS (16)
#define NEURON_WORD_THRESHOLD (0xFFFF)

/** Type Definitions *********************************************************/
typedef uint16_t NEURON_WORD;
typedef uint32_t NEURON_LONG;

/** Data *********************************************************************/

/** Functions ****************************************************************/
extern int evalNetwork( NEURON_WORD const * inputs, const int input_magnitude, int upsteps, int downsteps, NEURON_WORD const * const * const connectionWeights[], NEURON_WORD* outputs);


#endif //FAST_NUERAL_NETWORK_H
