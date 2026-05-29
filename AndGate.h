#pragma once

#include "Component.h"

/**
 * AND-Gatter Klasse (erbt von Gate)
 * Ausgabe ist 1, nur wenn beide Eingänge 1 sind
 * 
 * Merkmale (Labor 7):
 * - Hat genau 2 Eingangs-Pins
 * - Zieht sich Werte über m_inputs[] (Pull-Prinzip)
 * - Prüft auf nullptr (Floating-Pin-Check)
 */
class AndGate : public Component {
public:
    /**
     * Konstruktor: Nimmt einen Namen entgegen
     * @param n Der Name dieses AND-Gatters
     */
    AndGate(std::string n);

    /**
     * Berechnet das Ausgangssignal (AND-Logik über Smart Pointers)
     * Das Keyword 'final' verhindert, dass Subklassen diese Methode überschreiben
     */
    void evaluate() override final;

    /**
     * Gibt den aktuellen Zustand des Gatters aus
     */
    void printState() const override;
};
