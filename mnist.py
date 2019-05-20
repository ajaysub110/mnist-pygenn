import numpy as np 
import matplotlib.pyplot as plt 

import time
import pickle
import os 
from struct import unpack

from pygenn import genn_model, genn_wrapper

# Data path
root_path = '/home/ajays/Desktop/mnist-pygenn'
mnist_data_path = '/home/ajays/mnist/'
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

# Poisson model
poisson_model = genn_model.create_custom_neuron_class(
    "poisson_model",
    var_name_types=[("timeStepToSpike", "scalar"),("frequency","scalar")],
    sim_code="""
    if($(timeStepToSpike) <= 0.0f) 
    {
        $(timeStepToSpike) += $(gennrand_exponential) / $(frequency);
    }
    $(timeStepToSpike) -= 1.0;
    """,
    threshold_condition_code="$(timeStepToSpike) <= 0.0"
)()

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
    $(theta) += 1;
    """,
    threshold_condition_code="$(RefracTime) <= 0.0 && $(V) >= $(Vthres) + $(theta)",
    derived_params=[
        ("ExpTC", genn_model.create_dpf_class(lambda pars, dt: np.exp(-dt / pars[0]))()),
        ("ExpTtheta", genn_model.create_dpf_class(lambda pars, dt: np.exp(-dt / pars[5]))())
    ]
)()

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
)()

# Synapse
syn_model = genn_model.create_custom_postsynaptic_class(
    "syn_model",
    param_names=["TauG", "Erev"],
    decay_code="""
    $(inSyn) *= $(ExpDecay);
    """,
    apply_input_code="""
    $(Isyn) += $(inSyn) * ($(Erev) - $(V));
    """,
    derived_params=[
        ("ExpDecay", genn_model.create_dpf_class(lambda pars, dt: np.exp(-dt / pars[0]))())
    ]
)()

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
            const scalar newG = $(g) - ($(eta) * ($(Xpre) - $(Xtar)) * pow(($(gMax) - $(g)),$(mu)));
            $(g) = $(gMax) <= newG ? $(gMax) : newG;
        }
        """,

    pre_spike_code=
        """
        const scalar dt = $(t) - $(sT_pre);
        if(dt > 0) {
            const scalar expXpre = exp(-dt / $(tauMinus));
            $(Xpre) = ($(Xpre) * exp(-dt / $(tauMinus))) + 1.0;
        }
        """,

    is_pre_spike_time_required=True,
    is_post_spike_time_required=True)()

lateral_inhibition = genn_model.create_custom_init_var_snippet_class(
    "lateral_inhibition",
    param_names=['weight'],
    var_init_code="$(value)=($(id_pre)==$(id_post)) ? 0.0 : $(weight);"
)()

onevsone = genn_model.create_custom_init_var_snippet_class(
    "onevsone",
    param_names=['weight'],
    var_init_code="$(value)=($(id_pre)==$(id_post)) ? $(weight) : 0.0;"
)()

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
dt = 1.0

# Architecture
num_epochs = 3
num_examples = 400
n_input = 784
n_e = 100
n_i = n_e 
single_example_time = 350
resting_time = 150
runtime = num_examples * (single_example_time + resting_time)
input_intensity = 2. 
start_input_intensity = input_intensity

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
g_max = 0.01
x_tar = 0.1
eta = 0.01
mu = 1

# Group up parameters
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
lif_e_init = {"V": v_reset_e, "RefracTime":0.0, "SpikeNumber":0, "theta":0.0}
lif_i_init = {"V": v_reset_i, "RefracTime":0.0, "SpikeNumber":0}

poisson_init = {
    "timeStepToSpike": 0.0,
    "frequency": 0.0}

syn_e_params = {"TauG":tau_ge, "Erev":e_exc}
syn_i_params = {"TauG":tau_gi, "Erev":e_inh}

stdp_init = {"g":genn_model.init_var("Uniform",{"min":0.0, "max":g_max}), "eta":eta}
stdp_params = {"tauMinus": 20.0,"gMax": g_max,"Xtar":x_tar,"mu":mu}
stdp_pre_init = {"Xpre": 0.0}

syn_e_init = {"g":genn_model.init_var(onevsone,{"weight":-77.0})}
syn_i_init = {"g":genn_model.init_var(lateral_inhibition,{"weight":-77.0})}

# ********************************************************************************
#                      Model Instances
# ********************************************************************************

model = genn_model.GeNNModel("float","mnist")
model.dT = dt

# model.default_var_mode = genn_wrapper.VarMode_LOC_HOST_DEVICE_INIT_DEVICE

# Neuron populations
poisson_pop = model.add_neuron_population("poisson_pop",n_input,poisson_model,{},poisson_init)

