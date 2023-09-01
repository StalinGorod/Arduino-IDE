#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "LEB_EVO_COM";
const char* password = "satuduatiga";

ESP8266WebServer server(80);

void setup() {
  Serial.begin(115200);

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
    <h2>Selamat Datang</h2>\
    <a href='/'>Beranda</a> | <a href='/profil'>Profil</a>\ 
    </body>\
    </html>");
  });

   server.on("/profil", [](){
    server.send(200, "text/html", "<html>\
    <head>\
    <title>Profil</title>\
    <style>\
    h2 {color:blue;}\
    </style>\
    </head>\
    <body>\
    <h2>Ini Halaman Profil</h2>\
    <a href='/'>Beranda</a>\
    </body>\
    </html>");
  });

  server.begin();
  
}

void loop() {
   server.handleClient();                                                                                       
}
