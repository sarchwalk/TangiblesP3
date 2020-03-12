public class CallLogItem {
  
  //Atributes from spreadsheet
  //--------------------------
  //Who called / recieved a call,
  private String name;  
  
  //When the call occurred
  private int callYear; 
  private int callMonth; 
  private int callDay; 
  private int callTimeMinute; 
  
  // What kind of call was it [Dialed/Recieved/Missed]
  private String callType; 
  
  // How long the call ran, rounded to the nearest minute
  private int duration; 
  
  //Constructor 
  //  Built using row of spreadsheet
  public CallLogItem(TableRow row) {
    name = row.getString("name");
    
    callYear = row.getInt("callYear"); 
    callMonth = row.getInt("callMonth");
    callDay = row.getInt("callDay");
    //callTimeMinute = row.getInt("callTimeMinute");
    
    callType = row.getString("callLog");
    duration = row.getInt("durationMinutes");
    
    //println(callType + " - " + name + " " + callYear+"-"+callMonth+"-"+callDay+ " + " + callTimeMinute + " (" + duration + ")");
  }
  
  //Getters (Note: row data should be readonly)
  public int getYear() { return callYear; }
  public int getMonth() { return callMonth; }
  public int getDay() { return callDay; }
  //public int getCallTime() { return callTimeMinute; }
  public int getDuration() { return duration; }
  
  // Convert contact 'name' to code expected by Arduino
  public int getCode() {
    return Person.getType(name);
  }
  
  // Check if the call was missed by the user or unanswered by the callee
  public boolean isMissedCall() {
    boolean missed = callType.toLowerCase().equals("missed");
    boolean unanswered = (callType.toLowerCase().equals("dialed") && duration < 1);
    return (missed || unanswered);
  }
  
}
