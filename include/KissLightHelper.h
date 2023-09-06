#ifndef KISS_LIGHT_HELPER_H
#define KISS_LIGHT_HELPER_H

#include "KissLight.h"

class KissLightHelper {
public:
    static KissLightHelper customize(KissLight &kissLight);

    KissLightHelper &configureBatteryMonitor(Battery &battery);

    KissLightHelper &configureBatteryMonitor(float voltageEmpty,
                                             float voltageFull, float (*readVoltageFunc)());

    KissLightHelper &configureTemperatureMonitor(float (*temperatureReadFunc)());

private:
    KissLightHelper(KissLight &instance);

    KissLight &instance;
};

#endif
