#include <DS1302.h>
//RTC
#define SCK_PIN 4
#define IO_PIN 3
#define RST_PIN 2
//녹음기
int REC = 13;
int Play =12;
//사운드센서
int Sound_Sensor = A0;
int Sensor_val;
//진동감지센서
int vib = 7;
//RTC
DS1302 rtc(RST_PIN,IO_PIN,SCK_PIN);


void setup() {
    
  Serial.begin(9600);
  digitalWrite(11,HIGH);
  
  //RTC
  rtc.halt(false);
  rtc.writeProtect(false);
  rtc.setDOW(WEDNESDAY);
  rtc.setTime(11,58,50);
  rtc.setDate(13,9,2017);
  //ISD
  pinMode(REC,OUTPUT);
  pinMode(Play,OUTPUT);
  Serial.println(" R : Start record");
  Serial.println(" S : Stop to record");  
  Serial.println(" P : recorded sound play");
  Serial.println(" s : recorded sound is stopped to played");

}

void loop() {

  // 사운드센서
   Sensor_val = analogRead(Sound_Sensor);
   
   if(Sensor_val > 600) {
   Serial.print(Sensor_val);
   Serial.print("\n");
   delay(20);
  }

  //진동감지센서
  long measurement = TP_init();
  delay(50);

  //ISD
  while(Serial.available()){
    switch(Serial.read()){
      case 'R':
      digitalWrite(REC,HIGH);
      break;
      case 'S':
      digitalWrite(REC,LOW);
      break;
      case 'P':
      digitalWrite(Play,HIGH);
      digitalWrite(Play,LOW);
      break;
      case 's':
      digitalWrite(Play,LOW);
      break;
    }
  }
}
//진동감지센서
long TP_init(){
  delay(10);
  long measurement = pulseIn(vib,HIGH);
  return measurement;
}
