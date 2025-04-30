// MASTER

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ==== OLED SETTINGS ====
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// ==== IR SENSOR PINS ====
const int IR_L1_1 = 2;
const int IR_L1_2 = 3;
const int IR_L2_1 = 4;
const int IR_L2_2 = 5;
const int IR_L2_3 = 6;

// ==== TRAFFIC LIGHT PINS ====
const int RED_L1 = 7;
const int GREEN_L1 = 8;
const int RED_L2 = 9;
const int GREEN_L2 = 10;

// ==== TOUCH SENSOR AND JOYSTICK ====
const int TOUCH_PIN = 11;
const int JOYSTICK_X = A0;

// ==== STATES ====
bool manualMode = false;
bool lastTouchState = false;
int lastDirection = 0;
#define DIR_NONE 0
#define DIR_LEFT 1
#define DIR_RIGHT 2

// ==== FUNCTION DECLARATIONS ====
int getSensorCount(int s1, int s2, int s3 = -1);
int getGreenTime(int count);
void switchSignal(int greenL1, int greenL2);
void allSignalsOff();
void updateOLED(bool isCar);
void handleJoystickControl();

void setup() {
  pinMode(IR_L1_1, INPUT);
  pinMode(IR_L1_2, INPUT);
  pinMode(IR_L2_1, INPUT);
  pinMode(IR_L2_2, INPUT);
  pinMode(IR_L2_3, INPUT);

  pinMode(RED_L1, OUTPUT);
  pinMode(GREEN_L1, OUTPUT);
  pinMode(RED_L2, OUTPUT);
  pinMode(GREEN_L2, OUTPUT);

  pinMode(TOUCH_PIN, INPUT);
  pinMode(JOYSTICK_X, INPUT);

  Serial.begin(9600);  // Used to send data to Arduino 2

  // OLED Init
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED init failed");
    while (true); // Hang if OLED fails
  }

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Starting...");
  display.display();
  delay(1000);

  allSignalsOff();
  Serial.println("Mode: AUTOMATIC (IR sensor based)");
  updateOLED(false); // Default to "WALKING"
}

void loop() {
  bool currentTouchState = digitalRead(TOUCH_PIN);

  // Toggle mode on rising edge
  if (currentTouchState && !lastTouchState) {
    manualMode = !manualMode;
    if (manualMode) {
      Serial.println("Mode: MANUAL (Joystick Control)");
    } else {
      Serial.println("Mode: AUTOMATIC (IR sensor based)");
      lastDirection = DIR_NONE;
      allSignalsOff();

      // Resend countdown value to Arduino 2
      int l1_count = getSensorCount(IR_L1_1, IR_L1_2);
      int l2_count = getSensorCount(IR_L2_1, IR_L2_2, IR_L2_3);
      int countdownValue = max(getGreenTime(l1_count), getGreenTime(l2_count));
      if (countdownValue > 0) {
        Serial.println(countdownValue);
      }
    }
    delay(300); // Debounce
  }
  lastTouchState = currentTouchState;

  if (manualMode) {
    handleJoystickControl();
    return;
  }

  // === AUTOMATIC MODE ===
  int l1_count = getSensorCount(IR_L1_1, IR_L1_2);
  int l2_count = getSensorCount(IR_L2_1, IR_L2_2, IR_L2_3);

  if (l1_count == 0 && l2_count == 0) {
    allSignalsOff();
    updateOLED(false); // Lane 1 red by default
    delay(1000);
  } else if (l1_count >= l2_count) {
    switchSignal(getGreenTime(l1_count), 0);
  } else {
    switchSignal(0, getGreenTime(l2_count));
  }
}

void handleJoystickControl() {
  int xValue = analogRead(JOYSTICK_X);
  Serial.println(xValue);

  if (xValue < 400 && lastDirection != DIR_LEFT) {
    digitalWrite(GREEN_L2, HIGH);
    digitalWrite(RED_L2, LOW);
    digitalWrite(GREEN_L1, LOW);
    digitalWrite(RED_L1, HIGH);
    updateOLED(false); // Lane 1 red → WALKING
    lastDirection = DIR_LEFT;
  } else if (xValue > 600 && lastDirection != DIR_RIGHT) {
    digitalWrite(GREEN_L1, HIGH);
    digitalWrite(RED_L1, LOW);
    digitalWrite(GREEN_L2, LOW);
    digitalWrite(RED_L2, HIGH);
    updateOLED(true); // Lane 1 green → CAR
    lastDirection = DIR_RIGHT;
  }
}

int getSensorCount(int s1, int s2, int s3) {
  int count = 0;
  if (digitalRead(s1) == LOW) count++;
  if (digitalRead(s2) == LOW) count++;
  if (s3 != -1 && digitalRead(s3) == LOW) count++;
  return count;
}

int getGreenTime(int count) {
  if (count == 1) return 5;
  else if (count == 2) return 10;
  else return 15;
}

void switchSignal(int greenL1, int greenL2) {
  if (greenL1 > 0) {
    digitalWrite(GREEN_L1, HIGH);
    digitalWrite(RED_L1, LOW);
    digitalWrite(GREEN_L2, LOW);
    digitalWrite(RED_L2, HIGH);
    updateOLED(true); // Lane 1 GREEN → CAR

    Serial.println(greenL1);  // Send value to Arduino 2
    delay(greenL1 * 1000);
  } else if (greenL2 > 0) {
    digitalWrite(GREEN_L2, HIGH);
    digitalWrite(RED_L2, LOW);
    digitalWrite(GREEN_L1, LOW);
    digitalWrite(RED_L1, HIGH);
    updateOLED(false); // Lane 1 RED → WALKING

    Serial.println(greenL2);  // Send value to Arduino 2
    delay(greenL2 * 1000);
  }

  digitalWrite(GREEN_L1, LOW);
  digitalWrite(RED_L1, HIGH);
  digitalWrite(GREEN_L2, LOW);
  digitalWrite(RED_L2, HIGH);
  delay(1000);
}

void allSignalsOff() {
  digitalWrite(GREEN_L1, LOW);
  digitalWrite(RED_L1, LOW);
  digitalWrite(GREEN_L2, LOW);
  digitalWrite(RED_L2, LOW);
}

void updateOLED(bool isCar) {
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 0);
  if (isCar) {
    display.println("STOP");
  } else {
    display.println("WALK");
  }
  display.display();
}