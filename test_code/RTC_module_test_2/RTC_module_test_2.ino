#include <Wire.h>
#include <Time.h>
#include <DS1307RTC.h>

const char *monthName[12] ={
  "jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

tmElements_t tm;

void setup() {
  bool parse = false;
  bool config = false;

  if(getDate(__DATE__) && getTime(__TIME__)){
    parse = true;
    if(rtc.write(tm)){
      config = true;
    }
  }
}

void loop() {

}
