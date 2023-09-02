#include "light-modes/ConstantLightMode.h"

inline ConstantLightMode::ConstantLightMode(KissLight &kissLight) :
        DeviceAware(kissLight), State("ConstMode") {

}

inline bool ConstantLightMode::onEntering(ButtonEvent *event) {
    MainLightLevel mainLevel;

    switch (event->getClicksCount()) {
        case 0:
            // long press
            mainLevel = MainLightLevel::MIN;
            break;
        case 1:
            mainLevel = MainLightLevel::MAX;
            break;
        case 2:
            mainLevel = MainLightLevel::MED;
            break;
        default:
            return false;
    }

    getDevice().lightnessDimmer.setMainLevel(mainLevel, MAIN_LEVEL_TRANSITION_DURATION);
    getDevice().lightnessDimmer.setState(OnOffState::ON);

    return true;
}

inline bool ConstantLightMode::onEventHandling(ButtonEvent *event) {
    switch (event->getClicksCount()) {
        case 0:
            // long press
            getDevice().lightnessDimmer.setNextMainLevel(MAIN_LEVEL_TRANSITION_DURATION);
            return true;
        case 1:
            getDevice().enterState(getDevice().offMode);
            return true;
        case 2:
            getDevice().lightnessDimmer.setNextSubLevel(MAIN_LEVEL_TRANSITION_DURATION);
            return true;
        default:
            return false;
    }
}

