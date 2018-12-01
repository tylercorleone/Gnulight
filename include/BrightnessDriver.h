#ifndef BRIGHTNESSDRIVER_H
#define BRIGHTNESSDRIVER_H

#include "gnulight_config.h"

#include <Components.h>
#include <stdint.h>

#define LEVEL_MAX_LIMIT_TRANSITION_MS 2000
#define MIN_LEVEL_WITHOUT_PWM 0.031f

class BrightnessDriver: public CappablePotentiometer {
public:
	BrightnessDriver(TaskManager &taskManager);
	void updateLevelMaxLimit();
	void setBatteryCausedLimit(float limit);
	void setTemperatureCausedLimit(float limit);
	void onSetLevel(float level) override;
private:
	void digPotWrite(uint16_t value);
	float battCausedLimit = 1.0f;
	float tempCausedLimit = 1.0f;
	GradualCappablePotentiometerActuator *gradualMaxCurrentLevelSetter;
};

#endif
