// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// TLMotor              motor         12              
// TRMotor              motor         13              
// BRMotor              motor         9               
// BLMotor              motor         10              
// BElevator            motor         14              
// TElevator            motor         11              
// Color_Detection      vision        8               
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
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
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

void changeMode(){
  if(currentMode == RAMP){
    currentMode = DRIVE;
  }else{
    currentMode = RAMP;
  }
}

int8_t debug_mode = 0;

void enableDebuggerMode(){
  if(debug_mode)
    debug_mode = 0x0;
  else
    debug_mode = 0x1;
}

void usercontrol(void) {
  Controller1.ButtonR1.pressed(changeSpeedGrow);
  Controller1.ButtonR2.pressed(changeSpeedShrink);
  Controller1.ButtonX.pressed(changeMode);
  Controller1.ButtonL1.pressed(enableDebuggerMode);

  Controller1.ButtonUp.pressed(elevatorUp);
  Controller1.ButtonDown.pressed(elevatorReject);


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
    if(currentMode == DRIVE){
      moveRobot();
      cameraAutoSpin();
    }else{
      moveArm();
    }

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