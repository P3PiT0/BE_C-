// the setup function runs once when you press reset or power the board
const int pinLight=A0; //Analog output
int previous_state=1; //1 day, 0 night 
void setup() {
  Serial.begin(9600);
}

void loop() {
  int SensorValue = analogRead(pinLight);// [0;678]
  Serial.println(SensorValue);
  if (SensorValue < 200 && previous_state==1){
   Serial.println("Passage mode nuit"); 
   previous_state = 0; 
   //exception pour changer de mode 
  }
  else if (SensorValue >= 200 && previous_state==0) {
    Serial.println("Passage mode jour"); 
    previous_state = 1; 
   //exception pour changer de mode 
  }
  else {
    NULL; 
  }
  delay(500);// wait for a second
}
