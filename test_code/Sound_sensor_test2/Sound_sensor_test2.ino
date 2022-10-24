int Sound_Sensor = A0;
int Sensor_val;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Sensor_val = analogRead(Sound_Sensor);

  if(Sensor_val > 600) {
    Serial.print(Sensor_val);
    Serial.print("\n");
    delay(20);
  }
}
