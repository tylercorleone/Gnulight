#include "light-modes/OffMode.h"
#include "KissLight.h"

OffMode::OffMode(KissLight &kissLight) :
        DeviceAware(kissLight),
        State("OffMode", KISS_LIGHT_DEFAULT_APPENDER_LEVEL) {}

bool OffMode::onEntering(ButtonEvent *event) {
    getDevice().switchTo(OnOffState::OFF);
    return true;
}

bool OffMode::onExiting(ButtonEvent *event) {
    getDevice().switchTo(OnOffState::ON);
    return true;
}

bool OffMode::onEventHandling(ButtonEvent *event) {

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
            getDevice().enterState(getDevice().parameterCheckMode, &ParameterCheckMode::BATTERY_CHECK_MSG);
            return true;
        case 5:
            getDevice().enterState(getDevice().parameterCheckMode, &ParameterCheckMode::LAMP_TEMPERATURE_CHECK_MSG);
            return true;
        case 6:
            getDevice().lightnessDriver.isLightnessSimulationEnabled(
                    !getDevice().lightnessDriver.isLightnessSimulationEnabled());
            return true;
        default:
            return false;
    }
}
