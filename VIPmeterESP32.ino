#include <FS.h>                   //this needs to be first, or it all crashes and burns...

#include <Adafruit_INA219.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include "config.h"
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager
#include "DHT.h"
#include "ThingSpeak.h"
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <SPI.h>
#include <Wire.h>
#include <SD.h>

WiFiClient  client;
Adafruit_INA219 ina219;

//NTP
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

//OLED
byte panjang = 128;
byte lebar = 64;
#define OLED_RESET 4
Adafruit_SSD1306 display(panjang, lebar, &Wire, OLED_RESET);

int16_t posx;
int16_t posy;
uint16_t w, h;

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  Serial.println("\r\n\r\nVIP meter version 2021");
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0X3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    digitalWrite(led, 1);
    for (;;); // Don't proceed, loop forever
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  tampilanAwal();
  delay(4000);

  //SD INIT
  display.clearDisplay();
  Serial.println(F("INIT SD Card..."));
  initSD();
  delay(3000);
  initVA();

  //open wifi manager
  display.clearDisplay();
  display.getTextBounds(F("OPEN HOTSPOT"), 0, 0, &posx, &posy, &w, &h);
  display.setCursor((128 - w) / 2, 10);
  display.println(F("OPEN HOTSPOT"));
  display.display();

  display.getTextBounds(ssid, 0, 0, &posx, &posy, &w, &h);
  display.setCursor((128 - w) / 2, 30);
  display.println(ssid);
  display.display();

  WiFiManager wifiManager;
  wifiManager.setBreakAfterConfig(true);

  if (!wifiManager.autoConnect(ssid, ssid)) {
    Serial.println("Koneksi Error");
    display.getTextBounds(F("Koneksi Error"), 0, 0, &posx, &posy, &w, &h);
    display.setCursor((128 - w) / 2, 50);
    display.println(F("Koneksi Error"));
    display.display();
    delay(3000);
    ESP.restart();
    delay(5000);
  }

  Serial.println("Koneksi OK");

  display.getTextBounds(F("Koneksi OK"), 0, 0, &posx, &posy, &w, &h);
  display.setCursor((128 - w) / 2, 50);
  display.println(F("Koneksi OK"));
  display.display();
  delay(1000);

  display.clearDisplay();
  display.getTextBounds(F("TERHUBUNG KE"), 0, 0, &posx, &posy, &w, &h);
  display.setCursor((128 - w) / 2, 20);
  display.println(F("TERHUBUNG KE"));
  display.getTextBounds((char*)WiFi.SSID().c_str(), 0, 0, &posx, &posy, &w, &h);
  display.setCursor((128 - w) / 2, 40);
  display.println((char*)WiFi.SSID().c_str());
  display.display();
  delay(3000);
  display.clearDisplay();

  //NTP
  timeClient.begin();
  for (byte i = 0; i < 3; i++) {
    timeClient.update();
    unsigned long epochTime = timeClient.getEpochTime();
    struct tm *ptm = gmtime ((time_t *)&epochTime);
    hari = ptm->tm_mday;
    bulan = ptm->tm_mon + 1;
    tahun = ptm->tm_year + 1900;
    jam = timeClient.getHours();
    menit = timeClient.getMinutes();
    detik = timeClient.getSeconds();

    sprintf(dates, "%d/%02d/%02d", tahun, bulan, hari);
    sprintf(times, "%02d:%02d:%02d", jam, menit, detik);
    Serial.print(dates);
    Serial.print(" ");
    Serial.println(times);

    display.clearDisplay();
    display.getTextBounds(dates, 0, 0, &posx, &posy, &w, &h);
    display.setCursor((128 - w) / 2, 20);
    display.print(dates);
    display.getTextBounds(times, 0, 0, &posx, &posy, &w, &h);
    display.setCursor((128 - w) / 2, 40);
    display.print(times);
    display.display();
    delay(1000);
  }

  display.clearDisplay();
  mulaiServer();
  cekFile();

  display.clearDisplay();
  display.display();
  display.setTextSize(2);
  display.setTextColor(WHITE);

  while (detik != 59) {
    waktu();
    hapusmenu(20, 40);
    char countDown[] = "59 detik";
    sprintf(countDown, "%02d", 60 - detik);
    display.getTextBounds(countDown, 0, 0, &posx, &posy, &w, &h);
    display.setCursor((128 - w) / 2, 25);
    display.print(countDown);
    display.display();
    delay(100);
  }

  display.setTextSize(1);
  display.clearDisplay();
  display.display();
  delay(100);
}

void loop() {
  waktu();
  tampilWaktu();

  ambilData();
  delay(100);
  tampilData();
  simpanData();
  delay(1000);
  while (detik != 0) {
    waktu();
    delay(500);
  }

  kode = 0;
}
