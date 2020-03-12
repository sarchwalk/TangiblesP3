/*-----------------------------------------------------------------------------------
 * Shifts identified arm down one state
 * Adjusts arm angle according to state
 */
void wiltArm(int arm)
{
  if (armState[arm-1] < 2)
  {
    bool continueMoving = true;
    int previousState = armState[arm-1];

    // updates arm state to new state
    armState[arm-1]++;

    int servoOnePosition = armPositions[arm-1][previousState][0];// Initial servo one position
    int servoTwoPosition = armPositions[arm-1][previousState][1]; // Initial servo two position
  
    int servoOneEndPosition = armPositions[arm-1][armState[arm-1]][0]; // End position for servo one
    int servoTwoEndPosition = armPositions[arm-1][armState[arm-1]][1]; // End position for servo two  
    
    // Change the angle of the branches
    // Note: loop controls are within the block
    for(;continueMoving;)
    {
      switch(arm)
      {
        case(1):
          armOneServoOne.write(servoOnePosition);
          armOneServoTwo.write(servoTwoPosition);
          break;
        case(2):
          armTwoServoOne.write(servoOnePosition);
          armTwoServoTwo.write(servoTwoPosition);
          break;
        case(3):
          armThreeServoOne.write(servoOnePosition);
          armThreeServoTwo.write(servoTwoPosition);
          break;
        default:
          break;
      }
      delay(70);

      // Loop control handling - ensures that one servo does not force the other to continue past its bounds
      // Because each servo was hooked up differently its bounds must be handled differently
      if (arm == 1)
      {
          
        // Loop Control: Ensures that one servo does not force other to continue past its bounds
         if(servoOnePosition <= servoOneEndPosition)
          {
            servoOnePosition++;
          }
          if(servoTwoPosition >= servoTwoEndPosition)
          {
            servoTwoPosition--;
          }

        if(!(servoOnePosition <= servoOneEndPosition) && !(servoTwoPosition >= servoTwoEndPosition))
        {
          continueMoving = false;
        }
          
      }

      if(arm ==2)
      {
        // Loop Control: Ensures that one servo does not force other to continue past its bounds
         if(servoOnePosition <= servoOneEndPosition)
          {
            servoOnePosition++;
          }
          if(servoTwoPosition <= servoTwoEndPosition)
          {
            servoTwoPosition++;
          }

        if(!(servoOnePosition <= servoOneEndPosition) && !(servoTwoPosition <= servoTwoEndPosition))
        {
          
          continueMoving = false;
        }
      }


      
      if(arm ==3)
      {          
          // Loop Control: Ensures that one servo does not force other to continue past its bounds
           if(servoOnePosition >= servoOneEndPosition)
            {
              servoOnePosition--;
            }
            if(servoTwoPosition <= servoTwoEndPosition)
            {
              servoTwoPosition++;
            }
          
          if(!(servoOnePosition >= servoOneEndPosition) && !(servoTwoPosition <= servoTwoEndPosition))
          {
            
            continueMoving = false;
          }
        }
    }  

    setLEDState(armState[arm-1],arm);
     
  }
}






/*-----------------------------------------------------------------------------------
 * Grow arm accepts an arm number and shifts it up one state
 * Adjusts arm angle according to state
 */
void growArm(int arm) {
  if (armState[arm-1] > 0)
  {
    bool continueMoving = true;
    int previousState = armState[arm-1];

    // updates arm state to new state
    armState[arm-1]--;

    int servoOnePosition = armPositions[arm-1][previousState][0]; // Initial servo one position
    int servoTwoPosition = armPositions[arm-1][previousState][1]; // Initial servo two position
  
    int servoOneEndPosition = armPositions[arm-1][armState[arm-1]][0]; // End position for servo one
    int servoTwoEndPosition = armPositions[arm-1][armState[arm-1]][1]; // End position for servo two  
    
    // Change the angle of the branches
    for(;continueMoving;)
    {
      switch(arm)
      {
        case(1):
          armOneServoOne.write(servoOnePosition);
          armOneServoTwo.write(servoTwoPosition);
          break;
        case(2):
          armTwoServoOne.write(servoOnePosition);
          armTwoServoTwo.write(servoTwoPosition);
          break;
        case(3):
          armThreeServoOne.write(servoOnePosition);
          armThreeServoTwo.write(servoTwoPosition);
          break;
        default:
          break;
      }
      delay(70);

      // Loop control handling - ensures that one servo does not force the other to continue past its bounds
      // Because each servo was hooked up differently its bound must be handled differently
      if (arm == 1)
      {
          
        // Loop Control: Ensures that one servo does not force other to continue past its bounds
         if(servoOnePosition >= servoOneEndPosition)
          {
            servoOnePosition--;
          }
          if(servoTwoPosition <= servoTwoEndPosition)
          {
            servoTwoPosition++;
          }

        if(!(servoOnePosition >= servoOneEndPosition) && !(servoTwoPosition <= servoTwoEndPosition))
        {
          continueMoving = false;
        }
          
      }

      if(arm ==2)
      {
        // Loop Control: Ensures that one servo does not force other to continue past its bounds
         if(servoOnePosition >= servoOneEndPosition)
          {
            servoOnePosition--;
          }
          if(servoTwoPosition >= servoTwoEndPosition)
          {
            servoTwoPosition--;
          }

        if(!(servoOnePosition >= servoOneEndPosition) && !(servoTwoPosition >= servoTwoEndPosition))
        {
          
          continueMoving = false;
        }
      }
      
      if(arm ==3)
      {          
          // Loop Control: Ensures that one servo does not force other to continue past its bounds
           if(servoOnePosition <= servoOneEndPosition)
            {
              servoOnePosition++;
            }
            if(servoTwoPosition >= servoTwoEndPosition)
            {
              servoTwoPosition--;
            }
          
          if(!(servoOnePosition <= servoOneEndPosition) && !(servoTwoPosition >= servoTwoEndPosition))
          {
            
            continueMoving = false;
          }
        }
    }  

    setLEDState(armState[arm-1],arm);
  }
}
