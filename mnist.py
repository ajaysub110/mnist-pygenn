import numpy as np 
import matplotlib.pyplot as plt 

import time
import pickle
import os 
from struct import unpack
import random

from pygenn import genn_model, genn_wrapper

# Data path
root_path = '/home/ajays/Desktop/mnist-pygenn'
mnist_data_path = '/home/ajays/datasets/mnist/'
if not os.path.exists(os.path.join(root_path,'ckpt')):
    os.makedirs(os.path.join(root_path,'ckpt'))    

# ********************************************************************************
#                      Methods
# ********************************************************************************

# Load data into dictionary
def get_labeled_data(filename, bTrain = True):
    """Read input-vector (image) and target class (label, 0-9) and return
       it as list of tuples.
    """
    if os.path.isfile('%s.pickle' % filename):
        with open('%s.pickle' % filename, 'rb') as handle:
            data = pickle.load(handle)
    else:
        # Open the images with gzip in read binary mode
        if bTrain:
            images = open(mnist_data_path + 'train-images-idx3-ubyte','rb')
            labels = open(mnist_data_path + 'train-labels-idx1-ubyte','rb')
        else:
            images = open(mnist_data_path + 't10k-images-idx3-ubyte','rb')
            labels = open(mnist_data_path + 't10k-labels-idx1-ubyte','rb')
        # Get metadata for images
        images.read(4)  # skip the magic_number
        number_of_images = unpack('>I', images.read(4))[0]
        rows = unpack('>I', images.read(4))[0]
        cols = unpack('>I', images.read(4))[0]
        # Get metadata for labels
        labels.read(4)  # skip the magic_number
        N = unpack('>I', labels.read(4))[0]
        
        if number_of_images != N:
            raise Exception('number of labels did not match the number of images')
        # Get the data
        x = np.zeros((N, rows, cols), dtype=np.uint8)  # Initialize numpy array
        y = np.zeros((N, 1), dtype=np.uint8)  # Initialize numpy array
        for i in range(N):
            if i % 1000 == 0:
                print("i: %i" % i)
            x[i] = [[unpack('>B', images.read(1))[0] for unused_col in range(cols)]  for unused_row in range(rows) ]
            y[i] = unpack('>B', labels.read(1))[0]
                
        data = {'x': x, 'y': y, 'rows': rows, 'cols': cols}
        with open('%s.pickle' % filename, 'wb') as handle:
            pickle.dump(data, handle, protocol=pickle.HIGHEST_PROTOCOL)
    return data

def accuracy(predictions, y_list):
    return np.sum(np.array(predictions) == np.array(y_list)) / float(len(y_list)) * 100

# ********************************************************************************
#                      Model Definitions
# ********************************************************************************

# LIF neuron model
# excitatory neurons
lif_e_model = genn_model.create_custom_neuron_class(
    "lif_e_model",
    param_names=["Tau","Erest","Vreset","Vthres","RefracPeriod","tauTheta"],
    var_name_types=[("V","scalar"),("RefracTime","scalar"),("theta","scalar"),("SpikeNumber","unsigned int")],
    sim_code="""
    if ($(RefracTime) <= 0.0)
    {
        scalar alpha = $(Erest) + $(Isyn);
        $(V) = ($(V) - alpha) * $(ExpTC);
    }
    else
    {
        $(RefracTime) -= DT;
        $(theta) = $(theta) * $(ExpTtheta);
    }
    """,
    reset_code="""
    $(V) = $(Vreset);
    $(RefracTime) = $(RefracPeriod);
    $(SpikeNumber) += 1;
    $(theta) += 1.0;
    """,
    threshold_condition_code="$(RefracTime) <= 0.0 && $(V) >= $(Vthres) + $(theta)",
    derived_params=[
        ("ExpTC", genn_model.create_dpf_class(lambda pars, dt: np.exp(-dt / pars[0]))()),
        ("ExpTtheta", genn_model.create_dpf_class(lambda pars, dt: np.exp(-dt / pars[5]))())
    ]
)

