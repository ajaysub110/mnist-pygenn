

#ifndef _mnist_synapseFnct_cc
#define _mnist_synapseFnct_cc

//-------------------------------------------------------------------------
/*! \file synapseFnct.cc

\brief File generated from GeNN for the model mnist containing the equivalent of the synapse kernel and learning kernel functions for the CPU only version.
*/
//-------------------------------------------------------------------------

void calcSynapsesCPU(float t) {
    
    // synapse group input_e_pop
     {
        const unsigned int preReadDelaySlot = ((spkQuePtrpoisson_pop + 1) % 151);
        const unsigned int preReadDelayOffset = preReadDelaySlot * 1;
        // process presynaptic events: True Spikes
        for (unsigned int i = 0; i < glbSpkCntpoisson_pop[preReadDelaySlot]; i++) {
            const unsigned int ipre = glbSpkpoisson_pop[preReadDelayOffset + i];
            for (unsigned int ipost = 0; ipost < 1; ipost++) {
                float addtoinSyn;
                
                inSyninput_e_pop[ipost] += ginput_e_pop[ipre * 1 + ipost];
                const scalar dt = t - (1.00000000000000000e+00f + sTlif_e_pop[ipost]);
                if(dt > 0) {
                    const scalar timing = expf(-dt / (2.00000000000000000e+01f));
                    const scalar newWeight = ginput_e_pop[ipre * 1 + ipost] - ((1.05000000000000004e-04f) * postTraceinput_e_pop[ipost] * timing);
                    ginput_e_pop[ipre * 1 + ipost] = min((1.00000000000000002e-02f), max((0.00000000000000000e+00f), newWeight));
                }
                
            }
        }
    }
    
    // synapse group syn_e_pop
     {
        // process presynaptic events: True Spikes
        for (unsigned int i = 0; i < glbSpkCntlif_e_pop[0]; i++) {
            const unsigned int ipre = glbSpklif_e_pop[i];
            for (unsigned int ipost = 0; ipost < 1; ipost++) {
                float addtoinSyn;
                
                inSynsyn_e_pop[ipost] += gsyn_e_pop[ipre * 1 + ipost];
                const scalar dt = t - (1.00000000000000000e+00f + sTlif_i_pop[ipost]);
                if(dt > 0) {
                    const scalar timing = expf(-dt / (2.00000000000000000e+01f));
                    const scalar newWeight = gsyn_e_pop[ipre * 1 + ipost] - ((1.05000000000000004e-04f) * postTracesyn_e_pop[ipost] * timing);
                    gsyn_e_pop[ipre * 1 + ipost] = min((1.00000000000000002e-02f), max((0.00000000000000000e+00f), newWeight));
                }
                
            }
        }
    }
    
    // synapse group syn_i_pop
     {
        // process presynaptic events: True Spikes
        for (unsigned int i = 0; i < glbSpkCntlif_i_pop[0]; i++) {
            const unsigned int ipre = glbSpklif_i_pop[i];
            for (unsigned int ipost = 0; ipost < 1; ipost++) {
                float addtoinSyn;
                
                inSynsyn_i_pop[ipost] += gsyn_i_pop[ipre * 1 + ipost];
                const scalar dt = t - (1.00000000000000000e+00f + sTlif_e_pop[ipost]);
                if(dt > 0) {
                    const scalar timing = expf(-dt / (2.00000000000000000e+01f));
                    const scalar newWeight = gsyn_i_pop[ipre * 1 + ipost] - ((1.05000000000000004e-04f) * postTracesyn_i_pop[ipost] * timing);
                    gsyn_i_pop[ipre * 1 + ipost] = min((1.00000000000000002e-02f), max((0.00000000000000000e+00f), newWeight));
                }
                
            }
        }
    }
    
}

void learnSynapsesPostHost(float t) {
    unsigned int ipost;
    unsigned int ipre;
    unsigned int lSpk;
    
    // synapse group input_e_pop
     {
        const unsigned int preReadDelayOffset = ((spkQuePtrpoisson_pop + 1) % 151) * 1;
        for (ipost = 0; ipost < glbSpkCntlif_e_pop[0]; ipost++) {
            lSpk = glbSpklif_e_pop[ipost];
            for (ipre = 0; ipre < 1; ipre++) {
                
                const scalar dt = t - (1.51000000000000000e+02f + sTpoisson_pop[preReadDelayOffset + ipre]);
                if(dt > 0) {
                    const scalar timing = expf(-dt / (2.00000000000000000e+01f));
                    const scalar newWeight = ginput_e_pop[lSpk + 1 * ipre] + ((1.00000000000000005e-04f) * preTraceinput_e_pop[preReadDelayOffset + ipre] * timing);
                    ginput_e_pop[lSpk + 1 * ipre] = min((1.00000000000000002e-02f), max((0.00000000000000000e+00f), newWeight));
                }
                
            }
        }
    }
    // synapse group syn_e_pop
     {
        for (ipost = 0; ipost < glbSpkCntlif_i_pop[0]; ipost++) {
            lSpk = glbSpklif_i_pop[ipost];
            for (ipre = 0; ipre < 1; ipre++) {
                
                const scalar dt = t - (1.00000000000000000e+00f + sTlif_e_pop[ipre]);
                if(dt > 0) {
                    const scalar timing = expf(-dt / (2.00000000000000000e+01f));
                    const scalar newWeight = gsyn_e_pop[lSpk + 1 * ipre] + ((1.00000000000000005e-04f) * preTracesyn_e_pop[ipre] * timing);
                    gsyn_e_pop[lSpk + 1 * ipre] = min((1.00000000000000002e-02f), max((0.00000000000000000e+00f), newWeight));
                }
                
            }
        }
    }
    // synapse group syn_i_pop
     {
        for (ipost = 0; ipost < glbSpkCntlif_e_pop[0]; ipost++) {
            lSpk = glbSpklif_e_pop[ipost];
            for (ipre = 0; ipre < 1; ipre++) {
                
                const scalar dt = t - (1.00000000000000000e+00f + sTlif_i_pop[ipre]);
                if(dt > 0) {
                    const scalar timing = expf(-dt / (2.00000000000000000e+01f));
                    const scalar newWeight = gsyn_i_pop[lSpk + 1 * ipre] + ((1.00000000000000005e-04f) * preTracesyn_i_pop[ipre] * timing);
                    gsyn_i_pop[lSpk + 1 * ipre] = min((1.00000000000000002e-02f), max((0.00000000000000000e+00f), newWeight));
                }
                
            }
        }
    }
}

#endif
