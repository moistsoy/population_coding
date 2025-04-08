NEURON {
    SUFFIX C
    USEION ca READ eca WRITE ica
    RANGE g_c_bar
}

PARAMETER {
    g_c_bar = 0.21 (S/cm2)
    eca = 120 (mV)
}

STATE {
    c_c
}

CONSTANT {
    LOG10 = 2.302585
}

ASSIGNED {
    v (volt)
    ica (mA/cm2)
    c_c_inf c_c_tau
    cai (mM)
}

BREAKPOINT {
    SOLVE states METHOD cnexp
    ica = g_c_bar * c_c^2 * (v - eca)
}

DERIVATIVE states {
    c_c' = (c_c_inf - c_c) / c_c_tau
}

PROCEDURE rates(v (mV)) {
    LOCAL alpha_c, beta_c

    alpha_c = -0.00642 * (v + 40 * log(cai) / LOG10) * 1 / (-1 + exp(-((v + 40 * log(cai) / LOG10) + 18) / 25))
    beta_c = 1.7 * exp(-(v + 40 * log(cai) / LOG10 + 152) / 30)
    
    c_c_inf = alpha_c / (alpha_c + beta_c)
    c_c_tau = (1 / (alpha_c + beta_c) > 1.1) ? (1 / (alpha_c + beta_c)) : 1.1

}