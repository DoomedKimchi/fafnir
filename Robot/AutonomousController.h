#ifndef AUTONOMOUS_CONTROLLER_H
#define AUTONOMOUS_CONTROLLER_H

#include "Robot.h"

/*! \brief Controller for the autonomous period
 *
 * Controls the robot during the autonomous period of the competition
 * Currently, it only fires frisbees at targets */

class AutonomousController {
 private:
  /*! A pointer to the Robot fafnir */
  Robot *fafnir;

  /*! \brief Tells the robot to fire
   * \return Whether firing was successful */
  bool fire();

 public:
  
  void update();
  /*! \brief Constructs an autonomous controller with a pointer to fafnir
   * \param *fafnir A pointer to the Robot */
  AutonomousController(Robot *fafnir);

  /*! \brief Destructor */
  virtual ~AutonomousController();
};

#endif /* AUTONOMOUS_CONTROLLER_H */
