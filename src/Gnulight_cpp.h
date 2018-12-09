#include "Gnulight.h"

inline Gnulight::Gnulight(GnulightLightDriver &lightDriver, const char *name) :
		GenericDevice(&offMode, name), lightDriver(lightDriver) {
	lightDriver.maxBrightnessSetter = new GradualCappablePotentiometerActuator(
	DELAY_BETWEEN_LEVEL_CHANGE, *this, lightDriver);
}

inline void Gnulight::onSetup() {
	enterState(offMode);
}

inline void Gnulight::setState(OnOffState state) {

	if (state == OnOffState::ON) {
		logger.debug("onSwitch%s", "On");
		onSwitchOn();

		if (pBatteryMonitor != nullptr) {
			StartTask(pBatteryMonitor);
		}

		if (pTempMonitor != nullptr) {
			StartTask(pTempMonitor);
		}
	} else {
		if (pBatteryMonitor != nullptr) {
			StopTask(pBatteryMonitor);
		}

		if (pTempMonitor != nullptr) {
			StopTask(pTempMonitor);
		}

		lightnessDimmer.setState(OnOffState::OFF);

		logger.debug("onSwitch%s", "Off");
		onSwitchOff();
	}
}

inline void Gnulight::onSwitchOn() {

}

inline void Gnulight::onSwitchOff() {

}
