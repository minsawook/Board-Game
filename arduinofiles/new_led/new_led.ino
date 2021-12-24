#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
int btime = 0;
int debounce = 200;
int red_pin[20] = {52, 50, 48, 46, 44, 42, 40, 38, 36, 34, 32, 30, 28, 26, 53, 51, 49 , 47, 45, 43 };
#define btnRed 6
int readingred;
int red_position = 0;    
int previous1 = LOW;
int btnRedCurrent = HIGH;
long btnRedPreviouMillis = 0;
bool btnRedReady = false;

 void RandomRED() {
  int a;
  int count=0;
  
  a = random(1, 7);
  Serial.print("num: ");
  Serial.println(a);
  Serial.print("red_position: ");
  Serial.println(red_position);
int p=red_position + a;

    lcd.setCursor(0, 0);
  lcd.print(a);
  for (int i = red_position; i < p; i++) {
    for (int j = 0; j < 20; j++) {
      digitalWrite(red_pin[j], LOW);
    }

    if(i>19){
      i =0;
      p=p-20;
      count++;
      }
    Serial.println(red_pin[i]);
    digitalWrite(red_pin[i], HIGH);
    delay(1000);
  }

  red_position = red_position + a;

  Serial.print("red_position: ");
  Serial.println(red_position);
  if ( red_position > 19) {
    red_position = red_position -20;
  }
  Serial1.print(a);
 }
void setup() {
  Serial.begin(9600);
  Serial1.begin(115200);
   randomSeed(analogRead(0));
   for (int i = 0; i < 20; i++) {
    pinMode(red_pin[i], OUTPUT);
  }

}

void loop() {
  readingred = digitalRead(btnRed);
  if (readingred == LOW && previous1 == HIGH && (millis() - btime > debounce)) {
    RandomRED();
    btime = millis();
    delay(100);
  }
  previous1 = readingred; 
}
