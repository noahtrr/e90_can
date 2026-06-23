#ifndef KEYSLOT_H
#define KEYSLOT_H
#include <Arduino.h>

// Pin-Definitionen für die L298N H-Brücke
const int PIN_IN1 = 4; // Verbunden mit D4 am Nano
const int PIN_IN2 = 5; // Verbunden mit D5 am Nano

// Zeitdauer des Stromstoßes in Millisekunden
const int IMPULS_DAUER = 150; 

// Initialisiert die Pins für das Schloss
void schlossSetup();

// Verarbeitet serielle Befehle und steuert das Schloss
void schlossVerarbeiten();

// Funktionen für die Hardware-Ansteuerung
void schlossSchliessen();
void schlossOeffnen();
#endif