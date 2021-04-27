#include <mcp2515.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

struct can_frame messageBuffer;
MCP2515 mcp2515(10);

float tensao, corrente;

void setup() {


  lcd.init();
  lcd.backlight();
  lcd.clear();

  mcp2515.reset();
  mcp2515.setBitrate(CAN_125KBPS);
  mcp2515.setNormalMode();
}

void loop() {
  if (mcp2515.readMessage(&messageBuffer) == MCP2515::ERROR_OK){
    if(messageBuffer.can_id = 0x186555f4){
      tensao = ((messageBuffer.data[0] + messageBuffer.data[1] << 8) / 10);
      corrente = ((messageBuffer.data[2] + messageBuffer.data[3] << 8) / 10);
      lcd.setCursor(0, 0);
      lcd.print("V: ");
      lcd.setCursor(3, 0);
      lcd.print(tensao);
      lcd.print("V");
      lcd.setCursor(0, 1);
      lcd.print("C: ");
      lcd.setCursor(3, 1);
      lcd.print(corrente);
      lcd.print("A");   
    }
    delay(1000);
  }
}
