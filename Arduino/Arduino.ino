#include <Servo.h>
Servo Door;
#define OpenAngle 170
#define CloseAngle 75
#define servopin 3

#include <SPI.h>

#include <MFRC522.h>
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);

const int StreetLight = 4;

int LDR;

void setup() {

  pinMode(StreetLight, OUTPUT);
  pinMode(LDR, INPUT);

  Door.attach(servopin);

  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522

  Serial.begin(9600);

  DoorClose();
}

void loop() {

  LDR = analogRead(A0);

  if (LDR <= 25) {
    digitalWrite(StreetLight, HIGH);
  }

  else if (LDR >= 35) {

    digitalWrite(StreetLight, LOW);
  }

  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    return;
  }

  String content = "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }

  content.toUpperCase();
  if (content.substring(1) == "D5 8A B8 73")  {
    Door.attach(servopin);
    DoorOpen();
    Serial.println("Door Open Processed");
    delay(5000);
    DoorClose();
    delay(1000);
    Door.detach();
  }
}

void DoorOpen()  {
  Door.write(OpenAngle);
}

void DoorClose()  {
  Door.write(CloseAngle);
}