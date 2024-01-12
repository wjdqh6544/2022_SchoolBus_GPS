//master
#include <SPI.h>
void setup(void)
{
  SPI.begin();
  digitalWrite(SS, HIGH);
  SPI.setClockDivider(SPI_CLOCK_DIV128);
  Serial.begin(9600);
}
void loop(void){
  digitalWrite(SS, LOW);
  long A=SPI.transfer(0);
  delay(1000);
  digitalWrite(SS, HIGH);
  Serial.println(A);
}
