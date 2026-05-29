#include "Component.h"

/**
 * Konstruktor der Gate-Klasse
 * Initialisiert alle Attribute sicher
 */
Component::Component(std::string n) 
    : m_name(n), m_output(false) {
    std::cout << "[" << m_name << "] Component erstellt" << std::endl;
}

/**
 * Verbindet einen Eingang mit einem anderen Gatter (Kabel-Plugin)
 * Hardware-Schutzschaltung (Out-of-Bounds Check)
 */
void Component::connectInput(int index, std::shared_ptr<Component> source) {
    // Prüfen, ob der Pin physisch am Gatter existiert
    if (index >= 0 && index < static_cast<int>(m_inputs.size())) {
        m_inputs[index] = source;
        std::cout << "[VERKABELUNG] " << m_name << " Pin " << index 
                  << " verbunden mit " << source->m_name << std::endl;
    } else {
        std::cerr << "[FEHLER] " << m_name << ": Pin " << index << " existiert nicht! "
                  << "(Verfügbar: 0-" << (m_inputs.size() - 1) << ")" << std::endl;
    }
}

/**
 * Getter für den Ausgangswert
 */
bool Component::getOutput() const {
    return m_output;
}

/**
 * Virtueller Destruktor: Wird aufgerufen wenn Objekt zerstört wird
 */
Component::~Component() {
    std::cout << "[DESTRUKTOR] Zerstöre Gate: " << m_name << std::endl;
}
