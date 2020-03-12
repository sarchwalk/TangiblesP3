/*------------------------------------------------------------
 * Sets the LED color for the arm depending on the state
 * Each arm has 8 leds
 * Arm 1 has LEDs 1-8
 * Arm 2 has LEDs 9-16
 * Arm 3 has LEDs 17-24
 */
void setLEDState(int state, int arm)
{

  int r, g, b;
  int offset = 8*(arm-1);   // Sets the arms LEDs that should be changed
  
    switch(state)
    {
      case (0):
        r = 0;
        g = 102;
        b = 0;
        break;
     case (1):
        r = 255;
        g = 255;
        b = 0;
        break;
     case (2):
        r = 255;
        g = 0;
        b = 0;
        break;
      default:
        r = 255;
        g = 255;
        b = 255;
        break;
    }
    
    leds[0 + offset].setRGB(r,g,b);
    leds[1 + offset].setRGB(r,g,b);
    leds[2 + offset].setRGB(r,g,b);
    leds[3 + offset].setRGB(r,g,b);
    leds[4 + offset].setRGB(r,g,b);
    leds[5 + offset].setRGB(r,g,b);
    leds[6 + offset].setRGB(r,g,b);
    leds[7 + offset].setRGB(r,g,b);

    FastLED.show();
    FastLED.delay(1000 / UPDATES_PER_SECOND);
}
