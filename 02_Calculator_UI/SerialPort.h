#pragma once
#include <windows.h>
#include <string>

class SerialPort {
public:
    SerialPort();
    ~SerialPort();

    bool connect(const char* portName);
    void disconnect();
    void sendString(std::string message);
    std::string readString();
    bool isConnected();

private:
    HANDLE hSerial;
    bool connected_status;
};