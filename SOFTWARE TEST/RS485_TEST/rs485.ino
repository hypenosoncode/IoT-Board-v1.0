#include <ModbusRTU.h> // Library: https://github.com/emelianov/modbus-esp8266
#include <SoftwareSerial.h>
#include "IntToFloat.h"

ModbusRTU mb;
SoftwareSerial S(RX, TX);

int DE_RE = 2; 
int RX = 16;
int TX = 4;

uint16_t Mread0[2]; // Starting Read Data

bool cbWrite(Modbus::ResultCode event, uint16_t transactionId, void* data) 
{
  Serial.printf_P("Request Response: 0x%02X, Memory: %d\n", event, ESP.getFreeHeap());
  return true;
}

void setup() 
{
  Serial.begin(115200);
  S.begin(9600, SWSERIAL_8N1);
  mb.begin(&S, DE_RE); //RS485
  mb.master();
  Serial.println();
  Serial.println(sizeof(Mread0));
}
void loop()
{
  if (!mb.slave()) 
  {
    mb.readHreg(1, 1770, Mread0, 2 , cbWrite);  // (SlaveID, Start Address, Buffer, Length of Data, Modbus Function) ** Energy Meter Parameters
    Serial.println(InttoFloat(Mread0[0], Mread0[1])); // IN: 01-16bit, 02-16bit *** OUT: 32 bit Float
  }
  mb.task();
  delay(1000);
  yield();
}
