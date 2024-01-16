int pinBit1 = 16;
int pinBit2 = 5;
int pinBit3 = 4;
int pinBit4 = 0;
int pinBit5 = 2;
int pinBit6 = 14;
int pinBit7 = 12; 
int bit1 = 0;
int bit2 = 0;
int bit3 = 0;
int bit4 = 0;
int bit5 = 0;
int bit6 = 0;
int bit7 = 0;
int sensorPin = A0;
int sensorValue = 0;
int minGemessenerWert = 0;
int maxGemessenerWert = 550;
int minSkalierterWert = 0;
int maxSkalierterWert = 100;
int skalierterWert =0;

void setup() {
  Serial.begin(9600);
  pinMode(pinBit1, OUTPUT);
  pinMode(pinBit2, OUTPUT);
  pinMode(pinBit3, OUTPUT);
  pinMode(pinBit4, OUTPUT);
  pinMode(pinBit5, OUTPUT);
  pinMode(pinBit6, OUTPUT);
  pinMode(pinBit7, OUTPUT);
}

void loop() {
  // Zahl einlesen
  readSens();

  // Aufteilen in 7 Bits
   bit7 = (skalierterWert >> 6) & 1;
   bit6 = (skalierterWert >> 5) & 1;
   bit5 = (skalierterWert >> 4) & 1;
   bit4 = (skalierterWert >> 3) & 1;
   bit3 = (skalierterWert >> 2) & 1;
   bit2 = (skalierterWert >> 1) & 1;
   bit1 = skalierterWert & 1;

  digitalWrite(pinBit1, bit1);
  digitalWrite(pinBit2, bit2);
  digitalWrite(pinBit3, bit3);
  digitalWrite(pinBit4, bit4);
  digitalWrite(pinBit5, bit5);
  digitalWrite(pinBit6, bit6);
  digitalWrite(pinBit7, bit7);

  Serial.print("Bit 7: ");
  Serial.println(bit7);
  Serial.print("Bit 6: ");
  Serial.println(bit6);
  Serial.print("Bit 5: ");
  Serial.println(bit5);
  Serial.print("Bit 4: ");
  Serial.println(bit4);
  Serial.print("Bit 3: ");
  Serial.println(bit3);
  Serial.print("Bit 2: ");
  Serial.println(bit2);
  Serial.print("Bit 1: ");
  Serial.println(bit1);
  delay(500);
}




void readSens()//Read sensor value and scale 0-100
{
    sensorValue = analogRead(sensorPin);
    Serial.print("Moisture = " );
    Serial.println(sensorValue);
    skalierterWert = map(sensorValue, minGemessenerWert, maxGemessenerWert, minSkalierterWert, maxSkalierterWert);
    Serial.print("skalierter Wert = " );
    Serial.println(skalierterWert);
}