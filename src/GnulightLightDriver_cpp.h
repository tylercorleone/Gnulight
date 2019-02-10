#include "GnulightLightDriver.h"

inline GnulightLightDriver::GnulightLightDriver(const char *name) :
		CappablePotentiometer(name) {

}

inline void GnulightLightDriver::updateLevelMaxLimit() {
	maxBrightnessSetter->setLevelMaxLimit(
			_min(tempCausedLimit, battCausedLimit), STEP_UP_DOWN_DURATION);
}

inline void GnulightLightDriver::setBatteryCausedLimit(float limit) {
	battCausedLimit = limit;
	updateLevelMaxLimit();
}

inline void GnulightLightDriver::setTemperatureCausedLimit(float limit) {
	tempCausedLimit = limit;
	updateLevelMaxLimit();
}
