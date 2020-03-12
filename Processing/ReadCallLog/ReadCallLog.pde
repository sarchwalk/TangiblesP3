/*
    From tutorial found at: 
    https://arduinobasics.blogspot.com/2012/05/reading-from-text-file-and-sending-to.html
*/
import processing.serial.*;

//Turn sending on/off
boolean sendData=false;

// Port for sending data to Arduino
Serial comPort; 
//Object to send values to Arduino
DataLoader dLoader;  

void setup(){
  printArray(Serial.list());
  // IMPORTANT: 
  // Verify that the port connected to the arduino matches the selection below!
 
  comPort = new Serial(this, Serial.list()[1], 9600);
  
  //Red background when not sending data
  background(255,0,0);
}

void draw(){
}

void mousePressed() {
  //Toggle between sending values and not sending values
  sendData = !sendData;
  
  //If sendStrings is True - then send values to Arduino
  if(sendData) {
    background(0,255,0); //Change the background to green
    
    // When the background is green, transmit file values to the Arduino
    dLoader=new DataLoader(comPort);
    dLoader.start();
  }
  else {
    background(255,0,0); //Change background to red
  }
}
