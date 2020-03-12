/*============================================================*/
/* The StringLoader class imports data from a text file
 on a new Thread and sends each value once every half second */
public class DataLoader extends Thread {
 
 public DataLoader(Serial comPort){
   //default constructor
   this.comPort = comPort;
 }
 
 final static int minutesInDay = 1440;
 
 Serial comPort;
 
 public void run() {
   Table table = loadTable("call_logs.csv", "header");
   
   int year = -1;
   int month = -1;
   
   int[] talkTimeForMonth = { 0,0,0 }; 
     
   for(TableRow r: table.rows()) {
     if(!sendData) {
       break;
     }
     CallLogItem call = new CallLogItem(r);
     
     if(year == -1 || month == -1) {
       year = call.getYear();
       month = call.getMonth();
     }
     
     if(call.getYear() != year || call.getMonth() != month) {
       String toSend = ">";
       for(int b = 0; b < 3; b++) {
         toSend += (talkTimeForMonth[b] + " ");
         talkTimeForMonth[b] = 0;
       }
       toSend += "<";
       comPort.write(toSend);
       println("Sent: " + toSend);
       delay(5000);
     }
     
     year = call.getYear();
     month = call.getMonth();
     
     talkTimeForMonth[call.getCode()] += call.getDuration();
     
     //int outVal = call.getCode();
     //if(call.isMissedCall()) {
     //  println("Missed " + outVal);
     //  outVal *= -1;
     //  println("Missed " + outVal);
     //}
     //comPort.write(outVal);
     
   
     //println(name + " (" + personType + ") at " + callTime + " + " + dur);
   }
 }
}
