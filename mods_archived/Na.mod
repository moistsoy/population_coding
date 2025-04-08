NEURON {
    SUFFIX Na
    USEION na READ ena WRITE ina
    RANGE g_na_bar, m_na_inf, h_na_inf, m_na_tau, h_na_tau
}

PARAMETER {
    g_na_bar = 0.12 (S/cm2)
    ena = 50 (mV)
}

STATE {
    m_na h_na
}

ASSIGNED {
    v (volt)
    ina (mA/cm2)
    m_na_inf h_na_inf m_na_tau h_na_tau
}

BREAKPOINT {
    SOLVE states METHOD cnexp
    ina = g_na_bar * m_na^3 * h_na * (v - ena)
}

DERIVATIVE states {
    m_na' = (m_na_inf - m_na) / m_na_tau
    h_na' = (h_na_inf - h_na) / h_na_tau
}

PROCEDURE rates(v (mV)) {
    LOCAL alpha_m, beta_m, alpha_h, beta_h

    alpha_m = -0.2816 * (v + 28) / (-1 + exp(-(v + 28)/9.3))
    beta_m = 0.2464 * (v + 1) / (-1 + exp((v + 1)/6))
    
    alpha_h = 0.098 * exp(-(v + 43.1) / 20)
    beta_h = 1.4 / (1 + exp(-(v + 13.1) / 10))
    
    m_na_inf = alpha_m / (alpha_m + beta_m)
    h_na_inf = alpha_h / (alpha_h + beta_h)

    m_na_tau = 1 / (alpha_m + beta_m)
    h_na_tau = 1 / (alpha_h + beta_h)
}
