#include "light-modes/OffMode.h"
#include "KissLight.h"

inline OffMode::OffMode(KissLight &kissLight) :
        DeviceAware(kissLight), State("OffMode") {
}

inline bool OffMode::onEntering(ButtonEvent *event) {
    getDevice().switchTo(OnOffState::OFF);
    return true;
}

inline bool OffMode::onExiting(ButtonEvent *event) {
    getDevice().switchTo(OnOffState::ON);
    return true;
}

inline bool OffMode::onEventHandling(ButtonEvent *event) {

    switch (event->getClicksCount()) {
        case 0: // long press
        case 1:
        case 2:
            getDevice().enterState(getDevice().constantLightMode, event);
            return true;
        case 3:
            getDevice().enterState(getDevice().strobeMode, event);
            return true;
        case 4:
            getDevice().enterState(getDevice().parameterCheckMode,
                                   &getDevice().parameterCheckMode.BATTERY_CHECK_MSG);
            return true;
        case 5:
            getDevice().enterState(getDevice().parameterCheckMode,
                                   &getDevice().parameterCheckMode.LAMP_TEMPERATURE_CHECK_MSG);
            return true;
        case 6:
            getDevice().lightnessDimmer.isLightnessSimulationEnabled(
                    !getDevice().lightnessDimmer.isLightnessSimulationEnabled());
            return true;
        default:
            return false;
    }
}
