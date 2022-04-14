#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

//pinout
const int trigPinS1 = 13;
const int echoPinS1 = 15;
const int trigPinS2 = 12;
const int echoPinS2 = 14;


//wifi verbinding
#define WIFI_SSID "TheOtherESP"
#define WIFI_PASS "flashmeifyoucan"

// UDP communication with other esp
WiFiUDP UDP;
IPAddress remote_IP(192,168,4,1);
#define UDP_PORT 4210

//define sound speed in cm
#define SOUND_SPEED 0.034

//average distance
int avgS1;
int avgS2;
int detected = 0;

void setup() {
  //Serial start
  Serial.begin(115200);

  //define type of pin
  pinMode(trigPinS1, OUTPUT); 
  pinMode(echoPinS1, INPUT);
  pinMode(trigPinS2, OUTPUT); 
  pinMode(echoPinS2, INPUT);

  // Begin WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  WiFi.mode(WIFI_STA);
  
  // Connecting to WiFi...
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  // Loop continuously while WiFi is not connected
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print(".");
  }
  
  // Connected to WiFi
  Serial.println();
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());
 
  // Begin UDP port
  UDP.begin(UDP_PORT);
  Serial.print("Opening UDP port ");
  Serial.println(UDP_PORT);
  
  //load and calibrate sensor
  Serial.println("loading sensors");
  avgS1 = calibrateSensor(trigPinS1, echoPinS1);
  avgS2 = calibrateSensor(trigPinS2, echoPinS2);

  UDP.beginPacket(remote_IP, UDP_PORT);
  UDP.write("con");
  UDP.endPacket();
  UDP.beginPacket(remote_IP, UDP_PORT);
  UDP.write("0000");
  UDP.endPacket();
}

//keeps checking distance
void loop() {
  checkDistance();
  delay(100);
}


//check dinstance
void checkDistance(){
  int s1 = readDistance(trigPinS1, echoPinS1);
  int s2 = readDistance(trigPinS2, echoPinS2);
  
  Serial.print("S1: ");
  Serial.println(s1);
  Serial.print("S2: ");
  Serial.println(s2);
  Serial.print("avgS1: ");
  Serial.println(avgS1);
  Serial.print("avgS2: ");
  Serial.println(avgS2);
  if(s1 < avgS1*0.75 && s2 < avgS2*0.75){
    detected = detected + 1;
    Serial.println(detected);
  }
  if(detected >= 2){
    Serial.print("detected");
    UDP.beginPacket(remote_IP, UDP_PORT);
    UDP.write("gate2"); //name of detector, for seconde detector gate2, thirde gate3 etc..
    UDP.endPacket();
    delay(10);
    UDP.beginPacket(remote_IP, UDP_PORT);
    UDP.write("00000");
    UDP.endPacket();
    detected = 0;
  }
}


//read disrance from sencor to floor
int readDistance(int trig, int echo){
  long duration;
  int distanceCm;
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  distanceCm = duration * SOUND_SPEED/2;
  delay(10);
  return distanceCm;
}


//calibrate each sensor
int calibrateSensor(int trig, int echo){
  Serial.println("calibrating Sensor");
  int reading = 0;
  int readingTotal = 0;
  for(int i=0; i <= 300; i++){
    reading = readDistance(trig, echo);
    readingTotal = readingTotal + reading;
    Serial.print(".");
    delay(100);
  }
  int avg = readingTotal/300;
  return avg;
}