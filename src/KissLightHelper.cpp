#include "KissLightHelper.h"

inline KissLightHelper::KissLightHelper(KissLight &instance) :
        instance(instance) {}

inline KissLightHelper KissLightHelper::customize(KissLight &kissLight) {
    return KissLightHelper{kissLight};
}

inline KissLightHelper &KissLightHelper::configureBatteryMonitor(
        Battery &battery) {
    instance.pBatteryMonitor = new BatteryMonitor(instance, battery);
    return *this;
}

inline KissLightHelper &KissLightHelper::configureBatteryMonitor(
        float voltageEmpty, float voltageFull, float (*readVoltageFunc)()) {
    LinearBattery *pBattery = new LinearBattery(readVoltageFunc, voltageEmpty, voltageFull);
    instance.pBatteryMonitor = new BatteryMonitor(instance, *pBattery);
    return *this;
}

inline KissLightHelper &KissLightHelper::configureTemperatureMonitor(
        float (*temperatureReadFunc)()) {
    instance.pTempMonitor = new TempMonitor(instance, temperatureReadFunc);
    return *this;
}
