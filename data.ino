void mulaiServer() {
  display.getTextBounds(F("KONEKSI KE"), 0, 0, &posx, &posy, &w, &h);
  display.setCursor((128 - w) / 2, 10);
  display.println(F("KONEKSI KE"));
  display.getTextBounds(F("THINGSPEAK"), 0, 0, &posx, &posy, &w, &h);
  display.setCursor((128 - w) / 2, 30);
  display.println(F("THINGSPEAK"));
  display.display();

  display.setCursor(5, 50);
  while (!ThingSpeak.begin(client)) {
    display.print(F("."));
    display.display();
    delay(500);
  }
  hapusmenu(50, 15);
  display.getTextBounds(F("TERHUBUNG!!!"), 0, 0, &posx, &posy, &w, &h);
  display.setCursor((128 - w) / 2, 50);
  display.println(F("TERHUBUNG!!!"));
  display.display();
  delay(2000);
}

void ambilData() {
  shuntvoltage = ina219.getShuntVoltage_mV();
  busvoltage = ina219.getBusVoltage_V();
  loadvoltage = busvoltage + (shuntvoltage / 1000);
  current_mA = ina219.getCurrent_mA();
  power_mW = ina219.getPower_mW();

  humid = dht.readHumidity();
  suhu = dht.readTemperature();

  if (isnan(humid) || isnan(suhu)) {
    humid = -99.99;
    suhu = -99.99;
  }

  Serial.print(shuntvoltage);
  Serial.print(F(","));
  Serial.print(busvoltage);
  Serial.print(F(","));
  Serial.print(loadvoltage);
  Serial.print(F(","));
  Serial.print(current_mA);
  Serial.print(F(","));
  Serial.print(power_mW);
  Serial.print(F(","));
  Serial.print(suhu);
  Serial.print(F(","));
  Serial.println(humid);
  Serial.flush();

  ThingSpeak.setField(1, shuntvoltage);
  ThingSpeak.setField(2, busvoltage);
  ThingSpeak.setField(3, loadvoltage);
  ThingSpeak.setField(4, current_mA);
  ThingSpeak.setField(5, power_mW);
  ThingSpeak.setField(6, suhu);
  ThingSpeak.setField(7, humid);

  kode = 0;

  kode = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if (kode > 600) kode = 999;
  Serial.print("kode HTTP = ");
  Serial.println(kode);
  Serial.println("Berhasil");
}


void hapusmenu(byte h, byte h1) {
  display.fillRect(0, h, 128, h1, BLACK); //clear display
  display.display();
  display.setTextColor(WHITE, BLACK);
}
