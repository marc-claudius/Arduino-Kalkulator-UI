#include "SerialPort.h"
#include <iostream>

//Konstruktor Variablen werden Initialisiert. hSerial ist die Verbindung zum Gerät und Windows. connected_status speichert, ob die Verbindung zum Gerät besteht oder nicht.
SerialPort::SerialPort() {
    hSerial = INVALID_HANDLE_VALUE;
    connected_status = false;
}

//Destruktor, welcher die Verbindung zum Gerät trennt, wenn das Objekt geschlossen wird.
SerialPort::~SerialPort() {
    disconnect();
}

//connect versucht die Verbindung aufzubauen. hSerial verwendet den Port wie ein Textdokument, um mit dem Gerät zu kommunizieren. 
bool SerialPort::connect(const char* portName) {
    hSerial = CreateFileA(portName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hSerial == INVALID_HANDLE_VALUE) {
        std::cerr << "Fehler: Konnte " << portName << " nicht oeffnen!" << std::endl;
        return false;
    }

    //Konfiguration der seriellen Verbindung als DCB (Device Control Block). Hier werden die Baudrate, Datenbits, Stoppbits und Parität eingestellt. 
    //Diese Einstellungen müssen mit denen des Geräts übereinstimmen.
    DCB dcbSerialParams = {0};
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    if (!GetCommState(hSerial, &dcbSerialParams)) {
        return false;
    }
    
    dcbSerialParams.BaudRate = CBR_9600;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;
    
    if (!SetCommState(hSerial, &dcbSerialParams)) {
        return false;
    }

    // Konfiguration des Lese-Timeouts. Diese Einstellungen bestimmen, wie lange die ReadFile-Funktion wartet.
    COMMTIMEOUTS timeouts = {0};
    timeouts.ReadIntervalTimeout = MAXDWORD;
    timeouts.ReadTotalTimeoutConstant = 0;
    timeouts.ReadTotalTimeoutMultiplier = 0;
    SetCommTimeouts(hSerial, &timeouts);

    connected_status = true;
    std::cout << "Erfolgreich mit " << portName << " verbunden!" << std::endl;
    return true;
}
//Trennt die Verbindung sicher.
void SerialPort::disconnect() {
    if (connected_status) {
        CloseHandle(hSerial);
        connected_status = false;
    }
}

//Senden einer Nachricht in richtiger Form. Windows kann nur in einem Zeichenformat mit dem Gerät Kommunizieren. 
//Hinzugefügt wird noch ein Enter für das Warten des ESP.
void SerialPort::sendString(std::string message) {
    if (!connected_status) return;
    DWORD bytesWritten;
    message += "\n"; // Das Enter-Zeichen fuer den ESP
    WriteFile(hSerial, message.c_str(), message.length(), &bytesWritten, NULL);
}

//Lesen einer Nachricht vom Gerät. Daten werden in einem Puffer von 256 ZEichen gespeichert
//Konvertiert in ein String und mit einem Nullzeichen als Ende des Strings zurückgegeben.
std::string SerialPort::readString() {
    if (!connected_status) return "";
    char buffer[256];
    DWORD bytesRead;
    if (ReadFile(hSerial, buffer, sizeof(buffer) - 1, &bytesRead, NULL) && bytesRead > 0) {
        buffer[bytesRead] = '\0';
        return std::string(buffer);
    }
    return "";
}

//Verbindungsstatus wird zurückgegeben.
bool SerialPort::isConnected() {
    return connected_status;
}