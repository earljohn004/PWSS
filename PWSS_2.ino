#include "Timer.h"
#include "Sleep_n0m1.h"
#include "TASKS.h"

#define INITIAL 100

Timer t;

byte sensorInterrupt = 0;  // 0 = digital pin 2
byte sensorPin       = 2;

volatile byte pulseCount;  
boolean status;
int eventSerial, eventReceive, eventSend;
int valvePin;
int total;

//Function Instance
void ISR_pulseCounter();
void event_SendPacket();
void event_ReceivePacket();

void setup()
{
  // Initialize a serial connection for reporting values to the host
  Serial.begin(9600);
  
  // Pin for Interrupt for flow sensor 
  pinMode(sensorPin, INPUT);
  pinMode(13, OUTPUT);
  digitalWrite(sensorPin, HIGH);
  eventReceive = t.every(500,event_ReceivePacket);
  eventSend = t.every(1000 * 20,event_SendPacket);
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
  detachInterrupt(sensorInterrupt);
  deltaBALANCE=1;
  if(pulseCount==PPL)
  {
	if(water_volume==0) water_volume=0;
	else water_volume--;
	pulseCount=0;
  }else pulseCount++;
  attachInterrupt(sensorInterrupt, ISR_pulseCounter, FALLING);
}

void event_SendPacket()
{
    sendFunction();
}

void event_ReceivePacket()
{
    receiveFunction();
}

void serialEvent() {
  int i = -1;
  while (Serial.available()) {
    // get the new byte:
	Serial.println(i);
    i++;
    unsigned char inChar = (char)Serial.read();
    received_data[i] = inChar;
    if (inChar == 69 ) {
        flagGlobal = 1;
    }
  }
}
