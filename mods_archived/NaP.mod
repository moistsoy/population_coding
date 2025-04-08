NEURON {
    SUFFIX NaP
    USEION na READ ena WRITE ina
    RANGE g_nap_bar, m_nap_inf, h_nap_inf, m_nap_tau, h_nap_tau, DA
}

PARAMETER {
    g_nap_bar = 0.005 (S/cm2)
    DA = 0  : 0% DA (Default), set to 1 for 100% DA
    ena = 50 (mV)
}

STATE {
    m_nap h_nap
}

ASSIGNED {
    v (volt)
    ina (mA/cm2)
    m_nap_inf h_nap_inf m_nap_tau h_nap_tau
}

BREAKPOINT {
    SOLVE states METHOD cnexp
    ina = g_nap_bar * m_nap * h_nap * (v - ena)
}

DERIVATIVE states {
    m_nap' = (m_nap_inf - m_nap) / m_nap_tau
    h_nap' = (h_nap_inf - h_nap) / h_nap_tau
}

PROCEDURE rates(v (mV)) {
    LOCAL alpha_m, beta_m, alpha_h, beta_h
    
    if (DA == 0) {  : 0% DA
        alpha_m = -0.2816 * (v + 12) / (1 - exp(-(v + 12) / 9.3))
        beta_m = 0.2464 * (v - 15) / (1 - exp((v - 15) / 6))

        alpha_h = 2.8e-5 * exp(-(v + 42.8477) / 4.0248)
        beta_h = 0.02 / (1 + exp(-(v - 413.9284) / 148.2589))
    } else {  : 100% DA
        alpha_m = -0.2816 * (v + 17) / (1 - exp(-(v + 17) / 9.3))
        beta_m = 0.2464 * (v - 10) / (1 - exp((v - 10) / 6))

        alpha_h = 2.0e-5 * exp(-(v + 42.8477) / 4.0248)
        beta_h = 0.014286 / (1 + exp(-(v - 413.9284) / 148.2589))
    }
    
    m_nap_inf = alpha_m / (alpha_m + beta_m)
    h_nap_inf = alpha_h / (alpha_h + beta_h)

    m_nap_tau = 1 / (alpha_m + beta_m)
    h_nap_tau = 1 / (alpha_h + beta_h)
}

