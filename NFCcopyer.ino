#include <SPI.h>
#include <MFRC522.h>

/*----------------------
RFID-RC522     Arduino
------------------------
3.3V           3.3V
GND            GND
RST            D9
SDA (SS)       D10
SCK            D13
MOSI           D11
MISO           D12
IRQ            -
----------------------*/

#define RST_PIN         9          // Configurable, see typical pin layout above
#define SS_PIN          10         // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

void setup() {
  Serial.begin(115200);  // Initialize serial communications with the PC
  while (!Serial);    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin();       // Init SPI bus
  mfrc522.PCD_Init(); // Init MFRC522 card
  Serial.println("Scan your RFID/NFC card...");
}

void loop() {
  // Look for new cards
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  // Dump debug info about the card; PICC_HaltA() is automatically called
  Serial.println("**Card Detected:**");
  mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
  Serial.println();
  delay(1000); // Wait for 1 second before continuing
}
