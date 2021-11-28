/* LIBRARY YANG DIBUTUHKAN
  ADAFRUIT OLED SSD1306 https://github.com/adafruit/Adafruit_SSD1306
  ADAFRUIT GFX https://github.com/adafruit/Adafruit-GFX-Library
  ADAFRUIT INA219 https://github.com/adafruit/Adafruit_INA219
  ADAFRUIT DHTLIB https://github.com/adafruit/DHT-sensor-library
  SD
  WIFI MANAGER TZAPU https://github.com/tzapu/WiFiManager
  THINGSPEAK https://github.com/mathworks/thingspeak-arduino
  NTPCLIENT https://github.com/arduino-libraries/NTPClient
*/

unsigned long myChannelNumber = 1562897;
const char * myWriteAPIKey = "4QA750UPMLI6L632";

char ssid[] = "VIPmeter";
const long utcOffsetInSeconds = 0; // 7*3600 untuk WIB


char namaFile[] = "/VIP001.TXT";
#define DHTTYPE DHT22
#define DHTPIN 15
float suhu, humid;

byte led=2;
byte cs = 5;
byte bulan, hari, jam, menit, detik;
unsigned int tahun, kode;

char dates[] = "2021/10/10";
char times[] = "11:12:59";

float shuntvoltage = 0;
float busvoltage = 0;
float current_mA = 0;
float loadvoltage = 0;
float power_mW = 0;
