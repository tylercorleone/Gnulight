#ifndef PARAMETERCHECKMODE_H
#define PARAMETERCHECKMODE_H

#include "gnulight_config.h"

#include <Components.h>

class Gnulight;

#define SIGNAL_STROBE_INTERVAL_MS 800UL
#define DIGIT_SIGNAL_DUTY_CYCLE 0.15f
#define COMMA_SIGNAL_DUTY_CYCLE 1.0f

class ParameterCheckMode: public State<Gnulight, MessageEvent> {
public:
	const char *BATTERY_CHECK_MSG = "b";
	const char *LAMP_TEMPERATURE_CHECK_MSG = "t";
	ParameterCheckMode(Gnulight &gnulight);
protected:
	bool onEnterState(const MessageEvent &event) override;
	void onExitState() override;
	static uint32_t switchLightStatus(ParameterCheckMode *_this);
	FunctionsSequenceTask& renderValueWithFlashes = SequenceTaskBuilder::begin(
			ParameterCheckMode::switchLightStatus, this).thenRepeat();
	int8_t strobesForIntegerPartCount = 0;
	int8_t strobesForDecimalPartCount = 0;
};

#endif
