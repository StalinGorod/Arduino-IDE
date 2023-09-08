#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

void setup() {

  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  Wifi.begin("LEB_EVO_COM", "satuduatiga");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println(WiFi.localIP());
}

void loop() {
  if ((WiFi.status() == WL_CONNECTED)) {

    WiFiClient client;
    HTTPClient http;

    http.begin(client, "http://smktarunapersada.sch.id/proses_iot.php");
    http.addHeader("Content-Type", "application/json; charset=utf-8");

    int httpCode = http.POST("");
    
    Serial.print(httpCode);
    if (httpCode > 0) {
      if (httpCode == HTTP_CODE_OK) {
        const String& payload = http.getString();
        Serial.println(payload);
        if(payload == "ON"){
          digitalWrite(LED_BUILTIN, LOW);
        } else if(payload == "OFF") {
          digitalWrite(LED_BUILTIN, HIGH);
        }
      }
    }
    http.end();
  }

  delay(10000);
}
