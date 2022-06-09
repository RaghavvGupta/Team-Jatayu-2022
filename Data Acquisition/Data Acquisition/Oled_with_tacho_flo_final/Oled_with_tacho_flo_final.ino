
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

const byte PulsesPerRevolution1 = 1,PulsesPerRevolution2 = 1,PulsesPerRevolution3 = 1,PulsesPerRevolution4 = 1,PulsesPerRevolution5 = 1; 
const unsigned long ZeroTimeout1 = 100000,ZeroTimeout2 = 100000,ZeroTimeout3 = 100000,ZeroTimeout4 = 100000,ZeroTimeout5 = 100000;  
const byte numReadings1 = 2,numReadings2 = 2,numReadings3 = 2,numReadings4 = 2,numReadings5 = 2;  
volatile unsigned long LastTimeWeMeasured1,LastTimeWeMeasured2,LastTimeWeMeasured3,LastTimeWeMeasured4,LastTimeWeMeasured5;  // Stores the last time we measured a pulse so we can calculate the period.
volatile unsigned long PeriodBetweenPulses1 = ZeroTimeout1+1000,PeriodBetweenPulses2 = ZeroTimeout2+1000,PeriodBetweenPulses3 = ZeroTimeout3+1000,PeriodBetweenPulses4 = ZeroTimeout4+1000,PeriodBetweenPulses5 = ZeroTimeout5+1000;  // Stores the period between pulses in microseconds.
volatile unsigned long PeriodAverage1 = ZeroTimeout1+1000,PeriodAverage2 = ZeroTimeout2+1000,PeriodAverage3 = ZeroTimeout3+1000,PeriodAverage4 = ZeroTimeout4+1000,PeriodAverage5 = ZeroTimeout5+1000;  // Stores the period between pulses in microseconds in total, if we are taking multiple pulses.
unsigned long FrequencyRaw1,FrequencyRaw2,FrequencyRaw3,FrequencyRaw4,FrequencyRaw5;  // Calculated frequency, based on the period. This has a lot of extra decimals without the decimal point.
unsigned long FrequencyReal1,FrequencyReal2,FrequencyReal3,FrequencyReal4,FrequencyReal5;  // Frequency without decimals.
unsigned long RPM1,RPM2,RPM3,RPM4,RPM5;  // Raw RPM without any processing.
unsigned int PulseCounter1 = 1,PulseCounter2 = 1,PulseCounter3 = 1,PulseCounter4 = 1,PulseCounter5 = 1;  // Counts the amount of pulse readings we took so we can average multiple pulses before calculating the period.
unsigned long PeriodSum1,PeriodSum2,PeriodSum3,PeriodSum4,PeriodSum5; 
unsigned long LastTimeCycleMeasure1 = LastTimeWeMeasured1,LastTimeCycleMeasure2 = LastTimeWeMeasured2,LastTimeCycleMeasure3 = LastTimeWeMeasured3,LastTimeCycleMeasure4 = LastTimeWeMeasured4,LastTimeCycleMeasure5 = LastTimeWeMeasured5; 
unsigned long CurrentMicros1 = micros(),CurrentMicros2 = micros(),CurrentMicros3 = micros(),CurrentMicros4 = micros(),CurrentMicros5 = micros(); 
unsigned int AmountOfReadings1 = 1,AmountOfReadings2 = 1,AmountOfReadings3 = 1,AmountOfReadings4 = 1,AmountOfReadings5 = 1;
unsigned int ZeroDebouncingExtra1,ZeroDebouncingExtra2,ZeroDebouncingExtra3,ZeroDebouncingExtra4,ZeroDebouncingExtra5; 
unsigned long readings1[numReadings1],readings2[numReadings2],readings3[numReadings3],readings4[numReadings4],readings5[numReadings5];  // The input.
unsigned long readIndex1,readIndex2,readIndex3,readIndex4,readIndex5;  // The index of the current reading.
unsigned long total1,total2,total3,total4,total5;  // The running total.
unsigned long average1,average2,average3,average4,average5;  // The RPM value after applying the smoothing.
//techo preset end

//flowm preset start
int flag=0;
int fuel;
void isr1(){
  flag++;
}
int pin7=7;
int val=0;
//flowm preset end

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#if (SSD1306_LCDHEIGHT != 64)

