#include <arduino-timer.h>

const int BUTTON_1 = 10;
const int BUTTON_2 = 9;

bool check_in= false;
bool check_out= false;

const int LED=12;
int data=0;
char object=' ';
bool pressed = false;
long check_time= 0;
int aantal_mensen=0;
long time=0;


void setup(){
    pinMode(BUTTON_1, INPUT_PULLUP);
    pinMode(BUTTON_2, INPUT_PULLUP);
    pinMode(LED, OUTPUT);
    Serial.begin(9600);

}

void loop(){
  time = millis();
//  Serial.println(time);

  if (!digitalRead(BUTTON_1)){
    check_time= time;
    check_in= true;
    Serial.print("hoi");
    Serial.println(check_time);
    Serial.println(time);

    while(time<check_time+1200){
        Serial.println(time);

    time = millis();
      if(!digitalRead(BUTTON_2)){
        aantal_mensen++;
        check_out=true;
        delay(200);
//        break;

      }
//    Serial.println('w');
    }
  }
  if (!digitalRead(BUTTON_2)){
    check_time= time;
    check_out= false;
    Serial.println("hoii");

    while(time<check_time+1200){
        time = millis();

      if(!digitalRead(BUTTON_1)){
        aantal_mensen--;
        check_in=false;
        delay(200);
//        break;
      }
//    Serial.println('w');
    }
  }

 
if(aantal_mensen>0){
      Serial.println(aantal_mensen);

     digitalWrite(LED, HIGH);
  }else{
       Serial.println(aantal_mensen);

       digitalWrite(LED, LOW);
  }

}
