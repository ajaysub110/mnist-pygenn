#pragma once
#define EXPORT_VAR extern
#define EXPORT_FUNC
// Standard C++ includes
#include <chrono>
#include <iostream>
#include <random>

// Standard C includes
#include <cmath>
#include <cstdint>
#include <cstring>
#define DT 1.000000f
typedef float scalar;
#define SCALAR_MIN 1.175494351e-38f
#define SCALAR_MAX 3.402823466e+38f

#define TIME_MIN 1.175494351e-38f
#define TIME_MAX 3.402823466e+38f

// ------------------------------------------------------------------------
// bit tool macros
#define B(x,i) ((x) & (0x80000000 >> (i))) //!< Extract the bit at the specified position i from x
#define setB(x,i) x= ((x) | (0x80000000 >> (i))) //!< Set the bit at the specified position i in x to 1
#define delB(x,i) x= ((x) & (~(0x80000000 >> (i)))) //!< Set the bit at the specified position i in x to 0

extern "C" {
// ------------------------------------------------------------------------
// global variables
// ------------------------------------------------------------------------
EXPORT_VAR unsigned long long iT;
EXPORT_VAR float t;
EXPORT_VAR std::mt19937 rng;
EXPORT_VAR std::uniform_real_distribution<float> standardUniformDistribution;
EXPORT_VAR std::normal_distribution<float> standardNormalDistribution;
EXPORT_VAR std::exponential_distribution<float> standardExponentialDistribution;

// ------------------------------------------------------------------------
// timers
// ------------------------------------------------------------------------
EXPORT_VAR double neuronUpdateTime;
EXPORT_VAR double initTime;
EXPORT_VAR double presynapticUpdateTime;
EXPORT_VAR double postsynapticUpdateTime;
EXPORT_VAR double synapseDynamicsTime;
EXPORT_VAR double initSparseTime;
// ------------------------------------------------------------------------
// remote neuron groups
// ------------------------------------------------------------------------

// ------------------------------------------------------------------------
// local neuron groups
// ------------------------------------------------------------------------
#define spikeCount_lif_e_pop glbSpkCntlif_e_pop[0]
#define spike_lif_e_pop glbSpklif_e_pop
#define glbSpkShiftlif_e_pop 0

EXPORT_VAR unsigned int* glbSpkCntlif_e_pop;
EXPORT_VAR unsigned int* glbSpklif_e_pop;
EXPORT_VAR float* sTlif_e_pop;
EXPORT_VAR scalar* Vlif_e_pop;
EXPORT_VAR scalar* RefracTimelif_e_pop;
EXPORT_VAR scalar* thetalif_e_pop;
EXPORT_VAR unsigned int* SpikeNumberlif_e_pop;
#define spikeCount_lif_i_pop glbSpkCntlif_i_pop[0]
#define spike_lif_i_pop glbSpklif_i_pop
#define glbSpkShiftlif_i_pop 0

EXPORT_VAR unsigned int* glbSpkCntlif_i_pop;
EXPORT_VAR unsigned int* glbSpklif_i_pop;
EXPORT_VAR scalar* Vlif_i_pop;
EXPORT_VAR scalar* RefracTimelif_i_pop;
EXPORT_VAR unsigned int* SpikeNumberlif_i_pop;
#define spikeCount_poisson_pop glbSpkCntpoisson_pop[0]
#define spike_poisson_pop glbSpkpoisson_pop
#define glbSpkShiftpoisson_pop 0

EXPORT_VAR unsigned int* glbSpkCntpoisson_pop;
EXPORT_VAR unsigned int* glbSpkpoisson_pop;
EXPORT_VAR float* sTpoisson_pop;
EXPORT_VAR scalar* ratepoisson_pop;
EXPORT_VAR scalar* timeStepToSpikepoisson_pop;

// ------------------------------------------------------------------------
// postsynaptic variables
// ------------------------------------------------------------------------
EXPORT_VAR float* inSynsyn_ie_pop;
EXPORT_VAR float* inSynsyn_pe_pop;
EXPORT_VAR float* inSynsyn_ei_pop;

// ------------------------------------------------------------------------
// synapse connectivity
// ------------------------------------------------------------------------
EXPORT_VAR const unsigned int maxRowLengthsyn_ei_pop;
EXPORT_VAR unsigned int* rowLengthsyn_ei_pop;
EXPORT_VAR unsigned int* indsyn_ei_pop;

// ------------------------------------------------------------------------
// synapse variables
// ------------------------------------------------------------------------
EXPORT_VAR scalar* gsyn_ei_pop;
EXPORT_VAR scalar* gsyn_ie_pop;
EXPORT_VAR scalar* gsyn_pe_pop;
EXPORT_VAR scalar* etasyn_pe_pop;
EXPORT_VAR scalar* Xpresyn_pe_pop;

EXPORT_FUNC void pushlif_e_popSpikesToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pulllif_e_popSpikesFromDevice();
EXPORT_FUNC void pushlif_e_popCurrentSpikesToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pulllif_e_popCurrentSpikesFromDevice();
EXPORT_FUNC void pushlif_e_popSpikeTimesToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pulllif_e_popSpikeTimesFromDevice();
EXPORT_FUNC void pushVlif_e_popToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullVlif_e_popFromDevice();
EXPORT_FUNC void pushRefracTimelif_e_popToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullRefracTimelif_e_popFromDevice();
EXPORT_FUNC void pushthetalif_e_popToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullthetalif_e_popFromDevice();
EXPORT_FUNC void pushSpikeNumberlif_e_popToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullSpikeNumberlif_e_popFromDevice();
EXPORT_FUNC void pushlif_e_popStateToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pulllif_e_popStateFromDevice();
EXPORT_FUNC void pushlif_i_popSpikesToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pulllif_i_popSpikesFromDevice();
EXPORT_FUNC void pushlif_i_popCurrentSpikesToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pulllif_i_popCurrentSpikesFromDevice();
EXPORT_FUNC void pushVlif_i_popToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullVlif_i_popFromDevice();
EXPORT_FUNC void pushRefracTimelif_i_popToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullRefracTimelif_i_popFromDevice();
EXPORT_FUNC void pushSpikeNumberlif_i_popToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullSpikeNumberlif_i_popFromDevice();
EXPORT_FUNC void pushlif_i_popStateToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pulllif_i_popStateFromDevice();
EXPORT_FUNC void pushpoisson_popSpikesToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullpoisson_popSpikesFromDevice();
EXPORT_FUNC void pushpoisson_popCurrentSpikesToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullpoisson_popCurrentSpikesFromDevice();
EXPORT_FUNC void pushpoisson_popSpikeTimesToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullpoisson_popSpikeTimesFromDevice();
EXPORT_FUNC void pushratepoisson_popToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullratepoisson_popFromDevice();
EXPORT_FUNC void pushtimeStepToSpikepoisson_popToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pulltimeStepToSpikepoisson_popFromDevice();
EXPORT_FUNC void pushpoisson_popStateToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullpoisson_popStateFromDevice();
EXPORT_FUNC void pushsyn_ei_popConnectivityToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullsyn_ei_popConnectivityFromDevice();
EXPORT_FUNC void pushgsyn_ei_popToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullgsyn_ei_popFromDevice();
EXPORT_FUNC void pushinSynsyn_ei_popToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullinSynsyn_ei_popFromDevice();
EXPORT_FUNC void pushsyn_ei_popStateToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullsyn_ei_popStateFromDevice();
EXPORT_FUNC void pushgsyn_ie_popToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullgsyn_ie_popFromDevice();
EXPORT_FUNC void pushinSynsyn_ie_popToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullinSynsyn_ie_popFromDevice();
EXPORT_FUNC void pushsyn_ie_popStateToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullsyn_ie_popStateFromDevice();
EXPORT_FUNC void pushgsyn_pe_popToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullgsyn_pe_popFromDevice();
EXPORT_FUNC void pushetasyn_pe_popToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pulletasyn_pe_popFromDevice();
EXPORT_FUNC void pushXpresyn_pe_popToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullXpresyn_pe_popFromDevice();
EXPORT_FUNC void pushinSynsyn_pe_popToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullinSynsyn_pe_popFromDevice();
EXPORT_FUNC void pushsyn_pe_popStateToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void pullsyn_pe_popStateFromDevice();
// Runner functions
EXPORT_FUNC void copyStateToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void copyConnectivityToDevice(bool uninitialisedOnly = false);
EXPORT_FUNC void copyStateFromDevice();
EXPORT_FUNC void copyCurrentSpikesFromDevice();
EXPORT_FUNC void copyCurrentSpikeEventsFromDevice();
EXPORT_FUNC void allocateMem();
EXPORT_FUNC void freeMem();
EXPORT_FUNC void stepTime();

// Functions generated by backend
EXPORT_FUNC void updateNeurons(float t);
EXPORT_FUNC void updateSynapses(float t);
EXPORT_FUNC void initialize();
EXPORT_FUNC void initializeSparse();
}  // extern "C"
