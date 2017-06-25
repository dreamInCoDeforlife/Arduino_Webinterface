/*
 * Recieve instructions for robot control through website. 
 * http://wossrobotics.ca/LED_data.txt
 * To make this code work internet connection is needed
 * @Author : Aman Adhav
 * June 1st 2017
 */

import processing.serial.*;
import java.net.InetAddress;
// initialize arduino ports
Serial port;
Serial port1;

void setup () { 
  //size(600, 600);  // set up the window to whatever size you want
  println(Serial.list());  // List all the available serial ports
  String portName = "COM5"; // Change these port names as need according to the port list
  String portName1 = "COM7"; // Change these port names as need according to the port list
  
  // Define baud rate for the ports and make sure in the beginning they are clear
  port = new Serial(this, portName, 9600); 
  port1 = new Serial(this, portName1, 9600);
  port.clear();
  port1.clear();
  
}
public boolean isServerAlive()
  // To check if server is reachable
{
  
  try {
    
    InetAddress.getByName("wossrobotics.ca").isReachable(3000); //this checks if the website is reachable with 3000 as maximum ping
    return true;
  } 
  catch (Exception e) {
    return false;
  }
}
void draw(){

  // If the website is active
  if (isServerAlive()) {
    String onoffdata[] = loadStrings("http://wossrobotics.ca/LED_data.txt"); //load the character (instruction from the website)
    text("WORKING",10,100); // display if the website is reachable
    String a1d5[] = new String[1];
    if (onoffdata == null){ //if there is a glitch or the website is unreachable at that instant
       a1d5[0] = "9"; //change the character in the string to "9"
    }
    else{
      if (onoffdata.length != 0){ // if it is reachable
        a1d5[0] = onoffdata[0]; // get the value from first value from onoffdata[] 
      }else{
        a1d5[0] = "9"; // else make the value "9" (this is added to further filter the results because for some odd reason the wifi used to crash immediately crashing the program)
      }
        
    }
    
     // this part of the code sends serial data to the arduino values from 1-9 are recieved in this processing sketch and sent to the arduino serial ports
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
