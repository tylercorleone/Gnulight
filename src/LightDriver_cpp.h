#include "LightDriver.h"

inline void LightDriver::updateLevelMaxValue() {
	maxBrightnessActuator->updateLevelMaxValue(
			_min(tempCausedLimit, battCausedLimit), STEP_UP_DOWN_TRANSITION_DURATION);
}

inline void LightDriver::setBatteryCausedLimit(float limit) {
	battCausedLimit = limit;
	updateLevelMaxValue();
}

inline void LightDriver::setTemperatureCausedLimit(float limit) {
	tempCausedLimit = limit;
	updateLevelMaxValue();
}
