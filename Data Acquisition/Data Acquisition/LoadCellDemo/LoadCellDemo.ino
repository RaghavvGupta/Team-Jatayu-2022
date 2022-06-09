#include <HX711.h>

#include <HX711.h>

#include "HX711.h"
/*
 * white to GND       VCC-grey
 * grey to 5V         GND-red
 * blue to 3          DT-blue  ---   3
 * purple to 2        SCK-purple --- 2
 */

HX711 cell(3, 2);

void setup() {
  Serial.begin(9600);
}

unsigned long val = 0;
float count = 0;

void loop() {
  //count = count + 1;
  
  // Use only one of these
  //val = ((count-1)/count) * val    +  (1/count) * cell.read(); // take long term average
  //val = 0.5 * val    +   0.5 * cell.read(); // take recent average

  //200kg load cell as shocker
  val = cell.read(); // most recent reading
  val = 0.9 * val    +   0.1 * cell.read();
 //Serial.println((val-8373728)/19.50);
  Serial.println((val));
//0kg=8384421
//4kg=72610
//28kg=8921082
//without driver= 10222514
//with driver(rohan bhaiya)=




  //200 kg load cell as brake pedal
  //Serial.println( (val-8392509)/20.67);
  //18-08-2019(mounted) ---- zero =8392509
  //zero=8380305   //5kg=63368    //Serial.println( (val-8383208)/12.67);   //for 200kg load cell
  //zero=8022047   //2kg=8907707    // for 5kg load cell
/*

  19 aug 21
  static = 8388837
  4kg = 
  */
  
}
