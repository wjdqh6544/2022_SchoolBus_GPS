#include <ESP8266WiFi.h>

const char* ssid = "YKBUSGPS";
const char* password = "Yk.GPS!22@";

void setup(){
  Serial.begin(115200);
  Serial.println();
  Serial.print("Connecting to: ");
  Serial.print(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi Connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}
void loop(){
}
