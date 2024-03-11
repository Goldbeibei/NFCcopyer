// 包含SPI和MFRC522庫
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

#define RST_PIN 9           // 可配置，請參考典型引腳配置圖
#define SS_PIN 10          // 可配置，請參考典型引腳配置圖

MFRC522 mfrc522(SS_PIN, RST_PIN);  // 創建MFRC522實例

void setup() {
  Serial.begin(115200);     // 初始化與電腦的序列通信
  while (!Serial);        // 如果沒有打開序列埠，則不執行任何操作（適用於基於ATMEGA32U4的Arduino）
  SPI.begin();            // 初始化SPI總線
  mfrc522.PCD_Init();     // 初始化MFRC522卡
  Serial.println("將您的RFID/NFC卡靠近感應器...");
}

void loop() {
  // 尋找新卡
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // 選擇其中一張卡
  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  // 在序列監視器上顯示UID
  Serial.print("卡UID：");
  dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size);
  Serial.println();
  mfrc522.PICC_HaltA();
}

// 將位元組陣列轉存為十六進位格式
void dump_byte_array(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}
