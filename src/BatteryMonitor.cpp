#include "BatteryMonitor.h"
#include "KissLight.h"
#include <commons/components_utilities.h>

inline BatteryMonitor::BatteryMonitor(KissLight &kissLight, Battery &battery) :
        Task(BATTERY_MONITOR_INTERVAL_MS),
        DeviceAware(kissLight),
        Component("batteryMonitor", KISS_LIGHT_DEFAULT_APPENDER_LEVEL),
        battery(battery) {}

inline bool BatteryMonitor::OnStart() {
    remainingChargeCausingStepdown = 1.0f;
    setRemainingTime(0);
    return true;
}

inline void BatteryMonitor::OnStop() {
    getDevice().lightDriver.setBatteryCausedMaxValue(1.0f);
}

inline void BatteryMonitor::OnUpdate(uint32_t deltaTime) {
    float remainingCharge = battery.getRemainingCharge();

    logger.debug("batt: %d%%", components_round(remainingCharge * 100.0f));

    if (remainingCharge > remainingChargeCausingStepdown
        && remainingCharge
           < (remainingChargeCausingStepdown
              + BATTERY_MONITOR_FILTERED_RECHARGE_AMOUNT)) {

        /*
         * recharged but not sufficiently
         */
        return;
    }

    float batteryCausedLimit = BATTERY_CHARGE_TO_LIGHT_LIMIT(
            remainingChargeCausingStepdown = remainingCharge);

    getDevice().lightDriver.setBatteryCausedMaxValue(batteryCausedLimit);

    if (batteryCausedLimit == 0.0) {
        BATTERY_MONITOR_ON_EMPTY_BATTERY();
    }
}

inline void BatteryMonitor::onEmptyBattery() {
    logger.warn("empty battery!");
    getDevice().enterState(getDevice().offMode);
}