# inhibitory neurons
lif_i_model = genn_model.create_custom_neuron_class(
    "lif_i_model",
    param_names=["Tau","Erest","Vreset","Vthres","RefracPeriod"],
    var_name_types=[("V","scalar"),("RefracTime","scalar"),("SpikeNumber","unsigned int")],
    sim_code="""
    if ($(RefracTime) <= 0.0)
    {
        scalar alpha = $(Erest) + $(Isyn);
        $(V) = ($(V) - alpha) * $(ExpTC);
    }
    else
    {
        $(RefracTime) -= DT;
    }
    """,
    reset_code="""
    $(V) = $(Vreset);
    $(RefracTime) = $(RefracPeriod);
    $(SpikeNumber) += 1;
    """,
    threshold_condition_code="$(RefracTime) <= 0.0 && $(V) >= $(Vthres)",
    derived_params=[
        ("ExpTC", genn_model.create_dpf_class(lambda pars, dt: np.exp(-dt / pars[0]))())
    ]
)

# STDP
stdp_model = genn_model.create_custom_weight_update_class(
    "stdp_model",
    param_names=["tauMinus", "gMax", "Xtar", "mu"],
    var_name_types=[("g", "scalar"), ("eta", "scalar")],
    pre_var_name_types=[("Xpre", "scalar")],

    sim_code=
        """
        $(addToInSyn, $(g));
        """,

    learn_post_code=
        """
        const scalar dt = $(t) - $(sT_pre);
        if(dt > 0) {
            const scalar expXpre = $(Xpre) * exp(-dt / $(tauMinus));
            const scalar newG = $(g) - (($(eta) * (expXpre - $(Xtar)) * pow(($(gMax) - $(g)),$(mu))));
            $(g) = $(gMax) <= newG ? $(gMax) : newG;
        }
        """,

    pre_spike_code=
        """
        const scalar dt = $(t) - $(sT_pre);
        if(dt > 0) {
            const scalar expXpre = exp(-dt / $(tauMinus));
            $(Xpre) = expXpre + 1.0;
        }
        """,

    is_pre_spike_time_required=True,
    is_post_spike_time_required=True
)

poisson_model = genn_model.create_custom_neuron_class(
    'poisson_model',
    var_name_types={('rate','scalar'),('timeStepToSpike','scalar')},
    sim_code="""
    const scalar isi = 1000.0 / $(rate);
    if ($(timeStepToSpike) <= 0.0f) {
        $(timeStepToSpike) += isi * $(gennrand_exponential);
    }
    $(timeStepToSpike) -= 1.0;
    """,
    threshold_condition_code="$(timeStepToSpike) <= 0.0"
)

lateral_inhibition = genn_model.create_custom_init_var_snippet_class(
    "lateral_inhibition",
    param_names=["weight"],
    var_init_code="$(value)=($(id_pre)==$(id_post)) ? 0.0 : $(weight);"
)

# ********************************************************************************
#                      Data
# ********************************************************************************
start = time.time()
training = get_labeled_data('training')
end = time.time()
print('time needed to load training set:', end - start)
 
start = time.time()
testing = get_labeled_data('testing',bTrain = False)
end = time.time()
print('time needed to load test set:', end - start)

# ********************************************************************************
#                      Parameters and Hyperparameters
# ********************************************************************************

# Hyperparameters
# Global 
timestep = 1.0

# Architecture
num_epochs = 3
num_examples = 100
n_input = 784
n_e = 100
n_i = n_e
single_example_time = 350
resting_time = 150
runtime = num_examples * (single_example_time + resting_time)

# Neuron
tau_e = 100
tau_i = 10
e_rest_e = -65
e_rest_i = -60
v_reset_e = -65
v_reset_i = -45
v_thres_e = -52
v_thres_i = -40
refrac_period_e = 5.0
refrac_period_i = 2.0
e_exc = 1000
e_inh = 100
tau_theta_e = 1e7

# Synapse
tau_ge = 1
tau_gi = 2

