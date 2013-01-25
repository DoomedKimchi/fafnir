#ifndef LINEARVICTOR_H_
#define LINEARVICTOR_H_

/*! \brief A class that allows for easy use of Victors
 *
 * This class takes a linear speed value and converts it into a value that the Victor class in WPILib can use */

#include "WPILib.h"

class LinearVictor
{
 public:
  /*! \brief Creates a new LinearVictor on the desired port
   *
   * Initialises the Victor variable with the given port
   * \param portNum The port number for this victor */
  LinearVictor(int portNum);
  /*! \brief Destructor */
  virtual ~LinearVictor();
  
  /*! \brief sets the speed of the victor
   *
   * Sets the speed of the victor motor by after calculating the correct speed from the linear speed given
   * \param speed The speed to set the victor, scaled to a value from -1 to 1. This value will scale linearly with output.
   * \return The speed at which the victor is set */
  double set(double speed);
	
 private:
  /*! \brief Calculates a value for the victor
   * Calculates a value for the victor that will cause the output of the victor to scale linearly with the desired speed
   * \param desiredSpeed The input, scaled to a value from -1 to 1, to convert to a value for WPILib's victor class
   * \return The output for WPILib's victor */
  double calculateValue(double desiredSpeed);

  /*! The victor to use */
  Victor *victor;
};

#endif /*LINEARVICTOR_H_*/
