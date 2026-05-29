#include <iostream>
#include <vector>
#include <memory>
#include "Component.h"
#include "AndGate.h"
#include "OrGate.h"
#include "NotGate.h"
#include "XorGate.h"
#include "NandGate.h"
#include "Switch.h"
#include "Dflipflop.h"

/**
 * =====================================================================
 * Labor 7: Schaltkreisaufbau mit Smart Pointers (DAG-Architektur)
 * =====================================================================
 * 
 * Diese Demonstration zeigt:
 * 1. Den Aufbau eines echten digitalen Schaltkreises
 * 2. Die Verbindung von Gattern über Smart Pointers (Kupferkabel)
 * 3. Die Simulation eines Halbaddierers (Half Adder)
 * 4. Das "Pull-Prinzip" für Werteabfrage
 * 
 * Ein Halbaddierer:
 * - Nimmt zwei Ein-Bit-Eingänge (A, B)
 * - Produziert zwei Ausgänge: Summe (S) und Carry (C)
 * - S = A XOR B
 * - C = A AND B
 */

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "  C++ Digital Simulator - Labor 7" << std::endl;
    std::cout << "  Halbaddierer (Half Adder) Schaltkreis" << std::endl;
    std::cout << "========================================\n" << std::endl;

    // =====================================================================
    // Phase 4: Halbaddierer montieren
    // =====================================================================
    
    std::cout << "[SCHRITT 1] Komponenten instanziieren (als Smart Pointers)...\n" << std::endl;
    
    // Datenquellen (Schalter)
    auto swA = std::make_shared<Switch>("Input A");
    auto swB = std::make_shared<Switch>("Input B");
    auto swCarryIn = std::make_shared<Switch>("Carry In"); // Zusätzlicher Schalter für Volladdierer
    
    // Logikgatter
    auto xorGate_1 = std::make_shared<XorGate>("XOR (Summe)");
    auto xorGate_2 = std::make_shared<XorGate>("XOR (Summe 2)"); // Zusätztlicher XOR für Volladdierer
    auto andGate_1 = std::make_shared<AndGate>("AND (Carry)");
    auto andGate_2 = std::make_shared<AndGate>("AND (Carry 2)"); // Zusätztlicher AND für Volladdierer
    auto orGate = std::make_shared<OrGate>("OR (Carry Out)"); // OR-Gatte um Carry-Bit und Ergebnis von AND2
    auto notGate = std::make_shared<NotGate>("NOT (Inverter)"); // Optional: NOT-Gatter für erweiterte Tests

    // Flipflops
    auto dff = std::make_shared<Dflipflop>("D-FlipFlop"); // Optional: D-FlipFlop für erweiterte Tests

    // Vectoren zur Dflipflop und speicherung aller Gates
    std::vector<std::shared_ptr<Component>> allGates;
    allGates.push_back(xorGate_1);
    allGates.push_back(xorGate_2);
    allGates.push_back(andGate_1);
    allGates.push_back(andGate_2);
    allGates.push_back(orGate);
    allGates.push_back(notGate);
    
    std::vector<std::shared_ptr<Dflipflop>> allFlipflops;
    allFlipflops.push_back(dff);


    std::cout << "\n[SCHRITT 2] Schaltkreis verkabeln (DAG-Aufbau)...\n" << std::endl;
    
    // Verkabelung (Fan-Out!): Beide Schalter gehen an beide Gatter
    // ┌─────────────┐
    // │  Input A ──┬──> XOR
    // └─────────────┤
    //              └──> AND
    //
    // ┌─────────────┐
    // │  Input B ──┬──> XOR
    // └─────────────┤
    //              └──> AND
    
    xorGate_1->connectInput(0, swA);    // XOR Pin 0 = Input A
    xorGate_1->connectInput(1, swB);    // XOR Pin 1 = Input B

    xorGate_2->connectInput(0, xorGate_1); // XOR2 Pin 0 = XOR1 Output (Summe)
    xorGate_2->connectInput(1, swCarryIn); // XOR2 Pin 1 = Carry In (für Volladdierer)
    
    andGate_1->connectInput(0, swA);    // AND Pin 0 = Input A
    andGate_1->connectInput(1, swB);    // AND Pin 1 = Input B

    andGate_2->connectInput(0, xorGate_1); // AND2 Pin 0 = XOR1 Output (Summe)
    andGate_2->connectInput(1, swCarryIn); // AND2 Pin 1 = Carry In (für Volladdierer)
    
    orGate->connectInput(0, andGate_1); // OR Pin 0 = AND1 Output (Carry von A und B)
    orGate->connectInput(1, andGate_2); // OR Pin 1 = AND2 Output (Carry von Summe und Carry In)

    notGate->connectInput(0, dff); // NOT Pin 0 = D-FlipFlop Output

    dff->connectInput(0, notGate); // D-FlipFlop Pin 0 = NOT Output


    std::cout << "\n[SCHRITT 3] Wahrheitstabelle: Alle 4 Kombinationen testen...\n" << std::endl;
    std::cout << "┌─────┬─────┬────────┬───────┐" << std::endl;
    std::cout << "│  A  │  B  │ Summe  │ Carry │" << std::endl;
    std::cout << "├─────┼─────┼────────┼───────┤" << std::endl;
    
    // Test-Kombinationen: 0+0, 0+1, 1+0, 1+1
    std::vector<std::tuple<bool, bool, bool>> testCases = {
        {false, false, false}, // A=0, B=0, CarryIn=0
        {false, true, false},  // A=0, B=1, CarryIn=0
        {true, false, false},  // A=1, B=0, CarryIn=0
        {true, true, false}   // A=1, B=1, CarryIn=0
    };
    
    int testCount = 0;
    int passedCount = 0;
    
    for (auto [a, b, carryIn] : testCases) {
        // KRITISCH: Erst Schalter setzen, DANN evaluate() aufrufen!
        swA->setState(a);
        swB->setState(b);
        swCarryIn->setState(carryIn);
        
        // Evaluiere die Gatter (Pull-Prinzip: Sie holen sich Werte selbst)
        xorGate_2->evaluate();
        orGate->evaluate();
        notGate->evaluate();

        
        // Lese die Ergebnisse aus
        bool summe = xorGate_2->getOutput();
        bool carry = orGate->getOutput();
        bool dffstate = dff->getOutput();
        
        // Berechne erwartete Werte
        bool expectedSum = a ^ b;        // XOR
        bool expectedCarry = a && b;     // AND
        
        // Ausgabe der Testzelle
        // Diese Testzeilen stimmen nicht mit der Wahrheitstabelle überein
        std::cout << "│  " << (a ? 1 : 0) << "  │  " << (b ? 1 : 0) << "  │";
        std::cout << "   " << (summe ? 1 : 0) << "    │";
        std::cout << "   " << (carry ? 1 : 0) << "   │";


          // for-Schleife um alle Gatter zu Reseten
        for (int i = 0; i < 10; i++) {
            for (auto& gate : allGates) {
                gate->reset();
            }

            for (auto& gate : allGates) {
                gate->evaluate();
            }
            
            for (auto& flipflop : allFlipflops) {
                flipflop->onClockTick(); // Simuliere eine Taktflanke für alle D-FlipFlops;
            }

            std::cout << "Tick:  " << i+1 << "    " << dff->getOutput() << "   |" << std::endl;
        }
     
        // Überprüfe Korrektheit
        testCount += 2;
        if (summe == expectedSum) {
            std::cout << " ✓";
            passedCount++;
        } else {
            std::cout << " ✗";
        }
        std::cout << " ";
        if (carry == expectedCarry) {
            std::cout << "✓ " << std::endl;
            passedCount++;
        } else {
            std::cout << "✗ " << std::endl;
        }
    }
    
    std::cout << "└─────┴─────┴────────┴───────┘" << std::endl;
    
    std::cout << "\n[SCHRITT 4] Zustandsbericht der Komponenten:\n" << std::endl;
    
    swA->printState();
    swB->printState();
    xorGate_2->printState();
    orGate->printState();
    dff->printState();
    
    // =====================================================================
    // Abschluss und Exit-Code
    // =====================================================================
    std::cout << "\n========================================" << std::endl;
    std::cout << "Test Summary:" << std::endl;
    std::cout << "Bestanden: " << passedCount << " / " << testCount << std::endl;
    std::cout << "========================================" << std::endl;

    if (passedCount == testCount) {
        std::cout << "\n[SUCCESS] Halbaddierer funktioniert korrekt! ✓" << std::endl;
        std::cout << "Der DAG wurde erfolgreich aufgebaut und evaluiert." << std::endl;
        return 0;  // ← EXIT-CODE 0: ERFOLG (Grüner Haken für CI)
    } else {
        std::cerr << "\n[FEHLER] Mindestens ein Test fehlgeschlagen!" << std::endl;
        return 1;  // ← EXIT-CODE 1: FEHLER (Rotes Kreuz für CI)
    }
}
