#include "LightDriver.h"

inline LightDriver::LightDriver() :
        CappablePotentiometer("lightDriver", KISS_LIGHT_LOG_LEVEL) {}

inline void LightDriver::setMaxValue() {
    maxBrightnessActuator->setMaxValueGradually(
            _min(tempCausedLimit, battCausedLimit), STEP_UP_DOWN_TRANSITION_DURATION);
}

inline void LightDriver::setBatteryCausedLimit(float limit) {
    battCausedLimit = limit;
    setMaxValue();
}

inline void LightDriver::setTemperatureCausedLimit(float limit) {
    tempCausedLimit = limit;
    setMaxValue();
}
