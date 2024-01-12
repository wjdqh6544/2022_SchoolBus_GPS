#include <ESP8266wifi.h>
#include <SoftwareSerial.h>
SoftwareSerial ESP_8266(2,3);
SoftwareSerial NEO_6M(12,13); //TX, RX;
void setup(){
  Serial.begin(9600);
  ESP_8266.begin(9600);
  WiFi.init(&Serial_GPS);
  if (WiFi.status()==WL_NO_SHIELD){
    Serial.println("Communication with Wi-Fi Module Failed!");
    while(true);  }
  while (status()!=WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(Arduino);
    status = WiFi.begin(Arduino,arduinotest);
    delay(10000);
  }
  Serial.println("Connected to Wi-Fi successfully!");
  NEP_6m.begin(9600);
}

void loop(){
  NEO_6M.listen();
  if (NEO_6M.available()){
    Serial.write(NEO_6M.read()); }
  if (ESP_8266.available()){
    Serial.write(ESP_8266.read()); }  
}
