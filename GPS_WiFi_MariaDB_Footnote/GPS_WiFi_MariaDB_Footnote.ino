#include <ESP8266WiFi.h>           // Use this for WiFi instead of Ethernet
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

TinyGPSPlus GPS;
SoftwareSerial GPSSerial(D1, D2); // RX, TX
IPAddress server_ip(121, 183, 4, 176); // IP of the MySQL *server* here
char dbuser[] = "ykbus";              // MySQL user login username
char dbpasswd[] = "dudrhkdrh.qjtm@2022#";        // MySQL user login password

char ssid[] = "Art2.4GHz";         // your SSID
char passwd[] = "11223344";     // your SSID Password

WiFiClient client;                 // Use this for WiFi instead of EthernetClient
MySQL_Connection conn((Client *)&client);
MySQL_Cursor* cursor;

void connectWiFi() {
  while (!Serial); // wait for serial port to connect. Needed for Leonardo only
  Serial.print("\nTrying to Connect Wi-Fi...\n");
  delay(500);
  Serial.printf("SSID Name: %s", ssid);
  WiFi.mode(WIFI_STA); WiFi.begin(ssid, passwd);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n\nConnected to Wi-Fi Successfully!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void connectDB() {
  Serial.print("\nTrying to connect DB Server...\n");
  if (conn.connect(server_ip, 3306, dbuser, dbpasswd)) {
    delay(1000);
    Serial.println("\nConnected to DB Server Successfully!\n");
  }
  else {
    Serial.println("Failed to connect DB Server...");
    conn.close();
  }
  cursor = new MySQL_Cursor(&conn);
  delay(1000);
}

void insertDB() {
  double lat = GPS.location.lat();
  double lng = GPS.location.lng();
  int year = GPS.date.year();
  int month = GPS.date.month();
  int day = GPS.date.day();
  int hour = GPS.time.hour();
  int minute = GPS.time.minute();
  int second = GPS.time.second();
  Serial.print("\n\n\n*****\nLat: "); Serial.println(lat);
  Serial.print("Lng: "); Serial.println(lng);
  Serial.print("Year: "); Serial.println(year);
  Serial.print("Month: "); Serial.println(month);
  Serial.print("Second: "); Serial.println(second);
  Serial.println("***** \n");

  String Latitude = String(lat, 8);  String Longitude = String(lng, 8);
  String Year = String(year); String Month = String(month); String Day = String(day);
  String Hour = String(hour+9); String Minute = String(minute); String Second = String(second);
  Serial.print("Latitude: "); Serial.println(Latitude);
  Serial.print("Longitude: "); Serial.println(Longitude);
  String SQL = "INSERT INTO bus.bus (Latitude, Longitude, Year, Month, Day, Hour, Minute, Second) VALUES (" + Latitude + ", " + Longitude + ", " + Year + ", " + Month + ", " + Day + ", " + Hour + ", " + Minute + ", " + Second + ")";
  const char* INSERT_SQL = SQL.c_str();
  if (conn.connected()) {
    cursor->execute(INSERT_SQL);
    delay(5000);
  }
}

void setup() {
  Serial.begin(9600);
  GPSSerial.begin(9600);
  connectWiFi();
  connectDB();
}

void loop() {
  while (GPSSerial.available() > 0) {
    if (GPS.encode(GPSSerial.read())) {
      insertDB();
      delay(500);
    }
  }
}
