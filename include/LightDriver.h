#ifndef LIGHT_DRIVER_H
#define LIGHT_DRIVER_H

#include <Components.h>

class LightDriver : public TimedPotentiometer {
    friend class KissLight;

public:
    explicit LightDriver(TaskManager &taskManager);

    void setBatteryCausedMaxValue(float limit);

    void setTemperatureCausedMaxValue(float limit);

private:
    float batteryCausedMaxValue = 1.0f;
    float temperatureCausedMaxValue = 1.0f;
};

#endif
