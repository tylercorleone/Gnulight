#include "Gnulight.h"

inline Gnulight::Gnulight(GnulightLightDriver &_brightnessDriver,
		const char *deviceName) :
		GenericDevice(deviceName, &offMode), lightDriver(
				_brightnessDriver) {
	lightDriver.maxBrightnessSetter =
			new GradualCappablePotentiometerActuator(DELAY_BETWEEN_LEVEL_CHANGE,
					*this, lightDriver);
}

inline void Gnulight::onSetup() {
	enterState(offMode);
}

inline void Gnulight::setState(OnOffState state) {

	if (state == OnOffState::ON) {
		debugIfNamed("onSwitch%s", "On");
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

		debugIfNamed("onSwitch%s", "Off");
		onSwitchOff();
	}
}

inline void Gnulight::onSwitchOn() {

}

inline void Gnulight::onSwitchOff() {

}
