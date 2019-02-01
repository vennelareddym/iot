#include<ESP8266WebServer.h>
#include "Adafruit_MQTT_Client.h"
#define ldr A0
#define wifi "OnePlus2"
#define password "apple123"
#define server "io.adafruit.com"
#define port 1883
#define username "vinay_nayar"
#define key "c5bde271fd3845b9b59c13d664543a0e"
WiFiClient esp;
Adafruit_MQTT_Client mqtt(&esp,server,port,username,key);
Adafruit_MQTT_Subscribe feed=Adafruit_MQTT_Subscribe(&mqtt,username"/feeds/photocell");
void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
pinMode(16,OUTPUT);
delay(10);
Serial.println("Adafruit MQTT demo");
Serial.print("Connecting to");
Serial.println(wifi);
WiFi.begin(wifi,password);
while(WiFi.status()!=WL_CONNECTED)
{
  delay(500);
  Serial.print(".");
}
Serial.println("WiFi connected");
Serial.println("IP address:");
Serial.println(WiFi.localIP());
mqtt.subscribe(&feed);
Serial.print("Connecting to MQTT");
while(mqtt.connect())
{
  delay(500);
  Serial.print(".");
}
}

void loop() {
  // put your main code here, to run repeatedly:
  while(mqtt.readSubscription(5000))
  {
    Serial.print("Got:");
    Serial.print((char*)feed.lastread);
    int a=atoi((char*)feed.lastread);
    Serial.print("");
    Serial.println(a);
    if(a==0)
    {
      digitalWrite(16,0);
    }
    else
    {
      digitalWrite(16,1);
    }    
  }
}
