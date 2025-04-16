NEURON {
    POINT_PROCESS nmda
    NONSPECIFIC_CURRENT i
    RANGE tau1, tau2, e, gmax, tau_s, i
}

UNITS {
    (uS) = (microsiemens)
    (mV) = (millivolt)
    (nA) = (nanoamp)
}

PARAMETER {
    tau1 = 1.0 (ms)      : Fast time constant
    tau2 = 40.0 (ms)     : Slow time constant
    e = 0 (mV)           : Reversal potential
    gmax = 0.0001 (uS)   : Maximum conductance
    tau_s = 0.1 (ms)     : Gate time constant for Mg2+ block
}

ASSIGNED {
    v (mV)
    i (nA)
    g (uS)
    mgblock (1)
    s (1)         : Mg2+ gate variable
    factor (1)
}

STATE {
    A (uS)
    B (uS)
}

INITIAL {
    LOCAL tp
    A = 0
    B = 0
    s = 1
    if (tau1 / tau2 > 0.9999) {
        tau1 = 0.9999 * tau2
    }
    tp = (tau1 * tau2) / (tau2 - tau1) * log(tau2 / tau1)
    factor = -exp(-tp / tau1) + exp(-tp / tau2)
    factor = 1 / factor
}

BREAKPOINT {
    SOLVE state METHOD cnexp

    : Mg2+ block as a voltage-dependent sigmoid
    mgblock = 1.50265 / (1 + 0.33 * exp(-0.06 * v))

    : Update gating variable with exponential smoothing
    s = s * exp(-1 / tau_s) + (1 - exp(-1 / tau_s)) * mgblock

    g = gmax * (B - A) * s
    i = g * (v - e)
}

DERIVATIVE state {
    A' = -A / tau1
    B' = -B / tau2
}

NET_RECEIVE(weight (1)) {
    A = A + factor * weight
    B = B + factor * weight
}
