#pragma once

#include "Component.h"

/**
 * NOT-Gatter Klasse (erbt von Gate)
 * Ausgabe ist invertiert - WICHTIG: NOT hat nur einen Eingang!
 * 
 * Merkmale (Labor 7):
 * - Hat genau 1 Eingangs-Pin (m_inputs.size() == 1)
 * - Zieht sich Werte über m_inputs[0] (Pull-Prinzip)
 * - Prüft auf nullptr (Floating-Pin-Check)
 */
class NotGate : public Component {
public:
    /**
     * Konstruktor: Nimmt einen Namen entgegen
     * @param n Der Name dieses NOT-Gatters
     */
    NotGate(std::string n);

    /**
     * Berechnet das invertierte Ausgangssignal
     */
    void evaluate() override;

    /**
     * Gibt den aktuellen Zustand des Gatters aus
     */
    void printState() const override;
};
