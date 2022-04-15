#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <TM1637Display.h>
 
// Set AP credentials
#define AP_SSID "TheOtherESP"
#define AP_PASS "flashmeifyoucan"

#define CLK 14 //D5
#define DIO 12 //D6

///TM1637Display display(CLK, DIO); 
TM1637Display display(CLK, DIO);

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
int conGate = 0;

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

  display.setBrightness(0x0a); 
  display.clear();
}
 
void loop() {
  Time = millis();
  readPacket();
  checkConnect();
  goIn("gate1", "gate2", "Room1");
  goOut("gate2", "gate1", "Room1");
}

String readPacket(){
  UDP.parsePacket();
  UDP.read(packetBuffer, 255);
  msg = String(packetBuffer); 
  return msg;
}

void checkConnect(){
  if(readPacket() == "con"){
    conGate++;
    display.showNumberDec(conGate);
    Serial.println("conGate");
    Serial.println(conGate);
  }
  if(conGate == 0){
    Serial.println("zero");
    display.clear();
    delay(100);
    display.showNumberDec(0);
  }
}

void goIn(String D1, String D2, String roomID){
  //walk in the room
  if (readPacket() == D1){
    check_time= Time;
    check_in= true;
    while(Time<check_time+1200){
      // Receive packet
      Time = millis();
      //check second detector
      if(readPacket() == D2){
        Serial.println(roomID + " +1");
        check_out=true;
        delay(200);
      }
    }
  } 
}

void goOut(String D1, String D2, String roomID){
   //walk out of the room
  //check second detector
  if (readPacket() == D1){
    check_time= Time;
    check_out= false;
    while(Time<check_time+1200){
      // Receive packet
      readPacket();
      Time = millis();
      //check first detector
      if(readPacket() == D2){
        Serial.println(roomID + " -1");
        check_in=false;
        delay(200);
      }
    }
  }
}
