#include "AndGate.h"
#include <iostream>

/**
 * Konstruktor des AndGate
 * Initialisiert die Pins (genau 2 Eingänge) und ruft Basiskonstruktor auf
 */
AndGate::AndGate(std::string n) : Component(n) {
    m_inputs.resize(2);  // AND-Gatter hat exakt 2 Eingangs-Pins
    std::cout << "[" << m_name << "] AND-Gatter aktiviert (2 Pins)" << std::endl;
}

/**
 * Berechnet die AND-Logik über Smart Pointers (Pull-Prinzip)
 * 
 * Floating Pin Check: Sind beide Kabel eingesteckt?
 * - Wenn ja: hole die Werte von den Quell-Gattern ab
 * - Wenn nein: Warnung + Fallback auf false (sicherer Zustand)
 */
void AndGate::evaluate() {
    // Floating Pin Check: Sind beide Kabel eingesteckt?
    if (m_inputs[0] && m_inputs[1]) {
        bool valA = m_inputs[0]->getOutput();
        bool valB = m_inputs[1]->getOutput();
        m_output = valA && valB;
    } else {
        std::cerr << "[WARNUNG] " << m_name << ": AND-Gatter hat unverbundene Pins (Floating)!" << std::endl;
        m_output = false;  // Fallback-Zustand
    }
}

/**
 * Gibt den Zustand dieses AND-Gatters aus
 */
void AndGate::printState() const {
    std::string pinA = (m_inputs[0]) ? "verbunden" : "FLOATING";
    std::string pinB = (m_inputs[1]) ? "verbunden" : "FLOATING";
    std::cout << "AndGate [" << m_name << ": A=" << pinA 
              << ", B=" << pinB 
              << "] => Output=" << (m_output ? 1 : 0) << std::endl;
}
