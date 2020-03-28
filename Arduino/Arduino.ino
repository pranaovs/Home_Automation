#include "secrets.h"

#include <Servo.h>
Servo Door;
#define OpenAngle 170
#define CloseAngle 75
#define servopin 3

#include <MFRC522.h>
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);
#include <SPI.h>

const int StreetLight = 4;
const int btnpin = 5;
int StreetLightStatus = 0;

int LDR;
int rev;
int btn;
int people = 0;

void setup() {

  pinMode(StreetLight, OUTPUT);
  pinMode(btnpin, INPUT);

  Door.attach(servopin);

  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522

  Serial.begin(9600);

  DoorClose();
}

void loop() {

  LDR = analogRead(A0);
  btn = digitalRead(btnpin);

  if (btn == 1) {
    if (people > 0) {
      Door.attach(servopin);
      DoorOpen();
      people = people - 1;
      Serial.println('3');
      delay(2000);
      DoorClose();
      delay(1000);
      Door.detach();
    }

    else if (people == 0) {
      Door.attach(servopin);
      DoorOpen();
      delay(2000);
      DoorClose();
      delay(1000);
      Door.detach();
    }
  }

  if (LDR <= 25) {
    if (StreetLightStatus == 0) {
      digitalWrite(StreetLight, HIGH);
      Serial.println('4');
    }
    StreetLightStatus = 1;
  }

  else if (LDR >= 35) {
    if (StreetLightStatus == 1) {
      digitalWrite(StreetLight, LOW);
      Serial.println('5');
    }
    StreetLightStatus = 0;
  }

  if (Serial.available() > 0) {
    rev = Serial.read();
    if (rev == '2') {
      if (people > 0) {
        Door.attach(servopin);
        DoorOpen();
        people = people - 1;
        delay(2000);
        DoorClose();
        delay(1000);
      }
    }
  }

  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }

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

  if (content.substring(1) == "SECRET_RFID")  {
    Door.attach(servopin);
    DoorOpen();
    Serial.println('1');
    people = people + 1;
    delay(2000);
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
