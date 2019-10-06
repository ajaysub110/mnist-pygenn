#include "definitionsInternal.h"

extern "C" {
// ------------------------------------------------------------------------
// global variables
// ------------------------------------------------------------------------
unsigned long long iT;
float t;
std::mt19937 rng;
std::uniform_real_distribution<float> standardUniformDistribution(0.000000f, 1.000000f);
std::normal_distribution<float> standardNormalDistribution(0.000000f, 1.000000f);
std::exponential_distribution<float> standardExponentialDistribution(1.000000f);

// ------------------------------------------------------------------------
// timers
// ------------------------------------------------------------------------
double neuronUpdateTime;
double initTime;
double presynapticUpdateTime;
double postsynapticUpdateTime;
double synapseDynamicsTime;
double initSparseTime;
// ------------------------------------------------------------------------
// remote neuron groups
// ------------------------------------------------------------------------

// ------------------------------------------------------------------------
// local neuron groups
// ------------------------------------------------------------------------
unsigned int* glbSpkCntlif_e_pop;
unsigned int* glbSpklif_e_pop;
float* sTlif_e_pop;
scalar* Vlif_e_pop;
scalar* RefracTimelif_e_pop;
scalar* thetalif_e_pop;
unsigned int* SpikeNumberlif_e_pop;
unsigned int* glbSpkCntlif_i_pop;
unsigned int* glbSpklif_i_pop;
scalar* Vlif_i_pop;
scalar* RefracTimelif_i_pop;
unsigned int* SpikeNumberlif_i_pop;
unsigned int* glbSpkCntpoisson_pop;
unsigned int* glbSpkpoisson_pop;
float* sTpoisson_pop;
scalar* ratepoisson_pop;
scalar* timeStepToSpikepoisson_pop;

// ------------------------------------------------------------------------
// postsynaptic variables
// ------------------------------------------------------------------------
float* inSynsyn_ie_pop;
float* inSynsyn_pe_pop;
float* inSynsyn_ei_pop;

// ------------------------------------------------------------------------
// synapse connectivity
// ------------------------------------------------------------------------
const unsigned int maxRowLengthsyn_ei_pop = 1;
unsigned int* rowLengthsyn_ei_pop;
unsigned int* indsyn_ei_pop;

// ------------------------------------------------------------------------
// synapse variables
// ------------------------------------------------------------------------
scalar* gsyn_ei_pop;
scalar* gsyn_ie_pop;
scalar* gsyn_pe_pop;
scalar* etasyn_pe_pop;
scalar* Xpresyn_pe_pop;

}  // extern "C"
// ------------------------------------------------------------------------
// extra global params
// ------------------------------------------------------------------------

// ------------------------------------------------------------------------
// copying things to device
// ------------------------------------------------------------------------
void pushlif_e_popSpikesToDevice(bool uninitialisedOnly) {
}

void pushlif_e_popCurrentSpikesToDevice(bool uninitialisedOnly) {
}

void pushlif_e_popSpikeTimesToDevice(bool uninitialisedOnly) {
}

void pushVlif_e_popToDevice(bool uninitialisedOnly) {
}

void pushRefracTimelif_e_popToDevice(bool uninitialisedOnly) {
}

void pushthetalif_e_popToDevice(bool uninitialisedOnly) {
}

void pushSpikeNumberlif_e_popToDevice(bool uninitialisedOnly) {
}

void pushlif_e_popStateToDevice(bool uninitialisedOnly) {
    pushVlif_e_popToDevice(uninitialisedOnly);
    pushRefracTimelif_e_popToDevice(uninitialisedOnly);
    pushthetalif_e_popToDevice(uninitialisedOnly);
    pushSpikeNumberlif_e_popToDevice(uninitialisedOnly);
}

void pushlif_i_popSpikesToDevice(bool uninitialisedOnly) {
}

void pushlif_i_popCurrentSpikesToDevice(bool uninitialisedOnly) {
}

void pushVlif_i_popToDevice(bool uninitialisedOnly) {
}

void pushRefracTimelif_i_popToDevice(bool uninitialisedOnly) {
}

void pushSpikeNumberlif_i_popToDevice(bool uninitialisedOnly) {
}

void pushlif_i_popStateToDevice(bool uninitialisedOnly) {
    pushVlif_i_popToDevice(uninitialisedOnly);
    pushRefracTimelif_i_popToDevice(uninitialisedOnly);
    pushSpikeNumberlif_i_popToDevice(uninitialisedOnly);
}

void pushpoisson_popSpikesToDevice(bool uninitialisedOnly) {
}

void pushpoisson_popCurrentSpikesToDevice(bool uninitialisedOnly) {
}

void pushpoisson_popSpikeTimesToDevice(bool uninitialisedOnly) {
}

void pushratepoisson_popToDevice(bool uninitialisedOnly) {
}

void pushtimeStepToSpikepoisson_popToDevice(bool uninitialisedOnly) {
}

void pushpoisson_popStateToDevice(bool uninitialisedOnly) {
    pushratepoisson_popToDevice(uninitialisedOnly);
    pushtimeStepToSpikepoisson_popToDevice(uninitialisedOnly);
}

