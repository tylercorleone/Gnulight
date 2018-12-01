#include "Gnulight.h"

inline Gnulight::Gnulight(BrightnessDriver &brightnessDriver, const char *deviceName) :
		GenericDevice(deviceName, &powerOffMode), brightnessDriver(
				brightnessDriver) {

}

inline void Gnulight::onSetup() {
	button.setName("btn");
	enterState(powerOffMode);
}

inline void Gnulight::switchPower(OnOffState state) {
	infoIfNamed("switchPower(%s)", state == OnOffState::ON ? "ON" : "OFF");

	if (state == OnOffState::ON) {
		infoIfNamed("HERE GNULIGHT");
		onPowerOn();
		if (batteryMonitor != nullptr) {
			StartTask(batteryMonitor);
		}
		if (tempMonitor != nullptr) {
			StartTask(tempMonitor);
		}
	} else {
		if (batteryMonitor != nullptr) {
			StopTask(batteryMonitor);
		}
		if (tempMonitor != nullptr) {
			StopTask(tempMonitor);
		}infoIfNamed("GOODBYE");
		onPowerOff();
	}
}

inline void Gnulight::onPowerOn() {

}

inline void Gnulight::onPowerOff() {

}
