#include "Timer.h"
#include "Sleep_n0m1.h"
#include "functions.h"

#define INITIAL 100

Timer t;

byte sensorInterrupt = 0;  // 0 = digital pin 2
byte sensorPin       = 2;

volatile byte pulseCount;  
boolean status;
int eventSerial, eventValve, eventTest;
int valvePin;
int total;

//Function Instance
void ISR_pulseCounter();
void waterFlow();
void test();
void valveStatus();
void testPrint();
//void ISR_serialEvent();

void setup()
{
  // Initialize a serial connection for reporting values to the host
  Serial.begin(9600);
  //mySerial.begin(9600);
  
  // Pin for Interrupt for flow sensor 
  pinMode(sensorPin, INPUT);
  pinMode(13, OUTPUT);
  digitalWrite(sensorPin, HIGH);
  eventSerial = t.every(1000*5, waterFlow);
  eventValve = t.every(2000,valveStatus);
  eventTest = t.every(400,testPrint);
  //remaining = INITIAL;
  
  pulseCount        = 0;
  //Interrut 0 at pin 2
  attachInterrupt(sensorInterrupt, ISR_pulseCounter, FALLING);
}


void loop()
{
	t.update();
}

/*
Interrupt Service Routine
 */
void ISR_pulseCounter()
{
  // Increment the pulse counter
  pulseCount++;
}


/* Event functions */
void waterFlow()
{
    detachInterrupt(sensorInterrupt);
	  //remaining = remaining-(pulseCount/100); 
	  total = total + pulseCount;
		if(total >=1000) status = true;
		else status=false;
	  Serial.println(total);	
	  pulseCount=0;
    attachInterrupt(sensorInterrupt, ISR_pulseCounter, FALLING);
}

void serialEvent()
{
	while(Serial.available()){
	
		char inChar =(char) Serial.read();
		if(inChar=='0'){
			status=false;
			total=0;
			pulseCount=0;
			
		}
	}
}

void valveStatus()
{
	if(status==true)
		digitalWrite(13,HIGH);
	else
		digitalWrite(13,LOW);
}

void testPrint()
{
	unsigned char test[5] = "1234";
	decodeVolume(test);	
}

