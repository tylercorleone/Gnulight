#ifndef LITHIUMBATTERYMONITOR_H
#define LITHIUMBATTERYMONITOR_H

#include "gnulight_config.h"

#include <Components.h>
#include <stdint.h>
#include <stddef.h>
#include <Task.h>

#define BATTERY_LEVEL_MONITORING_INTERVAL_MS 15000
#define FILTERED_RECHARGE_AMOUNT 0.15f

class Gnulight;

class BatteryMonitor: public Task, public DeviceAware<Gnulight>, public Named {
public:
	BatteryMonitor(Gnulight &gnulight, Battery &battery);
	const Battery &battery;
private:
	bool OnStart() override;
	void OnStop() override;
	void OnUpdate(uint32_t deltaTime) override;
	float calculateInstantaneousMaxCurrent(float remainingCharge);
	void onEmptyBattery();
	float remainingChargeCausingStepdown = 1.0f;
};

#endif
