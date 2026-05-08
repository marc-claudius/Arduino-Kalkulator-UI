
//Dieser Code ist die Headerdatei für die SerialPort-Klasse, die die serielle Kommunikation mit einem Gerät ermöglicht.
//Dieser Code darf nur einmal durchlaufen werden auch wenn dieser mehrfach aufgerufen wird. Dies wird hier geschützt
#pragma once
//Zwei notwendige Bibliotheken werden eingebunden, um die serielle Kommunikation und die Verwendung von Strings zu ermöglichen.
#include <windows.h>
#include <string>

class SerialPort {
//Befehle, welche die Benutzeroberfläche aufrufen kann.
public:
    //Konstruktor und Destruktor. SerialPort wird automatisch aufgerufen. Der Destruktor wird aufgerufen, wenn das Objekt geschlossen wird.
    SerialPort();
    ~SerialPort();

    //connect versucht die verbindung aufzubauen. Das bool gibt ein true zurück, wenn das erfolgreich war.
    //disconnect trennt die Verbindung zum Gerät.
    //sendString sendet eine Nachricht an das Gerät.
    //readString liest eine Nachricht vom Gerät und gibt sie als String zurück.
    //isConnected gibt zurück, ob die Verbindung zum Gerät besteht oder nicht.
    bool connect(const char* portName);
    void disconnect();
    void sendString(std::string message);
    std::string readString();
    bool isConnected();

//private Variablen, welche die Verbindung zum Gerät und den Verbindungsstatus speichern. Diese Variablen sind nur innerhalb der Klasse SerialPort zugänglich und können nicht von außen verändert werden.
private:
    //Handle ist die Verbindung zum Gerät und Windows. 
    //connected_status speichert, ob die Verbindung zum Gerät besteht oder nicht.
    HANDLE hSerial;
    bool connected_status;
};