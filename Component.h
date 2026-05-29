#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <memory>

/**
 * Gate (Basisklasse) - Abstraktion für alle Logikgatter
 * 
 * Neue Architektur (Labor 7):
 * - Gatter werden über Smart Pointers (std::shared_ptr) verbunden
 * - Ein Vektor m_inputs speichert alle Eingänge (Adjazenzliste / DAG)
 * - Jedes Gatter kennt die Anzahl seiner benötigten Eingänge
 * - evaluate() zieht sich Werte aktiv über die Pointer (Pull-Prinzip)
 * 
 * Alle spezifischen Gatter (AndGate, OrGate, NotGate, etc.) erben von dieser Klasse
 * und müssen die reine virtuelle Methode evaluate() implementieren.
 */
class Component {
protected:
    // Geschützte Attribute
    std::string m_name;
    bool m_output;
    std::vector<std::shared_ptr<Component>> m_inputs;  // ← Die "Kupferkabel"

    bool m_alreadyCalculated = false; // Flag für Zyklus-Check (optional, für erweiterte Gattertypen)
public:
    /**
     * Konstruktor: Initialisiert ein Gatter mit Namen
     * @param n Der Name des Gatters (z.B. "Haupt-AND", "Carry")
     */
    Component(std::string n);

    /**
     * Verbindet einen Eingang mit einem anderen Gatter (Kabel-Plugin)
     * Includes Hardware-Schutzschaltung (Out-of-Bounds Check)
     * @param index Der Pin-Index (0, 1, ...)
     * @param source Das Quell-Gatter
     */
    void connectInput(int index, std::shared_ptr<Component> source);

    /**
     * Gibt den aktuellen Ausgangswert zurück
     * @return true wenn output=1, false wenn output=0
     */
    bool getOutput() const;

    /**
     * Rein virtuelle Methode: evaluate()
     * Berechnet den Ausgang basierend auf den verbundenen Eingängen (Pull-Prinzip)
     * Diese Methode MUSS von jeder abgeleiteten Klasse implementiert werden.
     */
    virtual void evaluate() = 0;

    // Optional: Für erweiterte Gattertypen, um den Berechnungsstatus zurückzusetzen
    virtual void reset() {
        m_alreadyCalculated = false;
    }

    /**
     * Gibt den aktuellen Zustand des Gatters aus
     */
    virtual void printState() const = 0;

    /**
     * Virtueller Destruktor: Sichert korrekte Cleanup-Reihenfolge bei Polymorphismus
     */
    virtual ~Component();
};
