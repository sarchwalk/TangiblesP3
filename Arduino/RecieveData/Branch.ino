int growthLevels[] = { 100, 100, 100 };

int expectedTalkTime[] = { 300, 50, 60 };

int growthMin = 0;
int growthMax = 255;

//
void setupBranches() {
  for(int b = 0; b < NUM_BRANCHES; b++) {
    pinMode(ledMains[b], OUTPUT);
    analogWrite(ledMains[b], growthLevels[b]);
  }
}

int calcGrowth(int branch, int talkTime) {
  int threshold = expectedTalkTime[branch];
  
  if (talkTime < (threshold - (threshold/2))) {
    return 1; // Bad
  }
  if(talkTime < (threshold + (threshold/2))) {
    return 2; // Average
  }
  return 3; // Amazing!
}

void grow(int branch, int amount) {
  growthLevels[branch] = (amount * 100);
  
  if(growthLevels[branch] < growthMin) { growthLevels[branch] = growthMin; }
  else if(growthLevels[branch] > growthMax) { growthLevels[branch] = growthMax; }
  
  analogWrite(ledMains[branch], growthLevels[branch]);
}
