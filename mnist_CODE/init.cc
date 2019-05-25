#include "definitionsInternal.h"
void initialize() {
     {
        uint32_t seedData[std::mt19937::state_size];
        std::random_device seedSource;
         {
            for(int i = 0; i < std::mt19937::state_size; i++) {
                seedData[i] = seedSource();
            }
        }
        std::seed_seq seeds(std::begin(seedData), std::end(seedData));
        rng.seed(seeds);
    }
    
    // ------------------------------------------------------------------------
    // Remote neuron groups
    
    // ------------------------------------------------------------------------
    // Local neuron groups
    // neuron group lif_e_pop
     {
        glbSpkCntlif_e_pop[0] = 0;
        for (unsigned i = 0; i < 100; i++) {
            glbSpklif_e_pop[i] = 0;
        }
        for (unsigned i = 0; i < 100; i++) {
            sTlif_e_pop[i] = -TIME_MAX;
        }
         {
            for (unsigned i = 0; i < 100; i++) {
                Vlif_e_pop[i] = (-6.50000000000000000e+01f);
            }
        }
         {
            for (unsigned i = 0; i < 100; i++) {
                RefracTimelif_e_pop[i] = (0.00000000000000000e+00f);
            }
        }
         {
            for (unsigned i = 0; i < 100; i++) {
                thetalif_e_pop[i] = (0.00000000000000000e+00f);
            }
        }
         {
            for (unsigned i = 0; i < 100; i++) {
                SpikeNumberlif_e_pop[i] = (0.00000000000000000e+00f);
            }
        }
        for (unsigned i = 0; i < 100; i++) {
            inSynsyn_i_pop[i] = 0.000000f;
        }
        for (unsigned i = 0; i < 100; i++) {
            inSyninput_e_pop[i] = 0.000000f;
        }
        // current source variables
    }
    // neuron group lif_i_pop
     {
        glbSpkCntlif_i_pop[0] = 0;
        for (unsigned i = 0; i < 100; i++) {
            glbSpklif_i_pop[i] = 0;
        }
         {
            for (unsigned i = 0; i < 100; i++) {
                Vlif_i_pop[i] = (-4.50000000000000000e+01f);
            }
        }
         {
            for (unsigned i = 0; i < 100; i++) {
                RefracTimelif_i_pop[i] = (0.00000000000000000e+00f);
            }
        }
         {
            for (unsigned i = 0; i < 100; i++) {
                SpikeNumberlif_i_pop[i] = (0.00000000000000000e+00f);
            }
        }
        for (unsigned i = 0; i < 100; i++) {
            inSynsyn_e_pop[i] = 0.000000f;
        }
        // current source variables
    }
    // neuron group poisson_pop
     {
        glbSpkCntpoisson_pop[0] = 0;
        for (unsigned i = 0; i < 784; i++) {
            glbSpkpoisson_pop[i] = 0;
        }
        for (unsigned i = 0; i < 784; i++) {
            sTpoisson_pop[i] = -TIME_MAX;
        }
         {
            for (unsigned i = 0; i < 784; i++) {
                timeStepToSpikepoisson_pop[i] = (0.00000000000000000e+00f);
            }
        }
         {
            for (unsigned i = 0; i < 784; i++) {
                frequencypoisson_pop[i] = (0.00000000000000000e+00f);
            }
        }
         {
            for (unsigned i = 0; i < 784; i++) {
                Xpreinput_e_pop[i] = (0.00000000000000000e+00f);
            }
        }
        // current source variables
    }
    // ------------------------------------------------------------------------
    // Synapse groups with dense connectivity
    // synapse group input_e_pop
     {
        for(unsigned int i = 0; i < 784; i++) {
             {
                for (unsigned j = 0; j < 100; j++) {
                    const scalar scale = (1.00000000000000000e+01f) - (0.00000000000000000e+00f);
                    ginput_e_pop[(i * 100) + j] = (0.00000000000000000e+00f) + (standardUniformDistribution(rng) * scale);
                }
            }
             {
                for (unsigned j = 0; j < 100; j++) {
                    etainput_e_pop[(i * 100) + j] = (1.00000000000000002e-03f);
                }
            }
        }
    }
    // synapse group syn_i_pop
     {
        for(unsigned int i = 0; i < 100; i++) {
             {
                for (unsigned j = 0; j < 100; j++) {
                    const scalar scale = (-1.00000000000000000e+01f) - (0.00000000000000000e+00f);
                    gsyn_i_pop[(i * 100) + j] = (0.00000000000000000e+00f) + (standardUniformDistribution(rng) * scale);
                }
            }
        }
    }
    // ------------------------------------------------------------------------
    // Synapse groups with sparse connectivity
    // synapse group syn_e_pop
    memset(rowLengthsyn_e_pop, 0, 100 * sizeof(unsigned int));
    for (unsigned int i = 0; i < 100; i++) {
        // Build sparse connectivity
        while(true) {
            indsyn_e_pop[(i * 1) + (rowLengthsyn_e_pop[i]++)] = i;
            break;
            
        }
    }
}

void initializeSparse() {
    // ------------------------------------------------------------------------
    // Synapse groups with sparse connectivity
     {
        // Loop through presynaptic neurons
        for (unsigned int i = 0; i < 100; i++)
         {
             {
                for (unsigned j = 0; j < rowLengthsyn_e_pop[i]; j++) {
                    const scalar scale = (1.00000000000000000e+01f) - (0.00000000000000000e+00f);
                    gsyn_e_pop[(i * 1) + j] = (0.00000000000000000e+00f) + (standardUniformDistribution(rng) * scale);
                }
            }
        }
    }
}
