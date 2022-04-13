#include <WiFi.h>
#include <HTTPClient.h>
#include <HTTPUpdate.h>
#include <WiFiClientSecure.h>
#include "cert.h"
#include <NTPClient.h>
#include <ArduinoJson.h>


#include <ArduinoJson.h>
#include <EEPROM.h>
#include <SPI.h>
#include <LoRa.h>



 int nct=0;
 boolean conCheck=true;

 #define SCK_GPIO18 18
#define MISO_GPIO19 19
#define MOSI_GPIO23 23

int  ss =5;
int rst =14;
int dio0=2;//4
int rstn=0;








#include <Firebase_ESP_Client.h>  
#define DATABASE_URL  "cdmesp32v1-default-rtdb.firebaseio.com"
#define DATABASE_SECRET "dkeek49OjPHN3ssrllJx2t1cq0VXTIRwT8Xsauk2"
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;



String APssid = "";
String APpassword = "";
#ifndef STASSID
#define STASSID "Siti Broadbandz"
#define STAPSK  "111111111"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;
String SS_ID_CLIENT;
String SS_PASS_CLIENT;



const long utcOffsetInSeconds = 19800;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);





String FirmwareVer = {
  "1.0.1"
};
#define URL_fw_Version "https://raw.githubusercontent.com/pankajauengg/CDMV1/main/Version.txt"
#define URL_fw_Bin "https://raw.githubusercontent.com/pankajauengg/CDMV1/main/CDM_ESP32V1.bin"

void firmwareUpdate();
int FirmwareVersionCheck();





void connect_wifi();
unsigned long previousMillis = 0; // will store last time LED was updated
unsigned long previousMillis_2 = 0;
const long interval = 30000;
const long mini_interval = 1000;



struct Button {
  const uint8_t PIN;
  uint32_t numberKeyPresses;
  bool pressed;
};



Button button_boot = {
  0,
  0,
  false
};



void IRAM_ATTR isr() {
  button_boot.numberKeyPresses += 1;
  button_boot.pressed = true;
}





WiFiClient TankClient;
WiFiClient MobileClient;
WiFiClient McClient;

long timFirebase = 0;
long timFirebaseUP=0;
boolean inix = true;
long timdis = 0;



void setup() {
  pinMode(button_boot.PIN, INPUT);
  attachInterrupt(button_boot.PIN, isr, RISING);
  Serial.begin(115200);
  Serial.print("Active firmware version:");
  Serial.println(FirmwareVer);  
  connect_wifi();
  init_firebase();
//  RTC();
//  setupcall();
  firebase_first_update();
}


void loop() {
  if (button_boot.pressed) { //to connect wifi via Android esp touch app 
    Serial.println("Firmware update Starting..");
    firmwareUpdate();
    button_boot.pressed = false;
  }
 repeatedCall();
Serial.println("Hello");
 delay(4000);
}



void connect_wifi() {
  Serial.println("Waiting for WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
