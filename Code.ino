#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
#define buzzer_pin A0

int count = 0;
String acceptedUIDs[] = {"3C B6 18 49" };  //Thêm các UID khác nếu cần: "53 18 7F 06"
Servo servo;
LiquidCrystal_I2C lcd(0x27, 16, 2);
MFRC522 rfid(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  pinMode(buzzer_pin,OUTPUT);
  servo.write(140);  //cửa đóng
  lcd.init();
  lcd.backlight();
  servo.attach(8);
  SPI.begin();
  rfid.PCD_Init();
}

void loop() {
  lcd.setCursor(4, 0);
  lcd.print("Welcome!");
  lcd.setCursor(1, 1);
  lcd.print("Put your card");

  if (!rfid.PICC_IsNewCardPresent())
    return;
  if (!rfid.PICC_ReadCardSerial())
    return;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Scanning");

  String ID = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    lcd.print(".");
    ID.concat(String(rfid.uid.uidByte[i] < 0x10 ? " 0" : " "));
    ID.concat(String(rfid.uid.uidByte[i], HEX));
    delay(300);
  }
  ID.toUpperCase();

  bool isAcceptedCard = false;
  // Kiểm tra xem UID có trong danh sách chấp nhận hay không
  for (int i = 0; i < sizeof(acceptedUIDs) / sizeof(acceptedUIDs[0]); i++) {
    if (ID.substring(1) == acceptedUIDs[i]) {
      isAcceptedCard = true;
      break;
    }
  }

  if (isAcceptedCard) {
    count++;
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Card Accepted!");
    delay(1500);

    if (count % 2 == 0) {
      servo.write(140);
      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("Door is locked");
      delay(1500);
      lcd.clear();
    } else {
      servo.write(0);
      lcd.clear();
      lcd.setCursor(2, 0);
      lcd.print("Door is open");
      delay(1500);
      lcd.clear();
    }
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Wrong card!");
    delay(1500);
    digitalWrite(buzzer_pin, HIGH);
    delay(500);
    digitalWrite(buzzer_pin, LOW);
    delay(500);
    lcd.clear();
  }
  rfid.PICC_HaltA();  
  rfid.PCD_StopCrypto1();
}

