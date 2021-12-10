////////////////////////////////////////////////////////
//  SPI_Slave
//
//  Date        : 23.11.2021
//  Author      : Christian Diekmann
//  Chip        : ATmega328P
//
///////////////////////////////////////////////////////

/**
   Features:
   ~ Get ascii value a or b from SPI master MCU
   ~ Toggle LED on/off
*/

#include <SPI.h>
volatile boolean flag = false;;
volatile byte c;

void setup (void)
{
  Serial.begin (115200);
  Serial.println("SLAVE");
  SPCR |= bit (SPE);      // turn on SPI in slave mode
  pinMode(MISO, OUTPUT);  // have to send on master in, *slave out*
  SPI.attachInterrupt(); // enable interrupt
  pinMode(LED_BUILTIN, OUTPUT);
}

// SPI interrupt routine
ISR (SPI_STC_vect)
{
   c = SPDR;  // grab byte from SPI Data Register
   flag = true;
}

void loop (void)
{
  if (flag)
  {
    Serial.println (c);
    if(c == 97){
      Serial.println ("LED ON");
      digitalWrite(LED_BUILTIN, HIGH);
    }
    if(c == 98){
      Serial.println ("LED OFF");
      digitalWrite(LED_BUILTIN, LOW);
    }
    flag = false;
  }
}
