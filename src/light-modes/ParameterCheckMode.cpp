#include "light-modes/ParameterCheckMode.h"
#include "KissLight.h"

ButtonEvent ParameterCheckMode::BATTERY_CHECK_MSG = ButtonEvent(0, 0);
ButtonEvent ParameterCheckMode::LAMP_TEMPERATURE_CHECK_MSG = ButtonEvent(1, 0);

ParameterCheckMode::ParameterCheckMode(KissLight &kissLight) :
        DeviceAware(kissLight),
        State("ParChkMode", KISS_LIGHT_DEFAULT_APPENDER_LEVEL),
        Task(0) {}

bool ParameterCheckMode::onEntering(ButtonEvent *event) {
    float parameterValue;

    if (event == &BATTERY_CHECK_MSG
        && getDevice().pBatteryMonitor != nullptr) {
        logger.trace("checking battery");

        /*
         * battery check
         */
        parameterValue = getDevice().pBatteryMonitor->battery.getRemainingCharge()
                         * 10.0f;
        parameterValue = components_round(parameterValue);
    } else if (event == &LAMP_TEMPERATURE_CHECK_MSG
               && getDevice().pTempMonitor != nullptr) {
        logger.trace("checking temperature");

        /*
         * temperature check
         */
        parameterValue = getDevice().pTempMonitor->readTemperature() / 10.0f;
    } else {
        return false;
    }

    // lets round to the first decimal
    parameterValue *= 10.0f;
    parameterValue = components_round(parameterValue) / 10.0f;

    logger.trace("value: %f", parameterValue);

    // the integer part
    strobesForIntegerPartCount = (int8_t) parameterValue;

    // the decimal part
    strobesForDecimalPartCount = ((int8_t) (parameterValue * 10)) % 10;

    getDevice().lightnessDriver.setState(OnOffState::OFF); // light could be ON!
    getDevice().lightnessDriver.setMainLevel(MainLightLevel::MED);
    getDevice().getTaskManager().StartTask(this);
    setRemainingTime(0);
    return true;
}

bool ParameterCheckMode::onExiting(ButtonEvent *event) {
    getDevice().getTaskManager().StopTask(this);
    return true;
}

void ParameterCheckMode::OnUpdate(uint32_t deltaTime) {
    if (strobesForIntegerPartCount <= 0
        && strobesForDecimalPartCount == 0) {

        /*
         * signal finished
         */
        getDevice().enterState(getDevice().offMode);
        return;
    }

    getDevice().lightnessDriver.toggleState();

    int8_t *pCounterToDecrement;
    float intervalMultiplier;

    if (strobesForIntegerPartCount >= 0) {

        /*
         * Is an integer or the comma
         */
        pCounterToDecrement = &strobesForIntegerPartCount;

        if (strobesForIntegerPartCount == 0
            && getDevice().lightnessDriver.getState() == OnOffState::ON) {
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

    if (getDevice().lightnessDriver.getState() == OnOffState::OFF) {
        --*pCounterToDecrement;
        intervalMultiplier = 1.0f - intervalMultiplier;
    }

    setTimeInterval(MsToTaskTime(PAR_CHECK_STROBE_PERIOD_MS * intervalMultiplier));
}
