#include <Wire.h>
#include <LiquidCrystal_I2C.h>
//#include <DHT.h>

// LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);
String scrollText = "Have a great day   ";
int scrollIndex = 0;
unsigned long lastScroll = 0;

// DHT
//#define DHTPIN 1
//#define DHTTYPE DHT11
//DHT dht(DHTPIN, DHTTYPE);

// 8x8 Dot Matrix
int rows[8] = {2, 7, A3, 5, 13, A2, 12, A0};
int cols[8] = {6, 11, 10, 3, A1, 4, 8, 9};

const byte digitPatterns[10][8] = {
  {0x3C, 0x66, 0x6E, 0x76, 0x66, 0x66, 0x3C, 0x00},
  {0x18, 0x38, 0x18, 0x18, 0x18, 0x18, 0x3C, 0x00},
  {0x3C, 0x66, 0x06, 0x0C, 0x30, 0x60, 0x7E, 0x00},
  {0x3C, 0x66, 0x06, 0x1C, 0x06, 0x66, 0x3C, 0x00},
  {0x0C, 0x1C, 0x3C, 0x6C, 0x7E, 0x0C, 0x0C, 0x00},
  {0x7E, 0x60, 0x7C, 0x06, 0x06, 0x66, 0x3C, 0x00},
  {0x1C, 0x30, 0x60, 0x7C, 0x66, 0x66, 0x3C, 0x00},
  {0x7E, 0x06, 0x0C, 0x18, 0x30, 0x30, 0x30, 0x00},
  {0x3C, 0x66, 0x66, 0x3C, 0x66, 0x66, 0x3C, 0x00},
  {0x3C, 0x66, 0x66, 0x3E, 0x06, 0x0C, 0x38, 0x00}
};

int countdown = 0;
int currentRow = 0;
unsigned long lastUpdate = 0;

void setup() {
  Serial.begin(9600);

  for (int i = 0; i < 8; i++) {
    pinMode(rows[i], OUTPUT);
    pinMode(cols[i], OUTPUT);
    digitalWrite(rows[i], HIGH);
    digitalWrite(cols[i], HIGH);
  }

  //dht.begin();
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Starting...");
}

void loop() {
  if (Serial.available()) {
    countdown = Serial.parseInt();
    lastUpdate = millis();
  }

  if (countdown > 0 && millis() - lastUpdate >= 1000) {
    countdown--;
    lastUpdate = millis();
  }

  scanMatrix(countdown);
  updateLCD();
}

void scanMatrix(int num) {
  if (num < 0 || num > 9) return;

  for (int r = 0; r < 8; r++) digitalWrite(rows[r], HIGH);

  byte rowBits = digitPatterns[num][currentRow];
  for (int c = 0; c < 8; c++) {
    digitalWrite(cols[c], (rowBits & (1 << (7 - c))) ? LOW : HIGH);
  }

  digitalWrite(rows[currentRow], LOW);
  delayMicroseconds(800);
  currentRow = (currentRow + 1) % 8;
}

void updateLCD() {
  // Scroll line
  if (millis() - lastScroll > 300) {
    lcd.setCursor(0, 0);
    lcd.print(scrollText.substring(scrollIndex, scrollIndex + 16));
    scrollIndex = (scrollIndex + 1) % scrollText.length();
    lastScroll = millis();
  }

  //float t = dht.readTemperature();
  //float h = dht.readHumidity();

  //lcd.setCursor(0, 1);
  //lcd.print("T:");
  //lcd.print(t, 0);
  //lcd.print((char)223);
  //lcd.print("C H:");
  //lcd.print(h, 0);
  //lcd.print("% ");
}
