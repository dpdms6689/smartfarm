#include <Arduino.h>
#include "BluetoothSerial.h"
BluetoothSerial SerialBT;
char rData[32] = { 0x00, };
int rPos = 0;
  
void setup() {
  ledcAttachPin(13, 1);
  ledcSetup(1, 12000, 8);
  ledcWrite(1, 255);  
  SerialBT.begin("M#0129"); //Bluetooth device name
 }

void loop() {
    while(0 < SerialBT.available()) {
      char ch = SerialBT.read();
      rData[rPos] = ch;
      rPos += 1;
       
      if(ch == '\n'){        
       if(memcmp(rData, "C_A-", 4) == 0) {
          if(rData[4] == 'a') ledcWrite(1, 0);
          if(rData[4] == 'b') ledcWrite(1, 255);
         }
      rPos = 0;
      memset(rData, 0x00, 32);
      break;
      }
      delay(10);
    }
  delay(20);
}
