#include "XorGate.h"
#include <iostream>

/**
 * Konstruktor des XorGate
 * Initialisiert die Pins (genau 2 Eingänge)
 */
XorGate::XorGate(std::string n) : Component(n) {
    m_inputs.resize(2);  // XOR-Gatter hat exakt 2 Eingangs-Pins
    std::cout << "[" << m_name << "] XOR-Gatter aktiviert (2 Pins)" << std::endl;
}

/**
 * Berechnet die XOR-Logik über Smart Pointers (Pull-Prinzip)
 * 
 * Floating Pin Check: Sind beide Kabel eingesteckt?
 * Logik: (A AND NOT B) OR (NOT A AND B)
 */
void XorGate::evaluate() {
    if (m_inputs[0] && m_inputs[1]) {
        bool valA = m_inputs[0]->getOutput();
        bool valB = m_inputs[1]->getOutput();
        m_output = (valA && !valB) || (!valA && valB);
    } else {
        std::cerr << "[WARNUNG] " << m_name << ": XOR-Gatter hat unverbundene Pins (Floating)!" << std::endl;
        m_output = false;
    }
}

/**
 * Gibt den Zustand dieses XOR-Gatters aus
 */
void XorGate::printState() const {
    std::string pinA = (m_inputs[0]) ? "verbunden" : "FLOATING";
    std::string pinB = (m_inputs[1]) ? "verbunden" : "FLOATING";
    std::cout << "XorGate [" << m_name << ": A=" << pinA 
              << ", B=" << pinB 
              << "] => Output=" << (m_output ? 1 : 0) << std::endl;
}