//#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif


#define YT_BMPWIDTH  64
#define YT_BMPHEIGHT 64
const unsigned char bitmap_YT[] PROGMEM = {
};




#define YT1_BMPWIDTH  91
#define YT1_BMPHEIGHT 64
const unsigned char bitmap_YT1[] PROGMEM = {
 };


const unsigned char audi_logo [] PROGMEM = {
};


int sensorValue = 0;
int voltage = 0;
const int analogInPin = A0;

//display.invertDisplay(true); // invert the colours of led display
//display.invertDisplay(false);
//display.drawPixel(10, 10, WHITE);//to highlight a particular pixel
void setup()   
{ 
  Serial.begin(9600);
 
  Serial2.begin(9600);
  
   pinMode(3,INPUT_PULLUP);
   pinMode(18,INPUT_PULLUP);
   pinMode(19,INPUT_PULLUP);

   
  attachInterrupt(digitalPinToInterrupt(18), Pulse_Event3, RISING); 
  attachInterrupt(digitalPinToInterrupt(19), Pulse_Event4, RISING); 

 //flowm setup start
 pinMode(3,INPUT_PULLUP);
 attachInterrupt(1,isr1, RISING);
 
 pinMode(7,INPUT_PULLUP);


 //flowm setup ends
 
 //display code
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize I2C addr to 0x3C ( for 128x64 Display )
  
  display.clearDisplay(); // clear the display before starting the program to avoid adafruit splashscreen ( *we can also skip it by modifing header file )
  // drawBitmap(x-axis position, y-axis position, bitmap data, bitmap width, bitmap height, color)
  /*
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("JAI JATAYU");
  delay(2000);
  */
  delay(1000);
}
/////////////////////////////////////////////////////////////////////////////////////////////



