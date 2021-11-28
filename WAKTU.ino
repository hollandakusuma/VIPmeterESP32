void waktu() {
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
  sprintf(times, "%02d:%02d", jam, menit);
  Serial.print(dates);
  Serial.print(" ");
  Serial.print(times);
  Serial.print(":");
  Serial.println(detik);
}

void tampilWaktu() {
  hapusmenu(0, 10);
  display.setCursor(0, 0);
  display.print(dates);
  display.setCursor(128-30,0);
  display.print(times);
  display.display();
}
