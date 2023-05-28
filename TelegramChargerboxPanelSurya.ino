#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>

#define NAMA_WIFI "PANDU"
#define PASSWORD_WIFI "peraiiii"

#define BOT_TOKEN "5817673322:AAEXfnNQ1GpE9EwYQ94OkbUGI64AllbmPm0"
#define USER_ID "6222789217"

#define notifikasiPin 4

X509List cert(TELEGRAM_CERTIFICATE_ROOT);
WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);

void setup() {
  Serial.begin(9600);
  WiFi.begin(NAMA_WIFI, PASSWORD_WIFI);
  secured_client.setTrustAnchors(&cert);
  configTime(0, 0, "pool.ntp.org");
  time_t waktu = time(nullptr);
  while(waktu < 24 * 3600) {
    delay(100);
    waktu = time(nullptr);
  }

  pinMode(notifikasiPin, INPUT);
}

void loop() {
  bool notifikasi = digitalRead(notifikasiPin);
  if(notifikasi == HIGH) {
    bot.sendMessage(USER_ID, "Ada Penyusup!", "");
  }
}

// String getText(int pesanBaru) {
//   for(int i = 0; i < pesanBaru; i++) {
//     String text = bot.messages[i].text;
//     return text;
//   }
// }