int REC = 13;
int Play =12;

void setup() {
Serial.begin(9600);
pinMode(REC,OUTPUT);
pinMode(Play,OUTPUT);
Serial.println(" R : Start record");
Serial.println(" S : Stop to record");  
Serial.println(" P : recorded sound play");
Serial.println(" s : recorded sound is stopped to played");

}

void loop() {
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
