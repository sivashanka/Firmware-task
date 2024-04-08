#define EEPROM_START_ADDRESS 0  
#define EEPROM_TOTAL_SIZE 1024     

void writeByteToEEPROM(int memoryAddress, byte dataByte) {
  if (memoryAddress >= EEPROM_START_ADDRESS && memoryAddress < EEPROM_START_ADDRESS + EEPROM_TOTAL_SIZE) {
    while (EECR & (1 << EEPE))
      ;
    EEAR = memoryAddress;
    EEDR = dataByte;
    EECR |= (1 << EEMPE);
    EECR |= (1 << EEPE);
  }
}

void setup() {}

void loop() {
  
  String receivedData = ""; 
  int dataLength = receivedData.length();
  int memoryAddress = EEPROM_START_ADDRESS;
  for (int i = 0; i < dataLength; i++) {
    writeByteToEEPROM(memoryAddress + i, receivedData[i]);
  }
}
