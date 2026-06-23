#include "keyslot.h"

void schlossSetup() {
    // Pins als Ausgang definieren
    pinMode(PIN_IN1, OUTPUT);
    pinMode(PIN_IN2, OUTPUT);
    
    // Im Ruhezustand alles auf LOW (stromlos und sicher)
    digitalWrite(PIN_IN1, LOW);
    digitalWrite(PIN_IN2, LOW);
}

void schlossSchliessen() {
    Serial.println("Befehl ausgefuehrt: SCHLIESSEN...");
    
    digitalWrite(PIN_IN1, HIGH); // +12V an Pin 13, GND an Pin 14
    digitalWrite(PIN_IN2, LOW);
    delay(IMPULS_DAUER);         // Kurzer Impuls
    
    digitalWrite(PIN_IN1, LOW);  // Sofort wieder komplett abschalten
    digitalWrite(PIN_IN2, LOW);
    Serial.println("Zustand: Verriegelt. Spule wieder stromlos.");
}

void schlossOeffnen() {
    Serial.println("Befehl ausgefuehrt: OEFFNEN...");
    
    digitalWrite(PIN_IN1, LOW);  // GND an Pin 13, +12V an Pin 14
    digitalWrite(PIN_IN2, HIGH); // Polaritaet umgedreht
    delay(IMPULS_DAUER);         // Kurzer Impuls
    
    digitalWrite(PIN_IN1, LOW);  // Sofort wieder komplett abschalten
    digitalWrite(PIN_IN2, LOW);
    Serial.println("Zustand: Offen. Spule wieder stromlos.");
}

void schlossVerarbeiten() {
    if (Serial.available() > 0) {
        String befehl = Serial.readStringUntil('\n');
        befehl.trim(); 
        
        if (befehl.equalsIgnoreCase("close")) {
            schlossSchliessen();
        } 
        else if (befehl.equalsIgnoreCase("open")) {
            schlossOeffnen();
        } 
        else if (befehl.length() > 0) {
            Serial.print("Unbekannter Befehl: '");
            Serial.print(befehl);
            Serial.println("' - Bitte nutze nur 'open' oder 'close'.");
        }
    }
}