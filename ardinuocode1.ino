#define EEPROM_START_ADDR 0  
#define EEPROM_SIZE 1024     

void writeByteToEEPROM(int address, byte data) {
  if (address >= EEPROM_START_ADDR && address < EEPROM_START_ADDR + EEPROM_SIZE) {
    while (EECR & (1 << EEPE))
      ;
    EEAR = address;
    EEDR = data;
    EECR |= (1 << EEMPE);
    EECR |= (1 << EEPE);
  }
}

void setup() {}

void loop() {
  // Simulated received string
  String receivedString = ""; 
  int strLength = receivedString.length();
  int address = EEPROM_START_ADDR;
  for (int i = 0; i < strLength; i++) {
    writeByteToEEPROM(address + i, receivedString[i]);
  }
}
