#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor TLMotor = motor(PORT20, ratio18_1, false);
motor TRMotor = motor(PORT11, ratio18_1, false);
motor BRMotor = motor(PORT16, ratio18_1, false);
motor BLMotor = motor(PORT2, ratio18_1, false);
motor BElevator = motor(PORT12, ratio18_1, false);
motor TElevator = motor(PORT1, ratio18_1, false);
/*vex-vision-config:begin*/
signature Color_Detection__REDBALL = signature (1, 5767, 8917, 7342, -103, 1437, 667, 1.4, 0);
signature Color_Detection__BLUEBALL = signature (2, -4347, -3091, -3719, 12497, 16543, 14520, 1.4, 0);
signature Color_Detection__SIG_3 = signature (3, 0, 0, 0, 0, 0, 0, 3, 0);
signature Color_Detection__SIG_4 = signature (4, 0, 0, 0, 0, 0, 0, 3, 0);
signature Color_Detection__SIG_5 = signature (5, 0, 0, 0, 0, 0, 0, 3, 0);
signature Color_Detection__SIG_6 = signature (6, 0, 0, 0, 0, 0, 0, 3, 0);
signature Color_Detection__SIG_7 = signature (7, 0, 0, 0, 0, 0, 0, 3, 0);
vision Color_Detection = vision (PORT15, 50, Color_Detection__REDBALL, Color_Detection__BLUEBALL, Color_Detection__SIG_3, Color_Detection__SIG_4, Color_Detection__SIG_5, Color_Detection__SIG_6, Color_Detection__SIG_7);
/*vex-vision-config:end*/
motor LArm = motor(PORT17, ratio18_1, false);
motor RArm = motor(PORT18, ratio18_1, false);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}