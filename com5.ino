/*
 * Communicate Up, Down, Left, Right motion for the Robot Arm. Processing IDE sends commands to the arduinos using serial port. 
 * Make sure the processing code is installed before using this arduino program
 * @Author : Aman Adhav
 * June 1st 2017
 */

//Define Clock wise and counter clock wise motion
#define CW  0
#define CCW 1

// Motor definitions to make life easier:
#define MOTOR_A 0
#define MOTOR_B 1
int incomingByte; //value that is incoming through the serial port
const byte PWMA = 3;  // PWM control (speed) for motor A
const byte PWMB = 11; // PWM control (speed) for motor B
const byte DIRA = 12; // Direction control for motor A
const byte DIRB = 13; // Direction control for motor B

void setup()
{
  Serial.begin(9600);
  setupArdumoto();
  
}

void loop()
{
  //check if there are any value in serial port(serial port is how you communicate with the arduino)
  if (Serial.available()){
    incomingByte = Serial.read(); // read the incoming byte from the serial port
    
    if (incomingByte == 'L'){
      driveArdumoto(MOTOR_B, CW, 100); // if incoming byte from the serial port is 'L' (LEFT) then drive motor clock wise 100 (analog write value) for 10ms
      delay(10);
    }else if (incomingByte == 'R'){   // if incoming byte from the serial port is 'R' (RIGHT) then drive motor counter clock wise speed 100 (analog write value) for 10ms
      driveArdumoto(MOTOR_B, CCW, 100);
      delay(10);
    }else if (incomingByte == 'U'){ // if incoming byte from the serial port is 'U' (UP) then drive motor clock wise speed 100 (analog write value) for 10ms
      driveArdumoto(MOTOR_A, CW, 100);
      delay(10);
    }else if (incomingByte == 'D'){// if incoming byte from the serial port is 'D' (DOWN) then drive motor counter clock wise speed 100 (analog write value) for 10ms
      driveArdumoto(MOTOR_A, CCW, 100);
      delay(10);
    }else{
      stopArdumoto(MOTOR_A); // else stop the motor (Commands are being given to control the claw motor) 
      stopArdumoto(MOTOR_B); // else stop the motor (Commands are being given to control the claw motor) 
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
