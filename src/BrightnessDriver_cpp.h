#include "BrightnessDriver.h"

inline BrightnessDriver::BrightnessDriver(TaskManager &taskManager) {
	setName("brightDriver");

	gradualMaxCurrentLevelSetter = new GradualCappablePotentiometerActuator(
			MsToTaskTime(DELAY_BETWEEN_LEVEL_CHANGE_MS), taskManager, *this);
}

inline void BrightnessDriver::updateLevelMaxLimit() {
	float limit = min(tempCausedLimit, battCausedLimit);

	gradualMaxCurrentLevelSetter->setLevelMaxLimit(limit,
			MsToTaskTime(STEP_UP_DOWN_DURATION_MS));
}

inline void BrightnessDriver::setBatteryCausedLimit(float limit) {
	battCausedLimit = limit;
	updateLevelMaxLimit();
}

inline void BrightnessDriver::setTemperatureCausedLimit(float limit) {
	tempCausedLimit = limit;
	updateLevelMaxLimit();
}
