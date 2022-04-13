#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
 
// Set AP credentials
#define AP_SSID "TheOtherESP"
#define AP_PASS "flashmeifyoucan"
 
// UDP makes acces point
WiFiUDP UDP;
IPAddress local_IP(192,168,4,1);
IPAddress gateway(192,168,4,1);
IPAddress subnet(255,255,255,0);
#define UDP_PORT 4210
 
// UDP Buffer
char packetBuffer[255];

//important variables
bool check_in= false;
bool check_out= false;
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
  Time = millis();
  readPacket();
  goIn("gate1", "gate2", "Room1");
  goOut("gate2", "gate1", "Room1");
}

void readPacket(){
  UDP.parsePacket();
  UDP.read(packetBuffer, 255);
  msg = String(packetBuffer); 
}

void goIn(String D1, String D2, String roomID){
  //walk in the room
  if (msg == D1){
    check_time= Time;
    check_in= true;
    while(Time<check_time+1200){
      // Receive packet
      readPacket(); 
      Time = millis();
      //check second detector
      if(msg == D2){
        Serial.println(roomID + "-1");
        check_out=true;
        delay(200);
      }
    }
  } 
}

void goOut(String D1, String D2, String roomID){
   //walk out of the room
  //check second detector
  if (msg == D1){
    check_time= Time;
    check_out= false;
    while(Time<check_time+1200){
      // Receive packet
      readPacket();
      Time = millis();
      //check first detector
      if(msg == D2){
        Serial.println(roomID + " -1");
        check_in=false;
        delay(200);
      }
    }
  }
}