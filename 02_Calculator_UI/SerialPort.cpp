#include "SerialPort.h"
#include <iostream>

SerialPort::SerialPort() {
    hSerial = INVALID_HANDLE_VALUE;
    connected_status = false;
}

SerialPort::~SerialPort() {
    disconnect();
}

bool SerialPort::connect(const char* portName) {
    hSerial = CreateFileA(portName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hSerial == INVALID_HANDLE_VALUE) {
        std::cerr << "Fehler: Konnte " << portName << " nicht oeffnen!" << std::endl;
        return false;
    }

    DCB dcbSerialParams = {0};
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    if (!GetCommState(hSerial, &dcbSerialParams)) {
        return false;
    }
    
    dcbSerialParams.BaudRate = CBR_9600; // Muss mit Arduino uebereinstimmen!
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;
    
    if (!SetCommState(hSerial, &dcbSerialParams)) {
        return false;
    }

    // Wartezeiten, damit das UI nicht einfriert
    COMMTIMEOUTS timeouts = {0};
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    SetCommTimeouts(hSerial, &timeouts);

    connected_status = true;
    std::cout << "Erfolgreich mit " << portName << " verbunden!" << std::endl;
    return true;
}

void SerialPort::disconnect() {
    if (connected_status) {
        CloseHandle(hSerial);
        connected_status = false;
    }
}

void SerialPort::sendString(std::string message) {
    if (!connected_status) return;
    DWORD bytesWritten;
    message += "\n"; // Das Enter-Zeichen fuer den ESP
    WriteFile(hSerial, message.c_str(), message.length(), &bytesWritten, NULL);
}

std::string SerialPort::readString() {
    if (!connected_status) return "";
    char buffer[256];
    DWORD bytesRead;
    if (ReadFile(hSerial, buffer, sizeof(buffer) - 1, &bytesRead, NULL) && bytesRead > 0) {
        buffer[bytesRead] = '\0'; // String sauber beenden
        return std::string(buffer);
    }
    return "";
}

bool SerialPort::isConnected() {
    return connected_status;
}