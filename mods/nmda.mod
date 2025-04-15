NEURON {
    POINT_PROCESS nmda
    NONSPECIFIC_CURRENT i
    RANGE tau1, tau2, e, gmax, i
}

UNITS {
    (uS) = (microsiemens)
    (mV) = (millivolt)
    (nA) = (nanoamp)
}

PARAMETER {
    tau1 = 1.0 (ms)
    tau2 = 40.0 (ms)
    e = 0 (mV)
    gmax = 0.001 (uS)
}

ASSIGNED {
    v (mV)
    i (nA)
    g (uS)
    mgblock (1)
    factor
}

STATE {
    A (uS)
    B (uS)
}

INITIAL {
    LOCAL tp
    A = 0
    B = 0
    tp = (tau1 * tau2)/(tau2 - tau1) * log(tau2 / tau1)
    factor = -exp(-tp/tau1) + exp(-tp/tau2)
    factor = 1 / factor
}

BREAKPOINT {
    SOLVE state METHOD cnexp
    mgblock = 1.50265 / (1 + 0.33 * exp(-0.0625 * v))
    g = gmax * (B - A) * mgblock
    i = g * (v - e)
}

DERIVATIVE state {
    A' = -A / tau1
    B' = -B / tau2
}

NET_RECEIVE(dummy (ms)) {
    A = A + factor
    B = B + factor
}