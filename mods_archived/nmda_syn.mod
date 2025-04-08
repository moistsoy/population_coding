NEURON {
    POINT_PROCESS NMDAsyn
    NONSPECIFIC_CURRENT i
    RANGE tau1, tau2, e, gmax, g, wn
    }

PARAMETER {
    tau1 = 2.3 (ms)   : Rise time constant
    tau2 = 95 (ms)    : Decay time constant
    e = 0 (mV)        : Reversal potential
    gmax = 4e-3 (uS)  : Maximal NMDA conductance
    wn = 1.0          : Synaptic efficacy (plastic weight)
}

ASSIGNED {
    v (mV)      : Membrane voltage
    i (nA)      : Synaptic current
    g (uS)      : Conductance
    factor      : Normalization factor
    s           : Mg2+ block scaling factor
}

STATE {
    A
    B
}

INITIAL {
    LOCAL tp
    A = 0
    B = 0
    tp = (tau1*tau2)/(tau2 - tau1) * log(tau2/tau1)
    factor = 1.0 / (-exp(-tp/tau1) + exp(-tp/tau2))  : Normalize peak
}

BREAKPOINT {
    SOLVE state METHOD cnexp
    rate(v)  : Ensure s is updated
    g = gmax * wn * (B - A)  : NMDA conductance
    i = g * s * (v - e)  : Voltage-dependent NMDA current
}

DERIVATIVE state {
    A' = -A / tau1
    B' = -B / tau2
}

PROCEDURE rate(v (mV)) {
    s = 1 / (1 + exp(-0.062 * v) * (1 / 3.57))  : NMDA Mg2+ block function
}

NET_RECEIVE (weight (uS)) {
    A = A + factor
    B = B + factor
}
