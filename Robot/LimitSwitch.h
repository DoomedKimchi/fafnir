#ifndef LIMIT_SWITCH_H
#define LIMIT_SWITCH_H

#include <WPILib.h>

class LimitSwitch : public DigitalInput {
	public:
		LimitSwitch(int CHANNEL);
		LimitSwitch(int MODULE, int CHANNEL);
		bool IsPressed();
};
#endif /* LIMIT_SWITCH_H */
