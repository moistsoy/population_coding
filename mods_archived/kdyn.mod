NEURON {
    SUFFIX kdyn
    USEION k READ ik, ki WRITE ko
    RANGE tau_k, depth, ko_inf, phi_k, FARADAY, ki
}

PARAMETER {
    FARADAY = 96485 (C/mol)
    depth = 0.07 (um)         : Depth of extracellular space
    tau_k = 7 (ms)         : Time constant for potassium accumulation
    ko_inf = 3.82 (mM)        : Baseline extracellular potassium concentration
    phi_k = 2.0           : Potassium flux scaling factor
    ki = 140 (mM)
}

STATE {
    ko (mM)  : Extracellular potassium concentration
}

ASSIGNED {
    ik (mA/cm2)  : Potassium current
    area (cm2)
}

INITIAL {
    ko = ko_inf  : Set initial extracellular K+ concentration
}

BREAKPOINT {
    SOLVE states METHOD cnexp
}

DERIVATIVE states {
    ko' = - (phi_k * ik) / (FARADAY * (area * depth)) + (ko_inf - ko) / tau_k
}
