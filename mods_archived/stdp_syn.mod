NEURON {
    POINT_PROCESS STDPsyn
    NONSPECIFIC_CURRENT i
    RANGE tau1, tau2, e, gmax, g, wn, USE, trec
    GLOBAL tlast, wmax, tau_LTP, tau_LTD, A_LTP, A_LTD
}

PARAMETER {
    tau1 = 0.5 (ms)   : Rise time constant
    tau2 = 3.0 (ms)   : Decay time constant
    e = 0 (mV)        : Reversal potential
    gmax = 4e-3 (uS)  : Maximal AMPA conductance
    USE = 0.6         : Utilization parameter for short-term depression
    trec = 800 (ms)   : Recovery time constant
    wn = 1.0          : Synaptic efficacy (plastic weight)
    
    wmax = 2.0        : Maximum synaptic weight
    tau_LTP = 20.0 (ms) : Time constant for LTP
    tau_LTD = 30.0 (ms) : Time constant for LTD
    A_LTP = 0.005       : LTP learning rate
    A_LTD = 0.005       : LTD learning rate
}

ASSIGNED {
    v (mV)      : Membrane voltage
    i (nA)      : Synaptic current
    g (uS)      : Conductance
    factor      : Normalization factor
    tlast (ms)  : Last spike time
}

STATE {
    A
    B
}

INITIAL {
    LOCAL tp
    A = 0
    B = 0
    tlast = -1e9
    tp = (tau1*tau2)/(tau2 - tau1) * log(tau2/tau1)
    factor = 1.0 / (-exp(-tp/tau1) + exp(-tp/tau2))  : Normalize peak
}

BREAKPOINT {
    SOLVE state METHOD cnexp
    g = gmax * wn * (B - A)
    i = g * (v - e)
}

DERIVATIVE state {
    A' = -A / tau1
    B' = -B / tau2
}

NET_RECEIVE (weight (uS), u, R, last_release) {

    LOCAL dt, w_change

    INITIAL {
        u = USE
        R = 1
        last_release = -1e9
    }

    dt = t - last_release
    if (dt > 0) {
        R = 1 - (1 - R) * exp(-dt / trec)
        u = USE + (1 - USE) * u * exp(-dt / trec)
        R = R - u * R
        A = A + factor * u * R
        B = B + factor * u * R
        last_release = t
    }

    : STDP update
    if (tlast > -1e9) {
        dt = t - tlast
        if (dt > 0) {
            w_change = A_LTP * exp(-dt / tau_LTP)
        } else {
            w_change = -A_LTD * exp(dt / tau_LTD)
        }
        wn = wn + w_change
        if (wn > wmax) {
            wn = wmax
        } else if (wn < 0) {
            wn = 0
        }
    }
    tlast = t
}
