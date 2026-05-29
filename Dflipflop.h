#pragma once
#include "Component.h"
/*******************************************************
 * D-FlipFlop Klasse (erbt von Component)
 * 
 * Merkmale:
 * - Speichert den letzten Zustand (D) bei einer steigenden Taktflanke
 * - Hat 2 Eingänge: D (Daten) und CLK (Takt)
 * - Gibt den gespeicherten Zustand am Ausgang Q aus
 * 
 * Funktionsweise:
 * - Bei einer steigenden Taktflanke (CLK von 0 auf 1) wird der Wert von D in Q übernommen
 * - Q bleibt konstant, bis die nächste steigende Taktflanke auftritt
 */

 class Dflipflop : public Component {
    private:
        bool m_storedState; // Speichert den aktuellen Zustand (Q)

    public:
        Dflipflop(std::string n);

        void evaluate() override;

        void onClockTick(); // Methode, die bei einer steigenden Taktflanke aufgerufen wird

        void printState() const override;


 };
