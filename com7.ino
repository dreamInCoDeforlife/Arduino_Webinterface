/*
 * Communicate CLAW OPEN, CLAW CLOSE motion for the Robot Arm. Processing IDE sends commands to the arduinos using serial port. 
 * Make sure the processing code is installed before using this arduino program
 * @Author : Aman Adhav
 * June 1st 2017
 */

//define clock wise and counter clock wise motion
#define CW  0
#define CCW 1

// Motor definitions to make life easier:
#define MOTOR_A 1
#define MOTOR_B 1
int incomingByte; //value that is incoming through the serial port
const byte PWMA = 3;  // PWM control (speed) for motor A
const byte PWMB = 11; // PWM control (speed) for motor B
const byte DIRA = 12; // Direction control for motor A
const byte DIRB = 13; // Direction control for motor B


void setup()
{
  Serial.begin(9600);
  
  setupArdumoto(); // Set all pins as outputs
  
}


void loop()
{
   //check if there are any value in serial port(serial port is how you communicate with the arduino)  
  if (Serial.available()){
    incomingByte = Serial.read(); // read the incoming byte from the serial port
    if (incomingByte == 'B'){ // if incoming byte from the serial port is 'B' (CLAW OPEN) then drive motor clock wise 125 (analog write value) for 10ms
      driveArdumoto(MOTOR_B, CW, 125);
      delay(100);
      stopArdumoto(MOTOR_B);
    }else if (incomingByte == 'C'){ // if incoming byte from the serial port is 'C' (CLAW CLOSE) then drive motor counter clock wise 125 (analog write value) for 10ms
      
      driveArdumoto(MOTOR_B, CCW, 125);
      delay(100);
      stopArdumoto(MOTOR_B);
    }else{
      //stopArdumoto(MOTOR_A);
      stopArdumoto(MOTOR_B);
    }
  }
  
}

// driveArdumoto drives 'motor' in 'dir' direction at 'spd' speed
void driveArdumoto(byte motor, byte dir, byte spd)
{
  if (motor == MOTOR_A)
  {
    digitalWrite(DIRA, dir);
    analogWrite(PWMA, spd);
  }
  else if (motor == MOTOR_B)
  {
    digitalWrite(DIRB, dir);
    analogWrite(PWMB, spd);
  }  
}

// stopArdumoto makes a motor stop
void stopArdumoto(byte motor)
{
  driveArdumoto(motor, 0, 0);
}

// setupArdumoto initialize all pins
void setupArdumoto()
{
  
  // All pins should be setup as outputs:
  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(DIRA, OUTPUT);
  pinMode(DIRB, OUTPUT);

  // Initialize all pins as low:
  digitalWrite(PWMA, LOW);
  digitalWrite(PWMB, LOW);
  digitalWrite(DIRA, LOW);
  digitalWrite(DIRB, LOW);
}
