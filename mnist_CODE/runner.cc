

//-------------------------------------------------------------------------
/*! \file runner.cc

\brief File generated from GeNN for the model mnist containing general control code.
*/
//-------------------------------------------------------------------------

#define RUNNER_CC_COMPILE

#include "definitions.h"
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <ctime>
#include <cassert>
#include <stdint.h>
#if defined(__GNUG__) && !defined(__clang__) && defined(__x86_64__)
    #include <gnu/libc-version.h>
#endif

// ------------------------------------------------------------------------
// global variables

extern "C" {
unsigned long long iT;
float t;

std::mt19937 rng;
std::uniform_real_distribution<float> standardUniformDistribution(0.000000f, 1.000000f);
std::normal_distribution<float> standardNormalDistribution(0.000000f, 1.000000f);
std::exponential_distribution<float> standardExponentialDistribution(1.000000f);

// ------------------------------------------------------------------------
// remote neuron groups


// ------------------------------------------------------------------------
// neuron variables

unsigned int * glbSpkCntlif_e_pop;
unsigned int * glbSpklif_e_pop;
float * sTlif_e_pop;
scalar * Vlif_e_pop;
scalar * RefracTimelif_e_pop;
// current source variables
unsigned int * glbSpkCntlif_i_pop;
unsigned int * glbSpklif_i_pop;
float * sTlif_i_pop;
scalar * Vlif_i_pop;
scalar * RefracTimelif_i_pop;
// current source variables
unsigned int * glbSpkCntpoisson_pop;
unsigned int * glbSpkpoisson_pop;
unsigned int spkQuePtrpoisson_pop;
float * sTpoisson_pop;
scalar * timeStepToSpikepoisson_pop;
// current source variables

// ------------------------------------------------------------------------
// postsynaptic variables
float * inSynsyn_i_pop;
float * inSyninput_e_pop;
float * inSynsyn_e_pop;

// ------------------------------------------------------------------------
// synapse variables

scalar * ginput_e_pop;
scalar * preTraceinput_e_pop;
scalar * postTraceinput_e_pop;
scalar * gsyn_e_pop;
scalar * preTracesyn_e_pop;
scalar * postTracesyn_e_pop;
scalar * gsyn_i_pop;
scalar * preTracesyn_i_pop;
scalar * postTracesyn_i_pop;

}	// extern "C"
//-------------------------------------------------------------------------
/*! \brief Function to convert a firing probability (per time step) 
to an integer of type uint64_t that can be used as a threshold for the GeNN random number generator to generate events with the given probability.
*/
//-------------------------------------------------------------------------

void convertProbabilityToRandomNumberThreshold(float *p_pattern, uint64_t *pattern, int N) {
    float fac= pow(2.0, (double) sizeof(uint64_t)*8-16);
    for (int i= 0; i < N; i++) {
        pattern[i]= (uint64_t) (p_pattern[i]*fac);
    }
}

//-------------------------------------------------------------------------
/*! \brief Function to convert a firing rate (in kHz) 
to an integer of type uint64_t that can be used as a threshold for the GeNN random number generator to generate events with the given rate.
*/
//-------------------------------------------------------------------------

void convertRateToRandomNumberThreshold(float *rateKHz_pattern, uint64_t *pattern, int N) {
    float fac= pow(2.0, (double) sizeof(uint64_t)*8-16)*DT;
    for (int i= 0; i < N; i++) {
        pattern[i]= (uint64_t) (rateKHz_pattern[i]*fac);
    }
}

#include "init.cc"
#include "neuronFnct.cc"
#include "synapseFnct.cc"

void allocateMem() {
    // ------------------------------------------------------------------------
    // remote neuron groups
    
    
    // ------------------------------------------------------------------------
    // local neuron groups
    glbSpkCntlif_e_pop = new unsigned int[1];
    glbSpklif_e_pop = new unsigned int[1];
    sTlif_e_pop = new float[1];
    Vlif_e_pop = new scalar[1];
    RefracTimelif_e_pop = new scalar[1];
    // current source variables
    
    glbSpkCntlif_i_pop = new unsigned int[1];
    glbSpklif_i_pop = new unsigned int[1];
    sTlif_i_pop = new float[1];
    Vlif_i_pop = new scalar[1];
    RefracTimelif_i_pop = new scalar[1];
    // current source variables
    
    glbSpkCntpoisson_pop = new unsigned int[151];
    glbSpkpoisson_pop = new unsigned int[151];
    sTpoisson_pop = new float[151];
    timeStepToSpikepoisson_pop = new scalar[1];
    // current source variables
    
    inSynsyn_i_pop = new float[1];
    inSyninput_e_pop = new float[1];
    inSynsyn_e_pop = new float[1];
    preTraceinput_e_pop = new scalar[151];
    postTraceinput_e_pop = new scalar[1];
    ginput_e_pop = new scalar[1];
    
    preTracesyn_e_pop = new scalar[1];
    postTracesyn_e_pop = new scalar[1];
    gsyn_e_pop = new scalar[1];
    
    preTracesyn_i_pop = new scalar[1];
    postTracesyn_i_pop = new scalar[1];
    gsyn_i_pop = new scalar[1];
    
}

void freeMem() {
    delete[] glbSpkCntlif_e_pop;
    delete[] glbSpklif_e_pop;
    delete[] sTlif_e_pop;
    delete[] Vlif_e_pop;
    delete[] RefracTimelif_e_pop;
    delete[] glbSpkCntlif_i_pop;
    delete[] glbSpklif_i_pop;
    delete[] sTlif_i_pop;
    delete[] Vlif_i_pop;
    delete[] RefracTimelif_i_pop;
    delete[] glbSpkCntpoisson_pop;
    delete[] glbSpkpoisson_pop;
    delete[] sTpoisson_pop;
    delete[] timeStepToSpikepoisson_pop;
    delete[] inSynsyn_i_pop;
    delete[] inSyninput_e_pop;
    delete[] inSynsyn_e_pop;
    delete[] preTraceinput_e_pop;
    delete[] postTraceinput_e_pop;
    delete[] ginput_e_pop;
    delete[] preTracesyn_e_pop;
    delete[] postTracesyn_e_pop;
    delete[] gsyn_e_pop;
    delete[] preTracesyn_i_pop;
    delete[] postTracesyn_i_pop;
    delete[] gsyn_i_pop;
}

void exitGeNN() {
    freeMem();
}

// ------------------------------------------------------------------------
// the actual time stepping procedure (using CPU)
void stepTimeCPU() {
    calcSynapsesCPU(t);
    learnSynapsesPostHost(t);
    spkQuePtrpoisson_pop = (spkQuePtrpoisson_pop + 1) % 151;
    calcNeuronsCPU(t);
    iT++;
    t= iT*DT;
}
