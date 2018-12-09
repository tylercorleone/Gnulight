#include "BatteryMonitor.h"

inline BatteryMonitor::BatteryMonitor(Gnulight &gnulight, Battery &battery) :
		Task(BATTERY_MONITOR_INTERVAL_MS), DeviceAware(gnulight), Component(
				" battMon"), battery(battery) {
}

inline bool BatteryMonitor::OnStart() {
	remainingChargeCausingStepdown = 1.0f;
	OnUpdate(0);
	return true;
}

inline void BatteryMonitor::OnStop() {
	Device().lightDriver.setBatteryCausedLimit(1.0f);
}

inline void BatteryMonitor::OnUpdate(uint32_t deltaTime) {
	float remainingCharge = battery.getRemainingCharge();

	logger.debug("batt. %d%%", _round(remainingCharge * 100));

	if (remainingCharge > remainingChargeCausingStepdown) {

		/*
		 * recharged
		 */
		if (remainingCharge < (remainingChargeCausingStepdown + BATTERY_MONITOR_FILTERED_RECHARGE_AMOUNT)) {

			/*
			 * but not sufficiently
			 */
			return;
		}
	}

	remainingChargeCausingStepdown = remainingCharge;

	float batteryCausedLimit = BATTERY_CHARGE_TO_LIGHT_LIMIT(remainingCharge);

	logger.trace("limit %f", batteryCausedLimit);

	Device().lightDriver.setBatteryCausedLimit(batteryCausedLimit);

	if (batteryCausedLimit == 0.0) {
		BATTERY_MONITOR_ON_EMPTY_BATTERY();
	}
}

inline void BatteryMonitor::onEmptyBattery() {
	logger.warn("empty batt!");
	Device().enterState(Device().offMode);
}
