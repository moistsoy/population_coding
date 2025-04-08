from neuron import h
import numpy as np
import matplotlib.pyplot as plt


### Morphology ###

soma_l = 28.62
soma_d = 21.84

dend_l = 650
dend_d = 6.5

### Passive properties ###

soma_Rm = 30000     # membrane resistance
soma_Eleak = -70    # leakage reversal potential
soma_Cm = 1.2       # membrane capacitance
soma_Ri = 150       # axial resistance

dend_Rm = soma_Rm / 1.92
dend_Eleak = -70
dend_Cm = soma_Cm * 1.92 
dend_Ri = 150

### Ionic conductances ###

soma_INa = 0.117      # Na+ current
soma_INaP = 0.0018     # persistent Na+ current
soma_IDR = 0.005       # delayed rectifier current
soma_IKS = 8e-5 + 0.001     # slowly inactivating K+ current
soma_IC = 0.0021       # voltage-dependent C-type K+ current
soma_IHVA = 0.0004     # high-voltage-activated Ca2+ current

dend_INa = 0.02
dend_INaP = 0.0008
dend_IDR = 0.0014
dend_IKS = soma_IKS
dend_IC = soma_IC
dend_IHVA = 0.0008

CAF = 600e-9   # calcium accumulation factor

### Plasticity parameters ###

ampa_tau1 = 0.55  # ms
ampa_tau2 = 2.2   # ms

nmda_taus = 0.1
nmda_tau1 = 10.6   # ms
nmda_tau2 = 285.0  # ms

### Desired peak conductances

g_AMPA_max = 4e-9   # S/cm2
g_NMDA_max = g_AMPA_max / 50    # S/cm2

USE = 0.6       # STD utilization parameter 
t_rec = 800     # recovery time (ms)


h.load_file('stdrun.hoc')

### load ionic conductances ###

h.nrn_load_dll("./mods/arm64/.libs/libnrnmech.so")
mechanisms = ['hh', 'naf', 'nap', 'hva', 'kdr', 'iks', 'ic', 'cadyn', 'kdyn']

### Create a soma ###

soma = h.Section(name='soma')

### Add morphology ###

soma.L = soma_l
soma.diam = soma_d

### Add passive properties ###

soma.insert('pas')
soma.g_pas = 1 / soma_Rm
soma.e_pas = soma_Eleak
soma.Ra = soma_Ri
soma.cm = soma_Cm

### Add ionic conductances ###

for i in mechanisms:
    soma.insert(i)

soma(0.5).nap.gnapbar = soma_INaP
soma(0.5).naf.gnafbar = soma_INa
soma(0.5).hva.ghvabar = soma_IHVA
soma(0.5).kdr.gkdrbar = soma_IDR
soma(0.5).iks.gKsbar = soma_IKS
soma(0.5).ic.gkcbar = soma_IC
soma(0.5).cadyn.CAF = CAF

### Create a dendrite ###

dend = h.Section(name='dend')

### Add morphology ###

dend.L = dend_l
dend.diam = dend_d

### Add passive properties ###

dend.insert('pas')  # Passive dendrite
dend.g_pas = 1 / dend_Rm
dend.e_pas = dend_Eleak
dend.Ra = dend_Ri
dend.cm = dend_Cm

# Add ionic conductances

for i in mechanisms:
    dend.insert(i)

dend(0.5).nap.gnapbar = dend_INaP
dend(0.5).naf.gnafbar = dend_INa
dend(0.5).hva.ghvabar = dend_IHVA
dend(0.5).kdr.gkdrbar = dend_IDR
dend(0.5).iks.gKsbar = dend_IKS
dend(0.5).ic.gkcbar = dend_IC
dend(0.5).cadyn.CAF = CAF

### Connect soma and dendrite ###
dend.connect(soma)

class Synapse:
    def __init__(self, sec, loc=0.5):
        self.syn_AMPA = h.Exp2Syn(loc, sec=sec)
        self.syn_NMDA = h.Exp2Syn(loc, sec=sec)
        
        # AMPA parameters
        self.syn_AMPA.tau1 = 0.2  # ms (rise time)
        self.syn_AMPA.tau2 = 1  # ms (decay time)
        self.syn_AMPA.e = 0       # mV (reversal potential)
        self.g_AMPA_max = 4e-9    # S (4 nS)
        
        # NMDA parameters
        self.syn_NMDA.tau1 = 2.3  # ms (rise time)
        self.syn_NMDA.tau2 = 95.0 # ms (decay time)
        self.syn_NMDA.e = 0       # mV (reversal potential)
        self.g_NMDA_max = 4e-9 / 50  # S (4/50 nS)
        
        # Short-term depression parameters
        self.U_SE = 0.6      # Utilization factor
        self.t_rec = 800      # Recovery time constant (ms)
        self.R = 1.0          # Fraction of available resources
        
        self.netcon_AMPA = h.NetCon(None, self.syn_AMPA)
        self.netcon_NMDA = h.NetCon(None, self.syn_NMDA)
        self.netcon_AMPA.weight[0] = self.g_AMPA_max
        self.netcon_NMDA.weight[0] = self.g_NMDA_max
        
    def activate(self, time):
        # Implement short-term depression
        self.R = self.R * (1 - self.U_SE) + (1 - self.R) * (1 - np.exp(-time/self.t_rec))
        weight_AMPA = self.g_AMPA_max * self.U_SE * self.R
        weight_NMDA = self.g_NMDA_max * self.U_SE * self.R
        
        self.netcon_AMPA.weight[0] = weight_AMPA
        self.netcon_NMDA.weight[0] = weight_NMDA
        
        self.netcon_AMPA.event(time)
        self.netcon_NMDA.event(time)

# Create a synapse
syn = Synapse(dend)

# Simulation setup
tstop = 1  # ms
dt = 0.1  # ms
timevec = np.arange(0, tstop, dt)
v_vec = h.Vector().record(soma(0.5)._ref_v)  # Record voltage

# Stimulate the synapse at different times
stim_times = [0.1]  # ms
for stim in stim_times:
    syn.activate(stim)

# h.finitialize(-65)
# h.continuerun(tstop)

# # Plot results
# plt.figure()
# plt.plot(timevec, v_vec, label='Membrane Potential')
# plt.xlabel('Time (ms)')
# plt.ylabel('Voltage (mV)')
# plt.legend()
# plt.show()
