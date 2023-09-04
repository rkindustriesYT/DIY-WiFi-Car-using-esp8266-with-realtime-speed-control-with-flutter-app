#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "NodeMCU-Car";
const char* password = "12345678";

ESP8266WebServer server(80);

int speed = 0;
String dir = "s";
String lR ="s";

void handleRoot() {
  String speedstr = server.arg("speed");
  String dirstr = server.arg("dir");
  String lRstr = server.arg("lR");
  
  // if (sliderValue1Str != "" && sliderValue2Str != "") {
    speed = speedstr.toInt();
    dir = dirstr;
    lR = lRstr;
  
  Serial.print(speed);
  Serial.print(" : ");
  Serial.print(dir);
  Serial.print(" : ");
  Serial.println(lR);
  // }
  if(dir =="f"){
    digitalWrite(D1,LOW);
    digitalWrite(D2,HIGH);
  }
  else if(dir =="b"){
    digitalWrite(D1,HIGH);
    digitalWrite(D2,LOW);
  }
  else{
     digitalWrite(D1,HIGH);
    digitalWrite(D2,LOW);
  }

  if(lR == "Left"){
    digitalWrite(D3,HIGH);
    digitalWrite(D4,LOW);
  }
  else if( lR == "Right"){
    digitalWrite(D3,LOW);
    digitalWrite(D4,HIGH);
  }
  else{digitalWrite(D3,LOW);
    digitalWrite(D4,LOW);}

  analogWrite(D5,speed);


  
  server.send(200, "text/plain", "OK");
}

void setup() {
  Serial.begin(9600);
    WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("Hotspot IP address: ");
  Serial.println(myIP);
  Serial.println(WiFi.softAPIP());

  server.on("/update", handleRoot);
  
  server.begin();
  Serial.println("HTTP server started");
  pinMode(D1,OUTPUT);
  pinMode(D2,OUTPUT);
  pinMode(D3,OUTPUT);
  pinMode(D4,OUTPUT);
  pinMode(D5,OUTPUT);
  

}

void loop() {
  server.handleClient();
  
  // Process the slider values as needed
  
  
  // Add your car control logic here
  
  
}
