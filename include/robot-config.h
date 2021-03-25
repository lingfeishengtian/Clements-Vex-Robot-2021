using namespace vex;

extern brain Brain;

using signature = vision::signature;

// VEXcode devices
extern controller Controller1;
extern motor TLMotor;
extern motor TRMotor;
extern motor BRMotor;
extern motor BLMotor;
extern motor BElevator;
extern motor TElevator;
extern signature Color_Detection__REDBALL;
extern signature Color_Detection__BLUEBALL;
extern signature Color_Detection__SIG_3;
extern signature Color_Detection__SIG_4;
extern signature Color_Detection__SIG_5;
extern signature Color_Detection__SIG_6;
extern signature Color_Detection__SIG_7;
extern vision Color_Detection;
extern motor LArm;
extern motor RArm;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );