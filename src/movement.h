#include <inttypes.h>

enum Mode{
  DRIVE,
  RAMP
};

extern Mode currentMode;
extern int8_t debug_mode;
extern double speed;

void moveRobot();
void moveArm();
void stopMotors();
void updateControllerStats();
void changeSpeedGrow();
void changeSpeedShrink();