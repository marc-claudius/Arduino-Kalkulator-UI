//Das hier ist die cpp Datei (C Plus Plus)
#include "CalculatorUI.h" //Diese Datei soll mit der Header-Datei sprechen und die Funktionen von ihr beziehen
#include <iostream> // Für einfache Textausgaben in der Entwicklerkonsole
#include "imgui.h" // Zugriff auf die ImGui Bib, um Symbole zu erstellen

// Konstruktor: Wird aufgerufen, wenn das UI-Objekt erstellt wird
CalculatorUI::CalculatorUI() {
    currentExpression = "";
    calculatedResult = "";
    isCalculating = false;
    std::cout << "[System] CalculatorUI erstellt." << std::endl;
}

// Destruktor: Wird aufgerufen, wenn das Programm beendet wird
CalculatorUI::~CalculatorUI() {
    std::cout << "[System] CalculatorUI zerstoert." << std::endl;
}

// Haupt-Render-Methode, wird pro Frame aufgerufen
void CalculatorUI::render() {
ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;

// Wendet die Regeln an (und positioniert es fix im Hauptfenster)
ImGui::SetNextWindowPos(ImVec2(0, 0));
// Passende Fenstergröße wie in der main.cpp
ImGui::SetNextWindowSize(ImVec2(400, 600)); // Passend zur Fenstergröße in der main.cpp
ImGui::Begin("Taschenrechner", NULL, windowFlags);


// Das Dysplay wird erstellt, mit einem dunklen Hintergrund und abgerundeten Ecken.
ImGui::PushStyleColor(ImGuiCol_ChildBg, IM_COL32(30, 30, 30, 255)); 
ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 15.0f); 
ImGui::BeginChild("Display", ImVec2(300, 80), true); 
    
// Wenn nichts eingetippt wurde, zeige eine graue "0", sonst unsere Eingabe
    if (currentExpression.empty()) {
        ImGui::TextColored(ImVec4(0.5f, 0.5f, 0.5f, 1.0f), "0"); 
    } else {
        ImGui::Text("%s", currentExpression.c_str()); 
    }
ImGui::EndChild();
ImGui::PopStyleColor(); 
ImGui::PopStyleVar();


// Hier werden die Buttons erstellt, mit verschiedenen Farben für Funktionstasten, Operatoren und Zahlen.
ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 35.0f); 
ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(6, 6));
ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(160, 160, 160, 255));
ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 0, 0, 255));
if (ImGui::Button("AC", ImVec2(70, 70))){
    buttonClear();
} 
ImGui::SameLine();
if (ImGui::Button("DEL", ImVec2(70, 70))){
    if (!currentExpression.empty()){
        currentExpression.pop_back();
    }
}
ImGui::SameLine();
if (ImGui::Button(".", ImVec2(70, 70))){
    addButton('.');
}
ImGui::PopStyleColor(2);
ImGui::SameLine();
ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(220, 100, 0, 255));
if (ImGui::Button("=", ImVec2(70, 70))){
    sendExpression();
}
ImGui::PopStyleColor();
ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(60, 60, 60, 255));
if (ImGui::Button("7", ImVec2(70, 70))){
    addButton('7'); 
}
ImGui::SameLine();
if (ImGui::Button("8", ImVec2(70, 70))){
    addButton('8'); 
}
ImGui::SameLine();
if (ImGui::Button("9", ImVec2(70, 70))){
    addButton('9'); 
}
ImGui::PopStyleColor();
ImGui::SameLine();
ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(220, 100, 0, 255));
if (ImGui::Button("/", ImVec2(70, 70))){
    addButton('/'); 
}
ImGui::PopStyleColor();
ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(60, 60, 60, 255));
if (ImGui::Button("4", ImVec2(70, 70))){
    addButton('4'); 
}
ImGui::SameLine();
if (ImGui::Button("5", ImVec2(70, 70))){
    addButton('5'); 
}
ImGui::SameLine();
if (ImGui::Button("6", ImVec2(70, 70))){
    addButton('6'); 
}
ImGui::PopStyleColor();
ImGui::SameLine();
ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(220, 100, 0, 255));
if (ImGui::Button("*", ImVec2(70, 70))){
    addButton('*'); 
}
ImGui::PopStyleColor();
ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(60, 60, 60, 255));
if (ImGui::Button("1", ImVec2(70, 70))){
    addButton('1'); 
}
ImGui::SameLine();
if (ImGui::Button("2", ImVec2(70, 70))){
    addButton('2'); 
}
ImGui::SameLine();
if (ImGui::Button("3", ImVec2(70, 70))){
    addButton('3'); 
}
ImGui::PopStyleColor();
ImGui::SameLine();
ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(220, 100, 0, 255));
if (ImGui::Button("-", ImVec2(70, 70))){
    addButton('-');
}
ImGui::PopStyleColor();
ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(160, 160, 160, 255));
if (ImGui::Button("(", ImVec2(70, 70))){
    addButton('(');
}
ImGui::SameLine();
ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(60, 60, 60, 255));
if (ImGui::Button("0", ImVec2(70, 70))){
    addButton('0'); 
}
ImGui::PopStyleColor();
ImGui::SameLine();
if (ImGui::Button(")", ImVec2(70, 70))){
    addButton(')'); 
}
ImGui::PopStyleColor();
ImGui::SameLine();
ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(220, 100, 0, 255));
if (ImGui::Button("+", ImVec2(70, 70))){
    addButton('+');
}
ImGui::PopStyleColor();
ImGui::PopStyleVar(2);
ImGui::End(); // Schließt das Fenster wieder
// Asynchrone Abfrage der Hardware-Schnittstelle auf eingehende Ergebnisse
    std::string response = espPort.readString();
    
    if (response != "") {
        receiveResult(response);
    }
}

// Einen Buchstaben zum Term hinzufuegen
void CalculatorUI::addButton(char btnChar) {
    if (!isCalculating) {
        currentExpression += btnChar;
        std::cout << "Taste gedrueckt: " << btnChar << " | Neuer Term: " << currentExpression << std::endl;
    }
}

// Den Term loeschen (AC)
void CalculatorUI::buttonClear() {
    if (!isCalculating) {
        currentExpression = "";
        calculatedResult = "";
    }
}

// Den Term an den Arduino senden
void CalculatorUI::sendExpression() {
    if (!currentExpression.empty() && !isCalculating) {
        isCalculating = true; // Eingabe sperren
        std::cout << "Sende an Arduino: " << currentExpression << std::endl;
        espPort.sendString(currentExpression);
    }
}

// Antwort vom Arduino empfangen
void CalculatorUI::receiveResult(std::string result) {
    while (!result.empty() && (result.back() == '\n' || result.back() == '\r')) {
        result.pop_back();
    }
    calculatedResult = result;
    currentExpression = result; // Ergebnis wird zum neuen Term, um weiterzurechnen
    isCalculating = false;      // Eingabe wieder freigeben
    std::cout << "Ergebnis empfangen: " << calculatedResult << std::endl;
}