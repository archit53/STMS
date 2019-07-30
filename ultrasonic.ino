
int trigPin = 11;    // Trigger
int echoPin = 12;    // Echo
long duration, cm, inches;
float per, stat1, stat2;
 
void setup() {
  //Serial Port begin
  Serial.begin (9600);
  //Define inputs and outputs
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}
 
void loop() {
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
 
  // Convert the time into a distance
  cm = (duration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
  inches = (duration/2) / 74;   // Divide by 74 or multiply by 0.0135
  
  if (cm > 0 && cm < 10)
  {
    stat1 = 50-cm;
    stat2 = stat1/50;
    per = stat2 * 100;
    Serial.println("Needs To Collect");
    Serial.println();
    
    Serial.print(per);
    Serial.print("%");
    Serial.println();
  }
  else if (cm >= 10 && cm < 20)
  {
    stat1 = 50-cm;
    stat2 = stat1/50;
    per = stat2 * 100;
    Serial.println("At Level 4");
    Serial.print(per);
    Serial.print("%");
    Serial.println();
  }
  else if (cm >= 20 && cm < 30)
  {
    stat1 = 50-cm;
    stat2 = stat1/50;
    per = stat2 * 100;
    Serial.println("At Level 3");
    Serial.print(per);
    Serial.print("%");
    Serial.println();
  }
  else if (cm >= 30 && cm < 40)
  {
    stat1 = 50-cm;
    stat2 = stat1/50;
    per = stat2 * 100;
    Serial.println("At Level 2");
    Serial.print(per);
    Serial.print("%");
    Serial.println();
  }
  else if (cm >= 40 && cm < 50)
  {
    stat1 = 50-cm;
    stat2 = stat1/50;
    per = stat2 * 100;
    Serial.println("At Level 1");
    Serial.print(per);
    Serial.print("%");
    Serial.println();
  }
  
  delay(250);
}
