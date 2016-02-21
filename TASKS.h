/*
  TASKS.h
 *
 *  Created on: Feb 08, 2015
 *      Author: ABAQUITA
 */

#ifndef TASKS_H_
#define TASKS_H_

#define PPL	461

/* P A C K E T    F O R M A T */
#define HEADER 0
#define WHAT_ID 1
#define TYPE 2
#define DATA 3
#define CHECKSUM 4
#define TERMINATOR 5

/* T O   B E   R E C E I V E D   R E Q U E S T   T Y P E S */
#define QUERY			10 
#define VALVE_SW		11
#define LOAD			12

/* T O   B E   S E N T   R E Q U E S T   T Y P E S */
#define BALANCE_UPDATE	2
#define STATUS			3

///* L E D   S T A T U S */
//#define HIGHH	32		//BLU
//#define MIDHI	16		//BLU+GRN
//#define MID		8		//GRN
//#define MIDLO	4		//GRN+RED
//#define LOWw	2		//RED
//
//#define OPEN 0
//#define CLOSE 1
/*****************************   GLOBAL VARIABLES   **********************************/
 unsigned char WCS_ID[4]={1,1,1,30}; //decode WCS_ID = ((1*1*1)+29) WCS_ID=30
 unsigned char received_data[16]={0};	//Receiver
 unsigned char send_data[16]={0};		//Send
 unsigned char RQ_TYPE=0;
 int packetReceived=0;

 const byte PACKET_TYPEB = 16;
 const byte PACKET_TYPEA = 12;

 int checksum1=0, checksum2=0;
 int flagGlobal=0;
 int flagQuery=0;
 boolean toggle=false;

/* Flow Sensor */
 unsigned char volume_balance[4]={0};

int water_volume = 0;
int deltaBALANCE;
int VALVE_flag=0;

void sendFunction();

/*****************************   USER FUNCTIONS   **********************************/
 int ComputeChecksum(unsigned char *packet, int len)
{
	int index;
	int sum = 0;
	for(index=0; index<len; index++)
		sum = sum +  (int)packet[index];
	return sum;
}

 void encodeVolume(int volume)
{
	int temp = 0;
		
	volume_balance[0] = (volume/1000) + 48;
	temp = volume%1000;
	volume_balance[1] = (temp/100) + 48;
	temp = temp%100;
	volume_balance[2] = (temp/10) + 48;
	volume_balance[3] = (temp%10) + 48;	
}

 int decodeVolume(unsigned char *vol)
{
	int voltmp=0;
	voltmp = (vol[9]-48)*1000;
	voltmp += (vol[10]-48)*100;
	voltmp += (vol[11]-48)*10;
	voltmp += vol[12]-48;
	return voltmp;
}

