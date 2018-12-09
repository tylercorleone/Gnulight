#ifndef PARAMETERCHECKMODE_H
#define PARAMETERCHECKMODE_H

#include "gnulight_config.h"

#include <Components.h>

class Gnulight;

class ParameterCheckMode: public State<Gnulight, MessageEvent> {
public:
	const char *BATTERY_CHECK_MSG = "b";
	const char *LAMP_TEMPERATURE_CHECK_MSG = "t";
	ParameterCheckMode(Gnulight &gnulight);
protected:
	bool onEnterState(const MessageEvent &event) override;
	void onExitState() override;
	static uint32_t switchLightStatus(ParameterCheckMode *_this);
	Procedure &renderValueWithFlashes = ProcedureBuilder::begin(
			ParameterCheckMode::switchLightStatus, this).thenRepeat();
	int8_t strobesForIntegerPartCount = 0;
	int8_t strobesForDecimalPartCount = 0;
};

#endif
