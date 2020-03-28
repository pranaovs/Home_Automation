#include "secrets.h"

#include <Blynk.h>
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
WidgetLED StreetLight(V8);

const int HallPin = 5; //The pin connected to the light in your Hall - 1
const int KitchenPin = 4; //The pin connected to the light in your Kitchen - 2
const int StudyRoomPin = 0; //The pin connected to the light in your StudyRoom - 3
const int BedRoomPin = 2; //The pin connected to the light in your BedRoom - 4
const int BedRoomFanPin = 14; //The pin connected to the fan in your BedRoom - 5

int people = 0;
int rev = 0;

char auth[] = "SECRET_AUTH";
char ssid[] = "SECRET_SSID";
char pass[] = "SECRET_PASS";

bool isFirstConnect = true;

BLYNK_CONNECTED() {
  if (isFirstConnect) {
    Blynk.syncAll();
    Blynk.virtualWrite(V7, people);
    Blynk.virtualWrite(V6, 0);
    StreetLight.off();
    isFirstConnect = false;
  }
}
BLYNK_WRITE(V1) {

  int HallLight = param.asInt();
  digitalWrite(HallPin, HallLight);
}

BLYNK_WRITE(V2) {

  int KitchenLight = param.asInt();
  digitalWrite(KitchenPin, KitchenLight);
}

BLYNK_WRITE(V3) {

  int StudyRoomLight = param.asInt();
  digitalWrite(StudyRoomPin, StudyRoomLight);
}

BLYNK_WRITE(V4) {

  int BedRoomLight = param.asInt();
  digitalWrite(BedRoomPin, BedRoomLight);
}

BLYNK_WRITE(V5) {

  int BedRoomFan = param.asInt();
  digitalWrite(BedRoomFanPin, BedRoomFan);
}

BLYNK_WRITE(V6) {

  int door = param.asInt();
  if (people > 0) {
    if (door == 1)  {
      Serial.println('2');
      people = people - 1;
      Blynk.virtualWrite(V7, people);
    }
  }
  Blynk.virtualWrite(V6, 0);
}

void setup()  {

  pinMode(HallPin, OUTPUT);
  pinMode(KitchenPin, OUTPUT);
  pinMode(StudyRoomPin, OUTPUT);
  pinMode(BedRoomPin, OUTPUT);
  pinMode(BedRoomFanPin, OUTPUT);

  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
}

void loop()  {

  if (Serial.available() > 0) {
    rev = Serial.read();

    if (rev == '1') {
      people = people + 1;
      Blynk.virtualWrite(V7, people);
    }

    else if (rev == '3') {
      if (people > 0) {
        people = people - 1;
        Blynk.virtualWrite(V7, people);
      }
    }

    else if (rev == '4')  {
      StreetLight.on();
    }

    else if (rev == '5')  {
      StreetLight.off();
    }
  }

  Blynk.run();
  
 }