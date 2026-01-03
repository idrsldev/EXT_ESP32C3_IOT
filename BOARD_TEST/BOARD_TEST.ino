#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#include <WiFi.h>

const char* WIFI_SSID = "Idrsldev_mobile";
const char* WIFI_PASS = "Idrislaode"; 
 
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SH1106G oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define PIN_SW1 0
#define PIN_SW2 1
#define PIN_SW3 2

#define PIN_LED1 5 
#define PIN_LED2 4
#define PIN_LED3 3

bool lastSW1 = 1, lastSW2 = 0, lastSW3 = 0;

long int timerWifi = 0;

bool initWifi = 0;
String statusWifi = "CONNECTING";
String IP = "0.0.0.0";

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("PROGRAM RUNNING SETUP"); 
 
  oled.begin(0x3C, true);
  
  oled.setTextSize(1);
  oled.setTextColor(SH110X_WHITE);
  oled.clearDisplay();
  oled.display();

  pinMode(PIN_LED1, OUTPUT);
  pinMode(PIN_LED2, OUTPUT);
  pinMode(PIN_LED3, OUTPUT);
  pinMode(PIN_SW1, INPUT_PULLUP);
  pinMode(PIN_SW2, INPUT_PULLUP);
  pinMode(PIN_SW3, INPUT_PULLUP);

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  WiFi.setTxPower(WIFI_POWER_8_5dBm);

  Serial.println("PROGRAM RUNNING LOOP");
}

void loop() {
  oled.clearDisplay();
  if(WiFi.status() != WL_CONNECTED){
    initWifi = 1;
    statusWifi = "CONNECTING";
    if(millis() - timerWifi > 3000){
      WiFi.disconnect();
      WiFi.mode(WIFI_STA);
      WiFi.begin(WIFI_SSID, WIFI_PASS);
      WiFi.setTxPower(WIFI_POWER_8_5dBm);
      timerWifi = millis();
    }
    IP = "0.0.0.0";
  } else if(WiFi.status() == WL_CONNECTED && initWifi){
    initWifi = 0;
    statusWifi = "CONNECTED";
    IP = WiFi.localIP().toString();
  }   

  bool SW1 = !digitalRead(PIN_SW1);
  bool SW2 = !digitalRead(PIN_SW2);
  bool SW3 = !digitalRead(PIN_SW3);

  digitalWrite(PIN_LED1, SW1);
  digitalWrite(PIN_LED2, SW2);
  digitalWrite(PIN_LED3, SW3);

  if(SW1 != lastSW1 || SW2 != lastSW2 || SW3 != lastSW3){
    Serial.println("SW1:" + String(SW1) + " SW2:" + String(SW2) + " SW3:" + String(SW3));   
    lastSW1 = SW1;
    lastSW2 = SW2;
    lastSW3 = SW3;
  }

  oled.setCursor(0, 30);
  if(SW1){
    oled.print("LED 1 ON");
  } else if(SW2){
    oled.print("LED 2 ON");
  } else if(SW3){
    oled.print("LED 3 ON");
  }


  oled.setCursor(0, 30);
  if(SW1){
    oled.print("LED 1 ON");
  } else if(SW2){
    oled.print("LED 2 ON");
  } else if(SW3){
    oled.print("LED 3 ON");
  }

  oled.setCursor(0, 0);
  oled.print("WIFI : ");
  oled.print(statusWifi);
  oled.setCursor(0, 10);
  oled.print("IP : ");
  oled.print(IP);
  oled.setCursor(0, 20);
  oled.print("SW1:" + String(SW1) + " SW2:" + String(SW2) + " SW3:" + String(SW3));

  oled.display(); 
}
