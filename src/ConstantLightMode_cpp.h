#include "ConstantLightMode.h"

inline ConstantLightMode::ConstantLightMode(Gnulight &gnulight) :
		State(gnulight, "ConstMod") {
}

inline bool ConstantLightMode::onEnterState(const ButtonEvent &event) {
	MainLightLevel wantedLevel;

	if (event.getClicksCount() > 0) {
		switch (event.getClicksCount()) {
		case 1:
			wantedLevel = MainLightLevel::MAX;
			break;
		case 2:
			wantedLevel = MainLightLevel::MED;
			break;
		default:
			return false;
		}
	} else if (event.getHoldStepsCount() > 0) {
		wantedLevel = MainLightLevel::MIN;
	} else {
		return false;
	}

	Device().lightnessDimmer.setLevel(0.0);
	Device().lightnessDimmer.setState(OnOffState::ON);
	Device().lightnessDimmer.setMainLevel(wantedLevel, MAIN_LEVEL_TRANSITION_DURATION);

	return true;
}

inline bool ConstantLightMode::handleEvent(const ButtonEvent &event) {
	if (event.getClicksCount() > 0) {
		switch (event.getClicksCount()) {
		case 1:
			Device().enterState(Device().offMode);
			return true;
		case 2:
			Device().lightnessDimmer.setNextSubLevel(MAIN_LEVEL_TRANSITION_DURATION);
			return true;
		default:
			return false;
		}
	} else if (event.getHoldStepsCount() > 0) {
		Device().lightnessDimmer.setNextMainLevel(MAIN_LEVEL_TRANSITION_DURATION);
		return true;
	} else {
		return false;
	}
}
