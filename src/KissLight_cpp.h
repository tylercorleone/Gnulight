#include "KissLight.h"

inline KissLight::KissLight(LightDriver &lightDriver, const char *name) :
        Device(offMode, name), lightDriver(lightDriver) {
    lightDriver.maxBrightnessActuator = new GradualCappablePotentiometerActuator(
            DELAY_BETWEEN_LEVEL_CHANGE, taskManager, lightDriver, "maxBrightnessActuator");
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
