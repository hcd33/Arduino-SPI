////////////////////////////////////////////////////////
//  SPI_Master
//
//  Date        : 23.11.2021
//  Author      : Christian Diekmann
//  Chip        : ATmega328P
//
///////////////////////////////////////////////////////

/*
   Features:
   ~ Get input value a or b from the serial monitor
   ~ Send value via SPI to slave MCU
*/

#include <SPI.h>

void setup (void)
{
  Serial.begin (115200);
  Serial.println("MASTER");

  digitalWrite(SS, HIGH);  // ensure SS stays high for now

  // Put SCK, MOSI, SS pins into output mode
  // also put SCK, MOSI into LOW state, and SS into HIGH state.
  // Then put SPI hardware into Master mode and turn SPI on
  SPI.begin ();

  // Slow down the master a bit
  SPI.setClockDivider(SPI_CLOCK_DIV8);
}


void loop (void)
{
  Serial.print("Input a or b: ");
  while (Serial.available() == 0) {}
  char value = Serial.read();


  if (value == 'a' || value == 'b')
  {
    Serial.println(value);
    digitalWrite(SS, LOW);    // enable Slave Select

    SPI.transfer(value);

    digitalWrite(SS, HIGH);  // disable Slave Select
  }
  else{
    Serial.println("Invalid input");
  }

}
