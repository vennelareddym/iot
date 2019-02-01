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
Adafruit_MQTT_Publish feed=Adafruit_MQTT_Publish(&mqtt,username"/feeds/photocell");
void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
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
Serial.print("Connecting to MQTT");
while(mqtt.connect())
{
  Serial.print(".");
}
}

void loop() {
  // put your main code here, to run repeatedly:
if(mqtt.connected())
{
  int data=analogRead(ldr);
  Serial.print("\nSending LDR val:");
  Serial.print(data);
  Serial.print("...");
  if(feed.publish(data))
  {
    Serial.println("Success");
  }
  else
  {
    Serial.println("Fail!");
  }
  delay(2000);
}
}
