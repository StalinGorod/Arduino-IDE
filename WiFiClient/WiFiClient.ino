#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "LEB_EVO_COM";
const char* password = "satuduatiga";

ESP8266WebServer server(80);

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  digtalWrite(LED_BUILTIN, HIGH);

  Serial.println();
  Serial.println();

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", [](){
    server.send(200, "text/html", "<html>\
    <head>\
    <title>Beranda</title>\
    <style>\
    h2 {color:green;}\
    </style>\
    </head>\
    <body>\
    <h2>LED Sedang ON</h2>\
    <a href='/'>ON</a> | <a href='/off'>OFF</a>\ 
    </body>\
    </html>");
    digtalWrite(LED_BUILTIN, LOW);
  });

   server.on("/off", [](){
    server.send(200, "text/html", "<html>\
    <head>\
    <title>Profil</title>\
    <style>\
    h2 {color:blue;}\
    </style>\
    </head>\
    <body>\
    <h2>LED Sedang OFF</h2>\
    <a href='/'>ON</a> | <a href='/off'>OFF</a>\ 
    </body>\
    </html>");
    digtalWrite(LED_BUILTIN, HIGH);
  });

  server.begin();
  
}

void loop() {
   server.handleClient();                                                                                       
}