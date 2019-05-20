

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
        const unsigned int preReadDelayOffset = preReadDelaySlot * 784;
        // process presynaptic events: True Spikes
        for (unsigned int i = 0; i < glbSpkCntpoisson_pop[preReadDelaySlot]; i++) {
            const unsigned int ipre = glbSpkpoisson_pop[preReadDelayOffset + i];
            for (unsigned int ipost = 0; ipost < 100; ipost++) {
                float addtoinSyn;
                
                inSyninput_e_pop[ipost] += ginput_e_pop[ipre * 100 + ipost];
                const scalar dt = t - (1.00000000000000000e+00f + sTlif_e_pop[ipost]);
                if(dt > 0) {
                    const scalar expXpre = expf(-dt / (2.00000000000000000e+01f));
                    Xpreinput_e_pop[preReadDelayOffset + ipre] *= expXpre;
                }
                
            }
        }
    }
    
    // synapse group syn_e_pop
     {
        // process presynaptic events: True Spikes
        for (unsigned int i = 0; i < glbSpkCntlif_e_pop[0]; i++) {
            const unsigned int ipre = glbSpklif_e_pop[i];
            for (unsigned int ipost = 0; ipost < 100; ipost++) {
                float addtoinSyn;
                
                inSynsyn_e_pop[ipost] += gsyn_e_pop[ipre * 100 + ipost];
                const scalar dt = t - (1.00000000000000000e+00f + sTlif_i_pop[ipost]);
                if(dt > 0) {
                    const scalar expXpre = expf(-dt / (2.00000000000000000e+01f));
                    Xpresyn_e_pop[ipre] *= expXpre;
                }
                
            }
        }
    }
    
    // synapse group syn_i_pop
     {
        // process presynaptic events: True Spikes
        for (unsigned int i = 0; i < glbSpkCntlif_i_pop[0]; i++) {
            const unsigned int ipre = glbSpklif_i_pop[i];
            for (unsigned int ipost = 0; ipost < 100; ipost++) {
                float addtoinSyn;
                
                inSynsyn_i_pop[ipost] += gsyn_i_pop[ipre * 100 + ipost];
                const scalar dt = t - (1.00000000000000000e+00f + sTlif_e_pop[ipost]);
                if(dt > 0) {
                    const scalar expXpre = expf(-dt / (2.00000000000000000e+01f));
                    Xpresyn_i_pop[ipre] *= expXpre;
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
        const unsigned int preReadDelayOffset = ((spkQuePtrpoisson_pop + 1) % 151) * 784;
        for (ipost = 0; ipost < glbSpkCntlif_e_pop[0]; ipost++) {
            lSpk = glbSpklif_e_pop[ipost];
            for (ipre = 0; ipre < 784; ipre++) {
                
                const scalar dt = t - (1.51000000000000000e+02f + sTpoisson_pop[preReadDelayOffset + ipre]);
                if(dt > 0) {
                    const scalar newG = ginput_e_pop[lSpk + 100 * ipre] - (etainput_e_pop[lSpk + 100 * ipre] * (Xpreinput_e_pop[preReadDelayOffset + ipre] - (1.00000000000000006e-01f)) * powf(((1.00000000000000002e-02f) - ginput_e_pop[lSpk + 100 * ipre]),(1.00000000000000000e+00f)));
                    ginput_e_pop[lSpk + 100 * ipre] = min((1.00000000000000002e-02f), newG);
                }
                
            }
        }
    }
    // synapse group syn_e_pop
     {
        for (ipost = 0; ipost < glbSpkCntlif_i_pop[0]; ipost++) {
            lSpk = glbSpklif_i_pop[ipost];
            for (ipre = 0; ipre < 100; ipre++) {
                
                const scalar dt = t - (1.00000000000000000e+00f + sTlif_e_pop[ipre]);
                if(dt > 0) {
                    const scalar newG = gsyn_e_pop[lSpk + 100 * ipre] - (etasyn_e_pop[lSpk + 100 * ipre] * (Xpresyn_e_pop[ipre] - (1.00000000000000006e-01f)) * powf(((1.00000000000000002e-02f) - gsyn_e_pop[lSpk + 100 * ipre]),(1.00000000000000000e+00f)));
                    gsyn_e_pop[lSpk + 100 * ipre] = min((1.00000000000000002e-02f), newG);
                }
                
            }
        }
    }
    // synapse group syn_i_pop
     {
        for (ipost = 0; ipost < glbSpkCntlif_e_pop[0]; ipost++) {
            lSpk = glbSpklif_e_pop[ipost];
            for (ipre = 0; ipre < 100; ipre++) {
                
                const scalar dt = t - (1.00000000000000000e+00f + sTlif_i_pop[ipre]);
                if(dt > 0) {
                    const scalar newG = gsyn_i_pop[lSpk + 100 * ipre] - (etasyn_i_pop[lSpk + 100 * ipre] * (Xpresyn_i_pop[ipre] - (1.00000000000000006e-01f)) * powf(((1.00000000000000002e-02f) - gsyn_i_pop[lSpk + 100 * ipre]),(1.00000000000000000e+00f)));
                    gsyn_i_pop[lSpk + 100 * ipre] = min((1.00000000000000002e-02f), newG);
                }
                
            }
        }
    }
}

#endif
