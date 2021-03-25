#include "vex.h"
#include "movement.h"
#include <stdint.h>

using namespace vex;

Mode currentMode = DRIVE;
double speed = 1.0;


bool autoSpin = false;

void elevatorReject(){
  BElevator.setVelocity(40 * speed, pct);
  BElevator.spin(reverse);
  TElevator.setVelocity(40 * speed, pct);
  TElevator.spin(forward);
}

void elevatorUp(){
  BElevator.setVelocity(40 * speed, pct);
  BElevator.spin(reverse);
TElevator.setVelocity(40 * speed, pct);
  TElevator.spin(reverse);
}

void elevatorPush(){
  BElevator.setVelocity(40 * speed, pct);
  BElevator.spin(forward);
  TElevator.setVelocity(40 * speed, pct);
  TElevator.spin(forward);
}
uint32_t blueNum;
uint32_t redNum;
uint32_t rednblueNum;
uint32_t cycles;


void cameraAutoSpin(){
   blueNum = Color_Detection.takeSnapshot(Color_Detection__BLUEBALL);
   redNum = Color_Detection.takeSnapshot(Color_Detection__REDBALL);
   rednblueNum = Color_Detection.takeSnapshot(Color_Detection__BLUEBALL)+Color_Detection.takeSnapshot(Color_Detection__REDBALL);
   //cycles = 2;
  
  //if(blueNum > 0 || redNum > 0){
  //  autoSpin = true;
  //  elevatorUp();
  //  wait(2, sec);
  //}else{
  //  autoSpin = false;
  //}
}

void moveRobot(){
    int leftvelocity = Controller1.Axis2.position(percentUnits::pct)/5 + Controller1.Axis4.position(percentUnits::pct)/5;
    int rightvelocity = Controller1.Axis2.position(percentUnits::pct)/5 - Controller1.Axis4.position(percentUnits::pct)/5;
    int horizon = (Controller1.Axis1.position(percentUnits::pct)/5 * speed);
    TLMotor.setVelocity(leftvelocity * speed + horizon, percent);
    TRMotor.setVelocity(rightvelocity * speed - horizon, percent);
    BLMotor.setVelocity(leftvelocity * speed - horizon, percent);
    BRMotor.setVelocity(rightvelocity * speed + horizon, percent);
    TLMotor.spin(forward);
    TRMotor.spin(reverse);
    BLMotor.spin(forward);
    BRMotor.spin(reverse);
}

void stopMotors(){
  if(!Controller1.ButtonA.pressing() && !Controller1.ButtonB.pressing()){
    LArm.stop();
    RArm.stop();
  }  
  if(!Controller1.ButtonUp.pressing() && !Controller1.ButtonDown.pressing() && !Controller1.ButtonLeft.pressing() && !autoSpin){
    BElevator.stop();
    TElevator.stop();
  }  
  if(Controller1.Axis1.position(percentUnits::pct) == 0 && Controller1.Axis2.position(percentUnits::pct) == 0 && Controller1.Axis4.position(percentUnits::pct) == 0){
    TLMotor.stop();
    TRMotor.stop();
    BLMotor.stop();
    BRMotor.stop();
  }
}

void mElevator(){
  
 
}


void updateControllerStats(){
  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(1,1);
  Controller1.Screen.print("Speed: %f", speed);
  Controller1.Screen.newLine();
  Controller1.Screen.print("R: %d B: %d ", redNum, blueNum);
  Controller1.Screen.newLine();
  Controller1.Screen.print("R&B：%d", rednblueNum);
  Controller1.Screen.newLine();


  double batPercent = Brain.Battery.capacity();
  if(debug_mode){
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print("Welcome to Developer Mode");
    Brain.Screen.newLine();
    Brain.Screen.print("Battery: %.2f%%  Timer: %f", batPercent, Brain.Timer.value());
    Brain.Screen.newLine();
    Brain.Screen.print("Camera Timestamp: %.2f%%", Color_Detection.timestamp());
    Brain.Screen.newLine();
  }else{
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print("Battery: %.2f%%  Timer: %f", batPercent, Brain.Timer.value());
    Brain.Screen.newLine();
    Brain.Screen.print("Hi Builders! This is how to use the program!");
    Brain.Screen.newLine();
    Brain.Screen.print("To change modes, press X.");
    Brain.Screen.newLine();
    Brain.Screen.print("To move, use the two joysticks. Left for");
    Brain.Screen.newLine();
    Brain.Screen.print("forward and backwards. Right for rotation.");
    Brain.Screen.newLine();
    Brain.Screen.print("To change the speed, use R1(more) and R2(less).");
    Brain.Screen.newLine();
    Brain.Screen.print("Ramp mode is still in development.");
    Brain.Screen.newLine();
    Brain.Screen.print("Autonomous(lazy mode) is still in development.");
    Brain.Screen.newLine();
    Brain.Screen.print("Message sponsored by the coders :)");

    Brain.Screen.drawCircle(200, 200, 10, 10);
    Brain.Screen.drawCircle(240, 200, 10, 10);
    Brain.Screen.drawLine(200, 220, 210, 225);
    Brain.Screen.drawLine(210, 225, 230, 225);
    Brain.Screen.drawLine(230, 225, 240, 220);
  }
}

void changeSpeedGrow(){
  speed += 0.1;
}

void changeSpeedShrink(){
  speed -= 0.1;
  if(speed < 0) speed = 0;
}