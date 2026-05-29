#pragma once

#include "Component.h"

/**
 * XOR-Gatter Klasse (erbt von Gate)
 * Ausgabe ist 1, wenn die Eingänge unterschiedlich sind
 * 
 * Logik: XOR(A, B) = (A AND NOT B) OR (NOT A AND B)
 * 
 * Merkmale (Labor 7):
 * - Hat genau 2 Eingangs-Pins
 * - Zieht sich Werte über m_inputs[] (Pull-Prinzip)
 * - Prüft auf nullptr (Floating-Pin-Check)
 */
class XorGate : public Component {
public:
    /**
     * Konstruktor: Nimmt einen Namen entgegen
     * @param n Der Name dieses XOR-Gatters
     */
    XorGate(std::string n);

    /**
     * Berechnet die XOR-Logik
     */
    void evaluate() override;

    /**
     * Gibt den aktuellen Zustand aus
     */
    void printState() const override;
};
