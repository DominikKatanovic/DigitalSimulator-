#include "OrGate.h"
#include <iostream>

/**
 * Konstruktor des OrGate
 * Initialisiert die Pins (genau 2 Eingänge)
 */
OrGate::OrGate(std::string n) : Component(n) {
    m_inputs.resize(2);  // OR-Gatter hat exakt 2 Eingangs-Pins
    std::cout << "[" << m_name << "] OR-Gatter aktiviert (2 Pins)" << std::endl;
}

/**
 * Berechnet die OR-Logik über Smart Pointers (Pull-Prinzip)
 * 
 * Floating Pin Check: Sind beide Kabel eingesteckt?
 */
void OrGate::evaluate() {
    if (m_inputs[0] && m_inputs[1]) {
        bool valA = m_inputs[0]->getOutput();
        bool valB = m_inputs[1]->getOutput();
        m_output = valA || valB;
    } else {
        std::cerr << "[WARNUNG] " << m_name << ": OR-Gatter hat unverbundene Pins (Floating)!" << std::endl;
        m_output = false;
    }
}

/**
 * Gibt den Zustand dieses OR-Gatters aus
 */
void OrGate::printState() const {
    std::string pinA = (m_inputs[0]) ? "verbunden" : "FLOATING";
    std::string pinB = (m_inputs[1]) ? "verbunden" : "FLOATING";
    std::cout << "OrGate [" << m_name << ": A=" << pinA 
              << ", B=" << pinB 
              << "] => Output=" << (m_output ? 1 : 0) << std::endl;
}
