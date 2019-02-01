#include<ESP8266WebServer.h>
ESP8266WebServer server;
const char username[]="vinay";
const char password[]="vn123456";
#define pin 16
void setup() {
  // put your setup code here, to run once:
pinMode(pin,OUTPUT);
Serial.begin(115200);
WiFi.softAP(username,password);
IPAddress myIP=WiFi.softAPIP();
Serial.print("AP IP address:");
Serial.println(myIP);
server.begin();
server.on("/led",led);
}

void loop() {
  // put your main code here, to run repeatedly:
server.handleClient();
}
void led()
{
  String myhtml="<html><head><title>My First Web Page</title></head><body style=\"background-color: coral \"><h1> <center>IOT</center></h1><form><center><br><button name=\"state\" type=\"submit\" value=\"0\">LED ON</button><button name=\"state\" type=\"submit\" value=\"1\">LED OFF</button></center></form></body></html>";
server.send(200,"text/html",myhtml);
if(server.arg("state")=="0")
{
  digitalWrite(pin,LOW);
}
else
{
  digitalWrite(pin,HIGH);
} 
}