void pushsyn_ei_popConnectivityToDevice(bool uninitialisedOnly) {
}

void pushgsyn_ei_popToDevice(bool uninitialisedOnly) {
}

void pushinSynsyn_ei_popToDevice(bool uninitialisedOnly) {
}

void pushsyn_ei_popStateToDevice(bool uninitialisedOnly) {
    pushgsyn_ei_popToDevice(uninitialisedOnly);
    pushinSynsyn_ei_popToDevice(uninitialisedOnly);
}

void pushgsyn_ie_popToDevice(bool uninitialisedOnly) {
}

void pushinSynsyn_ie_popToDevice(bool uninitialisedOnly) {
}

void pushsyn_ie_popStateToDevice(bool uninitialisedOnly) {
    pushgsyn_ie_popToDevice(uninitialisedOnly);
    pushinSynsyn_ie_popToDevice(uninitialisedOnly);
}

void pushgsyn_pe_popToDevice(bool uninitialisedOnly) {
}

void pushetasyn_pe_popToDevice(bool uninitialisedOnly) {
}

void pushXpresyn_pe_popToDevice(bool uninitialisedOnly) {
}

void pushinSynsyn_pe_popToDevice(bool uninitialisedOnly) {
}

void pushsyn_pe_popStateToDevice(bool uninitialisedOnly) {
    pushgsyn_pe_popToDevice(uninitialisedOnly);
    pushetasyn_pe_popToDevice(uninitialisedOnly);
    pushXpresyn_pe_popToDevice(uninitialisedOnly);
    pushinSynsyn_pe_popToDevice(uninitialisedOnly);
}


// ------------------------------------------------------------------------
// copying things from device
// ------------------------------------------------------------------------
void pulllif_e_popSpikesFromDevice() {
}

void pulllif_e_popCurrentSpikesFromDevice() {
}

void pulllif_e_popSpikeTimesFromDevice() {
}

void pullVlif_e_popFromDevice() {
}

void pullRefracTimelif_e_popFromDevice() {
}

void pullthetalif_e_popFromDevice() {
}

void pullSpikeNumberlif_e_popFromDevice() {
}

void pulllif_e_popStateFromDevice() {
    pullVlif_e_popFromDevice();
    pullRefracTimelif_e_popFromDevice();
    pullthetalif_e_popFromDevice();
    pullSpikeNumberlif_e_popFromDevice();
}

void pulllif_i_popSpikesFromDevice() {
}

void pulllif_i_popCurrentSpikesFromDevice() {
}

void pullVlif_i_popFromDevice() {
}

void pullRefracTimelif_i_popFromDevice() {
}

void pullSpikeNumberlif_i_popFromDevice() {
}

void pulllif_i_popStateFromDevice() {
    pullVlif_i_popFromDevice();
    pullRefracTimelif_i_popFromDevice();
    pullSpikeNumberlif_i_popFromDevice();
}

void pullpoisson_popSpikesFromDevice() {
}

void pullpoisson_popCurrentSpikesFromDevice() {
}

void pullpoisson_popSpikeTimesFromDevice() {
}

void pullratepoisson_popFromDevice() {
}

void pulltimeStepToSpikepoisson_popFromDevice() {
}

void pullpoisson_popStateFromDevice() {
    pullratepoisson_popFromDevice();
    pulltimeStepToSpikepoisson_popFromDevice();
}

void pullsyn_ei_popConnectivityFromDevice() {
}

void pullgsyn_ei_popFromDevice() {
}

void pullinSynsyn_ei_popFromDevice() {
}

void pullsyn_ei_popStateFromDevice() {
    pullgsyn_ei_popFromDevice();
    pullinSynsyn_ei_popFromDevice();
}

void pullgsyn_ie_popFromDevice() {
}

void pullinSynsyn_ie_popFromDevice() {
}

void pullsyn_ie_popStateFromDevice() {
    pullgsyn_ie_popFromDevice();
    pullinSynsyn_ie_popFromDevice();
}

void pullgsyn_pe_popFromDevice() {
}

void pulletasyn_pe_popFromDevice() {
}

void pullXpresyn_pe_popFromDevice() {
}

void pullinSynsyn_pe_popFromDevice() {
}

void pullsyn_pe_popStateFromDevice() {
    pullgsyn_pe_popFromDevice();
    pulletasyn_pe_popFromDevice();
    pullXpresyn_pe_popFromDevice();
    pullinSynsyn_pe_popFromDevice();
}


void copyStateToDevice(bool uninitialisedOnly) {
    pushlif_e_popStateToDevice(uninitialisedOnly);
    pushlif_i_popStateToDevice(uninitialisedOnly);
    pushpoisson_popStateToDevice(uninitialisedOnly);
    pushsyn_ei_popStateToDevice(uninitialisedOnly);
    pushsyn_ie_popStateToDevice(uninitialisedOnly);
    pushsyn_pe_popStateToDevice(uninitialisedOnly);
}

void copyConnectivityToDevice(bool uninitialisedOnly) {
    pushsyn_ei_popConnectivityToDevice(uninitialisedOnly);
}

