void tampilanAwal() {
  display.getTextBounds(F("VIP"), 0, 0, &posx, &posy, &w, &h);
  display.setCursor((panjang - w) / 2, 10);
  display.println(F("VIP"));
  display.getTextBounds(F("METER"), 0, 0, &posx, &posy, &w, &h);
  display.setCursor((panjang - w) / 2, 20);
  display.println(F("METER"));
  display.getTextBounds(F("BY"), 0, 0, &posx, &posy, &w, &h);
  display.setCursor((panjang - w) / 2, 30);
  display.println(F("BY"));
  display.getTextBounds(F("MANTIS ID"), 0, 0, &posx, &posy, &w, &h);
  display.setCursor((panjang - w) / 2, 40);
  display.println(F("MANTIS ID"));
  display.getTextBounds(F("2021"), 0, 0, &posx, &posy, &w, &h);
  display.setCursor((panjang - w) / 2, 50);
  display.println(F("2021"));
  display.display();
}

void initVA() {
  display.clearDisplay();
  display.getTextBounds(F("INIT VA METER"), 0, 0, &posx, &posy, &w, &h);
  display.setCursor((panjang - w) / 2, 20);
  display.println(F("INIT VA METER"));
  ina219.begin();
  dht.begin();
  delay(1000);
  display.getTextBounds(F("SUKSES"), 0, 0, &posx, &posy, &w, &h);
  display.setCursor((panjang - w) / 2, 40);
  display.println(F("SUKSES"));
  delay(1000);
}

void tampilData() {
  display.fillRect(0, 10, 70, 45, BLACK); //clear display
  display.fillRect(80, 10, 128, 45, BLACK); //clear display
  display.display();
  display.setTextColor(WHITE, BLACK);

  display.setCursor(5, 20);
  display.print(loadvoltage, 2); display.print(F(" V"));
  display.setCursor(5, 30);
  display.print(current_mA, 2); display.print(F(" mA"));
  display.setCursor(5, 40);
  display.print(power_mW);   display.print(F(" mW"));

  display.setCursor(80, 20);  display.print(suhu, 2);
  display.setCursor(80, 30);  display.print(humid, 2);
  display.setCursor(128 - 16, 15);  display.print(F("o"));
  display.setCursor(128 - 8, 20);  display.print(F("C"));
  display.setCursor(128 - 8, 30);  display.print(F("%"));



  hapusmenu(55, 64);
  display.getTextBounds(F("KODE = 200"), 0, 0, &posx, &posy, &w, &h);
  display.setCursor((panjang - w) / 2, 55);
  display.print(F("KODE = "));
  display.print(kode);
  display.display();
}
