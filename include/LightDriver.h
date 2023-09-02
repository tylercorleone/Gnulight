#ifndef KISS_LIGHT_LIGHT_DRIVER_H
#define KISS_LIGHT_LIGHT_DRIVER_H

#include "config.h"

#include <Components.h>
#include <stdint.h>

class LightDriver : public CappablePotentiometer {
    friend class KissLight;

public:
    LightDriver(const char *name = "lightDriver") :
            CappablePotentiometer(name) {}

    void updateLevelMaxValue();

    void setBatteryCausedLimit(float limit);

    void setTemperatureCausedLimit(float limit);

private:
    float battCausedLimit = 1.0f;
    float tempCausedLimit = 1.0f;
    // gets initialized in KissLight constructor
    GradualCappablePotentiometerActuator *maxBrightnessActuator;
};

#endif
