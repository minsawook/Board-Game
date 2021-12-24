#define btnyellow 6
#include <LiquidCrystal_I2C.h>
//LiquidCrystal_I2C lcd(0x27, 16, 2);
int btime = 0;
int debounce = 200;
int yellow_pin[20] = {52, 50, 48, 46, 44, 42, 40, 38, 36, 34, 32, 30, 28, 26, 24, 22, 29, 27, 25, 23};  // YELLOW LED
int readingyellow;
int yellow_position = 0;
int previous1 = LOW;
int btnyellowCurrent = HIGH;
long btnyellowPreviouMillis = 0;
bool btnyellowReady = false;

void Randomyellow() {
  int a;
  int count = 0;

  a = random(1, 7);
  Serial.print("num: ");
  Serial.println(a);
  Serial.print("yellow_position: ");
  Serial.println(yellow_position);
  int p = yellow_position + a;
  
  for (int i = yellow_position; i < p; i++) {
    for (int j = 0; j < 20; j++) {
      digitalWrite(yellow_pin[j], LOW);
    }

    if (i > 19) {
      i = 0;
      p = p - 20;
      count++;
    }

    Serial.println(yellow_pin[i]);
    digitalWrite(yellow_pin[i], HIGH);
    delay(1000);
  }

  yellow_position = yellow_position + a;

  Serial.print("yellow_position: ");
  Serial.println(yellow_position);
  if ( yellow_position > 19) {
    yellow_position = yellow_position - 20;
  }
  Serial1.print(a );
}
void setup() {
  Serial.begin(9600);
  Serial1.begin(115200);
  randomSeed(analogRead(0));
  for (int i = 0; i < 20; i++) {
    pinMode(yellow_pin[i], OUTPUT);
  }

}

void loop() {
  readingyellow = digitalRead(btnyellow);
  if (readingyellow == LOW && previous1 == HIGH && (millis() - btime > debounce)) {
    Randomyellow();
    btime = millis();
    delay(100);
  }
  previous1 = readingyellow;

}
