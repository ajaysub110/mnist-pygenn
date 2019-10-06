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
                const scalar scale = (-5.20000000000000000e+01f) - (-6.50000000000000000e+01f);
                Vlif_e_pop[i] = (-6.50000000000000000e+01f) + (standardUniformDistribution(rng) * scale);
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
            inSynsyn_ie_pop[i] = 0.000000f;
        }
        for (unsigned i = 0; i < 100; i++) {
            inSynsyn_pe_pop[i] = 0.000000f;
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
                const scalar scale = (-4.00000000000000000e+01f) - (-4.50000000000000000e+01f);
                Vlif_i_pop[i] = (-4.50000000000000000e+01f) + (standardUniformDistribution(rng) * scale);
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
            inSynsyn_ei_pop[i] = 0.000000f;
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
                ratepoisson_pop[i] = (1.00000000000000000e+02f);
            }
        }
         {
            for (unsigned i = 0; i < 784; i++) {
                timeStepToSpikepoisson_pop[i] = (0.00000000000000000e+00f);
            }
        }
         {
            for (unsigned i = 0; i < 784; i++) {
                Xpresyn_pe_pop[i] = (0.00000000000000000e+00f);
            }
        }
        // current source variables
    }
    // ------------------------------------------------------------------------
    // Synapse groups with dense connectivity
    // synapse group syn_ie_pop
     {
        for(unsigned int i = 0; i < 100; i++) {
             {
                for (unsigned j = 0; j < 100; j++) {
                    gsyn_ie_pop[(i * 100) + j]=(i==j) ? 0.0f : (1.00000000000000006e-01f);
                }
            }
        }
    }
    // synapse group syn_pe_pop
     {
        for(unsigned int i = 0; i < 784; i++) {
             {
                for (unsigned j = 0; j < 100; j++) {
                    const scalar scale = (1.00000000000000000e+00f) - (0.00000000000000000e+00f);
                    gsyn_pe_pop[(i * 100) + j] = (0.00000000000000000e+00f) + (standardUniformDistribution(rng) * scale);
                }
            }
             {
                for (unsigned j = 0; j < 100; j++) {
                    etasyn_pe_pop[(i * 100) + j] = (1.00000000000000006e-01f);
                }
            }
        }
    }
    // ------------------------------------------------------------------------
    // Synapse groups with sparse connectivity
    // synapse group syn_ei_pop
    memset(rowLengthsyn_ei_pop, 0, 100 * sizeof(unsigned int));
    for (unsigned int i = 0; i < 100; i++) {
        // Build sparse connectivity
        while(true) {
            indsyn_ei_pop[(i * 1) + (rowLengthsyn_ei_pop[i]++)] = i;
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
                for (unsigned j = 0; j < rowLengthsyn_ei_pop[i]; j++) {
                    const scalar scale = (1.00000000000000000e+00f) - (0.00000000000000000e+00f);
                    gsyn_ei_pop[(i * 1) + j] = (0.00000000000000000e+00f) + (standardUniformDistribution(rng) * scale);
                }
            }
        }
    }
}
