//Slave
#include <Wire.h>
#define SLAVE 4
byte count='A';
void setup(){
  Wire.begin(SLAVE);
  Wire.onRequest(sendToMaster);
}
void loop(){}
void sendToMaster(){
  Wire.write(++count);
  if(count>='z'){
    count='A';
  }
}
