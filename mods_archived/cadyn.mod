NEURON {
    SUFFIX cadyn
    USEION ca READ ica, cao WRITE cai
    RANGE tau_ca, depth, cai_inf, phi_ca, FARADAY, cao
}

PARAMETER {
    FARADAY = 96485 (C/mol)
    depth = 2e-4 (um)
    tau_ca = 250 (ms)
    cai_inf = 50e-6 (mM)
    phi_ca = 600e-9     : default is soma
    cao = 2 (mM)
}

STATE {
    cai (mM)
}

ASSIGNED {
    ica (mA/cm2)
    area (cm2)
}


INITIAL {
    cai = cai_inf  : VERBATIM cai = _ion_cai;ENDVERBATIM
    
}

BREAKPOINT {
    SOLVE states METHOD cnexp
}

DERIVATIVE states {
    cai' = - (phi_ca * ica) / (FARADAY *(area * depth)) + (cai_inf - cai) / tau_ca
}