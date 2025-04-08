NEURON {
    SUFFIX DR
    USEION k READ ek WRITE ik
    RANGE g_dr_bar, n_dr_inf, n_dr_tau
}

PARAMETER {
    g_dr_bar = 5 (S/cm2)
    ek = -77 (mV)
}

STATE {
    n_dr
}

ASSIGNED {
    v (volt)
    ik (mA/cm2)
    n_dr_inf n_dr_tau
}

BREAKPOINT {
    SOLVE states METHOD cnexp
    ik = g_dr_bar * n_dr^4 * (v - ek)
}

DERIVATIVE states {
    n_dr' = (n_dr_inf - n_dr) / n_dr_tau
}

PROCEDURE rates(v (mV)) {
    LOCAL alpha_n, beta_n

    alpha_n = -0.018 * (v - 13) / (-1 + exp(-(v - 13) / 25))
    beta_n = 0.0054 * (v - 23) / (-1 + exp((v - 23) / 12))
    
    n_dr_inf = alpha_n / (alpha_n + beta_n)

    n_dr_tau = 1 / (alpha_n + beta_n)
}