//sender

const int SSpin = 10;
const int MOSIpin = 11;
const int MISOpin = 12;
const int SCKpin = 13;

byte sendData = 80; // Value we are going to send
byte slaveData = 0; // Where we will store the value sent by the slave


void setup(){
  digitalWrite(SSpin, HIGH);
  pinMode(SSpin, OUTPUT);
  pinMode(MOSIpin, OUTPUT);
  pinMode(MISOpin, INPUT);
  pinMode(SCKpin, OUTPUT);
}

void loop(){
  digitalWrite(SSpin, LOW); // SS LOW
  slaveData=bitBangData(sendData); // Transmit Data
  digitalWrite(SSpin, HIGH);  // SS High again
}

byte bitBangData(byte _send){
  byte _receive = 0;
  for(int i=0; i<8; i++){ //8-Bit Data
    digitalWrite(MOSIpin, bitRead(_send, i)); //Set MOSI
    digitalWrite(SCKpin, HIGH); //SCK High
    bitWrite(_receive, i, digitalRead(MISOpin)); //Capture MISO
    digitalWrite(SCKpin, LOW); //SCK LOW
  }
  return _receive; //Return the received data
}
