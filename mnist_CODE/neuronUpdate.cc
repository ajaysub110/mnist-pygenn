#include "definitionsInternal.h"
#include "supportCode.h"

void updateNeurons(float t) {
    // neuron group lif_e_pop
     {
        glbSpkCntlif_e_pop[0] = 0;
        
        for(unsigned int i = 0; i < 100; i++) {
            scalar lV = Vlif_e_pop[i];
            scalar lRefracTime = RefracTimelif_e_pop[i];
            scalar ltheta = thetalif_e_pop[i];
            unsigned int lSpikeNumber = SpikeNumberlif_e_pop[i];
            float lsT = sTlif_e_pop[i];
            
            float Isyn = 0;
            // pull inSyn values in a coalesced access
            float linSynsyn_ie_pop = inSynsyn_ie_pop[i];
            Isyn += linSynsyn_ie_pop * ((1.00000000000000000e+03f) - lV);
            // pull inSyn values in a coalesced access
            float linSynsyn_pe_pop = inSynsyn_pe_pop[i];
            Isyn += linSynsyn_pe_pop * ((1.00000000000000000e+03f) - lV);
            // test whether spike condition was fulfilled previously
            const bool oldSpike= (lRefracTime <= 0.0f && lV >= (-5.20000000000000000e+01f) + ltheta);
            // calculate membrane potential
            
            if (lRefracTime <= 0.0f)
            {
                scalar alpha = (-6.50000000000000000e+01f) + Isyn;
                lV = (lV - alpha) * (9.90049833749168107e-01f);
            }
            else
            {
                lRefracTime -= DT;
                ltheta = ltheta * (9.99999900000005049e-01f);
            }
            
            // test for and register a true spike
            if ((lRefracTime <= 0.0f && lV >= (-5.20000000000000000e+01f) + ltheta) && !(oldSpike)) {
                glbSpklif_e_pop[glbSpkCntlif_e_pop[0]++] = i;
                sTlif_e_pop[i] = t;
                // spike reset code
                
                lV = (-6.50000000000000000e+01f);
                lRefracTime = (5.00000000000000000e+00f);
                lSpikeNumber += 1;
                ltheta += 1.0f;
                
            }
            Vlif_e_pop[i] = lV;
            RefracTimelif_e_pop[i] = lRefracTime;
            thetalif_e_pop[i] = ltheta;
            SpikeNumberlif_e_pop[i] = lSpikeNumber;
            // the post-synaptic dynamics
            linSynsyn_ie_pop*=(3.67879441171442334e-01f);
            inSynsyn_ie_pop[i] = linSynsyn_ie_pop;
            // the post-synaptic dynamics
            linSynsyn_pe_pop*=(3.67879441171442334e-01f);
            inSynsyn_pe_pop[i] = linSynsyn_pe_pop;
        }
    }
    // neuron group lif_i_pop
     {
        glbSpkCntlif_i_pop[0] = 0;
        
        for(unsigned int i = 0; i < 100; i++) {
            scalar lV = Vlif_i_pop[i];
            scalar lRefracTime = RefracTimelif_i_pop[i];
            unsigned int lSpikeNumber = SpikeNumberlif_i_pop[i];
            
            float Isyn = 0;
            // pull inSyn values in a coalesced access
            float linSynsyn_ei_pop = inSynsyn_ei_pop[i];
            Isyn += linSynsyn_ei_pop * ((1.00000000000000000e+02f) - lV);
            // test whether spike condition was fulfilled previously
            const bool oldSpike= (lRefracTime <= 0.0f && lV >= (-4.00000000000000000e+01f));
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
                glbSpklif_i_pop[glbSpkCntlif_i_pop[0]++] = i;
                // spike reset code
                
                lV = (-4.50000000000000000e+01f);
                lRefracTime = (2.00000000000000000e+00f);
                lSpikeNumber += 1;
                
            }
            Vlif_i_pop[i] = lV;
            RefracTimelif_i_pop[i] = lRefracTime;
            SpikeNumberlif_i_pop[i] = lSpikeNumber;
            // the post-synaptic dynamics
            linSynsyn_ei_pop*=(6.06530659712633424e-01f);
            inSynsyn_ei_pop[i] = linSynsyn_ei_pop;
        }
    }
    // neuron group poisson_pop
     {
        glbSpkCntpoisson_pop[0] = 0;
        
        for(unsigned int i = 0; i < 784; i++) {
            scalar lrate = ratepoisson_pop[i];
            scalar ltimeStepToSpike = timeStepToSpikepoisson_pop[i];
            float lsT = sTpoisson_pop[i];
            
            // test whether spike condition was fulfilled previously
            const bool oldSpike= (ltimeStepToSpike <= 0.0f);
            // calculate membrane potential
            
            const scalar isi = 1000.0f / lrate;
            if (ltimeStepToSpike <= 0.0f) {
                ltimeStepToSpike += isi * standardExponentialDistribution(rng);
            }
            ltimeStepToSpike -= 1.0f;
            
            // test for and register a true spike
            if ((ltimeStepToSpike <= 0.0f) && !(oldSpike)) {
                glbSpkpoisson_pop[glbSpkCntpoisson_pop[0]++] = i;
                sTpoisson_pop[i] = t;
                 {
                    // perform presynaptic update required for syn_pe_pop
                    scalar lXpre = Xpresyn_pe_pop[i];
                    
                    const scalar dt = t - (sTpoisson_pop[i]);
                    if(dt > 0) {
                        const scalar expXpre = expf(-dt / (2.00000000000000000e+01f));
                        lXpre = expXpre + 1.0f;
                    }
                    Xpresyn_pe_pop[i] = lXpre;
                }
            }
            ratepoisson_pop[i] = lrate;
            timeStepToSpikepoisson_pop[i] = ltimeStepToSpike;
        }
    }
}
