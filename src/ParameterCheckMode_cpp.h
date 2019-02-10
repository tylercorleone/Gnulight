#include "ParameterCheckMode.h"

inline ParameterCheckMode::ParameterCheckMode(Gnulight &gnulight) :
		State(gnulight, "ParCkMod"), Task(0) {
}

inline bool ParameterCheckMode::onEnterState(const MessageEvent &event) {
	float parameterValue;

	if (event.equals(BATTERY_CHECK_MSG)
			&& Device().pBatteryMonitor != nullptr) {

		/*
		 * battery check
		 */
		parameterValue = Device().pBatteryMonitor->battery.getRemainingCharge()
				* 10.0f;
		parameterValue = _round(parameterValue);
	} else if (event.equals(LAMP_TEMPERATURE_CHECK_MSG)
			&& Device().pTempMonitor != nullptr) {

		/*
		 * temperature check
		 */
		parameterValue = Device().pTempMonitor->readTemperature() / 10.0f;
	} else {
		return false;
	}

	// lets round to the first decimal
	parameterValue *= 10.0f;
	parameterValue = _round(parameterValue) / 10.0f;

	logger.trace("%s: %f", event.getMessage(), parameterValue);

	// the integer part
	strobesForIntegerPartCount = (int8_t) parameterValue;

	// the decimal part
	strobesForDecimalPartCount = ((int8_t) (parameterValue * 10)) % 10;

	Device().lightnessDimmer.setState(OnOffState::OFF); // light could be ON!
	Device().lightnessDimmer.setMainLevel(MainLightLevel::MED);
	Device().getTaskManager().StartTask(this);
	setRemainingTime(0);
	return true;
}

inline void ParameterCheckMode::onExitState() {
	Device().getTaskManager().StopTask(this);
}

inline void ParameterCheckMode::OnUpdate(uint32_t deltaTime) {
	if (strobesForIntegerPartCount <= 0
			&& strobesForDecimalPartCount == 0) {

		/*
		 * signal finished
		 */
		Device().enterState(Device().offMode);
		return;
	}

	Device().lightnessDimmer.toggleState();

	int8_t *pCounterToDecrement;
	float intervalMultiplier;

	if (strobesForIntegerPartCount >= 0) {

		/*
		 * Is an integer or the comma
		 */
		pCounterToDecrement = &strobesForIntegerPartCount;

		if (strobesForIntegerPartCount == 0
				&& Device().lightnessDimmer.getState()
						== OnOffState::ON) {
			intervalMultiplier = PAR_CHECK_COMMA_DUTY_CYCLE;
		} else {
			intervalMultiplier = PAR_CHECK_DIGIT_DUTY_CYCLE;
		}

	} else {

		/*
		 * Is a decimal
		 */
		pCounterToDecrement = &strobesForDecimalPartCount;
		intervalMultiplier = PAR_CHECK_DIGIT_DUTY_CYCLE;
	}

	if (Device().lightnessDimmer.getState() == OnOffState::OFF) {
		--*pCounterToDecrement;
		intervalMultiplier = 1.0f - intervalMultiplier;
	}

	setTimeInterval(MsToTaskTime(PAR_CHECK_STROBE_PERIOD_MS * intervalMultiplier));
}
