#pragma once

#include "Component.h"

/**
 * OR-Gatter Klasse (erbt von Gate)
 * Ausgabe ist 1, wenn mindestens ein Eingang 1 ist
 * 
 * Merkmale (Labor 7):
 * - Hat genau 2 Eingangs-Pins
 * - Zieht sich Werte über m_inputs[] (Pull-Prinzip)
 * - Prüft auf nullptr (Floating-Pin-Check)
 */
class OrGate : public Component {
public:
    /**
     * Konstruktor: Nimmt einen Namen entgegen
     * @param n Der Name dieses OR-Gatters
     */
    OrGate(std::string n);

    /**
     * Berechnet das Ausgangssignal (OR-Logik über Smart Pointers)
     */
    void evaluate() override;

    /**
     * Gibt den aktuellen Zustand des Gatters aus
     */
    void printState() const override;
};
