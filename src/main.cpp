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

#define ledR 2
#define ledG 3
#define ledB 4

uint8_t ledColor[3] = {255, 255, 255}; 
void setColor(uint8_t *color);

void setup() {
  Serial.begin(115200);
  ::setColor(ledColor);

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
    int args = req->args();
    for(int i=0;i<args;i++){
      Serial.printf("ARG[%s]: %s\n", req->argName(i).c_str(), req->arg(i).c_str());
      switch(req->argName(i).c_str()[0]){
        case 'R': ledColor[0] = req->arg(i).toInt(); break;
        case 'G': ledColor[1] = req->arg(i).toInt(); break;
        case 'B': ledColor[2] = req->arg(i).toInt(); break; 
      }
    }
    ::setColor(ledColor);
    req->send_P(200, "text/plain", "hello-from-esp");
  });

  server.begin();
  mdns.addService("http", "tcp", 80);
}

void loop() {
  // put your main code here, to run repeatedly:
  mdns.update();
}

void setColor(uint8_t *color) {
  for(uint8_t i = 0; i < 3; i++) Serial.printf("%d ", color[i]);
  Serial.println("");

  analogWrite(ledR, color[0]);
  analogWrite(ledG, color[1]);
  analogWrite(ledB, color[2]);
}