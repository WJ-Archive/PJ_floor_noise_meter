#define SCK_PIN 4
#define IO_PIN 3
#define RST_PIN 2
#include <DS1302.h>

DS1302 rtc(RST_PIN,IO_PIN,SCK_PIN);
char *now;
void setup() {
 
  rtc.halt(false);
  rtc.writeProtect(false);
  Serial.begin(9600);

  rtc.setDOW(FRIDAY);
  rtc.setTime(11,58,50);
  rtc.setDate(13,9,2017);
  
}

void loop() {
    //now = rtc.getTimeStr();
    while(1){
    Serial.print("it is ");
    Serial.print(rtc.getDOWStr());
    Serial.print(" ");
    Serial.print(rtc.getDateStr());
    Serial.print(" ");
    Serial.print("and the time is ");
    Serial.println(rtc.getTimeStr());
    //Serial.println(now);

    delay(1000);
    }
    
}