void receiveFunction() 
{
	int i=-1;	//iterator
	int state=0, data_counter=0;
   // int flag=0;
	while(1){
		if(flagGlobal==1/*No of elements is not equal to zero*/) 
		{
			i+=1; //increment array counter at the start
			switch(state)
			{
				case HEADER:
                    
                            if(data_counter == 0) //header = 0
							{
								if(received_data[i] == '4'){
                                    data_counter++;
                                }
								else{
									data_counter = 0;
									i = -1;
                                    flagGlobal=0;

								}
							}
							else if(data_counter == 1)
							{
								if(received_data[i] == 'p'){
                                    data_counter++;
                                }
								else{
									data_counter = 0;
									i = -1;
                                    flagGlobal=0;
								}
							}
							else if(data_counter == 2)
							{
								if(received_data[i] == '?'){
                                    data_counter++;
                                }
								else{
									data_counter = 0;
									i = -1;
                                    flagGlobal=0;
								}						
							}
							else if(data_counter == 3)
							{
								if(received_data[i] == '2'){
									data_counter = 0;
									state = WHAT_ID;
								}else{
									data_counter = 0;
									i = -1;
                                    flagGlobal=0;
								}						
							}
							break;
					
				case WHAT_ID: if(received_data[i] != WCS_ID[data_counter]) //1
                              {	  									  
								  state = HEADER;
								  data_counter = 0;
								  i = -1;
                                  flagGlobal=0;
							  }
							  else
							  {
								  if(data_counter == 3){
									  state = TYPE;
									  data_counter = 0;
								  }else 
                                  {
                                      data_counter++;
                                  }
							  }
							  break;
							 
				case TYPE: RQ_TYPE = received_data[i]; //2
						   if(received_data[i] == QUERY || received_data[i] == VALVE_SW)
						   {
							   state = CHECKSUM;
							   flagQuery = 1;

							   
						   }
						   else if(received_data[i] == LOAD){
							     state = DATA;
							     
						   }
						   break;
						   
				case DATA: if(data_counter == 3) //3
                           {
								data_counter = 0;
								state = CHECKSUM;
						   }else data_counter++;
						   break;
				
				case CHECKSUM:  if(data_counter == 1)
								{
									
									checksum1 = (checksum1 & 0xFFFF)|received_data[i];
									checksum2 = ComputeChecksum(received_data, i-1);
									if(checksum1 == checksum2)
									{
										state = TERMINATOR;
									}
									else
									{
										packetReceived = 0;
										i= -1;
										data_counter = 0;
										state = HEADER;
                                        flagGlobal=0;
									}
									
								}
								else 
								{ checksum1 = 0;
									checksum2 = 0;
									data_counter++;
									checksum1 = received_data[i] << 8;
								}
								
								
								break;
								
				case TERMINATOR:	
									data_counter = 0;
									i = -1;
									packetReceived = 1;
									state = HEADER;
                                    flagGlobal=0;
									if(flagQuery==1)
										sendFunction();
									break;
			}//switch end block
		}//if end block	
        else {
			break;
		}
	}//while end block	

}

void sendFunction()
{
	int i=0, checksum=0;
	//int checksum=0;
	
	while(1)
	{		
		//for(i=0; i<15;i++) send_data[i]='\0';
		send_data[0] = 52;	//4
		send_data[1] = 112;	//p
		send_data[2] = 63;	//?
		send_data[3] = 50;	//2
		send_data[4] = WCS_ID[0];	
		send_data[5] = WCS_ID[1];
		send_data[6] = WCS_ID[2];
		send_data[7] = WCS_ID[3];	//if WCS_ID = 1,1,1,6 : chksum = Header + ID = 286
		
		if(packetReceived)
		{
			switch(RQ_TYPE)
			{
				case QUERY:
						if(deltaBALANCE){
							deltaBALANCE=0;
							encodeVolume(water_volume);
							send_data[8]  = BALANCE_UPDATE;
							send_data[9]  = volume_balance[0]; 
							send_data[10] = volume_balance[1];
							send_data[11] = volume_balance[2];
							send_data[12] = volume_balance[3];
							checksum = ComputeChecksum(send_data, 13);	//chksum : 318 = 0000 0001 0011 1110
							send_data[13] = checksum >> 8;
							send_data[14] = checksum;
							send_data[15] = 69;//0
                            
                            Serial.write(send_data,PACKET_TYPEB);
						}
						else{
							send_data[8]  = STATUS;		//I AM ALIVE!
							checksum = ComputeChecksum(send_data, 9);	//chksum : 318 = 0000 0001 | 0010 0001
							send_data[9]  = checksum >> 8;
							send_data[10] = checksum;
							send_data[11] = 69;//0
                           
                            Serial.write(send_data,PACKET_TYPEA);
							
						}
						packetReceived=0;
						break;
						
				case VALVE_SW:
						VALVE_flag=1;
						packetReceived=0;
						break;
						
				case LOAD:	
							water_volume += decodeVolume(received_data);
							received_data[8] = QUERY;
							RQ_TYPE = QUERY;
							deltaBALANCE=1;
							break;
			}//switch end block
			
		}//if end block
        else {
			break;
		}
	}//while loop end block
}
void valveFunction()
{
	if(VALVE_flag==1)
	{
		toggle=!toggle;	
		digitalWrite(13,toggle); VALVE_flag=0; }	

	// add code for water volume closure
		
}
#endif /* TASKS_H_ */
