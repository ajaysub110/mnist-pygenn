

#ifndef _mnist_neuronFnct_cc
#define _mnist_neuronFnct_cc

//-------------------------------------------------------------------------
/*! \file neuronFnct.cc

\brief File generated from GeNN for the model mnist containing the the equivalent of neuron kernel function for the CPU-only version.
*/
//-------------------------------------------------------------------------

// include the support codes provided by the user for neuron or synaptic models
#include "support_code.h"

void calcNeuronsCPU(float t) {
    // neuron group lif_e_pop
     {
        glbSpkCntlif_e_pop[0] = 0;
        
        for (int n = 0; n < 1; n++) {
            scalar lV = Vlif_e_pop[n];
            scalar lRefracTime = RefracTimelif_e_pop[n];
            float lsT = sTlif_e_pop[n];
            float Isyn = 0;
            
            Isyn += inSynsyn_i_pop[n] * ((1.00000000000000000e+02f) - lV);
            
            
            Isyn += inSyninput_e_pop[n] * ((1.00000000000000000e+03f) - lV);
            
            // test whether spike condition was fulfilled previously
            bool oldSpike= (lRefracTime <= 0.0f && lV >= (-5.20000000000000000e+01f));
            // calculate membrane potential
            
            if (lRefracTime <= 0.0f)
            {
                scalar alpha = (-6.50000000000000000e+01f) + Isyn;
                lV = (lV - alpha) * (9.90049833749168107e-01f);
            }
            else
            {
                lRefracTime -= DT;
            }
            
            // test for and register a true spike
            if ((lRefracTime <= 0.0f && lV >= (-5.20000000000000000e+01f)) && !(oldSpike)) {
                glbSpklif_e_pop[glbSpkCntlif_e_pop[0]++] = n;
                 {
                    // perform presynaptic update required for syn_e_pop
                    scalar lpreTrace = preTracesyn_e_pop[n];
                    
                    const scalar dt = t - (sTlif_e_pop[n]);
                    lpreTrace = lpreTrace * expf(-dt / (2.00000000000000000e+01f)) + 1.0f;
                    preTracesyn_e_pop[n] = lpreTrace;
                }
                 {
                    // perform postsynaptic update required for input_e_pop
                    scalar lpostTrace = postTraceinput_e_pop[n];
                    
                    const scalar dt = t - (sTlif_e_pop[n]);
                    lpostTrace = lpostTrace * expf(-dt / (2.00000000000000000e+01f)) + 1.0f;
                    postTraceinput_e_pop[n] = lpostTrace;
                }
                 {
                    // perform postsynaptic update required for syn_i_pop
                    scalar lpostTrace = postTracesyn_i_pop[n];
                    
                    const scalar dt = t - (sTlif_e_pop[n]);
                    lpostTrace = lpostTrace * expf(-dt / (2.00000000000000000e+01f)) + 1.0f;
                    postTracesyn_i_pop[n] = lpostTrace;
                }
                sTlif_e_pop[n] = t;
                // spike reset code
                
                lV = (-6.50000000000000000e+01f);
                lRefracTime = (5.00000000000000000e+00f);
                
            }
            Vlif_e_pop[n] = lV;
            RefracTimelif_e_pop[n] = lRefracTime;
            // the post-synaptic dynamics
            
            inSynsyn_i_pop[n] *= (6.06530659712633424e-01f);
            
            // the post-synaptic dynamics
            
            inSyninput_e_pop[n] *= (3.67879441171442334e-01f);
            
        }
    }
    
    // neuron group lif_i_pop
     {
        glbSpkCntlif_i_pop[0] = 0;
        
        for (int n = 0; n < 1; n++) {
            scalar lV = Vlif_i_pop[n];
            scalar lRefracTime = RefracTimelif_i_pop[n];
            float lsT = sTlif_i_pop[n];
            float Isyn = 0;
            
            Isyn += inSynsyn_e_pop[n] * ((1.00000000000000000e+03f) - lV);
            
            // test whether spike condition was fulfilled previously
            bool oldSpike= (lRefracTime <= 0.0f && lV >= (-4.00000000000000000e+01f));
            // calculate membrane potential
            
            if (lRefracTime <= 0.0f)
            {
                scalar alpha = (-6.00000000000000000e+01f) + Isyn;
                lV = (lV - alpha) * (9.04837418035959518e-01f);
            }
            else
            {
                lRefracTime -= DT;
            }
            
            // test for and register a true spike
            if ((lRefracTime <= 0.0f && lV >= (-4.00000000000000000e+01f)) && !(oldSpike)) {
                glbSpklif_i_pop[glbSpkCntlif_i_pop[0]++] = n;
                 {
                    // perform presynaptic update required for syn_i_pop
                    scalar lpreTrace = preTracesyn_i_pop[n];
                    
                    const scalar dt = t - (sTlif_i_pop[n]);
                    lpreTrace = lpreTrace * expf(-dt / (2.00000000000000000e+01f)) + 1.0f;
                    preTracesyn_i_pop[n] = lpreTrace;
                }
                 {
                    // perform postsynaptic update required for syn_e_pop
                    scalar lpostTrace = postTracesyn_e_pop[n];
                    
                    const scalar dt = t - (sTlif_i_pop[n]);
                    lpostTrace = lpostTrace * expf(-dt / (2.00000000000000000e+01f)) + 1.0f;
                    postTracesyn_e_pop[n] = lpostTrace;
                }
                sTlif_i_pop[n] = t;
                // spike reset code
                
                lV = (-4.50000000000000000e+01f);
                lRefracTime = (2.00000000000000000e+00f);
                
            }
            Vlif_i_pop[n] = lV;
            RefracTimelif_i_pop[n] = lRefracTime;
            // the post-synaptic dynamics
            
            inSynsyn_e_pop[n] *= (3.67879441171442334e-01f);
            
        }
    }
    
    // neuron group poisson_pop
     {
        glbSpkCntpoisson_pop[spkQuePtrpoisson_pop] = 0;
        const unsigned int readDelayOffset = (((spkQuePtrpoisson_pop + 150) % 151) * 1);
        const unsigned int writeDelayOffset = (spkQuePtrpoisson_pop * 1);
        
        for (int n = 0; n < 1; n++) {
            scalar ltimeStepToSpike = timeStepToSpikepoisson_pop[n];
            float lsT = sTpoisson_pop[readDelayOffset + n];
            // test whether spike condition was fulfilled previously
            bool oldSpike= (ltimeStepToSpike <= 0.0f);
            // calculate membrane potential
            if(ltimeStepToSpike <= 0.0f) {
                ltimeStepToSpike += (6.66666666666666714e+01f) * standardExponentialDistribution(rng);
            }
            ltimeStepToSpike -= 1.0f;
            
            // test for and register a true spike
            if ((ltimeStepToSpike <= 0.0f) && !(oldSpike)) {
                glbSpkpoisson_pop[writeDelayOffset + glbSpkCntpoisson_pop[spkQuePtrpoisson_pop]++] = n;
                 {
                    // perform presynaptic update required for input_e_pop
                    scalar lpreTrace = preTraceinput_e_pop[readDelayOffset + n];
                    
                    const scalar dt = t - (sTpoisson_pop[readDelayOffset + n]);
                    lpreTrace = lpreTrace * expf(-dt / (2.00000000000000000e+01f)) + 1.0f;
                    preTraceinput_e_pop[writeDelayOffset + n] = lpreTrace;
                }
                sTpoisson_pop[writeDelayOffset + n] = t;
            }
            else {
                sTpoisson_pop[writeDelayOffset + n] = lsT;
                preTraceinput_e_pop[writeDelayOffset + n] = preTraceinput_e_pop[readDelayOffset + n];
            }
            timeStepToSpikepoisson_pop[n] = ltimeStepToSpike;
        }
    }
    
}
#endif
