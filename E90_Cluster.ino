#include "canbus.h"
#include "keyslot.h"
#include "airbag_counter.h"

// Timer für den 100ms Takt (Tacho-Wecker)
unsigned long last100msTime = 0;
const unsigned long interval100ms = 100;

// Timer für den 200ms Takt (Airbag & Gurt)
unsigned long last200msTime = 0;
const unsigned long interval200ms = 200;

void setup() {
  Serial.begin(115200);
  mcp2515.reset();
  mcp2515.setBitrate(CAN_100KBPS, MCP_8MHZ);
  mcp2515.setNormalMode();
  schlossSetup();
}

void loop() {
  unsigned long currentMillis = millis();

  // Schloss-Befehle permanent in Echtzeit auswerten
  schlossVerarbeiten();

  // --- 100ms TIMER BLOCK ---
  if (currentMillis - last100msTime >= interval100ms) {
    last100msTime = currentMillis;

    clusterWake();
  }

  // --- 200ms TIMER BLOCK ---
  if (currentMillis - last200msTime >= interval200ms) {
    last200msTime = currentMillis;

    sendeAirbagCounter();
  }
}