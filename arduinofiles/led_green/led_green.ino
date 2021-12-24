#define btngreen 6
int btime = 0;
int debounce = 200;
int green_pin[20] =  {52, 50, 48, 46, 44, 42, 40, 38, 36, 34, 32, 30, 26, 24, 22, 25, 23, 27, 29, 45};
int readinggreen;
int green_position = 0;
int previous1 = LOW;
int btngreenCurrent = HIGH;
long btngreenPreviouMillis = 0;
bool btngreenReady = false;

void Randomgreen() {
  int a;
  int count = 0;

  a = random(1, 7);
  Serial.print("num: ");
  Serial.println(a);
  Serial.print("green_position: ");
  Serial.println(green_position);
  int p = green_position + a;

  for (int i = green_position; i < p; i++) {
    for (int j = 0; j < 20; j++) {
      digitalWrite(green_pin[j], LOW);
    }

    if (i > 19) {
      i = 0;
      p = p - 20;
      count++;
    }
    Serial.println(green_pin[i]);
    digitalWrite(green_pin[i], HIGH);
    delay(1000);
  }

  green_position = green_position + a;

  Serial.print("green_position: ");
  Serial.println(green_position);
  if ( green_position > 19) {
    green_position = green_position - 20;
  }
   Serial1.print(a);  
}
void setup() {
  Serial.begin(9600);
  Serial1.begin(115200);
  randomSeed(analogRead(0));
  for (int i = 0; i < 20; i++) {
    pinMode(green_pin[i], OUTPUT);
  }
}

void loop() {
  readinggreen = digitalRead(btngreen);
  if (readinggreen == LOW && previous1 == HIGH && (millis() - btime > debounce)) {
    Randomgreen();
    btime = millis();
    delay(100);
  }
  previous1 = readinggreen;

}
