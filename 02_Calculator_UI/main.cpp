#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include "CalculatorUI.h"
#include <iostream>
#include <windows.h>
#include <string>
#include <iostream>

int main() {
    // 1. GLFW initialisieren, dieser Erstellt das Fenster für das UI
    if (!glfwInit()) {
        std::cerr << "Fehler beim Initialisieren von GLFW!" << std::endl;
        return -1;
    }
    glfwWindowHint(GLFW_SAMPLES, 8); //Kantenglättung für Kreise

    // 2. Fenster erstellen
    GLFWwindow* window = glfwCreateWindow(310, 470, "Arduino Kalkulator", NULL, NULL);
    if (!window) {
        std::cerr << "Fehler beim Erstellen des Fensters!" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // VSync aktivieren (verhindert Bildschirm-Flackern)

    // 3. ImGui initialisieren
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    
    //Arial wird Installiert
    io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\arial.ttf", 24.0f);

    // Wir aktivieren direkt den Dark-Mode fuer unser angestrebtes Design
    ImGui::StyleColorsDark(); 

    // Die Grafik-Backends mit unserem Fenster verknuepfen
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    // 4. Unsere eigene UI-Klasse Erschaffen
    CalculatorUI myUI;
    myUI.espPort.connect("COM3");

    // 5. Die Hauptschleife (Laeuft so lange, wie das Fenster offen ist)
    while (!glfwWindowShouldClose(window)) {
        // Events vom Betriebssystem abfragen (Maus bewegt, X geklickt?)
        glfwPollEvents();

        // Neuen Frame fuer das UI vorbereiten
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Hier rufen wir unsere UI-Logik auf
        myUI.render();

        // Das Bild final auf den Monitor zeichnen
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        
        // Den Hintergrund des Fensters dunkelgrau faerben
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f); 
        glClear(GL_COLOR_BUFFER_BIT);
        
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    // 6. Sauberes Aufraeumen, wenn der Nutzer das Fenster schliesst
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}