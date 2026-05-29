#pragma once

#include "Component.h"

/**
 * NAND-Gatter Klasse (erbt von Gate)
 * NAND = NOT(AND)
 * Ausgabe ist 0, nur wenn beide Eingaenge 1 sind
 * 
 * Merkmale (Labor 7):
 * - Hat genau 2 Eingangs-Pins
 * - Zieht sich Werte ueber m_inputs[] (Pull-Prinzip)
 * - Prueft auf nullptr (Floating-Pin-Check)
 */
class NandGate : public Component {
public:
    /**
     * Konstruktor: Nimmt einen Namen entgegen
     * @param n Der Name dieses NAND-Gatters
     */
    NandGate(std::string n);

    /**
     * Berechnet das NAND-Ausgangssignal (NAND-Logik ueber Smart Pointers)
     */
    void evaluate() override final;

    /**
     * Gibt den aktuellen Zustand des Gatters aus
     */
    void printState() const override;
};


