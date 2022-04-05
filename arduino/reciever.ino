#include <ESP8266WiFi.h>
#include <arduino-timer.h>
#include <espnow.h>

bool check_in= false;
bool check_out= false;

int data=0;
char object=' ';
bool pressed = false;
long check_time= 0;
int aantal_mensen=0;
long Time=0;
char* msg;

// Structure example to receive data
// Must match the sender structure
typedef struct struct_message {
    char a[5];
} struct_message;

// Create a struct_message called myData
struct_message myData;

 
void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(OnDataRecv);
}


// Callback function that will be executed when data is received
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.println(myData.a);
  msg = myData.a;
}

void loop() {
    Time = millis();

  //lopen in kamer
  if (msg == "gate1"){
    check_time= Time;
    check_in= true;
    Serial.print("hoi");
    Serial.println(check_time);
    Serial.println(Time);

    while(Time<check_time+1200){
        Serial.println(Time);

    Time = millis();
      if(msg == "gate2"){
        aantal_mensen++;
        check_out=true;
        delay(200);
      }
    }
  }

  //lopen uit kamer
  if (msg == "gate2"){
    check_time= Time;
    check_out= false;
    Serial.println("hoii");

    while(time<check_time+1200){
        Time = millis();

      if(msg == "gamte1"){
        aantal_mensen--;
        check_in=false;
        delay(200);
      }
    }
  }

  //aantal mensen in de kamer
  if(aantal_mensen>0){
      Serial.println(aantal_mensen);
  }
  else{
       Serial.println(aantal_mensen);
  }
}
