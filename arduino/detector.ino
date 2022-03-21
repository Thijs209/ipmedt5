#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <espnow.h>

//pinout
const int trigPinS1 = 13;
const int echoPinS1 = 15;
const int trigPinS2 = 12;
const int echoPinS2 = 14;

uint8_t broadcastAddress[] = {0xA8, 0x48, 0xFA, 0xD6, 0x8F, 0x2F};

typedef struct struct_message {
  char a[5];
} struct_message;

struct_message myData;

unsigned long lastTime = 0;  
unsigned long timerDelay = 2000;  // send readings timer

//wifi verbinding
const char *ssid     = "TelSam";
const char *password = "kikkers1234";

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

//define sound speed in cm
#define SOUND_SPEED 0.034

//average distance
int avgS1;
int avgS2;

//ime for calibration
int Hours = 14;
int Minutes = 43;
int Seconds = 30;

void setup() {
  //Serial start
  Serial.begin(115200);

  //define type of pin
  pinMode(trigPinS1, OUTPUT); 
  pinMode(echoPinS1, INPUT);
  pinMode(trigPinS2, OUTPUT); 
  pinMode(echoPinS2, INPUT);

  //connect to wifi
  Serial.println("loading wifi");
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  WiFi.mode(WIFI_STA);
  //start ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  // Register role of esp
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_register_send_cb(OnDataSent);
  // Register peer
  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);

  //start time register
  timeClient.begin();
  timeClient.setTimeOffset(3600);

  //load and calibrate sensor
  Serial.println("loading sensors");
  avgS1 = calibrateSensor(trigPinS1, echoPinS1);
  avgS2 = calibrateSensor(trigPinS2, echoPinS2);
}

void loop() {
  //tijd gevoelige acties uitvoeren
  timeSensitive();
  checkDistance();
}

//Confirmation of succesful dilivery
void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  Serial.print("Last Packet Send Status: ");
  if (sendStatus == 0){
    Serial.println("Delivery success");
  }
  else{
    Serial.println("Delivery fail");
  }
}

//tijd gevoelige acties
void timeSensitive(){
  timeClient.update();

  //caliberen alle sensoren
  if(timeClient.getHours() == Hours && timeClient.getMinutes() == Minutes && timeClient.getSeconds() > Seconds){
    Serial.println("calibrating sensors");
    Serial.println("will take about 2 minutes");
    avgS1 = calibrateSensor(trigPinS1, echoPinS1);
    avgS2 = calibrateSensor(trigPinS2, echoPinS2);
    Serial.println("Done calibrating");
    Serial.print("S1: ");
    Serial.println(avgS1);
    Serial.print("S2: ");
    Serial.println(avgS2);
  }
}

void checkDistance(){
  int s1 = readDistance(trigPinS1, echoPinS1);
  int s2 = readDistance(trigPinS1, echoPinS1);
  int s3 = readDistance(trigPinS1, echoPinS1);
  Serial.print("S1: ");
  Serial.println(s1);
  Serial.print("S2: ");
  Serial.println(s2);
  if(s1 < avgS1 && s2 < avgS2){
    if ((millis() - lastTime) > timerDelay) {
    // Set values to send
    strcpy(myData.a, "gate1");
    // Send message via ESP-NOW
    esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
    lastTime = millis();
    }
  }
}


//afstand tot sensor bepalen
int readDistance(int trig, int echo){
  long duration;
  float distanceCm;
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  distanceCm = duration * SOUND_SPEED/2;
  return distanceCm;
}


//individuele sensor caliberen
int calibrateSensor(int trig, int echo){
  Serial.println("calibrating Sensor");
  int reading = 0;
  int readingTotal = 0;
  for(int i=0; i <= 30; i++){
    reading = readDistance(trig, echo);
    readingTotal = readingTotal + reading;
    Serial.print(".");
    delay(1000);
  }
  int avg = readingTotal/30;
  return avg;
}
