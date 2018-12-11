#include "ParameterCheckMode.h"

inline ParameterCheckMode::ParameterCheckMode(Gnulight &gnulight) :
		State(gnulight, "ParCkMod") {
}

inline bool ParameterCheckMode::onEnterState(const MessageEvent &event) {
	float parameterValue;

	if (event.equals(BATTERY_CHECK_MSG) && Device().pBatteryMonitor != nullptr) {

		parameterValue = _round(Device().pBatteryMonitor->battery.getRemainingCharge() * 10.0f);

	} else if (event.equals(LAMP_TEMPERATURE_CHECK_MSG) && Device().pTempMonitor != nullptr) {

		parameterValue = Device().pTempMonitor->readTemperature() / 10.0f;

	} else {
		return false;
	}

	// lets round to the first decimal
	parameterValue = _round(parameterValue * 10.0f) / 10.0f;

	// the integer part
	strobesForIntegerPartCount = (int8_t) parameterValue;

	// the decimal part
	strobesForDecimalPartCount = ((int8_t) (parameterValue * 10)) % 10;

	logger.trace("%s: %f", event.getMessage(), parameterValue);

	Device().lightnessDimmer.setState(OnOffState::OFF); // light could be ON!
	Device().lightnessDimmer.setMainLevel(MainLightLevel::MED);
	Device().getTaskManager().StartTask(&renderValueWithFlashes);

	return true;
}

inline void ParameterCheckMode::onExitState() {
	Device().getTaskManager().StopTask(&renderValueWithFlashes);
}

inline uint32_t ParameterCheckMode::switchLightStatus(ParameterCheckMode *_this) {
	if (_this->strobesForIntegerPartCount <= 0
			&& _this->strobesForDecimalPartCount == 0) {

		/*
		 * signal finished
		 */
		_this->Device().enterState(_this->Device().offMode);
		return 0;
	}

	_this->Device().lightnessDimmer.toggleState();

	int8_t *pCounter;
	float intervalMultiplier;

	if (_this->strobesForIntegerPartCount >= 0) {

		/*
		 * Is an integer or the comma
		 */
		pCounter = &_this->strobesForIntegerPartCount;

		if (_this->strobesForIntegerPartCount == 0
				&& _this->Device().lightnessDimmer.getState() == OnOffState::ON) {
			intervalMultiplier = PAR_CHECK_COMMA_DUTY_CYCLE;
		} else {
			intervalMultiplier = PAR_CHECK_DIGIT_DUTY_CYCLE;
		}

	} else {

		/*
		 * Is a decimal
		 */
		pCounter = &_this->strobesForDecimalPartCount;
		intervalMultiplier = PAR_CHECK_DIGIT_DUTY_CYCLE;
	}

	if (_this->Device().lightnessDimmer.getState() == OnOffState::OFF) {
		--*pCounter;
		intervalMultiplier = 1.0f - intervalMultiplier;
	}

	return MsToTaskTime(PAR_CHECK_STROBE_PERIOD_MS * intervalMultiplier);
}
