#include "Switch.h"
#include <iostream>

/**
 * Konstruktor des Schalters
 * Ein Schalter hat KEINE Eingänge (m_inputs bleibt leer)
 * Der initiale Zustand ist OFF (false)
 */
Switch::Switch(std::string n) : Component(n) {
    m_inputs.resize(0);  // Schalter hat KEINE Eingänge!
    m_output = false;    // Initialer Zustand: OFF
    std::cout << "[" << m_name << "] Schalter erstellt (Datenquelle, kein Eingang)" << std::endl;
}

/**
 * Setzt den Schalter auf ON (true) oder OFF (false)
 * Dies ist die Hauptmethode zum Steuern des Schalters
 * 
 * Diese Methode wird von der main.cpp aufgerufen, um den Schalter zu steuern
 */
void Switch::setState(bool state) {
    m_output = state;
    std::cout << "[" << m_name << "] Zustand gesetzt auf: " << (state ? "ON (1)" : "OFF (0)") << std::endl;
}

/**
 * evaluate(): Bleibt absichtlich leer
 * Der Schalter ist eine Datenquelle - sein Output wird direkt via setState() gesetzt
 * Es gibt keine Abhängigkeiten oder Berechnungen zu machen
 */
void Switch::evaluate() {
    // Intentionally empty - Schalter benötigt keine Berechnung
}

/**
 * Gibt den aktuellen Zustand des Schalters aus
 */
void Switch::printState() const {
    std::cout << "Switch [" << m_name << "] => Output=" 
              << (m_output ? "ON (1)" : "OFF (0)") << std::endl;
}
