import processing.serial.*;
import java.net.InetAddress;
Serial port;  // The serial port
Serial port1;

void setup () { 
  //size(600, 600);  // set up the window to whatever size you want
  println(Serial.list());  // List all the available serial ports
  String portName = "COM3";
  String portName1 = "COM4";
  port = new Serial(this, portName, 9600);
  port1 = new Serial(this, portName1, 9600);
  port.clear();
  port1.clear();
  
  //background(255);    // set inital background
  //smooth();  // turn on antialiasing
}
public boolean isServerAlive()
  // To check if server is reachable
{
  
  try {
    
    InetAddress.getByName("wossrobotics.ca").isReachable(3000); //Replace with your name
    return true;
  } 
  catch (Exception e) {
    return false;
  }
}
void draw(){
  if (isServerAlive()) {
    String onoffdata[] = loadStrings("http://wossrobotics.ca/LED_data.txt");
    text("WORKING",10,100);
    String a1d5[] = new String[1];
    if (onoffdata == null){
       a1d5[0] = "9";
    }
    else{
      if (onoffdata.length != 0){
        a1d5[0] = onoffdata[0];
      }else{
        a1d5[0] = "9";
      }
        
    }
    
     //print("\n\n\n\n\n\n\n\n\n\n" + onoffdata.length + "\n\n\n\n\n\n\n\n\n\n");
     if (a1d5[0].equals("1")==true){
        println(" - UP");
        port.write('U');
      }
      else if(a1d5[0].equals("2")==true){
        println(" - DOWN");
        port.write('D');
      }
      else if (a1d5[0].equals("3")==true){
        println(" - LEFT");
        port.write('L');
      }else if (a1d5[0].equals("4")==true){
        println(" - RIGHT");
        port.write('R');
      
      }else if (a1d5[0].equals("5")==true){
        println(" - RIGHT");
        port1.write('B');
      }else if (a1d5[0].equals("6")==true){
        println(" - RIGHT");
        port1.write('C');
      }
      else{
        println(" - Turn Motor OFF");
        port.write('9');
        port1.write('9');
      }
  }else{
    text("POP A HOYA",10,100);
  }
  
}
