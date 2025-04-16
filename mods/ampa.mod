NEURON {
    POINT_PROCESS ampa
    NONSPECIFIC_CURRENT i
    RANGE tau1, tau2, gmax, e, i, USE, t_rec
}

UNITS {
    (uS) = (microsiemens)
    (mV) = (millivolt)
    (nA) = (nanoamp)
}

PARAMETER {
    tau1 = 0.55 (ms)
    tau2 = 2.2 (ms)
    gmax = 0.001 (uS)
    e = 0 (mV)
    USE = 0.6
    t_rec = 800 (ms)
}

ASSIGNED {
    v (mV)
    i (nA)
    g (uS)
    factor
}

STATE {
    A (uS)
    B (uS)
    R
}

INITIAL {
    A = 0
    B = 0
    R = 1
    if (tau1 / tau2 > 0.9999) {
        tau1 = 0.9999 * tau2
    }
    factor = 1 / (exp(-tau1 / tau2) - exp(-tau1 / tau1))
}

BREAKPOINT {
    SOLVE state METHOD cnexp
    g = gmax * (B - A)
    i = g * (v - e)
}

DERIVATIVE state {
    A' = -A / tau1
    B' = -B / tau2
    R' = (1 - R) / t_rec
}

NET_RECEIVE(weight (1)) {
    if (R > 1e-6) {
        A = A + weight * USE * R
        B = B + weight * USE * R
        R = R * (1 - USE)
    }
}
