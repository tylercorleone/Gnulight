#include "KissLightLightDriver.h"

inline KissLightLightDriver::KissLightLightDriver(const char *name) :
		CappablePotentiometer(name) {

}

inline void KissLightLightDriver::updateLevelMaxLimit() {
	maxBrightnessSetter->setLevelMaxLimit(
			_min(tempCausedLimit, battCausedLimit), STEP_UP_DOWN_DURATION);
}

inline void KissLightLightDriver::setBatteryCausedLimit(float limit) {
	battCausedLimit = limit;
	updateLevelMaxLimit();
}

inline void KissLightLightDriver::setTemperatureCausedLimit(float limit) {
	tempCausedLimit = limit;
	updateLevelMaxLimit();
}
