#pragma once

#include "Component.h"

/**
 * Switch (Schalter) Klasse - Datenquelle für den Schaltkreis
 * 
 * Ein Schalter ist auch ein Gatter, aber:
 * - Er hat KEINE Eingänge (m_inputs ist leer)
 * - Er wird von außen (Benutzer/main.cpp) umgelegt
 * - Seine evaluate() macht nichts (der Output wird direkt gesetzt)
 * 
 * Der Schalter ist die "Datenquelle" des DAGs.
 * Labor 7: Ein echte Datenquelle mit direkter setState()-Methode.
 */
class Switch : public Component {
public:
    /**
     * Konstruktor: Nimmt einen Namen entgegen
     * @param n Der Name dieses Schalters (z.B. "Input A", "Input B")
     */
    Switch(std::string n);

    /**
     * Setzt den Schalter auf ON oder OFF
     * Dies ist die Hauptmethode zum Steuern des Schalters
     * @param state true = ON (1), false = OFF (0)
     */
    void setState(bool state);

    /**
     * evaluate(): Bleibt leer (oder setzt nur m_output auf internen State)
     * Der Schalter hat keine Abhängigkeiten - sein Output wird direkt gesetzt
     */
    void evaluate() override;

    /**
     * Gibt den aktuellen Zustand des Schalters aus
     */
    void printState() const override;
};
