#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>

//const char* ssid = "Art2.4GHz";
//const char* password = "11223344";
String ssid = "Art2.4GHz";
String passwd = "11223344";

TinyGPSPlus gps;
SoftwareSerial gpsSerial(D1,D2); // RX, TX
char buffer[100];

void connectGPS(){
  if (gps.location.isUpdated()){
    double lat=gps.location.lat();
    double lng=gps.location.lng();
    double altitude = gps.altitude.meters();
    int year = gps.date.year();
    int month = gps.date.month();
    int day = gps.date.day();
    int hour = gps.time.hour();
    int minute = gps.time.minute();
    int second = gps.time.second();
    snprintf(buffer, sizeof(buffer),
                 "Latitude: %.8f, Longitude: %.8f, Altitude: %.2f m, "
                 "Date/Time: %d-%02d-%02d %02d:%02d:%02d",
                 lat, lng, altitude, year, month, day, hour, minute, second);
        Serial.println(buffer);   }  }

void connectWiFi(){
  Serial.println();
  Serial.println("Trying to Connect Wi-Fi...");
  Serial.print("Wi-Fi SSID Name: ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, passwd);
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");  }
  Serial.println("");
  Serial.println("WiFi Connected Successfully!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void setup(){
  Serial.begin(9600);
  gpsSerial.begin(9600);
  connectWiFi();  }
  
void loop(){
  while (gpsSerial.available()>0){
    if (gps.encode(gpsSerial.read())){
      connectGPS();
      delay(500); }}}
