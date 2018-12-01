#include "BrightnessDriver.h"

inline BrightnessDriver::BrightnessDriver(TaskManager &taskManager) {
	setName("brightDriver");

	gradualMaxCurrentLevelSetter = new GradualCappablePotentiometerActuator(
			DELAYED_LEVEL_SETTER_INTERVAL_MS, taskManager, *this);
}

inline void BrightnessDriver::updateLevelMaxLimit() {
	float limit = min(tempCausedLimit, battCausedLimit);

	gradualMaxCurrentLevelSetter->setLevelMaxLimit(limit,
			MsToTaskTime(LEVEL_MAX_LIMIT_TRANSITION_MS));
}

inline void BrightnessDriver::setBatteryCausedLimit(float limit) {
	battCausedLimit = limit;
	updateLevelMaxLimit();
}

inline void BrightnessDriver::setTemperatureCausedLimit(float limit) {
	tempCausedLimit = limit;
	updateLevelMaxLimit();
}
