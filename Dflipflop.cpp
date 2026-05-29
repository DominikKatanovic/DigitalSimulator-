#include "Dflipflop.h"
#include <iostream>

Dflipflop::Dflipflop(std::string n) : Component(n) {
    m_inputs.resize(1);
    std::cout << "[" << m_name << "] D-FlipFlop aktiv " << std::endl;
}

void Dflipflop::evaluate() {

    // Lese den D-Eingang und gib ihn sofort aus
    m_output = m_storedState;

}

void Dflipflop::onClockTick() {
    if (m_inputs[0] != nullptr) {
        m_inputs[0]->evaluate(); // Stelle sicher, dass der D-Eingang aktuell ist
        m_storedState = m_inputs[0]->getOutput(); // Hole den aktuellen Wert von D
    }
    else {
        m_storedState = false; // Sicherer Fallback: false
    }
}


void Dflipflop::printState() const {
    std::string pinD = (m_inputs[0]) ? "verbunden" : "FLOATING";
    std::cout << "Dflipflop [" << m_name << ": D=" << pinD << "] => Q=" << (m_output ? 1 : 0) << std::endl;
}