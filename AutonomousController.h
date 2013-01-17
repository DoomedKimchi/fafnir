#ifndef AUTONOMOUS_CONTROLLER_H
#define AUTONOMOUS_CONTROLLER_H

#include "Robot.h"

class AutonomousController {
 private:
  Robot *fafnir;
 public:
  AutonomousController(Robot *fafnir);
  boolean fire();
  virtual ~AutonomousController();
};

#endif /* AUTONOMOUS_CONTROLLER_H */
