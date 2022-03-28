#include "EEPROM.h"
byte eprombyte[4] = {0,0,0,0};
#define EEPROM_SIZE 64
//int head = 300;

void readEEPROM()
{
 for (int i = 0; i < 4; i++)
  {
    eprombyte[i]=(byte(EEPROM.read(i)));
    Serial.print(String(eprombyte[i])+", ");Serial.println("");
  }
  
}

void writeEEPROM()
{
  eprombyte[0] = play;
  eprombyte[1] = head/256;  // highbyte
  eprombyte[2] = head%256;  // lowbyte
  eprombyte[3] = 0;         // noch nicht benutzt
  
  for (int i = 0; i < 4; i++)
  {
    Serial.print(String(eprombyte[i])+", ");Serial.println("");
    EEPROM.write(i, eprombyte[i]);
  }
  EEPROM.commit();
}

void eprom_init()
{
  readEEPROM();
  if (eprombyte[0] ==1)
  {
    play = true; // Stürmer soll sofort loslegen
    head = eprombyte[1]*265+eprombyte[2];  //  hightbyte,lowbyte
    // eprombyte[3] wird noch nicht benutzt
  }
}


void eepromstuff() 
{
  delay(2000);
  head++;
  writeEEPROM();
  delay(500);
  readEEPROM();
}
