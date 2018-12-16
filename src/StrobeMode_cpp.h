#include "StrobeMode.h"

inline StrobeMode::StrobeMode(Gnulight &gnulight) :
		State(gnulight, "StrobMod") {
}

inline bool StrobeMode::onEnterState(const ButtonEvent &event) {
	logger.debug("type %d", strobeIndex);

	t_0 = MILLIS_PROVIDER();

	waveMaxLevel = Device().lightnessDimmer.setMainLevel(MainLightLevel::MED);

	if (strobes[strobeIndex] == SINUSOIDAL_WAVE
			|| strobes[strobeIndex] == TRIANGULAR_WAVE) {
		Device().lightnessDimmer.setLevel(0.0f);
		Device().lightnessDimmer.setState(OnOffState::ON);
	}

	Device().getTaskManager().StartTask(&toggleLightStatusTask);
	return true;
}

inline void StrobeMode::onExitState() {
	Device().getTaskManager().StopTask(&toggleLightStatusTask);
}

inline bool StrobeMode::handleEvent(const ButtonEvent &event) {
	t_0 = MILLIS_PROVIDER();

	if (event.getClicksCount() > 0) {

		switch (event.getClicksCount()) {
		case 1:
			Device().enterState(Device().offMode);
			return true;
		case 2:
			strobeIndex = (strobeIndex + 1) % STROBE_TYPES_COUNT;
			logger.debug("type %d", strobeIndex);

			if (strobes[strobeIndex] == SINUSOIDAL_WAVE
					|| strobes[strobeIndex] == TRIANGULAR_WAVE) {

				MainLightLevel currentMainLevel =
						Device().lightnessDimmer.getCurrentMainLevel();
				waveMaxLevel = Device().lightnessDimmer.setMainLevel(
						currentMainLevel);
				Device().lightnessDimmer.setState(OnOffState::ON);
			}
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
		// TODO: we should shut the light off, before?
		waveMaxLevel = Device().lightnessDimmer.setNextMainLevel();
	} else {
		return false;
	}

	toggleLightStatusTask.setTimeInterval(0);
	return true;
}

#define THE_PERIOD ((uint32_t) STROBE_PERIODICAL_SEQUENCE_PERIOD_MS * _this->periodMultiplierX1000 / 1000)
#define CURRENT_STROBE (_this->strobes[_this->strobeIndex])

inline uint32_t StrobeMode::onUpdate(StrobeMode *_this) {
	uint32_t nextIntervalMs;
	float nextLevel;

	switch (CURRENT_STROBE) {

	case ON_OFF_STROBE:
		nextIntervalMs = (uint32_t) STROBE_ON_OFF_INIT_PERIOD_MS / 2
				* _this->periodMultiplierX1000 / 1000;
		break;
	case BEACON_STROBE:
		if (_this->Device().lightnessDimmer.getState() == OnOffState::OFF) {
			nextIntervalMs = STROBE_BEACON_PERIOD_MS * STROBE_BEACON_DUTY_CYCLE;
		} else {
			nextIntervalMs = STROBE_BEACON_PERIOD_MS
					* (1.0f - STROBE_BEACON_DUTY_CYCLE);
		}
		break;
	case DISCO_STROBE:
		if (_this->Device().lightnessDimmer.getState() == OnOffState::OFF) {
			nextIntervalMs = STROBE_DISCO_PERIOD_MS * STROBE_DISCO_DUTY_CYCLE;
		} else {
			nextIntervalMs = STROBE_DISCO_PERIOD_MS
					* (1.0f - STROBE_DISCO_DUTY_CYCLE);
		}
		break;
	case SINUSOIDAL_WAVE:
		nextIntervalMs = STROBE_LEVEL_REFRESH_INTERVAL_MS;
		nextLevel = LEVEL_LOW_1
				+ (_this->waveMaxLevel - LEVEL_LOW_1)
						* (sinWave(MILLIS_PROVIDER() - _this->t_0, THE_PERIOD));
		break;
	case TRIANGULAR_WAVE:
		nextIntervalMs = STROBE_LEVEL_REFRESH_INTERVAL_MS;
		nextLevel = LEVEL_LOW_1
				+ (_this->waveMaxLevel - LEVEL_LOW_1)
						* triangularWave(MILLIS_PROVIDER() - _this->t_0,
						THE_PERIOD);
		break;
	default:
		return -1;
	}

	if (CURRENT_STROBE != SINUSOIDAL_WAVE
			&& CURRENT_STROBE != TRIANGULAR_WAVE) {

		/*
		 * it is an ON/OFF strobe
		 */
		_this->Device().lightnessDimmer.toggleState();
	} else {

		/*
		 * it is a "level-change" sequence
		 */
		_this->Device().lightnessDimmer.setLevel(nextLevel);
	}

	return MsToTaskTime(nextIntervalMs);
}

#undef THE_PERIOD
#undef CURRENT_STROBE

inline float StrobeMode::triangularWave(uint32_t millis, uint32_t periodMs) {
	millis = millis % periodMs;
	if (millis < periodMs / 2) {
		return static_cast<float>(millis) / (periodMs / 2);
	} else {
		return static_cast<float>(-(millis - periodMs)) / (periodMs / 2);
	}
}

inline float StrobeMode::sinWave(uint32_t millis, uint32_t periodMs) {
	return (-_cos(millis * (_TWO_PI / periodMs)) + 1.0f) / 2.0f;
}
