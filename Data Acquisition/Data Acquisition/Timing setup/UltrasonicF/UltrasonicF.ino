const int trigPin = 10;
const int echoPin = 11;
unsigned long int tf;

long duration;
int distanceCm, distanceInch;

void setup() {
 Serial.begin(9600);
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);

pinMode(8,INPUT);
pinMode(6,OUTPUT);

}

void loop() {

while((digitalRead(8))==HIGH)
{  
  digitalWrite(trigPin, LOW);
delay(10);
digitalWrite(trigPin, HIGH);
delay(50);
digitalWrite(trigPin, LOW);

duration = pulseIn(echoPin, HIGH);
distanceCm= duration*0.034/2;

Serial.println(distanceCm); 
Serial.println(" cm");

if(distanceCm<=70)
{ 
digitalWrite(6,HIGH);
//delay(50);
//digitalWrite(6,LOW);
}
else
{
   digitalWrite(6,LOW);
}
}
digitalWrite(6,LOW);
}
