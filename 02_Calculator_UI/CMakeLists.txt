# Benötigte CMake Version
cmake_minimum_required(VERSION 3.15)

# WICHTIG: Verbinde CMake mit unserem vcpkg-Paketmanager
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/../vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

# Name unseres Projekts
project(ArduinoKalkulatorUI)

# Wir fordern modernen C++17 Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Wir suchen die Pakete, die vcpkg für uns geladen hat
find_package(imgui CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(OpenGL REQUIRED) # <--- NEU: Wir suchen die Standard-Grafikbibliothek vom PC

# Unsere C++ Dateien
set(SOURCES
    main.cpp
    CalculatorUI.cpp
    CalculatorUI.h
    SerialPort.cpp
    SerialPort.h
)

# Wir erstellen die ausführende .exe Datei
add_executable(Kalkulator ${SOURCES})

# Wir verknüpfen unsere .exe mit den Bibliotheken (ImGui, GLFW und OpenGL)
# <--- NEU: Hinten OpenGL::GL hinzugefügt
target_link_libraries(Kalkulator PRIVATE imgui::imgui glfw OpenGL::GL)