# STDP
g_max = 1.0
x_tar = 0.002
eta = 0.1
mu = 0.5

# Parameters and initial values
lif_e_params = {
    "Tau":tau_e, 
    "Erest":e_rest_e,
    "Vreset":v_reset_e,
    "Vthres":v_thres_e,
    "RefracPeriod":refrac_period_e,
    "tauTheta":tau_theta_e
}
lif_i_params = {
    "Tau":tau_i, 
    "Erest":e_rest_i,
    "Vreset":v_reset_i,
    "Vthres":v_thres_i,
    "RefracPeriod":refrac_period_i
}

lif_e_init = {"V": genn_model.init_var("Uniform",{"min":v_reset_e,"max":v_thres_e}),
     "RefracTime":0.0, "SpikeNumber":0, "theta":0.0}
lif_i_init = {"V": genn_model.init_var("Uniform",{"min":v_reset_i,"max":v_thres_i}),
     "RefracTime":0.0, "SpikeNumber":0}

stdp_init = {"g":genn_model.init_var("Uniform",{"min":0.0, "max":g_max}), "eta":eta}
stdp_params = {"tauMinus": 20.0,"gMax": g_max,"Xtar":x_tar,"mu":mu}
stdp_pre_init = {"Xpre": 0.0}

# ********************************************************************************
#                      Model Instances
# ********************************************************************************

model = genn_model.GeNNModel("float","mnist")

# Neuron populations
poisson_pop = model.add_neuron_population("poisson_pop",n_input,poisson_model,{},{'rate':100.0,'timeStepToSpike':0.0})

lif_e_pop = model.add_neuron_population("lif_e_pop",n_e,lif_e_model,lif_e_params,lif_e_init)

lif_i_pop = model.add_neuron_population("lif_i_pop",n_i,lif_i_model,lif_i_params,lif_i_init)

syn_pe_pop = model.add_synapse_population("syn_pe_pop","DENSE_INDIVIDUALG",genn_wrapper.NO_DELAY,
    poisson_pop,lif_e_pop,
    stdp_model,stdp_params,stdp_init,stdp_pre_init,{},
    "ExpCond",{"tau":tau_ge,"E":e_exc},{})

syn_ei_pop = model.add_synapse_population("syn_ei_pop","SPARSE_INDIVIDUALG",genn_wrapper.NO_DELAY,
    lif_e_pop,lif_i_pop,
    "StaticPulse",{},{"g":genn_model.init_var("Uniform",{"min":0.0, "max":g_max})},{},{},
    "ExpCond",{"tau":tau_gi,"E":e_inh},{},genn_model.init_connectivity("OneToOne",{}))

syn_ie_pop = model.add_synapse_population("syn_ie_pop","DENSE_INDIVIDUALG",genn_wrapper.NO_DELAY,
    lif_i_pop,lif_e_pop,
    "StaticPulse",{},{"g":genn_model.init_var(lateral_inhibition,{"weight":0.1})},{},{},
    "ExpCond",{"tau":tau_ge,"E":e_exc},{})

# ********************************************************************************
#                      Building and Simulation
# ********************************************************************************
model.dT = timestep
print("Building Model")
model.build()
print("Loading Model")
model.load()

# Simulate
print("Simulating")
weight_initial = syn_pe_pop.get_var_values('g')
i=-1
while model.t <= runtime * num_epochs:
    if model.t >= (single_example_time+resting_time)*(i+1):
        # After example i -1,0,1,2,..
        print("Example {}, Time {}".format(int(i%num_examples),model.t))
        i += 1
        # Before example i 0,1,2,3,...
        neuron_view = poisson_pop.vars['timeStepToSpike'].view
        neuron_view[:] = 0.0
        neuron_view = lif_e_pop.vars['V'].view
        neuron_view[:] = random.uniform(v_reset_e,v_thres_e)
        model.push_state_to_device('lif_e_pop')
        neuron_view = lif_i_pop.vars['V'].view
        neuron_view[:] = random.uniform(v_reset_i,v_thres_i)
        model.push_state_to_device('lif_i_pop')

        rates = list(training['x'][i%num_examples,:,:].reshape((n_input)) / 4)
        neuron_view = poisson_pop.vars['rate'].view
        neuron_view[:] = rates
        model.push_state_to_device('poisson_pop')
    
    model.step_time()
