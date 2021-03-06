#include "Timer.h"
#include "Sleep_n0m1.h"
#include "TASKS.h"

Timer t;

byte sensorInterrupt = 0;  // 0 = digital pin 2
byte sensorPin       = 2;

volatile int pulseCount;  
boolean status;
int eventSerial, eventReceive, eventSend, eventValve;
int valvePin;
int total;
int iterator = -1; //For Serial

//Function Instance
void ISR_pulseCounter();
void event_SendPacket();
void event_ReceivePacket();
void event_ToggleValve();

void setup()
{
  /*All initializations are found here*/

  // Initialize a serial connection for reporting values to the host
  Serial.begin(38400);
  
  // Pin for Interrupt for flow sensor 
  pinMode(sensorPin, INPUT);
  pinMode(13, OUTPUT);

  pinMode(R_PIN, OUTPUT);
  pinMode(G_PIN, OUTPUT);
  pinMode(B_PIN, OUTPUT);

  digitalWrite(sensorPin, HIGH);

  digitalWrite(13,LOW);
  valveStatus = CLOSE;
  VALVE_flag=0;
  firstTimeConnection=-1;

  //digitalWrite(13,HIGH);
  //valveStatus=OPEN;
  
  eventReceive = t.every(500,event_ReceivePacket);
  eventSend = t.every(650,event_SendPacket); //changed Feb. 25, 2015 gabie 
  eventValve = t.every(900,event_ToggleValve);
  
  pulseCount        = 0;
  deltaBALANCE		= 0;
  water_volume		= 20;
 
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
  if(pulseCount==PPL || water_volume==0)
  {
	if(water_volume==0){
	   	water_volume=0;
		digitalWrite(13,LOW);
	}
	else{
	   	water_volume = water_volume - 1;
		pulseCount=0;
	}
  }else pulseCount = pulseCount + 1;
  attachInterrupt(sensorInterrupt, ISR_pulseCounter, FALLING);
}

void event_SendPacket()
{
    detachInterrupt(sensorInterrupt);
	sendFunction();
	attachInterrupt(sensorInterrupt, ISR_pulseCounter, FALLING);
}

void event_ReceivePacket()
{
    receiveFunction();
	iterator=-1;
}

void event_ToggleValve()
{
	valveFunction();
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    iterator+=1;
    unsigned char inChar = (unsigned char)Serial.read();
    received_data[iterator] = inChar;
    if (inChar == 0 ) {
        flagGlobal = 1;
		iterator=-1;
	   }
  }
}
