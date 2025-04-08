NEURON {
    SUFFIX KS
    USEION k READ ek WRITE ik
    RANGE g_ks_bar, a_ks_inf, a_ks_tau, b_ks_inf, b_ks_tau
}

PARAMETER {
    g_ks_bar = 0.009 (S/cm2)    : added 1.0 mS/cm2
    ek = -77 (mV)
}

STATE {
    a_ks b_ks
}

ASSIGNED {
    v (volt)
    ik (mA/cm2)
    a_ks_inf b_ks_inf a_ks_tau b_ks_tau 
}

BREAKPOINT {
    SOLVE states METHOD cnexp
    ik = g_ks_bar * a_ks * b_ks * (v - ek)
}

DERIVATIVE states {
    a_ks' = (a_ks_inf - a_ks) / a_ks_tau
    b_ks' = (b_ks_inf - b_ks) / b_ks_tau
}

PROCEDURE rates(v (mV)) {

    a_ks_inf = 1 / (1 + exp(-v + 34) / 6.5)
    b_ks_inf = 1 / (1 + exp(v + 65) / 6.6)

    a_ks_tau = 6.0
    b_ks_tau = 200 + 220 / (1 + exp(-(v + 71.6) / 6.85))
}