void loop() 
{ 
  //tacho code start
   LastTimeCycleMeasure1 = LastTimeWeMeasured1; 
  LastTimeCycleMeasure2 = LastTimeWeMeasured2; 
  LastTimeCycleMeasure3 = LastTimeWeMeasured3; 
  LastTimeCycleMeasure4 = LastTimeWeMeasured4; 
  LastTimeCycleMeasure5 = LastTimeWeMeasured5; 
  CurrentMicros1 = micros(); 
  CurrentMicros2 = micros(); 
  CurrentMicros3 = micros(); 
  CurrentMicros4 = micros(); 
  CurrentMicros5 = micros(); 
  if(CurrentMicros1 < LastTimeCycleMeasure1)
  {
    LastTimeCycleMeasure1 = CurrentMicros1;
  }
  if(CurrentMicros2 < LastTimeCycleMeasure2)
  {
    LastTimeCycleMeasure2 = CurrentMicros2;
  }
  if(CurrentMicros3 < LastTimeCycleMeasure3)
  {
    LastTimeCycleMeasure3 = CurrentMicros3;
  }
  if(CurrentMicros4 < LastTimeCycleMeasure4)
  {
    LastTimeCycleMeasure4 = CurrentMicros4;
  }
  if(CurrentMicros5 < LastTimeCycleMeasure5)
  {
    LastTimeCycleMeasure5 = CurrentMicros5;
  }
  FrequencyRaw1 = 10000000000 / PeriodAverage1;  
  FrequencyRaw2 = 10000000000 / PeriodAverage2;  
  FrequencyRaw3 = 10000000000 / PeriodAverage3;  
  FrequencyRaw4 = 10000000000 / PeriodAverage4;  
  FrequencyRaw5 = 10000000000 / PeriodAverage5;  
 
  if(PeriodBetweenPulses1 > ZeroTimeout1 - ZeroDebouncingExtra1 || CurrentMicros1 - LastTimeCycleMeasure1 > ZeroTimeout1 - ZeroDebouncingExtra1)
  { 
    FrequencyRaw1 = 0;  
    ZeroDebouncingExtra1 = 2000;  
  }
  else
  {
    ZeroDebouncingExtra1 = 0;  
  }
   if(PeriodBetweenPulses2 > ZeroTimeout2 - ZeroDebouncingExtra2 || CurrentMicros2 - LastTimeCycleMeasure2 > ZeroTimeout2 - ZeroDebouncingExtra2)
  { 
    FrequencyRaw2 = 0;  
    ZeroDebouncingExtra2 = 2000;  
  }
  else
  {
    ZeroDebouncingExtra2 = 0;  
  }
   if(PeriodBetweenPulses3 > ZeroTimeout3 - ZeroDebouncingExtra3 || CurrentMicros3 - LastTimeCycleMeasure3 > ZeroTimeout3 - ZeroDebouncingExtra3)
  { 
    FrequencyRaw3 = 0;  
    ZeroDebouncingExtra3 = 2000;  
  }
  else
  {
    ZeroDebouncingExtra3 = 0;  
  }
   if(PeriodBetweenPulses4 > ZeroTimeout4 - ZeroDebouncingExtra4 || CurrentMicros4 - LastTimeCycleMeasure4 > ZeroTimeout4 - ZeroDebouncingExtra4)
  { 
    FrequencyRaw4 = 0;  
    ZeroDebouncingExtra4 = 2000;  
  }
  else
  {
    ZeroDebouncingExtra4 = 0;  
  }
   if(PeriodBetweenPulses5 > ZeroTimeout5 - ZeroDebouncingExtra5 || CurrentMicros5 - LastTimeCycleMeasure5 > ZeroTimeout5 - ZeroDebouncingExtra5)
  { 
    FrequencyRaw5 = 0;  
    ZeroDebouncingExtra5 = 2000;  
  }
  else
  {
    ZeroDebouncingExtra5 = 0;  
  }
  

  FrequencyReal1 = FrequencyRaw1 / 10000; 
  FrequencyReal2 = FrequencyRaw2 / 10000; 
  FrequencyReal3 = FrequencyRaw3 / 10000; 
  FrequencyReal4 = FrequencyRaw4 / 10000; 
  FrequencyReal5 = FrequencyRaw5 / 10000;  

  // Calculate the RPM:
  RPM1 = FrequencyRaw1 / PulsesPerRevolution1 * 60; 
  RPM1 = RPM1 / 10000;
  RPM2 = FrequencyRaw2 / PulsesPerRevolution2 * 60; 
  RPM2 = RPM2 / 10000;
  RPM3 = FrequencyRaw3 / PulsesPerRevolution3 * 60; 
  RPM3 = RPM3 / 10000;
  RPM4 = FrequencyRaw4 / PulsesPerRevolution4 * 60; 
  RPM4 = RPM4 / 10000;
  RPM5 = FrequencyRaw5 / PulsesPerRevolution5 * 60; 
  RPM5 = RPM5 / 10000; 

  // Smoothing RPM:
  total1 = total1 - readings1[readIndex1];  
  readings1[readIndex1] = RPM1;  
  total1 = total1 + readings1[readIndex1];  
  readIndex1 = readIndex1 + 1;  
  
    total2 = total2 - readings2[readIndex2];  
  readings2[readIndex2] = RPM2;  
  total2 = total2 + readings2[readIndex2];  
  readIndex2 = readIndex2+ 1;  
   
    total3 = total3 - readings3[readIndex3];  
  readings3[readIndex3] = RPM3;  
  total3 = total3 + readings3[readIndex3];  
  readIndex3 = readIndex3 + 1;  
   
    total4 = total4 - readings4[readIndex4];  
  readings4[readIndex4] = RPM4;  
  total4 = total4 + readings4[readIndex4];  
  readIndex4 = readIndex4 + 1;  
   
    total5 = total5 - readings5[readIndex5];  
  readings5[readIndex5] = RPM5;  
  total5 = total5 + readings5[readIndex5];  
  readIndex5 = readIndex5 + 1;  

  if (readIndex1 >= numReadings1) 
  {
    readIndex1 = 0;  
  }
    if (readIndex2 >= numReadings2) 
  {
    readIndex2 = 0;  
  }
    if (readIndex3 >= numReadings3) 
  {
    readIndex3 = 0;  
  }
    if (readIndex4 >= numReadings4) 
  {
    readIndex4 = 0;  
  }
    if (readIndex5 >= numReadings5) 
  {
    readIndex5 = 0;  
  }
  
  average1 = total1 / numReadings1; 
  average2 = total2 / numReadings2; 
  average3 = total3 / numReadings3; 
  average4 = total4 / numReadings4; 
  average5 = total5 / numReadings5;  

 //tacho code end

//flowm starts
detachInterrupt(1);

val = digitalRead(pin7);  // read input value
  if (val == LOW) { 
    flag=0;   
  }

Serial.println(flag);
attachInterrupt(1,isr1, RISING);
//flowm ends
  
  /* 
  display.clearDisplay();                                   //clears screen for new transmission
  display.drawBitmap(0, 0, bitmap_YT, 64, 64, WHITE);       //select pixle location to start transmisssion and picture size to be displayed 
  display.display();                                        //screen strats to display
  delay(1000);  
  */
  display.clearDisplay();                         //clears screen to start new transmission
  display.setTextSize(3);                         //determining text asiwe
  display.setTextColor(WHITE);                    // font color
 // display.setCursor(1,20);                      //select pixle location 
 // display.print("RPM 1:");                      // text you want to display
 // display.println(average1);
 // display.print("RPM 2:");
 //display.println(average2);
  display.setCursor(0,0);
  display.print("  ");
  display.println(100-(flag/100));
  Serial.println(100-(flag/100));
  display.display();
 
//hc-05 start
  
    Serial2.print("engine=");
  Serial2.print(average3);

   Serial2.print(" Speed=");
  Serial2.print(average5*0.0016748*60);


   Serial2.print(" Flow=");
  Serial2.println(100-(flag/100));

//hc-05 end

   Serial.print("engine=");
  Serial.print(average3);

  
   Serial.print("Speed=");
  Serial.print(average5*0.0016748*60);

   Serial.print(" Flow=");
  Serial.println(100-(flag/100));
  
  
  
}


