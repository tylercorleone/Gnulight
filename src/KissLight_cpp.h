#include "KissLight.h"

inline KissLight::KissLight(LightDriver &lightDriver) :
        Device(offMode, "KissLight", KISS_LIGHT_LOG_LEVEL),
        lightDriver(lightDriver) {

    lightDriver.maxBrightnessActuator = new GradualCappablePotentiometerActuator(
            DELAY_BETWEEN_LEVEL_CHANGE, taskManager, lightDriver,
            "maxLightSetter", KISS_LIGHT_LOG_LEVEL
    );
}

inline void KissLight::switchTo(OnOffState state) {
    logger.debug("switching %s", state == OnOffState::ON ? "ON" : "OFF");

    currentPowerState = state;

    if (state == OnOffState::ON) {
        if (pBatteryMonitor != nullptr) {
            taskManager.StartTask(pBatteryMonitor);
        }

        if (pTempMonitor != nullptr) {
            taskManager.StartTask(pTempMonitor);
        }

        onSwitchOn();

    } else {
        if (pBatteryMonitor != nullptr) {
            taskManager.StopTask(pBatteryMonitor);
        }

        if (pTempMonitor != nullptr) {
            taskManager.StopTask(pTempMonitor);
        }

        lightnessDimmer.setState(OnOffState::OFF);

        onSwitchOff();
    }
}

inline OnOffState KissLight::getPowerState() {
    return currentPowerState;
}
