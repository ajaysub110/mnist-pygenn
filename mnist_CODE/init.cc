

//-------------------------------------------------------------------------
/*! \brief Function to (re)set all model variables to their compile-time, homogeneous initial values.
 Note that this typically includes synaptic weight values. The function (re)sets host side variables and copies them to the GPU device.
*/
//-------------------------------------------------------------------------

void initialize() {
    #if defined(__GNUG__) && !defined(__clang__) && defined(__x86_64__) && __GLIBC__ == 2 && (__GLIBC_MINOR__ == 23 || __GLIBC_MINOR__ == 24)
    if(std::getenv("LD_BIND_NOW") == NULL) {
        fprintf(stderr, "Warning: a bug has been found in glibc 2.23 or glibc 2.24 (https://bugs.launchpad.net/ubuntu/+source/glibc/+bug/1663280) "
                        "which results in poor CPU maths performance. We recommend setting the environment variable LD_BIND_NOW=1 to work around this issue.\n");
    }
    #endif
    srand((unsigned int) time(NULL));
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
    
    // remote neuron spike variables
    // neuron variables
    glbSpkCntlif_e_pop[0] = 0;
     {
        for (int i = 0; i < 1; i++) {
            glbSpklif_e_pop[i] = 0;
        }
    }
     {
        for (int i = 0; i < 1; i++) {
            sTlif_e_pop[i] = -TIME_MAX;
        }
    }
     {
        for (int i = 0; i < 1; i++) {
            Vlif_e_pop[i] = (-6.50000000000000000e+01f);
        }
    }
     {
        for (int i = 0; i < 1; i++) {
            RefracTimelif_e_pop[i] = (0.00000000000000000e+00f);
        }
    }
    // current source variables
     {
        for (int i = 0; i < 1; i++) {
            inSynsyn_i_pop[i] = 0.000000f;
        }
    }
     {
        for (int i = 0; i < 1; i++) {
            inSyninput_e_pop[i] = 0.000000f;
        }
    }
    glbSpkCntlif_i_pop[0] = 0;
     {
        for (int i = 0; i < 1; i++) {
            glbSpklif_i_pop[i] = 0;
        }
    }
     {
        for (int i = 0; i < 1; i++) {
            sTlif_i_pop[i] = -TIME_MAX;
        }
    }
     {
        for (int i = 0; i < 1; i++) {
            Vlif_i_pop[i] = (-4.50000000000000000e+01f);
        }
    }
     {
        for (int i = 0; i < 1; i++) {
            RefracTimelif_i_pop[i] = (0.00000000000000000e+00f);
        }
    }
    // current source variables
     {
        for (int i = 0; i < 1; i++) {
            inSynsyn_e_pop[i] = 0.000000f;
        }
    }
    spkQuePtrpoisson_pop = 0;
     {
        for (int i = 0; i < 151; i++) {
            glbSpkCntpoisson_pop[i] = 0;
        }
    }
     {
        for (int i = 0; i < 151; i++) {
            glbSpkpoisson_pop[i] = 0;
        }
    }
     {
        for (int i = 0; i < 151; i++) {
            sTpoisson_pop[i] = -TIME_MAX;
        }
    }
     {
        for (int i = 0; i < 1; i++) {
            timeStepToSpikepoisson_pop[i] = (1.50000000000000000e+02f);
        }
    }
    // current source variables
    
    // synapse variables
     {
        for (int i = 0; i < 1; i++) {
            scalar initVal;
            initVal = (0.00000000000000000e+00f);
            for (int d = 0; d < 151; d++) {
                preTraceinput_e_pop[(d * 1) + i] = initVal;
            }
        }
    }
     {
        for (int i = 0; i < 1; i++) {
            postTraceinput_e_pop[i] = (0.00000000000000000e+00f);
        }
    }
     {
        for (int i = 0; i < 1; i++) {
            for (int j = 0; j < 1; j++) {
                const scalar scale = (1.00000000000000002e-02f) - (0.00000000000000000e+00f);
                ginput_e_pop[(i * 1) + j] = (0.00000000000000000e+00f) + (standardUniformDistribution(rng) * scale);
            }
        }
    }
     {
        for (int i = 0; i < 1; i++) {
            preTracesyn_e_pop[i] = (0.00000000000000000e+00f);
        }
    }
     {
        for (int i = 0; i < 1; i++) {
            postTracesyn_e_pop[i] = (0.00000000000000000e+00f);
        }
    }
     {
        for (int i = 0; i < 1; i++) {
            for (int j = 0; j < 1; j++) {
                const scalar scale = (1.00000000000000002e-02f) - (0.00000000000000000e+00f);
                gsyn_e_pop[(i * 1) + j] = (0.00000000000000000e+00f) + (standardUniformDistribution(rng) * scale);
            }
        }
    }
     {
        for (int i = 0; i < 1; i++) {
            preTracesyn_i_pop[i] = (0.00000000000000000e+00f);
        }
    }
     {
        for (int i = 0; i < 1; i++) {
            postTracesyn_i_pop[i] = (0.00000000000000000e+00f);
        }
    }
     {
        for (int i = 0; i < 1; i++) {
            for (int j = 0; j < 1; j++) {
                const scalar scale = (1.00000000000000002e-02f) - (0.00000000000000000e+00f);
                gsyn_i_pop[(i * 1) + j] = (0.00000000000000000e+00f) + (standardUniformDistribution(rng) * scale);
            }
        }
    }
    
    
}

void initmnist() {
    
    
}

