#include "vex.h"
#include "movement.h"
#include <stdint.h>

using namespace vex;

void wheelsSetVelocity(int, int, int);
void spinWheelsFor(double);

double elevSpeed = 1.5;
double speed = 1.5;

bool autoSpin = false;

void mForward(double x){
  int veloc = (x < 0) ? -38 : 38;
  wheelsSetVelocity(veloc, veloc, 0);
  spinWheelsFor(x * (x < 0 ? -1 : 1));   
}

void mSide(double x){
  wheelsSetVelocity(0, 0, (x < 0) ? 40 : -40);
  spinWheelsFor(x);   
}

void mRotate(double deg){
  int lV = round((deg / 180.0) * 40);
  int rV = round((deg / 180.0) * 40) * -1;

  wheelsSetVelocity(lV, rV, 0);
  spinWheelsFor(1);
}

void mPullBall(double waitFor){
  armPull();
  elevatorUp();
  wait(waitFor, sec);
  stopMotors();
}

void elevatorReject(){
  BElevator.setVelocity(40 * elevSpeed, pct);
  BElevator.spin(reverse);
  TElevator.setVelocity(40 * elevSpeed, pct);
  TElevator.spin(fwd);
}

void elevatorUp(){
  BElevator.setVelocity(40 * elevSpeed, pct);
  BElevator.spin(reverse);
  TElevator.setVelocity(40 * elevSpeed, pct);
  TElevator.spin(reverse);
}

void elevatorPush(){
  BElevator.setVelocity(40 * elevSpeed, pct);
  BElevator.spin(fwd);
  TElevator.setVelocity(40 * elevSpeed, pct);
  TElevator.spin(fwd);
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

void armPull(){
  LArm.setVelocity(50, pct);
  LArm.spin(reverse);
  RArm.setVelocity(50, pct);
  RArm.spin(reverse);
}

void armReject(){
  LArm.setVelocity(50, pct);
  LArm.spin(fwd);
  RArm.setVelocity(50, pct);
  RArm.spin(fwd);
}

void wheelsSetVelocity(int leftVelocity, int rightVelocity, int horizontal){
    TLMotor.setVelocity(leftVelocity * speed + horizontal, percent);
    TRMotor.setVelocity(rightVelocity * speed - horizontal, percent);
    BLMotor.setVelocity(leftVelocity * speed - horizontal, percent);
    BRMotor.setVelocity(rightVelocity * speed + horizontal, percent);
}
/**
 *  If sec is 0, function will make wheels spin until manually stopped
 **/
void spinWheelsFor(double sec){
    TLMotor.spin(fwd);
    TRMotor.spin(reverse);
    BLMotor.spin(fwd);
    BRMotor.spin(reverse);
  if(sec > 0){
    wait(sec, seconds);
    stopMotors();
  }
}

void moveRobot(){
    int leftvelocity = Controller1.Axis2.position(percentUnits::pct)/5 + Controller1.Axis4.position(percentUnits::pct)/5;
    int rightvelocity = Controller1.Axis2.position(percentUnits::pct)/5 - Controller1.Axis4.position(percentUnits::pct)/5;
    int horizon = (Controller1.Axis1.position(percentUnits::pct)/5 * speed);

    wheelsSetVelocity(leftvelocity, rightvelocity, horizon);

    spinWheelsFor(0);
}

void stopMotors(){
  if(!Controller1.ButtonR1.pressing() && !Controller1.ButtonL1.pressing()){
    LArm.stop();
    RArm.stop();
  }  
  if(!Controller1.ButtonL2.pressing() && !Controller1.ButtonR2.pressing() && !Controller1.ButtonDown.pressing() && !autoSpin){
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

void updateControllerStats(){
  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(1,1);
  Controller1.Screen.print("GS: %.2fx ES: %.2fx", speed, elevSpeed);
  Controller1.Screen.newLine();
  Controller1.Screen.print("R: %d B: %d ", redNum, blueNum);
  Controller1.Screen.newLine();
  Controller1.Screen.print("Time：%f", Brain.Timer.value());
  Controller1.Screen.newLine();


  double batPercent = Brain.Battery.capacity();
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

void changeSpeedGrow(){
  speed += 0.1;
}

void changeSpeedShrink(){
  speed -= 0.1;
  if(speed < 0) speed = 0;
}

void changeElevSpeedGrow(){
  elevSpeed += 0.1;
}

void changeElevSpeedShrink(){
  elevSpeed -= 0.1;
  if(elevSpeed < 0) elevSpeed = 0;
}