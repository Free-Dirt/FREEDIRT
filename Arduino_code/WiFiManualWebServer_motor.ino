/*
    This sketch demonstrates how to set up a simple HTTP-like server.
    The server will set a GPIO pin depending on the request
      http://server_ip/gpio/0 will set the GPIO2 low,
      http://server_ip/gpio/1 will set the GPIO2 high
    server_ip is the IP address of the ESP8266 module, will be
    printed to Serial when the module is connected.
*/

#include <ESP8266WiFi.h>

#ifndef STASSID
#define STASSID "your-ssid"
#define STAPSK  "your-password"
#endif

//const char* ssid = "TP-Link_3D84";
//const char* password = "22749406";
const char* ssid = "iphonepmblzm";
const char* password = "hahaha136";
//const char* ssid = "LAPTOP-lzm";
//const char* password = "hahaha123";
//const char* ssid = "MSetup";

// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(80);


int input1 = 0; // pin0 input1
int input2 = 13; // pin13 input2
int input3 = 16; //pin16 input3
int input4 = 2; // pin2 input4

void setup() {
  Serial.begin(115200);

  //reset each IO, the mode is OUTPUT
  pinMode(input1,OUTPUT);
  pinMode(input2,OUTPUT);
  pinMode(input3,OUTPUT);
  pinMode(input4,OUTPUT);


  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print(F("Connecting to "));
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
//  WiFi.begin(ssid);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(F("."));
  }
  Serial.println();
  Serial.println(F("WiFi connected"));

  // Start the server
  server.begin();
  Serial.println(F("Server started"));

  // Print the IP address
  Serial.println(WiFi.localIP());
}

void loop() {
//  digitalWrite(input2,LOW);  // low voltage
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  Serial.println(F("new client"));

  client.setTimeout(5000); // default is 1000

  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(F("request: "));
  Serial.println(req);

  // Match the request
  // lf left forward
  // rf right forward
  // lb left backward
  // rb right backward
  // ls left stop
  // rs right stop

//  if (req.indexOf(F("/gpio/lf")) != -1) {
//    digitalWrite(input1,HIGH); // high voltage
//    digitalWrite(input2,LOW);  // low voltage
//  } else if (req.indexOf(F("/gpio/rf")) != -1) {
//    digitalWrite(input3,HIGH);
//    digitalWrite(input4,LOW);
//  } else if (req.indexOf(F("/gpio/lb")) != -1) {
//    digitalWrite(input1,LOW);
//    digitalWrite(input2,HIGH);
//  } else if (req.indexOf(F("/gpio/rb")) != -1) {
//    digitalWrite(input3,LOW);
//    digitalWrite(input4,HIGH);
//  } else if (req.indexOf(F("/gpio/ls")) != -1) {
//    digitalWrite(input1,LOW);
//    digitalWrite(input2,LOW);
//  } else if (req.indexOf(F("/gpio/rs")) != -1) {
//    digitalWrite(input3,LOW);
//    digitalWrite(input4,LOW);
//  }  

  if (req.indexOf(F("/gpio/f")) != -1) {
    digitalWrite(input1,HIGH); // high voltage
    digitalWrite(input2,LOW);  // low voltage
    digitalWrite(input3,HIGH); 
    digitalWrite(input4,LOW);  
  } else if (req.indexOf(F("/gpio/b")) != -1) {
    digitalWrite(input1,LOW);
    digitalWrite(input2,HIGH);  
    digitalWrite(input3,LOW);
    digitalWrite(input4,HIGH); 
  } else if (req.indexOf(F("/gpio/lt")) != -1) {
    digitalWrite(input1,LOW);
    digitalWrite(input2,HIGH);
    digitalWrite(input3,HIGH); 
    digitalWrite(input4,LOW);  
  } else if (req.indexOf(F("/gpio/rt")) != -1) {
    digitalWrite(input1,HIGH); 
    digitalWrite(input2,LOW);  
    digitalWrite(input3,LOW);
    digitalWrite(input4,HIGH);
  } else if (req.indexOf(F("/gpio/st")) != -1) {
    digitalWrite(input1,LOW);
    digitalWrite(input2,LOW);
    digitalWrite(input3,LOW);
    digitalWrite(input4,LOW);
  } 
    
 
    else {
    Serial.println(F("invalid request"));
//    val = digitalRead(input1);
  }
//
//  // Set LED according to the request
//  digitalWrite(input1, val);

  // read/ignore the rest of the request
  // do not client.flush(): it is for output only, see below
  while (client.available()) {
    // byte by byte is not very efficient
    client.read();
  }

  // Send the response to the client
  // it is OK for multiple small client.print/write,
  // because nagle algorithm will group them into one single packet
  client.print(F("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\nGPIO is now "));
//  client.print((val) ? F("high") : F("low"));
  client.print(F("<br><br>Click <a href='http://"));
  client.print(WiFi.localIP());
  client.print(F("/gpio/f'>here</a> to move forward"));

  client.print(F("<br><br>Click <a href='http://"));
  client.print(WiFi.localIP());
  client.print(F("/gpio/b'>here</a> to move backward"));

  client.print(F("<br><br>Click <a href='http://"));
  client.print(WiFi.localIP());
  client.print(F("/gpio/lt'>here</a> to rotate left"));

  client.print(F("<br><br>Click <a href='http://"));
  client.print(WiFi.localIP());
  client.print(F("/gpio/rt'>here</a> to rotate right"));

  client.print(F("<br><br>Click <a href='http://"));
  client.print(WiFi.localIP());
  client.print(F("/gpio/st'>here</a> to stop"));

//  
//  client.print(WiFi.localIP());
//  client.print(F("/gpio/0'>here</a> to switch LED GPIO off.</html>"));

  // The client will actually be *flushed* then disconnected
  // when the function returns and 'client' object is destroyed (out-of-scope)
  // flush = ensure written data are received by the other side
  Serial.println(F("Disconnecting from client"));
}
