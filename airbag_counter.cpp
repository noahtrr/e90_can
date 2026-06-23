#include "airbag_counter.h"
#include "canbus.h" 

const uint16_t AIRBAG_CAN_ID = 0x0D7;
const uint8_t AIRBAG_DLC = 2; 

struct can_frame airbagFrame;
uint8_t airbagCounter = 0;

void sendeAirbagCounter() {
    // CAN-Frame vorbereiten
    airbagFrame.can_id = AIRBAG_CAN_ID;
    airbagFrame.can_dlc = AIRBAG_DLC;
    
    // Byte[0]: Zähler von 0 bis 254
    airbagFrame.data[0] = airbagCounter;
    airbagFrame.data[1] = 0x00; // Füllbyte/Status

    // CAN-Nachricht absenden
    mcp2515.sendMessage(&airbagFrame);

    // Zähler für den nächsten Aufruf erhöhen
    airbagCounter++;
    if (airbagCounter > 254) {
        airbagCounter = 0; // Zurücksetzen bei Erreichen von 255
    }
}