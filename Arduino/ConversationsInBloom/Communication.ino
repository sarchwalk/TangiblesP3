


/**
 * Source: https://forum.arduino.cc/index.php?topic=396450
 * Read a line of data in from the serial port, one character at a time. 
 * Only read data between start and end markers to avoid unwanted behaviour.
 * 
 *  startMarker {char}  Character denoting the start of expected data
 *  endMarker   {char}  Character denoting the end of expected data
 *  
 * Results are stored in 'receivedChars'.
 */
void recvWithStartEndMarkers(char startMarker, char endMarker) {
    static boolean recvInProgress = false;
    static byte ndx = 0; //Index of the next char in the buffer string
    char rc; //Char read in
 
    while (Serial.available() > 0 && newData == false) {
        rc = Serial.read();

        // When recieving, accept any characters until the end marker
        if (recvInProgress == true) {
            if (rc != endMarker) { //Reading the string
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
            else { //Done receiving the string
                receivedChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }
        }

        else if (rc == startMarker) { //Start reading chars once the start char appears
            recvInProgress = true;
        }
    }
}

/**
 * Parse data received over serial into something the program can use.
 * 
 * Expected String format: 3 numbers (a, b, c) separated by spaces where
 *    a = Calls to/from Parents in Minutes per Month 
 *    b = Calls to/from Grandparents in Minutes per Month 
 *    c = Calls to/from Friends in Minutes per Month 
 *    
 * Results are stored in 'dataIn'.
 */
void parseReadData() {
  // Copy receipt buffer into temp buffer to be safe
  strcpy(tempChars, receivedChars);

  // c-string pointer used by strtok to hold results
  char * strtokIndx;
  
  strtokIndx = strtok(tempChars," ");
  dataIn[PARENTS] = atoi(strtokIndx);

  strtokIndx = strtok(NULL," ");
  dataIn[GRANDPARENTS] = atoi(strtokIndx);

  strtokIndx = strtok(NULL," ");
  dataIn[FRIENDS] = atoi(strtokIndx);
}
