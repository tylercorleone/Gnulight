#ifndef PARAMETERCHECKMODE_H
#define PARAMETERCHECKMODE_H

#include "gnulight_config.h"

#include <Components.h>

class Gnulight;

class ParameterCheckMode: public State<Gnulight, MessageEvent>, private Task {
public:
	const char *BATTERY_CHECK_MSG = "b";
	const char *LAMP_TEMPERATURE_CHECK_MSG = "t";
	ParameterCheckMode(Gnulight &gnulight);
protected:
	bool onEnterState(const MessageEvent &event) override;
	void onExitState() override;
	void OnUpdate(uint32_t deltaTime) override;
	int8_t strobesForIntegerPartCount = 0;
	int8_t strobesForDecimalPartCount = 0;
};

#endif
