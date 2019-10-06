#include "definitionsInternal.h"
#include "supportCode.h"

void updateSynapses(float t) {
    // synapse group syn_ei_pop
     {
        // process presynaptic events: True Spikes
        for (unsigned int i = 0; i < glbSpkCntlif_e_pop[0]; i++) {
            const unsigned int ipre = glbSpklif_e_pop[i];
            const unsigned int npost = rowLengthsyn_ei_pop[ipre];
            for (unsigned int j = 0; j < npost; j++) {
                const unsigned int synAddress = (ipre * 1) + j;
                const unsigned int ipost = indsyn_ei_pop[synAddress];
                inSynsyn_ei_pop[ipost] += gsyn_ei_pop[synAddress];
            }
        }
        
    }
    // synapse group syn_ie_pop
     {
        // process presynaptic events: True Spikes
        for (unsigned int i = 0; i < glbSpkCntlif_i_pop[0]; i++) {
            const unsigned int ipre = glbSpklif_i_pop[i];
            for (unsigned int ipost = 0; ipost < 100; ipost++) {
                const unsigned int synAddress = (ipre * 100) + ipost;
                inSynsyn_ie_pop[ipost] += gsyn_ie_pop[synAddress];
            }
        }
        
    }
    // synapse group syn_pe_pop
     {
        // process presynaptic events: True Spikes
        for (unsigned int i = 0; i < glbSpkCntpoisson_pop[0]; i++) {
            const unsigned int ipre = glbSpkpoisson_pop[i];
            for (unsigned int ipost = 0; ipost < 100; ipost++) {
                const unsigned int synAddress = (ipre * 100) + ipost;
                
                inSynsyn_pe_pop[ipost] += gsyn_pe_pop[synAddress];
            }
        }
        
    }
    // synapse group syn_pe_pop
     {
        const unsigned int numSpikes = glbSpkCntlif_e_pop[0];
        for (unsigned int j = 0; j < numSpikes; j++) {
            const unsigned int spike = glbSpklif_e_pop[j];
            for (unsigned int i = 0; i < 784; i++) {
                
                const scalar dt = t - (1.00000000000000000e+00f + sTpoisson_pop[i]);
                if(dt > 0) {
                    const scalar expXpre = Xpresyn_pe_pop[i] * expf(-dt / (2.00000000000000000e+01f));
                    const scalar newG = gsyn_pe_pop[((100 * i) + spike)] - ((etasyn_pe_pop[((100 * i) + spike)] * (expXpre - (2.00000000000000004e-03f)) * powf(((1.00000000000000000e+00f) - gsyn_pe_pop[((100 * i) + spike)]),(5.00000000000000000e-01f))));
                    gsyn_pe_pop[((100 * i) + spike)] = (1.00000000000000000e+00f) <= newG ? (1.00000000000000000e+00f) : newG;
                }
            }
        }
        
    }
}
