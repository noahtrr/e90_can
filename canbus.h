#ifndef CANBUS_H
#define CANBUS_H
#include <SPI.h>
#include <mcp2515.h>

extern MCP2515 mcp2515; 

void clusterWake();

#endif