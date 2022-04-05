#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
 
// Set AP credentials
#define AP_SSID "TheOtherESP"
#define AP_PASS "flashmeifyoucan"
 
// UDP
WiFiUDP UDP;
IPAddress local_IP(192,168,4,1);
IPAddress gateway(192,168,4,1);
IPAddress subnet(255,255,255,0);
#define UDP_PORT 4210
 
// UDP Buffer
char packetBuffer[255];

bool check_in= false;
bool check_out= false;
int data=0;
char object=' ';
bool pressed = false;
long check_time= 0;
int aantal_mensen=0;
long Time=0;
String msg;

 
void setup() {
  // Setup serial port
  Serial.begin(115200);
  Serial.println();
 
  // Begin Access Point
  Serial.println("Starting access point...");
  WiFi.softAPConfig(local_IP, gateway, subnet);
  WiFi.softAP(AP_SSID, AP_PASS);
  Serial.println(WiFi.localIP());
 
  // Begin listening to UDP port
  UDP.begin(UDP_PORT);
  Serial.print("Listening on UDP port ");
  Serial.println(UDP_PORT);
 
}
 
void loop() {
  // Receive packet
  UDP.parsePacket();
  UDP.read(packetBuffer, 255);
  msg = String(packetBuffer); 

  Time = millis();

  if (msg == "gate1"){
    check_time= Time;
    check_in= true;
    Serial.print("hoi1");
    delay(500);

    while(Time<check_time+1200){
      // Receive packet
    UDP.parsePacket();
    UDP.read(packetBuffer, 255);
    msg = String(packetBuffer); 

    Time = millis();
      if(msg == "gate2"){
        aantal_mensen++;
        Serial.println("hoi2");
        check_out=true;
        delay(200);
      }
    }
  }
  if (msg == "gate2"){
    check_time= Time;
    check_out= false;
    Serial.println("hoi2");
    delay(500);

    while(Time<check_time+1200){

      // Receive packet
      UDP.parsePacket();
      UDP.read(packetBuffer, 255);
      msg = String(packetBuffer); 
      Time = millis();

      if(msg == "gate1"){
        aantal_mensen--;
        Serial.println("hoi1");
        check_in=false;
        delay(200);
//        break;
      }
//    Serial.println('w');
    }
  } 
  Serial.println(aantal_mensen);
}