void copyStateFromDevice() {
    pulllif_e_popStateFromDevice();
    pulllif_i_popStateFromDevice();
    pullpoisson_popStateFromDevice();
    pullsyn_ei_popStateFromDevice();
    pullsyn_ie_popStateFromDevice();
    pullsyn_pe_popStateFromDevice();
}

void copyCurrentSpikesFromDevice() {
    pulllif_e_popCurrentSpikesFromDevice();
    pulllif_i_popCurrentSpikesFromDevice();
    pullpoisson_popCurrentSpikesFromDevice();
}

void copyCurrentSpikeEventsFromDevice() {
}

void allocateMem() {
    // ------------------------------------------------------------------------
    // global variables
    // ------------------------------------------------------------------------
    
    // ------------------------------------------------------------------------
    // timers
    // ------------------------------------------------------------------------
    // ------------------------------------------------------------------------
    // remote neuron groups
    // ------------------------------------------------------------------------
    
    // ------------------------------------------------------------------------
    // local neuron groups
    // ------------------------------------------------------------------------
    glbSpkCntlif_e_pop = new unsigned int[1];
    glbSpklif_e_pop = new unsigned int[100];
    sTlif_e_pop = new float[100];
    Vlif_e_pop = new scalar[100];
    RefracTimelif_e_pop = new scalar[100];
    thetalif_e_pop = new scalar[100];
    SpikeNumberlif_e_pop = new unsigned int[100];
    glbSpkCntlif_i_pop = new unsigned int[1];
    glbSpklif_i_pop = new unsigned int[100];
    Vlif_i_pop = new scalar[100];
    RefracTimelif_i_pop = new scalar[100];
    SpikeNumberlif_i_pop = new unsigned int[100];
    glbSpkCntpoisson_pop = new unsigned int[1];
    glbSpkpoisson_pop = new unsigned int[784];
    sTpoisson_pop = new float[784];
    ratepoisson_pop = new scalar[784];
    timeStepToSpikepoisson_pop = new scalar[784];
    
    // ------------------------------------------------------------------------
    // postsynaptic variables
    // ------------------------------------------------------------------------
    inSynsyn_ie_pop = new float[100];
    inSynsyn_pe_pop = new float[100];
    inSynsyn_ei_pop = new float[100];
    
    // ------------------------------------------------------------------------
    // synapse connectivity
    // ------------------------------------------------------------------------
    rowLengthsyn_ei_pop = new unsigned int[100];
    indsyn_ei_pop = new unsigned int[100];
    
    // ------------------------------------------------------------------------
    // synapse variables
    // ------------------------------------------------------------------------
    gsyn_ei_pop = new scalar[100];
    gsyn_ie_pop = new scalar[10000];
    gsyn_pe_pop = new scalar[78400];
    etasyn_pe_pop = new scalar[78400];
    Xpresyn_pe_pop = new scalar[784];
    
}

void freeMem() {
    // ------------------------------------------------------------------------
    // global variables
    // ------------------------------------------------------------------------
    
    // ------------------------------------------------------------------------
    // timers
    // ------------------------------------------------------------------------
    // ------------------------------------------------------------------------
    // remote neuron groups
    // ------------------------------------------------------------------------
    
    // ------------------------------------------------------------------------
    // local neuron groups
    // ------------------------------------------------------------------------
    delete[] glbSpkCntlif_e_pop;
    delete[] glbSpklif_e_pop;
    delete[] sTlif_e_pop;
    delete[] Vlif_e_pop;
    delete[] RefracTimelif_e_pop;
    delete[] thetalif_e_pop;
    delete[] SpikeNumberlif_e_pop;
    delete[] glbSpkCntlif_i_pop;
    delete[] glbSpklif_i_pop;
    delete[] Vlif_i_pop;
    delete[] RefracTimelif_i_pop;
    delete[] SpikeNumberlif_i_pop;
    delete[] glbSpkCntpoisson_pop;
    delete[] glbSpkpoisson_pop;
    delete[] sTpoisson_pop;
    delete[] ratepoisson_pop;
    delete[] timeStepToSpikepoisson_pop;
    
    // ------------------------------------------------------------------------
    // postsynaptic variables
    // ------------------------------------------------------------------------
    delete[] inSynsyn_ie_pop;
    delete[] inSynsyn_pe_pop;
    delete[] inSynsyn_ei_pop;
    
    // ------------------------------------------------------------------------
    // synapse connectivity
    // ------------------------------------------------------------------------
    delete[] rowLengthsyn_ei_pop;
    delete[] indsyn_ei_pop;
    
    // ------------------------------------------------------------------------
    // synapse variables
    // ------------------------------------------------------------------------
    delete[] gsyn_ei_pop;
    delete[] gsyn_ie_pop;
    delete[] gsyn_pe_pop;
    delete[] etasyn_pe_pop;
    delete[] Xpresyn_pe_pop;
    
}

void stepTime() {
    updateSynapses(t);
    updateNeurons(t);
    iT++;
    t = iT*DT;
}

