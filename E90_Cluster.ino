#include "canbus.h"
#include "keyslot.h"

unsigned long last100msTime = 0;
const unsigned long interval100ms = 100;

void setup() {
  Serial.begin(115200);
  mcp2515.reset();
  mcp2515.setBitrate(CAN_100KBPS, MCP_8MHZ);
  mcp2515.setNormalMode();
  schlossSetup();
}

void loop() {
  unsigned long currentMillis = millis();

  schlossVerarbeiten();

  if (currentMillis - last100msTime >= interval100ms) {
    last100msTime = currentMillis;

    clusterWake();
  }
}