lif_e_pop = model.add_neuron_population("lif_e_pop",n_e,lif_e_model,lif_e_params,lif_e_init)

lif_i_pop = model.add_neuron_population("lif_i_pop",n_i,lif_i_model,lif_i_params,lif_i_init)

input_e_pop = model.add_synapse_population("input_e_pop","DENSE_INDIVIDUALG",genn_wrapper.NO_DELAY,
    poisson_pop, lif_e_pop,
    stdp_model, stdp_params, stdp_init, stdp_pre_init, {},
    syn_model, syn_e_params, {})

syn_e_pop = model.add_synapse_population("syn_e_pop","SPARSE_INDIVIDUALG",genn_wrapper.NO_DELAY,
    lif_e_pop, lif_i_pop,
    "StaticPulse", {}, {"g":genn_model.init_var("Uniform",{"min":0.0, "max":g_max})}, {}, {},
    syn_model, syn_e_params, syn_e_init, genn_model.init_connectivity("OneToOne",{}))

syn_i_pop = model.add_synapse_population("syn_i_pop","DENSE_INDIVIDUALG",genn_wrapper.NO_DELAY,
    lif_i_pop, lif_e_pop,
    "StaticPulse", {}, {"g":genn_model.init_var("Uniform",{"min":0.0, "max":-g_max})}, {}, {},
    syn_model, syn_i_params, syn_i_init)


# ********************************************************************************
#                      Building and Simulation
# ********************************************************************************

print("Building Model")
model.build()
print("Loading Model")
model.load()

print("Simulating")

# Simulate
for j in range(num_epochs):
    for i in range(num_examples):
        rates = list(training['x'][i%60000,:,:].reshape((n_input)) / 8000. * input_intensity)
        poisson_pop.set_var('frequency', rates)
        poisson_pop.set_var('timeStepToSpike',0.0)

        model.push_state_to_device("poisson_pop")
        while model.t < single_example_time:
            model.step_time()

        print("Epoch: {}, Example: {}".format(j,i))

    # model.pull_state_from_device(input_e_pop)
    # model.pull_state_from_device(syn_e_pop)
    # model.pull_state_from_device(syn_i_pop)

    # input_e_g = input_e_pop.get_var_values("g")
    # syn_e_g = syn_e_pop.get_var_values("g")
    # syn_i_g = syn_i_pop.get_var_values("g")

    # np.save(os.path.join(root_path,'ckpt/epoch{}_input_e_g_ovo_li_1'.format(j)), input_e_g)
    # np.save(os.path.join(root_path,'ckpt/epoch{}_syn_e_g_ovo_li_1'.format(j)), syn_e_g)
    # np.save(os.path.join(root_path,'ckpt/epoch{}_syn_i_g_ovo_li_1'.format(j)), syn_i_g)

# ********************************************************************************
#                      Training and Classification
# ********************************************************************************

print()
print("Classifying examples")

# Set eta to 0
input_e_pop.set_var("eta",0.0)
# syn_e_pop.set_var("eta",0.0)
# syn_i_pop.set_var("eta",0.0)

# Set SpikeNumber to 0
lif_e_pop.set_var("SpikeNumber",0)
lif_i_pop.set_var("SpikeNumber",0)

spike_number_record = np.empty((n_e,10))

for i in range(num_examples):
    rates = list(training['x'][i%num_examples,:,:].reshape((n_input)) / 8000. * input_intensity)
    label = int(training['y'][i%num_examples])

    poisson_pop.set_var('frequency', rates)
    poisson_pop.set_var('timeStepToSpike',0.0)
    lif_e_pop.set_var("SpikeNumber",0)
    lif_i_pop.set_var("SpikeNumber",0)
    spike_number_view = lif_e_pop.vars["SpikeNumber"].view 
    model.push_state_to_device("poisson_pop")
    
    while model.t < single_example_time:
        model.step_time()
        model.pull_state_from_device(lif_e_pop)
    spike_number_record[:,label] += spike_number_view

    print("Example: {}, Target: {}".format(i,label))

neuron_labels = np.argmax(spike_number_record,axis=1)
print()
print("Neuron labels")
print(neuron_labels)

# ********************************************************************************
#                      Evaluation on Training set
# ********************************************************************************

print()
print()
print("Evaluating on training set")

# Set eta to 0
input_e_pop.set_var("eta",0.0)
# syn_e_pop.set_var("eta",0.0)
# syn_i_pop.set_var("eta",0.0)

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
    
    for i in range(n_e):
        digit_count[neuron_labels[i]] += spike_number_view[i]
    
    pred = np.argmax(digit_count,axis=0)
    predictions.append(pred)

print("Accuracy: {}%".format(accuracy(predictions,y_list)))