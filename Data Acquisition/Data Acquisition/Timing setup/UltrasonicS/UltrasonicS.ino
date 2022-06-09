             
const int trigPin = 10;
const int echoPin = 11;
//const int btrigPin = 5;
//const int bechoPin = 4;
float ti;
float tf;
 float t;
long duration;
int distanceCm, distanceInch;

void setup() {
 Serial.begin(9600);
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);

pinMode(8,OUTPUT);
pinMode(6,INPUT);
}

void loop() {
digitalWrite(8,LOW);
  
digitalWrite(trigPin, LOW);
delay(10);
digitalWrite(trigPin, HIGH);
delay(50);
digitalWrite(trigPin, LOW);

duration = pulseIn(echoPin, HIGH);
distanceCm= duration*0.034/2;
//distanceInch = duration*0.0133/2;

if(distanceCm<=70)
{ Serial.println("ti:");
  ti= millis();
//Serial.println(ti);
digitalWrite(8,HIGH);
//delay(3000);
//digitalWrite(8,LOW);
digitalRead(6);

while((digitalRead(6))==LOW)
{
  }
  if((digitalRead(6))==HIGH)
  {
 //  Serial.print("OK");
    tf=millis();
   // Serial.println("tf:");
  //  Serial.println(tf);
    
  }
digitalWrite(8,LOW);
}
else{
  digitalWrite(8,LOW);
}

//Serial.println(duration);
//Serial.print("Distance: "); 
//Serial.println(distanceCm); 
//Serial.println(" cm");
//Serial.println(ti);

//Serial.println(" cm");
delay(10);
//Serial.print("Distance: ");
//Serial.print(distanceInch);
//Serial.println(" inch");
//delay(10);

t=(tf-ti)/1000;
Serial.print("time:");
Serial.println(t);

}
