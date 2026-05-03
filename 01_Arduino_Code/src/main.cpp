#include <Arduino.h>

void setup() {
  Serial.begin(9600);
}

void loop() {
  // 1. Warten, bis der PC eine Nachricht schickt
  if (Serial.available() > 0) {
    
    // 2. Die komplette Zeile einlesen
    String input = Serial.readStringUntil('\n');
    // Versteckte Leerzeichen werden entfernen
    input.trim(); 
    
    if (input.length() > 0) {
      float result = 0.0;
      char operation = 0;
      int opIndex = -1;

      // 3. Welches Rechenzeichen hat der PC geschickt?
      if (input.indexOf('+') > 0) { operation = '+'; opIndex = input.indexOf('+'); }
      else if (input.indexOf('-') > 0) { operation = '-'; opIndex = input.indexOf('-'); }
      else if (input.indexOf('*') > 0) { operation = '*'; opIndex = input.indexOf('*'); }
      else if (input.indexOf('/') > 0) { operation = '/'; opIndex = input.indexOf('/'); }

      // 4. Wenn ein Rechenzeichen gefunden wurde: Zahlen trennen und rechnen
      if (opIndex > 0) {
        float num1 = input.substring(0, opIndex).toFloat();
        float num2 = input.substring(opIndex + 1).toFloat();

        switch (operation) {
          case '+': result = num1 + num2; break;
          case '-': result = num1 - num2; break;
          case '*': result = num1 * num2; break;
          case '/': 
            if (num2 != 0) { result = num1 / num2; } 
            else { Serial.println("Error"); return; }
            break;
        }

        // 5. Das Ergebnis zurückfunken!
        Serial.println(result);
        
      } else {
        Serial.println("Format-Error");
      }
    }
  }
}