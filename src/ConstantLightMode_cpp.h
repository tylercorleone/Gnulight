#include "ConstantLightMode.h"

inline ConstantLightMode::ConstantLightMode(Gnulight &gnulight) :
		State(gnulight, "constLightState") {
}

inline bool ConstantLightMode::onEnterState(const ButtonEvent &event) {
	LightLevelIndex wantedLevel;

	if (event.getClicksCount() > 0) {
		switch (event.getClicksCount()) {
		case 1:
			wantedLevel = LightLevelIndex::MAX;
			break;
		case 2:
			wantedLevel = LightLevelIndex::MED;
			break;
		default:
			return false;
		}
	} else if (event.getHoldStepsCount() > 0) {
		wantedLevel = LightLevelIndex::MIN;
	} else {
		return false;
	}

	Device().lightDimmer.setLevel(0.0);
	Device().lightDimmer.setState(OnOffState::ON);
	Device().lightDimmer.setMainLevel(wantedLevel, MAIN_LEVEL_TRANSITION_DURATION_MS);

	return true;
}

inline bool ConstantLightMode::handleEvent(const ButtonEvent &event) {
	if (event.getClicksCount() > 0) {
		switch (event.getClicksCount()) {
		case 1:
			Device().enterState(Device().powerOffMode);
			return true;
		case 2:
			Device().lightDimmer.setNextSubLevel(MAIN_LEVEL_TRANSITION_DURATION_MS);
			return true;
		default:
			return false;
		}
	} else if (event.getHoldStepsCount() > 0) {
		Device().lightDimmer.setNextMainLevel(MAIN_LEVEL_TRANSITION_DURATION_MS);
		return true;
	} else {
		return false;
	}
}
