

#include <Servo.h>
#include <FastLED.h>


//----------------------- Reuired for communication with processing-------------------------
#define PARENTS 0
#define GRANDPARENTS 1
#define FRIENDS 2

#define NUM_BRANCHES 3

// Threshold values used to caluclate whether certain callees have been contacted enough
// In Minutes per Month
int expectedTalkTime[] = { 300, 50, 60 };

// Call data recieved for each callee type
// In Minutes per Month
int dataIn[NUM_BRANCHES];

// Serial Buffer data
const byte numChars = 32;
char receivedChars[numChars];
char tempChars[numChars]; 

boolean newData = false;
//------------------------------------------------------------------------------------------



//---------------------------------- LED Setup ---------------------------------------------
#define LED_PIN  2
#define NUM_LEDS    24
#define BRIGHTNESS  64
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define UPDATES_PER_SECOND 100

CRGB leds[NUM_LEDS];
//------------------------------------------------------------------------------------------

Servo armOneServoOne;  
Servo armOneServoTwo;
Servo armTwoServoOne;
Servo armTwoServoTwo;
Servo armThreeServoOne;
Servo armThreeServoTwo;

// Current state at each arm
int armState[] = {2,2,2};     // The state of each arm - 0 is excellent, 1 is good, 2 is bad

// The angle each servo should be at for a given state
// Arm positions: [arms 1-3][states 1-3][servos 1-0] 
int armPositions[][3][2] = {
                          {{60,90},{90,50},{145,15}},
                          {{60,70},{90,100},{130,140}},
                          {{90,90},{60,100},{30,120}}};
                          
void setup() {

  Serial.begin(9600);
  
  // Servo Setup
  armOneServoOne.attach(3); 
  armOneServoTwo.attach(5);
  armTwoServoOne.attach(6);
  armTwoServoTwo.attach(9);
  armThreeServoOne.attach(10);
  armThreeServoTwo.attach(11);

  // LED setup
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.clear();

  // Setup initial tree state
  armOneServoOne.write(armPositions[0][2][0]);
  armOneServoTwo.write(armPositions[0][2][1]);
  armTwoServoOne.write(armPositions[1][2][0]);
  armTwoServoTwo.write(armPositions[1][2][1]);
  armThreeServoOne.write(armPositions[2][2][0]);
  armThreeServoTwo.write(armPositions[2][2][1]);
  
  //Sets each branch led to white
  setLEDState(2,1);
  setLEDState(2,2);
  setLEDState(2,3);
}



void loop() {
  
  // Look for data sent from Processing
  recvWithStartEndMarkers('>', '<');

  //Once all of a line from from Processing has been read in, deal with it
  if(newData) {
    // Split data into ints stored in dataIn
    parseReadData();
    
    //Update each branch based on data received 
    for(int branch = 0; branch < NUM_BRANCHES; branch++) {
        int newState = calcGrowth(branch, dataIn[branch]);
        handleStateChange(branch+1, newState);
    }
    newData = false; // Start looking for more data
  }
  
}

/*
 * Handles growing or wilting of specific branches
 */
void handleStateChange(int branch, int newState)
{
  int oldState = armState[branch-1];
  
  while(oldState != newState)
  {    
    // Arm should grow
    if(newState > oldState)
    {
      growArm(branch);
    }

    // Arm should wilt
    else if(newState < oldState)
    {
      wiltArm(branch);
    }
    oldState = armState[branch-1];
  }
}
