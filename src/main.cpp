// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// TLMotor              motor         20              
// TRMotor              motor         11              
// BRMotor              motor         16              
// BLMotor              motor         2               
// BElevator            motor         12              
// TElevator            motor         1               
// Color_Detection      vision        15              
// LArm                 motor         17              
// RArm                 motor         18              
// ---- END VEXCODE CONFIGURED DEVICES ----
/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/


#include "vex.h"
#include "movement.h"

using namespace vex;

// A global instance of competition
competition Competition;

void autonomous();

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

double var = 1.0;

void redVel(){
  var -= 0.1;
}

void incVel(){
  var += 0.1;
}

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/


void autonomous(void) {

  // Move forward
  mForward(0.58);
  // Rotate -135 degrees
  mRotate(-135);
  // Move forward
  mForward(0.7);
  // Pull and push ball out
  mPullBall(2.0);

  mForward(0.5);

  mPullBall(0.8);

  mForward(-0.8);

  mRotate(-45);
  
  mSide(1.6);

  mForward(0.5);

  mPullBall(2.0);
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*--
-------------------------------------------------------------------------*/

void usercontrol(void) {
  Controller1.ButtonR1.pressed(armPull);
  Controller1.ButtonR2.pressed(elevatorUp);

  Controller1.ButtonL1.pressed(armReject);
  Controller1.ButtonDown.pressed(elevatorPush);
  Controller1.ButtonL2.pressed(elevatorReject);

  Controller1.ButtonA.pressed(changeSpeedGrow);
  Controller1.ButtonB.pressed(changeSpeedShrink);
  Controller1.ButtonX.pressed(changeElevSpeedGrow);
  Controller1.ButtonY.pressed(changeElevSpeedShrink);

  //Controller1.ButtonUp.pressed(autonomous);
  Controller1.ButtonLeft.pressed(redVel);
  Controller1.ButtonRight.pressed(incVel);
  Color_Detection.setLedMode(vex::vision::ledMode::manual);
  Color_Detection.setLedColor(255, 255, 255);
  Color_Detection.setLedBrightness(100);
  // User control code here, inside the loop
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................
    
    updateControllerStats();
    moveRobot();
    cameraAutoSpin();
    stopMotors();

    wait(100, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}