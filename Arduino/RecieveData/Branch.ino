/**
 * Code to initialize branch hardware.
 */
void setupBranches() {
  //TODO: Replace with hardware setup
  for(int branch = 0; branch < NUM_BRANCHES; branch++) {
    setupFakeBranch(branch);
  }
}

/**
 * TODO
 */
void grow(int branch, int amount) {
  //TODO: replace with hardware code
  fakeGrow(branch, amount);
}

/**
 * Determines how much growth a branch should have based on monthly calling amounts.
 * 
 *  branch    {int} The branch needing a growth rate
 *  talkTime  {int} How much time was spent talking to that branch's group in a month
 *  
 * Returns:
 *  1 for poor growth
 *  2 for average growth
 *  3 for great growth
 */
int calcGrowth(int branch, int talkTime) {

  // Get the threshold using the expected average talk time value for the branch
  int threshold = expectedTalkTime[branch];

  /**
   * Split categories based on proximity to threshold
   *    Bad - less than 50% expected talk time
   *    Average - between 50% and 150% expected talk time
   *    Amazing - greater than 150% expected talk time
   */
  if (talkTime < (threshold*0.5) {
    return 1; // Bad
  }
  if(talkTime < (threshold*1.5) {
    return 2; // Average
  }
  return 3; // Amazing!
}

/**
 * TO BE REMOVED
 *  - Functions and hardware details for mocking data interaction via leds -
 */

 
int ledMains[NUM_BRANCHES] = { 11, 10, 9 };

void setupFakeBranch(int branch) {
  pinMode(ledMains[branch], OUTPUT);
  analogWrite(ledMains[branch], 100);
}

void fakeGrow(int branch, int amount) {
  int growth = ((amount-1) * 100);
  analogWrite(ledMains[branch], growth);
}
