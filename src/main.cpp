#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ESP8266mDNS.h>
    
const char* ssid     = "MY-ESP8266-SERVER";
const char* password = "esp8266server";

AsyncWebServer server(80);
MDNSResponder mdns;

#include <client-html.h>

void setup() {
  Serial.begin(115200);

  Serial.println("Setting Access Point...");
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  Serial.println(WiFi.localIP());

  if (!mdns.begin("mo0nchidlesp", IP)) {  //Start mDNS with name esp8266
    Serial.println("(-) MDNS not started");
  }
  Serial.println("(+) MDNS started");

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });

  server.on("/data", HTTP_POST, [](AsyncWebServerRequest *req){
    req->send_P(200, "text/plain", "hello-from-esp");
  });

  server.begin();
  mdns.addService("http", "tcp", 80);
}

void loop() {
  // put your main code here, to run repeatedly:
  mdns.update();
}