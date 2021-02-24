using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor TLMotor;
extern motor TRMotor;
extern motor BRMotor;
extern motor BLMotor;
extern motor BElevator;
extern motor TElevator;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );