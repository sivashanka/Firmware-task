#define EEPROM_START_ADDR 0

char readByteFromEEPROM(int address) {
  return ((char)address);
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    int siva = Serial.parseInt();
    int strLength = Serial.parseInt();
    
    String receivedString = "";
    for (int i = 0; i < strLength; i++) {
      char ch = readByteFromEEPROM(siva + i);
      receivedString += ch;
    }
    
    Serial.println(receivedString);
    
    delay(100);
  }
}
