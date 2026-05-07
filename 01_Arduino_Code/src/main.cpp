#include <Arduino.h>

void setup() {
  Serial.begin(9600);
}

void loop() {
  // Warteschleife, bis Daten vom PC ankommen
  if (Serial.available() > 0) {
    
    //Der String input wird erstellt und mit der gesamten Zeile aus der Eingabe gefüllt.
    String input = Serial.readStringUntil('\n');
    // Zur Sicherheit werden überflüssige Leerzeichen entfernt um Formatierungsfehler zu vermeiden.
    input.trim(); 
    
    //Variablen für die Berechnungen werden erstellt. result speichert das Ergebnis, operation das Rechenzeichen und opIndex die Position des Rechenzeichens im String.
    if (input.length() > 0) {
      float result = 0.0;
      char operation = 0;
      int opIndex = -1;

      // Die zuvor erstellten Variablen Operation und opIndex werden hier gefüllt. Hierfür wird input gelesen und gefiltert
      if (input.indexOf('+') > 0) { operation = '+'; opIndex = input.indexOf('+'); }
      else if (input.indexOf('-') > 0) { operation = '-'; opIndex = input.indexOf('-'); }
      else if (input.indexOf('*') > 0) { operation = '*'; opIndex = input.indexOf('*'); }
      else if (input.indexOf('/') > 0) { operation = '/'; opIndex = input.indexOf('/'); }

      //  Zahlen vor und nach dem Rechenzeichen trennen.
      if (opIndex > 0) {
        float num1 = input.substring(0, opIndex).toFloat();
        float num2 = input.substring(opIndex + 1).toFloat();
        
        //Berechnungen werden je nach Rechenzeichen durchgeführt. Bei Division wird zusätzlich geprüft, ob der Nenner 0 ist, Fehler wird ausgegeben
        switch (operation) {
          case '+': result = num1 + num2; break;
          case '-': result = num1 - num2; break;
          case '*': result = num1 * num2; break;
          case '/': 
            if (num2 != 0) { result = num1 / num2; } 
            else { Serial.println("Error"); return; }
            break;
        }

        // Ergebnis oder Fehler wird ausgegeben
        Serial.println(result);
        
      } else {
        Serial.println("Format-Error");
      }
    }
  }
}