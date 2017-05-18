#define CW  0
#define CCW 1

// Motor definitions to make life easier:
#define MOTOR_A 1
#define MOTOR_B 1
int incomingByte;
const byte PWMA = 3;  // PWM control (speed) for motor A
const byte PWMB = 11; // PWM control (speed) for motor B
const byte DIRA = 12; // Direction control for motor A
const byte DIRB = 13; // Direction control for motor B
//#include <Wire.h>

void setup()
{
  Serial.begin(9600);
  //Wire.begin(8);                // join i2c bus with address #8
  setupArdumoto(); // Set all pins as outputs
  
}

void loop()
{
    
  if (Serial.available()){
    incomingByte = Serial.read();
    if (incomingByte == 'B'){
      driveArdumoto(MOTOR_B, CW, 125);
      delay(100);
      stopArdumoto(MOTOR_B);
    }else if (incomingByte == 'C'){
      
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
