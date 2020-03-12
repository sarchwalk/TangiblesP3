/* TextFile Sender: Written by Scott C on 5th April 2013
 using Processing Version 2.0b8 */

import processing.serial.*;

Serial comPort;
int counter=0; // Helps to keep track of values sent.
int numItems=0; //Keep track of the number of values in text file
boolean sendData=false; //Turns sending on and off
DataLoader dLoader; //Used to send values to Arduino 

void setup(){
  printArray(Serial.list());
  
  // IMPORTANT: Verify the port connected to the arduino matches the selection!
 comPort = new Serial(this, Serial.list()[0], 9600);
 background(255,0,0); //Start with a Red background
}

void draw(){
}


void mousePressed() {
 //Toggle between sending values and not sending values
 sendData = !sendData;
 
 //If sendStrings is True - then send values to Arduino
 if(sendData){
 background(0,255,0); //Change the background to green
 
 /*When the background is green, transmit
 text file values to the Arduino */
 for(int i=0; i< 5; i++) {
   println(5-i);
 delay(1000);
 }
 dLoader=new DataLoader(comPort);
 dLoader.start();
 }else{
 background(255,0,0); //Change background to red
 //Reset the counter
 counter=0;
 }
}
