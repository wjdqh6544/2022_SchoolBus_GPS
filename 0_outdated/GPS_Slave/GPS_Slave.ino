#include <SoftwareSerial.h>
#include <TinyGPS.h>
#include <SPI.h>
SoftwareSerial GPS_Serial(8,9); //TX, RX
TinyGPS GPS;
long lat,lon;
void setup(){
  pinMode(MISO,OUTPUT);
  pinMode(MOSI,INPUT);
  pinMode(SCK,INPUT);
  pinMode(SS,INPUT);
  SPCR |= _BV(SPE);
  SPCR &= ~_BV(MSTR);
  SPCR |= _BV(SPIE);
  SPI.setClockDivider(SPI_CLOCK_DIV128);
  Serial.begin(9600);
  Serial.println("Start GPS... ");
  GPS_Serial.begin(9600);
}

ISR(SPI_STC_vect){
  long Confirm=SPDR;
  SPDR=lat;
}

void loop(){
 while(GPS_Serial.available()){ // check for gps data
if(GPS.encode(GPS_Serial.read())){ // encode gps data
GPS.get_position(&lat,&lon); // get latitude and longitude
// display position
Serial.print("Position: ");
Serial.print("lat: ");Serial.print(lat);Serial.print(" ");// print latitude
Serial.print("lon: ");Serial.println(lon); // print longitude
}}}
