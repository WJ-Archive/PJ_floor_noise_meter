int ledPin = 13;
int vib = 2;
void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin,OUTPUT);
  pinMode(vib,INPUT);
  Serial.begin(9600);
  Serial.println("---------------vibration demo------------");
  
}

void loop() {
  // put your main code here, to run repeatedly:
  long measurement = TP_init();
  delay(50);
  Serial.print("measurment = ");
  Serial.println(measurement);

}

long TP_init(){
  delay(10);
  long measurement = pulseIn(vib,HIGH);
  return measurement;
}

