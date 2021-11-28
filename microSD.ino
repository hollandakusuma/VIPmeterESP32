void initSD() {
  display.getTextBounds(F("init SD Card..."), 0, 0, &posx, &posy, &w, &h);
  display.setCursor((128 - w) / 2, 20);
  display.println(F("INIT SD Card..."));
  display.display();
  delay(1000);
  pinMode(cs, OUTPUT);
  digitalWrite(cs, HIGH);
  delay(200);
  if (!SD.begin(cs)) {
    while (1) {
      Serial.println(F("SD init error!!!"));
      display.getTextBounds(F("SD Card Error!!!"), 0, 0, &posx, &posy, &w, &h);
      display.setCursor((128 - w) / 2, 40);
      display.println(F("SD Card Error!!!"));
      display.display();
      delay(5000);
    }
  }

  Serial.println(F("SD CARD INIT OK!"));
  Serial.flush();
  display.getTextBounds(F("SD Card OK!"), 0, 0, &posx, &posy, &w, &h);
  display.setCursor((128 - w) / 2, 40);
  display.println(F("SD Card OK!"));
  display.display();
}

void cekFile() {
  byte indeks = 1;
  unsigned int nomor = 0;

  while (indeks) {
    nomor = nomor + 1;
    sprintf(namaFile, "/VIP%02d.txt", nomor);
    indeks = SD.exists(namaFile);
    if (indeks == 0) {
      Serial.print(namaFile);
      Serial.println(F(" tidak ada"));
      File file = SD.open(namaFile, FILE_WRITE);
      file.println(F("Tanggal (YYYY/MM/DD HH:MM:SS), Tegangan(V), Arus (mA), Daya (mW), Suhu (°C), Kelembaban(%), Kode HTTP"));
      file.flush();
      file.close();
    }
  }
  Serial.flush();
}

void simpanData() {
  File file = SD.open(namaFile, FILE_WRITE);
  file.print(shuntvoltage);
  file.print(F(","));
  file.print(busvoltage);
  file.print(F(","));
  file.print(loadvoltage);
  file.print(F(","));
  file.print(current_mA);
  file.print(F(","));
  file.print(power_mW);
  file.print(F(","));
  file.print(suhu);
  file.print(F(","));
  file.println(humid);
  file.flush();
  file.close();
}
