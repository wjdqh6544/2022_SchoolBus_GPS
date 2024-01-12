// Master
#include <Wire.h>
#define SLAVE 4
void setup(){
  Wire.begin();
  Serial.begin(9600);
  Serial.println("I2C");
}
void loop(){
  requestEvent();
  delay(1000);
}
void requestEvent(){
  Wire.requestFrom(SLAVE,1);
  char c=Wire.read();
  Serial.println(c);
}