model.pull_var_from_device('syn_pe_pop','g')
weight_final = syn_pe_pop.get_var_values('g')
print(weight_initial)
print(weight_final)
        
# ********************************************************************************
#                      Training and Classification
# ********************************************************************************
"""
print()
print("Classifying examples")

# Set eta to 0
input_e_pop.set_var("eta",0.0)

# Set SpikeNumber to 0
lif_e_pop.set_var("SpikeNumber",0)
lif_i_pop.set_var("SpikeNumber",0)

spike_number_record = np.zeros((n_e,10))

i=0
old_spike_number = np.zeros((n_e))
spike_number_record = np.zeros((n_e,10))
# spike_number_view = lif_e_pop.vars["SpikeNumber"].view
rates = list(training['x'][i%60000,:,:].reshape((n_input)) / 8000. * input_intensity)
label = int(training['y'][i%num_examples])
current_t = model.t
while model.t < current_t + runtime:
    model.step_time()
    if model.t >= current_t + (single_example_time + resting_time) * (i+1):
        spike_number_view = lif_e_pop.vars["SpikeNumber"].view
        # print(spike_number_view)
        # print(current_spike_number - old_spike_number)
        spike_number_record[:,label] += spike_number_view
        lif_e_pop.set_var("SpikeNumber",0)
        # print(spike_number_record)
        print("Example: {} Label: {}".format(i,label))
        i += 1
        rates = list(training['x'][i%60000,:,:].reshape((n_input)) / 8000. * input_intensity)
        label = int(training['y'][i%num_examples])
        poisson_pop.set_var('frequency', rates)
        poisson_pop.set_var('timeStepToSpike',0.0)
        lif_e_pop.set_var("SpikeNumber",0)
        lif_i_pop.set_var("SpikeNumber",0)


neuron_labels = np.argmax(spike_number_record,axis=1)
print()
print("Neuron labels")
print(neuron_labels)
print(spike_number_record)

# ********************************************************************************
#                      Evaluation on Training set
# ********************************************************************************

print()
print()
print("Evaluating on training set")

# Set eta to 0
input_e_pop.set_var("eta",0.0)

# Set SpikeNumber to 0
lif_e_pop.set_var("SpikeNumber",0)
lif_i_pop.set_var("SpikeNumber",0)
model.push_state_to_device("lif_e_pop")
model.push_state_to_device("lif_i_pop")

predictions = []
y_list = list(training['y'][:num_examples].reshape((num_examples)))

for i in range(num_examples):
    digit_count = np.empty((10))
    rates = list(training['x'][i%num_examples,:,:].reshape((n_input)) / 8000. * input_intensity)
    label = int(training['y'][i%num_examples])

    poisson_pop.set_var('frequency', rates)
    poisson_pop.set_var('timeStepToSpike',0.0)
    lif_e_pop.set_var("SpikeNumber",0)
    model.push_state_to_device("lif_e_pop")
    lif_i_pop.set_var("SpikeNumber",0)
    model.push_state_to_device("lif_i_pop")
    spike_number_view = lif_e_pop.vars["SpikeNumber"].view 
    model.push_state_to_device("poisson_pop")
    
    while model.t < single_example_time:
        model.step_time()
        model.pull_state_from_device(input_e_pop)
        model.pull_state_from_device(lif_e_pop)
    
    for j in range(n_e):
        # print(spike_number_view[j])
        digit_count[neuron_labels[j]] += spike_number_view[j]
    
    pred = np.argmax(digit_count,axis=0)
    predictions.append(pred)

# print(predictions[:50])
# print(y_list[:50])
print("Accuracy: {}%".format(accuracy(predictions,y_list)))
"""