void Pulse_Event2() 
{

  PeriodBetweenPulses2 = micros() - LastTimeWeMeasured2;  
  LastTimeWeMeasured2 = micros(); 
  if(PulseCounter2 >= AmountOfReadings2)  
  {
    PeriodAverage2 = PeriodSum2 / AmountOfReadings2;  
    PulseCounter2 = 2;  
    PeriodSum2 = PeriodBetweenPulses2;  
    int RemapedAmountOfReadings2 = map(PeriodBetweenPulses2, 40000, 5000, 1, 10); 
    RemapedAmountOfReadings2 = constrain(RemapedAmountOfReadings2, 1, 10);  
    AmountOfReadings2 = RemapedAmountOfReadings2;  
  }
  else
  {
    PulseCounter2++;  
    PeriodSum2 = PeriodSum2 + PeriodBetweenPulses2; 
  }

}  // End of Pulse_Event2.

void Pulse_Event3() 
{

  PeriodBetweenPulses3 = micros() - LastTimeWeMeasured3;  
  LastTimeWeMeasured3 = micros(); 
  if(PulseCounter3 >= AmountOfReadings3)  
  {
    PeriodAverage3 = PeriodSum3 / AmountOfReadings3;  
    PulseCounter3 = 1;  
    PeriodSum3 = PeriodBetweenPulses3;  
    int RemapedAmountOfReadings3 = map(PeriodBetweenPulses3, 40000, 5000, 1, 10); 
    RemapedAmountOfReadings3 = constrain(RemapedAmountOfReadings3, 1, 10);  
    AmountOfReadings3 = RemapedAmountOfReadings3;  
  }
  else
  {
    PulseCounter3++;  
    PeriodSum3 = PeriodSum3 + PeriodBetweenPulses3; 
  }

}  // End of Pulse_Event3.

void Pulse_Event4() 
{

  PeriodBetweenPulses4 = micros() - LastTimeWeMeasured4;  
  LastTimeWeMeasured4 = micros(); 
  if(PulseCounter4 >= AmountOfReadings4)  
  {
    PeriodAverage4 = PeriodSum4 / AmountOfReadings4;  
    PulseCounter4 = 1;  
    PeriodSum4 = PeriodBetweenPulses4;  
    int RemapedAmountOfReadings4 = map(PeriodBetweenPulses4, 40000, 5000, 1, 10); 
    RemapedAmountOfReadings4 = constrain(RemapedAmountOfReadings4, 1, 10);  
    AmountOfReadings4 = RemapedAmountOfReadings4;  
  }
  else
  {
    PulseCounter4++;  
    PeriodSum4 = PeriodSum4 + PeriodBetweenPulses4; 
  }

}  // End of Pulse_Event4.
