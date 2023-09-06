#include "KissLight.h"

inline KissLight::KissLight(LightDriver &lightDriver) :
        Device(offMode, "KissLight", KISS_LIGHT_DEFAULT_APPENDER_LEVEL),
        lightDriver(lightDriver) {}

inline void KissLight::switchTo(OnOffState state) {
    logger.info("switching %s", state == OnOffState::ON ? "ON" : "OFF");

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

        lightnessDriver.setState(OnOffState::OFF);

        onSwitchOff();
    }
}

inline OnOffState KissLight::getPowerState() {
    return currentPowerState;
}
