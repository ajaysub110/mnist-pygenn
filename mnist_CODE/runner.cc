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
scalar* timeStepToSpikepoisson_pop;
scalar* frequencypoisson_pop;

// ------------------------------------------------------------------------
// postsynaptic variables
// ------------------------------------------------------------------------
float* inSynsyn_i_pop;
float* inSyninput_e_pop;
float* inSynsyn_e_pop;

// ------------------------------------------------------------------------
// synapse connectivity
// ------------------------------------------------------------------------
const unsigned int maxRowLengthsyn_e_pop = 1;
unsigned int* rowLengthsyn_e_pop;
unsigned int* indsyn_e_pop;

// ------------------------------------------------------------------------
// synapse variables
// ------------------------------------------------------------------------
scalar* ginput_e_pop;
scalar* etainput_e_pop;
scalar* Xpreinput_e_pop;
scalar* gsyn_e_pop;
scalar* gsyn_i_pop;

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

void pushtimeStepToSpikepoisson_popToDevice(bool uninitialisedOnly) {
}

void pushfrequencypoisson_popToDevice(bool uninitialisedOnly) {
}

void pushpoisson_popStateToDevice(bool uninitialisedOnly) {
    pushtimeStepToSpikepoisson_popToDevice(uninitialisedOnly);
    pushfrequencypoisson_popToDevice(uninitialisedOnly);
}

void pushsyn_e_popConnectivityToDevice(bool uninitialisedOnly) {
}

void pushginput_e_popToDevice(bool uninitialisedOnly) {
}

void pushetainput_e_popToDevice(bool uninitialisedOnly) {
}

void pushXpreinput_e_popToDevice(bool uninitialisedOnly) {
}

void pushinSyninput_e_popToDevice(bool uninitialisedOnly) {
}

void pushinput_e_popStateToDevice(bool uninitialisedOnly) {
    pushginput_e_popToDevice(uninitialisedOnly);
    pushetainput_e_popToDevice(uninitialisedOnly);
    pushXpreinput_e_popToDevice(uninitialisedOnly);
    pushinSyninput_e_popToDevice(uninitialisedOnly);
}

void pushgsyn_e_popToDevice(bool uninitialisedOnly) {
}

void pushinSynsyn_e_popToDevice(bool uninitialisedOnly) {
}

void pushsyn_e_popStateToDevice(bool uninitialisedOnly) {
    pushgsyn_e_popToDevice(uninitialisedOnly);
    pushinSynsyn_e_popToDevice(uninitialisedOnly);
}

void pushgsyn_i_popToDevice(bool uninitialisedOnly) {
}

void pushinSynsyn_i_popToDevice(bool uninitialisedOnly) {
}

void pushsyn_i_popStateToDevice(bool uninitialisedOnly) {
    pushgsyn_i_popToDevice(uninitialisedOnly);
    pushinSynsyn_i_popToDevice(uninitialisedOnly);
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

void pulltimeStepToSpikepoisson_popFromDevice() {
}

void pullfrequencypoisson_popFromDevice() {
}

void pullpoisson_popStateFromDevice() {
    pulltimeStepToSpikepoisson_popFromDevice();
    pullfrequencypoisson_popFromDevice();
}

void pullsyn_e_popConnectivityFromDevice() {
}

void pullginput_e_popFromDevice() {
}

void pulletainput_e_popFromDevice() {
}

void pullXpreinput_e_popFromDevice() {
}

void pullinSyninput_e_popFromDevice() {
}

void pullinput_e_popStateFromDevice() {
    pullginput_e_popFromDevice();
    pulletainput_e_popFromDevice();
    pullXpreinput_e_popFromDevice();
    pullinSyninput_e_popFromDevice();
}

void pullgsyn_e_popFromDevice() {
}

void pullinSynsyn_e_popFromDevice() {
}

void pullsyn_e_popStateFromDevice() {
    pullgsyn_e_popFromDevice();
    pullinSynsyn_e_popFromDevice();
}

void pullgsyn_i_popFromDevice() {
}

void pullinSynsyn_i_popFromDevice() {
}

void pullsyn_i_popStateFromDevice() {
    pullgsyn_i_popFromDevice();
    pullinSynsyn_i_popFromDevice();
}


void copyStateToDevice(bool uninitialisedOnly) {
    pushlif_e_popStateToDevice(uninitialisedOnly);
    pushlif_i_popStateToDevice(uninitialisedOnly);
    pushpoisson_popStateToDevice(uninitialisedOnly);
    pushinput_e_popStateToDevice(uninitialisedOnly);
    pushsyn_e_popStateToDevice(uninitialisedOnly);
    pushsyn_i_popStateToDevice(uninitialisedOnly);
}

void copyConnectivityToDevice(bool uninitialisedOnly) {
    pushsyn_e_popConnectivityToDevice(uninitialisedOnly);
}

void copyStateFromDevice() {
    pulllif_e_popStateFromDevice();
    pulllif_i_popStateFromDevice();
    pullpoisson_popStateFromDevice();
    pullinput_e_popStateFromDevice();
    pullsyn_e_popStateFromDevice();
    pullsyn_i_popStateFromDevice();
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
    timeStepToSpikepoisson_pop = new scalar[784];
    frequencypoisson_pop = new scalar[784];
    
    // ------------------------------------------------------------------------
    // postsynaptic variables
    // ------------------------------------------------------------------------
    inSynsyn_i_pop = new float[100];
    inSyninput_e_pop = new float[100];
    inSynsyn_e_pop = new float[100];
    
    // ------------------------------------------------------------------------
    // synapse connectivity
    // ------------------------------------------------------------------------
    rowLengthsyn_e_pop = new unsigned int[100];
    indsyn_e_pop = new unsigned int[100];
    
    // ------------------------------------------------------------------------
    // synapse variables
    // ------------------------------------------------------------------------
    ginput_e_pop = new scalar[78400];
    etainput_e_pop = new scalar[78400];
    Xpreinput_e_pop = new scalar[784];
    gsyn_e_pop = new scalar[100];
    gsyn_i_pop = new scalar[10000];
    
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
    delete[] timeStepToSpikepoisson_pop;
    delete[] frequencypoisson_pop;
    
    // ------------------------------------------------------------------------
    // postsynaptic variables
    // ------------------------------------------------------------------------
    delete[] inSynsyn_i_pop;
    delete[] inSyninput_e_pop;
    delete[] inSynsyn_e_pop;
    
    // ------------------------------------------------------------------------
    // synapse connectivity
    // ------------------------------------------------------------------------
    delete[] rowLengthsyn_e_pop;
    delete[] indsyn_e_pop;
    
    // ------------------------------------------------------------------------
    // synapse variables
    // ------------------------------------------------------------------------
    delete[] ginput_e_pop;
    delete[] etainput_e_pop;
    delete[] Xpreinput_e_pop;
    delete[] gsyn_e_pop;
    delete[] gsyn_i_pop;
    
}

void stepTime() {
    updateSynapses(t);
    updateNeurons(t);
    iT++;
    t = iT*DT;
}

