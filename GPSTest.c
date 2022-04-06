/*  
 *  GPS Module
 *  
 *  Copyright (C) Libelium Comunicaciones Distribuidas S.L. 
 *  http://www.libelium.com 
 *  
 *  This program is free software: you can redistribute it and/or modify 
 *  it under the terms of the GNU General Public License as published by 
 *  the Free Software Foundation, either version 3 of the License, or 
 *  (at your option) any later version. 
 *  a
 *  This program is distributed in the hope that it will be useful, 
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of 
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License 
 *  along with this program.  If not, see http://www.gnu.org/licenses/. 
 *  
 *  Version:           2.0
 *  Design:            David Gascón 
 *  Implementation:    Marcos Yarza, Jorge Casanova & Marcos Martinez
 */

//Include ArduPi library
#include "arduPi.h"


// variables
char byteGPS = 0;
int i = 0;
int h = 0;

// Buffers for data input
char inBuffer[300] = "";
char GPS_RMC[100]="";
char GPS_GGA[100]="";

void setup(){

  //setup for mySerial port
  Serial.begin(4800); 
  printf("Starting...\n");
  delay(1000);
}

void loop(){
	
  
   // Read the RMC sentence from GPS
  byteGPS = 0;
  byteGPS = Serial.read();
  while(byteGPS != 'R'){
    byteGPS = Serial.read();
  }
  
  GPS_RMC[0]='$';
  GPS_RMC[1]='G';
  GPS_RMC[2]='P';    
  GPS_RMC[3]='R';
  
    i = 4;
    while(byteGPS != '*'){                  
      byteGPS = Serial.read();         
      inBuffer[i]=byteGPS;
      GPS_RMC[i]=byteGPS;
      i++;                      
  }
  
  // Read GGA sentence from GPS
  byteGPS = 0;
  byteGPS = Serial.read();
  while(byteGPS != 'A'){
    byteGPS = Serial.read();
  }
  GPS_GGA[0]='$';
  GPS_GGA[1]='G';
  GPS_GGA[2]='P';    
  GPS_GGA[3]='G';
  GPS_GGA[4]='G';
  GPS_GGA[5]='A';
  
    i = 6;
    while(byteGPS != '*'){                  
      byteGPS = Serial.read();         
      inBuffer[i]=byteGPS;
      GPS_GGA[i]=byteGPS;
      i++;                      
  }
    
  // print the GGA sentence to USB
  printf("GGA sentence: \n");
  h = 0;
  while(GPS_GGA[h] != 42){
    printf("%c",GPS_GGA[h]);
    h++;
  }
  printf("\n");
  
  // print the RMC sentence to USB
  printf("RMC sentence: \n");
  h = 0;
  while(GPS_RMC[h] != 42){
    printf("%c",GPS_RMC[h]);
    h++;
  }
  printf("\n");
}


int main (){
	setup();
	while(1){
		loop();
	}
	return (0);
}

	
