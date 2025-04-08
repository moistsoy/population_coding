NEURON {
    SUFFIX HVA
    USEION ca READ eca WRITE ica
    RANGE g_hva_bar, u_hva_inf, v_hva_inf, u_hva_tau, v_hva_tau
}

PARAMETER {
    g_hva_bar = 0.04 (S/cm2)
    eca = 120 (mV)
}

STATE {
    u_hva v_hva
}

ASSIGNED {
    v (volt)
    ica (mA/cm2)
    u_hva_inf v_hva_inf u_hva_tau v_hva_tau
}

BREAKPOINT {
    SOLVE states METHOD cnexp 
    ica = g_hva_bar * u_hva^2 * v_hva * (v - eca)
}

DERIVATIVE states {
    u_hva' = (u_hva_inf - u_hva) / u_hva_tau
    v_hva' = (v_hva_inf - v_hva) / v_hva_tau
}

PROCEDURE rates(v (mV)) {
    u_hva_inf = 1 / (1 + exp(-(v + 24.6) / 11.3))
    v_hva_inf = 1 / (1 + exp(v + 12.6) / 18.9)

    u_hva_tau = 1.25 * 2 / (exp(-0.031 * (v + 37.1)) + exp(0.031 * (v + 37.1)))
    v_hva_tau = 420.0 * 3  : sped up by 3..?
}