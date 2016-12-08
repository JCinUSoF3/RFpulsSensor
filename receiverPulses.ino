// receiver.pde
//
// Simple example of how to use VirtualWire to receive messages
// Implements a simplex (one-way) receiver with an Rx-B1 module
//
// See VirtualWire.h for detailed API docs
// Author: Mike McCauley (mikem@airspayce.com)
// Copyright (C) 2008 Mike McCauley
// $Id: receiver.pde,v 1.3 2009/03/30 00:07:24 mikem Exp $
#include <Wire.h>                 //Imports lcd libraries
#include <LiquidCrystal_I2C.h>    //Imports lcd libraries
#include <VirtualWire.h>          ////Imports receiver libraries
LiquidCrystal_I2C myDisplay(0x27,16,2); //sets lcd display
int count; //creates integer variable count
void setup()
{
    myDisplay.init();
    Serial.begin(9600);	// Debugging only
    Serial.println("setup"); // prints the string setup in serial
    vw_set_rx_pin(7); //sets D12 (formerly D7) as receive pin Try A0 or D7 also
    vw_set_ptt_inverted(true); // Required for DR3100
    vw_setup(1000);	 // Bits per sec
    vw_rx_start();       // Start the receiver PLL running
    myDisplay.backlight();//Turns lcd back light on
    myDisplay.print("makecourse-art"); //prints the string phreak on the lcd as in the phantom preak the king of nynex
    delay(2000); //sets a 2 second delay
}

void loop()
{
    uint8_t buf[VW_MAX_MESSAGE_LEN]; //parrameter buffer message being received
    uint8_t buflen = VW_MAX_MESSAGE_LEN; // the length of the buffer received
    if (vw_get_message(buf, &buflen)) // Non-blocking
    {
	      int i;                  // creates an integer variable i
        digitalWrite(13, true); // Flash a light to show received good message
	      // Message with a good checksum received, dump it.
	      Serial.print("Got: ");  // prints string Got: on serial before received data
        
	      
	      for (i = 0; i < buflen; i++) //for loop with int i set as zero and the buflen, to assure data stream
	      {
          char c = (buf[i]);          //character array varaible of received data
	        Serial.print(c);//prints buffer character by character
	        Serial.print("0's"); //keeps the received within a certain amount instead of constant fluctuating exact pulses
          delay(2000);         // sets a 2 second delay once data is received
          myDisplay.setCursor(1,8); //sets the lcd cursor
          myDisplay.clear();        // clears the lcd screen
          //myDisplay.print("CallSign:  ");
          myDisplay.print("pulse =");  //prints the string pulse = onto the lcd
          myDisplay.print(" "); // leaves a space aftet the = sign on the lcd
          myDisplay.print(c);   // prints the received data onto the lcd
          if (c == '1' ){
          myDisplay.print("00's");   
          }
          if (c == '6' ){
          digitalWrite(0,true);
          digitalWrite(1,false);   
          }//HAPPY FACE
          if (c == '7' ){
          digitalWrite(0,true);
          digitalWrite(1,false);   
          }//HAPPY FACE
          if (c == '8' ){
          digitalWrite(0,true);
          digitalWrite(1,false);   
          }//HAPPY FACE
          if (c == '9' ){
          digitalWrite(0,true); 
          digitalWrite(1,false);  
          }//HAPPY FACE
          if (c == '2' ){
          digitalWrite(1,true);
          digitalWrite(0,false);   
          }//ANGRY FACE
          if (c == '3' ){
          digitalWrite(1,true);
          digitalWrite(0,false);   
          }//ANGRY FACE
          if (c == '4' ){
          digitalWrite(1,true);
          digitalWrite(0,false);   
          }//ANGRY FACE
          if (c == '5' ){
          digitalWrite(1,true);
          digitalWrite(0,false);   
          }//ANGRY FACE
          myDisplay.print("0's"); // //keeps the received within a certain amount instead of constant fluctuating exact pulses
         //the following are used for testing purposes
          //volatile char r =Serial.read();
          //myDisplay.print(r);
          //myDisplay.print("0's");
          //myDisplay.print(count);
	      }
	      count++; //increases the count variable by one
        Serial.print(count); // prints the amount of times data is received to serial
	      Serial.println("");  // leaves a space between serial line prints
        digitalWrite(13, false); //flashes the light off at end of the loop
    }
    
}
