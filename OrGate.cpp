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
    if (m_alreadyCalculated) {
        return; // Verhindert doppelte Berechnung bei zyklischen Verbindungen (optional)
    }

    // Checken ob der Baum weiter läuft 
    // Wenn der ptr nicht null ist dann soll das nächste Kind weiter berechnet werden 
    if (m_inputs[0] != nullptr) {
        m_inputs[0]->evaluate();
    }
    if (m_inputs[1] != nullptr) {
        m_inputs[1]->evaluate();
    }

    // Berechnen der OR-Logik
    bool valA = (m_inputs[0] != nullptr) ? m_inputs[0]->getOutput() : false;  // Sicherer Fallback: false
    bool valB = (m_inputs[1] != nullptr) ? m_inputs[1]->getOutput() : false;  // Sicherer Fallback: false
    m_output = valA || valB;

    m_alreadyCalculated = true;
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
