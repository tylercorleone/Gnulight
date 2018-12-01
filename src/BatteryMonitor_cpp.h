#include "BatteryMonitor.h"

inline BatteryMonitor::BatteryMonitor(Gnulight &gnulight, Battery &battery) :
		Task(BATTERY_LEVEL_MONITORING_INTERVAL_MS), DeviceAware(gnulight), Named(
				"battMonitor"), battery(battery) {
}

inline bool BatteryMonitor::OnStart() {
	remainingChargeCausingStepdown = 1.0f;
	OnUpdate(0);
	return true;
}

inline void BatteryMonitor::OnStop() {
	Device().brightnessDriver.setBatteryCausedLimit(1.0f);
}

inline void BatteryMonitor::OnUpdate(uint32_t deltaTime) {
	float remainingCharge = battery.getRemainingCharge();

	debugIfNamed("batt: %f", remainingCharge);

	if (remainingCharge > remainingChargeCausingStepdown) {

		/*
		 * recharged
		 */
		if (remainingCharge < (remainingChargeCausingStepdown + FILTERED_RECHARGE_AMOUNT)) {

			/*
			 * but not sufficiently
			 */
			return;
		}
	}

	remainingChargeCausingStepdown = remainingCharge;

	float batteryCausedLimit = calculateInstantaneousMaxCurrent(
			remainingCharge);

	debugIfNamed("limit: %f", batteryCausedLimit);

	Device().brightnessDriver.setBatteryCausedLimit(batteryCausedLimit);

	if (batteryCausedLimit == 0.0) {
		onEmptyBattery();
	}
}

inline float BatteryMonitor::calculateInstantaneousMaxCurrent(float remainingCharge) {
	if (remainingCharge <= 0.0f) {
		return 0.0;
	} else if (remainingCharge < 0.05f) {
		return 0.05f;
	} else if (remainingCharge < 0.15f) {
		return 0.1f;
	} else if (remainingCharge < 0.25f) {
		return 0.25f;
	} else if (remainingCharge < 0.35f) {
		return 0.5f;
	}

	return 1.0f;
}

inline void BatteryMonitor::onEmptyBattery() {
	infoIfNamed("Empty batt.!");
	Device().enterState(Device().parameterCheckMode,
			MessageEvent(Device().parameterCheckMode.BATTERY_CHECK_MSG));
}
