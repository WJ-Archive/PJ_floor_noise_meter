#include <DS1302.h>
#include <math.h>
#include <SoftwareSerial.h>
#include "interlayer_noise.h"

#define EN_RTC_SET

// RTC module 
#define SCK_PIN   2
#define SDA_PIN   3
#define RST_PIN   4
// Recoder module
#define REC_PIN   13
#define PLAY_PIN  12
// RGB module
#define RED_PIN   5
#define GREEN_PIN 6
#define BLUE_PIN  7
// Bluetooth module
#define BT_TX_PIN 8   //Tx (보내는핀 설정)
#define BT_RX_PIN 9   //Rx (받는핀 설정)
// Read analog signal
#define SOUND_PIN 0

DS1302 rtc(RST_PIN,SDA_PIN,SCK_PIN);
SoftwareSerial mySerial(BT_TX_PIN, BT_RX_PIN);  //시리얼 통신을 위한 객체선언

NoiseFIFO Que;

int color=0;
double S_timer=0;
int timecheck=0;
unsigned char chBT;
void timeCheck();
void btRecord();
void setColor(int red,int green,int blue);
double measureNoise (int AnalogPin);

void setup() {
  Serial.begin(9600); //시리얼 모니터
  mySerial.begin(9600); //블루투스 시리얼
  
#ifdef EN_RTC_SET
  rtc.halt(false);
  rtc.writeProtect(false);
  rtc.setDOW(SATURDAY);
  rtc.setTime(8,56,00);
  rtc.setDate(13,11,2017);
#endif

  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  setColor(0,255,0);

}//setup

void loop() {
  int maxVolts_s = 0;    
  int valBT1, valBT2, valDB1, valDB2;
  double volts;


  // 시간체크 (주간/야간)
  timeCheck();
  
  // 녹음관련 ...
  btRecord();

  // 소리측정 ...
  volts = measureNoise (SOUND_PIN);
  //Serial.println ( 25*log10 (volts)+30); // logarithm of x to base 10. 0.03초에 한번 출력
  //1000ms(1초) 안에 30ms 동안 센싱해서 얻은 값중 제일큰값을 뽑아온다, 
  if(maxVolts_s < 25*log10(volts)+30)
    maxVolts_s = 25*log10(volts)+30;
  valDB1 = (maxVolts_s/10)+48;
  valDB2 = (maxVolts_s%10)+48;
  mySerial.write(valDB1);
  mySerial.write(valDB2);

  // 소리 1초씩 저장
  if(millis()>=S_timer){
    
    Que.enqueue(maxVolts_s);
    S_timer = S_timer + 1000;
    Serial.println(maxVolts_s);
    Serial.println(Que.Leq());
    // 층간소음도 범위 이상이면 앱에 소음정보전달
    if( (timecheck == 0 && Que.Leq() >= 43 && Que.maxNoise() >= 56 ) || (timecheck == 1 && Que.Leq() >= 38 && Que.maxNoise() >= 52) ) {
      // 1분등가소음도 앱에 전달
      valBT1 = (Que.Leq()/10)+48;
      valBT2 = (Que.Leq()%10)+48;
//      mySerial.write(valBT1);
//      mySerial.write(valBT2);
            
      // 최고소음도 앱에 전달
      valBT1 = (Que.maxNoise()/10)+48;
      valBT2 = (Que.maxNoise()%10)+48;
//      mySerial.write(valBT1);
//      mySerial.write(valBT2);
    }

    // 소음도에 따라 RGB 색설정 
    color = (maxVolts_s > 43 && color != 2);
    
    if( (timecheck == 0 && Que.Leq() >= 43 && Que.maxNoise() >= 57 ) || (timecheck == 1 && Que.Leq() >= 38 && Que.maxNoise() >= 52) )
      color = 2;
      
    switch(color) {
      case 0 : setColor(0,255,0); break;
      case 1 : setColor(0,0,255); break;
      case 2 : setColor(255,0,0); break;
    }
  }
  //if(startMillis == 0 ) S_timer = 0;  //millis 함수는 5일뒤 면 0 으로 초기화 된다고 한다. 그럼 같이 올라가던 S_timer 도 초기화
}

void setColor(int red,int green,int blue){
  analogWrite(RED_PIN,red);
  analogWrite(GREEN_PIN,green);
  analogWrite(BLUE_PIN,blue);
}

void timeCheck() {
    String strMor = "06:00:00\0";
    String strAft = "20:00:00\0";
    String strCheck = rtc.getTimeStr();
    
    if(strMor==strCheck)        timecheck = 0;
    else if(strAft == strCheck) timecheck = 1;
}


void btRecord() {
  unsigned char chBT; 
  
  //if(mySerial.available()){
    chBT = mySerial.read();
    //Serial.println(chBT);
    if (chBT == 'R' || chBT =='r'){
      digitalWrite(REC_PIN,HIGH);
    }else if(chBT == 'P' || chBT =='p'){
      digitalWrite(PLAY_PIN,HIGH);
      digitalWrite(PLAY_PIN,LOW);
    }else if(chBT == 'S' || chBT =='s'){
      digitalWrite(REC_PIN,LOW);
    }
  //}
}

double measureNoise (int AnalogPin) {
  const int sampleWindow = 300; //샘플링 시간 ms
  unsigned int signalMax = 0;
  unsigned int signalMin = 1024;
  unsigned int sample;
  unsigned int peakToPeak = 0;   // 음성신호의 진폭
  unsigned long startMillis = millis(); // 생플링 시작
  
  // 샘플링 구간동안 최댓값과 최소값을 읽어들입니다.
  while (millis() - startMillis < sampleWindow)
  {
    sample = analogRead(AnalogPin);
    if (sample < 1024) {  // toss out spurious readings
      if (sample > signalMax)
        signalMax = sample;  // save just the max levels
      if (sample < signalMin)
        signalMin = sample;  // save just the min levels
    }
  }
  peakToPeak = signalMax - signalMin;  // 최대값에서 최소값을 빼서 진폭을 계산
  
  return peakToPeak;
}


