/**
 * Determines how much growth a branch should have based on monthly calling amounts.
 * 
 *  branch    {int} The branch needing a growth rate
 *  talkTime  {int} How much time was spent talking to that branch's group in a month
 *  
 * Returns:
 *  3 for poor growth
 *  1 for average growth
 *  0 for great growth
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
  if (talkTime < (threshold*0.5)) {
    return 2; // Bad
  }
  if(talkTime <= (threshold*1.5)) {
    return 1; // Average
  }
  return 0; // Amazing!
}
