#include "PowerOffMode.h"

inline PowerOffMode::PowerOffMode(Gnulight &gnulight) :
		State(gnulight, "powerOffState") {
}

inline bool PowerOffMode::onEnterState() {
	Device().lightDimmer.setState(OnOffState::OFF);
	Device().switchPower(OnOffState::OFF);
	return true;
}

inline void PowerOffMode::onExitState() {
	Device().switchPower(OnOffState::ON);
}

inline bool PowerOffMode::handleEvent(const ButtonEvent &event) {

	if (event.getClicksCount() > 0) {

		switch (event.getClicksCount()) {
		case 1:
		case 2:
			Device().enterState(Device().constantLightMode, event);
			return true;
		case 3:
			Device().enterState(Device().strobeMode, event);
			return true;
		case 4:
			Device().enterState(Device().parameterCheckMode, MessageEvent(Device().parameterCheckMode.BATTERY_CHECK_MSG));
			return true;
		case 5:
			Device().enterState(Device().parameterCheckMode, MessageEvent(Device().parameterCheckMode.LAMP_TEMPERATURE_CHECK_MSG));
			return true;
		case 6:
			Device().lightDimmer.isLightnessSimulationEnabled(
					!Device().lightDimmer.isLightnessSimulationEnabled());
			return true;
		default:
			return false;
		}

	} else if (event.getHoldStepsCount() > 0) {
		Device().enterState(Device().constantLightMode, event);
		return true;
	} else {
		return false;
	}
}
