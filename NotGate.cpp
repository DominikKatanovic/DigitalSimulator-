#include "NotGate.h"
#include <iostream>

/**
 * Konstruktor des NotGate
 * Initialisiert die Pins (genau 1 Eingang)
 */
NotGate::NotGate(std::string n) : Component(n) {
    m_inputs.resize(1);  // NOT-Gatter hat exakt 1 Eingangs-Pin
    std::cout << "[" << m_name << "] NOT-Gatter aktiviert (1 Pin)" << std::endl;
}

/**
 * Berechnet die NOT-Logik über Smart Pointers (Pull-Prinzip)
 * 
 * Floating Pin Check: Ist das Kabel eingesteckt?
 */
void NotGate::evaluate() {
    if (m_inputs[0]) {
        bool val = m_inputs[0]->getOutput();
        m_output = !val;
    } else {
        std::cerr << "[WARNUNG] " << m_name << ": NOT-Gatter hat unverbundenen Pin (Floating)!" << std::endl;
        m_output = false;
    }
}

/**
 * Gibt den Zustand dieses NOT-Gatters aus
 */
void NotGate::printState() const {
    std::string pin = (m_inputs[0]) ? "verbunden" : "FLOATING";
    std::cout << "NotGate [" << m_name << ": Input=" << pin 
              << "] => Output=" << (m_output ? 1 : 0) << std::endl;
}





