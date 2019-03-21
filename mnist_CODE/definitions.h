

//-------------------------------------------------------------------------
/*! \file definitions.h

\brief File generated from GeNN for the model mnist containing useful Macros used for both GPU amd CPU versions.
*/
//-------------------------------------------------------------------------

#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include "utils.h"
#include "sparseUtils.h"

#include "sparseProjection.h"
#include <cstdint>
#include <random>

#define __device__
#define __global__
#define __host__
#define __constant__
#define __shared__
#undef DT
#define DT 1.000000f
#ifndef MYRAND
#define MYRAND(Y,X) Y = Y * 1103515245 + 12345; X = (Y >> 16);
#endif
#ifndef MYRAND_MAX
#define MYRAND_MAX 0x0000FFFFFFFFFFFFLL
#endif

#ifndef scalar
typedef float scalar;
#endif
#ifndef SCALAR_MIN
#define SCALAR_MIN 1.175494351e-38f
#endif
#ifndef SCALAR_MAX
#define SCALAR_MAX 3.402823466e+38f
#endif

#ifndef TIME_MIN
#define TIME_MIN 1.175494351e-38f
#endif
#ifndef TIME_MAX
#define TIME_MAX 3.402823466e+38f
#endif

extern "C" {
// ------------------------------------------------------------------------
// global variables

extern unsigned long long iT;
extern float t;

extern std::mt19937 rng;
extern std::uniform_real_distribution<float> standardUniformDistribution;
extern std::normal_distribution<float> standardNormalDistribution;
extern std::exponential_distribution<float> standardExponentialDistribution;

// ------------------------------------------------------------------------
// remote neuron groups


// ------------------------------------------------------------------------
// neuron variables

extern unsigned int * glbSpkCntlif_e_pop;
extern unsigned int * glbSpklif_e_pop;
extern float * sTlif_e_pop;
extern scalar * Vlif_e_pop;
extern scalar * RefracTimelif_e_pop;
// current source variables
extern unsigned int * glbSpkCntlif_i_pop;
extern unsigned int * glbSpklif_i_pop;
extern float * sTlif_i_pop;
extern scalar * Vlif_i_pop;
extern scalar * RefracTimelif_i_pop;
// current source variables
extern unsigned int * glbSpkCntpoisson_pop;
extern unsigned int * glbSpkpoisson_pop;
extern unsigned int spkQuePtrpoisson_pop;
extern float * sTpoisson_pop;
extern scalar * timeStepToSpikepoisson_pop;
// current source variables

#define glbSpkShiftlif_e_pop 0
#define glbSpkShiftlif_i_pop 0
#define glbSpkShiftpoisson_pop spkQuePtrpoisson_pop*1
#define spikeCount_lif_e_pop glbSpkCntlif_e_pop[0]
#define spike_lif_e_pop glbSpklif_e_pop
#define spikeCount_lif_i_pop glbSpkCntlif_i_pop[0]
#define spike_lif_i_pop glbSpklif_i_pop
#define spikeCount_poisson_pop glbSpkCntpoisson_pop[spkQuePtrpoisson_pop]
#define spike_poisson_pop (glbSpkpoisson_pop+(spkQuePtrpoisson_pop*1))

// ------------------------------------------------------------------------
// postsynaptic variables

extern float * inSynsyn_i_pop;
extern float * inSyninput_e_pop;
extern float * inSynsyn_e_pop;

// ------------------------------------------------------------------------
// synapse variables

extern scalar * ginput_e_pop;
extern scalar * preTraceinput_e_pop;
extern scalar * postTraceinput_e_pop;
extern scalar * gsyn_e_pop;
extern scalar * preTracesyn_e_pop;
extern scalar * postTracesyn_e_pop;
extern scalar * gsyn_i_pop;
extern scalar * preTracesyn_i_pop;
extern scalar * postTracesyn_i_pop;

#define Conductance SparseProjection
/*struct Conductance is deprecated. 
  By GeNN 2.0, Conductance is renamed as SparseProjection and contains only indexing values. 
  Please consider updating your user code by renaming Conductance as SparseProjection 
  and making g member a synapse variable.*/

// ------------------------------------------------------------------------
// Function for setting the CUDA device and the host's global variables.
// Also estimates memory usage on device.

void allocateMem();

// ------------------------------------------------------------------------
// Function to (re)set all model variables to their compile-time, homogeneous initial
// values. Note that this typically includes synaptic weight values. The function
// (re)sets host side variables and copies them to the GPU device.

void initialize();

// ------------------------------------------------------------------------
// Method for cleaning up and resetting device while quitting GeNN.

void exitGeNN();

// ------------------------------------------------------------------------
// initialization of variables, e.g. reverse sparse arrays etc.
// that the user would not want to worry about

void initmnist();

// ------------------------------------------------------------------------
// Function to free all global memory structures.

void freeMem();

//-------------------------------------------------------------------------
// Function to convert a firing probability (per time step) to an integer of type uint64_t
// that can be used as a threshold for the GeNN random number generator to generate events with the given probability.

void convertProbabilityToRandomNumberThreshold(float *p_pattern, uint64_t *pattern, int N);

//-------------------------------------------------------------------------
// Function to convert a firing rate (in kHz) to an integer of type uint64_t that can be used
// as a threshold for the GeNN random number generator to generate events with the given rate.

void convertRateToRandomNumberThreshold(float *rateKHz_pattern, uint64_t *pattern, int N);

// ------------------------------------------------------------------------
// the actual time stepping procedure (using CPU)

void stepTimeCPU();

}	// extern "C"
// ------------------------------------------------------------------------
// Throw an error for "old style" time stepping calls (using CPU)

template <class T>
void stepTimeCPU(T arg1, ...) {
    gennError("Since GeNN 2.2 the call to step time has changed to not take any arguments. You appear to attempt to pass arguments. This is no longer supported. See the GeNN 2.2. release notes and the manual for examples how to pass data like, e.g., Poisson rates and direct inputs, that were previously handled through arguments.");
}

#endif
