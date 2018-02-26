#include <AccelStepper.h>
#include <MultiStepper.h>

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

const char* ssid = "Slider";
const char* password = "chose-password";

ESP8266WebServer server(80);
int x;
const int enable = 16; /*D0*/
const int stepping = 2; /*D4*/
const int dir = 0; /*D3*/
const int m3 = 5; /*D1*/
const int m2 = 4; /*D2*/
const int m1 = 14; /*D5*/
const int StepperSpeed = 1;
const int sliderWidth = 34400;
int direct = 1;
int sliderWidthMulti = 0;
AccelStepper slider(AccelStepper::DRIVER, stepping, dir);
int maxspeed = 8000;



String webPage = "<html> <head> <style> button {   background-color: #f49a2a;  padding: 12px 28px;   width: 100%;  height: 12%;  border-radius: 8px;   border: 0px;  font-size: 50px;  color: white;   } h1 {  text-align: center;   }  </style> </head> <body> <h1>Camera-Slider</h1> <p><button onmousedown=location.href=\"/10sec\">10 Sec</button></p> <p><button onmousedown=location.href=\"/30sec\">30 Sec</button></p> <p><button onmousedown=location.href=\"/1min\">1 Minute</button></p> <p><button onmousedown=location.href=\"/5min\">5 Minutes</button></p> <p><button onmousedown=location.href=\"/10min\">10 Minutes</button></p> <p><button onmousedown=location.href=\"/fasthome\">Home</button></p> </body> </html>";

void handleRoot() {
  server.send(200, "text/html", webPage);
}

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void setup(void) {
  pinMode(enable, OUTPUT);
  pinMode(stepping, OUTPUT);
  pinMode(dir, OUTPUT);
  pinMode(m3, OUTPUT);
  pinMode(m2, OUTPUT);
  pinMode(m1, OUTPUT);
  digitalWrite(enable, 0);
  Serial.begin(115200);
  digitalWrite(m1, 1);
  digitalWrite(m2, 1);
  digitalWrite(m3, 1);

  WiFi.softAP(ssid, password);

  IPAddress apip = WiFi.softAPIP();
  Serial.println("apip");
  server.on("/", handleRoot);
  
  server.on("/10sec", []() {
    server.send(200, "text/html", webPage);

    slider.setMaxSpeed(sliderWidth/10);
    slider.setAcceleration(10000);
    if (direct == 0)
    {
      slider.moveTo(sliderWidth);
      ESP.wdtFeed();
      direct = 1;
    }
    else
    {
      slider.moveTo(0);
      ESP.wdtFeed();
      direct = 0;
    }
  });

  server.on("/30sec", []() {
    server.send(200, "text/html", webPage);
    slider.setMaxSpeed(sliderWidth/30);
    slider.setAcceleration(10000);
    if (direct == 0)
    {
      slider.moveTo(sliderWidth);
      ESP.wdtFeed();
      direct = 1;
    }
    else
    {
      slider.moveTo(0);
      ESP.wdtFeed();
      direct = 0;
    }

  });
  server.on("/1min", []() {
    server.send(200, "text/html", webPage);
    slider.setMaxSpeed(sliderWidth/60);
    slider.setAcceleration(10000);
    if (direct == 0)
    {
      slider.moveTo(sliderWidth);
      ESP.wdtFeed();
      direct = 1;
    }
    else
    {
      slider.moveTo(0);
      ESP.wdtFeed();
      direct = 0;
    }
  });
  server.on("/5min", []() {
    server.send(200, "text/html", webPage);
    slider.setMaxSpeed(sliderWidth/300);
    slider.setAcceleration(10000);
    if (direct == 0)
    {
      slider.moveTo(sliderWidth);
      ESP.wdtFeed();
      direct = 1;
    }
    else
    {
      slider.moveTo(0);
      ESP.wdtFeed();
      direct = 0;
    }
  });
    server.on("/10min", []() {
    server.send(200, "text/html", webPage);
    slider.setMaxSpeed(sliderWidth/600);
    slider.setAcceleration(10000);
    if (direct == 0)
    {
      slider.moveTo(sliderWidth);
      ESP.wdtFeed();
      direct = 1;
    }
    else
    {
      slider.moveTo(0);
      ESP.wdtFeed();
      direct = 0;
    }
  });
   server.on("/fasthome", []() {
    server.send(200, "text/html", webPage);
    slider.setMaxSpeed(maxspeed);
    slider.setAcceleration(30000);
    if (direct == 0)
    {
      slider.moveTo(sliderWidth);
      ESP.wdtFeed();
      direct = 1;
    }
    else
    {
      slider.moveTo(0);
      ESP.wdtFeed();
      direct = 0;
    }

  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
  slider.run();
}
