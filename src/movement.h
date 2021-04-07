#include <inttypes.h>

enum Mode{
  DRIVE,
  RAMP
};

extern Mode currentMode;
extern int8_t debug_mode;
extern double speed;

void moveRobot();
void mElevator();
void stopMotors();
void updateControllerStats();
void changeSpeedGrow();
void changeSpeedShrink();
void changeElevSpeedGrow();
void changeElevSpeedShrink();
void cameraAutoSpin();
void elevatorReject();
void elevatorUp();
void elevatorPush();
void mForward(double);
void left();
void right();