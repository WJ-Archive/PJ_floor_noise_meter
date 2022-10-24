int sensorPin= 0;
int ledPin =11;
void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int value = analogRead(sensorPin);
  int intensity= map(value,20,300,0,255);

  analogWrite(ledPin,intensity);
  delay(10);
  Serial.println(value);
  delay(100);
}
