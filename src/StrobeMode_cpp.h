#include "StrobeMode.h"

inline StrobeMode::StrobeMode(Gnulight &gnulight) :
		State(gnulight, "strobeState") {
}

inline bool StrobeMode::onEnterState(const ButtonEvent &event) {
	debugIfNamed("type %d", currentStrobeType);

	varName = Device().lightDimmer.setMainLevel(LightLevelIndex::MED);

	if (currentStrobeType == SINUSOIDAL_STROBE
			|| currentStrobeType == LINEAR_STROBE) {
		Device().lightDimmer.setState(OnOffState::ON);
	}

	Device().StartTask(&toggleLightStatusTask);
	return true;
}

inline void StrobeMode::onExitState() {
	Device().StopTask(&toggleLightStatusTask);
}

inline bool StrobeMode::handleEvent(const ButtonEvent &event) {
	if (event.getClicksCount() > 0) {

		switch (event.getClicksCount()) {
		case 1:
			Device().enterState(Device().powerOffMode);
			return true;
		case 2:
			currentStrobeType = (currentStrobeType + 1) % STROBE_TYPES_COUNT;
			debugIfNamed("type %d", currentStrobeType);

			if (currentStrobeType == SINUSOIDAL_STROBE
					|| currentStrobeType == LINEAR_STROBE) {

				LightLevelIndex currentMainLevel =
						Device().lightDimmer.getCurrentMainLevel();
				varName = Device().lightDimmer.setMainLevel(
						currentMainLevel);
				Device().lightDimmer.setState(OnOffState::ON);
			}

			toggleLightStatusTask.setTimeInterval(0);
			Device().ResetTask(&toggleLightStatusTask);
			return true;
		case 3:
			if (periodMultiplierX1000 <= 32000) {
				periodMultiplierX1000 *= 2;
			}
			return true;
		case 4:
			if (periodMultiplierX1000 > 125) {
				periodMultiplierX1000 /= 2;
			}
			return true;
		default:
			return false;
		}

	} else if (event.getHoldStepsCount() > 0) {
		varName = Device().lightDimmer.setNextMainLevel();
		return true;
	} else {
		return false;
	}
}

#define THE_PERIOD (STROBE_PERIODICAL_SEQUENCE_PERIOD_MS * _this->periodMultiplierX1000 / 1000)

inline uint32_t StrobeMode::switchLightStatus(StrobeMode* _this) {
	uint32_t nextIntervalMs;
	float nextPotentiometerLevel;

	switch (_this->currentStrobeType) {

	case ON_OFF_STROBE:
		nextIntervalMs = STROBE_ON_OFF_INIT_PERIOD_MS / 2
				* _this->periodMultiplierX1000 / 1000;
		break;
	case BEACON_STROBE:
		if (_this->Device().lightDimmer.getState() == OnOffState::OFF) {
			nextIntervalMs = STROBE_BEACON_PERIOD_MS * STROBE_BEACON_DUTY_CYCLE;
		} else {
			nextIntervalMs = STROBE_BEACON_PERIOD_MS
					* (1.0f - STROBE_BEACON_DUTY_CYCLE);
		}
		break;
	case DISCO_STROBE:
		if (_this->Device().lightDimmer.getState() == OnOffState::OFF) {
			nextIntervalMs = STROBE_DISCO_PERIOD_MS * STROBE_DISCO_DUTY_CYCLE;
		} else {
			nextIntervalMs = STROBE_DISCO_PERIOD_MS
					* (1.0f - STROBE_DISCO_DUTY_CYCLE);
		}
		break;
	case SINUSOIDAL_STROBE:
		nextIntervalMs = STROBE_LEVEL_REFRESH_INTERVAL_MS;
		nextPotentiometerLevel = LEVEL_LOW_1
				+ (_this->varName - LEVEL_LOW_1)
						* (sinWave(millis(), THE_PERIOD));
		break;
	case LINEAR_STROBE:
		nextIntervalMs = STROBE_LEVEL_REFRESH_INTERVAL_MS;
		nextPotentiometerLevel = LEVEL_LOW_1
				+ (_this->varName - LEVEL_LOW_1)
						* triangularWave(millis(), THE_PERIOD);
		break;
	default:
		return -1;
	}

	if (_this->currentStrobeType != SINUSOIDAL_STROBE
			&& _this->currentStrobeType != LINEAR_STROBE) {

		/*
		 * it is an ON/OFF strobe
		 */
		_this->Device().lightDimmer.toggleState();
	} else {

		/*
		 * it is a "level-change" sequence
		 */
		_this->Device().lightDimmer.setLevel(nextPotentiometerLevel);
	}

	return MsToTaskTime(nextIntervalMs);
}

#undef THE_PERIOD

inline float StrobeMode::triangularWave(uint32_t millis, uint32_t periodMs) {
	millis = millis % periodMs;
	if (millis < periodMs / 2) {
		return static_cast<float>(millis) / (periodMs / 2);
	} else {
		return static_cast<float>(-(millis - periodMs)) / (periodMs / 2);
	}
}

inline float StrobeMode::sinWave(uint32_t millis, uint32_t periodMs) {
	return (_sin(millis * (TWO_PI / periodMs)) + 1.0f) / 2.0f;
}
