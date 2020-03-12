/*
    Enum-style class used to convert a string to a code used to categorize data and store it in arrays.
*/
public class Person {
  
  //Default values
  final static int PARENT = 0;
  final static int GRANDPARENT = 1;
  final static int FRIEND = 2;
  
  final static int UNKNOWN = -1;
  
  //Check a string against expected values and return a code if a match is found
  static int getType(String comparer) {
    String lc_comparer = comparer.toLowerCase();
    
    if(lc_comparer.equals("parents")){
      return PARENT;
    }
    if(lc_comparer.equals("grandparents")) {
      return GRANDPARENT;
    }
    if(lc_comparer.equals("friends")) {
      return FRIEND;
    }
    return UNKNOWN;
  }
}
