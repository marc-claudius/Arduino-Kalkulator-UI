//Dieses Dokument ist die Header-Datei, das Inhaltsverzeichnis als abbild des UML-Diagrammes. 
#pragma once
#include <string>

class CalculatorUI {
private:
    // Unsere Variablen aus dem UML-Diagramm. 
    // Diese Variablen sind für die Ausdrücke zuständig, aktueller Ausdruck, berechneter Ausdruck und es wird gerechnet
    std::string currentExpression = "";
    std::string calculatedResult;
    bool isCalculating;

public:
    // Konstruktor (wird beim Start aufgerufen), die Oberfläche wird erstellt
    CalculatorUI(); 
    
    // Destruktor (räumt beim Beenden auf), Oberfläche wird geschlossen
    ~CalculatorUI(); 

    // Die neue Hauptfunktion für ImGui: Zeichnet das Fenster jeden Frame neu
    void render(); 

    // Unsere Methoden aus dem UML-Diagramm
    void addButton(char btnChar);
    void buttonClear();
    void sendExpression();
    void receiveResult(std::string result);
};