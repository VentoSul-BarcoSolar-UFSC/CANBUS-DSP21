#include <can.h>
#include <mcp2515.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

struct can_frame canMsg1;
MCP2515 mcp2515(10);

float tensao, corrente1, corrente2;

void setup() {
  canMsg1.can_id  = 0x186555f4;
  canMsg1.can_dlc = 8;

  canMsg1.data[2] = 0x32;
  canMsg1.data[3] = 0xFA;
  canMsg1.data[4] = 0x26;
  canMsg1.data[5] = 0x8E;


  lcd.init();
  lcd.backlight();
  lcd.clear();


  while (!Serial);
  Serial.begin(115200);

  mcp2515.reset();
  mcp2515.setBitrate(CAN_125KBPS);
  mcp2515.setNormalMode();

  Serial.println("Example: Write to CAN");
}

void loop() {
  if (canMsg1.can_id == 0x186555f4) {
    mcp2515.readMessage(&canMsg1);
    tensao = ((canMsg1.data[0] + canMsg1.data[1] << 8) / 10);
    corrente1 = ((canMsg1.data[2] + canMsg1.data[3] << 8) / 10);
    corrente2 = ((canMsg1.data[4] + canMsg1.data[5] << 8) / 10);

    lcd.setCursor(0, 0);
    lcd.print("V: ");
    lcd.setCursor(3, 0);
    lcd.print(tensao);
    lcd.setCursor(7, 0);
    lcd.print("V");
    lcd.setCursor(0, 1);
    lcd.print("C1: ");
    lcd.setCursor(3, 1);
    lcd.print(corrente1);
    lcd.setCursor(9, 1);
    lcd.print("A");
    lcd.setCursor(0, 1);
    lcd.print("C2: ");
    lcd.setCursor(11, 1);
    lcd.print(corrente2);
    lcd.setCursor(16, 1);
    lcd.print("A");
    delay(1000);

  }
}