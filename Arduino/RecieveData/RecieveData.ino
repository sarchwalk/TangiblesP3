#define PARENTS 0
#define GRANDPARENTS 1
#define FRIENDS 2

#define NUM_BRANCHES 3

int ledMains[NUM_BRANCHES] = { 11, 10, 9 };

void setup() {
  Serial.begin(9600);
  setupBranches();
    Serial.println("<Arduino is ready>");
  
}

int dataIn[NUM_BRANCHES];

const byte numChars = 32;
char receivedChars[numChars];
char tempChars[numChars]; 

boolean newData = false;

void loop() {
  /* check if data has been sent from the computer: */
  recvWithStartEndMarkers();
   
  if(newData) {
    parseReadData();
    for(int branch = 0; branch < NUM_BRANCHES; branch++) {
        int growthAmount = calcGrowth(branch, dataIn[branch]);
        grow(branch, growthAmount);
    }
    newData = false;
  }
}

void recvWithStartEndMarkers() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '>';
    char endMarker = '<';
    char rc;
 
    while (Serial.available() > 0 && newData == false) {
        rc = Serial.read();

        if (recvInProgress == true) {
            if (rc != endMarker) {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
            else {
                receivedChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }
        }

        else if (rc == startMarker) {
            recvInProgress = true;
        }
    }
}

void parseReadData() {
  strcpy(tempChars, receivedChars);
  
  char * strtokIndx; // this is used by strtok() as an index
  strtokIndx = strtok(tempChars," ");
  dataIn[PARENTS] = atoi(strtokIndx);

  strtokIndx = strtok(NULL," ");
  dataIn[GRANDPARENTS] = atoi(strtokIndx);

  strtokIndx = strtok(NULL," ");
  dataIn[FRIENDS] = atoi(strtokIndx);
}
