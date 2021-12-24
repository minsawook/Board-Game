#include <HardwareSerial.h>
HardwareSerial mySerial1(1);
HardwareSerial mySerial2(2); //3개의 시리얼 중 2번 채널을 사용
#if defined(ESP32)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif
#include <Firebase_ESP_Client.h>
  
//Provide the token generation process info.
#include <addons/TokenHelper.h>

/* 1. Define the WiFi credentials */
#define WIFI_SSID "now"
#define WIFI_PASSWORD "abcdefgh"

/* 2. Define the API Key */
#define API_KEY "AIzaSyCotkpt8EsQG54ySPGeKdOLe4u2lIuVX5w"

/* 3. Define the project ID */
#define FIREBASE_PROJECT_ID "test-6c718"

/* 4. Define the user Email and password that alreadey registerd or added in your project */
#define USER_EMAIL "mjc@naver.com"
#define USER_PASSWORD "mjcmjc"

//Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long dataMillis = 0;
int count = 0;
String red_;
String yellow_;
String green_;
int red=0;
int green=0;
int yellow=0;

void setup()
{


    mySerial1.begin(115200, SERIAL_8N1, 15, 16);// yellow RX:15 / TX:16번 핀 사용
  mySerial2.begin(115200, SERIAL_8N1, 12, 13);// red  RX:12 / TX:13번 핀 사용
    Serial.begin(115200); //green

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to Wi-Fi");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(300);
    }
    Serial.println();
    Serial.print("Connected with IP: ");
    Serial.println(WiFi.localIP());
    Serial.println();

    Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);

    /* Assign the api key (required) */
    config.api_key = API_KEY;

    /* Assign the user sign in credentials */
    auth.user.email = USER_EMAIL;
    auth.user.password = USER_PASSWORD;

    /* Assign the callback function for the long running token generation task */
    config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h

    Firebase.begin(&config, &auth);
    
    Firebase.reconnectWiFi(true);

}

void loop()
{
      if (mySerial1.available() > 0) {
        String yellow_ = mySerial1.readStringUntil('\n'); //추가 시리얼의 값을 수신하여 String으로 저장
        Serial.println(yellow); //기본 시리얼에 추가 시리얼 내용을 출력
        yellow = yellow_.toInt();
        
      }
      if (mySerial2.available() > 0) { //red
        String red_ = mySerial2.readStringUntil('\n'); //추가 시리얼의 값을 수신하여 String으로 저장
        Serial.println(red); //기본 시리얼에 추가 시리얼 내용을 출력
        red = red_.toInt();
         Serial.println(red);
      }
      if (Serial.available() > 0) {
        String green_ = Serial.readStringUntil('\n'); //추가 시리얼의 값을 수신하여 String으로 저장
        Serial.println(green); //기본 시리얼에 추가 시리얼 내용을 출력
        green = green_.toInt();
      }

    if (Firebase.ready() && (millis() - dataMillis > 1000 || dataMillis == 0))
    {
        dataMillis = millis();
        count++;

        Serial.println("Commit a document (set server value, update document)... ");

        std::vector<struct fb_esp_firestore_document_write_t> writes;

        struct fb_esp_firestore_document_write_t update_write;

        update_write.type = fb_esp_firestore_document_write_type_update;

        FirebaseJson content;
        String documentPath = "Events/event";        

        content.set("fields/dicenum1/integerValue", int(red));
         Serial.print("reddice number is:");
         Serial.println(red);
        content.set("fields/dicenum2/integerValue", int(yellow));
        Serial.print("yellowdice number is:");
         Serial.println(yellow);
        content.set("fields/dicenum3/integerValue", int(green));
        Serial.print("greendice number is:");
         Serial.println (green);
                       
        update_write.update_document_content = content.raw();

        update_write.update_document_path = documentPath.c_str();

        writes.push_back(update_write);

        if (Firebase.Firestore.commitDocument(&fbdo, FIREBASE_PROJECT_ID, "" /* databaseId can be (default) or empty */, writes /* dynamic array of fb_esp_firestore_document_write_t */, "" /* transaction */))
            Serial.printf("ok\n%s\n\n", fbdo.payload().c_str());
        else
            Serial.println(fbdo.errorReason());
    }
}
