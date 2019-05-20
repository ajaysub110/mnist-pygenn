#include "definitionsInternal.h"
#include "supportCode.h"

void updateSynapses(float t) {
    // synapse group input_e_pop
     {
        // process presynaptic events: True Spikes
        for (unsigned int i = 0; i < glbSpkCntpoisson_pop[0]; i++) {
            const unsigned int ipre = glbSpkpoisson_pop[i];
            for (unsigned int ipost = 0; ipost < 100; ipost++) {
                const unsigned int synAddress = (ipre * 100) + ipost;
                
                inSyninput_e_pop[ipost] += ginput_e_pop[synAddress];
            }
        }
        
    }
    // synapse group syn_e_pop
     {
        // process presynaptic events: True Spikes
        for (unsigned int i = 0; i < glbSpkCntlif_e_pop[0]; i++) {
            const unsigned int ipre = glbSpklif_e_pop[i];
            const unsigned int npost = rowLengthsyn_e_pop[ipre];
            for (unsigned int j = 0; j < npost; j++) {
                const unsigned int synAddress = (ipre * 1) + j;
                const unsigned int ipost = indsyn_e_pop[synAddress];
                inSynsyn_e_pop[ipost] += gsyn_e_pop[synAddress];
            }
        }
        
    }
    // synapse group syn_i_pop
     {
        // process presynaptic events: True Spikes
        for (unsigned int i = 0; i < glbSpkCntlif_i_pop[0]; i++) {
            const unsigned int ipre = glbSpklif_i_pop[i];
            for (unsigned int ipost = 0; ipost < 100; ipost++) {
                const unsigned int synAddress = (ipre * 100) + ipost;
                inSynsyn_i_pop[ipost] += gsyn_i_pop[synAddress];
            }
        }
        
    }
    // synapse group input_e_pop
     {
        const unsigned int numSpikes = glbSpkCntlif_e_pop[0];
        for (unsigned int j = 0; j < numSpikes; j++) {
            const unsigned int spike = glbSpklif_e_pop[j];
            for (unsigned int i = 0; i < 784; i++) {
                
                const scalar dt = t - (1.00000000000000000e+00f + sTpoisson_pop[i]);
                if(dt > 0) {
                    const scalar newG = ginput_e_pop[((100 * i) + spike)] - (etainput_e_pop[((100 * i) + spike)] * (Xpreinput_e_pop[i] - (1.00000000000000006e-01f)) * powf(((1.00000000000000002e-02f) - ginput_e_pop[((100 * i) + spike)]),(1.00000000000000000e+00f)));
                    ginput_e_pop[((100 * i) + spike)] = (1.00000000000000002e-02f) <= newG ? (1.00000000000000002e-02f) : newG;
                }
            }
        }
        
    }
}
