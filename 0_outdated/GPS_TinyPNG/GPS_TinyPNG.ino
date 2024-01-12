#include <SoftwareSerial.h>
#include <TinyGPS.h>

long lat,lon;
SoftwareSerial gpsSerial(8,9); // TX, RX
TinyGPS gps;

void setup() {
Serial.begin(9600);
Serial.println("Start GPS... ");
gpsSerial.begin(9600);
}

void loop() {
while(gpsSerial.available()){ // check for gps data
if(gps.encode(gpsSerial.read())){ // encode gps data
gps.get_position(&lat,&lon); // get latitude and longitude
// display position
Serial.print("Position: ");
Serial.print("lat: ");Serial.print(lat);Serial.print(" ");// print latitude
Serial.print("lon: ");Serial.println(lon); // print longitude
}}}
