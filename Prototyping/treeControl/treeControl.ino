

#include <Servo.h>
#include <FastLED.h>

#define LED_PIN  2
#define NUM_LEDS    24
#define BRIGHTNESS  64
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define UPDATES_PER_SECOND 100

CRGB leds[NUM_LEDS];

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

  // Setup initial tree state
  armOneServoOne.write(armPositions[0][2][0]);
  armOneServoTwo.write(armPositions[0][2][1]);
  armTwoServoOne.write(armPositions[1][2][0]);
  armTwoServoTwo.write(armPositions[1][2][1]);
  armThreeServoOne.write(armPositions[2][2][0]);
  armThreeServoTwo.write(armPositions[2][2][1]);
  

  // LED setup
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.clear();
  //Sets each led to white
  setLEDState(2,1);
  setLEDState(2,2);
  setLEDState(2,3);
}



void loop() {
  delay(1000);
  growArm(3);
}
