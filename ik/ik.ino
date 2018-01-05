#include <Servo.h>

// Servo's definition
Servo servoGuide;
Servo servoBase;
Servo servoArm;

// Auxiliar variables
int receivedData = 0;
char incomingByte;
bool newData = false;
bool receivedX = false;
bool receivedY = false;
bool receivedZ = false;
bool receivedCoordinates = false;

// x,y,z coordinates of the desired position
float x, y, z;
// alpha, beta and gamm joint angles
float guideAngle, baseAngle, armAngle;
// robot parameters
float z_1 = 7.6;
// Length of the bar that connects the servo and the clip in cm
float l_1 = 4.5;
// Lenght of the clip in cm
float l_2 = 7.5;
// Length of the arm  in cm
float l_3 = 7.5;


void setup() 
{
   Serial.begin(9600);
   servoGuide.attach(9);
   servoBase.attach(10);
   servoArm.attach(11);

   servoGuide.write(0);
   servoBase.write(0);
   servoArm.write(0);
}

void loop() 
{
    recvWithEndMarker();
    // Check if there is new data and process it accordingly
    if (newData)
    {
      processData();
    }
    if (receivedCoordinates)
    {
      computeJointAngles();
      moveJoints();
      delay(2000);
      servoGuide.write(30);
      delay(90);
      servoBase.write(0);
      servoArm.write(0);
      delay(2000);
      
    }
}

// Helper functions
void recvWithEndMarker() 
{
   if (Serial.available() > 0)      // something came across serial 
   {    
    receivedData = 0;              // throw away previous receivedData
    while(1)                        // force into a loop until 'n' is received
    {                      
      incomingByte = Serial.read();
      if (incomingByte == '\n') 
        break;                      // exit the while(1), we're done receiving
      if (incomingByte == -1) 
        continue;                   // if no characters are in the buffer read() returns -1
      receivedData *= 10;           // shift left 1 decimal place
      // convert ASCII to integer, add, and shift left 1 decimal place
      receivedData = ((incomingByte - 48) + receivedData);
    }
    newData = true;
    Serial.println(receivedData);
  }
}

void processData()
{
      // if number ends with 2 it is x coordinate, if it ends with
      // 5 it is y coordinate and else it is z coordinate
      // We divide by 10 to wipeout the marker number that indicates
      // the coordinate and store only the coordinate value.
      if (receivedData % 2 == 0)
      {
        x = receivedData/10;
        receivedX = true;
        Serial.println('X');
      }
      else if (receivedData % 5 == 0)
      {
        y = receivedData/10;
        receivedY = true;
        Serial.println('Y');
      }
      else
      {
        z = receivedData/10;
        receivedZ = true;
        Serial.println('Z');
      }
      
      if (receivedX && receivedY && receivedZ)
      {
        receivedCoordinates = true;
        receivedX = false;
        receivedY = false;
        receivedZ = false;
      }
      newData = false;
}

void computeJointAngles()
{
  armAngle = asin((z-z_1)/l_3)*180.0/PI;
  baseAngle = asin(x/(l_3*cos(armAngle*PI/180.0)))*180.0/(PI+0.0);
  guideAngle = acos((y-l_2-sqrt(pow(l_3, 2)-pow(z-z_1, 2)-pow(x, 2)))/l_1)*180/PI;
  receivedCoordinates = false;
  Serial.print("Arm: ");
  Serial.println(armAngle);
  Serial.print("Base: ");
  Serial.println(baseAngle);
  Serial.print("Guide: ");
  Serial.println(guideAngle);
  
}

void moveJoints()
{
  // Taking into account our 0 is when the servo 0 is at 120 degrees
  //servoGuide.write(120-guideAngle);
  servoGuide.write(int(guideAngle));
  servoBase.write(int(baseAngle));
  servoArm.write(int(-1*(armAngle+16)));
}

