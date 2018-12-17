#include "StrobeMode.h"

inline StrobeMode::StrobeMode(Gnulight &gnulight) :
		State(gnulight, "StrobMod") {

	signalGenerator = new SignalGenerator(gnulight.getTaskManager(),
			gnulight.lightnessDimmer, STROBE_LEVEL_REFRESH_INTERVAL_MS);
}

#define THE_PERIOD ((uint32_t) STROBE_PERIODICAL_SEQUENCE_PERIOD_MS * periodMultiplierX1000 / 1000)

inline bool StrobeMode::onEnterState(const ButtonEvent &event) {
	logger.trace("index %d", strobeIndex);

	levelMax = Device().lightnessDimmer.setMainLevel(MainLightLevel::MED);

	signalGenerator->start(signalTypes[strobeIndex], LEVEL_LOW_1, levelMax,
			THE_PERIOD);

	Device().lightnessDimmer.setLevel(0.0f);
	Device().lightnessDimmer.setState(OnOffState::ON);
	return true;
}

inline void StrobeMode::onExitState() {
	signalGenerator->stop();
}

inline bool StrobeMode::handleEvent(const ButtonEvent &event) {
	if (event.getClicksCount() > 0) {

		switch (event.getClicksCount()) {
		case 1:
			Device().enterState(Device().offMode);
			return true;
		case 2:
			strobeIndex = (strobeIndex + 1) % SIGNAL_TYPES_COUNT;
			logger.debug("index %d", strobeIndex);
			break;
		case 3:
			if (periodMultiplierX1000 <= 32000) {
				periodMultiplierX1000 *= 2;
			}
			break;
		case 4:
			if (periodMultiplierX1000 > 125) {
				periodMultiplierX1000 /= 2;
			}
			break;
		default:
			return false;
		}

	} else if (event.getHoldStepsCount() > 0) {
		levelMax = Device().lightnessDimmer.setNextMainLevel();
	} else {
		return false;
	}

	signalGenerator->start(signalTypes[strobeIndex], LEVEL_LOW_1, levelMax,
			THE_PERIOD);
	return true;
}

#undef THE_PERIOD
