#include "LightDriver.h"
#include "kiss-light-config.h"

LightDriver::LightDriver(TaskManager &taskManager) :
        TimedPotentiometer(DELAY_BETWEEN_LEVEL_CHANGE_MS, taskManager, "lightDriver",
                           KISS_LIGHT_DEFAULT_APPENDER_LEVEL) {}

void LightDriver::setBatteryCausedMaxValue(float limit) {
    batteryCausedMaxValue = limit;
    float maxValue = components_min(temperatureCausedMaxValue, batteryCausedMaxValue);
    setMaxValueGradually(maxValue, STEP_UP_DOWN_TRANSITION_DURATION);
}

void LightDriver::setTemperatureCausedMaxValue(float limit) {
    temperatureCausedMaxValue = limit;
    float maxValue = components_min(temperatureCausedMaxValue, batteryCausedMaxValue);
    setMaxValueGradually(maxValue, STEP_UP_DOWN_TRANSITION_DURATION);
}
