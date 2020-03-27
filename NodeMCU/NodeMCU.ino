#include "secrets.h"

#include <Blynk.h>
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

const int HallPin = 5; //The pin connected to the light in your Hall - 1
const int KitchenPin = 4; //The pin connected to the light in your Kitchen - 2
const int StudyRoomPin = 0; //The pin connected to the light in your StudyRoom - 3
const int BedRoomPin = 2; //The pin connected to the light in your BedRoom - 4
const int BedRoomFanPin = 14; //The pin connected to the fan in your BedRoom - 5

//Please enter your secrets in the "secrets.h" tab
char auth[] = SECRET_AUTH; 
char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;
//////////////////////////////////////////////////

BLYNK_WRITE(V1) {

  int HallLight = param.asInt(); // assigning incoming value from pin V1 to a variable
  // process received value

  digitalWrite(HallPin, HallLight);
  Serial.print("HallLight: ");
  Serial.println(HallLight);
}

BLYNK_WRITE(V2) {

  int KitchenLight = param.asInt(); // assigning incoming value from pin V2 to a variable
  // process received value

  digitalWrite(KitchenPin, KitchenLight);
  Serial.print("KitchenLight: ");
  Serial.println(KitchenLight);
}

BLYNK_WRITE(V3) {

  int StudyRoomLight = param.asInt(); // assigning incoming value from pin V3 to a variable
  // process received value

  digitalWrite(StudyRoomPin, StudyRoomLight);
  Serial.print("StudyRoomLight: ");
  Serial.println(StudyRoomLight);
}

BLYNK_WRITE(V4) {

  int BedRoomLight = param.asInt(); // assigning incoming value from pin V4 to a variable
  // process received value

  digitalWrite(BedRoomPin, BedRoomLight);
  Serial.print("BedRoomLight: ");
  Serial.println(BedRoomLight);
}

BLYNK_WRITE(V5) {

  int BedRoomFan = param.asInt(); // assigning incoming value from pin V5 to a variable
  // process received value

  digitalWrite(BedRoomFanPin, BedRoomFan);
  Serial.print("BedRoomFan: ");
  Serial.println(BedRoomFan);
}

void setup()
{
  // Debug console
  Serial.begin(9600);

  pinMode(HallPin, OUTPUT);
  pinMode(KitchenPin, OUTPUT);
  pinMode(StudyRoomPin, OUTPUT);
  pinMode(BedRoomPin, OUTPUT);
  pinMode(BedRoomFanPin, OUTPUT);

  Blynk.begin(auth, ssid, pass);
}

void loop()  {
  Blynk.run();
}
