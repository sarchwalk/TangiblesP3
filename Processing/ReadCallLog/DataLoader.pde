/*
    From tutorial found at: 
    https://arduinobasics.blogspot.com/2012/05/reading-from-text-file-and-sending-to.html
    
    Loads data from a spreadsheet and sends monthly details over serial for and Arduino to handle.
*/
public class DataLoader extends Thread {
 
 // Constructor
 public DataLoader(Serial comPort){
   this.comPort = comPort;
 }
 
 // The serial port for sending data to the Arduino
 Serial comPort;
 
 // Function to read a call log file, parse data, consolidate it, and send to ardino in an expected format.
 public void run() {
   // Get table data from file
   Table table = loadTable("call_logs.csv", "header");
   
   // Track year and month of entries for grouping - initialize to -1 as unknown
   int year = -1;
   int month = -1;
   
   // Sum of talk time consolidated for a month
   int[] talkTimeForMonth = { 0,0,0 }; 
   
   for(TableRow r: table.rows()) {
     // If sendData has been turned off, stop doing things
     if(!sendData) {
       break;
     }
     
     // Parse row into call object
     CallLogItem call = new CallLogItem(r);
     
     //If no info set yet, set initial year and month for comparison
     if(year == -1 || month == -1) {
       year = call.getYear();
       month = call.getMonth();
     }
     
     // If the current entrys month or year do not match the new entries, we've hit a new month - send data and reset
     if(call.getYear() != year || call.getMonth() != month) {
       // Arduino expects strings starting with '>'
       String toSend = ">";
       // Add times for each branch to the string
       for(int b = 0; b < 3; b++) {
         toSend += (talkTimeForMonth[b] + " ");
         talkTimeForMonth[b] = 0; //Reset the month
       }
       // Arduino expects strings ending with '<'
       toSend += "<";
       comPort.write(toSend);
       println("Sent: " + toSend);
       delay(5000); // Only send data every 5s to allow hardware to adjust
     }
     
     // Update year and month to match the new entry
     year = call.getYear();
     month = call.getMonth();
     
     // Update the call time for the current entry's month
     talkTimeForMonth[call.getCode()] += call.getDuration();
   }
 }
}
