#include <ESP8266WiFi.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

TinyGPSPlus GPS; SoftwareSerial GPSSerial(D3, D4); IPAddress server_ip(121, 183, 4, 176);
char dbuser[] = "ykbus"; char dbpasswd[] = "dudrhkdrh.qjtm@2022#";
char ssid[] = "YKBUSGPS"; char passwd[] = "Yk.GPS!22@";

WiFiClient client; MySQL_Connection conn((Client *)&client); MySQL_Cursor* cursor;

void connectWiFi() {
  WiFi.mode(WIFI_STA); WiFi.begin(ssid, passwd);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }
}

void connectDB() {
  if (conn.connect(server_ip, 3306, dbuser, dbpasswd)) {
    delay(1000);
  }
  else {
    conn.close();
  }
  cursor = new MySQL_Cursor(&conn);
  delay(1000);
}

void insertDB() {
  String Latitude = String(GPS.location.lat(), 8);  String Longitude = String(GPS.location.lng(), 8);
  String Year = String(GPS.date.year()); String Month = String(GPS.date.month()); String Day = String(GPS.date.day());
  String Hour = String(GPS.time.hour() + 9); String Minute = String(GPS.time.minute()); String Second = String(GPS.time.second());
  String SQL = "INSERT INTO bus.bus (Latitude, Longitude, Year, Month, Day, Hour, Minute, Second) VALUES (" + Latitude + ", " + Longitude + ", " + Year + ", " + Month + ", " + Day + ", " + Hour + ", " + Minute + ", " + Second + ")";
  const char* INSERT_SQL = SQL.c_str();
  if (conn.connected()) {
    cursor->execute(INSERT_SQL);
    delay(500);
  }
}

void setup() {
  GPSSerial.begin(9600);
  connectWiFi(); connectDB();
}

void loop() {
  while (GPSSerial.available() > 0) {
    if (GPS.encode(GPSSerial.read())) {
      insertDB();
      delay(4500);
    }
  }
}
