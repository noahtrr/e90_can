#include "canbus.h"

MCP2515 mcp2515(10); 

struct can_frame cluserWakeFrame;

void clusterWake() {
  static unsigned long lastIncrementTime = 0;
  static uint8_t checksum = 0xFE;
  
  unsigned long currentMillis = millis();

  if (currentMillis - lastIncrementTime >= 1400) {
    lastIncrementTime = currentMillis;
    checksum++;
  }

  // Set up the frame data
  cluserWakeFrame.can_id = 0x130;
  cluserWakeFrame.can_dlc = 5;
  cluserWakeFrame.data[0] = 0x45;
  cluserWakeFrame.data[1] = 0x40;
  cluserWakeFrame.data[2] = 0x21;
  cluserWakeFrame.data[3] = 0x8F;
  cluserWakeFrame.data[4] = checksum;

  // Send the message
  mcp2515.sendMessage(&cluserWakeFrame);
}