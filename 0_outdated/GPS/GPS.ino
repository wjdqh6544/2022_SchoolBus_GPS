#include <SoftwareSerial.h>
SoftwareSerial GPS(2,3); //TX, RX
void setup(){
  Serial.begin(9600);
  GPS.begin(9600);
}
void loop(){
  if(GPS.available()){
    Serial.write(GPS.read());
  }
}
