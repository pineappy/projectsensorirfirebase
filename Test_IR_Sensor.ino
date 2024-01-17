int IRSensor = 8; // connect ir sensor to arduino pin 2
int LED = 11; // conect Led to arduino pin 13

void setup() 
{
  pinMode (IRSensor, INPUT); // sensor pin INPUT
  pinMode (LED, OUTPUT); // Led pin OUTPUT
  Serial.begin(9600);
  delay(300);
  Serial.println("Simulasi Test IR Sensor");
}

void loop(){
  delay(300);
  Serial.print("IR Sensor value=  ");
  Serial.println(digitalRead(IRSensor));
  int statusSensor = digitalRead (IRSensor);  
  if (statusSensor == 1){
    digitalWrite(LED, LOW); // LED LOW
  }
  else{
    digitalWrite(LED, HIGH); // LED High
  }
  
}
